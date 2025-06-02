#include <stdint.h>
#include <stdbool.h>

typedef volatile struct gdma_dev_s {
	struct {
		struct {
			union {
				struct {
					uint32_t in_rst                        :    1;
					uint32_t in_loop_test                  :    1;
					uint32_t indscr_burst_en               :    1;
					uint32_t in_data_burst_en              :    1;
					uint32_t mem_trans_en                  :    1;
					uint32_t reserved5                     :    1;
					uint32_t reserved6                     :    26;
				};
				uint32_t val;
			} conf0;
			union {
				struct {
					uint32_t dma_infifo_full_thrs          :    12;
					uint32_t in_check_owner                :    1;
					uint32_t in_ext_mem_bk_size            :    2;
					uint32_t reserved15                    :    17;
				};
				uint32_t val;
			} conf1;
			union {
				struct {
					uint32_t in_done                       :    1;
					uint32_t in_suc_eof                    :    1;
					uint32_t in_err_eof                    :    1;
					uint32_t in_dscr_err                   :    1;
					uint32_t in_dscr_empty                 :    1;
					uint32_t infifo_full_wm                :    1;
					uint32_t infifo_ovf_l1                 :    1;
					uint32_t infifo_udf_l1                 :    1;
					uint32_t infifo_ovf_l3                 :    1;
					uint32_t infifo_udf_l3                 :    1;
					uint32_t reserved10                    :    22;
				};
				uint32_t val;
			} int_raw;
			union {
				struct {
					uint32_t in_done                       :    1;
					uint32_t in_suc_eof                    :    1;
					uint32_t in_err_eof                    :    1;
					uint32_t in_dscr_err                   :    1;
					uint32_t in_dscr_empty                 :    1;
					uint32_t infifo_full_wm                :    1;
					uint32_t infifo_ovf_l1                 :    1;
					uint32_t infifo_udf_l1                 :    1;
					uint32_t infifo_ovf_l3                 :    1;
					uint32_t infifo_udf_l3                 :    1;
					uint32_t reserved10                    :    22;
				};
				uint32_t val;
			} int_st;
			union {
				struct {
					uint32_t in_done                       :    1;
					uint32_t in_suc_eof                    :    1;
					uint32_t in_err_eof                    :    1;
					uint32_t in_dscr_err                   :    1;
					uint32_t in_dscr_empty                 :    1;
					uint32_t infifo_full_wm                :    1;
					uint32_t infifo_ovf_l1                 :    1;
					uint32_t infifo_udf_l1                 :    1;
					uint32_t infifo_ovf_l3                 :    1;
					uint32_t infifo_udf_l3                 :    1;
					uint32_t reserved10                    :    22;
				};
				uint32_t val;
			} int_ena;
			union {
				struct {
					uint32_t in_done                       :    1;
					uint32_t in_suc_eof                    :    1;
					uint32_t in_err_eof                    :    1;
					uint32_t in_dscr_err                   :    1;
					uint32_t in_dscr_empty                 :    1;
					uint32_t dma_infifo_full_wm            :    1;
					uint32_t infifo_ovf_l1                 :    1;
					uint32_t infifo_udf_l1                 :    1;
					uint32_t infifo_ovf_l3                 :    1;
					uint32_t infifo_udf_l3                 :    1;
					uint32_t reserved10                    :    22;
				};
				uint32_t val;
			} int_clr;
			union {
				struct {
					uint32_t infifo_full_l1                :    1;
					uint32_t infifo_empty_l1               :    1;
					uint32_t infifo_full_l2                :    1;
					uint32_t infifo_empty_l2               :    1;
					uint32_t infifo_full_l3                :    1;
					uint32_t infifo_empty_l3               :    1;
					uint32_t infifo_cnt_l1                 :    6;
					uint32_t infifo_cnt_l2                 :    7;
					uint32_t infifo_cnt_l3                 :    5;
					uint32_t in_remain_under_1b_l3         :    1;
					uint32_t in_remain_under_2b_l3         :    1;
					uint32_t in_remain_under_3b_l3         :    1;
					uint32_t in_remain_under_4b_l3         :    1;
					uint32_t in_buf_hungry                 :    1;
					uint32_t reserved29                    :    3;
				};
				uint32_t val;
			} infifo_status;
			union {
				struct {
					uint32_t infifo_rdata                  :    12;
					uint32_t infifo_pop                    :    1;
					uint32_t reserved13                    :    19;
				};
				uint32_t val;
			} pop;
			union {
				struct {
					uint32_t addr                          :    20;
					uint32_t auto_ret                      :    1;
					uint32_t stop                          :    1;
					uint32_t start                         :    1;
					uint32_t restart                       :    1;
					uint32_t park                          :    1;
					uint32_t reserved25                    :    7;
				};
				uint32_t val;
			} link;
			union {
				struct {
					uint32_t dscr_addr                     :    18;
					uint32_t in_dscr_state                 :    2;
					uint32_t in_state                      :    3;
					uint32_t reserved23                    :    9;
				};
				uint32_t val;
			} state;
			uint32_t suc_eof_des_addr;
			uint32_t err_eof_des_addr;
			uint32_t dscr;
			uint32_t dscr_bf0;
			uint32_t dscr_bf1;
			union {
				struct {
					uint32_t reserved0                     :    8;
					uint32_t rx_weight                     :    4;
					uint32_t reserved12                    :    20;
				};
				uint32_t val;
			} wight;
			uint32_t reserved_40;
			union {
				struct {
					uint32_t rx_pri                        :    4;
					uint32_t reserved4                     :    28;
				};
				uint32_t val;
			} pri;
			union {
				struct {
					uint32_t sel                           :    6;
					uint32_t reserved6                     :    26;
				};
				uint32_t val;
			} peri_sel;
			uint32_t reserved_4c;
			uint32_t reserved_50;
			uint32_t reserved_54;
			uint32_t reserved_58;
			uint32_t reserved_5c;
		} in;
		struct {
			union {
				struct {
					uint32_t out_rst                       :    1;
					uint32_t out_loop_test                 :    1;
					uint32_t out_auto_wrback               :    1;
					uint32_t out_eof_mode                  :    1;
					uint32_t outdscr_burst_en              :    1;
					uint32_t out_data_burst_en             :    1;
					uint32_t reserved6                     :    1;
					uint32_t reserved7                     :    25;
				};
				uint32_t val;
			} conf0;
			union {
				struct {
					uint32_t reserved0                     :    12;
					uint32_t out_check_owner               :    1;
					uint32_t out_ext_mem_bk_size           :    2;
					uint32_t reserved15                    :    17;
				};
				uint32_t val;
			} conf1;
			union {
				struct {
					uint32_t out_done                      :    1;
					uint32_t out_eof                       :    1;
					uint32_t out_dscr_err                  :    1;
					uint32_t out_total_eof                 :    1;
					uint32_t outfifo_ovf_l1                :    1;
					uint32_t outfifo_udf_l1                :    1;
					uint32_t outfifo_ovf_l3                :    1;
					uint32_t outfifo_udf_l3                :    1;
					uint32_t reserved8                     :    24;
				};
				uint32_t val;
			} int_raw;
			union {
				struct {
					uint32_t out_done                      :    1;
					uint32_t out_eof                       :    1;
					uint32_t out_dscr_err                  :    1;
					uint32_t out_total_eof                 :    1;
					uint32_t outfifo_ovf_l1                :    1;
					uint32_t outfifo_udf_l1                :    1;
					uint32_t outfifo_ovf_l3                :    1;
					uint32_t outfifo_udf_l3                :    1;
					uint32_t reserved8                     :    24;
				};
				uint32_t val;
			} int_st;
			union {
				struct {
					uint32_t out_done                      :    1;
					uint32_t out_eof                       :    1;
					uint32_t out_dscr_err                  :    1;
					uint32_t out_total_eof                 :    1;
					uint32_t outfifo_ovf_l1                :    1;
					uint32_t outfifo_udf_l1                :    1;
					uint32_t outfifo_ovf_l3                :    1;
					uint32_t outfifo_udf_l3                :    1;
					uint32_t reserved8                     :    24;
				};
				uint32_t val;
			} int_ena;
			union {
				struct {
					uint32_t out_done                      :    1;
					uint32_t out_eof                       :    1;
					uint32_t out_dscr_err                  :    1;
					uint32_t out_total_eof                 :    1;
					uint32_t outfifo_ovf_l1                :    1;
					uint32_t outfifo_udf_l1                :    1;
					uint32_t outfifo_ovf_l3                :    1;
					uint32_t outfifo_udf_l3                :    1;
					uint32_t reserved8                     :    24;
				};
				uint32_t val;
			} int_clr;
			union {
				struct {
					uint32_t outfifo_full_l1               :    1;
					uint32_t outfifo_empty_l1              :    1;
					uint32_t outfifo_full_l2               :    1;
					uint32_t outfifo_empty_l2              :    1;
					uint32_t outfifo_full_l3               :    1;
					uint32_t outfifo_empty_l3              :    1;
					uint32_t outfifo_cnt_l1                :    5;
					uint32_t outfifo_cnt_l2                :    7;
					uint32_t outfifo_cnt_l3                :    5;
					uint32_t out_remain_under_1b_l3        :    1;
					uint32_t out_remain_under_2b_l3        :    1;
					uint32_t out_remain_under_3b_l3        :    1;
					uint32_t out_remain_under_4b_l3        :    1;
					uint32_t reserved27                    :    5;
				};
				uint32_t val;
			} outfifo_status;
			union {
				struct {
					uint32_t outfifo_wdata                 :    9;
					uint32_t outfifo_push                  :    1;
					uint32_t reserved10                    :    22;
				};
				uint32_t val;
			} push;
			union {
				struct {
					uint32_t addr                          :    20;
					uint32_t stop                          :    1;
					uint32_t start                         :    1;
					uint32_t restart                       :    1;
					uint32_t park                          :    1;
					uint32_t reserved24                    :    8;
				};
				uint32_t val;
			} link;
			union {
				struct {
					uint32_t dscr_addr                     :    18;
					uint32_t out_dscr_state                :    2;
					uint32_t out_state                     :    3;
					uint32_t reserved23                    :    9;
				};
				uint32_t val;
			} state;
			uint32_t eof_des_addr;
			uint32_t eof_bfr_des_addr;
			uint32_t dscr;
			uint32_t dscr_bf0;
			uint32_t dscr_bf1;
			union {
				struct {
					uint32_t reserved0                     :    8;
					uint32_t tx_weight                     :    4;
					uint32_t reserved12                    :    20;
				};
				uint32_t val;
			} wight;
			uint32_t reserved_a0;
			union {
				struct {
					uint32_t tx_pri                        :    4;
					uint32_t reserved4                     :    28;
				};
				uint32_t val;
			} pri;
			union {
				struct {
					uint32_t sel                           :    6;
					uint32_t reserved6                     :    26;
				};
				uint32_t val;
			} peri_sel;
			uint32_t reserved_ac;
			uint32_t reserved_b0;
			uint32_t reserved_b4;
			uint32_t reserved_b8;
			uint32_t reserved_bc;
		} out;
	} channel[5];
	union {
		struct {
			uint32_t ahb_testmode                  :    3;
			uint32_t reserved3                     :    1;
			uint32_t ahb_testaddr                  :    2;
			uint32_t reserved6                     :    26;
		};
		uint32_t val;
	} ahb_test;
	union {
		struct {
			uint32_t reserved0                     :    4;
			uint32_t dma_ram_force_pd              :    1;
			uint32_t dma_ram_force_pu              :    1;
			uint32_t dma_ram_clk_fo                :    1;
			uint32_t reserved7                     :    25;
		};
		uint32_t val;
	} pd_conf;
	union {
		struct {
			uint32_t ahbm_rst_inter                :    1;
			uint32_t ahbm_rst_exter                :    1;
			uint32_t arb_pri_dis                   :    1;
			uint32_t reserved3                     :    1;
			uint32_t clk_en                        :    1;
			uint32_t reserved5                     :    27;
		};
		uint32_t val;
	} misc_conf;
	struct {
		union {
			struct {
				uint32_t in_size                       :    7;
				uint32_t reserved7                     :    25;
			};
			uint32_t val;
		} in;
		union {
			struct {
				uint32_t out_size                      :    7;
				uint32_t reserved7                     :    25;
			};
			uint32_t val;
		} out;
	} sram_size[5];
	uint32_t extmem_reject_addr;
	union {
		struct {
			uint32_t extmem_reject_attr            :    2;
			uint32_t extmem_reject_channel_num     :    4;
			uint32_t extmem_reject_peri_num        :    6;
			uint32_t reserved12                    :    20;
		};
		uint32_t val;
	} extmem_reject_st;
	union {
		struct {
			uint32_t extmem_reject                 :    1;
			uint32_t reserved1                     :    31;
		};
		uint32_t val;
	} extmem_reject_int_raw;
	union {
		struct {
			uint32_t extmem_reject                 :    1;
			uint32_t reserved1                     :    31;
		};
		uint32_t val;
	} extmem_reject_int_st;
	union {
		struct {
			uint32_t extmem_reject                 :    1;
			uint32_t reserved1                     :    31;
		};
		uint32_t val;
	} extmem_reject_int_ena;
	union {
		struct {
			uint32_t extmem_reject                 :    1;
			uint32_t reserved1                     :    31;
		};
		uint32_t val;
	} extmem_reject_int_clr;
	uint32_t date;
} gdma_dev_t;
extern gdma_dev_t GDMA;


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

