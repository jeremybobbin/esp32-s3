#include <stdbool.h>
#include <stdint.h>

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


typedef volatile struct i2s_dev_s {
	uint32_t reserved_0;
	uint32_t reserved_4;
	uint32_t reserved_8;
	union {
		struct {
			uint32_t rx_done                       :    1;
			uint32_t tx_done                       :    1;
			uint32_t rx_hung                       :    1;
			uint32_t tx_hung                       :    1;
			uint32_t reserved4                     :    28;
		};
		uint32_t val;
	} int_raw;
	union {
		struct {
			uint32_t rx_done                       :    1;
			uint32_t tx_done                       :    1;
			uint32_t rx_hung                       :    1;
			uint32_t tx_hung                       :    1;
			uint32_t reserved4                     :    28;
		};
		uint32_t val;
	} int_st;
	union {
		struct {
			uint32_t rx_done                       :    1;
			uint32_t tx_done                       :    1;
			uint32_t rx_hung                       :    1;
			uint32_t tx_hung                       :    1;
			uint32_t reserved4                     :    28;
		};
		uint32_t val;
	} int_ena;
	union {
		struct {
			uint32_t rx_done                       :    1;
			uint32_t tx_done                       :    1;
			uint32_t rx_hung                       :    1;
			uint32_t tx_hung                       :    1;
			uint32_t reserved4                     :    28;
		};
		uint32_t val;
	} int_clr;
	uint32_t reserved_1c;
	union {
		struct {
			uint32_t rx_reset                      :    1;
			uint32_t rx_fifo_reset                 :    1;
			uint32_t rx_start                      :    1;
			uint32_t rx_slave_mod                  :    1;
			uint32_t reserved4                     :    1;
			uint32_t rx_mono                       :    1;
			uint32_t reserved6                     :    1;
			uint32_t rx_big_endian                 :    1;
			uint32_t rx_update                     :    1;
			uint32_t rx_mono_fst_vld               :    1;
			uint32_t rx_pcm_conf                   :    2;
			uint32_t rx_pcm_bypass                 :    1;
			uint32_t rx_stop_mode                  :    2;
			uint32_t rx_left_align                 :    1;
			uint32_t rx_24_fill_en                 :    1;
			uint32_t rx_ws_idle_pol                :    1;
			uint32_t rx_bit_order                  :    1;
			uint32_t rx_tdm_en                     :    1;
			uint32_t rx_pdm_en                     :    1;
			uint32_t rx_pdm2pcm_en                 :    1;
			uint32_t rx_pdm_sinc_dsr_16_en         :    1;
			uint32_t reserved23                    :    9;
		};
		uint32_t val;
	} rx_conf;
	union {
		struct {
			uint32_t tx_reset                      :    1;
			uint32_t tx_fifo_reset                 :    1;
			uint32_t tx_start                      :    1;
			uint32_t tx_slave_mod                  :    1;
			uint32_t reserved4                     :    1;
			uint32_t tx_mono                       :    1;
			uint32_t tx_chan_equal                 :    1;
			uint32_t tx_big_endian                 :    1;
			uint32_t tx_update                     :    1;
			uint32_t tx_mono_fst_vld               :    1;
			uint32_t tx_pcm_conf                   :    2;
			uint32_t tx_pcm_bypass                 :    1;
			uint32_t tx_stop_en                    :    1;
			uint32_t reserved14                    :    1;
			uint32_t tx_left_align                 :    1;
			uint32_t tx_24_fill_en                 :    1;
			uint32_t tx_ws_idle_pol                :    1;
			uint32_t tx_bit_order                  :    1;
			uint32_t tx_tdm_en                     :    1;
			uint32_t tx_pdm_en                     :    1;
			uint32_t reserved21                    :    3;
			uint32_t tx_chan_mod                   :    3;
			uint32_t sig_loopback                  :    1;
			uint32_t reserved28                    :    4;
		};
		uint32_t val;
	} tx_conf;
	union {
		struct {
			uint32_t rx_tdm_ws_width               :    7;
			uint32_t rx_bck_div_num                :    6;
			uint32_t rx_bits_mod                   :    5;
			uint32_t rx_half_sample_bits           :    6;
			uint32_t rx_tdm_chan_bits              :    5;
			uint32_t rx_msb_shift                  :    1;
			uint32_t reserved30                    :    2;
		};
		uint32_t val;
	} rx_conf1;
	union {
		struct {
			uint32_t tx_tdm_ws_width               :    7;
			uint32_t tx_bck_div_num                :    6;
			uint32_t tx_bits_mod                   :    5;
			uint32_t tx_half_sample_bits           :    6;
			uint32_t tx_tdm_chan_bits              :    5;
			uint32_t tx_msb_shift                  :    1;
			uint32_t tx_bck_no_dly                 :    1;
			uint32_t reserved31                    :    1;
		};
		uint32_t val;
	} tx_conf1;
	union {
		struct {
			uint32_t rx_clkm_div_num               :    8;
			uint32_t reserved8                     :    18;
			uint32_t rx_clk_active                 :    1;
			uint32_t rx_clk_sel                    :    2;
			uint32_t mclk_sel                      :    1;
			uint32_t reserved30                    :    2;
		};
		uint32_t val;
	} rx_clkm_conf;
	union {
		struct {
			uint32_t tx_clkm_div_num               :    8;
			uint32_t reserved8                     :    18;
			uint32_t tx_clk_active                 :    1;
			uint32_t tx_clk_sel                    :    2;
			uint32_t clk_en                        :    1;
			uint32_t reserved30                    :    2;
		};
		uint32_t val;
	} tx_clkm_conf;
	union {
		struct {
			uint32_t rx_clkm_div_z                 :    9;
			uint32_t rx_clkm_div_y                 :    9;
			uint32_t rx_clkm_div_x                 :    9;
			uint32_t rx_clkm_div_yn1               :    1;
			uint32_t reserved28                    :    4;
		};
		uint32_t val;
	} rx_clkm_div_conf;
	union {
		struct {
			uint32_t tx_clkm_div_z                 :    9;
			uint32_t tx_clkm_div_y                 :    9;
			uint32_t tx_clkm_div_x                 :    9;
			uint32_t tx_clkm_div_yn1               :    1;
			uint32_t reserved28                    :    4;
		};
		uint32_t val;
	} tx_clkm_div_conf;
	union {
		struct {
			uint32_t tx_hp_bypass                  :    1;
			uint32_t tx_sinc_osr2                  :    4;
			uint32_t tx_prescale                   :    8;
			uint32_t tx_hp_in_shift                :    2;
			uint32_t tx_lp_in_shift                :    2;
			uint32_t tx_sinc_in_shift              :    2;
			uint32_t tx_sigmadelta_in_shift        :    2;
			uint32_t tx_sigmadelta_dither2         :    1;
			uint32_t tx_sigmadelta_dither          :    1;
			uint32_t tx_dac_2out_en                :    1;
			uint32_t tx_dac_mode_en                :    1;
			uint32_t pcm2pdm_conv_en               :    1;
			uint32_t reserved26                    :    6;
		};
		uint32_t val;
	} tx_pcm2pdm_conf;
	union {
		struct {
			uint32_t tx_pdm_fp                     :    10;
			uint32_t tx_pdm_fs                     :    10;
			uint32_t tx_iir_hp_mult12_5            :    3;
			uint32_t tx_iir_hp_mult12_0            :    3;
			uint32_t reserved26                    :    6;
		};
		uint32_t val;
	} tx_pcm2pdm_conf1;
	uint32_t reserved_48;
	uint32_t reserved_4c;
	union {
		struct {
			uint32_t rx_tdm_chan0_en               :    1;
			uint32_t rx_tdm_chan1_en               :    1;
			uint32_t rx_tdm_chan2_en               :    1;
			uint32_t rx_tdm_chan3_en               :    1;
			uint32_t rx_tdm_chan4_en               :    1;
			uint32_t rx_tdm_chan5_en               :    1;
			uint32_t rx_tdm_chan6_en               :    1;
			uint32_t rx_tdm_chan7_en               :    1;
			uint32_t rx_tdm_chan8_en               :    1;
			uint32_t rx_tdm_chan9_en               :    1;
			uint32_t rx_tdm_chan10_en              :    1;
			uint32_t rx_tdm_chan11_en              :    1;
			uint32_t rx_tdm_chan12_en              :    1;
			uint32_t rx_tdm_chan13_en              :    1;
			uint32_t rx_tdm_chan14_en              :    1;
			uint32_t rx_tdm_chan15_en              :    1;
			uint32_t rx_tdm_tot_chan_num           :    4;
			uint32_t reserved20                    :    12;
		};
		uint32_t val;
	} rx_tdm_ctrl;
	union {
		struct {
			uint32_t tx_tdm_chan0_en               :    1;
			uint32_t tx_tdm_chan1_en               :    1;
			uint32_t tx_tdm_chan2_en               :    1;
			uint32_t tx_tdm_chan3_en               :    1;
			uint32_t tx_tdm_chan4_en               :    1;
			uint32_t tx_tdm_chan5_en               :    1;
			uint32_t tx_tdm_chan6_en               :    1;
			uint32_t tx_tdm_chan7_en               :    1;
			uint32_t tx_tdm_chan8_en               :    1;
			uint32_t tx_tdm_chan9_en               :    1;
			uint32_t tx_tdm_chan10_en              :    1;
			uint32_t tx_tdm_chan11_en              :    1;
			uint32_t tx_tdm_chan12_en              :    1;
			uint32_t tx_tdm_chan13_en              :    1;
			uint32_t tx_tdm_chan14_en              :    1;
			uint32_t tx_tdm_chan15_en              :    1;
			uint32_t tx_tdm_tot_chan_num           :    4;
			uint32_t tx_tdm_skip_msk_en            :    1;
			uint32_t reserved21                    :    11;
		};
		uint32_t val;
	} tx_tdm_ctrl;
	union {
		struct {
			uint32_t rx_sd_in_dm                   :    2;
			uint32_t reserved2                     :    2;
			uint32_t rx_sd1_in_dm                  :    2;
			uint32_t reserved6                     :    2;
			uint32_t rx_sd2_in_dm                  :    2;
			uint32_t reserved10                    :    2;
			uint32_t rx_sd3_in_dm                  :    2;
			uint32_t reserved14                    :    2;
			uint32_t rx_ws_out_dm                  :    2;
			uint32_t reserved18                    :    2;
			uint32_t rx_bck_out_dm                 :    2;
			uint32_t reserved22                    :    2;
			uint32_t rx_ws_in_dm                   :    2;
			uint32_t reserved26                    :    2;
			uint32_t rx_bck_in_dm                  :    2;
			uint32_t reserved30                    :    2;
		};
		uint32_t val;
	} rx_timing;
	union {
		struct {
			uint32_t tx_sd_out_dm                  :    2;
			uint32_t reserved2                     :    2;
			uint32_t tx_sd1_out_dm                 :    2;
			uint32_t reserved6                     :    10;
			uint32_t tx_ws_out_dm                  :    2;
			uint32_t reserved18                    :    2;
			uint32_t tx_bck_out_dm                 :    2;
			uint32_t reserved22                    :    2;
			uint32_t tx_ws_in_dm                   :    2;
			uint32_t reserved26                    :    2;
			uint32_t tx_bck_in_dm                  :    2;
			uint32_t reserved30                    :    2;
		};
		uint32_t val;
	} tx_timing;
	union {
		struct {
			uint32_t fifo_timeout                  :    8;
			uint32_t fifo_timeout_shift            :    3;
			uint32_t fifo_timeout_ena              :    1;
			uint32_t reserved12                    :    20;
		};
		uint32_t val;
	} lc_hung_conf;
	union {
		struct {
			uint32_t rx_eof_num                    :    12;
			uint32_t reserved12                    :    20;
		};
		uint32_t val;
	} rx_eof_num;
	uint32_t conf_single_data;                             
	union {
		struct {
			uint32_t tx_idle                       :    1;
			uint32_t reserved1                     :    31;
		};
		uint32_t val;
	} state;
	uint32_t reserved_70;
	uint32_t reserved_74;
	uint32_t reserved_78;
	uint32_t reserved_7c;
	union {
		struct {
			uint32_t date                          :    28;
			uint32_t reserved28                    :    4;
		};
		uint32_t val;
	} date;
} i2s_dev_t;

typedef enum {
	I2S_CLK_D2CLK = 0,
} i2s_clock_src_t;

typedef enum {
	I2S_PDM_SIG_SCALING_DIV_2 = 0,
	I2S_PDM_SIG_SCALING_MUL_1 = 1,
	I2S_PDM_SIG_SCALING_MUL_2 = 2,
	I2S_PDM_SIG_SCALING_MUL_4 = 3,
} i2s_pdm_sig_scale_t;

typedef enum {
	I2S_PCM_DISABLE = 0,
	I2S_PCM_A_DECOMPRESS,
	I2S_PCM_A_COMPRESS,
	I2S_PCM_U_DECOMPRESS,
	I2S_PCM_U_COMPRESS,
} i2s_pcm_compress_t;

typedef enum {
	I2S_PDM_DSR_8S = 0,
	I2S_PDM_DSR_16S,
	I2S_PDM_DSR_MAX,
} i2s_pdm_dsr_t;


extern i2s_dev_t I2S0;
extern i2s_dev_t I2S1;

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
