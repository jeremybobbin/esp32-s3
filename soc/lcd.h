#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#define LCD_LL_GET_HW(id) (((id) == 0) ? (&LCD_CAM) : NULL)

#define LCD_LL_EVENT_VSYNC_END  (1 << 0)
#define LCD_LL_EVENT_TRANS_DONE (1 << 1)

#define LCD_LL_CLK_FRAC_DIV_N_MAX  256 // LCD_CLK = LCD_CLK_S / (N + b/a), the N register is 8 bit-width
#define LCD_LL_CLK_FRAC_DIV_AB_MAX 64  // LCD_CLK = LCD_CLK_S / (N + b/a), the a/b register is 6 bit-width
#define LCD_LL_PCLK_DIV_MAX        64  // LCD_PCLK = LCD_CLK / MO, the MO register is 6 bit-width

#define LCD_LL_COLOR_RANGE_TO_REG(range) (uint8_t[]){0,1}[(range)]
#define LCD_LL_CONV_STD_TO_REG(std)      (uint8_t[]){0,1}[(std)]
#define LCD_LL_YUV_SAMPLE_TO_REG(sample) (uint8_t[]){0,1,2}[(sample)]


typedef enum {
	// For CPU domain
	SOC_MOD_CLK_CPU = 1,                       /*!< CPU_CLK can be sourced from XTAL, PLL, or RC_FAST by configuring soc_cpu_clk_src_t */
	// For RTC domain
	SOC_MOD_CLK_RTC_FAST,                      /*!< RTC_FAST_CLK can be sourced from XTAL_D2 or RC_FAST by configuring soc_rtc_fast_clk_src_t */
	SOC_MOD_CLK_RTC_SLOW,                      /*!< RTC_SLOW_CLK can be sourced from RC_SLOW, XTAL32K, or RC_FAST_D256 by configuring soc_rtc_slow_clk_src_t */
	// For digital domain: peripherals, WIFI, BLE
	SOC_MOD_CLK_APB,                           /*!< APB_CLK is highly dependent on the CPU_CLK source */
	SOC_MOD_CLK_PLL_F80M,                      /*!< PLL_F80M_CLK is derived from PLL, and has a fixed frequency of 80MHz */
	SOC_MOD_CLK_PLL_F160M,                     /*!< PLL_F160M_CLK is derived from PLL, and has a fixed frequency of 160MHz */
	SOC_MOD_CLK_PLL_D2,                        /*!< PLL_D2_CLK is derived from PLL, it has a fixed divider of 2 */
	SOC_MOD_CLK_XTAL32K,                       /*!< XTAL32K_CLK comes from the external 32kHz crystal, passing a clock gating to the peripherals */
	SOC_MOD_CLK_RC_FAST,                       /*!< RC_FAST_CLK comes from the internal 20MHz rc oscillator, passing a clock gating to the peripherals */
	SOC_MOD_CLK_RC_FAST_D256,                  /*!< RC_FAST_D256_CLK comes from the internal 20MHz rc oscillator, divided by 256, and passing a clock gating to the peripherals */
	SOC_MOD_CLK_XTAL,                          /*!< XTAL_CLK comes from the external 40MHz crystal */
	SOC_MOD_CLK_TEMP_SENSOR,                   /*!< TEMP_SENSOR_CLK comes directly from the internal 20MHz rc oscillator */
	SOC_MOD_CLK_INVALID,                       /*!< Indication of the end of the available module clock sources */
} soc_module_clk_t;

typedef enum {
	LCD_CLK_SRC_PLL160M = SOC_MOD_CLK_PLL_F160M,
	LCD_CLK_SRC_PLL240M = SOC_MOD_CLK_PLL_D2,
	LCD_CLK_SRC_XTAL = SOC_MOD_CLK_XTAL,
	LCD_CLK_SRC_DEFAULT = SOC_MOD_CLK_PLL_F160M,
} soc_periph_lcd_clk_src_t;


typedef enum {
	COLOR_PIXEL_YUV444,
	COLOR_PIXEL_YUV422,
	COLOR_PIXEL_YUV420,
	COLOR_PIXEL_YUV411,
} color_pixel_yuv_format_t;

