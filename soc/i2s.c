
// The LL layer for I2S register operations

#include <stdbool.h>
#include "soc/i2s.h"
#include "soc/i2c.h"



#define I2S_LL_GET_HW(num) (((num) == 0) ? (&I2S0) : &I2S1)

#define I2S_LL_TDM_CH_MASK (0xffff)
#define I2S_LL_PDM_BCK_FACTOR          (64)
#define I2S_LL_BASE_CLK                (2*APB_CLK_FREQ)

#define I2S_LL_MCLK_DIVIDER_BIT_WIDTH  (9)
#define I2S_LL_MCLK_DIVIDER_MAX        ((1 << I2S_LL_MCLK_DIVIDER_BIT_WIDTH) - 1)

void i2s_ll_enable_clock(i2s_dev_t *hw)
{
	hw->tx_clkm_conf.clk_en = 1;
}

void i2s_ll_disable_clock(i2s_dev_t *hw)
{
	hw->tx_clkm_conf.clk_en = 0;
}

void i2s_ll_tx_enable_clock(i2s_dev_t *hw)
{
	hw->tx_clkm_conf.tx_clk_active = 1;
}

void i2s_ll_rx_enable_clock(i2s_dev_t *hw)
{
	hw->rx_clkm_conf.rx_clk_active = 1;
}

void i2s_ll_tx_disable_clock(i2s_dev_t *hw)
{
	hw->tx_clkm_conf.tx_clk_active = 0;
}

void i2s_ll_rx_disable_clock(i2s_dev_t *hw)
{
	hw->rx_clkm_conf.rx_clk_active = 0;
}

void i2s_ll_mclk_use_tx_clk(i2s_dev_t *hw)
{
	hw->rx_clkm_conf.mclk_sel = 0;
}

void i2s_ll_mclk_use_rx_clk(i2s_dev_t *hw)
{
	hw->rx_clkm_conf.mclk_sel = 1;
}

void i2s_ll_tx_set_slave_mod(i2s_dev_t *hw, bool slave_en)
{
	hw->tx_conf.tx_slave_mod = slave_en;
}

void i2s_ll_rx_set_slave_mod(i2s_dev_t *hw, bool slave_en)
{
	hw->rx_conf.rx_slave_mod = slave_en;
}

void i2s_ll_tx_reset(i2s_dev_t *hw)
{
	hw->tx_conf.tx_reset = 1;
	hw->tx_conf.tx_reset = 0;
}

void i2s_ll_rx_reset(i2s_dev_t *hw)
{
	hw->rx_conf.rx_reset = 1;
	hw->rx_conf.rx_reset = 0;
}

void i2s_ll_tx_reset_fifo(i2s_dev_t *hw)
{
	hw->tx_conf.tx_fifo_reset = 1;
	hw->tx_conf.tx_fifo_reset = 0;
}

void i2s_ll_rx_reset_fifo(i2s_dev_t *hw)
{
	hw->rx_conf.rx_fifo_reset = 1;
	hw->rx_conf.rx_fifo_reset = 0;
}

void i2s_ll_tx_clk_set_src(i2s_dev_t *hw, i2s_clock_src_t src)
{
	hw->tx_clkm_conf.tx_clk_sel = 2;
}

void i2s_ll_rx_clk_set_src(i2s_dev_t *hw, i2s_clock_src_t src)
{
	hw->rx_clkm_conf.rx_clk_sel = 2;
}

void i2s_ll_tx_set_bck_div_num(i2s_dev_t *hw, uint32_t val)
{
	hw->tx_conf1.tx_bck_div_num = val - 1;
}

void i2s_ll_tx_set_raw_clk_div(i2s_dev_t *hw, uint32_t x, uint32_t y, uint32_t z, uint32_t yn1)
{
	hw->tx_clkm_div_conf.tx_clkm_div_x = x;
	hw->tx_clkm_div_conf.tx_clkm_div_y = y;
	hw->tx_clkm_div_conf.tx_clkm_div_z = z;
	hw->tx_clkm_div_conf.tx_clkm_div_yn1 = yn1;
}

