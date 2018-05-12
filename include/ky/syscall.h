#ifndef KY_SYSCALL_H__
#define KY_SYSCALL_H__

#include "ky/compiler.h"

__syscall__ void yield(void);
__syscall__ noreturn void run(void);
__syscall__ noreturn void end(void);
__syscall__ noreturn void stall(void);

__syscall_handler__ void ky_syscall_yield(void);
__syscall_handler__ void ky_syscall_run(void);
__syscall_handler__ void ky_syscall_end(void);
__syscall_handler__ void ky_syscall_stall(void);

#include "arch/syscall.h"

#endif /* ! KY_SYSCALL_H__ */
