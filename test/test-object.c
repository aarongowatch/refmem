#include <stdio.h>
#include <stdlib.h>

#include "refmem/refmem.h"
#include "test/test-object.h"

typedef struct {
    test_object_t klass;
    refmem_t retain_count;
} test_object_private_t;

#define UPCAST(obj) ((test_object_private_t *)(obj))

static test_object_t test_object_klass;

static void _test_object_destroy(void *p)
{
    test_object_private_t *self = UPCAST(p);

    free(self);
}

static test_object_t *_test_object_retain(test_object_t *p)
{
    test_object_private_t *self = UPCAST(p);

    refmem_retain(&self->retain_count);

    return p;
}

static test_object_t *_test_object_release(test_object_t *p)
{
    test_object_private_t *self = UPCAST(p);

    if (refmem_release(&self->retain_count))
        return NULL;

    return p;
}

int test_object_create(test_object_t **p)
{
    test_object_private_t *self = NULL;

    *p = NULL;

    self = (test_object_private_t *)calloc(1, sizeof(test_object_private_t));

    if (self == NULL)
        return 1;

    self->klass = test_object_klass;

    refmem_init(&self->retain_count, _test_object_destroy, self);

    *p = (test_object_t *)self;

    return 0;
}

static test_object_t test_object_klass = {
    _test_object_retain,
    _test_object_release,
};
