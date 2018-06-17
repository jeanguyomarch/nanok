/* NanoK - MIT License */

#ifndef STM32F4_DISCO_ARCH_SYSCALL_H__
#define STM32F4_DISCO_ARCH_SYSCALL_H__

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

__syscall__ noreturn void nk_stall(void)
{
   /* TODO Improve */
   for (;;) continue;
   __builtin_unreachable();
}

#endif /* ! STM32F4_DISCO_ARCH_SYSCALL_H__ */ 
