/*
 * GENERATED CODE, DO NOT EDIT
 *
 * Component:
 *   Name: modality-component
 *   ID: 923c69c3-95c4-48cc-b62b-982924de6665
 *   Code hash: 0247b5f4b3e6b33778b0acb0e9f033db2475e993508e727f8bc676a4843d7534
 *   Instrumentation hash: 9c601a81a164a5c5ddbaa4d066bc01e8446ed68f1b2c596775035cbc04420c11
 */

#ifndef MODALITY_PROBE_GENERATED_IDENTIFIERS_H
#define MODALITY_PROBE_GENERATED_IDENTIFIERS_H

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Probes (sha3-256 d6b24cd87df09becbe7a5939065e7dd3b93136fd90f273521ba12b7f6fcdd65d)
 */

/*
 * Name: CONSUMER_THREAD
 * Description: Zephyr task 'consumer_thread'
 * Component ID: 923c69c3-95c4-48cc-b62b-982924de6665
 * Tags: Zephyr;task
 * Location: :
 */
#define CONSUMER_THREAD (63422UL)

/*
 * Name: PRODUCER_THREAD
 * Description: Zephyr task 'producer_thread'
 * Component ID: 923c69c3-95c4-48cc-b62b-982924de6665
 * Tags: Zephyr;task
 * Location: :
 */
#define PRODUCER_THREAD (45765UL)

/*
 * Events (sha3-256 ad1bb83dd541360d3290d846a0e8893c4e71f88960e16e4df47ba8542a2edb5b)
 */

/*
 * Name: TASK_CREATE
 * Description: Zephyr task create
 * Component ID: 923c69c3-95c4-48cc-b62b-982924de6665
 * Tags: Zephyr;task
 * Payload type: u32
 * Location: :
 */
#define TASK_CREATE (65534UL)

/*
 * Name: TASK_SWITCHED_IN
 * Description: Zephyr task switched in
 * Component ID: 923c69c3-95c4-48cc-b62b-982924de6665
 * Tags: Zephyr;task
 * Payload type: i32
 * Location: :
 */
#define TASK_SWITCHED_IN (65533UL)

/*
 * Name: TASK_SWITCHED_OUT
 * Description: Zephyr task switched out
 * Component ID: 923c69c3-95c4-48cc-b62b-982924de6665
 * Tags: Zephyr;task
 * Payload type:
 * Location: :
 */
#define TASK_SWITCHED_OUT (65532UL)

/*
 * Name: TASK_SUSPEND
 * Description: Zephyr task suspend
 * Component ID: 923c69c3-95c4-48cc-b62b-982924de6665
 * Tags: Zephyr;task
 * Payload type: u32
 * Location: :
 */
#define TASK_SUSPEND (65531UL)

/*
 * Name: TASK_SLEEP
 * Description: Zephyr task sleep
 * Component ID: 923c69c3-95c4-48cc-b62b-982924de6665
 * Tags: Zephyr;task
 * Payload type: u32
 * Location: :
 */
#define TASK_SLEEP (65530UL)

/*
 * Name: TASK_MSLEEP
 * Description: Zephyr task msleep
 * Component ID: 923c69c3-95c4-48cc-b62b-982924de6665
 * Tags: Zephyr;task
 * Payload type: i32
 * Location: :
 */
#define TASK_MSLEEP (65529UL)

/*
 * Name: TASK_USLEEP
 * Description: Zephyr task usleep
 * Component ID: 923c69c3-95c4-48cc-b62b-982924de6665
 * Tags: Zephyr;task
 * Payload type: i32
 * Location: :
 */
#define TASK_USLEEP (65528UL)

/*
 * Name: PRODUCING
 * Description: Producing message
 * Component ID: 923c69c3-95c4-48cc-b62b-982924de6665
 * Tags: app;ipc
 * Payload type: u32
 * Location: main.c:57
 */
#define PRODUCING (65536UL)

/*
 * Name: RX_MSG
 * Description: Received message
 * Component ID: 923c69c3-95c4-48cc-b62b-982924de6665
 * Tags: EXPECTATION;SEVERITY_10;app;ipc
 * Payload type: u32
 * Location: main.c:89
 */
#define RX_MSG (65537UL)

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MODALITY_PROBE_GENERATED_IDENTIFIERS_H */
