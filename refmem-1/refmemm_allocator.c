#include <stdio.h>
#include <stdlib.h>

#include "refmemm_allocator.h" 

static void __refmem_oom(void)
{
    fprintf(stderr, "ERROR: out of memory; aborting\n");
    abort();
}

refmem_allocator_oom_callback_t *refmem_allocator_oom_callback = __refmem_oom;
