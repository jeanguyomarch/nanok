===============================================================================
NanoK Design
===============================================================================

Scheduling
-------------------------------------------------------------------------------

NanoK uses a **cooperative** scheduling. It means that once a task hsa been
scheduled, it is **responsible** to give back the hand to the scheduler.
Otherwise, it will consume the whole CPU time, and other tasks will not get a
chance to execute. This approach has its downsides, but allows the developer of
an application to clearly separate its application into unitary actions that
will be executed in one go, without ever being pre-empted.

The scheduler that operates beind the hood is by itself extremely simple, as
all operations are performed in :math:`o(1)`, without involving unbounded
loops. Which means the scheduling is guaranteed to execute in a finite amount
of time.

When an application enters its *running* state, the scheduler will go through
the **scheduling ring**, which collects all the tasks that may be elected. The
initial state of the scheduling ring is determined by the order of task
creations before NanoK enters in run-mode (i.e. calling ``nk_run()``). The
first created task will end up first in the scheduling ring. The last task in
the scheduling ring is guaranteed to always be the **idle task**, which will
execute when no other task can be elected.

The topmost task in the scheduling ring is the next task to be elected. Once a
task is elected, it is removed from the scheduling ring.  Once a task has
completed the execution of a code fragment, it shall give back the hand to the
scheduler. A task has two ways to perform this:

* by calling ``nk_yield()``, which is a **best-effort strategy**: the task is
  immediately placed at the end of the scheduling ring, *before the idle task*,
  which means it will be re-scheduled before the idle task.
* or by calling ``nk_await()``, in which case the task will be put back in
  the scheduling ring only if the event passed to ``nk_await()`` has been
  triggered by another task.

The ``nk_yield()`` paradigm is shown in figure below:

.. figure:: _assets/nk_sched_1.png
   :alt: Yield-based scheduling illustration

   Example of the ``nk_yield()`` behavior

Note the differences with ``nk_await()``-based mechanisms:


.. figure:: _assets/nk_sched_2.png
   :alt: Await-based scheduling illustration

   Example of the ``nk_await()`` behavior
