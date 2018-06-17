/* NanoK - MIT License */

#ifndef NANOK_SCHEDULER_H__
#define NANOK_SCHEDULER_H__

#include "nanok/task.h"

KAPI void nk_scheduler_init(void);
KAPI void nk_scheduler_add(s_task *task);
KAPI void nk_scheduler_del(s_task *task);

KAPI s_task *nk_scheduler_schedule(void);
KAPI s_task *nk_scheduler_current_task_get(void);

#endif /* ! NANOK_SCHEDULER_H__ */
