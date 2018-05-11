#include "ktest/ktest.h"

#include "ky/pool.h"

static uintptr_t _storage[8];
static s_pool _pool = KY_POOL_INITIALIZER(_storage);

static void
test_pool_init(void)
{
   ky_pool_init(&_pool);

   KTEST_ASSERT(_storage[0] == (uintptr_t) &_storage[1]);
   KTEST_ASSERT(_storage[1] == (uintptr_t) &_storage[2]);
   KTEST_ASSERT(_storage[2] == (uintptr_t) &_storage[3]);
   KTEST_ASSERT(_storage[3] == (uintptr_t) &_storage[4]);
   KTEST_ASSERT(_storage[4] == (uintptr_t) &_storage[5]);
   KTEST_ASSERT(_storage[5] == (uintptr_t) &_storage[6]);
   KTEST_ASSERT(_storage[6] == (uintptr_t) &_storage[7]);
   KTEST_ASSERT(_storage[7] == (uintptr_t) NULL);
}

static void
test_pool_reserve(void)
{
   void *data;

   /* Fill the whole pool. Since the pool was just initialized, allocation will
    * be consecutive */
   for (size_t i = 0u; i < 8u; i++)
     {
        data = ky_pool_reserve(&_pool);
        KTEST_ASSERT(data == &_storage[i]);
        KTEST_ASSERT(ky_pool_index_get(&_pool, data) == i);
     }

   /* Release the last fetched element, then fill the pool back. Repeat a bit.
    * Each time, we should have the last element reserved. */
   for (size_t i = 0u; i < 100u; i++)
     {
        ky_pool_release(&_pool, data);
        data = ky_pool_reserve(&_pool);
        KTEST_ASSERT(data == &_storage[7]);
        KTEST_ASSERT(ky_pool_index_get(&_pool, data) == 7u);
     }

   /* Release the first element. Then reserve. We should get the first element
    * back. */
   ky_pool_release_nth(&_pool, 0u);
   data = ky_pool_reserve(&_pool);
   KTEST_ASSERT(data == &_storage[0]);
   KTEST_ASSERT(ky_pool_index_get(&_pool, data) == 0u);
}

KTESTS(
   test_pool_init,
   test_pool_reserve,
)
