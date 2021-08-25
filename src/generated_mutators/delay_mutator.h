/* Generated Modality mutator header file for 'DELAY_MUTATOR' */

#ifndef DELAY_MUTATOR_H
#define DELAY_MUTATOR_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

extern const uint64_t HASH_DELAY_MUTATOR_delay_ms;

extern void * const g_generated_state_DELAY_MUTATOR;

void mutate_DELAY_MUTATOR(
        modality_probe * const probe,
        void * const opaque_state,
        const uint64_t instrumentation_hash,
        void * const data,
        const size_t data_size);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* DELAY_MUTATOR_H */
