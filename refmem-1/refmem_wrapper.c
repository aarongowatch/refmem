#include <assert.h>
#include <string.h>
#include "refmem-1/refmem_wrapper.h"
#include "refmem-1/refmem_atomic.h"

static refmem_t refmem_wrapper;

typedef struct {
    refmem_t klass;
    int32_t retain_count;
    refmem_cleanup_func_t *cleanup;
    void *data;
} refmem_wrapper_t;

#define UPCAST(obj) ((refmem_wrapper_t *)(obj))
#define DOWNCAST(obj) ((refmem_t *)(obj))

int refmem_wrapper_create(refmem_t **p, void *data, refmem_cleanup_func_t *cleanup)
{
    refmem_wrapper_t *self = NULL;

    *p = NULL;

    self = calloc(1, sizeof(refmem_wrapper_t));

    if (self == NULL)
        return -1;

    self->klass        = refmem_wrapper;
    self->cleanup      = cleanup;
    self->data         = data; 
    self->retain_count = 1;

    *p = DOWNCAST(self); 

    return 0;
}

static void *__refmem_wrapper_retain(void *p)
{
    refmem_wrapper_t *self = UPCAST(p);

    assert(self->retain_count < INT32_MAX);

    refmem_atomic_increment(&self->retain_count);

    return self->data; 
}

static void *__refmem_wrapper_release(void *p)
{
    refmem_wrapper_t *self = UPCAST(p);

    if (refmem_atomic_decrement(&self->retain_count))
        goto EXIT;

    self->cleanup(self->data);

    free(self);

    return NULL;

EXIT:
    return self->data; 
}

static void *__refmem_wrapper_data(void *p)
{
    refmem_wrapper_t *self = UPCAST(p);

    return self->data;
}


static refmem_t refmem_wrapper = {
    __refmem_wrapper_retain,
    __refmem_wrapper_release,
    __refmem_wrapper_data, 
};
