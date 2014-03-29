#ifndef __REFMEM_PRIVATE_H__
#define __REFMEM_PRIVATE_H__

#include <stdint.h>
#include "config.h"
#include "refmem_allocator.h"

typedef struct {
    refmem_t refmem;
    refmem_allocator_t *allocator;
    void *data;
} refmem_private_t;

#define UPCAST(obj) ((refmem_private_t *)(obj - sizeof(refmem_private_t)))

#endif
