/*
 * Copyright (c) 2017-2023 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

#include <fboot.h>
#include <cmrt_mpu.h>
#include "supervisor.h"

#include <logging/log.h>
LOG_MODULE_DECLARE(cmrt, CONFIG_CMRT_LOG_LEVEL);

bool fboot_memmatch(cmrt_cc_t cc, const void *s1, const void *s2, size_t n)
{
	if (!is_aligned(s1, 4u) || !is_aligned(s2, 4u) || !is_aligned(n, 4u)) {
		/* Everything needs to be word aligned. */
		return false;
	}
	/*
	 * Timing constant word compare which returns zero if there are
	 * no differences. Feed the comparison values to canary core to
	 * make sure glitching the call to fboot_memmatch will not be enough
	 * to bypass the comparison.
	 */
	const uint32_t *w1 = s1;
	const uint32_t *w2 = s2;
	uint32_t res = 0;
	for (n >>= 2; n != 0u; n--) {
		if (cmrt_is_valid(cc)) {
			(void)cmrt_cc_mix(cc, *w1 ^ *w2);
		}
		res |= *w1 ^ *w2;
		++w1;
		++w2;
	}
	return res == 0u;
}

static inline cmrt_hc_t hash_open(uint32_t flags)
{
	/* Open fboot hash core statically without device_get_binding. */
	return (cmrt_hc_t)cmrt_dd_open(DEVICE_DT_GET(DT_CHOSEN(rambus_fboot_hc)), flags, NULL);
}

static cmrt_hc_t hash_init(cmrt_hc_t hc, cmrt_hash_algo_t algo)
{
	if (!cmrt_is_valid(hc)) {
		hc = hash_open(0);
		if (!cmrt_is_valid(hc)) { return CMRT_INVALID_HANDLE; }
	}
	int res = cmrt_hc_init(hc, algo, NULL, 0);
	if (res != 0) {
		LOG_INF("Cannot init hash: %d", res);
		cmrt_hc_close(hc);
		return CMRT_INVALID_HANDLE;
	}
	return hc;
}

static int hash_update(cmrt_hc_t hc, const void *data, size_t size)
{
	int res = cmrt_hc_update(hc, data, size);
	if (res != 0) {
		LOG_INF("Cannot update hash: %d", res);
		cmrt_hc_close(hc);
	}
	return res;
}

static int hash_final(cmrt_hc_t hc, void *digest)
{
	size_t size = SHA512_BYTES; /* max, assume caller has it right */
	int res = cmrt_hc_final(hc, NULL, 0, digest, &size);
	if (res != 0) { LOG_INF("Cannot final hash: %d", res); }
	cmrt_hc_close(hc);
	return res;
}

int fboot_hash(cmrt_hc_t hc, cmrt_hash_algo_t algo, const void *data, size_t size, void *digest)
{
	int res = -EIO;
	hc = hash_init(hc, algo);
	if (cmrt_is_valid(hc)) {
		res = hash_update(hc, data, size);
		if (res == 0) { res = hash_final(hc, digest); }
	}
	return res;
}

int fboot_hash2(cmrt_hc_t hc, cmrt_hash_algo_t algo, const void *data1, size_t size1, const void *data2, size_t size2, void *digest)
{
	int res = -EIO;
	hc = hash_init(hc, algo);
	if (cmrt_is_valid(hc)) {
		res = hash_update(hc, data1, size1);
		if (res == 0) { res = hash_update(hc, data2, size2); }
		if (res == 0) { res = hash_final(hc, digest); }
	}
	return res;
}

