refmem
======

Mostly experimental reference counted memory blocks for C.

Examples:

```c
/* smart pointer */

/* automatic retain count of 1 */
uint8_t *buf = refmemm_calloc(32, sizeof(uint8_t));

/* increment retain count by 1 */
refmemm_retain(buf);

/* decrement retain count by 1 */
refmemm_release(buf);

/* retain count drops to zero, buf is free'd */
refmemm_release(buf);
```

```c
/* using refmem with your own structs/objects */

typedef struct {
	refmem_t retain_count;
	char *dest;
	int x, y, z;
} my_struct_t;

my_struct_t *data = calloc(1, sizeof(my_struct_t));

data->dest = "The Supermarket";

/* configure cleanup callback and context, automatic retain count of 1 */
refmem_init(&data->retain_count, free, data);

/* increment retain count by 1 */
refmem_retain(&data->retain_count);

/* decrement retain count by 1 */
refmem_release(&data->retain_count);

/* decrement retain count by 1, free memory */
refmem_release(&data->retain_count);
```

More examples can be found under `test/`.

refmem works with any C data type and is thread-safe with GCC or on OSX. 
