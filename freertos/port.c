#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <xtensa/core.h>
//#include <xtensa/xtensa_context.h>
//#include "soc/soc_caps.h"
//#include "esp_private/crosscore_int.h"
#include "soc/cross-int.h"
#include "rom/ets_sys.h"
//#include "esp_system.h"
//#include "esp_log.h"
//#include "esp_int_wdt.h"
//#include "esp_app_trace.h"    /* Required for esp_apptrace_init. [refactor-todo] */
//#include "esp_chip_info.h"
#include "FreeRTOS.h"        /* This pulls in portmacro.h */
#include "task.h"            /* Required for TaskHandle_t, tskNO_AFFINITY, and vTaskStartScheduler */

#define traceISR_EXIT_TO_SCHEDULER(...) // TODO
#define abort(...) // TODO

#define ALIGNUP(n, val) (((val) + (n)-1) & -(n))

#define ESP_WATCHPOINT_LOAD 0x40000000
#define ESP_WATCHPOINT_STORE 0x80000000
#define ESP_WATCHPOINT_ACCESS 0xC0000000

#define SOC_CPU_WATCHPOINTS_NUM         2
#define XT_STK_NEXT1      sizeof(XtExcFrame)
#define XT_STK_EXTRA            ALIGNUP(4, XT_STK_NEXT1)
#define XT_STK_NEXT2            (XT_STK_EXTRA + XCHAL_EXTRA_SA_SIZE)
#define XT_STK_FRMSZ            (ALIGNUP(0x10, XT_STK_NEXT2) + 0x20)


//#include "port_systick.h"
#define XT_CP0_SA   0
#define XT_CP1_SA   ALIGNUP(XCHAL_CP1_SA_ALIGN, XT_CP0_SA + XCHAL_CP0_SA_SIZE)
#define XT_CP2_SA   ALIGNUP(XCHAL_CP2_SA_ALIGN, XT_CP1_SA + XCHAL_CP1_SA_SIZE)
#define XT_CP3_SA   ALIGNUP(XCHAL_CP3_SA_ALIGN, XT_CP2_SA + XCHAL_CP2_SA_SIZE)
#define XT_CP4_SA   ALIGNUP(XCHAL_CP4_SA_ALIGN, XT_CP3_SA + XCHAL_CP3_SA_SIZE)
#define XT_CP5_SA   ALIGNUP(XCHAL_CP5_SA_ALIGN, XT_CP4_SA + XCHAL_CP4_SA_SIZE)
#define XT_CP6_SA   ALIGNUP(XCHAL_CP6_SA_ALIGN, XT_CP5_SA + XCHAL_CP5_SA_SIZE)
#define XT_CP7_SA   ALIGNUP(XCHAL_CP7_SA_ALIGN, XT_CP6_SA + XCHAL_CP6_SA_SIZE)
#define XT_CP_SA_SIZE   ALIGNUP(16, XT_CP7_SA + XCHAL_CP7_SA_SIZE)

/*  Offsets within the overall save area:  */
#define XT_CPENABLE 0   /* (2 bytes) coprocessors active for this thread */
#define XT_CPSTORED 2   /* (2 bytes) coprocessors saved for this thread */
#define XT_CP_CS_ST 4   /* (2 bytes) coprocessor callee-saved regs stored for this thread */
#define XT_CP_ASA   8   /* (4 bytes) ptr to aligned save area */
/*  Overall size allows for dynamic alignment:  */
#define XT_CP_SIZE  (12 + XT_CP_SA_SIZE + XCHAL_TOTAL_SA_ALIGN)


typedef struct {
	long exit;
	long pc;
	long ps;
	long a0;
	long a1;
	long a2;
	long a3;
	long a4;
	long a5;
	long a6;
	long a7;
	long a8;
	long a9;
	long a10;
	long a11;
	long a12;
	long a13;
	long a14;
	long a15;
	long sar;
	long exccause;
	long excvaddr;
	long lbeg;
	long lend;
	long lcount;
	long tmp0;
	long tmp1;
	long tmp2;
} XtExcFrame;



/* ---------------------------------------------------- Variables ------------------------------------------------------
 *
 * ------------------------------------------------------------------------------------------------------------------ */

