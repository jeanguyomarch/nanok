/* NanoK - MIT License */

#include "nanok/assert.h"
#include "nanok/scheduler.h"
#include "nanok/task.h"
#include "nanok/list.h"
#include "nanok/assert.h"

static s_task *_current_task = NULL;

static s_list _normal_tasks = NK_LIST_INIT(_normal_tasks);

KAPI void
nk_scheduler_init(void)
{
   /* Nothing to do */
}

KAPI void
nk_scheduler_enqueue(s_task *task)
{
   nk_list_add_tail(&_normal_tasks, NK_INLIST_GET(task));
}

KAPI s_task *
nk_scheduler_current_task_get(void)
{
  return _current_task;
}

KAPI s_task *
nk_scheduler_schedule(void)
{
   NK_ASSERT(_normal_tasks.count > 0);
   /* Elect the first pending task */
   s_task *const task = NK_LIST_FIRST_ENTRY_GET(&_normal_tasks, s_task);

   /* Pop from the list the next task to be elected. It shall be 'task' */
   nk_list_del_head(&_normal_tasks);

   /* Proceed to the election */
   _current_task = task;
   return task;
}
