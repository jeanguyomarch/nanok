#ifndef NK_KTEST_KTEST_H__
#define NK_KTEST_KTEST_H__

#include <nanok/compiler.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdarg.h>
#include <signal.h>

typedef void (*const f_ktest)(void);

#define KTEST_ASSERT(Condition_)                                        \
  do {                                                                  \
    if (unlikely(! (Condition_))) {                                     \
      fprintf(stderr, "=========================================\n"     \
                      "ASSERTION FAILED in file %s at line %lu\n"       \
                      " ~> %s\n"                                        \
                      "=========================================\n",    \
              __FILE__, __LINE__ + 0UL, # Condition_);                  \
      raise(SIGABRT);                                                   \
    }                                                                   \
  } while (0)

#define KTESTS(...)                                             \
  static const f_ktest _tests[] =                               \
  { __VA_ARGS__  };                                             \
                                                                \
  int main(void)                                                \
  {                                                             \
    const size_t nb_tests = sizeof(_tests) / sizeof(_tests[0]); \
    for (size_t i = 0u; i < nb_tests; i++)                      \
    { _tests[i](); }                                            \
    return EXIT_SUCCESS;                                        \
  }

#endif /* ! NK_KTEST_KTEST_H__ */
