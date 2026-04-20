/*
 * Copyright (c) 2022-2023 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

#include <stdalign.h>
#include <stdbool.h>
#include <stddef.h>
#include <strings.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <assert.h>

#include <container.h>
#include <logging/log.h>
#include <drivers/cmrt/cmrt.h>
#include <drivers/cmrt/sic.h>

static void echo_function(void *p1, void *p2, void *p3)
{
	uint32_t flowid = (uint32_t)p1;
	uint8_t *buffer = (uint8_t *)p2;
	size_t bufmax = (size_t)p3;

	cmrt_sic_t sic = cmrt_sic_open(CMRT_O_SYNC, flowid);
	if (!cmrt_is_valid(sic)) {
		LOG_INF("Cannot open SIC");
		return;
	}
	LOG_INF("Waiting for SIC input on 0x%x...", (unsigned int)flowid);
	while (memcmp(buffer, "exit", sizeof("exit") - 1) != 0) {
		size_t buflen = bufmax;
		uint32_t peerid;
		int res = cmrt_sic_read(sic, buffer, &buflen, &peerid, 0);
		if (res < 0) {
			LOG_INF("Failed to read from HLOS: %d!", res);
			break;
		}

		LOG_INF("Echoing %d bytes from 0x%x to 0x%x",
			buflen, (unsigned int)flowid, (unsigned int)peerid);

		res = cmrt_sic_write(sic, buffer, buflen, peerid);
		if (res < 0) {
			LOG_INF("Failed to write to HLOS: %d!", res);
			break;
		}
	}
	cmrt_sic_close(sic);
}

void container(void *p1, void *p2, void *p3)
{
	/* MW gives the flowid in p1. */
	(void)p2;
	(void)p3;
	static alignas(4) uint8_t buffer[1024];
	/* Echo function is the same as in the echo supervisor. */
	echo_function(p1, (void *)buffer, (void *)sizeof(buffer));
}
