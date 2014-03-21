#include <stdlib.h>
#include "refmem_allocator.h"

static void *__refmem_allocator_default_alloc(void *ctx, size_t size)
{
    void *m = NULL;

    if (size == 0)
        return NULL;

    m = malloc(size);

    if (m == NULL && refmem_allocator_oom_callback)
        refmem_allocator_oom_callback();

    return m;
}

static void __refmem_allocator_default_free(void *ctx, void *mem)
{
    free(mem);
}

refmem_allocator_t refmem_allocator_default = {
    __refmem_allocator_default_alloc,
    __refmem_allocator_default_free,
};