typedef enum {
	LCD_YUV_SAMPLE_422 = COLOR_PIXEL_YUV422, /*!< YUV 4:2:2 sampling */
	LCD_YUV_SAMPLE_420 = COLOR_PIXEL_YUV420, /*!< YUV 4:2:0 sampling */
	LCD_YUV_SAMPLE_411 = COLOR_PIXEL_YUV411, /*!< YUV 4:1:1 sampling */
} lcd_yuv_sample_t;


typedef enum {
	COLOR_CONV_STD_RGB_YUV_BT601,
	COLOR_CONV_STD_RGB_YUV_BT709,
} color_conv_std_rgb_yuv_t;

typedef enum {
	LCD_YUV_CONV_STD_BT601 = COLOR_CONV_STD_RGB_YUV_BT601, /*!< YUV<->RGB conversion standard: BT.601 */
	LCD_YUV_CONV_STD_BT709 = COLOR_CONV_STD_RGB_YUV_BT709, /*!< YUV<->RGB conversion standard: BT.709 */
} lcd_yuv_conv_std_t;

typedef int lcd_clock_source_t;

typedef enum {
	COLOR_RANGE_LIMIT,
	COLOR_RANGE_FULL,
} color_range_t;

typedef enum {
	LCD_COLOR_RANGE_LIMIT = COLOR_RANGE_LIMIT, /*!< Limited color range */
	LCD_COLOR_RANGE_FULL = COLOR_RANGE_FULL,   /*!< Full color range */
} lcd_color_range_t;

typedef union {
	struct {
		uint32_t lcd_clkcnt_n: 6;
		uint32_t lcd_clk_equ_sysclk: 1;
		uint32_t lcd_ck_idle_edge: 1;
		uint32_t lcd_ck_out_edge: 1;
		uint32_t lcd_clkm_div_num: 8;
		uint32_t lcd_clkm_div_b: 6;
		uint32_t lcd_clkm_div_a: 6;
		uint32_t lcd_clk_sel: 2;
		uint32_t clk_en: 1;
	};
	uint32_t val;
} lcd_cam_lcd_clock_reg_t;

typedef union {
	struct {
		uint32_t reserved_0: 20;
		uint32_t lcd_conv_8bits_data_inv: 1;
		uint32_t lcd_conv_txtorx: 1;
		uint32_t lcd_conv_yuv2yuv_mode: 2;
		uint32_t lcd_conv_yuv_mode: 2;
		uint32_t lcd_conv_protocol_mode: 1;
		uint32_t lcd_conv_data_out_mode: 1;
		uint32_t lcd_conv_data_in_mode: 1;
		uint32_t lcd_conv_mode_8bits_on: 1;
		uint32_t lcd_conv_trans_mode: 1;
		uint32_t lcd_conv_bypass: 1;
	};
	uint32_t val;
} lcd_cam_lcd_rgb_yuv_reg_t;

typedef union {
	struct {
		uint32_t lcd_dout_cyclelen: 13;
		uint32_t lcd_always_out_en: 1;
		uint32_t reserved_14: 5;
		uint32_t lcd_8bits_order: 1;
		uint32_t lcd_update: 1;
		uint32_t lcd_bit_order: 1;
		uint32_t lcd_byte_order: 1;
		uint32_t lcd_2byte_en: 1;
		uint32_t lcd_dout: 1;
		uint32_t lcd_dummy: 1;
		uint32_t lcd_cmd: 1;
		uint32_t lcd_start: 1;
		uint32_t lcd_reset: 1;
		uint32_t lcd_dummy_cyclelen: 2;
		uint32_t lcd_cmd_2_cycle_en: 1;
	};
	uint32_t val;
} lcd_cam_lcd_user_reg_t;

typedef union {
	struct {
		uint32_t reserved_0: 1;
		uint32_t lcd_afifo_threshold_num: 5;
		uint32_t lcd_vfk_cyclelen: 6;
		uint32_t lcd_vbk_cyclelen: 13;
		uint32_t lcd_next_frame_en: 1;
		uint32_t lcd_bk_en: 1;
		uint32_t lcd_afifo_reset: 1;
		uint32_t lcd_cd_data_set: 1;
		uint32_t lcd_cd_dummy_set: 1;
		uint32_t lcd_cd_cmd_set: 1;
		uint32_t lcd_cd_idle_edge: 1;
	};
	uint32_t val;
} lcd_cam_lcd_misc_reg_t;

