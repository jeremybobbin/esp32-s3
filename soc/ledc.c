#include "soc/ledc.h"
#include <stdlib.h>

#define LEDC_LL_GET_HW()           &LEDC
#define LEDC_LL_DUTY_NUM_MAX       (LEDC_DUTY_NUM_LSCH0_V)
#define LEDC_LL_DUTY_CYCLE_MAX     (LEDC_DUTY_CYCLE_LSCH0_V)
#define LEDC_LL_DUTY_SCALE_MAX     (LEDC_DUTY_SCALE_LSCH0_V)
#define LEDC_LL_HPOINT_VAL_MAX     (LEDC_HPOINT_LSCH0_V)
#define LEDC_LL_FRACTIONAL_BITS    (8)
#define LEDC_LL_FRACTIONAL_MAX     ((1 << LEDC_LL_FRACTIONAL_BITS) - 1)

#define LEDC_LL_GLOBAL_CLOCKS { \
                                LEDC_SLOW_CLK_APB, \
                                LEDC_SLOW_CLK_XTAL, \
                                LEDC_SLOW_CLK_RC_FAST, \
                              }

#define LEDC_LL_GLOBAL_CLK_DEFAULT LEDC_SLOW_CLK_RC_FAST

void ledc_ll_enable_bus_clock(bool enable)
{
	SYSTEM.perip_clk_en0.ledc_clk_en = enable;
}

/// use a macro to wrap the function, force the caller to use it in a critical section
/// the critical section needs to declare the __DECLARE_RCC_ATOMIC_ENV variable in advance
#define ledc_ll_enable_bus_clock(...) (void)__DECLARE_RCC_ATOMIC_ENV; ledc_ll_enable_bus_clock(__VA_ARGS__)

void ledc_ll_enable_reset_reg(bool enable)
{
	SYSTEM.perip_rst_en0.ledc_rst = enable;
}

/// use a macro to wrap the function, force the caller to use it in a critical section
/// the critical section needs to declare the __DECLARE_RCC_ATOMIC_ENV variable in advance
#define ledc_ll_enable_reset_reg(...) (void)__DECLARE_RCC_ATOMIC_ENV; ledc_ll_enable_reset_reg(__VA_ARGS__)

void ledc_ll_enable_mem_power(bool enable)
{
}

void ledc_ll_enable_clock(ledc_dev_t *hw, bool en)
{
}

void ledc_ll_set_slow_clk_sel(ledc_dev_t *hw, ledc_slow_clk_sel_t slow_clk_sel)
{
	uint32_t clk_sel_val = 0;
	if (slow_clk_sel == LEDC_SLOW_CLK_APB) {
		clk_sel_val = 1;
	} else if (slow_clk_sel == LEDC_SLOW_CLK_RC_FAST) {
		clk_sel_val = 2;
	} else if (slow_clk_sel == LEDC_SLOW_CLK_XTAL) {
		clk_sel_val = 3;
	}
	hw->conf.apb_clk_sel = clk_sel_val;
}

void ledc_ll_get_slow_clk_sel(ledc_dev_t *hw, ledc_slow_clk_sel_t *slow_clk_sel)
{
	uint32_t clk_sel_val = hw->conf.apb_clk_sel;
	if (clk_sel_val == 1) {
		*slow_clk_sel = LEDC_SLOW_CLK_APB;
	} else if (clk_sel_val == 2) {
		*slow_clk_sel = LEDC_SLOW_CLK_RC_FAST;
	} else if (clk_sel_val == 3) {
		*slow_clk_sel = LEDC_SLOW_CLK_XTAL;
	} else {
		abort();
	}
}

void ledc_ll_ls_timer_update(ledc_dev_t *hw, ledc_mode_t speed_mode, ledc_timer_t timer_sel)
{
	hw->timer_group[speed_mode].timer[timer_sel].conf.low_speed_update = 1;
}

void ledc_ll_timer_rst(ledc_dev_t *hw, ledc_mode_t speed_mode, ledc_timer_t timer_sel)
{
	hw->timer_group[speed_mode].timer[timer_sel].conf.rst = 1;
	hw->timer_group[speed_mode].timer[timer_sel].conf.rst = 0;
}

