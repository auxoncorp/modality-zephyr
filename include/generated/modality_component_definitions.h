/*
 * GENERATED CODE, DO NOT EDIT
 *
 * Component:
 *   Name: zephyr-example-component
 *   ID: 2f7b0e9f-aa1d-4eda-87b5-6c88b8a7bf1f
 *   Code hash: a93a2872f06e261b8cd206d5615156ff6b154e0de81ad5fdddb198298d45d082
 *   Instrumentation hash: d8b97cf8fa96d08a6da4e7d39f8d3011f640898d6362cc8af092bdbc9536ad95
 */

#ifndef MODALITY_PROBE_GENERATED_IDENTIFIERS_H
#define MODALITY_PROBE_GENERATED_IDENTIFIERS_H

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Probes (sha3-256 9a3342c369c65ccde3684d15c81692594a316284f539ac1b10945c42c4f84743)
 */

/*
 * Name: PRODUCER
 * Description:
 * Component ID: 2f7b0e9f-aa1d-4eda-87b5-6c88b8a7bf1f
 * Tags:
 * Location: modapp/src/main.c:53
 */
#define PRODUCER (24850365UL)

/*
 * Name: CONSUMER
 * Description:
 * Component ID: 2f7b0e9f-aa1d-4eda-87b5-6c88b8a7bf1f
 * Tags:
 * Location: modapp/src/main.c:80
 */
#define CONSUMER (908247069UL)

/*
 * Name: MAIN
 * Description:
 * Component ID: 2f7b0e9f-aa1d-4eda-87b5-6c88b8a7bf1f
 * Tags:
 * Location: modapp/src/main.c:31
 */
#define MAIN (785032641UL)

/*
 * Events (sha3-256 a7ce504db53bc1e7035f5e947bac37caf0dddf58a9263389bf9aa7b61476e714)
 */

/*
 * Name: PRODUCER_STARTED
 * Description:
 * Component ID: 2f7b0e9f-aa1d-4eda-87b5-6c88b8a7bf1f
 * Tags:
 * Payload type:
 * Location: modapp/src/main.c:62
 */
#define PRODUCER_STARTED (1UL)

/*
 * Name: CONSUMER_STARTED
 * Description:
 * Component ID: 2f7b0e9f-aa1d-4eda-87b5-6c88b8a7bf1f
 * Tags:
 * Payload type:
 * Location: modapp/src/main.c:89
 */
#define CONSUMER_STARTED (2UL)

/*
 * Name: PRODUCER_SENT
 * Description:
 * Component ID: 2f7b0e9f-aa1d-4eda-87b5-6c88b8a7bf1f
 * Tags:
 * Payload type: u32
 * Location: modapp/src/main.c:70
 */
#define PRODUCER_SENT (3UL)

/*
 * Name: CONCUMER_RECEIVED
 * Description:
 * Component ID: 2f7b0e9f-aa1d-4eda-87b5-6c88b8a7bf1f
 * Tags:
 * Payload type: u32
 * Location: modapp/src/main.c:82
 */
#define CONCUMER_RECEIVED (4UL)

/*
 * Name: STARTUP_BEGIN
 * Description:
 * Component ID: 2f7b0e9f-aa1d-4eda-87b5-6c88b8a7bf1f
 * Tags:
 * Payload type:
 * Location: modapp/src/main.c:40
 */
#define STARTUP_BEGIN (5UL)

/*
 * Name: STARTUP_DONE
 * Description:
 * Component ID: 2f7b0e9f-aa1d-4eda-87b5-6c88b8a7bf1f
 * Tags:
 * Payload type:
 * Location: modapp/src/main.c:47
 */
#define STARTUP_DONE (6UL)

/*
 * Name: CONSUMER_RECEIVED
 * Description:
 * Component ID: 2f7b0e9f-aa1d-4eda-87b5-6c88b8a7bf1f
 * Tags:
 * Payload type: u32
 * Location: modapp/src/main.c:95
 */
#define CONSUMER_RECEIVED (7UL)

/*
 * Name: K_THREAD_CREATE
 * Description:
 * Component ID: 2f7b0e9f-aa1d-4eda-87b5-6c88b8a7bf1f
 * Tags: zephyr;syscall;thread
 * Payload type: u32
 * Location: modapp/src/modality_tracing.c:38
 */
#define K_THREAD_CREATE (8UL)

/*
 * Name: K_THREAD_START
 * Description:
 * Component ID: 2f7b0e9f-aa1d-4eda-87b5-6c88b8a7bf1f
 * Tags: zephyr;syscall;thread
 * Payload type: u32
 * Location: modapp/src/modality_tracing.c:47
 */
#define K_THREAD_START (9UL)

/*
 * Name: K_THREAD_SLEEP
 * Description:
 * Component ID: 2f7b0e9f-aa1d-4eda-87b5-6c88b8a7bf1f
 * Tags: zephyr;syscall;thread
 * Payload type: u32
 * Location: modapp/src/modality_tracing.c:58
 */
#define K_THREAD_SLEEP (10UL)

/*
 * Name: K_FIFO_GET
 * Description:
 * Component ID: 2f7b0e9f-aa1d-4eda-87b5-6c88b8a7bf1f
 * Tags: zephyr;syscall;fifo
 * Payload type: u32
 * Location: modapp/src/modality_tracing.c:67
 */
#define K_FIFO_GET (11UL)

/*
 * Name: K_FIFO_PUT
 * Description:
 * Component ID: 2f7b0e9f-aa1d-4eda-87b5-6c88b8a7bf1f
 * Tags: zephyr;syscall;fifo
 * Payload type: u32
 * Location: modapp/src/modality_tracing.c:76
 */
#define K_FIFO_PUT (12UL)

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MODALITY_PROBE_GENERATED_IDENTIFIERS_H */
