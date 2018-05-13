#ifndef KY_SYSCALL_H__
#define KY_SYSCALL_H__

#include "ky/compiler.h"

__syscall__ void ky_yield(void);
__syscall__ noreturn void ky_run(void);
__syscall__ noreturn void ky_terminate(void);
__syscall__ noreturn void ky_stall(void);

__syscall_handler__ void ky_syscall_yield(void);
__syscall_handler__ void ky_syscall_run(void);
__syscall_handler__ void ky_syscall_terminate(void);
__syscall_handler__ void ky_syscall_stall(void);

#include "arch/syscall.h"

#endif /* ! KY_SYSCALL_H__ */
