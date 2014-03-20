#ifndef __REFMEM_H__
#define __REFMEM_H__

#include <stdlib.h>

void *refmem_malloc(size_t size);
void *refmem_calloc(size_t count, size_t size);
void *refmem_retain(void *);
void *refmem_release(void *);

#endif // __REFMEM_H__
