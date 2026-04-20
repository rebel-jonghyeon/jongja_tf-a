/*
 * Copyright (c) 2023 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file
 */
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <errno.h>

#include <cmrt/fboot/datastore_attr.h>
#include <cmrt/ucu/span.h>
#include <cmrt/caliptra/handover.h>
#include <cmrt/caliptra/platdep.h>

#include "internal.h"

typedef struct {
	span name;
	size_t len;
	int target_root;
	uint32_t attrs;
} rta_info;

#define RTAINFO(id_, len_, root_, attrs_)			\
	[CMRT_CALIPTRA_RTA_##id_] = {				\
		.name = STRSPAN(#id_),				\
		.len = (len_),					\
		.target_root = CMRT_CALIPTRA_ROOT_IDX_##root_,	\
		.attrs = (attrs_)				\
	}

static const rta_info rtas[] = {
	/* Created by ROM */
	RTAINFO(LDevID_CERT, 0, RT, DS_U_READ),
	RTAINFO(OWNER_LDevID_CSR, 0, RT, DS_U_READ),
	RTAINFO(CDI_FMC, sizeof(cmrt_caliptra_digest_t), FMC, DS_S_READ | DS_S_WRITE),
	RTAINFO(ALIASFMC_PRIV, sizeof(cmrt_caliptra_privkey_t), FMC, DS_S_READ | DS_S_WRITE),
	RTAINFO(ALIASFMC_PUB, sizeof(cmrt_caliptra_pubkey_t), FMC, DS_S_READ | DS_S_WRITE),
	RTAINFO(ALIASFMC_CERT, 0, RT, DS_U_READ),

	/* Created by FMC */
	RTAINFO(ALIASRT_PRIV, sizeof(cmrt_caliptra_privkey_t), RT, DS_U_READ),
	RTAINFO(ALIASRT_PUB, sizeof(cmrt_caliptra_pubkey_t), RT, DS_U_READ),
	RTAINFO(ALIASRT_CERT, 0, RT, DS_U_READ),
	RTAINFO(OWNER_ALIASFMC_CSR, 0, RT, DS_U_READ),
	RTAINFO(CDI_RT, sizeof(cmrt_caliptra_digest_t), RT, DS_U_READ),
};

static const rta_info *get_rta_info(cmrt_caliptra_rta_id_t asset)
{
	const rta_info *info = NULL;
	if (asset < ARRAY_LEN(rtas)) {
		info = &rtas[asset];
	}
	return info;
}

int cmrt_caliptra_rta_store(cmrt_caliptra_rta_id_t asset, const void *data, size_t len)
{
	if (data == NULL) {
		return -EINVAL;
	}
	const rta_info *info = get_rta_info(asset);
	if (info == NULL) {
		/* Unknown asset. */
		return -EINVAL;
	}
	if ((info->len != 0u) && (len != info->len)) {
		/* Unexpected length for a fixed-size asset. */
		return -EINVAL;
	}
	int res;
	res = cmrt_caliptra_plat_datastore_write((const char *)info->name.p, info->name.n, data, len);
	if (res == 0) {
		res = cmrt_caliptra_plat_datastore_grant((const char *)info->name.p, info->name.n,
							 info->target_root, info->attrs);
	}
	return res;
}

int cmrt_caliptra_rta_retrieve(cmrt_caliptra_rta_id_t asset, void *data, size_t *len, bool erase)
{
	if (data == NULL) {
		return -EINVAL;
	}
	if (len == NULL) {
		return -EINVAL;
	}
	const rta_info *info = get_rta_info(asset);
	if (info == NULL) {
		/* Unknown asset. */
		return -EINVAL;
	}
	int res;
	res = cmrt_caliptra_plat_datastore_read((const char *)info->name.p, info->name.n, data, len);
	if (res == 0) {
		/* Check that we got the expected length if the asset
		 * is fixed-size.
		 */
		if ((info->len != 0u) && (*len != info->len)) {
			res = -EIO;
		}
		/* Clear the asset if requested. */
		if ((res == 0) && erase) {
			res = cmrt_caliptra_plat_datastore_write((const char *)info->name.p, info->name.n,
								 NULL, 0u);
		}
	}
	return res;
}
