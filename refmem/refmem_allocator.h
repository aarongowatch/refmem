#ifndef __REFMEM_ALLOCATOR_H__
#define __REFMEM_ALLOCATOR_H__

#include "refmem.h"

typedef struct {
    void *(*alloc)(void *ctx, size_t size);
    void (*free)(void *ctx, void *mem); 
} refmem_allocator_t;

extern refmem_allocator_t refmem_allocator_default;

void refmem_allocator_set_default(refmem_allocator_t *);

refmem_allocator_t *refmem_allocator_get_default(void);

#endif
