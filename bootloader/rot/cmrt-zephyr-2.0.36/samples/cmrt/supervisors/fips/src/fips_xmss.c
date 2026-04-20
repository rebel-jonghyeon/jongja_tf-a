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
#include <cmrt/shsig/xmss.h>
#include <cmrt/shsig/xmss_mt.h>

#include "fips.h"
#include "fips_asset.h"
#include "cri_utils.h"


int32_t fips_xmss_verify(fips_state_t *state, teec_abi_invokecommand_t *h)
{
	int32_t status = 0;
	uint8_t *pk = NULL;
	uint8_t *msg = NULL;
	size_t mlen;
	uint8_t *sig = NULL;
	cmrt_hc_t hc = CMRT_INVALID_HANDLE;

	dprintk("FIPS_SERVICE_XMSS_VERIFY\n");
	CHECK_COMMAND(FIPS_SERVICE_XMSS_VERIFY);

	pk = (uint8_t *) (h->params[0].memref.offset + SAC_MEMORY_BASE);
	msg = (uint8_t *) (h->params[1].memref.offset + SAC_MEMORY_BASE);
	mlen = h->params[1].memref.size;
	sig = (uint8_t *) (h->params[2].memref.offset + SAC_MEMORY_BASE);

	cmrt_xmss_algorithm_type xmss_type = cmrt_xmss_get_type(pk);
	dprintk("Public key XMSS type %u\n", (uint32_t)xmss_type);
	if (xmss_type == XMSS_RESERVED) {
		status = -EINVAL;
		goto out;
	}

	hc = cmrt_hc_open(NULL, CMRT_O_SYNC);
	if (!cmrt_is_valid(hc)) {
		status = -EIO;
		dprintk("Failed to open HC\n");
		goto out;
	}

	status = cmrt_xmss_verify(hc, pk, msg, mlen, sig, NULL);
	if (status) {
		status = -EIO;
		dprintk("XMSS verify failed: %d\n", status);
		goto out;
	}

out:
	if (cmrt_is_valid(hc)) {
		cmrt_hc_close(hc);
	}
	destroy_workcontext(status);
	return status;
}

#ifdef CONFIG_CMRT_SHSIG_XMSS_MT
int32_t fips_xmss_mt_verify(fips_state_t *state, teec_abi_invokecommand_t *h)
{
	int32_t status = 0;
	uint8_t *pk = NULL;
	uint8_t *msg = NULL;
	size_t mlen;
	uint8_t *sig = NULL;
	cmrt_hc_t hc = CMRT_INVALID_HANDLE;

	dprintk("FIPS_SERVICE_XMSSMT_VERIFY\n");
	CHECK_COMMAND(FIPS_SERVICE_XMSSMT_VERIFY);

	pk = (uint8_t *) (h->params[0].memref.offset + SAC_MEMORY_BASE);
	msg = (uint8_t *) (h->params[1].memref.offset + SAC_MEMORY_BASE);
	mlen = h->params[1].memref.size;
	sig = (uint8_t *) (h->params[2].memref.offset + SAC_MEMORY_BASE);

	cmrt_xmss_mt_algorithm_type xmss_mt_type = cmrt_xmss_mt_get_type(pk);
	dprintk("Public key XMSS-MT type %u\n", (uint32_t)xmss_mt_type);
	if (xmss_mt_type == XMSS_MT_RESERVED ||
	    xmss_mt_type > XMSS_MT_SHA2_60_12_256) {
		status = -EINVAL;
		goto out;
	}

	hc = cmrt_hc_open(NULL, CMRT_O_SYNC);
	if (!cmrt_is_valid(hc)) {
		status = -EIO;
		dprintk("Failed to open HC\n");
		goto out;
	}

	status = cmrt_xmss_mt_verify(hc, pk, msg, mlen, sig, NULL);

	if (status) {
		status = -EIO;
		dprintk("XMSS-MT verify failed: %d\n", status);
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
