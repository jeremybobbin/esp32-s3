#include "soc/soc.h"
#include "soc/rtc.h"
#include "soc/rtc_cntl_reg.h"
#include "soc/apb_ctrl_reg.h"
#include "soc/soc_caps.h"
#include "esp32s3/rom/lldesc.h"
#include "esp32s3/rom/cache.h"
#include "esp_attr.h"

#define RTC_CNTL_HAL_LINK_BUF_SIZE_MIN  (SOC_RTC_CNTL_CPU_PD_DMA_BLOCK_SIZE) /* The minimum size of dma link buffer */
#define RTC_CNTL_LL_RETENTION_TARGET_CPU         (1<<0)
#define RTC_CNTL_LL_RETENTION_TARGET_TAGMEM      (1<<1)

typedef struct rtc_cntl_link_buf_conf {
	uint32_t cfg[4];    /* 4 word for dma link buffer configuration */
} rtc_cntl_link_buf_conf_t;

void rtc_cntl_ll_set_wakeup_timer(uint64_t t)
{
	WRITE_PERI_REG(RTC_CNTL_SLP_TIMER0_REG, t & UINT32_MAX);
	WRITE_PERI_REG(RTC_CNTL_SLP_TIMER1_REG, t >> 32);

	SET_PERI_REG_MASK(RTC_CNTL_INT_CLR_REG, RTC_CNTL_MAIN_TIMER_INT_CLR_M);
	SET_PERI_REG_MASK(RTC_CNTL_SLP_TIMER1_REG, RTC_CNTL_MAIN_TIMER_ALARM_EN_M);
}

uint32_t rtc_cntl_ll_ext1_get_wakeup_pins(void)
{
	return REG_GET_FIELD(RTC_CNTL_EXT_WAKEUP1_STATUS_REG, RTC_CNTL_EXT_WAKEUP1_STATUS);
}

void rtc_cntl_ll_ext1_set_wakeup_pins(uint32_t mask, int mode)
{
	REG_SET_FIELD(RTC_CNTL_EXT_WAKEUP1_REG, RTC_CNTL_EXT_WAKEUP1_SEL, mask);
	SET_PERI_REG_BITS(RTC_CNTL_EXT_WAKEUP_CONF_REG, 0x1,
			mode, RTC_CNTL_EXT_WAKEUP1_LV_S);
}

void rtc_cntl_ll_ext1_clear_wakeup_pins(void)
{
	REG_SET_BIT(RTC_CNTL_EXT_WAKEUP1_REG, RTC_CNTL_EXT_WAKEUP1_STATUS_CLR);
}

void rtc_cntl_ll_set_tagmem_retention_link_addr(uint32_t link_addr)
{
	REG_SET_FIELD(APB_CTRL_RETENTION_CTRL1_REG, APB_CTRL_RETENTION_TAG_LINK_ADDR, link_addr);
}

void rtc_cntl_ll_enable_tagmem_retention(void)
{
	/* Enable i/d-cache tagmem retenttion. cpu: 1, tagmem: 2, cpu + tagmem: 3 */
	uint32_t target = REG_GET_FIELD(RTC_CNTL_RETENTION_CTRL_REG, RTC_CNTL_RETENTION_TARGET);
	REG_SET_FIELD(RTC_CNTL_RETENTION_CTRL_REG, RTC_CNTL_RETENTION_TARGET, (target | RTC_CNTL_LL_RETENTION_TARGET_TAGMEM));
}

void rtc_cntl_ll_enable_icache_tagmem_retention(uint32_t start_point, uint32_t vld_size, uint32_t size)
{
	REG_SET_FIELD(APB_CTRL_RETENTION_CTRL2_REG, APB_CTRL_RET_ICACHE_START_POINT, start_point);
	REG_SET_FIELD(APB_CTRL_RETENTION_CTRL2_REG, APB_CTRL_RET_ICACHE_VLD_SIZE, vld_size);
	REG_SET_FIELD(APB_CTRL_RETENTION_CTRL2_REG, APB_CTRL_RET_ICACHE_SIZE, size);
	REG_SET_BIT(APB_CTRL_RETENTION_CTRL2_REG, APB_CTRL_RET_ICACHE_ENABLE);
}

