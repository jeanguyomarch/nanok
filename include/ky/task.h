#ifndef KY_TASK_H__
#define KY_TASK_H__

#include "ky/list.h"
#include "ky/compiler.h"
#include "ky/object.h"

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

typedef void *(*f_task)(void *data);

typedef enum
{
   KY_TASK_STATUS_PAUSED = 0x1A,
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

   const char *const name;
   const f_task start;

   uint8_t *stack;
   const size_t stack_size;

   e_task_status status;
   const e_task_priority priority;

} s_task;

t_object_id ky_task_id_get(const s_task *task);

extern s_task ky_tasks[];
extern const size_t ky_tasks_count;




#endif /* ! KY_TASK_H__ */
