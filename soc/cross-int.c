#include <stdint.h>
#include "soc/cpu.h"
#include "soc/peripherals.h"
#include "freertos/FreeRTOS.h"
#include "freertos/portmacro.h"

#include "soc/intr-alloc.h"

#define REASON_YIELD            1<<0
#define REASON_FREQ_SWITCH      1<<1

#define REASON_PRINT_BACKTRACE  1<<2

#define DR_REG_SYSTEM_BASE                      0x600c0000
#define SYSTEM_CPU_INTR_FROM_CPU_0_REG          (DR_REG_SYSTEM_BASE + 0x30)
#define SYSTEM_CPU_INTR_FROM_CPU_1_REG          (DR_REG_SYSTEM_BASE + 0x34)

#define SYSTEM_CPU_INTR_FROM_CPU_0          1<<0
#define SYSTEM_CPU_INTR_FROM_CPU_1          1<<0

#define ESP_INTR_FLAG_IRAM          (1<<10)


static portMUX_TYPE reason_spinlock = portMUX_INITIALIZER_UNLOCKED;
static volatile uint32_t reason[portNUM_PROCESSORS];

void IRAM_ATTR esp_crosscore_isr_handle_yield(void)
{
	portYIELD_FROM_ISR();
}

static void IRAM_ATTR esp_crosscore_isr(void *arg) {
	uint32_t my_reason_val;
	//A pointer to the correct reason array item is passed to this ISR.
	volatile uint32_t *my_reason=arg;

	//Clear the interrupt first.
	if (cpu_ll_get_core_id()==0) {
		WRITE_PERI_REG(SYSTEM_CPU_INTR_FROM_CPU_0_REG, 0);
	} else {
		WRITE_PERI_REG(SYSTEM_CPU_INTR_FROM_CPU_1_REG, 0);
	}

	//Grab the reason and clear it.
	portENTER_CRITICAL_ISR(&reason_spinlock);
	my_reason_val=*my_reason;
	*my_reason=0;
	portEXIT_CRITICAL_ISR(&reason_spinlock);

	//Check what we need to do.
	if (my_reason_val & REASON_YIELD) {
		esp_crosscore_isr_handle_yield();
	}
	if (my_reason_val & REASON_FREQ_SWITCH) {
		/* Nothing to do here; the frequency switch event was already
		 * handled by a hook in xtensa_vectors.S. Could be used in the future
		 * to allow DFS features without the extra latency of the ISR hook.
		 */
	}
#if !CONFIG_IDF_TARGET_ESP32C3 && !CONFIG_IDF_TARGET_ESP32H2 // IDF-2986
	if (my_reason_val & REASON_PRINT_BACKTRACE) {
		esp_backtrace_print(100);
	}
#endif
}

//Initialize the crosscore interrupt on this core. Call this once
//on each active core.
void esp_crosscore_int_init(void) {
	portENTER_CRITICAL(&reason_spinlock);
	reason[cpu_ll_get_core_id()]=0;
	portEXIT_CRITICAL(&reason_spinlock);
	int err = 0;
	if (cpu_ll_get_core_id()==0) {
		err = esp_intr_alloc(ETS_FROM_CPU_INTR0_SOURCE, ESP_INTR_FLAG_IRAM, esp_crosscore_isr, (void*)&reason[0], NULL);
	} else {
		err = esp_intr_alloc(ETS_FROM_CPU_INTR1_SOURCE, ESP_INTR_FLAG_IRAM, esp_crosscore_isr, (void*)&reason[1], NULL);
	}
	ESP_ERROR_CHECK(err);
}

static void IRAM_ATTR esp_crosscore_int_send(int core_id, uint32_t reason_mask) {
	assert(core_id<portNUM_PROCESSORS);
	//Mark the reason we interrupt the other CPU
	portENTER_CRITICAL_ISR(&reason_spinlock);
	reason[core_id] |= reason_mask;
	portEXIT_CRITICAL_ISR(&reason_spinlock);
	//Poke the other CPU.
	if (core_id==0) {
		WRITE_PERI_REG(SYSTEM_CPU_INTR_FROM_CPU_0_REG, SYSTEM_CPU_INTR_FROM_CPU_0);
	} else {
		WRITE_PERI_REG(SYSTEM_CPU_INTR_FROM_CPU_1_REG, SYSTEM_CPU_INTR_FROM_CPU_1);
	}
}

static void IRAM_ATTR esp_crosscore_int_send_yield(int core_id)
{
	esp_crosscore_int_send(core_id, REASON_YIELD);
}

void IRAM_ATTR esp_crosscore_int_send_freq_switch(int core_id)
{
	esp_crosscore_int_send(core_id, REASON_FREQ_SWITCH);
}

#if !CONFIG_IDF_TARGET_ESP32C3 && !CONFIG_IDF_TARGET_ESP32H2
void IRAM_ATTR esp_crosscore_int_send_print_backtrace(int core_id)
{
	esp_crosscore_int_send(core_id, REASON_PRINT_BACKTRACE);
}
#endif
