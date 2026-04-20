/*
 * Copyright (c) 2021 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <cri/cmrt/omc.h>
#include "common.h"
#include "oec_common.h"


enum otp_command {
	OTP_ENCRYPT = 1,
	OTP_WRITE = 4
};

struct otp_args {
	uint32_t command;
	uint32_t args[2];
	uint32_t nbytes;
	uint8_t data[0];
};

/* 1. derive a key by otp and select the data to write (file on filesystem)
 * 2. encrypt the otp image with aes, write the image out (assuming outside
 * is sufficient for the output.
 */
static int otp_run(void *input, u32_t in_used,
		   void *output, u32_t *out_used, u32_t out_size)
{
	struct otp_args *args = input;
	if (((args->command & ~(OTP_WRITE | OTP_ENCRYPT)) != 0u) ||
	    (in_used < sizeof(struct otp_args) + args->nbytes) ||
	    ((args->command & OTP_ENCRYPT) && (args->nbytes > out_size))) {
		*out_used = 0;
		return -1;
	}
	int res = 0;
	size_t buflen = args->nbytes;
	const void *wbuf = args->data;
	if (args->command & OTP_ENCRYPT) {
		buflen = oec_image_encrypt(args->data, args->nbytes, 0);
		/* should have same things here */
		if (buflen <= out_size) {
			out_size = buflen;
		} else {
			out_size = 0;
		}
		memcpy(output, input, out_size);
		buflen = out_size;
		wbuf = output;
	} else {
		out_size = 0;
	}
	if (args->command & OTP_WRITE) {
		res = oec_image_update(wbuf, buflen, 1);
	}

	*out_used = out_size;

	return res;
}

const cmd_t cmd_otp = { CMDID_OTP, "OTP", "otp operations", otp_run };
