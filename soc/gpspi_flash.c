

// The Lowlevel layer for SPI Flash


#include <stdlib.h>
#include <sys/param.h> // For MIN/MAX
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#define SPI_FCMD_QUAD_M  (1<<9)
#define SPI_FREAD_QUAD_M  (1<<15)
#define SPI_FADDR_QUAD    (1<<6)
#define SPI_FADDR_QUAD_M  (1<<6)
#define SPI_FADDR_DUAL_M  (1<<5)
#define SPI_FCMD_DUAL_M  (1<<8)
#define SPI_FREAD_DUAL_M  (1<<14)
#define SPI_FWRITE_QUAD_M  (1<<13)
#define SPI_FWRITE_DUAL_M  (1<<12)


typedef enum {
	SPI_FLASH_SLOWRD = 0,
	SPI_FLASH_FASTRD,
	SPI_FLASH_DOUT,
	SPI_FLASH_DIO,
	SPI_FLASH_QOUT,
	SPI_FLASH_QIO,
	SPI_FLASH_OPI_STR = 16,
	SPI_FLASH_OPI_DTR,
	SPI_FLASH_READ_MODE_MAX,
} esp_flash_io_mode_t;

typedef union {
	struct {
		uint32_t clkcnt_l                      :    6;
		uint32_t clkcnt_h                      :    6;
		uint32_t clkcnt_n                      :    6;
		uint32_t clkdiv_pre                    :    4;
		uint32_t reserved22                    :    9;
		uint32_t clk_equ_sysclk                :    1;
	};
	uint32_t val;
} gpspi_flash_ll_clock_reg_t;

