/*
 * Copyright (c) 2023 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file
 */
#ifndef CMRT_CALIPTRA_HANDOVER_H
#define CMRT_CALIPTRA_HANDOVER_H
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

enum {
	CMRT_CALIPTRA_ROOT_IDX_FMC = 0,
	CMRT_CALIPTRA_ROOT_IDX_RT = 1,
};

typedef enum cmrt_caliptra_rta_id {
	CMRT_CALIPTRA_RTA_LDevID_CERT,
	CMRT_CALIPTRA_RTA_OWNER_LDevID_CSR,
	CMRT_CALIPTRA_RTA_CDI_FMC,
	CMRT_CALIPTRA_RTA_ALIASFMC_PRIV,
	CMRT_CALIPTRA_RTA_ALIASFMC_PUB,
	CMRT_CALIPTRA_RTA_ALIASFMC_CERT,
	CMRT_CALIPTRA_RTA_ALIASRT_PRIV,
	CMRT_CALIPTRA_RTA_ALIASRT_PUB,
	CMRT_CALIPTRA_RTA_ALIASRT_CERT,
	CMRT_CALIPTRA_RTA_OWNER_ALIASFMC_CSR,
	CMRT_CALIPTRA_RTA_CDI_RT,
} cmrt_caliptra_rta_id_t;

/**
 * Store a runtime asset.
 *
 * Write the given runtime asset into the data store. Each asset is
 * associated with a specific target layer (FMC, or RT) and
 * permissions. If the asset is fixed-length, @a len is verified to
 * match.
 *
 * @param asset the runtime asset identifier
 * @param data asset contents
 * @param len length of @a data
 * @return 0 on success, -ERRNO on error
 */
int cmrt_caliptra_rta_store(cmrt_caliptra_rta_id_t asset, const void *data, size_t len);

/**
 * Retrieve a runtime asset.
 *
 * Reads the given runtime asset from the data store. The asset is
 * optionally erased after reading. An error is returned if the asset
 * is fixed-length and the data store contained an item of different
 * length.
 *
 * @param asset the runtime asset identifier
 * @param data buffer to place the asset contents. The asset is only
 * copied if the buffer is large enough.
 * @param[inout] len available space in @a data. Contains the true
 * length on return.
 * @param erase if true, the asset is erased after successfully reading
 * @return 0 on success, -ERRNO on error
 */
int cmrt_caliptra_rta_retrieve(cmrt_caliptra_rta_id_t asset, void *data, size_t *len, bool erase);

#ifdef __cplusplus
}
#endif
#endif
