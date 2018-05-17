#include <ky/init.h>
#include <ky/syscall.h>
#include <ky/task.h>

#include <stm32f4xx.h>

typedef struct __attribute__((packed))
{
   uint32_t r0;
   uint32_t r1;
   uint32_t r2;
   uint32_t r3;
   uint32_t r12;
   uint32_t lr;
   uint32_t pc;
   xPSR_Type xpsr;
   /* XXX If the FPU is enabled, more elements are required */
} s_exception_frame;

/* Return to Thread mode, exception return uses non-floating-point state from
 * the PSP and execution uses PSP after return */
#define EXC_RETURN_TO_THREAD    0xFFFFFFFD

/* This function is automatically called when a task returns from its entry
 * point */
__attribute__((naked)) static void
_task_return_cb(void)
{
  ky_terminate();
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

   /* PSP: program stack pointer, starting from the top of the task. The first
    * 32-bits is used to hold the entry point of the program */
   uint32_t psp = ((uint32_t) stack_top) - sizeof(uint32_t);
   *((uint32_t *)psp) = (uint32_t) task->start;

   /* Reserve a frame for the first exception return */
   psp &= 0xFFFFFFF8; /* Alignment */
   psp -= sizeof(s_exception_frame);
   s_exception_frame *const frame = (s_exception_frame *) psp;
   frame->r0 = UINT32_C(0);
   frame->r1 = UINT32_C(0);
   frame->r2 = UINT32_C(0);
   frame->r3 = UINT32_C(0);
   frame->r12 = UINT32_C(0);
   frame->lr = (uint32_t) (&_task_return_cb);
   frame->pc = UINT32_C(0);

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
   for (;;) { ky_yield(); }
}

static t_stack_alignment _idle_stack[32];

s_task ky_idle_task =
{
   .start = _idle_main,
   .stack = _idle_stack,
   .stack_size = sizeof(_idle_stack),
   .status = KY_TASK_STATUS_INACTIVE,
   .priority = KY_TASK_PRIORITY_NORMAL,
};
