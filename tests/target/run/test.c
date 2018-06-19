#include <nanok/task.h>
#include <nanok/init.h>
#include <nanok/log.h>
#include <nanok/syscall.h>
#include <nanok/assert.h>

#include <stm32f429i_discovery.h>

KAPI noreturn void
nk_assert_fail(const char *filename __unused__,
               unsigned long line __unused__,
               const char *failure)
{
   arch_log_puts(failure);
   for (;;) continue;
}

static volatile uint32_t _counter = UINT32_C(0);

static void
_task1(void)
{
   for (;;) {
      _counter += UINT32_C(1);
      nk_yield();
   }
}


static void
_task2(void)
{
   for (;;) {
      if (_counter % 200000 == 0)
      {
         arch_log_puts("Toggle led");
         BSP_LED_Toggle(LED3);
      }
      nk_yield();
   }
}

void
main(void)
{
  nk_init();

  BSP_LED_Init(LED3);

  nk_task_add(_task1);
  nk_task_add(_task2);

  nk_run();
}
