/*
 * GENERATED CODE, DO NOT EDIT
 *
 * Component:
 *   Name: zephyr-example-component
 *   ID: 2f7b0e9f-aa1d-4eda-87b5-6c88b8a7bf1f
 *   Code hash: 80649425ea1215baac079b9f9693bc7c076b886da84941eea957616c0f229a59
 *   Instrumentation hash: d8b97cf8fa96d08a6da4e7d39f8d3011f640898d6362cc8af092bdbc9536ad95
 */

#ifndef MODALITY_PROBE_GENERATED_IDENTIFIERS_H
#define MODALITY_PROBE_GENERATED_IDENTIFIERS_H

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Probes (sha3-256 c3abf9f009c6d51ca0656d147b8c6ead4571fbfbfc6e4a31197ac338ca67e031)
 */

/*
 * Name: PRODUCER
 * Description:
 * Component ID: 2f7b0e9f-aa1d-4eda-87b5-6c88b8a7bf1f
 * Tags:
 * Location: modapp/src/main.c:57
 */
#define PRODUCER (24850365UL)

/*
 * Name: CONSUMER
 * Description:
 * Component ID: 2f7b0e9f-aa1d-4eda-87b5-6c88b8a7bf1f
 * Tags:
 * Location: modapp/src/main.c:92
 */
#define CONSUMER (908247069UL)

/*
 * Name: MAIN
 * Description:
 * Component ID: 2f7b0e9f-aa1d-4eda-87b5-6c88b8a7bf1f
 * Tags:
 * Location: modapp/src/main.c:35
 */
#define MAIN (785032641UL)

/*
 * Events (sha3-256 51c505ccb5cd6479e67c412c17ecdf24f2049e98270edd22a1319dec7099c76f)
 */

/*
 * Name: PRODUCER_STARTED
 * Description:
 * Component ID: 2f7b0e9f-aa1d-4eda-87b5-6c88b8a7bf1f
 * Tags:
 * Payload type:
 * Location: modapp/src/main.c:72
 */
#define PRODUCER_STARTED (1UL)

/*
 * Name: CONSUMER_STARTED
 * Description:
 * Component ID: 2f7b0e9f-aa1d-4eda-87b5-6c88b8a7bf1f
 * Tags:
 * Payload type:
 * Location: modapp/src/main.c:101
 */
#define CONSUMER_STARTED (2UL)

/*
 * Name: PRODUCER_SENT
 * Description:
 * Component ID: 2f7b0e9f-aa1d-4eda-87b5-6c88b8a7bf1f
 * Tags:
 * Payload type: u32
 * Location: modapp/src/main.c:82
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
 * Location: modapp/src/main.c:44
 */
#define STARTUP_BEGIN (5UL)

/*
 * Name: STARTUP_DONE
 * Description:
 * Component ID: 2f7b0e9f-aa1d-4eda-87b5-6c88b8a7bf1f
 * Tags:
 * Payload type:
 * Location: modapp/src/main.c:51
 */
#define STARTUP_DONE (6UL)

/*
 * Name: CONSUMER_RECEIVED
 * Description:
 * Component ID: 2f7b0e9f-aa1d-4eda-87b5-6c88b8a7bf1f
 * Tags:
 * Payload type: u32
 * Location: modapp/src/main.c:108
 */
#define CONSUMER_RECEIVED (7UL)

/*
 * Name: K_THREAD_CREATE
 * Description:
 * Component ID: 2f7b0e9f-aa1d-4eda-87b5-6c88b8a7bf1f
 * Tags: zephyr;syscall;thread
 * Payload type: u32
 * Location: modapp/src/modality_tracing.c:34
 */
#define K_THREAD_CREATE (8UL)

/*
 * Name: K_THREAD_START
 * Description:
 * Component ID: 2f7b0e9f-aa1d-4eda-87b5-6c88b8a7bf1f
 * Tags: zephyr;syscall;thread
 * Payload type: u32
 * Location: modapp/src/modality_tracing.c:42
 */
#define K_THREAD_START (9UL)

/*
 * Name: K_THREAD_SLEEP
 * Description:
 * Component ID: 2f7b0e9f-aa1d-4eda-87b5-6c88b8a7bf1f
 * Tags: zephyr;syscall;thread
 * Payload type: u32
 * Location: modapp/src/modality_tracing.c:50
 */
#define K_THREAD_SLEEP (10UL)

/*
 * Name: K_FIFO_GET
 * Description:
 * Component ID: 2f7b0e9f-aa1d-4eda-87b5-6c88b8a7bf1f
 * Tags: zephyr;syscall;fifo
 * Payload type: u32
 * Location: modapp/src/modality_tracing.c:58
 */
#define K_FIFO_GET (11UL)

/*
 * Name: K_FIFO_PUT
 * Description:
 * Component ID: 2f7b0e9f-aa1d-4eda-87b5-6c88b8a7bf1f
 * Tags: zephyr;syscall;fifo
 * Payload type: u32
 * Location: modapp/src/modality_tracing.c:66
 */
#define K_FIFO_PUT (12UL)

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MODALITY_PROBE_GENERATED_IDENTIFIERS_H */
