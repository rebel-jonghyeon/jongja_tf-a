/*
 * Copyright (c) 2023 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */
#ifndef CMRT_CALIPTRA_ROM_FLOW_H
#define CMRT_CALIPTRA_ROM_FLOW_H

#include <drivers/cmrt/tmc.h>
#include <cmrt/caliptra/types.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Information required during the Caliptra ROM flow. */
typedef struct cmrt_caliptra_rom_context {
	cmrt_tmc_t tmc;
	cmrt_caliptra_digest_t uds_hash;
	cmrt_caliptra_field_entropy_t field_entropy;
	cmrt_caliptra_deviceinfo_t devinfo;
	cmrt_caliptra_privkey_t ldevid_priv;
	cmrt_caliptra_pubkey_t ldevid_pub;
	cmrt_caliptra_digest_t cdi_ldevid;
} cmrt_caliptra_rom_context_t;

/**
 * Perform the initial step in the Caliptra ROM boot flow.
 *
 * Derive the IDevID identity and deobfuscate the current field
 * entropy.
 *
 * This must happen before any supervisor is loaded and the active
 * root is switched, because doing so will change the KDC derivation
 * path used in deobfuscation.
 *
 * @param context the Caliptra ROM context
 * @return 0 on success, -ERRNO on error.
 */
int cmrt_caliptra_rom_flow_init(cmrt_caliptra_rom_context_t *context);

/**
 * Perform the main Caliptra ROM boot flow.
 *
 * Derive the LDevID and AliasFMC identities, and save assets required
 * by the First Mutable Code (FMC) into the data store. This has to be
 * called after the FMC has been loaded to RAM and verified.
 *
 * The boot flow needs a TMC handle for signing; this is supplied from
 * outside so that sboot can start initialization early and perform
 * loading of FMC in parallel.
 *
 * @param tmc a TMC handle opened with CMRT_O_ASYNC. The handle is
 * consumed the Caliptra ROM boot flow (the caller shall not clean it up).
 * @param fmc_address address of the FMC in memory
 * @param fmc_size size of the FMC
 * @return 0 on success, -ERRNO on error.
 */
int cmrt_caliptra_rom_flow(cmrt_caliptra_rom_context_t *context,
			   cmrt_tmc_t tmc, const void *fmc_address, size_t fmc_size);

/**
 * Finalize the Caliptra ROM flow.
 *
 * This must be called in all cases, irrespective of the outcome of
 * previous functions.
 *
 * @param context the Caliptra ROM context
 */
void cmrt_caliptra_rom_flow_finalize(cmrt_caliptra_rom_context_t *context);

#ifdef __cplusplus
}
#endif
#endif
