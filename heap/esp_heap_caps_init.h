#include "esp_heap_caps.h"
#include "heap/soc_memory_layout.h"

void heap_caps_init(void);
void heap_caps_enable_nonos_stack_heaps(void);
int heap_caps_add_region(intptr_t start, intptr_t end);
int heap_caps_add_region_with_caps(const uint32_t caps[], intptr_t start, intptr_t end);
