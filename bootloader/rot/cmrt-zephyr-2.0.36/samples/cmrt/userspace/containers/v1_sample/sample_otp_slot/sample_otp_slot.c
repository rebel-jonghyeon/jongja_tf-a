/*
 * Copyright (c) 2018-2023 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

/**
 * @file
 * @brief Sample container to exercise OTP write functions,
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
#include <cri/cmrt/omc.h>

#define BUFSIZE 256

static int process_data(char *input_data, size_t input_size)
{
	(void)input_size;
	int res = 1;
	cri_otp_t otp;

	c_log("Note: input data not used\n");

	otp = cri_otp_open(CRI_O_SYNC);
	if (cri_is_valid(otp)) {
		/* perso has set this already, so should fail */
		static const uint8_t devid[12] = "DEV-ID-XXXXX";
		res = cri_otp_write_device_id(otp, devid, sizeof(devid));
		c_log("write device ID: res %d\n", res);
		cri_otp_close(otp);
	}

	otp = cri_otp_open(CRI_O_SYNC);
	if (cri_is_valid(otp)) {
		static const uint8_t oemid[8] = "OEM-ID-X";
		res = cri_otp_write_oem_id(otp, oemid, sizeof(oemid));
		c_log("write OEM ID: res %d\n", res);
		cri_otp_close(otp);
	}

	otp = cri_otp_open(CRI_O_SYNC);
	if (cri_is_valid(otp)) {
		/* perso has set this already, so should fail */
		const uint32_t tdv[OMC_TDV_WORDS] = {
			0x00000000, 0x11111111, 0x22222222, 0x33333333,
		};
		res = cri_otp_set_tdv(otp, tdv);
		c_log("write tdv: res %d\n", res);
		cri_otp_close(otp);
	}

	otp = cri_otp_open(CRI_O_SYNC);
	if (cri_is_valid(otp)) {
		res = cri_otp_set_lifecycle(otp, 0x20010D03); /* MISSION */
		c_log("write lifecycle: res %d\n", res);
		cri_otp_close(otp);
	}

	otp = cri_otp_open(CRI_O_SYNC);
	if (cri_is_valid(otp)) {
		cmrt_omc_key_split_t keysplit = {
		   .key = { 0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77,
			    0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff,
			    0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77,
			    0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff
			   }
		  };
		res = cri_otp_write_keysplit(otp, 3, &keysplit);
		c_log("write keysplit 3: res %d\n", res);
		cri_otp_close(otp);
	}

	otp = cri_otp_open(CRI_O_SYNC);
	if (cri_is_valid(otp)) {
		res = cri_otp_obliterate_perso(otp);
		c_log("disable manufacturing root: res %d\n", res);
		cri_otp_close(otp);
	}

	return snprintf(input_data, BUFSIZE,
			(res ? "failed: res %d\n" : "OK\n"), res);
}

int main(void)
{
	c_log("Sample (otp slot) container starting...\n");

	const cri_sic_t sic = cri_sic_open(0, 100);
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
