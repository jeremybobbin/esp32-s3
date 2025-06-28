#pragma once 

#include <stdlib.h>
#include <string.h>

//#include "rom/cache.h"
//#include "soc/spimem_flash.h"

#define ARRAY_SIZE(arr) (sizeof(arr)/sizeof(*(arr)))

#define SPI_TIMING_CONFIG_NUM_DEFAULT               20

#define SPI_DMA_INT_ENA_REG(i)          (REG_SPI_BASE(i) + 0x34)
#define SPI_APP1_INT_ENA    (1<<(20))
#define SPI_APP1_INT_ENA_M  (1<<(20))
#define SPI_APP1_INT_ENA_V  0x1
#define SPI_APP1_INT_ENA_S  20
#define SPI_APP2_INT_ENA    (1<<(19))
#define SPI_APP2_INT_ENA_M  (1<<(19))
#define SPI_APP2_INT_ENA_V  0x1
#define SPI_APP2_INT_ENA_S  19
/* SPI_MST_TX_AFIFO_REMPTY_ERR_INT_ENA : R/W ;bitpos:[18] ;default: 1'b0 ; */
/*description: The enable bit for SPI_MST_TX_AFIFO_REMPTY_ERR_INT interrupt..*/
#define SPI_MST_TX_AFIFO_REMPTY_ERR_INT_ENA    (1<<(18))
#define SPI_MST_TX_AFIFO_REMPTY_ERR_INT_ENA_M  (1<<(18))
#define SPI_MST_TX_AFIFO_REMPTY_ERR_INT_ENA_V  0x1
#define SPI_MST_TX_AFIFO_REMPTY_ERR_INT_ENA_S  18
/* SPI_MST_RX_AFIFO_WFULL_ERR_INT_ENA : R/W ;bitpos:[17] ;default: 1'b0 ; */
/*description: The enable bit for SPI_MST_RX_AFIFO_WFULL_ERR_INT interrupt..*/
#define SPI_MST_RX_AFIFO_WFULL_ERR_INT_ENA    (1<<(17))
#define SPI_MST_RX_AFIFO_WFULL_ERR_INT_ENA_M  (1<<(17))
#define SPI_MST_RX_AFIFO_WFULL_ERR_INT_ENA_V  0x1
#define SPI_MST_RX_AFIFO_WFULL_ERR_INT_ENA_S  17
/* SPI_SLV_CMD_ERR_INT_ENA : R/W ;bitpos:[16] ;default: 1'b0 ; */
/*description: The enable bit for SPI_SLV_CMD_ERR_INT interrupt..*/
#define SPI_SLV_CMD_ERR_INT_ENA    (1<<(16))
#define SPI_SLV_CMD_ERR_INT_ENA_M  (1<<(16))
#define SPI_SLV_CMD_ERR_INT_ENA_V  0x1
#define SPI_SLV_CMD_ERR_INT_ENA_S  16
/* SPI_SLV_BUF_ADDR_ERR_INT_ENA : R/W ;bitpos:[15] ;default: 1'b0 ; */
/*description: The enable bit for SPI_SLV_BUF_ADDR_ERR_INT interrupt..*/
#define SPI_SLV_BUF_ADDR_ERR_INT_ENA    (1<<(15))
#define SPI_SLV_BUF_ADDR_ERR_INT_ENA_M  (1<<(15))
#define SPI_SLV_BUF_ADDR_ERR_INT_ENA_V  0x1
#define SPI_SLV_BUF_ADDR_ERR_INT_ENA_S  15
/* SPI_SEG_MAGIC_ERR_INT_ENA : R/W ;bitpos:[14] ;default: 1'b0 ; */
/*description: The enable bit for SPI_SEG_MAGIC_ERR_INT interrupt..*/
#define SPI_SEG_MAGIC_ERR_INT_ENA    (1<<(14))
#define SPI_SEG_MAGIC_ERR_INT_ENA_M  (1<<(14))
#define SPI_SEG_MAGIC_ERR_INT_ENA_V  0x1
#define SPI_SEG_MAGIC_ERR_INT_ENA_S  14
/* SPI_DMA_SEG_TRANS_DONE_INT_ENA : R/W ;bitpos:[13] ;default: 1'b0 ; */
/*description: The enable bit for SPI_DMA_SEG_TRANS_DONE_INT interrupt..*/
#define SPI_DMA_SEG_TRANS_DONE_INT_ENA    (1<<(13))
#define SPI_DMA_SEG_TRANS_DONE_INT_ENA_M  (1<<(13))
#define SPI_DMA_SEG_TRANS_DONE_INT_ENA_V  0x1
#define SPI_DMA_SEG_TRANS_DONE_INT_ENA_S  13
/* SPI_TRANS_DONE_INT_ENA : R/W ;bitpos:[12] ;default: 1'b0 ; */
/*description: The enable bit for SPI_TRANS_DONE_INT interrupt..*/
#define SPI_TRANS_DONE_INT_ENA    (1<<(12))
#define SPI_TRANS_DONE_INT_ENA_M  (1<<(12))
#define SPI_TRANS_DONE_INT_ENA_V  0x1
#define SPI_TRANS_DONE_INT_ENA_S  12
/* SPI_SLV_WR_BUF_DONE_INT_ENA : R/W ;bitpos:[11] ;default: 1'b0 ; */
/*description: The enable bit for SPI_SLV_WR_BUF_DONE_INT interrupt..*/
#define SPI_SLV_WR_BUF_DONE_INT_ENA    (1<<(11))
#define SPI_SLV_WR_BUF_DONE_INT_ENA_M  (1<<(11))
#define SPI_SLV_WR_BUF_DONE_INT_ENA_V  0x1
#define SPI_SLV_WR_BUF_DONE_INT_ENA_S  11
/* SPI_SLV_RD_BUF_DONE_INT_ENA : R/W ;bitpos:[10] ;default: 1'b0 ; */
/*description: The enable bit for SPI_SLV_RD_BUF_DONE_INT interrupt..*/
#define SPI_SLV_RD_BUF_DONE_INT_ENA    (1<<(10))
#define SPI_SLV_RD_BUF_DONE_INT_ENA_M  (1<<(10))
#define SPI_SLV_RD_BUF_DONE_INT_ENA_V  0x1
#define SPI_SLV_RD_BUF_DONE_INT_ENA_S  10
/* SPI_SLV_WR_DMA_DONE_INT_ENA : R/W ;bitpos:[9] ;default: 1'b0 ; */
/*description: The enable bit for SPI_SLV_WR_DMA_DONE_INT interrupt..*/
#define SPI_SLV_WR_DMA_DONE_INT_ENA    (1<<(9))
#define SPI_SLV_WR_DMA_DONE_INT_ENA_M  (1<<(9))
#define SPI_SLV_WR_DMA_DONE_INT_ENA_V  0x1
#define SPI_SLV_WR_DMA_DONE_INT_ENA_S  9
/* SPI_SLV_RD_DMA_DONE_INT_ENA : R/W ;bitpos:[8] ;default: 1'b0 ; */
/*description: The enable bit for SPI_SLV_RD_DMA_DONE_INT interrupt..*/
#define SPI_SLV_RD_DMA_DONE_INT_ENA    (1<<(8))
#define SPI_SLV_RD_DMA_DONE_INT_ENA_M  (1<<(8))
#define SPI_SLV_RD_DMA_DONE_INT_ENA_V  0x1
#define SPI_SLV_RD_DMA_DONE_INT_ENA_S  8
/* SPI_SLV_CMDA_INT_ENA : R/W ;bitpos:[7] ;default: 1'b0 ; */
/*description: The enable bit for SPI slave CMDA interrupt..*/
#define SPI_SLV_CMDA_INT_ENA    (1<<(7))
#define SPI_SLV_CMDA_INT_ENA_M  (1<<(7))
#define SPI_SLV_CMDA_INT_ENA_V  0x1
#define SPI_SLV_CMDA_INT_ENA_S  7
/* SPI_SLV_CMD9_INT_ENA : R/W ;bitpos:[6] ;default: 1'b0 ; */
/*description: The enable bit for SPI slave CMD9 interrupt..*/
#define SPI_SLV_CMD9_INT_ENA    (1<<(6))
#define SPI_SLV_CMD9_INT_ENA_M  (1<<(6))
#define SPI_SLV_CMD9_INT_ENA_V  0x1
#define SPI_SLV_CMD9_INT_ENA_S  6
/* SPI_SLV_CMD8_INT_ENA : R/W ;bitpos:[5] ;default: 1'b0 ; */
/*description: The enable bit for SPI slave CMD8 interrupt..*/
#define SPI_SLV_CMD8_INT_ENA    (1<<(5))
#define SPI_SLV_CMD8_INT_ENA_M  (1<<(5))
#define SPI_SLV_CMD8_INT_ENA_V  0x1
#define SPI_SLV_CMD8_INT_ENA_S  5
/* SPI_SLV_CMD7_INT_ENA : R/W ;bitpos:[4] ;default: 1'b0 ; */
/*description: The enable bit for SPI slave CMD7 interrupt..*/
#define SPI_SLV_CMD7_INT_ENA    (1<<(4))
#define SPI_SLV_CMD7_INT_ENA_M  (1<<(4))
#define SPI_SLV_CMD7_INT_ENA_V  0x1
#define SPI_SLV_CMD7_INT_ENA_S  4
/* SPI_SLV_EN_QPI_INT_ENA : R/W ;bitpos:[3] ;default: 1'b0 ; */
/*description: The enable bit for SPI slave En_QPI interrupt..*/
#define SPI_SLV_EN_QPI_INT_ENA    (1<<(3))
#define SPI_SLV_EN_QPI_INT_ENA_M  (1<<(3))
#define SPI_SLV_EN_QPI_INT_ENA_V  0x1
#define SPI_SLV_EN_QPI_INT_ENA_S  3
/* SPI_SLV_EX_QPI_INT_ENA : R/W ;bitpos:[2] ;default: 1'b0 ; */
/*description: The enable bit for SPI slave Ex_QPI interrupt..*/
#define SPI_SLV_EX_QPI_INT_ENA    (1<<(2))
#define SPI_SLV_EX_QPI_INT_ENA_M  (1<<(2))
#define SPI_SLV_EX_QPI_INT_ENA_V  0x1
#define SPI_SLV_EX_QPI_INT_ENA_S  2
/* SPI_DMA_OUTFIFO_EMPTY_ERR_INT_ENA : R/W ;bitpos:[1] ;default: 1'b0 ; */
/*description: The enable bit for SPI_DMA_OUTFIFO_EMPTY_ERR_INT interrupt..*/
#define SPI_DMA_OUTFIFO_EMPTY_ERR_INT_ENA    (1<<(1))
#define SPI_DMA_OUTFIFO_EMPTY_ERR_INT_ENA_M  (1<<(1))
#define SPI_DMA_OUTFIFO_EMPTY_ERR_INT_ENA_V  0x1
#define SPI_DMA_OUTFIFO_EMPTY_ERR_INT_ENA_S  1
/* SPI_DMA_INFIFO_FULL_ERR_INT_ENA : R/W ;bitpos:[0] ;default: 1'b0 ; */
/*description: The enable bit for SPI_DMA_INFIFO_FULL_ERR_INT interrupt..*/
#define SPI_DMA_INFIFO_FULL_ERR_INT_ENA    (1<<(0))
#define SPI_DMA_INFIFO_FULL_ERR_INT_ENA_M  (1<<(0))
#define SPI_DMA_INFIFO_FULL_ERR_INT_ENA_V  0x1
#define SPI_DMA_INFIFO_FULL_ERR_INT_ENA_S  0

