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

typedef enum
{
   NK_TASK_STATUS_INACTIVE = 0x1A,
   NK_TASK_STATUS_ACTIVE = 0x32,
   NK_TASK_STATUS_WAITING = 0x2C,
} e_task_status;

typedef enum
{
   NK_TASK_PRIORITY_NORMAL = 0x08,
   NK_TASK_PRIORITY_URGENT = 0x24,
} e_task_priority;

typedef struct
{
   NK_INLIST;

   s_task_context context;

   f_task start;
   t_stack_alignment *stack;
   size_t stack_size;
   e_task_status status;
   e_task_priority priority;

} s_task;

KAPI void nk_task_init(void);
KAPI s_task *nk_task_add(f_task start, e_task_priority priority);
KAPI void nk_task_del(s_task *task);
KAPI void arch_task_setup(s_task *task);
KAPI void arch_task_cleanup(s_task *task);

KAPI extern s_task nk_idle_task;

#endif /* ! NANOK_TASK_H__ */