void gdma_ll_enable_m2m_mode(gdma_dev_t *dev, uint32_t channel, bool enable)
{
	dev->channel[channel].in.conf0.mem_trans_en = enable;
	if (enable) {
		// to enable m2m mode, the tx chan has to be the same to rx chan, and set to a valid value
		dev->channel[channel].in.peri_sel.sel = 0;
		dev->channel[channel].out.peri_sel.sel = 0;
	}
}

void gdma_ll_enable_clock(gdma_dev_t *dev, bool enable)
{
	dev->misc_conf.clk_en = enable;
}

///////////////////////////////////// RX /////////////////////////////////////////
uint32_t gdma_ll_rx_get_interrupt_status(gdma_dev_t *dev, uint32_t channel)
{
	return dev->channel[channel].in.int_st.val;
}

void gdma_ll_rx_enable_interrupt(gdma_dev_t *dev, uint32_t channel, uint32_t mask, bool enable)
{
	if (enable) {
		dev->channel[channel].in.int_ena.val |= mask;
	} else {
		dev->channel[channel].in.int_ena.val &= ~mask;
	}
}

void gdma_ll_rx_clear_interrupt_status(gdma_dev_t *dev, uint32_t channel, uint32_t mask)
{
	dev->channel[channel].in.int_clr.val = mask;
}