#define SPI_FREAD_OCT    (1<<(16))
#define SPI_FREAD_OCT_M  (1<<(16))
#define SPI_FREAD_OCT_V  0x1
#define SPI_FREAD_OCT_S  16
/* SPI_FREAD_QUAD : R/W ;bitpos:[15] ;default: 1'b0 ; */
/*description: In the read operations read-data phase apply 4 signals. 1: enable 0: disable.  C
an be configured in CONF state..*/
#define SPI_FREAD_QUAD    (1<<(15))
#define SPI_FREAD_QUAD_M  (1<<(15))
#define SPI_FREAD_QUAD_V  0x1
#define SPI_FREAD_QUAD_S  15
/* SPI_FREAD_DUAL : R/W ;bitpos:[14] ;default: 1'b0 ; */
/*description: In the read operations, read-data phase apply 2 signals. 1: enable 0: disable. C
an be configured in CONF state..*/
#define SPI_FREAD_DUAL    (1<<(14))
#define SPI_FREAD_DUAL_M  (1<<(14))
#define SPI_FREAD_DUAL_V  0x1
#define SPI_FREAD_DUAL_S  14
/* SPI_FCMD_OCT : R/W ;bitpos:[10] ;default: 1'b0 ; */
/*description: Apply 8 signals during command phase 1:enable 0: disable. Can be configured in C
ONF state..*/
#define SPI_FCMD_OCT    (1<<(10))
#define SPI_FCMD_OCT_M  (1<<(10))
#define SPI_FCMD_OCT_V  0x1
#define SPI_FCMD_OCT_S  10
/* SPI_FCMD_QUAD : R/W ;bitpos:[9] ;default: 1'b0 ; */
/*description: Apply 4 signals during command phase 1:enable 0: disable. Can be configured in C
ONF state..*/
#define SPI_FCMD_QUAD    (1<<(9))
#define SPI_FCMD_QUAD_M  (1<<(9))
#define SPI_FCMD_QUAD_V  0x1
#define SPI_FCMD_QUAD_S  9
/* SPI_FCMD_DUAL : R/W ;bitpos:[8] ;default: 1'b0 ; */
/*description: Apply 2 signals during command phase 1:enable 0: disable. Can be configured in C
ONF state..*/
#define SPI_FCMD_DUAL    (1<<(8))
#define SPI_FCMD_DUAL_M  (1<<(8))
#define SPI_FCMD_DUAL_V  0x1
#define SPI_FCMD_DUAL_S  8
/* SPI_FADDR_OCT : R/W ;bitpos:[7] ;default: 1'b0 ; */
/*description: Apply 8 signals during addr phase 1:enable 0: disable. Can be configured in CONF
 state..*/
