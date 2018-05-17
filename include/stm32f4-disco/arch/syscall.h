#ifndef STM32F4_DISCO_ARCH_SYSCALL_H__
#define STM32F4_DISCO_ARCH_SYSCALL_H__

// High registers are not preserved during a context switch

__syscall__ void ky_yield(void)
{
   asm volatile(
      "VPUSH {s16-s31}\n"
      "CPSIE i\n"
      "SVC 0\n"
      "CPSID i\n"
      "VPOP {s16-s31}\n"
      :
      :
      : "memory", "r4", "r5", "r6", "r7", "r8", "r9", "r10", "r11", "r12"
   );
}

__syscall__ noreturn void ky_run(void)
{
   asm volatile(
      "CPSIE i\n"
      "SVC 1\n"
      :
      :
      :
   );
   __builtin_unreachable();
}

__syscall__ noreturn void ky_terminate(void)
{
   asm volatile(
      "CPSIE i\n"
      "SVC 2\n"
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
