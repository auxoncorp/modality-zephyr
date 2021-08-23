#include <assert.h>
#include <modality/probe.h>
#include <stdio.h>

#include "generated/modality_component_definitions.h"
#include "irq.h"
#include "kernel.h"
#include "modality_comms.h"
#include "modality_tracing.h"

void modality_zephyr_k_thread_switched_in() {
#ifndef CONFIG_SMP
  static probe_registry_entry *last_entry = NULL;

  probe_registry_entry *current_entry = k_thread_custom_data_get();
  if (current_entry != NULL && current_entry != last_entry) {
    if (last_entry != NULL) {
      modality_probe_causal_snapshot last_probe_snapshot;
      int err;

      err = modality_probe_produce_snapshot(last_entry->probe,
                                                 &last_probe_snapshot);
      assert(err == MODALITY_PROBE_ERROR_OK);

      err = modality_probe_merge_snapshot(current_entry->probe,
                                               &last_probe_snapshot);
      assert(err == MODALITY_PROBE_ERROR_OK);
    }

    last_entry = current_entry;
  }
#endif
}

void modality_zephyr_k_thread_create(k_tid_t new_thread) {
  probe_registry_entry *current_entry = k_thread_custom_data_get();
  if (current_entry) {
    MODALITY_PROBE_RECORD_W_U32(current_entry->probe, K_THREAD_CREATE,
                                (uint32_t)&new_thread,
                                MODALITY_TAGS("zephyr", "syscall", "thread"));
  }
}

void modality_zephyr_k_thread_start(k_tid_t thread) {
  probe_registry_entry *current_entry = k_thread_custom_data_get();
  if (current_entry) {
    MODALITY_PROBE_RECORD_W_U32(current_entry->probe, K_THREAD_START,
                                (uint32_t)&thread,
                                MODALITY_TAGS("zephyr", "syscall", "thread"));
  }
}

void modality_zephyr_k_thread_sleep(k_timeout_t timeout) {
  /* printf("THREAD SLEEP %p (%s) %d\n", k_current_get(),
   * k_thread_name_get(k_current_get()), timeout.ticks); */
  probe_registry_entry *current_entry = k_thread_custom_data_get();
  if (current_entry) {
    MODALITY_PROBE_RECORD_W_U32(current_entry->probe, K_THREAD_SLEEP,
                                (uint32_t)timeout.ticks,
                                MODALITY_TAGS("zephyr", "syscall", "thread"));
  }
}

void modality_zephyr_k_fifo_get(struct k_fifo *fifo) {
  probe_registry_entry *current_entry = k_thread_custom_data_get();
  if (current_entry) {
    MODALITY_PROBE_RECORD_W_U32(current_entry->probe, K_FIFO_GET,
                                (uint32_t)fifo,
                                MODALITY_TAGS("zephyr", "syscall", "fifo"));
  }
}

void modality_zephyr_k_fifo_put(struct k_fifo *fifo) {
  probe_registry_entry *current_entry = k_thread_custom_data_get();
  if (current_entry) {
    MODALITY_PROBE_RECORD_W_U32(current_entry->probe, K_FIFO_PUT,
                                (uint32_t)fifo,
                                MODALITY_TAGS("zephyr", "syscall", "fifo"));
  }
}
