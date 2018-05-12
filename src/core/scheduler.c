#include "ky/assert.h"
#include "ky/scheduler.h"
#include "ky/task.h"
#include "ky/list.h"
#include "ky/assert.h"

static s_task *_current_task = NULL;

static s_list _normal_tasks = KY_LIST_INIT(_normal_tasks);
static s_list _urgent_tasks = KY_LIST_INIT(_urgent_tasks);

void
ky_scheduler_init(void)
{
   s_task *const idle = &ky_idle_task;
   arch_task_setup(idle);
   ky_scheduler_add(idle);
   _current_task = idle;
}

void
ky_scheduler_add(s_task *task)
{
   KY_ASSERT(task->status == KY_TASK_STATUS_INACTIVE);
   task->status = KY_TASK_STATUS_ACTIVE;

   s_list *const list = (task->priority == KY_TASK_PRIORITY_NORMAL)
      ? &_normal_tasks : &_urgent_tasks;
   ky_list_add_tail(list, KY_INLIST_GET(task));
}

void
ky_scheduler_del(s_task *task)
{
   KY_ASSERT(task->status == KY_TASK_STATUS_ACTIVE);
   task->status = KY_TASK_STATUS_INACTIVE;
   ky_inlist_del(KY_INLIST_GET(task));
}

s_task *
ky_scheduler_current_task_get(void)
{
  return _current_task;
}

static s_task *
_task_elect(s_list *tasks_list, s_task *task)
{
   s_task *const current_task = _current_task;
   ky_list_del_head(tasks_list);
   ky_list_add_tail(tasks_list, KY_INLIST_GET(current_task));
   _current_task = task;
   return current_task;
}

s_task *
ky_scheduler_schedule(void)
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

   KY_ASSERT(false && "A task shall have been elected");
   return NULL;
}
