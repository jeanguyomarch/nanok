#ifndef KY_COMPILER_H__
#define KY_COMPILER_H__

#define __weak__ __attribute__((weak))
#define __unused__ __attribute__((unused))
#define __noreutrn__ __attribute__((noreturn))

#define unlikely(Expression_) __builtin_expect((Expression_), 0)
#define likely(Expression_) __builtin_expect((Expression_), 1)

#define container_of(Ptr, Type, Member)                         \
   ({			                                        \
    const typeof(((Type *)0)->Member) * const __mptr = (Ptr);	\
    (Type *)((unsigned char *)__mptr - offsetof(Type, Member)); \
   })

#endif /* ! KY_COMPILER_H__ */
