#include "ky/pool.h"
#include "ky/event.h"
#include "ky/object.h"
#include "ky/scheduler.h"

struct event
{
   t_object_id event_id;
   t_object_id task_id;
};

static s_event _events_pool[64];
static s_pool _pool = KY_POOL_INITIALIZER(_events_pool);

s_event *
ky_event_new(void)
{
   s_event *const event = ky_pool_reserve(&_pool);
   event->event_id = ky_pool_index_get(&_pool, event);
   event->task_id = KY_OBJECT_ID_INVALID;

   return event;
}

void
ky_event_bind(s_event *event,
              t_object_id task_id)
{
   event->task_id = task_id;
}

void
ky_event_trigger(s_event *event)
{
   ky_scheduler_wake(event->task_id);
   ky_pool_release(&_pool, event);
}
