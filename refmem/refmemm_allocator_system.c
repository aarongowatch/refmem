#include <stdlib.h>
#include "refmemm_allocator.h"

static void *__refmem_allocator_system_alloc(void *ctx, size_t size)
{
    void *m = NULL;

    if (size == 0)
        return NULL;

    m = malloc(size);

    if (m == NULL && refmem_allocator_oom_callback)
        refmem_allocator_oom_callback();

    return m;
}

static void __refmem_allocator_system_free(void *ctx, void *mem)
{
    free(mem);
}

refmem_allocator_t refmem_allocator_system = {
    __refmem_allocator_system_alloc,
    __refmem_allocator_system_free,
};
