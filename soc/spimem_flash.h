#include <stdlib.h>
#include <sys/param.h> // For MIN/MAX
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#include "soc/spi.h"

#define SPI_FLASH_LL_CLKREG_VAL_5MHZ   {.spimem=SPIMEM_FLASH_LL_CLKREG_VAL_5MHZ}
#define SPI_FLASH_LL_CLKREG_VAL_10MHZ  {.spimem=SPIMEM_FLASH_LL_CLKREG_VAL_10MHZ}
#define SPI_FLASH_LL_CLKREG_VAL_20MHZ  {.spimem=SPIMEM_FLASH_LL_CLKREG_VAL_20MHZ}
#define SPI_FLASH_LL_CLKREG_VAL_26MHZ  {.spimem=SPIMEM_FLASH_LL_CLKREG_VAL_26MHZ}
#define SPI_FLASH_LL_CLKREG_VAL_40MHZ  {.spimem=SPIMEM_FLASH_LL_CLKREG_VAL_40MHZ}
#define SPI_FLASH_LL_CLKREG_VAL_80MHZ  {.spimem=SPIMEM_FLASH_LL_CLKREG_VAL_80MHZ}

#define SPIMEM_FLASH_LL_CLKREG_VAL_5MHZ   ((spimem_flash_ll_clock_reg_t){.val=0x000F070F})   ///< Clock set to 5 MHz
#define SPIMEM_FLASH_LL_CLKREG_VAL_10MHZ  ((spimem_flash_ll_clock_reg_t){.val=0x00070307})   ///< Clock set to 10 MHz
#define SPIMEM_FLASH_LL_CLKREG_VAL_20MHZ  ((spimem_flash_ll_clock_reg_t){.val=0x00030103})   ///< Clock set to 20 MHz
#define SPIMEM_FLASH_LL_CLKREG_VAL_26MHZ  ((spimem_flash_ll_clock_reg_t){.val=0x00020002})   ///< Clock set to 26 MHz
#define SPIMEM_FLASH_LL_CLKREG_VAL_40MHZ  ((spimem_flash_ll_clock_reg_t){.val=0x00010001})   ///< Clock set to 40 MHz
#define SPIMEM_FLASH_LL_CLKREG_VAL_80MHZ  ((spimem_flash_ll_clock_reg_t){.val=0x80000000})   ///< Clock set to 80 MHz

#define spi_flash_ll_get_hw(host_id)  (((host_id)<=SPI1_HOST ? (spi_dev_t*) spimem_flash_ll_get_hw(host_id) \
									  : gpspi_flash_ll_get_hw(host_id)))

#define spi_flash_ll_hw_get_id(dev) ({int dev_id = spimem_flash_ll_hw_get_id(dev); \
									 if (dev_id < 0) {\
										dev_id = gpspi_flash_ll_hw_get_id(dev);\
									 }\
									 dev_id; \
									})


#define spimem_flash_ll_get_hw(host_id)  (((host_id)==SPI1_HOST ?  &SPIMEM1 : NULL ))
#define spimem_flash_ll_hw_get_id(dev)  ((dev) == (void*)&SPIMEM1? SPI1_HOST: -1)

