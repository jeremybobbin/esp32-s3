#include <stdint.h>
#include <stdbool.h>

#define GDMA_LL_GET_HW(id) (((id) == 0) ? (&GDMA) : NULL)

#define GDMA_LL_RX_EVENT_MASK        (0x3FF)
#define GDMA_LL_TX_EVENT_MASK        (0xFF)

#define GDMA_LL_EVENT_TX_L3_FIFO_UDF (1<<7)
#define GDMA_LL_EVENT_TX_L3_FIFO_OVF (1<<6)
#define GDMA_LL_EVENT_TX_L1_FIFO_UDF (1<<5)
#define GDMA_LL_EVENT_TX_L1_FIFO_OVF (1<<4)
#define GDMA_LL_EVENT_TX_TOTAL_EOF   (1<<3)
#define GDMA_LL_EVENT_TX_DESC_ERROR  (1<<2)
#define GDMA_LL_EVENT_TX_EOF         (1<<1)
#define GDMA_LL_EVENT_TX_DONE        (1<<0)

#define GDMA_LL_EVENT_RX_L3_FIFO_UDF (1<<9)
#define GDMA_LL_EVENT_RX_L3_FIFO_OVF (1<<8)
#define GDMA_LL_EVENT_RX_L1_FIFO_UDF (1<<7)
#define GDMA_LL_EVENT_RX_L1_FIFO_OVF (1<<6)
#define GDMA_LL_EVENT_RX_WATER_MARK  (1<<5)
#define GDMA_LL_EVENT_RX_DESC_EMPTY  (1<<4)
#define GDMA_LL_EVENT_RX_DESC_ERROR  (1<<3)
#define GDMA_LL_EVENT_RX_ERR_EOF     (1<<2)
#define GDMA_LL_EVENT_RX_SUC_EOF     (1<<1)
#define GDMA_LL_EVENT_RX_DONE        (1<<0)

#define GDMA_LL_L2FIFO_BASE_SIZE (16) // Basic size of GDMA Level 2 FIFO

#define GDMA_LL_EXT_MEM_BK_SIZE_16B (0)
#define GDMA_LL_EXT_MEM_BK_SIZE_32B (1)
#define GDMA_LL_EXT_MEM_BK_SIZE_64B (2)

