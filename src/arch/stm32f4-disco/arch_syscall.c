/* NanoK - MIT License */

#include "nanok/syscall.h"
#include "nanok/task.h"
#include "nanok/scheduler.h"
#include "arch/exception_frame.h"

#include <stm32f4xx_hal.h>
#include <assert.h>

#define __syscall_handler__ __attribute__((naked)) noreturn

__attribute__((always_inline)) static inline uint32_t
_lr_get(void)
{
   register uint32_t result;
   asm volatile(
      "mov %0, lr\n"
      : "=r"(result)
   );
   return result;
}


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

static __syscall_handler__ void
_syscall_run(void)
{
   s_task *const first_task = nk_scheduler_schedule();
   assert(first_task != NULL);

   const s_task_context *const ctx = &(first_task->context);

   __set_PSP(ctx->psp);
   _exception_return(ctx->exc_return);
}


static __syscall_handler__ void
_syscall_yield(void)
{
   s_task *const current_task = nk_scheduler_current_task_get();
   nk_scheduler_enqueue(current_task);
   s_task *const elected_task = nk_scheduler_schedule();

   s_task_context *const prev_context = &(current_task->context);
   const s_task_context *const next_context = &(elected_task->context);

   prev_context->psp = __get_PSP();

   __set_PSP(next_context->psp);
   _exception_return(next_context->exc_return);
}

static __syscall_handler__ void
_syscall_await(void)
{
   s_task *const current_task = nk_scheduler_current_task_get();
   s_task *const elected_task = nk_scheduler_schedule();

   s_task_context *const prev_context = &(current_task->context);
   const s_task_context *const next_context = &(elected_task->context);

   prev_context->psp = __get_PSP();

   __set_PSP(next_context->psp);
   _exception_return(next_context->exc_return);
}

static __syscall_handler__ void
_syscall_terminate(void)
{
   s_task *const current_task = nk_scheduler_current_task_get();
   nk_task_del(current_task);

   const s_task *const new_task = nk_scheduler_schedule();
   assert(new_task != NULL);
   const s_task_context *const new_context = &(new_task->context);

   __set_PSP(new_context->psp);
   _exception_return(new_context->exc_return);
}


__attribute__((naked)) noreturn void
SVC_Handler(void)
{
   register uint32_t psp;
   asm volatile(
      "tst lr, #4\n"
      "ite eq\n"
      "mrseq %0, msp\n"
      "mrsne %0, psp\n"
      : "=r"(psp)
   );

   const s_exception_frame *const frame = (s_exception_frame *)psp;
   const uint8_t svc_id = ((const uint8_t *)frame->pc)[-2]; /* Thumb */

   static void (*const syscall[])(void) = {
      [0] = _syscall_yield,
      [1] = _syscall_run,
      [2] = _syscall_terminate,
      [3] = _syscall_await,
   };
   assert(svc_id < ARRAY_SIZE(syscall));
   syscall[svc_id]();
}
