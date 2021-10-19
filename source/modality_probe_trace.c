#include <init.h>
#include <kernel.h>

#ifdef CONFIG_MODALITY_PROBE_TRACING

#include "modality_probe_trace.h"
#include "modality_probe_events.h"

#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <modality/probe.h>

typedef struct
{
    void* tcb; /* k_tid_t */
    uint32_t probe_id;
    modality_probe* probe;
    modality_probe_causal_snapshot snapshot;
} tcb_probe_s;

static volatile uint32_t g_is_enabled = 0;
static const char* g_error_msg = NULL;
static k_tid_t g_current_tcb = NULL;
static k_tid_t g_prev_tcb = NULL;
static tcb_probe_s g_tcb_probes[CONFIG_MODALITY_PROBE_MAX_PROBES] = { { NULL } };
static uint16_t g_excluded_task_probe_ids[CONFIG_MODALITY_PROBE_MAX_EXCLUDED_THREADS] = { 0 };
#ifdef CONFIG_MODALITY_PROBE_USE_STATIC_ALLOCATION
static uint8_t g_probe_storage[CONFIG_MODALITY_PROBE_STATIC_STORAGE_SIZE];
static size_t g_next_storage_index = 0;
#endif /* CONFIG_MODALITY_PROBE_USE_STATIC_ALLOCATION */

#ifdef CONFIG_MODALITY_PROBE_INCLUDE_IO_THREAD
const char TRACE_IO_THREAD_NAME[] = CONFIG_MODALITY_PROBE_IO_THREAD_NAME;
static K_THREAD_STACK_DEFINE(g_io_thread_stack, CONFIG_MODALITY_PROBE_IO_THREAD_STACK_SIZE);
static struct k_thread g_io_thread_tcb = { 0 };
static uint8_t g_io_buffer[CONFIG_MODALITY_PROBE_IO_THREAD_BUFFER_SIZE] = { 0 };

static void io_thread_entry(void *p1, void *p2, void *p3);
static void io_thread_probe_report_iter_fn(modality_probe* probe);
static void io_thread_probe_mutator_announcement_iter_fn(modality_probe* probe);
#endif /* CONFIG_MODALITY_PROBE_INCLUDE_IO_THREAD */

/* Internal functions */
static uint8_t* alloc_storage(size_t size_bytes);
static modality_probe* alloc_probe(size_t size_bytes, uint32_t probe_id);
static void add_tcb_probe(k_tid_t thread, uint32_t probe_id, modality_probe* probe);
static tcb_probe_s* get_tcb_probe(k_tid_t thread);
static int is_task_excluded(uint16_t probe_id);
static uint16_t probe_id_hash(const char* task_name, uint8_t length);

void trace_enable(void)
{
    TRACE_ALLOC_CRITICAL_SECTION();

    if(g_is_enabled != 0)
    {
        /* Already enabled */
        return;
    }

    TRACE_ENTER_CRITICAL_SECTION();

    g_is_enabled = 1;

    TRACE_EXIT_CRITICAL_SECTION();
}

void trace_disable(void)
{
    g_is_enabled = 0;
}

int trace_is_enabled(void)
{
    return g_is_enabled != 0;
}

const char* trace_get_error(void)
{
    return g_error_msg;
}

void trace_exclude_thread(const char* name)
{
    int i;
    uint16_t probe_id;
    int slot_was_found = 0;
    TRACE_ALLOC_CRITICAL_SECTION();

    TRACE_ENTER_CRITICAL_SECTION();

    probe_id = probe_id_hash(name, STRLEN(name));

    for(i = 0; i < CONFIG_MODALITY_PROBE_MAX_EXCLUDED_THREADS; i += 1)
    {
        if(g_excluded_task_probe_ids[i] == 0)
        {
            g_excluded_task_probe_ids[i] = probe_id;
            slot_was_found = 1;
            break;
        }
    }

    if(slot_was_found == 0)
    {
        trace_error("No more excluded task slots available, increase CONFIG_MODALITY_PROBE_MAX_EXCLUDED_THREADS");
    }

    TRACE_EXIT_CRITICAL_SECTION();
}

modality_probe* trace_get_thread_probe(void)
{
    modality_probe* probe = NULL;
    k_tid_t thread = k_current_get();

    if(thread != NULL)
    {
        if(thread->custom_data != NULL)
        {
            probe = ((tcb_probe_s*) thread->custom_data)->probe;
        }
    }

    return probe;
}

