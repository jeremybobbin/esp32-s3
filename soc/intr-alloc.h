typedef void (*intr_handler_t)(void *arg);
typedef struct intr_handle_data_t intr_handle_data_t;
typedef intr_handle_data_t *intr_handle_t ;

int esp_intr_alloc(int source, int flags, intr_handler_t handler, void *arg, intr_handle_t *ret_handle);