typedef union {
	struct {
		uint32_t lcd_hb_front: 11;
		uint32_t lcd_va_height: 10;
		uint32_t lcd_vt_height: 10;
		uint32_t lcd_rgb_mode_en: 1;
	};
	uint32_t val;
} lcd_cam_lcd_ctrl_reg_t;

typedef union {
	struct {
		uint32_t lcd_vb_front: 8;
		uint32_t lcd_ha_width: 12;
		uint32_t lcd_ht_width: 12;
	};
	uint32_t val;
} lcd_cam_lcd_ctrl1_reg_t;

typedef union {
	struct {
		uint32_t lcd_vsync_width: 7;
		uint32_t lcd_vsync_idle_pol: 1;
		uint32_t lcd_de_idle_pol: 1;
		uint32_t lcd_hs_blank_en: 1;
		uint32_t reserved_10: 6;
		uint32_t lcd_hsync_width: 7;
		uint32_t lcd_hsync_idle_pol: 1;
		uint32_t lcd_hsync_position: 8;
	};
	uint32_t val;
} lcd_cam_lcd_ctrl2_reg_t;

typedef union {
	struct {
		uint32_t lcd_cmd_value: 32;
	};
	uint32_t val;
} lcd_cam_lcd_cmd_val_reg_t;

typedef union {
	struct {
		uint32_t lcd_cd_mode: 2;
		uint32_t lcd_de_mode: 2;
		uint32_t lcd_hsync_mode: 2;
		uint32_t lcd_vsync_mode: 2;
		uint32_t reserved_8: 24;
	};
	uint32_t val;
} lcd_cam_lcd_dly_mode_reg_t;

typedef union {
	struct {
		uint32_t dout0_mode: 2;
		uint32_t dout1_mode: 2;
		uint32_t dout2_mode: 2;
		uint32_t dout3_mode: 2;
		uint32_t dout4_mode: 2;
		uint32_t dout5_mode: 2;
		uint32_t dout6_mode: 2;
		uint32_t dout7_mode: 2;
		uint32_t dout8_mode: 2;
		uint32_t dout9_mode: 2;
		uint32_t dout10_mode: 2;
		uint32_t dout11_mode: 2;
		uint32_t dout12_mode: 2;
		uint32_t dout13_mode: 2;
		uint32_t dout14_mode: 2;
		uint32_t dout15_mode: 2;
	};
	uint32_t val;
} lcd_cam_lcd_data_dout_mode_reg_t;


typedef union {
	struct {
		uint32_t cam_stop_en: 1;
		uint32_t cam_vsync_filter_thres: 3;
		uint32_t cam_update: 1;
		uint32_t cam_byte_order: 1;
		uint32_t cam_bit_order: 1;
		uint32_t cam_line_int_en: 1;
		uint32_t cam_vs_eof_en: 1;
		uint32_t cam_clkm_div_num: 8;
		uint32_t cam_clkm_div_b: 6;
		uint32_t cam_clkm_div_a: 6;
		uint32_t cam_clk_sel: 2;
		uint32_t reserved_31: 1;
	};
	uint32_t val;
} lcd_cam_cam_ctrl_reg_t;

typedef union {
	struct {
		uint32_t cam_rec_data_bytelen: 16;
		uint32_t cam_line_int_num: 6;
		uint32_t cam_clk_inv: 1;
		uint32_t cam_vsync_filter_en: 1;
		uint32_t cam_2byte_en: 1;
		uint32_t cam_de_inv: 1;
		uint32_t cam_hsync_inv: 1;
		uint32_t cam_vsync_inv: 1;
		uint32_t cam_vh_de_mode_en: 1;
		uint32_t cam_start: 1;
		uint32_t cam_reset: 1;
		uint32_t cam_afifo_reset: 1;
	};
	uint32_t val;
} lcd_cam_cam_ctrl1_reg_t;

typedef union {
	struct {
		uint32_t reserved_0: 21;
		uint32_t cam_conv_8bits_data_inv: 1;
		uint32_t cam_conv_yuv2yuv_mode: 2;
		uint32_t cam_conv_yuv_mode: 2;
		uint32_t cam_conv_protocol_mode: 1;
		uint32_t cam_conv_data_out_mode: 1;
		uint32_t cam_conv_data_in_mode: 1;
		uint32_t cam_conv_mode_8bits_on: 1;
		uint32_t cam_conv_trans_mode: 1;
		uint32_t cam_conv_bypass: 1;
	};
	uint32_t val;
} lcd_cam_cam_rgb_yuv_reg_t;


