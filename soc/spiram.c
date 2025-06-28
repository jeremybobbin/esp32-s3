#include <stdlib.h>
#include <errno.h>

#include "soc/spiram.h"
#include "soc/gpio.h"
#include "soc/spi.h"
#include "rom/cache.h"
#include "heap/soc_memory_layout.h"
#include "heap/esp_heap_caps_init.h"

#define MMU_ACCESS_SPIRAM (1<<15)
#define MIN(a, b) (a) > (b) ? (b) : (a)

//#define PSRAM_MODE PSRAM_VADDR_MODE_NORMAL

static const char *TAG = "spiram";
static bool s_spiram_inited = false;
static psram_size_t s_psram_size;

#if CONFIG_SPIRAM_SPEED_40M
#define PSRAM_SPEED PSRAM_CACHE_S40M
#else  //#if CONFIG_SPIRAM_SPEED_80M
#define PSRAM_SPEED PSRAM_CACHE_S80M
#endif

#define CONFIG_SPIRAM_SIZE -1

void spi_flash_set_vendor_required_regs(void)
{
#if CONFIG_ESPTOOLPY_OCT_FLASH
    //Flash chip requires MSPI specifically, call this function to set them
    esp_opiflash_set_required_regs();
    SET_PERI_REG_BITS(SPI_MEM_CACHE_FCTRL_REG(1), SPI_MEM_CACHE_USR_CMD_4BYTE_V, 1, SPI_MEM_CACHE_USR_CMD_4BYTE_S);
#else
    // Set back MSPI registers after Octal PSRAM initialization.
    SET_PERI_REG_BITS(SPI_MEM_CACHE_FCTRL_REG(1), SPI_MEM_CACHE_USR_CMD_4BYTE_V, 0, SPI_MEM_CACHE_USR_CMD_4BYTE_S);
#endif // CONFIG_ESPTOOLPY_OCT_FLASH
}

void spi_flash_set_rom_required_regs(void) {
	CLEAR_PERI_REG_MASK(SPI_MEM_DDR_REG(1), SPI_MEM_SPI_FMEM_VAR_DUMMY);
}


static void psram_set_cs_timing(void) {
	//SPI0/1 share the cs_hold / cs_setup, cd_hold_time / cd_setup_time, cs_hold_delay registers for PSRAM, so we only need to set SPI0 related registers here
	SET_PERI_REG_MASK(SPI_MEM_SPI_SMEM_AC_REG(0), SPI_MEM_SPI_SMEM_CS_HOLD_M | SPI_MEM_SPI_SMEM_CS_SETUP_M);
	SET_PERI_REG_BITS(SPI_MEM_SPI_SMEM_AC_REG(0), SPI_MEM_SPI_SMEM_CS_HOLD_TIME_V, OCT_PSRAM_CS_HOLD_TIME, SPI_MEM_SPI_SMEM_CS_HOLD_TIME_S);
	SET_PERI_REG_BITS(SPI_MEM_SPI_SMEM_AC_REG(0), SPI_MEM_SPI_SMEM_CS_SETUP_TIME_V, OCT_PSRAM_CS_SETUP_TIME, SPI_MEM_SPI_SMEM_CS_SETUP_TIME_S);
	//CS1 high time
	SET_PERI_REG_BITS(SPI_MEM_SPI_SMEM_AC_REG(0), SPI_MEM_SPI_SMEM_CS_HOLD_DELAY_V, OCT_PSRAM_CS_HOLD_DELAY, SPI_MEM_SPI_SMEM_CS_HOLD_DELAY_S);
}

static void s_init_psram_pins(void) {
	//Set cs1 pin function
	PIN_FUNC_SELECT(GPIO_PIN_MUX_REG[OCT_PSRAM_CS1_IO],  FUNC_SPICS1_SPICS1);
	//Set mspi cs1 drive strength
	PIN_SET_DRV(GPIO_PIN_MUX_REG[OCT_PSRAM_CS1_IO], 3);
	//Set psram clock pin drive strength
	REG_SET_FIELD(SPI_MEM_DATE_REG(0), SPI_MEM_SPI_SMEM_SPICLK_FUN_DRV, 3);
}

