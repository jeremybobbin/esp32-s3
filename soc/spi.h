#include <stdlib.h>
#include <string.h>

#define SPI_LL_UNUSED_INT_MASK	(SPI_TRANS_DONE_INT_ENA | SPI_SLV_WR_DMA_DONE_INT_ENA | SPI_SLV_RD_DMA_DONE_INT_ENA | SPI_SLV_WR_BUF_DONE_INT_ENA | SPI_SLV_RD_BUF_DONE_INT_ENA)
#define SPI_LL_ONE_LINE_CTRL_MASK (SPI_FREAD_OCT | SPI_FREAD_QUAD | SPI_FREAD_DUAL | SPI_FCMD_OCT | \
		SPI_FCMD_QUAD | SPI_FCMD_DUAL | SPI_FADDR_OCT | SPI_FADDR_QUAD | SPI_FADDR_DUAL)
#define SPI_LL_ONE_LINE_USER_MASK (SPI_FWRITE_OCT | SPI_FWRITE_QUAD | SPI_FWRITE_DUAL)

#define HAL_SPI_SWAP_DATA_TX(data, len) HAL_SWAP32((uint32_t)(data) << (32 - len))
#define SPI_LL_PERIPH_CLK_FREQ (80 * 1000000)
#define SPI_LL_GET_HW(ID) ((ID)==0? ({abort();NULL;}):((ID)==1? &GPSPI2 : &GPSPI3))

#define SPI_LL_DATA_MAX_BIT_LEN (1 << 18)

typedef uint32_t spi_ll_clock_val_t;
typedef spi_dev_t spi_dma_dev_t;

typedef enum {
	SPI_LL_INTR_TRANS_DONE =	BIT(0),		///< A transaction has done
	SPI_LL_INTR_RDBUF =			BIT(6),		///< Has received RDBUF command. Only available in slave HD.
	SPI_LL_INTR_WRBUF =			BIT(7),		///< Has received WRBUF command. Only available in slave HD.
	SPI_LL_INTR_RDDMA =			BIT(8),		///< Has received RDDMA command. Only available in slave HD.
	SPI_LL_INTR_WRDMA =			BIT(9),		///< Has received WRDMA command. Only available in slave HD.
	SPI_LL_INTR_CMD7 =			BIT(10),	///< Has received CMD7 command. Only available in slave HD.
	SPI_LL_INTR_CMD8 =			BIT(11),	///< Has received CMD8 command. Only available in slave HD.
	SPI_LL_INTR_CMD9 =			BIT(12),	///< Has received CMD9 command. Only available in slave HD.
	SPI_LL_INTR_CMDA =			BIT(13),	///< Has received CMDA command. Only available in slave HD.
	SPI_LL_INTR_SEG_DONE =		BIT(14),
} spi_ll_intr_t;
FLAG_ATTR(spi_ll_intr_t)

typedef enum {
	SPI_LL_TRANS_LEN_COND_WRBUF =	BIT(0), ///< WRBUF length will be recorded
	SPI_LL_TRANS_LEN_COND_RDBUF =	BIT(1), ///< RDBUF length will be recorded
	SPI_LL_TRANS_LEN_COND_WRDMA =	BIT(2), ///< WRDMA length will be recorded
	SPI_LL_TRANS_LEN_COND_RDDMA =	BIT(3), ///< RDDMA length will be recorded
} spi_ll_trans_len_cond_t;
FLAG_ATTR(spi_ll_trans_len_cond_t)

typedef enum {
	SPI_LL_BASE_CMD_HD_WRBUF	= 0x01,
	SPI_LL_BASE_CMD_HD_RDBUF	= 0x02,
	SPI_LL_BASE_CMD_HD_WRDMA	= 0x03,
	SPI_LL_BASE_CMD_HD_RDDMA	= 0x04,
	SPI_LL_BASE_CMD_HD_SEG_END	= 0x05,
	SPI_LL_BASE_CMD_HD_EN_QPI	= 0x06,
	SPI_LL_BASE_CMD_HD_WR_END	= 0x07,
	SPI_LL_BASE_CMD_HD_INT0		= 0x08,
	SPI_LL_BASE_CMD_HD_INT1		= 0x09,
	SPI_LL_BASE_CMD_HD_INT2		= 0x0A,
} spi_ll_base_command_t;