void i2s_ll_tx_set_clk(i2s_dev_t *hw, i2s_ll_mclk_div_t *set)
{
	if (set->a == 0 || set->b == 0) {
		hw->tx_clkm_div_conf.tx_clkm_div_x = 0;
		hw->tx_clkm_div_conf.tx_clkm_div_y = 0;
		hw->tx_clkm_div_conf.tx_clkm_div_z = 0;
	} else {
		if (set->b > set->a / 2) {
			hw->tx_clkm_div_conf.tx_clkm_div_x = set->a / (set->a - set->b) - 1;
			hw->tx_clkm_div_conf.tx_clkm_div_y = set->a % (set->a - set->b);
			hw->tx_clkm_div_conf.tx_clkm_div_z = set->a - set->b;
			hw->tx_clkm_div_conf.tx_clkm_div_yn1 = 1;
		} else {
			hw->tx_clkm_div_conf.tx_clkm_div_x = set->a / set->b - 1;
			hw->tx_clkm_div_conf.tx_clkm_div_y = set->a % set->b + 1;
			hw->tx_clkm_div_conf.tx_clkm_div_z = set->b;
			hw->tx_clkm_div_conf.tx_clkm_div_yn1 = 0;
		}
	}
	HAL_FORCE_MODIFY_U32_REG_FIELD(hw->tx_clkm_conf, tx_clkm_div_num, set->mclk_div);
}

void i2s_ll_rx_set_bck_div_num(i2s_dev_t *hw, uint32_t val)
{
	hw->rx_conf1.rx_bck_div_num = val - 1;
}

void i2s_ll_rx_set_clk(i2s_dev_t *hw, i2s_ll_mclk_div_t *set)
{
	if (set->a == 0 || set->b == 0) {
		hw->rx_clkm_div_conf.rx_clkm_div_x = 0;
		hw->rx_clkm_div_conf.rx_clkm_div_y = 0;
		hw->rx_clkm_div_conf.rx_clkm_div_z = 0;
	} else {
		if (set->b > set->a / 2) {
			hw->rx_clkm_div_conf.rx_clkm_div_x = set->a / (set->a - set->b) - 1;
			hw->rx_clkm_div_conf.rx_clkm_div_y = set->a % (set->a - set->b);
			hw->rx_clkm_div_conf.rx_clkm_div_z = set->a - set->b;
			hw->rx_clkm_div_conf.rx_clkm_div_yn1 = 1;
		} else {
			hw->rx_clkm_div_conf.rx_clkm_div_x = set->a / set->b - 1;
			hw->rx_clkm_div_conf.rx_clkm_div_y = set->a % set->b + 1;
			hw->rx_clkm_div_conf.rx_clkm_div_z = set->b;
			hw->rx_clkm_div_conf.rx_clkm_div_yn1 = 0;
		}
	}
	HAL_FORCE_MODIFY_U32_REG_FIELD(hw->rx_clkm_conf, rx_clkm_div_num, set->mclk_div);
}

void i2s_ll_tx_start(i2s_dev_t *hw)
{
	hw->tx_conf.tx_update = 0;
	hw->tx_conf.tx_update = 1;
	hw->tx_conf.tx_start = 1;
}

void i2s_ll_rx_start(i2s_dev_t *hw)
{
	hw->rx_conf.rx_update = 0;
	hw->rx_conf.rx_update = 1;
	hw->rx_conf.rx_start = 1;
}

void i2s_ll_tx_stop(i2s_dev_t *hw)
{
	hw->tx_conf.tx_start = 0;
}

void i2s_ll_rx_stop(i2s_dev_t *hw)
{
	hw->rx_conf.rx_start = 0;
}

void i2s_ll_tx_set_ws_width(i2s_dev_t *hw, int width)
{
	hw->tx_conf1.tx_tdm_ws_width = width - 1;
}

void i2s_ll_rx_set_ws_width(i2s_dev_t *hw, int width)
{
	hw->rx_conf1.rx_tdm_ws_width = width - 1;
}

void i2s_ll_rx_set_eof_num(i2s_dev_t *hw, int eof_num)
{
	hw->rx_eof_num.rx_eof_num = eof_num;
}

void i2s_ll_tx_set_sample_bit(i2s_dev_t *hw, uint8_t chan_bit, int data_bit)
{
	hw->tx_conf1.tx_bits_mod = data_bit - 1;
	hw->tx_conf1.tx_tdm_chan_bits = chan_bit - 1;
}

void i2s_ll_rx_set_sample_bit(i2s_dev_t *hw, uint8_t chan_bit, int data_bit)
{
	hw->rx_conf1.rx_bits_mod = data_bit - 1;
	hw->rx_conf1.rx_tdm_chan_bits = chan_bit - 1;
}

void i2s_ll_tx_set_half_sample_bit(i2s_dev_t *hw, int half_sample_bits)
{
	hw->tx_conf1.tx_half_sample_bits = half_sample_bits - 1;
}

void i2s_ll_rx_set_half_sample_bit(i2s_dev_t *hw, int half_sample_bits)
{
	hw->rx_conf1.rx_half_sample_bits = half_sample_bits - 1;
}

