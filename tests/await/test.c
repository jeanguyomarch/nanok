#include "kstub/kstub.h"

#include "ky/task.h"
#include "ky/init.h"
#include "ky/syscall.h"
#include "ky/event.h"

KSTUB_ASSERT_HANDLER();

static s_event *_prod_to_1;
static s_event *_prod_to_2;
static s_event *_prod_end_evt;
static s_event *_reader_1_ended;
static s_event *_reader_2_ended;

#define MSG(Fmt, ...)  printf("%s: " Fmt "\n", __func__, ## __VA_ARGS__)

static void
_producer(void)
{
   MSG("Hi, I'm the producer. I'll emit events 1 & 2");

   ky_event_trigger(_prod_to_1);
   ky_event_trigger(_prod_to_2);

   MSG("Done. I'll now wait for reader 2 to end");
   ky_await(_reader_2_ended);

   MSG("Reader 2 shall be dead. I'll send event 1 a second time");
   ky_event_trigger(_prod_to_1);

   MSG("Done. I'll wait for reader 1 to end");
   ky_await(_reader_1_ended);

   MSG("I'll send a termination signal, then end");
   ky_event_trigger(_prod_end_evt);
}

static void
_reader_1(void)
{
   MSG("Awaiting event 1");
   ky_await(_prod_to_1);

   MSG("I received event 1. Waiting again");
   ky_await(_prod_to_1);

   MSG("Second event received. Will end now.");
   ky_event_trigger(_reader_1_ended);
}

static void
_reader_2(void)
{
   MSG("Awaiting event 2");
   ky_await(_prod_to_2);
   MSG("Event 2 received. Will end now");
   ky_event_trigger(_reader_2_ended);
}

static void
_sentinel(void)
{
   MSG("Awaiting for end event");
   ky_await(_prod_end_evt);

   MSG("End event received. Stalling...");
   ky_stall();
}


int
main(void)
{
   ky_init();

   _prod_to_1 = ky_event_repeated_new();
   _prod_to_2 = ky_event_new();
   _reader_1_ended = ky_event_new();
   _reader_2_ended = ky_event_new();
   _prod_end_evt = ky_event_new();

   ky_task_add(_reader_1, KY_TASK_PRIORITY_NORMAL);
   ky_task_add(_reader_2, KY_TASK_PRIORITY_NORMAL);
   ky_task_add(_producer, KY_TASK_PRIORITY_NORMAL);
   ky_task_add(_sentinel, KY_TASK_PRIORITY_NORMAL);

   ky_run();

   return EXIT_SUCCESS;
}

