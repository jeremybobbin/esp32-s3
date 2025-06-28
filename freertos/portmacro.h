#pragma once 

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdarg.h>
#include <xtensa/core.h>
#include <xtensa/hal.h>             
#include <xtensa/xtruntime.h>       
#include "freertos/spinlock.h"
#include "soc/cross-int.h"
#include "heap/esp_heap_caps.h"
#include "portbenchmark.h"

#include <limits.h>
#include <xtensa/system.h>
#include "soc/cpu.h"

#define portCHAR                    int8_t
#define portFLOAT                   float
#define portDOUBLE                  double
#define portLONG                    int32_t
#define portSHORT                   int16_t
#define portSTACK_TYPE              uint8_t
#define portBASE_TYPE               int

typedef portSTACK_TYPE              StackType_t;
typedef portBASE_TYPE               BaseType_t;
typedef unsigned portBASE_TYPE      UBaseType_t;
typedef uint32_t TickType_t;

#define portMAX_DELAY ( TickType_t ) 0xffffffffUL
#define portTASK_FUNCTION_PROTO( vFunction, pvParameters )  void vFunction( void *pvParameters )
#define portTASK_FUNCTION( vFunction, pvParameters )        void vFunction( void *pvParameters )

#define portCRITICAL_NESTING_IN_TCB     0
#define portSTACK_GROWTH                ( -1 )
#define portTICK_PERIOD_MS              ( ( TickType_t ) 1000 / configTICK_RATE_HZ )
#define portBYTE_ALIGNMENT              16
#define portNOP()                       XT_NOP()
BaseType_t xPortInIsrContext(void);
void vPortAssertIfInISR(void);
BaseType_t xPortInterruptedFromISRContext(void);
static inline UBaseType_t xPortSetInterruptMaskFromISR(void);
static inline void vPortClearInterruptMaskFromISR(UBaseType_t prev_level);
typedef spinlock_t                          portMUX_TYPE;               
#define portMUX_INITIALIZER_UNLOCKED        SPINLOCK_INITIALIZER        
#define portMUX_FREE_VAL                    SPINLOCK_FREE               
#define portMUX_NO_TIMEOUT                  SPINLOCK_WAIT_FOREVER       
#define portMUX_TRY_LOCK                    SPINLOCK_NO_WAIT            
#define portMUX_INITIALIZE(mux)             spinlock_initialize(mux)    

BaseType_t xPortEnterCriticalTimeout(portMUX_TYPE *mux, BaseType_t timeout);
static inline void __attribute__((always_inline)) vPortEnterCritical(portMUX_TYPE *mux);
void vPortExitCritical(portMUX_TYPE *mux);
BaseType_t xPortEnterCriticalTimeoutCompliance(portMUX_TYPE *mux, BaseType_t timeout);
static inline void __attribute__((always_inline)) vPortEnterCriticalCompliance(portMUX_TYPE *mux);
void vPortExitCriticalCompliance(portMUX_TYPE *mux);
static inline BaseType_t __attribute__((always_inline)) xPortEnterCriticalTimeoutSafe(portMUX_TYPE *mux, BaseType_t timeout);
static inline void __attribute__((always_inline)) vPortEnterCriticalSafe(portMUX_TYPE *mux);
static inline void __attribute__((always_inline)) vPortExitCriticalSafe(portMUX_TYPE *mux);

void vPortYield( void );
void vPortEvaluateYieldFromISR(int argc, ...);
void vPortYieldOtherCore(BaseType_t coreid);
static inline bool IRAM_ATTR xPortCanYield(void);


extern void esp_vApplicationIdleHook(void);     
extern void esp_vApplicationTickHook(void);     
void vApplicationSleep(TickType_t xExpectedIdleTime);

uint32_t xPortGetTickRateHz(void);
void vPortSetStackWatchpoint( void *pxStackStart );
static inline BaseType_t IRAM_ATTR xPortGetCoreID(void);
static inline void __attribute__((always_inline)) uxPortCompareSet(volatile uint32_t *addr, uint32_t compare, uint32_t *set);

static inline void __attribute__((always_inline)) uxPortCompareSetExtram(volatile uint32_t *addr, uint32_t compare, uint32_t *set);
#define portTcbMemoryCaps               (MALLOC_CAP_INTERNAL|MALLOC_CAP_8BIT)
#define portStackMemoryCaps             (MALLOC_CAP_INTERNAL|MALLOC_CAP_8BIT)
#define pvPortMallocTcbMem(size)        heap_caps_malloc(size, portTcbMemoryCaps)
#define pvPortMallocStackMem(size)      heap_caps_malloc(size, portStackMemoryCaps)

