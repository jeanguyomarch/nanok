#ifndef KY_LOG_H__
#define KY_LOG_H__

#include "ky/compiler.h"

KAPI void ky_log_puts(const char *message);
KAPI void ky_log_printf(const char *format, ...) __printf__(1, 2);

#endif /* ! KY_LOG_H__ */
