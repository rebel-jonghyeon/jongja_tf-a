/*
 * Copyright (c) 2024 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <errno.h>
#include <ctype.h>
#include <sys/types.h>
#include <stdalign.h>

#include <container.h>
#include <logging/log.h>
#include <drivers/cmrt/cmrt.h>
#include <drivers/cmrt/kdc.h>
#include <drivers/cmrt/sic.h>
#include <drivers/cmrt/dmac.h>
#include <drivers/cmrt/pke.h>

#define FLOWID 100

alignas(4) static uint8_t g_buf_dmac[1024] = {0};
alignas(4) static uint8_t g_buf_sic[1024] = {0};
static_assert(sizeof(g_buf_dmac) % 4 == 0,
	"DMAC buffer size must be multiple of 4");

alignas(4) static const uint8_t g_key_priv[] = {
	0xc7, 0x20, 0x7c, 0x3d, 0xac, 0x89, 0x34, 0xde,
	0x7e, 0x01, 0xd7, 0xda, 0x89, 0xce, 0x08, 0x5e,
	0xfb, 0xe2, 0xc8, 0x4e, 0x62, 0x2d, 0x43, 0x9d,
	0xfa, 0x5c, 0x83, 0xb2, 0xa8, 0x32, 0xfb, 0x3b
};

alignas(4) static const uint8_t g_expected_pubx[] = {
	0x96, 0x51, 0x63, 0x6e, 0x11, 0xd7, 0xe5, 0x96,
	0xd5, 0x34, 0xc0, 0x10, 0x6b, 0xef, 0x5d, 0x42,
	0x82, 0x2c, 0x3d, 0x48, 0xde, 0x05, 0xcb, 0x08,
	0x4c, 0x1e, 0x86, 0xe4, 0xac, 0xe0, 0x4b, 0xa8
};

alignas(4) static const uint8_t g_expected_puby[] = {
	0xa1, 0x3b, 0xb6, 0x1d, 0x77, 0xa7, 0x52, 0xa7,
	0x87, 0x0e, 0xed, 0x49, 0x9e, 0xf1, 0x9d, 0x44,
	0xb3, 0x53, 0x31, 0xec, 0x68, 0xe8, 0x36, 0xf6,
	0x51, 0x94, 0xbf, 0x14, 0x1e, 0xfa, 0xf3, 0x39
};

alignas(4) uint8_t g_pubx[32] = {0x5a};
alignas(4) uint8_t g_puby[32] = {0x5a};

/* true iff buf is filled with the 4-byte `pattern` for `nw` words. */
static bool memcmp_pattern(uint32_t pattern, const uint8_t *buf, size_t nw)
{
	size_t i;
	for (i=0; i < nw; i++) {
		if (((uint32_t *)buf)[i] != pattern) { break; }
	}

	if (i == nw) {
		return true;
	}

	return false;
}

static int start_kdc_derive(cmrt_kdc_t kdc, cmrt_kdc_cmd_t *kdc_cmd)
{
	memset(kdc_cmd, 0, sizeof(*kdc_cmd));

	kdc_cmd->diversify_len = 7;
	kdc_cmd->base_key_id = KEY_ID_SNAK;
	kdc_cmd->dest = KDC_DEST_SW;

	memcpy(kdc_cmd->diversify_path, "diverse", 7);

	int rc = cmrt_kdc_derive_key(kdc, kdc_cmd);
	if (rc) {
		LOG_ERR("cmrt_kdc_derive failed (%d)", rc);
		return rc;
	}

	return 0;
}

static int check_kdc_output()
{
	if (memcmp_pattern(0x5a5a5a5a, g_pubx, sizeof(g_pubx)/4)) {
		LOG_ERR("PKE output (%s) matches initial pattern: PKE failed", "pubx");
		return -1;
	}

	if (memcmp_pattern(0x5a5a5a5a, g_puby, sizeof(g_puby)/4)) {
		LOG_ERR("PKE output (%s) matches initial pattern: PKE failed", "puby");
		return -1;
	}

	return 0;
}


