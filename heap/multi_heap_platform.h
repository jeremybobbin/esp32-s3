#include "freertos/FreeRTOS.h"

#include <assert.h>

typedef portMUX_TYPE multi_heap_lock_t;

#define MULTI_HEAP_LOCK(PLOCK) do {                         \
        if((PLOCK) != NULL) {                               \
            portENTER_CRITICAL((PLOCK));                    \
        }                                                   \
    } while(0)


#define MULTI_HEAP_UNLOCK(PLOCK) do {                       \
        if ((PLOCK) != NULL) {                              \
            portEXIT_CRITICAL((PLOCK));                     \
        }                                                   \
    } while(0)

#define MULTI_HEAP_LOCK_INIT(PLOCK) do {                    \
        portMUX_INITIALIZE((PLOCK));                        \
    } while(0)

#define MULTI_HEAP_LOCK_STATIC_INITIALIZER     portMUX_INITIALIZER_UNLOCKED

#define MULTI_HEAP_PRINTF(...) // esp_rom_printf
#define MULTI_HEAP_STDERR_PRINTF(MSG, ...) esp_rom_printf(MSG, __VA_ARGS__)

#ifdef CONFIG_HEAP_TASK_TRACKING
#include <freertos/task.h>
#define MULTI_HEAP_BLOCK_OWNER TaskHandle_t task;
#define MULTI_HEAP_SET_BLOCK_OWNER(HEAD) (HEAD)->task = xTaskGetCurrentTaskHandle()
#define MULTI_HEAP_GET_BLOCK_OWNER(HEAD) ((HEAD)->task)
#else
#define MULTI_HEAP_BLOCK_OWNER
#define MULTI_HEAP_SET_BLOCK_OWNER(HEAD)
#define MULTI_HEAP_GET_BLOCK_OWNER(HEAD) (NULL)
#endif
