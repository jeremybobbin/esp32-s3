#pragma once

#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct esp_timer* esp_timer_handle_t;
typedef void (*esp_timer_cb_t)(void* arg);

typedef enum {
    ESP_TIMER_TASK,     //!< Callback is called from timer task
    ESP_TIMER_MAX,      //!< Count of the methods for dispatching timer callback
} esp_timer_dispatch_t;

typedef struct {
    esp_timer_cb_t callback;        //!< Function to call when timer expires
    void* arg;                      //!< Argument to pass to the callback
    esp_timer_dispatch_t dispatch_method;   //!< Call the callback from task or from ISR
    const char* name;               //!< Timer name, used in esp_timer_dump function
    bool skip_unhandled_events;     //!< Skip unhandled events for periodic timers
} esp_timer_create_args_t;

int esp_timer_early_init(void);
int esp_timer_init(void);
int esp_timer_deinit(void);
int esp_timer_create(const esp_timer_create_args_t* create_args, esp_timer_handle_t* out_handle);
int esp_timer_start_once(esp_timer_handle_t timer, uint64_t timeout_us);
int esp_timer_start_periodic(esp_timer_handle_t timer, uint64_t period);
int esp_timer_stop(esp_timer_handle_t timer);
int esp_timer_delete(esp_timer_handle_t timer);
int64_t esp_timer_get_time(void);
int64_t esp_timer_get_next_alarm(void);
int64_t esp_timer_get_next_alarm_for_wake_up(void);
int esp_timer_dump(FILE* stream);

bool esp_timer_is_active(esp_timer_handle_t timer);
