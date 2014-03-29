#include <assert.h>
#include <stdlib.h>

#include "test/test-object.h"

int main(int argc, char **argv)
{
    test_object_t *obj = NULL;

    if (test_object_create(&obj) != 0)
        return 1;

    assert(obj->retain(obj) == obj);
    assert(obj->release(obj) == obj);

    /* release returns NULL after object has been cleaned up */

    assert(obj->release(obj) == NULL);
}