#define SPI_MEM_CTRL_REG(i)          (REG_SPI_MEM_BASE(i) + 0x8)
/* SPI_MEM_FREAD_QIO : R/W ;bitpos:[24] ;default: 1'b0 ; */
/*description: In hardware 0xEB read operation, ADDR phase and DIN phase apply 4 signals(4-bit-
mode). 1: enable 0: disable. .*/
#define SPI_MEM_FREAD_QIO    (1<<(24))
#define SPI_MEM_FREAD_QIO_M  (1<<(24))
#define SPI_MEM_FREAD_QIO_V  0x1
#define SPI_MEM_FREAD_QIO_S  24
/* SPI_MEM_FREAD_DIO : R/W ;bitpos:[23] ;default: 1'b0 ; */
/*description: In hardware 0xBB read operation, ADDR phase and DIN phase apply 2 signals(2-bit-
mode). 1: enable 0: disable. .*/
#define SPI_MEM_FREAD_DIO    (1<<(23))
#define SPI_MEM_FREAD_DIO_M  (1<<(23))
#define SPI_MEM_FREAD_DIO_V  0x1
#define SPI_MEM_FREAD_DIO_S  23
/* SPI_MEM_WRSR_2B : R/W ;bitpos:[22] ;default: 1'b0 ; */
/*description: Two bytes data will be written to status register when it is set. 1: enable 0: d
isable. .*/
#define SPI_MEM_WRSR_2B    (1<<(22))
#define SPI_MEM_WRSR_2B_M  (1<<(22))
#define SPI_MEM_WRSR_2B_V  0x1
#define SPI_MEM_WRSR_2B_S  22
/* SPI_MEM_WP_REG : R/W ;bitpos:[21] ;default: 1'b1 ; */
/*description: Write protect signal output when SPI is idle.  1: output high, 0: output low. .*/
#define SPI_MEM_WP_REG    (1<<(21))
#define SPI_MEM_WP_REG_M  (1<<(21))
#define SPI_MEM_WP_REG_V  0x1
#define SPI_MEM_WP_REG_S  21
/* SPI_MEM_FREAD_QUAD : R/W ;bitpos:[20] ;default: 1'b0 ; */
/*description: In hardware 0x6B read operation, DIN phase apply 4 signals(4-bit-mode). 1: enabl
e 0: disable. .*/
#define SPI_MEM_FREAD_QUAD    (1<<(20))
#define SPI_MEM_FREAD_QUAD_M  (1<<(20))
#define SPI_MEM_FREAD_QUAD_V  0x1
#define SPI_MEM_FREAD_QUAD_S  20
/* SPI_MEM_D_POL : R/W ;bitpos:[19] ;default: 1'b1 ; */
/*description: The bit is used to set MOSI line polarity, 1: high 0, low.*/
#define SPI_MEM_D_POL    (1<<(19))
#define SPI_MEM_D_POL_M  (1<<(19))
#define SPI_MEM_D_POL_V  0x1
#define SPI_MEM_D_POL_S  19
/* SPI_MEM_Q_POL : R/W ;bitpos:[18] ;default: 1'b1 ; */
/*description: The bit is used to set MISO line polarity, 1: high 0, low.*/
#define SPI_MEM_Q_POL    (1<<(18))
#define SPI_MEM_Q_POL_M  (1<<(18))
#define SPI_MEM_Q_POL_V  0x1
#define SPI_MEM_Q_POL_S  18
/* SPI_MEM_RESANDRES : R/W ;bitpos:[15] ;default: 1'b1 ; */
/*description: The Device ID is read out to SPI_MEM_RD_STATUS register,  this bit combine with
spi_mem_flash_res bit. 1: enable 0: disable. .*/
#define SPI_MEM_RESANDRES    (1<<(15))
#define SPI_MEM_RESANDRES_M  (1<<(15))
#define SPI_MEM_RESANDRES_V  0x1
#define SPI_MEM_RESANDRES_S  15
/* SPI_MEM_FREAD_DUAL : R/W ;bitpos:[14] ;default: 1'b0 ; */
/*description: In hardware 0x3B read operation, DIN phase apply 2 signals. 1: enable 0: disable
. .*/
#define SPI_MEM_FREAD_DUAL    (1<<(14))
#define SPI_MEM_FREAD_DUAL_M  (1<<(14))
#define SPI_MEM_FREAD_DUAL_V  0x1
#define SPI_MEM_FREAD_DUAL_S  14
/* SPI_MEM_FASTRD_MODE : R/W ;bitpos:[13] ;default: 1'b1 ; */
/*description: This bit should be set when SPI_MEM_FREAD_QIO, SPI_MEM_FREAD_DIO, SPI_MEM_FREAD_
QUAD or SPI_MEM_FREAD_DUAL is set..*/
#define SPI_MEM_FASTRD_MODE    (1<<(13))
#define SPI_MEM_FASTRD_MODE_M  (1<<(13))
#define SPI_MEM_FASTRD_MODE_V  0x1
#define SPI_MEM_FASTRD_MODE_S  13
/* SPI_MEM_TX_CRC_EN : R/W ;bitpos:[11] ;default: 1'b0 ; */
/*description: For SPI1,  enable crc32 when writing encrypted data to flash. 1: enable 0:disabl
e.*/
#define SPI_MEM_TX_CRC_EN    (1<<(11))
#define SPI_MEM_TX_CRC_EN_M  (1<<(11))
#define SPI_MEM_TX_CRC_EN_V  0x1
#define SPI_MEM_TX_CRC_EN_S  11
/* SPI_MEM_FCS_CRC_EN : R/W ;bitpos:[10] ;default: 1'b0 ; */
/*description: For SPI1,  initialize crc32 module before writing encrypted data to flash. Activ
e low..*/
#define SPI_MEM_FCS_CRC_EN    (1<<(10))
#define SPI_MEM_FCS_CRC_EN_M  (1<<(10))
#define SPI_MEM_FCS_CRC_EN_V  0x1
#define SPI_MEM_FCS_CRC_EN_S  10
/* SPI_MEM_FCMD_OCT : R/W ;bitpos:[9] ;default: 1'b0 ; */
/*description: Set this bit to enable 8-bit-mode(8-bm) in CMD phase..*/
#define SPI_MEM_FCMD_OCT    (1<<(9))
#define SPI_MEM_FCMD_OCT_M  (1<<(9))
#define SPI_MEM_FCMD_OCT_V  0x1
#define SPI_MEM_FCMD_OCT_S  9
/* SPI_MEM_FCMD_QUAD : R/W ;bitpos:[8] ;default: 1'b0 ; */
/*description: Set this bit to enable 4-bit-mode(4-bm) in CMD phase..*/
#define SPI_MEM_FCMD_QUAD    (1<<(8))
#define SPI_MEM_FCMD_QUAD_M  (1<<(8))
#define SPI_MEM_FCMD_QUAD_V  0x1
#define SPI_MEM_FCMD_QUAD_S  8
/* SPI_MEM_FCMD_DUAL : R/W ;bitpos:[7] ;default: 1'b0 ; */
/*description: Set this bit to enable 2-bit-mode(2-bm) in CMD phase..*/
#define SPI_MEM_FCMD_DUAL    (1<<(7))
#define SPI_MEM_FCMD_DUAL_M  (1<<(7))
#define SPI_MEM_FCMD_DUAL_V  0x1
#define SPI_MEM_FCMD_DUAL_S  7
/* SPI_MEM_FADDR_OCT : R/W ;bitpos:[6] ;default: 1'b0 ; */
/*description: Set this bit to enable 8-bit-mode(8-bm) in ADDR phase..*/
#define SPI_MEM_FADDR_OCT    (1<<(6))
#define SPI_MEM_FADDR_OCT_M  (1<<(6))
#define SPI_MEM_FADDR_OCT_V  0x1
#define SPI_MEM_FADDR_OCT_S  6
/* SPI_MEM_FDIN_OCT : R/W ;bitpos:[5] ;default: 1'b0 ; */
/*description: Set this bit to enable 8-bit-mode(8-bm) in DIN phase..*/
#define SPI_MEM_FDIN_OCT    (1<<(5))
#define SPI_MEM_FDIN_OCT_M  (1<<(5))
#define SPI_MEM_FDIN_OCT_V  0x1
#define SPI_MEM_FDIN_OCT_S  5
/* SPI_MEM_FDOUT_OCT : R/W ;bitpos:[4] ;default: 1'b0 ; */
/*description: Set this bit to enable 8-bit-mode(8-bm) in DOUT phase..*/
#define SPI_MEM_FDOUT_OCT    (1<<(4))
#define SPI_MEM_FDOUT_OCT_M  (1<<(4))
#define SPI_MEM_FDOUT_OCT_V  0x1
#define SPI_MEM_FDOUT_OCT_S  4
/* SPI_MEM_FDUMMY_OUT : R/W ;bitpos:[3] ;default: 1'b0 ; */
/*description: In the DUMMY phase the signal level of SPI bus is output by the SPI0 controller..*/
#define SPI_MEM_FDUMMY_OUT    (1<<(3))
#define SPI_MEM_FDUMMY_OUT_M  (1<<(3))
#define SPI_MEM_FDUMMY_OUT_V  0x1
#define SPI_MEM_FDUMMY_OUT_S  3


