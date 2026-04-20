/*
 * Copyright (c) 2023-2024 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file
 */
#ifndef CMRT_UCU_SPAN_H
#define CMRT_UCU_SPAN_H
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Buffer view.
 *
 * The structure describes a data buffer either returned, or written
 * to (the pointer is kept constant for the most typical uses).
 */
typedef struct span {
	uint8_t const *p;	/**< pointer to data */
	size_t n;		/**< size of data in bytes */
} span;

/** Zero length span. */
#define EMPTY_SPAN ((span){NULL, 0u})

/**
 * Construct a span from a pointer and length.
 *
 * @param p pointer to the data
 * @param n length of the data
 * @return a span covering the memory [p, p+n).
 */
static inline span span_from(const void *p, size_t n)
{
	return (span){(const uint8_t *)p, n};
}

/**
 * Return a sub-span of s.
 *
 * @param s a span
 * @param begin starting offset of the sub-span
 * @param end ending offset of the sub-span
 * @return a span covering [s+begin, s+end), or EMPTY_SPAN if out of
 * bounds.
 */
static inline span span_slice(const span s, size_t begin, size_t end)
{
	span sub = EMPTY_SPAN;
	if ((begin < s.n) && (end <= s.n) && (begin <= end)) {
		sub.p = s.p + begin;
		sub.n = end - begin;
	}
	return sub;
}

/**
 * Copy src into dst.
 *
 * @param dst destination span
 * @param src source span
 * @return 0 on success, -1 if @a src is larger than @a dst.
 */
static inline int span_copy(span dst, const span src)
{
	int res = -1;
	if (dst.n >= src.n) {
		(void)memmove((void *)dst.p, src.p, src.n);
		res = 0;
	}
	return res;
}

/**
 * Return whether a span is valid.
 *
 * @param s a span
 * @return true if @a s points to non-NULL and has non-zero size.
 */
static inline bool span_valid(const span s)
{
	return ((s.p != NULL) && (s.n > 0u));
}

/**
 * A writer that writes to a fixed buffer.
 *
 * This is defined as a single element array for convenience: no need
 * to pass &writers around, since the array decays to a pointer when
 * passed in arguments.
 */
typedef struct span_writer_s {
	span buf;
	/**
	 * The .used field is always incremented when appending, thus
	 * it may become larger than the backing buffer size. This can
	 * be used to learn how many bytes would be needed, in case of
	 * insufficient storage.
	 */
	size_t used;
} span_writer[1];

/**
 * Initializer fro a @a span_writer backed by a given object.
 *
 * Example:
 * char buf[32];
 * span_writer w = SPAN_WRITER(buf);
 */
#define SPAN_WRITER(storage) {{{(const uint8_t *)&(storage), sizeof(storage)}, 0u}}

/**
 * Initialize a @a span_writer with the given span as backing buffer.
 *
 * @param writer the writer to initialize
 * @param buffer the backing buffer
 */
static inline void span_writer_init(span_writer writer, span buffer)
{
	writer->buf = buffer;
	writer->used = 0u;
}

/**
 * Return true if the writer has not overflowed.
 *
 * Use this to check if a sequence of operations succeeded.
 */
static inline bool span_writer_ok(const span_writer writer)
{
	return writer->used <= writer->buf.n;
}

/**
 * Return the written part of the writer as a span.
 */
static inline span span_writer_span(const span_writer writer)
{
	if (span_writer_ok(writer)) {
		return (span){writer->buf.p, writer->used};
	} else {
		return EMPTY_SPAN;
	}
}

/**
 * Append the data to the writer.
 *
 * If the result would overflow the writer, the data is not copied,
 * but writer->used is incremented. If the lengths would result in
 * unsigned wraparound, the whole operation is silently ignored.
 *
 * @param writer the writer
 * @param data the buffer to append
 */
static inline void span_writer_append(span_writer writer, span data)
{
	/* If the new length would wrap, the operation is completely
	 * ignored, and writer->used is not incremented.
	 */
	size_t nn = writer->used + data.n;
	if (nn >= data.n) { /* does not wrap */
		if (nn < writer->buf.n) { /* fits into the buffer */
			(void)memmove((void *)(writer->buf.p + writer->used), data.p, data.n);
		}
		writer->used = nn;
	}
}

/**
 * Convert data to hex.
 *
 * @param[in] data binary data
 * @param[out] hex output buffer for hex representation of @a data
 * @return 0 on success, -1 if @a hex is too short
 */
int span_bin2hex(const span data, span hex);

/**
 * Append hex-encoded data to the writer.
 *
 * If the hex-encoded data would not fit in the writer, then the data
 * is not copied, but writer->used is incremented.
 *
 * @param writer a writer
 * @param data binary data
 */
static inline void span_writer_append_hex(span_writer writer, span data)
{
	/* If the new length would wrap, the operation is completely
	 * ignored and writer->used is not incremented.
	 */
	if (data.n < SIZE_MAX / 2u) { /* 2*data.n does not wrap */
		size_t nn = writer->used + 2 * data.n;
		if (nn >= writer->used) { /* addition does not wrap */
			if (nn < writer->buf.n) { /* fits into the buffer */
				(void)span_bin2hex(data,
						   span_from(writer->buf.p + writer->used,
							     writer->buf.n - writer->used));
			}
			writer->used = nn;
		}
	}
}

#ifdef __cplusplus
}
#endif
#endif
