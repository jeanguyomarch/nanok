#include "ky/pool.h"
#include "ky/event.h"
#include "ky/object.h"
#include "ky/scheduler.h"

struct event
{
   t_object_id event_id;
   s_task *task;
};

static s_event _events_pool[64];
static s_pool _pool = KY_POOL_INIT(_events_pool);

s_event *
ky_event_new(void)
{
   s_event *const event = ky_pool_reserve(&_pool);
   event->event_id = ky_pool_index_get(&_pool, event);
   event->task = NULL;

   return event;
}

void
ky_event_bind(s_event *event,
              s_task *task)
{
   event->task = task;
}

void
ky_event_trigger(s_event *event)
{
   ky_scheduler_add(event->task);
   ky_pool_release(&_pool, event);
}
