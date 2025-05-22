#pragma once

#include <stdlib.h>
#include <stdint.h>
#include "heap/soc_memory_layout.h"
#include "multi_heap.h"
#include "multi_heap_platform.h"
#include "sys/queue.h"

#define HEAP_SIZE_MAX (SOC_MAX_CONTIGUOUS_RAM_SIZE)

typedef struct heap_t_ {
    uint32_t caps[SOC_MEMORY_TYPE_NO_PRIOS]; ///< Capabilities for the type of memory in this heap (as a prioritised set). Copied from soc_memory_types so it's in RAM not flash.
    intptr_t start;
    intptr_t end;
    multi_heap_lock_t heap_mux;
    multi_heap_handle_t heap;
    SLIST_ENTRY(heap_t_) next;
} heap_t;

extern SLIST_HEAD(registered_heap_ll, heap_t_) registered_heaps;

bool heap_caps_match(const heap_t *heap, uint32_t caps);

inline static IRAM_ATTR uint32_t get_all_caps(const heap_t *heap)
{
    if (heap->heap == NULL) {
        return 0;
    }
    uint32_t all_caps = 0;
    for (int prio = 0; prio < SOC_MEMORY_TYPE_NO_PRIOS; prio++) {
        all_caps |= heap->caps[prio];
    }
    return all_caps;
}

void *heap_caps_realloc_default(void *p, size_t size);
void *heap_caps_malloc_default(size_t size);
