/* NanoK - MIT License */

#include "nanok/assert.h"
#include "nanok/scheduler.h"
#include "nanok/task.h"
#include "nanok/syscall.h"
#include "nanok/list.h"
#include "nanok/assert.h"

static s_task *_current_task = NULL;


/*============================================================================*
 *                                  IDLE Task                                 *
 *============================================================================*/

static noreturn void
_idle_main(void)
{
   for (;;)
     {
        nk_yield();
     }
}

NK_STACK_DEFINE(_idle_stack, 64);
static s_task _idle_task =
{
   .start = _idle_main,
   .stack = _idle_stack,
   .stack_size = sizeof(_idle_stack) / sizeof(t_stack_alignment),
};
static s_inlist *const _idle = NK_INLIST_GET(&_idle_task);


/*============================================================================*
 *                                 Public API                                 *
 *============================================================================*/

KAPI void
nk_scheduler_init(void)
{
   arch_task_setup(&_idle_task);
   _idle->next = _idle;
   _idle->prev = _idle;
}

KAPI void
nk_scheduler_enqueue(s_task *task)
{
   nk_inlist_add_before(_idle, NK_INLIST_GET(task));
}

KAPI s_task *
nk_scheduler_current_task_get(void)
{
  return _current_task;
}

KAPI s_task *
nk_scheduler_schedule(void)
{
   /* Elect the first pending task: that's the task that is just after the IDLE
    * task.
    *
    * Step 0 (initial state):
    *
    *  .----------------------------------------.
    *  |  +------+    +--------+    +--------+  |
    *  '->+ IDLE +<-->+ TASK 1 +<-->+ TASK 2 +<-'
    *     +------+    +--------+    +--------+
    *
    * Step 1 (schedule TASK 1):
    *
    *  .--------------------------.
    *  |  +------+    +--------+  |
    *  '->+ IDLE +<-->+ TASK 2 +<-'
    *     +------+    +--------+
    *
    * Step 2 (schedule TASK 2).
    *  .------------.
    *  |  +------+  |
    *  '->+ IDLE +<-'
    *     +------+
    *
    * If we schedule IDLE, it means that ALL the tasks are in await() mode. So,
    * IDLE will be the first task to yield, which will be added back
    * immediately to the scheduling queue.
    */
   s_task *const task = NK_INLIST_ENTRY(_idle->next, s_task);
   nk_inlist_del(_idle->next);

   /* Proceed to the election */
   _current_task = task;
   return task;
}
