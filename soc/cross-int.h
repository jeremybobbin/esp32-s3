#pragma once

#include <stdint.h>

#define REASON_YIELD            1<<0
#define REASON_FREQ_SWITCH      1<<1
#define REASON_PRINT_BACKTRACE  1<<2

#define DR_REG_SYSTEM_BASE                      0x600c0000
#define SYSTEM_CPU_INTR_FROM_CPU_0_REG          (DR_REG_SYSTEM_BASE + 0x30)
#define SYSTEM_CPU_INTR_FROM_CPU_1_REG          (DR_REG_SYSTEM_BASE + 0x34)

#define SYSTEM_CPU_INTR_FROM_CPU_0          1<<0
#define SYSTEM_CPU_INTR_FROM_CPU_1          1<<0

#define ESP_INTR_FLAG_IRAM          (1<<10)

void esp_crosscore_isr_handle_yield(void);
void esp_crosscore_isr(void *arg);

void esp_crosscore_int_init(void);
void esp_crosscore_int_send(int core_id, uint32_t reason_mask);
void esp_crosscore_int_send_yield(int core_id);
void esp_crosscore_int_send_freq_switch(int core_id);
void esp_crosscore_int_send_print_backtrace(int core_id);
