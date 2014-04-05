#include <stdio.h>
#include <string.h>

#include "refmemm.h"
#include "refmem_private.h"

static void _refmemm_free(void *p)
{
    refmem_private_t *self = UPCAST_PRIVATE(p);

    self->allocator->free(self->allocator, self);
}

void *refmemm_retain(void *p)
{
    refmem_private_t *self = UPCAST(p); 

    refmem_retain(&self->refmem);

    return self->data;
}

void *refmemm_release(void *p)
{
    refmem_private_t *self = UPCAST(p);

    if (refmem_release(&self->refmem))
        return NULL;

    return self->data; 
}

void *refmem_malloc_ex(size_t size, refmem_allocator_t *allocator, void *ctx)
{
    refmem_private_t *self = NULL;
    size_t s = size + sizeof(refmem_private_t);

    self = (refmem_private_t *)allocator->alloc(ctx, size);

    if (self == NULL)
        return NULL;

    self->allocator = allocator;
    self->data      = (uint8_t *)self + sizeof(refmem_private_t);

    refmem_init(&self->refmem, _refmemm_free, self);

    return self->data; 
}

void *refmemm_malloc(size_t size)
{
    return refmem_malloc_ex(size, &refmem_allocator_system, NULL);
}

void *refmemm_calloc_ex(size_t count, size_t size, refmem_allocator_t *allocator, void *ctx)
{
    size_t s  = size * count;
    refmem_private_t *self = NULL; 

    self = UPCAST(refmem_malloc_ex(s, allocator, ctx));

    if (self == NULL)
        return NULL;

    memset(self->data, 0, s);

    return self->data;
}

void *refmemm_calloc(size_t count, size_t size)
{
    return refmemm_calloc_ex(count, size, &refmem_allocator_system, NULL);
}

