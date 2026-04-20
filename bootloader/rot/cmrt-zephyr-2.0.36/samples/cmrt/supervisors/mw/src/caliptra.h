/*
 * Copyright (c) 2023 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file
 */
#ifndef CMRT_MW_CALIPTRA_H
#define CMRT_MW_CALIPTRA_H
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <cmrt/caliptra/types.h>

#ifdef __cplusplus
extern "C" {
#endif


/*
 * Collection of runtime Caliptra assets transferred from sboot to MW.
 *
 * The Caliptra boot flow for the First Mutable Code (FMC) requires
 * certain assets from the previous layer. These are stored in the
 * security monitor datastore by sboot. Middleware must retrieve these
 * before it (auto-)loads the Caliptra RT container, because
 * afterwards the user container's root's permissions are applied and
 * prevent access to these assets.
 *
 * Therefore the boot flow is split into two stages:
 * cmrt_caliptra_fmc_init() fills this structure, which is then
 * consumed by cmrt_caliptra_fmc_flow().
 */
typedef struct cmrt_caliptra_fmc_context {
	cmrt_caliptra_digest_t cdi_fmc;
	cmrt_caliptra_privkey_t aliasfmc_priv;
	cmrt_caliptra_pubkey_t aliasfmc_pub;
} cmrt_caliptra_fmc_context_t;

int cmrt_caliptra_fmc_init(cmrt_caliptra_fmc_context_t *context);
int cmrt_caliptra_fmc_flow(cmrt_caliptra_fmc_context_t *context,
			       const void *rt_address, size_t rt_size);

#ifdef __cplusplus
}
#endif
#endif
