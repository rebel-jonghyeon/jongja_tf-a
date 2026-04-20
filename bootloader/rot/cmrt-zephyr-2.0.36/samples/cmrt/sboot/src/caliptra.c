/*
 * Copyright (c) 2023 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file
 */
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <sys/printk.h>
#include <logging/log.h>

#include <drivers/cmrt/cmrt.h>
#include <drivers/cmrt/tmc.h>
#include <drivers/cmrt/hc.h>
#include <drivers/cmrt/fmc.h>
#include <drivers/cmrt/sic_reg.h>
#include <cmrt/fboot/img_version.h>
#include <cmrt/fboot/img_format.h>

#include <cmrt/caliptra/flow.h>
#include <cmrt/caliptra/x509.h>
#include <cmrt/caliptra/assets.h>
#include <cmrt/caliptra/handover.h>

#include "caliptra.h"

/* fboot datastore direct call api */
#include "syscalls.h"

LOG_MODULE_DECLARE(cmrt, CONFIG_CMRT_LOG_LEVEL);

/*
 * Generate LDevID assets. Performs the following high-level steps:
 *
 * 1. Retrieve OTP assets (UDS seed, field entropy).
 * 2. Derive the IDevID keypair.
 * 3. Compute CDI_LDevID.
 * 4. Derive the LDevID keypair.
 * 5. Issue the LDevID certificate.
 * 6. Generate an LDevID certificate signing request.
 */
int ldevid_flow(cmrt_caliptra_rom_context_t *context)
{
	int res = 0;

	/* IDevID {priv, pub} := eccKPDF(udsHash, "IDevID key pair") */
	cmrt_caliptra_privkey_t idevid_priv;
	cmrt_caliptra_pubkey_t idevid_pub;
	if (res == 0) {
		res = cmrt_caliptra_ecckpdf(&context->uds_hash, sizeof(context->uds_hash),
					    CMRT_KP_INFO_IDevID, strlen(CMRT_KP_INFO_IDevID),
					    &idevid_priv, &idevid_pub);
	}

	/* CDI_LDevID :=  HMAC(udsHash, fieldEntropy) */
	if (res == 0) {
		res = cmrt_caliptra_hmac(&context->uds_hash, sizeof(context->uds_hash),
					 &context->field_entropy, sizeof(context->field_entropy),
					 &context->cdi_ldevid);
	}

	/* Clear udsHash and fieldEntropy from memory. */
	cmrt_caliptra_zeroize(&context->uds_hash, sizeof(context->uds_hash));
	cmrt_caliptra_zeroize(&context->field_entropy, sizeof(context->field_entropy));

	/* LDevID {priv, pub} := eccKPDF(CDI_LDevID, "LDevID Key Pair") */
	if (res == 0) {
		res = cmrt_caliptra_ecckpdf(&context->cdi_ldevid, sizeof(context->cdi_ldevid),
					    CMRT_KP_INFO_LDevID, strlen(CMRT_KP_INFO_LDevID),
					    &context->ldevid_priv, &context->ldevid_pub);
	}

	/* Obtain the fboot and sboot versions referenced in the
	 * LDevID certificate.
	 */
	alignas(4) uint8_t fboot_ver[48];
	size_t fboot_ver_len = sizeof(fboot_ver);
	alignas(4) uint8_t sboot_ver[48];
	size_t sboot_ver_len = sizeof(sboot_ver);
	if (res == 0) {
		res = fboot_get_image_version(CMRT_FBOOT_IMAGE_VERSION, fboot_ver, &fboot_ver_len);
		if (res == 0) {
			fboot_ver_len = strlen(fboot_ver);
		}
	}
	if (res == 0) {
		res = fboot_get_image_version(CMRT_SBOOT_IMAGE_VERSION, sboot_ver, &sboot_ver_len);
		if (res == 0) {
			sboot_ver_len = strlen(sboot_ver);
		}
	}

	/* Finalize TMC initialization before we start signing
	 * anything. This is done even if a previous step has failed,
	 * to allow non-caliptra boot flows.
	 */
	int tmc_res = cmrt_tmc_sync(context->tmc);
	/* We don't want to overwrite any current failures in res. */
	if (res == 0) {
		res = tmc_res;
	}
	cmrt_tmc_close(context->tmc);
	context->tmc = CMRT_INVALID_HANDLE;

	/* Generate the LDevID certificate, issued by IDevID. */
	cmrt_caliptra_tcb_t idevid = {
		.identity = CMRT_CALIPTRA_ID_IDevID,
		.privkey = &idevid_priv,
		.pubkey = &idevid_pub,
	};
	cmrt_caliptra_tcb_t ldevid = {
		.identity = CMRT_CALIPTRA_ID_LDevID,
		.privkey = &context->ldevid_priv,
		.pubkey = &context->ldevid_pub,
	};
	cmrt_caliptra_tcbinfo_t tcbis[] = {
		{
			.version = fboot_ver,
			.version_len = fboot_ver_len,
			.layer = 0,
		},
		{
			.version = sboot_ver,
			.version_len = sboot_ver_len,
			.layer = 0,
		},
	};
	cmrt_caliptra_cert_params_t ldevid_cert_params = {
		.issuer = &idevid,
		.subject = &ldevid,
		.deviceinfo = &context->devinfo,
		.tcbinfos = tcbis,
		.tcbinfos_len = ARRAY_SIZE(tcbis),
	};
	alignas(4) uint8_t der[CMRT_CALIPTRA_MAX_DER_LEN];
	size_t der_len = sizeof(der);
	if (res == 0) {
		res = cmrt_caliptra_write_cert(der, &der_len, &ldevid_cert_params);
	}

	/* Clear IDevID credentials from memory. */
	cmrt_caliptra_zeroize(&idevid_priv, sizeof(idevid_priv));
	cmrt_caliptra_zeroize(&idevid_pub, sizeof(idevid_pub));

	/* - LDevID certificate (FMC=none RT=R) */
	if (res == 0) {
		res = cmrt_caliptra_rta_store(CMRT_CALIPTRA_RTA_LDevID_CERT, der, der_len);
	}

	/* Construct the owner LDevID CSR. */
	cmrt_caliptra_csr_params_t owner_ldevid_csr_params = {
		.subject = &ldevid,
		.deviceinfo = &context->devinfo,
		.tcbinfos = tcbis,
		.tcbinfos_len = ARRAY_SIZE(tcbis),
	};
	if (res == 0) {
		res = cmrt_caliptra_write_csr(der, &der_len, &owner_ldevid_csr_params);
	}
	/* - Owner LDevID CSR (FMC=none RT=R) */
	if (res == 0) {
		res = cmrt_caliptra_rta_store(CMRT_CALIPTRA_RTA_OWNER_LDevID_CSR, der, der_len);
	}
	return res;
}

