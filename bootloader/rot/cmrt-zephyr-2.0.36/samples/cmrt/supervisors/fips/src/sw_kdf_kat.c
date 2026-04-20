/*
 * Copyright (c) 2020-2021 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

#include <cri/cmrt/eac.h>

#include <cri/cmrt/fips/fips_types.h>

#include "sw_kdf_kat.h"
#include "sw_kdf_kat_vectors.h"
#include "fips.h"
#include "cri_crypto.h"

#define MAX_OUTPUT_BYTES 256

static bool run_sw_one_step_kdf(const kdf_one_step_kat_t *kat)
{
	uint8_t output[MAX_OUTPUT_BYTES];

	int32_t status;

	uint32_t total_length = sizeof(hash_work_struct) + 4 + kat->z_length + kat->salt_length +
			kat->fixed_info_length + kat->output_length;

	status = sp800_108_kdf(output, kat->output_length, (uint8_t *)kat->salt, kat->salt_length,
			(uint8_t *)kat->z, kat->z_length, (uint8_t *)kat->fixed_info, kat->fixed_info_length, NULL);

	if (status) {
		goto out;
	}

	if (memcmp(kat->output, output, kat->output_length) == 0) {
		destroy_workcontext(total_length);
		return true;
	}

out:
	destroy_workcontext(total_length);
	return false;
}

static bool run_sw_two_step_kdf(const kdf_two_step_kat_t *kat)
{
	uint8_t output[MAX_OUTPUT_BYTES];

	int32_t status;

	uint32_t total_length = sizeof(hash_work_struct) + 4 + kat->z_length + kat->salt_length + 2 * (kat->label_length + kat->context_length + 5);

	status = kdf_component_extraction_expansion(output, kat->output_length, (uint8_t *)kat->salt, kat->salt_length,
			(uint8_t *)kat->z, kat->z_length, (uint8_t *)kat->label, kat->label_length, (uint8_t *)kat->context, kat->context_length, NULL);

	if (status) {
		goto out;
	}

	if (memcmp(kat->output, output, kat->output_length) == 0) {
		destroy_workcontext(total_length);
		return true;
	}

out:
	destroy_workcontext(total_length);
	return false;
}

uint32_t sw_one_step_kdf_run_kat(void)
{
	/* Run the sw kdf kats and expect output vector match */
	for (u32_t i = 0; i < KDF_ONE_STEP_KAT_VECTORS_COUNT; i++) {
		if (run_sw_one_step_kdf(&kdf_one_step_kat_vectors[i]) != true) {
			cri_eac_kat_error(CORE_ID_CPU, -EXDEV, -EFAULT);
		}
	}
	return 1;
}

uint32_t sw_two_step_kdf_run_kat(void)
{
	/* Run the sw kdf kats and expect output vector match */
	for (u32_t i = 0; i < KDF_TWO_STEP_KAT_VECTORS_COUNT; i++) {
		if (run_sw_two_step_kdf(&kdf_two_step_kat_vectors[i]) != true) {
			cri_eac_kat_error(CORE_ID_CPU, -EXDEV, -EFAULT);
		}
	}
	return 1;
}
