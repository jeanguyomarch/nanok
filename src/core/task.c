#include "ky/task.h"

t_object_id
ky_task_id_get(const s_task *task)
{
   return (t_object_id)(task - ky_tasks);
}
