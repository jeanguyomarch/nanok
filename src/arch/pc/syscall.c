#include "ky/syscall.h"
#include "ky/task.h"
#include "ky/scheduler.h"
#include "ky/assert.h"

__syscall_handler__ void
ky_syscall_run(void)
{
   s_task *const first_task = ky_scheduler_schedule();
   KY_ASSERT(first_task != NULL);

   setcontext(&(first_task->context.uctx));
}

__syscall_handler__ void
ky_syscall_yield(void)
{
   s_task *const current_task = ky_scheduler_current_task_get();
   const s_task *const elected_task = ky_scheduler_schedule();

   swapcontext(&(current_task->context.uctx), &(elected_task->context.uctx));
}

__syscall_handler__ void
ky_syscall_end(void)
{
   s_task *const current_task = ky_scheduler_current_task_get();
   ky_task_del(current_task);

   const s_task *const new_task = ky_scheduler_schedule();
   KY_ASSERT(new_task != NULL);
   setcontext(&(new_task->context.uctx));
}
