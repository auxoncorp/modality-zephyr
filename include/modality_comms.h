#pragma once
#include <zephyr.h>
#include <modality/probe.h>

int start_modality_comms(void);

#define PROBE_REGISTRY_OK 0
#define PROBE_REGISTRY_FULL -1

int8_t register_probe(modality_probe *probe, struct k_msgq *control_msgq);
void poll_control_plane_messages();

typedef struct probe_registry_entry {
  modality_probe *probe;
  /* struct k_fifo *control_fifo; */
  struct k_msgq *control_msgq;
  /* k_tid_t thread_id; */
} probe_registry_entry;