static int verify_ecdsa(cmrt_cc_t cc, uint32_t pktype, const uint8_t *pub, const uint8_t *digest, const uint8_t *signature)
{
	/* We cast it to uint32_t * later, so it must be well-aligned. */
	if (((uintptr_t)signature & (sizeof(uint32_t) - 1u)) != 0u) {
		return -EINVAL;
	}

	cmrt_ecc_curve_t curve;
	uint32_t digestlen;
	switch (pktype) {
	case PK_ECDSA_P256:
		curve = cmrt_pke_get_curve(CMRT_ECC_CURVE_NIST_P256);
		digestlen = SHA256_BYTES;
		break;
#ifdef CONFIG_CMRT_FBOOT_HAS_ECDSA_P521
	case PK_ECDSA_P521:
		curve = cmrt_pke_get_curve(CMRT_ECC_CURVE_NIST_P521);
		digestlen = SHA512_BYTES;
		break;
#endif
#ifdef CONFIG_CMRT_FBOOT_HAS_ECDSA_P384
	case PK_ECDSA_P384:
		curve = cmrt_pke_get_curve(CMRT_ECC_CURVE_NIST_P384);
		digestlen = SHA384_BYTES;
		break;
#endif
	default:
		return -EINVAL;
	}

	cmrt_pke_t pke = cmrt_pke_open(CMRT_O_SYNC);
	if (curve == NULL || !cmrt_is_valid(pke)) { return -ENODEV; }

	uint32_t comp_r[PKERAM_SLOT_WORDS] = { 0 };
	uint32_t curvelen = cmrt_pke_get_curve_length(curve);
	int res = cmrt_pke_ecdsa_verify_hash(pke, curve, pub, pub + curvelen,
				       digest, digestlen, signature,
				       signature + curvelen, comp_r);
	cmrt_pke_close(pke);
	const uint32_t *sign_r = (const uint32_t *)signature;
	for (size_t i = 0; i < SHA256_WORDS; i++) {
		/*
		 * Mix the minimum number of words (zeros) for all pktypes.
		 * We cannot really do more because we already have set CC
		 * to the expected value.
		 */
		if (cc != NULL) { (void)cmrt_cc_mix(cc, sign_r[i] ^ comp_r[i]); }
	}
#ifdef CONFIG_CMRT_FIPS_140_MODE
	LOG_INF("Zero ecdsa verification output");
	(void)memset(comp_r, 0x00, curvelen);
#endif
	if (res != 0) {
		LOG_INF("Ecdsa verify failed: %d", res);
		LOG_HEXDUMP_INF(digest, curvelen, "digest:");
		return -EPERM;
	}
	LOG_INF("ECDSA verify OK.");

	return 0;
}

static int derive_hmac_key(uint32_t id, uint8_t silo, cmrt_hc_t hc)
{
	cmrt_kdc_t kdc = cmrt_kdc_open(CMRT_O_SYNC);
	if (!cmrt_is_valid(kdc)) { return -ENODEV; }

	cmrt_kdc_cmd_t cmd;
	(void)memset(&cmd, 0, sizeof(cmd));
	/* Use zeroed full size diversify path. */
	cmd.diversify_len = 16;
	uint8_t *silop = (uint8_t *)cmd.diversify_path;
	/* And the 16th byte is silo. */
	silop[15] = silo;
	cmd.base_key_id = id;
	int res = cmrt_hc_kdc_cmd(hc, CMRT_HASH_SHA256, KDC_KEY_SIZE, &cmd);
	if (res == 0) { res = cmrt_kdc_derive_key(kdc, &cmd); }
	if (res != 0) { LOG_INF("Failed to derive key: %d", res); }
	cmrt_kdc_close(kdc);

	return res;
}

int fboot_verify_cid(cmrt_cc_t cc, const cmrt_img_footer_t *footer, const void *pkhash)
{
	uint32_t digest[SHA256_WORDS];
	int res = fboot_hash2(NULL, CMRT_HASH_SHA256, &footer->public_key_type,
			      sizeof(footer->public_key_type),
			      footer->public_key, footer->public_key_length,
			      digest);
	if (res != 0) { return res; }

	/* Public key hash must match to given pkhash. */
	if (pkhash != NULL) {
		if (!fboot_memmatch(cc, pkhash, digest, sizeof(digest))) {
			LOG_INF("Invalid public key hash");
			return -EFAULT;
		}
	}
	/* Container id prefix must be public key hash. */
	if (!fboot_memmatch(cc, footer->scid.cid.root.hash, digest, sizeof(digest))) {
		LOG_INF("Invalid container id");
		return -EPERM;
	}
	return 0;
}

int img_digest(cmrt_hc_t hc, cmrt_hash_algo_t algo, const void *blob, size_t size, const cmrt_img_footer_t *footer, void *digest)
{
	return fboot_hash2(hc, algo, blob,
			   size - footer->signature_length - sizeof(footer->footer_length),
			   (uint8_t *)blob + size - sizeof(footer->footer_length),
			   sizeof(footer->footer_length), digest);
}

int fboot_verify_hmac(cmrt_cc_t cc, const void *blob, size_t size, const void *pkhash, const cmrt_img_footer_t *footer)
{
	if (footer->public_key_type != PK_HMAC_SHA256) {
		LOG_INF("Invalid footer pktype: %d", (int)footer->public_key_type);
		return -EINVAL;
	}
	int res = fboot_verify_cid(cc, footer, pkhash);
	if (res != 0) { return res; }

	/* Open HC for KDC.*/
	cmrt_hc_t hc = hash_open(CMRT_O_HWC_KEYED);
	if (!cmrt_is_valid(hc)) { return -ENODEV; }

	/* Derive key for hmac, key will be put into HC. */
	res = derive_hmac_key(KEY_ID_PNAK, CAVEAT_SILO, hc); /* always silo */
	if (res != 0) {
		LOG_INF("PNAK derivation failed: %d", res);
		cmrt_hc_close(hc);
		return res;
	}
	/* Calculate hmac over the image and footer. */
	uint32_t digest[SHA256_WORDS];
	res = img_digest(hc, CMRT_HASH_SHA256, blob, size, footer, digest);
	if (res != 0) { return res; } /* hc is closed in img_digest */

	/* It must match image signature. */
	if (!fboot_memmatch(cc, footer->signature, digest, sizeof(digest))) {
		LOG_INF("Invalid signature");
		return -EPERM;
	}
	LOG_INF("HMAC verify OK.");
	return 0;
}

