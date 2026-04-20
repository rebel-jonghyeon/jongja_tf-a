/*
 * Copyright (c) 2019-2023 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

/**
 * @file
 * @brief Sample container to show how to transfer a key to SOC key
 *        destination 2 using KTC.
 */

#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <cri/cmrt.h>
#include "crisyscall-user.h"
#include "crilog-user.h"
#include <cri/cmrt/sic.h>
#include <cri/cmrt/ktc.h>

#define BUFSIZE 256
uint32_t key_buf[BUFSIZE / sizeof(uint32_t)] = {0};

static int transfer_key(uint32_t *key, size_t size)
{
	ktc_cmd_t p = {
		.metadata = { 0x1234, 0x5678 },
		.destination = 2,
		.key_size = size,
		.key = key
	};

	cri_ktc_t ktc = cri_ktc_open();
	if (!cri_is_valid(ktc)) {
		c_error("Failed to open ktc\n");
		return -1;
	}

	c_log("Transfer key (size %u)\n", size);
	int res = cri_ktc_export_key(ktc, &p);
	if (res)
		c_error("Key export failed for key size %u (%d)\n", size, res);

	cri_ktc_close(ktc);
	return res;
}

static int init_key_and_transfer(void)
{
	static const uint32_t block[] = {
		0x76543210, 0xfedcba98, 0x33221100, 0x77665544
	};
	char *p = (char *) key_buf;

	for (int i = 0; i + sizeof(block) <= sizeof(key_buf);
	     i += sizeof(block)) {
		memcpy(p + i, block, sizeof(block));
	}

	return transfer_key(key_buf, sizeof(key_buf));
}

static int process_data(char *input_data, size_t input_size)
{
	(void) input_size;

	int ret = init_key_and_transfer();

	if (ret)
		ret = sprintf(input_data, "Key transfer failed (%d).", ret);
	else
		ret = sprintf(input_data, "OK.");

	return ret;
}

int main(void)
{
	c_log("Sample (ktc) container starting...\n");

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
		} else if (fout < 0) {
			c_log("cri_wait() returned %d\n", ret);
			break;
		} else {
			c_log("No sic messages in 30 seconds...\n");
		}
	}
out:
	cri_sic_close(sic);
	c_log("Sample container exiting (ret %d)\n", ret);
	return ret;
}