static const char *TAG = "cpu_start"; /* [refactor-todo]: might be appropriate to change in the future, but for now maintain the same log output */
extern volatile int port_xSchedulerRunning[portNUM_PROCESSORS];
unsigned port_interruptNesting[portNUM_PROCESSORS] = {0};  // Interrupt nesting level. Increased/decreased in portasm.c, _frxt_int_enter/_frxt_int_exit
BaseType_t port_uxCriticalNesting[portNUM_PROCESSORS] = {0};
BaseType_t port_uxOldInterruptState[portNUM_PROCESSORS] = {0};


/* ------------------------------------------------ FreeRTOS Portable --------------------------------------------------
 * - Provides implementation for functions required by FreeRTOS
 * - Declared in portable.h
 * ------------------------------------------------------------------------------------------------------------------ */

// ----------------- Scheduler Start/End -------------------

/* Defined in xtensa_context.S */
extern void _xt_coproc_init(void);

BaseType_t xPortStartScheduler( void )
{
	portDISABLE_INTERRUPTS();
	// Interrupts are disabled at this point and stack contains PS with enabled interrupts when task context is restored

#if XCHAL_CP_NUM > 0
	/* Initialize co-processor management for tasks. Leave CPENABLE alone. */
	_xt_coproc_init();
#endif

	/* Setup the hardware to generate the tick. */
	vPortSetupTimer();

	port_xSchedulerRunning[xPortGetCoreID()] = 1;

	// Cannot be directly called from C; never returns
	__asm__ volatile ("call0    _frxt_dispatch\n");

	/* Should not get here. */
	return pdTRUE;
}

void vPortEndScheduler( void )
{
	/* It is unlikely that the Xtensa port will get stopped.  If required simply
	disable the tick interrupt here. */
	abort();
}

// ------------------------ Stack --------------------------

// User exception dispatcher when exiting
void _xt_user_exit(void);

#if CONFIG_FREERTOS_TASK_FUNCTION_WRAPPER
// Wrapper to allow task functions to return (increases stack overhead by 16 bytes)
static void vPortTaskWrapper(TaskFunction_t pxCode, void *pvParameters)
{
	pxCode(pvParameters);
	//FreeRTOS tasks should not return. Log the task name and abort.
	char *pcTaskName = pcTaskGetTaskName(NULL);
	abort();
}
#endif