volatile void *gdma_ll_rx_get_interrupt_status_reg(gdma_dev_t *dev, uint32_t channel)
{
	return (volatile void *)(&dev->channel[channel].in.int_st);
}

void gdma_ll_rx_enable_owner_check(gdma_dev_t *dev, uint32_t channel, bool enable)
{
	dev->channel[channel].in.conf1.in_check_owner = enable;
}

void gdma_ll_rx_enable_data_burst(gdma_dev_t *dev, uint32_t channel, bool enable)
{
	dev->channel[channel].in.conf0.in_data_burst_en = enable;
}

void gdma_ll_rx_enable_descriptor_burst(gdma_dev_t *dev, uint32_t channel, bool enable)
{
	dev->channel[channel].in.conf0.indscr_burst_en = enable;
}

void gdma_ll_rx_reset_channel(gdma_dev_t *dev, uint32_t channel)
{
	dev->channel[channel].in.conf0.in_rst = 1;
	dev->channel[channel].in.conf0.in_rst = 0;
}

void gdma_ll_rx_set_block_size_psram(gdma_dev_t *dev, uint32_t channel, uint32_t size_index)
{
	dev->channel[channel].in.conf1.in_ext_mem_bk_size = size_index;
}

void gdma_ll_rx_set_water_mark(gdma_dev_t *dev, uint32_t channel, uint32_t water_mark)
{
	dev->channel[channel].in.conf1.dma_infifo_full_thrs = water_mark;
}