int fboot_verify_sig(cmrt_cc_t cc, const void *blob, size_t size, const void *pkhash, const cmrt_img_footer_t *footer)
{
	int res = fboot_verify_cid(cc, footer, pkhash);
	if (res != 0) { return res; }
	/*
	 * Reserve enough digest space for the digest for all public key types.
	 * PKE driver copies curve length amount of the digest and for P-521
	 * it is 64 bytes.
	 */
	uint32_t digest[SHA3_512_WORDS];
	const uint8_t *d = (const uint8_t *)digest;
	switch (footer->public_key_type) {
	case PK_ECDSA_P256:
		/* Calculate hash over the image and footer. */
		res = img_digest(NULL, CMRT_HASH_SHA256, blob, size, footer, digest);
		if (res != 0) { break; }
		res = verify_ecdsa(cc, footer->public_key_type, footer->public_key, d, footer->signature);
		break;
#ifdef CONFIG_CMRT_FBOOT_HAS_ECDSA_P521
	case PK_ECDSA_P521:
		/* Calculate hash over the image and footer. */
		res = img_digest(NULL, HC_HASH_ALGO_SHA_512, blob, size, footer, digest);
		if (res != 0) { break; }
		res = verify_ecdsa(cc, footer->public_key_type, footer->public_key, d, footer->signature);
		break;
#endif
#ifdef CONFIG_CMRT_FBOOT_HAS_RSA_VERIFY
	case PK_RSAPSS_3K:
	case PK_RSAPSS_4K:
		/* Calculate hash over the image and footer. */
		res = img_digest(NULL, HC_HASH_ALGO_SHA3_512, blob, size, footer, digest);
		if (res != 0) { break; }
		res = fboot_verify_rsa(cc, footer->public_key_length, (uint32_t *)footer->public_key, (const uint32_t *)digest, (uint32_t *)footer->signature);
		break;
#endif
#ifdef CONFIG_CMRT_SUPERVISOR_IN_ROM
	case PK_SHA256:
		if (!IS_IN_ROM((uint32_t)blob) ||
		    !IS_IN_ROM((uint32_t)blob + size)) {
			/* Plain SHA256 is only allowed for ROM images. */
			res = -EPERM;
			break;
		}
		/* Calculate hash over the image and footer. */
		res = img_digest(NULL, CMRT_HASH_SHA256, blob, size, footer, digest);
		if (res != 0) { break; }
		if (!fboot_memmatch(cc, digest, footer->signature, SHA256_BYTES)) {
			/* No match for the digest given in footer. */
			res = -EPERM;
		}
		break;
#endif
#ifdef CONFIG_CMRT_FBOOT_HAS_LMS_VERIFY
	case PK_LMS:
		/* Calculate hash over the image and footer. */
		res = img_digest(NULL, CMRT_HASH_SHA256, blob, size, footer, digest);
		if (res != 0) { break; }
		res = fboot_verify_lms(cc, (const uint8_t *)footer->public_key,
				       (const uint8_t *)d, SHA256_BYTES,
				       (const uint8_t *)footer->signature);
		break;
#endif
#ifdef CONFIG_CMRT_FBOOT_HAS_LMS_HSS_VERIFY
	case PK_LMS_HSS:
		/* Calculate hash over the image and footer. */
		res = img_digest(NULL, CMRT_HASH_SHA256, blob, size, footer, digest);
		if (res != 0) { break; }
		res = fboot_verify_lms_hss(cc, (const uint8_t *)footer->public_key,
					   (const uint8_t *)d, SHA256_BYTES,
					   (const uint8_t *)footer->signature);
		break;
#endif
#ifdef CONFIG_CMRT_FBOOT_HAS_XMSS_VERIFY
	case PK_XMSS:
	case PK_XMSS_MT:
		res = fboot_verify_xmss(cc, blob, size, footer, digest, sizeof(digest));
		break;
#endif
#ifdef CONFIG_CMRT_FBOOT_HAS_ECDSA_P384
	case PK_ECDSA_P384:
		/* Calculate hash over the image and footer. */
		res = img_digest(NULL, HC_HASH_ALGO_SHA_384, blob, size, footer, digest);
		if (res != 0) { break; }
		res = verify_ecdsa(cc, footer->public_key_type, footer->public_key, d, footer->signature);
		break;
#endif
	default:
		LOG_INF("Invalid footer pktype: %d", (int)footer->public_key_type);
		res = -EINVAL;
		break;
	}
#ifdef CONFIG_CMRT_FIPS_140_MODE
	LOG_INF("Zero image digest");
	(void)memset(digest, 0x00, sizeof(digest));
#endif
	return res;
}

