#ifndef KSTUB_KSTUB_H__
#define KSTUB_KSTUB_H__

#include "nanok/assert.h"

#include <stdio.h>
#include <stdlib.h>

#define KSTUB_ASSERT_HANDLER()                                  \
   KAPI noreturn void                                           \
   nk_assert_fail(const char *filename,                      \
                  unsigned long line,                           \
                  const char *failure)                          \
   {                                                            \
      fprintf(stderr, "[%s:%lu] ASSERTION FAILED: %s\n",        \
              filename, line, failure);                         \
      exit(EXIT_FAILURE);                                       \
   }

#endif /* ! KSTUB_KSTUB_H__ */
