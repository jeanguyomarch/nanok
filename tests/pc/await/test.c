#include "kstub/kstub.h"

#include "nanok/task.h"
#include "nanok/init.h"
#include "nanok/syscall.h"
#include "nanok/event.h"

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

   nk_event_trigger(_prod_to_1);
   nk_event_trigger(_prod_to_2);

   MSG("Done. I'll now wait for reader 2 to end");
   nk_await(_reader_2_ended);

   MSG("Reader 2 shall be dead. I'll send event 1 a second time");
   nk_event_trigger(_prod_to_1);

   MSG("Done. I'll wait for reader 1 to end");
   nk_await(_reader_1_ended);

   MSG("I'll send a termination signal, then end");
   nk_event_trigger(_prod_end_evt);
}

static void
_reader_1(void)
{
   MSG("Awaiting event 1");
   nk_await(_prod_to_1);

   MSG("I received event 1. Waiting again");
   nk_await(_prod_to_1);

   MSG("Second event received. Will end now.");
   nk_event_trigger(_reader_1_ended);
}

static void
_reader_2(void)
{
   MSG("Awaiting event 2");
   nk_await(_prod_to_2);
   MSG("Event 2 received. Will end now");
   nk_event_trigger(_reader_2_ended);
}

static void
_sentinel(void)
{
   MSG("Awaiting for end event");
   nk_await(_prod_end_evt);

   MSG("End event received. Stalling...");
   nk_stall();
}


int
main(void)
{
   nk_init();

   _prod_to_1 = nk_event_new();
   _prod_to_2 = nk_event_new();
   _reader_1_ended = nk_event_new();
   _reader_2_ended = nk_event_new();
   _prod_end_evt = nk_event_new();

   nk_task_add(_reader_1);
   nk_task_add(_reader_2);
   nk_task_add(_producer);
   nk_task_add(_sentinel);

   nk_run();

   return EXIT_SUCCESS;
}
