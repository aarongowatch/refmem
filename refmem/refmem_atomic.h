#ifndef __REFMEM_ATOMIC_H__
#define __REFMEM_ATOMIC_H__

#include <stdint.h>

uint32_t refmem_atomic_increment(volatile uint32_t *p);
uint32_t refmem_atomic_decrement(volatile uint32_t *p);

#endif