static void s_init_psram_mode_reg(int spi_num, opi_psram_mode_reg_t *mode_reg_config) {
	esp_rom_spiflash_read_mode_t mode = ESP_ROM_SPIFLASH_OPI_DTR_MODE;
	int cmd_len = 16;
	uint32_t addr = 0x0;
	int addr_bit_len = 32;
	int dummy = OCT_PSRAM_RD_DUMMY_BITLEN;
	opi_psram_mode_reg_t mode_reg = {0};
	int data_bit_len = 16;

	//read
	esp_rom_opiflash_exec_cmd(spi_num, mode,
							 OPI_PSRAM_REG_READ, cmd_len,
							 addr, addr_bit_len,
							 dummy,
							 NULL, 0,
							 &mode_reg.mr0.val, data_bit_len,
							 1<<(1),
							 false);
	//modify
	mode_reg.mr0.lt = mode_reg_config->mr0.lt;
	mode_reg.mr0.read_latency = mode_reg_config->mr0.read_latency;
	mode_reg.mr0.drive_str = mode_reg_config->mr0.drive_str;

	//write
	esp_rom_opiflash_exec_cmd(spi_num, mode,
							 OPI_PSRAM_REG_WRITE, cmd_len,
							 addr, addr_bit_len,
							 0,
							 &mode_reg.mr0.val, 16,
							 NULL, 0,
							 1<<(1),
							 false);
}

static void s_get_psram_mode_reg(int spi_num, opi_psram_mode_reg_t *out_reg) {
	esp_rom_spiflash_read_mode_t mode = ESP_ROM_SPIFLASH_OPI_DTR_MODE;
	int cmd_len = 16;
	int addr_bit_len = 32;
	int dummy = OCT_PSRAM_RD_DUMMY_BITLEN;
	int data_bit_len = 16;

	//Read MR0~1 register
	esp_rom_opiflash_exec_cmd(spi_num, mode,
							 OPI_PSRAM_REG_READ, cmd_len,
							 0x0, addr_bit_len,
							 dummy,
							 NULL, 0,
							 &out_reg->mr0.val, data_bit_len,
							 1<<(1),
							 false);
	//Read MR2~3 register
	esp_rom_opiflash_exec_cmd(spi_num, mode,
							OPI_PSRAM_REG_READ, cmd_len,
							0x2, addr_bit_len,
							dummy,
							NULL, 0,
							&out_reg->mr2.val, data_bit_len,
							1<<(1),
							false);
	data_bit_len = 8;
	//Read MR4 register
	esp_rom_opiflash_exec_cmd(spi_num, mode,
							OPI_PSRAM_REG_READ, cmd_len,
							0x4, addr_bit_len,
							dummy,
							NULL, 0,
							&out_reg->mr4.val, data_bit_len,
							1<<(1),
							false);
	//Read MR8 register
	esp_rom_opiflash_exec_cmd(spi_num, mode,
							OPI_PSRAM_REG_READ, cmd_len,
							0x8, addr_bit_len,
							dummy,
							NULL, 0,
							&out_reg->mr8.val, data_bit_len,
							1<<(1),
							false);
}