void i2s_ll_tx_enable_msb_shift(i2s_dev_t *hw, bool msb_shift_enable)
{
	hw->tx_conf1.tx_msb_shift = msb_shift_enable;
}

void i2s_ll_rx_enable_msb_shift(i2s_dev_t *hw, bool msb_shift_enable)
{
	hw->rx_conf1.rx_msb_shift = msb_shift_enable;
}

void i2s_ll_tx_set_chan_num(i2s_dev_t *hw, int total_num)
{
	hw->tx_tdm_ctrl.tx_tdm_tot_chan_num = total_num - 1;
}

void i2s_ll_rx_set_chan_num(i2s_dev_t *hw, int total_num)
{
	hw->rx_tdm_ctrl.rx_tdm_tot_chan_num = total_num - 1;
}

void i2s_ll_tx_set_active_chan_mask(i2s_dev_t *hw, uint32_t chan_mask)
{
	typeof(hw->tx_tdm_ctrl) tdm_ctrl_reg = hw->tx_tdm_ctrl;
	tdm_ctrl_reg.val &= ~I2S_LL_TDM_CH_MASK;
	tdm_ctrl_reg.val |= chan_mask & I2S_LL_TDM_CH_MASK;
	hw->tx_tdm_ctrl.val = tdm_ctrl_reg.val;
}

void i2s_ll_rx_set_active_chan_mask(i2s_dev_t *hw, uint32_t chan_mask)
{
	typeof(hw->rx_tdm_ctrl) tdm_ctrl_reg = hw->rx_tdm_ctrl;
	tdm_ctrl_reg.val &= ~I2S_LL_TDM_CH_MASK;
	tdm_ctrl_reg.val |= chan_mask & I2S_LL_TDM_CH_MASK;
	hw->rx_tdm_ctrl.val = tdm_ctrl_reg.val;
}

void i2s_ll_tx_set_ws_idle_pol(i2s_dev_t *hw, bool ws_pol_level)
{
	hw->tx_conf.tx_ws_idle_pol = ws_pol_level;
}

void i2s_ll_rx_set_ws_idle_pol(i2s_dev_t *hw, bool ws_pol_level)
{
	hw->rx_conf.rx_ws_idle_pol = ws_pol_level;
}

void i2s_ll_tx_enable_pdm(i2s_dev_t *hw, bool pdm_enable)
{
	hw->tx_conf.tx_pdm_en = pdm_enable;
	hw->tx_conf.tx_tdm_en = !pdm_enable;
	hw->tx_pcm2pdm_conf.pcm2pdm_conv_en = pdm_enable;
}

void i2s_ll_rx_enable_pdm(i2s_dev_t *hw, bool pdm_enable)
{
	hw->rx_conf.rx_pdm_en = pdm_enable;
	hw->rx_conf.rx_tdm_en = !pdm_enable;
	hw->rx_conf.rx_pdm2pcm_en = pdm_enable;
}

void i2s_ll_tx_set_pdm_fpfs(i2s_dev_t *hw, uint32_t fp, uint32_t fs)
{
	hw->tx_pcm2pdm_conf1.tx_pdm_fp = fp;
	hw->tx_pcm2pdm_conf1.tx_pdm_fs = fs;
	hw->tx_pcm2pdm_conf.tx_sinc_osr2 = fp / fs;
}

uint32_t i2s_ll_tx_get_pdm_fp(i2s_dev_t *hw)
{
	return hw->tx_pcm2pdm_conf1.tx_pdm_fp;
}

uint32_t i2s_ll_tx_get_pdm_fs(i2s_dev_t *hw)
{
	return hw->tx_pcm2pdm_conf1.tx_pdm_fs;
}

void i2s_ll_tx_set_pdm_prescale(i2s_dev_t *hw, bool prescale)
{
	HAL_FORCE_MODIFY_U32_REG_FIELD(hw->tx_pcm2pdm_conf, tx_prescale, prescale);
}

void i2s_ll_tx_set_pdm_hp_scale(i2s_dev_t *hw, i2s_pdm_sig_scale_t sig_scale)
{
	hw->tx_pcm2pdm_conf.tx_hp_in_shift = sig_scale;
}

void i2s_ll_tx_set_pdm_lp_scale(i2s_dev_t *hw, i2s_pdm_sig_scale_t sig_scale)
{
	hw->tx_pcm2pdm_conf.tx_lp_in_shift = sig_scale;
}

void i2s_ll_tx_set_pdm_sinc_scale(i2s_dev_t *hw, i2s_pdm_sig_scale_t sig_scale)
{
	hw->tx_pcm2pdm_conf.tx_sinc_in_shift = sig_scale;
}

