#ifndef SOC_MEMORY_LAYOUT_H
#define SOC_MEMORY_LAYOUT_H

#include "heap/heap_memory_layout.h"

#define IRAM_ATTR _SECTION_ATTR_IMPL(".iram1", __COUNTER__)

// Forces data into DRAM instead of flash
#define DRAM_ATTR _SECTION_ATTR_IMPL(".dram1", __COUNTER__)
#define _SECTION_ATTR_IMPL(SECTION, COUNTER) __attribute__((section(SECTION "." _COUNTER_STRINGIFY(COUNTER))))

#define _COUNTER_STRINGIFY(COUNTER) #COUNTER



/* Overall memory map */
#define SOC_DROM_LOW    0x3C000000
#define SOC_DROM_HIGH   0x3D000000
#define SOC_IROM_LOW    0x42000000
#define SOC_IROM_HIGH   0x44000000
#define SOC_IRAM_LOW    0x40370000
#define SOC_IRAM_HIGH   0x403E0000
#define SOC_DRAM_LOW    0x3FC88000
#define SOC_DRAM_HIGH   0x3FD00000

#define SOC_RTC_IRAM_LOW  0x600FE000
#define SOC_RTC_IRAM_HIGH 0x60100000
#define SOC_RTC_DRAM_LOW  0x600FE000
#define SOC_RTC_DRAM_HIGH 0x60100000

#define SOC_RTC_DATA_LOW  0x50000000
#define SOC_RTC_DATA_HIGH 0x50002000

#define SOC_EXTRAM_DATA_LOW 0x3D000000
#define SOC_EXTRAM_DATA_HIGH 0x3E000000
#define SOC_IROM_MASK_LOW  0x40000000
#define SOC_IROM_MASK_HIGH 0x4001A100

#define SOC_EXTRAM_DATA_SIZE (SOC_EXTRAM_DATA_HIGH - SOC_EXTRAM_DATA_LOW)
#define SOC_MAX_CONTIGUOUS_RAM_SIZE (SOC_EXTRAM_DATA_HIGH - SOC_EXTRAM_DATA_LOW) ///< Largest span of contiguous memory (DRAM or IRAM) in the address space


//First and last words of the D/IRAM region, for both the DRAM address as well as the IRAM alias.
#define SOC_DIRAM_IRAM_LOW    0x40378000
#define SOC_DIRAM_IRAM_HIGH   0x403E0000
#define SOC_DIRAM_DRAM_LOW    0x3FC88000
#define SOC_DIRAM_DRAM_HIGH   0x3FCF0000

#define SOC_I_D_OFFSET (SOC_DIRAM_IRAM_LOW - SOC_DIRAM_DRAM_LOW)
#define MAP_DRAM_TO_IRAM(addr) (addr + SOC_I_D_OFFSET)
#define MAP_IRAM_TO_DRAM(addr) (addr - SOC_I_D_OFFSET)

// Region of memory accessible via DMA in internal memory. See esp_ptr_dma_capable().
#define SOC_DMA_LOW  0x3FC88000
#define SOC_DMA_HIGH 0x3FD00000

// Region of memory accessible via DMA in external memory. See esp_ptr_dma_ext_capable().
#define SOC_DMA_EXT_LOW     SOC_EXTRAM_DATA_LOW
#define SOC_DMA_EXT_HIGH    SOC_EXTRAM_DATA_HIGH


// Region of memory that is byte-accessible. See esp_ptr_byte_accessible().
#define SOC_BYTE_ACCESSIBLE_LOW     0x3FC88000
#define SOC_BYTE_ACCESSIBLE_HIGH    0x3FD00000

//Region of memory that is internal, as in on the same silicon die as the ESP32 CPUs
//(excluding RTC data region, that's checked separately.) See esp_ptr_internal().
#define SOC_MEM_INTERNAL_LOW        0x3FC88000
#define SOC_MEM_INTERNAL_HIGH       0x403E2000

// Start (highest address) of ROM boot stack, only relevant during early boot
#define SOC_ROM_STACK_START         0x3fceb710
#define SOC_ROM_STACK_SIZE          0x2000

inline static bool IRAM_ATTR esp_ptr_dma_capable(const void *p)
{
    return (intptr_t)p >= SOC_DMA_LOW && (intptr_t)p < SOC_DMA_HIGH;
}