void ledc_ll_timer_pause(ledc_dev_t *hw, ledc_mode_t speed_mode, ledc_timer_t timer_sel)
{
	hw->timer_group[speed_mode].timer[timer_sel].conf.pause = 1;
}

void ledc_ll_timer_resume(ledc_dev_t *hw, ledc_mode_t speed_mode, ledc_timer_t timer_sel)
{
	hw->timer_group[speed_mode].timer[timer_sel].conf.pause = 0;
}

void ledc_ll_set_clock_divider(ledc_dev_t *hw, ledc_mode_t speed_mode, ledc_timer_t timer_sel, uint32_t clock_divider)
{
	hw->timer_group[speed_mode].timer[timer_sel].conf.clock_divider = clock_divider;
}

void ledc_ll_get_clock_divider(ledc_dev_t *hw, ledc_mode_t speed_mode, ledc_timer_t timer_sel, uint32_t *clock_divider)
{
	*clock_divider = hw->timer_group[speed_mode].timer[timer_sel].conf.clock_divider;
}

void ledc_ll_get_clock_source(ledc_dev_t *hw, ledc_mode_t speed_mode, ledc_timer_t timer_sel, ledc_clk_src_t *clk_src)
{
	*clk_src = LEDC_APB_CLK;
}

void ledc_ll_set_duty_resolution(ledc_dev_t *hw, ledc_mode_t speed_mode, ledc_timer_t timer_sel, uint32_t duty_resolution)
{
	hw->timer_group[speed_mode].timer[timer_sel].conf.duty_resolution = duty_resolution;
}

void ledc_ll_get_duty_resolution(ledc_dev_t *hw, ledc_mode_t speed_mode, ledc_timer_t timer_sel, uint32_t *duty_resolution)
{
	*duty_resolution = hw->timer_group[speed_mode].timer[timer_sel].conf.duty_resolution;
}

void ledc_ll_get_max_duty(ledc_dev_t *hw, ledc_mode_t speed_mode, ledc_timer_t timer_sel, uint32_t *max_duty)
{
	*max_duty = (1 << (LEDC.timer_group[speed_mode].timer[timer_sel].conf.duty_resolution));
}

void ledc_ll_ls_channel_update(ledc_dev_t *hw, ledc_mode_t speed_mode, ledc_channel_t channel_num)
{
	hw->channel_group[speed_mode].channel[channel_num].conf0.low_speed_update = 1;
}

void ledc_ll_set_hpoint(ledc_dev_t *hw, ledc_mode_t speed_mode, ledc_channel_t channel_num, uint32_t hpoint_val)
{
	hw->channel_group[speed_mode].channel[channel_num].hpoint.hpoint = hpoint_val;
}

void ledc_ll_get_hpoint(ledc_dev_t *hw, ledc_mode_t speed_mode, ledc_channel_t channel_num, uint32_t *hpoint_val)
{
	*hpoint_val = hw->channel_group[speed_mode].channel[channel_num].hpoint.hpoint;
}

void ledc_ll_set_duty_int_part(ledc_dev_t *hw, ledc_mode_t speed_mode, ledc_channel_t channel_num, uint32_t duty_val)
{
	hw->channel_group[speed_mode].channel[channel_num].duty.duty = duty_val << 4;
}

void ledc_ll_get_duty(ledc_dev_t *hw, ledc_mode_t speed_mode, ledc_channel_t channel_num, uint32_t *duty_val)
{
	*duty_val = (hw->channel_group[speed_mode].channel[channel_num].duty_rd.duty_read >> 4);
}

void ledc_ll_set_duty_direction(ledc_dev_t *hw, ledc_mode_t speed_mode, ledc_channel_t channel_num, ledc_duty_direction_t duty_direction)
{
	hw->channel_group[speed_mode].channel[channel_num].conf1.duty_inc = duty_direction;
}

