/* NanoK - MIT License */

#ifndef NANOK_ASSERT_H__
#define NANOK_ASSERT_H__

#include "nanok/compiler.h"
#include <stdnoreturn.h>

KAPI noreturn void nk_assert_fail(const char *filename, unsigned long line, const char *failure);


#define NK_ASSERT(Condition_)                                        \
  do {                                                                  \
    if (unlikely(! (Condition_))) {                                     \
       nk_assert_fail(__FILE__, __LINE__ + 0UL, # Condition_);       \
    }                                                                   \
  } while (0)

#endif /* ! NANOK_ASSERT_H__ */
