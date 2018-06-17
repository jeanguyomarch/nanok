/* NanoK - MIT License */

#ifndef NANOK_SYSCALL_H__
#define NANOK_SYSCALL_H__

#include "nanok/compiler.h"

__syscall__ void nk_yield(void);
__syscall__ noreturn void nk_run(void);
__syscall__ noreturn void nk_terminate(void);
__syscall__ noreturn void nk_stall(void);

#include "arch/syscall.h"

#endif /* ! NANOK_SYSCALL_H__ */
