#include "config.h"

#if HAVE_LIBAPR_1 
#include <assert.h>
#include <apr-1/apr.h>
#include <apr-1/apr_pools.h>
#include "refmem/refmem.h"
#include "refmem/refmem_allocator.h"

typedef struct {
    char *b, *f;
    char buf[32];
} __test_t;

int main(int argc, char **argv)
{
    __test_t *test = NULL;
    apr_pool_t *pool;

    if (apr_initialize() != APR_SUCCESS)
        return 1;

    if (apr_pool_create(&pool, NULL) != APR_SUCCESS)
        return 1;

    test = refmem_calloc_ex(1, sizeof(__test_t), &refmem_allocator_apr_pools, pool);

    assert(test != NULL);

    assert(refmem_retain(test) != NULL);
    assert(refmem_release(test) != NULL);
    assert(refmem_release(test) == NULL);

    apr_pool_destroy(pool);

    apr_terminate();
}

#endif /* HAVE_LIBAPR_1 */
