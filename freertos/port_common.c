#include <string.h>
#include <stdbool.h>
#include <errno.h>

#include "FreeRTOS.h"
#include "task.h"
#include "portmacro.h"
#include "soc/cross-int.h"
#include "soc/spiram.h"
#include "heap/esp_heap_caps.h"
#include "heap/esp_heap_caps_init.h"

#define MAX_HOOKS 8

typedef bool (*esp_freertos_idle_cb_t)(void);
typedef void (*esp_freertos_tick_cb_t)(void);

static const char* TAG = "cpu_start";
volatile unsigned port_xSchedulerRunning[portNUM_PROCESSORS] = {0};
static volatile bool s_other_cpu_startup_done = false;
static portMUX_TYPE hooks_spinlock = portMUX_INITIALIZER_UNLOCKED;

esp_freertos_idle_cb_t idle_cb[portNUM_PROCESSORS][MAX_HOOKS]={0};
esp_freertos_tick_cb_t tick_cb[portNUM_PROCESSORS][MAX_HOOKS]={0};

void esp_vApplicationTickHook(void)
{
	int n;
	int core = xPortGetCoreID();
	for (n=0; n<MAX_HOOKS; n++) {
		if (tick_cb[core][n]!=NULL) {
			tick_cb[core][n]();
		}
	}
}

void esp_pm_impl_waiti(void) {
#if CONFIG_FREERTOS_USE_TICKLESS_IDLE
	int core_id = xPortGetCoreID();
	if (s_skipped_light_sleep[core_id]) {
		cpu_ll_waiti();
		esp_pm_impl_idle_hook();
	}
	s_skipped_light_sleep[core_id] = true;
#else
	cpu_ll_waiti();
#endif // CONFIG_FREERTOS_USE_TICKLESS_IDLE
}


void esp_vApplicationIdleHook(void)
{
	bool can_go_idle=true;
	int core = xPortGetCoreID();
	for (int n = 0; n < MAX_HOOKS; n++) {
		if (idle_cb[core][n] != NULL && !idle_cb[core][n]()) {
			can_go_idle = false;
		}
	}
	if (!can_go_idle) {
		return;
	}

#ifdef CONFIG_PM_ENABLE
	esp_pm_impl_idle_hook();
#endif

	esp_pm_impl_waiti();
}

int esp_register_freertos_idle_hook_for_cpu(esp_freertos_idle_cb_t new_idle_cb, UBaseType_t cpuid)
{
	if(cpuid >= portNUM_PROCESSORS){
		return EINVAL;
	}
	portENTER_CRITICAL(&hooks_spinlock);
	for(int n = 0; n < MAX_HOOKS; n++){
		if (idle_cb[cpuid][n]==NULL) {
			idle_cb[cpuid][n]=new_idle_cb;
			portEXIT_CRITICAL(&hooks_spinlock);
			return 0;
		}
	}
	portEXIT_CRITICAL(&hooks_spinlock);
	return ENOMEM;
}

int esp_register_freertos_idle_hook(esp_freertos_idle_cb_t new_idle_cb)
{
	return esp_register_freertos_idle_hook_for_cpu(new_idle_cb, xPortGetCoreID());
}

int esp_register_freertos_tick_hook_for_cpu(esp_freertos_tick_cb_t new_tick_cb, UBaseType_t cpuid)
{
	if(cpuid >= portNUM_PROCESSORS){
		return EINVAL;
	}
	portENTER_CRITICAL(&hooks_spinlock);
	for(int n = 0; n < MAX_HOOKS; n++){
		if (tick_cb[cpuid][n]==NULL) {
			tick_cb[cpuid][n]=new_tick_cb;
			portEXIT_CRITICAL(&hooks_spinlock);
			return 0;
		}
	}
	portEXIT_CRITICAL(&hooks_spinlock);
	return ENOMEM;
}

