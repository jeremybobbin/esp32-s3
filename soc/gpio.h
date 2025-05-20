#include <stdbool.h>
#include <stdint.h>

#define GPIO_LL_GET_HW(num) (((num) == 0) ? (&GPIO) : NULL)

#define GPIO_LL_INTR_ENA      (1<<0)
#define GPIO_LL_NMI_INTR_ENA  (1<<1)
/* The following are the bit fields for PERIPHS_IO_MUX_x_U registers */
/* Output enable in sleep mode */
#define SLP_OE (1<<0)
#define SLP_OE_M (1<<0)
#define SLP_OE_V 1
#define SLP_OE_S 0
/* Pin used for wakeup from sleep */
#define SLP_SEL (1<<1)
#define SLP_SEL_M (1<<1)
#define SLP_SEL_V 1
#define SLP_SEL_S 1
/* Pulldown enable in sleep mode */
#define SLP_PD (1<<2)
#define SLP_PD_M (1<<2)
#define SLP_PD_V 1
#define SLP_PD_S 2
/* Pullup enable in sleep mode */
#define SLP_PU (1<<3)
#define SLP_PU_M (1<<3)
#define SLP_PU_V 1
#define SLP_PU_S 3
/* Input enable in sleep mode */
#define SLP_IE (1<<4)
#define SLP_IE_M (1<<4)
#define SLP_IE_V 1
#define SLP_IE_S 4
/* Drive strength in sleep mode */
#define SLP_DRV 0x3
#define SLP_DRV_M (SLP_DRV_V << SLP_DRV_S)
#define SLP_DRV_V 0x3
#define SLP_DRV_S 5
/* Pulldown enable */
#define FUN_PD (1<<7)
#define FUN_PD_M (1<<7)
#define FUN_PD_V 1
#define FUN_PD_S 7
/* Pullup enable */
#define FUN_PU (1<<8)
#define FUN_PU_M (1<<8)
#define FUN_PU_V 1
#define FUN_PU_S 8
/* Input enable */
#define FUN_IE (1<<9)
#define FUN_IE_M (FUN_IE_V << FUN_IE_S)
#define FUN_IE_V 1
#define FUN_IE_S 9
/* Drive strength */
#define FUN_DRV 0x3
#define FUN_DRV_M (FUN_DRV_V << FUN_DRV_S)
#define FUN_DRV_V 0x3
#define FUN_DRV_S 10
/* Function select (possible values are defined for each pin as FUNC_pinname_function below) */
#define MCU_SEL 0x7
#define MCU_SEL_M (MCU_SEL_V << MCU_SEL_S)
#define MCU_SEL_V 0x7
#define MCU_SEL_S 12

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

//read value from register
#define REG_READ(_r) ({                                                                                                \
            (*(volatile uint32_t *)(_r));                                                                              \
        })

//write value to register
#define REG_WRITE(_r, _v) ({                                                                                           \
            (*(volatile uint32_t *)(_r)) = (_v);                                                                       \
        })

//clear bit or clear bits of register
#define REG_CLR_BIT(_r, _b)  ({                                                                                        \
            (*(volatile uint32_t*)(_r) &= ~(_b));                                                                      \
        })

//read value from register
#define READ_PERI_REG(addr) ({                                                                                         \
            (*((volatile uint32_t *)(addr)));                                                         \
        })

//write value to register
#define WRITE_PERI_REG(addr, val) ({                                                                                   \
            (*((volatile uint32_t *)(addr))) = (uint32_t)(val);                                       \
        })

//clear bits of register controlled by mask
#define CLEAR_PERI_REG_MASK(reg, mask) ({                                                                              \
            WRITE_PERI_REG((reg), (READ_PERI_REG(reg)&(~(mask))));                                                     \
        })

//set bits of register controlled by mask
#define SET_PERI_REG_MASK(reg, mask) ({                                                                                \
            WRITE_PERI_REG((reg), (READ_PERI_REG(reg)|(mask)));                                                        \
        })

//get bits of register controlled by mask
#define GET_PERI_REG_MASK(reg, mask) ({                                                                                \
            (READ_PERI_REG(reg) & (mask));                                                                             \
        })

