#include "config.h"
#if HAVE_STDLIB_H

#include "refmem.h"

static void *__refmem_allocator_default_alloc(void *p, size_t size)
{
    void *m = NULL;

    if (size == 0)
        return NULL;

    m = malloc(size);

    if (m == NULL && refmem_allocator_oom_callback)
        refmem_allocator_oom_callback();

    return m;
}

static void __refmem_allocator_default_free(void *p, void *mem)
{
    free(mem);
}

refmem_allocator_t refmem_allocator_default = {
    __refmem_allocator_default_alloc,
    __refmem_allocator_default_free,
};

#endif // HAVE_STDLIB_H
