#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

#include "soc/rtc_cntl.h"

#define RTC_SLOW_CLK_CAL_REG    RTC_CNTL_STORE1_REG
#define RTC_BOOT_TIME_LOW_REG   RTC_CNTL_STORE2_REG
#define RTC_BOOT_TIME_HIGH_REG  RTC_CNTL_STORE3_REG
#define RTC_XTAL_FREQ_REG       RTC_CNTL_STORE4_REG
#define RTC_ENTRY_LENGTH_REG    RTC_CNTL_STORE5_REG
#define RTC_ENTRY_ADDR_REG      RTC_CNTL_STORE6_REG
#define RTC_RESET_CAUSE_REG     RTC_CNTL_STORE6_REG
#define RTC_MEMORY_CRC_REG      RTC_CNTL_STORE7_REG

#define RTC_DISABLE_ROM_LOG ((1 << 0) | (1 << 16)) //!< Disable logging from the ROM code.

typedef enum {
	AWAKE = 0,             //<CPU ON
	LIGHT_SLEEP = 1<<0,    //CPU waiti, PLL ON.  We don't need explicitly set this mode.
	DEEP_SLEEP  = 1<<1     //CPU OFF, PLL OFF, only specific timer could wake up
} SLEEP_MODE;

typedef enum {
	NO_MEAN                =  0,
	POWERON_RESET          =  1,    
	RTC_SW_SYS_RESET       =  3,    
	DEEPSLEEP_RESET        =  5,    
	TG0WDT_SYS_RESET       =  7,    
	TG1WDT_SYS_RESET       =  8,    
	RTCWDT_SYS_RESET       =  9,    
	INTRUSION_RESET        = 10,    
	TG0WDT_CPU_RESET       = 11,    
	RTC_SW_CPU_RESET       = 12,    
	RTCWDT_CPU_RESET       = 13,    
	RTCWDT_BROWN_OUT_RESET = 15,    
	RTCWDT_RTC_RESET       = 16,    
	TG1WDT_CPU_RESET       = 17,    
	SUPER_WDT_RESET        = 18,    
	GLITCH_RTC_RESET       = 19,    
	EFUSE_RESET            = 20,    
	USB_UART_CHIP_RESET    = 21,    
	USB_JTAG_CHIP_RESET    = 22,    
	POWER_GLITCH_RESET     = 23,    
} RESET_REASON;

typedef enum {
	NO_SLEEP        = 0,
	EXT_EVENT0_TRIG = 1<<0,
	EXT_EVENT1_TRIG = 1<<1,
	GPIO_TRIG       = 1<<2,
	TIMER_EXPIRE    = 1<<3,
	SDIO_TRIG       = 1<<4,
	MAC_TRIG        = 1<<5,
	UART0_TRIG      = 1<<6,
	UART1_TRIG      = 1<<7,
	TOUCH_TRIG      = 1<<8,
	SAR_TRIG        = 1<<9,
	BT_TRIG         = 1<<10,
	RISCV_TRIG      = 1<<11,
	XTAL_DEAD_TRIG  = 1<<12,
	RISCV_TRAP_TRIG = 1<<13,
	USB_TRIG        = 1<<14
} WAKEUP_REASON;

typedef enum {
	DISEN_WAKEUP       = NO_SLEEP,
	EXT_EVENT0_TRIG_EN = EXT_EVENT0_TRIG,
	EXT_EVENT1_TRIG_EN = EXT_EVENT1_TRIG,
	GPIO_TRIG_EN       = GPIO_TRIG,
	TIMER_EXPIRE_EN    = TIMER_EXPIRE,
	SDIO_TRIG_EN       = SDIO_TRIG,
	MAC_TRIG_EN        = MAC_TRIG,
	UART0_TRIG_EN      = UART0_TRIG,
	UART1_TRIG_EN      = UART1_TRIG,
	TOUCH_TRIG_EN      = TOUCH_TRIG,
	SAR_TRIG_EN        = SAR_TRIG,
	BT_TRIG_EN         = BT_TRIG,
	RISCV_TRIG_EN      = RISCV_TRIG,
	XTAL_DEAD_TRIG_EN  = XTAL_DEAD_TRIG,
	RISCV_TRAP_TRIG_EN = RISCV_TRAP_TRIG,
	USB_TRIG_EN        = USB_TRIG
} WAKEUP_ENABLE;

RESET_REASON rtc_get_reset_reason(int cpu_no);
WAKEUP_REASON rtc_get_wakeup_cause(void);

typedef void (* esp_rom_wake_func_t)(void);


esp_rom_wake_func_t esp_rom_get_rtc_wake_addr(void);


void esp_rom_set_rtc_wake_addr(esp_rom_wake_func_t entry_addr, size_t length);


void rtc_suppress_rom_log(void); // REG_SET_BIT(RTC_CNTL_STORE4_REG, RTC_DISABLE_ROM_LOG);


void software_reset(void);


void software_reset_cpu(int cpu_no);
