/* NanoK - MIT License */

#include "nanok/task.h"
#include "nanok/syscall.h"
#include "nanok/log.h"

#include <assert.h>
#include <stdlib.h>

static void
_runner(f_task task_start)
{
   task_start();

   /* The functions will always end with the 'end' syscall, which will properly
    * destroy the task */
   nk_terminate();
}

static const size_t _stack_size = 8u * (1u << 20u); /* 8 MiB */

static inline uint8_t *
_stack_new(void)
{
   return malloc(_stack_size);
}

KAPI void
arch_task_setup(s_task *task)
{
   ucontext_t *const ctx = &(task->context.uctx);

   /* For the PC arch, we create our own stacks, of a much bigger size */
   task->context.stack = _stack_new();
   ctx->uc_stack.ss_sp = task->context.stack;
   ctx->uc_stack.ss_size = _stack_size;

   const int ret = getcontext(ctx);
   assert(ret == 0);
   makecontext(ctx, (void(*)()) _runner, 1, task->start);
}

KAPI void
arch_task_cleanup(s_task *task __unused__)
{
   // FIXME
   //free(task->context.stack);
}

KAPI void
arch_init(void)
{
}
