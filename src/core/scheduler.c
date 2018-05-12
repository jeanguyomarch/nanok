#include "ky/assert.h"
#include "ky/scheduler.h"
#include "ky/task.h"
#include "ky/list.h"

static t_object_id _current_task_id = KY_OBJECT_ID_INVALID;

static s_list _normal_tasks = KY_LIST_INIT(_normal_tasks);
static s_list _urgent_tasks = KY_LIST_INIT(_urgent_tasks);

void
ky_scheduler_wake(t_object_id task_id)
{
   KY_ASSERT(task_id < ky_tasks_count);
   s_task *const task = &(ky_tasks[task_id]);

   KY_ASSERT(task->status == KY_TASK_STATUS_PAUSED);
   task->status = KY_TASK_STATUS_ACTIVE;

   s_list *const list = (task->priority == KY_TASK_PRIORITY_NORMAL)
      ? &_normal_tasks : &_urgent_tasks;
   ky_list_add_tail(list, KY_INLIST_GET(task));
}

void
ky_scheduler_pause(t_object_id task_id)
{
   KY_ASSERT(task_id < ky_tasks_count);
   s_task *const task = &(ky_tasks[task_id]);

   KY_ASSERT(task->status == KY_TASK_STATUS_ACTIVE);
   task->status = KY_TASK_STATUS_PAUSED;
}

t_object_id
ky_scheduler_current_task_id_get(void)
{
  return _current_task_id;
}

static t_object_id
_task_elect(s_list *tasks_list, const s_task *task)
{
   ky_list_del_head(tasks_list);
   return ky_task_id_get(task);
}

t_object_id
ky_scheduler_elect(void)
{
   s_inlist *l;

   /* Elect the first urgent task, if any */
   KY_LIST_FOREACH(&_urgent_tasks, l)
     {
       s_task *const task = KY_INLIST_ENTRY(l, s_task);
       return _task_elect(&_urgent_tasks, task);
     }

   /* Elect the first normal task */
   KY_LIST_FOREACH(&_normal_tasks, l)
     {
       s_task *const task = KY_INLIST_ENTRY(l, s_task);
       return _task_elect(&_normal_tasks, task);
     }

   return KY_OBJECT_ID_INVALID;
}
