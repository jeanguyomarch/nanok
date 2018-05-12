#ifndef KY_EVENT_H__
#define KY_EVENT_H__

#include "ky/object.h"

typedef struct event s_event;

s_event *ky_event_new(void);
void ky_event_bind(s_event *event, t_object_id task_id);
void ky_event_trigger(s_event *event);

#endif /* KY_EVENT_H__ */
