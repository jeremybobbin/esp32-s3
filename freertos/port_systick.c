/*
 * SPDX-FileCopyrightText: 2017-2021 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <stdlib.h>
#include <string.h>
#include "soc/cpu.h"
#include "FreeRTOS.h"
#include "task.h"

//#include "soc/periph_defs.h"
//#include "soc/system_reg.h"
//#include "hal/systimer_hal.h"
//#include "hal/systimer_ll.h"
#ifdef CONFIG_FREERTOS_CORETIMER_0
	#define SYSTICK_INTR_ID (ETS_INTERNAL_TIMER0_INTR_SOURCE+ETS_INTERNAL_INTR_SOURCE_OFF)
#else
	#define SYSTICK_INTR_ID (ETS_INTERNAL_TIMER1_INTR_SOURCE+ETS_INTERNAL_INTR_SOURCE_OFF)
#endif


#define ETS_INTERNAL_TIMER0_INTR_SOURCE     -1 ///< Platform timer 0 interrupt source
#define ETS_INTERNAL_TIMER1_INTR_SOURCE     -2 ///< Platform timer 1 interrupt source
#define ETS_INTERNAL_TIMER2_INTR_SOURCE     -3 ///< Platform timer 2 interrupt source
#define ETS_INTERNAL_SW0_INTR_SOURCE        -4 ///< Software int source 1
#define ETS_INTERNAL_SW1_INTR_SOURCE        -5 ///< Software int source 2
#define ETS_INTERNAL_PROFILING_INTR_SOURCE  -6 ///< Int source for profiling
#define ETS_INTERNAL_UNUSED_INTR_SOURCE    -99 ///< Interrupt is not assigned to any source

/**@}*/

/** Provides SystemView with positive IRQ IDs, otherwise scheduler events are not shown properly
 */
#define ETS_INTERNAL_INTR_SOURCE_OFF        (-ETS_INTERNAL_PROFILING_INTR_SOURCE)

/** Enable interrupt by interrupt number */
#define ESP_INTR_ENABLE(inum)  esp_intr_enable_source(inum)

/** Disable interrupt by interrupt number */
#define ESP_INTR_DISABLE(inum) esp_intr_disable_source(inum)

#define traceISR_ENTER(...)
#define traceISR_EXIT(...)
#define traceQUEUE_GIVE_FROM_ISR(...)
#define traceQUEUE_TAKE_FROM_ISR(...)


BaseType_t xPortSysTickHandler(void);
BaseType_t xPortSysTickHandler(void)
{
    portbenchmarkIntLatency();
    traceISR_ENTER(SYSTICK_INTR_ID);
    BaseType_t ret = xTaskIncrementTick();
    if(ret != pdFALSE) {
        portYIELD_FROM_ISR();
    } else {
        traceISR_EXIT();
    }
    return ret;
}