void trace_probe_iterator(trace_probe_iterator_function_t iterator_function)
{
    int i;

    if(iterator_function != NULL)
    {
        for(i = 0; i < CONFIG_MODALITY_PROBE_MAX_PROBES; i += 1)
        {
            if(g_tcb_probes[i].probe != NULL)
            {
                iterator_function(g_tcb_probes[i].probe);
            }
        }
    }
}

/* Private functions */
void trace_error(const char* msg)
{
    trace_disable();

    if(g_error_msg == NULL)
    {
        g_error_msg = msg;
        TRACE_DEBUG_PRINTF("TRACE ERROR: %s\n", msg);
    }
}

void trace_register_thread_probe(k_tid_t thread, uint32_t priority)
{
    size_t err;
    uint16_t probe_id;
    int is_excluded;
    modality_probe *probe = NULL;
    TRACE_ALLOC_CRITICAL_SECTION();

    TRACE_ENTER_CRITICAL_SECTION();

    if(g_is_enabled != 0)
    {
        const char* task_name = k_thread_name_get(thread);
        const uint8_t name_len = (uint8_t) STRLEN(task_name);
        if((task_name != NULL) && (name_len != 0))
        {
            probe_id = probe_id_hash(task_name, name_len);

            is_excluded = is_task_excluded(probe_id);

            if(is_excluded == 0)
            {
                TRACE_DEBUG_PRINTF("Registering probe ID %lu for task '%s'\n", (unsigned long) probe_id, task_name);
                probe = alloc_probe(CONFIG_MODALITY_PROBE_THREAD_PROBE_SIZE, (uint32_t) probe_id);
            }

            if(probe != NULL)
            {
                add_tcb_probe(thread, (uint32_t) probe_id, probe);

                err = modality_probe_record_event_with_payload(probe, TRACE_EVENT_TASK_CREATE, priority);
                TRACE_ASSERT(err == 0, "Failed to record initial task creation event", MPT_UNUSED);
            }
        }
    }

    TRACE_EXIT_CRITICAL_SECTION();
}

void trace_produce_snapshot(void)
{
    size_t err;
    tcb_probe_s* tcb_probe;
    TRACE_ALLOC_CRITICAL_SECTION();

    TRACE_ENTER_CRITICAL_SECTION();

    if((g_is_enabled != 0) && (g_current_tcb != NULL))
    {
        tcb_probe = get_tcb_probe(g_current_tcb);
        TRACE_ASSERT(
                tcb_probe != NULL,
                "No tcb_probe_s associated with the current task (1)",
                MPT_UNUSED);

        if(tcb_probe != NULL)
        {
            err = modality_probe_produce_snapshot(tcb_probe->probe, &tcb_probe->snapshot);
            TRACE_ASSERT(err == 0, "Failed to produce Modality probe snapshot", MPT_UNUSED);
        }
    }

    TRACE_EXIT_CRITICAL_SECTION();
}


void trace_merge_snapshot(void)
{
    size_t err;
    tcb_probe_s* curr;
    tcb_probe_s* prev;
    TRACE_ALLOC_CRITICAL_SECTION();

    TRACE_ENTER_CRITICAL_SECTION();

    if((g_is_enabled != 0) && (g_current_tcb != NULL) && (g_prev_tcb != NULL))
    {
        curr = get_tcb_probe(g_current_tcb);
        TRACE_ASSERT(
                curr != NULL,
                "No tcb_probe_s associated with the current task (2)",
                MPT_UNUSED);

        prev = get_tcb_probe(g_prev_tcb);
        TRACE_ASSERT(
                prev != NULL,
                "No tcb_probe_s associated with the previous task",
                MPT_UNUSED);

        err = modality_probe_merge_snapshot(curr->probe, &prev->snapshot);
        TRACE_ASSERT(err == 0, "Failed to merge Modality probe snapshot", MPT_UNUSED);
    }

    TRACE_EXIT_CRITICAL_SECTION();
}


void trace_log_event(uint32_t id)
{
    size_t err;
    tcb_probe_s* tcb_probe;
    TRACE_ALLOC_CRITICAL_SECTION();

    TRACE_ENTER_CRITICAL_SECTION();

    if((g_is_enabled != 0) && (g_current_tcb != NULL))
    {
        tcb_probe = get_tcb_probe(g_current_tcb);
        TRACE_ASSERT(
                tcb_probe != NULL,
                "No tcb_probe_s associated with the current task (3)",
                MPT_UNUSED);

        if(tcb_probe != NULL)
        {
            err = modality_probe_record_event(tcb_probe->probe, id);
            TRACE_ASSERT(err == 0, "Failed to log Modality event", MPT_UNUSED);
        }
    }

    TRACE_EXIT_CRITICAL_SECTION();
}


