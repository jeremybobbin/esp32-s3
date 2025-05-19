#include <stdint.h>


uint32_t mpu_ll_id_to_addr(unsigned id);
void mpu_ll_set_region_rw(uint32_t addr);
void mpu_ll_set_region_rwx(uint32_t addr);
void mpu_ll_set_region_x(uint32_t addr);
void mpu_ll_set_region_illegal(uint32_t addr);
