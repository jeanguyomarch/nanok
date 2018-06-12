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

static volatile uint32_t _counter = UINT32_C(0);

static void
_task1(void)
{
   //  ky_log_puts("This is task1");
   for (;;) {
      _counter += UINT32_C(1);
      ky_yield();
   }
}


static void
_task2(void)
{
   //   ky_log_puts("This is task2");
   for (;;) {
      if (_counter % 200000 == 0)
        BSP_LED_Toggle(LED3);
      ky_yield();
   }
}

void
main(void)
{
  ky_init();

  BSP_LED_Init(LED3);

  ky_task_add(_task1, KY_TASK_PRIORITY_NORMAL);
  ky_task_add(_task2, KY_TASK_PRIORITY_NORMAL);

  ky_run();
}