#define SPI_FADDR_OCT    (1<<(7))
#define SPI_FADDR_OCT_M  (1<<(7))
#define SPI_FADDR_OCT_V  0x1
#define SPI_FADDR_OCT_S  7
/* SPI_FADDR_QUAD : R/W ;bitpos:[6] ;default: 1'b0 ; */
/*description: Apply 4 signals during addr phase 1:enable 0: disable. Can be configured in CONF
 state..*/
#define SPI_FADDR_QUAD    (1<<(6))
#define SPI_FADDR_QUAD_M  (1<<(6))
#define SPI_FADDR_QUAD_V  0x1
#define SPI_FADDR_QUAD_S  6
/* SPI_FADDR_DUAL : R/W ;bitpos:[5] ;default: 1'b0 ; */
/*description: Apply 2 signals during addr phase 1:enable 0: disable. Can be configured in CONF
 state..*/
#define SPI_FADDR_DUAL    (1<<(5))
#define SPI_FADDR_DUAL_M  (1<<(5))
#define SPI_FADDR_DUAL_V  0x1
#define SPI_FADDR_DUAL_S  5
/* SPI_DUMMY_OUT : R/W ;bitpos:[3] ;default: 1'b0 ; */
/*description: 0: In the dummy phase, the FSPI bus signals are not output. 1: In the dummy phas
e, the FSPI bus signals are output. Can be configured in CONF state..*/
#define SPI_DUMMY_OUT    (1<<(3))
#define SPI_DUMMY_OUT_M  (1<<(3))
#define SPI_DUMMY_OUT_V  0x1
#define SPI_DUMMY_OUT_S  3

