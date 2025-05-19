#include <stdint.h>
#include <stdbool.h>

uint32_t efuse_ll_get_flash_crypt_cnt(void);
uint32_t efuse_ll_get_wdt_delay_sel(void);
uint32_t efuse_ll_get_flash_type(void);
uint32_t efuse_ll_get_mac0(void);
uint32_t efuse_ll_get_mac1(void);
bool efuse_ll_get_secure_boot_v2_en(void);
uint32_t efuse_ll_get_chip_wafer_version_major(void);
uint32_t efuse_ll_get_chip_wafer_version_minor(void);
bool efuse_ll_get_disable_wafer_version_major(void);
uint32_t efuse_ll_get_blk_version_major(void);
uint32_t efuse_ll_get_blk_version_minor(void);
bool efuse_ll_get_disable_blk_version_major(void);
uint32_t efuse_ll_get_chip_ver_pkg(void);
bool efuse_ll_get_read_cmd(void);
bool efuse_ll_get_pgm_cmd(void);
void efuse_ll_set_read_cmd(void);
void efuse_ll_set_pgm_cmd(uint32_t block);
void efuse_ll_set_conf_read_op_code(void);
void efuse_ll_set_conf_write_op_code(void);
void efuse_ll_set_pwr_off_num(uint16_t value);
