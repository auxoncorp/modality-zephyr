#include <assert.h>
#include <errno.h>
#include <modality/probe.h>
#include <net/socket.h>
#include <stdio.h>
#include <zephyr.h>

#include "modality_comms.h"

/** How many probes can the registry hold? */
#define MODALITY_PROBE_REGISTRY_SIZE 4

/** What is the IP address of the machine that modality is running the
    collector on?*/
#define MODALITY_COLLECTOR_IP "192.0.2.2"

/** What port is the collector running on? This is configured in
    Modality.toml, in the 'collector_connections' key.*/
#define MODALITY_COLLECTOR_PORT 34333

/** How often should we try to send reports back to modality? If
    you're getting 'dropped events' messages, try reducing this
    value. */
#define MODALITY_REPORT_CADENCE K_MSEC(1000)

/** What port should we listen on for UDP control messages? This
    should match an entry in Modality.toml's 'control_connections'
    key. */
#define MODALITY_CONTROL_PLANE_PORT 34355

/** We need to run a thread for the control plane server. How big
    should its stack be? */
#define MODALITY_CONTROL_PLANE_STACK_SIZE 2048

/** What is the priority of the control plane server thread?*/
#define MODALITY_CONTROL_PLANE_PRIORITY -1

/** The size of the buffer used to recieve and move around control messages. */
#define MODALITY_CONTROL_MESSAGE_SIZE 124 // == 128 - 4

/** The maximum number of control messages that can be in-flight at once (inside
 * the zephyr application). */
#define MODALITY_CONTROL_MESSAGE_IN_FLIGHT_COUNT 4

static int g_collector_socket = -1;
static uint8_t g_report_buffer[1400];

static uint8_t g_announce_buffer[1400];
K_MUTEX_DEFINE(g_announce_buffer_mutex);

static void modality_control_plane_run(void);
K_THREAD_DEFINE(modality_control_plane_thread_id,
                MODALITY_CONTROL_PLANE_STACK_SIZE, modality_control_plane_run,
                NULL, NULL, NULL, MODALITY_CONTROL_PLANE_PRIORITY, 0, -1);

typedef struct probe_registry_entry {
  modality_probe *probe;
  struct k_msgq *control_msgq;
  bool sent_mutator_announcment;
} probe_registry_entry;

typedef struct probe_registry {
  probe_registry_entry entries[MODALITY_PROBE_REGISTRY_SIZE];
  uint8_t count;
} probe_registry;

static probe_registry g_probe_registry = {{{0}}};
K_MUTEX_DEFINE(g_probe_registry_mutex);

static void send_modality_reports(struct k_work *work);
K_WORK_DELAYABLE_DEFINE(send_modality_reports_delayable, send_modality_reports);

typedef struct control_message {
  size_t __reserved;
  atomic_t refcount;
  uint8_t data[MODALITY_CONTROL_MESSAGE_SIZE];
} control_message;

K_HEAP_DEFINE(control_message_heap,
              sizeof(control_message) *
                  MODALITY_CONTROL_MESSAGE_IN_FLIGHT_COUNT);

int8_t register_probe(modality_probe *probe, struct k_msgq *control_msgq) {
  int8_t err = PROBE_REGISTRY_OK;
  k_mutex_lock(&g_probe_registry_mutex, K_FOREVER);

  if (g_probe_registry.count >= MODALITY_PROBE_REGISTRY_SIZE) {
    err = PROBE_REGISTRY_FULL;
  } else {
    g_probe_registry.entries[g_probe_registry.count].probe = probe;
    g_probe_registry.entries[g_probe_registry.count].control_msgq =
        control_msgq;
    g_probe_registry.entries[g_probe_registry.count].sent_mutator_announcment =
        false;

    k_thread_custom_data_set(&g_probe_registry.entries[g_probe_registry.count]);
    g_probe_registry.count++;
  }

  k_mutex_unlock(&g_probe_registry_mutex);
  return err;
}

modality_probe *current_thread_probe() {
  probe_registry_entry *current_entry = k_thread_custom_data_get();
  if (current_entry != NULL) {
    return current_entry->probe;
  } else {
    return NULL;
  }
}

void send_modality_reports(struct k_work *work) {
  modality_probe *registered_probes[MODALITY_PROBE_REGISTRY_SIZE];
  size_t registered_probe_count = 0;

  // Copy out the needed data, to keep the lock narrow
  {
    k_mutex_lock(&g_probe_registry_mutex, K_FOREVER);

    registered_probe_count = g_probe_registry.count;
    for (int i = 0; i < registered_probe_count; i++) {
      registered_probes[i] = g_probe_registry.entries[i].probe;
    }

    k_mutex_unlock(&g_probe_registry_mutex);
  }

  for (int i = 0; i < registered_probe_count; i++) {
    modality_probe *probe = registered_probes[i];

    size_t report_size;

    int key = irq_lock();
    int err = modality_probe_report(probe, g_report_buffer,
                                    sizeof(g_report_buffer), &report_size);
    irq_unlock(key);

    assert(err == MODALITY_PROBE_ERROR_OK);

    if (report_size != 0) {
      const size_t status =
          send(g_collector_socket, &g_report_buffer[0], report_size, 0);
      assert(status != -1);
    }
  }

  k_work_reschedule(&send_modality_reports_delayable, MODALITY_REPORT_CADENCE);
}

