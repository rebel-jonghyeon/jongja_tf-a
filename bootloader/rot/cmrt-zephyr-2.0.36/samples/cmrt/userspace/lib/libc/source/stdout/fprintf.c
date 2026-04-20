/* fprintf.c */

/*
 * Copyright (c) 1997-2010, 2013-2014 Wind River Systems, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <stdarg.h>
#include <stdio.h>
#include <sys/libc-hooks.h>
#include <sys/cbprintf.h>

#define DESC(d) ((void *)d)

#if CONFIG_FPUTC_BUFFER_SIZE > 0
struct fputc_buffer {
	size_t count;
	char buf[CONFIG_FPUTC_BUFFER_SIZE];
};

static struct fputc_buffer stdout_buf;
static struct fputc_buffer stderr_buf;

static void buffer_flush(struct fputc_buffer *b, FILE *stream)
{
	zephyr_fwrite(b->buf, b->count, 1, stream);
	b->count = 0U;
}

static int buffer_fputc(int c, FILE *stream)
{
	struct fputc_buffer *b = stream == stdout ? &stdout_buf : &stderr_buf;
	b->buf[b->count++] = c;
	if (c == '\n' || b->count == CONFIG_FPUTC_BUFFER_SIZE) {
		buffer_flush(b, stream);
	}
	return c;
}
#endif

int fputc(int c, FILE *stream)
{
#if CONFIG_FPUTC_BUFFER_SIZE > 0
	return buffer_fputc(c, stream);
#else
	return zephyr_fputc(c, stream);
#endif
}

int fprintf(FILE *_MLIBC_RESTRICT stream, const char *_MLIBC_RESTRICT format, ...)
{
	va_list vargs;
	int     r;

	va_start(vargs, format);
	r = cbvprintf(fputc, DESC(stream), format, vargs);
	va_end(vargs);

	return r;
}

int vfprintf(FILE *_MLIBC_RESTRICT stream, const char *_MLIBC_RESTRICT format,
	     va_list vargs)
{
	int r;

	r = cbvprintf(fputc, DESC(stream), format, vargs);

	return r;
}

int printf(const char *_MLIBC_RESTRICT format, ...)
{
	va_list vargs;
	int     r;

	va_start(vargs, format);
	r = cbvprintf(fputc, DESC(stdout), format, vargs);
	va_end(vargs);

	return r;
}

int vprintf(const char *_MLIBC_RESTRICT format, va_list vargs)
{
	int r;

	r = cbvprintf(fputc, DESC(stdout), format, vargs);

	return r;
}