#define SPI_FWRITE_OCT    (1<<(14))
#define SPI_FWRITE_OCT_M  (1<<(14))
#define SPI_FWRITE_OCT_V  0x1
#define SPI_FWRITE_OCT_S  14
/* SPI_FWRITE_QUAD : R/W ;bitpos:[13] ;default: 1'b0 ; */
/*description: In the write operations read-data phase apply 4 signals. Can be configured in CO
NF state..*/
#define SPI_FWRITE_QUAD    (1<<(13))
#define SPI_FWRITE_QUAD_M  (1<<(13))
#define SPI_FWRITE_QUAD_V  0x1
#define SPI_FWRITE_QUAD_S  13
/* SPI_FWRITE_DUAL : R/W ;bitpos:[12] ;default: 1'b0 ; */
/*description: In the write operations read-data phase apply 2 signals. Can be configured in CO
NF state..*/
#define SPI_FWRITE_DUAL    (1<<(12))
#define SPI_FWRITE_DUAL_M  (1<<(12))
#define SPI_FWRITE_DUAL_V  0x1
#define SPI_FWRITE_DUAL_S  12
/* SPI_CK_OUT_EDGE : R/W ;bitpos:[9] ;default: 1'b0 ; */
/*description: the bit combined with spi_mosi_delay_mode bits to set mosi signal delay mode. Ca
n be configured in CONF state..*/
#define SPI_CK_OUT_EDGE    (1<<(9))
#define SPI_CK_OUT_EDGE_M  (1<<(9))
#define SPI_CK_OUT_EDGE_V  0x1
#define SPI_CK_OUT_EDGE_S  9
/* SPI_RSCK_I_EDGE : R/W ;bitpos:[8] ;default: 1'b0 ; */
/*description: In the slave mode, this bit can be used to change the polarity of rsck. 0: rsck
= !spi_ck_i. 1:rsck = spi_ck_i..*/
#define SPI_RSCK_I_EDGE    (1<<(8))
#define SPI_RSCK_I_EDGE_M  (1<<(8))
#define SPI_RSCK_I_EDGE_V  0x1
#define SPI_RSCK_I_EDGE_S  8
/* SPI_CS_SETUP : R/W ;bitpos:[7] ;default: 1'b1 ; */
/*description: spi cs is enable when spi is in  prepare  phase. 1: enable 0: disable. Can be co
nfigured in CONF state..*/
#define SPI_CS_SETUP    (1<<(7))
#define SPI_CS_SETUP_M  (1<<(7))
#define SPI_CS_SETUP_V  0x1
#define SPI_CS_SETUP_S  7
/* SPI_CS_HOLD : R/W ;bitpos:[6] ;default: 1'b1 ; */
/*description: spi cs keep low when spi is in  done  phase. 1: enable 0: disable. Can be config
ured in CONF state..*/
#define SPI_CS_HOLD    (1<<(6))
#define SPI_CS_HOLD_M  (1<<(6))
#define SPI_CS_HOLD_V  0x1
#define SPI_CS_HOLD_S  6
/* SPI_TSCK_I_EDGE : R/W ;bitpos:[5] ;default: 1'b0 ; */
/*description: In the slave mode, this bit can be used to change the polarity of tsck. 0: tsck
= spi_ck_i. 1:tsck = !spi_ck_i..*/
#define SPI_TSCK_I_EDGE    (1<<(5))
#define SPI_TSCK_I_EDGE_M  (1<<(5))
#define SPI_TSCK_I_EDGE_V  0x1
#define SPI_TSCK_I_EDGE_S  5
/* SPI_OPI_MODE : R/W ;bitpos:[4] ;default: 1'b0 ; */
/*description: Just for master mode. 1: spi controller is in OPI mode (all in 8-b-m). 0: others
. Can be configured in CONF state..*/
#define SPI_OPI_MODE    (1<<(4))
#define SPI_OPI_MODE_M  (1<<(4))
#define SPI_OPI_MODE_V  0x1
#define SPI_OPI_MODE_S  4
/* SPI_QPI_MODE : R/W/SS/SC ;bitpos:[3] ;default: 1'b0 ; */
/*description: Both for master mode and slave mode. 1: spi controller is in QPI mode. 0: others
. Can be configured in CONF state..*/
#define SPI_QPI_MODE    (1<<(3))
#define SPI_QPI_MODE_M  (1<<(3))
#define SPI_QPI_MODE_V  0x1
#define SPI_QPI_MODE_S  3
/* SPI_DOUTDIN : R/W ;bitpos:[0] ;default: 1'b0 ; */
/*description: Set the bit to enable full duplex communication. 1: enable 0: disable. Can be co
nfigured in CONF state..*/
#define SPI_DOUTDIN    (1<<(0))
#define SPI_DOUTDIN_M  (1<<(0))
#define SPI_DOUTDIN_V  0x1
#define SPI_DOUTDIN_S  0




