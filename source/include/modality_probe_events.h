#ifndef MODALITY_PROBE_EVENTS_H
#define MODALITY_PROBE_EVENTS_H

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Tracing event IDs
 *
 * Naming convention is TRACE_EVENT_<CLASS>_<FUNCTION>.
 * The manifest-gen script generates event entries named <CLASS>_<FUNCTION>, e.g.
 * the event TRACE_EVENT_TASK_CREATE will be in the manifest as TASK_CREATE.
 * A <class> tag will also be added to the event's metadata.
 *
 */
#define TRACE_EVENT_ID_TOP (0xFFFF)

#define TRACE_EVENT_TASK_CREATE (TRACE_EVENT_ID_TOP - 1)
#define TRACE_EVENT_TASK_SWITCHED_IN (TRACE_EVENT_ID_TOP - 2)
#define TRACE_EVENT_TASK_SWITCHED_OUT (TRACE_EVENT_ID_TOP - 3)
#define TRACE_EVENT_TASK_SUSPEND (TRACE_EVENT_ID_TOP - 4)
#define TRACE_EVENT_TASK_SLEEP (TRACE_EVENT_ID_TOP - 5)
#define TRACE_EVENT_TASK_MSLEEP (TRACE_EVENT_ID_TOP - 6)
#define TRACE_EVENT_TASK_USLEEP (TRACE_EVENT_ID_TOP - 7)

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MODALITY_PROBE_EVENTS_H */