static void s_print_psram_info(opi_psram_mode_reg_t *reg_val) {
/*
	ESP_EARLY_LOGI(TAG, "vendor id : 0x%02x (%s)", reg_val->mr1.vendor_id, reg_val->mr1.vendor_id == 0x0d ? "AP" : "UNKNOWN");
	ESP_EARLY_LOGI(TAG, "dev id    : 0x%02x (generation %d)", reg_val->mr2.dev_id, reg_val->mr2.dev_id + 1);
	ESP_EARLY_LOGI(TAG, "density   : 0x%02x (%d Mbit)", reg_val->mr2.density, reg_val->mr2.density == 0x1 ? 32 :
																			  reg_val->mr2.density == 0X3 ? 64 :
																			  reg_val->mr2.density == 0x5 ? 128 :
																			  reg_val->mr2.density == 0x7 ? 256 : 0);
	ESP_EARLY_LOGI(TAG, "good-die  : 0x%02x (%s)", reg_val->mr2.gb, reg_val->mr2.gb == 1 ? "Pass" : "Fail");
	ESP_EARLY_LOGI(TAG, "Latency   : 0x%02x (%s)", reg_val->mr0.lt, reg_val->mr0.lt == 1 ? "Fixed" : "Variable");
	ESP_EARLY_LOGI(TAG, "VCC       : 0x%02x (%s)", reg_val->mr3.vcc, reg_val->mr3.vcc == 1 ? "3V" : "1.8V");
	ESP_EARLY_LOGI(TAG, "SRF       : 0x%02x (%s Refresh)", reg_val->mr3.srf, reg_val->mr3.srf == 0x1 ? "Fast" : "Slow");
	ESP_EARLY_LOGI(TAG, "BurstType : 0x%02x (%s Wrap)", reg_val->mr8.bt, reg_val->mr8.bt == 1 && reg_val->mr8.bl != 3 ? "Hybrid" : "");
	ESP_EARLY_LOGI(TAG, "BurstLen  : 0x%02x (%d Byte)", reg_val->mr8.bl, reg_val->mr8.bl == 0x00 ? 16 :
																		 reg_val->mr8.bl == 0x01 ? 32 :
																		 reg_val->mr8.bl == 0x10 ? 64 : 1024);
	ESP_EARLY_LOGI(TAG, "Readlatency  : 0x%02x (%d cycles@%s)", reg_val->mr0.read_latency,  reg_val->mr0.read_latency * 2 + 6,
																reg_val->mr0.lt == 1 ? "Fixed" : "Variable");
	ESP_EARLY_LOGI(TAG, "DriveStrength: 0x%02x (1/%d)", reg_val->mr0.drive_str, reg_val->mr0.drive_str == 0x00 ? 1 :
																				reg_val->mr0.drive_str == 0x01 ? 2 :
																				reg_val->mr0.drive_str == 0x02 ? 4 : 8);
																				*/
}