typedef volatile struct spi_dev_s {
	union {
		struct {
			uint32_t conf_bitlen                   :    18;
			uint32_t reserved18                    :    5;
			uint32_t update                        :    1;
			uint32_t usr                           :    1;
			uint32_t reserved25                    :    7;
		};
		uint32_t val;
	} cmd;
	uint32_t addr;
	union {
		struct {
			uint32_t reserved0                     :    3;
			uint32_t dummy_out                     :    1;
			uint32_t reserved4                     :    1;
			uint32_t faddr_dual                    :    1;
			uint32_t faddr_quad                    :    1;
			uint32_t faddr_oct                     :    1;
			uint32_t fcmd_dual                     :    1;
			uint32_t fcmd_quad                     :    1;
			uint32_t fcmd_oct                      :    1;
			uint32_t reserved11                    :    3;
			uint32_t fread_dual                    :    1;
			uint32_t fread_quad                    :    1;
			uint32_t fread_oct                     :    1;
			uint32_t reserved17                    :    1;
			uint32_t q_pol                         :    1;
			uint32_t d_pol                         :    1;
			uint32_t hold_pol                      :    1;
			uint32_t wp_pol                        :    1;
			uint32_t reserved22                    :    1;
			uint32_t rd_bit_order                  :    2;
			uint32_t wr_bit_order                  :    2;
			uint32_t reserved27                    :    5;
		};
		uint32_t val;
	} ctrl;
	gpspi_flash_ll_clock_reg_t clock;
	union {
		struct {
			uint32_t doutdin                       :    1;
			uint32_t reserved1                     :    2;
			uint32_t qpi_mode                      :    1;
			uint32_t opi_mode                      :    1;
			uint32_t tsck_i_edge                   :    1;
			uint32_t cs_hold                       :    1;
			uint32_t cs_setup                      :    1;
			uint32_t rsck_i_edge                   :    1;
			uint32_t ck_out_edge                   :    1;
			uint32_t reserved10                    :    2;
			uint32_t fwrite_dual                   :    1;
			uint32_t fwrite_quad                   :    1;
			uint32_t fwrite_oct                    :    1;
			uint32_t usr_conf_nxt                  :    1;
			uint32_t reserved16                    :    1;
			uint32_t sio                           :    1;
			uint32_t reserved18                    :    6;
			uint32_t usr_miso_highpart             :    1;
			uint32_t usr_mosi_highpart             :    1;
			uint32_t usr_dummy_idle                :    1;
			uint32_t usr_mosi                      :    1;
			uint32_t usr_miso                      :    1;
			uint32_t usr_dummy                     :    1;
			uint32_t usr_addr                      :    1;
			uint32_t usr_command                   :    1;
		};
		uint32_t val;
	} user;
	union {
		struct {
			uint32_t usr_dummy_cyclelen            :    8;
			uint32_t reserved8                     :    8;
			uint32_t mst_wfull_err_end_en          :    1;
			uint32_t cs_setup_time                 :    5;
			uint32_t cs_hold_time                  :    5;
			uint32_t usr_addr_bitlen               :    5;
		};
		uint32_t val;
	} user1;
	union {
		struct {
			uint32_t usr_command_value             :    16;
			uint32_t reserved16                    :    11;
			uint32_t mst_rempty_err_end_en         :    1;
			uint32_t usr_command_bitlen            :    4;
		};
		uint32_t val;
	} user2;
	union {
		struct {
			uint32_t ms_data_bitlen                :    18;
			uint32_t reserved18                    :    14;
		};
		uint32_t val;
	} ms_dlen;
	union {
		struct {
			uint32_t cs0_dis                       :    1;
			uint32_t cs1_dis                       :    1;
			uint32_t cs2_dis                       :    1;
			uint32_t cs3_dis                       :    1;
			uint32_t cs4_dis                       :    1;
			uint32_t cs5_dis                       :    1;
			uint32_t ck_dis                        :    1;
			uint32_t master_cs_pol                 :    6;
			uint32_t reserved13                    :    3;
			uint32_t clk_data_dtr_en               :    1;
			uint32_t data_dtr_en                   :    1;
			uint32_t addr_dtr_en                   :    1;
			uint32_t cmd_dtr_en                    :    1;
			uint32_t reserved20                    :    3;
			uint32_t slave_cs_pol                  :    1;
			uint32_t dqs_idle_edge                 :    1;
			uint32_t reserved25                    :    4;
			uint32_t ck_idle_edge                  :    1;
			uint32_t cs_keep_active                :    1;
			uint32_t quad_din_pin_swap             :    1;
		};
		uint32_t val;
	} misc;
	union {
		struct {
			uint32_t din0_mode                     :    2;
			uint32_t din1_mode                     :    2;
			uint32_t din2_mode                     :    2;
			uint32_t din3_mode                     :    2;
			uint32_t din4_mode                     :    2;
			uint32_t din5_mode                     :    2;
			uint32_t din6_mode                     :    2;
			uint32_t din7_mode                     :    2;
			uint32_t timing_hclk_active            :    1;
			uint32_t reserved17                    :    15;
		};
		uint32_t val;
	} din_mode;
	union {
		struct {
			uint32_t din0_num                      :    2;
			uint32_t din1_num                      :    2;
			uint32_t din2_num                      :    2;
			uint32_t din3_num                      :    2;
			uint32_t din4_num                      :    2;
			uint32_t din5_num                      :    2;
			uint32_t din6_num                      :    2;
			uint32_t din7_num                      :    2;
			uint32_t reserved16                    :    16;
		};
		uint32_t val;
	} din_num;
	union {
		struct {
			uint32_t dout0_mode                    :    1;
			uint32_t dout1_mode                    :    1;
			uint32_t dout2_mode                    :    1;
			uint32_t dout3_mode                    :    1;
			uint32_t dout4_mode                    :    1;
			uint32_t dout5_mode                    :    1;
			uint32_t dout6_mode                    :    1;
			uint32_t dout7_mode                    :    1;
			uint32_t d_dqs_mode                    :    1;
			uint32_t reserved9                     :    23;
		};
		uint32_t val;
	} dout_mode;
	union {
		struct {
			uint32_t outfifo_empty                 :    1;
			uint32_t infifo_full                   :    1;
			uint32_t reserved2                     :    16;
			uint32_t dma_seg_trans_en              :    1;
			uint32_t rx_seg_trans_clr_en           :    1;
			uint32_t tx_seg_trans_clr_en           :    1;
			uint32_t rx_eof_en                     :    1;
			uint32_t reserved22                    :    5;
			uint32_t dma_rx_ena                    :    1;
			uint32_t dma_tx_ena                    :    1;
			uint32_t rx_afifo_rst                  :    1;
			uint32_t buf_afifo_rst                 :    1;
			uint32_t dma_afifo_rst                 :    1;
		};
		uint32_t val;
	} dma_conf;
	union {
		struct {
			uint32_t infifo_full_err               :    1;
			uint32_t outfifo_empty_err             :    1;
			uint32_t ex_qpi                        :    1;
			uint32_t en_qpi                        :    1;
			uint32_t cmd7                          :    1;
			uint32_t cmd8                          :    1;
			uint32_t cmd9                          :    1;
			uint32_t cmda                          :    1;
			uint32_t rd_dma_done                   :    1;
			uint32_t wr_dma_done                   :    1;
			uint32_t rd_buf_done                   :    1;
			uint32_t wr_buf_done                   :    1;
			uint32_t trans_done                    :    1;
			uint32_t dma_seg_trans_done            :    1;
			uint32_t seg_magic_err                 :    1;
			uint32_t buf_addr_err                  :    1;
			uint32_t cmd_err                       :    1;
			uint32_t mst_rx_afifo_wfull_err        :    1;
			uint32_t mst_tx_afifo_rempty_err       :    1;
			uint32_t app2                          :    1;
			uint32_t app1                          :    1;
			uint32_t reserved21                    :    11;
		};
		uint32_t val;
	} dma_int_ena;
	union {
		struct {
			uint32_t infifo_full_err               :    1;
			uint32_t outfifo_empty_err             :    1;
			uint32_t ex_qpi                        :    1;
			uint32_t en_qpi                        :    1;
			uint32_t cmd7                          :    1;
			uint32_t cmd8                          :    1;
			uint32_t cmd9                          :    1;
			uint32_t cmda                          :    1;
			uint32_t rd_dma_done                   :    1;
			uint32_t wr_dma_done                   :    1;
			uint32_t rd_buf_done                   :    1;
			uint32_t wr_buf_done                   :    1;
			uint32_t trans_done                    :    1;
			uint32_t dma_seg_trans_done            :    1;
			uint32_t seg_magic_err                 :    1;
			uint32_t buf_addr_err                  :    1;
			uint32_t cmd_err                       :    1;
			uint32_t mst_rx_afifo_wfull_err        :    1;
			uint32_t mst_tx_afifo_rempty_err       :    1;
			uint32_t app2                          :    1;
			uint32_t app1                          :    1;
			uint32_t reserved21                    :    11;
		};
		uint32_t val;
	} dma_int_clr;
	union {
		struct {
			uint32_t infifo_full_err               :    1;
			uint32_t outfifo_empty_err             :    1;
			uint32_t ex_qpi                        :    1;
			uint32_t en_qpi                        :    1;
			uint32_t cmd7                          :    1;
			uint32_t cmd8                          :    1;
			uint32_t cmd9                          :    1;
			uint32_t cmda                          :    1;
			uint32_t rd_dma_done                   :    1;
			uint32_t wr_dma_done                   :    1;
			uint32_t rd_buf_done                   :    1;
			uint32_t wr_buf_done                   :    1;
			uint32_t trans_done                    :    1;
			uint32_t dma_seg_trans_done            :    1;
			uint32_t seg_magic_err                 :    1;
			uint32_t buf_addr_err                  :    1;
			uint32_t cmd_err                       :    1;
			uint32_t mst_rx_afifo_wfull_err        :    1;
			uint32_t mst_tx_afifo_rempty_err       :    1;
			uint32_t app2                          :    1;
			uint32_t app1                          :    1;
			uint32_t reserved21                    :    11;
		};
		uint32_t val;
	} dma_int_raw;
	union {
		struct {
			uint32_t infifo_full_err               :    1;
			uint32_t outfifo_empty_err             :    1;
			uint32_t ex_qpi                        :    1;
			uint32_t en_qpi                        :    1;
			uint32_t cmd7                          :    1;
			uint32_t cmd8                          :    1;
			uint32_t cmd9                          :    1;
			uint32_t cmda                          :    1;
			uint32_t rd_dma_done                   :    1;
			uint32_t wr_dma_done                   :    1;
			uint32_t rd_buf_done                   :    1;
			uint32_t wr_buf_done                   :    1;
			uint32_t trans_done                    :    1;
			uint32_t dma_seg_trans_done            :    1;
			uint32_t seg_magic_err                 :    1;
			uint32_t buf_addr_err                  :    1;
			uint32_t cmd_err                       :    1;
			uint32_t mst_rx_afifo_wfull_err        :    1;
			uint32_t mst_tx_afifo_rempty_err       :    1;
			uint32_t app2                          :    1;
			uint32_t app1                          :    1;
			uint32_t reserved21                    :    11;
		};
		uint32_t val;
	} dma_int_st;
	union {
		struct {
			uint32_t infifo_full_err_int_set       :    1;
			uint32_t outfifo_empty_err_int_set     :    1;
			uint32_t ex_qpi_int_set                :    1;
			uint32_t en_qpi_int_set                :    1;
			uint32_t cmd7_int_set                  :    1;
			uint32_t cmd8_int_set                  :    1;
			uint32_t cmd9_int_set                  :    1;
			uint32_t cmda_int_set                  :    1;
			uint32_t rd_dma_done_int_set           :    1;
			uint32_t wr_dma_done_int_set           :    1;
			uint32_t rd_buf_done_int_set           :    1;
			uint32_t wr_buf_done_int_set           :    1;
			uint32_t trans_done_int_set            :    1;
			uint32_t dma_seg_trans_done_int_set    :    1;
			uint32_t seg_magic_err_int_set         :    1;
			uint32_t buf_addr_err_int_set          :    1;
			uint32_t cmd_err_int_set               :    1;
			uint32_t mst_rx_afifo_wfull_err_int_set:    1;
			uint32_t mst_tx_afifo_rempty_err_int_set:    1;
			uint32_t app2_int_set                  :    1;
			uint32_t app1_int_set                  :    1;
			uint32_t reserved21                    :    11;
		};
		uint32_t val;
	} dma_int_set;
	uint32_t reserved_48;
	uint32_t reserved_4c;
	uint32_t reserved_50;
	uint32_t reserved_54;
	uint32_t reserved_58;
	uint32_t reserved_5c;
	uint32_t reserved_60;
	uint32_t reserved_64;
	uint32_t reserved_68;
	uint32_t reserved_6c;
	uint32_t reserved_70;
	uint32_t reserved_74;
	uint32_t reserved_78;
	uint32_t reserved_7c;
	uint32_t reserved_80;
	uint32_t reserved_84;
	uint32_t reserved_88;
	uint32_t reserved_8c;
	uint32_t reserved_90;
	uint32_t reserved_94;
	uint32_t data_buf[16];                                             
	uint32_t reserved_d8;
	uint32_t reserved_dc;
	union {
		struct {
			uint32_t clk_mode                      :    2;
			uint32_t clk_mode_13                   :    1;
			uint32_t rsck_data_out                 :    1;
			uint32_t reserved4                     :    4;
			uint32_t rddma_bitlen_en               :    1;
			uint32_t wrdma_bitlen_en               :    1;
			uint32_t rdbuf_bitlen_en               :    1;
			uint32_t wrbuf_bitlen_en               :    1;
			uint32_t reserved12                    :    10;
			uint32_t dma_seg_magic_value           :    4;
			uint32_t slave_mode                    :    1;
			uint32_t soft_reset                    :    1;
			uint32_t usr_conf                      :    1;
			uint32_t reserved29                    :    3;
		};
		uint32_t val;
	} slave;
	union {
		struct {
			uint32_t data_bitlen                   :    18;
			uint32_t last_command                  :    8;
			uint32_t last_addr                     :    6;
		};
		uint32_t val;
	} slave1;
	union {
		struct {
			uint32_t clk_en                        :    1;
			uint32_t mst_clk_active                :    1;
			uint32_t mst_clk_sel                   :    1;
			uint32_t reserved3                     :    29;
		};
		uint32_t val;
	} clk_gate;
	uint32_t reserved_ec;
	union {
		struct {
			uint32_t date                          :    28;
			uint32_t reserved28                    :    4;
		};
		uint32_t val;
	} date;
} spi_dev_t;

