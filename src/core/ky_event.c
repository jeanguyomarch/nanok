#include "ky/pool.h"
#include "ky/event.h"
#include "ky/scheduler.h"
#include "ky/syscall.h"
#include "ky/assert.h"

struct event
{
   s_task *task;
   bool repeats;
};

static s_event _events_pool[16];
static s_pool _pool = KY_POOL_INIT(_events_pool);

KAPI void
ky_event_init(void)
{
   ky_pool_init(&_pool);
}

static s_event *
_event_new(bool repeats)
{
   s_event *const event = ky_pool_reserve(&_pool);
   event->task = NULL;
   event->repeats = repeats;
   return event;
}

KAPI s_event *
ky_event_new(void)
{
   return _event_new(false);
}

KAPI s_event *
ky_event_repeated_new(void)
{
   return _event_new(true);
}

KAPI void
ky_event_free(s_event *event)
{
   ky_pool_release(&_pool, event);
}

KAPI void
ky_event_trigger(s_event *event)
{
   KY_ASSERT(event->task != NULL);
   ky_scheduler_add(event->task);
   if (! event->repeats)
     ky_event_free(event);
}

KAPI void
ky_event_await(s_event *event,
               s_task *task)
{
   ky_event_bind(event, task);
   task->status = KY_TASK_STATUS_WAITING;
   ky_yield();
}

KAPI void
ky_event_bind(s_event *event,
              s_task *task)
{
   event->task = task;
}