void trace_log_event_with_payload(uint32_t id, uint32_t payload)
{
    size_t err;
    tcb_probe_s* tcb_probe;
    TRACE_ALLOC_CRITICAL_SECTION();

    TRACE_ENTER_CRITICAL_SECTION();

    if((g_is_enabled != 0) && (g_current_tcb != NULL))
    {
        tcb_probe = get_tcb_probe(g_current_tcb);
        TRACE_ASSERT(
                tcb_probe != NULL,
                "No tcb_probe_s associated with the current task (4)",
                MPT_UNUSED);

        if(tcb_probe != NULL)
        {
            err = modality_probe_record_event_with_payload(tcb_probe->probe, id, payload);
            TRACE_ASSERT(err == 0, "Failed to log Modality event with payload", MPT_UNUSED);
        }
    }

    TRACE_EXIT_CRITICAL_SECTION();
}

int trace_thread_is_registered(k_tid_t thread)
{
    k_tid_t t = thread;

    if(t == NULL)
    {
        t = k_current_get();
    }

    return (t->custom_data != NULL);
}

int trace_switched_thread(void)
{
    int did_switch_tcb = 0;

    if(g_current_tcb != k_current_get())
    {
        g_prev_tcb = g_current_tcb;
        g_current_tcb = k_current_get();
        did_switch_tcb = 1;
    }

    return did_switch_tcb;
}

/* Internal functions */
static uint8_t* alloc_storage(size_t size_bytes)
{
    uint8_t* storage = NULL;

#ifdef CONFIG_MODALITY_PROBE_USE_STATIC_ALLOCATION
    if((g_next_storage_index + size_bytes) <= CONFIG_MODALITY_PROBE_STATIC_STORAGE_SIZE)
    {
        storage = &g_probe_storage[g_next_storage_index];
        g_next_storage_index += size_bytes;
    }
#else /* CONFIG_MODALITY_PROBE_USE_STATIC_ALLOCATION == 0 */
    storage = (uint8_t*) TRACE_MALLOC(size_bytes);
#endif /* CONFIG_MODALITY_PROBE_USE_STATIC_ALLOCATION */

    return storage;
}

static modality_probe* alloc_probe(size_t size_bytes, uint32_t probe_id)
{
    modality_probe* probe = NULL;

    uint8_t* storage = alloc_storage(size_bytes);
    if(storage == NULL)
    {
        trace_error("Failed to allocate probe storage, increase CONFIG_MODALITY_PROBE_STATIC_STORAGE_SIZE");
    }
    else if(probe_id != 0)
    {
        size_t err = modality_probe_initialize(
                storage,
                size_bytes,
                probe_id,
                MODALITY_PROBE_TIME_RESOLUTION_UNSPECIFIED,
                MODALITY_PROBE_WALL_CLOCK_ID_LOCAL_ONLY,
                NULL,
                NULL,
                &probe);
        TRACE_ASSERT(err == 0, "Failed to initialize Modality probe", NULL);
    }

    return probe;
}


static void add_tcb_probe(k_tid_t thread, uint32_t probe_id, modality_probe* probe)
{
    int i;
    size_t err;
    int slot_was_found = 0;

    for(i = 0; i < CONFIG_MODALITY_PROBE_MAX_PROBES; i += 1)
    {
        if(g_tcb_probes[i].tcb == NULL)
        {
            err = modality_probe_produce_snapshot(probe, &g_tcb_probes[i].snapshot);
            TRACE_ASSERT(err == 0, "Failed to produce Modality probe snapshot", MPT_UNUSED);
            g_tcb_probes[i].tcb = thread;
            g_tcb_probes[i].probe_id = probe_id;
            g_tcb_probes[i].probe = probe;
            thread->custom_data = &g_tcb_probes[i];
            slot_was_found = 1;
            break;
        }
    }

    if(slot_was_found == 0)
    {
        trace_error("No more TCB probe slots available, increase CONFIG_MODALITY_PROBE_MAX_PROBES");
    }
}

