/*
 * Copyright (c) 2020-2022 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

#include <stdalign.h>
#include <zephyr.h>
#include <stdio.h>
#include <string.h>
#include <cri/cmrt/fmc.h>
#include "common.h"


#include <hexutil.h>

static alignas(4) char msg_buffer[1024];

/*
 * Write message to SAC memory.
 *
 * All access to SAC, read and write, must be word aligned and of size multiple
 * of word size. Therefore a word aligned temporary buffer is used.
 */
char *sac_write_msg(char *output, char *end, int log, const char *format, ...)
{
	u32_t size = end - output;
	size = size < sizeof(msg_buffer) ? size : sizeof(msg_buffer);

/* Write to staging buffer, account for string terminal character. */
	va_list vargs;
	va_start(vargs, format);
	int used = 1 + vsnprintf(msg_buffer, size, format, vargs);
	va_end(vargs);

	if (used >= size) { /* output truncated */
		used = size;
		msg_buffer[used-1] = '\0';
	} else {
		/* Align and pad */
		for (; (used < size) && (used & 3); used++) {
			msg_buffer[used] = '\0';
		}
	}

	if (log)
		printk("%s", msg_buffer);

/* Copy to SAC memory. */
	memcpy(output, msg_buffer, used);
	return output + used;
}

void hexdump_var(const char *name, const void *var, size_t len)
{
	printk("%s: %u\n", name, len);
	hexdump(var, len);
}
#ifdef DEBUG
void debug_hexdump_var(const char *file, int line,
		       const char *name, const void *var, size_t len)
{
	printk("Debug: %s:%d: %s: %u\n", file, line, name, len);
	hexdump(var, len);
}
#endif
