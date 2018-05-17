#include <ky/task.h>
#include <ky/init.h>
#include <ky/log.h>
#include <ky/syscall.h>
#include <ky/assert.h>

#include <stm32f429i_discovery.h>

KAPI noreturn void
ky_assert_fail(const char *filename __unused__,
               unsigned long line __unused__,
               const char *failure)
{
   ky_log_puts(failure);
   for (;;) continue;
}

static void
_task1(void)
{
   ky_log_puts("This is task1");
}

static void
_task2(void)
{
   ky_log_puts("This is task2");
}

void
main(void)
{
  ky_init();

  BSP_LED_Init(LED3);

  BSP_LED_Toggle(LED3);
  volatile uint32_t counter = 0;
  for (;;) {
     ++counter;
     if (counter % 200000 == 0)
        {
           BSP_LED_Toggle(LED3);
        }

  }

//  ky_task_add(_task1, KY_TASK_PRIORITY_NORMAL);
//  ky_task_add(_task2, KY_TASK_PRIORITY_NORMAL);
//
//  ky_run();
}