static void s_config_psram_spi_phases(void) {
	//Config Write CMD phase for SPI0 to access PSRAM
	SET_PERI_REG_MASK(SPI_MEM_CACHE_SCTRL_REG(0), SPI_MEM_CACHE_SRAM_USR_WCMD_M);
	SET_PERI_REG_BITS(SPI_MEM_SRAM_DWR_CMD_REG(0), SPI_MEM_CACHE_SRAM_USR_WR_CMD_BITLEN, OCT_PSRAM_WR_CMD_BITLEN - 1, SPI_MEM_CACHE_SRAM_USR_WR_CMD_BITLEN_S);
	SET_PERI_REG_BITS(SPI_MEM_SRAM_DWR_CMD_REG(0), SPI_MEM_CACHE_SRAM_USR_WR_CMD_VALUE, OPI_PSRAM_SYNC_WRITE, SPI_MEM_CACHE_SRAM_USR_WR_CMD_VALUE_S);

	//Config Read CMD phase for SPI0 to access PSRAM
	SET_PERI_REG_MASK(SPI_MEM_CACHE_SCTRL_REG(0), SPI_MEM_CACHE_SRAM_USR_RCMD_M);
	SET_PERI_REG_BITS(SPI_MEM_SRAM_DRD_CMD_REG(0), SPI_MEM_CACHE_SRAM_USR_RD_CMD_BITLEN_V, OCT_PSRAM_RD_CMD_BITLEN - 1, SPI_MEM_CACHE_SRAM_USR_RD_CMD_BITLEN_S);
	SET_PERI_REG_BITS(SPI_MEM_SRAM_DRD_CMD_REG(0), SPI_MEM_CACHE_SRAM_USR_RD_CMD_VALUE_V, OPI_PSRAM_SYNC_READ, SPI_MEM_CACHE_SRAM_USR_RD_CMD_VALUE_S);

	//Config ADDR phase
	SET_PERI_REG_BITS(SPI_MEM_CACHE_SCTRL_REG(0), SPI_MEM_SRAM_ADDR_BITLEN_V, OCT_PSRAM_ADDR_BITLEN - 1, SPI_MEM_SRAM_ADDR_BITLEN_S);
	SET_PERI_REG_MASK(SPI_MEM_CACHE_SCTRL_REG(0), SPI_MEM_CACHE_USR_SCMD_4BYTE_M);

	//Config RD/WR Dummy phase
	SET_PERI_REG_MASK(SPI_MEM_CACHE_SCTRL_REG(0), SPI_MEM_USR_RD_SRAM_DUMMY_M | SPI_MEM_USR_WR_SRAM_DUMMY_M);
	SET_PERI_REG_BITS(SPI_MEM_CACHE_SCTRL_REG(0), SPI_MEM_SRAM_RDUMMY_CYCLELEN_V, OCT_PSRAM_RD_DUMMY_BITLEN - 1, SPI_MEM_SRAM_RDUMMY_CYCLELEN_S);
	SET_PERI_REG_MASK(SPI_MEM_SPI_SMEM_DDR_REG(0), SPI_MEM_SPI_SMEM_VAR_DUMMY_M);
	SET_PERI_REG_BITS(SPI_MEM_CACHE_SCTRL_REG(0), SPI_MEM_SRAM_WDUMMY_CYCLELEN_V, OCT_PSRAM_WR_DUMMY_BITLEN - 1, SPI_MEM_SRAM_WDUMMY_CYCLELEN_S);

	CLEAR_PERI_REG_MASK(SPI_MEM_SPI_SMEM_DDR_REG(0), SPI_MEM_SPI_SMEM_DDR_WDAT_SWP_M | SPI_MEM_SPI_SMEM_DDR_RDAT_SWP_M);
	SET_PERI_REG_MASK(SPI_MEM_SPI_SMEM_DDR_REG(0), SPI_MEM_SPI_SMEM_DDR_EN_M);

	SET_PERI_REG_MASK(SPI_MEM_SRAM_CMD_REG(0), SPI_MEM_SDUMMY_OUT_M | SPI_MEM_SCMD_OCT_M | SPI_MEM_SADDR_OCT_M | SPI_MEM_SDOUT_OCT_M | SPI_MEM_SDIN_OCT_M);
	SET_PERI_REG_MASK(SPI_MEM_CACHE_SCTRL_REG(0), SPI_MEM_SRAM_OCT_M);

	Cache_Resume_DCache(0);
}


