#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>
#include <assert.h>
#include <errno.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "soc/cpu.h"
#include "heap/soc_memory_layout.h"
#include "soc/intr-alloc.h"

static const char* TAG = "intr_alloc";

#define ETS_INTERNAL_TIMER0_INTR_NO 6
#define ETS_INTERNAL_TIMER1_INTR_NO 15
#define ETS_INTERNAL_TIMER2_INTR_NO 16
#define ETS_INTERNAL_SW0_INTR_NO 7
#define ETS_INTERNAL_SW1_INTR_NO 29
#define ETS_INTERNAL_PROFILING_INTR_NO 11

typedef struct shared_vector_desc_t shared_vector_desc_t;
typedef struct vector_desc_t vector_desc_t;

struct shared_vector_desc_t {
	int disabled: 1;
	int source: 8;
	volatile uint32_t *statusreg;
	uint32_t statusmask;
	intr_handler_t isr;
	void *arg;
	shared_vector_desc_t *next;
};

#define VECDESC_FL_RESERVED     (1<<0)
#define VECDESC_FL_INIRAM       (1<<1)
#define VECDESC_FL_SHARED       (1<<2)
#define VECDESC_FL_NONSHARED    (1<<3)

struct vector_desc_t {
	int flags: 16;
	unsigned int cpu: 1;
	unsigned int intno: 5;
	int source: 8;
	shared_vector_desc_t *shared_vec_info;
	vector_desc_t *next;
};

struct intr_handle_data_t {
	vector_desc_t *vector_desc;
	shared_vector_desc_t *shared_vector_desc;
};

typedef struct non_shared_isr_arg_t non_shared_isr_arg_t;

struct non_shared_isr_arg_t {
	intr_handler_t isr;
	void *isr_arg;
	int source;
};

static vector_desc_t *vector_desc_head = NULL;

static uint32_t non_iram_int_mask[SOC_CPU_CORES_NUM];

static uint32_t non_iram_int_disabled[SOC_CPU_CORES_NUM];
static bool non_iram_int_disabled_flag[SOC_CPU_CORES_NUM];

static portMUX_TYPE spinlock = portMUX_INITIALIZER_UNLOCKED;

static void insert_vector_desc(vector_desc_t *to_insert)
{
	vector_desc_t *vd=vector_desc_head;
	vector_desc_t *prev=NULL;
	while(vd!=NULL) {
		if (vd->cpu > to_insert->cpu) break;
		if (vd->cpu == to_insert->cpu && vd->intno >= to_insert->intno) break;
		prev=vd;
		vd=vd->next;
	}
	if ((vector_desc_head==NULL) || (prev==NULL)) {
		to_insert->next = vd;
		vector_desc_head=to_insert;
	} else {
		prev->next=to_insert;
		to_insert->next=vd;
	}
}

//Returns a vector_desc entry for an intno/cpu, or NULL if none exists.
static vector_desc_t *find_desc_for_int(int intno, int cpu)
{
	vector_desc_t *vd=vector_desc_head;
	while(vd!=NULL) {
		if (vd->cpu==cpu && vd->intno==intno) break;
		vd=vd->next;
	}
	return vd;
}

static vector_desc_t *get_desc_for_int(int intno, int cpu)
{
	vector_desc_t *vd=find_desc_for_int(intno, cpu);
	if (vd==NULL) {
		vector_desc_t *newvd=heap_caps_malloc(sizeof(vector_desc_t), MALLOC_CAP_INTERNAL|MALLOC_CAP_8BIT);
		if (newvd==NULL) return NULL;
		memset(newvd, 0, sizeof(vector_desc_t));
		newvd->intno=intno;
		newvd->cpu=cpu;
		insert_vector_desc(newvd);
		return newvd;
	} else {
		return vd;
	}
}

static vector_desc_t * find_desc_for_source(int source, int cpu)
{
	vector_desc_t *vd=vector_desc_head;
	while(vd!=NULL) {
		if ( !(vd->flags & VECDESC_FL_SHARED) ) {
			if ( vd->source == source && cpu == vd->cpu ) break;
		} else if ( vd->cpu == cpu ) {
			bool found = false;
			shared_vector_desc_t *svd = vd->shared_vec_info;
			assert(svd != NULL );
			while(svd) {
				if ( svd->source == source ) {
					found = true;
					break;
				}
				svd = svd->next;
			}
			if ( found ) break;
		}
		vd=vd->next;
	}
	return vd;
}

