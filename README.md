refmem
======

Mostly experimental reference counted memory blocks for C.

Examples:

```c
/* automatic retain count of 1 */
uint8_t *buf = refmemm_calloc(32, sizeof(uint8_t));

/* increment retain count by 1 */
refmemm_retain(buf);

/* decrement retain count by 1 */
refmemm_release(buf);

/* retain count drops to zero, buf is free'd */
refmemm_release(buf);
```

refmem works with any C data type and is thread-safe with GCC or on OSX. 
