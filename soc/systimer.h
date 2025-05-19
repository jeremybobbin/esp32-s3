#include <stdint.h>
#include <stdbool.h>

#define SYSTIMER_LL_COUNTER_CLOCK       (0) // Counter used for "wallclock" time
#define SYSTIMER_LL_COUNTER_OS_TICK     (1) // Counter used for OS tick
#define SYSTIMER_LL_ALARM_OS_TICK_CORE0 (0) // Alarm used for OS tick of CPU core 0
#define SYSTIMER_LL_ALARM_OS_TICK_CORE1 (1) // Alarm used for OS tick of CPU core 1
#define SYSTIMER_LL_ALARM_CLOCK         (2) // Alarm used for "wallclock" time

#define SYSTIMER_LL_TICKS_PER_US        (16) // 16 systimer ticks == 1us

void systimer_ll_enable_clock(systimer_dev_t *dev, bool en);
void systimer_ll_enable_counter(systimer_dev_t *dev, uint32_t counter_id, bool en);
void systimer_ll_counter_can_stall_by_cpu(systimer_dev_t *dev, uint32_t counter_id, uint32_t cpu_id, bool can);
void systimer_ll_counter_snapshot(systimer_dev_t *dev, uint32_t counter_id);
bool systimer_ll_is_counter_value_valid(systimer_dev_t *dev, uint32_t counter_id);
void systimer_ll_set_counter_value(systimer_dev_t *dev, uint32_t counter_id, uint64_t value);
uint32_t systimer_ll_get_counter_value_low(systimer_dev_t *dev, uint32_t counter_id);
uint32_t systimer_ll_get_counter_value_high(systimer_dev_t *dev, uint32_t counter_id);
void systimer_ll_apply_counter_value(systimer_dev_t *dev, uint32_t counter_id);
void systimer_ll_set_alarm_target(systimer_dev_t *dev, uint32_t alarm_id, uint64_t value);
uint64_t systimer_ll_get_alarm_target(systimer_dev_t *dev, uint32_t alarm_id);
void systimer_ll_connect_alarm_counter(systimer_dev_t *dev, uint32_t alarm_id, uint32_t counter_id);
void systimer_ll_enable_alarm_oneshot(systimer_dev_t *dev, uint32_t alarm_id);
void systimer_ll_enable_alarm_period(systimer_dev_t *dev, uint32_t alarm_id);
void systimer_ll_set_alarm_period(systimer_dev_t *dev, uint32_t alarm_id, uint32_t period);
uint32_t systimer_ll_get_alarm_period(systimer_dev_t *dev, uint32_t alarm_id);
void systimer_ll_apply_alarm_value(systimer_dev_t *dev, uint32_t alarm_id);
void systimer_ll_enable_alarm(systimer_dev_t *dev, uint32_t alarm_id, bool en);
void systimer_ll_enable_alarm_int(systimer_dev_t *dev, uint32_t alarm_id, bool en);
bool systimer_ll_is_alarm_int_fired(systimer_dev_t *dev, uint32_t alarm_id);
void systimer_ll_clear_alarm_int(systimer_dev_t *dev, uint32_t alarm_id);
