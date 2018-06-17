#include "kstub/kstub.h"

#include "nanok/task.h"
#include "nanok/init.h"
#include "nanok/syscall.h"

KSTUB_ASSERT_HANDLER();

typedef enum
{
   EVENT_TASK_1,
   EVENT_TASK_2_BEFORE_YIELD,
   EVENT_TASK_2_AFTER_YIELD,
   EVENT_TASK_3_BEFORE_YIELD_0,
   EVENT_TASK_3_BEFORE_YIELD_1,
   EVENT_TASK_3_AFTER_YIELD_1,
} e_event;

static const e_event _expected_events[] =
{
   EVENT_TASK_1,
   EVENT_TASK_2_BEFORE_YIELD,
   EVENT_TASK_3_BEFORE_YIELD_0,
   EVENT_TASK_2_AFTER_YIELD,
   EVENT_TASK_3_BEFORE_YIELD_1,
   EVENT_TASK_3_AFTER_YIELD_1,
};

static e_event _events[ARRAY_SIZE(_expected_events)];
static size_t _index = 0u;

#define EVENT(Evt) \
   do { \
      printf("%s: %s\n", __func__, #Evt); \
      _events[_index++] = (Evt); \
   } while (0)

static void
_task1(void)
{
   EVENT(EVENT_TASK_1);
}

static void
_task2(void)
{
   EVENT(EVENT_TASK_2_BEFORE_YIELD);
   nk_yield();
   EVENT(EVENT_TASK_2_AFTER_YIELD);
}

static void
_task3(void)
{
   EVENT(EVENT_TASK_3_BEFORE_YIELD_0);
   nk_yield();
   EVENT(EVENT_TASK_3_BEFORE_YIELD_1);
   nk_yield();
   EVENT(EVENT_TASK_3_AFTER_YIELD_1);
   nk_stall();
}


int
main(void)
{
   nk_init();
   nk_task_add(_task1, NK_TASK_PRIORITY_NORMAL);
   nk_task_add(_task2, NK_TASK_PRIORITY_NORMAL);
   nk_task_add(_task3, NK_TASK_PRIORITY_NORMAL);

   nk_run();

   return EXIT_SUCCESS;
}
