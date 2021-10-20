#ifndef EXTERNAL_TRACING_H
#define EXTERNAL_TRACING_H

#ifdef __cplusplus
extern "C" {
#endif

#ifdef CONFIG_MODALITY_PROBE_TRACING

#include <kernel.h>
#include <init.h>
#include "modality_probe_trace.h"

#endif /* CONFIG_MODALITY_PROBE_TRACING */

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* EXTERNAL_TRACING_H */
