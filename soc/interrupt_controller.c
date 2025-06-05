#include <stdint.h>


void intr_cntrl_ll_enable_interrupts(uint32_t mask)
{
	xt_ints_on(mask);
}

void intr_cntrl_ll_disable_interrupts(uint32_t mask)
{
	xt_ints_off(mask);
}

uint32_t intr_cntrl_ll_read_interrupt_mask(void)
{
	uint32_t int_mask;
	RSR(INTENABLE, int_mask);
	return int_mask;
}

bool intr_cntrl_ll_has_handler(uint8_t intr, uint8_t cpu)
{
	return xt_int_has_handler(intr, cpu);
}

void intr_cntrl_ll_set_int_handler(uint8_t intr, interrupt_handler_t handler, void *arg)
{
	xt_set_interrupt_handler(intr, (xt_handler)handler, arg);
}

void *intr_cntrl_ll_get_int_handler_arg(uint8_t intr)
{
	return xt_get_interrupt_handler_arg(intr);
}

void intr_cntrl_ll_edge_int_acknowledge (int intr)
{
	xthal_set_intclear(1 << intr);
}
