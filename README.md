refmem
======

Mostly experimental reference counted memory blocks for C

Examples:

```c
/* automatic retain count of 1 */
uint8_t *buf = refmem_calloc(32, sizeof(uint8_t));

/* increment retain count by 1 */
refmem_retain(buf);

/* decrement retain count by 1 */
refmem_release(buf);

/* retain count drops to zero, buf is free'd */
refmem_release(buf);
```

refmem works with any C data type