static int get_debug_mode(uint32_t *dbg)
{
	int res = -EINVAL;
	if (dbg != NULL) {
		cmrt_fmc_t fmc = cmrt_fmc_open();
		if (cmrt_is_valid(fmc)) {
			uint32_t tdv = 0;
			res = cmrt_fmc_read(fmc, FMC_TDV_OFFSET, &tdv);
			if (res == 0) {
				*dbg = tdv & FMC_TEST_MODE_BIT;
			}
			cmrt_fmc_close(fmc);
		}
	}
	return res;
}

static int hash_otpfield(cmrt_omc_t omc, cmrt_hc_t hc, uint32_t offset, size_t len)
{
	/* The longest field we read is a root. */
	alignas(4) uint8_t tmp[OTP_ROOT_SIZE];
	int res = cmrt_omc_read(omc, offset, tmp, len);
	if (res == 0) {
		res = cmrt_hc_update(hc, tmp, len);
	}
	return res;
}

/* Feed the security state into the hash context. */
static int hash_otp_security_state(cmrt_hc_t hc)
{
	int res = 0;
	cmrt_omc_t omc = cmrt_omc_open(CMRT_O_SYNC);
	if (cmrt_is_valid(omc)) {
		if (res == 0) {
			res = hash_otpfield(omc, hc, OTP_STATUS_WORD_OFFSET, OTP_STATUS_WORD_SIZE);
		}
		if (res == 0) {
			res = hash_otpfield(omc, hc, OTP_KEY_OBLITERATE_OFFSET, OTP_KEY_OBLITERATE_SIZE);
		}
		if (res == 0) {
			res = hash_otpfield(omc, hc, OTP_DEVICE_ID_OFFSET, OTP_DEVICE_ID_SIZE);
		}
		if (res == 0) {
			res = hash_otpfield(omc, hc, OTP_OEM_ID_OFFSET, OTP_OEM_ID_SIZE);
		}
		if (res == 0) {
			res = hash_otpfield(omc, hc, OTP_ROOT_OFFSET(0), OTP_ROOT_SIZE);
		}
		if (res == 0) {
			res = hash_otpfield(omc, hc, OTP_ROOT_OFFSET(1), OTP_ROOT_SIZE);
		}
		cmrt_omc_close(omc);
	}
	return res;
}