int start_modality_comms(void) {
  printf("Starting modality comms tasks...\n");

  g_collector_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
  if (g_collector_socket < 0) {
    printf("error: socket: %d\n", errno);
    return -errno;
  }

  struct sockaddr_in modalityd_addr = {
      .sin_family = AF_INET,
      .sin_port = htons(MODALITY_COLLECTOR_PORT),
  };
  inet_pton(AF_INET, MODALITY_COLLECTOR_IP, &modalityd_addr.sin_addr);

  int ret =
      connect(g_collector_socket, (const struct sockadddr *)&modalityd_addr,
              sizeof(modalityd_addr));
  if (ret < 0) {
    printf("error: connect: %d\n", errno);
    return -errno;
  }

  k_work_reschedule(&send_modality_reports_delayable, K_MSEC(0));
  k_thread_start(modality_control_plane_thread_id);

  return 0;
}

/// Allocate a new control message with a refcount of 1
control_message *control_message_new() {
  control_message *msg = NULL;
  while (msg == NULL) {
    msg = (control_message *)k_heap_aligned_alloc(
        &control_message_heap, sizeof(void *), sizeof(control_message),
        K_FOREVER);

    // The timeout parameter to k_heap_alloc is a lie in some
    // configurations. do a sleep-retry loop.
    if (msg == NULL) {
      k_sleep(K_MSEC(50));
    }
  }

  msg->refcount = ATOMIC_INIT(0);
  return msg;
}

void control_message_ref(control_message *msg) {
  if (msg == NULL) {
    return;
  }

  atomic_val_t _prev = atomic_inc(&msg->refcount);
}

void control_message_unref(control_message *msg) {
  if (msg == NULL) {
    return;
  }
  atomic_val_t prev = atomic_dec(&msg->refcount);

  /// If we just went from 1 -> 0
  if (prev == 1) {
    k_heap_free(&control_message_heap, msg);
  }
}

static void modality_control_plane_run() {
  struct sockaddr_in addr = {.sin_family = AF_INET,
                             .sin_port = htons(MODALITY_CONTROL_PLANE_PORT),
                             .sin_addr = {.s_addr = htonl(INADDR_ANY)}};

  int server_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
  if (server_socket < 0) {
    printf("error: socket: %d\n", errno);
  }

  if (bind(server_socket, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
    printf("error: bind: %d\n", errno);
    return;
  }

  if (listen(server_socket, 5) < 0) {
    printf("error: listen: %d\n", errno);
    return;
  }

  do {
    struct sockaddr client_addr;
    socklen_t client_addr_len = sizeof(client_addr);

    control_message *msg = control_message_new();
    control_message_ref(msg);
    int received =
        recvfrom(server_socket, msg->data, MODALITY_CONTROL_MESSAGE_SIZE, 0,
                 &client_addr, &client_addr_len);

    if (received < 0) {
      /* Socket error */
      printf("error: recvfrom: %d\n", errno);
      return;
    }

    {
      k_mutex_lock(&g_probe_registry_mutex, K_FOREVER);

      int registered_probe_count = g_probe_registry.count;
      for (int i = 0; i < registered_probe_count; i++) {
        struct k_msgqw *control_msgq = g_probe_registry.entries[i].control_msgq;
        if (control_msgq != NULL) {
          control_message_ref(msg);

          k_msgq_put(control_msgq, &msg, K_FOREVER);
        }
      }

      k_mutex_unlock(&g_probe_registry_mutex);
    }

    control_message_unref(msg);

  } while (true);
}

void send_mutator_announcement(modality_probe *probe) {
  size_t announce_size;
  int err;
  size_t send_status;

  k_mutex_lock(&g_announce_buffer_mutex, K_FOREVER);

  err = modality_probe_announce_mutators(
      probe, g_announce_buffer, sizeof(g_announce_buffer), &announce_size);

  if (announce_size != 0 && err == MODALITY_PROBE_ERROR_OK) {
    send_status =
        send(g_collector_socket, &g_announce_buffer[0], announce_size, 0);
  }

  k_mutex_unlock(&g_announce_buffer_mutex);

  assert(err == MODALITY_PROBE_ERROR_OK);
  assert(send_status != -1);
}

void poll_control_plane_messages() {
  probe_registry_entry *entry =
      (probe_registry_entry *)k_thread_custom_data_get();
  if (entry == NULL) {
    return;
  }

  if (!entry->sent_mutator_announcment) {
    send_mutator_announcement(entry->probe);
    entry->sent_mutator_announcment = true;
  }

  if (entry->control_msgq != NULL) {
    while (true) {
      control_message *msg = NULL;
      int ret = k_msgq_get(entry->control_msgq, &msg, K_NO_WAIT);
      if (ret == -ENOMSG || msg == NULL) {
        break;
      }
      size_t _should_forward;
      size_t err = modality_probe_process_control_message(
          entry->probe, msg->data, MODALITY_CONTROL_MESSAGE_SIZE,
          &_should_forward);
      control_message_unref(msg);

      assert(err == MODALITY_PROBE_ERROR_OK);
    }
  }
}
