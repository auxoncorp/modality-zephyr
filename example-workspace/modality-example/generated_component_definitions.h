/*
 * GENERATED CODE, DO NOT EDIT
 *
 * Component:
 *   Name: modality-component
 *   ID: 923c69c3-95c4-48cc-b62b-982924de6665
 *   Code hash: 0247b5f4b3e6b33778b0acb0e9f033db2475e993508e727f8bc676a4843d7534
 *   Instrumentation hash: 04908eca4727f1dafcdde1e2fc84ef2b39e62012e65cd862ec2416c24788e79a
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
 * Events (sha3-256 65ba300d0e39ae740c6f32b6d0c06baf545b414b5c7978b154adfae79c6f77dc)
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
 * Name: TASK_DELAY
 * Description: Zephyr task delay
 * Component ID: 923c69c3-95c4-48cc-b62b-982924de6665
 * Tags: Zephyr;task
 * Payload type: u32
 * Location: :
 */
#define TASK_DELAY (65530UL)

/*
 * Name: TASK_DELAY_UNTIL
 * Description: Zephyr task delay until
 * Component ID: 923c69c3-95c4-48cc-b62b-982924de6665
 * Tags: Zephyr;task
 * Payload type: u32
 * Location: :
 */
#define TASK_DELAY_UNTIL (65529UL)

/*
 * Name: QUEUE_SEND
 * Description: Zephyr queue send
 * Component ID: 923c69c3-95c4-48cc-b62b-982924de6665
 * Tags: Zephyr;queue
 * Payload type: u32
 * Location: :
 */
#define QUEUE_SEND (65435UL)

/*
 * Name: QUEUE_SEND_BLOCKED
 * Description: Zephyr queue send blocked
 * Component ID: 923c69c3-95c4-48cc-b62b-982924de6665
 * Tags: Zephyr;queue
 * Payload type: u32
 * Location: :
 */
#define QUEUE_SEND_BLOCKED (65434UL)

/*
 * Name: QUEUE_SEND_FAILED
 * Description: Zephyr queue send failed
 * Component ID: 923c69c3-95c4-48cc-b62b-982924de6665
 * Tags: FAILURE;Zephyr;queue
 * Payload type: u32
 * Location: :
 */
#define QUEUE_SEND_FAILED (65433UL)

/*
 * Name: QUEUE_SEND_FRONT
 * Description: Zephyr queue send front
 * Component ID: 923c69c3-95c4-48cc-b62b-982924de6665
 * Tags: Zephyr;queue
 * Payload type: u32
 * Location: :
 */
#define QUEUE_SEND_FRONT (65432UL)

/*
 * Name: QUEUE_SEND_FRONT_BLOCKED
 * Description: Zephyr queue send front blocked
 * Component ID: 923c69c3-95c4-48cc-b62b-982924de6665
 * Tags: Zephyr;queue
 * Payload type: u32
 * Location: :
 */
#define QUEUE_SEND_FRONT_BLOCKED (65431UL)

/*
 * Name: QUEUE_SEND_FRONT_FAILED
 * Description: Zephyr queue send front failed
 * Component ID: 923c69c3-95c4-48cc-b62b-982924de6665
 * Tags: FAILURE;Zephyr;queue
 * Payload type: u32
 * Location: :
 */
#define QUEUE_SEND_FRONT_FAILED (65430UL)

/*
 * Name: QUEUE_SEND_FROMISR
 * Description: Zephyr queue send fromisr
 * Component ID: 923c69c3-95c4-48cc-b62b-982924de6665
 * Tags: Zephyr;queue;ISR
 * Payload type: u32
 * Location: :
 */
#define QUEUE_SEND_FROMISR (65429UL)

/*
 * Name: QUEUE_SEND_FROMISR_FAILED
 * Description: Zephyr queue send fromisr failed
 * Component ID: 923c69c3-95c4-48cc-b62b-982924de6665
 * Tags: FAILURE;Zephyr;queue;ISR
 * Payload type: u32
 * Location: :
 */
#define QUEUE_SEND_FROMISR_FAILED (65428UL)

/*
 * Name: QUEUE_SEND_FRONT_FROMISR
 * Description: Zephyr queue send front fromisr
 * Component ID: 923c69c3-95c4-48cc-b62b-982924de6665
 * Tags: Zephyr;queue;ISR
 * Payload type: u32
 * Location: :
 */
