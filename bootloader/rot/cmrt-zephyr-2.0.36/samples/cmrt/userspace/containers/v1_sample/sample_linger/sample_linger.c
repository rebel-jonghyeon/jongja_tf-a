/*
 * Copyright (c) 2020-2023 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

/**
 * @file
 * @brief Sample container receives SIC message, linger for a while
 *        (total 1 sec), then echo reply to the caller.
 */

#include <stdbool.h>
#include <cri/cmrt.h>
#include "crilog-user.h"
#include "crisyscall-user.h"
#include <cri/cmrt/sic.h>

static int linger(void)
{
	c_log("Call cri_wait([], 500ms)\n");
	const int fout = cri_wait(0, NULL, CRI_SECONDS(0.5));
	c_log("cri_wait([], 500ms) returned %d\n", fout);
	if (fout < 0)
		return -1;
	return 0;
}

int main(void)
{
	c_log("Sample (linger) container starting; open sic flow %d\n",
	      CRI_UNIT_CONTAINER_SAMPLE);

	const cri_sic_t sic = cri_sic_open(0, CRI_UNIT_CONTAINER_SAMPLE);
	if (!cri_is_valid(sic)) {
		c_error("SIC open failed: %d\n", sic);
		return 1;
	}
	cri_log("cri_sic_open(%d) returned fd %d\n",
		CRI_UNIT_CONTAINER_SAMPLE, sic);

	char buf[512];
	uint32_t peer;
	size_t msglen = sizeof(buf);
	c_log("Call cri_sic_read(%d, buf, %d)\n", sic, sizeof(buf));
	int err = cri_sic_read(sic, buf, &msglen, &peer);
	c_log("cri_sic_read() returned %d\n", err);
	if (err < 0) goto out;

	while (true) {
		c_log("Call cri_wait([%d], 30s)\n", sic);
		const int fout = cri_wait(1, &sic, CRI_SECONDS(30));
		c_log("cri_wait([%d], 30s) returned %d\n", sic, fout);

		if ((fout > 0) && (fout & 1u)) {
			err = cri_sic_sync(sic);
			c_log("cri_sic_sync() returned %d\n", err);
			if (err) break;

			c_log("Received sic message from 0x%x (%u bytes)\n",
			      peer, msglen);

			if (linger() < 0) break;

			c_log("Send sic message (echo reply) to 0x%x\n",
			      peer);
			err = cri_sic_write(sic, buf, msglen, peer);
			c_log("cri_sic_send_message() returned %d\n", err);
			if (err) break;

			if (linger() < 0) break;

			c_log("Call cri_sic_read(%d, buf, %d)\n",
			      sic, sizeof(buf));
			msglen = sizeof(buf);
			err = cri_sic_read(sic, buf, &msglen, &peer);
			c_log("cri_sic_read() returned %d\n", err);
			if (err) break;
		}
		else if (fout < 0) {
			c_log("cri_wait() returned %d\n", fout);
			break;
		}
		else {
			c_log("No sic messages in 30 seconds...\n");
		}
	}
out:
	cri_sic_close(sic);
	c_log("Sample container (linger) exiting.\n");
	return 1;
}
