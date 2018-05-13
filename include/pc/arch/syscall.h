#ifndef PC_ARCH_SYSCALL_H__
#define PC_ARCH_SYSCALL_H__

#include <stdlib.h>

__syscall__ void ky_yield(void)
{
   ky_syscall_yield();
}

__syscall__ noreturn void ky_run(void)
{
   ky_syscall_run();
   __builtin_unreachable();
}

__syscall__ noreturn void ky_terminate(void)
{
   ky_syscall_terminate();
   __builtin_unreachable();
}

__syscall__ noreturn void ky_stall(void)
{
   exit(EXIT_SUCCESS);
}

#endif /* ! PC_ARCH_SYSCALL_H__ */