void i2s_ll_tx_set_pdm_sd_scale(i2s_dev_t *hw, i2s_pdm_sig_scale_t sig_scale)
{
	hw->tx_pcm2pdm_conf.tx_sigmadelta_in_shift = sig_scale;
}

void i2s_ll_tx_set_pdm_hp_filter_param0(i2s_dev_t *hw, uint32_t param)
{
	hw->tx_pcm2pdm_conf1.tx_iir_hp_mult12_0 = param;
}

void i2s_ll_tx_set_pdm_hp_filter_param5(i2s_dev_t *hw, uint32_t param)
{
	hw->tx_pcm2pdm_conf1.tx_iir_hp_mult12_5 = param;
}

void i2s_ll_tx_enable_pdm_hp_filter(i2s_dev_t *hw, bool enable)
{
	hw->tx_pcm2pdm_conf.tx_hp_bypass = !enable;
}

void i2s_ll_tx_enable_pdm_sd_codec(i2s_dev_t *hw, bool enable)
{
	hw->tx_pcm2pdm_conf.tx_dac_2out_en = !enable;
	hw->tx_pcm2pdm_conf.tx_dac_mode_en = enable;
}

void i2s_ll_tx_set_pdm_sd_dither(i2s_dev_t *hw, uint32_t dither)
{
	hw->tx_pcm2pdm_conf.tx_sigmadelta_dither = dither;
}

void i2s_ll_tx_set_pdm_sd_dither2(i2s_dev_t *hw, uint32_t dither2)
{
	hw->tx_pcm2pdm_conf.tx_sigmadelta_dither2 = dither2;
}

void i2s_ll_rx_set_pdm_dsr(i2s_dev_t *hw, i2s_pdm_dsr_t dsr)
{
	hw->rx_conf.rx_pdm_sinc_dsr_16_en = dsr;
}

void i2s_ll_rx_get_pdm_dsr(i2s_dev_t *hw, i2s_pdm_dsr_t *dsr)
{
	*dsr = hw->rx_conf.rx_pdm_sinc_dsr_16_en;
}

void i2s_ll_tx_set_pcm_type(i2s_dev_t *hw, i2s_pcm_compress_t pcm_cfg)
{
	hw->tx_conf.tx_pcm_conf = pcm_cfg;
	hw->tx_conf.tx_pcm_bypass = !pcm_cfg;
}

void i2s_ll_rx_set_pcm_type(i2s_dev_t *hw, i2s_pcm_compress_t pcm_cfg)
{
	hw->rx_conf.rx_pcm_conf = pcm_cfg;
	hw->rx_conf.rx_pcm_bypass = !pcm_cfg;
}

void i2s_ll_tx_enable_left_align(i2s_dev_t *hw, bool ena)
{
	hw->tx_conf.tx_left_align = ena;
}

void i2s_ll_rx_enable_left_align(i2s_dev_t *hw, bool ena)
{
	hw->rx_conf.rx_left_align = ena;
}

void i2s_ll_rx_enable_big_endian(i2s_dev_t *hw, bool ena)
{
	hw->rx_conf.rx_big_endian = ena;
}

void i2s_ll_tx_enable_big_endian(i2s_dev_t *hw, bool ena)
{
	hw->tx_conf.tx_big_endian = ena;
}

void i2s_ll_tx_set_bit_order(i2s_dev_t *hw, bool lsb_order_ena)
{
	hw->tx_conf.tx_bit_order = lsb_order_ena;
}

void i2s_ll_rx_set_bit_order(i2s_dev_t *hw, bool lsb_order_ena)
{
	hw->rx_conf.rx_bit_order = lsb_order_ena;
}

void i2s_ll_tx_set_skip_mask(i2s_dev_t *hw, bool skip_mask_ena)
{
	hw->tx_tdm_ctrl.tx_tdm_skip_msk_en = skip_mask_ena;
}


void i2s_ll_set_single_data(i2s_dev_t *hw, uint32_t data)
{
	hw->conf_single_data = data;
}

void i2s_ll_tx_enable_mono_mode(i2s_dev_t *hw, bool mono_ena)
{
	hw->tx_conf.tx_mono = mono_ena;
	hw->tx_conf.tx_chan_equal = mono_ena;
}

void i2s_ll_rx_enable_mono_mode(i2s_dev_t *hw, bool mono_ena)
{
	hw->rx_conf.rx_mono = mono_ena;
	hw->rx_conf.rx_mono_fst_vld = mono_ena;
}

void i2s_ll_share_bck_ws(i2s_dev_t *hw, bool ena)
{
	hw->tx_conf.sig_loopback = ena;
}

