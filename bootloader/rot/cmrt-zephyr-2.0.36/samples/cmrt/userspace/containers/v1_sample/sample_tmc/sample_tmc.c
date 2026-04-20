/*
 * Copyright (c) 2019-2023 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

/**
 * @file
 * @brief Sample container to generate random data unsing TMC Core.
 */

#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include "crisyscall-user.h"
#include "crilog-user.h"
#include <cri/cmrt.h>
#include <cri/cmrt/sic.h>
#include <cri/cmrt/tmc.h>

#define BUFSIZE 256
static uint8_t buffer[BUFSIZE];

static int generate_data(const char *input)
{
	/* convert data received from hlos to integer */
	int rsize = (int) strtol(input, NULL, 0);
	c_log("Requested random data size is %d\n", rsize);
	if (rsize <= 0) {
		c_log("Setting random data size to 1\n");
		rsize = 1;
	}
	else if (rsize > BUFSIZE) {
		c_log("Clamping random data size to %d\n", BUFSIZE);
		rsize = BUFSIZE;
	}
	memset(buffer, 0, rsize);
	c_log("TMC open\n");
	cri_tmc_t tmc;
	if (!cri_is_valid(tmc = cri_tmc_open(CRI_O_SYNC))) {
		c_error("TMC open failed.\n");
		return 1;
	}
	int res = cri_tmc_generate(tmc, buffer, rsize);
	if (res != 0) {
		c_error("TMC generate failed: %d.\n", res);
		if (res > 0) {
			res = -res;
		}
		goto out;
	}
	c_log("Random Data:\n");
	hexdump(buffer, rsize);
	res = rsize;
 out:
	cri_tmc_close(tmc);
	return res;
}

int main(void)
{
	c_log("Sample (tmc) container starting...\n");

	const cri_sic_t sic = cri_sic_open(0, CRI_UNIT_CONTAINER_SAMPLE);
	if (!cri_is_valid(sic)) {
		c_error("SIC open failed: %d\n", sic);
		return 1;
	}
	uint32_t peer;
	size_t msglen = sizeof(buffer) - 4;
	int ret = cri_sic_read(sic, buffer, &msglen, &peer);
	if (ret) {
		c_log("cri_sic_read() returned %d\n", ret);
		goto out;
	}
	while (true) {
		const int fout = cri_wait(1, &sic, CRI_SECONDS(30));
		if ((fout > 0) && (fout & 1u)) {
			ret = cri_sic_sync(sic);
			if (ret) {
				c_log("cri_sic_sync() returned %d\n", ret);
				break;
			}
			c_log("Received sic message from 0x%x\n", peer);
			buffer[msglen] = '\0';
			int out = generate_data((const char *)buffer);
			if (out <= 0) {
				c_log("TMC failed to generate data.\n");
				break;
			}
			c_log("Sending sic message to 0x%x\n", peer);
			ret = cri_sic_write(sic, buffer, out, peer);
			if (ret) {
				c_log("cri_sic_write() returned %d\n", ret);
				break;
			}
			msglen = sizeof(buffer) - 4;
			ret = cri_sic_read(sic, buffer, &msglen, &peer);
			if (ret) {
				c_log("cri_sic_read() returned %d\n", ret);
				break;
			}
		}
		else if (fout < 0) {
			c_log("cri_wait() returned %d\n", ret);
			break;
		}
		else {
			c_log("No sic messages in 30 seconds...\n");
		}
	}
out:
	cri_sic_close(sic);
	c_log("Sample container exiting (ret %d)\n", ret);
	return ret;
}
