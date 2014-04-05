#ifndef __REFMEM_MEM_H__
#define __REFMEM_MEM_H__

#include <stdlib.h>
#include <refmem-1/refmemm_allocator.h>

void *refmemm_malloc(size_t size);
void *refmemm_malloc_ex(size_t size, refmem_allocator_t *allocator, void *ctx);

void *refmemm_calloc(size_t count, size_t size);
void *refmemm_calloc_ex(size_t count, size_t size, refmem_allocator_t *allocator, void *ctx);

void *refmemm_retain(void *);
void *refmemm_release(void *);

#endif // __REFMEM_MEM_H__