int esp_intr_mark_shared(int intno, int cpu, bool is_int_ram)
{
	if (intno>31) return EINVAL;
	if (cpu>=SOC_CPU_CORES_NUM) return EINVAL;

	portENTER_CRITICAL(&spinlock);
	vector_desc_t *vd=get_desc_for_int(intno, cpu);
	if (vd==NULL) {
		portEXIT_CRITICAL(&spinlock);
		return ENOMEM;
	}
	vd->flags=VECDESC_FL_SHARED;
	if (is_int_ram) vd->flags|=VECDESC_FL_INIRAM;
	portEXIT_CRITICAL(&spinlock);

	return ESP_OK;
}

int esp_intr_reserve(int intno, int cpu)
{
	if (intno>31) return EINVAL;
	if (cpu>=SOC_CPU_CORES_NUM) return EINVAL;

	portENTER_CRITICAL(&spinlock);
	vector_desc_t *vd=get_desc_for_int(intno, cpu);
	if (vd==NULL) {
		portEXIT_CRITICAL(&spinlock);
		return ENOMEM;
	}
	vd->flags=VECDESC_FL_RESERVED;
	portEXIT_CRITICAL(&spinlock);

	return ESP_OK;
}

static bool is_vect_desc_usable(vector_desc_t *vd, int flags, int cpu, int force)
{
	int x = vd->intno;
	if (interrupt_controller_hal_get_cpu_desc_flags(x, cpu)==INTDESC_RESVD) {
		return false;
	}
	if (interrupt_controller_hal_get_cpu_desc_flags(x, cpu)==INTDESC_SPECIAL && force==-1) {
		return false;
	}

	//check if interrupt is reserved at runtime
	if (vd->flags&VECDESC_FL_RESERVED)  {
		return false;
	}

	//Ints can't be both shared and non-shared.
	assert(!((vd->flags&VECDESC_FL_SHARED)&&(vd->flags&VECDESC_FL_NONSHARED)));
	//check if interrupt already is in use by a non-shared interrupt
	if (vd->flags&VECDESC_FL_NONSHARED) {
		return false;
	}
	// check shared interrupt flags
	if (vd->flags&VECDESC_FL_SHARED ) {
		if (flags&ESP_INTR_FLAG_SHARED) {
			bool in_iram_flag=((flags&ESP_INTR_FLAG_IRAM)!=0);
			bool desc_in_iram_flag=((vd->flags&VECDESC_FL_INIRAM)!=0);
			//Bail out if int is shared, but iram property doesn't match what we want.
			if ((vd->flags&VECDESC_FL_SHARED) && (desc_in_iram_flag!=in_iram_flag))  {
				return false;
			}
		} else {
			//We need an unshared IRQ; can't use shared ones; bail out if this is shared.
			return false;
		}
	} else if (interrupt_controller_hal_has_handler(x, cpu)) {
		//Check if interrupt already is allocated by interrupt_controller_hal_set_int_handler
		return false;
	}

	return true;
}

