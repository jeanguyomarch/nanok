/* NanoK - MIT License */

#include "nanok/pool.h"
#include "nanok/event.h"
#include "nanok/scheduler.h"
#include "nanok/syscall.h"
#include <assert.h>

static s_event _events_pool[16];
static s_pool _pool = NK_POOL_INIT(_events_pool);

KAPI void
nk_event_init(void)
{
   nk_pool_init(&_pool);
}

KAPI s_event *
nk_event_new(void)
{
   s_event *const event = nk_pool_reserve(&_pool);
   nk_event_setup(event);
   return event;
}

KAPI void
nk_event_setup(s_event *event)
{
   event->task = NULL;
}

KAPI void
nk_event_free(s_event *event)
{
   nk_pool_release(&_pool, event);
}

KAPI void
nk_event_trigger(s_event *event)
{
   assert(event->task != NULL);
   nk_scheduler_enqueue(event->task);
}

KAPI void
nk_event_bind(s_event *event,
              s_task *task)
{
   event->task = task;
}
