#ifndef NK_KTEST_KTEST_H__
#define NK_KTEST_KTEST_H__

#include "nanok/assert.h"

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
         nk_assert_fail(__FILE__, __LINE__ + 0UL, # Condition_);        \
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
  nk_assert_fail(const char *filename,                          \
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
    const size_t nb_tests = sizeof(_tests) / sizeof(_tests[0]); \
    int failed_tests = 0;                                       \
    for (size_t i = 0u; i < nb_tests; i++)                      \
    { failed_tests += ktest_run(_tests[i]) ? 0 : 1; }           \
    printf("--   PASSED: %i / %zu\n",                           \
          (int) nb_tests - failed_tests, nb_tests);             \
    return failed_tests;                                        \
  }

#endif /* ! NK_KTEST_KTEST_H__ */