int esp_register_freertos_tick_hook(esp_freertos_tick_cb_t new_tick_cb)
{
	return esp_register_freertos_tick_hook_for_cpu(new_tick_cb, xPortGetCoreID());
}

void esp_deregister_freertos_idle_hook_for_cpu(esp_freertos_idle_cb_t old_idle_cb, UBaseType_t cpuid)
{
	if(cpuid >= portNUM_PROCESSORS){
		return;
	}
	portENTER_CRITICAL(&hooks_spinlock);
	for(int n = 0; n < MAX_HOOKS; n++){
		if(idle_cb[cpuid][n] == old_idle_cb) idle_cb[cpuid][n] = NULL;
	}
	portEXIT_CRITICAL(&hooks_spinlock);
}

void esp_deregister_freertos_idle_hook(esp_freertos_idle_cb_t old_idle_cb)
{
	portENTER_CRITICAL(&hooks_spinlock);
	for(int m = 0; m < portNUM_PROCESSORS; m++) {
		esp_deregister_freertos_idle_hook_for_cpu(old_idle_cb, m);
	}
	portEXIT_CRITICAL(&hooks_spinlock);
}

void esp_deregister_freertos_tick_hook_for_cpu(esp_freertos_tick_cb_t old_tick_cb, UBaseType_t cpuid)
{
	if(cpuid >= portNUM_PROCESSORS){
		return;
	}
	portENTER_CRITICAL(&hooks_spinlock);
	for(int n = 0; n < MAX_HOOKS; n++){
		if(tick_cb[cpuid][n] == old_tick_cb) tick_cb[cpuid][n] = NULL;
	}
	portEXIT_CRITICAL(&hooks_spinlock);
}

void esp_deregister_freertos_tick_hook(esp_freertos_tick_cb_t old_tick_cb)
{
	portENTER_CRITICAL(&hooks_spinlock);
	for(int m = 0; m < portNUM_PROCESSORS; m++){
		esp_deregister_freertos_tick_hook_for_cpu(old_tick_cb, m);
	}
	portEXIT_CRITICAL(&hooks_spinlock);
}


static void main_task(void* args);
extern void app_main(void);

void esp_gdbstub_init(void);

void esp_startup_start_app_common(void) {
#if CONFIG_ESP_INT_WDT
	esp_int_wdt_init();
	//Initialize the interrupt watch dog for CPU0.
	esp_int_wdt_cpu_init();
#endif

	esp_crosscore_int_init();

	esp_gdbstub_init();

	portBASE_TYPE res = xTaskCreatePinnedToCore(&main_task, "main",
												ESP_TASK_MAIN_STACK, NULL,
												ESP_TASK_MAIN_PRIO, NULL, ESP_TASK_MAIN_CORE);
	assert(res == pdTRUE);
	(void)res;
}

static bool other_cpu_startup_idle_hook_cb(void) {
	s_other_cpu_startup_done = true;
	return true;
}


#define CONFIG_SPIRAM_MALLOC_RESERVE_INTERNAL 4096

static void main_task(void* args) {
	esp_register_freertos_idle_hook_for_cpu(other_cpu_startup_idle_hook_cb, !xPortGetCoreID());
	while (!s_other_cpu_startup_done) {
		;
	}
	esp_deregister_freertos_idle_hook_for_cpu(other_cpu_startup_idle_hook_cb, !xPortGetCoreID());

	// [refactor-todo] check if there is a way to move the following block to esp_system startup
	heap_caps_enable_nonos_stack_heaps();
	if (g_spiram_ok) {
		int r = esp_spiram_reserve_dma_pool(CONFIG_SPIRAM_MALLOC_RESERVE_INTERNAL);
		if (r != 0) {
			abort();
		}
	}

#ifdef CONFIG_ESP_TASK_WDT_PANIC
	if (esp_task_wdt_init(CONFIG_ESP_TASK_WDT_TIMEOUT_S, true)) {
		return;
	}
#elif CONFIG_ESP_TASK_WDT
	if (esp_task_wdt_init(CONFIG_ESP_TASK_WDT_TIMEOUT_S, false)) {
		return;
	}
#endif

#ifdef CONFIG_ESP_TASK_WDT_CHECK_IDLE_TASK_CPU0
	TaskHandle_t idle_0 = xTaskGetIdleTaskHandleForCPU(0);
	if(idle_0 != NULL){
		ESP_ERROR_CHECK(esp_task_wdt_add(idle_0));
	}
#endif
	//Add IDLE 1 to task wdt
#ifdef CONFIG_ESP_TASK_WDT_CHECK_IDLE_TASK_CPU1
	TaskHandle_t idle_1 = xTaskGetIdleTaskHandleForCPU(1);
	if(idle_1 != NULL){
		ESP_ERROR_CHECK(esp_task_wdt_add(idle_1));
	}
#endif

	app_main();
	vTaskDelete(NULL);
}

