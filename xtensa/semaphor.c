#include "xtensa/xtruntime.h"
void compare_and_set_extram(volatile uint32_t *addr, uint32_t compare, uint32_t *set)
{
	uint32_t intlevel, old_value;
	__asm__ __volatile__ ("rsil %0, " XTSTR(XCHAL_EXCM_LEVEL) "\n"
						  : "=r"(intlevel));

	spinlock_acquire(&global_extram_lock, SPINLOCK_WAIT_FOREVER);

	old_value = *addr;
	if (old_value == compare) {
		*addr = *set;
	}

	spinlock_release(&global_extram_lock);

	__asm__ __volatile__ ("memw \n"
						"wsr %0, ps\n"
						:: "r"(intlevel));

	*set = old_value;
}

void compare_and_set_native(volatile uint32_t *addr, uint32_t compare, uint32_t *set)
{
	__asm__ __volatile__ (
		"WSR 	    %2,SCOMPARE1 \n"
		"S32C1I     %0, %1, 0	 \n"
		:"=r"(*set)
		:"r"(addr), "r"(compare), "0"(*set)
	);

	old_value = *addr;
	if (old_value == compare) {
		*addr = *set;
	}

	__asm__ __volatile__ ("memw \n"
						  "wsr %0, ps\n"
						  :: "r"(intlevel));
	*set = old_value;
}