spi_dev_t *GPSPI2  = (void*)0x60024000;



#define gpspi_flash_ll_get_hw(host_id)  (((host_id)==SPI2_HOST ? GPSPI2 \
												: ((host_id)==SPI3_HOST ? &GPSPI3 \
												: ({abort();(spi_dev_t*)0;}))))

#define gpspi_flash_ll_hw_get_id(dev)   ( ((dev) == (void*)GPSPI2) ? SPI2_HOST : (\
										  ((dev) == (void*)&GPSPI3) ? SPI3_HOST : (\
										  -1 \
										)) )



//Supported clock register values
#define GPSPI_FLASH_LL_CLKREG_VAL_5MHZ   ((gpspi_flash_ll_clock_reg_t){.val=0x0000F1CF})   ///< Clock set to 5 MHz
#define GPSPI_FLASH_LL_CLKREG_VAL_10MHZ  ((gpspi_flash_ll_clock_reg_t){.val=0x000070C7})   ///< Clock set to 10 MHz
#define GPSPI_FLASH_LL_CLKREG_VAL_20MHZ  ((gpspi_flash_ll_clock_reg_t){.val=0x00003043})   ///< Clock set to 20 MHz
#define GPSPI_FLASH_LL_CLKREG_VAL_26MHZ  ((gpspi_flash_ll_clock_reg_t){.val=0x00002002})   ///< Clock set to 26 MHz
#define GPSPI_FLASH_LL_CLKREG_VAL_40MHZ  ((gpspi_flash_ll_clock_reg_t){.val=0x00001001})   ///< Clock set to 40 MHz
#define GPSPI_FLASH_LL_CLKREG_VAL_80MHZ  ((gpspi_flash_ll_clock_reg_t){.val=0x80000000})   ///< Clock set to 80 MHz

