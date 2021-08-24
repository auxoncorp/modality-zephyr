#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <zephyr.h>

#define STACK_SIZE 4096
#define PRODUCER_PRI -1
#define CONSUMER_PRI -1

static void producer_run(void);
K_THREAD_DEFINE(producer_thread_id, STACK_SIZE, producer_run, NULL, NULL, NULL,
                PRODUCER_PRI, 0, -1);

static void consumer_run(void);
K_THREAD_DEFINE(consumer_thread_id, STACK_SIZE, consumer_run, NULL, NULL, NULL,
                CONSUMER_PRI, 0, -1);

K_FIFO_DEFINE(number_fifo);

void main(void) {
  k_thread_start(producer_thread_id);
  k_thread_start(consumer_thread_id);
}

static void producer_run(void) {
  uint32_t counter = 0;
  while (1) {
    counter++;
    printf("Producer sending %i\n", counter);
    k_fifo_put(&number_fifo, &counter);

    k_sleep(K_MSEC(200));
  }
}

static void consumer_run(void) {
  while (1) {
    uint32_t *num = k_fifo_get(&number_fifo, K_FOREVER);
    printf("Consumer got %i\n", *num);
  }
}
