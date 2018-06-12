#ifndef STM32F4_DISCO_ARCH_SYSCALL_H__
#define STM32F4_DISCO_ARCH_SYSCALL_H__

// High registers are not preserved during a context switch

__syscall__ void ky_yield(void)
{
   asm volatile(
      /*"vpush {s16-s31}\n"*/
      "cpsie i\n"
      "svc 0\n"
      "cpsid i\n"
      /*"vpop {s16-s31}\n"*/
      :
      :
      : "memory", "r4", "r5", "r6", "r7", "r8", "r9", "r10", "r11", "r12"
   );
}

__syscall__ noreturn void ky_run(void)
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

__syscall__ noreturn void ky_terminate(void)
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

__syscall__ noreturn void ky_stall(void)
{
   /* TODO Improve */
   for (;;) continue;
   __builtin_unreachable();
}

#endif /* ! STM32F4_DISCO_ARCH_SYSCALL_H__ */ 
