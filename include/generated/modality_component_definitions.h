/*
 * GENERATED CODE, DO NOT EDIT
 *
 * Component:
 *   Name: zephyr-example-component
 *   ID: 2f7b0e9f-aa1d-4eda-87b5-6c88b8a7bf1f
 *   Code hash: 9d2b8fddb6ef2466a2a31dc8de0275aec22bad53082c910d5dc0b7ccec3eb797
 *   Instrumentation hash: d8b97cf8fa96d08a6da4e7d39f8d3011f640898d6362cc8af092bdbc9536ad95
 */

#ifndef MODALITY_PROBE_GENERATED_IDENTIFIERS_H
#define MODALITY_PROBE_GENERATED_IDENTIFIERS_H

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Probes (sha3-256 2449658ce3e6af66a297fb8b9def7228c7b6cf9063b415380ce07fd7a7d85570)
 */

/*
 * Name: PRODUCER
 * Description:
 * Component ID: 2f7b0e9f-aa1d-4eda-87b5-6c88b8a7bf1f
 * Tags:
 * Location: modapp/src/main.c:58
 */
#define PRODUCER (24850365UL)

/*
 * Name: CONSUMER
 * Description:
 * Component ID: 2f7b0e9f-aa1d-4eda-87b5-6c88b8a7bf1f
 * Tags:
 * Location: modapp/src/main.c:86
 */
#define CONSUMER (908247069UL)

/*
 * Name: MAIN
 * Description:
 * Component ID: 2f7b0e9f-aa1d-4eda-87b5-6c88b8a7bf1f
 * Tags:
 * Location: modapp/src/main.c:36
 */
#define MAIN (785032641UL)

/*
 * Events (sha3-256 a909bcc92eae3b636e43869b5ddab1118102914f6c14bc7060c865c4cfbceb77)
 */

/*
 * Name: PRODUCER_STARTED
 * Description:
 * Component ID: 2f7b0e9f-aa1d-4eda-87b5-6c88b8a7bf1f
 * Tags:
 * Payload type:
 * Location: modapp/src/main.c:67
 */
#define PRODUCER_STARTED (1UL)

/*
 * Name: CONSUMER_STARTED
 * Description:
 * Component ID: 2f7b0e9f-aa1d-4eda-87b5-6c88b8a7bf1f
 * Tags:
 * Payload type:
 * Location: modapp/src/main.c:95
 */
#define CONSUMER_STARTED (2UL)

/*
 * Name: PRODUCER_SENT
 * Description:
 * Component ID: 2f7b0e9f-aa1d-4eda-87b5-6c88b8a7bf1f
 * Tags:
 * Payload type: u32
 * Location: modapp/src/main.c:76
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
 * Location: modapp/src/main.c:45
 */
#define STARTUP_BEGIN (5UL)

/*
 * Name: STARTUP_DONE
 * Description:
 * Component ID: 2f7b0e9f-aa1d-4eda-87b5-6c88b8a7bf1f
 * Tags:
 * Payload type:
 * Location: modapp/src/main.c:52
 */
#define STARTUP_DONE (6UL)

/*
 * Name: CONSUMER_RECEIVED
 * Description:
 * Component ID: 2f7b0e9f-aa1d-4eda-87b5-6c88b8a7bf1f
 * Tags:
 * Payload type: u32
 * Location: modapp/src/main.c:102
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
