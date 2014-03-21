#include "config.h"

#if HAVE_LIBAPR_1
#include <apr-1/apr_pools.h>
#include "refmem_allocator.h"

static void *__refmem_allocator_apr_pool_alloc(void *ctx, size_t size)
{
    void *m = NULL;
    apr_pool_t *pool = (apr_pool_t *)ctx;

    m = apr_palloc(pool, size);

    /* apr has user-configurable OOM callback as well */
    if (m == NULL && refmem_allocator_oom_callback) 
        refmem_allocator_oom_callback();

    return m;
}

static void __refmem_allocator_apr_pool_free(void *ctx, void *p)
{
    /* we don't manage the memory pool, so nothing to do here */
}

refmem_allocator_t refmem_allocator_apr_pool = {
    __refmem_allocator_apr_pool_alloc,
    __refmem_allocator_apr_pool_free,
};

#endif /* HAVE_LIBAPR_1 */
