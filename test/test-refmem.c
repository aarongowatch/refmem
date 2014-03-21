#include <assert.h>
#include "refmem-1/refmem.h"

typedef struct {
    char *b, *f;
    char buf[32];
} __test_t;

int main(int argc, char **argv)
{
    /* automatic retain count of 1 */
    __test_t *p = refmem_calloc(1, sizeof(__test_t));

    if (p == NULL)
        return 1;

    assert(p->b == NULL);
    assert(p->f == NULL);
    assert(sizeof(p->buf) == 32);

    /* increment retain count */
    assert(refmem_retain(p) == p);

    /* decrement retain count */
    assert(refmem_release(p) == p);
    assert(refmem_release(p) == NULL);

    p = NULL;

    p = refmem_malloc(sizeof(__test_t));

    if (p == NULL)
        return 1;

    assert(sizeof(p->buf) == 32);

    assert(refmem_retain(p) == p);
    assert(refmem_release(p) == p);
    assert(refmem_release(p) == NULL);

    return 0;
}