void spi_ll_master_init(spi_dev_t *hw);
void spi_ll_slave_init(spi_dev_t *hw);
void spi_ll_slave_hd_init(spi_dev_t *hw);
bool spi_ll_usr_is_done(spi_dev_t *hw);
void spi_ll_master_user_start(spi_dev_t *hw);
void spi_ll_slave_user_start(spi_dev_t *hw);
uint32_t spi_ll_get_running_cmd(spi_dev_t *hw);
void spi_ll_slave_reset(spi_dev_t *hw);
void spi_ll_cpu_tx_fifo_reset(spi_dev_t *hw);
void spi_ll_cpu_rx_fifo_reset(spi_dev_t *hw);
void spi_ll_dma_tx_fifo_reset(spi_dev_t *hw);
void spi_ll_dma_rx_fifo_reset(spi_dev_t *hw);
void spi_ll_infifo_full_clr(spi_dev_t *hw);
void spi_ll_outfifo_empty_clr(spi_dev_t *hw);
void spi_ll_dma_rx_enable(spi_dev_t *hw, bool enable);
void spi_ll_dma_tx_enable(spi_dev_t *hw, bool enable);
void spi_ll_dma_set_rx_eof_generation(spi_dev_t *hw, bool enable);
void spi_ll_write_buffer(spi_dev_t *hw, const uint8_t *buffer_to_send, size_t bitlen);
void spi_ll_write_buffer_byte(spi_dev_t *hw, int byte_id, uint8_t *data, int len);
void spi_ll_read_buffer(spi_dev_t *hw, uint8_t *buffer_to_rcv, size_t bitlen);
void spi_ll_read_buffer_byte(spi_dev_t *hw, int byte_id, uint8_t *out_data, int len);
void spi_ll_master_set_pos_cs(spi_dev_t *hw, int cs, uint32_t pos_cs);
void spi_ll_set_tx_lsbfirst(spi_dev_t *hw, bool lsbfirst);
void spi_ll_set_rx_lsbfirst(spi_dev_t *hw, bool lsbfirst);
void spi_ll_master_set_mode(spi_dev_t *hw, uint8_t mode);
void spi_ll_slave_set_mode(spi_dev_t *hw, const int mode, bool dma_used);
void spi_ll_set_half_duplex(spi_dev_t *hw, bool half_duplex);
void spi_ll_set_sio_mode(spi_dev_t *hw, int sio_mode);
void spi_ll_master_set_line_mode(spi_dev_t *hw, spi_line_mode_t line_mode);
void spi_ll_slave_set_seg_mode(spi_dev_t *hw, bool seg_trans);
void spi_ll_master_select_cs(spi_dev_t *hw, int cs_id);
void spi_ll_master_keep_cs(spi_dev_t *hw, int keep_active);
void spi_ll_master_set_clock_by_reg(spi_dev_t *hw, const spi_ll_clock_val_t *val);
int spi_ll_freq_for_pre_n(int fapb, int pre, int n);
int spi_ll_master_cal_clock(int fapb, int hz, int duty_cycle, spi_ll_clock_val_t *out_reg);
int spi_ll_master_set_clock(spi_dev_t *hw, int fapb, int hz, int duty_cycle);
void spi_ll_set_mosi_delay(spi_dev_t *hw, int delay_mode, int delay_num);
void spi_ll_set_miso_delay(spi_dev_t *hw, int delay_mode, int delay_num);
void spi_ll_master_set_cs_hold(spi_dev_t *hw, int hold);
void spi_ll_master_set_cs_setup(spi_dev_t *hw, uint8_t setup);
void spi_ll_set_mosi_bitlen(spi_dev_t *hw, size_t bitlen);
void spi_ll_set_miso_bitlen(spi_dev_t *hw, size_t bitlen);
void spi_ll_slave_set_rx_bitlen(spi_dev_t *hw, size_t bitlen);
void spi_ll_slave_set_tx_bitlen(spi_dev_t *hw, size_t bitlen);
void spi_ll_set_command_bitlen(spi_dev_t *hw, int bitlen);
void spi_ll_set_addr_bitlen(spi_dev_t *hw, int bitlen);
void spi_ll_set_address(spi_dev_t *hw, uint64_t addr, int addrlen, uint32_t lsbfirst);
void spi_ll_set_command(spi_dev_t *hw, uint16_t cmd, int cmdlen, bool lsbfirst);
void spi_ll_set_dummy(spi_dev_t *hw, int dummy_n);
void spi_ll_enable_miso(spi_dev_t *hw, int enable);
void spi_ll_enable_mosi(spi_dev_t *hw, int enable);
uint32_t spi_ll_slave_get_rcv_bitlen(spi_dev_t *hw);
void spi_ll_enable_intr(spi_dev_t *hw, spi_ll_intr_t intr_mask);
void spi_ll_disable_intr(spi_dev_t *hw, spi_ll_intr_t intr_mask);
void spi_ll_set_intr(spi_dev_t *hw, spi_ll_intr_t intr_mask);
void spi_ll_clear_intr(spi_dev_t *hw, spi_ll_intr_t intr_mask);
bool spi_ll_get_intr(spi_dev_t *hw, spi_ll_intr_t intr_mask);
void spi_ll_disable_int(spi_dev_t *hw);
void spi_ll_clear_int_stat(spi_dev_t *hw);
void spi_ll_set_int_stat(spi_dev_t *hw);
void spi_ll_enable_int(spi_dev_t *hw);
void spi_ll_slave_hd_set_len_cond(spi_dev_t *hw, spi_ll_trans_len_cond_t cond_mask);
int spi_ll_slave_get_rx_byte_len(spi_dev_t *hw);
uint32_t spi_ll_slave_hd_get_last_addr(spi_dev_t *hw);
uint8_t spi_ll_get_slave_hd_base_command(spi_command_t cmd_t);
uint16_t spi_ll_get_slave_hd_command(spi_command_t cmd_t, spi_line_mode_t line_mode);
int spi_ll_get_slave_hd_dummy_bits(spi_line_mode_t line_mode);