#define HAL_SPI_SWAP_DATA_TX(data, len) __builtin_bswap32((uint32_t)(data) << (32 - len))
#define SPI_LL_PERIPH_CLK_FREQ (80 * 1000000)
#define SPI_LL_GET_HW(ID) ((ID)==0? ({abort();NULL;}):((ID)==1? &GPSPI2 : &GPSPI3))

#define SPI_LL_DATA_MAX_BIT_LEN (1 << 18)

#define SPI_DMA_INT_ENA_REG(i)          (REG_SPI_BASE(i) + 0x34)
#define SPI_APP1_INT_ENA    (1<<(20))
#define SPI_APP1_INT_ENA_M  (1<<(20))
#define SPI_APP1_INT_ENA_V  0x1
#define SPI_APP1_INT_ENA_S  20

#define SPI_LL_UNUSED_INT_MASK	(SPI_TRANS_DONE_INT_ENA | SPI_SLV_WR_DMA_DONE_INT_ENA | SPI_SLV_RD_DMA_DONE_INT_ENA | SPI_SLV_WR_BUF_DONE_INT_ENA | SPI_SLV_RD_BUF_DONE_INT_ENA)
#define SPI_LL_ONE_LINE_CTRL_MASK (SPI_FREAD_OCT | SPI_FREAD_QUAD | SPI_FREAD_DUAL | SPI_FCMD_OCT | \
		SPI_FCMD_QUAD | SPI_FCMD_DUAL | SPI_FADDR_OCT | SPI_FADDR_QUAD | SPI_FADDR_DUAL)
#define SPI_LL_ONE_LINE_USER_MASK (SPI_FWRITE_OCT | SPI_FWRITE_QUAD | SPI_FWRITE_DUAL)



#define SPI_CMD_REG(i)          (REG_SPI_BASE(i) + 0x0)
/* SPI_USR : R/W/SC ;bitpos:[24] ;default: 1'b0 ; */
/*description: User define command enable.  An operation will be triggered when the bit is set.
 The bit will be cleared once the operation done.1: enable 0: disable. Can not b
e changed by CONF_buf..*/
#define SPI_USR    (1<<(24))
#define SPI_USR_M  (1<<(24))
#define SPI_USR_V  0x1
#define SPI_USR_S  24
/* SPI_UPDATE : WT ;bitpos:[23] ;default: 1'b0 ; */
/*description: Set this bit to synchronize SPI registers from APB clock domain into SPI module
clock domain, which is only used in SPI master mode..*/
#define SPI_UPDATE    (1<<(23))
#define SPI_UPDATE_M  (1<<(23))
#define SPI_UPDATE_V  0x1
#define SPI_UPDATE_S  23
/* SPI_CONF_BITLEN : R/W ;bitpos:[17:0] ;default: 18'd0 ; */
/*description: Define the APB cycles of  SPI_CONF state. Can be configured in CONF state..*/
#define SPI_CONF_BITLEN    0x0003FFFF
#define SPI_CONF_BITLEN_M  ((SPI_CONF_BITLEN_V)<<(SPI_CONF_BITLEN_S))
#define SPI_CONF_BITLEN_V  0x3FFFF
#define SPI_CONF_BITLEN_S  0