bool gdma_ll_rx_is_fifo_full(gdma_dev_t *dev, uint32_t channel, uint32_t fifo_level)
{
	return dev->channel[channel].in.infifo_status.val & (1 << 2 * (fifo_level - 1));
}

bool gdma_ll_rx_is_fifo_empty(gdma_dev_t *dev, uint32_t channel, uint32_t fifo_level)
{
	return dev->channel[channel].in.infifo_status.val & (1 << (2 * (fifo_level - 1) + 1));
}

uint32_t gdma_ll_rx_get_fifo_bytes(gdma_dev_t *dev, uint32_t channel, uint32_t fifo_level)
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

uint32_t gdma_ll_rx_pop_data(gdma_dev_t *dev, uint32_t channel)
{
	dev->channel[channel].in.pop.infifo_pop = 1;
	return dev->channel[channel].in.pop.infifo_rdata;
}

void gdma_ll_rx_set_desc_addr(gdma_dev_t *dev, uint32_t channel, uint32_t addr)
{
	dev->channel[channel].in.link.addr = addr;
}

void gdma_ll_rx_start(gdma_dev_t *dev, uint32_t channel)
{
	dev->channel[channel].in.link.start = 1;
}

void gdma_ll_rx_stop(gdma_dev_t *dev, uint32_t channel)
{
	dev->channel[channel].in.link.stop = 1;
}

