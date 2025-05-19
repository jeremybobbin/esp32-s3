#pragma once

#include <stdint.h>
#include <stdbool.h>
#include "soc/soc_caps.h"
#include "soc/gdma_struct.h"
#include "soc/gdma_reg.h"

#ifdef __cplusplus
extern "C" {
#endif

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

static inline void gdma_ll_enable_m2m_mode(gdma_dev_t *dev, uint32_t channel, bool enable)
{
	dev->channel[channel].in.conf0.mem_trans_en = enable;
	if (enable) {
		// to enable m2m mode, the tx chan has to be the same to rx chan, and set to a valid value
		dev->channel[channel].in.peri_sel.sel = 0;
		dev->channel[channel].out.peri_sel.sel = 0;
	}
}

static inline void gdma_ll_enable_clock(gdma_dev_t *dev, bool enable)
{
	dev->misc_conf.clk_en = enable;
}

///////////////////////////////////// RX /////////////////////////////////////////
__attribute__((always_inline))
static inline uint32_t gdma_ll_rx_get_interrupt_status(gdma_dev_t *dev, uint32_t channel)
{
	return dev->channel[channel].in.int_st.val;
}

static inline void gdma_ll_rx_enable_interrupt(gdma_dev_t *dev, uint32_t channel, uint32_t mask, bool enable)
{
	if (enable) {
		dev->channel[channel].in.int_ena.val |= mask;
	} else {
		dev->channel[channel].in.int_ena.val &= ~mask;
	}
}

__attribute__((always_inline))
static inline void gdma_ll_rx_clear_interrupt_status(gdma_dev_t *dev, uint32_t channel, uint32_t mask)
{
	dev->channel[channel].in.int_clr.val = mask;
}

static inline volatile void *gdma_ll_rx_get_interrupt_status_reg(gdma_dev_t *dev, uint32_t channel)
{
	return (volatile void *)(&dev->channel[channel].in.int_st);
}

static inline void gdma_ll_rx_enable_owner_check(gdma_dev_t *dev, uint32_t channel, bool enable)
{
	dev->channel[channel].in.conf1.in_check_owner = enable;
}

static inline void gdma_ll_rx_enable_data_burst(gdma_dev_t *dev, uint32_t channel, bool enable)
{
	dev->channel[channel].in.conf0.in_data_burst_en = enable;
}

static inline void gdma_ll_rx_enable_descriptor_burst(gdma_dev_t *dev, uint32_t channel, bool enable)
{
	dev->channel[channel].in.conf0.indscr_burst_en = enable;
}

__attribute__((always_inline))
static inline void gdma_ll_rx_reset_channel(gdma_dev_t *dev, uint32_t channel)
{
	dev->channel[channel].in.conf0.in_rst = 1;
	dev->channel[channel].in.conf0.in_rst = 0;
}

static inline void gdma_ll_rx_set_block_size_psram(gdma_dev_t *dev, uint32_t channel, uint32_t size_index)
{
	dev->channel[channel].in.conf1.in_ext_mem_bk_size = size_index;
}

static inline void gdma_ll_rx_set_water_mark(gdma_dev_t *dev, uint32_t channel, uint32_t water_mark)
{
	dev->channel[channel].in.conf1.dma_infifo_full_thrs = water_mark;
}

static inline bool gdma_ll_rx_is_fifo_full(gdma_dev_t *dev, uint32_t channel, uint32_t fifo_level)
{
	return dev->channel[channel].in.infifo_status.val & (1 << 2 * (fifo_level - 1));
}

static inline bool gdma_ll_rx_is_fifo_empty(gdma_dev_t *dev, uint32_t channel, uint32_t fifo_level)
{
	return dev->channel[channel].in.infifo_status.val & (1 << (2 * (fifo_level - 1) + 1));
}

static inline uint32_t gdma_ll_rx_get_fifo_bytes(gdma_dev_t *dev, uint32_t channel, uint32_t fifo_level)
{
	switch (fifo_level) {
	case 1:
		return dev->channel[channel].in.infifo_status.infifo_cnt_l1;
	case 2:
		return dev->channel[channel].in.infifo_status.infifo_cnt_l2;
	case 3:
		return dev->channel[channel].in.infifo_status.infifo_cnt_l3;
	}
}

static inline uint32_t gdma_ll_rx_pop_data(gdma_dev_t *dev, uint32_t channel)
{
	dev->channel[channel].in.pop.infifo_pop = 1;
	return dev->channel[channel].in.pop.infifo_rdata;
}

__attribute__((always_inline))
static inline void gdma_ll_rx_set_desc_addr(gdma_dev_t *dev, uint32_t channel, uint32_t addr)
{
	dev->channel[channel].in.link.addr = addr;
}

__attribute__((always_inline))
static inline void gdma_ll_rx_start(gdma_dev_t *dev, uint32_t channel)
{
	dev->channel[channel].in.link.start = 1;
}

__attribute__((always_inline))
static inline void gdma_ll_rx_stop(gdma_dev_t *dev, uint32_t channel)
{
	dev->channel[channel].in.link.stop = 1;
}

__attribute__((always_inline))
static inline void gdma_ll_rx_restart(gdma_dev_t *dev, uint32_t channel)
{
	dev->channel[channel].in.link.restart = 1;
}

static inline void gdma_ll_rx_enable_auto_return(gdma_dev_t *dev, uint32_t channel, bool enable)
{
	dev->channel[channel].in.link.auto_ret = enable;
}

static inline bool gdma_ll_rx_is_fsm_idle(gdma_dev_t *dev, uint32_t channel)
{
	return dev->channel[channel].in.link.park;
}

__attribute__((always_inline))
static inline uint32_t gdma_ll_rx_get_success_eof_desc_addr(gdma_dev_t *dev, uint32_t channel)
{
	return dev->channel[channel].in.suc_eof_des_addr;
}

__attribute__((always_inline))
static inline uint32_t gdma_ll_rx_get_error_eof_desc_addr(gdma_dev_t *dev, uint32_t channel)
{
	return dev->channel[channel].in.err_eof_des_addr;
}

__attribute__((always_inline))
static inline uint32_t gdma_ll_rx_get_current_desc_addr(gdma_dev_t *dev, uint32_t channel)
{
	return dev->channel[channel].in.dscr;
}

static inline void gdma_ll_rx_set_weight(gdma_dev_t *dev, uint32_t channel, uint32_t weight)
{
	dev->channel[channel].in.wight.rx_weight = weight;
}

static inline void gdma_ll_rx_set_priority(gdma_dev_t *dev, uint32_t channel, uint32_t prio)
{
	dev->channel[channel].in.pri.rx_pri = prio;
}

static inline void gdma_ll_rx_connect_to_periph(gdma_dev_t *dev, uint32_t channel, int periph_id)
{
	dev->channel[channel].in.peri_sel.sel = periph_id;
}

///////////////////////////////////// TX /////////////////////////////////////////
__attribute__((always_inline))
static inline uint32_t gdma_ll_tx_get_interrupt_status(gdma_dev_t *dev, uint32_t channel)
{
	return dev->channel[channel].out.int_st.val;
}

static inline void gdma_ll_tx_enable_interrupt(gdma_dev_t *dev, uint32_t channel, uint32_t mask, bool enable)
{
	if (enable) {
		dev->channel[channel].out.int_ena.val |= mask;
	} else {
		dev->channel[channel].out.int_ena.val &= ~mask;
	}
}

__attribute__((always_inline))
static inline void gdma_ll_tx_clear_interrupt_status(gdma_dev_t *dev, uint32_t channel, uint32_t mask)
{
	dev->channel[channel].out.int_clr.val = mask;
}

static inline volatile void *gdma_ll_tx_get_interrupt_status_reg(gdma_dev_t *dev, uint32_t channel)
{
	return (volatile void *)(&dev->channel[channel].out.int_st);
}

static inline void gdma_ll_tx_enable_owner_check(gdma_dev_t *dev, uint32_t channel, bool enable)
{
	dev->channel[channel].out.conf1.out_check_owner = enable;
}

static inline void gdma_ll_tx_enable_data_burst(gdma_dev_t *dev, uint32_t channel, bool enable)
{
	dev->channel[channel].out.conf0.out_data_burst_en = enable;
}

static inline void gdma_ll_tx_enable_descriptor_burst(gdma_dev_t *dev, uint32_t channel, bool enable)
{
	dev->channel[channel].out.conf0.outdscr_burst_en = enable;
}

static inline void gdma_ll_tx_set_eof_mode(gdma_dev_t *dev, uint32_t channel, uint32_t mode)
{
	dev->channel[channel].out.conf0.out_eof_mode = mode;
}

static inline void gdma_ll_tx_enable_auto_write_back(gdma_dev_t *dev, uint32_t channel, bool enable)
{
	dev->channel[channel].out.conf0.out_auto_wrback = enable;
}

__attribute__((always_inline))
static inline void gdma_ll_tx_reset_channel(gdma_dev_t *dev, uint32_t channel)
{
	dev->channel[channel].out.conf0.out_rst = 1;
	dev->channel[channel].out.conf0.out_rst = 0;
}

static inline void gdma_ll_tx_set_block_size_psram(gdma_dev_t *dev, uint32_t channel, uint32_t size_index)
{
	dev->channel[channel].out.conf1.out_ext_mem_bk_size = size_index;
}

static inline bool gdma_ll_tx_is_fifo_full(gdma_dev_t *dev, uint32_t channel, uint32_t fifo_level)
{
	return dev->channel[channel].out.outfifo_status.val & (1 << 2 * (fifo_level - 1));
}

static inline bool gdma_ll_tx_is_fifo_empty(gdma_dev_t *dev, uint32_t channel, uint32_t fifo_level)
{
	return dev->channel[channel].out.outfifo_status.val & (1 << (2 * (fifo_level - 1) + 1));
}

static inline uint32_t gdma_ll_tx_get_fifo_bytes(gdma_dev_t *dev, uint32_t channel, uint32_t fifo_level)
{
	switch (fifo_level) {
	case 1:
		return dev->channel[channel].out.outfifo_status.outfifo_cnt_l1;
	case 2:
		return dev->channel[channel].out.outfifo_status.outfifo_cnt_l2;
	case 3:
		return dev->channel[channel].out.outfifo_status.outfifo_cnt_l3;
	}
}

static inline void gdma_ll_tx_push_data(gdma_dev_t *dev, uint32_t channel, uint32_t data)
{
	dev->channel[channel].out.push.outfifo_wdata = data;
	dev->channel[channel].out.push.outfifo_push = 1;
}

__attribute__((always_inline))
static inline void gdma_ll_tx_set_desc_addr(gdma_dev_t *dev, uint32_t channel, uint32_t addr)
{
	dev->channel[channel].out.link.addr = addr;
}

__attribute__((always_inline))
static inline void gdma_ll_tx_start(gdma_dev_t *dev, uint32_t channel)
{
	dev->channel[channel].out.link.start = 1;
}

__attribute__((always_inline))
static inline void gdma_ll_tx_stop(gdma_dev_t *dev, uint32_t channel)
{
	dev->channel[channel].out.link.stop = 1;
}

__attribute__((always_inline))
static inline void gdma_ll_tx_restart(gdma_dev_t *dev, uint32_t channel)
{
	dev->channel[channel].out.link.restart = 1;
}

static inline bool gdma_ll_tx_is_fsm_idle(gdma_dev_t *dev, uint32_t channel)
{
	return dev->channel[channel].out.link.park;
}

__attribute__((always_inline))
static inline uint32_t gdma_ll_tx_get_eof_desc_addr(gdma_dev_t *dev, uint32_t channel)
{
	return dev->channel[channel].out.eof_des_addr;
}

__attribute__((always_inline))
static inline uint32_t gdma_ll_tx_get_current_desc_addr(gdma_dev_t *dev, uint32_t channel)
{
	return dev->channel[channel].out.dscr;
}

static inline void gdma_ll_tx_set_weight(gdma_dev_t *dev, uint32_t channel, uint32_t weight)
{
	dev->channel[channel].out.wight.tx_weight = weight;
}

static inline void gdma_ll_tx_set_priority(gdma_dev_t *dev, uint32_t channel, uint32_t prio)
{
	dev->channel[channel].out.pri.tx_pri = prio;
}

static inline void gdma_ll_tx_connect_to_periph(gdma_dev_t *dev, uint32_t channel, int periph_id)
{
	dev->channel[channel].out.peri_sel.sel = periph_id;
}

#ifdef __cplusplus
}
#endif
