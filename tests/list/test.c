#include "ktest/ktest.h"

#include "ky/list.h"

typedef struct
{
   KY_INLIST;
   size_t id;
} s_item;

static s_item _items[8];
static s_list _list = KY_LIST_INIT(_list);

static void
test_list_init(void)
{
   for (size_t i = 0u; i < 8u; i++)
     {
        s_item *const item = &(_items[i]);
        ky_inlist_init(KY_INLIST_GET(item));
        item->id = i;
     }
}

static void
_list_content_expect(size_t len, const size_t data[len])
{
   KTEST_ASSERT(len == ky_list_count(&_list));

   size_t it = 0u;
   s_inlist *l;
   KY_LIST_FOREACH(&_list, l)
     {
        s_item *const item = KY_INLIST_ENTRY(l, s_item);
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
        ky_list_add_tail(&_list, KY_INLIST_GET(item));
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
        ky_list_del_head(&_list);
        _list_content_expect(8u - i, expect);
     }

   /* Add some more elements. We shall have:
    * 7 -> 2 -> 5
    */
   ky_list_add_tail(&_list, KY_INLIST_GET(&_items[2]));
   ky_list_add_tail(&_list, KY_INLIST_GET(&_items[5]));
   const size_t expected_1[] = { 7u, 2u, 5u, };
   _list_content_expect(3u, expected_1);
}

KTESTS(
   test_list_init,
   test_list_add_tail_del_head,
)
