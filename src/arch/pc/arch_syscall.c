/* NanoK - MIT License */

#include "nanok/syscall.h"
#include "nanok/task.h"
#include "nanok/scheduler.h"
#include "nanok/assert.h"

void
arch_syscall_run(void)
{
   s_task *const first_task = nk_scheduler_schedule();
   NK_ASSERT(first_task != NULL);

   setcontext(&(first_task->context.uctx));
}

void
arch_syscall_yield(void)
{
   s_task *const current_task = nk_scheduler_current_task_get();
   const s_task *const elected_task = nk_scheduler_schedule();

   swapcontext(&(current_task->context.uctx), &(elected_task->context.uctx));
}

KAPI void
arch_syscall_terminate(void)
{
   s_task *const current_task = nk_scheduler_current_task_get();
   nk_task_del(current_task);

   const s_task *const new_task = nk_scheduler_schedule();
   NK_ASSERT(new_task != NULL);
   setcontext(&(new_task->context.uctx));
   __builtin_unreachable();
}
