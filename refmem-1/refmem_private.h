#ifndef __REFMEM_PRIVATE_H__
#define __REFMEM_PRIVATE_H__

typedef struct {
    uint32_t retain_count;
    void *data;
} refmem_private_t;

#define UPCAST(obj) ((refmem_private_t *)(obj - sizeof(refmem_private_t)))

#endif
