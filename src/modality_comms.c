#include "modality_comms.h"

#include <assert.h>
#include <errno.h>
#include <net/socket.h>
#include <stdio.h>
#include <zephyr.h>

#define MODALITY_PROBE_REGISTRY_SIZE 16

#define MODALITY_COLLECTOR_IP "192.0.2.2"
#define MODALITY_COLLECTOR_PORT 34333
#define MODALITY_REPORT_CADENCE K_MSEC(1000)

#define MODALITY_CONTROL_PLANE_PORT 34355
#define MODALITY_CONTROL_PLANE_STACK_SIZE 2048
#define MODALITY_CONTROL_PLANE_PRIORITY 1

static int g_report_socket = -1;
static uint8_t g_report_buffer[1400];

static void modality_control_plane_run(void);
K_THREAD_DEFINE(modality_control_plane_thread_id,
                MODALITY_CONTROL_PLANE_STACK_SIZE, modality_control_plane_run,
                NULL, NULL, NULL, MODALITY_CONTROL_PLANE_PRIORITY, 0, -1);

typedef struct probe_registry_entry {
  modality_probe *probe;
  struct k_fifo *control_fifo;
  /* k_tid_t thread_id; */
} probe_registry_entry;

typedef struct probe_registry {
  probe_registry_entry entries[MODALITY_PROBE_REGISTRY_SIZE];
  uint8_t count;
} probe_registry;

static probe_registry g_probe_registry;
K_MUTEX_DEFINE(g_probe_registry_mutex);

int8_t register_probe(modality_probe *probe, struct k_fifo *control_fifo) {
  int8_t err = PROBE_REGISTRY_OK;
  k_mutex_lock(&g_probe_registry_mutex, K_FOREVER);

  if (g_probe_registry.count >= MODALITY_PROBE_REGISTRY_SIZE) {
    err = PROBE_REGISTRY_FULL;
    goto done;
  }

  g_probe_registry.entries[g_probe_registry.count].probe = probe;
  g_probe_registry.entries[g_probe_registry.count].control_fifo = control_fifo;
  g_probe_registry.count++;

done:
  k_mutex_unlock(&g_probe_registry_mutex);
  return err;
}

static void send_modality_reports(struct k_work *work);

K_WORK_DELAYABLE_DEFINE(send_modality_reports_delayable, send_modality_reports);
static void send_modality_reports(struct k_work *work) {
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
    const size_t err = modality_probe_report(
        probe, &g_report_buffer[0], sizeof(g_report_buffer), &report_size);
    assert(err == MODALITY_PROBE_ERROR_OK);

    if (report_size != 0) {
      const size_t status =
          send(g_report_socket, &g_report_buffer[0], report_size, 0);
      assert(status != -1);
    }
  }

  k_work_reschedule(&send_modality_reports_delayable, MODALITY_REPORT_CADENCE);
}

int start_modality_comms(void) {
  printf("Starting modality comms tasks...");

  g_report_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
  if (g_report_socket < 0) {
    printf("error: socket: %d\n", errno);
    return -errno;
  }

  struct sockaddr_in modalityd_addr = {
      .sin_family = AF_INET,
      .sin_port = htons(MODALITY_COLLECTOR_PORT),
  };
  inet_pton(AF_INET, MODALITY_COLLECTOR_IP, &modalityd_addr.sin_addr);

  int ret = connect(g_report_socket, (const struct sockadddr *)&modalityd_addr,
                    sizeof(modalityd_addr));
  if (ret < 0) {
    printf("error: connect: %d\n", errno);
    return -errno;
  }

  k_thread_name_set(modality_control_plane_thread_id, "modality_control_plane");
  k_thread_start(modality_control_plane_thread_id);

  k_work_reschedule(&send_modality_reports_delayable, MODALITY_REPORT_CADENCE);

  printf("done\n");

  return 0;
}

void stop_modality_comms(void) {
  k_thread_abort(modality_control_plane_thread_id);
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
    static uint8_t recv_buffer[64];

    int received = recvfrom(server_socket, recv_buffer,
                            sizeof(recv_buffer), 0, &client_addr,
                            &client_addr_len);

    if (received < 0) {
      /* Socket error */
      printf("error: recvfrom: %d\n", errno);
      return;
    }

    printf("Received %d bytes\n", received);
    printf("TODO distribute to probes\n");

  } while (true);
}
