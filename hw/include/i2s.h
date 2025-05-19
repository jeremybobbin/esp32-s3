#include <stdbool.h>

#define I2S_LL_GET_HW(num) (((num) == 0) ? (&I2S0) : &I2S1)

#define I2S_LL_TDM_CH_MASK (0xffff)
#define I2S_LL_PDM_BCK_FACTOR          (64)
#define I2S_LL_BASE_CLK                (2*APB_CLK_FREQ)

#define I2S_LL_MCLK_DIVIDER_BIT_WIDTH  (9)
#define I2S_LL_MCLK_DIVIDER_MAX        ((1 << I2S_LL_MCLK_DIVIDER_BIT_WIDTH) - 1)

typedef struct {
	uint16_t mclk_div; // I2S module clock devider, Fmclk = Fsclk /(mclk_div+b/a)
	uint16_t a;
	uint16_t b;        // The decimal part of module clock devider, the decimal is: b/a
} i2s_ll_mclk_div_t;

void i2s_ll_enable_clock(i2s_dev_t *hw);
void i2s_ll_disable_clock(i2s_dev_t *hw);
void i2s_ll_tx_enable_clock(i2s_dev_t *hw);
void i2s_ll_rx_enable_clock(i2s_dev_t *hw);
void i2s_ll_tx_disable_clock(i2s_dev_t *hw);
void i2s_ll_rx_disable_clock(i2s_dev_t *hw);
void i2s_ll_mclk_use_tx_clk(i2s_dev_t *hw);
void i2s_ll_mclk_use_rx_clk(i2s_dev_t *hw);
void i2s_ll_tx_set_slave_mod(i2s_dev_t *hw, bool slave_en);
void i2s_ll_rx_set_slave_mod(i2s_dev_t *hw, bool slave_en);
void i2s_ll_tx_reset(i2s_dev_t *hw);
void i2s_ll_rx_reset(i2s_dev_t *hw);
void i2s_ll_tx_reset_fifo(i2s_dev_t *hw);
void i2s_ll_rx_reset_fifo(i2s_dev_t *hw);
void i2s_ll_tx_clk_set_src(i2s_dev_t *hw, i2s_clock_src_t src);
void i2s_ll_rx_clk_set_src(i2s_dev_t *hw, i2s_clock_src_t src);
void i2s_ll_tx_set_bck_div_num(i2s_dev_t *hw, uint32_t val);
void i2s_ll_tx_set_raw_clk_div(i2s_dev_t *hw, uint32_t x, uint32_t y, uint32_t z, uint32_t yn1);
void i2s_ll_tx_set_clk(i2s_dev_t *hw, i2s_ll_mclk_div_t *set);
void i2s_ll_rx_set_bck_div_num(i2s_dev_t *hw, uint32_t val);
void i2s_ll_rx_set_clk(i2s_dev_t *hw, i2s_ll_mclk_div_t *set);
void i2s_ll_tx_start(i2s_dev_t *hw);
void i2s_ll_rx_start(i2s_dev_t *hw);
void i2s_ll_tx_stop(i2s_dev_t *hw);
void i2s_ll_rx_stop(i2s_dev_t *hw);
void i2s_ll_tx_set_ws_width(i2s_dev_t *hw, int width);
void i2s_ll_rx_set_ws_width(i2s_dev_t *hw, int width);
void i2s_ll_rx_set_eof_num(i2s_dev_t *hw, int eof_num);
void i2s_ll_tx_set_sample_bit(i2s_dev_t *hw, uint8_t chan_bit, int data_bit);
void i2s_ll_rx_set_sample_bit(i2s_dev_t *hw, uint8_t chan_bit, int data_bit);
void i2s_ll_tx_set_half_sample_bit(i2s_dev_t *hw, int half_sample_bits);
void i2s_ll_rx_set_half_sample_bit(i2s_dev_t *hw, int half_sample_bits);
void i2s_ll_tx_enable_msb_shift(i2s_dev_t *hw, bool msb_shift_enable);
void i2s_ll_rx_enable_msb_shift(i2s_dev_t *hw, bool msb_shift_enable);
void i2s_ll_tx_set_chan_num(i2s_dev_t *hw, int total_num);
void i2s_ll_rx_set_chan_num(i2s_dev_t *hw, int total_num);
void i2s_ll_tx_set_active_chan_mask(i2s_dev_t *hw, uint32_t chan_mask);
void i2s_ll_rx_set_active_chan_mask(i2s_dev_t *hw, uint32_t chan_mask);
void i2s_ll_tx_set_ws_idle_pol(i2s_dev_t *hw, bool ws_pol_level);
void i2s_ll_rx_set_ws_idle_pol(i2s_dev_t *hw, bool ws_pol_level);
void i2s_ll_tx_enable_pdm(i2s_dev_t *hw, bool pdm_enable);
void i2s_ll_rx_enable_pdm(i2s_dev_t *hw, bool pdm_enable);
void i2s_ll_tx_set_pdm_fpfs(i2s_dev_t *hw, uint32_t fp, uint32_t fs);
uint32_t i2s_ll_tx_get_pdm_fp(i2s_dev_t *hw);
uint32_t i2s_ll_tx_get_pdm_fs(i2s_dev_t *hw);
void i2s_ll_tx_set_pdm_prescale(i2s_dev_t *hw, bool prescale);
void i2s_ll_tx_set_pdm_hp_scale(i2s_dev_t *hw, i2s_pdm_sig_scale_t sig_scale);
void i2s_ll_tx_set_pdm_lp_scale(i2s_dev_t *hw, i2s_pdm_sig_scale_t sig_scale);
void i2s_ll_tx_set_pdm_sinc_scale(i2s_dev_t *hw, i2s_pdm_sig_scale_t sig_scale);
void i2s_ll_tx_set_pdm_sd_scale(i2s_dev_t *hw, i2s_pdm_sig_scale_t sig_scale);
void i2s_ll_tx_set_pdm_hp_filter_param0(i2s_dev_t *hw, uint32_t param);
void i2s_ll_tx_set_pdm_hp_filter_param5(i2s_dev_t *hw, uint32_t param);
void i2s_ll_tx_enable_pdm_hp_filter(i2s_dev_t *hw, bool enable);
void i2s_ll_tx_enable_pdm_sd_codec(i2s_dev_t *hw, bool enable);
void i2s_ll_tx_set_pdm_sd_dither(i2s_dev_t *hw, uint32_t dither);
void i2s_ll_tx_set_pdm_sd_dither2(i2s_dev_t *hw, uint32_t dither2);
void i2s_ll_rx_set_pdm_dsr(i2s_dev_t *hw, i2s_pdm_dsr_t dsr);
void i2s_ll_rx_get_pdm_dsr(i2s_dev_t *hw, i2s_pdm_dsr_t *dsr);
void i2s_ll_tx_set_pcm_type(i2s_dev_t *hw, i2s_pcm_compress_t pcm_cfg);
void i2s_ll_rx_set_pcm_type(i2s_dev_t *hw, i2s_pcm_compress_t pcm_cfg);
void i2s_ll_tx_enable_left_align(i2s_dev_t *hw, bool ena);
void i2s_ll_rx_enable_left_align(i2s_dev_t *hw, bool ena);
void i2s_ll_rx_enable_big_endian(i2s_dev_t *hw, bool ena);
void i2s_ll_tx_enable_big_endian(i2s_dev_t *hw, bool ena);
void i2s_ll_tx_set_bit_order(i2s_dev_t *hw, bool lsb_order_ena);
void i2s_ll_rx_set_bit_order(i2s_dev_t *hw, bool lsb_order_ena);
void i2s_ll_tx_set_skip_mask(i2s_dev_t *hw, bool skip_mask_ena);
void i2s_ll_set_single_data(i2s_dev_t *hw, uint32_t data);
void i2s_ll_tx_enable_mono_mode(i2s_dev_t *hw, bool mono_ena);
void i2s_ll_rx_enable_mono_mode(i2s_dev_t *hw, bool mono_ena);
void i2s_ll_share_bck_ws(i2s_dev_t *hw, bool ena);
