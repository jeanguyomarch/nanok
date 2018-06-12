#ifndef STM32F4_DISCO_ARCH_EXCEPTION_FRAME_H__
#define STM32F4_DISCO_ARCH_EXCEPTION_FRAME_H__

#include "ky/compiler.h"

#include <stm32f4xx.h>
#include <stdint.h>

typedef struct __attribute__((packed))
{
   uint32_t r0;
   uint32_t r1;
   uint32_t r2;
   uint32_t r3;
   uint32_t r12;
   uint32_t lr;
   uint32_t pc;
   xPSR_Type xpsr;
   /* XXX If the FPU is enabled, more elements are required */
} s_exception_frame;

#endif /* ! STM32F4_DISCO_ARCH_EXCEPTION_FRAME_H__ */