#define PIN_SLP_INPUT_ENABLE(PIN_NAME)      SET_PERI_REG_MASK(PIN_NAME,SLP_IE)
#define PIN_SLP_INPUT_DISABLE(PIN_NAME)     CLEAR_PERI_REG_MASK(PIN_NAME,SLP_IE)
#define PIN_SLP_OUTPUT_ENABLE(PIN_NAME)     SET_PERI_REG_MASK(PIN_NAME,SLP_OE)
#define PIN_SLP_OUTPUT_DISABLE(PIN_NAME)    CLEAR_PERI_REG_MASK(PIN_NAME,SLP_OE)
#define PIN_SLP_PULLUP_ENABLE(PIN_NAME)     SET_PERI_REG_MASK(PIN_NAME,SLP_PU)
#define PIN_SLP_PULLUP_DISABLE(PIN_NAME)    CLEAR_PERI_REG_MASK(PIN_NAME,SLP_PU)
#define PIN_SLP_PULLDOWN_ENABLE(PIN_NAME)   SET_PERI_REG_MASK(PIN_NAME,SLP_PD)
#define PIN_SLP_PULLDOWN_DISABLE(PIN_NAME)  CLEAR_PERI_REG_MASK(PIN_NAME,SLP_PD)
#define PIN_SLP_SEL_ENABLE(PIN_NAME)        SET_PERI_REG_MASK(PIN_NAME,SLP_SEL)
#define PIN_SLP_SEL_DISABLE(PIN_NAME)       CLEAR_PERI_REG_MASK(PIN_NAME,SLP_SEL)

#define PIN_INPUT_ENABLE(PIN_NAME)               SET_PERI_REG_MASK(PIN_NAME,FUN_IE)
#define PIN_INPUT_DISABLE(PIN_NAME)              CLEAR_PERI_REG_MASK(PIN_NAME,FUN_IE)
#define PIN_SET_DRV(PIN_NAME, drv)            REG_SET_FIELD(PIN_NAME, FUN_DRV, (drv));
#define PIN_PULLUP_DIS(PIN_NAME)                 REG_CLR_BIT(PIN_NAME, FUN_PU)
#define PIN_PULLUP_EN(PIN_NAME)                  REG_SET_BIT(PIN_NAME, FUN_PU)
#define PIN_PULLDWN_DIS(PIN_NAME)             REG_CLR_BIT(PIN_NAME, FUN_PD)
#define PIN_PULLDWN_EN(PIN_NAME)              REG_SET_BIT(PIN_NAME, FUN_PD)
#define PIN_FUNC_SELECT(PIN_NAME, FUNC)      REG_SET_FIELD(PIN_NAME, MCU_SEL, FUNC)

#define GPIO_PAD_PULLDOWN(num) do{PIN_PULLDWN_DIS(IOMUX_REG_GPIO##num);PIN_PULLUP_EN(IOMUX_REG_GPIO##num);}while(0)
#define GPIO_PAD_PULLUP(num) do{PIN_PULLUP_DIS(IOMUX_REG_GPIO##num);PIN_PULLDWN_EN(IOMUX_REG_GPIO##num);}while(0)
#define GPIO_PAD_SET_DRV(num, drv) PIN_SET_DRV(IOMUX_REG_GPIO##num, drv)

#define SPI_CS1_GPIO_NUM 26
#define SPI_HD_GPIO_NUM  27
#define SPI_WP_GPIO_NUM  28
#define SPI_CS0_GPIO_NUM 29
#define SPI_CLK_GPIO_NUM 30
#define SPI_Q_GPIO_NUM   31
#define SPI_D_GPIO_NUM   32
#define SPI_D4_GPIO_NUM  33
#define SPI_D5_GPIO_NUM  34
#define SPI_D6_GPIO_NUM  35
#define SPI_D7_GPIO_NUM  36
#define SPI_DQS_GPIO_NUM 37
#define SD_CLK_GPIO_NUM 12
#define SD_CMD_GPIO_NUM 11
#define SD_DATA0_GPIO_NUM 13
#define SD_DATA1_GPIO_NUM 14
#define SD_DATA2_GPIO_NUM 9
#define SD_DATA3_GPIO_NUM 10
#define USB_DM_GPIO_NUM   19
#define USB_DP_GPIO_NUM   20

#define MAX_RTC_GPIO_NUM 21
#define MAX_PAD_GPIO_NUM 48
#define MAX_GPIO_NUM    53

