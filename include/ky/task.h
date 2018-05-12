#ifndef KY_TASK_H__
#define KY_TASK_H__

#include "ky/list.h"
#include "ky/compiler.h"
#include "ky/object.h"
#include "arch/task.h"

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

typedef void (*f_task)(void);

typedef enum
{
   KY_TASK_STATUS_INACTIVE = 0x1A,
   KY_TASK_STATUS_ACTIVE = 0x32,
} e_task_status;

typedef enum
{
   KY_TASK_PRIORITY_NORMAL = 0x08,
   KY_TASK_PRIORITY_URGENT = 0x24,
} e_task_priority;

typedef struct
{
   KY_INLIST;

   s_task_context context;

   f_task start;
   uint8_t *stack;
   size_t stack_size;
   e_task_status status;
   e_task_priority priority;

} s_task;

KAPI s_task *ky_task_add(f_task start, e_task_priority priority);
KAPI void ky_task_del(s_task *task);
KAPI void arch_task_setup(s_task *task);
KAPI void arch_task_cleanup(s_task *task);

KAPI extern s_task ky_idle_task;


#endif /* ! KY_TASK_H__ */
