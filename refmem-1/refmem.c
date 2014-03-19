#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#if !__GNUC__ && __APPLE__
#include <libkern/OSAtomic.h>
#endif

#include "refmem-1/refmem.h"

typedef struct {
    refmem_t klass;
    int32_t retain_count;
    void *data;
} __m;

static refmem_t refmem_klass;

#define UPCAST(obj) ((__m *)((uint8_t *)obj - 32))

static void *__refmem_retain(void *p)
{
    __m *self = UPCAST(p); 

    assert(self->retain_count < INT32_MAX);

#if __GNUC__
    __sync_add_and_fetch(&self->retain_count, 1);
#elif __APPLE__
    OSAtomicIncrement32Barrier(&self->retain_count);
#else
    /* FIXME: mutex for shitty OS? */
    self->retain_count++;
#endif

    return self->data; 
}

static void *__refmem_release(void *p)
{
    __m *self = UPCAST(p); 

#if __GNUC__
    if (__sync_sub_and_fetch(&self->retain_count, 1))
#elif __APPLE__
    if (OSAtomicDecrement32Barrier(&self->retain_count))
#else
    /* bummer braj */
    if (self->retain_count--)
#endif
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
};
