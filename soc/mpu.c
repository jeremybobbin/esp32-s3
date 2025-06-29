
#include <stdint.h>
#include "xtensa/core-macros.h"

#define SOC_MPU_MIN_REGION_SIZE                   0x20000000U


uint32_t mpu_ll_id_to_addr(unsigned id)
{
	// vpn - id
	// 0x00000000 = 0
	// 0x20000000 = 1
	// 0x40000000 = 2
	// 0x60000000 = 3
	// 0x80000000 = 4
	// 0xa0000000 = 5
	// 0xc0000000 = 6
	// 0xe0000000 = 7
	return id * SOC_MPU_MIN_REGION_SIZE;
}

void mpu_ll_set_region_rw(uint32_t addr)
{
	WDTLB(0x0, addr); // cached, no allocate
}

void mpu_ll_set_region_rwx(uint32_t addr)
{
	WDTLB(0x2, addr); // bypass cache
}

void mpu_ll_set_region_x(uint32_t addr)
{
	WITLB(0x3, addr); // cached
}

void mpu_ll_set_region_illegal(uint32_t addr)
{
	WITLB(0xF, addr);
	WDTLB(0xF, addr);
}

