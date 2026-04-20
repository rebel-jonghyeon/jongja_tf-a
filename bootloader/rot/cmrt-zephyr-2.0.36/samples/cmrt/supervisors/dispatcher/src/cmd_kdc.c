/*
 * Copyright (c) 2020-2023 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

#include <stdio.h>
#include <string.h>

#include <device.h>
#include <cri/cmrt/hc.h>

#include "common.h"


struct kdc_args {
	uint8_t keyid; /* key id, use the long key always */
	uint8_t dlen;  /* diversify path length */
	uint8_t dest;  /* by default is KDC_DEST_SW */
	uint8_t reserved[1];
	uint8_t path[0]; /* the path */
};


static size_t min(size_t a, size_t b) { return (a < b) ? a : b; }

static int derive(const struct kdc_args *args, uint8_t *buf, size_t buflen)
{
	int res = -1;
	kdc_cmd_t cmd = {
		.base_key_id = args->keyid,
		.diversify_len = args->dlen + 1,
		.dest = args->dest,
	};
	/* We only support the long keys for now */
	if ((args->dlen > sizeof(cmd.diversify_path)) || (buflen < 32)) {
		return -1;
	}
	/* If dest is KTC, we must have use_keydests set properly in footer.json */
	memcpy(cmd.diversify_path, args->path, args->dlen);
	cri_kdc_t kdc = cri_kdc_open(0);
	/* we will not set the derive path now, it is set to private
	   key hash + handling caveats (i.e., silo).  Note that this
	   is actually whatever it needs to be for the stuff.

	   cri_kdc_set_derive_path(kdc, kdc_drv_path_t *drvpath);
	 */
	if (cri_is_valid(kdc)) {
		res = cri_kdc_derive_key(kdc, &cmd);
		if (res >= 0)
			res = cri_kdc_sync(kdc);
		if (res >= 0) {
			size_t n = min(32, buflen);
			memcpy(buf, cmd.key, n);
			res = n;
		}
		cri_kdc_close(kdc);
	}

	return res;
}


static int kdc_run(void *input, u32_t in_used,
		   void *output, u32_t *out_used, u32_t out_size)
{
	int res = -1;
	struct kdc_args *args = (struct kdc_args *)input;
	if (in_used >= sizeof(struct kdc_args) + args->dlen) {
		res = derive(args, output, out_size);
		if (res >= 0) {
			*out_used = res;
			res = 0; /* expected */
		}
	}
	if (res < 0) {
		*out_used = 0;
	}
	return res;
}

const cmd_t cmd_kdc = {
	CMDID_KDC, "KDC", "Derive keys with KDC", kdc_run
};
