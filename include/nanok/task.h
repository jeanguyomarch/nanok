/* NanoK - MIT License */

#ifndef NANOK_TASK_H__
#define NANOK_TASK_H__

#include "nanok/list.h"
#include "nanok/compiler.h"
#include "arch/task.h"
#include "arch/types.h"

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

#define NK_STACK_DEFINE(StackName, StackSize)                           \
  _Static_assert((StackSize) % sizeof(t_stack_alignment) == 0,          \
                 "Stacks must be aligned on t_stack_alignment");        \
  static _Alignas(t_stack_alignment)                                    \
  t_stack_alignment StackName[(StackSize) / sizeof(t_stack_alignment)]

typedef void (*f_task)(void);

typedef struct
{
   NK_INLIST;

   s_task_context context;

   f_task start;
   t_stack_alignment *stack;
   size_t stack_size;

} s_task;

KAPI void nk_task_init(void);
KAPI s_task *nk_task_add(f_task start);
KAPI void nk_task_del(s_task *task);
KAPI void arch_task_setup(s_task *task);
KAPI void arch_task_cleanup(s_task *task);

#endif /* ! NANOK_TASK_H__ */
