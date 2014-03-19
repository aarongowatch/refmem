#ifndef __REFMEM_ATOMIC_H__
#define __REFMEM_ATOMIC_H__

#include <stdint.h>

int32_t refmem_atomic_increment(int32_t *p);
int32_t refmem_atomic_decrement(int32_t *p);

#endif
