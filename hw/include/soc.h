#include "soc/soc.h"
#include "soc/rtc_cntl_reg.h"
#include "soc/soc_caps.h"
#include "soc/rtc.h"

void soc_ll_stall_core(int core);
void soc_ll_unstall_core(int core);
void soc_ll_reset_core(int core);
