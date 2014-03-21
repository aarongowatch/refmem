#include "refmem_atomic.h"

#if !__GNUC__ && __APPLE__
#include <libkern/OSAtomic.h>
#endif

uint32_t refmem_atomic_increment(volatile uint32_t *p)
{
#if __GNUC__
    return __sync_add_and_fetch(p, 1);
#elif __APPLE__
    return OSAtomicIncrement32Barrier(p);
#else
    /* this super is not atomic */
    return ++*p;
#endif
}

uint32_t refmem_atomic_decrement(volatile uint32_t *p)
{
#if __GNUC__
    return __sync_sub_and_fetch(p, 1);
#elif __APPLE__
    return OSAtomicDecrement32Barrier(p);
#else
    /* bummer braj */
    return --*p; 
#endif
}