#if portUSING_MPU_WRAPPERS
StackType_t *pxPortInitialiseStack( StackType_t *pxTopOfStack, TaskFunction_t pxCode, void *pvParameters, BaseType_t xRunPrivileged )
#else
StackType_t *pxPortInitialiseStack( StackType_t *pxTopOfStack, TaskFunction_t pxCode, void *pvParameters )
#endif
{
	StackType_t *sp, *tp;
	XtExcFrame  *frame;
#if XCHAL_CP_NUM > 0
	uint32_t *p;
#endif
	uint32_t *threadptr;
	void *task_thread_local_start;
	extern int _thread_local_start, _thread_local_end, _flash_rodata_start, _flash_rodata_align;
	// TODO: check that TLS area fits the stack
	uint32_t thread_local_sz = (uint8_t *)&_thread_local_end - (uint8_t *)&_thread_local_start;

	thread_local_sz = ALIGNUP(0x10, thread_local_sz);

	/* Initialize task's stack so that we have the following structure at the top:

		----LOW ADDRESSES ----------------------------------------HIGH ADDRESSES----------
		 task stack | interrupt stack frame | thread local vars | co-processor save area |
		----------------------------------------------------------------------------------
					|                                                                     |
					SP                                                                 pxTopOfStack

		All parts are aligned to 16 byte boundary. */
	sp = (StackType_t *) (((UBaseType_t)pxTopOfStack - XT_CP_SIZE - thread_local_sz - XT_STK_FRMSZ) & ~0xf);

	/* Clear the entire frame (do not use memset() because we don't depend on C library) */
	for (tp = sp; tp <= pxTopOfStack; ++tp) {
		*tp = 0;
	}

	frame = (XtExcFrame *) sp;

	/* Explicitly initialize certain saved registers */
#if CONFIG_FREERTOS_TASK_FUNCTION_WRAPPER
	frame->pc    = (UBaseType_t) vPortTaskWrapper;    /* task wrapper                        */
#else
	frame->pc   = (UBaseType_t) pxCode;                /* task entrypoint                    */
#endif
	frame->a0    = 0;                                /* to terminate GDB backtrace        */
	frame->a1    = (UBaseType_t) sp + XT_STK_FRMSZ;    /* physical top of stack frame        */
	frame->exit = (UBaseType_t) _xt_user_exit;        /* user exception exit dispatcher    */

	/* Set initial PS to int level 0, EXCM disabled ('rfe' will enable), user mode. */
	/* Also set entry point argument parameter. */
#ifdef __XTENSA_CALL0_ABI__
#if CONFIG_FREERTOS_TASK_FUNCTION_WRAPPER
	frame->a2 = (UBaseType_t) pxCode;
	frame->a3 = (UBaseType_t) pvParameters;
#else
	frame->a2 = (UBaseType_t) pvParameters;
#endif
	frame->ps = PS_UM | PS_EXCM;
#else /* __XTENSA_CALL0_ABI__ */
	/* + for windowed ABI also set WOE and CALLINC (pretend task was 'call4'd). */
#if CONFIG_FREERTOS_TASK_FUNCTION_WRAPPER
	frame->a6 = (UBaseType_t) pxCode;
	frame->a7 = (UBaseType_t) pvParameters;
#else
	frame->a6 = (UBaseType_t) pvParameters;
#endif
	frame->ps = PS_UM | PS_EXCM | PS_WOE | PS_CALLINC(1);
#endif /* __XTENSA_CALL0_ABI__ */

#ifdef XT_USE_SWPRI
	/* Set the initial virtual priority mask value to all 1's. */
	frame->vpri = 0xFFFFFFFF;
#endif

	/* Init threadptr register and set up TLS run-time area.
	 * The diagram in port/riscv/port.c illustrates the calculations below.
	 */
	task_thread_local_start = (void *)(((uint32_t)pxTopOfStack - XT_CP_SIZE - thread_local_sz) & ~0xf);
	memcpy(task_thread_local_start, &_thread_local_start, thread_local_sz);
	threadptr = (uint32_t *)(sp + XT_STK_EXTRA);
	/* Calculate THREADPTR value.
	 * The generated code will add THREADPTR value to a constant value determined at link time,
	 * to get the address of the TLS variable.
	 * The constant value is calculated by the linker as follows
	 * (search for 'tpoff' in elf32-xtensa.c in BFD):
	 *    offset = address - tls_section_vma + align_up(TCB_SIZE, tls_section_alignment)
	 * where TCB_SIZE is hardcoded to 8.
	 * Note this is slightly different compared to the RISC-V port, where offset = address - tls_section_vma.
	 */
	const uint32_t tls_section_alignment = (uint32_t) &_flash_rodata_align;  /* ALIGN value of .flash.rodata section */
	const uint32_t tcb_size = 8; /* Unrelated to FreeRTOS, this is the constant from BFD */
	const uint32_t base = (tcb_size + tls_section_alignment - 1) & (~(tls_section_alignment - 1));
	*threadptr = (uint32_t)task_thread_local_start - ((uint32_t)&_thread_local_start - (uint32_t)&_flash_rodata_start) - base;

#if XCHAL_CP_NUM > 0
	/* Init the coprocessor save area (see xtensa_context.h) */
	/* No access to TCB here, so derive indirectly. Stack growth is top to bottom.
	 * //p = (uint32_t *) xMPUSettings->coproc_area;
	 */
	p = (uint32_t *)(((uint32_t) pxTopOfStack - XT_CP_SIZE) & ~0xf);
	configASSERT( ( uint32_t ) p >= frame->a1 );
	p[0] = 0;
	p[1] = 0;
	p[2] = (((uint32_t) p) + 12 + XCHAL_TOTAL_SA_ALIGN - 1) & -XCHAL_TOTAL_SA_ALIGN;
#endif /* XCHAL_CP_NUM */

	configASSERT(((uint32_t) sp & portBYTE_ALIGNMENT_MASK) == 0);

	return sp;
}



/* ---------------------------------------------- Port Implementations -------------------------------------------------
 *
 * ------------------------------------------------------------------------------------------------------------------ */

// --------------------- Interrupts ------------------------

BaseType_t xPortInIsrContext(void)
{
	unsigned int irqStatus;
	BaseType_t ret;
	irqStatus = portSET_INTERRUPT_MASK_FROM_ISR();
	ret = (port_interruptNesting[xPortGetCoreID()] != 0);
	portCLEAR_INTERRUPT_MASK_FROM_ISR(irqStatus);
	return ret;
}

void vPortAssertIfInISR(void)
{
	configASSERT(xPortInIsrContext());
}

