#include <assert.h>
#include <modality/probe.h>
#include <stdio.h>
#include <stdlib.h>
#include <zephyr.h>

#include "generated/modality_component_definitions.h"
#include "modality_comms.h"

#define STACK_SIZE 4096
#define PRODUCER_PRI -1
#define CONSUMER_PRI -1

uint8_t g_main_probe_buffer[1024];
uint8_t g_producer_probe_buffer[1024];
uint8_t g_consumer_probe_buffer[1024];

static void producer_run(void);
K_THREAD_DEFINE(producer_thread_id, STACK_SIZE, producer_run, NULL, NULL, NULL,
                PRODUCER_PRI, 0, -1);

static void consumer_run(void);
K_THREAD_DEFINE(consumer_thread_id, STACK_SIZE, consumer_run, NULL, NULL, NULL,
                CONSUMER_PRI, 0, -1);

K_FIFO_DEFINE(number_fifo);

void main(void) {
  int err;
  modality_probe *probe = MODALITY_PROBE_NULL_INITIALIZER;
  err = MODALITY_PROBE_INIT(
      &g_main_probe_buffer[0], sizeof(g_main_probe_buffer), MAIN,
      MODALITY_PROBE_TIME_RESOLUTION_UNSPECIFIED,
      MODALITY_PROBE_WALL_CLOCK_ID_LOCAL_ONLY, NULL, NULL, &probe);
  assert(err == MODALITY_PROBE_ERROR_OK);

  err = register_probe(probe, NULL);
  assert(err == PROBE_REGISTRY_OK);

  MODALITY_PROBE_RECORD(probe, STARTUP_BEGIN);

  start_modality_comms();

  k_thread_start(producer_thread_id);
  k_thread_start(consumer_thread_id);

  MODALITY_PROBE_RECORD(probe, STARTUP_DONE);
}

static void producer_run(void) {
  int err;
  modality_probe *probe = MODALITY_PROBE_NULL_INITIALIZER;
  err = MODALITY_PROBE_INIT(
      &g_producer_probe_buffer[0], sizeof(g_producer_probe_buffer), PRODUCER,
      MODALITY_PROBE_TIME_RESOLUTION_UNSPECIFIED,
      MODALITY_PROBE_WALL_CLOCK_ID_LOCAL_ONLY, NULL, NULL, &probe);
  assert(err == MODALITY_PROBE_ERROR_OK);

  err = register_probe(probe, NULL);
  assert(err == PROBE_REGISTRY_OK);

  MODALITY_PROBE_RECORD(probe, PRODUCER_STARTED);

  uint32_t counter = 0;
  while (1) {
    counter++;
    printf("Producer sending %i\n", counter);
    k_fifo_put(&number_fifo, &counter);

    MODALITY_PROBE_RECORD_W_U32(probe, PRODUCER_SENT, counter);

    k_sleep(K_MSEC(200));
  }
}

static void consumer_run(void) {
  int err;

  modality_probe *probe = MODALITY_PROBE_NULL_INITIALIZER;
  err = MODALITY_PROBE_INIT(
      &g_consumer_probe_buffer[0], sizeof(g_consumer_probe_buffer), CONSUMER,
      MODALITY_PROBE_TIME_RESOLUTION_UNSPECIFIED,
      MODALITY_PROBE_WALL_CLOCK_ID_LOCAL_ONLY, NULL, NULL, &probe);
  assert(err == MODALITY_PROBE_ERROR_OK);

  err = register_probe(probe, NULL);
  assert(err == PROBE_REGISTRY_OK);

  MODALITY_PROBE_RECORD(probe, CONSUMER_STARTED);

  while (1) {
    uint32_t *num = k_fifo_get(&number_fifo, K_FOREVER);
    printf("Consumer got %i\n", *num);

    MODALITY_PROBE_RECORD_W_U32(probe, CONSUMER_RECEIVED, *num);
  }
}