static tcb_probe_s* get_tcb_probe(k_tid_t thread)
{
    return (tcb_probe_s*) thread->custom_data;
}

static int is_task_excluded(uint16_t probe_id)
{
    int i;
    int is_excluded = 0;

    for(i = 0; i < CONFIG_MODALITY_PROBE_MAX_EXCLUDED_THREADS; i += 1)
    {
        if(g_excluded_task_probe_ids[i] == probe_id)
        {
            is_excluded = 1;
            break;
        }
    }

    return is_excluded;
}

/* CRC-16/IBM-3740 */
static uint16_t probe_id_hash(const char* task_name, uint8_t length)
{
    unsigned char x;
    uint16_t crc = 0xFFFF;

    TRACE_ASSERT(task_name != NULL, "Task name must not be NULL", 0);
    TRACE_ASSERT(length != 0, "Task name length == 0", 0);

    while(length-- != 0)
    {
        x = crc >> 8 ^ *task_name++;
        x ^= x >> 4;
        crc = (crc << 8) ^ ((uint16_t) (x << 12)) ^ ((uint16_t) (x << 5)) ^ ((uint16_t) x);
    }

    return crc;
}

#ifdef CONFIG_MODALITY_PROBE_DO_STARTUP_INITIALIZATION
static int trace_pre_kernel_init(const struct device *dev)
{
    (void) dev;

    TRACE_DEBUG_PRINTF("Initializing tracing\n");
    trace_enable();
    trace_exclude_thread("idle 00");
    trace_exclude_thread("logging");
#ifdef CONFIG_MODALITY_PROBE_INCLUDE_IO_THREAD
    trace_exclude_thread(TRACE_IO_THREAD_NAME);
#endif

    return 0;
}

SYS_INIT(trace_pre_kernel_init, PRE_KERNEL_1, 99);
#endif /* CONFIG_MODALITY_PROBE_DO_STARTUP_INITIALIZATION */

#ifdef CONFIG_MODALITY_PROBE_INCLUDE_IO_THREAD
static int trace_post_kernel_init(const struct device *dev)
{
    (void) dev;

    k_thread_create(
            &g_io_thread_tcb,
            g_io_thread_stack,
            K_THREAD_STACK_SIZEOF(g_io_thread_stack),
            (k_thread_entry_t) io_thread_entry,
            NULL,
            NULL,
            NULL,
            CONFIG_MODALITY_PROBE_IO_THREAD_PRIORITY,
            0,
            K_NO_WAIT);

    k_thread_name_set(&g_io_thread_tcb, TRACE_IO_THREAD_NAME);

    return 0;
}

SYS_INIT(trace_post_kernel_init, POST_KERNEL, 99);

static void io_thread_entry(void *p1, void *p2, void *p3)
{
    (void) p1;
    (void) p2;
    (void) p3;
    size_t err;
    int32_t status;
    int32_t num_bytes;
    uint32_t target_probe_id;
    uint16_t iters = 0;

    k_msleep(CONFIG_MODALITY_PROBE_IO_THREAD_STARTUP_DELAY_MS);

    TRACE_IO_INIT();

    while(1)
    {
        /* Check for incoming control plane messages */
        num_bytes = 0;
        status = TRACE_IO_READ(&g_io_buffer[0], CONFIG_MODALITY_PROBE_IO_THREAD_BUFFER_SIZE, &num_bytes);

        if(status != 0)
        {
            trace_error("TRACE_IO_READ returned an error");
        }

        if((status == 0) && (num_bytes > 0))
        {
            /* TODO - control plane processing, task buffers and task-local processing method */
            (void) err;
            (void) target_probe_id;
        }

        /* Send probe reports */
        trace_probe_iterator(io_thread_probe_report_iter_fn);

        /* Send mutator announcements */
        if(iters > CONFIG_MODALITY_PROBE_IO_THREAD_ITERS_PER_MUTATOR_ANNOUNCEMENT)
        {
            iters = 0;
            trace_probe_iterator(io_thread_probe_mutator_announcement_iter_fn);
        }

        k_msleep(CONFIG_MODALITY_PROBE_IO_THREAD_DELAY_MS);

        iters += 1;
    }
}

