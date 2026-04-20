/*
 * Copyright (c) 2023 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file
 */
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#include <cmrt/caliptra/flow.h>
#include <cmrt/caliptra/x509.h>
#include <cmrt/caliptra/assets.h>
#include <cmrt/caliptra/handover.h>

#include <drivers/cmrt/fboot.h>

#include "caliptra.h"

int cmrt_caliptra_fmc_init(cmrt_caliptra_fmc_context_t *context)
{
	/* Retrieve and erase FMC-only assets from the data store. */

	/* This has to be done before the container is loaded, and
	 * current root is considered to be 0 (due to the fallback in
	 * datastore API). If the container is loaded then MW cannot
	 * anymore retrieve assets destined for root 0.
	 */

	size_t len = sizeof(context->cdi_fmc);
	int res = cmrt_caliptra_rta_retrieve(CMRT_CALIPTRA_RTA_CDI_FMC,
					     &context->cdi_fmc, &len, true);
	if (res == 0) {
		len = sizeof(context->aliasfmc_priv);
		res = cmrt_caliptra_rta_retrieve(CMRT_CALIPTRA_RTA_ALIASFMC_PRIV,
						 &context->aliasfmc_priv, &len, true);
	}
	if (res == 0) {
		len = sizeof(context->aliasfmc_pub);
		res = cmrt_caliptra_rta_retrieve(CMRT_CALIPTRA_RTA_ALIASFMC_PUB,
						 &context->aliasfmc_pub, &len, true);
	}
	return res;
}

/* If this function completes successfully, the following new assets
 * shall be available to RT:
 *
 * - CDI_rt
 * - AliasRT keypair
 * - AliasRT certificate
 * - Owner AliasRT CSR
 */
int cmrt_caliptra_fmc_flow(cmrt_caliptra_fmc_context_t *context,
			       const void *rt_address, size_t rt_size)
{
	int res = 0;

	cmrt_caliptra_deviceinfo_t devinfo;
	if (res == 0) {
		res = cmrt_caliptra_get_deviceinfo(&devinfo);
	}

	/* TCI_rt := HASH(RT image) */
	cmrt_caliptra_digest_t tci_rt;
	if (res == 0) {
		res = cmrt_caliptra_hash(rt_address, rt_size, &tci_rt);
	}

	/* CDI_rt := HMAC(CDI_fmc, TCI_rt) */
	cmrt_caliptra_digest_t cdi_rt;
	if (res == 0) {
		res = cmrt_caliptra_hmac(&context->cdi_fmc, sizeof(context->cdi_fmc),
					 &tci_rt, sizeof(tci_rt),
					 &cdi_rt);
	}

	if (res == 0) {
		res = cmrt_caliptra_rta_store(CMRT_CALIPTRA_RTA_CDI_RT, &cdi_rt, sizeof(cdi_rt));
	}

	/* AliasRT {priv, pub} := eccKPDF(CDI_rt, "AliasRT Key Pair") */
	cmrt_caliptra_privkey_t aliasrt_priv;
	cmrt_caliptra_pubkey_t aliasrt_pub;
	if (res == 0) {
		res = cmrt_caliptra_ecckpdf(&cdi_rt, sizeof(cdi_rt),
					    CMRT_KP_INFO_AliasRT, strlen(CMRT_KP_INFO_AliasRT),
					    &aliasrt_priv, &aliasrt_pub);
	}

	if (res == 0) {
		res = cmrt_caliptra_rta_store(CMRT_CALIPTRA_RTA_ALIASRT_PRIV,
				  &aliasrt_priv, sizeof(aliasrt_priv));
	}
	if (res == 0) {
		res = cmrt_caliptra_rta_store(CMRT_CALIPTRA_RTA_ALIASRT_PUB,
				  &aliasrt_pub, sizeof(aliasrt_pub));
	}

	/* AliasRT certificate */
	cmrt_caliptra_tcb_t aliasfmc = {
		.identity = CMRT_CALIPTRA_ID_AliasFMC,
		.privkey = &context->aliasfmc_priv,
		.pubkey = &context->aliasfmc_pub,
	};
	cmrt_caliptra_tcb_t aliasrt = {
		.identity = CMRT_CALIPTRA_ID_AliasRT,
		.privkey = &aliasrt_priv,
		.pubkey = &aliasrt_pub,
	};
	const cmrt_caliptra_digest_t *rt_fwids[] = {
		&tci_rt,
	};
	// TODO do containers have a version that we can get here?
	const char *rt_ver = "rt version";
	size_t rt_ver_len = strlen(rt_ver);
	cmrt_caliptra_tcbinfo_t rt_tcbis[] = {
		{
			.version = rt_ver,
			.version_len = rt_ver_len,
			.layer = 2,
			.fwids = rt_fwids,
			.fwids_len = ARRAY_SIZE(rt_fwids),
		},
	};
	cmrt_caliptra_cert_params_t aliasrt_cert_params = {
		.issuer = &aliasfmc,
		.subject = &aliasrt,
		.deviceinfo = &devinfo,
		.tcbinfos = rt_tcbis,
		.tcbinfos_len = ARRAY_SIZE(rt_tcbis),
	};
	alignas(4) uint8_t der[CMRT_CALIPTRA_MAX_DER_LEN];
	size_t der_len = sizeof(der);
	if (res == 0) {
		res = cmrt_caliptra_write_cert(der, &der_len, &aliasrt_cert_params);
	}

	if (res == 0) {
		res = cmrt_caliptra_rta_store(CMRT_CALIPTRA_RTA_ALIASRT_CERT, der, der_len);
	}

	/* Owner AliasFMC CSR */
	cmrt_caliptra_csr_params_t owner_aliasfmc_csr_params = {
		.subject = &aliasfmc,
		.deviceinfo = &devinfo,
		.tcbinfos = rt_tcbis,
		.tcbinfos_len = ARRAY_SIZE(rt_tcbis),
	};
	if (res == 0) {
		res = cmrt_caliptra_write_csr(der, &der_len, &owner_aliasfmc_csr_params);
	}
	if (res == 0) {
		res = cmrt_caliptra_rta_store(CMRT_CALIPTRA_RTA_OWNER_ALIASFMC_CSR, der, der_len);
	}

	/* Clear secrets from memory. */
	cmrt_caliptra_zeroize(context, sizeof(*context));

	/* These have been handed over to RT; clear them from FMC
	 * memory.
	 */
	cmrt_caliptra_zeroize(&tci_rt, sizeof(tci_rt));
	cmrt_caliptra_zeroize(&cdi_rt, sizeof(cdi_rt));

	return res;
}

int cmrt_caliptra_plat_datastore_read(const char *name, size_t namelen,
				      void *data, size_t *datalen)
{
	return fboot_data_store_read(name, namelen, data, datalen, false);
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
