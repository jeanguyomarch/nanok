#ifndef ARCH_TASK_H__
#define ARCH_TASK_H__

#include <ucontext.h>

typedef struct
{
   ucontext_t uctx;
   void *stack;
} s_task_context;

#endif /* ! ARCH_TASK_H__ */