#define portDISABLE_INTERRUPTS()            do { XTOS_SET_INTLEVEL(XCHAL_EXCM_LEVEL); portbenchmarkINTERRUPT_DISABLE(); } while (0)
#define portENABLE_INTERRUPTS()             do { portbenchmarkINTERRUPT_RESTORE(0); XTOS_SET_INTLEVEL(0); } while (0)
#define portSET_INTERRUPT_MASK_FROM_ISR()                   xPortSetInterruptMaskFromISR()
#define portCLEAR_INTERRUPT_MASK_FROM_ISR(prev_level)       vPortClearInterruptMaskFromISR(prev_level)

#define portASSERT_IF_IN_ISR() vPortAssertIfInISR()

#define portTRY_ENTER_CRITICAL(mux, timeout)        xPortEnterCriticalTimeout(mux, timeout)
#define portENTER_CRITICAL(mux)                     vPortEnterCritical(mux)
#define portEXIT_CRITICAL(mux)                      vPortExitCritical(mux)

#define portTRY_ENTER_CRITICAL_ISR(mux, timeout)    xPortEnterCriticalTimeout(mux, timeout)
#define portENTER_CRITICAL_ISR(mux)                 vPortEnterCritical(mux)
#define portEXIT_CRITICAL_ISR(mux)                  vPortExitCritical(mux)

#define portTRY_ENTER_CRITICAL_SAFE(mux, timeout)   xPortEnterCriticalTimeoutSafe(mux)
#define portENTER_CRITICAL_SAFE(mux)                vPortEnterCriticalSafe(mux)
#define portEXIT_CRITICAL_SAFE(mux)                 vPortExitCriticalSafe(mux)


#define portYIELD() vPortYield()
#define portYIELD_FROM_ISR(...) vPortEvaluateYieldFromISR(portGET_ARGUMENT_COUNT(__VA_ARGS__), ##__VA_ARGS__)
#define portYIELD_WITHIN_API() esp_crosscore_int_send_yield(xPortGetCoreID())


#ifndef CONFIG_FREERTOS_LEGACY_HOOKS
#define vApplicationIdleHook esp_vApplicationIdleHook
#define vApplicationTickHook esp_vApplicationTickHook
#endif 

#define portSUPPRESS_TICKS_AND_SLEEP(idleTime) vApplicationSleep(idleTime)


#define portCONFIGURE_TIMER_FOR_RUN_TIME_STATS()
#define portGET_RUN_TIME_COUNTER_VALUE() xthal_get_ccount()
#ifdef CONFIG_FREERTOS_RUN_TIME_STATS_USING_ESP_TIMER
#define portALT_GET_RUN_TIME_COUNTER_VALUE(x) do {x = (uint32_t)esp_timer_get_time();} while(0)
#endif


#if configUSE_PORT_OPTIMISED_TASK_SELECTION == 1

#if( configMAX_PRIORITIES > 32 )
#error configUSE_PORT_OPTIMISED_TASK_SELECTION can only be set to 1 when configMAX_PRIORITIES is less than or equal to 32.  It is very rare that a system requires more than 10 to 15 different priorities as tasks that share a priority will time slice.
#endif

#define portRECORD_READY_PRIORITY( uxPriority, uxReadyPriorities ) ( uxReadyPriorities ) |= ( 1UL << ( uxPriority ) )
#define portRESET_READY_PRIORITY( uxPriority, uxReadyPriorities ) ( uxReadyPriorities ) &= ~( 1UL << ( uxPriority ) )
#define portGET_HIGHEST_PRIORITY( uxTopPriority, uxReadyPriorities ) uxTopPriority = ( 31 - __builtin_clz( ( uxReadyPriorities ) ) )
#endif 


static inline UBaseType_t __attribute__((always_inline)) xPortSetInterruptMaskFromISR(void)
{
    UBaseType_t prev_int_level = XTOS_SET_INTLEVEL(XCHAL_EXCM_LEVEL);
    portbenchmarkINTERRUPT_DISABLE();
    return prev_int_level;
}

