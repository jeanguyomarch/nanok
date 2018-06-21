/* NanoK - MIT License */

#ifndef NANOK_EVENT_H__
#define NANOK_EVENT_H__

#include "nanok/compiler.h"
#include "nanok/scheduler.h"
#include "nanok/task.h"

typedef struct event s_event;
struct event
{
   s_task *task;
};

KAPI void nk_event_init(void);
KAPI s_event *nk_event_new(void);
KAPI void nk_event_setup(s_event *event);
KAPI void nk_event_free(s_event *event);
KAPI void nk_event_trigger(s_event *event);
KAPI void nk_event_bind(s_event *event, s_task *task);

#endif /* NANOK_EVENT_H__ */