void gdma_ll_rx_restart(gdma_dev_t *dev, uint32_t channel)
{
	dev->channel[channel].in.link.restart = 1;
}

void gdma_ll_rx_enable_auto_return(gdma_dev_t *dev, uint32_t channel, bool enable)
{
	dev->channel[channel].in.link.auto_ret = enable;
}

bool gdma_ll_rx_is_fsm_idle(gdma_dev_t *dev, uint32_t channel)
{
	return dev->channel[channel].in.link.park;
}

uint32_t gdma_ll_rx_get_success_eof_desc_addr(gdma_dev_t *dev, uint32_t channel)
{
	return dev->channel[channel].in.suc_eof_des_addr;
}

uint32_t gdma_ll_rx_get_error_eof_desc_addr(gdma_dev_t *dev, uint32_t channel)
{
	return dev->channel[channel].in.err_eof_des_addr;
}

uint32_t gdma_ll_rx_get_current_desc_addr(gdma_dev_t *dev, uint32_t channel)
{
	return dev->channel[channel].in.dscr;
}

void gdma_ll_rx_set_weight(gdma_dev_t *dev, uint32_t channel, uint32_t weight)
{
	dev->channel[channel].in.wight.rx_weight = weight;
}

void gdma_ll_rx_set_priority(gdma_dev_t *dev, uint32_t channel, uint32_t prio)
{
	dev->channel[channel].in.pri.rx_pri = prio;
}

void gdma_ll_rx_connect_to_periph(gdma_dev_t *dev, uint32_t channel, int periph_id)
{
	dev->channel[channel].in.peri_sel.sel = periph_id;
}

///////////////////////////////////// TX /////////////////////////////////////////
uint32_t gdma_ll_tx_get_interrupt_status(gdma_dev_t *dev, uint32_t channel)
{
	return dev->channel[channel].out.int_st.val;
}

void gdma_ll_tx_enable_interrupt(gdma_dev_t *dev, uint32_t channel, uint32_t mask, bool enable)
{
	if (enable) {
		dev->channel[channel].out.int_ena.val |= mask;
	} else {
		dev->channel[channel].out.int_ena.val &= ~mask;
	}
}

void gdma_ll_tx_clear_interrupt_status(gdma_dev_t *dev, uint32_t channel, uint32_t mask)
{
	dev->channel[channel].out.int_clr.val = mask;
}

volatile void *gdma_ll_tx_get_interrupt_status_reg(gdma_dev_t *dev, uint32_t channel)
{
	return (volatile void *)(&dev->channel[channel].out.int_st);
}

