#ifndef MODALITY_PROBE_TRACE_H
#define MODALITY_PROBE_TRACE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stddef.h>

#include "modality_probe_port.h"
#include "modality_probe_zephyr.h"

#ifndef CONFIG_MODALITY_PROBE_TRACING
#define MODALITY_PROBE_MACROS_ENABLED 0
#define MODALITY_MUTATOR_MACROS_ENABLED 0
#endif

#include <modality/probe.h>
#include "modality_probe_macros.h"

#define MPT_UNUSED
#define MPT_NOOP_STATEMENT do {} while( 0 )

typedef void (*trace_probe_iterator_function_t)(modality_probe* probe);

#ifdef CONFIG_MODALITY_PROBE_TRACING

#ifdef CONFIG_SMP
#error "SMP is not supported yet"
#endif

#ifndef CONFIG_THREAD_CUSTOM_DATA
#error "Tracing requires the use of CONFIG_THREAD_CUSTOM_DATA, set CONFIG_THREAD_CUSTOM_DATA=y in Kconfig"
#endif

#ifndef CONFIG_THREAD_NAME
#error "Tracing requires the use of CONFIG_THREAD_NAME, set CONFIG_THREAD_NAME=y in Kconfig"
#endif

#ifdef CONFIG_MODALITY_PROBE_USE_PRINTK
#ifndef CONFIG_PRINTK
#error "CONFIG_MODALITY_PROBE_USE_PRINTK requires the use of CONFIG_PRINTK, set CONFIG_PRINTK=y in Kconfig"
#endif
#endif

#ifdef CONFIG_MODALITY_PROBE_INCLUDE_IO_THREAD
#include "modality_probe_io.h"

extern const char TRACE_IO_THREAD_NAME[];

#ifndef TRACE_IO_INIT
#error "TRACE_IO_INIT not defined, it is required to be defined in modality_probe_io.h when using the IO thread"
#endif

#ifndef TRACE_IO_READ
#error "TRACE_IO_READ not defined, it is required to be defined in modality_probe_io.h when using the IO thread"
#endif

#ifndef TRACE_IO_WRITE
#error "TRACE_IO_WRITE not defined, it is required to be defined in modality_probe_io.h when using the IO thread"
#endif

#endif /* CONFIG_MODALITY_PROBE_INCLUDE_IO_THREAD */

void trace_enable(void);
void trace_disable(void);
int trace_is_enabled(void);
const char* trace_get_error(void);
void trace_exclude_thread(const char* name);
modality_probe* trace_get_thread_probe(void);
void trace_probe_iterator(trace_probe_iterator_function_t iterator_function);

#ifdef CONFIG_MODALITY_PROBE_USE_TRACE_ASSERT
/* NOTE: When enabled, failing TRACE_ASSERT's may leave interrupts disabled to aid in debugging */
#define TRACE_ASSERT(eval, msg, ret) \
if (!(eval)) \
{ \
    trace_error("TRACE_ASSERT: " msg); \
    return ret; \
}
#else /* CONFIG_MODALITY_PROBE_USE_TRACE_ASSERT == 0 */
#define TRACE_ASSERT(eval, msg, ret) MPT_NOOP_STATEMENT
#endif /* CONFIG_MODALITY_PROBE_USE_TRACE_ASSERT */

#ifndef TRACE_DEBUG_PRINTF
#define TRACE_DEBUG_PRINTF(...) MPT_NOOP_STATEMENT
#endif

/* Private functions */
void trace_error(const char* msg);
void trace_register_thread_probe(k_tid_t thread, uint32_t priority);
void trace_produce_snapshot(void);
void trace_merge_snapshot(void);
void trace_log_event(uint32_t id);
void trace_log_event_with_payload(uint32_t id, uint32_t payload);
int trace_thread_is_registered(k_tid_t thread);
int trace_switched_thread(void);

#else /* CONFIG_MODALITY_PROBE_TRACING == 0 */

#define TRACE_ASSERT(eval, msg, ret) MPT_NOOP_STATEMENT

#ifndef TRACE_DEBUG_PRINTF
#define TRACE_DEBUG_PRINTF(...) MPT_NOOP_STATEMENT
#endif

#define TRACE_IO_THREAD_NAME ""

#define trace_enable() MPT_NOOP_STATEMENT
#define trace_disable() MPT_NOOP_STATEMENT
#define trace_is_enabled() (0)
#define trace_get_error() (NULL)
#define trace_exclude_thread(x) MPT_NOOP_STATEMENT
#define trace_get_thread_probe() (NULL)
#define trace_probe_iterator(x) MPT_NOOP_STATEMENT

#define TRACE_GET_CURRENT_TASK() (NULL)

#endif /* CONFIG_MODALITY_PROBE_TRACING */

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MODALITY_PROBE_TRACE_H */