BaseType_t IRAM_ATTR xPortInterruptedFromISRContext(void)
{
	return (port_interruptNesting[xPortGetCoreID()] != 0);
}

// ------------------ Critical Sections --------------------

BaseType_t __attribute__((optimize("-O3"))) xPortEnterCriticalTimeout(portMUX_TYPE *mux, BaseType_t timeout)
{
	/* Interrupts may already be disabled (if this function is called in nested
	 * manner). However, there's no atomic operation that will allow us to check,
	 * thus we have to disable interrupts again anyways.
	 *
	 * However, if this is call is NOT nested (i.e., the first call to enter a
	 * critical section), we will save the previous interrupt level so that the
	 * saved level can be restored on the last call to exit the critical.
	 */
	BaseType_t xOldInterruptLevel = portSET_INTERRUPT_MASK_FROM_ISR();
	if (!spinlock_acquire(mux, timeout)) {
		//Timed out attempting to get spinlock. Restore previous interrupt level and return
		portCLEAR_INTERRUPT_MASK_FROM_ISR(xOldInterruptLevel);
		return pdFAIL;
	}
	//Spinlock acquired. Increment the critical nesting count.
	BaseType_t coreID = xPortGetCoreID();
	BaseType_t newNesting = port_uxCriticalNesting[coreID] + 1;
	port_uxCriticalNesting[coreID] = newNesting;
	//If this is the first entry to a critical section. Save the old interrupt level.
	if ( newNesting == 1 ) {
		port_uxOldInterruptState[coreID] = xOldInterruptLevel;
	}
	return pdPASS;
}

void __attribute__((optimize("-O3"))) vPortExitCritical(portMUX_TYPE *mux)
{
	/* This function may be called in a nested manner. Therefore, we only need
	 * to reenable interrupts if this is the last call to exit the critical. We
	 * can use the nesting count to determine whether this is the last exit call.
	 */
	spinlock_release(mux);
	BaseType_t coreID = xPortGetCoreID();
	BaseType_t nesting = port_uxCriticalNesting[coreID];

	if (nesting > 0) {
		nesting--;
		port_uxCriticalNesting[coreID] = nesting;
		//This is the last exit call, restore the saved interrupt level
		if ( nesting == 0 ) {
			portCLEAR_INTERRUPT_MASK_FROM_ISR(port_uxOldInterruptState[coreID]);
		}
	}
}

BaseType_t xPortEnterCriticalTimeoutCompliance(portMUX_TYPE *mux, BaseType_t timeout)
{
	BaseType_t ret;
	if (!xPortInIsrContext()) {
		ret = xPortEnterCriticalTimeout(mux, timeout);
	} else {
		ets_printf("port*_CRITICAL called from ISR context. Aborting!\n");
		abort();
		ret = pdFAIL;
	}
	return ret;
}

void vPortExitCriticalCompliance(portMUX_TYPE *mux)
{
	if (!xPortInIsrContext()) {
		vPortExitCritical(mux);
	} else {
		ets_printf("port*_CRITICAL called from ISR context. Aborting!\n");
		abort();
	}
}

// ---------------------- Yielding -------------------------

void vPortYieldOtherCore( BaseType_t coreid )
{
	esp_crosscore_int_send_yield( coreid );
}

extern void _frxt_setup_switch( void );     //Defined in portasm.S

void IRAM_ATTR vPortEvaluateYieldFromISR(int argc, ...)
{
	BaseType_t xYield;
	va_list ap;
	va_start(ap, argc);

	if (argc) {
		xYield = (BaseType_t)va_arg(ap, int);
		va_end(ap);
	} else {
		//it is a empty parameter vPortYieldFromISR macro call:
		va_end(ap);
		traceISR_EXIT_TO_SCHEDULER();
		_frxt_setup_switch();
		return;
	}

	//Yield exists, so need evaluate it first then switch:
	if (xYield == pdTRUE) {
		traceISR_EXIT_TO_SCHEDULER();
		_frxt_setup_switch();
	}
}

// ------------------- Hook Functions ----------------------

void  __attribute__((weak)) vApplicationStackOverflowHook( TaskHandle_t xTask, char *pcTaskName )
{
#define ERR_STR1 "***ERROR*** A stack overflow in task "
#define ERR_STR2 " has been detected."
	const char *str[] = {ERR_STR1, pcTaskName, ERR_STR2};

	char buf[sizeof(ERR_STR1) + CONFIG_FREERTOS_MAX_TASK_NAME_LEN + sizeof(ERR_STR2) + 1 /* null char */] = { 0 };

	char *dest = buf;
	for (size_t i = 0 ; i < sizeof(str) / sizeof(str[0]); i++) {
		dest = strcat(dest, str[i]);
	}
	//esp_system_abort(buf);
}

