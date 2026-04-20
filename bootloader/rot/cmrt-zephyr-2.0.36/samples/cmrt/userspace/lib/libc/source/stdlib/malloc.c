/*
 * Copyright (c) 2018 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <stdlib.h>
#include <zephyr.h>
#include <errno.h>
#include <sys/math_extras.h>
#include <string.h>
#include <app_memory/app_memdomain.h>
#include <sys/sys_heap.h>
#include <zephyr/types.h>

#ifdef CONFIG_MINIMAL_LIBC_MALLOC

void malloc_prepare(void *z_malloc_heap_mem, size_t z_malloc_heap_size);
static struct sys_heap z_malloc_heap;
static size_t HEAP_BYTES;

void *malloc(size_t size)
{
	void *ret = NULL;
	if (HEAP_BYTES > 0) {
		ret = sys_heap_aligned_alloc(&z_malloc_heap,
					     __alignof__(z_max_align_t),
					     size);
	}
	if (ret == NULL && size != 0) {
		errno = ENOMEM;
	}

	return ret;
}

void malloc_prepare(void *z_malloc_heap_mem, size_t z_malloc_heap_size)
{
	HEAP_BYTES = z_malloc_heap_size;
	if (HEAP_BYTES > 0) {
		sys_heap_init(&z_malloc_heap, z_malloc_heap_mem, HEAP_BYTES);
	}
}

void *realloc(void *ptr, size_t requested_size)
{
	void *ret = NULL;
	if (HEAP_BYTES > 0) {
		ret = sys_heap_aligned_realloc(&z_malloc_heap, ptr,
					       __alignof__(z_max_align_t),
					       requested_size);
	}
	if (ret == NULL && requested_size != 0) {
		errno = ENOMEM;
	}

	return ret;
}

void free(void *ptr)
{
	if (HEAP_BYTES > 0) {
		sys_heap_free(&z_malloc_heap, ptr);
	}
}

#endif /* CONFIG_MINIMAL_LIBC_MALLOC */

#ifdef CONFIG_MINIMAL_LIBC_CALLOC
void *calloc(size_t nmemb, size_t size)
{
	void *ret;

	if (size_mul_overflow(nmemb, size, &size)) {
		errno = ENOMEM;
		return NULL;
	}

	ret = malloc(size);

	if (ret != NULL) {
		(void)memset(ret, 0, size);
	}

	return ret;
}
#endif /* CONFIG_MINIMAL_LIBC_CALLOC */

#ifdef CONFIG_MINIMAL_LIBC_REALLOCARRAY
void *reallocarray(void *ptr, size_t nmemb, size_t size)
{
#if (CONFIG_MINIMAL_LIBC_MALLOC_ARENA_SIZE > 0)
	if (size_mul_overflow(nmemb, size, &size)) {
		errno = ENOMEM;
		return NULL;
	}
	return realloc(ptr, size);
#else
	return NULL;
#endif
}
#endif /* CONFIG_MINIMAL_LIBC_REALLOCARRAY */