//Locate a free interrupt compatible with the flags given.
//The 'force' argument can be -1, or 0-31 to force checking a certain interrupt.
//When a CPU is forced, the INTDESC_SPECIAL marked interrupts are also accepted.
static int get_available_int(int flags, int cpu, int force, int source)
{
	int x;
	int best=-1;
	int bestLevel=9;
	int bestSharedCt=INT_MAX;

	//Default vector desc, for vectors not in the linked list
	vector_desc_t empty_vect_desc;
	memset(&empty_vect_desc, 0, sizeof(vector_desc_t));

	//Level defaults to any low/med interrupt
	if (!(flags&ESP_INTR_FLAG_LEVELMASK)) flags|=ESP_INTR_FLAG_LOWMED;

	vector_desc_t *vd = find_desc_for_source(source, cpu);
	if ( vd ) {
		// if existing vd found, don't need to search any more.
		if ( force != -1 && force != vd->intno ) {
		} else if ( !is_vect_desc_usable(vd, flags, cpu, force) ) {
		} else {
			best = vd->intno;
		}
		return best;
	}
	if (force!=-1) {
		//if force assigned, don't need to search any more.
		vd = find_desc_for_int(force, cpu);
		if (vd == NULL ) {
			//if existing vd not found, just check the default state for the intr.
			empty_vect_desc.intno = force;
			vd = &empty_vect_desc;
		}
		if ( is_vect_desc_usable(vd, flags, cpu, force) ) {
			best = vd->intno;
		} else {
		}
		return best;
	}

	//No allocated handlers as well as forced intr, iterate over the 32 possible interrupts
	for (x=0; x<32; x++) {
		//Grab the vector_desc for this vector.
		vd=find_desc_for_int(x, cpu);
		if (vd==NULL) {
			empty_vect_desc.intno = x;
			vd=&empty_vect_desc;
		}

			x, interrupt_controller_hal_get_cpu_desc_flags(x,cpu)==INTDESC_RESVD, interrupt_controller_hal_get_level(x),
			interrupt_controller_hal_get_type(x)==INTTP_LEVEL?"LEVEL":"EDGE", interrupt_controller_hal_has_handler(x, cpu));

		if ( !is_vect_desc_usable(vd, flags, cpu, force) ) continue;

		if (flags&ESP_INTR_FLAG_SHARED) {
			//We're allocating a shared int.

			//See if int already is used as a shared interrupt.
			if (vd->flags&VECDESC_FL_SHARED) {
				//We can use this already-marked-as-shared interrupt. Count the already attached isrs in order to see
				//how useful it is.
				int no=0;
				shared_vector_desc_t *svdesc=vd->shared_vec_info;
				while (svdesc!=NULL) {
					no++;
					svdesc=svdesc->next;
				}
				if (no<bestSharedCt || bestLevel>interrupt_controller_hal_get_level(x)) {
					//Seems like this shared vector is both okay and has the least amount of ISRs already attached to it.
					best=x;
					bestSharedCt=no;
					bestLevel=interrupt_controller_hal_get_level(x);
				} else {
				}
			} else {
				if (best==-1) {
					//We haven't found a feasible shared interrupt yet. This one is still free and usable, even if
					//not marked as shared.
					//Remember it in case we don't find any other shared interrupt that qualifies.
					if (bestLevel>interrupt_controller_hal_get_level(x)) {
						best=x;
						bestLevel=interrupt_controller_hal_get_level(x);
					}
				} else {
				}
			}
		} else {
			//Seems this interrupt is feasible. Select it and break out of the loop; no need to search further.
			if (bestLevel>interrupt_controller_hal_get_level(x)) {
				best=x;
				bestLevel=interrupt_controller_hal_get_level(x);
			} else {
			}
		}
	}

	//Okay, by now we have looked at all potential interrupts and hopefully have selected the best one in best.
	return best;
}

//Common shared isr handler. Chain-call all ISRs.
static void IRAM_ATTR shared_intr_isr(void *arg)
{
	vector_desc_t *vd=(vector_desc_t*)arg;
	shared_vector_desc_t *sh_vec=vd->shared_vec_info;
	portENTER_CRITICAL_ISR(&spinlock);
	while(sh_vec) {
		if (!sh_vec->disabled) {
			if ((sh_vec->statusreg == NULL) || (*sh_vec->statusreg & sh_vec->statusmask)) {
				traceISR_ENTER(sh_vec->source+ETS_INTERNAL_INTR_SOURCE_OFF);
				sh_vec->isr(sh_vec->arg);
				// check if we will return to scheduler or to interrupted task after ISR
				if (!os_task_switch_is_pended(cpu_hal_get_core_id())) {
					traceISR_EXIT();
				}
			}
		}
		sh_vec=sh_vec->next;
	}
	portEXIT_CRITICAL_ISR(&spinlock);
}

