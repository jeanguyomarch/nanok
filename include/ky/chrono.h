#ifndef KY_CHRONO_H__
#define KY_CHRONO_H__

#include "arch/types.h"
#include "ky_event.h"

typedef struct
{
   time_t secs;
   t_nanoseconds ns;
} s_chrono_duration;

static inline ky_sleep()
{
   s_event *const event = ky_event_new();
   s_task *const task = ky_scheduler_current_task_get();

   ky_event_bind(event, task);

   ky_event_await(event, task);
}

#endif /* ! KY_CHRONO_H__ */