#ifdef CONFIG_CMRT_PMU
__noinit static uint32_t bb_digest[SHA256_WORDS];

int fboot_verify_bb(bool setup)
{
	/* Make sure SRAM was retained correctly. */
	cmrt_hc_t hc = hash_init(NULL, CMRT_HASH_SHA256);
	if (!cmrt_is_valid(hc)) { return -ENODEV; }
	uint32_t regions[CONFIG_CMRT_MPU_NUM_REGIONS];
	cmrt_mpu_read_regions(0, regions);
	for (int i = 1; i < CONFIG_CMRT_MPU_NUM_REGIONS; i++) {
		/* Hash everything in SRAM that is RO or RX but not W.
		 * Note that we only need to hash M segments because
		 * supervisor X and RO segments are set to RO for M. */
		uint32_t end = CMRT_MPU_ADDRESS(regions[i]);
		uint32_t bits = CMRT_MPU_BITS(regions[i]);
		if (CMRT_MPU_PRIVILEGE(regions[i]) == MPU_PRIVILEGE_M &&
		    IS_IN_RAM(end) && (bits & MPU_MODE_WRITABLE) == 0 &&
		    (bits & MPU_MODE_READABLE) != 0) {
			uint32_t start = CMRT_MPU_ADDRESS(regions[i - 1]);
			uint32_t size = end - start;
			LOG_INF("Adding 0x%x:%u into bb digest", start, size);
			int res = hash_update(hc, (const uint8_t *)(uintptr_t)start, size);
			if (res != 0) { return res; }
		}
	}
	uint32_t digest[SHA256_WORDS];
	int res = hash_final(hc, digest);
	if (res != 0) { return res; }
	if (setup) {
		/* Called to update digest. */
		(void)memcpy(bb_digest, digest, sizeof(digest));
		LOG_INF("Updated boot bypass digest");
	} else {
		/* Called to verify that calculated digest matches. */
		if (!fboot_memmatch(NULL, bb_digest, digest, sizeof(digest))) {
			LOG_INF("Invalid boot bypass digest");
			return -EPERM;
		}
		LOG_INF("Verified boot bypass digest");
	}
	return 0;
}
#endif

int fboot_set_tdv(const uint32_t tdv[CMRT_FMC_TDV_SIZE])
{
#ifdef CONFIG_JTAG_BEFORE_BOOT
	ARG_UNUSED(tdv);
	return 0;
#else
	cmrt_fmc_t fmc = cmrt_fmc_open();
	if (!cmrt_is_valid(fmc)) { return -ENODEV; }
	int res = 0;
	for (uint32_t i = 0; i < (uint32_t)CMRT_FMC_TDV_SIZE; i++) {
		res = cmrt_fmc_write(fmc, FMC_TDV_OFFSET + i * 4u,
				     tdv[i], 0xffffffffu);
		if (res != 0) { break; }
		LOG_INF("TDV[%u] written: 0x%x", i, tdv[i]);
	}
	cmrt_fmc_close(fmc);
	return res;
#endif
}

int fboot_kdc_set_hw_state(uint8_t value)
{
	cmrt_kdc_t kdc = cmrt_kdc_open(0);
	if (!cmrt_is_valid(kdc)) { return -ENODEV; }
	int res = cmrt_kdc_set_hw_state(kdc, value);
	cmrt_kdc_close(kdc);
	return res;
}

static inline bool is_bb_state(uint32_t lc)
{
	return lc == DLC_TESTED || lc == DLC_PROVISIONED || lc == DLC_MISSION;
}

void *fboot_bootbypass_vector(uint32_t state)
{
	uint32_t bbs = cmrt_read_reg(CMRT_SIC_BASE, R_BOOT_BYPASS_STATUS);
	uint32_t bbv = cmrt_read_reg(CMRT_SIC_BASE, R_BOOT_BYPASS_VECTOR);
	uint32_t flags = BOOT_BYPASS_ALLOWED | IN_MPU_RESET;
	if ((bbs & flags) == BOOT_BYPASS_ALLOWED && bbv != 0 && is_bb_state(state)) {
		return (void *)(uintptr_t)bbv;
	}
	return NULL;
}
