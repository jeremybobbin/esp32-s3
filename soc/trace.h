#include <stdlib.h>

#define DR_REG_SENSITIVE_BASE                   0x600C1000
#define TRACEMEM_CORE0_MUX_BLK_BITS(n)         ((1<<(((n)-2UL)/4UL)) | (TRACEMEM_MUX_BLK_ALLOC(n) << 14))
#define TRACEMEM_MUX_BLK_ALLOC(n)             (((n)-2UL)%4UL)
#define TRACEMEM_CORE0_MUX_BLK_BITS(n)         ((1<<(((n)-2UL)/4UL)) | (TRACEMEM_MUX_BLK_ALLOC(n) << 14))
#define TRACEMEM_CORE1_MUX_BLK_BITS(_n_)         ((1<<(7UL+(((_n_)-2UL)/4UL))) | (TRACEMEM_MUX_BLK_ALLOC(_n_) << 16))

#define DPORT_REG_GET_BIT(_r, _b)  (DPORT_REG_READ(_r) & (_b))
#define DPORT_CLEAR_PERI_REG_MASK(reg, mask) DPORT_WRITE_PERI_REG((reg), (DPORT_READ_PERI_REG(reg)&(~(mask))))
#define DPORT_WRITE_PERI_REG(addr, val) (*((volatile uint32_t *)(addr))) = (uint32_t)(val)
#define DPORT_READ_PERI_REG(addr)       (*((volatile uint32_t *)(addr)))
#define DPORT_SET_PERI_REG_MASK(reg, mask)   DPORT_WRITE_PERI_REG((reg), (DPORT_READ_PERI_REG(reg)|(mask)))
#define DPORT_REG_WRITE(r, v)   (*(volatile uint32_t *)(r)) = (v)
#define DPORT_REG_READ(r)    (*(volatile uint32_t *)(r))
#define SENSITIVE_INTERNAL_SRAM_USAGE_2_REG          (DR_REG_SENSITIVE_BASE + 0x18)


void trace_ll_set_mem_block(int cpu, int block);
