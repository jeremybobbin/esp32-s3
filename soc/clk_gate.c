#include <stdint.h>
#include <stdbool.h>
#include "heap/soc_memory_layout.h"


#define DR_REG_SYSTEM_BASE                      0x600c0000

#define SYSTEM_PERIP_CLK_EN0_REG          (DR_REG_SYSTEM_BASE + 0x18)
#define SYSTEM_PERIP_CLK_EN1_REG          (DR_REG_SYSTEM_BASE + 0x1C)
#define SYSTEM_PERIP_RST_EN0_REG          (DR_REG_SYSTEM_BASE + 0x20)
#define SYSTEM_PERIP_RST_EN1_REG          (DR_REG_SYSTEM_BASE + 0x24)

#define SYSTEM_CLK_EN                (1<<0)
#define SYSTEM_TIMERS_CLK_EN         (1<<0)
#define SYSTEM_PERI_BACKUP_CLK_EN    (1<<0)
#define SYSTEM_SPI01_CLK_EN          (1<<1)
#define SYSTEM_CRYPTO_AES_CLK_EN     (1<<1)
#define SYSTEM_PCNT_CLK_EN           (1<<10)
#define SYSTEM_USB_DEVICE_CLK_EN     (1<<10)
#define SYSTEM_LEDC_CLK_EN           (1<<11)
#define SYSTEM_UHCI1_CLK_EN          (1<<12)
#define SYSTEM_TIMERGROUP_CLK_EN     (1<<13)
#define SYSTEM_EFUSE_CLK_EN          (1<<14)
#define SYSTEM_TIMERGROUP1_CLK_EN    (1<<15)
#define SYSTEM_SPI3_CLK_EN           (1<<16)
#define SYSTEM_PWM0_CLK_EN           (1<<17)
#define SYSTEM_I2C_EXT1_CLK_EN       (1<<18)
#define SYSTEM_TWAI_CLK_EN           (1<<19)
#define SYSTEM_UART_CLK_EN           (1<<2)
#define SYSTEM_CRYPTO_SHA_CLK_EN     (1<<2)
#define SYSTEM_PWM1_CLK_EN           (1<<20)
#define SYSTEM_I2S1_CLK_EN           (1<<21)
#define SYSTEM_SPI2_DMA_CLK_EN       (1<<22)
#define SYSTEM_USB_CLK_EN            (1<<23)
#define SYSTEM_UART_MEM_CLK_EN       (1<<24)
#define SYSTEM_PWM2_CLK_EN           (1<<25)
#define SYSTEM_PWM3_CLK_EN           (1<<26)
#define SYSTEM_SPI3_DMA_CLK_EN       (1<<27)
#define SYSTEM_APB_SARADC_CLK_EN     (1<<28)
#define SYSTEM_SYSTIMER_CLK_EN       (1<<29)
#define SYSTEM_WDG_CLK_EN            (1<<3)
#define SYSTEM_CRYPTO_RSA_CLK_EN     (1<<3)
#define SYSTEM_ADC2_ARB_CLK_EN       (1<<30)
#define SYSTEM_SPI4_CLK_EN           (1<<31)
#define SYSTEM_I2S0_CLK_EN           (1<<4)
#define SYSTEM_CRYPTO_DS_CLK_EN      (1<<4)
#define SYSTEM_UART1_CLK_EN          (1<<5)
#define SYSTEM_CRYPTO_HMAC_CLK_EN    (1<<5)
#define SYSTEM_DMA_CLK_EN            (1<<6)
#define SYSTEM_SPI2_CLK_EN           (1<<6)
#define SYSTEM_I2C_EXT0_CLK_EN       (1<<7)
#define SYSTEM_SDIO_HOST_CLK_EN      (1<<7)
#define SYSTEM_UHCI0_CLK_EN          (1<<8)
#define SYSTEM_LCD_CAM_CLK_EN        (1<<8)
#define SYSTEM_RMT_CLK_EN            (1<<9)
#define SYSTEM_UART2_CLK_EN          (1<<9)



