/* NanoK - MIT License */

#include "nanok/scheduler.h"
#include "nanok/task.h"
#include "nanok/event.h"
#include "nanok/init.h"

KAPI void
nk_init(void)
{
   arch_init();

   arch_log_init();

   nk_event_init();
   nk_task_init();
   nk_scheduler_init();
}