static int start_dmac_fill(cmrt_dmac_t dmac)
{
	uint32_t fill_data = 0x5a5a5a5a;
	int rc = cmrt_dmac_fill(dmac, fill_data, (uint32_t)g_buf_dmac,
			sizeof(g_buf_dmac), 0);
	if (rc) {
		LOG_ERR("cmrt_dmac_fill failed (%d)", rc);
		return rc;
	}

	return 0;
}

static int check_dmac_output()
{
	if (memcmp_pattern(0x5a5a5a5a, g_buf_dmac, sizeof(g_buf_dmac)/4)) {
		return 0;
	}

	LOG_ERR("DMAC fill failed (fill pattern not matched in buffer)");
	return -EINVAL;
}

static int start_pke_keygen(cmrt_pke_t pke)
{
	cmrt_ecc_curve_t curve = cmrt_pke_get_curve(CMRT_ECC_CURVE_NIST_P256);
	if (!curve) { return -1; }

	int rc = cmrt_pke_ecdsa_keygen(pke, curve, g_key_priv, g_pubx, g_puby);
	if (rc) {
		LOG_ERR("cmrt_pke_ecdsa_keygen failed (%d)", rc);
		return rc;
	}

	return 0;
}

static int check_pke_output()
{
	if (memcmp(g_pubx, g_expected_pubx, sizeof(g_expected_pubx)/4)) {
		LOG_ERR("PKE failed (unexpected output %s)", "pubx");
		return -EINVAL;
	}

	if (memcmp(g_puby, g_expected_puby, sizeof(g_expected_puby)/4)) {
		LOG_ERR("PKE failed (unexpected output %s)", "puby");
		return -EINVAL;
	}

	return 0;
}

