/*
 * Copyright (c) 2020-2023 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

/**
 * @file
 * @brief Sample container to perform FFDH private and public key generation
 *        and FFDH Key Exchange operations.
 *        Operations are triggered by SIC message:
 *        's' runs with fixed key, 'g' uses generated keys.
 */

#include <errno.h>
#include <stdio.h>
#include <string.h>

#include <cri/cmrt.h>
#include "crilog-user.h"
#include "crisyscall-user.h"
#include <cri/cmrt/sic.h>
#include <cri/cmrt/pke.h>

static const uint32_t p_2048[64] = {
	0x1e1a1597, 0xdb094ae9, 0xd7ef09ca, 0x693877fa,
	0x6e11715f, 0x6116d227, 0xc198af12, 0xa4b54330,
	0xd7014103, 0x75f26375, 0x54e710c3, 0xc3a3960a,
	0xbd0be621, 0xded4010a, 0x89962856, 0xc0b857f6,
	0x71506026, 0xb3ca3f79, 0xe6b486f6, 0x1ccacb83,
	0x14056425, 0x67e144e5, 0xa41825d9, 0xf6a167b5,
	0x96524d8e, 0x3ad83477, 0x51bfa4ab, 0xf13c6d9a,
	0x35488a0e, 0x2d525267, 0xcaa6b790, 0xb63acae1,
	0x81b23f76, 0x4fdb70c5, 0x12307f5c, 0xbc39a0bf,
	0xb1e59bb8, 0xb941f54e, 0xd45f9088, 0x6c5bfc11,
	0x4275bf7b, 0x22e0b1ef, 0x5b4758c0, 0x91f9e672,
	0x6bcf67ed, 0x5a8a9d30, 0x97517abd, 0x209e0c64,
	0x830e9a7c, 0x3bf4296d, 0x34096faa, 0x16c3d911,
	0x61b2aa30, 0xfaf7df45, 0xd61957d4, 0xe00df8f1,
	0x435e3b00, 0x5d2ceed4, 0x660dd0f2, 0x8ceef608,
	0x65195999, 0xffbbd19c, 0xb4b6663c, 0x87a8e61d,
};
#define MOD_BYTES sizeof(p_2048)
#define MOD_BITS (MOD_BYTES * 8)

static const uint32_t q_2048[64] = {
	0x64f5fbd3, 0xa308b0fe, 0x1eb3750b, 0x99b1a47d,
	0x40129da2, 0xb4479976, 0xa709a097, 0x8cf83642,
};
static const uint32_t g_2048[64] = {
	0x6cc41659, 0x664b4c0f, 0xef98c582, 0x5e2327cf,
	0xd4795451, 0xd647d148, 0x90f00ef8, 0x2f630784,
	0x1db246c3, 0x184b523d, 0xcdc67eb6, 0xc7891428,
	0x0df92b52, 0x7fd02837, 0x64e0ec37, 0xb3353bbb,
	0x57cd0915, 0xecd06e15, 0xdf016199, 0xb7d2bbd2,
	0x052588b9, 0xc8484b1e, 0x13d3fe14, 0xdb2a3b73,
	0xd182ea0a, 0xd052b985, 0xe83b9c80, 0xa4bd1bff,
	0xfb3f2e55, 0xdfc967c1, 0x767164e1, 0xb5045af2,
	0x6f2f9193, 0x1d14348f, 0x428ebc83, 0x64e67982,
	0x82d6ed38, 0x8ac376d2, 0xaab8a862, 0x777de62a,
	0xe9ec144b, 0xddf463e5, 0xc77a57f2, 0x0196f931,
	0x41000a65, 0xa55ae313, 0xc28cbb18, 0x901228f8,
	0x7e8c6f62, 0xbc3773bf, 0x0c6b47b1, 0xbe3a6c1b,
	0xac0bb555, 0xff4fed4a, 0x77be463f, 0x10dbc150,
	0x1a0ba125, 0x07f4793a, 0x21ef2054, 0x4ca7b18f,
	0x60edbd48, 0x2e775066, 0x73134d0b, 0x3fb32c9b,
};

static const uint32_t priv_key_u_2048[64] = {
	0x454ac0f8, 0x29fd50c3, 0xd9143b81, 0xbf49d1ec,
	0x66d54efc, 0x40da18c7, 0x72105eef, 0x6d12b3db,
};

static const uint32_t pub_key_v_2048[64] = {
	0xb896008e, 0xf2d9d1a7, 0x548ab5f9, 0x140ffd68,
	0xd3ee9dee, 0xd292ba77, 0x6f6242a3, 0x4fae396d,
	0x57191d83, 0x0cb13dcd, 0x6ee75218, 0x14223f03,
	0xa388e3e9, 0x8948b333, 0xa3be67e9, 0x97537c84,
	0x52088943, 0xb4bf129a, 0x82a2eda3, 0xe2f969f8,
	0xd51c5c3b, 0x8ea2dcfc, 0x2298ba39, 0x18a5a5df,
	0x6ea23179, 0xa54e0a4d, 0xfab25e2d, 0x6650fc33,
	0x4a8a52e3, 0x84c71956, 0x490f444e, 0xc8763242,
	0xb7f79d30, 0xa0bd9692, 0x71e109fd, 0xea307e3f,
	0x31054f9a, 0x66c9c015, 0xd96d1dd8, 0x91aa14ac,
	0x956160c0, 0xd3915a0a, 0x64b86c4b, 0xb35ad5b0,
	0x73d14759, 0x65704c21, 0x5bb8befb, 0x6005ced6,
	0x52f3829b, 0xe54e8dec, 0x27936800, 0x05dedaf3,
	0x7e66b2f1, 0x8dc8926c, 0x09cbd78a, 0x5b438123,
	0xd57828e7, 0x230826e9, 0xd3a1d03b, 0x5b09663d,
	0x3b0ae337, 0xce9507b2, 0x3fef9586, 0x7d04b9e5,
};

