#include <stdio.h>
#include <string.h>

#include "refmem.h"
#include "refmem_atomic.h"
#include "refmem_private.h"

void *refmem_retain(void *p)
{
    refmem_private_t *self = UPCAST(p); 

    refmem_atomic_increment(&self->retain_count);

    return self->data;
}

void *refmem_release(void *p)
{
    refmem_private_t *self = UPCAST(p);

    if (refmem_atomic_decrement(&self->retain_count))
        return self->data;

    self->allocator->free(self->allocator, self);

    return NULL;
}

void *refmem_malloc(size_t size)
{
    refmem_private_t *self = NULL;
    refmem_allocator_t *allocator = refmem_allocator_get_default();
    size_t s = size + sizeof(refmem_private_t);

    if (allocator == NULL)
        return NULL;

    self = (refmem_private_t *)allocator->alloc(allocator, size);

    if (self == NULL)
        return NULL;

    /* FIXME: this should retain the allocator */ 
    self->allocator = allocator;
    self->data = (uint8_t *)self + sizeof(refmem_private_t);
    self->retain_count = 1;

    return self->data; 
}

void *refmem_calloc(size_t count, size_t size)
{
    size_t s  = size * count;
    refmem_private_t *self = NULL; 

    self = UPCAST(refmem_malloc(s));

    if (self == NULL)
        return NULL;

    memset(self->data, 0, s - sizeof(refmem_private_t));

    return self->data;
}

