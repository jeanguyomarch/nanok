#include "ky/scheduler.h"
#include "ky/assert.h"
#include "ky/task.h"
#include "ky/init.h"

void
ky_init(void)
{
   arch_init();

   ky_scheduler_init();
   KY_ASSERT(ky_scheduler_current_task_get() != NULL);
}
