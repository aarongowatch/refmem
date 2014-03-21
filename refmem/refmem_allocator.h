#ifndef __REFMEM_ALLOCATOR_H__
#define __REFMEM_ALLOCATOR_H__

typedef void (refmem_allocator_oom_callback_t)(void);

typedef struct {
    void *(*alloc)(void *ctx, size_t size);
    void (*free)(void *ctx, void *mem); 
} refmem_allocator_t;

extern refmem_allocator_t refmem_allocator_system;

#if HAVE_LIBAPR_1
extern refmem_allocator_t refmem_allocator_apr_pools;
#endif

extern refmem_allocator_t *refmem_allocator_default;

extern refmem_allocator_oom_callback_t *refmem_allocator_oom_callback;

#endif
