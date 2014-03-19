#include <assert.h>
#include "refmem-1/refmem.h"

typedef struct {
    char *b, *f;
    char buf[32];
} __test_t;

int main(int argc, char **argv)
{
    /* automatic reference count of 1 */
    __test_t *p = rcalloc(1, sizeof(__test_t));

    if (p == NULL)
        return 1;

    assert(p->b == NULL);
    assert(p->f == NULL);
    assert(sizeof(p->buf) == 32);

    assert(REFMEM(p)->data(p) == p);

    /* increment retain count */
    REFMEM(p)->retain(p);

    /* decrement retain count */
    REFMEM(p)->release(p);
    REFMEM(p)->release(p);

    p = NULL;

    p = rmalloc(sizeof(__test_t));

    if (p == NULL)
        return 1;

    assert(p->b == NULL);
    assert(p->f == NULL);
    assert(sizeof(p->buf) == 32);

    assert(REFMEM(p)->retain(p) == p);
    assert(REFMEM(p)->release(p) == p);
    assert(REFMEM(p)->release(p) == NULL);

    return 0;
}