static const uint32_t exp_shared_key_2048[64] = {
	0x2697864b, 0x8b09781d, 0xfaa68565, 0xf273937f,
	0x378b87ba, 0xe3e23bfe, 0x961b313f, 0xf0cf176e,
	0xf0914434, 0x467d92da, 0x8a6be150, 0x1fe7154b,
	0x3f5233d1, 0xd9fc1a97, 0xf69b6db0, 0x39c77e66,
	0x3c4f95d7, 0x1d984ef6, 0x4dccbff3, 0x69fd246d,
	0x662b0936, 0xc4ec9b82, 0x8982c821, 0x0f7555cf,
	0x2d654355, 0xf574d75e, 0xb29a6aae, 0x60830d96,
	0x7e198d67, 0x42b6b777, 0x67adaf90, 0x0e0c6d80,
	0x5455d43c, 0xa7aee543, 0x27bc55a0, 0x7983262f,
	0xf9218545, 0x224653d4, 0xf3c7c22b, 0x23973d05,
	0xb8218edf, 0xa3b8d206, 0xc95e466a, 0x23763bdd,
	0x42da1de2, 0x37efa52c, 0x9ca430da, 0xd7eb95f2,
	0x0fe9426d, 0xdfa8804a, 0x0a2ba810, 0x9117d75a,
	0xd4975c97, 0xa444941e, 0x62ad94e8, 0xd2b84444,
	0x8e2d48b5, 0x32bc9258, 0x1c1b85e6, 0x3c2ad650,
	0x304bebd8, 0x9451db4d, 0xf31bf350, 0x44f48409,
};

static void print_data(const char *name, const void *data,
		       const void *data_ev, size_t size)
{
	c_log("%s:\n", name);
	hexdump(data, size);

	if (data_ev) {
		c_log("expected %s:\n", name);
		hexdump(data_ev, size);
	}
}

static int do_dh(int use_fix_key)
{
	uint32_t priv_key[MOD_BYTES/4] = { 0 };
	uint32_t pub_key[MOD_BYTES/4] = { 0 };
	uint32_t shared_key[MOD_BYTES/4] = { 0 };
	uint32_t mod_size = MOD_BYTES;

	int res = EIO;
	cri_pke_t pke = cri_pke_open(0);

	if (!cri_is_valid(pke)) {
		c_error("Cannot open PKE\n");
		goto out;
	}
	/* Verify P, Q, G */
	res = cri_pke_ffdh_verify(pke, mod_size, p_2048, mod_size,
				  q_2048, mod_size, g_2048);
	if (res != 0) {
		c_error("Verify P, Q, G parameters failed\n");
		goto out;
	}
	c_log("P, Q, G parameters verified.\n");

	if (use_fix_key) {
		/* Use predefined keys */
		memcpy(priv_key, priv_key_u_2048, mod_size);
		memcpy(pub_key, pub_key_v_2048, mod_size);
	} else {
		res = cri_pke_ffdh_keygen(pke, mod_size, q_2048, priv_key);
		if (res != 0) {
			c_error("Generate private key failed\n");
			goto out;
		}
		res = cri_pke_ffdh(pke, mod_size, p_2048, q_2048, g_2048,
				   priv_key, 0, pub_key, 0);
		if (res != 0) {
			c_error("Generate own public key failed\n");
			goto out;
		}

		print_data("Private key", priv_key, 0, MOD_BYTES);
		print_data("Public key", pub_key, 0, MOD_BYTES);
	}
	res = cri_pke_ffdh(pke, mod_size, p_2048, q_2048, g_2048,
			&priv_key[0], &pub_key[0], NULL, &shared_key[0]);
	if (res != 0) {
		c_error("Generate shared public key failed\n");
		goto out;
	}

	if (use_fix_key) {
		print_data("Shared key", shared_key, exp_shared_key_2048, mod_size);
		if (memcmp(exp_shared_key_2048, shared_key, MOD_BYTES)) {
			c_error("Wrong shared key\n");
			goto out;
		}
	} else {
		print_data("Shared key", shared_key, 0, mod_size);
	}

	res = 0;
out:
	cri_pke_close(pke);
	if (res == 0) {
		c_log("FFDH OK\n");
	} else {
		c_log("FFDH NOK %d\n", res);
	}
	return res;
}

static int process_data(uint8_t *input_data, size_t input_size)
{
	(void) input_size;

	if (input_data) {
		if (*input_data == 'g') {
			/* Generate private and public keys */
			return do_dh(0);
		} else if (*input_data == 's') {
			/* Use predefined keys */
			return do_dh(1);
		}
	}
	c_error("Wrong command\n");
	return ENODEV;
}

#define BUFSIZE 256

int main(void)
{
	c_log("Sample (ffdh) container starting...\n");

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
			ret = process_data((uint8_t *)buf, msglen);

			msglen = snprintf(buf, sizeof(buf),
					  (ret ? "failed: res %d\n" : "OK\n"),
					  ret);
			c_log("Result %s", buf);

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
	c_log("Sample (ffdh) container exiting.\n");
	return 0;
}
