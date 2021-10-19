#ifndef MODALITY_PROBE_MACROS_H
#define MODALITY_PROBE_MACROS_H

#ifdef __cplusplus
extern "C" {
#endif

#ifdef CONFIG_MODALITY_PROBE_TRACING

#ifdef CONFIG_MODALITY_PROBE_INCLUDE_USER_LEVEL_PROBE_MACROS

#include <stdint.h>
#include <stdbool.h>

size_t mpt_record_event(modality_probe *probe, uint32_t event_id);
size_t mpt_record_event_with_time(modality_probe *probe, uint32_t event_id, uint64_t time_ns);
size_t mpt_record_event_with_payload_i8(modality_probe *probe, uint32_t event_id, int8_t payload);
size_t mpt_record_event_with_payload_i8_with_time(modality_probe *probe, uint32_t event_id, int8_t payload, uint64_t time_ns);
size_t mpt_record_event_with_payload_u8(modality_probe *probe, uint32_t event_id, uint8_t payload);
size_t mpt_record_event_with_payload_u8_with_time(modality_probe *probe, uint32_t event_id, uint8_t payload, uint64_t time_ns);
size_t mpt_record_event_with_payload_i16(modality_probe *probe, uint32_t event_id, int16_t payload);
size_t mpt_record_event_with_payload_i16_with_time(modality_probe *probe, uint32_t event_id, int16_t payload, uint64_t time_ns);
size_t mpt_record_event_with_payload_u16(modality_probe *probe, uint32_t event_id, uint16_t payload);
size_t mpt_record_event_with_payload_u16_with_time(modality_probe *probe, uint32_t event_id, uint16_t payload, uint64_t time_ns);
size_t mpt_record_event_with_payload_i32(modality_probe *probe, uint32_t event_id, int32_t payload);
size_t mpt_record_event_with_payload_i32_with_time(modality_probe *probe, uint32_t event_id, int32_t payload, uint64_t time_ns);
size_t mpt_record_event_with_payload_u32(modality_probe *probe, uint32_t event_id, uint32_t payload);
size_t mpt_record_event_with_payload_u32_with_time(modality_probe *probe, uint32_t event_id, uint32_t payload, uint64_t time_ns);
size_t mpt_record_event_with_payload_bool(modality_probe *probe, uint32_t event_id, bool payload);
size_t mpt_record_event_with_payload_bool_with_time(modality_probe *probe, uint32_t event_id, bool payload, uint64_t time_ns);
size_t mpt_record_event_with_payload_f32(modality_probe *probe, uint32_t event_id, float payload);
size_t mpt_record_event_with_payload_f32_with_time(modality_probe *probe, uint32_t event_id, float payload, uint64_t time_ns);
size_t mpt_produce_snapshot(modality_probe *probe, modality_probe_causal_snapshot *snapshot);
size_t mpt_produce_snapshot_bytes(modality_probe *probe, uint8_t *dst, size_t dst_size, size_t *out_written_bytes);
size_t mpt_merge_snapshot(modality_probe *probe, const modality_probe_causal_snapshot *snapshot);
size_t mpt_merge_snapshot_bytes(modality_probe *probe, const uint8_t *src, size_t src_size);

#undef MODALITY_PROBE_RECORD
#define MODALITY_PROBE_RECORD(probe, event, ...) mpt_record_event(probe, event)

#undef MODALITY_PROBE_RECORD_W_TIME
#define MODALITY_PROBE_RECORD_W_TIME(probe, event, time_ns, ...) mpt_record_event_with_time(probe, event, time_ns)

#undef MODALITY_PROBE_RECORD_W_I8
#define MODALITY_PROBE_RECORD_W_I8(probe, event, payload, ...) mpt_record_event_with_payload_i8(probe, event, payload)

#undef MODALITY_PROBE_RECORD_W_I8_W_TIME
#define MODALITY_PROBE_RECORD_W_I8_W_TIME(probe, event, payload, time_ns, ...) mpt_record_event_with_payload_i8_with_time(probe, event, payload, time_ns)

#undef MODALITY_PROBE_RECORD_W_U8
#define MODALITY_PROBE_RECORD_W_U8(probe, event, payload, ...) mpt_record_event_with_payload_u8(probe, event, payload)

#undef MODALITY_PROBE_RECORD_W_U8_W_TIME
#define MODALITY_PROBE_RECORD_W_U8_W_TIME(probe, event, payload, time_ns, ...) mpt_record_event_with_payload_u8_with_time(probe, event, payload, time_ns)

#undef MODALITY_PROBE_RECORD_W_I16
#define MODALITY_PROBE_RECORD_W_I16(probe, event, payload, ...) mpt_record_event_with_payload_i16(probe, event, payload)

#undef MODALITY_PROBE_RECORD_W_I16_W_TIME
#define MODALITY_PROBE_RECORD_W_I16_W_TIME(probe, event, payload, time_ns, ...) mpt_record_event_with_payload_i16_with_time(probe, event, payload, time_ns)

#undef MODALITY_PROBE_RECORD_W_U16
#define MODALITY_PROBE_RECORD_W_U16(probe, event, payload, ...) mpt_record_event_with_payload_u16(probe, event, payload)

#undef MODALITY_PROBE_RECORD_W_U16_W_TIME
#define MODALITY_PROBE_RECORD_W_U16_W_TIME(probe, event, payload, time_ns, ...) mpt_record_event_with_payload_u16_with_time(probe, event, payload, time_ns)

#undef MODALITY_PROBE_RECORD_W_I32
#define MODALITY_PROBE_RECORD_W_I32(probe, event, payload, ...) mpt_record_event_with_payload_i32(probe, event, payload)

#undef MODALITY_PROBE_RECORD_W_I32_W_TIME
#define MODALITY_PROBE_RECORD_W_I32_W_TIME(probe, event, payload, time_ns, ...) mpt_record_event_with_payload_i32_with_time(probe, event, payload, time_ns)

#undef MODALITY_PROBE_RECORD_W_U32
#define MODALITY_PROBE_RECORD_W_U32(probe, event, payload, ...) mpt_record_event_with_payload_u32(probe, event, payload)

#undef MODALITY_PROBE_RECORD_W_U32_W_TIME
#define MODALITY_PROBE_RECORD_W_U32_W_TIME(probe, event, payload, time_ns, ...) mpt_record_event_with_payload_u32_with_time(probe, event, payload, time_ns)

#undef MODALITY_PROBE_RECORD_W_BOOL
#define MODALITY_PROBE_RECORD_W_BOOL(probe, event, payload, ...) mpt_record_event_with_payload_bool(probe, event, payload)

#undef MODALITY_PROBE_RECORD_W_BOOL_W_TIME
#define MODALITY_PROBE_RECORD_W_BOOL_W_TIME(probe, event, payload, time_ns, ...) mpt_record_event_with_payload_bool_with_time(probe, event, payload, time_ns)

#undef MODALITY_PROBE_RECORD_W_F32
#define MODALITY_PROBE_RECORD_W_F32(probe, event, payload, ...) mpt_record_event_with_payload_f32(probe, event, payload)

#undef MODALITY_PROBE_RECORD_W_F32_W_TIME
#define MODALITY_PROBE_RECORD_W_F32_W_TIME(probe, event, payload, time_ns, ...) mpt_record_event_with_payload_f32_with_time(probe, event, payload, time_ns)

#undef MODALITY_PROBE_EXPECT
#define MODALITY_PROBE_EXPECT(probe, event, expr, ...) mpt_record_event_with_payload_u32(probe, event, (expr))

#undef MODALITY_PROBE_EXPECT_W_TIME
#define MODALITY_PROBE_EXPECT_W_TIME(probe, event, expr, time_ns, ...) mpt_record_event_with_payload_u32_with_time(probe, event, (expr), time_ns)

#undef MODALITY_PROBE_FAILURE
#define MODALITY_PROBE_FAILURE(probe, event, ...) mpt_record_event(probe, event)

#undef MODALITY_PROBE_FAILURE_W_TIME
#define MODALITY_PROBE_FAILURE_W_TIME(probe, event, time_ns, ...) mpt_record_event_with_time(probe, event, time_ns)

#define MODALITY_PROBE_PRODUCE_SNAPSHOT(probe, snapshot) \
    ((MODALITY_PROBE_MACROS_ENABLED) ? mpt_produce_snapshot(probe, snapshot) : MODALITY_PROBE_ERROR_OK)

#define MODALITY_PROBE_PRODUCE_SNAPSHOT_BYTES(probe, dest, dest_size, bytes_written) \
    ((MODALITY_PROBE_MACROS_ENABLED) ? mpt_produce_snapshot_bytes(\
        probe, dest, dest_size, bytes_written) : MODALITY_PROBE_ERROR_OK)

#define MODALITY_PROBE_MERGE_SNAPSHOT(probe, snapshot) \
    ((MODALITY_PROBE_MACROS_ENABLED) ? mpt_merge_snapshot(probe, snapshot) : MODALITY_PROBE_ERROR_OK)

#define MODALITY_PROBE_MERGE_SNAPSHOT_BYTES(probe, src, src_size) \
    ((MODALITY_PROBE_MACROS_ENABLED) ? mpt_merge_snapshot_bytes(probe, src, src_size) : MODALITY_PROBE_ERROR_OK)

#endif /* CONFIG_MODALITY_PROBE_INCLUDE_USER_LEVEL_PROBE_MACROS */

#else /* CONFIG_MODALITY_PROBE_TRACING == 0 */

/* Not in the standard probe.h definitions, make them no-ops here */
#ifndef MODALITY_PROBE_PRODUCE_SNAPSHOT
#define MODALITY_PROBE_PRODUCE_SNAPSHOT(probe, snapshot) (MODALITY_PROBE_ERROR_OK)
#endif
#ifndef MODALITY_PROBE_PRODUCE_SNAPSHOT_BYTES
#define MODALITY_PROBE_PRODUCE_SNAPSHOT_BYTES(probe, dest, dest_size, bytes_written) (MODALITY_PROBE_ERROR_OK)
#endif
#ifndef MODALITY_PROBE_MERGE_SNAPSHOT
#define MODALITY_PROBE_MERGE_SNAPSHOT(probe, snapshot) (MODALITY_PROBE_ERROR_OK)
#endif
#ifndef MODALITY_PROBE_MERGE_SNAPSHOT_BYTES
#define MODALITY_PROBE_MERGE_SNAPSHOT_BYTES(probe, src, src_size) (MODALITY_PROBE_ERROR_OK)
#endif

#endif /* CONFIG_MODALITY_PROBE_TRACING */

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MODALITY_PROBE_MACROS_H */