static int measure_security_state(cmrt_hc_t hc)
{
	int res = 0;
	if (res == 0) {
		res = hash_otp_security_state(hc);
	}
	if (res == 0) {
		uint32_t sboot_hash[SIC_SBOOT_HASH_REGS];
		for (uint32_t i = 0; i < SIC_SBOOT_HASH_REGS; ++i) {
			sboot_hash[i] = cmrt_read_reg(CMRT_SIC_BASE, R_SBOOT_HASH_0 + i*4u);
		}
		res = cmrt_hc_update(hc, &sboot_hash, sizeof(sboot_hash));
	}
	if (res == 0) {
		uint32_t debugmode;
		res = get_debug_mode(&debugmode);
		if (res == 0) {
			res = cmrt_hc_update(hc, &debugmode, sizeof(debugmode));
		}
	}
	return res;
}

static int calculate_cdi_fmc(const cmrt_caliptra_digest_t *cdi_ldevid,
			     const cmrt_caliptra_digest_t *tci_fmc,
			     cmrt_caliptra_digest_t *cdi_fmc)
{
	int res = 0;

	/* CDI_fmc_msg := SHA(security_state || TCI_fmc) */
	cmrt_hc_t hc = cmrt_hc_open(NULL, CMRT_O_SYNC);
	if (cmrt_is_valid(hc)) {
		res = cmrt_hc_init(hc, CMRT_HASH_SHA384, NULL, 0);
		if (res == 0) {
			res = measure_security_state(hc);
		}

		cmrt_caliptra_digest_t cdi_fmc_msg;
		size_t cdi_fmc_msg_len = sizeof(cdi_fmc_msg);
		if (res == 0) {
			res = cmrt_hc_final(hc, tci_fmc, sizeof(*tci_fmc),
					    &cdi_fmc_msg, &cdi_fmc_msg_len);
		}
		cmrt_hc_close(hc);

		/* CDI_fmc := HMAC(CDI_ldevid, CDI_fmc_msg) */
		if (res == 0) {
			res = cmrt_caliptra_hmac(cdi_ldevid, sizeof(*cdi_ldevid),
						 &cdi_fmc_msg, sizeof(cdi_fmc_msg),
						 cdi_fmc);
		}
	}
	return res;
}

/*
 * Generate FMC assets.
 *
 * 1. Calculate CDI_fmc.
 * 2. Derive the AliasFMC keypair.
 * 3. Issue the AliasFMC certificate.
 */
int fmc_flow(cmrt_caliptra_rom_context_t *context, const void *fmc_address, size_t fmc_size)
{
	int res = 0;

	/* TCI_fmc := HASH(fmc) */
	cmrt_caliptra_digest_t tci_fmc;
	if (res == 0) {
		res = cmrt_caliptra_hash(fmc_address, fmc_size, &tci_fmc);
	}
	cmrt_caliptra_digest_t cdi_fmc;
	if (res == 0) {
		res = calculate_cdi_fmc(&context->cdi_ldevid, &tci_fmc, &cdi_fmc);
	}

	/* AliasFMC {priv, pub} := eccKPDF(CDI_fmc, "AliasFMC key pair") */
	cmrt_caliptra_privkey_t aliasfmc_priv;
	cmrt_caliptra_pubkey_t aliasfmc_pub;
	if (res == 0) {
		res = cmrt_caliptra_ecckpdf(&cdi_fmc, sizeof(cdi_fmc),
					    CMRT_KP_INFO_AliasFMC, strlen(CMRT_KP_INFO_AliasFMC),
					    &aliasfmc_priv, &aliasfmc_pub);
	}

	/* Generate the AliasFMC certificate, issued by LDevID. */

	alignas(4) uint8_t fmc_ver[48];
	size_t fmc_ver_len = sizeof(fmc_ver);
	if (res == 0) {
		res = fboot_get_image_version(CMRT_SUPERVISOR_IMAGE_VERSION, fmc_ver, &fmc_ver_len);
		if (res == 0) {
			fmc_ver_len = strlen(fmc_ver);
		}
	}

	cmrt_caliptra_tcb_t aliasfmc = {
		.identity = CMRT_CALIPTRA_ID_AliasFMC,
		.privkey = &aliasfmc_priv,
		.pubkey = &aliasfmc_pub,
	};
	cmrt_caliptra_tcb_t ldevid = {
		.identity = CMRT_CALIPTRA_ID_LDevID,
		.privkey = &context->ldevid_priv,
		.pubkey = &context->ldevid_pub,
	};
	const cmrt_caliptra_digest_t *fmc_fwids[] = {
		&tci_fmc,
	};
	cmrt_caliptra_tcbinfo_t fmc_tcbis[] = {
		{
			.version = fmc_ver,
			.version_len = fmc_ver_len,
			.layer = 1,
			.fwids = fmc_fwids,
			.fwids_len = ARRAY_SIZE(fmc_fwids),
		},
	};
	cmrt_caliptra_cert_params_t aliasfmc_cert_params = {
		.issuer = &ldevid,
		.subject = &aliasfmc,
		.deviceinfo = &context->devinfo,
		.tcbinfos = fmc_tcbis,
		.tcbinfos_len = ARRAY_SIZE(fmc_tcbis),
	};
	alignas(4) uint8_t der[CMRT_CALIPTRA_MAX_DER_LEN];
	size_t der_len = sizeof(der);
	if (res == 0) {
		res = cmrt_caliptra_write_cert(der, &der_len, &aliasfmc_cert_params);
	}

	/* Clear LDevID assets from memory. */
	cmrt_caliptra_zeroize(&context->cdi_ldevid, sizeof(context->cdi_ldevid));
	cmrt_caliptra_zeroize(&context->ldevid_priv, sizeof(context->ldevid_priv));
	cmrt_caliptra_zeroize(&context->ldevid_pub, sizeof(context->ldevid_pub));

	/* Make the following assets available to the FMC and/or the
	 * RT. The permissions for the given asset are given in
	 * parentheses. The write permission is needed for erasing the
	 * asset.
	 */

	/* - CDI_fmc (FMC=RW RT=none) */
	if (res == 0) {
		res = cmrt_caliptra_rta_store(CMRT_CALIPTRA_RTA_CDI_FMC, &cdi_fmc, sizeof(cdi_fmc));
	}

	/* - AliasFMC keypair (FMC=RW RT=none) */
	if (res == 0) {
		res = cmrt_caliptra_rta_store(CMRT_CALIPTRA_RTA_ALIASFMC_PRIV, &aliasfmc_priv, sizeof(aliasfmc_priv));
	}
	if (res == 0) {
		res = cmrt_caliptra_rta_store(CMRT_CALIPTRA_RTA_ALIASFMC_PUB, &aliasfmc_pub, sizeof(aliasfmc_pub));
	}

	/* - AliasFMC certificate (FMC=none RT=R) */
	if (res == 0) {
		res = cmrt_caliptra_rta_store(CMRT_CALIPTRA_RTA_ALIASFMC_CERT, der, der_len);
	}

	return res;
}

