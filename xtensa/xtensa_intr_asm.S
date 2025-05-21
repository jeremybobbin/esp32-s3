#include <xtensa/hal.h>
#include <xtensa/config/core.h>

#include "xtensa/xtensa_context.h"
#include "freertos/FreeRTOSConfig.h"

#if XT_USE_SWPRI
/* Warning - this is not multicore-compatible. */
    .data
    .global _xt_intdata
    .align  8
_xt_intdata:
    .global _xt_intenable
    .type   _xt_intenable,@object
    .size   _xt_intenable,4
    .global _xt_vpri_mask
    .type   _xt_vpri_mask,@object
    .size   _xt_vpri_mask,4

_xt_intenable:     .word   0             /* Virtual INTENABLE     */
_xt_vpri_mask:     .word   0xFFFFFFFF    /* Virtual priority mask */
#endif

/*
-------------------------------------------------------------------------------
  Table of C-callable interrupt handlers for each interrupt. Note that not all
  slots can be filled, because interrupts at level > EXCM_LEVEL will not be
  dispatched to a C handler by default.

  Stored as:
  int 0 cpu 0
  int 0 cpu 1
  ...
  int 0 cpu n
  int 1 cpu 0
  int 1 cpu 1
  etc
-------------------------------------------------------------------------------
*/

    .data
    .global _xt_interrupt_table
    .align  8

_xt_interrupt_table:

    .set    i, 0
    .rept   XCHAL_NUM_INTERRUPTS*portNUM_PROCESSORS
    .word   xt_unhandled_interrupt      /* handler address               */
    .word   i                           /* handler arg (default: intnum) */
    .set    i, i+1
    .endr