#define SYSTEM_SPI4_RST           (1<<31)
#define SYSTEM_ADC2_ARB_RST       (1<<30)
#define SYSTEM_SYSTIMER_RST       (1<<29)
#define SYSTEM_APB_SARADC_RST     (1<<28)
#define SYSTEM_SPI3_DMA_RST       (1<<27)
#define SYSTEM_PWM3_RST           (1<<26)
#define SYSTEM_PWM2_RST           (1<<25)
#define SYSTEM_UART_MEM_RST       (1<<24)
#define SYSTEM_USB_RST            (1<<23)
#define SYSTEM_SPI2_DMA_RST       (1<<22)
#define SYSTEM_I2S1_RST           (1<<21)
#define SYSTEM_PWM1_RST           (1<<20)
#define SYSTEM_TWAI_RST           (1<<19)
#define SYSTEM_I2C_EXT1_RST       (1<<18)
#define SYSTEM_PWM0_RST           (1<<17)
#define SYSTEM_SPI3_RST           (1<<16)
#define SYSTEM_TIMERGROUP1_RST    (1<<15)
#define SYSTEM_EFUSE_RST          (1<<14)
#define SYSTEM_TIMERGROUP_RST     (1<<13)
#define SYSTEM_UHCI1_RST          (1<<12)
#define SYSTEM_LEDC_RST           (1<<11)
#define SYSTEM_PCNT_RST           (1<<10)
#define SYSTEM_RMT_RST            (1<<9)
#define SYSTEM_UHCI0_RST          (1<<8)
#define SYSTEM_I2C_EXT0_RST       (1<<7)
#define SYSTEM_SPI2_RST           (1<<6)
#define SYSTEM_UART1_RST          (1<<5)
#define SYSTEM_I2S0_RST           (1<<4)
#define SYSTEM_WDG_RST            (1<<3)
#define SYSTEM_UART_RST           (1<<2)
#define SYSTEM_SPI01_RST          (1<<1)
#define SYSTEM_TIMERS_RST         (1<<0)
#define SYSTEM_USB_DEVICE_RST     (1<<10)
#define SYSTEM_UART2_RST          (1<<9)
#define SYSTEM_LCD_CAM_RST        (1<<8)
#define SYSTEM_SDIO_HOST_RST      (1<<7)
#define SYSTEM_DMA_RST            (1<<6)
#define SYSTEM_CRYPTO_HMAC_RST    (1<<5)
#define SYSTEM_CRYPTO_DS_RST      (1<<4)
#define SYSTEM_CRYPTO_RSA_RST     (1<<3)
#define SYSTEM_CRYPTO_SHA_RST     (1<<2)
#define SYSTEM_CRYPTO_AES_RST     (1<<1)
#define SYSTEM_PERI_BACKUP_RST    (1<<0)

#define SYSTEM_WIFI_CLK_RNG_EN (1<<15)
#define SYSTEM_EFUSE_RST    (1<<14)

#define DR_REG_SYSCON_BASE                      0x60026000

#define SYSCON_CLK_OUT_EN_REG          (DR_REG_SYSCON_BASE + 0x8)
#define SYSCON_WIFI_CLK_EN_REG          (DR_REG_SYSCON_BASE + 0x14)
#define SYSCON_WIFI_RST_EN_REG          (DR_REG_SYSCON_BASE + 0x18)
#define SYSTEM_WIFI_CLK_EN_REG SYSCON_WIFI_CLK_EN_REG
#define SYSTEM_CORE_RST_EN_REG SYSTEM_WIFI_RST_EN_REG
#define SYSTEM_WIFI_RST_EN_REG SYSCON_WIFI_RST_EN_REG
#define SYSCON_FRONT_END_MEM_PD_REG          (DR_REG_SYSCON_BASE + 0x9C)

#define SYSTEM_WIFI_CLK_WIFI_EN_M  ((SYSTEM_WIFI_CLK_WIFI_EN_V)<<(SYSTEM_WIFI_CLK_WIFI_EN_S))
#define SYSTEM_WIFI_CLK_WIFI_EN_V  0x0
#define SYSTEM_WIFI_CLK_WIFI_EN_S  0

#define SYSTEM_WIFI_CLK_BT_EN  0x0
#define SYSTEM_WIFI_CLK_BT_EN_M  ((SYSTEM_WIFI_CLK_BT_EN_V)<<(SYSTEM_WIFI_CLK_BT_EN_S))
#define SYSTEM_WIFI_CLK_BT_EN_V  0x0
#define SYSTEM_WIFI_CLK_BT_EN_S  0

#define SYSTEM_RST_EN_DEDICATED_GPIO    (1<<7)

#define SYSTEM_WIFI_CLK_WIFI_BT_COMMON_M 0x78078F

