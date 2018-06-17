/* NanoK - MIT License */

#include "nanok/log.h"

#include <stdio.h>
#include <stdarg.h>

KAPI void
arch_log_init(void)
{
   /* Nothing to do */
}

KAPI void
arch_log_puts(const char *message)
{
   fputs(message, stdout);
}

KAPI void
arch_log_puts_n(const char *message, size_t len __unused__)
{
   fputs(message, stdout);
}

KAPI void
arch_log_printf(const char *format, ...)
{
   va_list args;

   va_start(args, format);
   vfprintf(stdout, format, args);
   va_end(args);
}
