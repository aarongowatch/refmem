#ifndef __REFMEM_H__
#define __REFMEM_H__

#include <stdlib.h>

#include "refmem_allocator.h"
#include "refmem_atomic.h"

typedef void (refmem_cleanup_func_t)(void *);

typedef struct {
    refmem_atomic_t retain_count;
    refmem_cleanup_func_t *cleanup;
    void *ctx;
} refmem_t;

void *refmem_malloc(size_t size);
void *refmem_malloc_ex(size_t size, refmem_allocator_t *allocator, void *ctx);

void *refmem_calloc(size_t count, size_t size);
void *refmem_calloc_ex(size_t count, size_t size, refmem_allocator_t *allocator, void *ctx);

void *refmem_retain(void *);
void *refmem_release(void *);

static inline void refmem_init(refmem_t *refmem, refmem_cleanup_func_t *f, void *ctx)
{
    refmem_atomic_set(&refmem->retain_count, 1);
    refmem->cleanup = f;
    refmem->ctx     = ctx;
}

static inline void refmem_retain_ex(refmem_t *refmem)
{
    refmem_atomic_increment(&refmem->retain_count);
}

static inline int refmem_release_ex(refmem_t *refmem)
{
    if (refmem_atomic_decrement_and_test(&refmem->retain_count))
    {
        if (refmem->cleanup)
            refmem->cleanup(refmem->ctx);

        return 1;
    }

    return 0;
}

#endif // __REFMEM_H__
