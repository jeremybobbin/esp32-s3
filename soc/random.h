#include <stdint.h>
#include <stdlib.h>

#define APB_CYCLE_WAIT_NUM (1778)
#define WDEV_RND_REG 0x6003507C

uint32_t esp_random(void);
void esp_fill_random(void *buf, size_t len);

