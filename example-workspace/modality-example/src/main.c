#include <zephyr.h>
#include <inttypes.h>
#include <assert.h>

/* Generated application event definitions */
#include "generated_component_definitions.h"

#define STACK_SIZE (2048)
#define PRODUCER_PRI -1
#define CONSUMER_PRI -1

static void producer_run(void);
K_THREAD_DEFINE(
        producer_thread,
        STACK_SIZE,
        producer_run,
        NULL, NULL, NULL,
        PRODUCER_PRI, 0, -1);

static void consumer_run(void);
K_THREAD_DEFINE(
        consumer_thread,
        STACK_SIZE,
        consumer_run,
        NULL, NULL, NULL,
        CONSUMER_PRI, 0, -1);

K_MSGQ_DEFINE(message_q, sizeof(uint32_t), 10, 4);

void main(void)
{
    printk("Modality Zephyr Example\n");

    k_thread_start(producer_thread);
    k_thread_start(consumer_thread);

    while(1)
    {
        k_msleep(1000);
        printk("Main loop\n");
    }
}

static void producer_run(void)
{
    int err;
    uint32_t val = 0;
    printk("Producer started\n");

    // This thread opts in to handling control plane messages for mutations/etc
    trace_alloc_control_plane_message_queue();

    modality_probe* probe = trace_get_thread_probe();
    assert(probe != NULL);

    while(1)
    {
        trace_process_control_plane_message();

        printk("Producing %" PRIu32 "\n", val);

        err = MODALITY_PROBE_RECORD_W_U32(
                    probe,
                    PRODUCING,
                    val,
                    MODALITY_TAGS("app", "ipc"),
                    "Producing message");
        assert(err == MODALITY_PROBE_ERROR_OK)

        err = k_msgq_put(&message_q, &val, K_FOREVER);
        assert(err == 0);
        val += 1;

        k_msleep(500);
    }
}

static void consumer_run(void)
{
    int err;
    uint32_t val;
    printk("Consumer started\n");

    modality_probe* probe = trace_get_thread_probe();
    assert(probe != NULL);

    while(1)
    {
        err = k_msgq_get(&message_q, &val, K_FOREVER);
        assert(err == 0);

        printk("Consuming %" PRIu32 "\n", val);

        err = MODALITY_PROBE_EXPECT(
                probe,
                RX_MSG,
                (val % 2 == 0),
                MODALITY_SEVERITY(10),
                MODALITY_TAGS("app", "ipc"),
                "Received message");
        assert(err == MODALITY_PROBE_ERROR_OK);
    }
}