static int do_concurrent()
{
	int rc = -1;
	cmrt_kdc_t kdc = CMRT_INVALID_HANDLE;
	cmrt_dmac_t dmac = CMRT_INVALID_HANDLE;
	cmrt_pke_t pke = CMRT_INVALID_HANDLE;
	cmrt_sic_t sic = CMRT_INVALID_HANDLE;
	/* The following needs to live until the cmrt_kdc_sync call. */
	cmrt_kdc_cmd_t kdc_cmd;

	kdc = cmrt_kdc_open(0);
	if (!cmrt_is_valid(kdc)) {
		LOG_ERR("cmrt_kdc_open failed");
		return -1;
	}

	dmac = cmrt_dmac_open(0);
	if (!cmrt_is_valid(dmac)) {
		LOG_ERR("cmrt_dmac_open failed");
		goto out;
	}

	pke = cmrt_pke_open(0);
	if (!cmrt_is_valid(pke)) {
		LOG_ERR("cmrt_pke_open failed");
		goto out;
	}

	sic = cmrt_sic_open(0, FLOWID);
	if (!cmrt_is_valid(sic)) {
		LOG_ERR("cmrt_sic_open failed");
		goto out;
	}

	uint32_t peerid = -1;
	size_t bufsz = sizeof(g_buf_sic);
	rc = cmrt_sic_read(sic, g_buf_sic, &bufsz, &peerid, 0);
	if (rc) { goto out; }
	LOG_INF("Started SIC echo");

	LOG_INF("Waiting on all operations...");
	cmrt_handle_t handles[] = { kdc, dmac, pke, sic };
	uint32_t cores_done = 0;
	while (cores_done != 0x0f && (rc = cmrt_wait(4, handles, CMRT_FOREVER)) > 0) {
		LOG_INF("In wait loop. cmrt_wait: 0x%08x", rc);
		uint32_t ready = (uint32_t)rc;

		if (ready & (1U << 0)) { /* kdc */
			if (cores_done & (1U << 0)) {
				/* For testing purposes, make sure that a core is handled only
				 * once, since we only do one operation per core.
				 * This applies to all the other handling branches. */
				LOG_ERR("KDC op already synced!");
				rc = -1;
				goto out;
			}

			rc = cmrt_kdc_sync(kdc);
			if (rc) {
				LOG_ERR("cmrt_kdc_sync failed (%d)", rc);
				goto out;
			}
			LOG_INF("KDC derive finished");
			LOG_HEXDUMP_INF((uint8_t *)kdc_cmd.key, 32, "key:");

			rc = check_kdc_output();
			if (rc) { goto out; }

			cores_done |= (1U << 0);
		}

		if (ready & (1U << 1)) { /* dmac */
			if (cores_done & (1U << 1)) {
				LOG_ERR("DMAC op already synced!");
				rc = -1;
				goto out;
			}

			rc = cmrt_dmac_sync(dmac);
			if (rc) {
				LOG_ERR("cmrt_dmac_sync failed (%d)", rc);
				goto out;
			}
			LOG_INF("DMAC fill finished");
			LOG_HEXDUMP_INF(g_buf_dmac, 16, "buf begin");
			LOG_HEXDUMP_INF(g_buf_dmac+sizeof(g_buf_dmac)-16, 16, "buf end");

			rc = check_dmac_output();
			if (rc) { goto out; }

			cores_done |= (1U << 1);
		}

		if (ready & (1U << 2)) { /* pke */
			if (cores_done & (1U << 2)) {
				LOG_ERR("PKE op already synced!");
				rc = -1;
				goto out;
			}

			rc = cmrt_pke_sync(pke);
			if (rc) {
				LOG_ERR("cmrt_pke_sync failed (%d)", rc);
				goto out;
			}
			LOG_INF("PKE keygen finished");
			LOG_HEXDUMP_INF(g_pubx, 32, "g_pubx");
			LOG_HEXDUMP_INF(g_puby, 32, "g_puby");

			rc = check_pke_output();
			if (rc) { goto out; }

			cores_done |= (1U << 2);
		}

		if (ready & (1U << 3)) { /* sic */
			rc = cmrt_sic_sync(sic);
			if (rc) {
				LOG_ERR("cmrt_sic_sync failed (%d)", rc);
				goto out;
			}

			LOG_INF("Got SIC msg (%zu bytes)", bufsz);
			LOG_HEXDUMP_INF(g_buf_sic, 16, "Msg:");

			rc = start_kdc_derive(kdc, &kdc_cmd);
			if (rc) { goto out; }
			LOG_INF("Started KDC derive");

			rc = start_dmac_fill(dmac);
			if (rc) { goto out; }
			LOG_INF("Started DMAC fill");

			rc = start_pke_keygen(pke);
			if (rc) { goto out; }
			LOG_INF("Started PKE keygen");

			rc = cmrt_sic_write(sic, g_buf_sic, bufsz, peerid);
			if (rc) {
				LOG_ERR("cmrt_sic_write failed (%d)", rc);
				goto out;
			}

			cores_done |= (1U << 3);
		}
	}

	if (rc < 0) {
		LOG_ERR("cmrt_wait failed (%d)", rc);
		goto out;
	}

	rc = 0;
out:
	if (cmrt_is_valid(kdc)) { cmrt_kdc_close(kdc); }
	if (cmrt_is_valid(dmac)) { cmrt_dmac_close(dmac); }
	if (cmrt_is_valid(pke)) { cmrt_pke_close(pke); }
	if (cmrt_is_valid(sic)) { cmrt_sic_close(sic); }
	return rc;
}

void main(void)
{
	cmrt_sic_write_reg(R_SCRATCH_0, 0xdeadbeef);

	int res = do_concurrent();

	cmrt_sic_write_reg(R_SCRATCH_0, (uint32_t)res);

	LOG_ERR("Container exited with %d!", res);
}