void gdma_ll_enable_m2m_mode(gdma_dev_t *dev, uint32_t channel, bool enable);
void gdma_ll_enable_clock(gdma_dev_t *dev, bool enable);
uint32_t gdma_ll_rx_get_interrupt_status(gdma_dev_t *dev, uint32_t channel);
void gdma_ll_rx_enable_interrupt(gdma_dev_t *dev, uint32_t channel, uint32_t mask, bool enable);
void gdma_ll_rx_clear_interrupt_status(gdma_dev_t *dev, uint32_t channel, uint32_t mask);
volatile void *gdma_ll_rx_get_interrupt_status_reg(gdma_dev_t *dev, uint32_t channel);
void gdma_ll_rx_enable_owner_check(gdma_dev_t *dev, uint32_t channel, bool enable);
void gdma_ll_rx_enable_data_burst(gdma_dev_t *dev, uint32_t channel, bool enable);
void gdma_ll_rx_enable_descriptor_burst(gdma_dev_t *dev, uint32_t channel, bool enable);
void gdma_ll_rx_reset_channel(gdma_dev_t *dev, uint32_t channel);
void gdma_ll_rx_set_block_size_psram(gdma_dev_t *dev, uint32_t channel, uint32_t size_index);
void gdma_ll_rx_set_water_mark(gdma_dev_t *dev, uint32_t channel, uint32_t water_mark);
bool gdma_ll_rx_is_fifo_full(gdma_dev_t *dev, uint32_t channel, uint32_t fifo_level);
bool gdma_ll_rx_is_fifo_empty(gdma_dev_t *dev, uint32_t channel, uint32_t fifo_level);
uint32_t gdma_ll_rx_get_fifo_bytes(gdma_dev_t *dev, uint32_t channel, uint32_t fifo_level);
uint32_t gdma_ll_rx_pop_data(gdma_dev_t *dev, uint32_t channel);
void gdma_ll_rx_set_desc_addr(gdma_dev_t *dev, uint32_t channel, uint32_t addr);
void gdma_ll_rx_start(gdma_dev_t *dev, uint32_t channel);
void gdma_ll_rx_stop(gdma_dev_t *dev, uint32_t channel);
void gdma_ll_rx_restart(gdma_dev_t *dev, uint32_t channel);
void gdma_ll_rx_enable_auto_return(gdma_dev_t *dev, uint32_t channel, bool enable);
bool gdma_ll_rx_is_fsm_idle(gdma_dev_t *dev, uint32_t channel);
uint32_t gdma_ll_rx_get_success_eof_desc_addr(gdma_dev_t *dev, uint32_t channel);
uint32_t gdma_ll_rx_get_error_eof_desc_addr(gdma_dev_t *dev, uint32_t channel);
uint32_t gdma_ll_rx_get_current_desc_addr(gdma_dev_t *dev, uint32_t channel);
void gdma_ll_rx_set_weight(gdma_dev_t *dev, uint32_t channel, uint32_t weight);
void gdma_ll_rx_set_priority(gdma_dev_t *dev, uint32_t channel, uint32_t prio);
void gdma_ll_rx_connect_to_periph(gdma_dev_t *dev, uint32_t channel, int periph_id);
uint32_t gdma_ll_tx_get_interrupt_status(gdma_dev_t *dev, uint32_t channel);
void gdma_ll_tx_enable_interrupt(gdma_dev_t *dev, uint32_t channel, uint32_t mask, bool enable);
void gdma_ll_tx_clear_interrupt_status(gdma_dev_t *dev, uint32_t channel, uint32_t mask);
volatile void *gdma_ll_tx_get_interrupt_status_reg(gdma_dev_t *dev, uint32_t channel);
void gdma_ll_tx_enable_owner_check(gdma_dev_t *dev, uint32_t channel, bool enable);
void gdma_ll_tx_enable_data_burst(gdma_dev_t *dev, uint32_t channel, bool enable);
void gdma_ll_tx_enable_descriptor_burst(gdma_dev_t *dev, uint32_t channel, bool enable);
void gdma_ll_tx_set_eof_mode(gdma_dev_t *dev, uint32_t channel, uint32_t mode);
void gdma_ll_tx_enable_auto_write_back(gdma_dev_t *dev, uint32_t channel, bool enable);
void gdma_ll_tx_reset_channel(gdma_dev_t *dev, uint32_t channel);
void gdma_ll_tx_set_block_size_psram(gdma_dev_t *dev, uint32_t channel, uint32_t size_index);
bool gdma_ll_tx_is_fifo_full(gdma_dev_t *dev, uint32_t channel, uint32_t fifo_level);
bool gdma_ll_tx_is_fifo_empty(gdma_dev_t *dev, uint32_t channel, uint32_t fifo_level);
uint32_t gdma_ll_tx_get_fifo_bytes(gdma_dev_t *dev, uint32_t channel, uint32_t fifo_level);
void gdma_ll_tx_push_data(gdma_dev_t *dev, uint32_t channel, uint32_t data);
void gdma_ll_tx_set_desc_addr(gdma_dev_t *dev, uint32_t channel, uint32_t addr);
void gdma_ll_tx_start(gdma_dev_t *dev, uint32_t channel);
void gdma_ll_tx_stop(gdma_dev_t *dev, uint32_t channel);
void gdma_ll_tx_restart(gdma_dev_t *dev, uint32_t channel);
bool gdma_ll_tx_is_fsm_idle(gdma_dev_t *dev, uint32_t channel);
uint32_t gdma_ll_tx_get_eof_desc_addr(gdma_dev_t *dev, uint32_t channel);
uint32_t gdma_ll_tx_get_current_desc_addr(gdma_dev_t *dev, uint32_t channel);
void gdma_ll_tx_set_weight(gdma_dev_t *dev, uint32_t channel, uint32_t weight);
void gdma_ll_tx_set_priority(gdma_dev_t *dev, uint32_t channel, uint32_t prio);
void gdma_ll_tx_connect_to_periph(gdma_dev_t *dev, uint32_t channel, int periph_id);