void ledc_ll_set_duty_num(ledc_dev_t *hw, ledc_mode_t speed_mode, ledc_channel_t channel_num, uint32_t duty_num)
{
	hw->channel_group[speed_mode].channel[channel_num].conf1.duty_num = duty_num;
}

void ledc_ll_set_duty_cycle(ledc_dev_t *hw, ledc_mode_t speed_mode, ledc_channel_t channel_num, uint32_t duty_cycle)
{
	hw->channel_group[speed_mode].channel[channel_num].conf1.duty_cycle = duty_cycle;
}

void ledc_ll_set_duty_scale(ledc_dev_t *hw, ledc_mode_t speed_mode, ledc_channel_t channel_num, uint32_t duty_scale)
{
	hw->channel_group[speed_mode].channel[channel_num].conf1.duty_scale = duty_scale;
}

void ledc_ll_set_fade_param(ledc_dev_t *hw, ledc_mode_t speed_mode, ledc_channel_t channel_num, uint32_t dir, uint32_t cycle, uint32_t scale, uint32_t step)
{
	typeof(hw->channel_group[speed_mode].channel[channel_num].conf1) conf1_reg;
	conf1_reg.val = hw->channel_group[speed_mode].channel[channel_num].conf1.val;
	conf1_reg.duty_inc = dir;
	conf1_reg.duty_num = step;
	conf1_reg.duty_cycle = cycle;
	conf1_reg.duty_scale = scale;
	hw->channel_group[speed_mode].channel[channel_num].conf1.val = conf1_reg.val;
}

void ledc_ll_set_sig_out_en(ledc_dev_t *hw, ledc_mode_t speed_mode, ledc_channel_t channel_num, bool sig_out_en)
{
	hw->channel_group[speed_mode].channel[channel_num].conf0.sig_out_en = sig_out_en;
}

void ledc_ll_set_duty_start(ledc_dev_t *hw, ledc_mode_t speed_mode, ledc_channel_t channel_num, bool duty_start)
{
	hw->channel_group[speed_mode].channel[channel_num].conf1.duty_start = duty_start;
}

void ledc_ll_set_idle_level(ledc_dev_t *hw, ledc_mode_t speed_mode, ledc_channel_t channel_num, uint32_t idle_level)
{
	hw->channel_group[speed_mode].channel[channel_num].conf0.idle_lv = idle_level & 0x1;
}

void ledc_ll_set_fade_end_intr(ledc_dev_t *hw, ledc_mode_t speed_mode, ledc_channel_t channel_num, bool fade_end_intr_en)
{
	uint32_t value = hw->int_ena.val;
	uint32_t int_en_base = LEDC_DUTY_CHNG_END_LSCH0_INT_ENA_S;
	hw->int_ena.val = fade_end_intr_en ? (value | BIT(int_en_base + channel_num)) : (value & (~(BIT(int_en_base + channel_num))));
}

void ledc_ll_get_fade_end_intr_status(ledc_dev_t *hw, ledc_mode_t speed_mode, uint32_t *intr_status)
{
	uint32_t value = hw->int_st.val;
	uint32_t int_en_base = LEDC_DUTY_CHNG_END_LSCH0_INT_ENA_S;
	*intr_status = (value >> int_en_base) & 0xff;
}

void ledc_ll_clear_fade_end_intr_status(ledc_dev_t *hw, ledc_mode_t speed_mode, ledc_channel_t channel_num)
{
	uint32_t int_en_base = LEDC_DUTY_CHNG_END_LSCH0_INT_ENA_S;
	hw->int_clr.val = BIT(int_en_base + channel_num);
}

void ledc_ll_bind_channel_timer(ledc_dev_t *hw, ledc_mode_t speed_mode, ledc_channel_t channel_num, ledc_timer_t timer_sel)
{
	hw->channel_group[speed_mode].channel[channel_num].conf0.timer_sel = timer_sel;
}

void ledc_ll_get_channel_timer(ledc_dev_t *hw, ledc_mode_t speed_mode, ledc_channel_t channel_num, ledc_timer_t *timer_sel)
{
	*timer_sel = (ledc_timer_t)(hw->channel_group[speed_mode].channel[channel_num].conf0.timer_sel);
}