void gpspi_flash_ll_reset(spi_dev_t *dev)
{
	dev->user.val = 0;
	dev->ctrl.val = 0;

	dev->clk_gate.clk_en = 1;
	dev->clk_gate.mst_clk_active = 1;
	dev->clk_gate.mst_clk_sel = 1;

	dev->dma_conf.val = 0;
	dev->dma_conf.tx_seg_trans_clr_en = 1;
	dev->dma_conf.rx_seg_trans_clr_en = 1;
	dev->dma_conf.dma_seg_trans_en = 0;
}

bool gpspi_flash_ll_cmd_is_done(const spi_dev_t *dev)
{
	return (dev->cmd.usr == 0);
}

void gpspi_flash_ll_get_buffer_data(spi_dev_t *dev, void *buffer, uint32_t read_len)
{
	if (((intptr_t)buffer % 4 == 0) && (read_len % 4 == 0)) {
		// If everything is word-aligned, do a faster memcpy
		memcpy(buffer, (void *)dev->data_buf, read_len);
	} else {
		// Otherwise, slow(er) path copies word by word
		int copy_len = read_len;
		for (uint32_t i = 0; i < (read_len + 3) / 4; i++) {
			int word_len = MIN(sizeof(uint32_t), copy_len);
			uint32_t word = dev->data_buf[i];
			memcpy(buffer, &word, word_len);
			buffer = (void *)((intptr_t)buffer + word_len);
			copy_len -= word_len;
		}
	}
}

