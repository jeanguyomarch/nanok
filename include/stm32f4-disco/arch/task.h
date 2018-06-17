/* NanoK - MIT License */

#ifndef STM32F4_DISCO_ARCH_TASK_H__
#define STM32F4_DISCO_ARCH_TASK_H__

#include <stdint.h>

typedef struct
{
   uint32_t exc_return;
     /**< Execution code when returning from an exception */
   uint32_t psp;
     /**< Program stack pointer */
     
} s_task_context;


#endif /* ! STM32F4_DISCO_ARCH_TASK_H__ */ 