static void io_thread_probe_report_iter_fn(modality_probe* probe)
{
    size_t err;
    int32_t status;
    size_t report_size_bytes = 0;
    int32_t num_bytes = 0;
    TRACE_ALLOC_CRITICAL_SECTION();

    TRACE_ENTER_CRITICAL_SECTION();

    err = modality_probe_report(
            probe,
            &g_io_buffer[0],
            CONFIG_MODALITY_PROBE_IO_THREAD_BUFFER_SIZE,
            &report_size_bytes);

    TRACE_EXIT_CRITICAL_SECTION();

    TRACE_ASSERT(err == 0, "Failed to generate Modality probe report", MPT_UNUSED);

    if(report_size_bytes != 0)
    {
        status = TRACE_IO_WRITE(&g_io_buffer[0], (uint32_t) report_size_bytes, &num_bytes);
        if(status != 0)
        {
            trace_error("TRACE_IO_WRITE returned an error (1)");
        }

        if(num_bytes != (int32_t) report_size_bytes)
        {
            TRACE_DEBUG_PRINTF(("TRACE_IO_WRITE sent partial report buffer\n"));
        }
    }
}

static void io_thread_probe_mutator_announcement_iter_fn(modality_probe* probe)
{
    size_t err;
    int32_t status;
    size_t anncmnt_size_bytes = 0;
    int32_t num_bytes = 0;
    TRACE_ALLOC_CRITICAL_SECTION();

    TRACE_ENTER_CRITICAL_SECTION();

    err = modality_probe_announce_mutators(
            probe,
            &g_io_buffer[0],
            CONFIG_MODALITY_PROBE_IO_THREAD_BUFFER_SIZE,
            &anncmnt_size_bytes);

    TRACE_EXIT_CRITICAL_SECTION();

    TRACE_ASSERT(err == 0, "Failed to generate Modality mutator announcement", MPT_UNUSED);

    if(anncmnt_size_bytes != 0)
    {
        status = TRACE_IO_WRITE(&g_io_buffer[0], (uint32_t) anncmnt_size_bytes, &num_bytes);
        if(status != 0)
        {
            trace_error("TRACE_IO_WRITE returned an error (2)");
        }

        if(num_bytes != (int32_t) anncmnt_size_bytes)
        {
            TRACE_DEBUG_PRINTF(("TRACE_IO_WRITE sent partial mutator announcement buffer\n"));
        }
    }
}
#endif /* CONFIG_MODALITY_PROBE_INCLUDE_IO_THREAD */

/* Modality probe API wrappers */
#ifdef CONFIG_MODALITY_PROBE_INCLUDE_USER_LEVEL_PROBE_MACROS

#define MPT_WP_API_WRAPPER(fn_suffix, type) \
    size_t MPT_CAT2(mpt_, fn_suffix)(modality_probe *probe, uint32_t event_id, type payload) \
    { \
        TRACE_ALLOC_CRITICAL_SECTION(); \
        TRACE_ENTER_CRITICAL_SECTION(); \
        const size_t err = MPT_CAT2(modality_probe_, fn_suffix)(probe, event_id, payload); \
        TRACE_EXIT_CRITICAL_SECTION(); \
        return err; \
    }

#define MPT_WP_WT_API_WRAPPER(fn_suffix, type) \
    size_t MPT_CAT2(mpt_, fn_suffix)(modality_probe *probe, uint32_t event_id, type payload, uint64_t time_ns) \
    { \
        TRACE_ALLOC_CRITICAL_SECTION(); \
        TRACE_ENTER_CRITICAL_SECTION(); \
        const size_t err = MPT_CAT2(modality_probe_, fn_suffix)(probe, event_id, payload, time_ns); \
        TRACE_EXIT_CRITICAL_SECTION(); \
        return err; \
    }

size_t mpt_record_event(modality_probe *probe, uint32_t event_id)
{
    TRACE_ALLOC_CRITICAL_SECTION();
    TRACE_ENTER_CRITICAL_SECTION();
    const size_t err = modality_probe_record_event(probe, event_id);
    TRACE_EXIT_CRITICAL_SECTION();
    return err;
}
size_t mpt_record_event_with_time(modality_probe *probe, uint32_t event_id, uint64_t time_ns)
{
    TRACE_ALLOC_CRITICAL_SECTION();
    TRACE_ENTER_CRITICAL_SECTION();
    const size_t err = modality_probe_record_event_with_time(probe, event_id, time_ns);
    TRACE_EXIT_CRITICAL_SECTION();
    return err;
}