int psram_enable(psram_cache_mode_t mode, psram_vaddr_mode_t vaddrmode) {
	s_init_psram_pins();
	psram_set_cs_timing();

	//enter MSPI slow mode to init PSRAM device registers
	spi_timing_enter_mspi_low_speed_mode(true);

	//set to variable dummy mode
	SET_PERI_REG_MASK(SPI_MEM_DDR_REG(1), SPI_MEM_SPI_FMEM_VAR_DUMMY);
	esp_rom_spi_set_dtr_swap_mode(1, false, false);

	//Set PSRAM read latency and drive strength
	static opi_psram_mode_reg_t mode_reg = {0};
	mode_reg.mr0.lt = 1;
	mode_reg.mr0.read_latency = 2;
	mode_reg.mr0.drive_str = 0;
	s_init_psram_mode_reg(1, &mode_reg);
	//Print PSRAM info
	s_get_psram_mode_reg(1, &mode_reg);
	s_print_psram_info(&mode_reg);
	s_psram_size = mode_reg.mr2.density == 0x1 ? PSRAM_SIZE_32MBITS  :
				   mode_reg.mr2.density == 0X3 ? PSRAM_SIZE_64MBITS  :
				   mode_reg.mr2.density == 0x5 ? PSRAM_SIZE_128MBITS :
				   mode_reg.mr2.density == 0x7 ? PSRAM_SIZE_256MBITS : 0;

	//Do PSRAM timing tuning, we use SPI1 to do the tuning, and set the SPI0 PSRAM timing related registers accordingly
	spi_timing_psram_tuning();
	//Back to the high speed mode. Flash/PSRAM clocks are set to the clock that user selected. SPI0/1 registers are all set correctly
	spi_timing_enter_mspi_high_speed_mode(true);

	/**
	 * Tuning may change SPI1 regs, whereas legacy spi_flash APIs rely on these regs.
	 * This function is to restore SPI1 init state.
	 */
	spi_flash_set_rom_required_regs();
	//Flash chip requires MSPI specifically, call this function to set them
	spi_flash_set_vendor_required_regs();

	s_config_psram_spi_phases();
	return 0;
}

psram_size_t psram_get_size()
{
	return s_psram_size;
}

bool esp_spiram_test(void) {
	size_t spiram_size = esp_spiram_get_size();
	volatile int *spiram = (volatile int *)(SOC_EXTRAM_DATA_HIGH - spiram_size);
	size_t p;
	size_t s = spiram_size;
	int errct = 0;
	int initial_err = -1;

	if (SOC_EXTRAM_DATA_SIZE < spiram_size) {
		spiram = (volatile int *)SOC_EXTRAM_DATA_LOW;
		s = SOC_EXTRAM_DATA_HIGH - SOC_EXTRAM_DATA_LOW;
	}
	for (p = 0; p < (s / sizeof(int)); p += 8) {
		spiram[p] = p ^ 0xAAAAAAAA;
	}
	for (p = 0; p < (s / sizeof(int)); p += 8) {
		if (spiram[p] != (p ^ 0xAAAAAAAA)) {
			errct++;
			if (errct == 1) {
				initial_err = p * 4;
			}
			if (errct < 4) {
			}
		}
	}
	if (errct) {
		return false;
	} else {
		return true;
	}
}

void esp_spiram_init_cache(void)
{
	size_t spiram_size = esp_spiram_get_size();
	Cache_Suspend_DCache();
	if ((SOC_EXTRAM_DATA_HIGH - SOC_EXTRAM_DATA_LOW) >= spiram_size) {
		Cache_Dbus_MMU_Set(MMU_ACCESS_SPIRAM, SOC_EXTRAM_DATA_HIGH - spiram_size, 0, 64, spiram_size >> 16, 0);
	} else {
		Cache_Dbus_MMU_Set(MMU_ACCESS_SPIRAM, SOC_EXTRAM_DATA_HIGH - spiram_size, 0, 64, (SOC_EXTRAM_DATA_HIGH - SOC_EXTRAM_DATA_LOW) >> 16, 0);
	}
	REG_CLR_BIT(EXTMEM_DCACHE_CTRL1_REG, EXTMEM_DCACHE_SHUT_CORE0_BUS);
	REG_CLR_BIT(EXTMEM_DCACHE_CTRL1_REG, EXTMEM_DCACHE_SHUT_CORE1_BUS);
	Cache_Resume_DCache(0);
}

static uint32_t pages_for_flash = 0;
static uint32_t instruction_in_spiram = 0;
static uint32_t rodata_in_spiram = 0;

#if CONFIG_SPIRAM_FETCH_INSTRUCTIONS
static int instr_flash2spiram_offs = 0;
static uint32_t instr_start_page = 0;
static uint32_t instr_end_page = 0;
#endif

#if CONFIG_SPIRAM_RODATA
static int rodata_flash2spiram_offs = 0;
static uint32_t rodata_start_page = 0;
static uint32_t rodata_end_page = 0;
#endif

