#include <stddef.h> /* For NULL declaration */
#include <stdint.h>
#include <stdbool.h>
#include "hal/misc.h"
#include "soc/lcd_cam_reg.h"
#include "soc/lcd_cam_struct.h"
#include "hal/assert.h"
#include "hal/lcd_types.h"

#define LCD_LL_GET_HW(id) (((id) == 0) ? (&LCD_CAM) : NULL)

#define LCD_LL_EVENT_VSYNC_END  (1 << 0)
#define LCD_LL_EVENT_TRANS_DONE (1 << 1)

#define LCD_LL_CLK_FRAC_DIV_N_MAX  256 // LCD_CLK = LCD_CLK_S / (N + b/a), the N register is 8 bit-width
#define LCD_LL_CLK_FRAC_DIV_AB_MAX 64  // LCD_CLK = LCD_CLK_S / (N + b/a), the a/b register is 6 bit-width
#define LCD_LL_PCLK_DIV_MAX        64  // LCD_PCLK = LCD_CLK / MO, the MO register is 6 bit-width

#define LCD_LL_COLOR_RANGE_TO_REG(range) (uint8_t[]){0,1}[(range)]
#define LCD_LL_CONV_STD_TO_REG(std)      (uint8_t[]){0,1}[(std)]
#define LCD_LL_YUV_SAMPLE_TO_REG(sample) (uint8_t[]){0,1,2}[(sample)]

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
