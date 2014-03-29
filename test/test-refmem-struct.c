#include <assert.h>
#include <stdlib.h>

#include "refmem/refmem_object.h"

typedef struct {
    refmem_t retain_count;
    int x, y, z;
    char *foo;
} test_object_t;

static int freed = 0;

static void _free(void *ctx)
{
    free(ctx);

    freed = 1;
}

int main(int argc, char **argv)
{
    test_object_t *obj = calloc(1, sizeof(test_object_t));

    if (obj == NULL)
        return 1;

    obj->x   = obj->y = obj->z = 5;
    obj->foo = "test";

    refmem_init(&obj->retain_count, _free, obj);

    refmem_retain(&obj->retain_count);

    /* returns 1 when object is cleaned up */
    assert(refmem_release(&obj->retain_count) == 0);
    assert(refmem_release(&obj->retain_count) == 1);

    assert(freed == 1);
}
