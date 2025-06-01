#include "freertos/portmacro.h"

#define portCHAR                    int8_t
#define portFLOAT                   float
#define portDOUBLE                  double
#define portLONG                    int32_t
#define portSHORT                   int16_t
#define portSTACK_TYPE              uint8_t
#define portBASE_TYPE               int

typedef portSTACK_TYPE              StackType_t;
typedef portBASE_TYPE               BaseType_t;


#define portBYTE_ALIGNMENT_MASK	   ( 0x000f )

#ifndef portNUM_CONFIGURABLE_REGIONS
	#define portNUM_CONFIGURABLE_REGIONS	1
#endif

#ifndef portHAS_STACK_OVERFLOW_CHECKING
	#define portHAS_STACK_OVERFLOW_CHECKING	   0
#endif

#ifndef portARCH_NAME
	#define portARCH_NAME	 NULL
#endif

#include "mpu_wrappers.h"


#if ( portUSING_MPU_WRAPPERS == 1 )
	#if ( portHAS_STACK_OVERFLOW_CHECKING == 1 )
		StackType_t * pxPortInitialiseStack( StackType_t * pxTopOfStack,
			 StackType_t * pxEndOfStack,
			 TaskFunction_t pxCode,
			 void * pvParameters,
			 BaseType_t xRunPrivileged ) PRIVILEGED_FUNCTION;
	#else
		StackType_t * pxPortInitialiseStack( StackType_t * pxTopOfStack,
			 TaskFunction_t pxCode,
			 void * pvParameters,
			 BaseType_t xRunPrivileged ) PRIVILEGED_FUNCTION;
	#endif
#else 
	#if ( portHAS_STACK_OVERFLOW_CHECKING == 1 )
		StackType_t * pxPortInitialiseStack( StackType_t * pxTopOfStack,
			 StackType_t * pxEndOfStack,
			 TaskFunction_t pxCode,
			 void * pvParameters ) PRIVILEGED_FUNCTION;
	#else
		StackType_t * pxPortInitialiseStack( StackType_t * pxTopOfStack,
			 TaskFunction_t pxCode,
			 void * pvParameters ) PRIVILEGED_FUNCTION;
	#endif
#endif

#ifdef configUSE_FREERTOS_PROVIDED_HEAP


typedef struct HeapRegion
{
	uint8_t * pucStartAddress;
	size_t xSizeInBytes;
} HeapRegion_t;


typedef struct xHeapStats
{
	size_t xAvailableHeapSpaceInBytes;			
	size_t xSizeOfLargestFreeBlockInBytes;		
	size_t xSizeOfSmallestFreeBlockInBytes;		
	size_t xNumberOfFreeBlocks;					
	size_t xMinimumEverFreeBytesRemaining;		
	size_t xNumberOfSuccessfulAllocations;		
	size_t xNumberOfSuccessfulFrees;			
} HeapStats_t;

void vPortDefineHeapRegions( const HeapRegion_t * const pxHeapRegions ) PRIVILEGED_FUNCTION;
void vPortGetHeapStats( HeapStats_t * pxHeapStats );

void * pvPortMalloc( size_t xSize ) PRIVILEGED_FUNCTION;
void vPortFree( void * pv ) PRIVILEGED_FUNCTION;
void vPortInitialiseBlocks( void ) PRIVILEGED_FUNCTION;
size_t xPortGetFreeHeapSize( void ) PRIVILEGED_FUNCTION;
size_t xPortGetMinimumEverFreeHeapSize( void ) PRIVILEGED_FUNCTION;

#if( configSTACK_ALLOCATION_FROM_SEPARATE_HEAP == 1 )
	void *pvPortMallocStack( size_t xSize ) PRIVILEGED_FUNCTION;
	void vPortFreeStack( void *pv ) PRIVILEGED_FUNCTION;
#else
	#define pvPortMallocStack pvPortMalloc
	#define vPortFreeStack vPortFree
#endif
#else  // configUSE_FREERTOS_PROVIDED_HEAP


#define pvPortMalloc malloc
#define vPortFree free
#define xPortGetFreeHeapSize esp_get_free_heap_size
#define xPortGetMinimumEverFreeHeapSize esp_get_minimum_free_heap_size

#endif


BaseType_t xPortStartScheduler( void ) PRIVILEGED_FUNCTION;


void vPortEndScheduler( void ) PRIVILEGED_FUNCTION;


#if ( portUSING_MPU_WRAPPERS == 1 )
	struct xMEMORY_REGION;
	void vPortStoreTaskMPUSettings( xMPU_SETTINGS * xMPUSettings,
		const struct xMEMORY_REGION * const xRegions,
		StackType_t * pxBottomOfStack,
		uint32_t ulStackDepth ) PRIVILEGED_FUNCTION;
#endif