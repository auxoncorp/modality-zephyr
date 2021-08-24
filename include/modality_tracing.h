#ifndef MODALITY_ZEPHYR_INCLUDE_MODALITY_TRACING_H_
#define MODALITY_ZEPHYR_INCLUDE_MODALITY_TRACING_H_

#include <kernel.h>

void modality_zephyr_k_thread_create(k_tid_t new_thread);
void modality_zephyr_k_thread_sleep(k_timeout_t timeout);
void modality_zephyr_k_thread_start(k_tid_t thread);
void modality_zephyr_k_thread_switched_in();
void modality_zephyr_k_fifo_get(struct k_fifo *fifo);
void modality_zephyr_k_fifo_put(struct k_fifo *fifo);

#endif
