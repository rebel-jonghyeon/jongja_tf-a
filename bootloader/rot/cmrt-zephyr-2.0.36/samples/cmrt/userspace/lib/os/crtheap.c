#include <stddef.h>


extern char __heap_begin[];
extern char __heap_end[];

extern void malloc_prepare(void *z_malloc_heap_mem, size_t z_malloc_heap_size);


#define CONSTRUCTOR(prio) __attribute__((constructor(prio)))
/* Required to allow an init priority <= 100, which we use as this is part of
 * the standard library.  Must be smaller to allow heap use in other
 * members of init array.
 */
#pragma GCC diagnostic ignored "-Wprio-ctor-dtor"

void user_heap_init(void);
CONSTRUCTOR(99) void user_heap_init(void)
{
	/* Initialize malloc always, heap may be zero. */
	size_t heap_size = (size_t)(__heap_end - __heap_begin);
	malloc_prepare(__heap_begin, heap_size);
}