#define REG_IO_MUX_BASE DR_REG_IO_MUX_BASE
#define PIN_CTRL                          (REG_IO_MUX_BASE +0x00)
#define PAD_POWER_SEL                               BIT(15)
#define PAD_POWER_SEL_V                             0x1
#define PAD_POWER_SEL_M                             BIT(15)
#define PAD_POWER_SEL_S                             15


#define PAD_POWER_SWITCH_DELAY                      0x7
#define PAD_POWER_SWITCH_DELAY_V                    0x7
#define PAD_POWER_SWITCH_DELAY_M                    (PAD_POWER_SWITCH_DELAY_V << PAD_POWER_SWITCH_DELAY_S)
#define PAD_POWER_SWITCH_DELAY_S                    12


#define CLK_OUT3                                    0xf
#define CLK_OUT3_V                                  CLK_OUT3
#define CLK_OUT3_S                                  8
#define CLK_OUT3_M                                  (CLK_OUT3_V << CLK_OUT3_S)
#define CLK_OUT2                                    0xf
#define CLK_OUT2_V                                  CLK_OUT2
#define CLK_OUT2_S                                  4
#define CLK_OUT2_M                                  (CLK_OUT2_V << CLK_OUT2_S)
#define CLK_OUT1                                    0xf
#define CLK_OUT1_V                                  CLK_OUT1
#define CLK_OUT1_S                                  0
#define CLK_OUT1_M                                  (CLK_OUT1_V << CLK_OUT1_S)


typedef union {
		struct {
			uint32_t clkcnt_l					   :	8;
			uint32_t clkcnt_h					   :	8;
			uint32_t clkcnt_n					   :	8;
			uint32_t reserved24					   :	7;
			uint32_t clk_equ_sysclk				   :	1;
		};
		uint32_t val;
} spimem_flash_ll_clock_reg_t ;