void rtc_cntl_ll_enable_dcache_tagmem_retention(uint32_t start_point, uint32_t vld_size, uint32_t size)
{
	REG_SET_FIELD(APB_CTRL_RETENTION_CTRL3_REG, APB_CTRL_RET_DCACHE_START_POINT, start_point);
	REG_SET_FIELD(APB_CTRL_RETENTION_CTRL3_REG, APB_CTRL_RET_DCACHE_VLD_SIZE, vld_size);
	REG_SET_FIELD(APB_CTRL_RETENTION_CTRL3_REG, APB_CTRL_RET_DCACHE_SIZE, size);
	REG_SET_BIT(APB_CTRL_RETENTION_CTRL3_REG, APB_CTRL_RET_DCACHE_ENABLE);
}

void rtc_cntl_ll_disable_tagmem_retention(void)
{
	/* Enable i/d-cache tagmem retenttion. cpu: 1, tagmem: 2, cpu + tagmem: 3 */
	uint32_t target = REG_GET_FIELD(RTC_CNTL_RETENTION_CTRL_REG, RTC_CNTL_RETENTION_TARGET);
	REG_SET_FIELD(RTC_CNTL_RETENTION_CTRL_REG, RTC_CNTL_RETENTION_TARGET, (target & ~RTC_CNTL_LL_RETENTION_TARGET_TAGMEM));
}

void rtc_cntl_ll_disable_icache_tagmem_retention(void)
{
	REG_CLR_BIT(APB_CTRL_RETENTION_CTRL2_REG, APB_CTRL_RET_ICACHE_ENABLE);
}

void rtc_cntl_ll_disable_dcache_tagmem_retention(void)
{
	REG_CLR_BIT(APB_CTRL_RETENTION_CTRL3_REG, APB_CTRL_RET_DCACHE_ENABLE);
}

void rtc_cntl_ll_set_cpu_retention_link_addr(uint32_t link_addr)
{
	REG_SET_FIELD(APB_CTRL_RETENTION_CTRL_REG, APB_CTRL_RETENTION_CPU_LINK_ADDR, link_addr);
}

void rtc_cntl_ll_enable_cpu_retention_clock(void)
{
	REG_SET_BIT(RTC_CNTL_CLK_CONF_REG, RTC_CNTL_DIG_CLK8M_EN); /* Enable internal 20 MHz clock */
}

void rtc_cntl_ll_enable_cpu_retention(void)
{
	uint32_t target = REG_GET_FIELD(RTC_CNTL_RETENTION_CTRL_REG, RTC_CNTL_RETENTION_TARGET);

	REG_SET_FIELD(RTC_CNTL_RETENTION_CTRL_REG, RTC_CNTL_RETENTION_TARGET, (target | RTC_CNTL_LL_RETENTION_TARGET_CPU));
	/* Enable retention when cpu sleep enable */
	REG_SET_BIT(RTC_CNTL_RETENTION_CTRL_REG, RTC_CNTL_RETENTION_EN);
}

void rtc_cntl_ll_config_cpu_retention_timing(int wait, int clkoff_wait, int done_wait)
{
	REG_SET_FIELD(RTC_CNTL_RETENTION_CTRL_REG, RTC_CNTL_RETENTION_WAIT, wait);
	REG_SET_FIELD(RTC_CNTL_RETENTION_CTRL_REG, RTC_CNTL_RETENTION_CLKOFF_WAIT, clkoff_wait);
	REG_SET_FIELD(RTC_CNTL_RETENTION_CTRL_REG, RTC_CNTL_RETENTION_DONE_WAIT, done_wait);
}

void rtc_cntl_ll_disable_cpu_retention(void)
{
	REG_CLR_BIT(RTC_CNTL_RETENTION_CTRL_REG, RTC_CNTL_RETENTION_EN);
}

void rtc_cntl_ll_ulp_int_clear(void)
{
	REG_SET_BIT(RTC_CNTL_INT_CLR_REG, RTC_CNTL_ULP_CP_INT_CLR);
	REG_SET_BIT(RTC_CNTL_INT_CLR_REG, RTC_CNTL_COCPU_INT_CLR);
	REG_SET_BIT(RTC_CNTL_INT_CLR_REG, RTC_CNTL_COCPU_TRAP_INT_CLR);
}


void * rtc_cntl_hal_dma_link_init(void *elem, void *buff, int size, void *next)
{
	HAL_ASSERT(elem != NULL);
	HAL_ASSERT(buff != NULL);
	HAL_ASSERT(size >= RTC_CNTL_HAL_LINK_BUF_SIZE_MIN);

	lldesc_t *plink = (lldesc_t *)elem;

	plink->eof    = next ? 0 : 1;
	plink->owner  = DMA_DESCRIPTOR_BUFFER_OWNER_DMA;
	plink->size   = size >> 4;  /* in unit of 16 bytes */
	plink->length = size >> 4;
	plink->buf    = buff;
	plink->offset = 0;
	plink->sosf   = 0;
	STAILQ_NEXT(plink, qe) = next;
	return (void *)plink;
}