//get bits of register controlled by highest bit and lowest bit
#define GET_PERI_REG_BITS(reg, hipos,lowpos) ({                                                                        \
            ((READ_PERI_REG(reg)>>(lowpos))&((1<<((hipos)-(lowpos)+1))-1));                                            \
        })

//set bits of register controlled by mask and shift
#define SET_PERI_REG_BITS(reg,bit_map,value,shift) ({                                                                  \
            (WRITE_PERI_REG((reg),(READ_PERI_REG(reg)&(~((bit_map)<<(shift))))|(((value) & bit_map)<<(shift)) ));      \
        })

//get field of register
#define GET_PERI_REG_BITS2(reg, mask,shift) ({                                                                         \
            ((READ_PERI_REG(reg)>>(shift))&(mask));                                                                    \
        })

#define REG_SET_FIELD(_r, _f, _v) ({                                                                                   \
            (REG_WRITE((_r),((REG_READ(_r) & ~((_f##_V) << (_f##_S)))|(((_v) & (_f##_V))<<(_f##_S)))));                \
        })

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

#define FUNC_DAC_1_GPIO17_0            0
#define FUNC_DAC_1_GPIO17              1
#define FUNC_DAC_1_U1TXD               2
#define FUNC_DAC_2_CLK_OUT3            3
#define FUNC_DAC_2_GPIO18_0            0
#define FUNC_DAC_2_GPIO18              1
#define FUNC_DAC_2_U1RXD               2
#define FUNC_GPIO0_GPIO0_0             0
#define FUNC_GPIO0_GPIO0               1
#define FUNC_GPIO10_FSPICS0            4
#define FUNC_GPIO10_FSPIIO4            2
#define FUNC_GPIO10_GPIO10_0           0
#define FUNC_GPIO10_GPIO10             1
#define FUNC_GPIO10_SUBSPICS0          3
#define FUNC_GPIO11_FSPID              4
#define FUNC_GPIO11_FSPIIO5            2
#define FUNC_GPIO11_GPIO11_0           0
#define FUNC_GPIO11_GPIO11             1
#define FUNC_GPIO11_SUBSPID            3
#define FUNC_GPIO12_FSPICLK            4
#define FUNC_GPIO12_FSPIIO6            2
#define FUNC_GPIO12_GPIO12_0           0
#define FUNC_GPIO12_GPIO12             1
#define FUNC_GPIO12_SUBSPICLK          3
#define FUNC_GPIO13_FSPIIO7            2
#define FUNC_GPIO13_FSPIQ              4
#define FUNC_GPIO13_GPIO13_0           0
#define FUNC_GPIO13_GPIO13             1
#define FUNC_GPIO13_SUBSPIQ            3
#define FUNC_GPIO14_FSPIDQS            2
#define FUNC_GPIO14_FSPIWP             4
#define FUNC_GPIO14_GPIO14_0           0
#define FUNC_GPIO14_GPIO14             1
#define FUNC_GPIO14_SUBSPIWP           3
#define FUNC_GPIO19_CLK_OUT2           3
#define FUNC_GPIO19_GPIO19_0           0
#define FUNC_GPIO19_GPIO19             1
#define FUNC_GPIO19_U1RTS              2
#define FUNC_GPIO1_GPIO1_0             0
#define FUNC_GPIO1_GPIO1               1
#define FUNC_GPIO20_CLK_OUT1           3
#define FUNC_GPIO20_GPIO20_0           0
#define FUNC_GPIO20_GPIO20             1
#define FUNC_GPIO20_U1CTS              2
#define FUNC_GPIO21_GPIO21_0           0
#define FUNC_GPIO21_GPIO21             1
#define FUNC_GPIO2_GPIO2_0             0
#define FUNC_GPIO2_GPIO2               1
#define FUNC_GPIO33_FSPIHD             2
#define FUNC_GPIO33_GPIO33_0           0
#define FUNC_GPIO33_GPIO33             1
#define FUNC_GPIO33_SPIIO4             4
#define FUNC_GPIO33_SUBSPIHD           3
#define FUNC_GPIO34_FSPICS0            2
#define FUNC_GPIO34_GPIO34_0           0
#define FUNC_GPIO34_GPIO34             1
#define FUNC_GPIO34_SPIIO5             4
#define FUNC_GPIO34_SUBSPICS0          3
#define FUNC_GPIO35_FSPID              2
#define FUNC_GPIO35_GPIO35_0           0
#define FUNC_GPIO35_GPIO35             1
#define FUNC_GPIO35_SPIIO6             4
#define FUNC_GPIO35_SUBSPID            3
#define FUNC_GPIO36_FSPICLK            2
#define FUNC_GPIO36_GPIO36_0           0
#define FUNC_GPIO36_GPIO36             1
#define FUNC_GPIO36_SPIIO7             4
#define FUNC_GPIO36_SUBSPICLK          3
#define FUNC_GPIO37_FSPIQ              2
#define FUNC_GPIO37_GPIO37_0           0
#define FUNC_GPIO37_GPIO37             1
#define FUNC_GPIO37_SPIDQS             4
#define FUNC_GPIO37_SUBSPIQ            3
#define FUNC_GPIO38_FSPIWP             2
#define FUNC_GPIO38_GPIO38_0           0
#define FUNC_GPIO38_GPIO38             1
#define FUNC_GPIO38_SUBSPIWP           3
#define FUNC_GPIO3_GPIO3_0             0
#define FUNC_GPIO3_GPIO3               1
#define FUNC_GPIO45_GPIO45_0           0
#define FUNC_GPIO45_GPIO45             1
#define FUNC_GPIO46_GPIO46_0           0
#define FUNC_GPIO46_GPIO46             1
#define FUNC_GPIO4_GPIO4_0             0
#define FUNC_GPIO4_GPIO4               1
#define FUNC_GPIO5_GPIO5_0             0
#define FUNC_GPIO5_GPIO5               1
#define FUNC_GPIO6_GPIO6_0             0
#define FUNC_GPIO6_GPIO6               1
#define FUNC_GPIO7_GPIO7_0             0
#define FUNC_GPIO7_GPIO7               1
#define FUNC_GPIO8_GPIO8_0             0
#define FUNC_GPIO8_GPIO8               1
#define FUNC_GPIO8_SUBSPICS1           3
#define FUNC_GPIO9_FSPIHD              4
#define FUNC_GPIO9_GPIO9_0             0
#define FUNC_GPIO9_GPIO9               1
#define FUNC_GPIO9_SUBSPIHD            3
#define FUNC_MTCK_CLK_OUT3             2
#define FUNC_MTCK_GPIO39               1
#define FUNC_MTCK_MTCK                 0
#define FUNC_MTCK_SUBSPICS1            3
#define FUNC_MTDI_CLK_OUT1             2
#define FUNC_MTDI_GPIO41               1
#define FUNC_MTDI_MTDI                 0
#define FUNC_MTDO_CLK_OUT2             2
#define FUNC_MTDO_GPIO40               1
#define FUNC_MTDO_MTDO                 0
#define FUNC_MTMS_GPIO42               1
#define FUNC_MTMS_MTMS                 0
#define FUNC_SPICLK_GPIO30             1
#define FUNC_SPICLK_N_GPIO48           1
#define FUNC_SPICLK_N_SPICLK_DIFF      0
#define FUNC_SPICLK_N_SUBSPICLK_DIFF   2
#define FUNC_SPICLK_P_GPIO47           1
#define FUNC_SPICLK_P_SPICLK_DIFF      0
#define FUNC_SPICLK_P_SUBSPICLK_DIFF   2
#define FUNC_SPICLK_SPICLK             0
#define FUNC_SPICS0_GPIO29             1
#define FUNC_SPICS0_SPICS0             0
#define FUNC_SPICS1_GPIO26             1
#define FUNC_SPICS1_SPICS1             0
#define FUNC_SPID_GPIO32               1
#define FUNC_SPID_SPID                 0
#define FUNC_SPIHD_GPIO27              1
#define FUNC_SPIHD_SPIHD               0
#define FUNC_SPIQ_GPIO31               1
#define FUNC_SPIQ_SPIQ                 0
#define FUNC_SPIWP_GPIO28              1
#define FUNC_SPIWP_SPIWP               0
#define FUNC_U0RXD_CLK_OUT2            2
#define FUNC_U0RXD_GPIO44              1
#define FUNC_U0RXD_U0RXD               0
#define FUNC_U0TXD_CLK_OUT1            2
#define FUNC_U0TXD_GPIO43              1
#define FUNC_U0TXD_U0TXD               0
#define FUNC_XTAL_32K_N_GPIO16_0       0
#define FUNC_XTAL_32K_N_GPIO16         1
#define FUNC_XTAL_32K_N_U0CTS          2
#define FUNC_XTAL_32K_P_GPIO15_0       0
#define FUNC_XTAL_32K_P_GPIO15         1
#define FUNC_XTAL_32K_P_U0RTS          2
#define PERIPHS_IO_MUX_DAC_1_U        (0x60009000+0x48)
#define PERIPHS_IO_MUX_DAC_2_U        (0x60009000+0x4c)
#define PERIPHS_IO_MUX_GPIO0_U        (0x60009000+0x04)
#define PERIPHS_IO_MUX_GPIO10_U       (0x60009000+0x2c)
#define PERIPHS_IO_MUX_GPIO11_U       (0x60009000+0x30)
#define PERIPHS_IO_MUX_GPIO12_U       (0x60009000+0x34)
#define PERIPHS_IO_MUX_GPIO13_U       (0x60009000+0x38)
#define PERIPHS_IO_MUX_GPIO14_U       (0x60009000+0x3c)
#define PERIPHS_IO_MUX_GPIO19_U       (0x60009000+0x50)
#define PERIPHS_IO_MUX_GPIO1_U        (0x60009000+0x08)
#define PERIPHS_IO_MUX_GPIO20_U       (0x60009000+0x54)
#define PERIPHS_IO_MUX_GPIO21_U       (0x60009000+0x58)
#define PERIPHS_IO_MUX_GPIO2_U        (0x60009000+0x0c)
#define PERIPHS_IO_MUX_GPIO33_U       (0x60009000+0x88)
#define PERIPHS_IO_MUX_GPIO34_U       (0x60009000+0x8c)
#define PERIPHS_IO_MUX_GPIO35_U       (0x60009000+0x90)
#define PERIPHS_IO_MUX_GPIO36_U       (0x60009000+0x94)
#define PERIPHS_IO_MUX_GPIO37_U       (0x60009000+0x98)
#define PERIPHS_IO_MUX_GPIO38_U       (0x60009000+0x9c)
#define PERIPHS_IO_MUX_GPIO3_U        (0x60009000+0x10)
#define PERIPHS_IO_MUX_GPIO45_U       (0x60009000+0xb8)
#define PERIPHS_IO_MUX_GPIO46_U       (0x60009000+0xbc)
#define PERIPHS_IO_MUX_GPIO4_U        (0x60009000+0x14)
#define PERIPHS_IO_MUX_GPIO5_U        (0x60009000+0x18)
#define PERIPHS_IO_MUX_GPIO6_U        (0x60009000+0x1c)
#define PERIPHS_IO_MUX_GPIO7_U        (0x60009000+0x20)
#define PERIPHS_IO_MUX_GPIO8_U        (0x60009000+0x24)
#define PERIPHS_IO_MUX_GPIO9_U        (0x60009000+0x28)
#define PERIPHS_IO_MUX_MTCK_U         (0x60009000+0xa0)
#define PERIPHS_IO_MUX_MTDI_U         (0x60009000+0xa8)
#define PERIPHS_IO_MUX_MTDO_U         (0x60009000+0xa4)
#define PERIPHS_IO_MUX_MTMS_U         (0x60009000+0xac)
#define PERIPHS_IO_MUX_SPICLK_N_U     (0x60009000+0xc4)
#define PERIPHS_IO_MUX_SPICLK_P_U     (0x60009000+0xc0)
#define PERIPHS_IO_MUX_SPICLK_U       (0x60009000+0x7c)
#define PERIPHS_IO_MUX_SPICS0_U       (0x60009000+0x78)
#define PERIPHS_IO_MUX_SPICS1_U       (0x60009000+0x6c)
#define PERIPHS_IO_MUX_SPID_U         (0x60009000+0x84)
#define PERIPHS_IO_MUX_SPIHD_U        (0x60009000+0x70)
#define PERIPHS_IO_MUX_SPIQ_U         (0x60009000+0x80)
#define PERIPHS_IO_MUX_SPIWP_U        (0x60009000+0x74)
#define PERIPHS_IO_MUX_U0RXD_U        (0x60009000+0xb4)
#define PERIPHS_IO_MUX_U0TXD_U        (0x60009000+0xb0)
#define PERIPHS_IO_MUX_XTAL_32K_N_U   (0x60009000+0x44)
#define PERIPHS_IO_MUX_XTAL_32K_P_U   (0x60009000+0x40)
#define IO_MUX_DATE_REG               (0x60009000+0xfc)
#define IO_MUX_DATE                    0xFFFFFFFF
#define IO_MUX_DATE_S                  0
#define IO_MUX_DATE_VERSION            0x1907160

typedef enum {
	GPIO_NUM_NC = -1,    /*!< Use to signal not connected to S/W */
	GPIO_NUM_0 = 0,     /*!< GPIO0, input and output */
	GPIO_NUM_1 = 1,     /*!< GPIO1, input and output */
	GPIO_NUM_2 = 2,     /*!< GPIO2, input and output */
	GPIO_NUM_3 = 3,     /*!< GPIO3, input and output */
	GPIO_NUM_4 = 4,     /*!< GPIO4, input and output */
	GPIO_NUM_5 = 5,     /*!< GPIO5, input and output */
	GPIO_NUM_6 = 6,     /*!< GPIO6, input and output */
	GPIO_NUM_7 = 7,     /*!< GPIO7, input and output */
	GPIO_NUM_8 = 8,     /*!< GPIO8, input and output */
	GPIO_NUM_9 = 9,     /*!< GPIO9, input and output */
	GPIO_NUM_10 = 10,   /*!< GPIO10, input and output */
	GPIO_NUM_11 = 11,   /*!< GPIO11, input and output */
	GPIO_NUM_12 = 12,   /*!< GPIO12, input and output */
	GPIO_NUM_13 = 13,   /*!< GPIO13, input and output */
	GPIO_NUM_14 = 14,   /*!< GPIO14, input and output */
	GPIO_NUM_15 = 15,   /*!< GPIO15, input and output */
	GPIO_NUM_16 = 16,   /*!< GPIO16, input and output */
	GPIO_NUM_17 = 17,   /*!< GPIO17, input and output */
	GPIO_NUM_18 = 18,   /*!< GPIO18, input and output */
	GPIO_NUM_19 = 19,   /*!< GPIO19, input and output */
	GPIO_NUM_20 = 20,   /*!< GPIO20, input and output */
	GPIO_NUM_21 = 21,   /*!< GPIO21, input and output */
	GPIO_NUM_26 = 26,   /*!< GPIO26, input and output */
	GPIO_NUM_27 = 27,   /*!< GPIO27, input and output */
	GPIO_NUM_28 = 28,   /*!< GPIO28, input and output */
	GPIO_NUM_29 = 29,   /*!< GPIO29, input and output */
	GPIO_NUM_30 = 30,   /*!< GPIO30, input and output */
	GPIO_NUM_31 = 31,   /*!< GPIO31, input and output */
	GPIO_NUM_32 = 32,   /*!< GPIO32, input and output */
	GPIO_NUM_33 = 33,   /*!< GPIO33, input and output */
	GPIO_NUM_34 = 34,   /*!< GPIO34, input and output */
	GPIO_NUM_35 = 35,   /*!< GPIO35, input and output */
	GPIO_NUM_36 = 36,   /*!< GPIO36, input and output */
	GPIO_NUM_37 = 37,   /*!< GPIO37, input and output */
	GPIO_NUM_38 = 38,   /*!< GPIO38, input and output */
	GPIO_NUM_39 = 39,   /*!< GPIO39, input and output */
	GPIO_NUM_40 = 40,   /*!< GPIO40, input and output */
	GPIO_NUM_41 = 41,   /*!< GPIO41, input and output */
	GPIO_NUM_42 = 42,   /*!< GPIO42, input and output */
	GPIO_NUM_43 = 43,   /*!< GPIO43, input and output */
	GPIO_NUM_44 = 44,   /*!< GPIO44, input and output */
	GPIO_NUM_45 = 45,   /*!< GPIO45, input and output */
	GPIO_NUM_46 = 46,   /*!< GPIO46, input and output */
	GPIO_NUM_47 = 47,   /*!< GPIO47, input and output */
	GPIO_NUM_48 = 48,   /*!< GPIO48, input and output */
	GPIO_NUM_MAX,
} gpio_num_t;

typedef enum {
	GPIO_INTR_DISABLE = 0,     /*!< Disable GPIO interrupt                             */
	GPIO_INTR_POSEDGE = 1,     /*!< GPIO interrupt type : rising edge                  */
	GPIO_INTR_NEGEDGE = 2,     /*!< GPIO interrupt type : falling edge                 */
	GPIO_INTR_ANYEDGE = 3,     /*!< GPIO interrupt type : both rising and falling edge */
	GPIO_INTR_LOW_LEVEL = 4,   /*!< GPIO interrupt type : input low level trigger      */
	GPIO_INTR_HIGH_LEVEL = 5,  /*!< GPIO interrupt type : input high level trigger     */
	GPIO_INTR_MAX,
} gpio_int_type_t;

typedef enum {
	GPIO_DRIVE_CAP_0       = 0,    /*!< Pad drive capability: weak          */
	GPIO_DRIVE_CAP_1       = 1,    /*!< Pad drive capability: stronger      */
	GPIO_DRIVE_CAP_2       = 2,    /*!< Pad drive capability: medium */
	GPIO_DRIVE_CAP_DEFAULT = 2,    /*!< Pad drive capability: medium */
	GPIO_DRIVE_CAP_3       = 3,    /*!< Pad drive capability: strongest     */
	GPIO_DRIVE_CAP_MAX,
} gpio_drive_cap_t;

typedef volatile struct gpio_dev_s {
	uint32_t bt_select;
	uint32_t out;
	uint32_t out_w1ts;
	uint32_t out_w1tc;
	union {
		struct {
			uint32_t data                          :    22;
			uint32_t reserved22                    :    10;
		};
		uint32_t val;
	} out1;
	union {
		struct {
			uint32_t data                          :    22;
			uint32_t reserved22                    :    10;
		};
		uint32_t val;
	} out1_w1ts;
	union {
		struct {
			uint32_t data                          :    22;
			uint32_t reserved22                    :    10;
		};
		uint32_t val;
	} out1_w1tc;
	union {
		struct {
			uint32_t sel                           :    8;
			uint32_t reserved8                     :    24;
		};
		uint32_t val;
	} sdio_select;
	uint32_t enable;
	uint32_t enable_w1ts;
	uint32_t enable_w1tc;
	union {
		struct {
			uint32_t data                          :    22;
			uint32_t reserved22                    :    10;
		};
		uint32_t val;
	} enable1;
	union {
		struct {
			uint32_t data                          :    22;
			uint32_t reserved22                    :    10;
		};
		uint32_t val;
	} enable1_w1ts;
	union {
		struct {
			uint32_t data                          :    22;
			uint32_t reserved22                    :    10;
		};
		uint32_t val;
	} enable1_w1tc;
	union {
		struct {
			uint32_t strapping                     :    16;
			uint32_t reserved16                    :    16;
		};
		uint32_t val;
	} strap;
	uint32_t in;
	union {
		struct {
			uint32_t data                          :    22;
			uint32_t reserved22                    :    10;
		};
		uint32_t val;
	} in1;
	uint32_t status;
	uint32_t status_w1ts;
	uint32_t status_w1tc;
	union {
		struct {
			uint32_t intr_st                       :    22;
			uint32_t reserved22                    :    10;
		};
		uint32_t val;
	} status1;
	union {
		struct {
			uint32_t intr_st                       :    22;
			uint32_t reserved22                    :    10;
		};
		uint32_t val;
	} status1_w1ts;
	union {
		struct {
			uint32_t intr_st                       :    22;
			uint32_t reserved22                    :    10;
		};
		uint32_t val;
	} status1_w1tc;
	uint32_t pcpu_int;                                            /*GPIO0~31 PRO & APP CPU interrupt status*/
	uint32_t pcpu_nmi_int;                                        /*GPIO0~31 PRO & APP CPU non-maskable interrupt status*/
	uint32_t cpusdio_int;
	union {
		struct {
			uint32_t intr                          :    22;       /*GPIO32-48 PRO & APP CPU interrupt status*/
			uint32_t reserved22                    :    10;
		};
		uint32_t val;
	} pcpu_int1;
	union {
		struct {
			uint32_t intr                          :    22;       /*GPIO32-48 PRO & APP CPU non-maskable interrupt status*/
			uint32_t reserved22                    :    10;
		};
		uint32_t val;
	} pcpu_nmi_int1;
	union {
		struct {
			uint32_t intr                          :    22;
			uint32_t reserved22                    :    10;
		};
		uint32_t val;
	} cpusdio_int1;
	union {
		struct {
			uint32_t sync2_bypass                  :    2;
			uint32_t pad_driver                    :    1;
			uint32_t sync1_bypass                  :    2;
			uint32_t reserved5                     :    2;
			uint32_t int_type                      :    3;
			uint32_t wakeup_enable                 :    1;
			uint32_t config                        :    2;
			uint32_t int_ena                       :    5;
			uint32_t reserved18                    :    14;
		};
		uint32_t val;
	} pin[54];
	uint32_t status_next;
	union {
		struct {
			uint32_t intr_st_next                  :    22;
			uint32_t reserved22                    :    10;
		};
		uint32_t val;
	} status_next1;
	union {
		struct {
			uint32_t func_sel                      :    6;
			uint32_t sig_in_inv                    :    1;
			uint32_t sig_in_sel                    :    1;
			uint32_t reserved8                     :    24;
		};
		uint32_t val;
	} func_in_sel_cfg[256];
	union {
		struct {
			uint32_t func_sel                      :    9;
			uint32_t inv_sel                       :    1;
			uint32_t oen_sel                       :    1;
			uint32_t oen_inv_sel                   :    1;
			uint32_t reserved12                    :    20;
		};
		uint32_t val;
	} func_out_sel_cfg[54];
	union {
		struct {
			uint32_t clk_en                        :    1;
			uint32_t reserved1                     :    31;
		};
		uint32_t val;
	} clock_gate;
	uint32_t reserved_630;
	uint32_t reserved_634;
	uint32_t reserved_638;
	uint32_t reserved_63c;
	uint32_t reserved_640;
	uint32_t reserved_644;
	uint32_t reserved_648;
	uint32_t reserved_64c;
	uint32_t reserved_650;
	uint32_t reserved_654;
	uint32_t reserved_658;
	uint32_t reserved_65c;
	uint32_t reserved_660;
	uint32_t reserved_664;
	uint32_t reserved_668;
	uint32_t reserved_66c;
	uint32_t reserved_670;
	uint32_t reserved_674;
	uint32_t reserved_678;
	uint32_t reserved_67c;
	uint32_t reserved_680;
	uint32_t reserved_684;
	uint32_t reserved_688;
	uint32_t reserved_68c;
	uint32_t reserved_690;
	uint32_t reserved_694;
	uint32_t reserved_698;
	uint32_t reserved_69c;
	uint32_t reserved_6a0;
	uint32_t reserved_6a4;
	uint32_t reserved_6a8;
	uint32_t reserved_6ac;
	uint32_t reserved_6b0;
	uint32_t reserved_6b4;
	uint32_t reserved_6b8;
	uint32_t reserved_6bc;
	uint32_t reserved_6c0;
	uint32_t reserved_6c4;
	uint32_t reserved_6c8;
	uint32_t reserved_6cc;
	uint32_t reserved_6d0;
	uint32_t reserved_6d4;
	uint32_t reserved_6d8;
	uint32_t reserved_6dc;
	uint32_t reserved_6e0;
	uint32_t reserved_6e4;
	uint32_t reserved_6e8;
	uint32_t reserved_6ec;
	uint32_t reserved_6f0;
	uint32_t reserved_6f4;
	uint32_t reserved_6f8;
	union {
		struct {
			uint32_t date                          :    28;
			uint32_t reserved28                    :    4;
		};
		uint32_t val;
	} date;
} gpio_dev_t;

extern gpio_dev_t *GPIO;

void gpio_ll_pullup_en(gpio_dev_t *hw, gpio_num_t gpio_num);
void gpio_ll_pullup_dis(gpio_dev_t *hw, gpio_num_t gpio_num);
void gpio_ll_pulldown_en(gpio_dev_t *hw, gpio_num_t gpio_num);
void gpio_ll_pulldown_dis(gpio_dev_t *hw, gpio_num_t gpio_num);
void gpio_ll_set_intr_type(gpio_dev_t *hw, gpio_num_t gpio_num, gpio_int_type_t intr_type);
void gpio_ll_get_intr_status(gpio_dev_t *hw, uint32_t core_id, uint32_t *status);
void gpio_ll_get_intr_status_high(gpio_dev_t *hw, uint32_t core_id, uint32_t *status);
void gpio_ll_clear_intr_status(gpio_dev_t *hw, uint32_t mask);
void gpio_ll_clear_intr_status_high(gpio_dev_t *hw, uint32_t mask);
void gpio_ll_intr_enable_on_core(gpio_dev_t *hw, uint32_t core_id, gpio_num_t gpio_num);
void gpio_ll_intr_disable(gpio_dev_t *hw, gpio_num_t gpio_num);
void gpio_ll_input_disable(gpio_dev_t *hw, gpio_num_t gpio_num);
void gpio_ll_input_enable(gpio_dev_t *hw, gpio_num_t gpio_num);
void gpio_ll_output_disable(gpio_dev_t *hw, gpio_num_t gpio_num);
void gpio_ll_output_enable(gpio_dev_t *hw, gpio_num_t gpio_num);
void gpio_ll_od_disable(gpio_dev_t *hw, gpio_num_t gpio_num);
void gpio_ll_od_enable(gpio_dev_t *hw, gpio_num_t gpio_num);
void gpio_ll_set_level(gpio_dev_t *hw, gpio_num_t gpio_num, uint32_t level);
int gpio_ll_get_level(gpio_dev_t *hw, gpio_num_t gpio_num);
void gpio_ll_wakeup_enable(gpio_dev_t *hw, gpio_num_t gpio_num, gpio_int_type_t intr_type);
void gpio_ll_wakeup_disable(gpio_dev_t *hw, gpio_num_t gpio_num);
void gpio_ll_set_drive_capability(gpio_dev_t *hw, gpio_num_t gpio_num, gpio_drive_cap_t strength);
void gpio_ll_get_drive_capability(gpio_dev_t *hw, gpio_num_t gpio_num, gpio_drive_cap_t *strength);
void gpio_ll_deep_sleep_hold_en(gpio_dev_t *hw);
void gpio_ll_deep_sleep_hold_dis(gpio_dev_t *hw);
bool gpio_ll_deep_sleep_hold_is_en(gpio_dev_t *hw);
void gpio_ll_hold_en(gpio_dev_t *hw, gpio_num_t gpio_num);
void gpio_ll_hold_dis(gpio_dev_t *hw, gpio_num_t gpio_num);
bool gpio_ll_is_digital_io_hold(gpio_dev_t *hw, uint32_t gpio_num);
void gpio_ll_iomux_in(gpio_dev_t *hw, uint32_t gpio, uint32_t signal_idx);
void gpio_ll_iomux_out(gpio_dev_t *hw, uint8_t gpio_num, int func, uint32_t oen_inv);
void gpio_ll_force_hold_all(gpio_dev_t *hw);
void gpio_ll_force_unhold_all(void);
void gpio_ll_sleep_sel_en(gpio_dev_t *hw, gpio_num_t gpio_num);
void gpio_ll_sleep_sel_dis(gpio_dev_t *hw, gpio_num_t gpio_num);
void gpio_ll_sleep_pullup_dis(gpio_dev_t *hw, gpio_num_t gpio_num);
void gpio_ll_sleep_pullup_en(gpio_dev_t *hw, gpio_num_t gpio_num);
void gpio_ll_sleep_pulldown_en(gpio_dev_t *hw, gpio_num_t gpio_num);
void gpio_ll_sleep_pulldown_dis(gpio_dev_t *hw, gpio_num_t gpio_num);
void gpio_ll_sleep_input_disable(gpio_dev_t *hw, gpio_num_t gpio_num);
void gpio_ll_sleep_input_enable(gpio_dev_t *hw, gpio_num_t gpio_num);
void gpio_ll_sleep_output_disable(gpio_dev_t *hw, gpio_num_t gpio_num);
void gpio_ll_sleep_output_enable(gpio_dev_t *hw, gpio_num_t gpio_num);
