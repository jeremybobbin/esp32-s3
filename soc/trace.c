
#include <stdlib.h>


void trace_ll_set_mem_block(int cpu, int block)
{
	uint32_t block_bits = 0;

	if (cpu == 0) {
		block_bits = TRACEMEM_CORE0_MUX_BLK_BITS(block);
	} else {
		block_bits = TRACEMEM_CORE1_MUX_BLK_BITS(block);
	}
	DPORT_SET_PERI_REG_MASK(SENSITIVE_INTERNAL_SRAM_USAGE_2_REG, block_bits);
}