#if CONFIG_APPTRACE_SV_ENABLE
//Common non-shared isr handler wrapper.
static void IRAM_ATTR non_shared_intr_isr(void *arg)
{
	non_shared_isr_arg_t *ns_isr_arg=(non_shared_isr_arg_t*)arg;
	portENTER_CRITICAL_ISR(&spinlock);
	traceISR_ENTER(ns_isr_arg->source+ETS_INTERNAL_INTR_SOURCE_OFF);
	// FIXME: can we call ISR and check os_task_switch_is_pended() after releasing spinlock?
	// when CONFIG_APPTRACE_SV_ENABLE = 0 ISRs for non-shared IRQs are called without spinlock
	ns_isr_arg->isr(ns_isr_arg->isr_arg);
	// check if we will return to scheduler or to interrupted task after ISR
	if (!os_task_switch_is_pended(cpu_hal_get_core_id())) {
		traceISR_EXIT();
	}
	portEXIT_CRITICAL_ISR(&spinlock);
}
#endif

//We use ESP_EARLY_LOG* here because this can be called before the scheduler is running.
int esp_intr_alloc_intrstatus(int source, int flags, uint32_t intrstatusreg, uint32_t intrstatusmask, intr_handler_t handler,
										void *arg, intr_handle_t *ret_handle)
{
	intr_handle_data_t *ret=NULL;
	int force=-1;
	ESP_EARLY_LOGV(TAG, "esp_intr_alloc_intrstatus (cpu %u): checking args", cpu_hal_get_core_id());
	//Shared interrupts should be level-triggered.
	if ((flags&ESP_INTR_FLAG_SHARED) && (flags&ESP_INTR_FLAG_EDGE)) return EINVAL;
	//You can't set an handler / arg for a non-C-callable interrupt.
	if ((flags&ESP_INTR_FLAG_HIGH) && (handler)) return EINVAL;
	//Shared ints should have handler and non-processor-local source
	if ((flags&ESP_INTR_FLAG_SHARED) && (!handler || source<0)) return EINVAL;
	//Statusreg should have a mask
	if (intrstatusreg && !intrstatusmask) return EINVAL;
	//If the ISR is marked to be IRAM-resident, the handler must not be in the cached region
	//ToDo: if we are to allow placing interrupt handlers into the 0x400c0000—0x400c2000 region,
	//we need to make sure the interrupt is connected to the CPU0.
	//CPU1 does not have access to the RTC fast memory through this region.
	if ((flags & ESP_INTR_FLAG_IRAM) && handler && !esp_ptr_in_iram(handler) && !esp_ptr_in_rtc_iram_fast(handler)) {
		return EINVAL;
	}

	//Default to prio 1 for shared interrupts. Default to prio 1, 2 or 3 for non-shared interrupts.
	if ((flags&ESP_INTR_FLAG_LEVELMASK)==0) {
		if (flags&ESP_INTR_FLAG_SHARED) {
			flags|=ESP_INTR_FLAG_LEVEL1;
		} else {
			flags|=ESP_INTR_FLAG_LOWMED;
		}
	}
	ESP_EARLY_LOGV(TAG, "esp_intr_alloc_intrstatus (cpu %u): Args okay. Resulting flags 0x%X", cpu_hal_get_core_id(), flags);

	//Check 'special' interrupt sources. These are tied to one specific interrupt, so we
	//have to force get_free_int to only look at that.
	if (source==ETS_INTERNAL_TIMER0_INTR_SOURCE) force=ETS_INTERNAL_TIMER0_INTR_NO;
	if (source==ETS_INTERNAL_TIMER1_INTR_SOURCE) force=ETS_INTERNAL_TIMER1_INTR_NO;
	if (source==ETS_INTERNAL_TIMER2_INTR_SOURCE) force=ETS_INTERNAL_TIMER2_INTR_NO;
	if (source==ETS_INTERNAL_SW0_INTR_SOURCE) force=ETS_INTERNAL_SW0_INTR_NO;
	if (source==ETS_INTERNAL_SW1_INTR_SOURCE) force=ETS_INTERNAL_SW1_INTR_NO;
	if (source==ETS_INTERNAL_PROFILING_INTR_SOURCE) force=ETS_INTERNAL_PROFILING_INTR_NO;

	//Allocate a return handle. If we end up not needing it, we'll free it later on.
	ret=heap_caps_malloc(sizeof(intr_handle_data_t), MALLOC_CAP_INTERNAL|MALLOC_CAP_8BIT);
	if (ret==NULL) return ENOMEM;

	portENTER_CRITICAL(&spinlock);
	uint32_t cpu = cpu_hal_get_core_id();
	//See if we can find an interrupt that matches the flags.
	int intr=get_available_int(flags, cpu, force, source);
	if (intr==-1) {
		//None found. Bail out.
		portEXIT_CRITICAL(&spinlock);
		free(ret);
		return ENOENT;
	}
	//Get an int vector desc for int.
	vector_desc_t *vd=get_desc_for_int(intr, cpu);
	if (vd==NULL) {
		portEXIT_CRITICAL(&spinlock);
		free(ret);
		return ENOMEM;
	}

	//Allocate that int!
	if (flags&ESP_INTR_FLAG_SHARED) {
		//Populate vector entry and add to linked list.
		shared_vector_desc_t *sh_vec=malloc(sizeof(shared_vector_desc_t));
		if (sh_vec==NULL) {
			portEXIT_CRITICAL(&spinlock);
			free(ret);
			return ENOMEM;
		}
		memset(sh_vec, 0, sizeof(shared_vector_desc_t));
		sh_vec->statusreg=(uint32_t*)intrstatusreg;
		sh_vec->statusmask=intrstatusmask;
		sh_vec->isr=handler;
		sh_vec->arg=arg;
		sh_vec->next=vd->shared_vec_info;
		sh_vec->source=source;
		sh_vec->disabled=0;
		vd->shared_vec_info=sh_vec;
		vd->flags|=VECDESC_FL_SHARED;
		//(Re-)set shared isr handler to new value.
		interrupt_controller_hal_set_int_handler(intr, shared_intr_isr, vd);
	} else {
		//Mark as unusable for other interrupt sources. This is ours now!
		vd->flags=VECDESC_FL_NONSHARED;
		if (handler) {
#if CONFIG_APPTRACE_SV_ENABLE
			non_shared_isr_arg_t *ns_isr_arg=malloc(sizeof(non_shared_isr_arg_t));
			if (!ns_isr_arg) {
				portEXIT_CRITICAL(&spinlock);
				free(ret);
				return ENOMEM;
			}
			ns_isr_arg->isr=handler;
			ns_isr_arg->isr_arg=arg;
			ns_isr_arg->source=source;
			interrupt_controller_hal_set_int_handler(intr, non_shared_intr_isr, ns_isr_arg);
#else
			interrupt_controller_hal_set_int_handler(intr, handler, arg);
#endif
		}

		if (flags & ESP_INTR_FLAG_EDGE) {
			interrupt_controller_hal_edge_int_acknowledge(intr);
		}

		vd->source=source;
	}
	if (flags&ESP_INTR_FLAG_IRAM) {
		vd->flags|=VECDESC_FL_INIRAM;
		non_iram_int_mask[cpu]&=~(1<<intr);
	} else {
		vd->flags&=~VECDESC_FL_INIRAM;
		non_iram_int_mask[cpu]|=(1<<intr);
	}
	if (source>=0) {
		intr_matrix_set(cpu, source, intr);
	}

	//Fill return handle data.
	ret->vector_desc=vd;
	ret->shared_vector_desc=vd->shared_vec_info;

	//Enable int at CPU-level;
	ESP_INTR_ENABLE(intr);

	//If interrupt has to be started disabled, do that now; ints won't be enabled for real until the end
	//of the critical section.
	if (flags&ESP_INTR_FLAG_INTRDISABLED) {
		esp_intr_disable(ret);
	}

	portEXIT_CRITICAL(&spinlock);

	//Fill return handle if needed, otherwise free handle.
	if (ret_handle!=NULL) {
		*ret_handle=ret;
	} else {
		free(ret);
	}

	ESP_EARLY_LOGD(TAG, "Connected src %d to int %d (cpu %d)", source, intr, cpu);
	return ESP_OK;
}

