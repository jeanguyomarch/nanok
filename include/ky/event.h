#ifndef KY_EVENT_H__
#define KY_EVENT_H__

#include "ky/compiler.h"
#include "ky/scheduler.h"
#include "ky/task.h"

typedef struct event s_event;

KAPI void ky_event_init(void);
KAPI s_event *ky_event_new(void);
KAPI s_event *ky_event_repeated_new(void);
KAPI void ky_event_free(s_event *event);
KAPI void ky_event_trigger(s_event *event);
KAPI void ky_event_await(s_event *event, s_task *task);
KAPI void ky_event_bind(s_event *event, s_task *task);

static inline void
ky_await(s_event *event)
{
   ky_event_await(event, ky_scheduler_current_task_get());
}

#endif /* KY_EVENT_H__ */
