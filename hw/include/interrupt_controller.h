#include <stdint.h>
#include "soc/soc_caps.h"
#include "soc/soc.h"
#include "xtensa/xtensa_api.h"
#include "xtensa/config/specreg.h"
#include "xt_instr_macros.h"

void intr_cntrl_ll_enable_interrupts(uint32_t mask);
void intr_cntrl_ll_disable_interrupts(uint32_t mask);
uint32_t intr_cntrl_ll_read_interrupt_mask(void);
bool intr_cntrl_ll_has_handler(uint8_t intr, uint8_t cpu);
void intr_cntrl_ll_set_int_handler(uint8_t intr, interrupt_handler_t handler, void *arg);
void *intr_cntrl_ll_get_int_handler_arg(uint8_t intr);
void intr_cntrl_ll_edge_int_acknowledge (int intr);
