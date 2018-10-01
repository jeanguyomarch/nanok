#include "kstub/kstub.h"

#include "nanok/task.h"
#include "nanok/init.h"
#include "nanok/syscall.h"

#define EVENT(Evt) \
  printf("%s: %s\n", __func__, Evt)

static void
_task1(void)
{
   EVENT("start, will end");
}

static void
_task2(void)
{
   EVENT("start, before yield");
   nk_yield();
   EVENT("after yield");
}

static void
_task3(void)
{
   EVENT("start, before yield");
   nk_yield();
   EVENT("inbetween yields");
   nk_yield();
   EVENT("after yield, will stall");
   nk_stall();
}


int
main(void)
{
   nk_init();
   nk_task_add(_task1);
   nk_task_add(_task2);
   nk_task_add(_task3);

   nk_run();

   return EXIT_SUCCESS;
}
