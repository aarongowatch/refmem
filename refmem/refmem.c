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
        goto EXIT;

    free(self);

    return NULL;

EXIT:
    return self->data; 
}

void *refmem_malloc(size_t size)
{
    size_t s = size + sizeof(refmem_private_t);
    refmem_private_t *self = (refmem_private_t *)malloc(s);

    if (self == NULL)
        return NULL;

    self->data = (uint8_t *)self + sizeof(refmem_private_t);
    self->retain_count = 1;

    return self->data; 
}

void *refmem_calloc(size_t count, size_t size)
{
    size_t s  = size * count;
    refmem_private_t *self = UPCAST(refmem_malloc(s));

    if (self == NULL)
        return NULL;

    memset(self->data, 0, s);

    return self->data;
}

