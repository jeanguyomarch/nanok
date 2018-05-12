#ifndef KY_ASSERT_H__
#define KY_ASSERT_H__

#include "ky/compiler.h"
#include <stdnoreturn.h>

noreturn void ky_assert_fail(const char *filename, unsigned long line, const char *failure);

#define KY_ASSERT(Condition_)                                   \
  do {                                                          \
    if (unlikely(! (Condition_))) {                             \
       ky_assert_fail(__FILE__, __LINE__ + 0UL, # Condition_);  \
    }                                                           \
  } while (0)

#endif /* ! KY_ASSERT_H__ */
