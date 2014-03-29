#ifndef __REFMEM_ATOMIC_H__
#define __REFMEM_ATOMIC_H__

#if !__GNUC__ && __APPLE__
#include <libkern/OSAtomic.h>
#endif

typedef struct {
    volatile int counter;
} refmem_atomic_t;

#define refmem_atomic_decrement_and_test(p) (refmem_atomic_decrement_and_return((p)) == 0)

static inline void refmem_atomic_set(refmem_atomic_t *p, int i)
{
    p->counter = i;
}

static inline int refmem_atomic_increment(refmem_atomic_t *p)
{
    int result = 0;
#if __GNUC__
    result = __sync_add_and_fetch(&p->counter, 1);
#elif __APPLE__
    result = OSAtomicIncrement32Barrier(&p->counter);
#else
    /* this super is not atomic */
    result = ++*p->counter;
#endif
    return result;
}

static inline int refmem_atomic_decrement_and_return(refmem_atomic_t *p)
{
    int result = 0;
#if __GNUC__
    result = __sync_sub_and_fetch(&p->counter, 1);
#elif __APPLE__
    result = OSAtomicDecrement32Barrier(&p->counter);
#else
    /* bummer braj */
    result = --*p->counter;
#endif
    return result;
}

#endif // __REFMEM_ATOMIC_H__
