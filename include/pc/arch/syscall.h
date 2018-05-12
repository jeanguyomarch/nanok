#ifndef ARCH_PC_SYSCALL_H__
#define ARCH_PC_SYSCALL_H__

#include <stdlib.h>

__syscall__ void yield(void)
{
   ky_syscall_yield();
}

__syscall__ noreturn void run(void)
{
   ky_syscall_run();
   __builtin_unreachable();
}

__syscall__ noreturn void end(void)
{
   ky_syscall_end();
   __builtin_unreachable();
}

__syscall__ noreturn void stall(void)
{
   exit(EXIT_SUCCESS);
}

#endif /* ! ARCH_PC_SYSCALL_H__ */