// ----------------------- System --------------------------

uint32_t xPortGetTickRateHz(void)
{
	return (uint32_t)configTICK_RATE_HZ;
}


#define STACK_WATCH_AREA_SIZE 32
#define STACK_WATCH_POINT_NUMBER (SOC_CPU_WATCHPOINTS_NUM - 1)

void vPortSetStackWatchpoint( void *pxStackStart )
{
	//Set watchpoint 1 to watch the last 32 bytes of the stack.
	//Unfortunately, the Xtensa watchpoints can't set a watchpoint on a random [base - base+n] region because
	//the size works by masking off the lowest address bits. For that reason, we futz a bit and watch the lowest 32
	//bytes of the stack we can actually watch. In general, this can cause the watchpoint to be triggered at most
	//28 bytes early. The value 32 is chosen because it's larger than the stack canary, which in FreeRTOS is 20 bytes.
	//This way, we make sure we trigger before/when the stack canary is corrupted, not after.
	int addr = (int)pxStackStart;
	addr = (addr + 31) & (~31);

	cpu_ll_set_watchpoint(STACK_WATCH_POINT_NUMBER, (char *)addr, 32, false, true);
}

/* ---------------------------------------------- Misc Implementations -------------------------------------------------
 *
 * ------------------------------------------------------------------------------------------------------------------ */

// -------------------- Co-Processor -----------------------

/*
 * Used to set coprocessor area in stack. Current hack is to reuse MPU pointer for coprocessor area.
 */
#if portUSING_MPU_WRAPPERS
void vPortStoreTaskMPUSettings( xMPU_SETTINGS *xMPUSettings, const struct xMEMORY_REGION *const xRegions, StackType_t *pxBottomOfStack, uint32_t usStackDepth )
{
#if XCHAL_CP_NUM > 0
	xMPUSettings->coproc_area = ( StackType_t * ) ( ( uint32_t ) ( pxBottomOfStack + usStackDepth - 1 ));
	xMPUSettings->coproc_area = ( StackType_t * ) ( ( ( portPOINTER_SIZE_TYPE ) xMPUSettings->coproc_area ) & ( ~( ( portPOINTER_SIZE_TYPE ) portBYTE_ALIGNMENT_MASK ) ) );
	xMPUSettings->coproc_area = ( StackType_t * ) ( ( ( uint32_t ) xMPUSettings->coproc_area - XT_CP_SIZE ) & ~0xf );


	/* NOTE: we cannot initialize the coprocessor save area here because FreeRTOS is going to
	 * clear the stack area after we return. This is done in pxPortInitialiseStack().
	 */
#endif
}

void vPortReleaseTaskMPUSettings( xMPU_SETTINGS *xMPUSettings )
{
	/* If task has live floating point registers somewhere, release them */
	_xt_coproc_release( xMPUSettings->coproc_area );
}
#endif /* portUSING_MPU_WRAPPERS */

// --------------------- App Start-up ----------------------

#if !CONFIG_FREERTOS_UNICORE
void esp_startup_start_app_other_cores(void)
{
	// For now, we only support up to two core: 0 and 1.
	if (xPortGetCoreID() >= 2) {
		abort();
	}

	// Wait for FreeRTOS initialization to finish on PRO CPU
	while (port_xSchedulerRunning[0] == 0) {
		;
	}

#if CONFIG_ESP_INT_WDT
	//Initialize the interrupt watch dog for CPU1.
	esp_int_wdt_cpu_init();
#endif

	esp_crosscore_int_init();

	xPortStartScheduler();
	abort(); /* Only get to here if FreeRTOS somehow very broken */
}
#endif // !CONFIG_FREERTOS_UNICORE

extern void esp_startup_start_app_common(void);

void esp_startup_start_app(void)
{
#if !CONFIG_ESP_INT_WDT
#if CONFIG_ESP32_ECO3_CACHE_LOCK_FIX
	assert(!soc_has_cache_lock_bug() && "ESP32 Rev 3 + Dual Core + PSRAM requires INT WDT enabled in project config!");
#endif
#endif

	esp_startup_start_app_common();

	vTaskStartScheduler();
}
