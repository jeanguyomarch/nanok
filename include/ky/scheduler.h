#ifndef KY_SCHEDULER_H__
#define KY_SCHEDULER_H__

#include "ky/object.h"

void ky_scheduler_wake(t_object_id task_id);
void ky_scheduler_pause(t_object_id task_id);
t_object_id ky_scheduler_current_task_id_get(void);

#endif /* ! KY_SCHEDULER_H__ */