#define SYSTEM_WIFI_CLK_EN_REG SYSCON_WIFI_CLK_EN_REG
#define SYSTEM_BT_BASEBAND_EN (1<<11)
#define SYSTEM_BT_LC_EN (3<<16)
#define SYSTEM_CORE_RST_EN_REG SYSTEM_WIFI_RST_EN_REG
#define SYSTEM_WIFIMAC_RST          (1<<2)
#define SYSTEM_BTBB_RST             (1<<3)
#define SYSTEM_RW_BTMAC_RST         (1<<9)
#define SYSTEM_RW_BTLP_RST          (1<<10)
#define SYSTEM_RW_BTMAC_REG_RST     (1<<11)
#define SYSTEM_RW_BTLP_REG_RST      (1<<12)
#define SYSTEM_BTBB_REG_RST         (1<<13)
#define SYSTEM_CPU_PERI_CLK_EN_REG          (DR_REG_SYSTEM_BASE + 0x8)
#define SYSTEM_CLK_EN_DEDICATED_GPIO    (1<<7)
#define SYSTEM_CPU_PERI_RST_EN_REG          (DR_REG_SYSTEM_BASE + 0xC)
#define SYSTEM_RST_EN_DEDICATED_GPIO    (1<<7)
#define SYSTEM_TWAI_CLK_EN    (1<<19)
#define SYSTEM_USB_RST    (1<<23)
#define SYSTEM_RMT_RST    (1<<9)
#define SYSTEM_TIMERS_RST    (1<<0)
#define SYSTEM_DMA_RST    (1<<6)
#define SYSTEM_CRYPTO_AES_RST    (1<<1)
#define SYSTEM_CLK_EN    (1<<0)


typedef enum {
	PERIPH_LEDC_MODULE = 0,
	PERIPH_UART0_MODULE,
	PERIPH_UART1_MODULE,
	PERIPH_UART2_MODULE,
	PERIPH_USB_MODULE,
	PERIPH_I2C0_MODULE,
	PERIPH_I2C1_MODULE,
	PERIPH_I2S0_MODULE,
	PERIPH_I2S1_MODULE,
	PERIPH_LCD_CAM_MODULE,
	PERIPH_TIMG0_MODULE,
	PERIPH_TIMG1_MODULE,
	PERIPH_PWM0_MODULE,
	PERIPH_PWM1_MODULE,
	PERIPH_PWM2_MODULE,
	PERIPH_PWM3_MODULE,
	PERIPH_UHCI0_MODULE,
	PERIPH_UHCI1_MODULE,
	PERIPH_RMT_MODULE,
	PERIPH_PCNT_MODULE,
	PERIPH_SPI_MODULE,
	PERIPH_SPI2_MODULE,
	PERIPH_SPI3_MODULE,
	PERIPH_SDMMC_MODULE,
	PERIPH_TWAI_MODULE,
	PERIPH_RNG_MODULE,
	PERIPH_WIFI_MODULE,
	PERIPH_BT_MODULE,
	PERIPH_WIFI_BT_COMMON_MODULE,
	PERIPH_BT_BASEBAND_MODULE,
	PERIPH_BT_LC_MODULE,
	PERIPH_AES_MODULE,
	PERIPH_SHA_MODULE,
	PERIPH_HMAC_MODULE,
	PERIPH_DS_MODULE,
	PERIPH_RSA_MODULE,
	PERIPH_SYSTIMER_MODULE,
	PERIPH_GDMA_MODULE,
	PERIPH_DEDIC_GPIO_MODULE,
	PERIPH_SARADC_MODULE,
	PERIPH_MODULE_MAX
} periph_module_t;

