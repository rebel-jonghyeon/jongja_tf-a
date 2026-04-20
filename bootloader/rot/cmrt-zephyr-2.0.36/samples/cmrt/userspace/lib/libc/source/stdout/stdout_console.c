/* stdout_console.c */

/*
 * Copyright (c) 2014 Wind River Systems, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <stdio.h>
#include <sys/libc-hooks.h>
#include <syscall_handler.h>
#include <string.h>

int fputs(const char *_MLIBC_RESTRICT s, FILE *_MLIBC_RESTRICT stream)
{
	int len = strlen(s);
	int ret;

	ret = fwrite(s, 1, len, stream);

	return len == ret ? 0 : EOF;
}

size_t fwrite(const void *_MLIBC_RESTRICT ptr, size_t size, size_t nitems,
			  FILE *_MLIBC_RESTRICT stream)
{
	return zephyr_fwrite(ptr, size, nitems, stream);
}


int puts(const char *s)
{
	if (fputs(s, stdout) == EOF) {
		return EOF;
	}

	return fputc('\n', stdout) == EOF ? EOF : 0;
}
