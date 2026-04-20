/*
 * Copyright (c) 2018-2023 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

#ifndef CRILOG_USER_H
#define CRILOG_USER_H

#include <stdio.h>
#include <stdlib.h>

/*
 * Logging from the container (usable in debug environments)
 */

#ifndef NDEBUG

/*!
 * Log a line.  Logs a line with the function and line number.
 * If NDEBUG is defined on inclusion of this file, does nothing.
 * @param fmt printf-style format
 * @param arg argument list
 * @return cri_log() return value
 */
#define cri_log(fmt, ...) \
	do { fprintf(stdout, "CD: " fmt, ##__VA_ARGS__); } while(0)
#define c_log(fmt, ...) \
	do { fprintf(stdout, "CD: " fmt, ##__VA_ARGS__); } while(0)


/*!
 * Log an error.  The log will include the function and line number of
 * the invoking expression.
 * @param fmt printf-style formatting
 * @param arg argument list
 * @return cri_log() return value
 */
#define c_error(fmt, ...) \
	do { fprintf(stderr, "CE: " fmt, ##__VA_ARGS__); } while(0)


/*!
 * Dump buffer as hex.  Does a human-readable hex dump of \a buf.  If
 * NDEBUG is defined at the point of inclusion of this header, the
 * expression does nothing.
 * @param buf buffer to dump
 * @param len length of \a buffer in bytes
 */
#define hexdump(b, l) do { (void)b; (void)l; } while (0)


/*!
 * Assert condition.  Logs a message and exits with value 1.  If
 * NDEBUG is defined at the point where this file is included, expands
 * to a null expression.
 * @param test expression to verify
 */
#define cri_assert(test)						\
	do {								\
		if (!(test)) {						\
			fprintf(stderr, "CE: Assertion `" #test "' failed."); \
			abort();					\
		}							\
	} while (0)


#else /* !NDEBUG  -- logging useless in release environments */

#define cri_log(...) do {} while (0)
#define c_log(...) do {} while (0)
#define c_error(...) do {} while (0)
#define hexdump(b, l) do { (void)b; (void)l; } while (0)

#define cri_assert(test) do { if (!(test)) abort(); } while (0)

#endif /* NDEBUG */

#endif