#define QUEUE_SEND_FRONT_FROMISR (65427UL)

/*
 * Name: QUEUE_SEND_FRONT_FROMISR_FAILED
 * Description: Zephyr queue send front fromisr failed
 * Component ID: 923c69c3-95c4-48cc-b62b-982924de6665
 * Tags: FAILURE;Zephyr;queue;ISR
 * Payload type: u32
 * Location: :
 */
#define QUEUE_SEND_FRONT_FROMISR_FAILED (65426UL)

/*
 * Name: QUEUE_RECEIVE
 * Description: Zephyr queue receive
 * Component ID: 923c69c3-95c4-48cc-b62b-982924de6665
 * Tags: Zephyr;queue
 * Payload type: u32
 * Location: :
 */
#define QUEUE_RECEIVE (65335UL)

/*
 * Name: QUEUE_RECEIVE_BLOCKED
 * Description: Zephyr queue receive blocked
 * Component ID: 923c69c3-95c4-48cc-b62b-982924de6665
 * Tags: Zephyr;queue
 * Payload type: u32
 * Location: :
 */
#define QUEUE_RECEIVE_BLOCKED (65334UL)

/*
 * Name: QUEUE_RECEIVE_FAILED
 * Description: Zephyr queue receive failed
 * Component ID: 923c69c3-95c4-48cc-b62b-982924de6665
 * Tags: FAILURE;Zephyr;queue
 * Payload type: u32
 * Location: :
 */
#define QUEUE_RECEIVE_FAILED (65333UL)

/*
 * Name: QUEUE_RECEIVE_FROMISR
 * Description: Zephyr queue receive fromisr
 * Component ID: 923c69c3-95c4-48cc-b62b-982924de6665
 * Tags: Zephyr;queue;ISR
 * Payload type: u32
 * Location: :
 */
#define QUEUE_RECEIVE_FROMISR (65332UL)

/*
 * Name: QUEUE_RECEIVE_FROMISR_FAILED
 * Description: Zephyr queue receive fromisr failed
 * Component ID: 923c69c3-95c4-48cc-b62b-982924de6665
 * Tags: FAILURE;Zephyr;queue;ISR
 * Payload type: u32
 * Location: :
 */
#define QUEUE_RECEIVE_FROMISR_FAILED (65331UL)

/*
 * Name: SEMAPHORE_GIVE
 * Description: Zephyr semaphore give
 * Component ID: 923c69c3-95c4-48cc-b62b-982924de6665
 * Tags: Zephyr;semaphore
 * Payload type: u32
 * Location: :
 */
#define SEMAPHORE_GIVE (65235UL)

/*
 * Name: SEMAPHORE_GIVE_BLOCKED
 * Description: Zephyr semaphore give blocked
 * Component ID: 923c69c3-95c4-48cc-b62b-982924de6665
 * Tags: Zephyr;semaphore
 * Payload type: u32
 * Location: :
 */
#define SEMAPHORE_GIVE_BLOCKED (65234UL)

/*
 * Name: SEMAPHORE_GIVE_FAILED
 * Description: Zephyr semaphore give failed
 * Component ID: 923c69c3-95c4-48cc-b62b-982924de6665
 * Tags: FAILURE;Zephyr;semaphore
 * Payload type: u32
 * Location: :
 */
#define SEMAPHORE_GIVE_FAILED (65233UL)

/*
 * Name: SEMAPHORE_GIVE_FROMISR
 * Description: Zephyr semaphore give fromisr
 * Component ID: 923c69c3-95c4-48cc-b62b-982924de6665
 * Tags: Zephyr;semaphore;ISR
 * Payload type: u32
 * Location: :
 */
#define SEMAPHORE_GIVE_FROMISR (65232UL)

/*
 * Name: SEMAPHORE_GIVE_FROMISR_FAILED
 * Description: Zephyr semaphore give fromisr failed
 * Component ID: 923c69c3-95c4-48cc-b62b-982924de6665
 * Tags: FAILURE;Zephyr;semaphore;ISR
 * Payload type: u32
 * Location: :
 */
#define SEMAPHORE_GIVE_FROMISR_FAILED (65231UL)

/*
 * Name: SEMAPHORE_TAKE
 * Description: Zephyr semaphore take
 * Component ID: 923c69c3-95c4-48cc-b62b-982924de6665
 * Tags: Zephyr;semaphore
 * Payload type: u32
 * Location: :
 */
