#include <assert.h>
#include <stdio.h>
#include <refmem-1/refmem_atomic.h>
#include <refmem-1/refmemm.h>

typedef struct {
    char *b, *f;
    char buf[32];
} __test_t;

int main(int argc, char **argv)
{
    /* automatic retain count of 1 */
    __test_t *p = refmemm_calloc(1, sizeof(__test_t));

    if (p == NULL)
        return 1;

    assert(p->b == NULL);
    assert(p->f == NULL);
    assert(sizeof(p->buf) == 32);

    /* increment retain count */
    assert(refmemm_retain(p) == p);

    /* decrement retain count */
    assert(refmemm_release(p) == p);
    assert(refmemm_release(p) == NULL);

    p = NULL;

    p = refmemm_malloc(sizeof(__test_t));

    if (p == NULL)
        return 1;

    assert(sizeof(p->buf) == 32);

    assert(refmemm_retain(p) == p);
    assert(refmemm_release(p) == p);
    assert(refmemm_release(p) == NULL);

    return 0;
}

