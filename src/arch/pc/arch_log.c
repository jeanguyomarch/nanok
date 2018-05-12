#include "ky/log.h"

#include <stdio.h>
#include <stdarg.h>

KAPI void
ky_log_puts(const char *message)
{
   fputs(message, stdout);
}

KAPI void
ky_log_printf(const char *format, ...)
{
   va_list args;

   va_start(args, format);
   vfprintf(stdout, format, args);
   va_end(args);
}
