

//We should mark the interrupt for the timer used by FreeRTOS as reserved. The specific timer
//is selectable using menuconfig; we use these cpp bits to convert that into something we can use in
//the table below.
#if CONFIG_FREERTOS_CORETIMER_0
#define INT6RES INTDESC_RESVD
#else
#define INT6RES INTDESC_SPECIAL
#endif

#if CONFIG_FREERTOS_CORETIMER_1
#define INT15RES INTDESC_RESVD
#else
#define INT15RES INTDESC_SPECIAL
#endif

#define SOC_CPU_CORES_NUM               2

typedef enum {
	ESP_CPU_INTR_TYPE_LEVEL = 0,
	ESP_CPU_INTR_TYPE_EDGE,
	ESP_CPU_INTR_TYPE_NA,
} esp_cpu_intr_type_t;

typedef enum {
	INTDESC_NORMAL = 0,
	INTDESC_RESVD,
	INTDESC_SPECIAL,
} int_desc_flag_t;

typedef enum {
	INTTP_LEVEL = ESP_CPU_INTR_TYPE_LEVEL,
	INTTP_EDGE = ESP_CPU_INTR_TYPE_EDGE,
	INTTP_NA = ESP_CPU_INTR_TYPE_NA,
} int_type_t;

typedef struct {
	int level;
	int_type_t type;
	int_desc_flag_t cpuflags[SOC_CPU_CORES_NUM];
} int_desc_t;

typedef void (*interrupt_handler_t)(void *arg);


//This is basically a software-readable version of the interrupt usage table in include/soc/soc.h
const static int_desc_t interrupt_descriptor_table [32]={
	{ 1, INTTP_LEVEL, {INTDESC_RESVD,  INTDESC_RESVD } }, //0
	{ 1, INTTP_LEVEL, {INTDESC_RESVD,  INTDESC_RESVD } }, //1
	{ 1, INTTP_LEVEL, {INTDESC_NORMAL, INTDESC_NORMAL} }, //2
	{ 1, INTTP_LEVEL, {INTDESC_NORMAL, INTDESC_NORMAL} }, //3
	{ 1, INTTP_LEVEL, {INTDESC_RESVD,  INTDESC_NORMAL} }, //4
	{ 1, INTTP_LEVEL, {INTDESC_RESVD,  INTDESC_RESVD } }, //5
	{ 1, INTTP_NA,    {INT6RES,        INT6RES       } }, //6
	{ 1, INTTP_NA,    {INTDESC_SPECIAL,INTDESC_SPECIAL}}, //7
	{ 1, INTTP_LEVEL, {INTDESC_RESVD,  INTDESC_RESVD } }, //8
	{ 1, INTTP_LEVEL, {INTDESC_NORMAL, INTDESC_NORMAL} }, //9
	{ 1, INTTP_EDGE , {INTDESC_NORMAL, INTDESC_NORMAL} }, //10
	{ 3, INTTP_NA,    {INTDESC_SPECIAL,INTDESC_SPECIAL}}, //11
	{ 1, INTTP_LEVEL, {INTDESC_NORMAL, INTDESC_NORMAL} }, //12
	{ 1, INTTP_LEVEL, {INTDESC_NORMAL, INTDESC_NORMAL} }, //13
	{ 7, INTTP_LEVEL, {INTDESC_RESVD,  INTDESC_RESVD } }, //14, NMI
	{ 3, INTTP_NA,    {INT15RES,       INT15RES      } }, //15
	{ 5, INTTP_NA,    {INTDESC_SPECIAL,INTDESC_SPECIAL} }, //16
	{ 1, INTTP_LEVEL, {INTDESC_NORMAL, INTDESC_NORMAL} }, //17
	{ 1, INTTP_LEVEL, {INTDESC_NORMAL, INTDESC_NORMAL} }, //18
	{ 2, INTTP_LEVEL, {INTDESC_NORMAL, INTDESC_NORMAL} }, //19
	{ 2, INTTP_LEVEL, {INTDESC_NORMAL, INTDESC_NORMAL} }, //20
	{ 2, INTTP_LEVEL, {INTDESC_NORMAL, INTDESC_NORMAL} }, //21
	{ 3, INTTP_EDGE,  {INTDESC_RESVD,  INTDESC_NORMAL} }, //22
	{ 3, INTTP_LEVEL, {INTDESC_NORMAL, INTDESC_NORMAL} }, //23
	{ 4, INTTP_LEVEL, {INTDESC_RESVD,  INTDESC_NORMAL} }, //24
	{ 4, INTTP_LEVEL, {INTDESC_RESVD,  INTDESC_RESVD } }, //25
	{ 5, INTTP_LEVEL, {INTDESC_NORMAL, INTDESC_RESVD } }, //26
	{ 3, INTTP_LEVEL, {INTDESC_RESVD,  INTDESC_RESVD } }, //27
	{ 4, INTTP_EDGE,  {INTDESC_NORMAL, INTDESC_NORMAL} }, //28
	{ 3, INTTP_NA,    {INTDESC_SPECIAL,INTDESC_SPECIAL}}, //29
	{ 4, INTTP_EDGE,  {INTDESC_RESVD,  INTDESC_RESVD } }, //30
	{ 5, INTTP_LEVEL, {INTDESC_RESVD,  INTDESC_RESVD } }, //31
};

const int_desc_t *interrupt_controller_hal_desc_table(void)
{
	return interrupt_descriptor_table;
}
