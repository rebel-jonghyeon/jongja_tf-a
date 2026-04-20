/*
 * Copyright (c) 2017-2023 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

/**
 * @file
 * @brief Sample container to demonstrate OTP root deletion/obliteration.
 *        operation is triggered by SIC message.
 */

#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

#include "crisyscall-user.h"
#include "crilog-user.h"
#include <cri/cmrt.h>
#include <cri/cmrt/sic.h>

static int verify_otp_root(void)
{
#if 0
	const bristol_omc_root_t root = {
		.id.hash = {
			0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88,
			0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88,
			0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88,
			0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88,
		},
		.perm.slot_perm.val = 0x0,
		.perm.key_perm.val = 0xFFFFFFFF,
		.perm.feature_perm.val = 0xFFFFFFFF,
		.perm.sw_otp_perm[0].val = 0x1FFFF << 15,
		.perm.sw_otp_perm[1].val = 0x1FFFF << 15,
		.perm.software_perm.val = 0xFFFFFFFF,
	};

	int res;

	res = __cri_create_root(3, &root);
	if (res) return res;
	res = cri_obliterate_root(3);
	if (res) return res;
	return 0;
#endif
	c_log("Calling cri_obliterate_root\n");
	int ret = cri_obliterate_root(3);
	return ret;
}

#define BUFSIZE 256

static int process_data(char *input_data, size_t input_size)
{
	(void)input_size;

	c_log("Note: input data not used\n");

	int res = verify_otp_root();
	if (res) {
		c_error("OTP ROOT failed: %d\n", res);
	}
	return snprintf(input_data, BUFSIZE,
			(res ? "failed: res %d\n" : "OK\n"), res);
}

int main(void)
{
	c_log("Sample (otp sub) container starting...\n");

	const cri_sic_t sic = cri_sic_open(0, CRI_UNIT_CONTAINER_SAMPLE);
	if (!cri_is_valid(sic)) {
		c_error("SIC open failed: %d\n", sic);
		return 1;
	}

	char buf[BUFSIZE];
	uint32_t peer;
	size_t msglen = sizeof(buf);
	int ret = cri_sic_read(sic, buf, &msglen, &peer);
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
			msglen = process_data(buf, msglen);

			c_log("Sending sic message to 0x%x\n", peer);
			ret = cri_sic_write(sic, buf, msglen, peer);
			if (ret) {
				c_log("cri_sic_write() returned %d\n", ret);
				break;
			}
			msglen = sizeof(buf);
			ret = cri_sic_read(sic, buf, &msglen, &peer);
			if (ret) {
				c_log("cri_sic_read() returned %d\n", ret);
				break;
			}
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
	c_log("Sample container exiting.\n");
	return 1;
}
