/* NanoK - MIT License */

#include "nanok/pool.h"
#include <assert.h>

struct pool_item
{
   struct pool_item *next;
};


KAPI void
nk_pool_init(s_pool *pool)
{
   uint8_t *const storage = (uint8_t *)pool->storage;

   s_pool_item *prev = pool->storage;
   s_pool_item *next = prev; /* next is initialized to please the compiler */

   pool->head = prev;
   for (size_t i = 1u; i < pool->size; ++i)
     {
        next = (s_pool_item *) &(storage[i * pool->elem_size]);
        prev->next = next;
        prev = next;
     }
   next->next = NULL;
}

KAPI void *
nk_pool_reserve(s_pool *pool)
{
   s_pool_item *const old_head = pool->head;

   assert(old_head != NULL);

   pool->head = old_head->next;

   return old_head;
}

KAPI void
nk_pool_release(s_pool *pool,
                void *data)
{
   s_pool_item *const item = data;

   assert((item >= pool->storage) &&
          (item < pool->storage + (pool->size * pool->elem_size)));

   s_pool_item *const old_head = pool->head;
   pool->head = item;
   item->next = old_head;
}

KAPI void
nk_pool_release_nth(s_pool *pool,
                    size_t nth)
{
   uint8_t *const storage = (uint8_t *) pool->storage;
   void *const item = &(storage[nth * pool->elem_size]);
   nk_pool_release(pool, item);
}

KAPI size_t
nk_pool_index_get(const s_pool *pool,
                  const void *data)
{
   const uint8_t *const item = data;
   const uint8_t *const storage = (const uint8_t *) pool->storage;

   assert((item >= storage) &&
          (item < storage + (pool->size * pool->elem_size)));

   return (size_t)(item - storage) / pool->elem_size;
}
