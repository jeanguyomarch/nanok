#ifndef KY_INLIST_H__
#define KY_INLIST_H__

#include "ky/compiler.h"

#include <stddef.h>
#include <stdbool.h>

typedef struct inlist s_inlist;

struct inlist
{
   s_inlist *next;
   s_inlist *prev;
};

typedef struct
{
   s_inlist head;
   size_t count;
} s_list;

#define KY_INLIST s_inlist inlist__
#define KY_INLIST_GET(Item) (&((Item)->inlist__))

#define KY_INLIST_INIT() { .next = NULL, .prev = NULL }
#define KY_LIST_INIT(List)                                      \
  {                                                             \
     .head.next = &(List.head),                                 \
     .head.prev = &(List.head),                                 \
     .count = 0u,                                               \
  }

#define KY_INLIST_ENTRY(Inlist, Type) container_of(Inlist, Type, inlist__)

#define KY_LIST_FOREACH(List, It) \
   for ((It) = (List)->head.next; (void*)(It) != (void*)(List); (It) = (It)->next)


static inline void
ky_inlist_init(s_inlist *inlist)
{
   inlist->next = NULL;
   inlist->prev = NULL;
}

static inline void
ky_list_add_tail(s_list *list, s_inlist *inlist)
{
   inlist->next = &(list->head);
   inlist->prev = list->head.prev;

   list->head.prev->next = inlist;
   list->head.prev = inlist;

   list->count += 1u;
}

static inline void
ky_inlist_del(s_inlist *inlist)
{
   inlist->next->prev = inlist->prev;
   inlist->prev->next = inlist->next;
   ky_inlist_init(inlist);
}

static inline void
ky_list_del_head(s_list *list)
{
   ky_inlist_del(list->head.next);
   list->count -= 1u;
}

static inline void
ky_list_del(s_list *list, s_inlist *inlist)
{
   ky_inlist_del(inlist);
   list->count -= 1u;
}

static inline size_t
ky_list_count(const s_list *list)
{
   return list->count;
}

static inline bool
ky_list_empty(const s_list *list)
{
   return ky_list_count(list) == 0u;
}

static inline s_inlist *
ky_list_first_get(s_list *list)
{
   return list->head.next;
}

#define KY_LIST_FIRST_ENTRY_GET(List, Type) \
  KY_INLIST_ENTRY((List)->head.next, Type)

#include "ky/log.h"
static inline void
ky_list_dump(const s_list *list)
{
   s_inlist *l;
   ky_log_printf("list<%p> prev=%p next=%p of %zu elements\n",
                 list, list->head.prev, list->head.next, list->count);
   KY_LIST_FOREACH(list, l)
   {
      ky_log_printf("  %p <- %p -> %p\n",
                    l->prev, l, l->next);
   }
}

#endif /* ! KY_INLIST_H__ */
