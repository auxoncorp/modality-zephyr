/* Generated Modality mutator implementation for 'DELAY_MUTATOR' */

#include <stdint.h>
#include <stdbool.h>
#include <assert.h>

#include "modality/probe.h"
#include "modality/mutation_interface.h"

void *memcpy(void *dest, const void *src, size_t n);

typedef struct g_generated_state_s
{
    bool is_registered;
    bool is_injected;
    uint32_t delay_ms;
} g_generated_state_s;

static g_generated_state_s g_generated_state =
{
    .is_registered = false,
    .is_injected = false,
    .delay_ms = 200,
};

void * const g_generated_state_DELAY_MUTATOR = &g_generated_state;

static const modality_mutation_parameter_definition PARAM_DEFS_DELAY_MUTATOR[1] =
{
    [0] =
    {
        .param_type =
        {
            .tag = MUTATION_PARAM_TYPE_U32,
            .body.u32 =
            {
                .minimum_effect_value = 200,
                .nominal_range = { .inclusive_start = 0, .inclusive_end = 400 },
                .safety_range = { .inclusive_start = 0, .inclusive_end = 400 },
                .hard_range = { .inclusive_start = 0, .inclusive_end = 400 },
            },
        },
        .name = "delay-ms",
    },
};

const uint64_t HASH_DELAY_MUTATOR_delay_ms = 4030848773318608516ULL;

static const modality_mutation_definition MUTATOR_DEF_DELAY_MUTATOR =
{
    .name = "delay-mutator",
    .params = PARAM_DEFS_DELAY_MUTATOR,
    .params_length = 1,
    .tags = NULL,
    .tags_length = 0,
};

static size_t clear_mutations(
        void * const fi)
{
    assert(fi != NULL);
    g_generated_state_s * const state = (g_generated_state_s*) fi;
    state->is_injected = false;
    return 0;
}

static size_t get_definition(
        void * const fi,
        const modality_mutation_definition ** const definition)
{
    assert(fi != NULL);
    (*definition) = &MUTATOR_DEF_DELAY_MUTATOR;
    return 0;
}

static size_t inject_mutation(
        void * const fi,
        const modality_mutation_param * const params,
        const size_t params_length)
{
    assert(fi != NULL);
    g_generated_state_s * const state = (g_generated_state_s*) fi;
    assert(params != NULL);
    assert(params_length == 1);

    assert(params[0].tag == MUTATION_PARAM_U32);
    state->delay_ms = params[0].body.u32.value;

    state->is_injected = true;
    return 0;
}

static const modality_mutation_interface DELAY_MUTATOR =
{
    .state = (void*) &g_generated_state,
    .inject_mutation = &inject_mutation,
    .get_definition = &get_definition,
    .clear_mutations = &clear_mutations,
};

void mutate_DELAY_MUTATOR(
        modality_probe * const probe,
        void * const opaque_state,
        const uint64_t instrumentation_hash,
        void * const data,
        const size_t data_size)
{
    assert(probe != NULL);
    assert(opaque_state != NULL);
    assert(instrumentation_hash != 0);
    assert(data != NULL);
    assert(data_size != 0);

    g_generated_state_s * const state = (g_generated_state_s*) opaque_state;
    assert(state == &g_generated_state);

    if(state->is_registered == false)
    {
        state->is_registered = true;

        const size_t err = modality_probe_register_mutator(
                probe,
                &DELAY_MUTATOR);
        assert(err == MODALITY_PROBE_ERROR_OK);
    }

    if(state->is_injected == true)
    {
        if(instrumentation_hash == HASH_DELAY_MUTATOR_delay_ms)
        {
            assert(data_size == sizeof(state->delay_ms));
            (void) memcpy(data, &state->delay_ms, data_size);
        }
        else
        {
            assert(false); /* Got an unrecognized hash */
        }
    }
}
