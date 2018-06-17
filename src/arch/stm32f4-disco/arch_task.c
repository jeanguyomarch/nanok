/* NanoK - MIT License */

#include "nanok/init.h"
#include "nanok/syscall.h"
#include "nanok/task.h"
#include "arch/exception_frame.h"

/* Return to Thread mode, exception return uses non-floating-point state from
 * the PSP and execution uses PSP after return */
#define EXC_RETURN_TO_THREAD    0xFFFFFFFD

/* This function is automatically called when a task returns from its entry
 * point */
__attribute__((naked)) static void
_task_return_cb(void)
{
  nk_terminate();
}

KAPI void
arch_task_setup(s_task *task)
{
   /*
    * We want to fill the following stack frame layout. This is specified
    * by the Cortex-m4 processor model.
    *
    * +-----------------------------+ <--- stack top       HIGH ADDR
    * | Task Start                  |
    * +-----------------------------+
    * | {alignment}                 |
    * +-----------------------------+
    * | xPSR                        |
    * +-----------------------------+
    * | PC                          |
    * +-----------------------------+
    * | LR                          |
    * +-----------------------------+
    * | R12                         |
    * +-----------------------------+
    * | R3                          |
    * +-----------------------------+
    * | R2                          |
    * +-----------------------------+
    * | R1                          |
    * +-----------------------------+
    * | R0                          |
    * +-----------------------------+
    * | ...                         |                      LOW ADDR
    *
    */

   /* Get the top of the task */
   uint32_t *const stack = task->stack;
   uint32_t *const stack_top = &(stack[task->stack_size / sizeof(uint32_t)]);

   /* PSP: program stack pointer, starting from the top of the task. From the
    * PSP we reserve the room to hold the exception frame. It is naturally
    * aligned by design. */
   const uint32_t psp = ((uint32_t) stack_top) - sizeof(s_exception_frame);

   /* Reserve a frame for the first exception return */
   s_exception_frame *const frame = (s_exception_frame *) psp;
   frame->r0 = UINT32_C(0);
   frame->r1 = UINT32_C(0);
   frame->r2 = UINT32_C(0);
   frame->r3 = UINT32_C(0);
   frame->r12 = UINT32_C(0);
   frame->lr = (uint32_t) &_task_return_cb;
   frame->pc = (uint32_t) task->start;

   /* xPSR: zeroed-out, except for the THUMB bit */
   frame->xpsr.w = UINT32_C(0);
   frame->xpsr.b.T = 1u;

   /* Fill-in the task context. This will be used by the kernel to control the
    * task's execution */
   s_task_context *const ctx = &(task->context);
   ctx->exc_return = EXC_RETURN_TO_THREAD;
   ctx->psp = psp;
}

KAPI void
arch_task_cleanup(s_task *task __unused__)
{
   /* Nothing to do */
}

static void
_idle_main(void)
{
   for (;;) { nk_yield(); }
}

NK_STACK_DEFINE(_idle_stack, 128);

s_task nk_idle_task =
{
   .start = _idle_main,
   .stack = _idle_stack,
   .stack_size = sizeof(_idle_stack),
   .status = NK_TASK_STATUS_INACTIVE,
   .priority = NK_TASK_PRIORITY_NORMAL,
};
