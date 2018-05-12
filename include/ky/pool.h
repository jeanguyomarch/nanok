#ifndef KY_POOL_H__
#define KY_POOL_H__

#include <stddef.h>
#include <stdint.h>

typedef struct pool_item s_pool_item;

typedef struct
{
   s_pool_item *const storage;
   s_pool_item *head;
   const size_t elem_size;
   const size_t size;
} s_pool;

#define KY_POOL_INITIALIZER(Storage)                    \
  {                                                     \
     .storage = (s_pool_item *) Storage,                \
     .size = sizeof(Storage) / sizeof(Storage[0]),      \
     .elem_size = sizeof(Storage[0]),                   \
     .head = (s_pool_item *) Storage,                   \
  };                                                    \
  _Static_assert(                                       \
      sizeof(Storage[0]) >= sizeof(void *),             \
      "Pool element size must be greater or than the size of a pointer")


void ky_pool_init(s_pool *pool);
void *ky_pool_reserve(s_pool *pool);
void ky_pool_release(s_pool *pool, void *data);
void ky_pool_release_nth(s_pool *pool, size_t nth);
size_t ky_pool_index_get(const s_pool *pool, const void *data);

#endif /* ! KY_POOL_H__ */
