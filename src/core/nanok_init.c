/* NanoK - MIT License */

#include "nanok/scheduler.h"
#include "nanok/assert.h"
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

   /* Initialize the scheduler. We shall have at least one task ready to be
    * run. It may be just the IDLE task, but we REQUIRE one task */
   nk_scheduler_init();
}
