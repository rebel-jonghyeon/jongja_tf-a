/*
 * Copyright (c) 2017-2023 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

/**
 * @file
 * @brief Sample container to create root 3.
 *        Operation is triggered by SIC message.
 */

#include <string.h>
#include <cri/cmrt.h>
#include <cri/cmrt/sic.h>
#include <cri/cmrt/omc.h>
#include "crisyscall-user.h"
#include "crilog-user.h"

extern cmrt_omc_root_t cri_root;

#define BUFSIZE 256

static size_t process_data(char *buf, size_t buflen)
{
	/* input ignored -- using same buffer for reply */
	(void)buflen;

	int res = cri_create_root(3, &cri_root);
	c_log("create root 3, res %d\n", res);
	if (res != 0) {
		c_error("############ create root failed ############\n");
		c_error("failed to create root 3\n");
		strncpy(buf, "failed: create root 3\n", BUFSIZE);
	} else {
		strncpy(buf, "OK\n", BUFSIZE);
	}
	buf[BUFSIZE-1] = '\0';

	return strlen(buf);
}

int main(void)
{
	c_log("Sample (create root) container starting...\n");

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
	c_log("Sample (create root) container exiting.\n");
	return 0;
}
