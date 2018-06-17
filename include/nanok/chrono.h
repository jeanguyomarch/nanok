/* NanoK - MIT License */

#ifndef NANOK_CHRONO_H__
#define NANOK_CHRONO_H__

#include "arch/types.h"
#include "nk_event.h"

typedef struct
{
   time_t secs;
   t_nanoseconds ns;
} s_chrono_duration;

#endif /* ! NANOK_CHRONO_H__ */