int esp_intr_alloc(int source, int flags, intr_handler_t handler, void *arg, intr_handle_t *ret_handle)
{
	return esp_intr_alloc_intrstatus(source, flags, 0, 0, handler, arg, ret_handle);
}

int IRAM_ATTR esp_intr_set_in_iram(intr_handle_t handle, bool is_in_iram)
{
	if (!handle) return EINVAL;
	vector_desc_t *vd = handle->vector_desc;
	if (vd->flags & VECDESC_FL_SHARED) {
	  return EINVAL;
	}
	portENTER_CRITICAL(&spinlock);
	uint32_t mask = (1 << vd->intno);
	if (is_in_iram) {
		vd->flags |= VECDESC_FL_INIRAM;
		non_iram_int_mask[vd->cpu] &= ~mask;
	} else {
		vd->flags &= ~VECDESC_FL_INIRAM;
		non_iram_int_mask[vd->cpu] |= mask;
	}
	portEXIT_CRITICAL(&spinlock);
	return ESP_OK;
}

#if !CONFIG_FREERTOS_UNICORE
static void esp_intr_free_cb(void *arg)
{
	(void)esp_intr_free((intr_handle_t)arg);
}
#endif 

int esp_intr_free(intr_handle_t handle)
{
	bool free_shared_vector=false;
	if (!handle) return EINVAL;

#if !CONFIG_FREERTOS_UNICORE
	//Assign this routine to the core where this interrupt is allocated on.
	if (handle->vector_desc->cpu!=cpu_hal_get_core_id()) {
		int ret = esp_ipc_call_blocking(handle->vector_desc->cpu, &esp_intr_free_cb, (void *)handle);
		return ret == ESP_OK ? ESP_OK : ESP_FAIL;
	}
#endif 

	portENTER_CRITICAL(&spinlock);
	esp_intr_disable(handle);
	if (handle->vector_desc->flags&VECDESC_FL_SHARED) {
		//Find and kill the shared int
		shared_vector_desc_t *svd=handle->vector_desc->shared_vec_info;
		shared_vector_desc_t *prevsvd=NULL;
		assert(svd); //should be something in there for a shared int
		while (svd!=NULL) {
			if (svd==handle->shared_vector_desc) {
				//Found it. Now kill it.
				if (prevsvd) {
					prevsvd->next=svd->next;
				} else {
					handle->vector_desc->shared_vec_info=svd->next;
				}
				free(svd);
				break;
			}
			prevsvd=svd;
			svd=svd->next;
		}
		//If nothing left, disable interrupt.
		if (handle->vector_desc->shared_vec_info==NULL) free_shared_vector=true;
		ESP_EARLY_LOGV(TAG, "esp_intr_free: Deleting shared int: %s. Shared int is %s", svd?"not found or last one":"deleted", free_shared_vector?"empty now.":"still in use");
	}

	if ((handle->vector_desc->flags&VECDESC_FL_NONSHARED) || free_shared_vector) {
		ESP_EARLY_LOGV(TAG, "esp_intr_free: Disabling int, killing handler");
#if CONFIG_APPTRACE_SV_ENABLE
		if (!free_shared_vector) {
			void *isr_arg = interrupt_controller_hal_get_int_handler_arg(handle->vector_desc->intno);
			if (isr_arg) {
				free(isr_arg);
			}
		}
#endif
		//Reset to normal handler:
		interrupt_controller_hal_set_int_handler(handle->vector_desc->intno, NULL, (void*)((int)handle->vector_desc->intno));
		//Theoretically, we could free the vector_desc... not sure if that's worth the few bytes of memory
		//we save.(We can also not use the same exit path for empty shared ints anymore if we delete
		//the desc.) For now, just mark it as free.
		handle->vector_desc->flags&=!(VECDESC_FL_NONSHARED|VECDESC_FL_RESERVED);
		handle->vector_desc->source = ETS_INTERNAL_UNUSED_INTR_SOURCE;
		//Also kill non_iram mask bit.
		non_iram_int_mask[handle->vector_desc->cpu]&=~(1<<(handle->vector_desc->intno));
	}
	portEXIT_CRITICAL(&spinlock);
	free(handle);
	return ESP_OK;
}

