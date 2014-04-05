#ifndef __REFMEM_H__
#define __REFMEM_H__

#include "refmem_atomic.h"

typedef void (refmem_cleanup_func_t)(void *);

typedef struct {
    refmem_atomic_t retain_count;
    refmem_cleanup_func_t *cleanup;
    void *ctx;
} refmem_t;

static inline void refmem_init(refmem_t *refmem, refmem_cleanup_func_t *cleanup, void *ctx)
{
    refmem_atomic_set(&refmem->retain_count, 1);
    refmem->cleanup = cleanup;
    refmem->ctx     = ctx;
}

static inline void refmem_retain(refmem_t *refmem)
{
    refmem_atomic_increment(&refmem->retain_count);
}

static inline int refmem_release(refmem_t *refmem)
{
    if (refmem_atomic_decrement_and_test(&refmem->retain_count))
    {
        if (refmem->cleanup)
            refmem->cleanup(refmem->ctx);

        return 1;
    }

    return 0;
}

#endif /* __REFMEM_H__ */
