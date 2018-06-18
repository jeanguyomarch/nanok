/* NanoK - MIT License */

#include "nanok/pool.h"
#include "nanok/event.h"
#include "nanok/scheduler.h"
#include "nanok/syscall.h"
#include "nanok/assert.h"

struct event
{
   s_task *task;
   bool repeats;
};

static s_event _events_pool[16];
static s_pool _pool = NK_POOL_INIT(_events_pool);

KAPI void
nk_event_init(void)
{
   nk_pool_init(&_pool);
}

static s_event *
_event_new(bool repeats)
{
   s_event *const event = nk_pool_reserve(&_pool);
   event->task = NULL;
   event->repeats = repeats;
   return event;
}

KAPI s_event *
nk_event_new(void)
{
   return _event_new(false);
}

KAPI s_event *
nk_event_repeated_new(void)
{
   return _event_new(true);
}

KAPI void
nk_event_free(s_event *event)
{
   nk_pool_release(&_pool, event);
}

KAPI void
nk_event_trigger(s_event *event)
{
   NK_ASSERT(event->task != NULL);
   nk_scheduler_enqueue(event->task);
   if (! event->repeats)
     nk_event_free(event);
}

KAPI void
nk_event_bind(s_event *event,
              s_task *task)
{
   event->task = task;
}
