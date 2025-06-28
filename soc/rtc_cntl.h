#include <stdint.h>

#define RTC_CNTL_LL_RETENTION_TARGET_CPU         (1<<0)
#define RTC_CNTL_LL_RETENTION_TARGET_TAGMEM      (1<<1)

/* The value that needs to be written to RTC_CNTL_SWD_WPROTECT_REG to write-enable the wdt registers */
#define RTC_CNTL_SWD_WKEY_VALUE 0x8F1D312A

#define RTC_CNTL_TIME0_REG		RTC_CNTL_TIME_LOW0_REG
#define RTC_CNTL_TIME1_REG		RTC_CNTL_TIME_HIGH0_REG

#define RTC_CNTL_OPTIONS0_REG          (0x60008000 + 0x0)

/* RTC_CNTL_SW_SYS_RST : WO ;bitpos:[31] ;default: 1'd0 ; */
/*description: SW system reset.*/
#define RTC_CNTL_SW_SYS_RST    (1<<31)
#define RTC_CNTL_SW_SYS_RST_M  (1<<31)
#define RTC_CNTL_SW_SYS_RST_V  0x1
#define RTC_CNTL_SW_SYS_RST_S  31
/* RTC_CNTL_DG_WRAP_FORCE_NORST : R/W ;bitpos:[30] ;default: 1'd0 ; */
/*description: digital core force no reset in deep sleep.*/
#define RTC_CNTL_DG_WRAP_FORCE_NORST    (1<<30)
#define RTC_CNTL_DG_WRAP_FORCE_NORST_M  (1<<30)
#define RTC_CNTL_DG_WRAP_FORCE_NORST_V  0x1
#define RTC_CNTL_DG_WRAP_FORCE_NORST_S  30
/* RTC_CNTL_DG_WRAP_FORCE_RST : R/W ;bitpos:[29] ;default: 1'd0 ; */
/*description: digital wrap force reset in deep sleep.*/
#define RTC_CNTL_DG_WRAP_FORCE_RST    (1<<29)
#define RTC_CNTL_DG_WRAP_FORCE_RST_M  (1<<29)
#define RTC_CNTL_DG_WRAP_FORCE_RST_V  0x1
#define RTC_CNTL_DG_WRAP_FORCE_RST_S  29
/* RTC_CNTL_ANALOG_FORCE_NOISO : R/W ;bitpos:[28] ;default: 1'd1 ; */
/*description: .*/
#define RTC_CNTL_ANALOG_FORCE_NOISO    (1<<28)
#define RTC_CNTL_ANALOG_FORCE_NOISO_M  (1<<28)
#define RTC_CNTL_ANALOG_FORCE_NOISO_V  0x1
#define RTC_CNTL_ANALOG_FORCE_NOISO_S  28
/* RTC_CNTL_PLL_FORCE_NOISO : R/W ;bitpos:[27] ;default: 1'd1 ; */
/*description: .*/
#define RTC_CNTL_PLL_FORCE_NOISO    (1<<27)
#define RTC_CNTL_PLL_FORCE_NOISO_M  (1<<27)
#define RTC_CNTL_PLL_FORCE_NOISO_V  0x1
#define RTC_CNTL_PLL_FORCE_NOISO_S  27
/* RTC_CNTL_XTL_FORCE_NOISO : R/W ;bitpos:[26] ;default: 1'd1 ; */
/*description: .*/
#define RTC_CNTL_XTL_FORCE_NOISO    (1<<26)
#define RTC_CNTL_XTL_FORCE_NOISO_M  (1<<26)
#define RTC_CNTL_XTL_FORCE_NOISO_V  0x1
#define RTC_CNTL_XTL_FORCE_NOISO_S  26
/* RTC_CNTL_ANALOG_FORCE_ISO : R/W ;bitpos:[25] ;default: 1'd0 ; */
/*description: .*/
#define RTC_CNTL_ANALOG_FORCE_ISO    (1<<25)
#define RTC_CNTL_ANALOG_FORCE_ISO_M  (1<<25)
#define RTC_CNTL_ANALOG_FORCE_ISO_V  0x1
#define RTC_CNTL_ANALOG_FORCE_ISO_S  25
/* RTC_CNTL_PLL_FORCE_ISO : R/W ;bitpos:[24] ;default: 1'd0 ; */
/*description: .*/
#define RTC_CNTL_PLL_FORCE_ISO    (1<<24)
#define RTC_CNTL_PLL_FORCE_ISO_M  (1<<24)
#define RTC_CNTL_PLL_FORCE_ISO_V  0x1
#define RTC_CNTL_PLL_FORCE_ISO_S  24
/* RTC_CNTL_XTL_FORCE_ISO : R/W ;bitpos:[23] ;default: 1'd0 ; */
/*description: .*/
#define RTC_CNTL_XTL_FORCE_ISO    (1<<23)
#define RTC_CNTL_XTL_FORCE_ISO_M  (1<<23)
#define RTC_CNTL_XTL_FORCE_ISO_V  0x1
#define RTC_CNTL_XTL_FORCE_ISO_S  23
/* RTC_CNTL_XTL_EN_WAIT : R/W ;bitpos:[17:14] ;default: 4'd2 ; */
/*description: wait bias_sleep and current source wakeup.*/
#define RTC_CNTL_XTL_EN_WAIT    0x0000000F
#define RTC_CNTL_XTL_EN_WAIT_M  ((RTC_CNTL_XTL_EN_WAIT_V)<<(RTC_CNTL_XTL_EN_WAIT_S))
#define RTC_CNTL_XTL_EN_WAIT_V  0xF
#define RTC_CNTL_XTL_EN_WAIT_S  14
/* RTC_CNTL_XTL_FORCE_PU : R/W ;bitpos:[13] ;default: 1'd1 ; */
/*description: crystall force power up.*/
#define RTC_CNTL_XTL_FORCE_PU    (1<<13)
#define RTC_CNTL_XTL_FORCE_PU_M  (1<<13)
#define RTC_CNTL_XTL_FORCE_PU_V  0x1
#define RTC_CNTL_XTL_FORCE_PU_S  13
/* RTC_CNTL_XTL_FORCE_PD : R/W ;bitpos:[12] ;default: 1'b0 ; */
/*description: crystall force power down.*/
#define RTC_CNTL_XTL_FORCE_PD    (1<<12)
#define RTC_CNTL_XTL_FORCE_PD_M  (1<<12)
#define RTC_CNTL_XTL_FORCE_PD_V  0x1
#define RTC_CNTL_XTL_FORCE_PD_S  12
/* RTC_CNTL_BBPLL_FORCE_PU : R/W ;bitpos:[11] ;default: 1'd0 ; */
/*description: BB_PLL force power up.*/
#define RTC_CNTL_BBPLL_FORCE_PU    (1<<11)
#define RTC_CNTL_BBPLL_FORCE_PU_M  (1<<11)
#define RTC_CNTL_BBPLL_FORCE_PU_V  0x1
#define RTC_CNTL_BBPLL_FORCE_PU_S  11
/* RTC_CNTL_BBPLL_FORCE_PD : R/W ;bitpos:[10] ;default: 1'b0 ; */
/*description: BB_PLL force power down.*/
#define RTC_CNTL_BBPLL_FORCE_PD    (1<<10)
#define RTC_CNTL_BBPLL_FORCE_PD_M  (1<<10)
#define RTC_CNTL_BBPLL_FORCE_PD_V  0x1
#define RTC_CNTL_BBPLL_FORCE_PD_S  10
/* RTC_CNTL_BBPLL_I2C_FORCE_PU : R/W ;bitpos:[9] ;default: 1'd0 ; */
/*description: BB_PLL_I2C force power up.*/
#define RTC_CNTL_BBPLL_I2C_FORCE_PU    (1<<9)
#define RTC_CNTL_BBPLL_I2C_FORCE_PU_M  (1<<9)
#define RTC_CNTL_BBPLL_I2C_FORCE_PU_V  0x1
#define RTC_CNTL_BBPLL_I2C_FORCE_PU_S  9
/* RTC_CNTL_BBPLL_I2C_FORCE_PD : R/W ;bitpos:[8] ;default: 1'b0 ; */
/*description: BB_PLL _I2C force power down.*/
#define RTC_CNTL_BBPLL_I2C_FORCE_PD    (1<<8)
#define RTC_CNTL_BBPLL_I2C_FORCE_PD_M  (1<<8)
#define RTC_CNTL_BBPLL_I2C_FORCE_PD_V  0x1
#define RTC_CNTL_BBPLL_I2C_FORCE_PD_S  8
/* RTC_CNTL_BB_I2C_FORCE_PU : R/W ;bitpos:[7] ;default: 1'd0 ; */
/*description: BB_I2C force power up.*/
#define RTC_CNTL_BB_I2C_FORCE_PU    (1<<7)
#define RTC_CNTL_BB_I2C_FORCE_PU_M  (1<<7)
#define RTC_CNTL_BB_I2C_FORCE_PU_V  0x1
#define RTC_CNTL_BB_I2C_FORCE_PU_S  7
/* RTC_CNTL_BB_I2C_FORCE_PD : R/W ;bitpos:[6] ;default: 1'b0 ; */
/*description: BB_I2C force power down.*/
#define RTC_CNTL_BB_I2C_FORCE_PD    (1<<6)
#define RTC_CNTL_BB_I2C_FORCE_PD_M  (1<<6)
#define RTC_CNTL_BB_I2C_FORCE_PD_V  0x1
#define RTC_CNTL_BB_I2C_FORCE_PD_S  6
/* RTC_CNTL_SW_PROCPU_RST : WO ;bitpos:[5] ;default: 1'b0 ; */
/*description: PRO CPU SW reset.*/
#define RTC_CNTL_SW_PROCPU_RST    (1<<5)
#define RTC_CNTL_SW_PROCPU_RST_M  (1<<5)
#define RTC_CNTL_SW_PROCPU_RST_V  0x1
#define RTC_CNTL_SW_PROCPU_RST_S  5
/* RTC_CNTL_SW_APPCPU_RST : WO ;bitpos:[4] ;default: 1'b0 ; */
/*description: APP CPU SW reset.*/
#define RTC_CNTL_SW_APPCPU_RST    (1<<4)
#define RTC_CNTL_SW_APPCPU_RST_M  (1<<4)
#define RTC_CNTL_SW_APPCPU_RST_V  0x1
#define RTC_CNTL_SW_APPCPU_RST_S  4
/* RTC_CNTL_SW_STALL_PROCPU_C0 : R/W ;bitpos:[3:2] ;default: 2'b0 ; */
/*description: {reg_sw_stall_procpu_c1[5:0],  reg_sw_stall_procpu_c0[1:0]} == 0x86 will stall P
RO CPU.*/
#define RTC_CNTL_SW_STALL_PROCPU_C0    0x00000003
#define RTC_CNTL_SW_STALL_PROCPU_C0_M  ((RTC_CNTL_SW_STALL_PROCPU_C0_V)<<(RTC_CNTL_SW_STALL_PROCPU_C0_S))
#define RTC_CNTL_SW_STALL_PROCPU_C0_V  0x3
#define RTC_CNTL_SW_STALL_PROCPU_C0_S  2
/* RTC_CNTL_SW_STALL_APPCPU_C0 : R/W ;bitpos:[1:0] ;default: 2'b0 ; */
/*description: {reg_sw_stall_appcpu_c1[5:0],  reg_sw_stall_appcpu_c0[1:0]} == 0x86 will stall A
PP CPU.*/
#define RTC_CNTL_SW_STALL_APPCPU_C0    0x00000003
#define RTC_CNTL_SW_STALL_APPCPU_C0_M  ((RTC_CNTL_SW_STALL_APPCPU_C0_V)<<(RTC_CNTL_SW_STALL_APPCPU_C0_S))
#define RTC_CNTL_SW_STALL_APPCPU_C0_V  0x3
#define RTC_CNTL_SW_STALL_APPCPU_C0_S  0

#define RTC_CNTL_SLP_TIMER0_REG          (0x60008000 + 0x4)
/* RTC_CNTL_SLP_VAL_LO : R/W ;bitpos:[31:0] ;default: 32'h0 ; */
/*description: .*/
#define RTC_CNTL_SLP_VAL_LO    0xFFFFFFFF
#define RTC_CNTL_SLP_VAL_LO_M  ((RTC_CNTL_SLP_VAL_LO_V)<<(RTC_CNTL_SLP_VAL_LO_S))
#define RTC_CNTL_SLP_VAL_LO_V  0xFFFFFFFF
#define RTC_CNTL_SLP_VAL_LO_S  0

#define RTC_CNTL_SLP_TIMER1_REG          (0x60008000 + 0x8)
/* RTC_CNTL_MAIN_TIMER_ALARM_EN : WO ;bitpos:[16] ;default: 1'h0 ; */
/*description: timer alarm enable bit.*/
#define RTC_CNTL_MAIN_TIMER_ALARM_EN    (1<<16)
#define RTC_CNTL_MAIN_TIMER_ALARM_EN_M  (1<<16)
#define RTC_CNTL_MAIN_TIMER_ALARM_EN_V  0x1
#define RTC_CNTL_MAIN_TIMER_ALARM_EN_S  16
/* RTC_CNTL_SLP_VAL_HI : R/W ;bitpos:[15:0] ;default: 16'h0 ; */
/*description: RTC sleep timer high 16 bits.*/
#define RTC_CNTL_SLP_VAL_HI    0x0000FFFF
#define RTC_CNTL_SLP_VAL_HI_M  ((RTC_CNTL_SLP_VAL_HI_V)<<(RTC_CNTL_SLP_VAL_HI_S))
#define RTC_CNTL_SLP_VAL_HI_V  0xFFFF
#define RTC_CNTL_SLP_VAL_HI_S  0

#define RTC_CNTL_TIME_UPDATE_REG          (0x60008000 + 0xC)
/* RTC_CNTL_TIME_UPDATE : WO ;bitpos:[31] ;default: 1'h0 ; */
/*description: Set 1: to update register with RTC timer.*/
#define RTC_CNTL_TIME_UPDATE    (1<<31)
#define RTC_CNTL_TIME_UPDATE_M  (1<<31)
#define RTC_CNTL_TIME_UPDATE_V  0x1
#define RTC_CNTL_TIME_UPDATE_S  31
/* RTC_CNTL_TIMER_SYS_RST : R/W ;bitpos:[29] ;default: 1'b0 ; */
/*description: enable to record system reset time.*/
#define RTC_CNTL_TIMER_SYS_RST    (1<<29)
#define RTC_CNTL_TIMER_SYS_RST_M  (1<<29)
#define RTC_CNTL_TIMER_SYS_RST_V  0x1
#define RTC_CNTL_TIMER_SYS_RST_S  29
/* RTC_CNTL_TIMER_XTL_OFF : R/W ;bitpos:[28] ;default: 1'b0 ; */
/*description: Enable to record 40M XTAL OFF time.*/
#define RTC_CNTL_TIMER_XTL_OFF    (1<<28)
#define RTC_CNTL_TIMER_XTL_OFF_M  (1<<28)
#define RTC_CNTL_TIMER_XTL_OFF_V  0x1
#define RTC_CNTL_TIMER_XTL_OFF_S  28
/* RTC_CNTL_TIMER_SYS_STALL : R/W ;bitpos:[27] ;default: 1'b0 ; */
/*description: Enable to record system stall time.*/
#define RTC_CNTL_TIMER_SYS_STALL    (1<<27)
#define RTC_CNTL_TIMER_SYS_STALL_M  (1<<27)
#define RTC_CNTL_TIMER_SYS_STALL_V  0x1
#define RTC_CNTL_TIMER_SYS_STALL_S  27

#define RTC_CNTL_TIME_LOW0_REG          (0x60008000 + 0x10)
/* RTC_CNTL_TIMER_VALUE0_LOW : RO ;bitpos:[31:0] ;default: 32'h0 ; */
/*description: RTC timer low 32 bits.*/
#define RTC_CNTL_TIMER_VALUE0_LOW    0xFFFFFFFF
#define RTC_CNTL_TIMER_VALUE0_LOW_M  ((RTC_CNTL_TIMER_VALUE0_LOW_V)<<(RTC_CNTL_TIMER_VALUE0_LOW_S))
#define RTC_CNTL_TIMER_VALUE0_LOW_V  0xFFFFFFFF
#define RTC_CNTL_TIMER_VALUE0_LOW_S  0

#define RTC_CNTL_TIME_HIGH0_REG          (0x60008000 + 0x14)
/* RTC_CNTL_TIMER_VALUE0_HIGH : RO ;bitpos:[15:0] ;default: 16'h0 ; */
/*description: RTC timer high 16 bits.*/
#define RTC_CNTL_TIMER_VALUE0_HIGH    0x0000FFFF
#define RTC_CNTL_TIMER_VALUE0_HIGH_M  ((RTC_CNTL_TIMER_VALUE0_HIGH_V)<<(RTC_CNTL_TIMER_VALUE0_HIGH_S))
#define RTC_CNTL_TIMER_VALUE0_HIGH_V  0xFFFF
#define RTC_CNTL_TIMER_VALUE0_HIGH_S  0

#define RTC_CNTL_STATE0_REG          (0x60008000 + 0x18)
/* RTC_CNTL_SLEEP_EN : R/W ;bitpos:[31] ;default: 1'd0 ; */
/*description: sleep enable bit.*/
#define RTC_CNTL_SLEEP_EN    (1<<31)
#define RTC_CNTL_SLEEP_EN_M  (1<<31)
#define RTC_CNTL_SLEEP_EN_V  0x1
#define RTC_CNTL_SLEEP_EN_S  31
/* RTC_CNTL_SLP_REJECT : R/W ;bitpos:[30] ;default: 1'd0 ; */
/*description: leep reject bit.*/
#define RTC_CNTL_SLP_REJECT    (1<<30)
#define RTC_CNTL_SLP_REJECT_M  (1<<30)
#define RTC_CNTL_SLP_REJECT_V  0x1
#define RTC_CNTL_SLP_REJECT_S  30
/* RTC_CNTL_SLP_WAKEUP : R/W ;bitpos:[29] ;default: 1'd0 ; */
/*description: leep wakeup bit.*/
#define RTC_CNTL_SLP_WAKEUP    (1<<29)
#define RTC_CNTL_SLP_WAKEUP_M  (1<<29)
#define RTC_CNTL_SLP_WAKEUP_V  0x1
#define RTC_CNTL_SLP_WAKEUP_S  29
/* RTC_CNTL_SDIO_ACTIVE_IND : RO ;bitpos:[28] ;default: 1'd0 ; */
/*description: SDIO active indication.*/
#define RTC_CNTL_SDIO_ACTIVE_IND    (1<<28)
#define RTC_CNTL_SDIO_ACTIVE_IND_M  (1<<28)
#define RTC_CNTL_SDIO_ACTIVE_IND_V  0x1
#define RTC_CNTL_SDIO_ACTIVE_IND_S  28
/* RTC_CNTL_APB2RTC_BRIDGE_SEL : R/W ;bitpos:[22] ;default: 1'd0 ; */
/*description: 1: APB to RTC using bridge.*/
#define RTC_CNTL_APB2RTC_BRIDGE_SEL    (1<<22)
#define RTC_CNTL_APB2RTC_BRIDGE_SEL_M  (1<<22)
#define RTC_CNTL_APB2RTC_BRIDGE_SEL_V  0x1
#define RTC_CNTL_APB2RTC_BRIDGE_SEL_S  22
/* RTC_CNTL_SLP_REJECT_CAUSE_CLR : WO ;bitpos:[1] ;default: 1'b0 ; */
/*description: clear rtc sleep reject cause.*/
#define RTC_CNTL_SLP_REJECT_CAUSE_CLR    (1<<1)
#define RTC_CNTL_SLP_REJECT_CAUSE_CLR_M  (1<<1)
#define RTC_CNTL_SLP_REJECT_CAUSE_CLR_V  0x1
#define RTC_CNTL_SLP_REJECT_CAUSE_CLR_S  1
/* RTC_CNTL_SW_CPU_INT : WO ;bitpos:[0] ;default: 1'b0 ; */
/*description: rtc software interrupt to main cpu.*/
#define RTC_CNTL_SW_CPU_INT    (1<<0)
#define RTC_CNTL_SW_CPU_INT_M  (1<<0)
#define RTC_CNTL_SW_CPU_INT_V  0x1
#define RTC_CNTL_SW_CPU_INT_S  0

#define RTC_CNTL_TIMER1_REG          (0x60008000 + 0x1C)
/* RTC_CNTL_PLL_BUF_WAIT : R/W ;bitpos:[31:24] ;default: 8'd40 ; */
/*description: PLL wait cycles in slow_clk_rtc.*/
#define RTC_CNTL_PLL_BUF_WAIT    0x000000FF
#define RTC_CNTL_PLL_BUF_WAIT_M  ((RTC_CNTL_PLL_BUF_WAIT_V)<<(RTC_CNTL_PLL_BUF_WAIT_S))
#define RTC_CNTL_PLL_BUF_WAIT_V  0xFF
#define RTC_CNTL_PLL_BUF_WAIT_S  24
/* RTC_CNTL_XTL_BUF_WAIT : R/W ;bitpos:[23:14] ;default: 10'd80 ; */
/*description: XTAL wait cycles in slow_clk_rtc.*/
#define RTC_CNTL_XTL_BUF_WAIT    0x000003FF
#define RTC_CNTL_XTL_BUF_WAIT_M  ((RTC_CNTL_XTL_BUF_WAIT_V)<<(RTC_CNTL_XTL_BUF_WAIT_S))
#define RTC_CNTL_XTL_BUF_WAIT_V  0x3FF
#define RTC_CNTL_XTL_BUF_WAIT_S  14
/* RTC_CNTL_CK8M_WAIT : R/W ;bitpos:[13:6] ;default: 8'h10 ; */
/*description: CK8M wait cycles in slow_clk_rtc.*/
#define RTC_CNTL_CK8M_WAIT    0x000000FF
#define RTC_CNTL_CK8M_WAIT_M  ((RTC_CNTL_CK8M_WAIT_V)<<(RTC_CNTL_CK8M_WAIT_S))
#define RTC_CNTL_CK8M_WAIT_V  0xFF
#define RTC_CNTL_CK8M_WAIT_S  6
/* RTC_CNTL_CPU_STALL_WAIT : R/W ;bitpos:[5:1] ;default: 5'd1 ; */
/*description: CPU stall wait cycles in fast_clk_rtc.*/
#define RTC_CNTL_CPU_STALL_WAIT    0x0000001F
#define RTC_CNTL_CPU_STALL_WAIT_M  ((RTC_CNTL_CPU_STALL_WAIT_V)<<(RTC_CNTL_CPU_STALL_WAIT_S))
#define RTC_CNTL_CPU_STALL_WAIT_V  0x1F
#define RTC_CNTL_CPU_STALL_WAIT_S  1
/* RTC_CNTL_CPU_STALL_EN : R/W ;bitpos:[0] ;default: 1'd1 ; */
/*description: CPU stall enable bit.*/
#define RTC_CNTL_CPU_STALL_EN    (1<<0)
#define RTC_CNTL_CPU_STALL_EN_M  (1<<0)
#define RTC_CNTL_CPU_STALL_EN_V  0x1
#define RTC_CNTL_CPU_STALL_EN_S  0

#define RTC_CNTL_TIMER2_REG          (0x60008000 + 0x20)
/* RTC_CNTL_MIN_TIME_CK8M_OFF : R/W ;bitpos:[31:24] ;default: 8'h1 ; */
/*description: minimal cycles in slow_clk_rtc for CK8M in power down state.*/
#define RTC_CNTL_MIN_TIME_CK8M_OFF    0x000000FF
#define RTC_CNTL_MIN_TIME_CK8M_OFF_M  ((RTC_CNTL_MIN_TIME_CK8M_OFF_V)<<(RTC_CNTL_MIN_TIME_CK8M_OFF_S))
#define RTC_CNTL_MIN_TIME_CK8M_OFF_V  0xFF
#define RTC_CNTL_MIN_TIME_CK8M_OFF_S  24
/* RTC_CNTL_ULPCP_TOUCH_START_WAIT : R/W ;bitpos:[23:15] ;default: 9'h10 ; */
/*description: wait cycles in slow_clk_rtc before ULP-coprocessor / touch controller start to w
ork.*/
#define RTC_CNTL_ULPCP_TOUCH_START_WAIT    0x000001FF
#define RTC_CNTL_ULPCP_TOUCH_START_WAIT_M  ((RTC_CNTL_ULPCP_TOUCH_START_WAIT_V)<<(RTC_CNTL_ULPCP_TOUCH_START_WAIT_S))
#define RTC_CNTL_ULPCP_TOUCH_START_WAIT_V  0x1FF
#define RTC_CNTL_ULPCP_TOUCH_START_WAIT_S  15

#define RTC_CNTL_TIMER3_REG          (0x60008000 + 0x24)
/* RTC_CNTL_BT_POWERUP_TIMER : R/W ;bitpos:[31:25] ;default: 7'd10 ; */
/*description: .*/
#define RTC_CNTL_BT_POWERUP_TIMER    0x0000007F
#define RTC_CNTL_BT_POWERUP_TIMER_M  ((RTC_CNTL_BT_POWERUP_TIMER_V)<<(RTC_CNTL_BT_POWERUP_TIMER_S))
#define RTC_CNTL_BT_POWERUP_TIMER_V  0x7F
#define RTC_CNTL_BT_POWERUP_TIMER_S  25
/* RTC_CNTL_BT_WAIT_TIMER : R/W ;bitpos:[24:16] ;default: 9'h16 ; */
/*description: .*/
#define RTC_CNTL_BT_WAIT_TIMER    0x000001FF
#define RTC_CNTL_BT_WAIT_TIMER_M  ((RTC_CNTL_BT_WAIT_TIMER_V)<<(RTC_CNTL_BT_WAIT_TIMER_S))
#define RTC_CNTL_BT_WAIT_TIMER_V  0x1FF
#define RTC_CNTL_BT_WAIT_TIMER_S  16
/* RTC_CNTL_WIFI_POWERUP_TIMER : R/W ;bitpos:[15:9] ;default: 7'h5 ; */
/*description: .*/
#define RTC_CNTL_WIFI_POWERUP_TIMER    0x0000007F
#define RTC_CNTL_WIFI_POWERUP_TIMER_M  ((RTC_CNTL_WIFI_POWERUP_TIMER_V)<<(RTC_CNTL_WIFI_POWERUP_TIMER_S))
#define RTC_CNTL_WIFI_POWERUP_TIMER_V  0x7F
#define RTC_CNTL_WIFI_POWERUP_TIMER_S  9
/* RTC_CNTL_WIFI_WAIT_TIMER : R/W ;bitpos:[8:0] ;default: 9'h8 ; */
/*description: .*/
#define RTC_CNTL_WIFI_WAIT_TIMER    0x000001FF
#define RTC_CNTL_WIFI_WAIT_TIMER_M  ((RTC_CNTL_WIFI_WAIT_TIMER_V)<<(RTC_CNTL_WIFI_WAIT_TIMER_S))
#define RTC_CNTL_WIFI_WAIT_TIMER_V  0x1FF
#define RTC_CNTL_WIFI_WAIT_TIMER_S  0

#define RTC_CNTL_TIMER4_REG          (0x60008000 + 0x28)
/* RTC_CNTL_DG_WRAP_POWERUP_TIMER : R/W ;bitpos:[31:25] ;default: 7'h8 ; */
/*description: .*/
#define RTC_CNTL_DG_WRAP_POWERUP_TIMER    0x0000007F
#define RTC_CNTL_DG_WRAP_POWERUP_TIMER_M  ((RTC_CNTL_DG_WRAP_POWERUP_TIMER_V)<<(RTC_CNTL_DG_WRAP_POWERUP_TIMER_S))
#define RTC_CNTL_DG_WRAP_POWERUP_TIMER_V  0x7F
#define RTC_CNTL_DG_WRAP_POWERUP_TIMER_S  25
/* RTC_CNTL_DG_WRAP_WAIT_TIMER : R/W ;bitpos:[24:16] ;default: 9'h20 ; */
/*description: .*/
#define RTC_CNTL_DG_WRAP_WAIT_TIMER    0x000001FF
#define RTC_CNTL_DG_WRAP_WAIT_TIMER_M  ((RTC_CNTL_DG_WRAP_WAIT_TIMER_V)<<(RTC_CNTL_DG_WRAP_WAIT_TIMER_S))
#define RTC_CNTL_DG_WRAP_WAIT_TIMER_V  0x1FF
#define RTC_CNTL_DG_WRAP_WAIT_TIMER_S  16
/* RTC_CNTL_POWERUP_TIMER : R/W ;bitpos:[15:9] ;default: 7'h5 ; */
/*description: .*/
#define RTC_CNTL_POWERUP_TIMER    0x0000007F
#define RTC_CNTL_POWERUP_TIMER_M  ((RTC_CNTL_POWERUP_TIMER_V)<<(RTC_CNTL_POWERUP_TIMER_S))
#define RTC_CNTL_POWERUP_TIMER_V  0x7F
#define RTC_CNTL_POWERUP_TIMER_S  9
/* RTC_CNTL_WAIT_TIMER : R/W ;bitpos:[8:0] ;default: 9'h8 ; */
/*description: .*/
#define RTC_CNTL_WAIT_TIMER    0x000001FF
#define RTC_CNTL_WAIT_TIMER_M  ((RTC_CNTL_WAIT_TIMER_V)<<(RTC_CNTL_WAIT_TIMER_S))
#define RTC_CNTL_WAIT_TIMER_V  0x1FF
#define RTC_CNTL_WAIT_TIMER_S  0

#define RTC_CNTL_TIMER5_REG          (0x60008000 + 0x2C)
/* RTC_CNTL_MIN_SLP_VAL : R/W ;bitpos:[15:8] ;default: 8'h80 ; */
/*description: minimal sleep cycles in slow_clk_rtc.*/
#define RTC_CNTL_MIN_SLP_VAL    0x000000FF
#define RTC_CNTL_MIN_SLP_VAL_M  ((RTC_CNTL_MIN_SLP_VAL_V)<<(RTC_CNTL_MIN_SLP_VAL_S))
#define RTC_CNTL_MIN_SLP_VAL_V  0xFF
#define RTC_CNTL_MIN_SLP_VAL_S  8

#define RTC_CNTL_TIMER6_REG          (0x60008000 + 0x30)
/* RTC_CNTL_DG_PERI_POWERUP_TIMER : R/W ;bitpos:[31:25] ;default: 7'h8 ; */
/*description: .*/
#define RTC_CNTL_DG_PERI_POWERUP_TIMER    0x0000007F
#define RTC_CNTL_DG_PERI_POWERUP_TIMER_M  ((RTC_CNTL_DG_PERI_POWERUP_TIMER_V)<<(RTC_CNTL_DG_PERI_POWERUP_TIMER_S))
#define RTC_CNTL_DG_PERI_POWERUP_TIMER_V  0x7F
#define RTC_CNTL_DG_PERI_POWERUP_TIMER_S  25
/* RTC_CNTL_DG_PERI_WAIT_TIMER : R/W ;bitpos:[24:16] ;default: 9'h20 ; */
/*description: .*/
#define RTC_CNTL_DG_PERI_WAIT_TIMER    0x000001FF
#define RTC_CNTL_DG_PERI_WAIT_TIMER_M  ((RTC_CNTL_DG_PERI_WAIT_TIMER_V)<<(RTC_CNTL_DG_PERI_WAIT_TIMER_S))
#define RTC_CNTL_DG_PERI_WAIT_TIMER_V  0x1FF
#define RTC_CNTL_DG_PERI_WAIT_TIMER_S  16
/* RTC_CNTL_CPU_TOP_POWERUP_TIMER : R/W ;bitpos:[15:9] ;default: 7'h5 ; */
/*description: .*/
#define RTC_CNTL_CPU_TOP_POWERUP_TIMER    0x0000007F
#define RTC_CNTL_CPU_TOP_POWERUP_TIMER_M  ((RTC_CNTL_CPU_TOP_POWERUP_TIMER_V)<<(RTC_CNTL_CPU_TOP_POWERUP_TIMER_S))
#define RTC_CNTL_CPU_TOP_POWERUP_TIMER_V  0x7F
#define RTC_CNTL_CPU_TOP_POWERUP_TIMER_S  9
/* RTC_CNTL_CPU_TOP_WAIT_TIMER : R/W ;bitpos:[8:0] ;default: 9'h8 ; */
/*description: .*/
#define RTC_CNTL_CPU_TOP_WAIT_TIMER    0x000001FF
#define RTC_CNTL_CPU_TOP_WAIT_TIMER_M  ((RTC_CNTL_CPU_TOP_WAIT_TIMER_V)<<(RTC_CNTL_CPU_TOP_WAIT_TIMER_S))
#define RTC_CNTL_CPU_TOP_WAIT_TIMER_V  0x1FF
#define RTC_CNTL_CPU_TOP_WAIT_TIMER_S  0

#define RTC_CNTL_ANA_CONF_REG          (0x60008000 + 0x34)
/* RTC_CNTL_PLL_I2C_PU : R/W ;bitpos:[31] ;default: 1'd0 ; */
/*description: .*/
#define RTC_CNTL_PLL_I2C_PU    (1<<31)
#define RTC_CNTL_PLL_I2C_PU_M  (1<<31)
#define RTC_CNTL_PLL_I2C_PU_V  0x1
#define RTC_CNTL_PLL_I2C_PU_S  31
/* RTC_CNTL_CKGEN_I2C_PU : R/W ;bitpos:[30] ;default: 1'd0 ; */
/*description: 1: CKGEN_I2C power up.*/
#define RTC_CNTL_CKGEN_I2C_PU    (1<<30)
#define RTC_CNTL_CKGEN_I2C_PU_M  (1<<30)
#define RTC_CNTL_CKGEN_I2C_PU_V  0x1
#define RTC_CNTL_CKGEN_I2C_PU_S  30
/* RTC_CNTL_RFRX_PBUS_PU : R/W ;bitpos:[28] ;default: 1'd0 ; */
/*description: 1: RFRX_PBUS power up.*/
#define RTC_CNTL_RFRX_PBUS_PU    (1<<28)
#define RTC_CNTL_RFRX_PBUS_PU_M  (1<<28)
#define RTC_CNTL_RFRX_PBUS_PU_V  0x1
#define RTC_CNTL_RFRX_PBUS_PU_S  28
/* RTC_CNTL_TXRF_I2C_PU : R/W ;bitpos:[27] ;default: 1'd0 ; */
/*description: 1: TXRF_I2C power up.*/
#define RTC_CNTL_TXRF_I2C_PU    (1<<27)
#define RTC_CNTL_TXRF_I2C_PU_M  (1<<27)
#define RTC_CNTL_TXRF_I2C_PU_V  0x1
#define RTC_CNTL_TXRF_I2C_PU_S  27
/* RTC_CNTL_PVTMON_PU : R/W ;bitpos:[26] ;default: 1'b0 ; */
/*description: 1: PVTMON power up.*/
#define RTC_CNTL_PVTMON_PU    (1<<26)
#define RTC_CNTL_PVTMON_PU_M  (1<<26)
#define RTC_CNTL_PVTMON_PU_V  0x1
#define RTC_CNTL_PVTMON_PU_S  26
/* RTC_CNTL_BBPLL_CAL_SLP_START : R/W ;bitpos:[25] ;default: 1'b0 ; */
/*description: start BBPLL calibration during sleep.*/
#define RTC_CNTL_BBPLL_CAL_SLP_START    (1<<25)
#define RTC_CNTL_BBPLL_CAL_SLP_START_M  (1<<25)
#define RTC_CNTL_BBPLL_CAL_SLP_START_V  0x1
#define RTC_CNTL_BBPLL_CAL_SLP_START_S  25
/* RTC_CNTL_ANALOG_TOP_ISO_MONITOR : R/W ;bitpos:[24] ;default: 1'b0 ; */
/*description: PLLA force power up.*/
#define RTC_CNTL_ANALOG_TOP_ISO_MONITOR    (1<<24)
#define RTC_CNTL_ANALOG_TOP_ISO_MONITOR_M  (1<<24)
#define RTC_CNTL_ANALOG_TOP_ISO_MONITOR_V  0x1
#define RTC_CNTL_ANALOG_TOP_ISO_MONITOR_S  24
/* RTC_CNTL_ANALOG_TOP_ISO_SLEEP : R/W ;bitpos:[23] ;default: 1'b0 ; */
/*description: PLLA force power down.*/
#define RTC_CNTL_ANALOG_TOP_ISO_SLEEP    (1<<23)
#define RTC_CNTL_ANALOG_TOP_ISO_SLEEP_M  (1<<23)
#define RTC_CNTL_ANALOG_TOP_ISO_SLEEP_V  0x1
#define RTC_CNTL_ANALOG_TOP_ISO_SLEEP_S  23
/* RTC_CNTL_SAR_I2C_PU : R/W ;bitpos:[22] ;default: 1'b1 ; */
/*description: PLLA force power up.*/
#define RTC_CNTL_SAR_I2C_PU    (1<<22)
#define RTC_CNTL_SAR_I2C_PU_M  (1<<22)
#define RTC_CNTL_SAR_I2C_PU_V  0x1
#define RTC_CNTL_SAR_I2C_PU_S  22
/* RTC_CNTL_GLITCH_RST_EN : R/W ;bitpos:[20] ;default: 1'b0 ; */
/*description: .*/
#define RTC_CNTL_GLITCH_RST_EN    (1<<20)
#define RTC_CNTL_GLITCH_RST_EN_M  (1<<20)
#define RTC_CNTL_GLITCH_RST_EN_V  0x1
#define RTC_CNTL_GLITCH_RST_EN_S  20
/* RTC_CNTL_I2C_RESET_POR_FORCE_PU : R/W ;bitpos:[19] ;default: 1'b0 ; */
/*description: .*/
#define RTC_CNTL_I2C_RESET_POR_FORCE_PU    (1<<19)
#define RTC_CNTL_I2C_RESET_POR_FORCE_PU_M  (1<<19)
#define RTC_CNTL_I2C_RESET_POR_FORCE_PU_V  0x1
#define RTC_CNTL_I2C_RESET_POR_FORCE_PU_S  19
/* RTC_CNTL_I2C_RESET_POR_FORCE_PD : R/W ;bitpos:[18] ;default: 1'b1 ; */
/*description: .*/
#define RTC_CNTL_I2C_RESET_POR_FORCE_PD    (1<<18)
#define RTC_CNTL_I2C_RESET_POR_FORCE_PD_M  (1<<18)
#define RTC_CNTL_I2C_RESET_POR_FORCE_PD_V  0x1
#define RTC_CNTL_I2C_RESET_POR_FORCE_PD_S  18

#define RTC_CNTL_RESET_STATE_REG          (0x60008000 + 0x38)
/* RTC_CNTL_PRO_DRESET_MASK : R/W ;bitpos:[25] ;default: 1'b0 ; */
/*description: .*/
#define RTC_CNTL_PRO_DRESET_MASK    (1<<25)
#define RTC_CNTL_PRO_DRESET_MASK_M  (1<<25)
#define RTC_CNTL_PRO_DRESET_MASK_V  0x1
#define RTC_CNTL_PRO_DRESET_MASK_S  25
/* RTC_CNTL_APP_DRESET_MASK : R/W ;bitpos:[24] ;default: 1'b0 ; */
/*description: .*/
#define RTC_CNTL_APP_DRESET_MASK    (1<<24)
#define RTC_CNTL_APP_DRESET_MASK_M  (1<<24)
#define RTC_CNTL_APP_DRESET_MASK_V  0x1
#define RTC_CNTL_APP_DRESET_MASK_S  24
/* RTC_CNTL_RESET_FLAG_JTAG_APPCPU_CLR : WO ;bitpos:[23] ;default: 1'b0 ; */
/*description: .*/
#define RTC_CNTL_RESET_FLAG_JTAG_APPCPU_CLR    (1<<23)
#define RTC_CNTL_RESET_FLAG_JTAG_APPCPU_CLR_M  (1<<23)
#define RTC_CNTL_RESET_FLAG_JTAG_APPCPU_CLR_V  0x1
#define RTC_CNTL_RESET_FLAG_JTAG_APPCPU_CLR_S  23
/* RTC_CNTL_RESET_FLAG_JTAG_PROCPU_CLR : WO ;bitpos:[22] ;default: 1'b0 ; */
/*description: .*/
#define RTC_CNTL_RESET_FLAG_JTAG_PROCPU_CLR    (1<<22)
#define RTC_CNTL_RESET_FLAG_JTAG_PROCPU_CLR_M  (1<<22)
#define RTC_CNTL_RESET_FLAG_JTAG_PROCPU_CLR_V  0x1
#define RTC_CNTL_RESET_FLAG_JTAG_PROCPU_CLR_S  22
/* RTC_CNTL_RESET_FLAG_JTAG_APPCPU : RO ;bitpos:[21] ;default: 1'b0 ; */
/*description: .*/
#define RTC_CNTL_RESET_FLAG_JTAG_APPCPU    (1<<21)
#define RTC_CNTL_RESET_FLAG_JTAG_APPCPU_M  (1<<21)
#define RTC_CNTL_RESET_FLAG_JTAG_APPCPU_V  0x1
#define RTC_CNTL_RESET_FLAG_JTAG_APPCPU_S  21
/* RTC_CNTL_RESET_FLAG_JTAG_PROCPU : RO ;bitpos:[20] ;default: 1'b0 ; */
/*description: .*/
#define RTC_CNTL_RESET_FLAG_JTAG_PROCPU    (1<<20)
#define RTC_CNTL_RESET_FLAG_JTAG_PROCPU_M  (1<<20)
#define RTC_CNTL_RESET_FLAG_JTAG_PROCPU_V  0x1
#define RTC_CNTL_RESET_FLAG_JTAG_PROCPU_S  20
/* RTC_CNTL_PROCPU_OCD_HALT_ON_RESET : R/W ;bitpos:[19] ;default: 1'b0 ; */
/*description: PROCPU OcdHaltOnReset.*/
#define RTC_CNTL_PROCPU_OCD_HALT_ON_RESET    (1<<19)
#define RTC_CNTL_PROCPU_OCD_HALT_ON_RESET_M  (1<<19)
#define RTC_CNTL_PROCPU_OCD_HALT_ON_RESET_V  0x1
#define RTC_CNTL_PROCPU_OCD_HALT_ON_RESET_S  19
/* RTC_CNTL_APPCPU_OCD_HALT_ON_RESET : R/W ;bitpos:[18] ;default: 1'b0 ; */
/*description: APPCPU OcdHaltOnReset.*/
#define RTC_CNTL_APPCPU_OCD_HALT_ON_RESET    (1<<18)
#define RTC_CNTL_APPCPU_OCD_HALT_ON_RESET_M  (1<<18)
#define RTC_CNTL_APPCPU_OCD_HALT_ON_RESET_V  0x1
#define RTC_CNTL_APPCPU_OCD_HALT_ON_RESET_S  18
/* RTC_CNTL_RESET_FLAG_APPCPU_CLR : WO ;bitpos:[17] ;default: 1'b0 ; */
/*description: clear APP CPU reset flag.*/
#define RTC_CNTL_RESET_FLAG_APPCPU_CLR    (1<<17)
#define RTC_CNTL_RESET_FLAG_APPCPU_CLR_M  (1<<17)
#define RTC_CNTL_RESET_FLAG_APPCPU_CLR_V  0x1
#define RTC_CNTL_RESET_FLAG_APPCPU_CLR_S  17
/* RTC_CNTL_RESET_FLAG_PROCPU_CLR : WO ;bitpos:[16] ;default: 1'b0 ; */
/*description: clear PRO CPU reset_flag.*/
#define RTC_CNTL_RESET_FLAG_PROCPU_CLR    (1<<16)
#define RTC_CNTL_RESET_FLAG_PROCPU_CLR_M  (1<<16)
#define RTC_CNTL_RESET_FLAG_PROCPU_CLR_V  0x1
#define RTC_CNTL_RESET_FLAG_PROCPU_CLR_S  16
/* RTC_CNTL_RESET_FLAG_APPCPU : RO ;bitpos:[15] ;default: 1'b0 ; */
/*description: APP CPU reset flag.*/
#define RTC_CNTL_RESET_FLAG_APPCPU    (1<<15)
#define RTC_CNTL_RESET_FLAG_APPCPU_M  (1<<15)
#define RTC_CNTL_RESET_FLAG_APPCPU_V  0x1
#define RTC_CNTL_RESET_FLAG_APPCPU_S  15
/* RTC_CNTL_RESET_FLAG_PROCPU : RO ;bitpos:[14] ;default: 1'b0 ; */
/*description: PRO CPU reset_flag.*/
#define RTC_CNTL_RESET_FLAG_PROCPU    (1<<14)
#define RTC_CNTL_RESET_FLAG_PROCPU_M  (1<<14)
#define RTC_CNTL_RESET_FLAG_PROCPU_V  0x1
#define RTC_CNTL_RESET_FLAG_PROCPU_S  14
/* RTC_CNTL_PROCPU_STAT_VECTOR_SEL : R/W ;bitpos:[13] ;default: 1'b1 ; */
/*description: PRO CPU state vector sel.*/
#define RTC_CNTL_PROCPU_STAT_VECTOR_SEL    (1<<13)
#define RTC_CNTL_PROCPU_STAT_VECTOR_SEL_M  (1<<13)
#define RTC_CNTL_PROCPU_STAT_VECTOR_SEL_V  0x1
#define RTC_CNTL_PROCPU_STAT_VECTOR_SEL_S  13
/* RTC_CNTL_APPCPU_STAT_VECTOR_SEL : R/W ;bitpos:[12] ;default: 1'b1 ; */
/*description: APP CPU state vector sel.*/
#define RTC_CNTL_APPCPU_STAT_VECTOR_SEL    (1<<12)
#define RTC_CNTL_APPCPU_STAT_VECTOR_SEL_M  (1<<12)
#define RTC_CNTL_APPCPU_STAT_VECTOR_SEL_V  0x1
#define RTC_CNTL_APPCPU_STAT_VECTOR_SEL_S  12
/* RTC_CNTL_RESET_CAUSE_APPCPU : RO ;bitpos:[11:6] ;default: 0 ; */
/*description: reset cause of APP CPU.*/
#define RTC_CNTL_RESET_CAUSE_APPCPU    0x0000003F
#define RTC_CNTL_RESET_CAUSE_APPCPU_M  ((RTC_CNTL_RESET_CAUSE_APPCPU_V)<<(RTC_CNTL_RESET_CAUSE_APPCPU_S))
#define RTC_CNTL_RESET_CAUSE_APPCPU_V  0x3F
#define RTC_CNTL_RESET_CAUSE_APPCPU_S  6
/* RTC_CNTL_RESET_CAUSE_PROCPU : RO ;bitpos:[5:0] ;default: 0 ; */
/*description: reset cause of PRO CPU.*/
#define RTC_CNTL_RESET_CAUSE_PROCPU    0x0000003F
#define RTC_CNTL_RESET_CAUSE_PROCPU_M  ((RTC_CNTL_RESET_CAUSE_PROCPU_V)<<(RTC_CNTL_RESET_CAUSE_PROCPU_S))
#define RTC_CNTL_RESET_CAUSE_PROCPU_V  0x3F
#define RTC_CNTL_RESET_CAUSE_PROCPU_S  0

#define RTC_CNTL_WAKEUP_STATE_REG          (0x60008000 + 0x3C)
/* RTC_CNTL_WAKEUP_ENA : R/W ;bitpos:[31:15] ;default: 17'b1100 ; */
/*description: wakeup enable bitmap.*/
#define RTC_CNTL_WAKEUP_ENA    0x0001FFFF
#define RTC_CNTL_WAKEUP_ENA_M  ((RTC_CNTL_WAKEUP_ENA_V)<<(RTC_CNTL_WAKEUP_ENA_S))
#define RTC_CNTL_WAKEUP_ENA_V  0x1FFFF
#define RTC_CNTL_WAKEUP_ENA_S  15

#define RTC_CNTL_INT_ENA_REG          (0x60008000 + 0x40)
/* RTC_CNTL_TOUCH_APPROACH_LOOP_DONE_INT_ENA : R/W ;bitpos:[20] ;default: 1'b0 ; */
/*description: .*/
#define RTC_CNTL_TOUCH_APPROACH_LOOP_DONE_INT_ENA    (1<<20)
#define RTC_CNTL_TOUCH_APPROACH_LOOP_DONE_INT_ENA_M  (1<<20)
#define RTC_CNTL_TOUCH_APPROACH_LOOP_DONE_INT_ENA_V  0x1
#define RTC_CNTL_TOUCH_APPROACH_LOOP_DONE_INT_ENA_S  20
/* RTC_CNTL_GLITCH_DET_INT_ENA : R/W ;bitpos:[19] ;default: 1'b0 ; */
/*description: enbale gitch det interrupt.*/
#define RTC_CNTL_GLITCH_DET_INT_ENA    (1<<19)
#define RTC_CNTL_GLITCH_DET_INT_ENA_M  (1<<19)
#define RTC_CNTL_GLITCH_DET_INT_ENA_V  0x1
#define RTC_CNTL_GLITCH_DET_INT_ENA_S  19
/* RTC_CNTL_TOUCH_TIMEOUT_INT_ENA : R/W ;bitpos:[18] ;default: 1'b0 ; */
/*description: enable touch timeout interrupt.*/
#define RTC_CNTL_TOUCH_TIMEOUT_INT_ENA    (1<<18)
#define RTC_CNTL_TOUCH_TIMEOUT_INT_ENA_M  (1<<18)
#define RTC_CNTL_TOUCH_TIMEOUT_INT_ENA_V  0x1
#define RTC_CNTL_TOUCH_TIMEOUT_INT_ENA_S  18
/* RTC_CNTL_COCPU_TRAP_INT_ENA : R/W ;bitpos:[17] ;default: 1'b0 ; */
/*description: enable cocpu trap interrupt.*/
#define RTC_CNTL_COCPU_TRAP_INT_ENA    (1<<17)
#define RTC_CNTL_COCPU_TRAP_INT_ENA_M  (1<<17)
#define RTC_CNTL_COCPU_TRAP_INT_ENA_V  0x1
#define RTC_CNTL_COCPU_TRAP_INT_ENA_S  17
/* RTC_CNTL_XTAL32K_DEAD_INT_ENA : R/W ;bitpos:[16] ;default: 1'b0 ; */
/*description: enable xtal32k_dead  interrupt.*/
#define RTC_CNTL_XTAL32K_DEAD_INT_ENA    (1<<16)
#define RTC_CNTL_XTAL32K_DEAD_INT_ENA_M  (1<<16)
#define RTC_CNTL_XTAL32K_DEAD_INT_ENA_V  0x1
#define RTC_CNTL_XTAL32K_DEAD_INT_ENA_S  16
/* RTC_CNTL_SWD_INT_ENA : R/W ;bitpos:[15] ;default: 1'b0 ; */
/*description: enable super watch dog interrupt.*/
#define RTC_CNTL_SWD_INT_ENA    (1<<15)
#define RTC_CNTL_SWD_INT_ENA_M  (1<<15)
#define RTC_CNTL_SWD_INT_ENA_V  0x1
#define RTC_CNTL_SWD_INT_ENA_S  15
/* RTC_CNTL_SARADC2_INT_ENA : R/W ;bitpos:[14] ;default: 1'b0 ; */
/*description: enable saradc2 interrupt.*/
#define RTC_CNTL_SARADC2_INT_ENA    (1<<14)
#define RTC_CNTL_SARADC2_INT_ENA_M  (1<<14)
#define RTC_CNTL_SARADC2_INT_ENA_V  0x1
#define RTC_CNTL_SARADC2_INT_ENA_S  14
/* RTC_CNTL_COCPU_INT_ENA : R/W ;bitpos:[13] ;default: 1'b0 ; */
/*description: enable riscV cocpu interrupt.*/
#define RTC_CNTL_COCPU_INT_ENA    (1<<13)
#define RTC_CNTL_COCPU_INT_ENA_M  (1<<13)
#define RTC_CNTL_COCPU_INT_ENA_V  0x1
#define RTC_CNTL_COCPU_INT_ENA_S  13
/* RTC_CNTL_TSENS_INT_ENA : R/W ;bitpos:[12] ;default: 1'b0 ; */
/*description: enable tsens interrupt.*/
#define RTC_CNTL_TSENS_INT_ENA    (1<<12)
#define RTC_CNTL_TSENS_INT_ENA_M  (1<<12)
#define RTC_CNTL_TSENS_INT_ENA_V  0x1
#define RTC_CNTL_TSENS_INT_ENA_S  12
/* RTC_CNTL_SARADC1_INT_ENA : R/W ;bitpos:[11] ;default: 1'b0 ; */
/*description: enable saradc1 interrupt.*/
#define RTC_CNTL_SARADC1_INT_ENA    (1<<11)
#define RTC_CNTL_SARADC1_INT_ENA_M  (1<<11)
#define RTC_CNTL_SARADC1_INT_ENA_V  0x1
#define RTC_CNTL_SARADC1_INT_ENA_S  11
/* RTC_CNTL_MAIN_TIMER_INT_ENA : R/W ;bitpos:[10] ;default: 1'b0 ; */
/*description: enable RTC main timer interrupt.*/
#define RTC_CNTL_MAIN_TIMER_INT_ENA    (1<<10)
#define RTC_CNTL_MAIN_TIMER_INT_ENA_M  (1<<10)
#define RTC_CNTL_MAIN_TIMER_INT_ENA_V  0x1
#define RTC_CNTL_MAIN_TIMER_INT_ENA_S  10
/* RTC_CNTL_BROWN_OUT_INT_ENA : R/W ;bitpos:[9] ;default: 1'b0 ; */
/*description: enable brown out interrupt.*/
#define RTC_CNTL_BROWN_OUT_INT_ENA    (1<<9)
#define RTC_CNTL_BROWN_OUT_INT_ENA_M  (1<<9)
#define RTC_CNTL_BROWN_OUT_INT_ENA_V  0x1
#define RTC_CNTL_BROWN_OUT_INT_ENA_S  9
/* RTC_CNTL_TOUCH_INACTIVE_INT_ENA : R/W ;bitpos:[8] ;default: 1'b0 ; */
/*description: enable touch inactive interrupt.*/
#define RTC_CNTL_TOUCH_INACTIVE_INT_ENA    (1<<8)
#define RTC_CNTL_TOUCH_INACTIVE_INT_ENA_M  (1<<8)
#define RTC_CNTL_TOUCH_INACTIVE_INT_ENA_V  0x1
#define RTC_CNTL_TOUCH_INACTIVE_INT_ENA_S  8
/* RTC_CNTL_TOUCH_ACTIVE_INT_ENA : R/W ;bitpos:[7] ;default: 1'b0 ; */
/*description: enable touch active interrupt.*/
#define RTC_CNTL_TOUCH_ACTIVE_INT_ENA    (1<<7)
#define RTC_CNTL_TOUCH_ACTIVE_INT_ENA_M  (1<<7)
#define RTC_CNTL_TOUCH_ACTIVE_INT_ENA_V  0x1
#define RTC_CNTL_TOUCH_ACTIVE_INT_ENA_S  7
/* RTC_CNTL_TOUCH_DONE_INT_ENA : R/W ;bitpos:[6] ;default: 1'b0 ; */
/*description: enable touch done interrupt.*/
#define RTC_CNTL_TOUCH_DONE_INT_ENA    (1<<6)
#define RTC_CNTL_TOUCH_DONE_INT_ENA_M  (1<<6)
#define RTC_CNTL_TOUCH_DONE_INT_ENA_V  0x1
#define RTC_CNTL_TOUCH_DONE_INT_ENA_S  6
/* RTC_CNTL_ULP_CP_INT_ENA : R/W ;bitpos:[5] ;default: 1'b0 ; */
/*description: enable ULP-coprocessor interrupt.*/
#define RTC_CNTL_ULP_CP_INT_ENA    (1<<5)
#define RTC_CNTL_ULP_CP_INT_ENA_M  (1<<5)
#define RTC_CNTL_ULP_CP_INT_ENA_V  0x1
#define RTC_CNTL_ULP_CP_INT_ENA_S  5
/* RTC_CNTL_TOUCH_SCAN_DONE_INT_ENA : R/W ;bitpos:[4] ;default: 1'b0 ; */
/*description: enable touch scan done interrupt.*/
#define RTC_CNTL_TOUCH_SCAN_DONE_INT_ENA    (1<<4)
#define RTC_CNTL_TOUCH_SCAN_DONE_INT_ENA_M  (1<<4)
#define RTC_CNTL_TOUCH_SCAN_DONE_INT_ENA_V  0x1
#define RTC_CNTL_TOUCH_SCAN_DONE_INT_ENA_S  4
/* RTC_CNTL_WDT_INT_ENA : R/W ;bitpos:[3] ;default: 1'b0 ; */
/*description: enable RTC WDT interrupt.*/
#define RTC_CNTL_WDT_INT_ENA    (1<<3)
#define RTC_CNTL_WDT_INT_ENA_M  (1<<3)
#define RTC_CNTL_WDT_INT_ENA_V  0x1
#define RTC_CNTL_WDT_INT_ENA_S  3
/* RTC_CNTL_SDIO_IDLE_INT_ENA : R/W ;bitpos:[2] ;default: 1'b0 ; */
/*description: enable SDIO idle interrupt.*/
#define RTC_CNTL_SDIO_IDLE_INT_ENA    (1<<2)
#define RTC_CNTL_SDIO_IDLE_INT_ENA_M  (1<<2)
#define RTC_CNTL_SDIO_IDLE_INT_ENA_V  0x1
#define RTC_CNTL_SDIO_IDLE_INT_ENA_S  2
/* RTC_CNTL_SLP_REJECT_INT_ENA : R/W ;bitpos:[1] ;default: 1'b0 ; */
/*description: enable sleep reject interrupt.*/
#define RTC_CNTL_SLP_REJECT_INT_ENA    (1<<1)
#define RTC_CNTL_SLP_REJECT_INT_ENA_M  (1<<1)
#define RTC_CNTL_SLP_REJECT_INT_ENA_V  0x1
#define RTC_CNTL_SLP_REJECT_INT_ENA_S  1
/* RTC_CNTL_SLP_WAKEUP_INT_ENA : R/W ;bitpos:[0] ;default: 1'b0 ; */
/*description: enable sleep wakeup interrupt.*/
#define RTC_CNTL_SLP_WAKEUP_INT_ENA    (1<<0)
#define RTC_CNTL_SLP_WAKEUP_INT_ENA_M  (1<<0)
#define RTC_CNTL_SLP_WAKEUP_INT_ENA_V  0x1
#define RTC_CNTL_SLP_WAKEUP_INT_ENA_S  0

#define RTC_CNTL_INT_RAW_REG          (0x60008000 + 0x44)
/* RTC_CNTL_TOUCH_APPROACH_LOOP_DONE_INT_RAW : R/W ;bitpos:[20] ;default: 1'b0 ; */
/*description: .*/
#define RTC_CNTL_TOUCH_APPROACH_LOOP_DONE_INT_RAW    (1<<20)
#define RTC_CNTL_TOUCH_APPROACH_LOOP_DONE_INT_RAW_M  (1<<20)
#define RTC_CNTL_TOUCH_APPROACH_LOOP_DONE_INT_RAW_V  0x1
#define RTC_CNTL_TOUCH_APPROACH_LOOP_DONE_INT_RAW_S  20
/* RTC_CNTL_GLITCH_DET_INT_RAW : RO ;bitpos:[19] ;default: 1'b0 ; */
/*description: glitch_det_interrupt_raw.*/
#define RTC_CNTL_GLITCH_DET_INT_RAW    (1<<19)
#define RTC_CNTL_GLITCH_DET_INT_RAW_M  (1<<19)
#define RTC_CNTL_GLITCH_DET_INT_RAW_V  0x1
#define RTC_CNTL_GLITCH_DET_INT_RAW_S  19
/* RTC_CNTL_TOUCH_TIMEOUT_INT_RAW : RO ;bitpos:[18] ;default: 1'b0 ; */
/*description: touch timeout interrupt raw.*/
#define RTC_CNTL_TOUCH_TIMEOUT_INT_RAW    (1<<18)
#define RTC_CNTL_TOUCH_TIMEOUT_INT_RAW_M  (1<<18)
#define RTC_CNTL_TOUCH_TIMEOUT_INT_RAW_V  0x1
#define RTC_CNTL_TOUCH_TIMEOUT_INT_RAW_S  18
/* RTC_CNTL_COCPU_TRAP_INT_RAW : RO ;bitpos:[17] ;default: 1'b0 ; */
/*description: cocpu trap interrupt raw.*/
#define RTC_CNTL_COCPU_TRAP_INT_RAW    (1<<17)
#define RTC_CNTL_COCPU_TRAP_INT_RAW_M  (1<<17)
#define RTC_CNTL_COCPU_TRAP_INT_RAW_V  0x1
#define RTC_CNTL_COCPU_TRAP_INT_RAW_S  17
/* RTC_CNTL_XTAL32K_DEAD_INT_RAW : RO ;bitpos:[16] ;default: 1'b0 ; */
/*description: xtal32k dead detection interrupt raw.*/
#define RTC_CNTL_XTAL32K_DEAD_INT_RAW    (1<<16)
#define RTC_CNTL_XTAL32K_DEAD_INT_RAW_M  (1<<16)
#define RTC_CNTL_XTAL32K_DEAD_INT_RAW_V  0x1
#define RTC_CNTL_XTAL32K_DEAD_INT_RAW_S  16
/* RTC_CNTL_SWD_INT_RAW : RO ;bitpos:[15] ;default: 1'b0 ; */
/*description: super watch dog interrupt raw.*/
#define RTC_CNTL_SWD_INT_RAW    (1<<15)
#define RTC_CNTL_SWD_INT_RAW_M  (1<<15)
#define RTC_CNTL_SWD_INT_RAW_V  0x1
#define RTC_CNTL_SWD_INT_RAW_S  15
/* RTC_CNTL_SARADC2_INT_RAW : RO ;bitpos:[14] ;default: 1'b0 ; */
/*description: saradc2 interrupt raw.*/
#define RTC_CNTL_SARADC2_INT_RAW    (1<<14)
#define RTC_CNTL_SARADC2_INT_RAW_M  (1<<14)
#define RTC_CNTL_SARADC2_INT_RAW_V  0x1
#define RTC_CNTL_SARADC2_INT_RAW_S  14
/* RTC_CNTL_COCPU_INT_RAW : RO ;bitpos:[13] ;default: 1'b0 ; */
/*description: riscV cocpu interrupt raw.*/
#define RTC_CNTL_COCPU_INT_RAW    (1<<13)
#define RTC_CNTL_COCPU_INT_RAW_M  (1<<13)
#define RTC_CNTL_COCPU_INT_RAW_V  0x1
#define RTC_CNTL_COCPU_INT_RAW_S  13
/* RTC_CNTL_TSENS_INT_RAW : RO ;bitpos:[12] ;default: 1'b0 ; */
/*description: tsens interrupt raw.*/
#define RTC_CNTL_TSENS_INT_RAW    (1<<12)
#define RTC_CNTL_TSENS_INT_RAW_M  (1<<12)
#define RTC_CNTL_TSENS_INT_RAW_V  0x1
#define RTC_CNTL_TSENS_INT_RAW_S  12
/* RTC_CNTL_SARADC1_INT_RAW : RO ;bitpos:[11] ;default: 1'b0 ; */
/*description: saradc1 interrupt raw.*/
#define RTC_CNTL_SARADC1_INT_RAW    (1<<11)
#define RTC_CNTL_SARADC1_INT_RAW_M  (1<<11)
#define RTC_CNTL_SARADC1_INT_RAW_V  0x1
#define RTC_CNTL_SARADC1_INT_RAW_S  11
/* RTC_CNTL_MAIN_TIMER_INT_RAW : RO ;bitpos:[10] ;default: 1'b0 ; */
/*description: RTC main timer interrupt raw.*/
#define RTC_CNTL_MAIN_TIMER_INT_RAW    (1<<10)
#define RTC_CNTL_MAIN_TIMER_INT_RAW_M  (1<<10)
#define RTC_CNTL_MAIN_TIMER_INT_RAW_V  0x1
#define RTC_CNTL_MAIN_TIMER_INT_RAW_S  10
/* RTC_CNTL_BROWN_OUT_INT_RAW : RO ;bitpos:[9] ;default: 1'b0 ; */
/*description: brown out interrupt raw.*/
#define RTC_CNTL_BROWN_OUT_INT_RAW    (1<<9)
#define RTC_CNTL_BROWN_OUT_INT_RAW_M  (1<<9)
#define RTC_CNTL_BROWN_OUT_INT_RAW_V  0x1
#define RTC_CNTL_BROWN_OUT_INT_RAW_S  9
/* RTC_CNTL_TOUCH_INACTIVE_INT_RAW : RO ;bitpos:[8] ;default: 1'b0 ; */
/*description: touch inactive interrupt raw.*/
#define RTC_CNTL_TOUCH_INACTIVE_INT_RAW    (1<<8)
#define RTC_CNTL_TOUCH_INACTIVE_INT_RAW_M  (1<<8)
#define RTC_CNTL_TOUCH_INACTIVE_INT_RAW_V  0x1
#define RTC_CNTL_TOUCH_INACTIVE_INT_RAW_S  8
/* RTC_CNTL_TOUCH_ACTIVE_INT_RAW : RO ;bitpos:[7] ;default: 1'b0 ; */
/*description: touch active interrupt raw.*/
#define RTC_CNTL_TOUCH_ACTIVE_INT_RAW    (1<<7)
#define RTC_CNTL_TOUCH_ACTIVE_INT_RAW_M  (1<<7)
#define RTC_CNTL_TOUCH_ACTIVE_INT_RAW_V  0x1
#define RTC_CNTL_TOUCH_ACTIVE_INT_RAW_S  7
/* RTC_CNTL_TOUCH_DONE_INT_RAW : RO ;bitpos:[6] ;default: 1'b0 ; */
/*description: touch interrupt raw.*/
#define RTC_CNTL_TOUCH_DONE_INT_RAW    (1<<6)
#define RTC_CNTL_TOUCH_DONE_INT_RAW_M  (1<<6)
#define RTC_CNTL_TOUCH_DONE_INT_RAW_V  0x1
#define RTC_CNTL_TOUCH_DONE_INT_RAW_S  6
/* RTC_CNTL_ULP_CP_INT_RAW : RO ;bitpos:[5] ;default: 1'b0 ; */
/*description: ULP-coprocessor interrupt raw.*/
#define RTC_CNTL_ULP_CP_INT_RAW    (1<<5)
#define RTC_CNTL_ULP_CP_INT_RAW_M  (1<<5)
#define RTC_CNTL_ULP_CP_INT_RAW_V  0x1
#define RTC_CNTL_ULP_CP_INT_RAW_S  5
/* RTC_CNTL_TOUCH_SCAN_DONE_INT_RAW : RO ;bitpos:[4] ;default: 1'b0 ; */
/*description: .*/
#define RTC_CNTL_TOUCH_SCAN_DONE_INT_RAW    (1<<4)
#define RTC_CNTL_TOUCH_SCAN_DONE_INT_RAW_M  (1<<4)
#define RTC_CNTL_TOUCH_SCAN_DONE_INT_RAW_V  0x1
#define RTC_CNTL_TOUCH_SCAN_DONE_INT_RAW_S  4
/* RTC_CNTL_WDT_INT_RAW : RO ;bitpos:[3] ;default: 1'b0 ; */
/*description: RTC WDT interrupt raw.*/
#define RTC_CNTL_WDT_INT_RAW    (1<<3)
#define RTC_CNTL_WDT_INT_RAW_M  (1<<3)
#define RTC_CNTL_WDT_INT_RAW_V  0x1
#define RTC_CNTL_WDT_INT_RAW_S  3
/* RTC_CNTL_SDIO_IDLE_INT_RAW : RO ;bitpos:[2] ;default: 1'b0 ; */
/*description: SDIO idle interrupt raw.*/
#define RTC_CNTL_SDIO_IDLE_INT_RAW    (1<<2)
#define RTC_CNTL_SDIO_IDLE_INT_RAW_M  (1<<2)
#define RTC_CNTL_SDIO_IDLE_INT_RAW_V  0x1
#define RTC_CNTL_SDIO_IDLE_INT_RAW_S  2
/* RTC_CNTL_SLP_REJECT_INT_RAW : RO ;bitpos:[1] ;default: 1'b0 ; */
/*description: sleep reject interrupt raw.*/
#define RTC_CNTL_SLP_REJECT_INT_RAW    (1<<1)
#define RTC_CNTL_SLP_REJECT_INT_RAW_M  (1<<1)
#define RTC_CNTL_SLP_REJECT_INT_RAW_V  0x1
#define RTC_CNTL_SLP_REJECT_INT_RAW_S  1
/* RTC_CNTL_SLP_WAKEUP_INT_RAW : RO ;bitpos:[0] ;default: 1'b0 ; */
/*description: sleep wakeup interrupt raw.*/
#define RTC_CNTL_SLP_WAKEUP_INT_RAW    (1<<0)
#define RTC_CNTL_SLP_WAKEUP_INT_RAW_M  (1<<0)
#define RTC_CNTL_SLP_WAKEUP_INT_RAW_V  0x1
#define RTC_CNTL_SLP_WAKEUP_INT_RAW_S  0

#define RTC_CNTL_INT_ST_REG          (0x60008000 + 0x48)
/* RTC_CNTL_TOUCH_APPROACH_LOOP_DONE_INT_ST : RO ;bitpos:[20] ;default: 1'b0 ; */
/*description: .*/
#define RTC_CNTL_TOUCH_APPROACH_LOOP_DONE_INT_ST    (1<<20)
#define RTC_CNTL_TOUCH_APPROACH_LOOP_DONE_INT_ST_M  (1<<20)
#define RTC_CNTL_TOUCH_APPROACH_LOOP_DONE_INT_ST_V  0x1
#define RTC_CNTL_TOUCH_APPROACH_LOOP_DONE_INT_ST_S  20
/* RTC_CNTL_GLITCH_DET_INT_ST : RO ;bitpos:[19] ;default: 1'b0 ; */
/*description: glitch_det_interrupt state.*/
#define RTC_CNTL_GLITCH_DET_INT_ST    (1<<19)
#define RTC_CNTL_GLITCH_DET_INT_ST_M  (1<<19)
#define RTC_CNTL_GLITCH_DET_INT_ST_V  0x1
#define RTC_CNTL_GLITCH_DET_INT_ST_S  19
/* RTC_CNTL_TOUCH_TIMEOUT_INT_ST : RO ;bitpos:[18] ;default: 1'b0 ; */
/*description: Touch timeout interrupt state.*/
#define RTC_CNTL_TOUCH_TIMEOUT_INT_ST    (1<<18)
#define RTC_CNTL_TOUCH_TIMEOUT_INT_ST_M  (1<<18)
#define RTC_CNTL_TOUCH_TIMEOUT_INT_ST_V  0x1
#define RTC_CNTL_TOUCH_TIMEOUT_INT_ST_S  18
/* RTC_CNTL_COCPU_TRAP_INT_ST : RO ;bitpos:[17] ;default: 1'b0 ; */
/*description: cocpu trap interrupt state.*/
#define RTC_CNTL_COCPU_TRAP_INT_ST    (1<<17)
#define RTC_CNTL_COCPU_TRAP_INT_ST_M  (1<<17)
#define RTC_CNTL_COCPU_TRAP_INT_ST_V  0x1
#define RTC_CNTL_COCPU_TRAP_INT_ST_S  17
/* RTC_CNTL_XTAL32K_DEAD_INT_ST : RO ;bitpos:[16] ;default: 1'b0 ; */
/*description: xtal32k dead detection interrupt state.*/
#define RTC_CNTL_XTAL32K_DEAD_INT_ST    (1<<16)
#define RTC_CNTL_XTAL32K_DEAD_INT_ST_M  (1<<16)
#define RTC_CNTL_XTAL32K_DEAD_INT_ST_V  0x1
#define RTC_CNTL_XTAL32K_DEAD_INT_ST_S  16
/* RTC_CNTL_SWD_INT_ST : RO ;bitpos:[15] ;default: 1'b0 ; */
/*description: super watch dog interrupt state.*/
#define RTC_CNTL_SWD_INT_ST    (1<<15)
#define RTC_CNTL_SWD_INT_ST_M  (1<<15)
#define RTC_CNTL_SWD_INT_ST_V  0x1
#define RTC_CNTL_SWD_INT_ST_S  15
/* RTC_CNTL_SARADC2_INT_ST : RO ;bitpos:[14] ;default: 1'b0 ; */
/*description: saradc2 interrupt state.*/
#define RTC_CNTL_SARADC2_INT_ST    (1<<14)
#define RTC_CNTL_SARADC2_INT_ST_M  (1<<14)
#define RTC_CNTL_SARADC2_INT_ST_V  0x1
#define RTC_CNTL_SARADC2_INT_ST_S  14
/* RTC_CNTL_COCPU_INT_ST : RO ;bitpos:[13] ;default: 1'b0 ; */
/*description: riscV cocpu interrupt state.*/
#define RTC_CNTL_COCPU_INT_ST    (1<<13)
#define RTC_CNTL_COCPU_INT_ST_M  (1<<13)
#define RTC_CNTL_COCPU_INT_ST_V  0x1
#define RTC_CNTL_COCPU_INT_ST_S  13
/* RTC_CNTL_TSENS_INT_ST : RO ;bitpos:[12] ;default: 1'b0 ; */
/*description: tsens interrupt state.*/
#define RTC_CNTL_TSENS_INT_ST    (1<<12)
#define RTC_CNTL_TSENS_INT_ST_M  (1<<12)
#define RTC_CNTL_TSENS_INT_ST_V  0x1
#define RTC_CNTL_TSENS_INT_ST_S  12
/* RTC_CNTL_SARADC1_INT_ST : RO ;bitpos:[11] ;default: 1'b0 ; */
/*description: saradc1 interrupt state.*/
#define RTC_CNTL_SARADC1_INT_ST    (1<<11)
#define RTC_CNTL_SARADC1_INT_ST_M  (1<<11)
#define RTC_CNTL_SARADC1_INT_ST_V  0x1
#define RTC_CNTL_SARADC1_INT_ST_S  11
/* RTC_CNTL_MAIN_TIMER_INT_ST : RO ;bitpos:[10] ;default: 1'b0 ; */
/*description: RTC main timer interrupt state.*/
#define RTC_CNTL_MAIN_TIMER_INT_ST    (1<<10)
#define RTC_CNTL_MAIN_TIMER_INT_ST_M  (1<<10)
#define RTC_CNTL_MAIN_TIMER_INT_ST_V  0x1
#define RTC_CNTL_MAIN_TIMER_INT_ST_S  10
/* RTC_CNTL_BROWN_OUT_INT_ST : RO ;bitpos:[9] ;default: 1'b0 ; */
/*description: brown out interrupt state.*/
#define RTC_CNTL_BROWN_OUT_INT_ST    (1<<9)
#define RTC_CNTL_BROWN_OUT_INT_ST_M  (1<<9)
#define RTC_CNTL_BROWN_OUT_INT_ST_V  0x1
#define RTC_CNTL_BROWN_OUT_INT_ST_S  9
/* RTC_CNTL_TOUCH_INACTIVE_INT_ST : RO ;bitpos:[8] ;default: 1'b0 ; */
/*description: touch inactive interrupt state.*/
#define RTC_CNTL_TOUCH_INACTIVE_INT_ST    (1<<8)
#define RTC_CNTL_TOUCH_INACTIVE_INT_ST_M  (1<<8)
#define RTC_CNTL_TOUCH_INACTIVE_INT_ST_V  0x1
#define RTC_CNTL_TOUCH_INACTIVE_INT_ST_S  8
/* RTC_CNTL_TOUCH_ACTIVE_INT_ST : RO ;bitpos:[7] ;default: 1'b0 ; */
/*description: touch active interrupt state.*/
#define RTC_CNTL_TOUCH_ACTIVE_INT_ST    (1<<7)
#define RTC_CNTL_TOUCH_ACTIVE_INT_ST_M  (1<<7)
#define RTC_CNTL_TOUCH_ACTIVE_INT_ST_V  0x1
#define RTC_CNTL_TOUCH_ACTIVE_INT_ST_S  7
/* RTC_CNTL_TOUCH_DONE_INT_ST : RO ;bitpos:[6] ;default: 1'b0 ; */
/*description: touch done interrupt state.*/
#define RTC_CNTL_TOUCH_DONE_INT_ST    (1<<6)
#define RTC_CNTL_TOUCH_DONE_INT_ST_M  (1<<6)
#define RTC_CNTL_TOUCH_DONE_INT_ST_V  0x1
#define RTC_CNTL_TOUCH_DONE_INT_ST_S  6
/* RTC_CNTL_ULP_CP_INT_ST : RO ;bitpos:[5] ;default: 1'b0 ; */
/*description: ULP-coprocessor interrupt state.*/
#define RTC_CNTL_ULP_CP_INT_ST    (1<<5)
#define RTC_CNTL_ULP_CP_INT_ST_M  (1<<5)
#define RTC_CNTL_ULP_CP_INT_ST_V  0x1
#define RTC_CNTL_ULP_CP_INT_ST_S  5
/* RTC_CNTL_TOUCH_SCAN_DONE_INT_ST : RO ;bitpos:[4] ;default: 1'b0 ; */
/*description: .*/
#define RTC_CNTL_TOUCH_SCAN_DONE_INT_ST    (1<<4)
#define RTC_CNTL_TOUCH_SCAN_DONE_INT_ST_M  (1<<4)
#define RTC_CNTL_TOUCH_SCAN_DONE_INT_ST_V  0x1
#define RTC_CNTL_TOUCH_SCAN_DONE_INT_ST_S  4
/* RTC_CNTL_WDT_INT_ST : RO ;bitpos:[3] ;default: 1'b0 ; */
/*description: RTC WDT interrupt state.*/
#define RTC_CNTL_WDT_INT_ST    (1<<3)
#define RTC_CNTL_WDT_INT_ST_M  (1<<3)
#define RTC_CNTL_WDT_INT_ST_V  0x1
#define RTC_CNTL_WDT_INT_ST_S  3
/* RTC_CNTL_SDIO_IDLE_INT_ST : RO ;bitpos:[2] ;default: 1'b0 ; */
/*description: SDIO idle interrupt state.*/
#define RTC_CNTL_SDIO_IDLE_INT_ST    (1<<2)
#define RTC_CNTL_SDIO_IDLE_INT_ST_M  (1<<2)
#define RTC_CNTL_SDIO_IDLE_INT_ST_V  0x1
#define RTC_CNTL_SDIO_IDLE_INT_ST_S  2
/* RTC_CNTL_SLP_REJECT_INT_ST : RO ;bitpos:[1] ;default: 1'b0 ; */
/*description: sleep reject interrupt state.*/
#define RTC_CNTL_SLP_REJECT_INT_ST    (1<<1)
#define RTC_CNTL_SLP_REJECT_INT_ST_M  (1<<1)
#define RTC_CNTL_SLP_REJECT_INT_ST_V  0x1
#define RTC_CNTL_SLP_REJECT_INT_ST_S  1
/* RTC_CNTL_SLP_WAKEUP_INT_ST : RO ;bitpos:[0] ;default: 1'b0 ; */
/*description: sleep wakeup interrupt state.*/
#define RTC_CNTL_SLP_WAKEUP_INT_ST    (1<<0)
#define RTC_CNTL_SLP_WAKEUP_INT_ST_M  (1<<0)
#define RTC_CNTL_SLP_WAKEUP_INT_ST_V  0x1
#define RTC_CNTL_SLP_WAKEUP_INT_ST_S  0

#define RTC_CNTL_INT_CLR_REG          (0x60008000 + 0x4C)
/* RTC_CNTL_TOUCH_APPROACH_LOOP_DONE_INT_CLR : WO ;bitpos:[20] ;default: 1'b0 ; */
/*description: .*/
#define RTC_CNTL_TOUCH_APPROACH_LOOP_DONE_INT_CLR    (1<<20)
#define RTC_CNTL_TOUCH_APPROACH_LOOP_DONE_INT_CLR_M  (1<<20)
#define RTC_CNTL_TOUCH_APPROACH_LOOP_DONE_INT_CLR_V  0x1
#define RTC_CNTL_TOUCH_APPROACH_LOOP_DONE_INT_CLR_S  20
/* RTC_CNTL_GLITCH_DET_INT_CLR : WO ;bitpos:[19] ;default: 1'b0 ; */
/*description: Clear glitch det interrupt state.*/
#define RTC_CNTL_GLITCH_DET_INT_CLR    (1<<19)
#define RTC_CNTL_GLITCH_DET_INT_CLR_M  (1<<19)
#define RTC_CNTL_GLITCH_DET_INT_CLR_V  0x1
#define RTC_CNTL_GLITCH_DET_INT_CLR_S  19
/* RTC_CNTL_TOUCH_TIMEOUT_INT_CLR : WO ;bitpos:[18] ;default: 1'b0 ; */
/*description: Clear touch timeout interrupt state.*/
#define RTC_CNTL_TOUCH_TIMEOUT_INT_CLR    (1<<18)
#define RTC_CNTL_TOUCH_TIMEOUT_INT_CLR_M  (1<<18)
#define RTC_CNTL_TOUCH_TIMEOUT_INT_CLR_V  0x1
#define RTC_CNTL_TOUCH_TIMEOUT_INT_CLR_S  18
/* RTC_CNTL_COCPU_TRAP_INT_CLR : WO ;bitpos:[17] ;default: 1'b0 ; */
/*description: Clear cocpu trap interrupt state.*/
#define RTC_CNTL_COCPU_TRAP_INT_CLR    (1<<17)
#define RTC_CNTL_COCPU_TRAP_INT_CLR_M  (1<<17)
#define RTC_CNTL_COCPU_TRAP_INT_CLR_V  0x1
#define RTC_CNTL_COCPU_TRAP_INT_CLR_S  17
/* RTC_CNTL_XTAL32K_DEAD_INT_CLR : WO ;bitpos:[16] ;default: 1'b0 ; */
/*description: Clear RTC WDT interrupt state.*/
#define RTC_CNTL_XTAL32K_DEAD_INT_CLR    (1<<16)
#define RTC_CNTL_XTAL32K_DEAD_INT_CLR_M  (1<<16)
#define RTC_CNTL_XTAL32K_DEAD_INT_CLR_V  0x1
#define RTC_CNTL_XTAL32K_DEAD_INT_CLR_S  16
/* RTC_CNTL_SWD_INT_CLR : WO ;bitpos:[15] ;default: 1'b0 ; */
/*description: Clear super watch dog interrupt state.*/
#define RTC_CNTL_SWD_INT_CLR    (1<<15)
#define RTC_CNTL_SWD_INT_CLR_M  (1<<15)
#define RTC_CNTL_SWD_INT_CLR_V  0x1
#define RTC_CNTL_SWD_INT_CLR_S  15
/* RTC_CNTL_SARADC2_INT_CLR : WO ;bitpos:[14] ;default: 1'b0 ; */
/*description: Clear saradc2 interrupt state.*/
#define RTC_CNTL_SARADC2_INT_CLR    (1<<14)
#define RTC_CNTL_SARADC2_INT_CLR_M  (1<<14)
#define RTC_CNTL_SARADC2_INT_CLR_V  0x1
#define RTC_CNTL_SARADC2_INT_CLR_S  14
/* RTC_CNTL_COCPU_INT_CLR : WO ;bitpos:[13] ;default: 1'b0 ; */
/*description: Clear riscV cocpu interrupt state.*/
#define RTC_CNTL_COCPU_INT_CLR    (1<<13)
#define RTC_CNTL_COCPU_INT_CLR_M  (1<<13)
#define RTC_CNTL_COCPU_INT_CLR_V  0x1
#define RTC_CNTL_COCPU_INT_CLR_S  13
/* RTC_CNTL_TSENS_INT_CLR : WO ;bitpos:[12] ;default: 1'b0 ; */
/*description: Clear tsens interrupt state.*/
#define RTC_CNTL_TSENS_INT_CLR    (1<<12)
#define RTC_CNTL_TSENS_INT_CLR_M  (1<<12)
#define RTC_CNTL_TSENS_INT_CLR_V  0x1
#define RTC_CNTL_TSENS_INT_CLR_S  12
/* RTC_CNTL_SARADC1_INT_CLR : WO ;bitpos:[11] ;default: 1'b0 ; */
/*description: Clear saradc1 interrupt state.*/
#define RTC_CNTL_SARADC1_INT_CLR    (1<<11)
#define RTC_CNTL_SARADC1_INT_CLR_M  (1<<11)
#define RTC_CNTL_SARADC1_INT_CLR_V  0x1
#define RTC_CNTL_SARADC1_INT_CLR_S  11
/* RTC_CNTL_MAIN_TIMER_INT_CLR : WO ;bitpos:[10] ;default: 1'b0 ; */
/*description: Clear RTC main timer interrupt state.*/
#define RTC_CNTL_MAIN_TIMER_INT_CLR    (1<<10)
#define RTC_CNTL_MAIN_TIMER_INT_CLR_M  (1<<10)
#define RTC_CNTL_MAIN_TIMER_INT_CLR_V  0x1
#define RTC_CNTL_MAIN_TIMER_INT_CLR_S  10
/* RTC_CNTL_BROWN_OUT_INT_CLR : WO ;bitpos:[9] ;default: 1'b0 ; */
/*description: Clear brown out interrupt state.*/
#define RTC_CNTL_BROWN_OUT_INT_CLR    (1<<9)
#define RTC_CNTL_BROWN_OUT_INT_CLR_M  (1<<9)
#define RTC_CNTL_BROWN_OUT_INT_CLR_V  0x1
#define RTC_CNTL_BROWN_OUT_INT_CLR_S  9
/* RTC_CNTL_TOUCH_INACTIVE_INT_CLR : WO ;bitpos:[8] ;default: 1'b0 ; */
/*description: Clear touch inactive interrupt state.*/
#define RTC_CNTL_TOUCH_INACTIVE_INT_CLR    (1<<8)
#define RTC_CNTL_TOUCH_INACTIVE_INT_CLR_M  (1<<8)
#define RTC_CNTL_TOUCH_INACTIVE_INT_CLR_V  0x1
#define RTC_CNTL_TOUCH_INACTIVE_INT_CLR_S  8
/* RTC_CNTL_TOUCH_ACTIVE_INT_CLR : WO ;bitpos:[7] ;default: 1'b0 ; */
/*description: Clear touch active interrupt state.*/
#define RTC_CNTL_TOUCH_ACTIVE_INT_CLR    (1<<7)
#define RTC_CNTL_TOUCH_ACTIVE_INT_CLR_M  (1<<7)
#define RTC_CNTL_TOUCH_ACTIVE_INT_CLR_V  0x1
#define RTC_CNTL_TOUCH_ACTIVE_INT_CLR_S  7
/* RTC_CNTL_TOUCH_DONE_INT_CLR : WO ;bitpos:[6] ;default: 1'b0 ; */
/*description: Clear touch done interrupt state.*/
#define RTC_CNTL_TOUCH_DONE_INT_CLR    (1<<6)
#define RTC_CNTL_TOUCH_DONE_INT_CLR_M  (1<<6)
#define RTC_CNTL_TOUCH_DONE_INT_CLR_V  0x1
#define RTC_CNTL_TOUCH_DONE_INT_CLR_S  6
/* RTC_CNTL_ULP_CP_INT_CLR : WO ;bitpos:[5] ;default: 1'b0 ; */
/*description: Clear ULP-coprocessor interrupt state.*/
#define RTC_CNTL_ULP_CP_INT_CLR    (1<<5)
#define RTC_CNTL_ULP_CP_INT_CLR_M  (1<<5)
#define RTC_CNTL_ULP_CP_INT_CLR_V  0x1
#define RTC_CNTL_ULP_CP_INT_CLR_S  5
/* RTC_CNTL_TOUCH_SCAN_DONE_INT_CLR : WO ;bitpos:[4] ;default: 1'b0 ; */
/*description: .*/
#define RTC_CNTL_TOUCH_SCAN_DONE_INT_CLR    (1<<4)
#define RTC_CNTL_TOUCH_SCAN_DONE_INT_CLR_M  (1<<4)
#define RTC_CNTL_TOUCH_SCAN_DONE_INT_CLR_V  0x1
#define RTC_CNTL_TOUCH_SCAN_DONE_INT_CLR_S  4
/* RTC_CNTL_WDT_INT_CLR : WO ;bitpos:[3] ;default: 1'b0 ; */
/*description: Clear RTC WDT interrupt state.*/
#define RTC_CNTL_WDT_INT_CLR    (1<<3)
#define RTC_CNTL_WDT_INT_CLR_M  (1<<3)
#define RTC_CNTL_WDT_INT_CLR_V  0x1
#define RTC_CNTL_WDT_INT_CLR_S  3
/* RTC_CNTL_SDIO_IDLE_INT_CLR : WO ;bitpos:[2] ;default: 1'b0 ; */
/*description: Clear SDIO idle interrupt state.*/
#define RTC_CNTL_SDIO_IDLE_INT_CLR    (1<<2)
#define RTC_CNTL_SDIO_IDLE_INT_CLR_M  (1<<2)
#define RTC_CNTL_SDIO_IDLE_INT_CLR_V  0x1
#define RTC_CNTL_SDIO_IDLE_INT_CLR_S  2
/* RTC_CNTL_SLP_REJECT_INT_CLR : WO ;bitpos:[1] ;default: 1'b0 ; */
/*description: Clear sleep reject interrupt state.*/
#define RTC_CNTL_SLP_REJECT_INT_CLR    (1<<1)
#define RTC_CNTL_SLP_REJECT_INT_CLR_M  (1<<1)
#define RTC_CNTL_SLP_REJECT_INT_CLR_V  0x1
#define RTC_CNTL_SLP_REJECT_INT_CLR_S  1
/* RTC_CNTL_SLP_WAKEUP_INT_CLR : WO ;bitpos:[0] ;default: 1'b0 ; */
/*description: Clear sleep wakeup interrupt state.*/
#define RTC_CNTL_SLP_WAKEUP_INT_CLR    (1<<0)
#define RTC_CNTL_SLP_WAKEUP_INT_CLR_M  (1<<0)
#define RTC_CNTL_SLP_WAKEUP_INT_CLR_V  0x1
#define RTC_CNTL_SLP_WAKEUP_INT_CLR_S  0

#define RTC_CNTL_STORE0_REG          (0x60008000 + 0x50)
/* RTC_CNTL_SCRATCH0 : R/W ;bitpos:[31:0] ;default: 0 ; */
/*description: .*/
#define RTC_CNTL_SCRATCH0    0xFFFFFFFF
#define RTC_CNTL_SCRATCH0_M  ((RTC_CNTL_SCRATCH0_V)<<(RTC_CNTL_SCRATCH0_S))
#define RTC_CNTL_SCRATCH0_V  0xFFFFFFFF
#define RTC_CNTL_SCRATCH0_S  0

#define RTC_CNTL_STORE1_REG          (0x60008000 + 0x54)
/* RTC_CNTL_SCRATCH1 : R/W ;bitpos:[31:0] ;default: 0 ; */
/*description: .*/
#define RTC_CNTL_SCRATCH1    0xFFFFFFFF
#define RTC_CNTL_SCRATCH1_M  ((RTC_CNTL_SCRATCH1_V)<<(RTC_CNTL_SCRATCH1_S))
#define RTC_CNTL_SCRATCH1_V  0xFFFFFFFF
#define RTC_CNTL_SCRATCH1_S  0

#define RTC_CNTL_STORE2_REG          (0x60008000 + 0x58)
/* RTC_CNTL_SCRATCH2 : R/W ;bitpos:[31:0] ;default: 0 ; */
/*description: .*/
#define RTC_CNTL_SCRATCH2    0xFFFFFFFF
#define RTC_CNTL_SCRATCH2_M  ((RTC_CNTL_SCRATCH2_V)<<(RTC_CNTL_SCRATCH2_S))
#define RTC_CNTL_SCRATCH2_V  0xFFFFFFFF
#define RTC_CNTL_SCRATCH2_S  0

#define RTC_CNTL_STORE3_REG          (0x60008000 + 0x5C)
/* RTC_CNTL_SCRATCH3 : R/W ;bitpos:[31:0] ;default: 0 ; */
/*description: .*/
#define RTC_CNTL_SCRATCH3    0xFFFFFFFF
#define RTC_CNTL_SCRATCH3_M  ((RTC_CNTL_SCRATCH3_V)<<(RTC_CNTL_SCRATCH3_S))
#define RTC_CNTL_SCRATCH3_V  0xFFFFFFFF
#define RTC_CNTL_SCRATCH3_S  0

#define RTC_CNTL_EXT_XTL_CONF_REG          (0x60008000 + 0x60)
/* RTC_CNTL_XTL_EXT_CTR_EN : R/W ;bitpos:[31] ;default: 1'b0 ; */
/*description: .*/
#define RTC_CNTL_XTL_EXT_CTR_EN    (1<<31)
#define RTC_CNTL_XTL_EXT_CTR_EN_M  (1<<31)
#define RTC_CNTL_XTL_EXT_CTR_EN_V  0x1
#define RTC_CNTL_XTL_EXT_CTR_EN_S  31
/* RTC_CNTL_XTL_EXT_CTR_LV : R/W ;bitpos:[30] ;default: 1'b0 ; */
/*description: 0: power down XTAL at high level.*/
#define RTC_CNTL_XTL_EXT_CTR_LV    (1<<30)
#define RTC_CNTL_XTL_EXT_CTR_LV_M  (1<<30)
#define RTC_CNTL_XTL_EXT_CTR_LV_V  0x1
#define RTC_CNTL_XTL_EXT_CTR_LV_S  30
/* RTC_CNTL_XTAL32K_GPIO_SEL : R/W ;bitpos:[23] ;default: 1'b0 ; */
/*description: XTAL_32K sel. 0: external XTAL_32K.*/
#define RTC_CNTL_XTAL32K_GPIO_SEL    (1<<23)
#define RTC_CNTL_XTAL32K_GPIO_SEL_M  (1<<23)
#define RTC_CNTL_XTAL32K_GPIO_SEL_V  0x1
#define RTC_CNTL_XTAL32K_GPIO_SEL_S  23
/* RTC_CNTL_WDT_STATE : RO ;bitpos:[22:20] ;default: 3'h0 ; */
/*description: state of 32k_wdt.*/
#define RTC_CNTL_WDT_STATE    0x00000007
#define RTC_CNTL_WDT_STATE_M  ((RTC_CNTL_WDT_STATE_V)<<(RTC_CNTL_WDT_STATE_S))
#define RTC_CNTL_WDT_STATE_V  0x7
#define RTC_CNTL_WDT_STATE_S  20
/* RTC_CNTL_DAC_XTAL_32K : R/W ;bitpos:[19:17] ;default: 3'd3 ; */
/*description: DAC_XTAL_32K.*/
#define RTC_CNTL_DAC_XTAL_32K    0x00000007
#define RTC_CNTL_DAC_XTAL_32K_M  ((RTC_CNTL_DAC_XTAL_32K_V)<<(RTC_CNTL_DAC_XTAL_32K_S))
#define RTC_CNTL_DAC_XTAL_32K_V  0x7
#define RTC_CNTL_DAC_XTAL_32K_S  17
/* RTC_CNTL_XPD_XTAL_32K : R/W ;bitpos:[16] ;default: 1'd0 ; */
/*description: XPD_XTAL_32K.*/
#define RTC_CNTL_XPD_XTAL_32K    (1<<16)
#define RTC_CNTL_XPD_XTAL_32K_M  (1<<16)
#define RTC_CNTL_XPD_XTAL_32K_V  0x1
#define RTC_CNTL_XPD_XTAL_32K_S  16
/* RTC_CNTL_DRES_XTAL_32K : R/W ;bitpos:[15:13] ;default: 3'd3 ; */
/*description: DRES_XTAL_32K.*/
#define RTC_CNTL_DRES_XTAL_32K    0x00000007
#define RTC_CNTL_DRES_XTAL_32K_M  ((RTC_CNTL_DRES_XTAL_32K_V)<<(RTC_CNTL_DRES_XTAL_32K_S))
#define RTC_CNTL_DRES_XTAL_32K_V  0x7
#define RTC_CNTL_DRES_XTAL_32K_S  13
/* RTC_CNTL_DGM_XTAL_32K : R/W ;bitpos:[12:10] ;default: 3'd3 ; */
/*description: xtal_32k gm control.*/
#define RTC_CNTL_DGM_XTAL_32K    0x00000007
#define RTC_CNTL_DGM_XTAL_32K_M  ((RTC_CNTL_DGM_XTAL_32K_V)<<(RTC_CNTL_DGM_XTAL_32K_S))
#define RTC_CNTL_DGM_XTAL_32K_V  0x7
#define RTC_CNTL_DGM_XTAL_32K_S  10
/* RTC_CNTL_DBUF_XTAL_32K : R/W ;bitpos:[9] ;default: 1'b0 ; */
/*description: 0: single-end buffer 1: differential buffer.*/
#define RTC_CNTL_DBUF_XTAL_32K    (1<<9)
#define RTC_CNTL_DBUF_XTAL_32K_M  (1<<9)
#define RTC_CNTL_DBUF_XTAL_32K_V  0x1
#define RTC_CNTL_DBUF_XTAL_32K_S  9
/* RTC_CNTL_ENCKINIT_XTAL_32K : R/W ;bitpos:[8] ;default: 1'b0 ; */
/*description: apply an internal clock to help xtal 32k to start.*/
#define RTC_CNTL_ENCKINIT_XTAL_32K    (1<<8)
#define RTC_CNTL_ENCKINIT_XTAL_32K_M  (1<<8)
#define RTC_CNTL_ENCKINIT_XTAL_32K_V  0x1
#define RTC_CNTL_ENCKINIT_XTAL_32K_S  8
/* RTC_CNTL_XTAL32K_XPD_FORCE : R/W ;bitpos:[7] ;default: 1'b1 ; */
/*description: Xtal 32k xpd control by sw or fsm.*/
#define RTC_CNTL_XTAL32K_XPD_FORCE    (1<<7)
#define RTC_CNTL_XTAL32K_XPD_FORCE_M  (1<<7)
#define RTC_CNTL_XTAL32K_XPD_FORCE_V  0x1
#define RTC_CNTL_XTAL32K_XPD_FORCE_S  7
/* RTC_CNTL_XTAL32K_AUTO_RETURN : R/W ;bitpos:[6] ;default: 1'b0 ; */
/*description: xtal 32k switch back xtal when xtal is restarted.*/
#define RTC_CNTL_XTAL32K_AUTO_RETURN    (1<<6)
#define RTC_CNTL_XTAL32K_AUTO_RETURN_M  (1<<6)
#define RTC_CNTL_XTAL32K_AUTO_RETURN_V  0x1
#define RTC_CNTL_XTAL32K_AUTO_RETURN_S  6
/* RTC_CNTL_XTAL32K_AUTO_RESTART : R/W ;bitpos:[5] ;default: 1'b0 ; */
/*description: xtal 32k restart xtal when xtal is dead.*/
#define RTC_CNTL_XTAL32K_AUTO_RESTART    (1<<5)
#define RTC_CNTL_XTAL32K_AUTO_RESTART_M  (1<<5)
#define RTC_CNTL_XTAL32K_AUTO_RESTART_V  0x1
#define RTC_CNTL_XTAL32K_AUTO_RESTART_S  5
/* RTC_CNTL_XTAL32K_AUTO_BACKUP : R/W ;bitpos:[4] ;default: 1'b0 ; */
/*description: xtal 32k switch to back up clock when xtal is dead.*/
#define RTC_CNTL_XTAL32K_AUTO_BACKUP    (1<<4)
#define RTC_CNTL_XTAL32K_AUTO_BACKUP_M  (1<<4)
#define RTC_CNTL_XTAL32K_AUTO_BACKUP_V  0x1
#define RTC_CNTL_XTAL32K_AUTO_BACKUP_S  4
/* RTC_CNTL_XTAL32K_EXT_CLK_FO : R/W ;bitpos:[3] ;default: 1'b0 ; */
/*description: xtal 32k external xtal clock force on.*/
#define RTC_CNTL_XTAL32K_EXT_CLK_FO    (1<<3)
#define RTC_CNTL_XTAL32K_EXT_CLK_FO_M  (1<<3)
#define RTC_CNTL_XTAL32K_EXT_CLK_FO_V  0x1
#define RTC_CNTL_XTAL32K_EXT_CLK_FO_S  3
/* RTC_CNTL_XTAL32K_WDT_RESET : R/W ;bitpos:[2] ;default: 1'b0 ; */
/*description: xtal 32k watch dog sw reset.*/
#define RTC_CNTL_XTAL32K_WDT_RESET    (1<<2)
#define RTC_CNTL_XTAL32K_WDT_RESET_M  (1<<2)
#define RTC_CNTL_XTAL32K_WDT_RESET_V  0x1
#define RTC_CNTL_XTAL32K_WDT_RESET_S  2
/* RTC_CNTL_XTAL32K_WDT_CLK_FO : R/W ;bitpos:[1] ;default: 1'b0 ; */
/*description: xtal 32k watch dog clock force on.*/
#define RTC_CNTL_XTAL32K_WDT_CLK_FO    (1<<1)
#define RTC_CNTL_XTAL32K_WDT_CLK_FO_M  (1<<1)
#define RTC_CNTL_XTAL32K_WDT_CLK_FO_V  0x1
#define RTC_CNTL_XTAL32K_WDT_CLK_FO_S  1
/* RTC_CNTL_XTAL32K_WDT_EN : R/W ;bitpos:[0] ;default: 1'b0 ; */
/*description: xtal 32k watch dog enable.*/
#define RTC_CNTL_XTAL32K_WDT_EN    (1<<0)
#define RTC_CNTL_XTAL32K_WDT_EN_M  (1<<0)
#define RTC_CNTL_XTAL32K_WDT_EN_V  0x1
#define RTC_CNTL_XTAL32K_WDT_EN_S  0

#define RTC_CNTL_EXT_WAKEUP_CONF_REG          (0x60008000 + 0x64)
/* RTC_CNTL_EXT_WAKEUP1_LV : R/W ;bitpos:[31] ;default: 1'b0 ; */
/*description: .*/
#define RTC_CNTL_EXT_WAKEUP1_LV    (1<<31)
#define RTC_CNTL_EXT_WAKEUP1_LV_M  (1<<31)
#define RTC_CNTL_EXT_WAKEUP1_LV_V  0x1
#define RTC_CNTL_EXT_WAKEUP1_LV_S  31
/* RTC_CNTL_EXT_WAKEUP0_LV : R/W ;bitpos:[30] ;default: 1'b0 ; */
/*description: 0: external wakeup at low level.*/
#define RTC_CNTL_EXT_WAKEUP0_LV    (1<<30)
#define RTC_CNTL_EXT_WAKEUP0_LV_M  (1<<30)
#define RTC_CNTL_EXT_WAKEUP0_LV_V  0x1
#define RTC_CNTL_EXT_WAKEUP0_LV_S  30
/* RTC_CNTL_GPIO_WAKEUP_FILTER : R/W ;bitpos:[29] ;default: 1'd0 ; */
/*description: enable filter for gpio wakeup event.*/
#define RTC_CNTL_GPIO_WAKEUP_FILTER    (1<<29)
#define RTC_CNTL_GPIO_WAKEUP_FILTER_M  (1<<29)
#define RTC_CNTL_GPIO_WAKEUP_FILTER_V  0x1
#define RTC_CNTL_GPIO_WAKEUP_FILTER_S  29

#define RTC_CNTL_SLP_REJECT_CONF_REG          (0x60008000 + 0x68)
/* RTC_CNTL_DEEP_SLP_REJECT_EN : R/W ;bitpos:[31] ;default: 1'b0 ; */
/*description: enable reject for deep sleep.*/
#define RTC_CNTL_DEEP_SLP_REJECT_EN    (1<<31)
#define RTC_CNTL_DEEP_SLP_REJECT_EN_M  (1<<31)
#define RTC_CNTL_DEEP_SLP_REJECT_EN_V  0x1
#define RTC_CNTL_DEEP_SLP_REJECT_EN_S  31
/* RTC_CNTL_LIGHT_SLP_REJECT_EN : R/W ;bitpos:[30] ;default: 1'b0 ; */
/*description: enable reject for light sleep.*/
#define RTC_CNTL_LIGHT_SLP_REJECT_EN    (1<<30)
#define RTC_CNTL_LIGHT_SLP_REJECT_EN_M  (1<<30)
#define RTC_CNTL_LIGHT_SLP_REJECT_EN_V  0x1
#define RTC_CNTL_LIGHT_SLP_REJECT_EN_S  30
/* RTC_CNTL_SLEEP_REJECT_ENA : R/W ;bitpos:[29:12] ;default: 17'd0 ; */
/*description: sleep reject enable.*/
#define RTC_CNTL_SLEEP_REJECT_ENA    0x0003FFFF
#define RTC_CNTL_SLEEP_REJECT_ENA_M  ((RTC_CNTL_SLEEP_REJECT_ENA_V)<<(RTC_CNTL_SLEEP_REJECT_ENA_S))
#define RTC_CNTL_SLEEP_REJECT_ENA_V  0x3FFFF
#define RTC_CNTL_SLEEP_REJECT_ENA_S  12

#define RTC_CNTL_CPU_PERIOD_CONF_REG          (0x60008000 + 0x6C)
/* RTC_CNTL_CPUPERIOD_SEL : R/W ;bitpos:[31:30] ;default: 2'b00 ; */
/*description: .*/
#define RTC_CNTL_CPUPERIOD_SEL    0x00000003
#define RTC_CNTL_CPUPERIOD_SEL_M  ((RTC_CNTL_CPUPERIOD_SEL_V)<<(RTC_CNTL_CPUPERIOD_SEL_S))
#define RTC_CNTL_CPUPERIOD_SEL_V  0x3
#define RTC_CNTL_CPUPERIOD_SEL_S  30
/* RTC_CNTL_CPUSEL_CONF : R/W ;bitpos:[29] ;default: 1'b0 ; */
/*description: CPU sel option.*/
#define RTC_CNTL_CPUSEL_CONF    (1<<29)
#define RTC_CNTL_CPUSEL_CONF_M  (1<<29)
#define RTC_CNTL_CPUSEL_CONF_V  0x1
#define RTC_CNTL_CPUSEL_CONF_S  29

#define RTC_CNTL_SDIO_ACT_CONF_REG          (0x60008000 + 0x70)
/* RTC_CNTL_SDIO_ACT_DNUM : R/W ;bitpos:[31:22] ;default: 10'b0 ; */
/*description: .*/
#define RTC_CNTL_SDIO_ACT_DNUM    0x000003FF
#define RTC_CNTL_SDIO_ACT_DNUM_M  ((RTC_CNTL_SDIO_ACT_DNUM_V)<<(RTC_CNTL_SDIO_ACT_DNUM_S))
#define RTC_CNTL_SDIO_ACT_DNUM_V  0x3FF
#define RTC_CNTL_SDIO_ACT_DNUM_S  22

#define RTC_CNTL_CLK_CONF_REG          (0x60008000 + 0x74)
/* RTC_CNTL_ANA_CLK_RTC_SEL : R/W ;bitpos:[31:30] ;default: 2'd0 ; */
/*description: .*/
#define RTC_CNTL_ANA_CLK_RTC_SEL    0x00000003
#define RTC_CNTL_ANA_CLK_RTC_SEL_M  ((RTC_CNTL_ANA_CLK_RTC_SEL_V)<<(RTC_CNTL_ANA_CLK_RTC_SEL_S))
#define RTC_CNTL_ANA_CLK_RTC_SEL_V  0x3
#define RTC_CNTL_ANA_CLK_RTC_SEL_S  30
/* RTC_CNTL_FAST_CLK_RTC_SEL : R/W ;bitpos:[29] ;default: 1'b0 ; */
/*description: fast_clk_rtc sel. 0: XTAL div 4.*/
#define RTC_CNTL_FAST_CLK_RTC_SEL    (1<<29)
#define RTC_CNTL_FAST_CLK_RTC_SEL_M  (1<<29)
#define RTC_CNTL_FAST_CLK_RTC_SEL_V  0x1
#define RTC_CNTL_FAST_CLK_RTC_SEL_S  29
/* RTC_CNTL_XTAL_GLOBAL_FORCE_NOGATING : R/W ;bitpos:[28] ;default: 1'b1 ; */
/*description: .*/
#define RTC_CNTL_XTAL_GLOBAL_FORCE_NOGATING    (1<<28)
#define RTC_CNTL_XTAL_GLOBAL_FORCE_NOGATING_M  (1<<28)
#define RTC_CNTL_XTAL_GLOBAL_FORCE_NOGATING_V  0x1
#define RTC_CNTL_XTAL_GLOBAL_FORCE_NOGATING_S  28
/* RTC_CNTL_XTAL_GLOBAL_FORCE_GATING : R/W ;bitpos:[27] ;default: 1'b0 ; */
/*description: .*/
#define RTC_CNTL_XTAL_GLOBAL_FORCE_GATING    (1<<27)
#define RTC_CNTL_XTAL_GLOBAL_FORCE_GATING_M  (1<<27)
#define RTC_CNTL_XTAL_GLOBAL_FORCE_GATING_V  0x1
#define RTC_CNTL_XTAL_GLOBAL_FORCE_GATING_S  27
/* RTC_CNTL_CK8M_FORCE_PU : R/W ;bitpos:[26] ;default: 1'd0 ; */
/*description: CK8M force power up.*/
#define RTC_CNTL_CK8M_FORCE_PU    (1<<26)
#define RTC_CNTL_CK8M_FORCE_PU_M  (1<<26)
#define RTC_CNTL_CK8M_FORCE_PU_V  0x1
#define RTC_CNTL_CK8M_FORCE_PU_S  26
/* RTC_CNTL_CK8M_FORCE_PD : R/W ;bitpos:[25] ;default: 1'd0 ; */
/*description: CK8M force power down.*/
#define RTC_CNTL_CK8M_FORCE_PD    (1<<25)
#define RTC_CNTL_CK8M_FORCE_PD_M  (1<<25)
#define RTC_CNTL_CK8M_FORCE_PD_V  0x1
#define RTC_CNTL_CK8M_FORCE_PD_S  25
/* RTC_CNTL_CK8M_DFREQ : R/W ;bitpos:[24:17] ;default: 8'd172 ; */
/*description: CK8M_DFREQ.*/
#define RTC_CNTL_CK8M_DFREQ    0x000000FF
#define RTC_CNTL_CK8M_DFREQ_M  ((RTC_CNTL_CK8M_DFREQ_V)<<(RTC_CNTL_CK8M_DFREQ_S))
#define RTC_CNTL_CK8M_DFREQ_V  0xFF
#define RTC_CNTL_CK8M_DFREQ_S  17
/* RTC_CNTL_CK8M_FORCE_NOGATING : R/W ;bitpos:[16] ;default: 1'd0 ; */
/*description: CK8M force no gating during sleep.*/
#define RTC_CNTL_CK8M_FORCE_NOGATING    (1<<16)
#define RTC_CNTL_CK8M_FORCE_NOGATING_M  (1<<16)
#define RTC_CNTL_CK8M_FORCE_NOGATING_V  0x1
#define RTC_CNTL_CK8M_FORCE_NOGATING_S  16
/* RTC_CNTL_XTAL_FORCE_NOGATING : R/W ;bitpos:[15] ;default: 1'd0 ; */
/*description: XTAL force no gating during sleep.*/
#define RTC_CNTL_XTAL_FORCE_NOGATING    (1<<15)
#define RTC_CNTL_XTAL_FORCE_NOGATING_M  (1<<15)
#define RTC_CNTL_XTAL_FORCE_NOGATING_V  0x1
#define RTC_CNTL_XTAL_FORCE_NOGATING_S  15
/* RTC_CNTL_CK8M_DIV_SEL : R/W ;bitpos:[14:12] ;default: 3'd3 ; */
/*description: divider = reg_ck8m_div_sel + 1.*/
#define RTC_CNTL_CK8M_DIV_SEL    0x00000007
#define RTC_CNTL_CK8M_DIV_SEL_M  ((RTC_CNTL_CK8M_DIV_SEL_V)<<(RTC_CNTL_CK8M_DIV_SEL_S))
#define RTC_CNTL_CK8M_DIV_SEL_V  0x7
#define RTC_CNTL_CK8M_DIV_SEL_S  12
/* RTC_CNTL_DIG_CLK8M_EN : R/W ;bitpos:[10] ;default: 1'd0 ; */
/*description: enable CK8M for digital core (no relationship with RTC core).*/
#define RTC_CNTL_DIG_CLK8M_EN    (1<<10)
#define RTC_CNTL_DIG_CLK8M_EN_M  (1<<10)
#define RTC_CNTL_DIG_CLK8M_EN_V  0x1
#define RTC_CNTL_DIG_CLK8M_EN_S  10
/* RTC_CNTL_DIG_CLK8M_D256_EN : R/W ;bitpos:[9] ;default: 1'd1 ; */
/*description: enable CK8M_D256_OUT for digital core (no relationship with RTC core).*/
#define RTC_CNTL_DIG_CLK8M_D256_EN    (1<<9)
#define RTC_CNTL_DIG_CLK8M_D256_EN_M  (1<<9)
#define RTC_CNTL_DIG_CLK8M_D256_EN_V  0x1
#define RTC_CNTL_DIG_CLK8M_D256_EN_S  9
/* RTC_CNTL_DIG_XTAL32K_EN : R/W ;bitpos:[8] ;default: 1'd0 ; */
/*description: enable CK_XTAL_32K for digital core (no relationship with RTC core).*/
#define RTC_CNTL_DIG_XTAL32K_EN    (1<<8)
#define RTC_CNTL_DIG_XTAL32K_EN_M  (1<<8)
#define RTC_CNTL_DIG_XTAL32K_EN_V  0x1
#define RTC_CNTL_DIG_XTAL32K_EN_S  8
/* RTC_CNTL_ENB_CK8M_DIV : R/W ;bitpos:[7] ;default: 1'd0 ; */
/*description: 1: CK8M_D256_OUT is actually CK8M.*/
#define RTC_CNTL_ENB_CK8M_DIV    (1<<7)
#define RTC_CNTL_ENB_CK8M_DIV_M  (1<<7)
#define RTC_CNTL_ENB_CK8M_DIV_V  0x1
#define RTC_CNTL_ENB_CK8M_DIV_S  7
/* RTC_CNTL_ENB_CK8M : R/W ;bitpos:[6] ;default: 1'd0 ; */
/*description: disable CK8M and CK8M_D256_OUT.*/
#define RTC_CNTL_ENB_CK8M    (1<<6)
#define RTC_CNTL_ENB_CK8M_M  (1<<6)
#define RTC_CNTL_ENB_CK8M_V  0x1
#define RTC_CNTL_ENB_CK8M_S  6
/* RTC_CNTL_CK8M_DIV : R/W ;bitpos:[5:4] ;default: 2'b01 ; */
/*description: CK8M_D256_OUT divider. 00: div128.*/
#define RTC_CNTL_CK8M_DIV    0x00000003
#define RTC_CNTL_CK8M_DIV_M  ((RTC_CNTL_CK8M_DIV_V)<<(RTC_CNTL_CK8M_DIV_S))
#define RTC_CNTL_CK8M_DIV_V  0x3
#define RTC_CNTL_CK8M_DIV_S  4
/* RTC_CNTL_CK8M_DIV_SEL_VLD : R/W ;bitpos:[3] ;default: 1'b1 ; */
/*description: used to sync reg_ck8m_div_sel bus. Clear vld before set reg_ck8m_div_sel.*/
#define RTC_CNTL_CK8M_DIV_SEL_VLD    (1<<3)
#define RTC_CNTL_CK8M_DIV_SEL_VLD_M  (1<<3)
#define RTC_CNTL_CK8M_DIV_SEL_VLD_V  0x1
#define RTC_CNTL_CK8M_DIV_SEL_VLD_S  3
/* RTC_CNTL_EFUSE_CLK_FORCE_NOGATING : R/W ;bitpos:[2] ;default: 1'b1 ; */
/*description: .*/
#define RTC_CNTL_EFUSE_CLK_FORCE_NOGATING    (1<<2)
#define RTC_CNTL_EFUSE_CLK_FORCE_NOGATING_M  (1<<2)
#define RTC_CNTL_EFUSE_CLK_FORCE_NOGATING_V  0x1
#define RTC_CNTL_EFUSE_CLK_FORCE_NOGATING_S  2
/* RTC_CNTL_EFUSE_CLK_FORCE_GATING : R/W ;bitpos:[1] ;default: 1'b0 ; */
/*description: .*/
#define RTC_CNTL_EFUSE_CLK_FORCE_GATING    (1<<1)
#define RTC_CNTL_EFUSE_CLK_FORCE_GATING_M  (1<<1)
#define RTC_CNTL_EFUSE_CLK_FORCE_GATING_V  0x1
#define RTC_CNTL_EFUSE_CLK_FORCE_GATING_S  1

#define RTC_CNTL_SLOW_CLK_CONF_REG          (0x60008000 + 0x78)
/* RTC_CNTL_SLOW_CLK_NEXT_EDGE : R/W ;bitpos:[31] ;default: 1'b0 ; */
/*description: .*/
#define RTC_CNTL_SLOW_CLK_NEXT_EDGE    (1<<31)
#define RTC_CNTL_SLOW_CLK_NEXT_EDGE_M  (1<<31)
#define RTC_CNTL_SLOW_CLK_NEXT_EDGE_V  0x1
#define RTC_CNTL_SLOW_CLK_NEXT_EDGE_S  31
/* RTC_CNTL_ANA_CLK_DIV : R/W ;bitpos:[30:23] ;default: 8'd0 ; */
/*description: .*/
#define RTC_CNTL_ANA_CLK_DIV    0x000000FF
#define RTC_CNTL_ANA_CLK_DIV_M  ((RTC_CNTL_ANA_CLK_DIV_V)<<(RTC_CNTL_ANA_CLK_DIV_S))
#define RTC_CNTL_ANA_CLK_DIV_V  0xFF
#define RTC_CNTL_ANA_CLK_DIV_S  23
/* RTC_CNTL_ANA_CLK_DIV_VLD : R/W ;bitpos:[22] ;default: 1'b1 ; */
/*description: used to sync div bus. clear vld before set reg_rtc_ana_clk_div.*/
#define RTC_CNTL_ANA_CLK_DIV_VLD    (1<<22)
#define RTC_CNTL_ANA_CLK_DIV_VLD_M  (1<<22)
#define RTC_CNTL_ANA_CLK_DIV_VLD_V  0x1
#define RTC_CNTL_ANA_CLK_DIV_VLD_S  22

#define RTC_CNTL_SDIO_CONF_REG          (0x60008000 + 0x7C)
/* RTC_CNTL_XPD_SDIO_REG : R/W ;bitpos:[31] ;default: 1'd0 ; */
/*description: .*/
#define RTC_CNTL_XPD_SDIO_REG    (1<<31)
#define RTC_CNTL_XPD_SDIO_REG_M  (1<<31)
#define RTC_CNTL_XPD_SDIO_REG_V  0x1
#define RTC_CNTL_XPD_SDIO_REG_S  31
/* RTC_CNTL_DREFH_SDIO : R/W ;bitpos:[30:29] ;default: 2'b00 ; */
/*description: SW option for DREFH_SDIO. Only active when reg_sdio_force = 1.*/
#define RTC_CNTL_DREFH_SDIO    0x00000003
#define RTC_CNTL_DREFH_SDIO_M  ((RTC_CNTL_DREFH_SDIO_V)<<(RTC_CNTL_DREFH_SDIO_S))
#define RTC_CNTL_DREFH_SDIO_V  0x3
#define RTC_CNTL_DREFH_SDIO_S  29
/* RTC_CNTL_DREFM_SDIO : R/W ;bitpos:[28:27] ;default: 2'b01 ; */
/*description: SW option for DREFM_SDIO. Only active when reg_sdio_force = 1.*/
#define RTC_CNTL_DREFM_SDIO    0x00000003
#define RTC_CNTL_DREFM_SDIO_M  ((RTC_CNTL_DREFM_SDIO_V)<<(RTC_CNTL_DREFM_SDIO_S))
#define RTC_CNTL_DREFM_SDIO_V  0x3
#define RTC_CNTL_DREFM_SDIO_S  27
/* RTC_CNTL_DREFL_SDIO : R/W ;bitpos:[26:25] ;default: 2'b01 ; */
/*description: SW option for DREFL_SDIO. Only active when reg_sdio_force = 1.*/
#define RTC_CNTL_DREFL_SDIO    0x00000003
#define RTC_CNTL_DREFL_SDIO_M  ((RTC_CNTL_DREFL_SDIO_V)<<(RTC_CNTL_DREFL_SDIO_S))
#define RTC_CNTL_DREFL_SDIO_V  0x3
#define RTC_CNTL_DREFL_SDIO_S  25
/* RTC_CNTL_REG1P8_READY : RO ;bitpos:[24] ;default: 1'd0 ; */
/*description: read only register for REG1P8_READY.*/
#define RTC_CNTL_REG1P8_READY    (1<<24)
#define RTC_CNTL_REG1P8_READY_M  (1<<24)
#define RTC_CNTL_REG1P8_READY_V  0x1
#define RTC_CNTL_REG1P8_READY_S  24
/* RTC_CNTL_SDIO_TIEH : R/W ;bitpos:[23] ;default: 1'd1 ; */
/*description: SW option for SDIO_TIEH. Only active when reg_sdio_force = 1.*/
#define RTC_CNTL_SDIO_TIEH    (1<<23)
#define RTC_CNTL_SDIO_TIEH_M  (1<<23)
#define RTC_CNTL_SDIO_TIEH_V  0x1
#define RTC_CNTL_SDIO_TIEH_S  23
/* RTC_CNTL_SDIO_FORCE : R/W ;bitpos:[22] ;default: 1'd0 ; */
/*description: 1: use SW option to control SDIO_REG.*/
#define RTC_CNTL_SDIO_FORCE    (1<<22)
#define RTC_CNTL_SDIO_FORCE_M  (1<<22)
#define RTC_CNTL_SDIO_FORCE_V  0x1
#define RTC_CNTL_SDIO_FORCE_S  22
/* RTC_CNTL_SDIO_PD_EN : R/W ;bitpos:[21] ;default: 1'd1 ; */
/*description: power down SDIO_REG in sleep. Only active when reg_sdio_force = 0.*/
#define RTC_CNTL_SDIO_PD_EN    (1<<21)
#define RTC_CNTL_SDIO_PD_EN_M  (1<<21)
#define RTC_CNTL_SDIO_PD_EN_V  0x1
#define RTC_CNTL_SDIO_PD_EN_S  21
/* RTC_CNTL_SDIO_ENCURLIM : R/W ;bitpos:[20] ;default: 1'd1 ; */
/*description: enable current limit.*/
#define RTC_CNTL_SDIO_ENCURLIM    (1<<20)
#define RTC_CNTL_SDIO_ENCURLIM_M  (1<<20)
#define RTC_CNTL_SDIO_ENCURLIM_V  0x1
#define RTC_CNTL_SDIO_ENCURLIM_S  20
/* RTC_CNTL_SDIO_MODECURLIM : R/W ;bitpos:[19] ;default: 1'd0 ; */
/*description: select current limit mode.*/
#define RTC_CNTL_SDIO_MODECURLIM    (1<<19)
#define RTC_CNTL_SDIO_MODECURLIM_M  (1<<19)
#define RTC_CNTL_SDIO_MODECURLIM_V  0x1
#define RTC_CNTL_SDIO_MODECURLIM_S  19
/* RTC_CNTL_SDIO_DCURLIM : R/W ;bitpos:[18:16] ;default: 3'd0 ; */
/*description: tune current limit threshold when tieh = 0. About 800mA/(8+d).*/
#define RTC_CNTL_SDIO_DCURLIM    0x00000007
#define RTC_CNTL_SDIO_DCURLIM_M  ((RTC_CNTL_SDIO_DCURLIM_V)<<(RTC_CNTL_SDIO_DCURLIM_S))
#define RTC_CNTL_SDIO_DCURLIM_V  0x7
#define RTC_CNTL_SDIO_DCURLIM_S  16
/* RTC_CNTL_SDIO_EN_INITI : R/W ;bitpos:[15] ;default: 1'd1 ; */
/*description: 0 to set init[1:0]=0.*/
#define RTC_CNTL_SDIO_EN_INITI    (1<<15)
#define RTC_CNTL_SDIO_EN_INITI_M  (1<<15)
#define RTC_CNTL_SDIO_EN_INITI_V  0x1
#define RTC_CNTL_SDIO_EN_INITI_S  15
/* RTC_CNTL_SDIO_INITI : R/W ;bitpos:[14:13] ;default: 2'd1 ; */
/*description: add resistor from ldo output to ground. 0: no res.*/
#define RTC_CNTL_SDIO_INITI    0x00000003
#define RTC_CNTL_SDIO_INITI_M  ((RTC_CNTL_SDIO_INITI_V)<<(RTC_CNTL_SDIO_INITI_S))
#define RTC_CNTL_SDIO_INITI_V  0x3
#define RTC_CNTL_SDIO_INITI_S  13
/* RTC_CNTL_SDIO_DCAP : R/W ;bitpos:[12:11] ;default: 2'b11 ; */
/*description: ability to prevent LDO from overshoot.*/
#define RTC_CNTL_SDIO_DCAP    0x00000003
#define RTC_CNTL_SDIO_DCAP_M  ((RTC_CNTL_SDIO_DCAP_V)<<(RTC_CNTL_SDIO_DCAP_S))
#define RTC_CNTL_SDIO_DCAP_V  0x3
#define RTC_CNTL_SDIO_DCAP_S  11
/* RTC_CNTL_SDIO_DTHDRV : R/W ;bitpos:[10:9] ;default: 2'b11 ; */
/*description: Tieh = 1 mode drive ability. Initially set to 0 to limit charge current.*/
#define RTC_CNTL_SDIO_DTHDRV    0x00000003
#define RTC_CNTL_SDIO_DTHDRV_M  ((RTC_CNTL_SDIO_DTHDRV_V)<<(RTC_CNTL_SDIO_DTHDRV_S))
#define RTC_CNTL_SDIO_DTHDRV_V  0x3
#define RTC_CNTL_SDIO_DTHDRV_S  9
/* RTC_CNTL_SDIO_TIMER_TARGET : R/W ;bitpos:[7:0] ;default: 8'd10 ; */
/*description: timer count to apply reg_sdio_dcap after sdio power on.*/
#define RTC_CNTL_SDIO_TIMER_TARGET    0x000000FF
#define RTC_CNTL_SDIO_TIMER_TARGET_M  ((RTC_CNTL_SDIO_TIMER_TARGET_V)<<(RTC_CNTL_SDIO_TIMER_TARGET_S))
#define RTC_CNTL_SDIO_TIMER_TARGET_V  0xFF
#define RTC_CNTL_SDIO_TIMER_TARGET_S  0

#define RTC_CNTL_BIAS_CONF_REG          (0x60008000 + 0x80)
/* RTC_CNTL_DBG_ATTEN_WAKEUP : R/W ;bitpos:[29:26] ;default: 4'd0 ; */
/*description: .*/
#define RTC_CNTL_DBG_ATTEN_WAKEUP    0x0000000F
#define RTC_CNTL_DBG_ATTEN_WAKEUP_M  ((RTC_CNTL_DBG_ATTEN_WAKEUP_V)<<(RTC_CNTL_DBG_ATTEN_WAKEUP_S))
#define RTC_CNTL_DBG_ATTEN_WAKEUP_V  0xF
#define RTC_CNTL_DBG_ATTEN_WAKEUP_S  26
/* RTC_CNTL_DBG_ATTEN_MONITOR : R/W ;bitpos:[25:22] ;default: 4'd0 ; */
/*description: DBG_ATTEN when rtc in monitor state.*/
#define RTC_CNTL_DBG_ATTEN_MONITOR    0x0000000F
#define RTC_CNTL_DBG_ATTEN_MONITOR_M  ((RTC_CNTL_DBG_ATTEN_MONITOR_V)<<(RTC_CNTL_DBG_ATTEN_MONITOR_S))
#define RTC_CNTL_DBG_ATTEN_MONITOR_V  0xF
#define RTC_CNTL_DBG_ATTEN_MONITOR_S  22
/* RTC_CNTL_DBG_ATTEN_DEEP_SLP : R/W ;bitpos:[21:18] ;default: 4'd0 ; */
/*description: DBG_ATTEN when rtc in sleep state.*/
#define RTC_CNTL_DBG_ATTEN_DEEP_SLP    0x0000000F
#define RTC_CNTL_DBG_ATTEN_DEEP_SLP_M  ((RTC_CNTL_DBG_ATTEN_DEEP_SLP_V)<<(RTC_CNTL_DBG_ATTEN_DEEP_SLP_S))
#define RTC_CNTL_DBG_ATTEN_DEEP_SLP_V  0xF
#define RTC_CNTL_DBG_ATTEN_DEEP_SLP_S  18
/* RTC_CNTL_BIAS_SLEEP_MONITOR : R/W ;bitpos:[17] ;default: 1'b0 ; */
/*description: bias_sleep when rtc in monitor state.*/
#define RTC_CNTL_BIAS_SLEEP_MONITOR    (1<<17)
#define RTC_CNTL_BIAS_SLEEP_MONITOR_M  (1<<17)
#define RTC_CNTL_BIAS_SLEEP_MONITOR_V  0x1
#define RTC_CNTL_BIAS_SLEEP_MONITOR_S  17
/* RTC_CNTL_BIAS_SLEEP_DEEP_SLP : R/W ;bitpos:[16] ;default: 1'b1 ; */
/*description: bias_sleep when rtc in sleep_state.*/
#define RTC_CNTL_BIAS_SLEEP_DEEP_SLP    (1<<16)
#define RTC_CNTL_BIAS_SLEEP_DEEP_SLP_M  (1<<16)
#define RTC_CNTL_BIAS_SLEEP_DEEP_SLP_V  0x1
#define RTC_CNTL_BIAS_SLEEP_DEEP_SLP_S  16
/* RTC_CNTL_PD_CUR_MONITOR : R/W ;bitpos:[15] ;default: 1'b0 ; */
/*description: xpd cur when rtc in monitor state.*/
#define RTC_CNTL_PD_CUR_MONITOR    (1<<15)
#define RTC_CNTL_PD_CUR_MONITOR_M  (1<<15)
#define RTC_CNTL_PD_CUR_MONITOR_V  0x1
#define RTC_CNTL_PD_CUR_MONITOR_S  15
/* RTC_CNTL_PD_CUR_DEEP_SLP : R/W ;bitpos:[14] ;default: 1'b0 ; */
/*description: xpd cur when rtc in sleep_state.*/
#define RTC_CNTL_PD_CUR_DEEP_SLP    (1<<14)
#define RTC_CNTL_PD_CUR_DEEP_SLP_M  (1<<14)
#define RTC_CNTL_PD_CUR_DEEP_SLP_V  0x1
#define RTC_CNTL_PD_CUR_DEEP_SLP_S  14
/* RTC_CNTL_BIAS_BUF_MONITOR : R/W ;bitpos:[13] ;default: 1'b0 ; */
/*description: .*/
#define RTC_CNTL_BIAS_BUF_MONITOR    (1<<13)
#define RTC_CNTL_BIAS_BUF_MONITOR_M  (1<<13)
#define RTC_CNTL_BIAS_BUF_MONITOR_V  0x1
#define RTC_CNTL_BIAS_BUF_MONITOR_S  13
/* RTC_CNTL_BIAS_BUF_DEEP_SLP : R/W ;bitpos:[12] ;default: 1'b0 ; */
/*description: .*/
#define RTC_CNTL_BIAS_BUF_DEEP_SLP    (1<<12)
#define RTC_CNTL_BIAS_BUF_DEEP_SLP_M  (1<<12)
#define RTC_CNTL_BIAS_BUF_DEEP_SLP_V  0x1
#define RTC_CNTL_BIAS_BUF_DEEP_SLP_S  12
/* RTC_CNTL_BIAS_BUF_WAKE : R/W ;bitpos:[11] ;default: 1'b1 ; */
/*description: .*/
#define RTC_CNTL_BIAS_BUF_WAKE    (1<<11)
#define RTC_CNTL_BIAS_BUF_WAKE_M  (1<<11)
#define RTC_CNTL_BIAS_BUF_WAKE_V  0x1
#define RTC_CNTL_BIAS_BUF_WAKE_S  11
/* RTC_CNTL_BIAS_BUF_IDLE : R/W ;bitpos:[10] ;default: 1'b0 ; */
/*description: .*/
#define RTC_CNTL_BIAS_BUF_IDLE    (1<<10)
#define RTC_CNTL_BIAS_BUF_IDLE_M  (1<<10)
#define RTC_CNTL_BIAS_BUF_IDLE_V  0x1
#define RTC_CNTL_BIAS_BUF_IDLE_S  10

#define RTC_CNTL_REG          (0x60008000 + 0x84)
/* RTC_CNTL_REGULATOR_FORCE_PU : R/W ;bitpos:[31] ;default: 1'd1 ; */
/*description: .*/
#define RTC_CNTL_REGULATOR_FORCE_PU    (1<<31)
#define RTC_CNTL_REGULATOR_FORCE_PU_M  (1<<31)
#define RTC_CNTL_REGULATOR_FORCE_PU_V  0x1
#define RTC_CNTL_REGULATOR_FORCE_PU_S  31
/* RTC_CNTL_REGULATOR_FORCE_PD : R/W ;bitpos:[30] ;default: 1'd0 ; */
/*description: RTC_REG force power down (for RTC_REG power down means decrease the voltage to 0
.8v or lower ).*/
#define RTC_CNTL_REGULATOR_FORCE_PD    (1<<30)
#define RTC_CNTL_REGULATOR_FORCE_PD_M  (1<<30)
#define RTC_CNTL_REGULATOR_FORCE_PD_V  0x1
#define RTC_CNTL_REGULATOR_FORCE_PD_S  30
/* RTC_CNTL_DBOOST_FORCE_PU : R/W ;bitpos:[29] ;default: 1'd1 ; */
/*description: RTC_DBOOST force power up.*/
#define RTC_CNTL_DBOOST_FORCE_PU    (1<<29)
#define RTC_CNTL_DBOOST_FORCE_PU_M  (1<<29)
#define RTC_CNTL_DBOOST_FORCE_PU_V  0x1
#define RTC_CNTL_DBOOST_FORCE_PU_S  29
/* RTC_CNTL_DBOOST_FORCE_PD : R/W ;bitpos:[28] ;default: 1'd0 ; */
/*description: RTC_DBOOST force power down.*/
#define RTC_CNTL_DBOOST_FORCE_PD    (1<<28)
#define RTC_CNTL_DBOOST_FORCE_PD_M  (1<<28)
#define RTC_CNTL_DBOOST_FORCE_PD_V  0x1
#define RTC_CNTL_DBOOST_FORCE_PD_S  28
/* Approximate mapping of voltages to RTC_CNTL_DBIAS_WAK, RTC_CNTL_DBIAS_SLP,
 * RTC_CNTL_DIG_DBIAS_WAK, RTC_CNTL_DIG_DBIAS_SLP values.
 * Valid if RTC_CNTL_DBG_ATTEN is 0.
 */
#define RTC_CNTL_DIG_DBIAS_0V85  0
#define RTC_CNTL_DIG_DBIAS_0V90  1
#define RTC_CNTL_DIG_DBIAS_0V95  2
#define RTC_CNTL_DIG_DBIAS_1V00  3
#define RTC_CNTL_DIG_DBIAS_1V05  4
#define RTC_CNTL_DIG_DBIAS_1V10  5
#define RTC_CNTL_DIG_DBIAS_1V15  6
#define RTC_CNTL_DIG_DBIAS_1V20  7


/* RTC_CNTL_SCK_DCAP : R/W ;bitpos:[21:14] ;default: 8'd0 ; */
/*description: SCK_DCAP.*/
#define RTC_CNTL_SCK_DCAP    0x000000FF
#define RTC_CNTL_SCK_DCAP_M  ((RTC_CNTL_SCK_DCAP_V)<<(RTC_CNTL_SCK_DCAP_S))
#define RTC_CNTL_SCK_DCAP_V  0xFF
#define RTC_CNTL_SCK_DCAP_S  14
/* RTC_CNTL_DIG_CAL_EN : R/W ;bitpos:[7] ;default: 1'b0 ; */
/*description: .*/
#define RTC_CNTL_DIG_CAL_EN    (1<<7)
#define RTC_CNTL_DIG_CAL_EN_M  (1<<7)
#define RTC_CNTL_DIG_CAL_EN_V  0x1
#define RTC_CNTL_DIG_CAL_EN_S  7

#define RTC_CNTL_PWC_REG          (0x60008000 + 0x88)
/* RTC_CNTL_PAD_FORCE_HOLD : R/W ;bitpos:[21] ;default: 1'd0 ; */
/*description: rtc pad force hold.*/
#define RTC_CNTL_PAD_FORCE_HOLD    (1<<21)
#define RTC_CNTL_PAD_FORCE_HOLD_M  (1<<21)
#define RTC_CNTL_PAD_FORCE_HOLD_V  0x1
#define RTC_CNTL_PAD_FORCE_HOLD_S  21
/* RTC_CNTL_PD_EN : R/W ;bitpos:[20] ;default: 1'd0 ; */
/*description: enable power down rtc_peri in sleep .*/
#define RTC_CNTL_PD_EN    (1<<20)
#define RTC_CNTL_PD_EN_M  (1<<20)
#define RTC_CNTL_PD_EN_V  0x1
#define RTC_CNTL_PD_EN_S  20
/* RTC_CNTL_FORCE_PU : R/W ;bitpos:[19] ;default: 1'd0 ; */
/*description: rtc_peri force power up.*/
#define RTC_CNTL_FORCE_PU    (1<<19)
#define RTC_CNTL_FORCE_PU_M  (1<<19)
#define RTC_CNTL_FORCE_PU_V  0x1
#define RTC_CNTL_FORCE_PU_S  19
/* RTC_CNTL_FORCE_PD : R/W ;bitpos:[18] ;default: 1'b0 ; */
/*description: rtc_peri force power down.*/
#define RTC_CNTL_FORCE_PD    (1<<18)
#define RTC_CNTL_FORCE_PD_M  (1<<18)
#define RTC_CNTL_FORCE_PD_V  0x1
#define RTC_CNTL_FORCE_PD_S  18
/* RTC_CNTL_SLOWMEM_FORCE_LPU : R/W ;bitpos:[11] ;default: 1'b1 ; */
/*description: RTC memory force no PD.*/
#define RTC_CNTL_SLOWMEM_FORCE_LPU    (1<<11)
#define RTC_CNTL_SLOWMEM_FORCE_LPU_M  (1<<11)
#define RTC_CNTL_SLOWMEM_FORCE_LPU_V  0x1
#define RTC_CNTL_SLOWMEM_FORCE_LPU_S  11
/* RTC_CNTL_SLOWMEM_FORCE_LPD : R/W ;bitpos:[10] ;default: 1'b0 ; */
/*description: RTC memory force PD.*/
#define RTC_CNTL_SLOWMEM_FORCE_LPD    (1<<10)
#define RTC_CNTL_SLOWMEM_FORCE_LPD_M  (1<<10)
#define RTC_CNTL_SLOWMEM_FORCE_LPD_V  0x1
#define RTC_CNTL_SLOWMEM_FORCE_LPD_S  10
/* RTC_CNTL_SLOWMEM_FOLW_CPU : R/W ;bitpos:[9] ;default: 1'b0 ; */
/*description: 1: RTC memory  PD following CPU.*/
#define RTC_CNTL_SLOWMEM_FOLW_CPU    (1<<9)
#define RTC_CNTL_SLOWMEM_FOLW_CPU_M  (1<<9)
#define RTC_CNTL_SLOWMEM_FOLW_CPU_V  0x1
#define RTC_CNTL_SLOWMEM_FOLW_CPU_S  9
/* RTC_CNTL_FASTMEM_FORCE_LPU : R/W ;bitpos:[8] ;default: 1'b1 ; */
/*description: Fast RTC memory force no PD.*/
#define RTC_CNTL_FASTMEM_FORCE_LPU    (1<<8)
#define RTC_CNTL_FASTMEM_FORCE_LPU_M  (1<<8)
#define RTC_CNTL_FASTMEM_FORCE_LPU_V  0x1
#define RTC_CNTL_FASTMEM_FORCE_LPU_S  8
/* RTC_CNTL_FASTMEM_FORCE_LPD : R/W ;bitpos:[7] ;default: 1'b0 ; */
/*description: Fast RTC memory force PD.*/
#define RTC_CNTL_FASTMEM_FORCE_LPD    (1<<7)
#define RTC_CNTL_FASTMEM_FORCE_LPD_M  (1<<7)
#define RTC_CNTL_FASTMEM_FORCE_LPD_V  0x1
#define RTC_CNTL_FASTMEM_FORCE_LPD_S  7
/* RTC_CNTL_FASTMEM_FOLW_CPU : R/W ;bitpos:[6] ;default: 1'b0 ; */
/*description: 1: Fast RTC memory PD following CPU.*/
#define RTC_CNTL_FASTMEM_FOLW_CPU    (1<<6)
#define RTC_CNTL_FASTMEM_FOLW_CPU_M  (1<<6)
#define RTC_CNTL_FASTMEM_FOLW_CPU_V  0x1
#define RTC_CNTL_FASTMEM_FOLW_CPU_S  6
/* RTC_CNTL_FORCE_NOISO : R/W ;bitpos:[5] ;default: 1'd1 ; */
/*description: rtc_peri force no ISO.*/
#define RTC_CNTL_FORCE_NOISO    (1<<5)
#define RTC_CNTL_FORCE_NOISO_M  (1<<5)
#define RTC_CNTL_FORCE_NOISO_V  0x1
#define RTC_CNTL_FORCE_NOISO_S  5
/* RTC_CNTL_FORCE_ISO : R/W ;bitpos:[4] ;default: 1'd0 ; */
/*description: rtc_peri force ISO.*/
#define RTC_CNTL_FORCE_ISO    (1<<4)
#define RTC_CNTL_FORCE_ISO_M  (1<<4)
#define RTC_CNTL_FORCE_ISO_V  0x1
#define RTC_CNTL_FORCE_ISO_S  4
/* RTC_CNTL_SLOWMEM_FORCE_ISO : R/W ;bitpos:[3] ;default: 1'b0 ; */
/*description: RTC memory force ISO.*/
#define RTC_CNTL_SLOWMEM_FORCE_ISO    (1<<3)
#define RTC_CNTL_SLOWMEM_FORCE_ISO_M  (1<<3)
#define RTC_CNTL_SLOWMEM_FORCE_ISO_V  0x1
#define RTC_CNTL_SLOWMEM_FORCE_ISO_S  3
/* RTC_CNTL_SLOWMEM_FORCE_NOISO : R/W ;bitpos:[2] ;default: 1'b1 ; */
/*description: RTC memory force no ISO.*/
#define RTC_CNTL_SLOWMEM_FORCE_NOISO    (1<<2)
#define RTC_CNTL_SLOWMEM_FORCE_NOISO_M  (1<<2)
#define RTC_CNTL_SLOWMEM_FORCE_NOISO_V  0x1
#define RTC_CNTL_SLOWMEM_FORCE_NOISO_S  2
/* RTC_CNTL_FASTMEM_FORCE_ISO : R/W ;bitpos:[1] ;default: 1'b0 ; */
/*description: Fast RTC memory force ISO.*/
#define RTC_CNTL_FASTMEM_FORCE_ISO    (1<<1)
#define RTC_CNTL_FASTMEM_FORCE_ISO_M  (1<<1)
#define RTC_CNTL_FASTMEM_FORCE_ISO_V  0x1
#define RTC_CNTL_FASTMEM_FORCE_ISO_S  1
/* RTC_CNTL_FASTMEM_FORCE_NOISO : R/W ;bitpos:[0] ;default: 1'b1 ; */
/*description: Fast RTC memory force no ISO.*/
#define RTC_CNTL_FASTMEM_FORCE_NOISO    (1<<0)
#define RTC_CNTL_FASTMEM_FORCE_NOISO_M  (1<<0)
#define RTC_CNTL_FASTMEM_FORCE_NOISO_V  0x1
#define RTC_CNTL_FASTMEM_FORCE_NOISO_S  0

#define RTC_CNTL_REGULATOR_DRV_CTRL_REG          (0x60008000 + 0x8C)
/* RTC_CNTL_DG_VDD_DRV_B_MONITOR : R/W ;bitpos:[27:20] ;default: 8'h0 ; */
/*description: .*/
#define RTC_CNTL_DG_VDD_DRV_B_MONITOR    0x000000FF
#define RTC_CNTL_DG_VDD_DRV_B_MONITOR_M  ((RTC_CNTL_DG_VDD_DRV_B_MONITOR_V)<<(RTC_CNTL_DG_VDD_DRV_B_MONITOR_S))
#define RTC_CNTL_DG_VDD_DRV_B_MONITOR_V  0xFF
#define RTC_CNTL_DG_VDD_DRV_B_MONITOR_S  20
/* RTC_CNTL_DG_VDD_DRV_B_SLP : R/W ;bitpos:[19:12] ;default: 8'h0 ; */
/*description: .*/
#define RTC_CNTL_DG_VDD_DRV_B_SLP    0x000000FF
#define RTC_CNTL_DG_VDD_DRV_B_SLP_M  ((RTC_CNTL_DG_VDD_DRV_B_SLP_V)<<(RTC_CNTL_DG_VDD_DRV_B_SLP_S))
#define RTC_CNTL_DG_VDD_DRV_B_SLP_V  0xFF
#define RTC_CNTL_DG_VDD_DRV_B_SLP_S  12
/* RTC_CNTL_REGULATOR_DRV_B_SLP : R/W ;bitpos:[11:6] ;default: 6'b0 ; */
/*description: .*/
#define RTC_CNTL_REGULATOR_DRV_B_SLP    0x0000003F
#define RTC_CNTL_REGULATOR_DRV_B_SLP_M  ((RTC_CNTL_REGULATOR_DRV_B_SLP_V)<<(RTC_CNTL_REGULATOR_DRV_B_SLP_S))
#define RTC_CNTL_REGULATOR_DRV_B_SLP_V  0x3F
#define RTC_CNTL_REGULATOR_DRV_B_SLP_S  6
/* RTC_CNTL_REGULATOR_DRV_B_MONITOR : R/W ;bitpos:[5:0] ;default: 6'b0 ; */
/*description: .*/
#define RTC_CNTL_REGULATOR_DRV_B_MONITOR    0x0000003F
#define RTC_CNTL_REGULATOR_DRV_B_MONITOR_M  ((RTC_CNTL_REGULATOR_DRV_B_MONITOR_V)<<(RTC_CNTL_REGULATOR_DRV_B_MONITOR_S))
#define RTC_CNTL_REGULATOR_DRV_B_MONITOR_V  0x3F
#define RTC_CNTL_REGULATOR_DRV_B_MONITOR_S  0

#define RTC_CNTL_DIG_PWC_REG          (0x60008000 + 0x90)
/* RTC_CNTL_DG_WRAP_PD_EN : R/W ;bitpos:[31] ;default: 0 ; */
/*description: .*/
#define RTC_CNTL_DG_WRAP_PD_EN    (1<<31)
#define RTC_CNTL_DG_WRAP_PD_EN_M  (1<<31)
#define RTC_CNTL_DG_WRAP_PD_EN_V  0x1
#define RTC_CNTL_DG_WRAP_PD_EN_S  31
/* RTC_CNTL_WIFI_PD_EN : R/W ;bitpos:[30] ;default: 0 ; */
/*description: enable power down wifi in sleep.*/
#define RTC_CNTL_WIFI_PD_EN    (1<<30)
#define RTC_CNTL_WIFI_PD_EN_M  (1<<30)
#define RTC_CNTL_WIFI_PD_EN_V  0x1
#define RTC_CNTL_WIFI_PD_EN_S  30
/* RTC_CNTL_CPU_TOP_PD_EN : R/W ;bitpos:[29] ;default: 0 ; */
/*description: enable power down internal SRAM 4 in sleep.*/
#define RTC_CNTL_CPU_TOP_PD_EN    (1<<29)
#define RTC_CNTL_CPU_TOP_PD_EN_M  (1<<29)
#define RTC_CNTL_CPU_TOP_PD_EN_V  0x1
#define RTC_CNTL_CPU_TOP_PD_EN_S  29
/* RTC_CNTL_DG_PERI_PD_EN : R/W ;bitpos:[28] ;default: 0 ; */
/*description: enable power down internal SRAM 3 in sleep.*/
#define RTC_CNTL_DG_PERI_PD_EN    (1<<28)
#define RTC_CNTL_DG_PERI_PD_EN_M  (1<<28)
#define RTC_CNTL_DG_PERI_PD_EN_V  0x1
#define RTC_CNTL_DG_PERI_PD_EN_S  28
/* RTC_CNTL_BT_PD_EN : R/W ;bitpos:[27] ;default: 0 ; */
/*description: enable power down internal SRAM 2 in sleep.*/
#define RTC_CNTL_BT_PD_EN    (1<<27)
#define RTC_CNTL_BT_PD_EN_M  (1<<27)
#define RTC_CNTL_BT_PD_EN_V  0x1
#define RTC_CNTL_BT_PD_EN_S  27
/* RTC_CNTL_CPU_TOP_FORCE_PU : R/W ;bitpos:[22] ;default: 1'd1 ; */
/*description: digital dcdc force power up.*/
#define RTC_CNTL_CPU_TOP_FORCE_PU    (1<<22)
#define RTC_CNTL_CPU_TOP_FORCE_PU_M  (1<<22)
#define RTC_CNTL_CPU_TOP_FORCE_PU_V  0x1
#define RTC_CNTL_CPU_TOP_FORCE_PU_S  22
/* RTC_CNTL_CPU_TOP_FORCE_PD : R/W ;bitpos:[21] ;default: 1'b0 ; */
/*description: digital dcdc force power down.*/
#define RTC_CNTL_CPU_TOP_FORCE_PD    (1<<21)
#define RTC_CNTL_CPU_TOP_FORCE_PD_M  (1<<21)
#define RTC_CNTL_CPU_TOP_FORCE_PD_V  0x1
#define RTC_CNTL_CPU_TOP_FORCE_PD_S  21
/* RTC_CNTL_DG_WRAP_FORCE_PU : R/W ;bitpos:[20] ;default: 1'd1 ; */
/*description: digital core force power up.*/
#define RTC_CNTL_DG_WRAP_FORCE_PU    (1<<20)
#define RTC_CNTL_DG_WRAP_FORCE_PU_M  (1<<20)
#define RTC_CNTL_DG_WRAP_FORCE_PU_V  0x1
#define RTC_CNTL_DG_WRAP_FORCE_PU_S  20
/* RTC_CNTL_DG_WRAP_FORCE_PD : R/W ;bitpos:[19] ;default: 1'b0 ; */
/*description: digital core force power down.*/
#define RTC_CNTL_DG_WRAP_FORCE_PD    (1<<19)
#define RTC_CNTL_DG_WRAP_FORCE_PD_M  (1<<19)
#define RTC_CNTL_DG_WRAP_FORCE_PD_V  0x1
#define RTC_CNTL_DG_WRAP_FORCE_PD_S  19
/* RTC_CNTL_WIFI_FORCE_PU : R/W ;bitpos:[18] ;default: 1'd1 ; */
/*description: wifi force power up.*/
#define RTC_CNTL_WIFI_FORCE_PU    (1<<18)
#define RTC_CNTL_WIFI_FORCE_PU_M  (1<<18)
#define RTC_CNTL_WIFI_FORCE_PU_V  0x1
#define RTC_CNTL_WIFI_FORCE_PU_S  18
/* RTC_CNTL_WIFI_FORCE_PD : R/W ;bitpos:[17] ;default: 1'b0 ; */
/*description: wifi force power down.*/
#define RTC_CNTL_WIFI_FORCE_PD    (1<<17)
#define RTC_CNTL_WIFI_FORCE_PD_M  (1<<17)
#define RTC_CNTL_WIFI_FORCE_PD_V  0x1
#define RTC_CNTL_WIFI_FORCE_PD_S  17
/* RTC_CNTL_DG_PERI_FORCE_PU : R/W ;bitpos:[14] ;default: 1'd1 ; */
/*description: internal SRAM 3 force power up.*/
#define RTC_CNTL_DG_PERI_FORCE_PU    (1<<14)
#define RTC_CNTL_DG_PERI_FORCE_PU_M  (1<<14)
#define RTC_CNTL_DG_PERI_FORCE_PU_V  0x1
#define RTC_CNTL_DG_PERI_FORCE_PU_S  14
/* RTC_CNTL_DG_PERI_FORCE_PD : R/W ;bitpos:[13] ;default: 1'b0 ; */
/*description: internal SRAM 3 force power down.*/
#define RTC_CNTL_DG_PERI_FORCE_PD    (1<<13)
#define RTC_CNTL_DG_PERI_FORCE_PD_M  (1<<13)
#define RTC_CNTL_DG_PERI_FORCE_PD_V  0x1
#define RTC_CNTL_DG_PERI_FORCE_PD_S  13
/* RTC_CNTL_BT_FORCE_PU : R/W ;bitpos:[12] ;default: 1'd1 ; */
/*description: internal SRAM 2 force power up.*/
#define RTC_CNTL_BT_FORCE_PU    (1<<12)
#define RTC_CNTL_BT_FORCE_PU_M  (1<<12)
#define RTC_CNTL_BT_FORCE_PU_V  0x1
#define RTC_CNTL_BT_FORCE_PU_S  12
/* RTC_CNTL_BT_FORCE_PD : R/W ;bitpos:[11] ;default: 1'b0 ; */
/*description: internal SRAM 2 force power down.*/
#define RTC_CNTL_BT_FORCE_PD    (1<<11)
#define RTC_CNTL_BT_FORCE_PD_M  (1<<11)
#define RTC_CNTL_BT_FORCE_PD_V  0x1
#define RTC_CNTL_BT_FORCE_PD_S  11
/* RTC_CNTL_LSLP_MEM_FORCE_PU : R/W ;bitpos:[4] ;default: 1'b1 ; */
/*description: memories in digital core force no PD in sleep.*/
#define RTC_CNTL_LSLP_MEM_FORCE_PU    (1<<4)
#define RTC_CNTL_LSLP_MEM_FORCE_PU_M  (1<<4)
#define RTC_CNTL_LSLP_MEM_FORCE_PU_V  0x1
#define RTC_CNTL_LSLP_MEM_FORCE_PU_S  4
/* RTC_CNTL_LSLP_MEM_FORCE_PD : R/W ;bitpos:[3] ;default: 1'b0 ; */
/*description: memories in digital core force PD in sleep.*/
#define RTC_CNTL_LSLP_MEM_FORCE_PD    (1<<3)
#define RTC_CNTL_LSLP_MEM_FORCE_PD_M  (1<<3)
#define RTC_CNTL_LSLP_MEM_FORCE_PD_V  0x1
#define RTC_CNTL_LSLP_MEM_FORCE_PD_S  3

#define RTC_CNTL_DIG_ISO_REG          (0x60008000 + 0x94)
/* RTC_CNTL_DG_WRAP_FORCE_NOISO : R/W ;bitpos:[31] ;default: 1'd1 ; */
/*description: .*/
#define RTC_CNTL_DG_WRAP_FORCE_NOISO    (1<<31)
#define RTC_CNTL_DG_WRAP_FORCE_NOISO_M  (1<<31)
#define RTC_CNTL_DG_WRAP_FORCE_NOISO_V  0x1
#define RTC_CNTL_DG_WRAP_FORCE_NOISO_S  31
/* RTC_CNTL_DG_WRAP_FORCE_ISO : R/W ;bitpos:[30] ;default: 1'd0 ; */
/*description: digital core force ISO.*/
#define RTC_CNTL_DG_WRAP_FORCE_ISO    (1<<30)
#define RTC_CNTL_DG_WRAP_FORCE_ISO_M  (1<<30)
#define RTC_CNTL_DG_WRAP_FORCE_ISO_V  0x1
#define RTC_CNTL_DG_WRAP_FORCE_ISO_S  30
/* RTC_CNTL_WIFI_FORCE_NOISO : R/W ;bitpos:[29] ;default: 1'd1 ; */
/*description: wifi force no ISO.*/
#define RTC_CNTL_WIFI_FORCE_NOISO    (1<<29)
#define RTC_CNTL_WIFI_FORCE_NOISO_M  (1<<29)
#define RTC_CNTL_WIFI_FORCE_NOISO_V  0x1
#define RTC_CNTL_WIFI_FORCE_NOISO_S  29
/* RTC_CNTL_WIFI_FORCE_ISO : R/W ;bitpos:[28] ;default: 1'd0 ; */
/*description: wifi force ISO.*/
#define RTC_CNTL_WIFI_FORCE_ISO    (1<<28)
#define RTC_CNTL_WIFI_FORCE_ISO_M  (1<<28)
#define RTC_CNTL_WIFI_FORCE_ISO_V  0x1
#define RTC_CNTL_WIFI_FORCE_ISO_S  28
/* RTC_CNTL_CPU_TOP_FORCE_NOISO : R/W ;bitpos:[27] ;default: 1'd1 ; */
/*description: internal SRAM 4 force no ISO.*/
#define RTC_CNTL_CPU_TOP_FORCE_NOISO    (1<<27)
#define RTC_CNTL_CPU_TOP_FORCE_NOISO_M  (1<<27)
#define RTC_CNTL_CPU_TOP_FORCE_NOISO_V  0x1
#define RTC_CNTL_CPU_TOP_FORCE_NOISO_S  27
/* RTC_CNTL_CPU_TOP_FORCE_ISO : R/W ;bitpos:[26] ;default: 1'd0 ; */
/*description: internal SRAM 4 force ISO.*/
#define RTC_CNTL_CPU_TOP_FORCE_ISO    (1<<26)
#define RTC_CNTL_CPU_TOP_FORCE_ISO_M  (1<<26)
#define RTC_CNTL_CPU_TOP_FORCE_ISO_V  0x1
#define RTC_CNTL_CPU_TOP_FORCE_ISO_S  26
/* RTC_CNTL_DG_PERI_FORCE_NOISO : R/W ;bitpos:[25] ;default: 1'd1 ; */
/*description: internal SRAM 3 force no ISO.*/
#define RTC_CNTL_DG_PERI_FORCE_NOISO    (1<<25)
#define RTC_CNTL_DG_PERI_FORCE_NOISO_M  (1<<25)
#define RTC_CNTL_DG_PERI_FORCE_NOISO_V  0x1
#define RTC_CNTL_DG_PERI_FORCE_NOISO_S  25
/* RTC_CNTL_DG_PERI_FORCE_ISO : R/W ;bitpos:[24] ;default: 1'd0 ; */
/*description: internal SRAM 3 force ISO.*/
#define RTC_CNTL_DG_PERI_FORCE_ISO    (1<<24)
#define RTC_CNTL_DG_PERI_FORCE_ISO_M  (1<<24)
#define RTC_CNTL_DG_PERI_FORCE_ISO_V  0x1
#define RTC_CNTL_DG_PERI_FORCE_ISO_S  24
/* RTC_CNTL_BT_FORCE_NOISO : R/W ;bitpos:[23] ;default: 1'd1 ; */
/*description: internal SRAM 2 force no ISO.*/
#define RTC_CNTL_BT_FORCE_NOISO    (1<<23)
#define RTC_CNTL_BT_FORCE_NOISO_M  (1<<23)
#define RTC_CNTL_BT_FORCE_NOISO_V  0x1
#define RTC_CNTL_BT_FORCE_NOISO_S  23
/* RTC_CNTL_BT_FORCE_ISO : R/W ;bitpos:[22] ;default: 1'd0 ; */
/*description: internal SRAM 2 force ISO.*/
#define RTC_CNTL_BT_FORCE_ISO    (1<<22)
#define RTC_CNTL_BT_FORCE_ISO_M  (1<<22)
#define RTC_CNTL_BT_FORCE_ISO_V  0x1
#define RTC_CNTL_BT_FORCE_ISO_S  22
/* RTC_CNTL_DG_PAD_FORCE_HOLD : R/W ;bitpos:[15] ;default: 1'd0 ; */
/*description: digital pad force hold.*/
#define RTC_CNTL_DG_PAD_FORCE_HOLD    (1<<15)
#define RTC_CNTL_DG_PAD_FORCE_HOLD_M  (1<<15)
#define RTC_CNTL_DG_PAD_FORCE_HOLD_V  0x1
#define RTC_CNTL_DG_PAD_FORCE_HOLD_S  15
/* RTC_CNTL_DG_PAD_FORCE_UNHOLD : R/W ;bitpos:[14] ;default: 1'd1 ; */
/*description: digital pad force un-hold.*/
#define RTC_CNTL_DG_PAD_FORCE_UNHOLD    (1<<14)
#define RTC_CNTL_DG_PAD_FORCE_UNHOLD_M  (1<<14)
#define RTC_CNTL_DG_PAD_FORCE_UNHOLD_V  0x1
#define RTC_CNTL_DG_PAD_FORCE_UNHOLD_S  14
/* RTC_CNTL_DG_PAD_FORCE_ISO : R/W ;bitpos:[13] ;default: 1'd0 ; */
/*description: digital pad force ISO.*/
#define RTC_CNTL_DG_PAD_FORCE_ISO    (1<<13)
#define RTC_CNTL_DG_PAD_FORCE_ISO_M  (1<<13)
#define RTC_CNTL_DG_PAD_FORCE_ISO_V  0x1
#define RTC_CNTL_DG_PAD_FORCE_ISO_S  13
/* RTC_CNTL_DG_PAD_FORCE_NOISO : R/W ;bitpos:[12] ;default: 1'd1 ; */
/*description: digital pad force no ISO.*/
#define RTC_CNTL_DG_PAD_FORCE_NOISO    (1<<12)
#define RTC_CNTL_DG_PAD_FORCE_NOISO_M  (1<<12)
#define RTC_CNTL_DG_PAD_FORCE_NOISO_V  0x1
#define RTC_CNTL_DG_PAD_FORCE_NOISO_S  12
/* RTC_CNTL_DG_PAD_AUTOHOLD_EN : R/W ;bitpos:[11] ;default: 1'd0 ; */
/*description: digital pad enable auto-hold.*/
#define RTC_CNTL_DG_PAD_AUTOHOLD_EN    (1<<11)
#define RTC_CNTL_DG_PAD_AUTOHOLD_EN_M  (1<<11)
#define RTC_CNTL_DG_PAD_AUTOHOLD_EN_V  0x1
#define RTC_CNTL_DG_PAD_AUTOHOLD_EN_S  11
/* RTC_CNTL_CLR_DG_PAD_AUTOHOLD : WO ;bitpos:[10] ;default: 1'd0 ; */
/*description: wtite only register to clear digital pad auto-hold.*/
#define RTC_CNTL_CLR_DG_PAD_AUTOHOLD    (1<<10)
#define RTC_CNTL_CLR_DG_PAD_AUTOHOLD_M  (1<<10)
#define RTC_CNTL_CLR_DG_PAD_AUTOHOLD_V  0x1
#define RTC_CNTL_CLR_DG_PAD_AUTOHOLD_S  10
/* RTC_CNTL_DG_PAD_AUTOHOLD : RO ;bitpos:[9] ;default: 1'd0 ; */
/*description: read only register to indicate digital pad auto-hold status.*/
#define RTC_CNTL_DG_PAD_AUTOHOLD    (1<<9)
#define RTC_CNTL_DG_PAD_AUTOHOLD_M  (1<<9)
#define RTC_CNTL_DG_PAD_AUTOHOLD_V  0x1
#define RTC_CNTL_DG_PAD_AUTOHOLD_S  9
/* RTC_CNTL_DIG_ISO_FORCE_ON : R/W ;bitpos:[8] ;default: 1'd0 ; */
/*description: .*/
#define RTC_CNTL_DIG_ISO_FORCE_ON    (1<<8)
#define RTC_CNTL_DIG_ISO_FORCE_ON_M  (1<<8)
#define RTC_CNTL_DIG_ISO_FORCE_ON_V  0x1
#define RTC_CNTL_DIG_ISO_FORCE_ON_S  8
/* RTC_CNTL_DIG_ISO_FORCE_OFF : R/W ;bitpos:[7] ;default: 1'd1 ; */
/*description: .*/
#define RTC_CNTL_DIG_ISO_FORCE_OFF    (1<<7)
#define RTC_CNTL_DIG_ISO_FORCE_OFF_M  (1<<7)
#define RTC_CNTL_DIG_ISO_FORCE_OFF_V  0x1
#define RTC_CNTL_DIG_ISO_FORCE_OFF_S  7

#define RTC_CNTL_WDTCONFIG0_REG          (0x60008000 + 0x98)
/* RTC_CNTL_WDT_EN : R/W ;bitpos:[31] ;default: 1'h0 ; */
/*description: .*/
#define RTC_CNTL_WDT_EN    (1<<31)
#define RTC_CNTL_WDT_EN_M  (1<<31)
#define RTC_CNTL_WDT_EN_V  0x1
#define RTC_CNTL_WDT_EN_S  31
/* RTC_CNTL_WDT_STG0 : R/W ;bitpos:[30:28] ;default: 3'h0 ; */
/*description: 1: interrupt stage en.*/
#define RTC_CNTL_WDT_STG0    0x00000007
#define RTC_CNTL_WDT_STG0_M  ((RTC_CNTL_WDT_STG0_V)<<(RTC_CNTL_WDT_STG0_S))
#define RTC_CNTL_WDT_STG0_V  0x7
#define RTC_CNTL_WDT_STG0_S  28
/* RTC_CNTL_WDT_STG1 : R/W ;bitpos:[27:25] ;default: 3'h0 ; */
/*description: 1: interrupt stage en.*/
#define RTC_CNTL_WDT_STG1    0x00000007
#define RTC_CNTL_WDT_STG1_M  ((RTC_CNTL_WDT_STG1_V)<<(RTC_CNTL_WDT_STG1_S))
#define RTC_CNTL_WDT_STG1_V  0x7
#define RTC_CNTL_WDT_STG1_S  25
/* RTC_CNTL_WDT_STG2 : R/W ;bitpos:[24:22] ;default: 3'h0 ; */
/*description: 1: interrupt stage en.*/
#define RTC_CNTL_WDT_STG2    0x00000007
#define RTC_CNTL_WDT_STG2_M  ((RTC_CNTL_WDT_STG2_V)<<(RTC_CNTL_WDT_STG2_S))
#define RTC_CNTL_WDT_STG2_V  0x7
#define RTC_CNTL_WDT_STG2_S  22
/* RTC_CNTL_WDT_STG3 : R/W ;bitpos:[21:19] ;default: 3'h0 ; */
/*description: 1: interrupt stage en.*/
#define RTC_CNTL_WDT_STG3    0x00000007
#define RTC_CNTL_WDT_STG3_M  ((RTC_CNTL_WDT_STG3_V)<<(RTC_CNTL_WDT_STG3_S))
#define RTC_CNTL_WDT_STG3_V  0x7
#define RTC_CNTL_WDT_STG3_S  19

/* RTC_CNTL_WDT_CPU_RESET_LENGTH : R/W ;bitpos:[18:16] ;default: 3'h1 ; */
/*description: CPU reset counter length.*/
#define RTC_CNTL_WDT_CPU_RESET_LENGTH    0x00000007
#define RTC_CNTL_WDT_CPU_RESET_LENGTH_M  ((RTC_CNTL_WDT_CPU_RESET_LENGTH_V)<<(RTC_CNTL_WDT_CPU_RESET_LENGTH_S))
#define RTC_CNTL_WDT_CPU_RESET_LENGTH_V  0x7
#define RTC_CNTL_WDT_CPU_RESET_LENGTH_S  16
/* RTC_CNTL_WDT_SYS_RESET_LENGTH : R/W ;bitpos:[15:13] ;default: 3'h1 ; */
/*description: system reset counter length.*/
#define RTC_CNTL_WDT_SYS_RESET_LENGTH    0x00000007
#define RTC_CNTL_WDT_SYS_RESET_LENGTH_M  ((RTC_CNTL_WDT_SYS_RESET_LENGTH_V)<<(RTC_CNTL_WDT_SYS_RESET_LENGTH_S))
#define RTC_CNTL_WDT_SYS_RESET_LENGTH_V  0x7
#define RTC_CNTL_WDT_SYS_RESET_LENGTH_S  13
/* RTC_CNTL_WDT_FLASHBOOT_MOD_EN : R/W ;bitpos:[12] ;default: 1'h1 ; */
/*description: enable WDT in flash boot.*/
#define RTC_CNTL_WDT_FLASHBOOT_MOD_EN    (1<<12)
#define RTC_CNTL_WDT_FLASHBOOT_MOD_EN_M  (1<<12)
#define RTC_CNTL_WDT_FLASHBOOT_MOD_EN_V  0x1
#define RTC_CNTL_WDT_FLASHBOOT_MOD_EN_S  12
/* RTC_CNTL_WDT_PROCPU_RESET_EN : R/W ;bitpos:[11] ;default: 1'd0 ; */
/*description: enable WDT reset PRO CPU.*/
#define RTC_CNTL_WDT_PROCPU_RESET_EN    (1<<11)
#define RTC_CNTL_WDT_PROCPU_RESET_EN_M  (1<<11)
#define RTC_CNTL_WDT_PROCPU_RESET_EN_V  0x1
#define RTC_CNTL_WDT_PROCPU_RESET_EN_S  11
/* RTC_CNTL_WDT_APPCPU_RESET_EN : R/W ;bitpos:[10] ;default: 1'd0 ; */
/*description: enable WDT reset APP CPU.*/
#define RTC_CNTL_WDT_APPCPU_RESET_EN    (1<<10)
#define RTC_CNTL_WDT_APPCPU_RESET_EN_M  (1<<10)
#define RTC_CNTL_WDT_APPCPU_RESET_EN_V  0x1
#define RTC_CNTL_WDT_APPCPU_RESET_EN_S  10
/* RTC_CNTL_WDT_PAUSE_IN_SLP : R/W ;bitpos:[9] ;default: 1'd1 ; */
/*description: pause WDT in sleep.*/
#define RTC_CNTL_WDT_PAUSE_IN_SLP    (1<<9)
#define RTC_CNTL_WDT_PAUSE_IN_SLP_M  (1<<9)
#define RTC_CNTL_WDT_PAUSE_IN_SLP_V  0x1
#define RTC_CNTL_WDT_PAUSE_IN_SLP_S  9
/* RTC_CNTL_WDT_CHIP_RESET_EN : R/W ;bitpos:[8] ;default: 1'b0 ; */
/*description: wdt reset whole chip enable.*/
#define RTC_CNTL_WDT_CHIP_RESET_EN    (1<<8)
#define RTC_CNTL_WDT_CHIP_RESET_EN_M  (1<<8)
#define RTC_CNTL_WDT_CHIP_RESET_EN_V  0x1
#define RTC_CNTL_WDT_CHIP_RESET_EN_S  8
/* RTC_CNTL_WDT_CHIP_RESET_WIDTH : R/W ;bitpos:[7:0] ;default: 8'd20 ; */
/*description: chip reset siginal pulse width.*/
#define RTC_CNTL_WDT_CHIP_RESET_WIDTH    0x000000FF
#define RTC_CNTL_WDT_CHIP_RESET_WIDTH_M  ((RTC_CNTL_WDT_CHIP_RESET_WIDTH_V)<<(RTC_CNTL_WDT_CHIP_RESET_WIDTH_S))
#define RTC_CNTL_WDT_CHIP_RESET_WIDTH_V  0xFF
#define RTC_CNTL_WDT_CHIP_RESET_WIDTH_S  0

#define RTC_CNTL_WDTCONFIG1_REG          (0x60008000 + 0x9C)
/* RTC_CNTL_WDT_STG0_HOLD : R/W ;bitpos:[31:0] ;default: 32'd200000 ; */
/*description: .*/
#define RTC_CNTL_WDT_STG0_HOLD    0xFFFFFFFF
#define RTC_CNTL_WDT_STG0_HOLD_M  ((RTC_CNTL_WDT_STG0_HOLD_V)<<(RTC_CNTL_WDT_STG0_HOLD_S))
#define RTC_CNTL_WDT_STG0_HOLD_V  0xFFFFFFFF
#define RTC_CNTL_WDT_STG0_HOLD_S  0

#define RTC_CNTL_WDTCONFIG2_REG          (0x60008000 + 0xA0)
/* RTC_CNTL_WDT_STG1_HOLD : R/W ;bitpos:[31:0] ;default: 32'd80000 ; */
/*description: .*/
#define RTC_CNTL_WDT_STG1_HOLD    0xFFFFFFFF
#define RTC_CNTL_WDT_STG1_HOLD_M  ((RTC_CNTL_WDT_STG1_HOLD_V)<<(RTC_CNTL_WDT_STG1_HOLD_S))
#define RTC_CNTL_WDT_STG1_HOLD_V  0xFFFFFFFF
#define RTC_CNTL_WDT_STG1_HOLD_S  0

#define RTC_CNTL_WDTCONFIG3_REG          (0x60008000 + 0xA4)
/* RTC_CNTL_WDT_STG2_HOLD : R/W ;bitpos:[31:0] ;default: 32'hfff ; */
/*description: .*/
#define RTC_CNTL_WDT_STG2_HOLD    0xFFFFFFFF
#define RTC_CNTL_WDT_STG2_HOLD_M  ((RTC_CNTL_WDT_STG2_HOLD_V)<<(RTC_CNTL_WDT_STG2_HOLD_S))
#define RTC_CNTL_WDT_STG2_HOLD_V  0xFFFFFFFF
#define RTC_CNTL_WDT_STG2_HOLD_S  0

#define RTC_CNTL_WDTCONFIG4_REG          (0x60008000 + 0xA8)
/* RTC_CNTL_WDT_STG3_HOLD : R/W ;bitpos:[31:0] ;default: 32'hfff ; */
/*description: .*/
#define RTC_CNTL_WDT_STG3_HOLD    0xFFFFFFFF
#define RTC_CNTL_WDT_STG3_HOLD_M  ((RTC_CNTL_WDT_STG3_HOLD_V)<<(RTC_CNTL_WDT_STG3_HOLD_S))
#define RTC_CNTL_WDT_STG3_HOLD_V  0xFFFFFFFF
#define RTC_CNTL_WDT_STG3_HOLD_S  0

#define RTC_CNTL_WDTFEED_REG          (0x60008000 + 0xAC)
/* RTC_CNTL_WDT_FEED : WO ;bitpos:[31] ;default: 1'd0 ; */
/*description: .*/
#define RTC_CNTL_WDT_FEED    (1<<31)
#define RTC_CNTL_WDT_FEED_M  (1<<31)
#define RTC_CNTL_WDT_FEED_V  0x1
#define RTC_CNTL_WDT_FEED_S  31

#define RTC_CNTL_WDTWPROTECT_REG          (0x60008000 + 0xB0)
/* RTC_CNTL_WDT_WKEY : R/W ;bitpos:[31:0] ;default: 32'h50d83aa1 ; */
/*description: .*/
#define RTC_CNTL_WDT_WKEY    0xFFFFFFFF
#define RTC_CNTL_WDT_WKEY_M  ((RTC_CNTL_WDT_WKEY_V)<<(RTC_CNTL_WDT_WKEY_S))
#define RTC_CNTL_WDT_WKEY_V  0xFFFFFFFF
#define RTC_CNTL_WDT_WKEY_S  0

#define RTC_CNTL_SWD_CONF_REG          (0x60008000 + 0xB4)
/* RTC_CNTL_SWD_AUTO_FEED_EN : R/W ;bitpos:[31] ;default: 1'b0 ; */
/*description: automatically feed swd when int comes.*/
#define RTC_CNTL_SWD_AUTO_FEED_EN    (1<<31)
#define RTC_CNTL_SWD_AUTO_FEED_EN_M  (1<<31)
#define RTC_CNTL_SWD_AUTO_FEED_EN_V  0x1
#define RTC_CNTL_SWD_AUTO_FEED_EN_S  31
/* RTC_CNTL_SWD_DISABLE : R/W ;bitpos:[30] ;default: 1'b0 ; */
/*description: disabel SWD.*/
#define RTC_CNTL_SWD_DISABLE    (1<<30)
#define RTC_CNTL_SWD_DISABLE_M  (1<<30)
#define RTC_CNTL_SWD_DISABLE_V  0x1
#define RTC_CNTL_SWD_DISABLE_S  30
/* RTC_CNTL_SWD_FEED : WO ;bitpos:[29] ;default: 1'b0 ; */
/*description: Sw feed swd.*/
#define RTC_CNTL_SWD_FEED    (1<<29)
#define RTC_CNTL_SWD_FEED_M  (1<<29)
#define RTC_CNTL_SWD_FEED_V  0x1
#define RTC_CNTL_SWD_FEED_S  29
/* RTC_CNTL_SWD_RST_FLAG_CLR : WO ;bitpos:[28] ;default: 1'b0 ; */
/*description: reset swd reset flag.*/
#define RTC_CNTL_SWD_RST_FLAG_CLR    (1<<28)
#define RTC_CNTL_SWD_RST_FLAG_CLR_M  (1<<28)
#define RTC_CNTL_SWD_RST_FLAG_CLR_V  0x1
#define RTC_CNTL_SWD_RST_FLAG_CLR_S  28
/* RTC_CNTL_SWD_SIGNAL_WIDTH : R/W ;bitpos:[27:18] ;default: 10'd300 ; */
/*description: adjust signal width send to swd.*/
#define RTC_CNTL_SWD_SIGNAL_WIDTH    0x000003FF
#define RTC_CNTL_SWD_SIGNAL_WIDTH_M  ((RTC_CNTL_SWD_SIGNAL_WIDTH_V)<<(RTC_CNTL_SWD_SIGNAL_WIDTH_S))
#define RTC_CNTL_SWD_SIGNAL_WIDTH_V  0x3FF
#define RTC_CNTL_SWD_SIGNAL_WIDTH_S  18
/* RTC_CNTL_SWD_BYPASS_RST : R/W ;bitpos:[17] ;default: 1'b0 ; */
/*description: .*/
#define RTC_CNTL_SWD_BYPASS_RST    (1<<17)
#define RTC_CNTL_SWD_BYPASS_RST_M  (1<<17)
#define RTC_CNTL_SWD_BYPASS_RST_V  0x1
#define RTC_CNTL_SWD_BYPASS_RST_S  17
/* RTC_CNTL_SWD_FEED_INT : RO ;bitpos:[1] ;default: 1'b0 ; */
/*description: swd interrupt for feeding.*/
#define RTC_CNTL_SWD_FEED_INT    (1<<1)
#define RTC_CNTL_SWD_FEED_INT_M  (1<<1)
#define RTC_CNTL_SWD_FEED_INT_V  0x1
#define RTC_CNTL_SWD_FEED_INT_S  1
/* RTC_CNTL_SWD_RESET_FLAG : RO ;bitpos:[0] ;default: 1'b0 ; */
/*description: swd reset flag.*/
#define RTC_CNTL_SWD_RESET_FLAG    (1<<0)
#define RTC_CNTL_SWD_RESET_FLAG_M  (1<<0)
#define RTC_CNTL_SWD_RESET_FLAG_V  0x1
#define RTC_CNTL_SWD_RESET_FLAG_S  0

#define RTC_CNTL_SWD_WPROTECT_REG          (0x60008000 + 0xB8)
/* RTC_CNTL_SWD_WKEY : R/W ;bitpos:[31:0] ;default: 32'h8f1d312a ; */
/*description: .*/
#define RTC_CNTL_SWD_WKEY    0xFFFFFFFF
#define RTC_CNTL_SWD_WKEY_M  ((RTC_CNTL_SWD_WKEY_V)<<(RTC_CNTL_SWD_WKEY_S))
#define RTC_CNTL_SWD_WKEY_V  0xFFFFFFFF
#define RTC_CNTL_SWD_WKEY_S  0

#define RTC_CNTL_SW_CPU_STALL_REG          (0x60008000 + 0xBC)
/* RTC_CNTL_SW_STALL_PROCPU_C1 : R/W ;bitpos:[31:26] ;default: 6'b0 ; */
/*description: .*/
#define RTC_CNTL_SW_STALL_PROCPU_C1    0x0000003F
#define RTC_CNTL_SW_STALL_PROCPU_C1_M  ((RTC_CNTL_SW_STALL_PROCPU_C1_V)<<(RTC_CNTL_SW_STALL_PROCPU_C1_S))
#define RTC_CNTL_SW_STALL_PROCPU_C1_V  0x3F
#define RTC_CNTL_SW_STALL_PROCPU_C1_S  26
/* RTC_CNTL_SW_STALL_APPCPU_C1 : R/W ;bitpos:[25:20] ;default: 6'b0 ; */
/*description: {reg_sw_stall_appcpu_c1[5:0].*/
#define RTC_CNTL_SW_STALL_APPCPU_C1    0x0000003F
#define RTC_CNTL_SW_STALL_APPCPU_C1_M  ((RTC_CNTL_SW_STALL_APPCPU_C1_V)<<(RTC_CNTL_SW_STALL_APPCPU_C1_S))
#define RTC_CNTL_SW_STALL_APPCPU_C1_V  0x3F
#define RTC_CNTL_SW_STALL_APPCPU_C1_S  20

#define RTC_CNTL_STORE4_REG          (0x60008000 + 0xC0)
/* RTC_CNTL_SCRATCH4 : R/W ;bitpos:[31:0] ;default: 0 ; */
/*description: .*/
#define RTC_CNTL_SCRATCH4    0xFFFFFFFF
#define RTC_CNTL_SCRATCH4_M  ((RTC_CNTL_SCRATCH4_V)<<(RTC_CNTL_SCRATCH4_S))
#define RTC_CNTL_SCRATCH4_V  0xFFFFFFFF
#define RTC_CNTL_SCRATCH4_S  0

#define RTC_CNTL_STORE5_REG          (0x60008000 + 0xC4)
/* RTC_CNTL_SCRATCH5 : R/W ;bitpos:[31:0] ;default: 0 ; */
/*description: .*/
#define RTC_CNTL_SCRATCH5    0xFFFFFFFF
#define RTC_CNTL_SCRATCH5_M  ((RTC_CNTL_SCRATCH5_V)<<(RTC_CNTL_SCRATCH5_S))
#define RTC_CNTL_SCRATCH5_V  0xFFFFFFFF
#define RTC_CNTL_SCRATCH5_S  0

#define RTC_CNTL_STORE6_REG          (0x60008000 + 0xC8)
/* RTC_CNTL_SCRATCH6 : R/W ;bitpos:[31:0] ;default: 0 ; */
/*description: .*/
#define RTC_CNTL_SCRATCH6    0xFFFFFFFF
#define RTC_CNTL_SCRATCH6_M  ((RTC_CNTL_SCRATCH6_V)<<(RTC_CNTL_SCRATCH6_S))
#define RTC_CNTL_SCRATCH6_V  0xFFFFFFFF
#define RTC_CNTL_SCRATCH6_S  0

#define RTC_CNTL_STORE7_REG          (0x60008000 + 0xCC)
/* RTC_CNTL_SCRATCH7 : R/W ;bitpos:[31:0] ;default: 0 ; */
/*description: .*/
#define RTC_CNTL_SCRATCH7    0xFFFFFFFF
#define RTC_CNTL_SCRATCH7_M  ((RTC_CNTL_SCRATCH7_V)<<(RTC_CNTL_SCRATCH7_S))
#define RTC_CNTL_SCRATCH7_V  0xFFFFFFFF
#define RTC_CNTL_SCRATCH7_S  0

#define RTC_CNTL_LOW_POWER_ST_REG          (0x60008000 + 0xD0)
/* RTC_CNTL_MAIN_STATE : RO ;bitpos:[31:28] ;default: 4'd0 ; */
/*description: rtc main state machine status.*/
#define RTC_CNTL_MAIN_STATE    0x0000000F
#define RTC_CNTL_MAIN_STATE_M  ((RTC_CNTL_MAIN_STATE_V)<<(RTC_CNTL_MAIN_STATE_S))
#define RTC_CNTL_MAIN_STATE_V  0xF
#define RTC_CNTL_MAIN_STATE_S  28
/* RTC_CNTL_MAIN_STATE_IN_IDLE : RO ;bitpos:[27] ;default: 1'b0 ; */
/*description: rtc main state machine is in idle state.*/
#define RTC_CNTL_MAIN_STATE_IN_IDLE    (1<<27)
#define RTC_CNTL_MAIN_STATE_IN_IDLE_M  (1<<27)
#define RTC_CNTL_MAIN_STATE_IN_IDLE_V  0x1
#define RTC_CNTL_MAIN_STATE_IN_IDLE_S  27
/* RTC_CNTL_MAIN_STATE_IN_SLP : RO ;bitpos:[26] ;default: 1'b0 ; */
/*description: rtc main state machine is in sleep state.*/
#define RTC_CNTL_MAIN_STATE_IN_SLP    (1<<26)
#define RTC_CNTL_MAIN_STATE_IN_SLP_M  (1<<26)
#define RTC_CNTL_MAIN_STATE_IN_SLP_V  0x1
#define RTC_CNTL_MAIN_STATE_IN_SLP_S  26
/* RTC_CNTL_MAIN_STATE_IN_WAIT_XTL : RO ;bitpos:[25] ;default: 1'b0 ; */
/*description: rtc main state machine is in wait xtal state.*/
#define RTC_CNTL_MAIN_STATE_IN_WAIT_XTL    (1<<25)
#define RTC_CNTL_MAIN_STATE_IN_WAIT_XTL_M  (1<<25)
#define RTC_CNTL_MAIN_STATE_IN_WAIT_XTL_V  0x1
#define RTC_CNTL_MAIN_STATE_IN_WAIT_XTL_S  25
/* RTC_CNTL_MAIN_STATE_IN_WAIT_PLL : RO ;bitpos:[24] ;default: 1'b0 ; */
/*description: rtc main state machine is in wait pll state.*/
#define RTC_CNTL_MAIN_STATE_IN_WAIT_PLL    (1<<24)
#define RTC_CNTL_MAIN_STATE_IN_WAIT_PLL_M  (1<<24)
#define RTC_CNTL_MAIN_STATE_IN_WAIT_PLL_V  0x1
#define RTC_CNTL_MAIN_STATE_IN_WAIT_PLL_S  24
/* RTC_CNTL_MAIN_STATE_IN_WAIT_8M : RO ;bitpos:[23] ;default: 1'b0 ; */
/*description: rtc main state machine is in wait 8m state.*/
#define RTC_CNTL_MAIN_STATE_IN_WAIT_8M    (1<<23)
#define RTC_CNTL_MAIN_STATE_IN_WAIT_8M_M  (1<<23)
#define RTC_CNTL_MAIN_STATE_IN_WAIT_8M_V  0x1
#define RTC_CNTL_MAIN_STATE_IN_WAIT_8M_S  23
/* RTC_CNTL_IN_LOW_POWER_STATE : RO ;bitpos:[22] ;default: 1'b0 ; */
/*description: rtc main state machine is in the states of low power.*/
#define RTC_CNTL_IN_LOW_POWER_STATE    (1<<22)
#define RTC_CNTL_IN_LOW_POWER_STATE_M  (1<<22)
#define RTC_CNTL_IN_LOW_POWER_STATE_V  0x1
#define RTC_CNTL_IN_LOW_POWER_STATE_S  22
/* RTC_CNTL_IN_WAKEUP_STATE : RO ;bitpos:[21] ;default: 1'b0 ; */
/*description: rtc main state machine is in the states of wakeup process.*/
#define RTC_CNTL_IN_WAKEUP_STATE    (1<<21)
#define RTC_CNTL_IN_WAKEUP_STATE_M  (1<<21)
#define RTC_CNTL_IN_WAKEUP_STATE_V  0x1
#define RTC_CNTL_IN_WAKEUP_STATE_S  21
/* RTC_CNTL_MAIN_STATE_WAIT_END : RO ;bitpos:[20] ;default: 1'b0 ; */
/*description: rtc main state machine has been waited for some cycles.*/
#define RTC_CNTL_MAIN_STATE_WAIT_END    (1<<20)
#define RTC_CNTL_MAIN_STATE_WAIT_END_M  (1<<20)
#define RTC_CNTL_MAIN_STATE_WAIT_END_V  0x1
#define RTC_CNTL_MAIN_STATE_WAIT_END_S  20
/* RTC_CNTL_RDY_FOR_WAKEUP : RO ;bitpos:[19] ;default: 1'b0 ; */
/*description: rtc is ready to receive wake up trigger from wake up source.*/
#define RTC_CNTL_RDY_FOR_WAKEUP    (1<<19)
#define RTC_CNTL_RDY_FOR_WAKEUP_M  (1<<19)
#define RTC_CNTL_RDY_FOR_WAKEUP_V  0x1
#define RTC_CNTL_RDY_FOR_WAKEUP_S  19
/* RTC_CNTL_MAIN_STATE_PLL_ON : RO ;bitpos:[18] ;default: 1'b0 ; */
/*description: rtc main state machine is in states that pll should be running.*/
#define RTC_CNTL_MAIN_STATE_PLL_ON    (1<<18)
#define RTC_CNTL_MAIN_STATE_PLL_ON_M  (1<<18)
#define RTC_CNTL_MAIN_STATE_PLL_ON_V  0x1
#define RTC_CNTL_MAIN_STATE_PLL_ON_S  18
/* RTC_CNTL_MAIN_STATE_XTAL_ISO : RO ;bitpos:[17] ;default: 1'b0 ; */
/*description: no use any more.*/
#define RTC_CNTL_MAIN_STATE_XTAL_ISO    (1<<17)
#define RTC_CNTL_MAIN_STATE_XTAL_ISO_M  (1<<17)
#define RTC_CNTL_MAIN_STATE_XTAL_ISO_V  0x1
#define RTC_CNTL_MAIN_STATE_XTAL_ISO_S  17
/* RTC_CNTL_COCPU_STATE_DONE : RO ;bitpos:[16] ;default: 1'b0 ; */
/*description: ulp/cocpu is done.*/
#define RTC_CNTL_COCPU_STATE_DONE    (1<<16)
#define RTC_CNTL_COCPU_STATE_DONE_M  (1<<16)
#define RTC_CNTL_COCPU_STATE_DONE_V  0x1
#define RTC_CNTL_COCPU_STATE_DONE_S  16
/* RTC_CNTL_COCPU_STATE_SLP : RO ;bitpos:[15] ;default: 1'b0 ; */
/*description: ulp/cocpu is in sleep state.*/
#define RTC_CNTL_COCPU_STATE_SLP    (1<<15)
#define RTC_CNTL_COCPU_STATE_SLP_M  (1<<15)
#define RTC_CNTL_COCPU_STATE_SLP_V  0x1
#define RTC_CNTL_COCPU_STATE_SLP_S  15
/* RTC_CNTL_COCPU_STATE_SWITCH : RO ;bitpos:[14] ;default: 1'b0 ; */
/*description: ulp/cocpu is about to working. Switch rtc main state.*/
#define RTC_CNTL_COCPU_STATE_SWITCH    (1<<14)
#define RTC_CNTL_COCPU_STATE_SWITCH_M  (1<<14)
#define RTC_CNTL_COCPU_STATE_SWITCH_V  0x1
#define RTC_CNTL_COCPU_STATE_SWITCH_S  14
/* RTC_CNTL_COCPU_STATE_START : RO ;bitpos:[13] ;default: 1'b0 ; */
/*description: ulp/cocpu should start to work.*/
#define RTC_CNTL_COCPU_STATE_START    (1<<13)
#define RTC_CNTL_COCPU_STATE_START_M  (1<<13)
#define RTC_CNTL_COCPU_STATE_START_V  0x1
#define RTC_CNTL_COCPU_STATE_START_S  13
/* RTC_CNTL_TOUCH_STATE_DONE : RO ;bitpos:[12] ;default: 1'b0 ; */
/*description: touch is done.*/
#define RTC_CNTL_TOUCH_STATE_DONE    (1<<12)
#define RTC_CNTL_TOUCH_STATE_DONE_M  (1<<12)
#define RTC_CNTL_TOUCH_STATE_DONE_V  0x1
#define RTC_CNTL_TOUCH_STATE_DONE_S  12
/* RTC_CNTL_TOUCH_STATE_SLP : RO ;bitpos:[11] ;default: 1'b0 ; */
/*description: touch is in sleep state.*/
#define RTC_CNTL_TOUCH_STATE_SLP    (1<<11)
#define RTC_CNTL_TOUCH_STATE_SLP_M  (1<<11)
#define RTC_CNTL_TOUCH_STATE_SLP_V  0x1
#define RTC_CNTL_TOUCH_STATE_SLP_S  11
/* RTC_CNTL_TOUCH_STATE_SWITCH : RO ;bitpos:[10] ;default: 1'b0 ; */
/*description: touch is about to working. Switch rtc main state.*/
#define RTC_CNTL_TOUCH_STATE_SWITCH    (1<<10)
#define RTC_CNTL_TOUCH_STATE_SWITCH_M  (1<<10)
#define RTC_CNTL_TOUCH_STATE_SWITCH_V  0x1
#define RTC_CNTL_TOUCH_STATE_SWITCH_S  10
/* RTC_CNTL_TOUCH_STATE_START : RO ;bitpos:[9] ;default: 1'b0 ; */
/*description: touch should start to work.*/
#define RTC_CNTL_TOUCH_STATE_START    (1<<9)
#define RTC_CNTL_TOUCH_STATE_START_M  (1<<9)
#define RTC_CNTL_TOUCH_STATE_START_V  0x1
#define RTC_CNTL_TOUCH_STATE_START_S  9
/* RTC_CNTL_XPD_DIG : RO ;bitpos:[8] ;default: 1'b0 ; */
/*description: digital wrap power down.*/
#define RTC_CNTL_XPD_DIG    (1<<8)
#define RTC_CNTL_XPD_DIG_M  (1<<8)
#define RTC_CNTL_XPD_DIG_V  0x1
#define RTC_CNTL_XPD_DIG_S  8
/* RTC_CNTL_DIG_ISO : RO ;bitpos:[7] ;default: 1'b0 ; */
/*description: digital wrap iso.*/
#define RTC_CNTL_DIG_ISO    (1<<7)
#define RTC_CNTL_DIG_ISO_M  (1<<7)
#define RTC_CNTL_DIG_ISO_V  0x1
#define RTC_CNTL_DIG_ISO_S  7
/* RTC_CNTL_XPD_WIFI : RO ;bitpos:[6] ;default: 1'b0 ; */
/*description: wifi wrap power down.*/
#define RTC_CNTL_XPD_WIFI    (1<<6)
#define RTC_CNTL_XPD_WIFI_M  (1<<6)
#define RTC_CNTL_XPD_WIFI_V  0x1
#define RTC_CNTL_XPD_WIFI_S  6
/* RTC_CNTL_WIFI_ISO : RO ;bitpos:[5] ;default: 1'b0 ; */
/*description: wifi iso.*/
#define RTC_CNTL_WIFI_ISO    (1<<5)
#define RTC_CNTL_WIFI_ISO_M  (1<<5)
#define RTC_CNTL_WIFI_ISO_V  0x1
#define RTC_CNTL_WIFI_ISO_S  5
/* RTC_CNTL_XPD_RTC_PERI : RO ;bitpos:[4] ;default: 1'b0 ; */
/*description: rtc peripheral power down .*/
#define RTC_CNTL_XPD_RTC_PERI    (1<<4)
#define RTC_CNTL_XPD_RTC_PERI_M  (1<<4)
#define RTC_CNTL_XPD_RTC_PERI_V  0x1
#define RTC_CNTL_XPD_RTC_PERI_S  4
/* RTC_CNTL_PERI_ISO : RO ;bitpos:[3] ;default: 1'b0 ; */
/*description: rtc peripheral iso.*/
#define RTC_CNTL_PERI_ISO    (1<<3)
#define RTC_CNTL_PERI_ISO_M  (1<<3)
#define RTC_CNTL_PERI_ISO_V  0x1
#define RTC_CNTL_PERI_ISO_S  3
/* RTC_CNTL_XPD_DIG_DCDC : RO ;bitpos:[2] ;default: 1'b0 ; */
/*description: External DCDC power down.*/
#define RTC_CNTL_XPD_DIG_DCDC    (1<<2)
#define RTC_CNTL_XPD_DIG_DCDC_M  (1<<2)
#define RTC_CNTL_XPD_DIG_DCDC_V  0x1
#define RTC_CNTL_XPD_DIG_DCDC_S  2
/* RTC_CNTL_XPD_ROM0 : RO ;bitpos:[0] ;default: 1'b0 ; */
/*description: rom0 power down.*/
#define RTC_CNTL_XPD_ROM0    (1<<0)
#define RTC_CNTL_XPD_ROM0_M  (1<<0)
#define RTC_CNTL_XPD_ROM0_V  0x1
#define RTC_CNTL_XPD_ROM0_S  0

#define RTC_CNTL_DIAG0_REG          (0x60008000 + 0xD4)
/* RTC_CNTL_LOW_POWER_DIAG1 : RO ;bitpos:[31:0] ;default: 0 ; */
/*description: .*/
#define RTC_CNTL_LOW_POWER_DIAG1    0xFFFFFFFF
#define RTC_CNTL_LOW_POWER_DIAG1_M  ((RTC_CNTL_LOW_POWER_DIAG1_V)<<(RTC_CNTL_LOW_POWER_DIAG1_S))
#define RTC_CNTL_LOW_POWER_DIAG1_V  0xFFFFFFFF
#define RTC_CNTL_LOW_POWER_DIAG1_S  0

#define RTC_CNTL_PAD_HOLD_REG          (0x60008000 + 0xD8)
/* RTC_CNTL_PAD21_HOLD : R/W ;bitpos:[21] ;default: 1'b0 ; */
/*description: .*/
#define RTC_CNTL_PAD21_HOLD    (1<<21)
#define RTC_CNTL_PAD21_HOLD_M  (1<<21)
#define RTC_CNTL_PAD21_HOLD_V  0x1
#define RTC_CNTL_PAD21_HOLD_S  21
/* RTC_CNTL_PAD20_HOLD : R/W ;bitpos:[20] ;default: 1'b0 ; */
/*description: .*/
#define RTC_CNTL_PAD20_HOLD    (1<<20)
#define RTC_CNTL_PAD20_HOLD_M  (1<<20)
#define RTC_CNTL_PAD20_HOLD_V  0x1
#define RTC_CNTL_PAD20_HOLD_S  20
/* RTC_CNTL_PAD19_HOLD : R/W ;bitpos:[19] ;default: 1'b0 ; */
/*description: .*/
#define RTC_CNTL_PAD19_HOLD    (1<<19)
#define RTC_CNTL_PAD19_HOLD_M  (1<<19)
#define RTC_CNTL_PAD19_HOLD_V  0x1
#define RTC_CNTL_PAD19_HOLD_S  19
/* RTC_CNTL_PDAC2_HOLD : R/W ;bitpos:[18] ;default: 1'b0 ; */
/*description: .*/
#define RTC_CNTL_PDAC2_HOLD    (1<<18)
#define RTC_CNTL_PDAC2_HOLD_M  (1<<18)
#define RTC_CNTL_PDAC2_HOLD_V  0x1
#define RTC_CNTL_PDAC2_HOLD_S  18
/* RTC_CNTL_PDAC1_HOLD : R/W ;bitpos:[17] ;default: 1'b0 ; */
/*description: .*/
#define RTC_CNTL_PDAC1_HOLD    (1<<17)
#define RTC_CNTL_PDAC1_HOLD_M  (1<<17)
#define RTC_CNTL_PDAC1_HOLD_V  0x1
#define RTC_CNTL_PDAC1_HOLD_S  17
/* RTC_CNTL_X32N_HOLD : R/W ;bitpos:[16] ;default: 1'b0 ; */
/*description: .*/
#define RTC_CNTL_X32N_HOLD    (1<<16)
#define RTC_CNTL_X32N_HOLD_M  (1<<16)
#define RTC_CNTL_X32N_HOLD_V  0x1
#define RTC_CNTL_X32N_HOLD_S  16
/* RTC_CNTL_X32P_HOLD : R/W ;bitpos:[15] ;default: 1'b0 ; */
/*description: .*/
#define RTC_CNTL_X32P_HOLD    (1<<15)
#define RTC_CNTL_X32P_HOLD_M  (1<<15)
#define RTC_CNTL_X32P_HOLD_V  0x1
#define RTC_CNTL_X32P_HOLD_S  15
/* RTC_CNTL_TOUCH_PAD14_HOLD : R/W ;bitpos:[14] ;default: 1'b0 ; */
/*description: .*/
#define RTC_CNTL_TOUCH_PAD14_HOLD    (1<<14)
#define RTC_CNTL_TOUCH_PAD14_HOLD_M  (1<<14)
#define RTC_CNTL_TOUCH_PAD14_HOLD_V  0x1
#define RTC_CNTL_TOUCH_PAD14_HOLD_S  14
/* RTC_CNTL_TOUCH_PAD13_HOLD : R/W ;bitpos:[13] ;default: 1'b0 ; */
/*description: .*/
#define RTC_CNTL_TOUCH_PAD13_HOLD    (1<<13)
#define RTC_CNTL_TOUCH_PAD13_HOLD_M  (1<<13)
#define RTC_CNTL_TOUCH_PAD13_HOLD_V  0x1
#define RTC_CNTL_TOUCH_PAD13_HOLD_S  13
/* RTC_CNTL_TOUCH_PAD12_HOLD : R/W ;bitpos:[12] ;default: 1'b0 ; */
/*description: .*/
#define RTC_CNTL_TOUCH_PAD12_HOLD    (1<<12)
#define RTC_CNTL_TOUCH_PAD12_HOLD_M  (1<<12)
#define RTC_CNTL_TOUCH_PAD12_HOLD_V  0x1
#define RTC_CNTL_TOUCH_PAD12_HOLD_S  12
/* RTC_CNTL_TOUCH_PAD11_HOLD : R/W ;bitpos:[11] ;default: 1'b0 ; */
/*description: .*/
#define RTC_CNTL_TOUCH_PAD11_HOLD    (1<<11)
#define RTC_CNTL_TOUCH_PAD11_HOLD_M  (1<<11)
#define RTC_CNTL_TOUCH_PAD11_HOLD_V  0x1
#define RTC_CNTL_TOUCH_PAD11_HOLD_S  11
/* RTC_CNTL_TOUCH_PAD10_HOLD : R/W ;bitpos:[10] ;default: 1'b0 ; */
/*description: .*/
#define RTC_CNTL_TOUCH_PAD10_HOLD    (1<<10)
#define RTC_CNTL_TOUCH_PAD10_HOLD_M  (1<<10)
#define RTC_CNTL_TOUCH_PAD10_HOLD_V  0x1
#define RTC_CNTL_TOUCH_PAD10_HOLD_S  10
/* RTC_CNTL_TOUCH_PAD9_HOLD : R/W ;bitpos:[9] ;default: 1'b0 ; */
/*description: .*/
#define RTC_CNTL_TOUCH_PAD9_HOLD    (1<<9)
#define RTC_CNTL_TOUCH_PAD9_HOLD_M  (1<<9)
#define RTC_CNTL_TOUCH_PAD9_HOLD_V  0x1
#define RTC_CNTL_TOUCH_PAD9_HOLD_S  9
/* RTC_CNTL_TOUCH_PAD8_HOLD : R/W ;bitpos:[8] ;default: 1'b0 ; */
/*description: .*/
#define RTC_CNTL_TOUCH_PAD8_HOLD    (1<<8)
#define RTC_CNTL_TOUCH_PAD8_HOLD_M  (1<<8)
#define RTC_CNTL_TOUCH_PAD8_HOLD_V  0x1
#define RTC_CNTL_TOUCH_PAD8_HOLD_S  8
/* RTC_CNTL_TOUCH_PAD7_HOLD : R/W ;bitpos:[7] ;default: 1'b0 ; */
/*description: .*/
#define RTC_CNTL_TOUCH_PAD7_HOLD    (1<<7)
#define RTC_CNTL_TOUCH_PAD7_HOLD_M  (1<<7)
#define RTC_CNTL_TOUCH_PAD7_HOLD_V  0x1
#define RTC_CNTL_TOUCH_PAD7_HOLD_S  7
/* RTC_CNTL_TOUCH_PAD6_HOLD : R/W ;bitpos:[6] ;default: 1'b0 ; */
/*description: .*/
#define RTC_CNTL_TOUCH_PAD6_HOLD    (1<<6)
#define RTC_CNTL_TOUCH_PAD6_HOLD_M  (1<<6)
#define RTC_CNTL_TOUCH_PAD6_HOLD_V  0x1
#define RTC_CNTL_TOUCH_PAD6_HOLD_S  6
/* RTC_CNTL_TOUCH_PAD5_HOLD : R/W ;bitpos:[5] ;default: 1'b0 ; */
/*description: .*/
#define RTC_CNTL_TOUCH_PAD5_HOLD    (1<<5)
#define RTC_CNTL_TOUCH_PAD5_HOLD_M  (1<<5)
#define RTC_CNTL_TOUCH_PAD5_HOLD_V  0x1
#define RTC_CNTL_TOUCH_PAD5_HOLD_S  5
/* RTC_CNTL_TOUCH_PAD4_HOLD : R/W ;bitpos:[4] ;default: 1'b0 ; */
/*description: .*/
#define RTC_CNTL_TOUCH_PAD4_HOLD    (1<<4)
#define RTC_CNTL_TOUCH_PAD4_HOLD_M  (1<<4)
#define RTC_CNTL_TOUCH_PAD4_HOLD_V  0x1
#define RTC_CNTL_TOUCH_PAD4_HOLD_S  4
/* RTC_CNTL_TOUCH_PAD3_HOLD : R/W ;bitpos:[3] ;default: 1'b0 ; */
/*description: .*/
#define RTC_CNTL_TOUCH_PAD3_HOLD    (1<<3)
#define RTC_CNTL_TOUCH_PAD3_HOLD_M  (1<<3)
#define RTC_CNTL_TOUCH_PAD3_HOLD_V  0x1
#define RTC_CNTL_TOUCH_PAD3_HOLD_S  3
/* RTC_CNTL_TOUCH_PAD2_HOLD : R/W ;bitpos:[2] ;default: 1'b0 ; */
/*description: .*/
#define RTC_CNTL_TOUCH_PAD2_HOLD    (1<<2)
#define RTC_CNTL_TOUCH_PAD2_HOLD_M  (1<<2)
#define RTC_CNTL_TOUCH_PAD2_HOLD_V  0x1
#define RTC_CNTL_TOUCH_PAD2_HOLD_S  2
/* RTC_CNTL_TOUCH_PAD1_HOLD : R/W ;bitpos:[1] ;default: 1'b0 ; */
/*description: .*/
#define RTC_CNTL_TOUCH_PAD1_HOLD    (1<<1)
#define RTC_CNTL_TOUCH_PAD1_HOLD_M  (1<<1)
#define RTC_CNTL_TOUCH_PAD1_HOLD_V  0x1
#define RTC_CNTL_TOUCH_PAD1_HOLD_S  1
/* RTC_CNTL_TOUCH_PAD0_HOLD : R/W ;bitpos:[0] ;default: 1'b0 ; */
/*description: .*/
#define RTC_CNTL_TOUCH_PAD0_HOLD    (1<<0)
#define RTC_CNTL_TOUCH_PAD0_HOLD_M  (1<<0)
#define RTC_CNTL_TOUCH_PAD0_HOLD_V  0x1
#define RTC_CNTL_TOUCH_PAD0_HOLD_S  0

#define RTC_CNTL_DIG_PAD_HOLD_REG          (0x60008000 + 0xDC)
/* RTC_CNTL_DIG_PAD_HOLD : R/W ;bitpos:[31:0] ;default: 32'b0 ; */
/*description: .*/
#define RTC_CNTL_DIG_PAD_HOLD    0xFFFFFFFF
#define RTC_CNTL_DIG_PAD_HOLD_M  ((RTC_CNTL_DIG_PAD_HOLD_V)<<(RTC_CNTL_DIG_PAD_HOLD_S))
#define RTC_CNTL_DIG_PAD_HOLD_V  0xFFFFFFFF
#define RTC_CNTL_DIG_PAD_HOLD_S  0

#define RTC_CNTL_EXT_WAKEUP1_REG          (0x60008000 + 0xE0)
/* RTC_CNTL_EXT_WAKEUP1_STATUS_CLR : WO ;bitpos:[22] ;default: 1'd0 ; */
/*description: clear ext wakeup1 status.*/
#define RTC_CNTL_EXT_WAKEUP1_STATUS_CLR    (1<<22)
#define RTC_CNTL_EXT_WAKEUP1_STATUS_CLR_M  (1<<22)
#define RTC_CNTL_EXT_WAKEUP1_STATUS_CLR_V  0x1
#define RTC_CNTL_EXT_WAKEUP1_STATUS_CLR_S  22
/* RTC_CNTL_EXT_WAKEUP1_SEL : R/W ;bitpos:[21:0] ;default: 22'd0 ; */
/*description: Bitmap to select RTC pads for ext wakeup1.*/
#define RTC_CNTL_EXT_WAKEUP1_SEL    0x003FFFFF
#define RTC_CNTL_EXT_WAKEUP1_SEL_M  ((RTC_CNTL_EXT_WAKEUP1_SEL_V)<<(RTC_CNTL_EXT_WAKEUP1_SEL_S))
#define RTC_CNTL_EXT_WAKEUP1_SEL_V  0x3FFFFF
#define RTC_CNTL_EXT_WAKEUP1_SEL_S  0

#define RTC_CNTL_EXT_WAKEUP1_STATUS_REG          (0x60008000 + 0xE4)
/* RTC_CNTL_EXT_WAKEUP1_STATUS : RO ;bitpos:[21:0] ;default: 22'd0 ; */
/*description: ext wakeup1 status.*/
#define RTC_CNTL_EXT_WAKEUP1_STATUS    0x003FFFFF
#define RTC_CNTL_EXT_WAKEUP1_STATUS_M  ((RTC_CNTL_EXT_WAKEUP1_STATUS_V)<<(RTC_CNTL_EXT_WAKEUP1_STATUS_S))
#define RTC_CNTL_EXT_WAKEUP1_STATUS_V  0x3FFFFF
#define RTC_CNTL_EXT_WAKEUP1_STATUS_S  0

#define RTC_CNTL_BROWN_OUT_REG          (0x60008000 + 0xE8)
/* RTC_CNTL_BROWN_OUT_DET : RO ;bitpos:[31] ;default: 1'b0 ; */
/*description: .*/
#define RTC_CNTL_BROWN_OUT_DET    (1<<31)
#define RTC_CNTL_BROWN_OUT_DET_M  (1<<31)
#define RTC_CNTL_BROWN_OUT_DET_V  0x1
#define RTC_CNTL_BROWN_OUT_DET_S  31
/* RTC_CNTL_BROWN_OUT_ENA : R/W ;bitpos:[30] ;default: 1'b1 ; */
/*description: enable brown out.*/
#define RTC_CNTL_BROWN_OUT_ENA    (1<<30)
#define RTC_CNTL_BROWN_OUT_ENA_M  (1<<30)
#define RTC_CNTL_BROWN_OUT_ENA_V  0x1
#define RTC_CNTL_BROWN_OUT_ENA_S  30
/* RTC_CNTL_BROWN_OUT_CNT_CLR : WO ;bitpos:[29] ;default: 1'b0 ; */
/*description: clear brown out counter.*/
#define RTC_CNTL_BROWN_OUT_CNT_CLR    (1<<29)
#define RTC_CNTL_BROWN_OUT_CNT_CLR_M  (1<<29)
#define RTC_CNTL_BROWN_OUT_CNT_CLR_V  0x1
#define RTC_CNTL_BROWN_OUT_CNT_CLR_S  29
/* RTC_CNTL_BROWN_OUT_ANA_RST_EN : R/W ;bitpos:[28] ;default: 1'b0 ; */
/*description: .*/
#define RTC_CNTL_BROWN_OUT_ANA_RST_EN    (1<<28)
#define RTC_CNTL_BROWN_OUT_ANA_RST_EN_M  (1<<28)
#define RTC_CNTL_BROWN_OUT_ANA_RST_EN_V  0x1
#define RTC_CNTL_BROWN_OUT_ANA_RST_EN_S  28
/* RTC_CNTL_BROWN_OUT_RST_SEL : R/W ;bitpos:[27] ;default: 1'b0 ; */
/*description: 1:  4-pos reset.*/
#define RTC_CNTL_BROWN_OUT_RST_SEL    (1<<27)
#define RTC_CNTL_BROWN_OUT_RST_SEL_M  (1<<27)
#define RTC_CNTL_BROWN_OUT_RST_SEL_V  0x1
#define RTC_CNTL_BROWN_OUT_RST_SEL_S  27
/* RTC_CNTL_BROWN_OUT_RST_ENA : R/W ;bitpos:[26] ;default: 1'b0 ; */
/*description: enable brown out reset.*/
#define RTC_CNTL_BROWN_OUT_RST_ENA    (1<<26)
#define RTC_CNTL_BROWN_OUT_RST_ENA_M  (1<<26)
#define RTC_CNTL_BROWN_OUT_RST_ENA_V  0x1
#define RTC_CNTL_BROWN_OUT_RST_ENA_S  26
/* RTC_CNTL_BROWN_OUT_RST_WAIT : R/W ;bitpos:[25:16] ;default: 10'h3ff ; */
/*description: brown out reset wait cycles.*/
#define RTC_CNTL_BROWN_OUT_RST_WAIT    0x000003FF
#define RTC_CNTL_BROWN_OUT_RST_WAIT_M  ((RTC_CNTL_BROWN_OUT_RST_WAIT_V)<<(RTC_CNTL_BROWN_OUT_RST_WAIT_S))
#define RTC_CNTL_BROWN_OUT_RST_WAIT_V  0x3FF
#define RTC_CNTL_BROWN_OUT_RST_WAIT_S  16
/* RTC_CNTL_BROWN_OUT_PD_RF_ENA : R/W ;bitpos:[15] ;default: 1'b0 ; */
/*description: enable power down RF when brown out happens.*/
#define RTC_CNTL_BROWN_OUT_PD_RF_ENA    (1<<15)
#define RTC_CNTL_BROWN_OUT_PD_RF_ENA_M  (1<<15)
#define RTC_CNTL_BROWN_OUT_PD_RF_ENA_V  0x1
#define RTC_CNTL_BROWN_OUT_PD_RF_ENA_S  15
/* RTC_CNTL_BROWN_OUT_CLOSE_FLASH_ENA : R/W ;bitpos:[14] ;default: 1'b0 ; */
/*description: enable close flash when brown out happens.*/
#define RTC_CNTL_BROWN_OUT_CLOSE_FLASH_ENA    (1<<14)
#define RTC_CNTL_BROWN_OUT_CLOSE_FLASH_ENA_M  (1<<14)
#define RTC_CNTL_BROWN_OUT_CLOSE_FLASH_ENA_V  0x1
#define RTC_CNTL_BROWN_OUT_CLOSE_FLASH_ENA_S  14
/* RTC_CNTL_BROWN_OUT_INT_WAIT : R/W ;bitpos:[13:4] ;default: 10'h1 ; */
/*description: brown out interrupt wait cycles.*/
#define RTC_CNTL_BROWN_OUT_INT_WAIT    0x000003FF
#define RTC_CNTL_BROWN_OUT_INT_WAIT_M  ((RTC_CNTL_BROWN_OUT_INT_WAIT_V)<<(RTC_CNTL_BROWN_OUT_INT_WAIT_S))
#define RTC_CNTL_BROWN_OUT_INT_WAIT_V  0x3FF
#define RTC_CNTL_BROWN_OUT_INT_WAIT_S  4

#define RTC_CNTL_TIME_LOW1_REG          (0x60008000 + 0xEC)
/* RTC_CNTL_TIMER_VALUE1_LOW : RO ;bitpos:[31:0] ;default: 32'h0 ; */
/*description: RTC timer low 32 bits.*/
#define RTC_CNTL_TIMER_VALUE1_LOW    0xFFFFFFFF
#define RTC_CNTL_TIMER_VALUE1_LOW_M  ((RTC_CNTL_TIMER_VALUE1_LOW_V)<<(RTC_CNTL_TIMER_VALUE1_LOW_S))
#define RTC_CNTL_TIMER_VALUE1_LOW_V  0xFFFFFFFF
#define RTC_CNTL_TIMER_VALUE1_LOW_S  0

#define RTC_CNTL_TIME_HIGH1_REG          (0x60008000 + 0xF0)
/* RTC_CNTL_TIMER_VALUE1_HIGH : RO ;bitpos:[15:0] ;default: 16'h0 ; */
/*description: RTC timer high 16 bits.*/
#define RTC_CNTL_TIMER_VALUE1_HIGH    0x0000FFFF
#define RTC_CNTL_TIMER_VALUE1_HIGH_M  ((RTC_CNTL_TIMER_VALUE1_HIGH_V)<<(RTC_CNTL_TIMER_VALUE1_HIGH_S))
#define RTC_CNTL_TIMER_VALUE1_HIGH_V  0xFFFF
#define RTC_CNTL_TIMER_VALUE1_HIGH_S  0

#define RTC_CNTL_XTAL32K_CLK_FACTOR_REG          (0x60008000 + 0xF4)
/* RTC_CNTL_XTAL32K_CLK_FACTOR : R/W ;bitpos:[31:0] ;default: 32'h0 ; */
/*description: xtal 32k watch dog backup clock factor.*/
#define RTC_CNTL_XTAL32K_CLK_FACTOR    0xFFFFFFFF
#define RTC_CNTL_XTAL32K_CLK_FACTOR_M  ((RTC_CNTL_XTAL32K_CLK_FACTOR_V)<<(RTC_CNTL_XTAL32K_CLK_FACTOR_S))
#define RTC_CNTL_XTAL32K_CLK_FACTOR_V  0xFFFFFFFF
#define RTC_CNTL_XTAL32K_CLK_FACTOR_S  0

#define RTC_CNTL_XTAL32K_CONF_REG          (0x60008000 + 0xF8)
/* RTC_CNTL_XTAL32K_STABLE_THRES : R/W ;bitpos:[31:28] ;default: 4'h0 ; */
/*description: if restarted xtal32k period is smaller than this.*/
#define RTC_CNTL_XTAL32K_STABLE_THRES    0x0000000F
#define RTC_CNTL_XTAL32K_STABLE_THRES_M  ((RTC_CNTL_XTAL32K_STABLE_THRES_V)<<(RTC_CNTL_XTAL32K_STABLE_THRES_S))
#define RTC_CNTL_XTAL32K_STABLE_THRES_V  0xF
#define RTC_CNTL_XTAL32K_STABLE_THRES_S  28
/* RTC_CNTL_XTAL32K_WDT_TIMEOUT : R/W ;bitpos:[27:20] ;default: 8'hff ; */
/*description: If no clock detected for this amount of time.*/
#define RTC_CNTL_XTAL32K_WDT_TIMEOUT    0x000000FF
#define RTC_CNTL_XTAL32K_WDT_TIMEOUT_M  ((RTC_CNTL_XTAL32K_WDT_TIMEOUT_V)<<(RTC_CNTL_XTAL32K_WDT_TIMEOUT_S))
#define RTC_CNTL_XTAL32K_WDT_TIMEOUT_V  0xFF
#define RTC_CNTL_XTAL32K_WDT_TIMEOUT_S  20
/* RTC_CNTL_XTAL32K_RESTART_WAIT : R/W ;bitpos:[19:4] ;default: 16'h0 ; */
/*description: cycles to wait to repower on xtal 32k.*/
#define RTC_CNTL_XTAL32K_RESTART_WAIT    0x0000FFFF
#define RTC_CNTL_XTAL32K_RESTART_WAIT_M  ((RTC_CNTL_XTAL32K_RESTART_WAIT_V)<<(RTC_CNTL_XTAL32K_RESTART_WAIT_S))
#define RTC_CNTL_XTAL32K_RESTART_WAIT_V  0xFFFF
#define RTC_CNTL_XTAL32K_RESTART_WAIT_S  4
/* RTC_CNTL_XTAL32K_RETURN_WAIT : R/W ;bitpos:[3:0] ;default: 4'h0 ; */
/*description: cycles to wait to return noral xtal 32k.*/
#define RTC_CNTL_XTAL32K_RETURN_WAIT    0x0000000F
#define RTC_CNTL_XTAL32K_RETURN_WAIT_M  ((RTC_CNTL_XTAL32K_RETURN_WAIT_V)<<(RTC_CNTL_XTAL32K_RETURN_WAIT_S))
#define RTC_CNTL_XTAL32K_RETURN_WAIT_V  0xF
#define RTC_CNTL_XTAL32K_RETURN_WAIT_S  0

#define RTC_CNTL_ULP_CP_TIMER_REG          (0x60008000 + 0xFC)
/* RTC_CNTL_ULP_CP_SLP_TIMER_EN : R/W ;bitpos:[31] ;default: 1'd0 ; */
/*description: ULP-coprocessor timer enable bit.*/
#define RTC_CNTL_ULP_CP_SLP_TIMER_EN    (1<<31)
#define RTC_CNTL_ULP_CP_SLP_TIMER_EN_M  (1<<31)
#define RTC_CNTL_ULP_CP_SLP_TIMER_EN_V  0x1
#define RTC_CNTL_ULP_CP_SLP_TIMER_EN_S  31
/* RTC_CNTL_ULP_CP_GPIO_WAKEUP_CLR : WO ;bitpos:[30] ;default: 1'd0 ; */
/*description: ULP-coprocessor wakeup by GPIO state clear.*/
#define RTC_CNTL_ULP_CP_GPIO_WAKEUP_CLR    (1<<30)
#define RTC_CNTL_ULP_CP_GPIO_WAKEUP_CLR_M  (1<<30)
#define RTC_CNTL_ULP_CP_GPIO_WAKEUP_CLR_V  0x1
#define RTC_CNTL_ULP_CP_GPIO_WAKEUP_CLR_S  30
/* RTC_CNTL_ULP_CP_GPIO_WAKEUP_ENA : R/W ;bitpos:[29] ;default: 1'd0 ; */
/*description: ULP-coprocessor wakeup by GPIO enable.*/
#define RTC_CNTL_ULP_CP_GPIO_WAKEUP_ENA    (1<<29)
#define RTC_CNTL_ULP_CP_GPIO_WAKEUP_ENA_M  (1<<29)
#define RTC_CNTL_ULP_CP_GPIO_WAKEUP_ENA_V  0x1
#define RTC_CNTL_ULP_CP_GPIO_WAKEUP_ENA_S  29
/* RTC_CNTL_ULP_CP_PC_INIT : R/W ;bitpos:[10:0] ;default: 11'b0 ; */
/*description: ULP-coprocessor PC initial address.*/
#define RTC_CNTL_ULP_CP_PC_INIT    0x000007FF
#define RTC_CNTL_ULP_CP_PC_INIT_M  ((RTC_CNTL_ULP_CP_PC_INIT_V)<<(RTC_CNTL_ULP_CP_PC_INIT_S))
#define RTC_CNTL_ULP_CP_PC_INIT_V  0x7FF
#define RTC_CNTL_ULP_CP_PC_INIT_S  0

#define RTC_CNTL_ULP_CP_CTRL_REG          (0x60008000 + 0x100)
/* RTC_CNTL_ULP_CP_START_TOP : R/W ;bitpos:[31] ;default: 1'd0 ; */
/*description: Write 1 to start ULP-coprocessor.*/
#define RTC_CNTL_ULP_CP_START_TOP    (1<<31)
#define RTC_CNTL_ULP_CP_START_TOP_M  (1<<31)
#define RTC_CNTL_ULP_CP_START_TOP_V  0x1
#define RTC_CNTL_ULP_CP_START_TOP_S  31
/* RTC_CNTL_ULP_CP_FORCE_START_TOP : R/W ;bitpos:[30] ;default: 1'd0 ; */
/*description: 1: ULP-coprocessor is started by SW.*/
#define RTC_CNTL_ULP_CP_FORCE_START_TOP    (1<<30)
#define RTC_CNTL_ULP_CP_FORCE_START_TOP_M  (1<<30)
#define RTC_CNTL_ULP_CP_FORCE_START_TOP_V  0x1
#define RTC_CNTL_ULP_CP_FORCE_START_TOP_S  30
/* RTC_CNTL_ULP_CP_RESET : R/W ;bitpos:[29] ;default: 1'd0 ; */
/*description: ulp coprocessor clk software reset.*/
#define RTC_CNTL_ULP_CP_RESET    (1<<29)
#define RTC_CNTL_ULP_CP_RESET_M  (1<<29)
#define RTC_CNTL_ULP_CP_RESET_V  0x1
#define RTC_CNTL_ULP_CP_RESET_S  29
/* RTC_CNTL_ULP_CP_CLK_FO : R/W ;bitpos:[28] ;default: 1'd0 ; */
/*description: ulp coprocessor clk force on.*/
#define RTC_CNTL_ULP_CP_CLK_FO    (1<<28)
#define RTC_CNTL_ULP_CP_CLK_FO_M  (1<<28)
#define RTC_CNTL_ULP_CP_CLK_FO_V  0x1
#define RTC_CNTL_ULP_CP_CLK_FO_S  28
/* RTC_CNTL_ULP_CP_MEM_OFFST_CLR : WO ;bitpos:[22] ;default: 1'd0 ; */
/*description: .*/
#define RTC_CNTL_ULP_CP_MEM_OFFST_CLR    (1<<22)
#define RTC_CNTL_ULP_CP_MEM_OFFST_CLR_M  (1<<22)
#define RTC_CNTL_ULP_CP_MEM_OFFST_CLR_V  0x1
#define RTC_CNTL_ULP_CP_MEM_OFFST_CLR_S  22
/* RTC_CNTL_ULP_CP_MEM_ADDR_SIZE : R/W ;bitpos:[21:11] ;default: 11'd512 ; */
/*description: .*/
#define RTC_CNTL_ULP_CP_MEM_ADDR_SIZE    0x000007FF
#define RTC_CNTL_ULP_CP_MEM_ADDR_SIZE_M  ((RTC_CNTL_ULP_CP_MEM_ADDR_SIZE_V)<<(RTC_CNTL_ULP_CP_MEM_ADDR_SIZE_S))
#define RTC_CNTL_ULP_CP_MEM_ADDR_SIZE_V  0x7FF
#define RTC_CNTL_ULP_CP_MEM_ADDR_SIZE_S  11
/* RTC_CNTL_ULP_CP_MEM_ADDR_INIT : R/W ;bitpos:[10:0] ;default: 11'd512 ; */
/*description: .*/
#define RTC_CNTL_ULP_CP_MEM_ADDR_INIT    0x000007FF
#define RTC_CNTL_ULP_CP_MEM_ADDR_INIT_M  ((RTC_CNTL_ULP_CP_MEM_ADDR_INIT_V)<<(RTC_CNTL_ULP_CP_MEM_ADDR_INIT_S))
#define RTC_CNTL_ULP_CP_MEM_ADDR_INIT_V  0x7FF
#define RTC_CNTL_ULP_CP_MEM_ADDR_INIT_S  0

#define RTC_CNTL_COCPU_CTRL_REG          (0x60008000 + 0x104)
/* RTC_CNTL_COCPU_CLKGATE_EN : R/W ;bitpos:[27] ;default: 1'b0 ; */
/*description: .*/
#define RTC_CNTL_COCPU_CLKGATE_EN    (1<<27)
#define RTC_CNTL_COCPU_CLKGATE_EN_M  (1<<27)
#define RTC_CNTL_COCPU_CLKGATE_EN_V  0x1
#define RTC_CNTL_COCPU_CLKGATE_EN_S  27
/* RTC_CNTL_COCPU_SW_INT_TRIGGER : WO ;bitpos:[26] ;default: 1'b0 ; */
/*description: trigger cocpu register interrupt.*/
#define RTC_CNTL_COCPU_SW_INT_TRIGGER    (1<<26)
#define RTC_CNTL_COCPU_SW_INT_TRIGGER_M  (1<<26)
#define RTC_CNTL_COCPU_SW_INT_TRIGGER_V  0x1
#define RTC_CNTL_COCPU_SW_INT_TRIGGER_S  26
/* RTC_CNTL_COCPU_DONE : R/W ;bitpos:[25] ;default: 1'b0 ; */
/*description: done signal used by riscv to control timer. .*/
#define RTC_CNTL_COCPU_DONE    (1<<25)
#define RTC_CNTL_COCPU_DONE_M  (1<<25)
#define RTC_CNTL_COCPU_DONE_V  0x1
#define RTC_CNTL_COCPU_DONE_S  25
/* RTC_CNTL_COCPU_DONE_FORCE : R/W ;bitpos:[24] ;default: 1'b0 ; */
/*description: 1: select riscv done 0: select ulp done.*/
#define RTC_CNTL_COCPU_DONE_FORCE    (1<<24)
#define RTC_CNTL_COCPU_DONE_FORCE_M  (1<<24)
#define RTC_CNTL_COCPU_DONE_FORCE_V  0x1
#define RTC_CNTL_COCPU_DONE_FORCE_S  24
/* RTC_CNTL_COCPU_SEL : R/W ;bitpos:[23] ;default: 1'b1 ; */
/*description: 1: old ULP 0: new riscV.*/
#define RTC_CNTL_COCPU_SEL    (1<<23)
#define RTC_CNTL_COCPU_SEL_M  (1<<23)
#define RTC_CNTL_COCPU_SEL_V  0x1
#define RTC_CNTL_COCPU_SEL_S  23
/* RTC_CNTL_COCPU_SHUT_RESET_EN : R/W ;bitpos:[22] ;default: 1'b0 ; */
/*description: to reset cocpu.*/
#define RTC_CNTL_COCPU_SHUT_RESET_EN    (1<<22)
#define RTC_CNTL_COCPU_SHUT_RESET_EN_M  (1<<22)
#define RTC_CNTL_COCPU_SHUT_RESET_EN_V  0x1
#define RTC_CNTL_COCPU_SHUT_RESET_EN_S  22
/* RTC_CNTL_COCPU_SHUT_2_CLK_DIS : R/W ;bitpos:[21:14] ;default: 8'd40 ; */
/*description: time from shut cocpu to disable clk.*/
#define RTC_CNTL_COCPU_SHUT_2_CLK_DIS    0x000000FF
#define RTC_CNTL_COCPU_SHUT_2_CLK_DIS_M  ((RTC_CNTL_COCPU_SHUT_2_CLK_DIS_V)<<(RTC_CNTL_COCPU_SHUT_2_CLK_DIS_S))
#define RTC_CNTL_COCPU_SHUT_2_CLK_DIS_V  0xFF
#define RTC_CNTL_COCPU_SHUT_2_CLK_DIS_S  14
/* RTC_CNTL_COCPU_SHUT : R/W ;bitpos:[13] ;default: 1'b0 ; */
/*description: to shut cocpu.*/
#define RTC_CNTL_COCPU_SHUT    (1<<13)
#define RTC_CNTL_COCPU_SHUT_M  (1<<13)
#define RTC_CNTL_COCPU_SHUT_V  0x1
#define RTC_CNTL_COCPU_SHUT_S  13
/* RTC_CNTL_COCPU_START_2_INTR_EN : R/W ;bitpos:[12:7] ;default: 6'd16 ; */
/*description: time from start cocpu to give start interrupt.*/
#define RTC_CNTL_COCPU_START_2_INTR_EN    0x0000003F
#define RTC_CNTL_COCPU_START_2_INTR_EN_M  ((RTC_CNTL_COCPU_START_2_INTR_EN_V)<<(RTC_CNTL_COCPU_START_2_INTR_EN_S))
#define RTC_CNTL_COCPU_START_2_INTR_EN_V  0x3F
#define RTC_CNTL_COCPU_START_2_INTR_EN_S  7
/* RTC_CNTL_COCPU_START_2_RESET_DIS : R/W ;bitpos:[6:1] ;default: 6'd8 ; */
/*description: time from start cocpu to pull down reset.*/
#define RTC_CNTL_COCPU_START_2_RESET_DIS    0x0000003F
#define RTC_CNTL_COCPU_START_2_RESET_DIS_M  ((RTC_CNTL_COCPU_START_2_RESET_DIS_V)<<(RTC_CNTL_COCPU_START_2_RESET_DIS_S))
#define RTC_CNTL_COCPU_START_2_RESET_DIS_V  0x3F
#define RTC_CNTL_COCPU_START_2_RESET_DIS_S  1
/* RTC_CNTL_COCPU_CLK_FO : R/W ;bitpos:[0] ;default: 1'b0 ; */
/*description: cocpu clk force on.*/
#define RTC_CNTL_COCPU_CLK_FO    (1<<0)
#define RTC_CNTL_COCPU_CLK_FO_M  (1<<0)
#define RTC_CNTL_COCPU_CLK_FO_V  0x1
#define RTC_CNTL_COCPU_CLK_FO_S  0

#define RTC_CNTL_TOUCH_CTRL1_REG          (0x60008000 + 0x108)
/* RTC_CNTL_TOUCH_MEAS_NUM : R/W ;bitpos:[31:16] ;default: 16'h1000 ; */
/*description: the meas length (in 8MHz).*/
#define RTC_CNTL_TOUCH_MEAS_NUM    0x0000FFFF
#define RTC_CNTL_TOUCH_MEAS_NUM_M  ((RTC_CNTL_TOUCH_MEAS_NUM_V)<<(RTC_CNTL_TOUCH_MEAS_NUM_S))
#define RTC_CNTL_TOUCH_MEAS_NUM_V  0xFFFF
#define RTC_CNTL_TOUCH_MEAS_NUM_S  16
/* RTC_CNTL_TOUCH_SLEEP_CYCLES : R/W ;bitpos:[15:0] ;default: 16'h100 ; */
/*description: sleep cycles for timer.*/
#define RTC_CNTL_TOUCH_SLEEP_CYCLES    0x0000FFFF
#define RTC_CNTL_TOUCH_SLEEP_CYCLES_M  ((RTC_CNTL_TOUCH_SLEEP_CYCLES_V)<<(RTC_CNTL_TOUCH_SLEEP_CYCLES_S))
#define RTC_CNTL_TOUCH_SLEEP_CYCLES_V  0xFFFF
#define RTC_CNTL_TOUCH_SLEEP_CYCLES_S  0

#define RTC_CNTL_TOUCH_CTRL2_REG          (0x60008000 + 0x10C)
/* RTC_CNTL_TOUCH_CLKGATE_EN : R/W ;bitpos:[31] ;default: 1'b0 ; */
/*description: touch clock enable.*/
#define RTC_CNTL_TOUCH_CLKGATE_EN    (1<<31)
#define RTC_CNTL_TOUCH_CLKGATE_EN_M  (1<<31)
#define RTC_CNTL_TOUCH_CLKGATE_EN_V  0x1
#define RTC_CNTL_TOUCH_CLKGATE_EN_S  31
/* RTC_CNTL_TOUCH_CLK_FO : R/W ;bitpos:[30] ;default: 1'b0 ; */
/*description: touch clock force on.*/
#define RTC_CNTL_TOUCH_CLK_FO    (1<<30)
#define RTC_CNTL_TOUCH_CLK_FO_M  (1<<30)
#define RTC_CNTL_TOUCH_CLK_FO_V  0x1
#define RTC_CNTL_TOUCH_CLK_FO_S  30
/* RTC_CNTL_TOUCH_RESET : R/W ;bitpos:[29] ;default: 1'b0 ; */
/*description: reset upgrade touch.*/
#define RTC_CNTL_TOUCH_RESET    (1<<29)
#define RTC_CNTL_TOUCH_RESET_M  (1<<29)
#define RTC_CNTL_TOUCH_RESET_V  0x1
#define RTC_CNTL_TOUCH_RESET_S  29
/* RTC_CNTL_TOUCH_TIMER_FORCE_DONE : R/W ;bitpos:[28:27] ;default: 2'b0 ; */
/*description: force touch timer done.*/
#define RTC_CNTL_TOUCH_TIMER_FORCE_DONE    0x00000003
#define RTC_CNTL_TOUCH_TIMER_FORCE_DONE_M  ((RTC_CNTL_TOUCH_TIMER_FORCE_DONE_V)<<(RTC_CNTL_TOUCH_TIMER_FORCE_DONE_S))
#define RTC_CNTL_TOUCH_TIMER_FORCE_DONE_V  0x3
#define RTC_CNTL_TOUCH_TIMER_FORCE_DONE_S  27
/* RTC_CNTL_TOUCH_SLP_CYC_DIV : R/W ;bitpos:[26:25] ;default: 2'd0 ; */
/*description: when a touch pad is active.*/
#define RTC_CNTL_TOUCH_SLP_CYC_DIV    0x00000003
#define RTC_CNTL_TOUCH_SLP_CYC_DIV_M  ((RTC_CNTL_TOUCH_SLP_CYC_DIV_V)<<(RTC_CNTL_TOUCH_SLP_CYC_DIV_S))
#define RTC_CNTL_TOUCH_SLP_CYC_DIV_V  0x3
#define RTC_CNTL_TOUCH_SLP_CYC_DIV_S  25
/* RTC_CNTL_TOUCH_XPD_WAIT : R/W ;bitpos:[24:17] ;default: 8'h4 ; */
/*description: the waiting cycles (in 8MHz) between TOUCH_START and TOUCH_XPD.*/
#define RTC_CNTL_TOUCH_XPD_WAIT    0x000000FF
#define RTC_CNTL_TOUCH_XPD_WAIT_M  ((RTC_CNTL_TOUCH_XPD_WAIT_V)<<(RTC_CNTL_TOUCH_XPD_WAIT_S))
#define RTC_CNTL_TOUCH_XPD_WAIT_V  0xFF
#define RTC_CNTL_TOUCH_XPD_WAIT_S  17
/* RTC_CNTL_TOUCH_START_FORCE : R/W ;bitpos:[16] ;default: 1'b0 ; */
/*description: 1: to start touch fsm by SW.*/
#define RTC_CNTL_TOUCH_START_FORCE    (1<<16)
#define RTC_CNTL_TOUCH_START_FORCE_M  (1<<16)
#define RTC_CNTL_TOUCH_START_FORCE_V  0x1
#define RTC_CNTL_TOUCH_START_FORCE_S  16
/* RTC_CNTL_TOUCH_START_EN : R/W ;bitpos:[15] ;default: 1'b0 ; */
/*description: 1: start touch fsm.*/
#define RTC_CNTL_TOUCH_START_EN    (1<<15)
#define RTC_CNTL_TOUCH_START_EN_M  (1<<15)
#define RTC_CNTL_TOUCH_START_EN_V  0x1
#define RTC_CNTL_TOUCH_START_EN_S  15
/* RTC_CNTL_TOUCH_START_FSM_EN : R/W ;bitpos:[14] ;default: 1'b1 ; */
/*description: 1: TOUCH_START & TOUCH_XPD is controlled by touch fsm.*/
#define RTC_CNTL_TOUCH_START_FSM_EN    (1<<14)
#define RTC_CNTL_TOUCH_START_FSM_EN_M  (1<<14)
#define RTC_CNTL_TOUCH_START_FSM_EN_V  0x1
#define RTC_CNTL_TOUCH_START_FSM_EN_S  14
/* RTC_CNTL_TOUCH_SLP_TIMER_EN : R/W ;bitpos:[13] ;default: 1'd0 ; */
/*description: touch timer enable bit.*/
#define RTC_CNTL_TOUCH_SLP_TIMER_EN    (1<<13)
#define RTC_CNTL_TOUCH_SLP_TIMER_EN_M  (1<<13)
#define RTC_CNTL_TOUCH_SLP_TIMER_EN_V  0x1
#define RTC_CNTL_TOUCH_SLP_TIMER_EN_S  13
/* RTC_CNTL_TOUCH_DBIAS : R/W ;bitpos:[12] ;default: 1'b0 ; */
/*description: 1:use self bias 0:use bandgap bias.*/
#define RTC_CNTL_TOUCH_DBIAS    (1<<12)
#define RTC_CNTL_TOUCH_DBIAS_M  (1<<12)
#define RTC_CNTL_TOUCH_DBIAS_V  0x1
#define RTC_CNTL_TOUCH_DBIAS_S  12
/* RTC_CNTL_TOUCH_REFC : R/W ;bitpos:[11:9] ;default: 3'h0 ; */
/*description: TOUCH pad0 reference cap.*/
#define RTC_CNTL_TOUCH_REFC    0x00000007
#define RTC_CNTL_TOUCH_REFC_M  ((RTC_CNTL_TOUCH_REFC_V)<<(RTC_CNTL_TOUCH_REFC_S))
#define RTC_CNTL_TOUCH_REFC_V  0x7
#define RTC_CNTL_TOUCH_REFC_S  9
/* RTC_CNTL_TOUCH_XPD_BIAS : R/W ;bitpos:[8] ;default: 1'd0 ; */
/*description: TOUCH_XPD_BIAS.*/
#define RTC_CNTL_TOUCH_XPD_BIAS    (1<<8)
#define RTC_CNTL_TOUCH_XPD_BIAS_M  (1<<8)
#define RTC_CNTL_TOUCH_XPD_BIAS_V  0x1
#define RTC_CNTL_TOUCH_XPD_BIAS_S  8
/* RTC_CNTL_TOUCH_DREFH : R/W ;bitpos:[7:6] ;default: 2'b11 ; */
/*description: TOUCH_DREFH.*/
#define RTC_CNTL_TOUCH_DREFH    0x00000003
#define RTC_CNTL_TOUCH_DREFH_M  ((RTC_CNTL_TOUCH_DREFH_V)<<(RTC_CNTL_TOUCH_DREFH_S))
#define RTC_CNTL_TOUCH_DREFH_V  0x3
#define RTC_CNTL_TOUCH_DREFH_S  6
/* RTC_CNTL_TOUCH_DREFL : R/W ;bitpos:[5:4] ;default: 2'b00 ; */
/*description: TOUCH_DREFL.*/
#define RTC_CNTL_TOUCH_DREFL    0x00000003
#define RTC_CNTL_TOUCH_DREFL_M  ((RTC_CNTL_TOUCH_DREFL_V)<<(RTC_CNTL_TOUCH_DREFL_S))
#define RTC_CNTL_TOUCH_DREFL_V  0x3
#define RTC_CNTL_TOUCH_DREFL_S  4
/* RTC_CNTL_TOUCH_DRANGE : R/W ;bitpos:[3:2] ;default: 2'b11 ; */
/*description: TOUCH_DRANGE.*/
#define RTC_CNTL_TOUCH_DRANGE    0x00000003
#define RTC_CNTL_TOUCH_DRANGE_M  ((RTC_CNTL_TOUCH_DRANGE_V)<<(RTC_CNTL_TOUCH_DRANGE_S))
#define RTC_CNTL_TOUCH_DRANGE_V  0x3
#define RTC_CNTL_TOUCH_DRANGE_S  2

#define RTC_CNTL_TOUCH_SCAN_CTRL_REG          (0x60008000 + 0x110)
/* RTC_CNTL_TOUCH_OUT_RING : R/W ;bitpos:[31:28] ;default: 4'hf ; */
/*description: select out ring pad.*/
#define RTC_CNTL_TOUCH_OUT_RING    0x0000000F
#define RTC_CNTL_TOUCH_OUT_RING_M  ((RTC_CNTL_TOUCH_OUT_RING_V)<<(RTC_CNTL_TOUCH_OUT_RING_S))
#define RTC_CNTL_TOUCH_OUT_RING_V  0xF
#define RTC_CNTL_TOUCH_OUT_RING_S  28
/* RTC_CNTL_TOUCH_BUFDRV : R/W ;bitpos:[27:25] ;default: 3'h0 ; */
/*description: touch7 buffer driver strength.*/
#define RTC_CNTL_TOUCH_BUFDRV    0x00000007
#define RTC_CNTL_TOUCH_BUFDRV_M  ((RTC_CNTL_TOUCH_BUFDRV_V)<<(RTC_CNTL_TOUCH_BUFDRV_S))
#define RTC_CNTL_TOUCH_BUFDRV_V  0x7
#define RTC_CNTL_TOUCH_BUFDRV_S  25
/* RTC_CNTL_TOUCH_SCAN_PAD_MAP : R/W ;bitpos:[24:10] ;default: 15'h0 ; */
/*description: touch scan mode pad enable map.*/
#define RTC_CNTL_TOUCH_SCAN_PAD_MAP    0x00007FFF
#define RTC_CNTL_TOUCH_SCAN_PAD_MAP_M  ((RTC_CNTL_TOUCH_SCAN_PAD_MAP_V)<<(RTC_CNTL_TOUCH_SCAN_PAD_MAP_S))
#define RTC_CNTL_TOUCH_SCAN_PAD_MAP_V  0x7FFF
#define RTC_CNTL_TOUCH_SCAN_PAD_MAP_S  10
/* RTC_CNTL_TOUCH_SHIELD_PAD_EN : R/W ;bitpos:[9] ;default: 1'b0 ; */
/*description: touch pad14 will be used as shield.*/
#define RTC_CNTL_TOUCH_SHIELD_PAD_EN    (1<<9)
#define RTC_CNTL_TOUCH_SHIELD_PAD_EN_M  (1<<9)
#define RTC_CNTL_TOUCH_SHIELD_PAD_EN_V  0x1
#define RTC_CNTL_TOUCH_SHIELD_PAD_EN_S  9
/* RTC_CNTL_TOUCH_INACTIVE_CONNECTION : R/W ;bitpos:[8] ;default: 1'b1 ; */
/*description: inactive touch pads connect to 1: gnd 0: HighZ.*/
#define RTC_CNTL_TOUCH_INACTIVE_CONNECTION    (1<<8)
#define RTC_CNTL_TOUCH_INACTIVE_CONNECTION_M  (1<<8)
#define RTC_CNTL_TOUCH_INACTIVE_CONNECTION_V  0x1
#define RTC_CNTL_TOUCH_INACTIVE_CONNECTION_S  8
/* RTC_CNTL_TOUCH_DENOISE_EN : R/W ;bitpos:[2] ;default: 1'b0 ; */
/*description: touch pad0 will be used to de-noise.*/
#define RTC_CNTL_TOUCH_DENOISE_EN    (1<<2)
#define RTC_CNTL_TOUCH_DENOISE_EN_M  (1<<2)
#define RTC_CNTL_TOUCH_DENOISE_EN_V  0x1
#define RTC_CNTL_TOUCH_DENOISE_EN_S  2
/* RTC_CNTL_TOUCH_DENOISE_RES : R/W ;bitpos:[1:0] ;default: 2'd2 ; */
/*description: De-noise resolution: 12/10/8/4 bit.*/
#define RTC_CNTL_TOUCH_DENOISE_RES    0x00000003
#define RTC_CNTL_TOUCH_DENOISE_RES_M  ((RTC_CNTL_TOUCH_DENOISE_RES_V)<<(RTC_CNTL_TOUCH_DENOISE_RES_S))
#define RTC_CNTL_TOUCH_DENOISE_RES_V  0x3
#define RTC_CNTL_TOUCH_DENOISE_RES_S  0

#define RTC_CNTL_TOUCH_SLP_THRES_REG          (0x60008000 + 0x114)
/* RTC_CNTL_TOUCH_SLP_PAD : R/W ;bitpos:[31:27] ;default: 4'hf ; */
/*description:  .*/
#define RTC_CNTL_TOUCH_SLP_PAD    0x0000001F
#define RTC_CNTL_TOUCH_SLP_PAD_M  ((RTC_CNTL_TOUCH_SLP_PAD_V)<<(RTC_CNTL_TOUCH_SLP_PAD_S))
#define RTC_CNTL_TOUCH_SLP_PAD_V  0x1F
#define RTC_CNTL_TOUCH_SLP_PAD_S  27
/* RTC_CNTL_TOUCH_SLP_APPROACH_EN : R/W ;bitpos:[26] ;default: 1'b0 ; */
/*description: sleep pad approach function enable.*/
#define RTC_CNTL_TOUCH_SLP_APPROACH_EN    (1<<26)
#define RTC_CNTL_TOUCH_SLP_APPROACH_EN_M  (1<<26)
#define RTC_CNTL_TOUCH_SLP_APPROACH_EN_V  0x1
#define RTC_CNTL_TOUCH_SLP_APPROACH_EN_S  26
/* RTC_CNTL_TOUCH_SLP_TH : R/W ;bitpos:[21:0] ;default: 22'h0 ; */
/*description: the threshold for sleep touch pad.*/
#define RTC_CNTL_TOUCH_SLP_TH    0x003FFFFF
#define RTC_CNTL_TOUCH_SLP_TH_M  ((RTC_CNTL_TOUCH_SLP_TH_V)<<(RTC_CNTL_TOUCH_SLP_TH_S))
#define RTC_CNTL_TOUCH_SLP_TH_V  0x3FFFFF
#define RTC_CNTL_TOUCH_SLP_TH_S  0

#define RTC_CNTL_TOUCH_APPROACH_REG          (0x60008000 + 0x118)
/* RTC_CNTL_TOUCH_APPROACH_MEAS_TIME : R/W ;bitpos:[31:24] ;default: 8'd80 ; */
/*description: approach pads total meas times.*/
#define RTC_CNTL_TOUCH_APPROACH_MEAS_TIME    0x000000FF
#define RTC_CNTL_TOUCH_APPROACH_MEAS_TIME_M  ((RTC_CNTL_TOUCH_APPROACH_MEAS_TIME_V)<<(RTC_CNTL_TOUCH_APPROACH_MEAS_TIME_S))
#define RTC_CNTL_TOUCH_APPROACH_MEAS_TIME_V  0xFF
#define RTC_CNTL_TOUCH_APPROACH_MEAS_TIME_S  24
/* RTC_CNTL_TOUCH_SLP_CHANNEL_CLR : WO ;bitpos:[23] ;default: 1'd0 ; */
/*description: clear touch slp channel.*/
#define RTC_CNTL_TOUCH_SLP_CHANNEL_CLR    (1<<23)
#define RTC_CNTL_TOUCH_SLP_CHANNEL_CLR_M  (1<<23)
#define RTC_CNTL_TOUCH_SLP_CHANNEL_CLR_V  0x1
#define RTC_CNTL_TOUCH_SLP_CHANNEL_CLR_S  23

#define RTC_CNTL_TOUCH_FILTER_CTRL_REG          (0x60008000 + 0x11C)
/* RTC_CNTL_TOUCH_FILTER_EN : R/W ;bitpos:[31] ;default: 1'b1 ; */
/*description: touch filter enable.*/
#define RTC_CNTL_TOUCH_FILTER_EN    (1<<31)
#define RTC_CNTL_TOUCH_FILTER_EN_M  (1<<31)
#define RTC_CNTL_TOUCH_FILTER_EN_V  0x1
#define RTC_CNTL_TOUCH_FILTER_EN_S  31
/* RTC_CNTL_TOUCH_FILTER_MODE : R/W ;bitpos:[30:28] ;default: 3'd1 ; */
/*description: 0: IIR ? 1: IIR ? 2: IIR 1/8 3: Jitter.*/
#define RTC_CNTL_TOUCH_FILTER_MODE    0x00000007
#define RTC_CNTL_TOUCH_FILTER_MODE_M  ((RTC_CNTL_TOUCH_FILTER_MODE_V)<<(RTC_CNTL_TOUCH_FILTER_MODE_S))
#define RTC_CNTL_TOUCH_FILTER_MODE_V  0x7
#define RTC_CNTL_TOUCH_FILTER_MODE_S  28
/* RTC_CNTL_TOUCH_DEBOUNCE : R/W ;bitpos:[27:25] ;default: 3'd3 ; */
/*description: debounce counter.*/
#define RTC_CNTL_TOUCH_DEBOUNCE    0x00000007
#define RTC_CNTL_TOUCH_DEBOUNCE_M  ((RTC_CNTL_TOUCH_DEBOUNCE_V)<<(RTC_CNTL_TOUCH_DEBOUNCE_S))
#define RTC_CNTL_TOUCH_DEBOUNCE_V  0x7
#define RTC_CNTL_TOUCH_DEBOUNCE_S  25
/* RTC_CNTL_TOUCH_CONFIG3 : R/W ;bitpos:[24:23] ;default: 2'd1 ; */
/*description: */
#define RTC_CNTL_TOUCH_CONFIG3 0x00000003
#define RTC_CNTL_TOUCH_CONFIG3_M ((RTC_CNTL_TOUCH_CONFIG3_V) << (RTC_CNTL_TOUCH_CONFIG3_S))
#define RTC_CNTL_TOUCH_CONFIG3_V 0x3
#define RTC_CNTL_TOUCH_CONFIG3_S 23
/* RTC_CNTL_TOUCH_NOISE_THRES : R/W ;bitpos:[22:21] ;default: 2'd1 ; */
/*description: .*/
#define RTC_CNTL_TOUCH_NOISE_THRES    0x00000003
#define RTC_CNTL_TOUCH_NOISE_THRES_M  ((RTC_CNTL_TOUCH_NOISE_THRES_V)<<(RTC_CNTL_TOUCH_NOISE_THRES_S))
#define RTC_CNTL_TOUCH_NOISE_THRES_V  0x3
#define RTC_CNTL_TOUCH_NOISE_THRES_S  21
/* RTC_CNTL_TOUCH_CONFIG2 : R/W ;bitpos:[20:19] ;default: 2'd1 ; */
/*description: */
#define RTC_CNTL_TOUCH_CONFIG2 0x00000003
#define RTC_CNTL_TOUCH_CONFIG2_M ((RTC_CNTL_TOUCH_CONFIG2_V) << (RTC_CNTL_TOUCH_CONFIG2_S))
#define RTC_CNTL_TOUCH_CONFIG2_V 0x3
#define RTC_CNTL_TOUCH_CONFIG2_S 19
/* RTC_CNTL_TOUCH_CONFIG1 : R/W ;bitpos:[18:15] ;default: 4'd5 ; */
/*description: */
#define RTC_CNTL_TOUCH_CONFIG1 0x0000000F
#define RTC_CNTL_TOUCH_CONFIG1_M ((RTC_CNTL_TOUCH_CONFIG1_V) << (RTC_CNTL_TOUCH_CONFIG1_S))
#define RTC_CNTL_TOUCH_CONFIG1_V 0xF
#define RTC_CNTL_TOUCH_CONFIG1_S 15
/* RTC_CNTL_TOUCH_JITTER_STEP : R/W ;bitpos:[14:11] ;default: 4'd1 ; */
/*description: touch jitter step.*/
#define RTC_CNTL_TOUCH_JITTER_STEP    0x0000000F
#define RTC_CNTL_TOUCH_JITTER_STEP_M  ((RTC_CNTL_TOUCH_JITTER_STEP_V)<<(RTC_CNTL_TOUCH_JITTER_STEP_S))
#define RTC_CNTL_TOUCH_JITTER_STEP_V  0xF
#define RTC_CNTL_TOUCH_JITTER_STEP_S  11
/* RTC_CNTL_TOUCH_SMOOTH_LVL : R/W ;bitpos:[10:9] ;default: 2'd0 ; */
/*description: .*/
#define RTC_CNTL_TOUCH_SMOOTH_LVL    0x00000003
#define RTC_CNTL_TOUCH_SMOOTH_LVL_M  ((RTC_CNTL_TOUCH_SMOOTH_LVL_V)<<(RTC_CNTL_TOUCH_SMOOTH_LVL_S))
#define RTC_CNTL_TOUCH_SMOOTH_LVL_V  0x3
#define RTC_CNTL_TOUCH_SMOOTH_LVL_S  9
/* RTC_CNTL_TOUCH_BYPASS_NOISE_THRES : R/W ;bitpos:[8] ;default: 1'b0 ; */
/*description: .*/
#define RTC_CNTL_TOUCH_BYPASS_NOISE_THRES    (1<<8)
#define RTC_CNTL_TOUCH_BYPASS_NOISE_THRES_M  (1<<8)
#define RTC_CNTL_TOUCH_BYPASS_NOISE_THRES_V  0x1
#define RTC_CNTL_TOUCH_BYPASS_NOISE_THRES_S  8
/* RTC_CNTL_TOUCH_BYPASS_NEG_THRES : R/W ;bitpos:[7] ;default: 1'b0 ; */
/*description: */
#define RTC_CNTL_TOUCH_BYPASS_NEG_THRES (1<<7)
#define RTC_CNTL_TOUCH_BYPASS_NEG_THRES_M (1<<7)
#define RTC_CNTL_TOUCH_BYPASS_NEG_THRES_V 0x1
#define RTC_CNTL_TOUCH_BYPASS_NEG_THRES_S 7

#define RTC_CNTL_USB_CONF_REG          (0x60008000 + 0x120)
/* RTC_CNTL_SW_HW_USB_PHY_SEL : R/W ;bitpos:[20] ;default: 1'b0 ; */
/*description: .*/
#define RTC_CNTL_SW_HW_USB_PHY_SEL    (1<<20)
#define RTC_CNTL_SW_HW_USB_PHY_SEL_M  (1<<20)
#define RTC_CNTL_SW_HW_USB_PHY_SEL_V  0x1
#define RTC_CNTL_SW_HW_USB_PHY_SEL_S  20
/* RTC_CNTL_SW_USB_PHY_SEL : R/W ;bitpos:[19] ;default: 1'b0 ; */
/*description: .*/
#define RTC_CNTL_SW_USB_PHY_SEL    (1<<19)
#define RTC_CNTL_SW_USB_PHY_SEL_M  (1<<19)
#define RTC_CNTL_SW_USB_PHY_SEL_V  0x1
#define RTC_CNTL_SW_USB_PHY_SEL_S  19
/* RTC_CNTL_IO_MUX_RESET_DISABLE : R/W ;bitpos:[18] ;default: 1'd0 ; */
/*description: .*/
#define RTC_CNTL_IO_MUX_RESET_DISABLE    (1<<18)
#define RTC_CNTL_IO_MUX_RESET_DISABLE_M  (1<<18)
#define RTC_CNTL_IO_MUX_RESET_DISABLE_V  0x1
#define RTC_CNTL_IO_MUX_RESET_DISABLE_S  18
/* RTC_CNTL_USB_RESET_DISABLE : R/W ;bitpos:[17] ;default: 1'd0 ; */
/*description: .*/
#define RTC_CNTL_USB_RESET_DISABLE    (1<<17)
#define RTC_CNTL_USB_RESET_DISABLE_M  (1<<17)
#define RTC_CNTL_USB_RESET_DISABLE_V  0x1
#define RTC_CNTL_USB_RESET_DISABLE_S  17
/* RTC_CNTL_USB_TX_EN_OVERRIDE : R/W ;bitpos:[16] ;default: 1'd0 ; */
/*description: .*/
#define RTC_CNTL_USB_TX_EN_OVERRIDE    (1<<16)
#define RTC_CNTL_USB_TX_EN_OVERRIDE_M  (1<<16)
#define RTC_CNTL_USB_TX_EN_OVERRIDE_V  0x1
#define RTC_CNTL_USB_TX_EN_OVERRIDE_S  16
/* RTC_CNTL_USB_TX_EN : R/W ;bitpos:[15] ;default: 1'd0 ; */
/*description: .*/
#define RTC_CNTL_USB_TX_EN    (1<<15)
#define RTC_CNTL_USB_TX_EN_M  (1<<15)
#define RTC_CNTL_USB_TX_EN_V  0x1
#define RTC_CNTL_USB_TX_EN_S  15
/* RTC_CNTL_USB_TXP : R/W ;bitpos:[14] ;default: 1'd0 ; */
/*description: .*/
#define RTC_CNTL_USB_TXP    (1<<14)
#define RTC_CNTL_USB_TXP_M  (1<<14)
#define RTC_CNTL_USB_TXP_V  0x1
#define RTC_CNTL_USB_TXP_S  14
/* RTC_CNTL_USB_TXM : R/W ;bitpos:[13] ;default: 1'd0 ; */
/*description: .*/
#define RTC_CNTL_USB_TXM    (1<<13)
#define RTC_CNTL_USB_TXM_M  (1<<13)
#define RTC_CNTL_USB_TXM_V  0x1
#define RTC_CNTL_USB_TXM_S  13
/* RTC_CNTL_USB_PAD_ENABLE : R/W ;bitpos:[12] ;default: 1'd0 ; */
/*description: .*/
#define RTC_CNTL_USB_PAD_ENABLE    (1<<12)
#define RTC_CNTL_USB_PAD_ENABLE_M  (1<<12)
#define RTC_CNTL_USB_PAD_ENABLE_V  0x1
#define RTC_CNTL_USB_PAD_ENABLE_S  12
/* RTC_CNTL_USB_PAD_ENABLE_OVERRIDE : R/W ;bitpos:[11] ;default: 1'd0 ; */
/*description: .*/
#define RTC_CNTL_USB_PAD_ENABLE_OVERRIDE    (1<<11)
#define RTC_CNTL_USB_PAD_ENABLE_OVERRIDE_M  (1<<11)
#define RTC_CNTL_USB_PAD_ENABLE_OVERRIDE_V  0x1
#define RTC_CNTL_USB_PAD_ENABLE_OVERRIDE_S  11
/* RTC_CNTL_USB_PULLUP_VALUE : R/W ;bitpos:[10] ;default: 1'd0 ; */
/*description: .*/
#define RTC_CNTL_USB_PULLUP_VALUE    (1<<10)
#define RTC_CNTL_USB_PULLUP_VALUE_M  (1<<10)
#define RTC_CNTL_USB_PULLUP_VALUE_V  0x1
#define RTC_CNTL_USB_PULLUP_VALUE_S  10
/* RTC_CNTL_USB_DM_PULLDOWN : R/W ;bitpos:[9] ;default: 1'd0 ; */
/*description: .*/
#define RTC_CNTL_USB_DM_PULLDOWN    (1<<9)
#define RTC_CNTL_USB_DM_PULLDOWN_M  (1<<9)
#define RTC_CNTL_USB_DM_PULLDOWN_V  0x1
#define RTC_CNTL_USB_DM_PULLDOWN_S  9
/* RTC_CNTL_USB_DM_PULLUP : R/W ;bitpos:[8] ;default: 1'd0 ; */
/*description: .*/
#define RTC_CNTL_USB_DM_PULLUP    (1<<8)
#define RTC_CNTL_USB_DM_PULLUP_M  (1<<8)
#define RTC_CNTL_USB_DM_PULLUP_V  0x1
#define RTC_CNTL_USB_DM_PULLUP_S  8
/* RTC_CNTL_USB_DP_PULLDOWN : R/W ;bitpos:[7] ;default: 1'd0 ; */
/*description: .*/
#define RTC_CNTL_USB_DP_PULLDOWN    (1<<7)
#define RTC_CNTL_USB_DP_PULLDOWN_M  (1<<7)
#define RTC_CNTL_USB_DP_PULLDOWN_V  0x1
#define RTC_CNTL_USB_DP_PULLDOWN_S  7
/* RTC_CNTL_USB_DP_PULLUP : R/W ;bitpos:[6] ;default: 1'd0 ; */
/*description: .*/
#define RTC_CNTL_USB_DP_PULLUP    (1<<6)
#define RTC_CNTL_USB_DP_PULLUP_M  (1<<6)
#define RTC_CNTL_USB_DP_PULLUP_V  0x1
#define RTC_CNTL_USB_DP_PULLUP_S  6
/* RTC_CNTL_USB_PAD_PULL_OVERRIDE : R/W ;bitpos:[5] ;default: 1'd0 ; */
/*description: .*/
#define RTC_CNTL_USB_PAD_PULL_OVERRIDE    (1<<5)
#define RTC_CNTL_USB_PAD_PULL_OVERRIDE_M  (1<<5)
#define RTC_CNTL_USB_PAD_PULL_OVERRIDE_V  0x1
#define RTC_CNTL_USB_PAD_PULL_OVERRIDE_S  5
/* RTC_CNTL_USB_VREF_OVERRIDE : R/W ;bitpos:[4] ;default: 1'd0 ; */
/*description: .*/
#define RTC_CNTL_USB_VREF_OVERRIDE    (1<<4)
#define RTC_CNTL_USB_VREF_OVERRIDE_M  (1<<4)
#define RTC_CNTL_USB_VREF_OVERRIDE_V  0x1
#define RTC_CNTL_USB_VREF_OVERRIDE_S  4
/* RTC_CNTL_USB_VREFL : R/W ;bitpos:[3:2] ;default: 2'd0 ; */
/*description: .*/
#define RTC_CNTL_USB_VREFL    0x00000003
#define RTC_CNTL_USB_VREFL_M  ((RTC_CNTL_USB_VREFL_V)<<(RTC_CNTL_USB_VREFL_S))
#define RTC_CNTL_USB_VREFL_V  0x3
#define RTC_CNTL_USB_VREFL_S  2
/* RTC_CNTL_USB_VREFH : R/W ;bitpos:[1:0] ;default: 2'd0 ; */
/*description: .*/
#define RTC_CNTL_USB_VREFH    0x00000003
#define RTC_CNTL_USB_VREFH_M  ((RTC_CNTL_USB_VREFH_V)<<(RTC_CNTL_USB_VREFH_S))
#define RTC_CNTL_USB_VREFH_V  0x3
#define RTC_CNTL_USB_VREFH_S  0

#define RTC_CNTL_TOUCH_TIMEOUT_CTRL_REG          (0x60008000 + 0x124)
/* RTC_CNTL_TOUCH_TIMEOUT_EN : R/W ;bitpos:[22] ;default: 1'b1 ; */
/*description: .*/
#define RTC_CNTL_TOUCH_TIMEOUT_EN    (1<<22)
#define RTC_CNTL_TOUCH_TIMEOUT_EN_M  (1<<22)
#define RTC_CNTL_TOUCH_TIMEOUT_EN_V  0x1
#define RTC_CNTL_TOUCH_TIMEOUT_EN_S  22
/* RTC_CNTL_TOUCH_TIMEOUT_NUM : R/W ;bitpos:[21:0] ;default: 22'h3fffff ; */
/*description: .*/
#define RTC_CNTL_TOUCH_TIMEOUT_NUM    0x003FFFFF
#define RTC_CNTL_TOUCH_TIMEOUT_NUM_M  ((RTC_CNTL_TOUCH_TIMEOUT_NUM_V)<<(RTC_CNTL_TOUCH_TIMEOUT_NUM_S))
#define RTC_CNTL_TOUCH_TIMEOUT_NUM_V  0x3FFFFF
#define RTC_CNTL_TOUCH_TIMEOUT_NUM_S  0

#define RTC_CNTL_SLP_REJECT_CAUSE_REG          (0x60008000 + 0x128)
/* RTC_CNTL_REJECT_CAUSE : RO ;bitpos:[17:0] ;default: 18'd0 ; */
/*description: sleep reject cause.*/
#define RTC_CNTL_REJECT_CAUSE    0x0003FFFF
#define RTC_CNTL_REJECT_CAUSE_M  ((RTC_CNTL_REJECT_CAUSE_V)<<(RTC_CNTL_REJECT_CAUSE_S))
#define RTC_CNTL_REJECT_CAUSE_V  0x3FFFF
#define RTC_CNTL_REJECT_CAUSE_S  0

#define RTC_CNTL_OPTION1_REG          (0x60008000 + 0x12C)
/* RTC_CNTL_FORCE_DOWNLOAD_BOOT : R/W ;bitpos:[0] ;default: 1'd0 ; */
/*description: .*/
#define RTC_CNTL_FORCE_DOWNLOAD_BOOT    (1<<0)
#define RTC_CNTL_FORCE_DOWNLOAD_BOOT_M  (1<<0)
#define RTC_CNTL_FORCE_DOWNLOAD_BOOT_V  0x1
#define RTC_CNTL_FORCE_DOWNLOAD_BOOT_S  0

#define RTC_CNTL_SLP_WAKEUP_CAUSE_REG          (0x60008000 + 0x130)
/* RTC_CNTL_WAKEUP_CAUSE : RO ;bitpos:[16:0] ;default: 17'd0 ; */
/*description: sleep wakeup cause.*/
#define RTC_CNTL_WAKEUP_CAUSE    0x0001FFFF
#define RTC_CNTL_WAKEUP_CAUSE_M  ((RTC_CNTL_WAKEUP_CAUSE_V)<<(RTC_CNTL_WAKEUP_CAUSE_S))
#define RTC_CNTL_WAKEUP_CAUSE_V  0x1FFFF
#define RTC_CNTL_WAKEUP_CAUSE_S  0

#define RTC_CNTL_ULP_CP_TIMER_1_REG          (0x60008000 + 0x134)
/* RTC_CNTL_ULP_CP_TIMER_SLP_CYCLE : R/W ;bitpos:[31:8] ;default: 24'd200 ; */
/*description: sleep cycles for ULP-coprocessor timer.*/
#define RTC_CNTL_ULP_CP_TIMER_SLP_CYCLE    0x00FFFFFF
#define RTC_CNTL_ULP_CP_TIMER_SLP_CYCLE_M  ((RTC_CNTL_ULP_CP_TIMER_SLP_CYCLE_V)<<(RTC_CNTL_ULP_CP_TIMER_SLP_CYCLE_S))
#define RTC_CNTL_ULP_CP_TIMER_SLP_CYCLE_V  0xFFFFFF
#define RTC_CNTL_ULP_CP_TIMER_SLP_CYCLE_S  8

#define RTC_CNTL_INT_ENA_W1TS_REG          (0x60008000 + 0x138)
/* RTC_CNTL_TOUCH_APPROACH_LOOP_DONE_INT_ENA_W1TS : WO ;bitpos:[20] ;default: 1'b0 ; */
/*description: .*/
#define RTC_CNTL_TOUCH_APPROACH_LOOP_DONE_INT_ENA_W1TS    (1<<20)
#define RTC_CNTL_TOUCH_APPROACH_LOOP_DONE_INT_ENA_W1TS_M  (1<<20)
#define RTC_CNTL_TOUCH_APPROACH_LOOP_DONE_INT_ENA_W1TS_V  0x1
#define RTC_CNTL_TOUCH_APPROACH_LOOP_DONE_INT_ENA_W1TS_S  20
/* RTC_CNTL_GLITCH_DET_INT_ENA_W1TS : WO ;bitpos:[19] ;default: 1'b0 ; */
/*description: enbale gitch det interrupt.*/
#define RTC_CNTL_GLITCH_DET_INT_ENA_W1TS    (1<<19)
#define RTC_CNTL_GLITCH_DET_INT_ENA_W1TS_M  (1<<19)
#define RTC_CNTL_GLITCH_DET_INT_ENA_W1TS_V  0x1
#define RTC_CNTL_GLITCH_DET_INT_ENA_W1TS_S  19
/* RTC_CNTL_TOUCH_TIMEOUT_INT_ENA_W1TS : WO ;bitpos:[18] ;default: 1'b0 ; */
/*description: enable touch timeout interrupt.*/
#define RTC_CNTL_TOUCH_TIMEOUT_INT_ENA_W1TS    (1<<18)
#define RTC_CNTL_TOUCH_TIMEOUT_INT_ENA_W1TS_M  (1<<18)
#define RTC_CNTL_TOUCH_TIMEOUT_INT_ENA_W1TS_V  0x1
#define RTC_CNTL_TOUCH_TIMEOUT_INT_ENA_W1TS_S  18
/* RTC_CNTL_COCPU_TRAP_INT_ENA_W1TS : WO ;bitpos:[17] ;default: 1'b0 ; */
/*description: enable cocpu trap interrupt.*/
#define RTC_CNTL_COCPU_TRAP_INT_ENA_W1TS    (1<<17)
#define RTC_CNTL_COCPU_TRAP_INT_ENA_W1TS_M  (1<<17)
#define RTC_CNTL_COCPU_TRAP_INT_ENA_W1TS_V  0x1
#define RTC_CNTL_COCPU_TRAP_INT_ENA_W1TS_S  17
/* RTC_CNTL_XTAL32K_DEAD_INT_ENA_W1TS : WO ;bitpos:[16] ;default: 1'b0 ; */
/*description: enable xtal32k_dead  interrupt.*/
#define RTC_CNTL_XTAL32K_DEAD_INT_ENA_W1TS    (1<<16)
#define RTC_CNTL_XTAL32K_DEAD_INT_ENA_W1TS_M  (1<<16)
#define RTC_CNTL_XTAL32K_DEAD_INT_ENA_W1TS_V  0x1
#define RTC_CNTL_XTAL32K_DEAD_INT_ENA_W1TS_S  16
/* RTC_CNTL_SWD_INT_ENA_W1TS : WO ;bitpos:[15] ;default: 1'b0 ; */
/*description: enable super watch dog interrupt.*/
#define RTC_CNTL_SWD_INT_ENA_W1TS    (1<<15)
#define RTC_CNTL_SWD_INT_ENA_W1TS_M  (1<<15)
#define RTC_CNTL_SWD_INT_ENA_W1TS_V  0x1
#define RTC_CNTL_SWD_INT_ENA_W1TS_S  15
/* RTC_CNTL_SARADC2_INT_ENA_W1TS : WO ;bitpos:[14] ;default: 1'b0 ; */
/*description: enable saradc2 interrupt.*/
#define RTC_CNTL_SARADC2_INT_ENA_W1TS    (1<<14)
#define RTC_CNTL_SARADC2_INT_ENA_W1TS_M  (1<<14)
#define RTC_CNTL_SARADC2_INT_ENA_W1TS_V  0x1
#define RTC_CNTL_SARADC2_INT_ENA_W1TS_S  14
/* RTC_CNTL_COCPU_INT_ENA_W1TS : WO ;bitpos:[13] ;default: 1'b0 ; */
/*description: enable riscV cocpu interrupt.*/
#define RTC_CNTL_COCPU_INT_ENA_W1TS    (1<<13)
#define RTC_CNTL_COCPU_INT_ENA_W1TS_M  (1<<13)
#define RTC_CNTL_COCPU_INT_ENA_W1TS_V  0x1
#define RTC_CNTL_COCPU_INT_ENA_W1TS_S  13
/* RTC_CNTL_TSENS_INT_ENA_W1TS : WO ;bitpos:[12] ;default: 1'b0 ; */
/*description: enable tsens interrupt.*/
#define RTC_CNTL_TSENS_INT_ENA_W1TS    (1<<12)
#define RTC_CNTL_TSENS_INT_ENA_W1TS_M  (1<<12)
#define RTC_CNTL_TSENS_INT_ENA_W1TS_V  0x1
#define RTC_CNTL_TSENS_INT_ENA_W1TS_S  12
/* RTC_CNTL_SARADC1_INT_ENA_W1TS : WO ;bitpos:[11] ;default: 1'b0 ; */
/*description: enable saradc1 interrupt.*/
#define RTC_CNTL_SARADC1_INT_ENA_W1TS    (1<<11)
#define RTC_CNTL_SARADC1_INT_ENA_W1TS_M  (1<<11)
#define RTC_CNTL_SARADC1_INT_ENA_W1TS_V  0x1
#define RTC_CNTL_SARADC1_INT_ENA_W1TS_S  11
/* RTC_CNTL_MAIN_TIMER_INT_ENA_W1TS : WO ;bitpos:[10] ;default: 1'b0 ; */
/*description: enable RTC main timer interrupt.*/
#define RTC_CNTL_MAIN_TIMER_INT_ENA_W1TS    (1<<10)
#define RTC_CNTL_MAIN_TIMER_INT_ENA_W1TS_M  (1<<10)
#define RTC_CNTL_MAIN_TIMER_INT_ENA_W1TS_V  0x1
#define RTC_CNTL_MAIN_TIMER_INT_ENA_W1TS_S  10
/* RTC_CNTL_BROWN_OUT_INT_ENA_W1TS : WO ;bitpos:[9] ;default: 1'b0 ; */
/*description: enable brown out interrupt.*/
#define RTC_CNTL_BROWN_OUT_INT_ENA_W1TS    (1<<9)
#define RTC_CNTL_BROWN_OUT_INT_ENA_W1TS_M  (1<<9)
#define RTC_CNTL_BROWN_OUT_INT_ENA_W1TS_V  0x1
#define RTC_CNTL_BROWN_OUT_INT_ENA_W1TS_S  9
/* RTC_CNTL_TOUCH_INACTIVE_INT_ENA_W1TS : WO ;bitpos:[8] ;default: 1'b0 ; */
/*description: enable touch inactive interrupt.*/
#define RTC_CNTL_TOUCH_INACTIVE_INT_ENA_W1TS    (1<<8)
#define RTC_CNTL_TOUCH_INACTIVE_INT_ENA_W1TS_M  (1<<8)
#define RTC_CNTL_TOUCH_INACTIVE_INT_ENA_W1TS_V  0x1
#define RTC_CNTL_TOUCH_INACTIVE_INT_ENA_W1TS_S  8
/* RTC_CNTL_TOUCH_ACTIVE_INT_ENA_W1TS : WO ;bitpos:[7] ;default: 1'b0 ; */
/*description: enable touch active interrupt.*/
#define RTC_CNTL_TOUCH_ACTIVE_INT_ENA_W1TS    (1<<7)
#define RTC_CNTL_TOUCH_ACTIVE_INT_ENA_W1TS_M  (1<<7)
#define RTC_CNTL_TOUCH_ACTIVE_INT_ENA_W1TS_V  0x1
#define RTC_CNTL_TOUCH_ACTIVE_INT_ENA_W1TS_S  7
/* RTC_CNTL_TOUCH_DONE_INT_ENA_W1TS : WO ;bitpos:[6] ;default: 1'b0 ; */
/*description: enable touch done interrupt.*/
#define RTC_CNTL_TOUCH_DONE_INT_ENA_W1TS    (1<<6)
#define RTC_CNTL_TOUCH_DONE_INT_ENA_W1TS_M  (1<<6)
#define RTC_CNTL_TOUCH_DONE_INT_ENA_W1TS_V  0x1
#define RTC_CNTL_TOUCH_DONE_INT_ENA_W1TS_S  6
/* RTC_CNTL_ULP_CP_INT_ENA_W1TS : WO ;bitpos:[5] ;default: 1'b0 ; */
/*description: enable ULP-coprocessor interrupt.*/
#define RTC_CNTL_ULP_CP_INT_ENA_W1TS    (1<<5)
#define RTC_CNTL_ULP_CP_INT_ENA_W1TS_M  (1<<5)
#define RTC_CNTL_ULP_CP_INT_ENA_W1TS_V  0x1
#define RTC_CNTL_ULP_CP_INT_ENA_W1TS_S  5
/* RTC_CNTL_TOUCH_SCAN_DONE_INT_ENA_W1TS : WO ;bitpos:[4] ;default: 1'b0 ; */
/*description: enable touch scan done interrupt.*/
#define RTC_CNTL_TOUCH_SCAN_DONE_INT_ENA_W1TS    (1<<4)
#define RTC_CNTL_TOUCH_SCAN_DONE_INT_ENA_W1TS_M  (1<<4)
#define RTC_CNTL_TOUCH_SCAN_DONE_INT_ENA_W1TS_V  0x1
#define RTC_CNTL_TOUCH_SCAN_DONE_INT_ENA_W1TS_S  4
/* RTC_CNTL_WDT_INT_ENA_W1TS : WO ;bitpos:[3] ;default: 1'b0 ; */
/*description: enable RTC WDT interrupt.*/
#define RTC_CNTL_WDT_INT_ENA_W1TS    (1<<3)
#define RTC_CNTL_WDT_INT_ENA_W1TS_M  (1<<3)
#define RTC_CNTL_WDT_INT_ENA_W1TS_V  0x1
#define RTC_CNTL_WDT_INT_ENA_W1TS_S  3
/* RTC_CNTL_SDIO_IDLE_INT_ENA_W1TS : WO ;bitpos:[2] ;default: 1'b0 ; */
/*description: enable SDIO idle interrupt.*/
#define RTC_CNTL_SDIO_IDLE_INT_ENA_W1TS    (1<<2)
#define RTC_CNTL_SDIO_IDLE_INT_ENA_W1TS_M  (1<<2)
#define RTC_CNTL_SDIO_IDLE_INT_ENA_W1TS_V  0x1
#define RTC_CNTL_SDIO_IDLE_INT_ENA_W1TS_S  2
/* RTC_CNTL_SLP_REJECT_INT_ENA_W1TS : WO ;bitpos:[1] ;default: 1'b0 ; */
/*description: enable sleep reject interrupt.*/
#define RTC_CNTL_SLP_REJECT_INT_ENA_W1TS    (1<<1)
#define RTC_CNTL_SLP_REJECT_INT_ENA_W1TS_M  (1<<1)
#define RTC_CNTL_SLP_REJECT_INT_ENA_W1TS_V  0x1
#define RTC_CNTL_SLP_REJECT_INT_ENA_W1TS_S  1
/* RTC_CNTL_SLP_WAKEUP_INT_ENA_W1TS : WO ;bitpos:[0] ;default: 1'b0 ; */
/*description: enable sleep wakeup interrupt.*/
#define RTC_CNTL_SLP_WAKEUP_INT_ENA_W1TS    (1<<0)
#define RTC_CNTL_SLP_WAKEUP_INT_ENA_W1TS_M  (1<<0)
#define RTC_CNTL_SLP_WAKEUP_INT_ENA_W1TS_V  0x1
#define RTC_CNTL_SLP_WAKEUP_INT_ENA_W1TS_S  0

#define RTC_CNTL_INT_ENA_W1TC_REG          (0x60008000 + 0x13C)
/* RTC_CNTL_TOUCH_APPROACH_LOOP_DONE_INT_ENA_W1TC : WO ;bitpos:[20] ;default: 1'b0 ; */
/*description: .*/
#define RTC_CNTL_TOUCH_APPROACH_LOOP_DONE_INT_ENA_W1TC    (1<<20)
#define RTC_CNTL_TOUCH_APPROACH_LOOP_DONE_INT_ENA_W1TC_M  (1<<20)
#define RTC_CNTL_TOUCH_APPROACH_LOOP_DONE_INT_ENA_W1TC_V  0x1
#define RTC_CNTL_TOUCH_APPROACH_LOOP_DONE_INT_ENA_W1TC_S  20
/* RTC_CNTL_GLITCH_DET_INT_ENA_W1TC : WO ;bitpos:[19] ;default: 1'b0 ; */
/*description: enbale gitch det interrupt.*/
#define RTC_CNTL_GLITCH_DET_INT_ENA_W1TC    (1<<19)
#define RTC_CNTL_GLITCH_DET_INT_ENA_W1TC_M  (1<<19)
#define RTC_CNTL_GLITCH_DET_INT_ENA_W1TC_V  0x1
#define RTC_CNTL_GLITCH_DET_INT_ENA_W1TC_S  19
/* RTC_CNTL_TOUCH_TIMEOUT_INT_ENA_W1TC : WO ;bitpos:[18] ;default: 1'b0 ; */
/*description: enable touch timeout interrupt.*/
#define RTC_CNTL_TOUCH_TIMEOUT_INT_ENA_W1TC    (1<<18)
#define RTC_CNTL_TOUCH_TIMEOUT_INT_ENA_W1TC_M  (1<<18)
#define RTC_CNTL_TOUCH_TIMEOUT_INT_ENA_W1TC_V  0x1
#define RTC_CNTL_TOUCH_TIMEOUT_INT_ENA_W1TC_S  18
/* RTC_CNTL_COCPU_TRAP_INT_ENA_W1TC : WO ;bitpos:[17] ;default: 1'b0 ; */
/*description: enable cocpu trap interrupt.*/
#define RTC_CNTL_COCPU_TRAP_INT_ENA_W1TC    (1<<17)
#define RTC_CNTL_COCPU_TRAP_INT_ENA_W1TC_M  (1<<17)
#define RTC_CNTL_COCPU_TRAP_INT_ENA_W1TC_V  0x1
#define RTC_CNTL_COCPU_TRAP_INT_ENA_W1TC_S  17
/* RTC_CNTL_XTAL32K_DEAD_INT_ENA_W1TC : WO ;bitpos:[16] ;default: 1'b0 ; */
/*description: enable xtal32k_dead  interrupt.*/
#define RTC_CNTL_XTAL32K_DEAD_INT_ENA_W1TC    (1<<16)
#define RTC_CNTL_XTAL32K_DEAD_INT_ENA_W1TC_M  (1<<16)
#define RTC_CNTL_XTAL32K_DEAD_INT_ENA_W1TC_V  0x1
#define RTC_CNTL_XTAL32K_DEAD_INT_ENA_W1TC_S  16
/* RTC_CNTL_SWD_INT_ENA_W1TC : WO ;bitpos:[15] ;default: 1'b0 ; */
/*description: enable super watch dog interrupt.*/
#define RTC_CNTL_SWD_INT_ENA_W1TC    (1<<15)
#define RTC_CNTL_SWD_INT_ENA_W1TC_M  (1<<15)
#define RTC_CNTL_SWD_INT_ENA_W1TC_V  0x1
#define RTC_CNTL_SWD_INT_ENA_W1TC_S  15
/* RTC_CNTL_SARADC2_INT_ENA_W1TC : WO ;bitpos:[14] ;default: 1'b0 ; */
/*description: enable saradc2 interrupt.*/
#define RTC_CNTL_SARADC2_INT_ENA_W1TC    (1<<14)
#define RTC_CNTL_SARADC2_INT_ENA_W1TC_M  (1<<14)
#define RTC_CNTL_SARADC2_INT_ENA_W1TC_V  0x1
#define RTC_CNTL_SARADC2_INT_ENA_W1TC_S  14
/* RTC_CNTL_COCPU_INT_ENA_W1TC : WO ;bitpos:[13] ;default: 1'b0 ; */
/*description: enable riscV cocpu interrupt.*/
#define RTC_CNTL_COCPU_INT_ENA_W1TC    (1<<13)
#define RTC_CNTL_COCPU_INT_ENA_W1TC_M  (1<<13)
#define RTC_CNTL_COCPU_INT_ENA_W1TC_V  0x1
#define RTC_CNTL_COCPU_INT_ENA_W1TC_S  13
/* RTC_CNTL_TSENS_INT_ENA_W1TC : WO ;bitpos:[12] ;default: 1'b0 ; */
/*description: enable tsens interrupt.*/
#define RTC_CNTL_TSENS_INT_ENA_W1TC    (1<<12)
#define RTC_CNTL_TSENS_INT_ENA_W1TC_M  (1<<12)
#define RTC_CNTL_TSENS_INT_ENA_W1TC_V  0x1
#define RTC_CNTL_TSENS_INT_ENA_W1TC_S  12
/* RTC_CNTL_SARADC1_INT_ENA_W1TC : WO ;bitpos:[11] ;default: 1'b0 ; */
/*description: enable saradc1 interrupt.*/
#define RTC_CNTL_SARADC1_INT_ENA_W1TC    (1<<11)
#define RTC_CNTL_SARADC1_INT_ENA_W1TC_M  (1<<11)
#define RTC_CNTL_SARADC1_INT_ENA_W1TC_V  0x1
#define RTC_CNTL_SARADC1_INT_ENA_W1TC_S  11
/* RTC_CNTL_MAIN_TIMER_INT_ENA_W1TC : WO ;bitpos:[10] ;default: 1'b0 ; */
/*description: enable RTC main timer interrupt.*/
#define RTC_CNTL_MAIN_TIMER_INT_ENA_W1TC    (1<<10)
#define RTC_CNTL_MAIN_TIMER_INT_ENA_W1TC_M  (1<<10)
#define RTC_CNTL_MAIN_TIMER_INT_ENA_W1TC_V  0x1
#define RTC_CNTL_MAIN_TIMER_INT_ENA_W1TC_S  10
/* RTC_CNTL_BROWN_OUT_INT_ENA_W1TC : WO ;bitpos:[9] ;default: 1'b0 ; */
/*description: enable brown out interrupt.*/
#define RTC_CNTL_BROWN_OUT_INT_ENA_W1TC    (1<<9)
#define RTC_CNTL_BROWN_OUT_INT_ENA_W1TC_M  (1<<9)
#define RTC_CNTL_BROWN_OUT_INT_ENA_W1TC_V  0x1
#define RTC_CNTL_BROWN_OUT_INT_ENA_W1TC_S  9
/* RTC_CNTL_TOUCH_INACTIVE_INT_ENA_W1TC : WO ;bitpos:[8] ;default: 1'b0 ; */
/*description: enable touch inactive interrupt.*/
#define RTC_CNTL_TOUCH_INACTIVE_INT_ENA_W1TC    (1<<8)
#define RTC_CNTL_TOUCH_INACTIVE_INT_ENA_W1TC_M  (1<<8)
#define RTC_CNTL_TOUCH_INACTIVE_INT_ENA_W1TC_V  0x1
#define RTC_CNTL_TOUCH_INACTIVE_INT_ENA_W1TC_S  8
/* RTC_CNTL_TOUCH_ACTIVE_INT_ENA_W1TC : WO ;bitpos:[7] ;default: 1'b0 ; */
/*description: enable touch active interrupt.*/
#define RTC_CNTL_TOUCH_ACTIVE_INT_ENA_W1TC    (1<<7)
#define RTC_CNTL_TOUCH_ACTIVE_INT_ENA_W1TC_M  (1<<7)
#define RTC_CNTL_TOUCH_ACTIVE_INT_ENA_W1TC_V  0x1
#define RTC_CNTL_TOUCH_ACTIVE_INT_ENA_W1TC_S  7
/* RTC_CNTL_TOUCH_DONE_INT_ENA_W1TC : WO ;bitpos:[6] ;default: 1'b0 ; */
/*description: enable touch done interrupt.*/
#define RTC_CNTL_TOUCH_DONE_INT_ENA_W1TC    (1<<6)
#define RTC_CNTL_TOUCH_DONE_INT_ENA_W1TC_M  (1<<6)
#define RTC_CNTL_TOUCH_DONE_INT_ENA_W1TC_V  0x1
#define RTC_CNTL_TOUCH_DONE_INT_ENA_W1TC_S  6
/* RTC_CNTL_ULP_CP_INT_ENA_W1TC : WO ;bitpos:[5] ;default: 1'b0 ; */
/*description: enable ULP-coprocessor interrupt.*/
#define RTC_CNTL_ULP_CP_INT_ENA_W1TC    (1<<5)
#define RTC_CNTL_ULP_CP_INT_ENA_W1TC_M  (1<<5)
#define RTC_CNTL_ULP_CP_INT_ENA_W1TC_V  0x1
#define RTC_CNTL_ULP_CP_INT_ENA_W1TC_S  5
/* RTC_CNTL_TOUCH_SCAN_DONE_INT_ENA_W1TC : WO ;bitpos:[4] ;default: 1'b0 ; */
/*description: enable touch scan done interrupt.*/
#define RTC_CNTL_TOUCH_SCAN_DONE_INT_ENA_W1TC    (1<<4)
#define RTC_CNTL_TOUCH_SCAN_DONE_INT_ENA_W1TC_M  (1<<4)
#define RTC_CNTL_TOUCH_SCAN_DONE_INT_ENA_W1TC_V  0x1
#define RTC_CNTL_TOUCH_SCAN_DONE_INT_ENA_W1TC_S  4
/* RTC_CNTL_WDT_INT_ENA_W1TC : WO ;bitpos:[3] ;default: 1'b0 ; */
/*description: enable RTC WDT interrupt.*/
#define RTC_CNTL_WDT_INT_ENA_W1TC    (1<<3)
#define RTC_CNTL_WDT_INT_ENA_W1TC_M  (1<<3)
#define RTC_CNTL_WDT_INT_ENA_W1TC_V  0x1
#define RTC_CNTL_WDT_INT_ENA_W1TC_S  3
/* RTC_CNTL_SDIO_IDLE_INT_ENA_W1TC : WO ;bitpos:[2] ;default: 1'b0 ; */
/*description: enable SDIO idle interrupt.*/
#define RTC_CNTL_SDIO_IDLE_INT_ENA_W1TC    (1<<2)
#define RTC_CNTL_SDIO_IDLE_INT_ENA_W1TC_M  (1<<2)
#define RTC_CNTL_SDIO_IDLE_INT_ENA_W1TC_V  0x1
#define RTC_CNTL_SDIO_IDLE_INT_ENA_W1TC_S  2
/* RTC_CNTL_SLP_REJECT_INT_ENA_W1TC : WO ;bitpos:[1] ;default: 1'b0 ; */
/*description: enable sleep reject interrupt.*/
#define RTC_CNTL_SLP_REJECT_INT_ENA_W1TC    (1<<1)
#define RTC_CNTL_SLP_REJECT_INT_ENA_W1TC_M  (1<<1)
#define RTC_CNTL_SLP_REJECT_INT_ENA_W1TC_V  0x1
#define RTC_CNTL_SLP_REJECT_INT_ENA_W1TC_S  1
/* RTC_CNTL_SLP_WAKEUP_INT_ENA_W1TC : WO ;bitpos:[0] ;default: 1'b0 ; */
/*description: enable sleep wakeup interrupt.*/
#define RTC_CNTL_SLP_WAKEUP_INT_ENA_W1TC    (1<<0)
#define RTC_CNTL_SLP_WAKEUP_INT_ENA_W1TC_M  (1<<0)
#define RTC_CNTL_SLP_WAKEUP_INT_ENA_W1TC_V  0x1
#define RTC_CNTL_SLP_WAKEUP_INT_ENA_W1TC_S  0

#define RTC_CNTL_RETENTION_CTRL_REG          (0x60008000 + 0x140)
/* RTC_CNTL_RETENTION_WAIT : R/W ;bitpos:[31:25] ;default: 7'd20 ; */
/*description: wait cycles for rention operation.*/
#define RTC_CNTL_RETENTION_WAIT    0x0000007F
#define RTC_CNTL_RETENTION_WAIT_M  ((RTC_CNTL_RETENTION_WAIT_V)<<(RTC_CNTL_RETENTION_WAIT_S))
#define RTC_CNTL_RETENTION_WAIT_V  0x7F
#define RTC_CNTL_RETENTION_WAIT_S  25
/* RTC_CNTL_RETENTION_EN : R/W ;bitpos:[24] ;default: 1'd0 ; */
/*description: .*/
#define RTC_CNTL_RETENTION_EN    (1<<24)
#define RTC_CNTL_RETENTION_EN_M  (1<<24)
#define RTC_CNTL_RETENTION_EN_V  0x1
#define RTC_CNTL_RETENTION_EN_S  24
/* RTC_CNTL_RETENTION_CLKOFF_WAIT : R/W ;bitpos:[23:20] ;default: 4'd3 ; */
/*description: .*/
#define RTC_CNTL_RETENTION_CLKOFF_WAIT    0x0000000F
#define RTC_CNTL_RETENTION_CLKOFF_WAIT_M  ((RTC_CNTL_RETENTION_CLKOFF_WAIT_V)<<(RTC_CNTL_RETENTION_CLKOFF_WAIT_S))
#define RTC_CNTL_RETENTION_CLKOFF_WAIT_V  0xF
#define RTC_CNTL_RETENTION_CLKOFF_WAIT_S  20
/* RTC_CNTL_RETENTION_DONE_WAIT : R/W ;bitpos:[19:17] ;default: 3'd2 ; */
/*description: .*/
#define RTC_CNTL_RETENTION_DONE_WAIT    0x00000007
#define RTC_CNTL_RETENTION_DONE_WAIT_M  ((RTC_CNTL_RETENTION_DONE_WAIT_V)<<(RTC_CNTL_RETENTION_DONE_WAIT_S))
#define RTC_CNTL_RETENTION_DONE_WAIT_V  0x7
#define RTC_CNTL_RETENTION_DONE_WAIT_S  17
/* RTC_CNTL_RETENTION_CLK_SEL : R/W ;bitpos:[16] ;default: 1'b0 ; */
/*description: .*/
#define RTC_CNTL_RETENTION_CLK_SEL    (1<<16)
#define RTC_CNTL_RETENTION_CLK_SEL_M  (1<<16)
#define RTC_CNTL_RETENTION_CLK_SEL_V  0x1
#define RTC_CNTL_RETENTION_CLK_SEL_S  16
/* RTC_CNTL_RETENTION_TARGET : R/W ;bitpos:[15:14] ;default: 2'b0 ; */
/*description: .*/
#define RTC_CNTL_RETENTION_TARGET    0x00000003
#define RTC_CNTL_RETENTION_TARGET_M  ((RTC_CNTL_RETENTION_TARGET_V)<<(RTC_CNTL_RETENTION_TARGET_S))
#define RTC_CNTL_RETENTION_TARGET_V  0x3
#define RTC_CNTL_RETENTION_TARGET_S  14
/* RTC_CNTL_RETENTION_TAG_MODE : R/W ;bitpos:[13:10] ;default: 4'd0 ; */
/*description: .*/
#define RTC_CNTL_RETENTION_TAG_MODE    0x0000000F
#define RTC_CNTL_RETENTION_TAG_MODE_M  ((RTC_CNTL_RETENTION_TAG_MODE_V)<<(RTC_CNTL_RETENTION_TAG_MODE_S))
#define RTC_CNTL_RETENTION_TAG_MODE_V  0xF
#define RTC_CNTL_RETENTION_TAG_MODE_S  10

#define RTC_CNTL_PG_CTRL_REG          (0x60008000 + 0x144)
/* RTC_CNTL_POWER_GLITCH_EN : R/W ;bitpos:[31] ;default: 1'b0 ; */
/*description: .*/
#define RTC_CNTL_POWER_GLITCH_EN    (1<<31)
#define RTC_CNTL_POWER_GLITCH_EN_M  (1<<31)
#define RTC_CNTL_POWER_GLITCH_EN_V  0x1
#define RTC_CNTL_POWER_GLITCH_EN_S  31
/* RTC_CNTL_POWER_GLITCH_EFUSE_SEL : R/W ;bitpos:[30] ;default: 1'b0 ; */
/*description: select use analog fib signal.*/
#define RTC_CNTL_POWER_GLITCH_EFUSE_SEL    (1<<30)
#define RTC_CNTL_POWER_GLITCH_EFUSE_SEL_M  (1<<30)
#define RTC_CNTL_POWER_GLITCH_EFUSE_SEL_V  0x1
#define RTC_CNTL_POWER_GLITCH_EFUSE_SEL_S  30
/* RTC_CNTL_POWER_GLITCH_FORCE_PU : R/W ;bitpos:[29] ;default: 1'b0 ; */
/*description: .*/
#define RTC_CNTL_POWER_GLITCH_FORCE_PU    (1<<29)
#define RTC_CNTL_POWER_GLITCH_FORCE_PU_M  (1<<29)
#define RTC_CNTL_POWER_GLITCH_FORCE_PU_V  0x1
#define RTC_CNTL_POWER_GLITCH_FORCE_PU_S  29
/* RTC_CNTL_POWER_GLITCH_FORCE_PD : R/W ;bitpos:[28] ;default: 1'b0 ; */
/*description: .*/
#define RTC_CNTL_POWER_GLITCH_FORCE_PD    (1<<28)
#define RTC_CNTL_POWER_GLITCH_FORCE_PD_M  (1<<28)
#define RTC_CNTL_POWER_GLITCH_FORCE_PD_V  0x1
#define RTC_CNTL_POWER_GLITCH_FORCE_PD_S  28
/* RTC_CNTL_POWER_GLITCH_DSENSE : R/W ;bitpos:[27:26] ;default: 2'b0 ; */
/*description: .*/
#define RTC_CNTL_POWER_GLITCH_DSENSE    0x00000003
#define RTC_CNTL_POWER_GLITCH_DSENSE_M  ((RTC_CNTL_POWER_GLITCH_DSENSE_V)<<(RTC_CNTL_POWER_GLITCH_DSENSE_S))
#define RTC_CNTL_POWER_GLITCH_DSENSE_V  0x3
#define RTC_CNTL_POWER_GLITCH_DSENSE_S  26

#define RTC_CNTL_FIB_SEL_REG          (0x60008000 + 0x148)
/* RTC_CNTL_FIB_SEL : R/W ;bitpos:[2:0] ;default: 3'd7 ; */
/*description: .*/
#define RTC_CNTL_FIB_SEL    0x00000007
#define RTC_CNTL_FIB_SEL_M  ((RTC_CNTL_FIB_SEL_V)<<(RTC_CNTL_FIB_SEL_S))
#define RTC_CNTL_FIB_SEL_V  0x7
#define RTC_CNTL_FIB_SEL_S  0

#define RTC_CNTL_FIB_GLITCH_RST 1<<0
#define RTC_CNTL_FIB_BOR_RST 1<<1
#define RTC_CNTL_FIB_SUPER_WDT_RST 1<<2

#define RTC_CNTL_TOUCH_DAC_REG          (0x60008000 + 0x14C)
/* RTC_CNTL_TOUCH_PAD0_DAC : R/W ;bitpos:[31:29] ;default: 3'd0 ; */
/*description: .*/
#define RTC_CNTL_TOUCH_PAD0_DAC    0x00000007
#define RTC_CNTL_TOUCH_PAD0_DAC_M  ((RTC_CNTL_TOUCH_PAD0_DAC_V)<<(RTC_CNTL_TOUCH_PAD0_DAC_S))
#define RTC_CNTL_TOUCH_PAD0_DAC_V  0x7
#define RTC_CNTL_TOUCH_PAD0_DAC_S  29
/* RTC_CNTL_TOUCH_PAD1_DAC : R/W ;bitpos:[28:26] ;default: 3'd0 ; */
/*description: .*/
#define RTC_CNTL_TOUCH_PAD1_DAC    0x00000007
#define RTC_CNTL_TOUCH_PAD1_DAC_M  ((RTC_CNTL_TOUCH_PAD1_DAC_V)<<(RTC_CNTL_TOUCH_PAD1_DAC_S))
#define RTC_CNTL_TOUCH_PAD1_DAC_V  0x7
#define RTC_CNTL_TOUCH_PAD1_DAC_S  26
/* RTC_CNTL_TOUCH_PAD2_DAC : R/W ;bitpos:[25:23] ;default: 3'd0 ; */
/*description: .*/
#define RTC_CNTL_TOUCH_PAD2_DAC    0x00000007
#define RTC_CNTL_TOUCH_PAD2_DAC_M  ((RTC_CNTL_TOUCH_PAD2_DAC_V)<<(RTC_CNTL_TOUCH_PAD2_DAC_S))
#define RTC_CNTL_TOUCH_PAD2_DAC_V  0x7
#define RTC_CNTL_TOUCH_PAD2_DAC_S  23
/* RTC_CNTL_TOUCH_PAD3_DAC : R/W ;bitpos:[22:20] ;default: 3'd0 ; */
/*description: .*/
#define RTC_CNTL_TOUCH_PAD3_DAC    0x00000007
#define RTC_CNTL_TOUCH_PAD3_DAC_M  ((RTC_CNTL_TOUCH_PAD3_DAC_V)<<(RTC_CNTL_TOUCH_PAD3_DAC_S))
#define RTC_CNTL_TOUCH_PAD3_DAC_V  0x7
#define RTC_CNTL_TOUCH_PAD3_DAC_S  20
/* RTC_CNTL_TOUCH_PAD4_DAC : R/W ;bitpos:[19:17] ;default: 3'd0 ; */
/*description: .*/
#define RTC_CNTL_TOUCH_PAD4_DAC    0x00000007
#define RTC_CNTL_TOUCH_PAD4_DAC_M  ((RTC_CNTL_TOUCH_PAD4_DAC_V)<<(RTC_CNTL_TOUCH_PAD4_DAC_S))
#define RTC_CNTL_TOUCH_PAD4_DAC_V  0x7
#define RTC_CNTL_TOUCH_PAD4_DAC_S  17
/* RTC_CNTL_TOUCH_PAD5_DAC : R/W ;bitpos:[16:14] ;default: 3'd0 ; */
/*description: .*/
#define RTC_CNTL_TOUCH_PAD5_DAC    0x00000007
#define RTC_CNTL_TOUCH_PAD5_DAC_M  ((RTC_CNTL_TOUCH_PAD5_DAC_V)<<(RTC_CNTL_TOUCH_PAD5_DAC_S))
#define RTC_CNTL_TOUCH_PAD5_DAC_V  0x7
#define RTC_CNTL_TOUCH_PAD5_DAC_S  14
/* RTC_CNTL_TOUCH_PAD6_DAC : R/W ;bitpos:[13:11] ;default: 3'd0 ; */
/*description: .*/
#define RTC_CNTL_TOUCH_PAD6_DAC    0x00000007
#define RTC_CNTL_TOUCH_PAD6_DAC_M  ((RTC_CNTL_TOUCH_PAD6_DAC_V)<<(RTC_CNTL_TOUCH_PAD6_DAC_S))
#define RTC_CNTL_TOUCH_PAD6_DAC_V  0x7
#define RTC_CNTL_TOUCH_PAD6_DAC_S  11
/* RTC_CNTL_TOUCH_PAD7_DAC : R/W ;bitpos:[10:8] ;default: 3'd0 ; */
/*description: .*/
#define RTC_CNTL_TOUCH_PAD7_DAC    0x00000007
#define RTC_CNTL_TOUCH_PAD7_DAC_M  ((RTC_CNTL_TOUCH_PAD7_DAC_V)<<(RTC_CNTL_TOUCH_PAD7_DAC_S))
#define RTC_CNTL_TOUCH_PAD7_DAC_V  0x7
#define RTC_CNTL_TOUCH_PAD7_DAC_S  8
/* RTC_CNTL_TOUCH_PAD8_DAC : R/W ;bitpos:[7:5] ;default: 3'd0 ; */
/*description: .*/
#define RTC_CNTL_TOUCH_PAD8_DAC    0x00000007
#define RTC_CNTL_TOUCH_PAD8_DAC_M  ((RTC_CNTL_TOUCH_PAD8_DAC_V)<<(RTC_CNTL_TOUCH_PAD8_DAC_S))
#define RTC_CNTL_TOUCH_PAD8_DAC_V  0x7
#define RTC_CNTL_TOUCH_PAD8_DAC_S  5
/* RTC_CNTL_TOUCH_PAD9_DAC : R/W ;bitpos:[4:2] ;default: 3'd0 ; */
/*description: .*/
#define RTC_CNTL_TOUCH_PAD9_DAC    0x00000007
#define RTC_CNTL_TOUCH_PAD9_DAC_M  ((RTC_CNTL_TOUCH_PAD9_DAC_V)<<(RTC_CNTL_TOUCH_PAD9_DAC_S))
#define RTC_CNTL_TOUCH_PAD9_DAC_V  0x7
#define RTC_CNTL_TOUCH_PAD9_DAC_S  2

#define RTC_CNTL_TOUCH_DAC1_REG          (0x60008000 + 0x150)
/* RTC_CNTL_TOUCH_PAD10_DAC : R/W ;bitpos:[31:29] ;default: 3'd0 ; */
/*description: .*/
#define RTC_CNTL_TOUCH_PAD10_DAC    0x00000007
#define RTC_CNTL_TOUCH_PAD10_DAC_M  ((RTC_CNTL_TOUCH_PAD10_DAC_V)<<(RTC_CNTL_TOUCH_PAD10_DAC_S))
#define RTC_CNTL_TOUCH_PAD10_DAC_V  0x7
#define RTC_CNTL_TOUCH_PAD10_DAC_S  29
/* RTC_CNTL_TOUCH_PAD11_DAC : R/W ;bitpos:[28:26] ;default: 3'd0 ; */
/*description: .*/
#define RTC_CNTL_TOUCH_PAD11_DAC    0x00000007
#define RTC_CNTL_TOUCH_PAD11_DAC_M  ((RTC_CNTL_TOUCH_PAD11_DAC_V)<<(RTC_CNTL_TOUCH_PAD11_DAC_S))
#define RTC_CNTL_TOUCH_PAD11_DAC_V  0x7
#define RTC_CNTL_TOUCH_PAD11_DAC_S  26
/* RTC_CNTL_TOUCH_PAD12_DAC : R/W ;bitpos:[25:23] ;default: 3'd0 ; */
/*description: .*/
#define RTC_CNTL_TOUCH_PAD12_DAC    0x00000007
#define RTC_CNTL_TOUCH_PAD12_DAC_M  ((RTC_CNTL_TOUCH_PAD12_DAC_V)<<(RTC_CNTL_TOUCH_PAD12_DAC_S))
#define RTC_CNTL_TOUCH_PAD12_DAC_V  0x7
#define RTC_CNTL_TOUCH_PAD12_DAC_S  23
/* RTC_CNTL_TOUCH_PAD13_DAC : R/W ;bitpos:[22:20] ;default: 3'd0 ; */
/*description: .*/
#define RTC_CNTL_TOUCH_PAD13_DAC    0x00000007
#define RTC_CNTL_TOUCH_PAD13_DAC_M  ((RTC_CNTL_TOUCH_PAD13_DAC_V)<<(RTC_CNTL_TOUCH_PAD13_DAC_S))
#define RTC_CNTL_TOUCH_PAD13_DAC_V  0x7
#define RTC_CNTL_TOUCH_PAD13_DAC_S  20
/* RTC_CNTL_TOUCH_PAD14_DAC : R/W ;bitpos:[19:17] ;default: 3'd0 ; */
/*description: .*/
#define RTC_CNTL_TOUCH_PAD14_DAC    0x00000007
#define RTC_CNTL_TOUCH_PAD14_DAC_M  ((RTC_CNTL_TOUCH_PAD14_DAC_V)<<(RTC_CNTL_TOUCH_PAD14_DAC_S))
#define RTC_CNTL_TOUCH_PAD14_DAC_V  0x7
#define RTC_CNTL_TOUCH_PAD14_DAC_S  17

#define RTC_CNTL_COCPU_DISABLE_REG          (0x60008000 + 0x154)
/* RTC_CNTL_DISABLE_RTC_CPU : R/W ;bitpos:[31] ;default: 1'b0 ; */
/*description: .*/
#define RTC_CNTL_DISABLE_RTC_CPU    (1<<31)
#define RTC_CNTL_DISABLE_RTC_CPU_M  (1<<31)
#define RTC_CNTL_DISABLE_RTC_CPU_V  0x1
#define RTC_CNTL_DISABLE_RTC_CPU_S  31

#define RTC_CNTL_DATE_REG          (0x60008000 + 0x1FC)
/* RTC_CNTL_DATE : R/W ;bitpos:[27:0] ;default: 28'h2101271 ; */
/*description: .*/
#define RTC_CNTL_DATE    0x0FFFFFFF
#define RTC_CNTL_DATE_M  ((RTC_CNTL_DATE_V)<<(RTC_CNTL_DATE_S))
#define RTC_CNTL_DATE_V  0xFFFFFFF
#define RTC_CNTL_DATE_S  0
/*LDO SLAVE : R/W ;bitpos:[18:13] ; default: 6'd0 ;*/
/*description: .*/
#define RTC_CNTL_SLAVE_PD    0x0000003F
#define RTC_CNTL_SLAVE_PD_M  ((RTC_CNTL_SLAVE_V)<<(RTC_CNTL_SLAVE_S))
#define RTC_CNTL_SLAVE_PD_V  0x3F
#define RTC_CNTL_SLAVE_PD_S  13
#define APB_CTRL_SYSCLK_CONF_REG          (DR_REG_APB_CTRL_BASE + 0x0)

#define DMA_DESCRIPTOR_BUFFER_OWNER_DMA (1)

/*-------------------------- RTC CAPS --------------------------------------*/
#define SOC_RTC_CNTL_CPU_PD_DMA_BUS_WIDTH       (128)
#define SOC_RTC_CNTL_CPU_PD_REG_FILE_NUM        (549)
#define SOC_RTC_CNTL_CPU_PD_DMA_ADDR_ALIGN      (SOC_RTC_CNTL_CPU_PD_DMA_BUS_WIDTH >> 3)
#define SOC_RTC_CNTL_CPU_PD_DMA_BLOCK_SIZE      (SOC_RTC_CNTL_CPU_PD_DMA_BUS_WIDTH >> 3)

#define SOC_RTC_CNTL_CPU_PD_RETENTION_MEM_SIZE  (SOC_RTC_CNTL_CPU_PD_REG_FILE_NUM * (SOC_RTC_CNTL_CPU_PD_DMA_BUS_WIDTH >> 3))

/* I/D Cache tag memory retention hardware parameters */
#define SOC_RTC_CNTL_TAGMEM_PD_DMA_BUS_WIDTH    (128)
#define SOC_RTC_CNTL_TAGMEM_PD_DMA_ADDR_ALIGN   (SOC_RTC_CNTL_TAGMEM_PD_DMA_BUS_WIDTH >> 3)

/*-------------------------- RTCIO CAPS --------------------------------------*/
#define SOC_RTCIO_PIN_COUNT   22
#define SOC_RTCIO_INPUT_OUTPUT_SUPPORTED 1
#define SOC_RTCIO_HOLD_SUPPORTED 1
#define SOC_RTCIO_WAKE_SUPPORTED 1



#define DR_REG_APB_CTRL_BASE                    0x60026000

/* APB_CTRL_RST_TICK_CNT : R/W ;bitpos:[12] ;default: 1'b0 ; */
/*description: .*/
#define APB_CTRL_RST_TICK_CNT    (1<<(12))
#define APB_CTRL_RST_TICK_CNT_M  (1<<(12))
#define APB_CTRL_RST_TICK_CNT_V  0x1
#define APB_CTRL_RST_TICK_CNT_S  12
/* APB_CTRL_CLK_EN : R/W ;bitpos:[11] ;default: 1'b0 ; */
/*description: .*/
#define APB_CTRL_CLK_EN    (1<<(11))
#define APB_CTRL_CLK_EN_M  (1<<(11))
#define APB_CTRL_CLK_EN_V  0x1
#define APB_CTRL_CLK_EN_S  11
/* APB_CTRL_CLK_320M_EN : R/W ;bitpos:[10] ;default: 1'b0 ; */
/*description: .*/
#define APB_CTRL_CLK_320M_EN    (1<<(10))
#define APB_CTRL_CLK_320M_EN_M  (1<<(10))
#define APB_CTRL_CLK_320M_EN_V  0x1
#define APB_CTRL_CLK_320M_EN_S  10
/* APB_CTRL_PRE_DIV_CNT : R/W ;bitpos:[9:0] ;default: 10'h1 ; */
/*description: .*/
#define APB_CTRL_PRE_DIV_CNT    0x000003FF
#define APB_CTRL_PRE_DIV_CNT_M  ((APB_CTRL_PRE_DIV_CNT_V)<<(APB_CTRL_PRE_DIV_CNT_S))
#define APB_CTRL_PRE_DIV_CNT_V  0x3FF
#define APB_CTRL_PRE_DIV_CNT_S  0

#define APB_CTRL_TICK_CONF_REG          (DR_REG_APB_CTRL_BASE + 0x4)
/* APB_CTRL_TICK_ENABLE : R/W ;bitpos:[16] ;default: 1'd1 ; */
/*description: .*/
#define APB_CTRL_TICK_ENABLE    (1<<(16))
#define APB_CTRL_TICK_ENABLE_M  (1<<(16))
#define APB_CTRL_TICK_ENABLE_V  0x1
#define APB_CTRL_TICK_ENABLE_S  16
/* APB_CTRL_CK8M_TICK_NUM : R/W ;bitpos:[15:8] ;default: 8'd7 ; */
/*description: .*/
#define APB_CTRL_CK8M_TICK_NUM    0x000000FF
#define APB_CTRL_CK8M_TICK_NUM_M  ((APB_CTRL_CK8M_TICK_NUM_V)<<(APB_CTRL_CK8M_TICK_NUM_S))
#define APB_CTRL_CK8M_TICK_NUM_V  0xFF
#define APB_CTRL_CK8M_TICK_NUM_S  8
/* APB_CTRL_XTAL_TICK_NUM : R/W ;bitpos:[7:0] ;default: 8'd39 ; */
/*description: .*/
#define APB_CTRL_XTAL_TICK_NUM    0x000000FF
#define APB_CTRL_XTAL_TICK_NUM_M  ((APB_CTRL_XTAL_TICK_NUM_V)<<(APB_CTRL_XTAL_TICK_NUM_S))
#define APB_CTRL_XTAL_TICK_NUM_V  0xFF
#define APB_CTRL_XTAL_TICK_NUM_S  0

#define APB_CTRL_CLK_OUT_EN_REG          (DR_REG_APB_CTRL_BASE + 0x8)
/* APB_CTRL_CLK_XTAL_OEN : R/W ;bitpos:[10] ;default: 1'b1 ; */
/*description: .*/
#define APB_CTRL_CLK_XTAL_OEN    (1<<(10))
#define APB_CTRL_CLK_XTAL_OEN_M  (1<<(10))
#define APB_CTRL_CLK_XTAL_OEN_V  0x1
#define APB_CTRL_CLK_XTAL_OEN_S  10
/* APB_CTRL_CLK40X_BB_OEN : R/W ;bitpos:[9] ;default: 1'b1 ; */
/*description: .*/
#define APB_CTRL_CLK40X_BB_OEN    (1<<(9))
#define APB_CTRL_CLK40X_BB_OEN_M  (1<<(9))
#define APB_CTRL_CLK40X_BB_OEN_V  0x1
#define APB_CTRL_CLK40X_BB_OEN_S  9
/* APB_CTRL_CLK_DAC_CPU_OEN : R/W ;bitpos:[8] ;default: 1'b1 ; */
/*description: .*/
#define APB_CTRL_CLK_DAC_CPU_OEN    (1<<(8))
#define APB_CTRL_CLK_DAC_CPU_OEN_M  (1<<(8))
#define APB_CTRL_CLK_DAC_CPU_OEN_V  0x1
#define APB_CTRL_CLK_DAC_CPU_OEN_S  8
/* APB_CTRL_CLK_ADC_INF_OEN : R/W ;bitpos:[7] ;default: 1'b1 ; */
/*description: .*/
#define APB_CTRL_CLK_ADC_INF_OEN    (1<<(7))
#define APB_CTRL_CLK_ADC_INF_OEN_M  (1<<(7))
#define APB_CTRL_CLK_ADC_INF_OEN_V  0x1
#define APB_CTRL_CLK_ADC_INF_OEN_S  7
/* APB_CTRL_CLK_320M_OEN : R/W ;bitpos:[6] ;default: 1'b1 ; */
/*description: .*/
#define APB_CTRL_CLK_320M_OEN    (1<<(6))
#define APB_CTRL_CLK_320M_OEN_M  (1<<(6))
#define APB_CTRL_CLK_320M_OEN_V  0x1
#define APB_CTRL_CLK_320M_OEN_S  6
/* APB_CTRL_CLK160_OEN : R/W ;bitpos:[5] ;default: 1'b1 ; */
/*description: .*/
#define APB_CTRL_CLK160_OEN    (1<<(5))
#define APB_CTRL_CLK160_OEN_M  (1<<(5))
#define APB_CTRL_CLK160_OEN_V  0x1
#define APB_CTRL_CLK160_OEN_S  5
/* APB_CTRL_CLK80_OEN : R/W ;bitpos:[4] ;default: 1'b1 ; */
/*description: .*/
#define APB_CTRL_CLK80_OEN    (1<<(4))
#define APB_CTRL_CLK80_OEN_M  (1<<(4))
#define APB_CTRL_CLK80_OEN_V  0x1
#define APB_CTRL_CLK80_OEN_S  4
/* APB_CTRL_CLK_BB_OEN : R/W ;bitpos:[3] ;default: 1'b1 ; */
/*description: .*/
#define APB_CTRL_CLK_BB_OEN    (1<<(3))
#define APB_CTRL_CLK_BB_OEN_M  (1<<(3))
#define APB_CTRL_CLK_BB_OEN_V  0x1
#define APB_CTRL_CLK_BB_OEN_S  3
/* APB_CTRL_CLK44_OEN : R/W ;bitpos:[2] ;default: 1'b1 ; */
/*description: .*/
#define APB_CTRL_CLK44_OEN    (1<<(2))
#define APB_CTRL_CLK44_OEN_M  (1<<(2))
#define APB_CTRL_CLK44_OEN_V  0x1
#define APB_CTRL_CLK44_OEN_S  2
/* APB_CTRL_CLK22_OEN : R/W ;bitpos:[1] ;default: 1'b1 ; */
/*description: .*/
#define APB_CTRL_CLK22_OEN    (1<<(1))
#define APB_CTRL_CLK22_OEN_M  (1<<(1))
#define APB_CTRL_CLK22_OEN_V  0x1
#define APB_CTRL_CLK22_OEN_S  1
/* APB_CTRL_CLK20_OEN : R/W ;bitpos:[0] ;default: 1'b1 ; */
/*description: .*/
#define APB_CTRL_CLK20_OEN    (1<<(0))
#define APB_CTRL_CLK20_OEN_M  (1<<(0))
#define APB_CTRL_CLK20_OEN_V  0x1
#define APB_CTRL_CLK20_OEN_S  0

#define APB_CTRL_WIFI_BB_CFG_REG          (DR_REG_APB_CTRL_BASE + 0xC)
/* APB_CTRL_WIFI_BB_CFG : R/W ;bitpos:[31:0] ;default: 32'h0 ; */
/*description: .*/
#define APB_CTRL_WIFI_BB_CFG    0xFFFFFFFF
#define APB_CTRL_WIFI_BB_CFG_M  ((APB_CTRL_WIFI_BB_CFG_V)<<(APB_CTRL_WIFI_BB_CFG_S))
#define APB_CTRL_WIFI_BB_CFG_V  0xFFFFFFFF
#define APB_CTRL_WIFI_BB_CFG_S  0

#define APB_CTRL_WIFI_BB_CFG_2_REG          (DR_REG_APB_CTRL_BASE + 0x10)
/* APB_CTRL_WIFI_BB_CFG_2 : R/W ;bitpos:[31:0] ;default: 32'h0 ; */
/*description: .*/
#define APB_CTRL_WIFI_BB_CFG_2    0xFFFFFFFF
#define APB_CTRL_WIFI_BB_CFG_2_M  ((APB_CTRL_WIFI_BB_CFG_2_V)<<(APB_CTRL_WIFI_BB_CFG_2_S))
#define APB_CTRL_WIFI_BB_CFG_2_V  0xFFFFFFFF
#define APB_CTRL_WIFI_BB_CFG_2_S  0

#define APB_CTRL_WIFI_CLK_EN_REG          (DR_REG_APB_CTRL_BASE + 0x14)
/* APB_CTRL_WIFI_CLK_EN : R/W ;bitpos:[31:0] ;default: 32'hfffce030 ; */
/*description: .*/
#define APB_CTRL_WIFI_CLK_EN    0xFFFFFFFF
#define APB_CTRL_WIFI_CLK_EN_M  ((APB_CTRL_WIFI_CLK_EN_V)<<(APB_CTRL_WIFI_CLK_EN_S))
#define APB_CTRL_WIFI_CLK_EN_V  0xFFFFFFFF
#define APB_CTRL_WIFI_CLK_EN_S  0

#define APB_CTRL_WIFI_RST_EN_REG          (DR_REG_APB_CTRL_BASE + 0x18)
/* APB_CTRL_WIFI_RST : R/W ;bitpos:[31:0] ;default: 32'h0 ; */
/*description: .*/
#define APB_CTRL_WIFI_RST    0xFFFFFFFF
#define APB_CTRL_WIFI_RST_M  ((APB_CTRL_WIFI_RST_V)<<(APB_CTRL_WIFI_RST_S))
#define APB_CTRL_WIFI_RST_V  0xFFFFFFFF
#define APB_CTRL_WIFI_RST_S  0

#define APB_CTRL_HOST_INF_SEL_REG          (DR_REG_APB_CTRL_BASE + 0x1C)
/* APB_CTRL_PERI_IO_SWAP : R/W ;bitpos:[7:0] ;default: 8'h0 ; */
/*description: .*/
#define APB_CTRL_PERI_IO_SWAP    0x000000FF
#define APB_CTRL_PERI_IO_SWAP_M  ((APB_CTRL_PERI_IO_SWAP_V)<<(APB_CTRL_PERI_IO_SWAP_S))
#define APB_CTRL_PERI_IO_SWAP_V  0xFF
#define APB_CTRL_PERI_IO_SWAP_S  0

#define APB_CTRL_EXT_MEM_PMS_LOCK_REG          (DR_REG_APB_CTRL_BASE + 0x20)
/* APB_CTRL_EXT_MEM_PMS_LOCK : R/W ;bitpos:[0] ;default: 1'b0 ; */
/*description: .*/
#define APB_CTRL_EXT_MEM_PMS_LOCK    (1<<(0))
#define APB_CTRL_EXT_MEM_PMS_LOCK_M  (1<<(0))
#define APB_CTRL_EXT_MEM_PMS_LOCK_V  0x1
#define APB_CTRL_EXT_MEM_PMS_LOCK_S  0

#define APB_CTRL_EXT_MEM_WRITEBACK_BYPASS_REG          (DR_REG_APB_CTRL_BASE + 0x24)
/* APB_CTRL_WRITEBACK_BYPASS : R/W ;bitpos:[0] ;default: 1'b0 ; */
/*description: Set 1 to bypass cache writeback request to external memory so that spi will not
check its attribute..*/
#define APB_CTRL_WRITEBACK_BYPASS    (1<<(0))
#define APB_CTRL_WRITEBACK_BYPASS_M  (1<<(0))
#define APB_CTRL_WRITEBACK_BYPASS_V  0x1
#define APB_CTRL_WRITEBACK_BYPASS_S  0

#define APB_CTRL_FLASH_ACE0_ATTR_REG          (DR_REG_APB_CTRL_BASE + 0x28)
/* APB_CTRL_FLASH_ACE0_ATTR : R/W ;bitpos:[8:0] ;default: 9'hff ; */
/*description: .*/
#define APB_CTRL_FLASH_ACE0_ATTR    0x000001FF
#define APB_CTRL_FLASH_ACE0_ATTR_M  ((APB_CTRL_FLASH_ACE0_ATTR_V)<<(APB_CTRL_FLASH_ACE0_ATTR_S))
#define APB_CTRL_FLASH_ACE0_ATTR_V  0x1FF
#define APB_CTRL_FLASH_ACE0_ATTR_S  0

#define APB_CTRL_FLASH_ACE1_ATTR_REG          (DR_REG_APB_CTRL_BASE + 0x2C)
/* APB_CTRL_FLASH_ACE1_ATTR : R/W ;bitpos:[8:0] ;default: 9'hff ; */
/*description: .*/
#define APB_CTRL_FLASH_ACE1_ATTR    0x000001FF
#define APB_CTRL_FLASH_ACE1_ATTR_M  ((APB_CTRL_FLASH_ACE1_ATTR_V)<<(APB_CTRL_FLASH_ACE1_ATTR_S))
#define APB_CTRL_FLASH_ACE1_ATTR_V  0x1FF
#define APB_CTRL_FLASH_ACE1_ATTR_S  0

#define APB_CTRL_FLASH_ACE2_ATTR_REG          (DR_REG_APB_CTRL_BASE + 0x30)
/* APB_CTRL_FLASH_ACE2_ATTR : R/W ;bitpos:[8:0] ;default: 9'hff ; */
/*description: .*/
#define APB_CTRL_FLASH_ACE2_ATTR    0x000001FF
#define APB_CTRL_FLASH_ACE2_ATTR_M  ((APB_CTRL_FLASH_ACE2_ATTR_V)<<(APB_CTRL_FLASH_ACE2_ATTR_S))
#define APB_CTRL_FLASH_ACE2_ATTR_V  0x1FF
#define APB_CTRL_FLASH_ACE2_ATTR_S  0

#define APB_CTRL_FLASH_ACE3_ATTR_REG          (DR_REG_APB_CTRL_BASE + 0x34)
/* APB_CTRL_FLASH_ACE3_ATTR : R/W ;bitpos:[8:0] ;default: 9'hff ; */
/*description: .*/
#define APB_CTRL_FLASH_ACE3_ATTR    0x000001FF
#define APB_CTRL_FLASH_ACE3_ATTR_M  ((APB_CTRL_FLASH_ACE3_ATTR_V)<<(APB_CTRL_FLASH_ACE3_ATTR_S))
#define APB_CTRL_FLASH_ACE3_ATTR_V  0x1FF
#define APB_CTRL_FLASH_ACE3_ATTR_S  0

#define APB_CTRL_FLASH_ACE0_ADDR_REG          (DR_REG_APB_CTRL_BASE + 0x38)
/* APB_CTRL_FLASH_ACE0_ADDR_S : R/W ;bitpos:[31:0] ;default: 32'h0 ; */
/*description: .*/
#define APB_CTRL_FLASH_ACE0_ADDR_S    0xFFFFFFFF
#define APB_CTRL_FLASH_ACE0_ADDR_S_M  ((APB_CTRL_FLASH_ACE0_ADDR_S_V)<<(APB_CTRL_FLASH_ACE0_ADDR_S_S))
#define APB_CTRL_FLASH_ACE0_ADDR_S_V  0xFFFFFFFF
#define APB_CTRL_FLASH_ACE0_ADDR_S_S  0

#define APB_CTRL_FLASH_ACE1_ADDR_REG          (DR_REG_APB_CTRL_BASE + 0x3C)
/* APB_CTRL_FLASH_ACE1_ADDR_S : R/W ;bitpos:[31:0] ;default: 32'h10000000 ; */
/*description: .*/
#define APB_CTRL_FLASH_ACE1_ADDR_S    0xFFFFFFFF
#define APB_CTRL_FLASH_ACE1_ADDR_S_M  ((APB_CTRL_FLASH_ACE1_ADDR_S_V)<<(APB_CTRL_FLASH_ACE1_ADDR_S_S))
#define APB_CTRL_FLASH_ACE1_ADDR_S_V  0xFFFFFFFF
#define APB_CTRL_FLASH_ACE1_ADDR_S_S  0

#define APB_CTRL_FLASH_ACE2_ADDR_REG          (DR_REG_APB_CTRL_BASE + 0x40)
/* APB_CTRL_FLASH_ACE2_ADDR_S : R/W ;bitpos:[31:0] ;default: 32'h20000000 ; */
/*description: .*/
#define APB_CTRL_FLASH_ACE2_ADDR_S    0xFFFFFFFF
#define APB_CTRL_FLASH_ACE2_ADDR_S_M  ((APB_CTRL_FLASH_ACE2_ADDR_S_V)<<(APB_CTRL_FLASH_ACE2_ADDR_S_S))
#define APB_CTRL_FLASH_ACE2_ADDR_S_V  0xFFFFFFFF
#define APB_CTRL_FLASH_ACE2_ADDR_S_S  0

#define APB_CTRL_FLASH_ACE3_ADDR_REG          (DR_REG_APB_CTRL_BASE + 0x44)
/* APB_CTRL_FLASH_ACE3_ADDR_S : R/W ;bitpos:[31:0] ;default: 32'h30000000 ; */
/*description: .*/
#define APB_CTRL_FLASH_ACE3_ADDR_S    0xFFFFFFFF
#define APB_CTRL_FLASH_ACE3_ADDR_S_M  ((APB_CTRL_FLASH_ACE3_ADDR_S_V)<<(APB_CTRL_FLASH_ACE3_ADDR_S_S))
#define APB_CTRL_FLASH_ACE3_ADDR_S_V  0xFFFFFFFF
#define APB_CTRL_FLASH_ACE3_ADDR_S_S  0

#define APB_CTRL_FLASH_ACE0_SIZE_REG          (DR_REG_APB_CTRL_BASE + 0x48)
/* APB_CTRL_FLASH_ACE0_SIZE : R/W ;bitpos:[15:0] ;default: 16'h1000 ; */
/*description: .*/
#define APB_CTRL_FLASH_ACE0_SIZE    0x0000FFFF
#define APB_CTRL_FLASH_ACE0_SIZE_M  ((APB_CTRL_FLASH_ACE0_SIZE_V)<<(APB_CTRL_FLASH_ACE0_SIZE_S))
#define APB_CTRL_FLASH_ACE0_SIZE_V  0xFFFF
#define APB_CTRL_FLASH_ACE0_SIZE_S  0

#define APB_CTRL_FLASH_ACE1_SIZE_REG          (DR_REG_APB_CTRL_BASE + 0x4C)
/* APB_CTRL_FLASH_ACE1_SIZE : R/W ;bitpos:[15:0] ;default: 16'h1000 ; */
/*description: .*/
#define APB_CTRL_FLASH_ACE1_SIZE    0x0000FFFF
#define APB_CTRL_FLASH_ACE1_SIZE_M  ((APB_CTRL_FLASH_ACE1_SIZE_V)<<(APB_CTRL_FLASH_ACE1_SIZE_S))
#define APB_CTRL_FLASH_ACE1_SIZE_V  0xFFFF
#define APB_CTRL_FLASH_ACE1_SIZE_S  0

#define APB_CTRL_FLASH_ACE2_SIZE_REG          (DR_REG_APB_CTRL_BASE + 0x50)
/* APB_CTRL_FLASH_ACE2_SIZE : R/W ;bitpos:[15:0] ;default: 16'h1000 ; */
/*description: .*/
#define APB_CTRL_FLASH_ACE2_SIZE    0x0000FFFF
#define APB_CTRL_FLASH_ACE2_SIZE_M  ((APB_CTRL_FLASH_ACE2_SIZE_V)<<(APB_CTRL_FLASH_ACE2_SIZE_S))
#define APB_CTRL_FLASH_ACE2_SIZE_V  0xFFFF
#define APB_CTRL_FLASH_ACE2_SIZE_S  0

#define APB_CTRL_FLASH_ACE3_SIZE_REG          (DR_REG_APB_CTRL_BASE + 0x54)
/* APB_CTRL_FLASH_ACE3_SIZE : R/W ;bitpos:[15:0] ;default: 16'h1000 ; */
/*description: .*/
#define APB_CTRL_FLASH_ACE3_SIZE    0x0000FFFF
#define APB_CTRL_FLASH_ACE3_SIZE_M  ((APB_CTRL_FLASH_ACE3_SIZE_V)<<(APB_CTRL_FLASH_ACE3_SIZE_S))
#define APB_CTRL_FLASH_ACE3_SIZE_V  0xFFFF
#define APB_CTRL_FLASH_ACE3_SIZE_S  0

#define APB_CTRL_SRAM_ACE0_ATTR_REG          (DR_REG_APB_CTRL_BASE + 0x58)
/* APB_CTRL_SRAM_ACE0_ATTR : R/W ;bitpos:[8:0] ;default: 9'hff ; */
/*description: .*/
#define APB_CTRL_SRAM_ACE0_ATTR    0x000001FF
#define APB_CTRL_SRAM_ACE0_ATTR_M  ((APB_CTRL_SRAM_ACE0_ATTR_V)<<(APB_CTRL_SRAM_ACE0_ATTR_S))
#define APB_CTRL_SRAM_ACE0_ATTR_V  0x1FF
#define APB_CTRL_SRAM_ACE0_ATTR_S  0

#define APB_CTRL_SRAM_ACE1_ATTR_REG          (DR_REG_APB_CTRL_BASE + 0x5C)
/* APB_CTRL_SRAM_ACE1_ATTR : R/W ;bitpos:[8:0] ;default: 9'hff ; */
/*description: .*/
#define APB_CTRL_SRAM_ACE1_ATTR    0x000001FF
#define APB_CTRL_SRAM_ACE1_ATTR_M  ((APB_CTRL_SRAM_ACE1_ATTR_V)<<(APB_CTRL_SRAM_ACE1_ATTR_S))
#define APB_CTRL_SRAM_ACE1_ATTR_V  0x1FF
#define APB_CTRL_SRAM_ACE1_ATTR_S  0

#define APB_CTRL_SRAM_ACE2_ATTR_REG          (DR_REG_APB_CTRL_BASE + 0x60)
/* APB_CTRL_SRAM_ACE2_ATTR : R/W ;bitpos:[8:0] ;default: 9'hff ; */
/*description: .*/
#define APB_CTRL_SRAM_ACE2_ATTR    0x000001FF
#define APB_CTRL_SRAM_ACE2_ATTR_M  ((APB_CTRL_SRAM_ACE2_ATTR_V)<<(APB_CTRL_SRAM_ACE2_ATTR_S))
#define APB_CTRL_SRAM_ACE2_ATTR_V  0x1FF
#define APB_CTRL_SRAM_ACE2_ATTR_S  0

#define APB_CTRL_SRAM_ACE3_ATTR_REG          (DR_REG_APB_CTRL_BASE + 0x64)
/* APB_CTRL_SRAM_ACE3_ATTR : R/W ;bitpos:[8:0] ;default: 9'hff ; */
/*description: .*/
#define APB_CTRL_SRAM_ACE3_ATTR    0x000001FF
#define APB_CTRL_SRAM_ACE3_ATTR_M  ((APB_CTRL_SRAM_ACE3_ATTR_V)<<(APB_CTRL_SRAM_ACE3_ATTR_S))
#define APB_CTRL_SRAM_ACE3_ATTR_V  0x1FF
#define APB_CTRL_SRAM_ACE3_ATTR_S  0

#define APB_CTRL_SRAM_ACE0_ADDR_REG          (DR_REG_APB_CTRL_BASE + 0x68)
/* APB_CTRL_SRAM_ACE0_ADDR_S : R/W ;bitpos:[31:0] ;default: 32'h0 ; */
/*description: .*/
#define APB_CTRL_SRAM_ACE0_ADDR_S    0xFFFFFFFF
#define APB_CTRL_SRAM_ACE0_ADDR_S_M  ((APB_CTRL_SRAM_ACE0_ADDR_S_V)<<(APB_CTRL_SRAM_ACE0_ADDR_S_S))
#define APB_CTRL_SRAM_ACE0_ADDR_S_V  0xFFFFFFFF
#define APB_CTRL_SRAM_ACE0_ADDR_S_S  0

#define APB_CTRL_SRAM_ACE1_ADDR_REG          (DR_REG_APB_CTRL_BASE + 0x6C)
/* APB_CTRL_SRAM_ACE1_ADDR_S : R/W ;bitpos:[31:0] ;default: 32'h10000000 ; */
/*description: .*/
#define APB_CTRL_SRAM_ACE1_ADDR_S    0xFFFFFFFF
#define APB_CTRL_SRAM_ACE1_ADDR_S_M  ((APB_CTRL_SRAM_ACE1_ADDR_S_V)<<(APB_CTRL_SRAM_ACE1_ADDR_S_S))
#define APB_CTRL_SRAM_ACE1_ADDR_S_V  0xFFFFFFFF
#define APB_CTRL_SRAM_ACE1_ADDR_S_S  0

#define APB_CTRL_SRAM_ACE2_ADDR_REG          (DR_REG_APB_CTRL_BASE + 0x70)
/* APB_CTRL_SRAM_ACE2_ADDR_S : R/W ;bitpos:[31:0] ;default: 32'h20000000 ; */
/*description: .*/
#define APB_CTRL_SRAM_ACE2_ADDR_S    0xFFFFFFFF
#define APB_CTRL_SRAM_ACE2_ADDR_S_M  ((APB_CTRL_SRAM_ACE2_ADDR_S_V)<<(APB_CTRL_SRAM_ACE2_ADDR_S_S))
#define APB_CTRL_SRAM_ACE2_ADDR_S_V  0xFFFFFFFF
#define APB_CTRL_SRAM_ACE2_ADDR_S_S  0

#define APB_CTRL_SRAM_ACE3_ADDR_REG          (DR_REG_APB_CTRL_BASE + 0x74)
/* APB_CTRL_SRAM_ACE3_ADDR_S : R/W ;bitpos:[31:0] ;default: 32'h30000000 ; */
/*description: .*/
#define APB_CTRL_SRAM_ACE3_ADDR_S    0xFFFFFFFF
#define APB_CTRL_SRAM_ACE3_ADDR_S_M  ((APB_CTRL_SRAM_ACE3_ADDR_S_V)<<(APB_CTRL_SRAM_ACE3_ADDR_S_S))
#define APB_CTRL_SRAM_ACE3_ADDR_S_V  0xFFFFFFFF
#define APB_CTRL_SRAM_ACE3_ADDR_S_S  0

#define APB_CTRL_SRAM_ACE0_SIZE_REG          (DR_REG_APB_CTRL_BASE + 0x78)
/* APB_CTRL_SRAM_ACE0_SIZE : R/W ;bitpos:[15:0] ;default: 16'h1000 ; */
/*description: .*/
#define APB_CTRL_SRAM_ACE0_SIZE    0x0000FFFF
#define APB_CTRL_SRAM_ACE0_SIZE_M  ((APB_CTRL_SRAM_ACE0_SIZE_V)<<(APB_CTRL_SRAM_ACE0_SIZE_S))
#define APB_CTRL_SRAM_ACE0_SIZE_V  0xFFFF
#define APB_CTRL_SRAM_ACE0_SIZE_S  0

#define APB_CTRL_SRAM_ACE1_SIZE_REG          (DR_REG_APB_CTRL_BASE + 0x7C)
/* APB_CTRL_SRAM_ACE1_SIZE : R/W ;bitpos:[15:0] ;default: 16'h1000 ; */
/*description: .*/
#define APB_CTRL_SRAM_ACE1_SIZE    0x0000FFFF
#define APB_CTRL_SRAM_ACE1_SIZE_M  ((APB_CTRL_SRAM_ACE1_SIZE_V)<<(APB_CTRL_SRAM_ACE1_SIZE_S))
#define APB_CTRL_SRAM_ACE1_SIZE_V  0xFFFF
#define APB_CTRL_SRAM_ACE1_SIZE_S  0

#define APB_CTRL_SRAM_ACE2_SIZE_REG          (DR_REG_APB_CTRL_BASE + 0x80)
/* APB_CTRL_SRAM_ACE2_SIZE : R/W ;bitpos:[15:0] ;default: 16'h1000 ; */
/*description: .*/
#define APB_CTRL_SRAM_ACE2_SIZE    0x0000FFFF
#define APB_CTRL_SRAM_ACE2_SIZE_M  ((APB_CTRL_SRAM_ACE2_SIZE_V)<<(APB_CTRL_SRAM_ACE2_SIZE_S))
#define APB_CTRL_SRAM_ACE2_SIZE_V  0xFFFF
#define APB_CTRL_SRAM_ACE2_SIZE_S  0

#define APB_CTRL_SRAM_ACE3_SIZE_REG          (DR_REG_APB_CTRL_BASE + 0x84)
/* APB_CTRL_SRAM_ACE3_SIZE : R/W ;bitpos:[15:0] ;default: 16'h1000 ; */
/*description: .*/
#define APB_CTRL_SRAM_ACE3_SIZE    0x0000FFFF
#define APB_CTRL_SRAM_ACE3_SIZE_M  ((APB_CTRL_SRAM_ACE3_SIZE_V)<<(APB_CTRL_SRAM_ACE3_SIZE_S))
#define APB_CTRL_SRAM_ACE3_SIZE_V  0xFFFF
#define APB_CTRL_SRAM_ACE3_SIZE_S  0

#define APB_CTRL_SPI_MEM_PMS_CTRL_REG          (DR_REG_APB_CTRL_BASE + 0x88)
/* APB_CTRL_SPI_MEM_REJECT_CDE : RO ;bitpos:[6:2] ;default: 5'h0 ; */
/*description: .*/
#define APB_CTRL_SPI_MEM_REJECT_CDE    0x0000001F
#define APB_CTRL_SPI_MEM_REJECT_CDE_M  ((APB_CTRL_SPI_MEM_REJECT_CDE_V)<<(APB_CTRL_SPI_MEM_REJECT_CDE_S))
#define APB_CTRL_SPI_MEM_REJECT_CDE_V  0x1F
#define APB_CTRL_SPI_MEM_REJECT_CDE_S  2
/* APB_CTRL_SPI_MEM_REJECT_CLR : WOD ;bitpos:[1] ;default: 1'b0 ; */
/*description: .*/
#define APB_CTRL_SPI_MEM_REJECT_CLR    (1<<(1))
#define APB_CTRL_SPI_MEM_REJECT_CLR_M  (1<<(1))
#define APB_CTRL_SPI_MEM_REJECT_CLR_V  0x1
#define APB_CTRL_SPI_MEM_REJECT_CLR_S  1
/* APB_CTRL_SPI_MEM_REJECT_INT : RO ;bitpos:[0] ;default: 1'b0 ; */
/*description: .*/
#define APB_CTRL_SPI_MEM_REJECT_INT    (1<<(0))
#define APB_CTRL_SPI_MEM_REJECT_INT_M  (1<<(0))
#define APB_CTRL_SPI_MEM_REJECT_INT_V  0x1
#define APB_CTRL_SPI_MEM_REJECT_INT_S  0

#define APB_CTRL_SPI_MEM_REJECT_ADDR_REG          (DR_REG_APB_CTRL_BASE + 0x8C)
/* APB_CTRL_SPI_MEM_REJECT_ADDR : RO ;bitpos:[31:0] ;default: 32'h0 ; */
/*description: .*/
#define APB_CTRL_SPI_MEM_REJECT_ADDR    0xFFFFFFFF
#define APB_CTRL_SPI_MEM_REJECT_ADDR_M  ((APB_CTRL_SPI_MEM_REJECT_ADDR_V)<<(APB_CTRL_SPI_MEM_REJECT_ADDR_S))
#define APB_CTRL_SPI_MEM_REJECT_ADDR_V  0xFFFFFFFF
#define APB_CTRL_SPI_MEM_REJECT_ADDR_S  0

#define APB_CTRL_SDIO_CTRL_REG          (DR_REG_APB_CTRL_BASE + 0x90)
/* APB_CTRL_SDIO_WIN_ACCESS_EN : R/W ;bitpos:[0] ;default: 1'h0 ; */
/*description: .*/
#define APB_CTRL_SDIO_WIN_ACCESS_EN    (1<<(0))
#define APB_CTRL_SDIO_WIN_ACCESS_EN_M  (1<<(0))
#define APB_CTRL_SDIO_WIN_ACCESS_EN_V  0x1
#define APB_CTRL_SDIO_WIN_ACCESS_EN_S  0

#define APB_CTRL_REDCY_SIG0_REG          (DR_REG_APB_CTRL_BASE + 0x94)
/* APB_CTRL_REDCY_ANDOR : RO ;bitpos:[31] ;default: 1'h0 ; */
/*description: .*/
#define APB_CTRL_REDCY_ANDOR    (1<<(31))
#define APB_CTRL_REDCY_ANDOR_M  (1<<(31))
#define APB_CTRL_REDCY_ANDOR_V  0x1
#define APB_CTRL_REDCY_ANDOR_S  31
/* APB_CTRL_REDCY_SIG0 : R/W ;bitpos:[30:0] ;default: 31'h0 ; */
/*description: .*/
#define APB_CTRL_REDCY_SIG0    0x7FFFFFFF
#define APB_CTRL_REDCY_SIG0_M  ((APB_CTRL_REDCY_SIG0_V)<<(APB_CTRL_REDCY_SIG0_S))
#define APB_CTRL_REDCY_SIG0_V  0x7FFFFFFF
#define APB_CTRL_REDCY_SIG0_S  0

#define APB_CTRL_REDCY_SIG1_REG          (DR_REG_APB_CTRL_BASE + 0x98)
/* APB_CTRL_REDCY_NANDOR : RO ;bitpos:[31] ;default: 1'h0 ; */
/*description: .*/
#define APB_CTRL_REDCY_NANDOR    (1<<(31))
#define APB_CTRL_REDCY_NANDOR_M  (1<<(31))
#define APB_CTRL_REDCY_NANDOR_V  0x1
#define APB_CTRL_REDCY_NANDOR_S  31
/* APB_CTRL_REDCY_SIG1 : R/W ;bitpos:[30:0] ;default: 31'h0 ; */
/*description: .*/
#define APB_CTRL_REDCY_SIG1    0x7FFFFFFF
#define APB_CTRL_REDCY_SIG1_M  ((APB_CTRL_REDCY_SIG1_V)<<(APB_CTRL_REDCY_SIG1_S))
#define APB_CTRL_REDCY_SIG1_V  0x7FFFFFFF
#define APB_CTRL_REDCY_SIG1_S  0

#define APB_CTRL_FRONT_END_MEM_PD_REG          (DR_REG_APB_CTRL_BASE + 0x9C)
/* APB_CTRL_FREQ_MEM_FORCE_PD : R/W ;bitpos:[7] ;default: 1'b0 ; */
/*description: .*/
#define APB_CTRL_FREQ_MEM_FORCE_PD    (1<<(7))
#define APB_CTRL_FREQ_MEM_FORCE_PD_M  (1<<(7))
#define APB_CTRL_FREQ_MEM_FORCE_PD_V  0x1
#define APB_CTRL_FREQ_MEM_FORCE_PD_S  7
/* APB_CTRL_FREQ_MEM_FORCE_PU : R/W ;bitpos:[6] ;default: 1'b1 ; */
/*description: .*/
#define APB_CTRL_FREQ_MEM_FORCE_PU    (1<<(6))
#define APB_CTRL_FREQ_MEM_FORCE_PU_M  (1<<(6))
#define APB_CTRL_FREQ_MEM_FORCE_PU_V  0x1
#define APB_CTRL_FREQ_MEM_FORCE_PU_S  6
/* APB_CTRL_DC_MEM_FORCE_PD : R/W ;bitpos:[5] ;default: 1'b0 ; */
/*description: .*/
#define APB_CTRL_DC_MEM_FORCE_PD    (1<<(5))
#define APB_CTRL_DC_MEM_FORCE_PD_M  (1<<(5))
#define APB_CTRL_DC_MEM_FORCE_PD_V  0x1
#define APB_CTRL_DC_MEM_FORCE_PD_S  5
/* APB_CTRL_DC_MEM_FORCE_PU : R/W ;bitpos:[4] ;default: 1'b1 ; */
/*description: .*/
#define APB_CTRL_DC_MEM_FORCE_PU    (1<<(4))
#define APB_CTRL_DC_MEM_FORCE_PU_M  (1<<(4))
#define APB_CTRL_DC_MEM_FORCE_PU_V  0x1
#define APB_CTRL_DC_MEM_FORCE_PU_S  4
/* APB_CTRL_PBUS_MEM_FORCE_PD : R/W ;bitpos:[3] ;default: 1'b0 ; */
/*description: .*/
#define APB_CTRL_PBUS_MEM_FORCE_PD    (1<<(3))
#define APB_CTRL_PBUS_MEM_FORCE_PD_M  (1<<(3))
#define APB_CTRL_PBUS_MEM_FORCE_PD_V  0x1
#define APB_CTRL_PBUS_MEM_FORCE_PD_S  3
/* APB_CTRL_PBUS_MEM_FORCE_PU : R/W ;bitpos:[2] ;default: 1'b1 ; */
/*description: .*/
#define APB_CTRL_PBUS_MEM_FORCE_PU    (1<<(2))
#define APB_CTRL_PBUS_MEM_FORCE_PU_M  (1<<(2))
#define APB_CTRL_PBUS_MEM_FORCE_PU_V  0x1
#define APB_CTRL_PBUS_MEM_FORCE_PU_S  2
/* APB_CTRL_AGC_MEM_FORCE_PD : R/W ;bitpos:[1] ;default: 1'b0 ; */
/*description: .*/
#define APB_CTRL_AGC_MEM_FORCE_PD    (1<<(1))
#define APB_CTRL_AGC_MEM_FORCE_PD_M  (1<<(1))
#define APB_CTRL_AGC_MEM_FORCE_PD_V  0x1
#define APB_CTRL_AGC_MEM_FORCE_PD_S  1
/* APB_CTRL_AGC_MEM_FORCE_PU : R/W ;bitpos:[0] ;default: 1'b1 ; */
/*description: .*/
#define APB_CTRL_AGC_MEM_FORCE_PU    (1<<(0))
#define APB_CTRL_AGC_MEM_FORCE_PU_M  (1<<(0))
#define APB_CTRL_AGC_MEM_FORCE_PU_V  0x1
#define APB_CTRL_AGC_MEM_FORCE_PU_S  0

#define APB_CTRL_SPI_MEM_ECC_CTRL_REG          (DR_REG_APB_CTRL_BASE + 0xA0)
/* APB_CTRL_SRAM_PAGE_SIZE : R/W ;bitpos:[21:20] ;default: 2'd2 ; */
/*description: Set the page size of the used MSPI external RAM. 0: 256 bytes. 1: 512 bytes. 2:
1024 bytes. 3: 2048 bytes..*/
#define APB_CTRL_SRAM_PAGE_SIZE    0x00000003
#define APB_CTRL_SRAM_PAGE_SIZE_M  ((APB_CTRL_SRAM_PAGE_SIZE_V)<<(APB_CTRL_SRAM_PAGE_SIZE_S))
#define APB_CTRL_SRAM_PAGE_SIZE_V  0x3
#define APB_CTRL_SRAM_PAGE_SIZE_S  20
/* APB_CTRL_FLASH_PAGE_SIZE : R/W ;bitpos:[19:18] ;default: 2'd0 ; */
/*description: Set the page size of the used MSPI flash. 0: 256 bytes. 1: 512 bytes. 2: 1024 by
tes. 3: 2048 bytes..*/
#define APB_CTRL_FLASH_PAGE_SIZE    0x00000003
#define APB_CTRL_FLASH_PAGE_SIZE_M  ((APB_CTRL_FLASH_PAGE_SIZE_V)<<(APB_CTRL_FLASH_PAGE_SIZE_S))
#define APB_CTRL_FLASH_PAGE_SIZE_V  0x3
#define APB_CTRL_FLASH_PAGE_SIZE_S  18

#define APB_CTRL_CLKGATE_FORCE_ON_REG          (DR_REG_APB_CTRL_BASE + 0xA8)
/* APB_CTRL_SRAM_CLKGATE_FORCE_ON : R/W ;bitpos:[13:3] ;default: ~11'b0 ; */
/*description: .*/
#define APB_CTRL_SRAM_CLKGATE_FORCE_ON    0x000007FF
#define APB_CTRL_SRAM_CLKGATE_FORCE_ON_M  ((APB_CTRL_SRAM_CLKGATE_FORCE_ON_V)<<(APB_CTRL_SRAM_CLKGATE_FORCE_ON_S))
#define APB_CTRL_SRAM_CLKGATE_FORCE_ON_V  0x7FF
#define APB_CTRL_SRAM_CLKGATE_FORCE_ON_S  3
/* APB_CTRL_ROM_CLKGATE_FORCE_ON : R/W ;bitpos:[2:0] ;default: ~3'b0 ; */
/*description: .*/
#define APB_CTRL_ROM_CLKGATE_FORCE_ON    0x00000007
#define APB_CTRL_ROM_CLKGATE_FORCE_ON_M  ((APB_CTRL_ROM_CLKGATE_FORCE_ON_V)<<(APB_CTRL_ROM_CLKGATE_FORCE_ON_S))
#define APB_CTRL_ROM_CLKGATE_FORCE_ON_V  0x7
#define APB_CTRL_ROM_CLKGATE_FORCE_ON_S  0

#define APB_CTRL_MEM_POWER_DOWN_REG          (DR_REG_APB_CTRL_BASE + 0xAC)
/* APB_CTRL_SRAM_POWER_DOWN : R/W ;bitpos:[13:3] ;default: 11'b0 ; */
/*description: .*/
#define APB_CTRL_SRAM_POWER_DOWN    0x000007FF
#define APB_CTRL_SRAM_POWER_DOWN_M  ((APB_CTRL_SRAM_POWER_DOWN_V)<<(APB_CTRL_SRAM_POWER_DOWN_S))
#define APB_CTRL_SRAM_POWER_DOWN_V  0x7FF
#define APB_CTRL_SRAM_POWER_DOWN_S  3
/* APB_CTRL_ROM_POWER_DOWN : R/W ;bitpos:[2:0] ;default: 3'b0 ; */
/*description: .*/
#define APB_CTRL_ROM_POWER_DOWN    0x00000007
#define APB_CTRL_ROM_POWER_DOWN_M  ((APB_CTRL_ROM_POWER_DOWN_V)<<(APB_CTRL_ROM_POWER_DOWN_S))
#define APB_CTRL_ROM_POWER_DOWN_V  0x7
#define APB_CTRL_ROM_POWER_DOWN_S  0

#define APB_CTRL_MEM_POWER_UP_REG          (DR_REG_APB_CTRL_BASE + 0xB0)
/* APB_CTRL_SRAM_POWER_UP : R/W ;bitpos:[13:3] ;default: ~11'b0 ; */
/*description: .*/
#define APB_CTRL_SRAM_POWER_UP    0x000007FF
#define APB_CTRL_SRAM_POWER_UP_M  ((APB_CTRL_SRAM_POWER_UP_V)<<(APB_CTRL_SRAM_POWER_UP_S))
#define APB_CTRL_SRAM_POWER_UP_V  0x7FF
#define APB_CTRL_SRAM_POWER_UP_S  3
/* APB_CTRL_ROM_POWER_UP : R/W ;bitpos:[2:0] ;default: ~3'b0 ; */
/*description: .*/
#define APB_CTRL_ROM_POWER_UP    0x00000007
#define APB_CTRL_ROM_POWER_UP_M  ((APB_CTRL_ROM_POWER_UP_V)<<(APB_CTRL_ROM_POWER_UP_S))
#define APB_CTRL_ROM_POWER_UP_V  0x7
#define APB_CTRL_ROM_POWER_UP_S  0

#define APB_CTRL_RETENTION_CTRL_REG          (DR_REG_APB_CTRL_BASE + 0xB4)
/* APB_CTRL_NOBYPASS_CPU_ISO_RST : R/W ;bitpos:[27] ;default: 1'b0 ; */
/*description: .*/
#define APB_CTRL_NOBYPASS_CPU_ISO_RST    (1<<(27))
#define APB_CTRL_NOBYPASS_CPU_ISO_RST_M  (1<<(27))
#define APB_CTRL_NOBYPASS_CPU_ISO_RST_V  0x1
#define APB_CTRL_NOBYPASS_CPU_ISO_RST_S  27
/* APB_CTRL_RETENTION_CPU_LINK_ADDR : R/W ;bitpos:[26:0] ;default: 27'd0 ; */
/*description: .*/
#define APB_CTRL_RETENTION_CPU_LINK_ADDR    0x07FFFFFF
#define APB_CTRL_RETENTION_CPU_LINK_ADDR_M  ((APB_CTRL_RETENTION_CPU_LINK_ADDR_V)<<(APB_CTRL_RETENTION_CPU_LINK_ADDR_S))
#define APB_CTRL_RETENTION_CPU_LINK_ADDR_V  0x7FFFFFF
#define APB_CTRL_RETENTION_CPU_LINK_ADDR_S  0

#define APB_CTRL_RETENTION_CTRL1_REG          (DR_REG_APB_CTRL_BASE + 0xB8)
/* APB_CTRL_RETENTION_TAG_LINK_ADDR : R/W ;bitpos:[26:0] ;default: 27'd0 ; */
/*description: .*/
#define APB_CTRL_RETENTION_TAG_LINK_ADDR    0x07FFFFFF
#define APB_CTRL_RETENTION_TAG_LINK_ADDR_M  ((APB_CTRL_RETENTION_TAG_LINK_ADDR_V)<<(APB_CTRL_RETENTION_TAG_LINK_ADDR_S))
#define APB_CTRL_RETENTION_TAG_LINK_ADDR_V  0x7FFFFFF
#define APB_CTRL_RETENTION_TAG_LINK_ADDR_S  0

#define APB_CTRL_RETENTION_CTRL2_REG          (DR_REG_APB_CTRL_BASE + 0xBC)
/* APB_CTRL_RET_ICACHE_ENABLE : R/W ;bitpos:[31] ;default: 1'b0 ; */
/*description: .*/
#define APB_CTRL_RET_ICACHE_ENABLE    (1<<(31))
#define APB_CTRL_RET_ICACHE_ENABLE_M  (1<<(31))
#define APB_CTRL_RET_ICACHE_ENABLE_V  0x1
#define APB_CTRL_RET_ICACHE_ENABLE_S  31
/* APB_CTRL_RET_ICACHE_START_POINT : R/W ;bitpos:[29:22] ;default: 8'd0 ; */
/*description: .*/
#define APB_CTRL_RET_ICACHE_START_POINT    0x000000FF
#define APB_CTRL_RET_ICACHE_START_POINT_M  ((APB_CTRL_RET_ICACHE_START_POINT_V)<<(APB_CTRL_RET_ICACHE_START_POINT_S))
#define APB_CTRL_RET_ICACHE_START_POINT_V  0xFF
#define APB_CTRL_RET_ICACHE_START_POINT_S  22
/* APB_CTRL_RET_ICACHE_VLD_SIZE : R/W ;bitpos:[20:13] ;default: 8'hff ; */
/*description: .*/
#define APB_CTRL_RET_ICACHE_VLD_SIZE    0x000000FF
#define APB_CTRL_RET_ICACHE_VLD_SIZE_M  ((APB_CTRL_RET_ICACHE_VLD_SIZE_V)<<(APB_CTRL_RET_ICACHE_VLD_SIZE_S))
#define APB_CTRL_RET_ICACHE_VLD_SIZE_V  0xFF
#define APB_CTRL_RET_ICACHE_VLD_SIZE_S  13
/* APB_CTRL_RET_ICACHE_SIZE : R/W ;bitpos:[11:4] ;default: 8'hff ; */
/*description: .*/
#define APB_CTRL_RET_ICACHE_SIZE    0x000000FF
#define APB_CTRL_RET_ICACHE_SIZE_M  ((APB_CTRL_RET_ICACHE_SIZE_V)<<(APB_CTRL_RET_ICACHE_SIZE_S))
#define APB_CTRL_RET_ICACHE_SIZE_V  0xFF
#define APB_CTRL_RET_ICACHE_SIZE_S  4

#define APB_CTRL_RETENTION_CTRL3_REG          (DR_REG_APB_CTRL_BASE + 0xC0)
/* APB_CTRL_RET_DCACHE_ENABLE : R/W ;bitpos:[31] ;default: 1'b0 ; */
/*description: .*/
#define APB_CTRL_RET_DCACHE_ENABLE    (1<<(31))
#define APB_CTRL_RET_DCACHE_ENABLE_M  (1<<(31))
#define APB_CTRL_RET_DCACHE_ENABLE_V  0x1
#define APB_CTRL_RET_DCACHE_ENABLE_S  31
/* APB_CTRL_RET_DCACHE_START_POINT : R/W ;bitpos:[30:22] ;default: 9'd0 ; */
/*description: .*/
#define APB_CTRL_RET_DCACHE_START_POINT    0x000001FF
#define APB_CTRL_RET_DCACHE_START_POINT_M  ((APB_CTRL_RET_DCACHE_START_POINT_V)<<(APB_CTRL_RET_DCACHE_START_POINT_S))
#define APB_CTRL_RET_DCACHE_START_POINT_V  0x1FF
#define APB_CTRL_RET_DCACHE_START_POINT_S  22
/* APB_CTRL_RET_DCACHE_VLD_SIZE : R/W ;bitpos:[21:13] ;default: 9'h1ff ; */
/*description: .*/
#define APB_CTRL_RET_DCACHE_VLD_SIZE    0x000001FF
#define APB_CTRL_RET_DCACHE_VLD_SIZE_M  ((APB_CTRL_RET_DCACHE_VLD_SIZE_V)<<(APB_CTRL_RET_DCACHE_VLD_SIZE_S))
#define APB_CTRL_RET_DCACHE_VLD_SIZE_V  0x1FF
#define APB_CTRL_RET_DCACHE_VLD_SIZE_S  13
/* APB_CTRL_RET_DCACHE_SIZE : R/W ;bitpos:[12:4] ;default: 9'h1ff ; */
/*description: .*/
#define APB_CTRL_RET_DCACHE_SIZE    0x000001FF
#define APB_CTRL_RET_DCACHE_SIZE_M  ((APB_CTRL_RET_DCACHE_SIZE_V)<<(APB_CTRL_RET_DCACHE_SIZE_S))
#define APB_CTRL_RET_DCACHE_SIZE_V  0x1FF
#define APB_CTRL_RET_DCACHE_SIZE_S  4

#define APB_CTRL_RETENTION_CTRL4_REG          (DR_REG_APB_CTRL_BASE + 0xC4)
/* APB_CTRL_RETENTION_INV_CFG : R/W ;bitpos:[31:0] ;default: ~32'h0 ; */
/*description: .*/
#define APB_CTRL_RETENTION_INV_CFG    0xFFFFFFFF
#define APB_CTRL_RETENTION_INV_CFG_M  ((APB_CTRL_RETENTION_INV_CFG_V)<<(APB_CTRL_RETENTION_INV_CFG_S))
#define APB_CTRL_RETENTION_INV_CFG_V  0xFFFFFFFF
#define APB_CTRL_RETENTION_INV_CFG_S  0

#define APB_CTRL_RETENTION_CTRL5_REG          (DR_REG_APB_CTRL_BASE + 0xC8)
/* APB_CTRL_RETENTION_DISABLE : R/W ;bitpos:[0] ;default: 1'b0 ; */
/*description: .*/
#define APB_CTRL_RETENTION_DISABLE    (1<<(0))
#define APB_CTRL_RETENTION_DISABLE_M  (1<<(0))
#define APB_CTRL_RETENTION_DISABLE_V  0x1
#define APB_CTRL_RETENTION_DISABLE_S  0

#define APB_CTRL_DATE_REG          (DR_REG_APB_CTRL_BASE + 0x3FC)
/* APB_CTRL_DATE : R/W ;bitpos:[31:0] ;default: 32'h2101150 ; */
/*description: Version control.*/
#define APB_CTRL_DATE    0xFFFFFFFF
#define APB_CTRL_DATE_M  ((APB_CTRL_DATE_V)<<(APB_CTRL_DATE_S))
#define APB_CTRL_DATE_V  0xFFFFFFFF
#define APB_CTRL_DATE_S  0


typedef volatile struct rtc_cntl_dev_s {
	union {
		struct {
			uint32_t sw_stall_appcpu_c0            :    2;  /*{reg_sw_stall_appcpu_c1[5:0],  reg_sw_stall_appcpu_c0[1:0]} == 0x86 will stall APP CPU*/
			uint32_t sw_stall_procpu_c0            :    2;  /*{reg_sw_stall_procpu_c1[5:0],  reg_sw_stall_procpu_c0[1:0]} == 0x86 will stall PRO CPU*/
			uint32_t sw_appcpu_rst                 :    1;  /*APP CPU SW reset*/
			uint32_t sw_procpu_rst                 :    1;  /*PRO CPU SW reset*/
			uint32_t bb_i2c_force_pd               :    1;  /*BB_I2C force power down*/
			uint32_t bb_i2c_force_pu               :    1;  /*BB_I2C force power up*/
			uint32_t bbpll_i2c_force_pd            :    1;  /*BB_PLL _I2C force power down*/
			uint32_t bbpll_i2c_force_pu            :    1;  /*BB_PLL_I2C force power up*/
			uint32_t bbpll_force_pd                :    1;  /*BB_PLL force power down*/
			uint32_t bbpll_force_pu                :    1;  /*BB_PLL force power up*/
			uint32_t xtl_force_pd                  :    1;  /*crystall force power down*/
			uint32_t xtl_force_pu                  :    1;  /*crystall force power up*/
			uint32_t xtl_en_wait                   :    4;  /*wait bias_sleep and current source wakeup*/
			uint32_t reserved18                    :    5;
			uint32_t xtl_force_iso                 :    1;
			uint32_t pll_force_iso                 :    1;
			uint32_t analog_force_iso              :    1;
			uint32_t xtl_force_noiso               :    1;
			uint32_t pll_force_noiso               :    1;
			uint32_t analog_force_noiso            :    1;
			uint32_t dg_wrap_force_rst             :    1;  /*digital wrap force reset in deep sleep*/
			uint32_t dg_wrap_force_norst           :    1;  /*digital core force no reset in deep sleep*/
			uint32_t sw_sys_rst                    :    1;  /*SW system reset*/
		};
		uint32_t val;
	} options0;
	uint32_t slp_timer0;
	union {
		struct {
			uint32_t slp_val_hi                    :    16;  /*RTC sleep timer high 16 bits*/
			uint32_t main_timer_alarm_en           :    1;  /*timer alarm enable bit*/
			uint32_t reserved17                    :    15;
		};
		uint32_t val;
	} slp_timer1;
	union {
		struct {
			uint32_t reserved0                     :    27;
			uint32_t timer_sys_stall               :    1;  /*Enable to record system stall time*/
			uint32_t timer_xtl_off                 :    1;  /*Enable to record 40M XTAL OFF time*/
			uint32_t timer_sys_rst                 :    1;  /*enable to record system reset time*/
			uint32_t reserved30                    :    1;
			uint32_t update                        :    1;  /*Set 1: to update register with RTC timer*/
		};
		uint32_t val;
	} time_update;
	uint32_t time_low0;
	union {
		struct {
			uint32_t rtc_timer_value0_high         :    16;  /*RTC timer high 16 bits*/
			uint32_t reserved16                    :    16;
		};
		uint32_t val;
	} time_high0;
	union {
		struct {
			uint32_t rtc_sw_cpu_int                :    1;  /*rtc software interrupt to main cpu*/
			uint32_t rtc_slp_reject_cause_clr      :    1;  /*clear rtc sleep reject cause*/
			uint32_t reserved2                     :    20;
			uint32_t apb2rtc_bridge_sel            :    1;  /*1: APB to RTC using bridge*/
			uint32_t reserved23                    :    5;
			uint32_t sdio_active_ind               :    1;  /*SDIO active indication*/
			uint32_t slp_wakeup                    :    1;  /*leep wakeup bit*/
			uint32_t slp_reject                    :    1;  /*leep reject bit*/
			uint32_t sleep_en                      :    1;  /*sleep enable bit*/
		};
		uint32_t val;
	} state0;
	union {
		struct {
			uint32_t cpu_stall_en                  :    1;  /*CPU stall enable bit*/
			uint32_t cpu_stall_wait                :    5;  /*CPU stall wait cycles in fast_clk_rtc*/
			uint32_t ck8m_wait                     :    8;  /*CK8M wait cycles in slow_clk_rtc*/
			uint32_t xtl_buf_wait                  :    10;  /*XTAL wait cycles in slow_clk_rtc*/
			uint32_t pll_buf_wait                  :    8;  /*PLL wait cycles in slow_clk_rtc*/
		};
		uint32_t val;
	} timer1;
	union {
		struct {
			uint32_t reserved0                     :    15;
			uint32_t ulpcp_touch_start_wait        :    9;  /*wait cycles in slow_clk_rtc before ULP-coprocessor / touch controller start to work*/
			uint32_t min_time_ck8m_off             :    8;  /*minimal cycles in slow_clk_rtc for CK8M in power down state*/
		};
		uint32_t val;
	} timer2;
	union {
		struct {
			uint32_t wifi_wait_timer               :    9;
			uint32_t wifi_powerup_timer            :    7;
			uint32_t bt_wait_timer                 :    9;
			uint32_t bt_powerup_timer              :    7;
		};
		uint32_t val;
	} timer3;
	union {
		struct {
			uint32_t rtc_wait_timer                :    9;
			uint32_t rtc_powerup_timer             :    7;
			uint32_t dg_wrap_wait_timer            :    9;
			uint32_t dg_wrap_powerup_timer         :    7;
		};
		uint32_t val;
	} timer4;
	union {
		struct {
			uint32_t reserved0                     :    8;
			uint32_t min_slp_val                   :    8;  /*minimal sleep cycles in slow_clk_rtc*/
			uint32_t reserved16                    :    16;
		};
		uint32_t val;
	} timer5;
	union {
		struct {
			uint32_t cpu_top_wait_timer            :    9;
			uint32_t cpu_top_powerup_timer         :    7;
			uint32_t dg_peri_wait_timer            :    9;
			uint32_t dg_peri_powerup_timer         :    7;
		};
		uint32_t val;
	} timer6;
	union {
		struct {
			uint32_t reserved0                     :    18;
			uint32_t i2c_reset_por_force_pd        :    1;
			uint32_t i2c_reset_por_force_pu        :    1;
			uint32_t glitch_rst_en                 :    1;
			uint32_t reserved21                    :    1;  /*PLLA force power down*/
			uint32_t sar_i2c_pu                    :    1;  /*PLLA force power up*/
			uint32_t analog_top_iso_sleep          :    1;  /*PLLA force power down*/
			uint32_t analog_top_iso_monitor        :    1;  /*PLLA force power up*/
			uint32_t bbpll_cal_slp_start           :    1;  /*start BBPLL calibration during sleep*/
			uint32_t pvtmon_pu                     :    1;  /*1: PVTMON power up*/
			uint32_t txrf_i2c_pu                   :    1;  /*1: TXRF_I2C power up*/
			uint32_t rfrx_pbus_pu                  :    1;  /*1: RFRX_PBUS power up*/
			uint32_t reserved29                    :    1;
			uint32_t ckgen_i2c_pu                  :    1;  /*1: CKGEN_I2C power up*/
			uint32_t pll_i2c_pu                    :    1;
		};
		uint32_t val;
	} ana_conf;
	union {
		struct {
			uint32_t reset_cause_procpu            :    6;  /*reset cause of PRO CPU*/
			uint32_t reset_cause_appcpu            :    6;  /*reset cause of APP CPU*/
			uint32_t appcpu_stat_vector_sel        :    1;  /*APP CPU state vector sel*/
			uint32_t procpu_stat_vector_sel        :    1;  /*PRO CPU state vector sel*/
			uint32_t reset_flag_procpu             :    1;  /*PRO CPU reset_flag*/
			uint32_t reset_flag_appcpu             :    1;  /*APP CPU reset flag*/
			uint32_t reset_flag_procpu_clr         :    1;  /*clear PRO CPU reset_flag*/
			uint32_t reset_flag_appcpu_clr         :    1;  /*clear APP CPU reset flag*/
			uint32_t appcpu_ocd_halt_on_reset      :    1;  /*APPCPU OcdHaltOnReset*/
			uint32_t procpu_ocd_halt_on_reset      :    1;  /*PROCPU OcdHaltOnReset*/
			uint32_t reset_flag_jtag_procpu        :    1;
			uint32_t reset_flag_jtag_appcpu        :    1;
			uint32_t reset_flag_jtag_procpu_clr    :    1;
			uint32_t reset_flag_jtag_appcpu_clr    :    1;
			uint32_t rtc_app_dreset_mask           :    1;
			uint32_t rtc_pro_dreset_mask           :    1;
			uint32_t reserved26                    :    6;
		};
		uint32_t val;
	} reset_state;
	union {
		struct {
			uint32_t reserved0                     :    15;
			uint32_t rtc_wakeup_ena                :    17;  /*wakeup enable bitmap*/
		};
		uint32_t val;
	} wakeup_state;
	union {
		struct {
			uint32_t slp_wakeup                    :    1;  /*enable sleep wakeup interrupt*/
			uint32_t slp_reject                    :    1;  /*enable sleep reject interrupt*/
			uint32_t sdio_idle                     :    1;  /*enable SDIO idle interrupt*/
			uint32_t rtc_wdt                       :    1;  /*enable RTC WDT interrupt*/
			uint32_t rtc_touch_scan_done           :    1;  /*enable touch scan done interrupt*/
			uint32_t rtc_ulp_cp                    :    1;  /*enable ULP-coprocessor interrupt*/
			uint32_t rtc_touch_done                :    1;  /*enable touch done interrupt*/
			uint32_t rtc_touch_active              :    1;  /*enable touch active interrupt*/
			uint32_t rtc_touch_inactive            :    1;  /*enable touch inactive interrupt*/
			uint32_t rtc_brown_out                 :    1;  /*enable brown out interrupt*/
			uint32_t rtc_main_timer                :    1;  /*enable RTC main timer interrupt*/
			uint32_t rtc_saradc1                   :    1;  /*enable saradc1 interrupt*/
			uint32_t rtc_tsens                     :    1;  /*enable tsens interrupt*/
			uint32_t rtc_cocpu                     :    1;  /*enable riscV cocpu interrupt*/
			uint32_t rtc_saradc2                   :    1;  /*enable saradc2 interrupt*/
			uint32_t rtc_swd                       :    1;  /*enable super watch dog interrupt*/
			uint32_t rtc_xtal32k_dead              :    1;  /*enable xtal32k_dead  interrupt*/
			uint32_t rtc_cocpu_trap                :    1;  /*enable cocpu trap interrupt*/
			uint32_t rtc_touch_timeout             :    1;  /*enable touch timeout interrupt*/
			uint32_t rtc_glitch_det                :    1;  /*enbale gitch det interrupt*/
			uint32_t rtc_touch_approach_loop_done  :    1;
			uint32_t reserved21                    :    11;
		};
		uint32_t val;
	} int_ena;
	union {
		struct {
			uint32_t slp_wakeup                    :    1;  /*sleep wakeup interrupt raw*/
			uint32_t slp_reject                    :    1;  /*sleep reject interrupt raw*/
			uint32_t sdio_idle                     :    1;  /*SDIO idle interrupt raw*/
			uint32_t rtc_wdt                       :    1;  /*RTC WDT interrupt raw*/
			uint32_t rtc_touch_scan_done           :    1;
			uint32_t rtc_ulp_cp                    :    1;  /*ULP-coprocessor interrupt raw*/
			uint32_t rtc_touch_done                :    1;  /*touch interrupt raw*/
			uint32_t rtc_touch_active              :    1;  /*touch active interrupt raw*/
			uint32_t rtc_touch_inactive            :    1;  /*touch inactive interrupt raw*/
			uint32_t rtc_brown_out                 :    1;  /*brown out interrupt raw*/
			uint32_t rtc_main_timer                :    1;  /*RTC main timer interrupt raw*/
			uint32_t rtc_saradc1                   :    1;  /*saradc1 interrupt raw*/
			uint32_t rtc_tsens                     :    1;  /*tsens interrupt raw*/
			uint32_t rtc_cocpu                     :    1;  /*riscV cocpu interrupt raw*/
			uint32_t rtc_saradc2                   :    1;  /*saradc2 interrupt raw*/
			uint32_t rtc_swd                       :    1;  /*super watch dog interrupt raw*/
			uint32_t rtc_xtal32k_dead              :    1;  /*xtal32k dead detection interrupt raw*/
			uint32_t rtc_cocpu_trap                :    1;  /*cocpu trap interrupt raw*/
			uint32_t rtc_touch_timeout             :    1;  /*touch timeout interrupt raw*/
			uint32_t rtc_glitch_det                :    1;  /*glitch_det_interrupt_raw*/
			uint32_t rtc_touch_approach_loop_done  :    1;
			uint32_t reserved21                    :    11;
		};
		uint32_t val;
	} int_raw;
	union {
		struct {
			uint32_t slp_wakeup                    :    1;  /*sleep wakeup interrupt state*/
			uint32_t slp_reject                    :    1;  /*sleep reject interrupt state*/
			uint32_t sdio_idle                     :    1;  /*SDIO idle interrupt state*/
			uint32_t rtc_wdt                       :    1;  /*RTC WDT interrupt state*/
			uint32_t rtc_touch_scan_done           :    1;
			uint32_t rtc_ulp_cp                    :    1;  /*ULP-coprocessor interrupt state*/
			uint32_t rtc_touch_done                :    1;  /*touch done interrupt state*/
			uint32_t rtc_touch_active              :    1;  /*touch active interrupt state*/
			uint32_t rtc_touch_inactive            :    1;  /*touch inactive interrupt state*/
			uint32_t rtc_brown_out                 :    1;  /*brown out interrupt state*/
			uint32_t rtc_main_timer                :    1;  /*RTC main timer interrupt state*/
			uint32_t rtc_saradc1                   :    1;  /*saradc1 interrupt state*/
			uint32_t rtc_tsens                     :    1;  /*tsens interrupt state*/
			uint32_t rtc_cocpu                     :    1;  /*riscV cocpu interrupt state*/
			uint32_t rtc_saradc2                   :    1;  /*saradc2 interrupt state*/
			uint32_t rtc_swd                       :    1;  /*super watch dog interrupt state*/
			uint32_t rtc_xtal32k_dead              :    1;  /*xtal32k dead detection interrupt state*/
			uint32_t rtc_cocpu_trap                :    1;  /*cocpu trap interrupt state*/
			uint32_t rtc_touch_timeout             :    1;  /*Touch timeout interrupt state*/
			uint32_t rtc_glitch_det                :    1;  /*glitch_det_interrupt state*/
			uint32_t rtc_touch_approach_loop_done  :    1;
			uint32_t reserved21                    :    11;
		};
		uint32_t val;
	} int_st;
	union {
		struct {
			uint32_t slp_wakeup                    :    1;  /*Clear sleep wakeup interrupt state*/
			uint32_t slp_reject                    :    1;  /*Clear sleep reject interrupt state*/
			uint32_t sdio_idle                     :    1;  /*Clear SDIO idle interrupt state*/
			uint32_t rtc_wdt                       :    1;  /*Clear RTC WDT interrupt state*/
			uint32_t rtc_touch_scan_done           :    1;
			uint32_t rtc_ulp_cp                    :    1;  /*Clear ULP-coprocessor interrupt state*/
			uint32_t rtc_touch_done                :    1;  /*Clear touch done interrupt state*/
			uint32_t rtc_touch_active              :    1;  /*Clear touch active interrupt state*/
			uint32_t rtc_touch_inactive            :    1;  /*Clear touch inactive interrupt state*/
			uint32_t rtc_brown_out                 :    1;  /*Clear brown out interrupt state*/
			uint32_t rtc_main_timer                :    1;  /*Clear RTC main timer interrupt state*/
			uint32_t rtc_saradc1                   :    1;  /*Clear saradc1 interrupt state*/
			uint32_t rtc_tsens                     :    1;  /*Clear tsens interrupt state*/
			uint32_t rtc_cocpu                     :    1;  /*Clear riscV cocpu interrupt state*/
			uint32_t rtc_saradc2                   :    1;  /*Clear saradc2 interrupt state*/
			uint32_t rtc_swd                       :    1;  /*Clear super watch dog interrupt state*/
			uint32_t rtc_xtal32k_dead              :    1;  /*Clear RTC WDT interrupt state*/
			uint32_t rtc_cocpu_trap                :    1;  /*Clear cocpu trap interrupt state*/
			uint32_t rtc_touch_timeout             :    1;  /*Clear touch timeout interrupt state*/
			uint32_t rtc_glitch_det                :    1;  /*Clear glitch det interrupt state*/
			uint32_t rtc_touch_approach_loop_done  :    1;
			uint32_t reserved21                    :    11;
		};
		uint32_t val;
	} int_clr;
	uint32_t store[4];
	union {
		struct {
			uint32_t xtal32k_wdt_en                :    1;  /*xtal 32k watch dog enable*/
			uint32_t xtal32k_wdt_clk_fo            :    1;  /*xtal 32k watch dog clock force on*/
			uint32_t xtal32k_wdt_reset             :    1;  /*xtal 32k watch dog sw reset*/
			uint32_t xtal32k_ext_clk_fo            :    1;  /*xtal 32k external xtal clock force on*/
			uint32_t xtal32k_auto_backup           :    1;  /*xtal 32k switch to back up clock when xtal is dead*/
			uint32_t xtal32k_auto_restart          :    1;  /*xtal 32k restart xtal when xtal is dead*/
			uint32_t xtal32k_auto_return           :    1;  /*xtal 32k switch back xtal when xtal is restarted*/
			uint32_t xtal32k_xpd_force             :    1;  /*Xtal 32k xpd control by sw or fsm*/
			uint32_t enckinit_xtal_32k             :    1;  /*apply an internal clock to help xtal 32k to start*/
			uint32_t dbuf_xtal_32k                 :    1;  /*0: single-end buffer 1: differential buffer*/
			uint32_t dgm_xtal_32k                  :    3;  /*xtal_32k gm control*/
			uint32_t dres_xtal_32k                 :    3;  /*DRES_XTAL_32K*/
			uint32_t xpd_xtal_32k                  :    1;  /*XPD_XTAL_32K*/
			uint32_t dac_xtal_32k                  :    3;  /*DAC_XTAL_32K*/
			uint32_t rtc_wdt_state                 :    3;  /*state of 32k_wdt*/
			uint32_t rtc_xtal32k_gpio_sel          :    1;  /*XTAL_32K sel. 0: external XTAL_32K*/
			uint32_t reserved24                    :    6;
			uint32_t ctr_lv                        :    1;  /*0: power down XTAL at high level*/
			uint32_t ctr_en                        :    1;
		};
		uint32_t val;
	} ext_xtl_conf;
	union {
		struct {
			uint32_t reserved0                     :    29;
			uint32_t gpio_wakeup_filter            :    1;  /*enable filter for gpio wakeup event*/
			uint32_t ext_wakeup0_lv                :    1;  /*0: external wakeup at low level*/
			uint32_t ext_wakeup1_lv                :    1;
		};
		uint32_t val;
	} ext_wakeup_conf;
	union {
		struct {
			uint32_t reserved0                     :    12;
			uint32_t rtc_sleep_reject_ena          :    18;  /*sleep reject enable*/
			uint32_t light_slp_reject_en           :    1;  /*enable reject for light sleep*/
			uint32_t deep_slp_reject_en            :    1;  /*enable reject for deep sleep*/
		};
		uint32_t val;
	} slp_reject_conf;
	union {
		struct {
			uint32_t reserved0                     :    29;
			uint32_t cpusel_conf                   :    1;  /*CPU sel option*/
			uint32_t cpuperiod_sel                 :    2;
		};
		uint32_t val;
	} cpu_period_conf;
	union {
		struct {
			uint32_t reserved0                     :    22;
			uint32_t sdio_act_dnum                 :    10;
		};
		uint32_t val;
	} sdio_act_conf;
	union {
		struct {
			uint32_t reserved0                     :    1;
			uint32_t efuse_clk_force_gating        :    1;
			uint32_t efuse_clk_force_nogating      :    1;
			uint32_t ck8m_div_sel_vld              :    1;  /*used to sync reg_ck8m_div_sel bus. Clear vld before set reg_ck8m_div_sel*/
			uint32_t ck8m_div                      :    2;  /*CK8M_D256_OUT divider. 00: div128*/
			uint32_t enb_ck8m                      :    1;  /*disable CK8M and CK8M_D256_OUT*/
			uint32_t enb_ck8m_div                  :    1;  /*1: CK8M_D256_OUT is actually CK8M*/
			uint32_t dig_xtal32k_en                :    1;  /*enable CK_XTAL_32K for digital core (no relationship with RTC core)*/
			uint32_t dig_clk8m_d256_en             :    1;  /*enable CK8M_D256_OUT for digital core (no relationship with RTC core)*/
			uint32_t dig_clk8m_en                  :    1;  /*enable CK8M for digital core (no relationship with RTC core)*/
			uint32_t reserved11                    :    1;
			uint32_t ck8m_div_sel                  :    3;  /*divider = reg_ck8m_div_sel + 1*/
			uint32_t xtal_force_nogating           :    1;  /*XTAL force no gating during sleep*/
			uint32_t ck8m_force_nogating           :    1;  /*CK8M force no gating during sleep*/
			uint32_t ck8m_dfreq                    :    8;  /*CK8M_DFREQ*/
			uint32_t ck8m_force_pd                 :    1;  /*CK8M force power down*/
			uint32_t ck8m_force_pu                 :    1;  /*CK8M force power up*/
			uint32_t xtal_global_force_gating      :    1;
			uint32_t xtal_global_force_nogating    :    1;
			uint32_t fast_clk_rtc_sel              :    1;  /*fast_clk_rtc sel. 0: XTAL div 4*/
			uint32_t ana_clk_rtc_sel               :    2;
		};
		uint32_t val;
	} clk_conf;
	union {
		struct {
			uint32_t reserved0                     :    22;
			uint32_t rtc_ana_clk_div_vld           :    1;  /*used to sync div bus. clear vld before set reg_rtc_ana_clk_div*/
			uint32_t rtc_ana_clk_div               :    8;
			uint32_t slow_clk_next_edge            :    1;
		};
		uint32_t val;
	} slow_clk_conf;
	union {
		struct {
			uint32_t sdio_timer_target             :    8;  /*timer count to apply reg_sdio_dcap after sdio power on*/
			uint32_t reserved8                     :    1;
			uint32_t sdio_dthdrv                   :    2;  /*Tieh = 1 mode drive ability. Initially set to 0 to limit charge current*/
			uint32_t sdio_dcap                     :    2;  /*ability to prevent LDO from overshoot*/
			uint32_t sdio_initi                    :    2;  /*add resistor from ldo output to ground. 0: no res*/
			uint32_t sdio_en_initi                 :    1;  /*0 to set init[1:0]=0*/
			uint32_t sdio_dcurlim                  :    3;  /*tune current limit threshold when tieh = 0. About 800mA/(8+d)*/
			uint32_t sdio_modecurlim               :    1;  /*select current limit mode*/
			uint32_t sdio_encurlim                 :    1;  /*enable current limit*/
			uint32_t sdio_pd_en                    :    1;  /*power down SDIO_REG in sleep. Only active when reg_sdio_force = 0*/
			uint32_t sdio_force                    :    1;  /*1: use SW option to control SDIO_REG*/
			uint32_t sdio_tieh                     :    1;  /*SW option for SDIO_TIEH. Only active when reg_sdio_force = 1*/
			uint32_t reg1p8_ready                  :    1;  /*read only register for REG1P8_READY*/
			uint32_t drefl_sdio                    :    2;  /*SW option for DREFL_SDIO. Only active when reg_sdio_force = 1*/
			uint32_t drefm_sdio                    :    2;  /*SW option for DREFM_SDIO. Only active when reg_sdio_force = 1*/
			uint32_t drefh_sdio                    :    2;  /*SW option for DREFH_SDIO. Only active when reg_sdio_force = 1*/
			uint32_t xpd_sdio                      :    1;
		};
		uint32_t val;
	} sdio_conf;
	union {
		struct {
			uint32_t reserved0                     :    10;
			uint32_t bias_buf_idle                 :    1;
			uint32_t bias_buf_wake                 :    1;
			uint32_t bias_buf_deep_slp             :    1;
			uint32_t bias_buf_monitor              :    1;
			uint32_t pd_cur_deep_slp               :    1;  /*xpd cur when rtc in sleep_state*/
			uint32_t pd_cur_monitor                :    1;  /*xpd cur when rtc in monitor state*/
			uint32_t bias_sleep_deep_slp           :    1;  /*bias_sleep when rtc in sleep_state*/
			uint32_t bias_sleep_monitor            :    1;  /*bias_sleep when rtc in monitor state*/
			uint32_t dbg_atten_deep_slp            :    4;  /*DBG_ATTEN when rtc in sleep state*/
			uint32_t dbg_atten_monitor             :    4;  /*DBG_ATTEN when rtc in monitor state*/
			uint32_t dbg_atten_wakeup              :    4;
			uint32_t reserved30                    :    2;
		};
		uint32_t val;
	} bias_conf;
	union {
		struct {
			uint32_t reserved0                     :    7;
			uint32_t dig_cal_en                    :    1;
			uint32_t reserved8                     :    6;
			uint32_t sck_dcap                      :    8;  /*SCK_DCAP*/
			uint32_t reserved22                    :    6;
			uint32_t rtc_dboost_force_pd           :    1;  /*RTC_DBOOST force power down*/
			uint32_t rtc_dboost_force_pu           :    1;  /*RTC_DBOOST force power up*/
			uint32_t rtculator_force_pd            :    1;  /*RTC_REG force power down (for RTC_REG power down means decrease the voltage to 0.8v or lower )*/
			uint32_t rtculator_force_pu            :    1;
		};
		uint32_t val;
	} rtc;
	union {
		struct {
			uint32_t rtc_fastmem_force_noiso       :    1;  /*Fast RTC memory force no ISO*/
			uint32_t rtc_fastmem_force_iso         :    1;  /*Fast RTC memory force ISO*/
			uint32_t rtc_slowmem_force_noiso       :    1;  /*RTC memory force no ISO*/
			uint32_t rtc_slowmem_force_iso         :    1;  /*RTC memory force ISO*/
			uint32_t rtc_force_iso                 :    1;  /*rtc_peri force ISO*/
			uint32_t rtc_force_noiso               :    1;  /*rtc_peri force no ISO*/
			uint32_t rtc_fastmem_folw_cpu          :    1;  /*1: Fast RTC memory PD following CPU*/
			uint32_t fastmem_force_lpd             :    1;  /*Fast RTC memory force PD*/
			uint32_t fastmem_force_lpu             :    1;  /*Fast RTC memory force no PD*/
			uint32_t rtc_slowmem_folw_cpu          :    1;  /*1: RTC memory  PD following CPU*/
			uint32_t rtc_slowmem_force_lpd         :    1;  /*RTC memory force PD*/
			uint32_t rtc_slowmem_force_lpu         :    1;  /*RTC memory force no PD*/
			uint32_t reserved12                    :    6;  /*enable power down RTC memory in sleep*/
			uint32_t rtc_force_pd                  :    1;  /*rtc_peri force power down*/
			uint32_t rtc_force_pu                  :    1;  /*rtc_peri force power up*/
			uint32_t rtc_pd_en                     :    1;  /*enable power down rtc_peri in sleep */
			uint32_t rtc_pad_force_hold            :    1;  /*rtc pad force hold*/
			uint32_t reserved22                    :    10;
		};
		uint32_t val;
	} pwc;
	union {
		struct {
			uint32_t rtculator_drv_b_monitor       :    6;
			uint32_t rtculator_drv_b_slp           :    6;
			uint32_t dg_vdd_drv_b_slp              :    8;
			uint32_t dg_vdd_drv_b_monitor          :    8;
			uint32_t reserved28                    :    4;
		};
		uint32_t val;
	} regulator_drv_ctrl;
	union {
		struct {
			uint32_t reserved0                     :    3;
			uint32_t lslp_mem_force_pd             :    1;  /*memories in digital core force PD in sleep*/
			uint32_t lslp_mem_force_pu             :    1;  /*memories in digital core force no PD in sleep*/
			uint32_t reserved5                     :    6;  /*internal SRAM 1 force power up*/
			uint32_t bt_force_pd                   :    1;  /*internal SRAM 2 force power down*/
			uint32_t bt_force_pu                   :    1;  /*internal SRAM 2 force power up*/
			uint32_t dg_peri_force_pd              :    1;  /*internal SRAM 3 force power down*/
			uint32_t dg_peri_force_pu              :    1;  /*internal SRAM 3 force power up*/
			uint32_t reserved15                    :    2;  /*internal SRAM 4 force power up*/
			uint32_t wifi_force_pd                 :    1;  /*wifi force power down*/
			uint32_t wifi_force_pu                 :    1;  /*wifi force power up*/
			uint32_t dg_wrap_force_pd              :    1;  /*digital core force power down*/
			uint32_t dg_wrap_force_pu              :    1;  /*digital core force power up*/
			uint32_t cpu_top_force_pd              :    1;  /*digital dcdc force power down*/
			uint32_t cpu_top_force_pu              :    1;  /*digital dcdc force power up*/
			uint32_t reserved23                    :    4;  /*enable power down internal SRAM 1 in sleep*/
			uint32_t bt_pd_en                      :    1;  /*enable power down internal SRAM 2 in sleep*/
			uint32_t dg_peri_pd_en                 :    1;  /*enable power down internal SRAM 3 in sleep*/
			uint32_t cpu_top_pd_en                 :    1;  /*enable power down internal SRAM 4 in sleep*/
			uint32_t wifi_pd_en                    :    1;  /*enable power down wifi in sleep*/
			uint32_t dg_wrap_pd_en                 :    1;
		};
		uint32_t val;
	} dig_pwc;
	union {
		struct {
			uint32_t reserved0                     :    7;
			uint32_t dig_iso_force_off             :    1;
			uint32_t dig_iso_force_on              :    1;
			uint32_t dg_pad_autohold               :    1;  /*read only register to indicate digital pad auto-hold status*/
			uint32_t clr_dg_pad_autohold           :    1;  /*wtite only register to clear digital pad auto-hold*/
			uint32_t dg_pad_autohold_en            :    1;  /*digital pad enable auto-hold*/
			uint32_t dg_pad_force_noiso            :    1;  /*digital pad force no ISO*/
			uint32_t dg_pad_force_iso              :    1;  /*digital pad force ISO*/
			uint32_t dg_pad_force_unhold           :    1;  /*digital pad force un-hold*/
			uint32_t dg_pad_force_hold             :    1;  /*digital pad force hold*/
			uint32_t reserved16                    :    6;  /*internal SRAM 1 force no ISO*/
			uint32_t bt_force_iso                  :    1;  /*internal SRAM 2 force ISO*/
			uint32_t bt_force_noiso                :    1;  /*internal SRAM 2 force no ISO*/
			uint32_t dg_peri_force_iso             :    1;  /*internal SRAM 3 force ISO*/
			uint32_t dg_peri_force_noiso           :    1;  /*internal SRAM 3 force no ISO*/
			uint32_t cpu_top_force_iso             :    1;  /*internal SRAM 4 force ISO*/
			uint32_t cpu_top_force_noiso           :    1;  /*internal SRAM 4 force no ISO*/
			uint32_t wifi_force_iso                :    1;  /*wifi force ISO*/
			uint32_t wifi_force_noiso              :    1;  /*wifi force no ISO*/
			uint32_t dg_wrap_force_iso             :    1;  /*digital core force ISO*/
			uint32_t dg_wrap_force_noiso           :    1;
		};
		uint32_t val;
	} dig_iso;
	union {
		struct {
			uint32_t chip_reset_width              :    8;  /*chip reset siginal pulse width*/
			uint32_t chip_reset_en                 :    1;  /*wdt reset whole chip enable*/
			uint32_t pause_in_slp                  :    1;  /*pause WDT in sleep*/
			uint32_t appcpu_reset_en               :    1;  /*enable WDT reset APP CPU*/
			uint32_t procpu_reset_en               :    1;  /*enable WDT reset PRO CPU*/
			uint32_t flashboot_mod_en              :    1;  /*enable WDT in flash boot*/
			uint32_t sys_reset_length              :    3;  /*system reset counter length*/
			uint32_t cpu_reset_length              :    3;  /*CPU reset counter length*/
			uint32_t stg3                          :    3;  /*1: interrupt stage en*/
			uint32_t stg2                          :    3;  /*1: interrupt stage en*/
			uint32_t stg1                          :    3;  /*1: interrupt stage en*/
			uint32_t stg0                          :    3;  /*1: interrupt stage en*/
			uint32_t en                            :    1;
		};
		uint32_t val;
	} wdt_config0;
	uint32_t wdt_config1;
	uint32_t wdt_config2;
	uint32_t wdt_config3;
	uint32_t wdt_config4;
	union {
		struct {
			uint32_t reserved0                     :    31;
			uint32_t feed                          :    1;
		};
		uint32_t val;
	} wdt_feed;
	uint32_t wdt_wprotect;
	union {
		struct {
			uint32_t swd_reset_flag                :    1;  /*swd reset flag*/
			uint32_t swd_feed_int                  :    1;  /*swd interrupt for feeding*/
			uint32_t reserved2                     :    15;
			uint32_t swd_bypass_rst                :    1;
			uint32_t swd_signal_width              :    10;  /*adjust signal width send to swd*/
			uint32_t swd_rst_flag_clr              :    1;  /*reset swd reset flag*/
			uint32_t swd_feed                      :    1;  /*Sw feed swd*/
			uint32_t swd_disable                   :    1;  /*disabel SWD*/
			uint32_t swd_auto_feed_en              :    1;  /*automatically feed swd when int comes*/
		};
		uint32_t val;
	} swd_conf;
	uint32_t swd_wprotect;
	union {
		struct {
			uint32_t reserved0                     :    20;
			uint32_t appcpu_c1                     :    6;  /*{reg_sw_stall_appcpu_c1[5:0]*/
			uint32_t procpu_c1                     :    6;
		};
		uint32_t val;
	} sw_cpu_stall;
	uint32_t store4;
	uint32_t store5;
	uint32_t store6;
	uint32_t store7;
	union {
		struct {
			uint32_t xpd_rom0                      :    1;  /*rom0 power down*/
			uint32_t reserved1                     :    1;
			uint32_t xpd_dig_dcdc                  :    1;  /*External DCDC power down*/
			uint32_t rtc_peri_iso                  :    1;  /*rtc peripheral iso*/
			uint32_t xpd_rtc_peri                  :    1;  /*rtc peripheral power down */
			uint32_t wifi_iso                      :    1;  /*wifi iso*/
			uint32_t xpd_wifi                      :    1;  /*wifi wrap power down*/
			uint32_t dig_iso                       :    1;  /*digital wrap iso*/
			uint32_t xpd_dig                       :    1;  /*digital wrap power down*/
			uint32_t rtc_touch_state_start         :    1;  /*touch should start to work*/
			uint32_t rtc_touch_state_switch        :    1;  /*touch is about to working. Switch rtc main state*/
			uint32_t rtc_touch_state_slp           :    1;  /*touch is in sleep state*/
			uint32_t rtc_touch_state_done          :    1;  /*touch is done*/
			uint32_t rtc_cocpu_state_start         :    1;  /*ulp/cocpu should start to work*/
			uint32_t rtc_cocpu_state_switch        :    1;  /*ulp/cocpu is about to working. Switch rtc main state*/
			uint32_t rtc_cocpu_state_slp           :    1;  /*ulp/cocpu is in sleep state*/
			uint32_t rtc_cocpu_state_done          :    1;  /*ulp/cocpu is done*/
			uint32_t rtc_main_state_xtal_iso       :    1;  /*no use any more*/
			uint32_t rtc_main_state_pll_on         :    1;  /*rtc main state machine is in states that pll should be running*/
			uint32_t rtc_rdy_for_wakeup            :    1;  /*rtc is ready to receive wake up trigger from wake up source*/
			uint32_t rtc_main_state_wait_end       :    1;  /*rtc main state machine has been waited for some cycles*/
			uint32_t rtc_in_wakeup_state           :    1;  /*rtc main state machine is in the states of wakeup process*/
			uint32_t rtc_in_low_power_state        :    1;  /*rtc main state machine is in the states of low power*/
			uint32_t rtc_main_state_in_wait_8m     :    1;  /*rtc main state machine is in wait 8m state*/
			uint32_t rtc_main_state_in_wait_pll    :    1;  /*rtc main state machine is in wait pll state*/
			uint32_t rtc_main_state_in_wait_xtl    :    1;  /*rtc main state machine is in wait xtal state*/
			uint32_t rtc_main_state_in_slp         :    1;  /*rtc main state machine is in sleep state*/
			uint32_t rtc_main_state_in_idle        :    1;  /*rtc main state machine is in idle state*/
			uint32_t rtc_main_state                :    4;  /*rtc main state machine status*/
		};
		uint32_t val;
	} low_power_st;
	uint32_t diag0;
	union {
		struct {
			uint32_t touch_pad0_hold               :    1;
			uint32_t touch_pad1_hold               :    1;
			uint32_t touch_pad2_hold               :    1;
			uint32_t touch_pad3_hold               :    1;
			uint32_t touch_pad4_hold               :    1;
			uint32_t touch_pad5_hold               :    1;
			uint32_t touch_pad6_hold               :    1;
			uint32_t touch_pad7_hold               :    1;
			uint32_t touch_pad8_hold               :    1;
			uint32_t touch_pad9_hold               :    1;
			uint32_t touch_pad10_hold              :    1;
			uint32_t touch_pad11_hold              :    1;
			uint32_t touch_pad12_hold              :    1;
			uint32_t touch_pad13_hold              :    1;
			uint32_t touch_pad14_hold              :    1;
			uint32_t x32p_hold                     :    1;
			uint32_t x32n_hold                     :    1;
			uint32_t pdac1_hold                    :    1;
			uint32_t pdac2_hold                    :    1;
			uint32_t rtc_pad19_hold                :    1;
			uint32_t rtc_pad20_hold                :    1;
			uint32_t rtc_pad21_hold                :    1;
			uint32_t reserved22                    :    10;
		};
		uint32_t val;
	} pad_hold;
	uint32_t dig_pad_hold;
	union {
		struct {
			uint32_t ext_wakeup1_sel               :    22;  /*Bitmap to select RTC pads for ext wakeup1*/
			uint32_t ext_wakeup1_status_clr        :    1;  /*clear ext wakeup1 status*/
			uint32_t reserved23                    :    9;
		};
		uint32_t val;
	} ext_wakeup1;
	union {
		struct {
			uint32_t ext_wakeup1_status            :    22;  /*ext wakeup1 status*/
			uint32_t reserved22                    :    10;
		};
		uint32_t val;
	} ext_wakeup1_status;
	union {
		struct {
			uint32_t reserved0                     :    4;
			uint32_t int_wait                      :    10;  /*brown out interrupt wait cycles*/
			uint32_t close_flash_ena               :    1;  /*enable close flash when brown out happens*/
			uint32_t pd_rf_ena                     :    1;  /*enable power down RF when brown out happens*/
			uint32_t rst_wait                      :    10;  /*brown out reset wait cycles*/
			uint32_t rst_ena                       :    1;  /*enable brown out reset*/
			uint32_t rst_sel                       :    1;  /*1:  4-pos reset*/
			uint32_t ana_rst_en                    :    1;
			uint32_t cnt_clr                       :    1;  /*clear brown out counter*/
			uint32_t ena                           :    1;  /*enable brown out*/
			uint32_t det                           :    1;
		};
		uint32_t val;
	} brown_out;
	uint32_t time_low1;
	union {
		struct {
			uint32_t rtc_timer_value1_high         :    16;  /*RTC timer high 16 bits*/
			uint32_t reserved16                    :    16;
		};
		uint32_t val;
	} time_high1;
	uint32_t xtal32k_clk_factor;
	union {
		struct {
			uint32_t xtal32k_return_wait           :    4;  /*cycles to wait to return noral xtal 32k*/
			uint32_t xtal32k_restart_wait          :    16;  /*cycles to wait to repower on xtal 32k*/
			uint32_t xtal32k_wdt_timeout           :    8;  /*If no clock detected for this amount of time*/
			uint32_t xtal32k_stable_thres          :    4;  /*if restarted xtal32k period is smaller than this*/
		};
		uint32_t val;
	} xtal32k_conf;
	union {
		struct {
			uint32_t ulp_cp_pc_init                :    11;  /*ULP-coprocessor PC initial address*/
			uint32_t reserved11                    :    18;
			uint32_t ulp_cp_gpio_wakeup_ena        :    1;  /*ULP-coprocessor wakeup by GPIO enable*/
			uint32_t ulp_cp_gpio_wakeup_clr        :    1;  /*ULP-coprocessor wakeup by GPIO state clear*/
			uint32_t ulp_cp_slp_timer_en           :    1;  /*ULP-coprocessor timer enable bit*/
		};
		uint32_t val;
	} ulp_cp_timer;
	union {
		struct {
			uint32_t ulp_cp_mem_addr_init          :    11;
			uint32_t ulp_cp_mem_addr_size          :    11;
			uint32_t ulp_cp_mem_offst_clr          :    1;
			uint32_t reserved23                    :    5;
			uint32_t ulp_cp_clk_fo                 :    1;  /*ulp coprocessor clk force on*/
			uint32_t ulp_cp_reset                  :    1;  /*ulp coprocessor clk software reset*/
			uint32_t ulp_cp_force_start_top        :    1;  /*1: ULP-coprocessor is started by SW*/
			uint32_t ulp_cp_start_top              :    1;  /*Write 1 to start ULP-coprocessor*/
		};
		uint32_t val;
	} ulp_cp_ctrl;
	union {
		struct {
			uint32_t cocpu_clk_fo                  :    1;  /*cocpu clk force on*/
			uint32_t cocpu_start_2_reset_dis       :    6;  /*time from start cocpu to pull down reset*/
			uint32_t cocpu_start_2_intr_en         :    6;  /*time from start cocpu to give start interrupt*/
			uint32_t cocpu_shut                    :    1;  /*to shut cocpu*/
			uint32_t cocpu_shut_2_clk_dis          :    8;  /*time from shut cocpu to disable clk*/
			uint32_t cocpu_shut_reset_en           :    1;  /*to reset cocpu*/
			uint32_t cocpu_sel                     :    1;  /*1: old ULP 0: new riscV*/
			uint32_t cocpu_done_force              :    1;  /*1: select riscv done 0: select ulp done*/
			uint32_t cocpu_done                    :    1;  /*done signal used by riscv to control timer. */
			uint32_t cocpu_sw_int_trigger          :    1;  /*trigger cocpu register interrupt*/
			uint32_t cocpu_clkgate_en              :    1;
			uint32_t reserved28                    :    4;
		};
		uint32_t val;
	} cocpu_ctrl;
	union {
		struct {
			uint32_t touch_sleep_cycles            :    16;  /*sleep cycles for timer*/
			uint32_t touch_meas_num                :    16;  /*the meas length (in 8MHz)*/
		};
		uint32_t val;
	} touch_ctrl1;
	union {
		struct {
			uint32_t reserved0                     :    2;
			uint32_t touch_drange                  :    2;  /*TOUCH_DRANGE*/
			uint32_t touch_drefl                   :    2;  /*TOUCH_DREFL*/
			uint32_t touch_drefh                   :    2;  /*TOUCH_DREFH*/
			uint32_t touch_xpd_bias                :    1;  /*TOUCH_XPD_BIAS*/
			uint32_t touch_refc                    :    3;  /*TOUCH pad0 reference cap*/
			uint32_t touch_dbias                   :    1;  /*1:use self bias 0:use bandgap bias*/
			uint32_t touch_slp_timer_en            :    1;  /*touch timer enable bit*/
			uint32_t touch_start_fsm_en            :    1;  /*1: TOUCH_START & TOUCH_XPD is controlled by touch fsm*/
			uint32_t touch_start_en                :    1;  /*1: start touch fsm*/
			uint32_t touch_start_force             :    1;  /*1: to start touch fsm by SW*/
			uint32_t touch_xpd_wait                :    8;  /*the waiting cycles (in 8MHz) between TOUCH_START and TOUCH_XPD*/
			uint32_t touch_slp_cyc_div             :    2;  /*when a touch pad is active*/
			uint32_t touch_timer_force_done        :    2;  /*force touch timer done*/
			uint32_t touch_reset                   :    1;  /*reset upgrade touch*/
			uint32_t touch_clk_fo                  :    1;  /*touch clock force on*/
			uint32_t touch_clkgate_en              :    1;  /*touch clock enable*/
		};
		uint32_t val;
	} touch_ctrl2;
	union {
		struct {
			uint32_t touch_denoise_res             :    2;  /*De-noise resolution: 12/10/8/4 bit*/
			uint32_t touch_denoise_en              :    1;  /*touch pad0 will be used to de-noise*/
			uint32_t reserved3                     :    5;
			uint32_t touch_inactive_connection     :    1;  /*inactive touch pads connect to 1: gnd 0: HighZ*/
			uint32_t touch_shield_pad_en           :    1;  /*touch pad14 will be used as shield*/
			uint32_t touch_scan_pad_map            :    15;  /*touch scan mode pad enable map*/
			uint32_t touch_bufdrv                  :    3;  /*touch7 buffer driver strength*/
			uint32_t touch_out_ring                :    4;  /*select out ring pad*/
		};
		uint32_t val;
	} touch_scan_ctrl;
	union {
		struct {
			uint32_t touch_slp_th                  :    22;  /*the threshold for sleep touch pad*/
			uint32_t reserved22                    :    4;
			uint32_t touch_slp_approach_en         :    1;  /*sleep pad approach function enable*/
			uint32_t touch_slp_pad                 :    5;  /* */
		};
		uint32_t val;
	} touch_slp_thres;
	union {
		struct {
			uint32_t reserved0                     :    23;
			uint32_t touch_slp_channel_clr         :    1;  /*clear touch slp channel*/
			uint32_t touch_approach_meas_time      :    8;  /*approach pads total meas times*/
		};
		uint32_t val;
	} touch_approach;
	union {
		struct {
			uint32_t reserved0                     :    7;
			uint32_t touch_bypass_neg_noise_thres  :    1;
			uint32_t touch_bypass_noise_thres      :    1;
			uint32_t touch_smooth_lvl              :    2;
			uint32_t touch_jitter_step             :    4;  /*touch jitter step*/
			uint32_t config1:               4;
			uint32_t config2:               2;
			uint32_t touch_noise_thres             :    2;
			uint32_t config3:               2;
			uint32_t touch_debounce                :    3;  /*debounce counter*/
			uint32_t touch_filter_mode             :    3;  /*0: IIR ? 1: IIR ? 2: IIR 1/8 3: Jitter*/
			uint32_t touch_filter_en               :    1;  /*touch filter enable*/
		};
		uint32_t val;
	} touch_filter_ctrl;
	union {
		struct {
			uint32_t usb_vrefh                     :    2;
			uint32_t usb_vrefl                     :    2;
			uint32_t usb_vref_override             :    1;
			uint32_t usb_pad_pull_override         :    1;
			uint32_t usb_dp_pullup                 :    1;
			uint32_t usb_dp_pulldown               :    1;
			uint32_t usb_dm_pullup                 :    1;
			uint32_t usb_dm_pulldown               :    1;
			uint32_t usb_pullup_value              :    1;
			uint32_t usb_pad_enable_override       :    1;
			uint32_t usb_pad_enable                :    1;
			uint32_t usb_txm                       :    1;
			uint32_t usb_txp                       :    1;
			uint32_t usb_tx_en                     :    1;
			uint32_t usb_tx_en_override            :    1;
			uint32_t usb_reset_disable             :    1;
			uint32_t io_mux_reset_disable          :    1;
			uint32_t sw_usb_phy_sel                :    1;
			uint32_t sw_hw_usb_phy_sel             :    1;
			uint32_t reserved21                    :    11;
		};
		uint32_t val;
	} usb_conf;
	union {
		struct {
			uint32_t touch_timeout_num             :    22;
			uint32_t touch_timeout_en              :    1;
			uint32_t reserved23                    :    9;
		};
		uint32_t val;
	} touch_timeout_ctrl;
	union {
		struct {
			uint32_t reject_cause                  :    18;  /*sleep reject cause*/
			uint32_t reserved18                    :    14;
		};
		uint32_t val;
	} slp_reject_cause;
	union {
		struct {
			uint32_t force_download_boot           :    1;
			uint32_t reserved1                     :    31;
		};
		uint32_t val;
	} option1;
	union {
		struct {
			uint32_t wakeup_cause                  :    17;  /*sleep wakeup cause*/
			uint32_t reserved17                    :    15;
		};
		uint32_t val;
	} slp_wakeup_cause;
	union {
		struct {
			uint32_t reserved0                     :    8;
			uint32_t ulp_cp_timer_slp_cycle        :    24;  /*sleep cycles for ULP-coprocessor timer*/
		};
		uint32_t val;
	} ulp_cp_timer_1;
	union {
		struct {
			uint32_t slp_wakeup_w1ts               :    1;  /*enable sleep wakeup interrupt*/
			uint32_t slp_reject_w1ts               :    1;  /*enable sleep reject interrupt*/
			uint32_t sdio_idle_w1ts                :    1;  /*enable SDIO idle interrupt*/
			uint32_t rtc_wdt_w1ts                  :    1;  /*enable RTC WDT interrupt*/
			uint32_t rtc_touch_scan_done_w1ts      :    1;  /*enable touch scan done interrupt*/
			uint32_t rtc_ulp_cp_w1ts               :    1;  /*enable ULP-coprocessor interrupt*/
			uint32_t rtc_touch_done_w1ts           :    1;  /*enable touch done interrupt*/
			uint32_t rtc_touch_active_w1ts         :    1;  /*enable touch active interrupt*/
			uint32_t rtc_touch_inactive_w1ts       :    1;  /*enable touch inactive interrupt*/
			uint32_t w1ts                          :    1;  /*enable brown out interrupt*/
			uint32_t rtc_main_timer_w1ts           :    1;  /*enable RTC main timer interrupt*/
			uint32_t rtc_saradc1_w1ts              :    1;  /*enable saradc1 interrupt*/
			uint32_t rtc_tsens_w1ts                :    1;  /*enable tsens interrupt*/
			uint32_t rtc_cocpu_w1ts                :    1;  /*enable riscV cocpu interrupt*/
			uint32_t rtc_saradc2_w1ts              :    1;  /*enable saradc2 interrupt*/
			uint32_t rtc_swd_w1ts                  :    1;  /*enable super watch dog interrupt*/
			uint32_t rtc_xtal32k_dead_w1ts         :    1;  /*enable xtal32k_dead  interrupt*/
			uint32_t rtc_cocpu_trap_w1ts           :    1;  /*enable cocpu trap interrupt*/
			uint32_t rtc_touch_timeout_w1ts        :    1;  /*enable touch timeout interrupt*/
			uint32_t rtc_glitch_det_w1ts           :    1;  /*enbale gitch det interrupt*/
			uint32_t rtc_touch_approach_loop_done_w1ts:    1;
			uint32_t reserved21                    :    11;
		};
		uint32_t val;
	} int_ena_w1ts;
	union {
		struct {
			uint32_t slp_wakeup_w1tc               :    1;  /*enable sleep wakeup interrupt*/
			uint32_t slp_reject_w1tc               :    1;  /*enable sleep reject interrupt*/
			uint32_t sdio_idle_w1tc                :    1;  /*enable SDIO idle interrupt*/
			uint32_t rtc_wdt_w1tc                  :    1;  /*enable RTC WDT interrupt*/
			uint32_t rtc_touch_scan_done_w1tc      :    1;  /*enable touch scan done interrupt*/
			uint32_t rtc_ulp_cp_w1tc               :    1;  /*enable ULP-coprocessor interrupt*/
			uint32_t rtc_touch_done_w1tc           :    1;  /*enable touch done interrupt*/
			uint32_t rtc_touch_active_w1tc         :    1;  /*enable touch active interrupt*/
			uint32_t rtc_touch_inactive_w1tc       :    1;  /*enable touch inactive interrupt*/
			uint32_t w1tc                          :    1;  /*enable brown out interrupt*/
			uint32_t rtc_main_timer_w1tc           :    1;  /*enable RTC main timer interrupt*/
			uint32_t rtc_saradc1_w1tc              :    1;  /*enable saradc1 interrupt*/
			uint32_t rtc_tsens_w1tc                :    1;  /*enable tsens interrupt*/
			uint32_t rtc_cocpu_w1tc                :    1;  /*enable riscV cocpu interrupt*/
			uint32_t rtc_saradc2_w1tc              :    1;  /*enable saradc2 interrupt*/
			uint32_t rtc_swd_w1tc                  :    1;  /*enable super watch dog interrupt*/
			uint32_t rtc_xtal32k_dead_w1tc         :    1;  /*enable xtal32k_dead  interrupt*/
			uint32_t rtc_cocpu_trap_w1tc           :    1;  /*enable cocpu trap interrupt*/
			uint32_t rtc_touch_timeout_w1tc        :    1;  /*enable touch timeout interrupt*/
			uint32_t rtc_glitch_det_w1tc           :    1;  /*enbale gitch det interrupt*/
			uint32_t rtc_touch_approach_loop_done_w1tc:    1;
			uint32_t reserved21                    :    11;
		};
		uint32_t val;
	} int_ena_w1tc;
	union {
		struct {
			uint32_t reserved0                     :    10;
			uint32_t retention_tag_mode            :    4;
			uint32_t retention_target              :    2;
			uint32_t retention_clk_sel             :    1;
			uint32_t retention_done_wait           :    3;
			uint32_t retention_clkoff_wait         :    4;
			uint32_t retention_en                  :    1;
			uint32_t retention_wait                :    7;  /*wait cycles for rention operation*/
		};
		uint32_t val;
	} retention_ctrl;
	union {
		struct {
			uint32_t reserved0                     :    26;
			uint32_t power_glitch_dsense           :    2;
			uint32_t power_glitch_force_pd         :    1;
			uint32_t power_glitch_force_pu         :    1;
			uint32_t power_glitch_efuse_sel        :    1;  /*select use analog fib signal*/
			uint32_t power_glitch_en               :    1;
		};
		uint32_t val;
	} pg_ctrl;
	union {
		struct {
			uint32_t rtc_fib_sel                   :    3;
			uint32_t reserved3                     :    29;
		};
		uint32_t val;
	} fib_sel;
	union {
		struct {
			uint32_t reserved0                     :    2;
			uint32_t touch_pad9_dac                :    3;
			uint32_t touch_pad8_dac                :    3;
			uint32_t touch_pad7_dac                :    3;
			uint32_t touch_pad6_dac                :    3;
			uint32_t touch_pad5_dac                :    3;
			uint32_t touch_pad4_dac                :    3;
			uint32_t touch_pad3_dac                :    3;
			uint32_t touch_pad2_dac                :    3;
			uint32_t touch_pad1_dac                :    3;
			uint32_t touch_pad0_dac                :    3;
		};
		uint32_t val;
	} touch_dac;
	union {
		struct {
			uint32_t reserved0                     :    17;
			uint32_t touch_pad14_dac               :    3;
			uint32_t touch_pad13_dac               :    3;
			uint32_t touch_pad12_dac               :    3;
			uint32_t touch_pad11_dac               :    3;
			uint32_t touch_pad10_dac               :    3;
		};
		uint32_t val;
	} touch_dac1;
	union {
		struct {
			uint32_t reserved0                     :    31;
			uint32_t disable_rtc_cpu               :    1;
		};
		uint32_t val;
	} cocpu_disable;
	uint32_t reserved_158;
	uint32_t reserved_15c;
	uint32_t reserved_160;
	uint32_t reserved_164;
	uint32_t reserved_168;
	uint32_t reserved_16c;
	uint32_t reserved_170;
	uint32_t reserved_174;
	uint32_t reserved_178;
	uint32_t reserved_17c;
	uint32_t reserved_180;
	uint32_t reserved_184;
	uint32_t reserved_188;
	uint32_t reserved_18c;
	uint32_t reserved_190;
	uint32_t reserved_194;
	uint32_t reserved_198;
	uint32_t reserved_19c;
	uint32_t reserved_1a0;
	uint32_t reserved_1a4;
	uint32_t reserved_1a8;
	uint32_t reserved_1ac;
	uint32_t reserved_1b0;
	uint32_t reserved_1b4;
	uint32_t reserved_1b8;
	uint32_t reserved_1bc;
	uint32_t reserved_1c0;
	uint32_t reserved_1c4;
	uint32_t reserved_1c8;
	uint32_t reserved_1cc;
	uint32_t reserved_1d0;
	uint32_t reserved_1d4;
	uint32_t reserved_1d8;
	uint32_t reserved_1dc;
	uint32_t reserved_1e0;
	uint32_t reserved_1e4;
	uint32_t reserved_1e8;
	uint32_t reserved_1ec;
	uint32_t reserved_1f0;
	uint32_t reserved_1f4;
	uint32_t reserved_1f8;
	union {
		struct {
			uint32_t date                          :    28;
			uint32_t reserved28                    :    4;
		};
		uint32_t val;
	} date;
} rtc_cntl_dev_t;


extern rtc_cntl_dev_t *RTCCNTL;

void rtc_cntl_ll_set_wakeup_timer(uint64_t t);
uint32_t rtc_cntl_ll_ext1_get_wakeup_pins(void);
void rtc_cntl_ll_ext1_set_wakeup_pins(uint32_t mask, int mode);
void rtc_cntl_ll_ext1_clear_wakeup_pins(void);
void rtc_cntl_ll_set_tagmem_retention_link_addr(uint32_t link_addr);
void rtc_cntl_ll_enable_tagmem_retention(void);
void rtc_cntl_ll_enable_icache_tagmem_retention(uint32_t start_point, uint32_t vld_size, uint32_t size);
void rtc_cntl_ll_enable_dcache_tagmem_retention(uint32_t start_point, uint32_t vld_size, uint32_t size);
void rtc_cntl_ll_disable_tagmem_retention(void);
void rtc_cntl_ll_disable_icache_tagmem_retention(void);
void rtc_cntl_ll_disable_dcache_tagmem_retention(void);
void rtc_cntl_ll_set_cpu_retention_link_addr(uint32_t link_addr);
void rtc_cntl_ll_enable_cpu_retention_clock(void);
void rtc_cntl_ll_enable_cpu_retention(void);
void rtc_cntl_ll_config_cpu_retention_timing(int wait, int clkoff_wait, int done_wait);
void rtc_cntl_ll_disable_cpu_retention(void);
void rtc_cntl_ll_ulp_int_clear(void);
