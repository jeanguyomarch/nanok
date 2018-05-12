#ifndef KY_INLIST_H__
#define KY_INLIST_H__

#include "ky/compiler.h"

#include <stddef.h>

typedef struct inlist s_inlist;

struct inlist
{
   s_inlist *next;
};

typedef struct
{
   s_inlist head;
   s_inlist tail;
   size_t count;
} s_list;

#define KY_INLIST s_inlist inlist__
#define KY_INLIST_GET(Item) (&((Item)->inlist__))

#define KY_INLIST_INIT() { .next = NULL, }
#define KY_LIST_INIT(List) { .head.next = NULL, .tail.next = &List.head, .count = 0u }

static inline void
ky_inlist_init(s_inlist *inlist)
{
   inlist->next = NULL;
}

static inline void
ky_list_add_tail(s_list *list, s_inlist *inlist)
{
   list->tail.next->next = inlist;
   list->tail.next = inlist;
   inlist->next = NULL;
   list->count += 1u;
}

static inline void
ky_list_del_head(s_list *list)
{
   list->head.next = list->head.next->next;
   list->count -= 1u;
}

static inline size_t
ky_list_count(const s_list *list)
{
   return list->count;
}

//static inline void
//ky_list_init(s_list *list)
//{
//   list->head.next = NULL;
//   list->tail.next = &list->head.next;
//}

#define KY_INLIST_ENTRY(Inlist, Type) container_of(Inlist, Type, inlist__)

#define KY_LIST_FOREACH(List, It) \
  for ((It) = (List)->head.next; (It) != NULL; (It) = (It)->next)


#endif /* ! KY_INLIST_H__ */
