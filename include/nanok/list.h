/* NanoK - MIT License */

#ifndef NANOK_INLIST_H__
#define NANOK_INLIST_H__

#include "nanok/compiler.h"

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

#define NK_INLIST s_inlist inlist__
#define NK_INLIST_GET(Item) (&((Item)->inlist__))

#define NK_INLIST_INIT() { .next = NULL, .prev = NULL }
#define NK_LIST_INIT(List)                                      \
  {                                                             \
     .head.next = &(List.head),                                 \
     .head.prev = &(List.head),                                 \
     .count = 0u,                                               \
  }

#define NK_INLIST_ENTRY(Inlist, Type) container_of(Inlist, Type, inlist__)

#define NK_LIST_FOREACH(List, It) \
   for ((It) = (List)->head.next; (void*)(It) != (void*)(List); (It) = (It)->next)


static inline void
nk_inlist_setup(s_inlist *inlist)
{
   inlist->next = NULL;
   inlist->prev = NULL;
}

static inline void
nk_list_add_tail(s_list *list, s_inlist *inlist)
{
   inlist->next = &(list->head);
   inlist->prev = list->head.prev;

   list->head.prev->next = inlist;
   list->head.prev = inlist;

   list->count += 1u;
}

static inline void
nk_inlist_add_after(s_inlist *elem, s_inlist *to_add)
{
   to_add->next = elem->next;
   to_add->prev = elem;
   elem->next->prev = to_add;
   elem->next = to_add;
}

static inline void
nk_list_add_after(s_list *list, s_inlist *elem, s_inlist *to_add)
{
   nk_inlist_add_after(elem, to_add);
   list->count += 1u;
}

static inline void
nk_inlist_add_before(s_inlist *elem, s_inlist *to_add)
{
   to_add->next = elem;
   to_add->prev = elem->prev;
   elem->prev->next = to_add;
   elem->prev = to_add;
}

static inline void
nk_list_add_before(s_list *list, s_inlist *elem, s_inlist *to_add)
{
   nk_inlist_add_before(elem, to_add);
   list->count += 1u;
}

static inline void
nk_inlist_del(s_inlist *inlist)
{
   inlist->next->prev = inlist->prev;
   inlist->prev->next = inlist->next;
}

static inline void
nk_list_del_head(s_list *list)
{
   nk_inlist_del(list->head.next);
   list->count -= 1u;
}

static inline void
nk_list_del(s_list *list, s_inlist *inlist)
{
   nk_inlist_del(inlist);
   list->count -= 1u;
}

static inline size_t
nk_list_count(const s_list *list)
{
   return list->count;
}

static inline bool
nk_list_empty(const s_list *list)
{
   return nk_list_count(list) == 0u;
}

static inline s_inlist *
nk_list_first_get(s_list *list)
{
   return list->head.next;
}

#define NK_LIST_FIRST_ENTRY_GET(List, Type) \
  NK_INLIST_ENTRY((List)->head.next, Type)

#include "nanok/log.h"
static inline void
nk_list_dump(const s_list *list)
{
   s_inlist *l;
   arch_log_printf("list<%p> prev=%p next=%p of %zu elements\n",
                   list, list->head.prev, list->head.next, list->count);
   NK_LIST_FOREACH(list, l)
   {
      arch_log_printf("  %p <- %p -> %p\n",
                      l->prev, l, l->next);
   }
}

#endif /* ! NANOK_INLIST_H__ */