typedef volatile struct spi_mem_dev_s {
	union {
		struct {
			uint32_t reserved0					   :	17;
			uint32_t flash_pe					   :	1;
			uint32_t usr						   :	1;
			uint32_t flash_hpm					   :	1;
			uint32_t flash_res					   :	1;
			uint32_t flash_dp					   :	1;
			uint32_t flash_ce					   :	1;
			uint32_t flash_be					   :	1;
			uint32_t flash_se					   :	1;
			uint32_t flash_pp					   :	1;
			uint32_t flash_wrsr					   :	1;
			uint32_t flash_rdsr					   :	1;
			uint32_t flash_rdid					   :	1;
			uint32_t flash_wrdi					   :	1;
			uint32_t flash_wren					   :	1;
			uint32_t flash_read					   :	1;
		};
		uint32_t val;
	} cmd;
	uint32_t addr;
	union {
		struct {
			uint32_t reserved0					   :	3;
			uint32_t fdummy_out					   :	1;
			uint32_t fdout_oct					   :	1;
			uint32_t fdin_oct					   :	1;
			uint32_t faddr_oct					   :	1;
			uint32_t fcmd_dual					   :	1;
			uint32_t fcmd_quad					   :	1;
			uint32_t fcmd_oct					   :	1;
			uint32_t fcs_crc_en					   :	1;
			uint32_t tx_crc_en					   :	1;
			uint32_t reserved12					   :	1;
			uint32_t fastrd_mode				   :	1;
			uint32_t fread_dual					   :	1;
			uint32_t resandres					   :	1;
			uint32_t reserved16					   :	2;
			uint32_t q_pol						   :	1;
			uint32_t d_pol						   :	1;
			uint32_t fread_quad					   :	1;
			uint32_t wp							   :	1;
			uint32_t wrsr_2b					   :	1;
			uint32_t fread_dio					   :	1;
			uint32_t fread_qio					   :	1;
			uint32_t reserved25					   :	7;
		};
		uint32_t val;
	} ctrl;
	union {
		struct {
			uint32_t clk_mode					   :	2;
			uint32_t cs_hold_dly_res			   :	10;
			uint32_t reserved2					   :	18;
			uint32_t rxfifo_rst					   :	1;
			uint32_t reserved31					   :	1;
		};
		uint32_t val;
	} ctrl1;
	union {
		struct {
			uint32_t cs_setup_time				   :	5;
			uint32_t cs_hold_time				   :	5;
			uint32_t ecc_cs_hold_time			   :	3;
			uint32_t ecc_skip_page_corner		   :	1;
			uint32_t ecc_16to18_byte_en			   :	1;
			uint32_t reserved15					   :	10;
			uint32_t cs_hold_delay				   :	6;
			uint32_t sync_reset					   :	1;
		};
		uint32_t val;
	} ctrl2;
	spimem_flash_ll_clock_reg_t clock;
	union {
		struct {
			uint32_t reserved0					   :	6;
			uint32_t cs_hold					   :	1;
			uint32_t cs_setup					   :	1;
			uint32_t reserved8					   :	1;
			uint32_t ck_out_edge				   :	1;
			uint32_t reserved10					   :	2;
			uint32_t fwrite_dual				   :	1;
			uint32_t fwrite_quad				   :	1;
			uint32_t fwrite_dio					   :	1;
			uint32_t fwrite_qio					   :	1;
			uint32_t reserved16					   :	8;
			uint32_t usr_miso_highpart			   :	1;
			uint32_t usr_mosi_highpart			   :	1;
			uint32_t usr_dummy_idle				   :	1;
			uint32_t usr_mosi					   :	1;
			uint32_t usr_miso					   :	1;
			uint32_t usr_dummy					   :	1;
			uint32_t usr_addr					   :	1;
			uint32_t usr_command				   :	1;
		};
		uint32_t val;
	} user;
	union {
		struct {
			uint32_t usr_dummy_cyclelen			   :	6;
			uint32_t reserved6					   :	20;
			uint32_t usr_addr_bitlen			   :	6;
		};
		uint32_t val;
	} user1;
	union {
		struct {
			uint32_t usr_command_value			   :	16;
			uint32_t reserved16					   :	12;
			uint32_t usr_command_bitlen			   :	4;
		};
		uint32_t val;
	} user2;
	union {
		struct {
			uint32_t usr_mosi_bit_len			   :	10;
			uint32_t reserved10					   :	22;
		};
		uint32_t val;
	} mosi_dlen;
	union {
		struct {
			uint32_t usr_miso_bit_len			   :	10;
			uint32_t reserved10					   :	22;
		};
		uint32_t val;
	} miso_dlen;
	union {
		struct {
			uint32_t status						   :	16;
			uint32_t wb_mode					   :	8;
			uint32_t reserved24					   :	8;
		};
		uint32_t val;
	} rd_status;
	uint32_t ext_addr;
	union {
		struct {
			uint32_t cs0_dis					   :	1;
			uint32_t cs1_dis					   :	1;
			uint32_t reserved0					   :	5;
			uint32_t fsub_pin					   :	1;
			uint32_t ssub_pin					   :	1;
			uint32_t ck_idle_edge				   :	1;
			uint32_t cs_keep_active				   :	1;
			uint32_t auto_per					   :	1;
			uint32_t reserved12					   :	20;
		};
		uint32_t val;
	} misc;
	uint32_t tx_crc;
	union {
		struct {
			uint32_t req_en						   :	1;
			uint32_t usr_cmd_4byte				   :	1;
			uint32_t flash_usr_cmd				   :	1;
			uint32_t fdin_dual					   :	1;
			uint32_t fdout_dual					   :	1;
			uint32_t faddr_dual					   :	1;
			uint32_t fdin_quad					   :	1;
			uint32_t fdout_quad					   :	1;
			uint32_t faddr_quad					   :	1;
			uint32_t reserved9					   :	23;
		};
		uint32_t val;
	} cache_fctrl;
	union {
		struct {
			uint32_t usr_scmd_4byte				   :	1;
			uint32_t usr_sram_dio				   :	1;
			uint32_t usr_sram_qio				   :	1;
			uint32_t usr_wr_sram_dummy			   :	1;
			uint32_t usr_rd_sram_dummy			   :	1;
			uint32_t usr_rcmd					   :	1;
			uint32_t sram_rdummy_cyclelen		   :	6;
			uint32_t reserved12					   :	2;
			uint32_t sram_addr_bitlen			   :	6;
			uint32_t usr_wcmd					   :	1;
			uint32_t sram_oct					   :	1;
			uint32_t sram_wdummy_cyclelen		   :	6;
			uint32_t reserved28					   :	4;
		};
		uint32_t val;
	} cache_sctrl;
	union {
		struct {
			uint32_t sclk_mode					   :	2;
			uint32_t swb_mode					   :	8;
			uint32_t sdin_dual					   :	1;
			uint32_t sdout_dual					   :	1;
			uint32_t saddr_dual					   :	1;
			uint32_t scmd_dual					   :	1;
			uint32_t sdin_quad					   :	1;
			uint32_t sdout_quad					   :	1;
			uint32_t saddr_quad					   :	1;
			uint32_t scmd_quad					   :	1;
			uint32_t sdin_oct					   :	1;
			uint32_t sdout_oct					   :	1;
			uint32_t saddr_oct					   :	1;
			uint32_t scmd_oct					   :	1;
			uint32_t sdummy_out					   :	1;
			uint32_t reserved23					   :	9;
		};
		uint32_t val;
	} sram_cmd;
	union {
		struct {
			uint32_t usr_rd_cmd_value			   :	16;
			uint32_t reserved16					   :	12;
			uint32_t usr_rd_cmd_bitlen			   :	4;
		};
		uint32_t val;
	} sram_drd_cmd;
	union {
		struct {
			uint32_t usr_wr_cmd_value			   :	16;
			uint32_t reserved16					   :	12;
			uint32_t usr_wr_cmd_bitlen			   :	4;
		};
		uint32_t val;
	} sram_dwr_cmd;
	union {
		struct {
			uint32_t cnt_l						   :	8;
			uint32_t cnt_h						   :	8;
			uint32_t cnt_n						   :	8;
			uint32_t reserved24					   :	7;
			uint32_t equ_sysclk					   :	1;
		};
		uint32_t val;
	} sram_clk;
	union {
		struct {
			uint32_t st							   :	3;
			uint32_t reserved3					   :	29;
		};
		uint32_t val;
	} fsm;
	uint32_t data_buf[16];
	union {
		struct {
			uint32_t waiti_en					   :	1;
			uint32_t waiti_dummy				   :	1;
			uint32_t waiti_cmd					   :	8;
			uint32_t waiti_dummy_cyclelen		   :	6;
			uint32_t reserved16					   :	16;
		};
		uint32_t val;
	} flash_waiti_ctrl;
	union {
		struct {
			uint32_t flash_per					   :	1;
			uint32_t flash_pes					   :	1;
			uint32_t flash_per_wait_en			   :	1;
			uint32_t flash_pes_wait_en			   :	1;
			uint32_t pes_per_en					   :	1;
			uint32_t pesr_idle_en				   :	1;
			uint32_t reserved6					   :	26;
		};
		uint32_t val;
	} flash_sus_cmd;
	union {
		struct {
			uint32_t flash_pes_en				   :	1;
			uint32_t flash_per_command			   :	8;
			uint32_t flash_pes_command			   :	8;
			uint32_t reserved17					   :	15;
		};
		uint32_t val;
	} flash_sus_ctrl;
	union {
		struct {
			uint32_t flash_sus					   :	1;
			uint32_t reserved1					   :	1;
			uint32_t flash_hpm_dly_256			   :	1;
			uint32_t flash_res_dly_256			   :	1;
			uint32_t flash_dp_dly_256			   :	1;
			uint32_t flash_per_dly_256			   :	1;
			uint32_t flash_pes_dly_256			   :	1;
			uint32_t reserved7					   :	25;
		};
		uint32_t val;
	} sus_status;
	union {
		struct {
			uint32_t timing_clk_ena				   :	1;
			uint32_t timing_cali				   :	1;
			uint32_t extra_dummy_cyclelen		   :	3;
			uint32_t reserved5					   :	27;
		};
		uint32_t val;
	} timing_cali;
	union {
		struct {
			uint32_t din0_mode					   :	3;
			uint32_t din1_mode					   :	3;
			uint32_t din2_mode					   :	3;
			uint32_t din3_mode					   :	3;
			uint32_t din4_mode					   :	3;
			uint32_t din5_mode					   :	3;
			uint32_t din6_mode					   :	3;
			uint32_t din7_mode					   :	3;
			uint32_t dins_mode					   :	3;
			uint32_t reserved27					   :	5;
		};
		uint32_t val;
	} din_mode;
	union {
		struct {
			uint32_t din0_num					   :	2;
			uint32_t din1_num					   :	2;
			uint32_t din2_num					   :	2;
			uint32_t din3_num					   :	2;
			uint32_t din4_num					   :	2;
			uint32_t din5_num					   :	2;
			uint32_t din6_num					   :	2;
			uint32_t din7_num					   :	2;
			uint32_t dins_num					   :	2;
			uint32_t reserved18					   :	14;
		};
		uint32_t val;
	} din_num;
	union {
		struct {
			uint32_t dout0_mode					   :	1;
			uint32_t dout1_mode					   :	1;
			uint32_t dout2_mode					   :	1;
			uint32_t dout3_mode					   :	1;
			uint32_t dout4_mode					   :	1;
			uint32_t dout5_mode					   :	1;
			uint32_t dout6_mode					   :	1;
			uint32_t dout7_mode					   :	1;
			uint32_t douts_mode					   :	1;
			uint32_t reserved9					   :	23;
		};
		uint32_t val;
	} dout_mode;
	uint32_t reserved_b8;
	union {
		struct {
			uint32_t smem_timing_clk_ena		   :	1;
			uint32_t smem_timing_cali			   :	1;
			uint32_t smem_extra_dummy_cyclelen	   :	3;
			uint32_t reserved5					   :	27;
		};
		uint32_t val;
	} spi_smem_timing_cali;
	union {
		struct {
			uint32_t smem_din0_mode				   :	3;
			uint32_t smem_din1_mode				   :	3;
			uint32_t smem_din2_mode				   :	3;
			uint32_t smem_din3_mode				   :	3;
			uint32_t smem_din4_mode				   :	3;
			uint32_t smem_din5_mode				   :	3;
			uint32_t smem_din6_mode				   :	3;
			uint32_t smem_din7_mode				   :	3;
			uint32_t smem_dins_mode				   :	3;
			uint32_t reserved27					   :	5;
		};
		uint32_t val;
	} spi_smem_din_mode;
	union {
		struct {
			uint32_t smem_din0_num				   :	2;
			uint32_t smem_din1_num				   :	2;
			uint32_t smem_din2_num				   :	2;
			uint32_t smem_din3_num				   :	2;
			uint32_t smem_din4_num				   :	2;
			uint32_t smem_din5_num				   :	2;
			uint32_t smem_din6_num				   :	2;
			uint32_t smem_din7_num				   :	2;
			uint32_t smem_dins_num				   :	2;
			uint32_t reserved18					   :	14;
		};
		uint32_t val;
	} spi_smem_din_num;
	union {
		struct {
			uint32_t smem_dout0_mode			   :	1;
			uint32_t smem_dout1_mode			   :	1;
			uint32_t smem_dout2_mode			   :	1;
			uint32_t smem_dout3_mode			   :	1;
			uint32_t smem_dout4_mode			   :	1;
			uint32_t smem_dout5_mode			   :	1;
			uint32_t smem_dout6_mode			   :	1;
			uint32_t smem_dout7_mode			   :	1;
			uint32_t smem_douts_mode			   :	1;
			uint32_t reserved9					   :	23;
		};
		uint32_t val;
	} spi_smem_dout_mode;
	union {
		struct {
			uint32_t ecc_err_int_num			   :	8;
			uint32_t fmem_ecc_err_int_en		   :	1;
			uint32_t reserved9					   :	23;
		};
		uint32_t val;
	} ecc_ctrl;
	uint32_t ecc_err_addr;
	union {
		struct {
			uint32_t reserved0					   :	6;
			uint32_t ecc_data_err_bit			   :	7;
			uint32_t ecc_chk_err_bit			   :	3;
			uint32_t ecc_byte_err				   :	1;
			uint32_t ecc_err_cnt				   :	8;
			uint32_t reserved25					   :	7;
		};
		uint32_t val;
	} ecc_err_bit;
	uint32_t reserved_d8;
	union {
		struct {
			uint32_t smem_cs_setup				   :	1;
			uint32_t smem_cs_hold				   :	1;
			uint32_t smem_cs_setup_time			   :	5;
			uint32_t smem_cs_hold_time			   :	5;
			uint32_t smem_ecc_cs_hold_time		   :	3;
			uint32_t smem_ecc_skip_page_corner	   :	1;
			uint32_t smem_ecc_16to18_byte_en	   :	1;
			uint32_t reserved17					   :	7;
			uint32_t smem_ecc_err_int_en		   :	1;
			uint32_t smem_cs_hold_delay			   :	6;
			uint32_t reserved31					   :	1;
		};
		uint32_t val;
	} spi_smem_ac;
	union {
		struct {
			uint32_t fmem_ddr_en				   :	1;
			uint32_t fmem_var_dummy				   :	1;
			uint32_t fmem_ddr_rdat_swp			   :	1;
			uint32_t fmem_ddr_wdat_swp			   :	1;
			uint32_t fmem_ddr_cmd_dis			   :	1;
			uint32_t fmem_outminbytelen			   :	7;
			uint32_t fmem_tx_ddr_msk_en			   :	1;
			uint32_t fmem_rx_ddr_msk_en			   :	1;
			uint32_t fmem_usr_ddr_dqs_thd		   :	7;
			uint32_t fmem_ddr_dqs_loop			   :	1;
			uint32_t fmem_ddr_dqs_loop_mode		   :	1;
			uint32_t reserved23					   :	1;
			uint32_t fmem_clk_diff_en			   :	1;
			uint32_t fmem_hyperbus_mode			   :	1;
			uint32_t fmem_dqs_ca_in				   :	1;
			uint32_t fmem_hyperbus_dummy_2x		   :	1;
			uint32_t fmem_clk_diff_inv			   :	1;
			uint32_t fmem_octa_ram_addr			   :	1;
			uint32_t fmem_hyperbus_ca			   :	1;
			uint32_t reserved31					   :	1;
		};
		uint32_t val;
	} ddr;
	union {
		struct {
			uint32_t smem_ddr_en				   :	1;
			uint32_t smem_var_dummy				   :	1;
			uint32_t smem_ddr_rdat_swp			   :	1;
			uint32_t smem_ddr_wdat_swp			   :	1;
			uint32_t smem_ddr_cmd_dis			   :	1;
			uint32_t smem_outminbytelen			   :	7;
			uint32_t smem_tx_ddr_msk_en			   :	1;
			uint32_t smem_rx_ddr_msk_en			   :	1;
			uint32_t smem_usr_ddr_dqs_thd		   :	7;
			uint32_t smem_ddr_dqs_loop			   :	1;
			uint32_t smem_ddr_dqs_loop_mode		   :	1;
			uint32_t reserved23					   :	1;
			uint32_t smem_clk_diff_en			   :	1;
			uint32_t smem_hyperbus_mode			   :	1;
			uint32_t smem_dqs_ca_in				   :	1;
			uint32_t smem_hyperbus_dummy_2x		   :	1;
			uint32_t smem_clk_diff_inv			   :	1;
			uint32_t smem_octa_ram_addr			   :	1;
			uint32_t smem_hyperbus_ca			   :	1;
			uint32_t reserved31					   :	1;
		};
		uint32_t val;
	} spi_smem_ddr;
	union {
		struct {
			uint32_t clk_en						   :	1;
			uint32_t reserved1					   :	31;
		};
		uint32_t val;
	} clock_gate;
	union {
		struct {
			uint32_t core_clk_sel				   :	2;
			uint32_t reserved2					   :	30;
		};
		uint32_t val;
	} core_clk_sel;
	union {
		struct {
			uint32_t per_end_en					   :	1;
			uint32_t pes_end_en					   :	1;
			uint32_t total_trans_end_en			   :	1;
			uint32_t brown_out_en				   :	1;
			uint32_t ecc_err_en					   :	1;
			uint32_t reserved5					   :	27;
		};
		uint32_t val;
	} int_ena;
	union {
		struct {
			uint32_t per_end_int_clr			   :	1;
			uint32_t pes_end_int_clr			   :	1;
			uint32_t total_trans_end_int_clr	   :	1;
			uint32_t brown_out_int_clr			   :	1;
			uint32_t ecc_err_int_clr			   :	1;
			uint32_t reserved5					   :	27;
		};
		uint32_t val;
	} int_clr;
	union {
		struct {
			uint32_t per_end_int_raw			   :	1;
			uint32_t pes_end_int_raw			   :	1;
			uint32_t total_trans_end_int_raw	   :	1;
			uint32_t brown_out_int_raw			   :	1;
			uint32_t ecc_err_int_raw			   :	1;
			uint32_t reserved5					   :	27;
		};
		uint32_t val;
	} int_raw;
	union {
		struct {
			uint32_t per_end_int_st				   :	1;
			uint32_t pes_end_int_st				   :	1;
			uint32_t total_trans_end_int_st		   :	1;
			uint32_t brown_out_int_st			   :	1;
			uint32_t ecc_err_int_st				   :	1;
			uint32_t reserved5					   :	27;
		};
		uint32_t val;
	} int_st;
	uint32_t reserved_100;
	uint32_t reserved_104;
	uint32_t reserved_108;
	uint32_t reserved_10c;
	uint32_t reserved_110;
	uint32_t reserved_114;
	uint32_t reserved_118;
	uint32_t reserved_11c;
	uint32_t reserved_120;
	uint32_t reserved_124;
	uint32_t reserved_128;
	uint32_t reserved_12c;
	uint32_t reserved_130;
	uint32_t reserved_134;
	uint32_t reserved_138;
	uint32_t reserved_13c;
	uint32_t reserved_140;
	uint32_t reserved_144;
	uint32_t reserved_148;
	uint32_t reserved_14c;
	uint32_t reserved_150;
	uint32_t reserved_154;
	uint32_t reserved_158;
	uint32_t reserved_15c;
	uint32_t reserved_160;
	uint32_t reserved_164;
	uint32_t reserved_168;
	uint32_t reserved_16c;
	uint32_t reserved_170;
	uint32_t reserved_174;
	uint32_t reserved_178;
	uint32_t reserved_17c;
	uint32_t reserved_180;
	uint32_t reserved_184;
	uint32_t reserved_188;
	uint32_t reserved_18c;
	uint32_t reserved_190;
	uint32_t reserved_194;
	uint32_t reserved_198;
	uint32_t reserved_19c;
	uint32_t reserved_1a0;
	uint32_t reserved_1a4;
	uint32_t reserved_1a8;
	uint32_t reserved_1ac;
	uint32_t reserved_1b0;
	uint32_t reserved_1b4;
	uint32_t reserved_1b8;
	uint32_t reserved_1bc;
	uint32_t reserved_1c0;
	uint32_t reserved_1c4;
	uint32_t reserved_1c8;
	uint32_t reserved_1cc;
	uint32_t reserved_1d0;
	uint32_t reserved_1d4;
	uint32_t reserved_1d8;
	uint32_t reserved_1dc;
	uint32_t reserved_1e0;
	uint32_t reserved_1e4;
	uint32_t reserved_1e8;
	uint32_t reserved_1ec;
	uint32_t reserved_1f0;
	uint32_t reserved_1f4;
	uint32_t reserved_1f8;
	uint32_t reserved_1fc;
	uint32_t reserved_200;
	uint32_t reserved_204;
	uint32_t reserved_208;
	uint32_t reserved_20c;
	uint32_t reserved_210;
	uint32_t reserved_214;
	uint32_t reserved_218;
	uint32_t reserved_21c;
	uint32_t reserved_220;
	uint32_t reserved_224;
	uint32_t reserved_228;
	uint32_t reserved_22c;
	uint32_t reserved_230;
	uint32_t reserved_234;
	uint32_t reserved_238;
	uint32_t reserved_23c;
	uint32_t reserved_240;
	uint32_t reserved_244;
	uint32_t reserved_248;
	uint32_t reserved_24c;
	uint32_t reserved_250;
	uint32_t reserved_254;
	uint32_t reserved_258;
	uint32_t reserved_25c;
	uint32_t reserved_260;
	uint32_t reserved_264;
	uint32_t reserved_268;
	uint32_t reserved_26c;
	uint32_t reserved_270;
	uint32_t reserved_274;
	uint32_t reserved_278;
	uint32_t reserved_27c;
	uint32_t reserved_280;
	uint32_t reserved_284;
	uint32_t reserved_288;
	uint32_t reserved_28c;
	uint32_t reserved_290;
	uint32_t reserved_294;
	uint32_t reserved_298;
	uint32_t reserved_29c;
	uint32_t reserved_2a0;
	uint32_t reserved_2a4;
	uint32_t reserved_2a8;
	uint32_t reserved_2ac;
	uint32_t reserved_2b0;
	uint32_t reserved_2b4;
	uint32_t reserved_2b8;
	uint32_t reserved_2bc;
	uint32_t reserved_2c0;
	uint32_t reserved_2c4;
	uint32_t reserved_2c8;
	uint32_t reserved_2cc;
	uint32_t reserved_2d0;
	uint32_t reserved_2d4;
	uint32_t reserved_2d8;
	uint32_t reserved_2dc;
	uint32_t reserved_2e0;
	uint32_t reserved_2e4;
	uint32_t reserved_2e8;
	uint32_t reserved_2ec;
	uint32_t reserved_2f0;
	uint32_t reserved_2f4;
	uint32_t reserved_2f8;
	uint32_t reserved_2fc;
	uint32_t reserved_300;
	uint32_t reserved_304;
	uint32_t reserved_308;
	uint32_t reserved_30c;
	uint32_t reserved_310;
	uint32_t reserved_314;
	uint32_t reserved_318;
	uint32_t reserved_31c;
	uint32_t reserved_320;
	uint32_t reserved_324;
	uint32_t reserved_328;
	uint32_t reserved_32c;
	uint32_t reserved_330;
	uint32_t reserved_334;
	uint32_t reserved_338;
	uint32_t reserved_33c;
	uint32_t reserved_340;
	uint32_t reserved_344;
	uint32_t reserved_348;
	uint32_t reserved_34c;
	uint32_t reserved_350;
	uint32_t reserved_354;
	uint32_t reserved_358;
	uint32_t reserved_35c;
	uint32_t reserved_360;
	uint32_t reserved_364;
	uint32_t reserved_368;
	uint32_t reserved_36c;
	uint32_t reserved_370;
	uint32_t reserved_374;
	uint32_t reserved_378;
	uint32_t reserved_37c;
	uint32_t reserved_380;
	uint32_t reserved_384;
	uint32_t reserved_388;
	uint32_t reserved_38c;
	uint32_t reserved_390;
	uint32_t reserved_394;
	uint32_t reserved_398;
	uint32_t reserved_39c;
	uint32_t reserved_3a0;
	uint32_t reserved_3a4;
	uint32_t reserved_3a8;
	uint32_t reserved_3ac;
	uint32_t reserved_3b0;
	uint32_t reserved_3b4;
	uint32_t reserved_3b8;
	uint32_t reserved_3bc;
	uint32_t reserved_3c0;
	uint32_t reserved_3c4;
	uint32_t reserved_3c8;
	uint32_t reserved_3cc;
	uint32_t reserved_3d0;
	uint32_t reserved_3d4;
	uint32_t reserved_3d8;
	uint32_t reserved_3dc;
	uint32_t reserved_3e0;
	uint32_t reserved_3e4;
	uint32_t reserved_3e8;
	uint32_t reserved_3ec;
	uint32_t reserved_3f0;
	uint32_t reserved_3f4;
	uint32_t reserved_3f8;
	union {
		struct {
			uint32_t reg_smem_spiclk_fun_drv	   :	2;
			uint32_t fmem_spiclk_fun_drv		   :	2;
			uint32_t reg_spiclk_pad_drv_ctl_en	   :	1;
			uint32_t date						   :	23;
			uint32_t reserved28					   :	4;
		};
		uint32_t val;
	} date;
} spi_mem_dev_t;

