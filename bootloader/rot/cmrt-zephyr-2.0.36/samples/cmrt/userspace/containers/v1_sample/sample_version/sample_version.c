/*
 * Copyright (c) 2021-2023 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

/**
 * @file
 * @brief Test container to get OTP counter and binary versions.
 */

#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdalign.h>
#include <cri/cmrt/img_version.h>
#include <cri/cmrt.h>
#include "crilog-user.h"
#include "crisyscall-user.h"
#include <cri/cmrt/sic.h>
enum {
	SIC_BUFSIZE = 256,
	MAX_VERSION_SIZE = 64
};

static int process_data(uint8_t *input_data, size_t input_size)
{
	(void)input_size;
	int res;

	uint8_t cmd = *input_data;
	size_t size = MAX_VERSION_SIZE;
	alignas(4) char version[MAX_VERSION_SIZE];
	switch (cmd) {
	case 'a':
		res = cri_get_img_version(CMRT_TBOOT_IMG_OTP, &version,
					  &size);
		if (res)
			c_error("Get Tboot OTP counter failed: %d\n", res);
		else
			c_log("Tboot Tboot OTP counter: %s\n", version);
		break;
	case 'b':
		res = cri_get_img_version(CMRT_SUPERVISOR_IMG_OTP, &version,
					  &size);
		if (res)
			c_error("Get Supervisor OTP counter failed: %d\n", res);
		else
			c_log("Tboot Supervisor OTP counter: %s\n", version);
		break;
	case 'f':
		res = cri_get_img_version(CMRT_FBOOT_VERSION, &version,
					  &size);
		if (res)
			c_error("Get fboot version failed: %d\n", res);
		else
			c_log("Fboot version: %s\n", version);
		break;
	case 's':
		res = cri_get_img_version(CMRT_SBOOT_VERSION, &version,
					  &size);
		if (res)
			c_error("Get sboot version failed: %d\n", res);
		else
			c_log("Sboot version: %s\n", version);
		break;
	case 'm':
		res = cri_get_img_version(CMRT_SUPERVISOR_VERSION, &version,
					  &size);
		if (res)
			c_error("Get supervisor version failed: %d\n", res);
		else
			c_log("Supervisor version: %s\n", version);
		break;
	default:
		c_error("invalid command %x\n", cmd);
		res = EINVAL;
		break;
	}
	return snprintf((char *)input_data, SIC_BUFSIZE,
			(res ? "failed: res %d\n" : version), res);
}

int main(void)
{
	c_log("Sample (version) container starting...\n");

	const cri_sic_t sic = cri_sic_open(0, CRI_UNIT_CONTAINER_SAMPLE);
	if (!cri_is_valid(sic)) {
		c_error("SIC open failed: %d\n", sic);
		return 1;
	}

	alignas(4) char buf[SIC_BUFSIZE];
	uint32_t peer;
	size_t msglen = sizeof(buf);
	int ret = cri_sic_read(sic, buf, &msglen, &peer);
	if (ret) {
		c_log("cri_sic_read() returned %d\n", ret);
		goto out;
	}
	while (true) {
		const int fout = cri_wait(1, &sic, CRI_SECONDS(30));
		if ((fout > 0) && (fout & 1)) {
			ret = cri_sic_sync(sic);
			if (ret) {
				c_log("cri_sic_sync() returned %d\n", ret);
				break;
			}
			c_log("Received sic message from 0x%x\n", peer);
			msglen = process_data((uint8_t *)buf, msglen);

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
