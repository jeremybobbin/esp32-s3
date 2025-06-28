#include <stdint.h>
#include <stdbool.h>

#include "soc/peripherals.h"

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

uint32_t periph_ll_get_clk_en_mask(periph_module_t periph);
uint32_t periph_ll_get_rst_en_mask(periph_module_t periph, bool enable);
void periph_ll_enable_clk_clear_rst(periph_module_t periph);
void periph_ll_disable_clk_set_rst(periph_module_t periph);
void IRAM_ATTR periph_ll_wifi_bt_module_enable_clk_clear_rst(void);
void IRAM_ATTR periph_ll_wifi_bt_module_disable_clk_set_rst(void);
void periph_ll_reset(periph_module_t periph);
bool IRAM_ATTR periph_ll_periph_enabled(periph_module_t periph);
void periph_ll_wifi_module_enable_clk_clear_rst(void);
void periph_ll_wifi_module_disable_clk_set_rst(void);
