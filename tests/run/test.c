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
   for (;;)
     {
        printf("This is task 1\n");
        sleep(1);
        stall();
     }
}

int
main(void)
{
   ky_init();
   //ky_task_add(_task1, KY_TASK_PRIORITY_NORMAL);

   run();
   return 0;
}
