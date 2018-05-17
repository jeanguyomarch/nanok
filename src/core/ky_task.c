#include "ky/task.h"
#include "ky/scheduler.h"
#include "ky/pool.h"
#include "ky/assert.h"
#include "arch/types.h"

#define TASKS_COUNT 16u
static s_task _tasks[TASKS_COUNT];
static s_pool _task_pool = KY_POOL_INIT(_tasks);

#define STACK_SIZE 1024u
typedef t_stack_alignment t_stack[STACK_SIZE / sizeof(t_stack_alignment)];

static t_stack _stacks[TASKS_COUNT];
static s_pool _stack_pool = KY_POOL_INIT(_stacks);

KAPI void
ky_task_init(void)
{
   ky_pool_init(&_task_pool);
   ky_pool_init(&_stack_pool);
}

KAPI s_task *
ky_task_add(f_task start,
            e_task_priority priority)
{
   s_task *const task = ky_pool_reserve(&_task_pool);

   task->start = start;
   task->stack = ky_pool_reserve(&_stack_pool);
   task->stack_size = STACK_SIZE;
   task->priority = priority;
   task->status = KY_TASK_STATUS_INACTIVE;

   arch_task_setup(task);
   ky_scheduler_add(task);

   return task;
}

KAPI void
ky_task_del(s_task *task)
{
   arch_task_cleanup(task);
   ky_scheduler_del(task);
   ky_pool_release(&_stack_pool, task->stack);
   ky_pool_release(&_task_pool, task);
}
