/*
 * Copyright (c) 2022  Cryptography Research, Inc. (CRI).
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <stddef.h>
#include <zephyr/types.h>
#include <ctype.h>
#include <stdio.h>
#include <sys/util.h>
#include <logging/log.h>

void sys_hexdump(const uint8_t *buf, size_t len, const char *msg)
{
	char hex[80];
	char *h = hex;
	char *t = hex;
	uint32_t off = 0;

	while (len > 0) {
		if (off % 16 == 0) {
			h = hex;
			const uint8_t *o = (const uint8_t *)&off;
			for (int i = 3; i >= 0; i--) {
				(void)hex2char(o[i] >> 4, h++);
				(void)hex2char(o[i] & 0xf, h++);
			}
			*h++ = ' ';
			t = h;
			for (int i = 0; i < 48; i++) { *t++ = ' '; }
			*t++ = '|';
			for (int i = 0; i < 16; i++) { *t++ = ' '; }
			*t++ = '|';
			*t = '\0';
			t -= 17;
		}
		(void)hex2char(*buf >> 4, h++);
		(void)hex2char(*buf & 0xf, h++);
		*h++ = ' ';
		if (isprint(*buf)) { *t++ = *buf; }
		else { *t++ = '.'; }

		off++;
		if (off % 16 == 0) {
			(void)fprintf(stdout, "%s%s\n", msg, hex);
		}
		buf++;
		len--;
	}
	if (off % 16 != 0) {
		(void)fprintf(stdout, "%s %s\n", msg, hex);
	}
}
