/* NanoK - MIT License */

#include "nanok/task.h"
#include "nanok/scheduler.h"
#include "nanok/pool.h"
#include "nanok/assert.h"
#include "arch/types.h"

#define TASKS_COUNT 4u
static s_task _tasks[TASKS_COUNT];
static s_pool _task_pool = NK_POOL_INIT(_tasks);

#define STACK_SIZE 512u 
typedef t_stack_alignment t_stack[STACK_SIZE / sizeof(t_stack_alignment)];

static t_stack _stacks[TASKS_COUNT];
static s_pool _stack_pool = NK_POOL_INIT(_stacks);

KAPI void
nk_task_init(void)
{
   nk_pool_init(&_task_pool);
   nk_pool_init(&_stack_pool);
}

KAPI s_task *
nk_task_add(f_task start,
            e_task_priority priority)
{
   s_task *const task = nk_pool_reserve(&_task_pool);

   task->start = start;
   task->stack = nk_pool_reserve(&_stack_pool);
   task->stack_size = STACK_SIZE;
   task->priority = priority;
   task->status = NK_TASK_STATUS_INACTIVE;

   arch_task_setup(task);
   nk_scheduler_add(task);

   return task;
}

KAPI void
nk_task_del(s_task *task)
{
   arch_task_cleanup(task);
   nk_scheduler_del(task);
   nk_pool_release(&_stack_pool, task->stack);
   nk_pool_release(&_task_pool, task);
}
