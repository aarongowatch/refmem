refmem
======

Mostly experimental feference counted memory blocks for C

Examples:

```c
/* automatic retain count of 1 */
uint8_t *buf = refmem_calloc(32, sizeof(uint8_t));

/* increment retain count by 1 */
refmem_retain(buf);

/* decrement retain count by 1 */
refmem_release(buf);

/* buf is free'd */
refmem_relese(buf);
```
