#include "ktest/ktest.h"

#include "nanok/list.h"

typedef struct
{
   NK_INLIST;
   size_t id;
} s_item;

static s_item _items[8];
static s_list _list = NK_LIST_INIT(_list);

static void
test_list_init(void)
{
   for (size_t i = 0u; i < 8u; i++)
     {
        s_item *const item = &(_items[i]);
        nk_inlist_setup(NK_INLIST_GET(item));
        item->id = i;
     }
}

static void
_list_content_expect(size_t len, const size_t data[len])
{
   KTEST_ASSERT(len == nk_list_count(&_list));

   size_t it = 0u;
   s_inlist *l;
   NK_LIST_FOREACH(&_list, l)
     {
        s_item *const item = NK_INLIST_ENTRY(l, s_item);
        KTEST_ASSERT(item->id == data[it]);
        it += 1u;
     }
}

static void
test_list_add_tail_del_head(void)
{
   /* Add all elements so we end up with the following chain:
    * 0 -> 1 -> 2 -> 3 -> 4 -> 5 -> 6 -> 7
    */
   for (size_t i = 0u; i < 8u; i++)
     {
        s_item *const item = &(_items[i]);
        nk_list_add_tail(&_list, NK_INLIST_GET(item));
     }
   const size_t expected_0[] = { 0u, 1u, 2u, 3u, 4u, 5u, 6u, 7u, };
   _list_content_expect(8, expected_0);

   /* Delete the head until we have only one eleement. We shall have
    * 1 -> 2 -> 3 -> 4 -> 5 -> 6 -> 7
    * 2 -> 3 -> 4 -> 5 -> 6 -> 7
    * ...
    * 7
    */
   for (size_t i = 1u; i <= 7u; i++)
     {
        const size_t *const expect = &(expected_0[i]);
        nk_list_del_head(&_list);
        _list_content_expect(8u - i, expect);
     }

   /* Add some more elements. We shall have:
    * 7 -> 2 -> 5
    */
   nk_list_add_tail(&_list, NK_INLIST_GET(&_items[2]));
   nk_list_add_tail(&_list, NK_INLIST_GET(&_items[5]));
   const size_t expected_1[] = { 7u, 2u, 5u, };
   _list_content_expect(3u, expected_1);

   /* Remove all three elements. We shall end with zero element */
   nk_list_del_head(&_list);
   nk_list_del_head(&_list);
   nk_list_del_head(&_list);

   /* Add some elements back:
    * 7 -> 6 -> 4
    */
   nk_list_add_tail(&_list, NK_INLIST_GET(&_items[7]));
   nk_list_add_tail(&_list, NK_INLIST_GET(&_items[6]));
   nk_list_add_tail(&_list, NK_INLIST_GET(&_items[4]));
   const size_t expected_2[] = { 7u, 6u, 4u, };
   _list_content_expect(3u, expected_2);
}

KTESTS(
   test_list_init,
   test_list_add_tail_del_head,
)
