/*
 * GENERATED CODE, DO NOT EDIT
 *
 * Component:
 *   Name: modality-component
 *   ID: 0acf9a64-951b-4bc0-a32d-e58af6845291
 *   Code hash: 0bc72238a876c9cf46ce2bcf626df2bcd9cb3fe4be542f2816924814ba073ac3
 *   Instrumentation hash: 301f721287753518497e279fac5ad34803f7ec33e908e2c6935cc80f5dd37367
 */

#ifndef MODALITY_PROBE_GENERATED_IDENTIFIERS_H
#define MODALITY_PROBE_GENERATED_IDENTIFIERS_H

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Probes (sha3-256 c98e53e712959b22d84d24538048920e90c95dbdd359808e7b0905f54ac82b09)
 */

/*
 * Name: CONSUMER_THREAD
 * Description: Zephyr thread 'consumer_thread'
 * Component ID: 0acf9a64-951b-4bc0-a32d-e58af6845291
 * Tags: Zephyr;task
 * Location: :
 */
#define CONSUMER_THREAD (63422UL)

/*
 * Name: PRODUCER_THREAD
 * Description: Zephyr thread 'producer_thread'
 * Component ID: 0acf9a64-951b-4bc0-a32d-e58af6845291
 * Tags: Zephyr;task
 * Location: :
 */
#define PRODUCER_THREAD (45765UL)

/*
 * Events (sha3-256 192f4866960ac105f22ea5af36088632c08005c604451b46219a09083d409584)
 */

/*
 * Name: THREAD_CREATE
 * Description: Zephyr thread create
 * Component ID: 0acf9a64-951b-4bc0-a32d-e58af6845291
 * Tags: Zephyr;thread
 * Payload type: i32
 * Location: :
 */
#define THREAD_CREATE (65534UL)

/*
 * Name: THREAD_SWITCHED_IN
 * Description: Zephyr thread switched in
 * Component ID: 0acf9a64-951b-4bc0-a32d-e58af6845291
 * Tags: Zephyr;thread
 * Payload type: i32
 * Location: :
 */
#define THREAD_SWITCHED_IN (65533UL)

/*
 * Name: THREAD_SWITCHED_OUT
 * Description: Zephyr thread switched out
 * Component ID: 0acf9a64-951b-4bc0-a32d-e58af6845291
 * Tags: Zephyr;thread
 * Payload type:
 * Location: :
 */
#define THREAD_SWITCHED_OUT (65532UL)

/*
 * Name: THREAD_SUSPEND
 * Description: Zephyr thread suspend
 * Component ID: 0acf9a64-951b-4bc0-a32d-e58af6845291
 * Tags: Zephyr;thread
 * Payload type: u32
 * Location: :
 */
#define THREAD_SUSPEND (65531UL)

/*
 * Name: THREAD_SLEEP
 * Description: Zephyr thread sleep
 * Component ID: 0acf9a64-951b-4bc0-a32d-e58af6845291
 * Tags: Zephyr;thread
 * Payload type: u32
 * Location: :
 */
#define THREAD_SLEEP (65530UL)

/*
 * Name: THREAD_MSLEEP
 * Description: Zephyr thread msleep
 * Component ID: 0acf9a64-951b-4bc0-a32d-e58af6845291
 * Tags: Zephyr;thread
 * Payload type: i32
 * Location: :
 */
#define THREAD_MSLEEP (65529UL)

/*
 * Name: THREAD_USLEEP
 * Description: Zephyr thread usleep
 * Component ID: 0acf9a64-951b-4bc0-a32d-e58af6845291
 * Tags: Zephyr;thread
 * Payload type: i32
 * Location: :
 */
#define THREAD_USLEEP (65528UL)

/*
 * Name: PRODUCING
 * Description: Producing message
 * Component ID: 0acf9a64-951b-4bc0-a32d-e58af6845291
 * Tags: app;ipc
 * Payload type: u32
 * Location: main.c:62
 */
#define PRODUCING (65536UL)

/*
 * Name: RX_MSG
 * Description: Received message
 * Component ID: 0acf9a64-951b-4bc0-a32d-e58af6845291
 * Tags: EXPECTATION;SEVERITY_10;app;ipc
 * Payload type: u32
 * Location: main.c:94
 */
#define RX_MSG (65537UL)

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MODALITY_PROBE_GENERATED_IDENTIFIERS_H */
