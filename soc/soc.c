

#define SOC_CPU_CORES_NUM               2

#include "soc/gpio.h"
#include "soc/rtc_cntl.h"

void soc_ll_stall_core(int core)
{
	const int rtc_cntl_c1_m[SOC_CPU_CORES_NUM] = {RTC_CNTL_SW_STALL_PROCPU_C1_M, RTC_CNTL_SW_STALL_APPCPU_C1_M};
	const int rtc_cntl_c1_s[SOC_CPU_CORES_NUM] = {RTC_CNTL_SW_STALL_PROCPU_C1_S, RTC_CNTL_SW_STALL_APPCPU_C1_S};
	const int rtc_cntl_c0_m[SOC_CPU_CORES_NUM] = {RTC_CNTL_SW_STALL_PROCPU_C0_M, RTC_CNTL_SW_STALL_APPCPU_C0_M};
	const int rtc_cntl_c0_s[SOC_CPU_CORES_NUM] = {RTC_CNTL_SW_STALL_PROCPU_C0_S, RTC_CNTL_SW_STALL_APPCPU_C0_S};

	CLEAR_PERI_REG_MASK(RTC_CNTL_SW_CPU_STALL_REG, rtc_cntl_c1_m[core]);
	SET_PERI_REG_MASK(RTC_CNTL_SW_CPU_STALL_REG, 0x21 << rtc_cntl_c1_s[core]);
	CLEAR_PERI_REG_MASK(RTC_CNTL_OPTIONS0_REG, rtc_cntl_c0_m[core]);
	SET_PERI_REG_MASK(RTC_CNTL_OPTIONS0_REG, 2 << rtc_cntl_c0_s[core]);
}

void soc_ll_unstall_core(int core)
{
	const int rtc_cntl_c1_m[SOC_CPU_CORES_NUM] = {RTC_CNTL_SW_STALL_PROCPU_C1_M, RTC_CNTL_SW_STALL_APPCPU_C1_M};
	const int rtc_cntl_c0_m[SOC_CPU_CORES_NUM] = {RTC_CNTL_SW_STALL_PROCPU_C0_M, RTC_CNTL_SW_STALL_APPCPU_C0_M};
	CLEAR_PERI_REG_MASK(RTC_CNTL_SW_CPU_STALL_REG, rtc_cntl_c1_m[core]);
	CLEAR_PERI_REG_MASK(RTC_CNTL_OPTIONS0_REG, rtc_cntl_c0_m[core]);
}

void soc_ll_reset_core(int core)
{
	SET_PERI_REG_MASK(RTC_CNTL_OPTIONS0_REG,
			core == 0 ? RTC_CNTL_SW_PROCPU_RST_M : RTC_CNTL_SW_APPCPU_RST_M);
}

