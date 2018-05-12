#ifndef KY_SCHEDULER_H__
#define KY_SCHEDULER_H__

#include "ky/task.h"

void ky_scheduler_init(void);
void ky_scheduler_add(s_task *task);
void ky_scheduler_del(s_task *task);

s_task *ky_scheduler_schedule(void);
s_task *ky_scheduler_current_task_get(void);

#endif /* ! KY_SCHEDULER_H__ */
