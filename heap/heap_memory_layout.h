#pragma once

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#define SOC_MEMORY_TYPE_NO_PRIOS 3

typedef struct {
    const char *name;  ///< Name of this memory type
    uint32_t caps[SOC_MEMORY_TYPE_NO_PRIOS]; ///< Capabilities for this memory type (as a prioritised set)
    bool aliased_iram;   ///< If true, this is data memory that is is also mapped in IRAM
    bool startup_stack; ///< If true, memory of this type is used for ROM stack during startup
} soc_memory_type_desc_t;

extern const soc_memory_type_desc_t soc_memory_types[];
extern const size_t soc_memory_type_count;

typedef struct {
    intptr_t start;  ///< Start address of the region
    size_t size;            ///< Size of the region in bytes
    size_t type;             ///< Type of the region (index into soc_memory_types array)
    intptr_t iram_address; ///< If non-zero, is equivalent address in IRAM
} soc_memory_region_t;

extern const soc_memory_region_t soc_memory_regions[];
extern const size_t soc_memory_region_count;

typedef struct {
    intptr_t start;
    intptr_t end;
} soc_reserved_region_t;

#define SOC_RESERVE_MEMORY_REGION(START, END, NAME)     \
    __attribute__((section(".reserved_memory_address"))) __attribute__((used)) \
    static soc_reserved_region_t reserved_region_##NAME = { START, END };

size_t soc_get_available_memory_regions(soc_memory_region_t *regions);

size_t soc_get_available_memory_region_max_count(void);
