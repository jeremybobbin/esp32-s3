#ifndef XTENSA_INTR_H
#define XTENSA_INTR_H 1

#include "xtensa/hal.h"
#include "freertos/FreeRTOSConfig.h"
#include "heap/soc_memory_layout.h"

typedef struct xt_handler_table_entry {
	void * handler;
	void * arg;
} xt_handler_table_entry;

extern xt_handler_table_entry _xt_interrupt_table[XCHAL_NUM_INTERRUPTS*portNUM_PROCESSORS];
typedef void (*xt_handler)(void *);

void IRAM_ATTR xt_unhandled_interrupt(void * arg);
bool xt_int_has_handler(int intr, int cpu);
xt_handler xt_set_interrupt_handler(int n, xt_handler f, void * arg);
void *xt_get_interrupt_handler_arg(int n);

#endif