typedef enum {
	SPI_FLASH_SLOWRD = 0, ///< Data read using single I/O, some limits on speed
	SPI_FLASH_FASTRD, ///< Data read using single I/O, no limit on speed
	SPI_FLASH_DOUT,   ///< Data read using dual I/O
	SPI_FLASH_DIO,    ///< Both address & data transferred using dual I/O
	SPI_FLASH_QOUT,   ///< Data read using quad I/O
	SPI_FLASH_QIO,    ///< Both address & data transferred using quad I/O
	#define SPI_FLASH_OPI_FLAG 16    ///< A flag for flash work in opi mode, the io mode below are opi, above are SPI/QSPI mode. DO NOT use this value in any API.
	SPI_FLASH_OPI_STR = SPI_FLASH_OPI_FLAG,///< Only support on OPI flash, flash read and write under STR mode
	SPI_FLASH_OPI_DTR,///< Only support on OPI flash, flash read and write under DTR mode
	SPI_FLASH_READ_MODE_MAX,    ///< The fastest io mode supported by the host is ``ESP_FLASH_READ_MODE_MAX-1``.
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

typedef union  {
	gpspi_flash_ll_clock_reg_t gpspi;
	spimem_flash_ll_clock_reg_t spimem;
} spi_flash_ll_clock_reg_t;


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

extern spi_dev_t *GPSPI1, *GPSPI2, *GPSPI3;


typedef uint32_t spi_ll_clock_val_t;
typedef spi_dev_t spi_dma_dev_t;

typedef enum {
	SPI1_HOST=0,    ///< SPI1
	SPI2_HOST=1,    ///< SPI2
	SPI3_HOST=2,    ///< SPI3
} spi_host_device_t;

typedef enum {
	SPI_EV_BUF_TX         = 1<<(0),
	SPI_EV_BUF_RX         = 1<<(1),
	SPI_EV_SEND_DMA_READY = 1<<(2),
	SPI_EV_SEND           = 1<<(3),
	SPI_EV_RECV_DMA_READY = 1<<(4),
	SPI_EV_RECV           = 1<<(5),
	SPI_EV_CMD9           = 1<<(6),
	SPI_EV_CMDA           = 1<<(7),
	SPI_EV_TRANS          = 1<<(8),
} spi_event_t;

typedef struct {
    uint8_t cmd_lines;
    uint8_t addr_lines;
    uint8_t data_lines;
} spi_line_mode_t;

typedef enum {
	SPI_CMD_HD_WRBUF    = 1<<(0),
	SPI_CMD_HD_RDBUF    = 1<<(1),
	SPI_CMD_HD_WRDMA    = 1<<(2),
	SPI_CMD_HD_RDDMA    = 1<<(3),
	SPI_CMD_HD_SEG_END  = 1<<(4),
	SPI_CMD_HD_EN_QPI   = 1<<(5),
	SPI_CMD_HD_WR_END   = 1<<(6),
	SPI_CMD_HD_INT0     = 1<<(7),
	SPI_CMD_HD_INT1     = 1<<(8),
	SPI_CMD_HD_INT2     = 1<<(9),
} spi_command_t;


typedef enum {
	SPI_LL_INTR_TRANS_DONE =	1<<(0),		///< A transaction has done
	SPI_LL_INTR_RDBUF =			1<<(6),		///< Has received RDBUF command. Only available in slave HD.
	SPI_LL_INTR_WRBUF =			1<<(7),		///< Has received WRBUF command. Only available in slave HD.
	SPI_LL_INTR_RDDMA =			1<<(8),		///< Has received RDDMA command. Only available in slave HD.
	SPI_LL_INTR_WRDMA =			1<<(9),		///< Has received WRDMA command. Only available in slave HD.
	SPI_LL_INTR_CMD7 =			1<<(10),	///< Has received CMD7 command. Only available in slave HD.
	SPI_LL_INTR_CMD8 =			1<<(11),	///< Has received CMD8 command. Only available in slave HD.
	SPI_LL_INTR_CMD9 =			1<<(12),	///< Has received CMD9 command. Only available in slave HD.
	SPI_LL_INTR_CMDA =			1<<(13),	///< Has received CMDA command. Only available in slave HD.
	SPI_LL_INTR_SEG_DONE =		1<<(14),
} spi_ll_intr_t;

typedef enum {
	SPI_LL_TRANS_LEN_COND_WRBUF =	1<<(0), ///< WRBUF length will be recorded
	SPI_LL_TRANS_LEN_COND_RDBUF =	1<<(1), ///< RDBUF length will be recorded
	SPI_LL_TRANS_LEN_COND_WRDMA =	1<<(2), ///< WRDMA length will be recorded
	SPI_LL_TRANS_LEN_COND_RDDMA =	1<<(3), ///< RDDMA length will be recorded
} spi_ll_trans_len_cond_t;

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

typedef enum {
	SPI_TIMING_CONFIG_CORE_CLOCK_80M,
	SPI_TIMING_CONFIG_CORE_CLOCK_120M,
	SPI_TIMING_CONFIG_CORE_CLOCK_160M,
	SPI_TIMING_CONFIG_CORE_CLOCK_240M
} spi_timing_config_core_clock_t;

typedef struct {
	uint32_t extra_dummy;
	uint32_t cs_hold;
	uint8_t cs_setup;
	spi_flash_ll_clock_reg_t clock_config;
} spi_flash_hal_timing_config_t;

typedef struct {
	uint8_t spi_din_mode;    /*!< input signal delay mode*/
	uint8_t spi_din_num;     /*!< input signal delay number */
	uint8_t extra_dummy_len; /*!< extra dummy length*/
} spi_timing_tuning_param_t;

typedef struct {
	spi_timing_tuning_param_t tuning_config_table[SPI_TIMING_CONFIG_NUM_DEFAULT];   //available timing tuning configs
	uint32_t available_config_num;
	uint32_t default_config_id; //If tuning fails, we use this one as default
} spi_timing_config_t;


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

void spi_timing_set_pin_drive_strength(void);
static spi_timing_config_core_clock_t get_mspi_core_clock(void);
static uint32_t get_flash_clock_divider(void);
static uint32_t get_psram_clock_divider(void);
static void init_spi1_for_tuning(bool is_flash);
static void sweep_for_success_sample_points(uint8_t *reference_data, const spi_timing_config_t *config, bool is_flash, uint8_t *out_array);
static void find_max_consecutive_success_points(uint8_t *array, uint32_t size, uint32_t *out_length, uint32_t *out_end_index);
static uint32_t select_best_tuning_config_dtr(spi_timing_config_t *config, uint32_t consecutive_length, uint32_t end);
static uint32_t select_best_tuning_config_str(spi_timing_config_t *config, uint32_t consecutive_length, uint32_t end);
static void select_best_tuning_config(spi_timing_config_t *config, uint32_t consecutive_length, uint32_t end, bool is_flash);
static void do_tuning(uint8_t *reference_data, spi_timing_config_t *timing_config, bool is_flash);
static void get_flash_tuning_configs(spi_timing_config_t *config);
void spi_timing_flash_tuning(void);
void spi_timing_flash_tuning(void);
static void get_psram_tuning_configs(spi_timing_config_t *config);
void spi_timing_psram_tuning(void);
void spi_timing_psram_tuning(void);
static void clear_timing_tuning_regs(bool control_spi1);
void spi_timing_enter_mspi_low_speed_mode(bool control_spi1);
static void set_timing_tuning_regs_as_required(bool control_spi1);
void spi_timing_enter_mspi_high_speed_mode(bool control_spi1);
void spi_timing_change_speed_mode_cache_safe(bool switch_down);
bool spi_timing_is_tuned(void);
void spi_timing_get_flash_timing_param(spi_flash_hal_timing_config_t *out_timing_config);
void spi_timing_get_flash_timing_param(spi_flash_hal_timing_config_t *out_timing_config);