void gpspi_flash_ll_write_word(spi_dev_t *dev, uint32_t word)
{
	dev->data_buf[0] = word;
}

void gpspi_flash_ll_set_buffer_data(spi_dev_t *dev, const void *buffer, uint32_t length)
{
	// Load data registers, word at a time
	int num_words = (length + 3) / 4;
	for (int i = 0; i < num_words; i++) {
		uint32_t word = 0;
		uint32_t word_len = MIN(length, sizeof(word));
		memcpy(&word, buffer, word_len);
		dev->data_buf[i] = word;
		length -= word_len;
		buffer = (void *)((intptr_t)buffer + word_len);
	}
}

void gpspi_flash_ll_user_start(spi_dev_t *dev)
{
	dev->cmd.update = 1;
	while (dev->cmd.update);
	dev->cmd.usr = 1;
}

void gpspi_flash_ll_set_hold_pol(spi_dev_t *dev, uint32_t pol_val)
{
	dev->ctrl.hold_pol = pol_val;
}

bool gpspi_flash_ll_host_idle(const spi_dev_t *dev)
{
	return dev->cmd.usr == 0;
}

void gpspi_flash_ll_read_phase(spi_dev_t *dev)
{
	typeof (dev->user) user = {
		.usr_command = 1,
		.usr_mosi = 0,
		.usr_miso = 1,
		.usr_addr = 1,
	};
	dev->user = user;
}
void gpspi_flash_ll_set_cs_pin(spi_dev_t *dev, int pin)
{
	dev->misc.cs0_dis = (pin == 0) ? 0 : 1;
	dev->misc.cs1_dis = (pin == 1) ? 0 : 1;
}

