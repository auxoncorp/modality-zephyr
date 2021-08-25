#pragma once
#include <zephyr.h>
#include <modality/probe.h>

/** Start the control thread and the scheduled reporting task. */
int start_modality_comms(void);

#define PROBE_REGISTRY_OK 0
#define PROBE_REGISTRY_FULL -1

/** After a probe is initialized, register it with the control thread
    and periodic reporting task, and for usage with all trace-level
    instrumentation from this thread. This must be called from the
    thread the probe will be used from.

    - probe: The already-allocated probe for the current thread.

    - control_msgq: The message queue to use for distributing control
      messages to each thread. It should be allocated like this:

         K_MSGQ_DEFINE(my_control_msgq, sizeof(void *), 2, sizeof(void *));

      All you need to do is allocate it; everything else is handled
      automatically.
    */
int8_t register_probe(modality_probe *probe, struct k_msgq *control_msgq);

/** Handle any pending control messages for the calling thread.  Send
    mutator announcements if necessary. */
void poll_control_plane_messages();

/** Get the probe that's registered with the current thread, if there
    is one. NULL if there isn't. */
modality_probe *current_thread_probe();