int esp_intr_get_intno(intr_handle_t handle)
{
	return handle->vector_desc->intno;
}

int esp_intr_get_cpu(intr_handle_t handle)
{
	return handle->vector_desc->cpu;
}



//Muxing an interrupt source to interrupt 6, 7, 11, 15, 16 or 29 cause the interrupt to effectively be disabled.
#define INT_MUX_DISABLED_INTNO 6

int IRAM_ATTR esp_intr_enable(intr_handle_t handle)
{
	if (!handle) return EINVAL;
	portENTER_CRITICAL_SAFE(&spinlock);
	int source;
	if (handle->shared_vector_desc) {
		handle->shared_vector_desc->disabled=0;
		source=handle->shared_vector_desc->source;
	} else {
		source=handle->vector_desc->source;
	}
	if (source >= 0) {
		//Disabled using int matrix; re-connect to enable
		intr_matrix_set(handle->vector_desc->cpu, source, handle->vector_desc->intno);
	} else {
		//Re-enable using cpu int ena reg
		if (handle->vector_desc->cpu!=cpu_hal_get_core_id()) return EINVAL; //Can only enable these ints on this cpu
		ESP_INTR_ENABLE(handle->vector_desc->intno);
	}
	portEXIT_CRITICAL_SAFE(&spinlock);
	return ESP_OK;
}