void gpspi_flash_ll_set_read_mode(spi_dev_t *dev, esp_flash_io_mode_t read_mode)
{
	typeof (dev->ctrl) ctrl = dev->ctrl;
	typeof (dev->user) user = dev->user;

	ctrl.val &= ~(SPI_FCMD_QUAD_M | SPI_FADDR_QUAD_M | SPI_FREAD_QUAD_M | SPI_FCMD_DUAL_M | SPI_FADDR_DUAL_M | SPI_FREAD_DUAL_M);
	user.val &= ~(SPI_FWRITE_QUAD_M | SPI_FWRITE_DUAL_M);

	switch (read_mode) {
	case SPI_FLASH_FASTRD:
		//the default option
	case SPI_FLASH_SLOWRD:
		break;
	case SPI_FLASH_QIO:
		ctrl.fread_quad = 1;
		ctrl.faddr_quad = 1;
		user.fwrite_quad = 1;
		break;
	case SPI_FLASH_QOUT:
		ctrl.fread_quad = 1;
		user.fwrite_quad = 1;
		break;
	case SPI_FLASH_DIO:
		ctrl.fread_dual = 1;
		ctrl.faddr_dual = 1;
		user.fwrite_dual = 1;
		break;
	case SPI_FLASH_DOUT:
		ctrl.fread_dual = 1;
		user.fwrite_dual = 1;
		break;
	default:
		abort();
	}

	dev->ctrl = ctrl;
	dev->user = user;
}

void gpspi_flash_ll_set_clock(spi_dev_t *dev, gpspi_flash_ll_clock_reg_t *clock_val)
{
	dev->clock = *clock_val;
}

void gpspi_flash_ll_set_miso_bitlen(spi_dev_t *dev, uint32_t bitlen)
{
	dev->user.usr_miso = bitlen > 0;
	if (bitlen) {
		dev->ms_dlen.ms_data_bitlen = bitlen - 1;
	}
}

void gpspi_flash_ll_set_mosi_bitlen(spi_dev_t *dev, uint32_t bitlen)
{
	dev->user.usr_mosi = bitlen > 0;
	if (bitlen) {
		dev->ms_dlen.ms_data_bitlen = bitlen - 1;
	}
}

void gpspi_flash_ll_set_command(spi_dev_t *dev, uint8_t command, uint32_t bitlen)
{
	dev->user.usr_command = 1;
	typeof(dev->user2) user2 = {
		.usr_command_value = command,
		.usr_command_bitlen = (bitlen - 1),
	};
	dev->user2 = user2;
}

int gpspi_flash_ll_get_addr_bitlen(spi_dev_t *dev)
{
	return dev->user.usr_addr ? dev->user1.usr_addr_bitlen + 1 : 0;
}

void gpspi_flash_ll_set_addr_bitlen(spi_dev_t *dev, uint32_t bitlen)
{
	dev->user1.usr_addr_bitlen = (bitlen - 1);
	dev->user.usr_addr = bitlen ? 1 : 0;
}

void gpspi_flash_ll_set_usr_address(spi_dev_t *dev, uint32_t addr, uint32_t bitlen)
{
	// The blank region should be all ones
	uint32_t padding_ones = (bitlen == 32? 0 : UINT32_MAX >> bitlen);
	dev->addr = (addr << (32 - bitlen)) | padding_ones;
}


void gpspi_flash_ll_set_address(spi_dev_t *dev, uint32_t addr)
{
	dev->addr = addr;
}

void gpspi_flash_ll_set_dummy(spi_dev_t *dev, uint32_t dummy_n)
{
	dev->user.usr_dummy = dummy_n ? 1 : 0;
	HAL_FORCE_MODIFY_U32_REG_FIELD(dev->user1, dev->user1.usr_dummy_cyclelen, dummy_n - 1);
}

void gpspi_flash_ll_set_dummy_out(spi_dev_t *dev, uint32_t out_en, uint32_t out_lev)
{
	dev->ctrl.dummy_out = out_en;
	dev->ctrl.q_pol = out_lev;
	dev->ctrl.d_pol = out_lev;
}

void gpspi_flash_ll_set_hold(spi_dev_t *dev, uint32_t hold_n)
{
	dev->user1.cs_hold_time = hold_n - 1;
	dev->user.cs_hold = (hold_n > 0? 1: 0);
}

void gpspi_flash_ll_set_cs_setup(spi_dev_t *dev, uint32_t cs_setup_time)
{
	dev->user.cs_setup = (cs_setup_time > 0 ? 1 : 0);
	dev->user1.cs_setup_time = cs_setup_time - 1;
}

