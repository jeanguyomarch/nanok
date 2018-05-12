#include "ky/scheduler.h"
#include "ky/assert.h"
#include "ky/task.h"
#include "ky/event.h"
#include "ky/init.h"

void
ky_init(void)
{
   arch_init();

   ky_event_init();
   ky_task_init();

   /* Initialize the scheduler. We shall have at least one task ready to be
    * run. It may be just the IDLE task, but we REQUIRE one task */
   ky_scheduler_init();
   KY_ASSERT(ky_scheduler_current_task_get() != NULL);
}
