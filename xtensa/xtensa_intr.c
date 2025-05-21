#include "xtensa_intr.h"
#include "freertos/portmacro.h"

void IRAM_ATTR xt_unhandled_interrupt(void * arg)
{
	//esp_rom_printf("Unhandled interrupt %d on cpu %d!\n", (int)arg, xPortGetCoreID());
}

//Returns true if handler for interrupt is not the default unhandled interrupt handler
bool xt_int_has_handler(int intr, int cpu)
{
	return (_xt_interrupt_table[intr*portNUM_PROCESSORS+cpu].handler != xt_unhandled_interrupt);
}

xt_handler xt_set_interrupt_handler(int n, xt_handler f, void * arg)
{
	xt_handler_table_entry * entry;
	xt_handler               old;

	if( n < 0 || n >= XCHAL_NUM_INTERRUPTS )
		return 0;       /* invalid interrupt number */
	if( Xthal_intlevel[n] > XCHAL_EXCM_LEVEL )
		return 0;       /* priority level too high to safely handle in C */

	/* Convert exception number to _xt_exception_table name */
	n = n * portNUM_PROCESSORS + xPortGetCoreID();

	entry = _xt_interrupt_table + n;
	old   = entry->handler;

	if (f) {
		entry->handler = f;
		entry->arg     = arg;
	}
	else {
		entry->handler = &xt_unhandled_interrupt;
		entry->arg     = (void*)n;
	}

	return ((old == &xt_unhandled_interrupt) ? 0 : old);
}

void *xt_get_interrupt_handler_arg(int n)
{
	xt_handler_table_entry * entry;

	if( n < 0 || n >= XCHAL_NUM_INTERRUPTS )
		return 0;       /* invalid interrupt number */

	/* Convert exception number to _xt_exception_table name */
	n = n * portNUM_PROCESSORS + xPortGetCoreID();

	entry = _xt_interrupt_table + n;
	return entry->arg;
}
