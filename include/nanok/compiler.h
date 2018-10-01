/* NanoK - MIT License */
/**
 * \file nanok/compiler.h
 * \brief Platform-agnistic compiler helpers
 *
 * The C compiler often comes with a set of handy extensions that make code
 * writing more concise and mor efficient when carefully used. This header
 * provides these compiler extensions in a protable manner (independant of the
 * target, and maybe later independant of the compiler).
 *
 * @{
 */

#ifndef NANOK_COMPILER_H__
#define NANOK_COMPILER_H__

/**
 * \def __syscall__
 *
 * Mark a function as being a syscall. This forces inlining.
 */
#define __syscall__ __attribute__((always_inline)) static inline

/**
 * \def __weak__
 *
 * Mark a function as being weak: it will have a weak linkage.
 */
#define __weak__ __attribute__((weak))

/**
 * \def __unused__
 *
 * Mark a variable, function or function parameter as being unused.
 */
#define __unused__ __attribute__((unused))

/**
 * \def __printf__(FmtIdx, ArgIdx)
 *
 * Mark a function as accepting a printf-like format
 *
 * \param[in] FmtIdx The index in the function parameters where the format will
 *   reside. Starts at 1.
 * \param[in] ArgIdx The index in the function parameters after which variadic
 *   arguments will be provided. Starts at 1.
 */
#define __printf__(FmtIdx, ArgIdx) __attribute__((__format__ (__gnu_printf__, FmtIdx, ArgIdx)))

/**
 * \def unlikely(Expression_)
 *
 * Mark a branch as being unlikely (in a cold code path).
 *
 * \param[in] Expression_ The expression which evaluation is unlikely to be
 *   true-ish
 */
#define unlikely(Expression_) __builtin_expect((Expression_), 0)

/**
 * \def likely(Expression_)
 *
 * Mark a branch as being likely (in a hot code path).
 *
 * \param[in] Expression_ The expression which evaluation is likely to be
 *   true-ish
 */
#define likely(Expression_) __builtin_expect((Expression_), 1)

/**
 * \def container_of(Ptr, Type, Member)
 *
 * Retrieve the container of a C object, assuming a zero-allocation container.
 *
 * \param[in] Ptr Pointer to the C object contained within a container
 * \param[in] Type C type of the container
 * \param[in] Member name of the C structure in the object in its container
 */
#define container_of(Ptr, Type, Member)                         \
   ({			                                        \
    const typeof(((Type *)0)->Member) * const __mptr = (Ptr);	\
    (Type *)((unsigned char *)__mptr - offsetof(Type, Member)); \
   })

/**
 * \def KAPI
 *
 * This macro qualifies publicly exported APIs.
 */
#define KAPI __attribute__ ((visibility("default")))

/**
 * \def ARRAY_SIZE(Arr)
 *
 * Evaluate the number of elements contained in a staticly-sized C array.
 *
 * \param[in] Arr A statically-sized array
 * \warning This will yield to invalid results if used on a pointer.
 */
#define ARRAY_SIZE(Arr) (sizeof(Arr) / sizeof((Arr)[0]))

#endif /* ! NANOK_COMPILER_H__ */ /** @} */