uint32_t periph_ll_get_clk_en_mask(periph_module_t periph)
{
	switch (periph) {
	case PERIPH_SARADC_MODULE:
		return SYSTEM_APB_SARADC_CLK_EN;
	case PERIPH_RMT_MODULE:
		return SYSTEM_RMT_CLK_EN;
	case PERIPH_LEDC_MODULE:
		return SYSTEM_LEDC_CLK_EN;
	case PERIPH_UART0_MODULE:
		return SYSTEM_UART_CLK_EN;
	case PERIPH_UART1_MODULE:
		return SYSTEM_UART1_CLK_EN;
	case PERIPH_UART2_MODULE:
		return SYSTEM_UART2_CLK_EN;
	case PERIPH_USB_MODULE:
		return SYSTEM_USB_CLK_EN;
	case PERIPH_I2C0_MODULE:
		return SYSTEM_I2C_EXT0_CLK_EN;
	case PERIPH_I2C1_MODULE:
		return SYSTEM_I2C_EXT1_CLK_EN;
	case PERIPH_I2S0_MODULE:
		return SYSTEM_I2S0_CLK_EN;
	case PERIPH_I2S1_MODULE:
		return SYSTEM_I2S1_CLK_EN;
	case PERIPH_LCD_CAM_MODULE:
		return SYSTEM_LCD_CAM_CLK_EN;
	case PERIPH_TIMG0_MODULE:
		return SYSTEM_TIMERGROUP_CLK_EN;
	case PERIPH_TIMG1_MODULE:
		return SYSTEM_TIMERGROUP1_CLK_EN;
	case PERIPH_PWM0_MODULE:
		return SYSTEM_PWM0_CLK_EN;
	case PERIPH_PWM1_MODULE:
		return SYSTEM_PWM1_CLK_EN;
	case PERIPH_UHCI0_MODULE:
		return SYSTEM_UHCI0_CLK_EN;
	case PERIPH_UHCI1_MODULE:
		return SYSTEM_UHCI1_CLK_EN;
	case PERIPH_PCNT_MODULE:
		return SYSTEM_PCNT_CLK_EN;
	case PERIPH_SPI_MODULE:
		return SYSTEM_SPI01_CLK_EN;
	case PERIPH_SPI2_MODULE:
		return SYSTEM_SPI2_CLK_EN;
	case PERIPH_SPI3_MODULE:
		return SYSTEM_SPI3_CLK_EN;
	case PERIPH_SDMMC_MODULE:
		return SYSTEM_SDIO_HOST_CLK_EN;
	case PERIPH_TWAI_MODULE:
		return SYSTEM_TWAI_CLK_EN;
	case PERIPH_RNG_MODULE:
		return SYSTEM_WIFI_CLK_RNG_EN;
	case PERIPH_WIFI_MODULE:
		return SYSTEM_WIFI_CLK_WIFI_EN_M;
	case PERIPH_BT_MODULE:
		return SYSTEM_WIFI_CLK_BT_EN_M;
	case PERIPH_WIFI_BT_COMMON_MODULE:
		return SYSTEM_WIFI_CLK_WIFI_BT_COMMON_M;
	case PERIPH_BT_BASEBAND_MODULE:
		return SYSTEM_BT_BASEBAND_EN;
	case PERIPH_BT_LC_MODULE:
		return SYSTEM_BT_LC_EN;
	case PERIPH_SYSTIMER_MODULE:
		return SYSTEM_SYSTIMER_CLK_EN;
	case PERIPH_DEDIC_GPIO_MODULE:
		return SYSTEM_CLK_EN_DEDICATED_GPIO;
	case PERIPH_GDMA_MODULE:
		return SYSTEM_DMA_CLK_EN;
	case PERIPH_AES_MODULE:
		return SYSTEM_CRYPTO_AES_CLK_EN;
	case PERIPH_SHA_MODULE:
		return SYSTEM_CRYPTO_SHA_CLK_EN;
	case PERIPH_RSA_MODULE:
		return SYSTEM_CRYPTO_RSA_CLK_EN;
	case PERIPH_HMAC_MODULE:
		return SYSTEM_CRYPTO_HMAC_CLK_EN;
	case PERIPH_DS_MODULE:
		return SYSTEM_CRYPTO_DS_CLK_EN;
	default:
		return 0;
	}
}

