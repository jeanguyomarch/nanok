/* NanoK - MIT License */

#ifndef NANOK_LOG_H__
#define NANOK_LOG_H__

#include "nanok/compiler.h"
#include <stddef.h>

KAPI void arch_log_puts(const char *message);
KAPI void arch_log_puts_n(const char *message, size_t length);
KAPI void arch_log_printf(const char *format, ...) __printf__(1, 2);
KAPI void arch_log_init(void);

#define NK_PUTS(String) \
   arch_log_puts_n("" String "", sizeof(String) - 1u)

#endif /* ! NANOK_LOG_H__ */
