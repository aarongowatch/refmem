#ifndef __TEST_TEST_OBJECT_H__
#define __TEST_TEST_OBJECT_H__

typedef struct test_object_s test_object_t;

int test_object_create(test_object_t **p);

struct test_object_s {
    test_object_t *(*retain)(test_object_t *p);
    test_object_t *(*release)(test_object_t *p);
};

#endif /* __TEST_TEST_OBJECT_H__ */
