#include "ky/syscall.h"
#include "ky/task.h"
#include "ky/scheduler.h"
#include "ky/assert.h"

#include <stm32f4xx_hal.h>

__attribute__((always_inline)) noreturn static inline void
_exception_return(uint32_t exc_return)
{
   asm volatile(
      "bx %0\n"
      :
      : "r"(exc_return)
      :
   );
   __builtin_unreachable();
}

__attribute__((always_inline)) static inline uint32_t
_lr_get(void)
{
   register uint32_t result;
   asm volatile(
      "MOV %0, lr\n"
      : "=r"(result)
   );
   return result;
}

__syscall_handler__ void
ky_syscall_run(void)
{
   s_task *const first_task = ky_scheduler_schedule();
   KY_ASSERT(first_task != NULL);

   const s_task_context *const ctx = &(first_task->context);

   __set_PSP(ctx->psp);
   _exception_return(ctx->exc_return);
}

__syscall_handler__ void
ky_syscall_yield(void)
{
   s_task *const current_task = ky_scheduler_current_task_get();
   s_task *const elected_task = ky_scheduler_schedule();

   s_task_context *const prev_context = &(current_task->context);
   const s_task_context *const next_context = &(elected_task->context);

   prev_context->psp = __get_PSP();
   prev_context->exc_return = _lr_get();

   __set_PSP(next_context->psp);
   _exception_return(next_context->exc_return);
}

__syscall_handler__ void
ky_syscall_terminate(void)
{
   s_task *const current_task = ky_scheduler_current_task_get();
   ky_task_del(current_task);

   const s_task *const new_task = ky_scheduler_schedule();
   KY_ASSERT(new_task != NULL);
   const s_task_context *const new_context = &(new_task->context);

   __set_PSP(new_context->psp);
   _exception_return(new_context->exc_return);
}

