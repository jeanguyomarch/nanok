/* NanoK - MIT License */

#ifndef NANOK_COMPILER_H__
#define NANOK_COMPILER_H__

#include "arch/compiler.h"

#include <stdnoreturn.h>

#define __syscall__ __attribute__((always_inline)) static inline

#define __weak__ __attribute__((weak))
#define __unused__ __attribute__((unused))
#define __printf__(FmtIdx, ArgIdx) __attribute__((__format__ (__gnu_printf__, FmtIdx, ArgIdx)))

#define unlikely(Expression_) __builtin_expect((Expression_), 0)
#define likely(Expression_) __builtin_expect((Expression_), 1)

#define container_of(Ptr, Type, Member)                         \
   ({			                                        \
    const typeof(((Type *)0)->Member) * const __mptr = (Ptr);	\
    (Type *)((unsigned char *)__mptr - offsetof(Type, Member)); \
   })

#define KAPI __attribute__ ((visibility("default")))

#define ARRAY_SIZE(Arr) (sizeof(Arr) / sizeof((Arr)[0]))

#endif /* ! NANOK_COMPILER_H__ */