#define SEMAPHORE_TAKE (65135UL)

/*
 * Name: SEMAPHORE_TAKE_BLOCKED
 * Description: Zephyr semaphore take blocked
 * Component ID: 923c69c3-95c4-48cc-b62b-982924de6665
 * Tags: Zephyr;semaphore
 * Payload type: u32
 * Location: :
 */
#define SEMAPHORE_TAKE_BLOCKED (65134UL)

/*
 * Name: SEMAPHORE_TAKE_FAILED
 * Description: Zephyr semaphore take failed
 * Component ID: 923c69c3-95c4-48cc-b62b-982924de6665
 * Tags: FAILURE;Zephyr;semaphore
 * Payload type: u32
 * Location: :
 */
#define SEMAPHORE_TAKE_FAILED (65133UL)

/*
 * Name: SEMAPHORE_TAKE_FROMISR
 * Description: Zephyr semaphore take fromisr
 * Component ID: 923c69c3-95c4-48cc-b62b-982924de6665
 * Tags: Zephyr;semaphore;ISR
 * Payload type: u32
 * Location: :
 */
#define SEMAPHORE_TAKE_FROMISR (65132UL)

/*
 * Name: SEMAPHORE_TAKE_FROMISR_FAILED
 * Description: Zephyr semaphore take fromisr failed
 * Component ID: 923c69c3-95c4-48cc-b62b-982924de6665
 * Tags: FAILURE;Zephyr;semaphore;ISR
 * Payload type: u32
 * Location: :
 */
#define SEMAPHORE_TAKE_FROMISR_FAILED (65131UL)

/*
 * Name: MUTEX_GIVE
 * Description: Zephyr mutex give
 * Component ID: 923c69c3-95c4-48cc-b62b-982924de6665
 * Tags: Zephyr;mutex
 * Payload type:
 * Location: :
 */
#define MUTEX_GIVE (65035UL)

/*
 * Name: MUTEX_GIVE_BLOCKED
 * Description: Zephyr mutex give blocked
 * Component ID: 923c69c3-95c4-48cc-b62b-982924de6665
 * Tags: Zephyr;mutex
 * Payload type:
 * Location: :
 */
#define MUTEX_GIVE_BLOCKED (65034UL)

/*
 * Name: MUTEX_GIVE_FAILED
 * Description: Zephyr mutex give failed
 * Component ID: 923c69c3-95c4-48cc-b62b-982924de6665
 * Tags: FAILURE;Zephyr;mutex
 * Payload type:
 * Location: :
 */
#define MUTEX_GIVE_FAILED (65033UL)

/*
 * Name: MUTEX_TAKE
 * Description: Zephyr mutex take
 * Component ID: 923c69c3-95c4-48cc-b62b-982924de6665
 * Tags: Zephyr;mutex
 * Payload type:
 * Location: :
 */
#define MUTEX_TAKE (64935UL)

/*
 * Name: MUTEX_TAKE_BLOCKED
 * Description: Zephyr mutex take blocked
 * Component ID: 923c69c3-95c4-48cc-b62b-982924de6665
 * Tags: Zephyr;mutex
 * Payload type:
 * Location: :
 */
#define MUTEX_TAKE_BLOCKED (64934UL)

/*
 * Name: MUTEX_TAKE_FAILED
 * Description: Zephyr mutex take failed
 * Component ID: 923c69c3-95c4-48cc-b62b-982924de6665
 * Tags: FAILURE;Zephyr;mutex
 * Payload type:
 * Location: :
 */
#define MUTEX_TAKE_FAILED (64933UL)

/*
 * Name: RX_MSG
 * Description: Received message
 * Component ID: 923c69c3-95c4-48cc-b62b-982924de6665
 * Tags: EXPECTATION;SEVERITY_10;app;ipc
 * Payload type: u32
 * Location: main.c:89
 */
#define RX_MSG (65536UL)

/*
 * Name: PRODUCING
 * Description: Producing message
 * Component ID: 923c69c3-95c4-48cc-b62b-982924de6665
 * Tags: app;ipc
 * Payload type: u32
 * Location: main.c:57
 */
#define PRODUCING (65537UL)

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MODALITY_PROBE_GENERATED_IDENTIFIERS_H */