typedef union {
	struct {
		uint32_t lcd_vsync_int_ena: 1;
		uint32_t lcd_trans_done_int_ena: 1;
		uint32_t cam_vsync_int_ena: 1;
		uint32_t cam_hs_int_ena: 1;
		uint32_t reserved_4: 28;
	};
	uint32_t val;
} lcd_cam_lc_dma_int_ena_reg_t;

typedef union {
	struct {
		uint32_t lcd_vsync_int_raw: 1;
		uint32_t lcd_trans_done_int_raw: 1;
		uint32_t cam_vsync_int_raw: 1;
		uint32_t cam_hs_int_raw: 1;
		uint32_t reserved_4: 28;
	};
	uint32_t val;
} lcd_cam_lc_dma_int_raw_reg_t;

typedef union {
	struct {
		uint32_t lcd_vsync_int_st: 1;
		uint32_t lcd_trans_done_int_st: 1;
		uint32_t cam_vsync_int_st: 1;
		uint32_t cam_hs_int_st: 1;
		uint32_t reserved_4: 28;
	};
	uint32_t val;
} lcd_cam_lc_dma_int_st_reg_t;

typedef union {
	struct {
		uint32_t lcd_vsync_int_clr: 1;
		uint32_t lcd_trans_done_int_clr: 1;
		uint32_t cam_vsync_int_clr: 1;
		uint32_t cam_hs_int_clr: 1;
		uint32_t reserved_4: 28;
	};
	uint32_t val;
} lcd_cam_lc_dma_int_clr_reg_t;


typedef union {
	struct {
		uint32_t lc_date: 28;
		uint32_t reserved_28: 4;
	};
	uint32_t val;
} lcd_cam_lc_reg_date_reg_t;


typedef struct lcd_cam_dev_t {
	volatile lcd_cam_lcd_clock_reg_t lcd_clock;
	volatile lcd_cam_cam_ctrl_reg_t cam_ctrl;
	volatile lcd_cam_cam_ctrl1_reg_t cam_ctrl1;
	volatile lcd_cam_cam_rgb_yuv_reg_t cam_rgb_yuv;
	volatile lcd_cam_lcd_rgb_yuv_reg_t lcd_rgb_yuv;
	volatile lcd_cam_lcd_user_reg_t lcd_user;
	volatile lcd_cam_lcd_misc_reg_t lcd_misc;
	volatile lcd_cam_lcd_ctrl_reg_t lcd_ctrl;
	volatile lcd_cam_lcd_ctrl1_reg_t lcd_ctrl1;
	volatile lcd_cam_lcd_ctrl2_reg_t lcd_ctrl2;
	volatile lcd_cam_lcd_cmd_val_reg_t lcd_cmd_val;
	uint32_t reserved_02c;
	volatile lcd_cam_lcd_dly_mode_reg_t lcd_dly_mode;
	uint32_t reserved_034;
	volatile lcd_cam_lcd_data_dout_mode_reg_t lcd_data_dout_mode;
	uint32_t reserved_03c[10];
	volatile lcd_cam_lc_dma_int_ena_reg_t lc_dma_int_ena;
	volatile lcd_cam_lc_dma_int_raw_reg_t lc_dma_int_raw;
	volatile lcd_cam_lc_dma_int_st_reg_t lc_dma_int_st;
	volatile lcd_cam_lc_dma_int_clr_reg_t lc_dma_int_clr;
	uint32_t reserved_074[34];
	volatile lcd_cam_lc_reg_date_reg_t lc_reg_date;
} lcd_cam_dev_t;