inline static bool IRAM_ATTR esp_ptr_dma_ext_capable(const void *p)
{
#ifdef SOC_PSRAM_DMA_CAPABLE
    return (intptr_t)p >= SOC_DMA_EXT_LOW && (intptr_t)p < SOC_DMA_EXT_HIGH;
#else
    return false;
#endif
}

inline static bool IRAM_ATTR esp_ptr_word_aligned(const void *p)
{
    return ((intptr_t)p) % 4 == 0;
}

inline static bool IRAM_ATTR esp_ptr_executable(const void *p)
{
    intptr_t ip = (intptr_t) p;
    return (ip >= SOC_IROM_LOW && ip < SOC_IROM_HIGH)
        || (ip >= SOC_IRAM_LOW && ip < SOC_IRAM_HIGH)
        || (ip >= SOC_IROM_MASK_LOW && ip < SOC_IROM_MASK_HIGH)
#if defined(SOC_CACHE_APP_LOW) && defined(CONFIG_FREERTOS_UNICORE)
        || (ip >= SOC_CACHE_APP_LOW && ip < SOC_CACHE_APP_HIGH)
#endif
        || (ip >= SOC_RTC_IRAM_LOW && ip < SOC_RTC_IRAM_HIGH);
}

inline static bool IRAM_ATTR esp_ptr_byte_accessible(const void *p)
{
    intptr_t ip = (intptr_t) p;
    bool r;
    r = (ip >= SOC_BYTE_ACCESSIBLE_LOW && ip < SOC_BYTE_ACCESSIBLE_HIGH);
#if CONFIG_ESP_SYSTEM_ALLOW_RTC_FAST_MEM_AS_HEAP
    /* For ESP32 case, RTC fast memory is accessible to PRO cpu only and hence
     * for single core configuration (where it gets added to system heap) following
     * additional check is required */
    r |= (ip >= SOC_RTC_DRAM_LOW && ip < SOC_RTC_DRAM_HIGH);
#endif
#if CONFIG_SPIRAM
#if CONFIG_SPIRAM_SIZE != -1 // Fixed size, can be more accurate
    r |= (ip >= SOC_EXTRAM_DATA_LOW && ip < (SOC_EXTRAM_DATA_LOW + CONFIG_SPIRAM_SIZE));
#else
    r |= (ip >= SOC_EXTRAM_DATA_LOW && ip < (SOC_EXTRAM_DATA_HIGH));
#endif
#endif
    return r;
}

inline static bool IRAM_ATTR esp_ptr_internal(const void *p) {
    bool r;
    r = ((intptr_t)p >= SOC_MEM_INTERNAL_LOW && (intptr_t)p < SOC_MEM_INTERNAL_HIGH);
    r |= ((intptr_t)p >= SOC_RTC_DATA_LOW && (intptr_t)p < SOC_RTC_DATA_HIGH);
#if CONFIG_ESP_SYSTEM_ALLOW_RTC_FAST_MEM_AS_HEAP
    /* For ESP32 case, RTC fast memory is accessible to PRO cpu only and hence
     * for single core configuration (where it gets added to system heap) following
     * additional check is required */
    r |= ((intptr_t)p >= SOC_RTC_DRAM_LOW && (intptr_t)p < SOC_RTC_DRAM_HIGH);
#endif
    return r;
}


inline static bool IRAM_ATTR esp_ptr_external_ram(const void *p) {
#if SOC_SPIRAM_SUPPORTED
    return ((intptr_t)p >= SOC_EXTRAM_DATA_LOW && (intptr_t)p < SOC_EXTRAM_DATA_HIGH);
#else
    return false; // SoC has no external RAM
#endif
}

inline static bool IRAM_ATTR esp_ptr_in_iram(const void *p) {
#if CONFIG_IDF_TARGET_ESP32 && CONFIG_FREERTOS_UNICORE
    return ((intptr_t)p >= SOC_CACHE_APP_LOW && (intptr_t)p < SOC_IRAM_HIGH);
#else
    return ((intptr_t)p >= SOC_IRAM_LOW && (intptr_t)p < SOC_IRAM_HIGH);
#endif
}

inline static bool IRAM_ATTR esp_ptr_in_drom(const void *p) {
    return ((intptr_t)p >= SOC_DROM_LOW && (intptr_t)p < SOC_DROM_HIGH);
}

