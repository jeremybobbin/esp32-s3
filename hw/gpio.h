#include <stdbool.h>

#define GPIO_LL_GET_HW(num) (((num) == 0) ? (&GPIO) : NULL)

#define GPIO_LL_INTR_ENA      (1<<0)
#define GPIO_LL_NMI_INTR_ENA  (1<<1)

void gpio_ll_pullup_en(gpio_dev_t *hw, gpio_num_t gpio_num);
void gpio_ll_pullup_dis(gpio_dev_t *hw, gpio_num_t gpio_num);
void gpio_ll_pulldown_en(gpio_dev_t *hw, gpio_num_t gpio_num);
void gpio_ll_pulldown_dis(gpio_dev_t *hw, gpio_num_t gpio_num);
void gpio_ll_set_intr_type(gpio_dev_t *hw, gpio_num_t gpio_num, gpio_int_type_t intr_type);
void gpio_ll_get_intr_status(gpio_dev_t *hw, uint32_t core_id, uint32_t *status);
void gpio_ll_get_intr_status_high(gpio_dev_t *hw, uint32_t core_id, uint32_t *status);
void gpio_ll_clear_intr_status(gpio_dev_t *hw, uint32_t mask);
void gpio_ll_clear_intr_status_high(gpio_dev_t *hw, uint32_t mask);
void gpio_ll_intr_enable_on_core(gpio_dev_t *hw, uint32_t core_id, gpio_num_t gpio_num);
void gpio_ll_intr_disable(gpio_dev_t *hw, gpio_num_t gpio_num);
void gpio_ll_input_disable(gpio_dev_t *hw, gpio_num_t gpio_num);
void gpio_ll_input_enable(gpio_dev_t *hw, gpio_num_t gpio_num);
void gpio_ll_output_disable(gpio_dev_t *hw, gpio_num_t gpio_num);
void gpio_ll_output_enable(gpio_dev_t *hw, gpio_num_t gpio_num);
void gpio_ll_od_disable(gpio_dev_t *hw, gpio_num_t gpio_num);
void gpio_ll_od_enable(gpio_dev_t *hw, gpio_num_t gpio_num);
void gpio_ll_set_level(gpio_dev_t *hw, gpio_num_t gpio_num, uint32_t level);
int gpio_ll_get_level(gpio_dev_t *hw, gpio_num_t gpio_num);
void gpio_ll_wakeup_enable(gpio_dev_t *hw, gpio_num_t gpio_num, gpio_int_type_t intr_type);
void gpio_ll_wakeup_disable(gpio_dev_t *hw, gpio_num_t gpio_num);
void gpio_ll_set_drive_capability(gpio_dev_t *hw, gpio_num_t gpio_num, gpio_drive_cap_t strength);
void gpio_ll_get_drive_capability(gpio_dev_t *hw, gpio_num_t gpio_num, gpio_drive_cap_t *strength);
void gpio_ll_deep_sleep_hold_en(gpio_dev_t *hw);
void gpio_ll_deep_sleep_hold_dis(gpio_dev_t *hw);
bool gpio_ll_deep_sleep_hold_is_en(gpio_dev_t *hw);
void gpio_ll_hold_en(gpio_dev_t *hw, gpio_num_t gpio_num);
void gpio_ll_hold_dis(gpio_dev_t *hw, gpio_num_t gpio_num);
bool gpio_ll_is_digital_io_hold(gpio_dev_t *hw, uint32_t gpio_num);
void gpio_ll_iomux_in(gpio_dev_t *hw, uint32_t gpio, uint32_t signal_idx);
void gpio_ll_iomux_out(gpio_dev_t *hw, uint8_t gpio_num, int func, uint32_t oen_inv);
void gpio_ll_force_hold_all(gpio_dev_t *hw);
void gpio_ll_force_unhold_all(void);
void gpio_ll_sleep_sel_en(gpio_dev_t *hw, gpio_num_t gpio_num);
void gpio_ll_sleep_sel_dis(gpio_dev_t *hw, gpio_num_t gpio_num);
void gpio_ll_sleep_pullup_dis(gpio_dev_t *hw, gpio_num_t gpio_num);
void gpio_ll_sleep_pullup_en(gpio_dev_t *hw, gpio_num_t gpio_num);
void gpio_ll_sleep_pulldown_en(gpio_dev_t *hw, gpio_num_t gpio_num);
void gpio_ll_sleep_pulldown_dis(gpio_dev_t *hw, gpio_num_t gpio_num);
void gpio_ll_sleep_input_disable(gpio_dev_t *hw, gpio_num_t gpio_num);
void gpio_ll_sleep_input_enable(gpio_dev_t *hw, gpio_num_t gpio_num);
void gpio_ll_sleep_output_disable(gpio_dev_t *hw, gpio_num_t gpio_num);
void gpio_ll_sleep_output_enable(gpio_dev_t *hw, gpio_num_t gpio_num);
