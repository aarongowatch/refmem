#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "refmem-1/refmem.h"
#include "refmem-1/refmem_atomic.h"

typedef struct {
    refmem_t klass;
    int32_t retain_count;
    refmem_cleanup_func_t *cleanup;
    void *data;
} __m;

static refmem_t refmem_klass;

#define UPCAST(obj) ((__m *)((uint8_t *)obj - 48))

static void *__refmem_retain(void *p)
{
    __m *self = UPCAST(p); 

    assert(self->retain_count < INT32_MAX);

    refmem_atomic_increment(&self->retain_count);

    return self->data; 
}

static void *__refmem_release(void *p)
{
    __m *self = UPCAST(p); 

    if (refmem_atomic_decrement(&self->retain_count))
      goto EXIT;

    free(self);

EXIT:
    return NULL;
}

void *rmalloc(size_t size)
{
    size_t s = size + sizeof(__m);
    __m *self = (__m *)malloc(s);

    if (self == NULL)
        return NULL;

    self->data  = (uint8_t *)self + sizeof(__m);
    self->klass = refmem_klass;
    self->retain_count = 1;

    return self->data; 
}

void *rcalloc(size_t count, size_t size)
{
    size_t s  = size * count;
    __m *self = UPCAST(rmalloc(s));

    if (self == NULL)
        return NULL;

    memset(self->data, 0, s);

    return self->data;
}

static refmem_t refmem_klass = {
    __refmem_retain, 
    __refmem_release,
    NULL,
};
