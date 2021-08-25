#include <assert.h>
#include <modality/probe.h>
#include <zephyr.h>

#include "generated/modality_component_definitions.h"
#include "modality_comms.h"
#include "modality_tracing.h"

void modality_zephyr_k_thread_switched_in() {
#ifndef CONFIG_SMP
  static modality_probe *last_probe = NULL;

  modality_probe *current_probe = current_thread_probe();
  if (current_probe != NULL && current_probe != last_probe) {
    if (last_probe != NULL) {
      modality_probe_causal_snapshot last_probe_snapshot;
      int err;

      err = modality_probe_produce_snapshot(last_probe, &last_probe_snapshot);
      assert(err == MODALITY_PROBE_ERROR_OK);

      err = modality_probe_merge_snapshot(current_probe, &last_probe_snapshot);
      assert(err == MODALITY_PROBE_ERROR_OK);
    }

    last_probe = current_probe;
  }
#endif
}

void modality_zephyr_k_thread_create(k_tid_t new_thread) {
  modality_probe *probe = current_thread_probe();
  if (probe) {
    MODALITY_PROBE_RECORD_W_U32(probe, K_THREAD_CREATE, (uint32_t)&new_thread,
                                MODALITY_TAGS("zephyr", "syscall", "thread"));
  }
}

void modality_zephyr_k_thread_start(k_tid_t thread) {
  modality_probe *probe = current_thread_probe();
  if (probe) {
    MODALITY_PROBE_RECORD_W_U32(probe, K_THREAD_START, (uint32_t)&thread,
                                MODALITY_TAGS("zephyr", "syscall", "thread"));
  }
}

void modality_zephyr_k_thread_sleep(k_timeout_t timeout) {
  modality_probe *probe = current_thread_probe();
  if (probe) {
    MODALITY_PROBE_RECORD_W_U32(probe, K_THREAD_SLEEP, (uint32_t)timeout.ticks,
                                MODALITY_TAGS("zephyr", "syscall", "thread"));
  }
}

void modality_zephyr_k_fifo_get(struct k_fifo *fifo) {
  modality_probe *probe = current_thread_probe();
  if (probe) {
    MODALITY_PROBE_RECORD_W_U32(probe, K_FIFO_GET, (uint32_t)fifo,
                                MODALITY_TAGS("zephyr", "syscall", "fifo"));
  }
}

void modality_zephyr_k_fifo_put(struct k_fifo *fifo) {
  modality_probe *probe = current_thread_probe();
  if (probe) {
    MODALITY_PROBE_RECORD_W_U32(probe, K_FIFO_PUT, (uint32_t)fifo,
                                MODALITY_TAGS("zephyr", "syscall", "fifo"));
  }
}
