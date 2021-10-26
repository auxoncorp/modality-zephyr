#ifndef MODALITY_PROBE_PORT_H
#define MODALITY_PROBE_PORT_H

#ifdef __cplusplus
extern "C" {
#endif

#include <kernel.h>

#ifdef CONFIG_MODALITY_PROBE_USE_PRINTK
#include <sys/printk.h>
#define TRACE_DEBUG_PRINTF(...) printk(__VA_ARGS__)
#endif

#ifndef TRACE_ALLOC_CRITICAL_SECTION
#define TRACE_ALLOC_CRITICAL_SECTION() int __irq_state;
#endif
#ifndef TRACE_ENTER_CRITICAL_SECTION
#define TRACE_ENTER_CRITICAL_SECTION() { __irq_state = irq_lock(); }
#endif
#ifndef TRACE_EXIT_CRITICAL_SECTION
#define TRACE_EXIT_CRITICAL_SECTION() { irq_unlock(__irq_state); }
#endif

#ifndef TRACE_MALLOC
#define TRACE_MALLOC(size) k_malloc(size)
#endif

#ifndef TRACE_ALIGNED_ALLOC
#define TRACE_ALIGNED_ALLOC(align, size) k_aligned_alloc(align, size)
#endif

#ifndef TRACE_FREE
#define TRACE_FREE(ptr) k_free(ptr)
#endif

#ifndef STRLEN
#define STRLEN(a) strlen((a))
#endif

#ifndef MPT_CAT2
#define MPT__CAT2(a, b) a##b
#define MPT_CAT2(a, b) MPT__CAT2(a, b)
#endif

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MODALITY_PROBE_PORT_H */
