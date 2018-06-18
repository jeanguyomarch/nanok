/* NanoK - MIT License */

#ifndef PC_ARCH_SYSCALL_H__
#define PC_ARCH_SYSCALL_H__

#include "nanok/task.h"
#include "nanok/scheduler.h"
#include "nanok/assert.h"
#include "nanok/event.h"

#include <stdlib.h>
#include <ucontext.h>

__syscall__ void nk_yield(void)
{
   /* Put the current task at the end of the scheduling queue. It
    * will be found TWICE when nk_scheduler_schedule() is called,
    * but will be immediately removed ONCE there. */
   s_task *const current_task = nk_scheduler_current_task_get();
   nk_scheduler_enqueue(current_task);
   const s_task *const elected_task = nk_scheduler_schedule();

   swapcontext(&(current_task->context.uctx), &(elected_task->context.uctx));
}

__syscall__ void nk_await(s_event *event)
{
   /* Same than nk_yield(), but does not put the current task back into the
    * scheduling queue */
   s_task *const current_task = nk_scheduler_current_task_get();
   nk_event_bind(event, current_task);

   const s_task *const elected_task = nk_scheduler_schedule();

   swapcontext(&(current_task->context.uctx), &(elected_task->context.uctx));
}

__syscall__ noreturn void nk_run(void)
{
   s_task *const first_task = nk_scheduler_schedule();
   NK_ASSERT(first_task != NULL);

   setcontext(&(first_task->context.uctx));
   __builtin_unreachable();
}

__syscall__ noreturn void nk_terminate(void)
{
   s_task *const current_task = nk_scheduler_current_task_get();
   nk_task_del(current_task);

   const s_task *const new_task = nk_scheduler_schedule();
   NK_ASSERT(new_task != NULL);
   setcontext(&(new_task->context.uctx));
   __builtin_unreachable();
}

__syscall__ noreturn void nk_stall(void)
{
   exit(EXIT_SUCCESS);
}

#endif /* ! PC_ARCH_SYSCALL_H__ */
