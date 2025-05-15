#include <stdint.h>
#include <stdbool.h>

#define GPIO_REG_READ(reg)              (*(volatile uint32_t *)(reg))
#define GPIO_REG_WRITE(reg, val)        ((*((volatile uint32_t *)(reg))) = (uint32_t)(val))
#define GPIO_ID_PIN0                    0
#define GPIO_ID_PIN(n)                  (GPIO_ID_PIN0+(n))
#define GPIO_PIN_ADDR(i)                ((0x60004000 + 0x74) + i*4)

#define GPIO_FUNC_IN_HIGH               0x38
#define GPIO_FUNC_IN_LOW                0x3C

#define GPIO_ID_IS_PIN_REGISTER(reg_id) \
    ((reg_id >= GPIO_ID_PIN0) && (reg_id <= GPIO_ID_PIN(GPIO_PIN_COUNT-1)))

#define GPIO_REGID_TO_PINIDX(reg_id) ((reg_id) - GPIO_ID_PIN0)

typedef enum {
    GPIO_PIN_INTR_DISABLE = 0,
    GPIO_PIN_INTR_POSEDGE = 1,
    GPIO_PIN_INTR_NEGEDGE = 2,
    GPIO_PIN_INTR_ANYEDGE = 3,
    GPIO_PIN_INTR_LOLEVEL = 4,
    GPIO_PIN_INTR_HILEVEL = 5
} GPIO_INT_TYPE;

#define GPIO_OUTPUT_SET(k, v) ((k < 32) ? gpio_output_set(v<<k, (v ? 0 : 1)<<k, 1<<k,0) : \
                         gpio_output_set_high(v<<(k - 32), (v ? 0 : 1)<<(k - 32), 1<<(k -32),0))

#define GPIO_DIS_OUTPUT(k)    ((k < 32) ? gpio_output_set(0,0,0, 1<<k) : gpio_output_set_high(0,0,0, 1<<(k - 32)))
#define GPIO_INPUT_GET(k)     ((k < 32) ? ((gpio_input_get()>>k)&0x1) : ((gpio_input_get_high()>>(k - 32))&0x1))

typedef void (* gpio_intr_handler_fn_t)(uint32_t intr_mask, bool high, void *arg);

void gpio_init(void);
void gpio_output_set(uint32_t set_mask, uint32_t clear_mask, uint32_t enable_mask, uint32_t disable_mask);
void gpio_output_set_high(uint32_t set_mask, uint32_t clear_mask, uint32_t enable_mask, uint32_t disable_mask);
uint32_t gpio_input_get(void);
uint32_t gpio_input_get_high(void);
void gpio_intr_handler_register(gpio_intr_handler_fn_t fn, void *arg);
uint32_t gpio_intr_pending(void);
uint32_t gpio_intr_pending_high(void);
void gpio_intr_ack(uint32_t ack_mask);
void gpio_intr_ack_high(uint32_t ack_mask);
void gpio_pin_wakeup_enable(uint32_t i, GPIO_INT_TYPE intr_state);
void gpio_pin_wakeup_disable(void);
void gpio_matrix_in(uint32_t gpio, uint32_t signal_idx, bool inv);
void gpio_matrix_out(uint32_t gpio, uint32_t signal_idx, bool out_inv, bool oen_inv);
void gpio_pad_select_gpio(uint32_t gpio_num);
void gpio_pad_set_drv(uint32_t gpio_num, uint32_t drv);
void gpio_pad_pullup(uint32_t gpio_num);
void gpio_pad_pulldown(uint32_t gpio_num);
void gpio_pad_unhold(uint32_t gpio_num);
void gpio_pad_hold(uint32_t gpio_num);
void gpio_pad_input_enable(uint32_t gpio_num);
