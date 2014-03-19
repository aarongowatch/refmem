#ifndef __REFMEM_H__
#define __REFMEM_H__

#include <stdlib.h>
#include <stdint.h>

#define REFMEM(obj) ((refmem_t *)((uint8_t *)obj - 32)) 

void *rmalloc(size_t size);
void *rcalloc(size_t count, size_t size);

typedef struct {
    void *(*retain)(void *);
    void *(*release)(void *);
} refmem_t;

#endif // __REFMEM_H__
