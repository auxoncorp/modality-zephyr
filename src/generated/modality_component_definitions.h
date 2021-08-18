/*
 * GENERATED CODE, DO NOT EDIT
 *
 * Component:
 *   Name: zephyr-example-component
 *   ID: 2f7b0e9f-aa1d-4eda-87b5-6c88b8a7bf1f
 *   Code hash: c5bb3ef22761a121eb0483de49e830573b78a42a1f86e3776e69bd41bbb5c8c9
 *   Instrumentation hash: b31af80186bd0f5ce746c99a70def5dcbdaad7c0b1e528c7c0144ec7c754768e
 */

#ifndef MODALITY_PROBE_GENERATED_IDENTIFIERS_H
#define MODALITY_PROBE_GENERATED_IDENTIFIERS_H

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Probes (sha3-256 957c96df15d0ca3134067ab61d42cd7e54eec4bebbe8c6fb04eae5df2709b616)
 */

/*
 * Name: PRODUCER
 * Description: Producer probe
 * Component ID: 2f7b0e9f-aa1d-4eda-87b5-6c88b8a7bf1f
 * Tags: zephyr;sample
 * Location: modapp/src/main.c:41
 */
#define PRODUCER (24850365UL)

/*
 * Name: CONSUMER
 * Description: Consumer probe
 * Component ID: 2f7b0e9f-aa1d-4eda-87b5-6c88b8a7bf1f
 * Tags: zephyr;sample
 * Location: modapp/src/main.c:67
 */
#define CONSUMER (908247069UL)

/*
 * Events (sha3-256 77a6de9f3f14d1d4bbb797ca8335b1ca6fbbb724e0b6d80b44b77f93b151fa5b)
 */

/*
 * Name: PRODUCER_STARTED
 * Description:
 * Component ID: 2f7b0e9f-aa1d-4eda-87b5-6c88b8a7bf1f
 * Tags:
 * Payload type:
 * Location: modapp/src/main.c:51
 */
#define PRODUCER_STARTED (1UL)

/*
 * Name: CONSUMER_STARTED
 * Description:
 * Component ID: 2f7b0e9f-aa1d-4eda-87b5-6c88b8a7bf1f
 * Tags:
 * Payload type:
 * Location: modapp/src/main.c:77
 */
#define CONSUMER_STARTED (2UL)

/*
 * Name: PRODUCER_SENT
 * Description:
 * Component ID: 2f7b0e9f-aa1d-4eda-87b5-6c88b8a7bf1f
 * Tags:
 * Payload type: u32
 * Location: modapp/src/main.c:58
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

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MODALITY_PROBE_GENERATED_IDENTIFIERS_H */
