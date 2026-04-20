/*
 * Copyright (c) 2019-2023 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

/**
 * @file
 * @brief Sample container to demonstrate Key Derivation using KDC.
 */

#include <string.h>
#include <stdalign.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <cri/cmrt.h>
#include "crisyscall-user.h"
#include "crilog-user.h"
#include <cri/cmrt/sic.h>
#include <cri/cmrt/kdc.h>

#define BUFSIZE 256

static int process_data(uint8_t *input_data, size_t input_size)
{
	(void)input_size;

	cri_kdc_t kdc;
	static const char diversify_path[] = "it's magic";
	int res = -1;

	/* HLOS feed base key id. See KEY_ID_DGOK, KEY_ID_OTP_KEYSPLIT, etc. */
	uint32_t keyid = *(uint32_t *)input_data;

	c_log("KDC open\n");
	if (!cri_is_valid(kdc = cri_kdc_open(CRI_O_SYNC))) {
		c_error("failed to open KDC\n");
		goto out;
	}

	c_log("KDC open with keyid: %08x\n", keyid);

	kdc_cmd_t cmd = {
		.base_key_id = keyid,
		.dest = KDC_DEST_SW,
		/*
		 * The +1 is necessary due to KDC's definition
		 * of diversify length.
		 */
		.diversify_len = strlen(diversify_path) + 1
	};
	memcpy(cmd.diversify_path, diversify_path, strlen(diversify_path));
	res = cri_kdc_derive_key(kdc, &cmd);
	cri_kdc_close(kdc);

out:
	if (res == 0) {
		memcpy(input_data, cmd.key, KDC_KEY_SIZE);
		return KDC_KEY_SIZE;
	} else {
		memset(input_data, 0, 4);
		return 4;
	}
}

int main(void)
{
	c_log("Sample (kdc) container starting...\n");

	const cri_sic_t sic = cri_sic_open(0, CRI_UNIT_CONTAINER_SAMPLE);
	if (!cri_is_valid(sic)) {
		c_error("SIC open failed: %d\n", sic);
		return 1;
	}

	alignas(4) char buf[BUFSIZE];
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
