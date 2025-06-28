#pragma once

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    size_t total_free_bytes;
    size_t total_allocated_bytes;
    size_t largest_free_block;
    size_t minimum_free_bytes;
    size_t allocated_blocks;
    size_t free_blocks;
    size_t total_blocks;
} multi_heap_info_t;

typedef struct multi_heap_info *multi_heap_handle_t;
void *multi_heap_aligned_alloc(multi_heap_handle_t heap, size_t size, size_t alignment);
void *multi_heap_malloc(multi_heap_handle_t heap, size_t size);
void multi_heap_free(multi_heap_handle_t heap, void *p);
void *multi_heap_realloc(multi_heap_handle_t heap, void *p, size_t size);
size_t multi_heap_get_allocated_size(multi_heap_handle_t heap, void *p);
multi_heap_handle_t multi_heap_register(void *start, size_t size);
void multi_heap_set_lock(multi_heap_handle_t heap, void* lock);
void multi_heap_dump(multi_heap_handle_t heap);
bool multi_heap_check(multi_heap_handle_t heap, bool print_errors);
size_t multi_heap_free_size(multi_heap_handle_t heap);
size_t multi_heap_minimum_free_size(multi_heap_handle_t heap);
void multi_heap_get_info(multi_heap_handle_t heap, multi_heap_info_t *info);
