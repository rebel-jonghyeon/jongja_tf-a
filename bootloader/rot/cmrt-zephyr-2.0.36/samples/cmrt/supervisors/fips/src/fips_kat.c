/*
 * Copyright (c) 2020-2024 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

#include <zephyr.h>
#include <device.h>
#include <string.h>
#include <ctype.h>
#include <smcalls.h>
#include <sac.h>

#include <cri/cmrt/hc.h>
#include <cri/cmrt/aes.h>
#include <cri/cmrt/sic.h>
#include <cri/cmrt/pke.h>
#include <cri/cmrt.h>

#include <tee_client_api.h>
#include <tee_client_abi.h>

#include <cri/cmrt/fips/fips_types.h>

#include "teec_cmvp.h"
#include "teefs_cmvp.h"
#include "fips.h"
#include "cmvp_sw.h"
#include "sw_kdf_kat.h"
#include "cri_crypto.h"

typedef enum {
	KAT_TESTS_HC1       = 0x00001,
	KAT_TESTS_HC2       = 0x00010,
	KAT_TESTS_AES       = 0x00100,
	KAT_TESTS_PKE_ECDSA = 0x01000,
	KAT_TESTS_PKE_ECDH  = 0x02000,
	KAT_TESTS_PKE_RSA   = 0x04000,
	KAT_TESTS_PKE_KDF_1 = 0x10000,
	KAT_TESTS_PKE_KDF_2 = 0x20000
} kat_tests_id;

extern uint32_t rsa_run_kat(void);

bool run_all_kats(void)
{
	/*
	 * FIPS KATs usage on startup:
	 * Fboot runs the SHA256 KAT before verifying the sboot image.
	 * Sboot runs the SHA256 and ECDSA KAT before verifying the supervisor image.
	 * The supervisor runs ALL KATs before any service is allowed to execute.
	 * All inputs and outputs are suppressed during this time.
	 * Only after running all KATs can the supervisor assert the FIPS mode signal.
	 * At runtime:
	 * Executes all KATs when requested via the Self-Test service.
	 */
	uint32_t res = 0;

	dprintk("Running PKE kat\n");
	cri_pke_t pke = cri_pke_open(CRI_O_HWC_FORCE_KAT);
	if (cri_is_valid(pke)) {
		res |= KAT_TESTS_PKE_ECDH;
		res |= KAT_TESTS_PKE_ECDSA;
		cri_pke_close(pke);
	}
	dprintk("Running RSA kat\n");
	if (rsa_run_kat() > 0) {
		res |= KAT_TESTS_PKE_RSA;
	}
	dprintk("Running one-step KDF sp800_108 and 800_56C kat\n");
	if (sw_one_step_kdf_run_kat() > 0) {
		res |= KAT_TESTS_PKE_KDF_1;
	}
	dprintk("Running two-step KDF 800_56C kat\n");
	if (sw_two_step_kdf_run_kat() > 0) {
		res |= KAT_TESTS_PKE_KDF_2;
	}
	/* Cores which could require entrophy from EMC run in the end. */
	dprintk("Running HC kat\n");
	cri_hc_t hc = cri_hc_open(CRI_O_HWC_FORCE_KAT);
	if (cri_is_valid(hc)) {
		res |= KAT_TESTS_HC1;
		cri_hc_close(hc);
	}
#ifdef CONFIG_CMRT_HC2
	dprintk("Running HC2 kat\n");
	cri_hc_t hc2 = cri_hc2_open(CRI_O_HWC_FORCE_KAT);
	if (cri_is_valid(hc2)) {
		res |= KAT_TESTS_HC2;
		cri_hc_close(hc2);
	}
#endif

	dprintk("Running AES kat\n");
	cri_aes_t aes = cri_aes_open(CRI_O_HWC_FORCE_KAT);
	if (cri_is_valid(aes)) {
		res |= KAT_TESTS_AES;
		cri_aes_close(aes);
	}
	destroy_workcontext(0);

	enum { expected_res = (KAT_TESTS_HC1 |
#ifdef CONFIG_CMRT_HC2
			       KAT_TESTS_HC2 |
#endif
			       KAT_TESTS_AES |
			       KAT_TESTS_PKE_ECDH |
			       KAT_TESTS_PKE_ECDSA |
			       KAT_TESTS_PKE_RSA |
			       KAT_TESTS_PKE_KDF_1 |
			       KAT_TESTS_PKE_KDF_2)
	};

	if (res == expected_res) {
		dprintk("All KATs done\n");
		return true;
	}

	dprintk("All KATs were not properly executed 0x%x != 0x%x\n", res,
		expected_res);
	return false;
}

int32_t fips_selftest(fips_state_t *state, teec_abi_invokecommand_t *h)
{
	int32_t ret = 0;
	dprintk("FIPS_SERVICE_SELF_TEST\n");

	if (!run_all_kats()) {
		ret = -EIO;
	}

	return ret;
}