void gdma_ll_tx_enable_owner_check(gdma_dev_t *dev, uint32_t channel, bool enable)
{
	dev->channel[channel].out.conf1.out_check_owner = enable;
}

void gdma_ll_tx_enable_data_burst(gdma_dev_t *dev, uint32_t channel, bool enable)
{
	dev->channel[channel].out.conf0.out_data_burst_en = enable;
}

void gdma_ll_tx_enable_descriptor_burst(gdma_dev_t *dev, uint32_t channel, bool enable)
{
	dev->channel[channel].out.conf0.outdscr_burst_en = enable;
}

void gdma_ll_tx_set_eof_mode(gdma_dev_t *dev, uint32_t channel, uint32_t mode)
{
	dev->channel[channel].out.conf0.out_eof_mode = mode;
}

void gdma_ll_tx_enable_auto_write_back(gdma_dev_t *dev, uint32_t channel, bool enable)
{
	dev->channel[channel].out.conf0.out_auto_wrback = enable;
}

void gdma_ll_tx_reset_channel(gdma_dev_t *dev, uint32_t channel)
{
	dev->channel[channel].out.conf0.out_rst = 1;
	dev->channel[channel].out.conf0.out_rst = 0;
}

void gdma_ll_tx_set_block_size_psram(gdma_dev_t *dev, uint32_t channel, uint32_t size_index)
{
	dev->channel[channel].out.conf1.out_ext_mem_bk_size = size_index;
}

bool gdma_ll_tx_is_fifo_full(gdma_dev_t *dev, uint32_t channel, uint32_t fifo_level)
{
	return dev->channel[channel].out.outfifo_status.val & (1 << 2 * (fifo_level - 1));
}

bool gdma_ll_tx_is_fifo_empty(gdma_dev_t *dev, uint32_t channel, uint32_t fifo_level)
{
	return dev->channel[channel].out.outfifo_status.val & (1 << (2 * (fifo_level - 1) + 1));
}

uint32_t gdma_ll_tx_get_fifo_bytes(gdma_dev_t *dev, uint32_t channel, uint32_t fifo_level)
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

void gdma_ll_tx_push_data(gdma_dev_t *dev, uint32_t channel, uint32_t data)
{
	dev->channel[channel].out.push.outfifo_wdata = data;
	dev->channel[channel].out.push.outfifo_push = 1;
}

void gdma_ll_tx_set_desc_addr(gdma_dev_t *dev, uint32_t channel, uint32_t addr)
{
	dev->channel[channel].out.link.addr = addr;
}

void gdma_ll_tx_start(gdma_dev_t *dev, uint32_t channel)
{
	dev->channel[channel].out.link.start = 1;
}

void gdma_ll_tx_stop(gdma_dev_t *dev, uint32_t channel)
{
	dev->channel[channel].out.link.stop = 1;
}

void gdma_ll_tx_restart(gdma_dev_t *dev, uint32_t channel)
{
	dev->channel[channel].out.link.restart = 1;
}

bool gdma_ll_tx_is_fsm_idle(gdma_dev_t *dev, uint32_t channel)
{
	return dev->channel[channel].out.link.park;
}

uint32_t gdma_ll_tx_get_eof_desc_addr(gdma_dev_t *dev, uint32_t channel)
{
	return dev->channel[channel].out.eof_des_addr;
}

uint32_t gdma_ll_tx_get_current_desc_addr(gdma_dev_t *dev, uint32_t channel)
{
	return dev->channel[channel].out.dscr;
}

void gdma_ll_tx_set_weight(gdma_dev_t *dev, uint32_t channel, uint32_t weight)
{
	dev->channel[channel].out.wight.tx_weight = weight;
}

void gdma_ll_tx_set_priority(gdma_dev_t *dev, uint32_t channel, uint32_t prio)
{
	dev->channel[channel].out.pri.tx_pri = prio;
}

void gdma_ll_tx_connect_to_periph(gdma_dev_t *dev, uint32_t channel, int periph_id)
{
	dev->channel[channel].out.peri_sel.sel = periph_id;
}

