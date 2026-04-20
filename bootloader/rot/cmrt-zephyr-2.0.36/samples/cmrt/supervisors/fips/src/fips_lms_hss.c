/*
 * Copyright (c) 2023 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

#include <stdint.h>
#include <stddef.h>
#include <string.h>

#include <drivers/cmrt/cmrt.h>
#include <drivers/cmrt/hc.h>
#include <drivers/cmrt/fips/fips_types.h>
#include <drivers/cmrt/sac_mem.h>
#include <drivers/cmrt/util.h>
#include <cmrt/shsig/lms.h>

#include "fips.h"
#include "fips_asset.h"
#include "cri_utils.h"

int32_t fips_lms_verify(fips_state_t *state, teec_abi_invokecommand_t *h)
{
	int32_t status = 0;
	uint8_t *pk = NULL;
	uint8_t *msg = NULL;
	size_t mlen;
	uint8_t *sig = NULL;
	cmrt_hc_t hc = CMRT_INVALID_HANDLE;

	dprintk("FIPS_SERVICE_LMS_VERIFY\n");
	CHECK_COMMAND(FIPS_SERVICE_LMS_VERIFY);

	pk = (uint8_t *) (h->params[0].memref.offset + SAC_MEMORY_BASE);
	msg = (uint8_t *) (h->params[1].memref.offset + SAC_MEMORY_BASE);
	mlen = h->params[1].memref.size;
	sig = (uint8_t *) (h->params[2].memref.offset + SAC_MEMORY_BASE);

	cmrt_lms_algorithm_type lms_type = cmrt_lms_get_type(pk, false);
	if (lms_type == LMS_RESERVED) {
		status = -EINVAL;
		goto out;
	}

	hc = cmrt_hc_open(NULL, CMRT_O_SYNC);
	if (!cmrt_is_valid(hc)) {
		status = -EIO;
		dprintk("Failed to open HC\n");
		goto out;
	}

	status = cmrt_lms_verify(hc, pk, msg, mlen, sig);

	if (status) {
		status = -EIO;
		dprintk("LMS verify failed: %d\n", status);
		goto out;
	}

out:
	if (cmrt_is_valid(hc)) {
		cmrt_hc_close(hc);
	}
	destroy_workcontext(status);
	return status;
}

#ifdef CONFIG_CMRT_SHSIG_LMS_HSS
int32_t fips_hss_verify(fips_state_t *state, teec_abi_invokecommand_t *h)
{
	int32_t status = 0;
	uint8_t *pk = NULL;
	uint8_t *msg = NULL;
	size_t mlen;
	uint8_t *sig = NULL;
	cmrt_hc_t hc = CMRT_INVALID_HANDLE;

	dprintk("FIPS_SERVICE_HSS_VERIFY\n");
	CHECK_COMMAND(FIPS_SERVICE_HSS_VERIFY);

	pk = (uint8_t *) (h->params[0].memref.offset + SAC_MEMORY_BASE);
	msg = (uint8_t *) (h->params[1].memref.offset + SAC_MEMORY_BASE);
	mlen = h->params[1].memref.size;
	sig = (uint8_t *) (h->params[2].memref.offset + SAC_MEMORY_BASE);

	cmrt_lms_algorithm_type lms_type = cmrt_lms_get_type(pk, true);
	if (lms_type == LMS_RESERVED) {
		status = -EINVAL;
		goto out;
	}

	hc = cmrt_hc_open(NULL, CMRT_O_SYNC);
	if (!cmrt_is_valid(hc)) {
		status = -EIO;
		dprintk("Failed to open HC\n");
		goto out;
	}

	status = cmrt_lms_hss_verify(hc, pk, msg, mlen, sig);

	if (status) {
		status = -EIO;
		dprintk("HSS verify failed: %d\n", status);
		goto out;
	}

out:
	if (cmrt_is_valid(hc)) {
		cmrt_hc_close(hc);
	}
	destroy_workcontext(status);
	return status;
}
#endif