void lcd_ll_enable_clock(lcd_cam_dev_t *dev, bool en);
void lcd_ll_select_clk_src(lcd_cam_dev_t *dev, lcd_clock_source_t src);
void lcd_ll_set_group_clock_coeff(lcd_cam_dev_t *dev, int div_num, int div_a, int div_b);
void lcd_ll_set_clock_idle_level(lcd_cam_dev_t *dev, bool level);
void lcd_ll_set_pixel_clock_edge(lcd_cam_dev_t *dev, bool active_on_neg);
void lcd_ll_set_pixel_clock_prescale(lcd_cam_dev_t *dev, uint32_t prescale);
void lcd_ll_enable_rgb_yuv_convert(lcd_cam_dev_t *dev, bool en);
void lcd_ll_set_convert_data_width(lcd_cam_dev_t *dev, uint32_t width);
void lcd_ll_set_input_color_range(lcd_cam_dev_t *dev, lcd_color_range_t range);
void lcd_ll_set_output_color_range(lcd_cam_dev_t *dev, lcd_color_range_t range);
void lcd_ll_set_yuv_convert_std(lcd_cam_dev_t *dev, lcd_yuv_conv_std_t std);
void lcd_ll_set_convert_mode_rgb_to_yuv(lcd_cam_dev_t *dev, lcd_yuv_sample_t yuv_sample);
void lcd_ll_set_convert_mode_yuv_to_rgb(lcd_cam_dev_t *dev, lcd_yuv_sample_t yuv_sample);
void lcd_ll_set_convert_mode_yuv_to_yuv(lcd_cam_dev_t *dev, lcd_yuv_sample_t src_sample, lcd_yuv_sample_t dst_sample);
void lcd_ll_set_phase_cycles(lcd_cam_dev_t *dev, uint32_t cmd_cycles, uint32_t dummy_cycles, uint32_t data_cycles);
void lcd_ll_set_blank_cycles(lcd_cam_dev_t *dev, uint32_t fk_cycles, uint32_t bk_cycles);
void lcd_ll_set_data_width(lcd_cam_dev_t *dev, uint32_t width);
void lcd_ll_enable_output_always_on(lcd_cam_dev_t *dev, bool en);
void lcd_ll_start(lcd_cam_dev_t *dev);
void lcd_ll_stop(lcd_cam_dev_t *dev);
void lcd_ll_reset(lcd_cam_dev_t *dev);
void lcd_ll_reverse_bit_order(lcd_cam_dev_t *dev, bool en);
void lcd_ll_swap_byte_order(lcd_cam_dev_t *dev, uint32_t width, bool en);
void lcd_ll_fifo_reset(lcd_cam_dev_t *dev);
void lcd_ll_set_dc_level(lcd_cam_dev_t *dev, bool idle_phase, bool cmd_phase, bool dummy_phase, bool data_phase);
void lcd_ll_set_dc_delay_ticks(lcd_cam_dev_t *dev, uint32_t delay);
void lcd_ll_set_command(lcd_cam_dev_t *dev, uint32_t data_width, uint32_t command);
void lcd_ll_enable_rgb_mode(lcd_cam_dev_t *dev, bool en);
void lcd_ll_enable_auto_next_frame(lcd_cam_dev_t *dev, bool en);
void lcd_ll_enable_output_hsync_in_porch_region(lcd_cam_dev_t *dev, bool en);
void lcd_ll_set_hsync_position(lcd_cam_dev_t *dev, uint32_t offset_in_line);
void lcd_ll_set_horizontal_timing(lcd_cam_dev_t *dev, uint32_t hsw, uint32_t hbp, uint32_t active_width, uint32_t hfp);
void lcd_ll_set_vertical_timing(lcd_cam_dev_t *dev, uint32_t vsw, uint32_t vbp, uint32_t active_height, uint32_t vfp);
void lcd_ll_set_idle_level(lcd_cam_dev_t *dev, bool hsync_idle_level, bool vsync_idle_level, bool de_idle_level);
void lcd_ll_set_delay_ticks(lcd_cam_dev_t *dev, uint32_t hsync_delay, uint32_t vsync_delay, uint32_t de_delay);
void lcd_ll_set_data_delay_ticks(lcd_cam_dev_t *dev, uint32_t delay);
void lcd_ll_enable_interrupt(lcd_cam_dev_t *dev, uint32_t mask, bool en);
uint32_t lcd_ll_get_interrupt_status(lcd_cam_dev_t *dev);
void lcd_ll_clear_interrupt_status(lcd_cam_dev_t *dev, uint32_t mask);
volatile void *lcd_ll_get_interrupt_status_reg(lcd_cam_dev_t *dev);
