#include "refmem_atomic.h"

#if !__GNUC__ && __APPLE__
#include <libkern/OSAtomic.h>
#endif

inline void refmem_atomic_set(refmem_atomic_t *p, int i)
{
    p->counter = i;
}

inline int refmem_atomic_increment(refmem_atomic_t *p)
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

inline int refmem_atomic_decrement(refmem_atomic_t *p)
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

