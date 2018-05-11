#ifndef KY_KTEST_KTEST_H__
#define KY_KTEST_KTEST_H__

#include "ky/assert.h"

#include <setjmp.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdarg.h>

extern jmp_buf _ktest_ctx;

typedef void (*const f_ktest)(void);

#define KTEST_ASSERT(Condition_)                                        \
   do {                                                                 \
      if (! (Condition_)) {                                             \
         ky_assert_fail(__FILE__, __LINE__ + 0UL, # Condition_);        \
      }                                                                 \
   } while (0)

static inline bool
ktest_run(f_ktest test)
{
   if (! setjmp(_ktest_ctx))
   {
      test();
      return true;
   }
   else
   { return false; }
}


#define KTESTS(...)                                             \
  static const f_ktest _tests[] =                               \
  { __VA_ARGS__  };                                             \
  jmp_buf _ktest_ctx;                                           \
                                                                \
  void                                                          \
  ky_assert_fail(const char *filename,                          \
                 unsigned long line,                            \
                 const char *failure)                           \
  {                                                             \
     fprintf(stderr, "[%s:%lu] ASSERTION_FAILED: %s\n",         \
             filename, line, failure);                          \
     longjmp(_ktest_ctx, !0);                                   \
  }                                                             \
                                                                \
  int main(void)                                                \
  {                                                             \
    size_t nb_tests = sizeof(_tests) / sizeof(_tests[0]);       \
    size_t failed_tests = 0u;                                   \
    for (size_t i = 0u; i < nb_tests; i++)                      \
    {  failed_tests += ktest_run(_tests[i]) ? 0u : 1u; }        \
    return failed_tests;                                        \
  }

#endif /* ! KY_KTEST_KTEST_H__ */
