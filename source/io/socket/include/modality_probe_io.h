#ifndef MODALITY_PROBE_IO_H
#define MODALITY_PROBE_IO_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

void trace_io_init(void);

int32_t trace_io_read(void* data, uint32_t size, int32_t* bytes_read);

int32_t trace_io_write(void* data, uint32_t size, int32_t* bytes_written);

#define TRACE_IO_INIT() trace_io_init()

#define TRACE_IO_READ(_data, _size, _bytes_read) trace_io_read(_data, _size, _bytes_read)

#define TRACE_IO_WRITE(_data, _size, _bytes_written) trace_io_write(_data, _size, _bytes_written)

#ifdef __cplusplus
}
#endif

#endif /* MODALITY_PROBE_IO_H */