#if CONFIG_SPIRAM_FETCH_INSTRUCTIONS || CONFIG_SPIRAM_RODATA
static uint32_t page0_mapped = 0;
static uint32_t page0_page = INVALID_PHY_PAGE;
#endif

uint32_t esp_spiram_instruction_access_enabled(void)
{
	return instruction_in_spiram;
}

uint32_t esp_spiram_rodata_access_enabled(void)
{
	return rodata_in_spiram;
}

#if CONFIG_SPIRAM_FETCH_INSTRUCTIONS
int esp_spiram_enable_instruction_access(void)
{
	size_t spiram_size = esp_spiram_get_size();
	uint32_t pages_in_flash = 0;
	pages_in_flash += Cache_Count_Flash_Pages(CACHE_IBUS, &page0_mapped);
	if ((pages_in_flash + pages_for_flash) > (spiram_size >> 16)) {
		return ENOMEM;
	}
	uint32_t mmu_value = *(volatile uint32_t *)(DR_REG_MMU_TABLE + CACHE_IROM_MMU_START);
	instr_flash2spiram_offs = mmu_value - pages_for_flash;
	pages_for_flash = Cache_Flash_To_SPIRAM_Copy(CACHE_IBUS, IRAM0_CACHE_ADDRESS_LOW, pages_for_flash, &page0_page);
	instruction_in_spiram = 1;
	return 0;
}
#endif

#if CONFIG_SPIRAM_RODATA
int esp_spiram_enable_rodata_access(void)
{
	size_t spiram_size = esp_spiram_get_size();
	uint32_t pages_in_flash = 0;
	pages_in_flash += Cache_Count_Flash_Pages(CACHE_DBUS, &page0_mapped);

	if ((pages_in_flash + pages_for_flash) > (spiram_size >> 16)) {
		return ENOMEM;
	}
	uint32_t mmu_value = *(volatile uint32_t *)(DR_REG_MMU_TABLE + CACHE_DROM_MMU_START);
	rodata_flash2spiram_offs = mmu_value - pages_for_flash;
	pages_for_flash = Cache_Flash_To_SPIRAM_Copy(CACHE_DBUS, DRAM0_CACHE_ADDRESS_LOW, pages_for_flash, &page0_page);
	rodata_in_spiram = 1;
	return 0;
}
#endif

#if CONFIG_SPIRAM_FETCH_INSTRUCTIONS
void instruction_flash_page_info_init(void)
{
	uint32_t instr_page_cnt = ((uint32_t)&_instruction_reserved_end - SOC_IROM_LOW + MMU_PAGE_SIZE - 1) / MMU_PAGE_SIZE;

	instr_start_page = *(volatile uint32_t *)(DR_REG_MMU_TABLE + CACHE_IROM_MMU_START);
	instr_start_page &= MMU_ADDRESS_MASK;
	instr_end_page = instr_start_page + instr_page_cnt - 1;
}

uint32_t instruction_flash_start_page_get(void)
{
	return instr_start_page;
}

uint32_t instruction_flash_end_page_get(void)
{
	return instr_end_page;
}

int instruction_flash2spiram_offset(void)
{
	return instr_flash2spiram_offs;
}
#endif

#if CONFIG_SPIRAM_RODATA
void rodata_flash_page_info_init(void)
{
	uint32_t rodata_page_cnt = ((uint32_t)&_rodata_reserved_end - ((uint32_t)&_rodata_reserved_start & ~ (MMU_PAGE_SIZE - 1)) + MMU_PAGE_SIZE - 1) / MMU_PAGE_SIZE;

	rodata_start_page = *(volatile uint32_t *)(DR_REG_MMU_TABLE + CACHE_DROM_MMU_START);
	rodata_start_page &= MMU_ADDRESS_MASK;
	rodata_end_page = rodata_start_page + rodata_page_cnt - 1;
}