inline static bool IRAM_ATTR esp_ptr_in_dram(const void *p) {
    return ((intptr_t)p >= SOC_DRAM_LOW && (intptr_t)p < SOC_DRAM_HIGH);
}

inline static bool IRAM_ATTR esp_ptr_in_diram_dram(const void *p) {
    return ((intptr_t)p >= SOC_DIRAM_DRAM_LOW && (intptr_t)p < SOC_DIRAM_DRAM_HIGH);
}

inline static bool IRAM_ATTR esp_ptr_in_diram_iram(const void *p) {
    return ((intptr_t)p >= SOC_DIRAM_IRAM_LOW && (intptr_t)p < SOC_DIRAM_IRAM_HIGH);
}

inline static bool IRAM_ATTR esp_ptr_in_rtc_iram_fast(const void *p) {
    return ((intptr_t)p >= SOC_RTC_IRAM_LOW && (intptr_t)p < SOC_RTC_IRAM_HIGH);
}

inline static bool IRAM_ATTR esp_ptr_in_rtc_dram_fast(const void *p) {
    return ((intptr_t)p >= SOC_RTC_DRAM_LOW && (intptr_t)p < SOC_RTC_DRAM_HIGH);
}

inline static bool IRAM_ATTR esp_ptr_in_rtc_slow(const void *p) {
    return ((intptr_t)p >= SOC_RTC_DATA_LOW && (intptr_t)p < SOC_RTC_DATA_HIGH);
}

/* Convert a D/IRAM DRAM pointer to equivalent word address in IRAM

   - Address must be word aligned
   - Address must pass esp_ptr_in_diram_dram() test, or result will be invalid pointer
*/
inline static void * IRAM_ATTR esp_ptr_diram_dram_to_iram(const void *p) {
#if SOC_DIRAM_INVERTED
    return (void *) ( SOC_DIRAM_IRAM_LOW + (SOC_DIRAM_DRAM_HIGH - (intptr_t)p) - 4);
#else
    return (void *) ( SOC_DIRAM_IRAM_LOW + ((intptr_t)p - SOC_DIRAM_DRAM_LOW) );
#endif
}

/* Convert a D/IRAM IRAM pointer to equivalent word address in DRAM

   - Address must be word aligned
   - Address must pass esp_ptr_in_diram_iram() test, or result will be invalid pointer
*/
inline static void * IRAM_ATTR esp_ptr_diram_iram_to_dram(const void *p) {
#if SOC_DIRAM_INVERTED
    return (void *) ( SOC_DIRAM_DRAM_LOW + (SOC_DIRAM_IRAM_HIGH - (intptr_t)p) - 4);
#else
    return (void *) ( SOC_DIRAM_DRAM_LOW + ((intptr_t)p - SOC_DIRAM_IRAM_LOW) );
#endif
}

inline static bool IRAM_ATTR esp_stack_ptr_in_dram(uint32_t sp)
{
    //Check if stack ptr is in between SOC_DRAM_LOW and SOC_DRAM_HIGH, and 16 byte aligned.
    return !(sp < SOC_DRAM_LOW + 0x10 || sp > SOC_DRAM_HIGH - 0x10 || ((sp & 0xF) != 0));
}

#if CONFIG_SPIRAM_ALLOW_STACK_EXTERNAL_MEMORY
inline static bool IRAM_ATTR esp_stack_ptr_in_extram(uint32_t sp)
{
    //Check if stack ptr is in between SOC_EXTRAM_DATA_LOW and SOC_EXTRAM_DATA_HIGH, and 16 byte aligned.
    return !(sp < SOC_EXTRAM_DATA_LOW + 0x10 || sp > SOC_EXTRAM_DATA_HIGH - 0x10 || ((sp & 0xF) != 0));
}
#endif

inline static bool IRAM_ATTR esp_stack_ptr_is_sane(uint32_t sp)
{
    return esp_stack_ptr_in_dram(sp)
#if CONFIG_SPIRAM_ALLOW_STACK_EXTERNAL_MEMORY
        || esp_stack_ptr_in_extram(sp)
#endif
#if CONFIG_ESP_SYSTEM_ALLOW_RTC_FAST_MEM_AS_HEAP
        || esp_ptr_in_rtc_dram_fast((void*) sp)
#endif
        ;
}

#endif
