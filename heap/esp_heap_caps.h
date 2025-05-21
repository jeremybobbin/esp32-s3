#include <stdint.h>
#include <stdlib.h>
#include "multi_heap.h"

#define MALLOC_CAP_EXEC             (1<<0)  ///< Memory must be able to run executable code
#define MALLOC_CAP_32BIT            (1<<1)  ///< Memory must allow for aligned 32-bit data accesses
#define MALLOC_CAP_8BIT             (1<<2)  ///< Memory must allow for 8/16/...-bit data accesses
#define MALLOC_CAP_DMA              (1<<3)  ///< Memory must be able to accessed by DMA
#define MALLOC_CAP_PID2             (1<<4)  ///< Memory must be mapped to PID2 memory space (PIDs are not currently used)
#define MALLOC_CAP_PID3             (1<<5)  ///< Memory must be mapped to PID3 memory space (PIDs are not currently used)
#define MALLOC_CAP_PID4             (1<<6)  ///< Memory must be mapped to PID4 memory space (PIDs are not currently used)
#define MALLOC_CAP_PID5             (1<<7)  ///< Memory must be mapped to PID5 memory space (PIDs are not currently used)
#define MALLOC_CAP_PID6             (1<<8)  ///< Memory must be mapped to PID6 memory space (PIDs are not currently used)
#define MALLOC_CAP_PID7             (1<<9)  ///< Memory must be mapped to PID7 memory space (PIDs are not currently used)
#define MALLOC_CAP_SPIRAM           (1<<10) ///< Memory must be in SPI RAM
#define MALLOC_CAP_INTERNAL         (1<<11) ///< Memory must be internal; specifically it should not disappear when flash/spiram cache is switched off
#define MALLOC_CAP_DEFAULT          (1<<12) ///< Memory can be returned in a non-capability-specific memory allocation (e.g. malloc(), calloc()) call
#define MALLOC_CAP_IRAM_8BIT        (1<<13) ///< Memory must be in IRAM and allow unaligned access
#define MALLOC_CAP_RETENTION        (1<<14) ///< Memory must be able to accessed by retention DMA
#define MALLOC_CAP_RTCRAM           (1<<15) ///< Memory must be in RTC fast memory

#define MALLOC_CAP_INVALID          (1<<31) ///< Memory can't be used / list end marker

typedef void (*esp_alloc_failed_hook_t) (size_t size, uint32_t caps, const char * function_name);

int heap_caps_register_failed_alloc_callback(esp_alloc_failed_hook_t callback);
void *heap_caps_malloc(size_t size, uint32_t caps);

void heap_caps_free( void *ptr);
void *heap_caps_realloc( void *ptr, size_t size, uint32_t caps);
void *heap_caps_aligned_alloc(size_t alignment, size_t size, uint32_t caps);
void *heap_caps_aligned_calloc(size_t alignment, size_t n, size_t size, uint32_t caps);
void *heap_caps_calloc(size_t n, size_t size, uint32_t caps);
size_t heap_caps_get_total_size(uint32_t caps);
size_t heap_caps_get_free_size( uint32_t caps );
size_t heap_caps_get_minimum_free_size( uint32_t caps );
size_t heap_caps_get_largest_free_block( uint32_t caps );
void heap_caps_get_info( multi_heap_info_t *info, uint32_t caps );
void heap_caps_print_heap_info( uint32_t caps );
bool heap_caps_check_integrity_all(bool print_errors);
bool heap_caps_check_integrity(uint32_t caps, bool print_errors);
bool heap_caps_check_integrity_addr(intptr_t addr, bool print_errors);
void heap_caps_malloc_extmem_enable(size_t limit);
void *heap_caps_malloc_prefer( size_t size, size_t num, ... );
void *heap_caps_realloc_prefer( void *ptr, size_t size, size_t num, ... );
void *heap_caps_calloc_prefer( size_t n, size_t size, size_t num, ... );
void heap_caps_dump(uint32_t caps);
void heap_caps_dump_all(void);
size_t heap_caps_get_allocated_size( void *ptr );
