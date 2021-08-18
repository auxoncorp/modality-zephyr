#pragma once
#include <kernel.h>
#include <modality/probe.h>

int start_modality_comms(void);
void stop_modality_comms(void);

#define PROBE_REGISTRY_OK 0
#define PROBE_REGISTRY_FULL -1
int8_t register_probe(modality_probe *probe, struct k_fifo *control_fifo);
