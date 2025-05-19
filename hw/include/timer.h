#include <stdlib.h>

typedef struct {
	timg_dev_t *dev;
	timer_idx_t idx;
} timer_ll_context_t;

#define TIMER_LL_GET_HW(num) ((num == 0) ? (&TIMERG0) : (&TIMERG1))

void timer_ll_set_divider(timg_dev_t *hw, timer_idx_t timer_num, uint32_t divider);
void timer_ll_get_divider(timg_dev_t *hw, timer_idx_t timer_num, uint32_t *divider);
void timer_ll_set_counter_value(timg_dev_t *hw, timer_idx_t timer_num, uint64_t load_val);
void timer_ll_get_counter_value(timg_dev_t *hw, timer_idx_t timer_num, uint64_t *timer_val)
void timer_ll_set_counter_increase(timg_dev_t *hw, timer_idx_t timer_num, bool increase_en);
bool timer_ll_get_counter_increase(timg_dev_t *hw, timer_idx_t timer_num);
void timer_ll_set_counter_enable(timg_dev_t *hw, timer_idx_t timer_num, bool counter_en)
bool timer_ll_get_counter_enable(timg_dev_t *hw, timer_idx_t timer_num);
void timer_ll_set_auto_reload(timg_dev_t *hw, timer_idx_t timer_num, bool auto_reload_en);
bool timer_ll_get_auto_reload(timg_dev_t *hw, timer_idx_t timer_num)
void timer_ll_set_alarm_value(timg_dev_t *hw, timer_idx_t timer_num, uint64_t alarm_value)
void timer_ll_get_alarm_value(timg_dev_t *hw, timer_idx_t timer_num, uint64_t *alarm_value);
void timer_ll_set_alarm_enable(timg_dev_t *hw, timer_idx_t timer_num, bool alarm_en)
bool timer_ll_get_alarm_enable(timg_dev_t *hw, timer_idx_t timer_num);
void timer_ll_intr_enable(timg_dev_t *hw, timer_idx_t timer_num)
void timer_ll_intr_disable(timg_dev_t *hw, timer_idx_t timer_num)
void timer_ll_clear_intr_status(timg_dev_t *hw, timer_idx_t timer_num)
void timer_ll_get_intr_status(timg_dev_t *hw, uint32_t *intr_status)
void timer_ll_get_intr_raw_status(timer_group_t group_num, uint32_t *intr_raw_status)
void timer_ll_set_level_int_enable(timg_dev_t *hw, timer_idx_t timer_num, bool level_int_en);
bool timer_ll_get_level_int_enable(timg_dev_t *hw, timer_idx_t timer_num);
void timer_ll_set_edge_int_enable(timg_dev_t *hw, timer_idx_t timer_num, bool edge_int_en);
bool timer_ll_get_edge_int_enable(timg_dev_t *hw, timer_idx_t timer_num);
uint32_t timer_ll_get_intr_status_reg(timg_dev_t *hw);
uint32_t timer_ll_get_intr_mask_bit(timg_dev_t *hw, timer_idx_t timer_num);
void timer_ll_set_use_xtal(timg_dev_t *hw, timer_idx_t timer_num, bool use_xtal_en);
bool timer_ll_get_use_xtal(timg_dev_t *hw, timer_idx_t timer_num);