bool xPortCheckValidTCBMem(const void *ptr) {
	return esp_ptr_internal(ptr) && esp_ptr_byte_accessible(ptr);
}

bool xPortcheckValidStackMem(const void *ptr) {
#ifdef CONFIG_SPIRAM_ALLOW_STACK_EXTERNAL_MEMORY
	return esp_ptr_byte_accessible(ptr);
#else
	return esp_ptr_internal(ptr) && esp_ptr_byte_accessible(ptr);
#endif
}

void vApplicationGetIdleTaskMemory(StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize ) {
	StaticTask_t *pxTCBBufferTemp;
	StackType_t *pxStackBufferTemp;

	#if (portSTACK_GROWTH > 0)
	{
		//Allocate TCB and stack buffer in internal memory
		pxTCBBufferTemp = pvPortMallocTcbMem(sizeof(StaticTask_t));
		pxStackBufferTemp = pvPortMallocStackMem(configIDLE_TASK_STACK_SIZE);
	}
	#else
	{
		//Allocate TCB and stack buffer in internal memory
		pxStackBufferTemp = pvPortMallocStackMem(configIDLE_TASK_STACK_SIZE);
		pxTCBBufferTemp = pvPortMallocTcbMem(sizeof(StaticTask_t));
	}
	#endif

	assert(pxTCBBufferTemp != NULL);
	assert(pxStackBufferTemp != NULL);
	//Write back pointers
	*ppxIdleTaskTCBBuffer = pxTCBBufferTemp;
	*ppxIdleTaskStackBuffer = pxStackBufferTemp;
	*pulIdleTaskStackSize = configIDLE_TASK_STACK_SIZE;
}

void vApplicationGetTimerTaskMemory(StaticTask_t **ppxTimerTaskTCBBuffer, StackType_t **ppxTimerTaskStackBuffer, uint32_t *pulTimerTaskStackSize ) {
	StaticTask_t *pxTCBBufferTemp;
	StackType_t *pxStackBufferTemp;

#if (portSTACK_GROWTH > 0)
	{
		//Allocate TCB and stack buffer in internal memory
		pxTCBBufferTemp = pvPortMallocTcbMem(sizeof(StaticTask_t));
		pxStackBufferTemp = pvPortMallocStackMem(configTIMER_TASK_STACK_DEPTH);
	}
#else
	{
		//Allocate TCB and stack buffer in internal memory
		pxStackBufferTemp = pvPortMallocStackMem(configTIMER_TASK_STACK_DEPTH);
		pxTCBBufferTemp = pvPortMallocTcbMem(sizeof(StaticTask_t));
	}
#endif

	assert(pxTCBBufferTemp != NULL);
	assert(pxStackBufferTemp != NULL);
	//Write back pointers
	*ppxTimerTaskTCBBuffer = pxTCBBufferTemp;
	*ppxTimerTaskStackBuffer = pxStackBufferTemp;
	*pulTimerTaskStackSize = configTIMER_TASK_STACK_DEPTH;
}