int cmrt_caliptra_rom_flow_init(cmrt_caliptra_rom_context_t *context)
{
	memset(context, 0, sizeof(*context));
	cmrt_caliptra_oam_t oam;
	int res = cmrt_caliptra_oam_open(oam);
	if (res == 0) {
		res = cmrt_caliptra_oam_init(oam, 0);
	}
	cmrt_caliptra_uds_t uds_seed;
	if (res == 0) {
		res = cmrt_caliptra_oam_read_uds_seed(oam, &uds_seed);
	}
	int slot;
	if (res == 0) {
		res = cmrt_caliptra_oam_read_field_entropy(oam, &context->field_entropy, &slot);
	}
	cmrt_caliptra_oam_close(oam);
	/* OAM (omc) must be closed before deobfuscating, otherwise
	 * KDC blocks.
	 */

	if (res == 0) {
		res = cmrt_caliptra_derive_uds_hash(&uds_seed, &context->uds_hash);
	}
	if (res == 0) {
		res = cmrt_caliptra_deobfuscate_field_entropy(&context->field_entropy, slot);
	}
	cmrt_caliptra_zeroize(&uds_seed, sizeof(uds_seed));
	return res;
}

int cmrt_caliptra_rom_flow(cmrt_caliptra_rom_context_t *context,
			   cmrt_tmc_t tmc,
			   const void *fmc_address, size_t fmc_size)
{
	context->tmc = tmc;
	int res = cmrt_caliptra_get_deviceinfo(&context->devinfo);
	if (res == 0) {
		res = ldevid_flow(context);
	}
	if (res == 0) {
		res = fmc_flow(context, fmc_address, fmc_size);
	}
	return res;
}

void cmrt_caliptra_rom_flow_finalize(cmrt_caliptra_rom_context_t *context)
{
	/* If the previous steps did not sync/close the TMC (indicated
	 * by setting 'tmc' to CMRT_INVALID_HANDLE), we must do it
	 * here.
	 */
	if (cmrt_is_valid(context->tmc)) {
		cmrt_tmc_sync(context->tmc);
		cmrt_tmc_close(context->tmc);
		context->tmc = CMRT_INVALID_HANDLE;
	}
	cmrt_caliptra_zeroize(context, sizeof(*context));
}

int cmrt_caliptra_plat_datastore_write(const char *name, size_t namelen,
				       const void *data, size_t datalen)
{
	return fboot_data_store_write(name, namelen, data, datalen, false);
}

int cmrt_caliptra_plat_datastore_grant(const char *name, size_t namelen, int root, uint32_t attr)
{
	return fboot_data_store_grant(name, namelen, attr, root, false);
}