MPT_WP_API_WRAPPER(record_event_with_payload_i8, int8_t)
MPT_WP_API_WRAPPER(record_event_with_payload_u8, uint8_t)
MPT_WP_API_WRAPPER(record_event_with_payload_i16, int16_t)
MPT_WP_API_WRAPPER(record_event_with_payload_u16, uint16_t)
MPT_WP_API_WRAPPER(record_event_with_payload_i32, int32_t)
MPT_WP_API_WRAPPER(record_event_with_payload_u32, uint32_t)
MPT_WP_API_WRAPPER(record_event_with_payload_bool, bool)
MPT_WP_API_WRAPPER(record_event_with_payload_f32, float)

MPT_WP_WT_API_WRAPPER(record_event_with_payload_i8_with_time, int8_t)
MPT_WP_WT_API_WRAPPER(record_event_with_payload_u8_with_time, uint8_t)
MPT_WP_WT_API_WRAPPER(record_event_with_payload_i16_with_time, int16_t)
MPT_WP_WT_API_WRAPPER(record_event_with_payload_u16_with_time, uint16_t)
MPT_WP_WT_API_WRAPPER(record_event_with_payload_i32_with_time, int32_t)
MPT_WP_WT_API_WRAPPER(record_event_with_payload_u32_with_time, uint32_t)
MPT_WP_WT_API_WRAPPER(record_event_with_payload_bool_with_time, bool)
MPT_WP_WT_API_WRAPPER(record_event_with_payload_f32_with_time, float)

size_t mpt_produce_snapshot(modality_probe *probe, modality_probe_causal_snapshot *snapshot)
{
    TRACE_ALLOC_CRITICAL_SECTION();
    TRACE_ENTER_CRITICAL_SECTION();
    const size_t err = modality_probe_produce_snapshot(probe, snapshot);
    TRACE_EXIT_CRITICAL_SECTION();
    return err;
}

size_t mpt_produce_snapshot_bytes(
        modality_probe *probe,
        uint8_t *history_destination,
        size_t history_destination_bytes,
        size_t *out_written_bytes)
{
    TRACE_ALLOC_CRITICAL_SECTION();
    TRACE_ENTER_CRITICAL_SECTION();
    const size_t err = modality_probe_produce_snapshot_bytes(
            probe,
            history_destination,
            history_destination_bytes,
            out_written_bytes);
    TRACE_EXIT_CRITICAL_SECTION();
    return err;
}

size_t mpt_merge_snapshot(
        modality_probe *probe,
        const modality_probe_causal_snapshot *snapshot)
{
    TRACE_ALLOC_CRITICAL_SECTION();
    TRACE_ENTER_CRITICAL_SECTION();
    const size_t err = modality_probe_merge_snapshot(probe, snapshot);
    TRACE_EXIT_CRITICAL_SECTION();
    return err;
}

size_t mpt_merge_snapshot_bytes(
        modality_probe *probe,
        const uint8_t *history_source,
        size_t history_source_bytes)
{
    TRACE_ALLOC_CRITICAL_SECTION();
    TRACE_ENTER_CRITICAL_SECTION();
    const size_t err = modality_probe_merge_snapshot_bytes(
            probe,
            history_source,
            history_source_bytes);
    TRACE_EXIT_CRITICAL_SECTION();
    return err;
}

#endif /* CONFIG_MODALITY_PROBE_INCLUDE_USER_LEVEL_PROBE_MACROS */

/* Tracing hooks */
void sys_trace_k_thread_create(struct k_thread *new_thread, int prio)
{
    if(new_thread->custom_data == NULL)
    {
        trace_register_thread_probe(new_thread, (uint32_t) prio);
    }
}

void sys_trace_k_thread_switched_out(void)
{
    if(trace_thread_is_registered(NULL))
    {
        trace_log_event(TRACE_EVENT_TASK_SWITCHED_OUT);
        trace_produce_snapshot();
    }
}

void sys_trace_k_thread_switched_in(void)
{
    if(trace_thread_is_registered(NULL))
    {
        if(trace_switched_thread())
        {
            trace_merge_snapshot();
        }
        trace_log_event_with_payload(TRACE_EVENT_TASK_SWITCHED_IN, (uint32_t) k_current_get()->base.prio);
    }
}

void sys_trace_k_thread_suspend(struct k_thread *thread)
{
    if(trace_thread_is_registered(NULL))
    {
        trace_log_event_with_payload(TRACE_EVENT_TASK_SUSPEND, (uint32_t) thread);
    }
}

#endif /* CONFIG_MODALITY_PROBE_TRACING */