uint32_t rodata_flash_start_page_get(void)
{
	return rodata_start_page;
}

uint32_t rodata_flash_end_page_get(void)
{
	return rodata_end_page;
}

int rodata_flash2spiram_offset(void)
{
	return rodata_flash2spiram_offs;
}
#endif

int esp_spiram_init(void)
{
	int r;
	r = psram_enable(PSRAM_SPEED, PSRAM_MODE);
	if (r != 0) {
		return r;
	}
	s_spiram_inited = true;
#if (CONFIG_SPIRAM_SIZE != -1)
	if (esp_spiram_get_size() != CONFIG_SPIRAM_SIZE) {
		return EINVAL;
	}
#endif

	return 0;
}


int esp_spiram_add_to_heapalloc(void)
{
	size_t spiram_size = esp_spiram_get_size();
	uint32_t size_for_flash = (pages_for_flash << 16);

	return heap_caps_add_region((intptr_t)SOC_EXTRAM_DATA_HIGH - spiram_size + size_for_flash, (intptr_t)SOC_EXTRAM_DATA_HIGH - 1);
}

int esp_spiram_reserve_dma_pool(size_t size) {
	if (size == 0) {
		return 0;
	}

	while (size > 0) {
		size_t next_size = heap_caps_get_largest_free_block(MALLOC_CAP_DMA|MALLOC_CAP_INTERNAL);
		next_size = MIN(next_size, size);

		uint8_t *dma_heap = heap_caps_malloc(next_size, MALLOC_CAP_DMA|MALLOC_CAP_INTERNAL);
		if (!dma_heap || next_size == 0) {
			return ENOMEM;
		}

		uint32_t caps[] = { 0, MALLOC_CAP_DMA|MALLOC_CAP_INTERNAL, MALLOC_CAP_8BIT|MALLOC_CAP_32BIT };
		int e = heap_caps_add_region_with_caps(caps, (intptr_t) dma_heap, (intptr_t) dma_heap+next_size-1);
		if (e != 0) {
			return e;
		}
		size -= next_size;
	}
	return 0;
}

size_t esp_spiram_get_size(void)
{
	if (!s_spiram_inited) {
		abort();
	}

	psram_size_t size = psram_get_size();
	if (size == PSRAM_SIZE_16MBITS) {
		return 2 * 1024 * 1024;
	}
	if (size == PSRAM_SIZE_32MBITS) {
		return 4 * 1024 * 1024;
	}
	if (size == PSRAM_SIZE_64MBITS) {
		return 8 * 1024 * 1024;
	}
	if (size == PSRAM_SIZE_128MBITS) {
		return 16 * 1024 * 1024;
	}
	if (size == PSRAM_SIZE_256MBITS) {
		return 32 * 1024 * 1024;
	}
	return CONFIG_SPIRAM_SIZE;
}


void esp_spiram_writeback_cache(void)
{
	extern void Cache_WriteBack_All(void);
	Cache_WriteBack_All();
}


bool esp_spiram_is_initialized(void)
{
	return s_spiram_inited;
}

uint8_t psram_get_cs_io(void) {
	return OCT_PSRAM_CS1_IO;
}

uint8_t esp_spiram_get_cs_io(void) {
	return psram_get_cs_io();
}

#define SPI_TIMING_CORE_CLOCK_MHZ 80 // TODO

spi_timing_config_core_clock_t spi_timing_config_get_core_clock(void) {
	switch (SPI_TIMING_CORE_CLOCK_MHZ) {
	case 80:
		return SPI_TIMING_CONFIG_CORE_CLOCK_80M;
	case 120:
		return SPI_TIMING_CONFIG_CORE_CLOCK_120M;
	case 160:
		return SPI_TIMING_CONFIG_CORE_CLOCK_160M;
	case 240:
		return SPI_TIMING_CONFIG_CORE_CLOCK_240M;
	default:
		abort();
	}
}


