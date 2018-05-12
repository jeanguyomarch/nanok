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
   KY_ASSERT(task->status != KY_TASK_STATUS_ACTIVE);
   task->status = KY_TASK_STATUS_ACTIVE;

   s_list *const list = (task->priority == KY_TASK_PRIORITY_NORMAL)
      ? &_normal_tasks : &_urgent_tasks;
   ky_list_add_tail(list, KY_INLIST_GET(task));
}

void
ky_scheduler_del(s_task *task)
{
   /* We can only delete elected tasks (tasks that stop themselves). So when
    * this function is called, the task has already been removed from any waiting
    * list.
    *
    * Just mark its state as being inactive (debug), and do nothing more.
    */
   KY_ASSERT(task->status == KY_TASK_STATUS_ACTIVE);
   task->status = KY_TASK_STATUS_INACTIVE;
}

s_task *
ky_scheduler_current_task_get(void)
{
  return _current_task;
}

static s_task *
_task_elect(s_list *tasks_list, s_task *task)
{
   /* Pop from the list the next task to be elected. It shall be 'task' */
   KY_ASSERT((void *)task == (void *)tasks_list->head.next);
   ky_list_del_head(tasks_list);

   /* If the task that is currently elected (by which will change when this
    * function returns) can be elected again, insert it as the bottom of the
    * election list. That's a round robin. */
   if (_current_task->status == KY_TASK_STATUS_ACTIVE)
     {
        ky_list_add_tail(tasks_list, KY_INLIST_GET(_current_task));
     }

   /* Proceed to the election */
   _current_task = task;
   return _current_task;
}

s_task *
ky_scheduler_schedule(void)
{
   /* Elect the first pending urgent task, if any.
    * Otherwise, elect the first pending normal task, if any.
    * Otherwise, keep the current task elected by doing nothing. */
   if (! ky_list_empty(&_urgent_tasks))
     {
        s_task *const task = KY_LIST_FIRST_ENTRY_GET(&_urgent_tasks, s_task);
        return _task_elect(&_urgent_tasks, task);
     }
   else if (likely(! ky_list_empty(&_normal_tasks)))
     {
        s_task *const task = KY_LIST_FIRST_ENTRY_GET(&_normal_tasks, s_task);
        return _task_elect(&_normal_tasks, task);
     }
   else
     {
        return _current_task;
     }
}