static inline void __attribute__((always_inline)) vPortClearInterruptMaskFromISR(UBaseType_t prev_level)
{
    portbenchmarkINTERRUPT_RESTORE(prev_level);
    XTOS_RESTORE_JUST_INTLEVEL(prev_level);
}


static inline void __attribute__((always_inline)) vPortEnterCritical(portMUX_TYPE *mux)
{
    xPortEnterCriticalTimeout(mux, portMUX_NO_TIMEOUT);
}

static inline void __attribute__((always_inline)) vPortEnterCriticalCompliance(portMUX_TYPE *mux)
{
    xPortEnterCriticalTimeoutCompliance(mux, portMUX_NO_TIMEOUT);
}

static inline BaseType_t __attribute__((always_inline)) xPortEnterCriticalTimeoutSafe(portMUX_TYPE *mux, BaseType_t timeout)
{
    BaseType_t ret;
    if (xPortInIsrContext()) {
        ret = portTRY_ENTER_CRITICAL_ISR(mux, timeout);
    } else {
        ret = portTRY_ENTER_CRITICAL(mux, timeout);
    }
    return ret;
}

static inline void __attribute__((always_inline)) vPortEnterCriticalSafe(portMUX_TYPE *mux)
{
    xPortEnterCriticalTimeoutSafe(mux, portMUX_NO_TIMEOUT);
}

static inline void __attribute__((always_inline)) vPortExitCriticalSafe(portMUX_TYPE *mux)
{
    if (xPortInIsrContext()) {
        portEXIT_CRITICAL_ISR(mux);
    } else {
        portEXIT_CRITICAL(mux);
    }
}


static inline bool IRAM_ATTR xPortCanYield(void)
{
    uint32_t ps_reg = 0;

    RSR(PS, ps_reg);

    

    return ((ps_reg & PS_INTLEVEL_MASK) == 0);
}


static inline BaseType_t IRAM_ATTR xPortGetCoreID(void)
{
    return (uint32_t) cpu_ll_get_core_id();
}

static inline void __attribute__((always_inline)) uxPortCompareSet(volatile uint32_t *addr, uint32_t compare, uint32_t *set)
{
    compare_and_set_native(addr, compare, set);
}

static inline void __attribute__((always_inline)) uxPortCompareSetExtram(volatile uint32_t *addr, uint32_t compare, uint32_t *set)
{
#ifdef CONFIG_SPIRAM
    compare_and_set_extram(addr, compare, set);
#endif
}

typedef struct {
#if XCHAL_CP_NUM > 0
    volatile StackType_t *coproc_area;
#endif

#if portUSING_MPU_WRAPPERS
    int mpu_setting;
#endif
} xMPU_SETTINGS;

#if (XCHAL_CP_NUM > 0) && !portUSING_MPU_WRAPPERS
#undef portUSING_MPU_WRAPPERS
#define portUSING_MPU_WRAPPERS 1
#define MPU_WRAPPERS_H
#define PRIVILEGED_FUNCTION
#define PRIVILEGED_DATA
#endif

void _xt_coproc_release(volatile void *coproc_sa_base);
#if( portUSING_MPU_WRAPPERS == 1 )
struct xMEMORY_REGION;
void vPortStoreTaskMPUSettings( xMPU_SETTINGS *xMPUSettings, const struct xMEMORY_REGION *const xRegions, StackType_t *pxBottomOfStack, uint32_t usStackDepth ) PRIVILEGED_FUNCTION;
void vPortReleaseTaskMPUSettings( xMPU_SETTINGS *xMPUSettings );
#endif

#define portGET_ARGUMENT_COUNT(...) portGET_ARGUMENT_COUNT_INNER(0, ##__VA_ARGS__,1,0)
#define portGET_ARGUMENT_COUNT_INNER(zero, one, count, ...) count

_Static_assert(portGET_ARGUMENT_COUNT() == 0, "portGET_ARGUMENT_COUNT() result does not match for 0 arguments");
_Static_assert(portGET_ARGUMENT_COUNT(1) == 1, "portGET_ARGUMENT_COUNT() result does not match for 1 argument");

bool xPortCheckValidTCBMem(const void *ptr);
bool xPortcheckValidStackMem(const void *ptr);

#define portVALID_TCB_MEM(ptr) xPortCheckValidTCBMem(ptr)
#define portVALID_STACK_MEM(ptr) xPortcheckValidStackMem(ptr)