uint32_t periph_ll_get_rst_en_mask(periph_module_t periph, bool enable)
{
	switch (periph) {
	case PERIPH_SARADC_MODULE:
		return SYSTEM_APB_SARADC_RST;
	case PERIPH_RMT_MODULE:
		return SYSTEM_RMT_RST;
	case PERIPH_LEDC_MODULE:
		return SYSTEM_LEDC_RST;
	case PERIPH_WIFI_MODULE:
		return SYSTEM_WIFIMAC_RST;
	case PERIPH_BT_MODULE:
		return  (SYSTEM_BTBB_RST | SYSTEM_BTBB_REG_RST | SYSTEM_RW_BTMAC_RST | SYSTEM_RW_BTLP_RST | SYSTEM_RW_BTMAC_REG_RST | SYSTEM_RW_BTLP_REG_RST);
	case PERIPH_UART0_MODULE:
		return SYSTEM_UART_RST;
	case PERIPH_UART1_MODULE:
		return SYSTEM_UART1_RST;
	case PERIPH_UART2_MODULE:
		return SYSTEM_UART2_RST;
	case PERIPH_USB_MODULE:
		return SYSTEM_USB_RST;
	case PERIPH_I2C0_MODULE:
		return SYSTEM_I2C_EXT0_RST;
	case PERIPH_I2C1_MODULE:
		return SYSTEM_I2C_EXT1_RST;
	case PERIPH_I2S0_MODULE:
		return SYSTEM_I2S0_RST;
	case PERIPH_I2S1_MODULE:
		return SYSTEM_I2S1_RST;
	case PERIPH_LCD_CAM_MODULE:
		return SYSTEM_LCD_CAM_RST;
	case PERIPH_TIMG0_MODULE:
		return SYSTEM_TIMERGROUP_RST;
	case PERIPH_TIMG1_MODULE:
		return SYSTEM_TIMERGROUP1_RST;
	case PERIPH_PWM0_MODULE:
		return SYSTEM_PWM0_RST;
	case PERIPH_PWM1_MODULE:
		return SYSTEM_PWM1_RST;
	case PERIPH_UHCI0_MODULE:
		return SYSTEM_UHCI0_RST;
	case PERIPH_UHCI1_MODULE:
		return SYSTEM_UHCI1_RST;
	case PERIPH_PCNT_MODULE:
		return SYSTEM_PCNT_RST;
	case PERIPH_SPI_MODULE:
		return SYSTEM_SPI01_RST;
	case PERIPH_SPI2_MODULE:
		return SYSTEM_SPI2_RST;
	case PERIPH_SPI3_MODULE:
		return SYSTEM_SPI3_RST;
	case PERIPH_SDMMC_MODULE:
		return SYSTEM_SDIO_HOST_RST;
	case PERIPH_TWAI_MODULE:
		return SYSTEM_TWAI_RST;
	case PERIPH_SYSTIMER_MODULE:
		return SYSTEM_SYSTIMER_RST;
	case PERIPH_DEDIC_GPIO_MODULE:
		return SYSTEM_RST_EN_DEDICATED_GPIO;
	case PERIPH_GDMA_MODULE:
		return SYSTEM_DMA_RST;
	case PERIPH_HMAC_MODULE:
		return SYSTEM_CRYPTO_HMAC_RST;
	case PERIPH_DS_MODULE:
		return SYSTEM_CRYPTO_DS_RST;
	case PERIPH_AES_MODULE:
		if (enable == true) {
			// Clear reset on digital signature, otherwise AES unit is held in reset also.
			return (SYSTEM_CRYPTO_AES_RST | SYSTEM_CRYPTO_DS_RST);
		} else {
			//Don't return other units to reset, as this pulls reset on RSA & SHA units, respectively.
			return SYSTEM_CRYPTO_AES_RST;
		}
	case PERIPH_SHA_MODULE:
		if (enable == true) {
			// Clear reset on digital signature and HMAC, otherwise SHA is held in reset
			return (SYSTEM_CRYPTO_SHA_RST | SYSTEM_CRYPTO_DS_RST | SYSTEM_CRYPTO_HMAC_RST) ;
		} else {
			// Don't assert reset on secure boot, otherwise AES is held in reset
			return SYSTEM_CRYPTO_SHA_RST;
		}
	case PERIPH_RSA_MODULE:
		if (enable == true) {
			/* also clear reset on digital signature, otherwise RSA is held in reset */
			return (SYSTEM_CRYPTO_RSA_RST | SYSTEM_CRYPTO_DS_RST);
		} else {
			/* don't reset digital signature unit, as this resets AES also */
			return SYSTEM_CRYPTO_RSA_RST;
		}
	default:
		return 0;
	}
}

static uint32_t periph_ll_get_clk_en_reg(periph_module_t periph)
{
	switch (periph) {
	case PERIPH_DEDIC_GPIO_MODULE:
		return SYSTEM_CPU_PERI_CLK_EN_REG;
	case PERIPH_RNG_MODULE:
	case PERIPH_WIFI_MODULE:
	case PERIPH_BT_MODULE:
	case PERIPH_WIFI_BT_COMMON_MODULE:
	case PERIPH_BT_BASEBAND_MODULE:
	case PERIPH_BT_LC_MODULE:
		return SYSTEM_WIFI_CLK_EN_REG ;
	case PERIPH_UART2_MODULE:
	case PERIPH_SDMMC_MODULE:
	case PERIPH_LCD_CAM_MODULE:
	case PERIPH_GDMA_MODULE:
	case PERIPH_HMAC_MODULE:
	case PERIPH_DS_MODULE:
	case PERIPH_AES_MODULE:
	case PERIPH_SHA_MODULE:
	case PERIPH_RSA_MODULE:
		return SYSTEM_PERIP_CLK_EN1_REG;
	default:
		return SYSTEM_PERIP_CLK_EN0_REG;
	}
}

