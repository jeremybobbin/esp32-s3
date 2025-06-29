#include <stdint.h>
#include <stdbool.h>
#include <sys/param.h>

#include "soc/efuse.h"

efuse_dev_t *EFUSE = (void*)0x60007000;

#define EFUSE_BLK_NUM  0x0000000F
#define EFUSE_BLK_NUM_M  ((EFUSE_BLK_NUM_V)<<(EFUSE_BLK_NUM_S))
#define EFUSE_BLK_NUM_V  0xF
#define EFUSE_BLK_NUM_S  2

#define EFUSE_PGM_CMD    1<<1

#define EFUSE_WRITE_OP_CODE 0x5a5a
#define EFUSE_READ_OP_CODE 0x5aa5

uint32_t efuse_ll_get_flash_crypt_cnt(void) {
	return EFUSE->rd_repeat_data1.reg_spi_boot_crypt_cnt;
}

uint32_t efuse_ll_get_wdt_delay_sel(void) {
	return EFUSE->rd_repeat_data1.reg_wdt_delay_sel;
}

uint32_t efuse_ll_get_flash_type(void) {
	return EFUSE->rd_repeat_data3.reg_flash_type;
}

uint32_t efuse_ll_get_mac0(void) {
	return EFUSE->rd_mac_spi_sys_0;
}

uint32_t efuse_ll_get_mac1(void) {
	return EFUSE->rd_mac_spi_sys_1.reg_mac_1;
}

bool efuse_ll_get_secure_boot_v2_en(void) {
	return EFUSE->rd_repeat_data2.reg_secure_boot_en;
}

uint32_t efuse_ll_get_chip_wafer_version_major(void) {
	return EFUSE->rd_mac_spi_sys_5.wafer_version_major;
}

uint32_t efuse_ll_get_chip_wafer_version_minor(void) {
	return (EFUSE->rd_mac_spi_sys_5.wafer_version_minor_high << 3) + EFUSE->rd_mac_spi_sys_3.wafer_version_minor_low;
}

bool efuse_ll_get_disable_wafer_version_major(void) {
	return EFUSE->rd_repeat_data4.disable_wafer_version_major;
}

uint32_t efuse_ll_get_blk_version_major(void) {
	return EFUSE->rd_sys_part1_data4.blk_version_major;
}

uint32_t efuse_ll_get_blk_version_minor(void) {
	return EFUSE->rd_mac_spi_sys_3.blk_version_minor;
}

bool efuse_ll_get_disable_blk_version_major(void) {
	return EFUSE->rd_repeat_data4.disable_blk_version_major;
}

uint32_t efuse_ll_get_chip_ver_pkg(void) {
	return 0;
}


bool efuse_ll_get_read_cmd(void) {
	return EFUSE->cmd.read_cmd;
}

bool efuse_ll_get_pgm_cmd(void) {
	return EFUSE->cmd.pgm_cmd;
}

void efuse_ll_set_read_cmd(void) {
	EFUSE->cmd.read_cmd = 1;
}

void efuse_ll_set_pgm_cmd(uint32_t block) {
	EFUSE->cmd.val = ((block << EFUSE_BLK_NUM_S) & EFUSE_BLK_NUM_M) | EFUSE_PGM_CMD;
}

void efuse_ll_set_conf_read_op_code(void) {
	EFUSE->conf.op_code = EFUSE_READ_OP_CODE;
}

void efuse_ll_set_conf_write_op_code(void) {
	EFUSE->conf.op_code = EFUSE_WRITE_OP_CODE;
}

void efuse_ll_set_pwr_off_num(uint16_t value) {
	EFUSE->wr_tim_conf2.pwr_off_num = value;
}

#define ESP_EFUSE_BLOCK_ERROR_BITS(error_reg, block) ((error_reg) & (0x0F << (4 * (block))))


//The wafer_major and MSB of wafer_minor fields was allocated to other purposes when block version is v1.1.
//Luckily only chip v0.0 have this kind of block version and efuse usage.
//This workaround fixes the issue.
bool is_eco0(uint32_t minor_raw)
{
	return ((minor_raw & 0x7) == 0 &&
			efuse_ll_get_blk_version_major() == 1 && efuse_ll_get_blk_version_minor() == 1);
}

uint32_t efuse_hal_get_major_chip_version(void)
{
	uint32_t minor_raw = efuse_ll_get_chip_wafer_version_minor();

	if (is_eco0(minor_raw)) {
		return 0;
	}
	return efuse_ll_get_chip_wafer_version_major();
}

uint32_t efuse_hal_get_minor_chip_version(void)
{
	uint32_t minor_raw = efuse_ll_get_chip_wafer_version_minor();

	if (is_eco0(minor_raw)) {
		return 0;
	}
	return minor_raw;
}
