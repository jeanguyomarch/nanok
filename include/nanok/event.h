/* NanoK - MIT License */
/**
 * \file nanok/event.h
 * \brief Tasks Inter-Event Module
 *
 * After a call to await(), the task will sleep until the event associated to
 * the await() action has been triggered by nk_event_trigger().  Once an event
 * has been dynamically reserved by nk_event_new() - in which case it must
 * explicitely be released by nk_event_free() when done, or initialized with
 * nk_event_setup(), the event can be bound to a given task with
 * nk_event_bind().
 *
 * @{
 */

#ifndef NANOK_EVENT_H__
#define NANOK_EVENT_H__

#include "nanok/compiler.h"
#include "nanok/scheduler.h"
#include "nanok/task.h"

/** Opaque type that represents an event */
typedef struct event s_event;

/** Structure that descrives an event */
struct event
{
   s_task *task; /**< Pointer to the task to receive the event */
};


/**
 * Initializes the event module. This shall be called by nk_init() at the boot
 * of the kernel.
 */
KAPI void nk_event_init(void);

/**
 * Dynamically reserves an event and initializes it.
 *
 * There is a statically allocated memory pools of events. If you reclaim too
 * much events, you will raise a fatal out-of-memory error.
 *
 * When done with the event, use nk_event_free() to release it.
 *
 * \return A pointer to a memory region that describes an event
 *
 * \see nk_event_setup()
 * \see nk_event_free()
 */
KAPI s_event *nk_event_new(void);

/**
 * Initializes memory allocated to handle an event.
 *
 * This is typically used by nk_event_new(). Use this function if you maintain
 * your own event storage.
 *
 * \param[in] event Pointer to the memory region dedicated to an event.
 */
KAPI void nk_event_setup(s_event *event);

/**
 * Release an event allocated by nk_event_new()
 *
 * \param[in] event Pointer to the memory region dedicated to an event.
 *
 * \warning If \p event was not returned by nk_event_new(), the behavior of
 *   this function is undefined
 */
KAPI void nk_event_free(s_event *event);

/**
 * Trigger an event. This will make a task in await state bound to the event \p
 * event to be placed in the scheduling queue.
 *
 * \param[in] event Pointer to the memory region dedicated to an event.
 */
KAPI void nk_event_trigger(const s_event *event);

/**
 * Bind an event to a given task.
 *
 * When the task \p task will enter in a await state, it can be awoken when the
 * event \p event is trigger by a later call to nk_event_trigger().
 *
 * \param[in] event Pointer to the memory region dedicated to an event.
 * \param[in] task Pointer to the memory region that describes a task
 */
KAPI void nk_event_bind(s_event *event, s_task *task);

#endif /* NANOK_EVENT_H__ */ /** @} */
