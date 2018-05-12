#include "ky/task.h"
#include "ky/init.h"
#include "ky/syscall.h"

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

KAPI noreturn void
ky_assert_fail(const char *filename,
               unsigned long line,
               const char *failure)
{
   fprintf(stderr, "[%s:%lu] ASSERTION FAILED: %s\n",
           filename, line, failure);
   exit(EXIT_FAILURE);
}

static void
_task1(void)
{
   printf("This is task 1. I will return and die.\n");
}

static void
_task2(void)
{
   printf("This is task 2. I should have started after 1. I will yield now\n");
   yield();
   printf("This is task 2. I resumed after yield\n");
}

static void
_task3(void)
{
   printf("This is task 3. I should have started after 2\n");
   yield();
   printf("This is task 3. Task2 should have died now. I will yield\n");
   yield();
   printf("This is task 3. I'm done yielding. I'll stall\n");
   stall();
}


int
main(void)
{
   ky_init();
   ky_task_add(_task1, KY_TASK_PRIORITY_NORMAL);
   ky_task_add(_task2, KY_TASK_PRIORITY_NORMAL);
   ky_task_add(_task3, KY_TASK_PRIORITY_NORMAL);

   run();

   return EXIT_SUCCESS;
}