int IRAM_ATTR esp_intr_disable(intr_handle_t handle)
{
	if (!handle) return EINVAL;
	portENTER_CRITICAL_SAFE(&spinlock);
	int source;
	bool disabled = 1;
	if (handle->shared_vector_desc) {
		handle->shared_vector_desc->disabled=1;
		source=handle->shared_vector_desc->source;

		shared_vector_desc_t *svd=handle->vector_desc->shared_vec_info;
		assert( svd != NULL );
		while( svd ) {
			if ( svd->source == source && svd->disabled == 0 ) {
				disabled = 0;
				break;
			}
			svd = svd->next;
		}
	} else {
		source=handle->vector_desc->source;
	}

	if (source >= 0) {
		if ( disabled ) {
			//Disable using int matrix
			intr_matrix_set(handle->vector_desc->cpu, source, INT_MUX_DISABLED_INTNO);
		}
	} else {
		//Disable using per-cpu regs
		if (handle->vector_desc->cpu!=cpu_hal_get_core_id()) {
			portEXIT_CRITICAL_SAFE(&spinlock);
			return EINVAL; //Can only enable these ints on this cpu
		}
		ESP_INTR_DISABLE(handle->vector_desc->intno);
	}
	portEXIT_CRITICAL_SAFE(&spinlock);
	return ESP_OK;
}

void IRAM_ATTR esp_intr_noniram_disable(void)
{
	portENTER_CRITICAL_SAFE(&spinlock);
	uint32_t oldint;
	uint32_t cpu = cpu_hal_get_core_id();
	uint32_t non_iram_ints = non_iram_int_mask[cpu];
	if (non_iram_int_disabled_flag[cpu]) {
		abort();
	}
	non_iram_int_disabled_flag[cpu] = true;
	oldint = interrupt_controller_hal_read_interrupt_mask();
	interrupt_controller_hal_disable_interrupts(non_iram_ints);
	// Save disabled ints
	non_iram_int_disabled[cpu] = oldint & non_iram_ints;
	portEXIT_CRITICAL_SAFE(&spinlock);
}

void IRAM_ATTR esp_intr_noniram_enable(void)
{
	portENTER_CRITICAL_SAFE(&spinlock);
	uint32_t cpu = cpu_hal_get_core_id();
	int non_iram_ints = non_iram_int_disabled[cpu];
	if (!non_iram_int_disabled_flag[cpu]) {
		abort();
	}
	non_iram_int_disabled_flag[cpu] = false;
	interrupt_controller_hal_enable_interrupts(non_iram_ints);
	portEXIT_CRITICAL_SAFE(&spinlock);
}

//These functions are provided in ROM, but the ROM-based functions use non-multicore-capable
//virtualized interrupt levels. Thus, we disable them in the ld file and provide working
//equivalents here.


void IRAM_ATTR ets_isr_unmask(uint32_t mask) {
	interrupt_controller_hal_enable_interrupts(mask);
}

void IRAM_ATTR ets_isr_mask(uint32_t mask) {
	interrupt_controller_hal_disable_interrupts(mask);
}

void esp_intr_enable_source(int inum)
{
	interrupt_controller_hal_enable_interrupts(1 << inum);
}

void esp_intr_disable_source(int inum)
{
	interrupt_controller_hal_disable_interrupts(1 << inum);
}
