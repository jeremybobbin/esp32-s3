#include <stdlib.h>
#include "soc/rtc_io_periph.h"
#include "soc/rtc_io_struct.h"
#include "hal/rtc_io_types.h"
#include "hal/gpio_types.h"
#include "soc/io_mux_reg.h"
#include "soc/usb_serial_jtag_reg.h"
#include "soc/usb_serial_jtag_struct.h"

#define RTCIO_LL_PIN_FUNC     0

typedef enum {
	RTCIO_FUNC_RTC = 0x0,		  /*!< The pin controled by RTC module. */
	RTCIO_FUNC_DIGITAL = 0x1,	  /*!< The pin controlled by DIGITAL module. */
} rtcio_ll_func_t;

typedef enum {
	RTCIO_WAKEUP_DISABLE	= 0,	/*!< Disable GPIO interrupt */
	RTCIO_WAKEUP_LOW_LEVEL	= 0x4,	/*!< GPIO interrupt type : input low level trigger */
	RTCIO_WAKEUP_HIGH_LEVEL = 0x5,	/*!< GPIO interrupt type : input high level trigger */
} rtcio_ll_wake_type_t;

typedef enum {
	RTCIO_OUTPUT_NORMAL = 0,	/*!< RTCIO output mode is normal. */
	RTCIO_OUTPUT_OD = 0x1,		/*!< RTCIO output mode is open-drain. */
} rtcio_ll_out_mode_t;

void rtcio_ll_function_select(int rtcio_num, rtcio_ll_func_t func);
void rtcio_ll_output_enable(int rtcio_num);
void rtcio_ll_output_disable(int rtcio_num);
void rtcio_ll_set_level(int rtcio_num, uint32_t level);
void rtcio_ll_input_enable(int rtcio_num);
void rtcio_ll_input_disable(int rtcio_num);
uint32_t rtcio_ll_get_level(int rtcio_num);
void rtcio_ll_set_drive_capability(int rtcio_num, uint32_t strength);
uint32_t rtcio_ll_get_drive_capability(int rtcio_num);
void rtcio_ll_output_mode_set(int rtcio_num, rtcio_ll_out_mode_t mode);
void rtcio_ll_pullup_enable(int rtcio_num);
void rtcio_ll_pullup_disable(int rtcio_num);
void rtcio_ll_pulldown_enable(int rtcio_num);
void rtcio_ll_pulldown_disable(int rtcio_num);
void rtcio_ll_force_hold_enable(int rtcio_num);
void rtcio_ll_force_hold_disable(int rtcio_num);
void rtcio_ll_force_hold_all(void);
void rtcio_ll_force_unhold_all(void);
void rtcio_ll_wakeup_enable(int rtcio_num, rtcio_ll_wake_type_t type);
void rtcio_ll_wakeup_disable(int rtcio_num);
void rtcio_ll_enable_output_in_sleep(gpio_num_t gpio_num);
void rtcio_ll_in_sleep_disable_output(gpio_num_t gpio_num);
void rtcio_ll_in_sleep_enable_input(gpio_num_t gpio_num);
void rtcio_ll_in_sleep_disable_input(gpio_num_t gpio_num);
void rtcio_ll_enable_sleep_setting(gpio_num_t gpio_num);
void rtcio_ll_disable_sleep_setting(gpio_num_t gpio_num);
void rtcio_ll_ext0_set_wakeup_pin(int rtcio_num, int level);
