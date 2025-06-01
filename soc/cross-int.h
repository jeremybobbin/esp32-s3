#include <stdint.h>
#include "freertos/FreeRTOS.h"
#include "freertos/portmacro.h"

#define REASON_YIELD            1<<0
#define REASON_FREQ_SWITCH      1<<1

#define REASON_PRINT_BACKTRACE  1<<2

void IRAM_ATTR esp_crosscore_isr_handle_yield(void);
void IRAM_ATTR esp_crosscore_isr(void *arg);

void esp_crosscore_int_init(void);
void IRAM_ATTR esp_crosscore_int_send(int core_id, uint32_t reason_mask);
void IRAM_ATTR esp_crosscore_int_send_yield(int core_id);
void IRAM_ATTR esp_crosscore_int_send_freq_switch(int core_id);
void IRAM_ATTR esp_crosscore_int_send_print_backtrace(int core_id);
