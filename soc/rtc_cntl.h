
#define RTC_CNTL_LL_RETENTION_TARGET_CPU         (BIT(0))
#define RTC_CNTL_LL_RETENTION_TARGET_TAGMEM      (BIT(1))

void rtc_cntl_ll_set_wakeup_timer(uint64_t t);
uint32_t rtc_cntl_ll_ext1_get_wakeup_pins(void);
void rtc_cntl_ll_ext1_set_wakeup_pins(uint32_t mask, int mode);
void rtc_cntl_ll_ext1_clear_wakeup_pins(void);
void rtc_cntl_ll_set_tagmem_retention_link_addr(uint32_t link_addr);
void rtc_cntl_ll_enable_tagmem_retention(void);
void rtc_cntl_ll_enable_icache_tagmem_retention(uint32_t start_point, uint32_t vld_size, uint32_t size);
void rtc_cntl_ll_enable_dcache_tagmem_retention(uint32_t start_point, uint32_t vld_size, uint32_t size);
void rtc_cntl_ll_disable_tagmem_retention(void);
void rtc_cntl_ll_disable_icache_tagmem_retention(void);
void rtc_cntl_ll_disable_dcache_tagmem_retention(void);
void rtc_cntl_ll_set_cpu_retention_link_addr(uint32_t link_addr);
void rtc_cntl_ll_enable_cpu_retention_clock(void);
void rtc_cntl_ll_enable_cpu_retention(void);
void rtc_cntl_ll_config_cpu_retention_timing(int wait, int clkoff_wait, int done_wait);
void rtc_cntl_ll_disable_cpu_retention(void);
void rtc_cntl_ll_ulp_int_clear(void);
