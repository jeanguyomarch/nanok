/* NanoK - MIT License */

#ifndef STM32F4_DISCO_ARCH_SYSCALL_H__
#define STM32F4_DISCO_ARCH_SYSCALL_H__

#include "nanok/event.h"

__syscall__ void nk_yield(void)
{
   asm volatile(
      "cpsie i\n"
      "svc 0\n"
      "cpsid i\n"
      :
      :
      : "memory", "r4", "r5", "r6", "r7", "r8", "r9", "r10", "r11", "r12"
   );
}

__syscall__ noreturn void nk_run(void)
{
   asm volatile(
      "cpsie i\n"
      "svc 1\n"
      :
      :
      :
   );
   __builtin_unreachable();
}

__syscall__ noreturn void nk_terminate(void)
{
   asm volatile(
      "cpsie i\n"
      "svc 2\n"
      :
      :
      :
   );
   __builtin_unreachable();
}

__syscall__ void nk_await(s_event *event)
{
   s_task *const current_task = nk_scheduler_current_task_get();
   nk_event_bind(event, current_task);

   __sync_synchronize(); /* Do not re-organize instructions from here */
   asm volatile(
      "cpsie i\n"
      "svc 3\n"
      :
      :
      :
   );
}

#endif /* ! STM32F4_DISCO_ARCH_SYSCALL_H__ */ 