#if SOC_PM_SUPPORT_CPU_PD

#define DEFAULT_RETENTION_WAIT_CYCLES          (0x7f)
#define DEFAULT_RETENTION_CLKOFF_WAIT_CYCLES   (0xf)
#define DEFAULT_RETENTION_DONE_WAIT_CYCLES     (0x7)

void rtc_cntl_hal_enable_cpu_retention(void *addr)
{
	rtc_cntl_sleep_retent_t *retent = (rtc_cntl_sleep_retent_t *)addr;

	if (addr) {
		if (retent->cpu_pd_mem) {
			lldesc_t *plink = (lldesc_t *)retent->cpu_pd_mem;

			/* dma link buffer configure */
			rtc_cntl_link_buf_conf_t *pbuf = (rtc_cntl_link_buf_conf_t *)plink->buf;
			pbuf->cfg[0] = 0;
			pbuf->cfg[1] = 0;
			pbuf->cfg[2] = 0;
			pbuf->cfg[3] = 0xfffe0000;

			rtc_cntl_ll_set_cpu_retention_link_addr((uint32_t)plink);
			rtc_cntl_ll_config_cpu_retention_timing(
					DEFAULT_RETENTION_WAIT_CYCLES,
					DEFAULT_RETENTION_CLKOFF_WAIT_CYCLES,
					DEFAULT_RETENTION_DONE_WAIT_CYCLES
				);
			rtc_cntl_ll_enable_cpu_retention_clock();
			rtc_cntl_ll_enable_cpu_retention();
		}
	}
}

void IRAM_ATTR rtc_cntl_hal_disable_cpu_retention(void *addr)
{
	rtc_cntl_sleep_retent_t *retent = (rtc_cntl_sleep_retent_t *)addr;

	if (addr) {
		if (retent->cpu_pd_mem) {
			/* I/d-cache tagmem retention has not been included or not
			 * been enabled, after the system wakes up, all the contents
			 * of i/d-cache need to be invalidated. */
#if SOC_PM_SUPPORT_TAGMEM_PD
			if (!retent->tagmem.icache.enable) {
				Cache_Invalidate_ICache_All();
			}
			if (!retent->tagmem.dcache.enable) {
				Cache_Invalidate_DCache_All();
			}
#else
			Cache_Invalidate_ICache_All();
			Cache_Invalidate_DCache_All();
#endif // SOC_PM_SUPPORT_TAGMEM_PD
			rtc_cntl_ll_disable_cpu_retention();
		}
	}
}

#endif // SOC_PM_SUPPORT_CPU_PD

#if SOC_PM_SUPPORT_TAGMEM_PD

void rtc_cntl_hal_enable_tagmem_retention(void *addr)
{
	rtc_cntl_sleep_retent_t *retent = (rtc_cntl_sleep_retent_t *)addr;

	if (addr) {
		if (retent->tagmem.link_addr) {
			rtc_cntl_ll_set_tagmem_retention_link_addr((uint32_t)(retent->tagmem.link_addr));
			rtc_cntl_ll_enable_tagmem_retention();
			if (retent->tagmem.icache.enable) {
				rtc_cntl_ll_enable_icache_tagmem_retention(
						retent->tagmem.icache.start_point,
						retent->tagmem.icache.vld_size,
						retent->tagmem.icache.size
					);
			}
			if (retent->tagmem.dcache.enable) {
				rtc_cntl_ll_enable_dcache_tagmem_retention(
						retent->tagmem.dcache.start_point,
						retent->tagmem.dcache.vld_size,
						retent->tagmem.dcache.size
					);
			}
		}
	}
}

void IRAM_ATTR rtc_cntl_hal_disable_tagmem_retention(void *addr)
{
	rtc_cntl_sleep_retent_t *retent = (rtc_cntl_sleep_retent_t *)addr;

	if (addr) {
		if (retent->tagmem.link_addr) {
			rtc_cntl_ll_disable_tagmem_retention();
			if (retent->tagmem.icache.enable) {
				rtc_cntl_ll_disable_icache_tagmem_retention();
			}
			if (retent->tagmem.dcache.enable) {
				rtc_cntl_ll_disable_dcache_tagmem_retention();
			}
		}
	}
}

#endif // SOC_PM_SUPPORT_TAGMEM_PD
