/*
 * Copyright (c) 2023 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file
 */
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <cmrt/ucu/span.h>

static char hexchar(uint8_t n)
{
	if (n < 10u) {
		return (char)n + '0';
	} else if (n < 16u) {
		return (char)(n - 10u) + 'A';
	} else {
		return '\0';
	}
}

int span_bin2hex(const span data, span hex)
{
	if ((hex.n / 2u) < data.n) {
		return -1;
	}
	uint8_t *p = (uint8_t *)hex.p;
	for (size_t i = 0; i < data.n; ++i) {
		p[2*i] = hexchar(data.p[i] >> 4);
		p[2*i+1] = hexchar(data.p[i] & 0xFu);
	}
	return 0;
}
