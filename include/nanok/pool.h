/* NanoK - MIT License */

#ifndef NANOK_POOL_H__
#define NANOK_POOL_H__

#include "nanok/compiler.h"
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

#define NK_POOL_INIT(Storage)                           \
  {                                                     \
     .storage = (s_pool_item *) Storage,                \
     .head = (s_pool_item *) Storage,                   \
     .size = sizeof(Storage) / sizeof(Storage[0]),      \
     .elem_size = sizeof(Storage[0]),                   \
  };                                                    \
  _Static_assert(                                       \
      sizeof(Storage[0]) >= sizeof(void *),             \
      "Pool element size must be greater or than the size of a pointer"); \
  _Static_assert(                                       \
      sizeof(Storage) > sizeof(Storage[0]),             \
      "A pool must contain more than one element")



KAPI void nk_pool_init(s_pool *pool);
KAPI void *nk_pool_reserve(s_pool *pool);
KAPI void nk_pool_release(s_pool *pool, void *data);
KAPI void nk_pool_release_nth(s_pool *pool, size_t nth);
KAPI size_t nk_pool_index_get(const s_pool *pool, const void *data);

#endif /* ! NANOK_POOL_H__ */