extern spi_mem_dev_t SPIMEM0;
extern spi_mem_dev_t SPIMEM1;

void spimem_flash_ll_reset(spi_mem_dev_t *dev);
bool spimem_flash_ll_cmd_is_done(const spi_mem_dev_t *dev);
void spimem_flash_ll_erase_chip(spi_mem_dev_t *dev);
void spimem_flash_ll_erase_sector(spi_mem_dev_t *dev);
void spimem_flash_ll_erase_block(spi_mem_dev_t *dev);
void spimem_flash_ll_suspend(spi_mem_dev_t *dev);
void spimem_flash_ll_resume(spi_mem_dev_t *dev);
void spimem_flash_ll_auto_suspend_init(spi_mem_dev_t *dev, bool auto_sus);
void spimem_flash_ll_auto_resume_init(spi_mem_dev_t *dev, bool auto_res);
void spimem_flash_ll_suspend_cmd_setup(spi_mem_dev_t *dev, uint32_t sus_cmd);
void spimem_flash_ll_resume_cmd_setup(spi_mem_dev_t *dev, uint32_t res_cmd);
void spimem_flash_ll_rd_sus_cmd_setup(spi_mem_dev_t *dev, uint32_t pesr_cmd);
void spimem_flash_ll_sus_check_sus_setup(spi_mem_dev_t *dev, bool sus_check_sus_en);
void spimem_flash_ll_res_check_sus_setup(spi_mem_dev_t *dev, bool res_check_sus_en);
void spimem_flash_ll_set_read_sus_status(spi_mem_dev_t *dev, uint32_t sus_mask);
void spimem_flash_ll_auto_wait_idle_init(spi_mem_dev_t *dev, bool auto_waiti);
bool spimem_flash_ll_sus_status(spi_mem_dev_t *dev);
void spimem_flash_ll_set_write_protect(spi_mem_dev_t *dev, bool wp);
void spimem_flash_ll_get_buffer_data(spi_mem_dev_t *dev, void *buffer, uint32_t read_len);
void spimem_flash_ll_set_buffer_data(spi_mem_dev_t *dev, const void *buffer, uint32_t length);
void spimem_flash_ll_program_page(spi_mem_dev_t *dev, const void *buffer, uint32_t length);
void spimem_flash_ll_user_start(spi_mem_dev_t *dev);
bool spimem_flash_ll_host_idle(const spi_mem_dev_t *dev);
void spimem_flash_ll_read_phase(spi_mem_dev_t *dev);
void spimem_flash_ll_set_cs_pin(spi_mem_dev_t *dev, int pin);
void spimem_flash_ll_set_read_mode(spi_mem_dev_t *dev, esp_flash_io_mode_t read_mode);
void spimem_flash_ll_set_clock(spi_mem_dev_t *dev, spimem_flash_ll_clock_reg_t *clock_val);
void spimem_flash_ll_set_miso_bitlen(spi_mem_dev_t *dev, uint32_t bitlen);
void spimem_flash_ll_set_mosi_bitlen(spi_mem_dev_t *dev, uint32_t bitlen);
void spimem_flash_ll_set_command(spi_mem_dev_t *dev, uint32_t command, uint32_t bitlen);
int spimem_flash_ll_get_addr_bitlen(spi_mem_dev_t *dev);
void spimem_flash_ll_set_addr_bitlen(spi_mem_dev_t *dev, uint32_t bitlen);
void spimem_flash_ll_set_address(spi_mem_dev_t *dev, uint32_t addr);
void spimem_flash_ll_set_usr_address(spi_mem_dev_t *dev, uint32_t addr, uint32_t bitlen);
void spimem_flash_ll_set_dummy(spi_mem_dev_t *dev, uint32_t dummy_n);
void spimem_flash_ll_set_dummy_out(spi_mem_dev_t *dev, uint32_t out_en, uint32_t out_lev);
void spimem_flash_ll_set_hold(spi_mem_dev_t *dev, uint32_t hold_n);
void spimem_flash_ll_set_cs_setup(spi_mem_dev_t *dev, uint32_t cs_setup_time);
void spimem_flash_ll_set_extra_dummy(spi_mem_dev_t *dev, uint32_t extra_dummy);