static uint32_t periph_ll_get_rst_en_reg(periph_module_t periph)
{
	switch (periph) {
	case PERIPH_DEDIC_GPIO_MODULE:
		return SYSTEM_CPU_PERI_RST_EN_REG;
	case PERIPH_RNG_MODULE:
	case PERIPH_WIFI_MODULE:
	case PERIPH_BT_MODULE:
	case PERIPH_WIFI_BT_COMMON_MODULE:
	case PERIPH_BT_BASEBAND_MODULE:
	case PERIPH_BT_LC_MODULE:
		return SYSTEM_CORE_RST_EN_REG;
	case PERIPH_UART2_MODULE:
	case PERIPH_SDMMC_MODULE:
	case PERIPH_LCD_CAM_MODULE:
	case PERIPH_GDMA_MODULE:
	case PERIPH_HMAC_MODULE:
	case PERIPH_DS_MODULE:
	case PERIPH_AES_MODULE:
	case PERIPH_SHA_MODULE:
	case PERIPH_RSA_MODULE:
		return SYSTEM_PERIP_RST_EN1_REG;
	default:
		return SYSTEM_PERIP_RST_EN0_REG;
	}
}

void periph_ll_enable_clk_clear_rst(periph_module_t periph)
{
	DPORT_SET_PERI_REG_MASK(periph_ll_get_clk_en_reg(periph), periph_ll_get_clk_en_mask(periph));
	DPORT_CLEAR_PERI_REG_MASK(periph_ll_get_rst_en_reg(periph), periph_ll_get_rst_en_mask(periph, true));
}

void periph_ll_disable_clk_set_rst(periph_module_t periph)
{
	DPORT_CLEAR_PERI_REG_MASK(periph_ll_get_clk_en_reg(periph), periph_ll_get_clk_en_mask(periph));
	DPORT_SET_PERI_REG_MASK(periph_ll_get_rst_en_reg(periph), periph_ll_get_rst_en_mask(periph, false));
}

void IRAM_ATTR periph_ll_wifi_bt_module_enable_clk_clear_rst(void)
{
	DPORT_SET_PERI_REG_MASK(SYSTEM_WIFI_CLK_EN_REG, SYSTEM_WIFI_CLK_WIFI_BT_COMMON_M);
	DPORT_CLEAR_PERI_REG_MASK(SYSTEM_CORE_RST_EN_REG, 0);
}

void IRAM_ATTR periph_ll_wifi_bt_module_disable_clk_set_rst(void)
{
	DPORT_CLEAR_PERI_REG_MASK(SYSTEM_WIFI_CLK_EN_REG, SYSTEM_WIFI_CLK_WIFI_BT_COMMON_M);
	DPORT_SET_PERI_REG_MASK(SYSTEM_CORE_RST_EN_REG, 0);
}

void periph_ll_reset(periph_module_t periph)
{
	DPORT_SET_PERI_REG_MASK(periph_ll_get_rst_en_reg(periph), periph_ll_get_rst_en_mask(periph, false));
	DPORT_CLEAR_PERI_REG_MASK(periph_ll_get_rst_en_reg(periph), periph_ll_get_rst_en_mask(periph, false));
}

bool IRAM_ATTR periph_ll_periph_enabled(periph_module_t periph)
{
	return DPORT_REG_GET_BIT(periph_ll_get_rst_en_reg(periph), periph_ll_get_rst_en_mask(periph, false)) == 0 &&
		   DPORT_REG_GET_BIT(periph_ll_get_clk_en_reg(periph), periph_ll_get_clk_en_mask(periph)) != 0;
}

void periph_ll_wifi_module_enable_clk_clear_rst(void)
{
	DPORT_SET_PERI_REG_MASK(SYSTEM_WIFI_CLK_EN_REG, SYSTEM_WIFI_CLK_WIFI_EN_M);
	DPORT_CLEAR_PERI_REG_MASK(SYSTEM_CORE_RST_EN_REG, 0);
}

void periph_ll_wifi_module_disable_clk_set_rst(void)
{
	DPORT_CLEAR_PERI_REG_MASK(SYSTEM_WIFI_CLK_EN_REG, SYSTEM_WIFI_CLK_WIFI_EN_M);
	DPORT_SET_PERI_REG_MASK(SYSTEM_CORE_RST_EN_REG, 0);
}
