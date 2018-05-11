#ifndef KY_COMPILER_H__
#define KY_COMPILER_H__

#define __weak__ __attribute__((weak))
#define __unused__ __attribute__((unused))

#define __unlikely__(Expression_) __builtin_expect((Expression_), 0)
#define __likely__(Expression_) __builtin_expect((Expression_), 1)

#endif /* ! KY_COMPILER_H__ */
