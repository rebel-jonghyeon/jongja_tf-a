/*
 * Copyright (c) 2020-2022 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

#include <zephyr.h>
#include <device.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <ctype.h>

#include <cri/cmrt/sac.h>
#include <cri/cmrt/eac.h>
#include <cri/cmrt/hc.h>
#include <cri/cmrt/tee_client_api.h> /* TEEC_MEMREF values */
#include <cri/cmrt/tee_client_abi.h>
#include <cri/cmrt.h>

#include <cri/cmrt/fips/fips_types.h>

#include "teec_cmvp.h"
#include "teefs_cmvp.h"
#include "fips_asset.h"
#include "fips.h"
#include "cmvp_sw.h"
#include "cri_utils.h"
#include "cri_crypto.h"

#define H_outputBits 256

/* The function expect L to be in bytes, only counter gets added to fixedInfo */
int32_t sp800_108_kdf(uint8_t *derived_key,
		uint32_t derived_key_length,
		uint8_t *salt,
		uint32_t salt_length,
		uint8_t *z,
		uint32_t z_length,
		uint8_t *fixed_info,
		uint32_t fixed_info_length,
		uint8_t *work_area)
{
	int32_t status = 0;

	hash_work_struct *sha;

	uint32_t n = (uint32_t) (((derived_key_length * 8) + (H_outputBits - 1)) / H_outputBits);

	uint8_t *input;
	uint8_t *result;

	uint8_t i;

	if (work_area == NULL) {
		sha = (hash_work_struct *)workcontext;
	} else {
		sha = (hash_work_struct *)ALIGN_32_BIT_POINTER(work_area);
	}

	sha->hashtype = FIPS_HASH_SHA256;
	sha->hashlen = 32;

	input = (uint8_t *)ALIGN_32_BIT_POINTER(sha + sizeof(hash_work_struct));

	memset(input, 0x00, 4);
	if (z_length != 0) {
		memcpy(input + 4, z, z_length);
	}
	if (fixed_info_length != 0) {
		memcpy(input + 4 + z_length, fixed_info, fixed_info_length);
	}

	result = (uint8_t *)ALIGN_32_BIT_POINTER(input + 4 + z_length + fixed_info_length);

	for (i = 0; i < n; i++) {
		*(input + 3) = i + 1;
		dhexdump("input", input, 4 + z_length + fixed_info_length);
		status = cri_mac_gen(sha, input, 4 + z_length + fixed_info_length, salt, salt_length, result + i*32, 32);
		if (status) {
			status = -EIO;
			goto direct_exit;
		}
		dhexdump("result", result + i*32, 32);
	}

	memcpy(derived_key, result, derived_key_length);

direct_exit:
	return status;
}

int32_t kdf_data_extraction_expansion(uint8_t *derived_key,
		uint32_t derived_key_length,
		uint8_t *salt,
		uint32_t salt_length,
		uint8_t *z,
		uint32_t z_length,
		uint8_t *fixed_info,
		uint32_t fixed_info_length,
		uint8_t *work_area)
{
	int32_t status = 0;

	hash_work_struct *sha;

	uint8_t *kdk;

	if (work_area == NULL) {
		sha = (hash_work_struct *)workcontext;
	} else {
		sha = (hash_work_struct *)ALIGN_32_BIT_POINTER(work_area);
	}

	kdk = (uint8_t *)ALIGN_32_BIT_POINTER(sha + sizeof(hash_work_struct));

	sha->hashtype = FIPS_HASH_SHA256;
	sha->hashlen = 32;

	status = cri_mac_gen(sha, z, z_length, salt, salt_length, kdk, 32);
	if (status) {
		status = -EIO;
		goto direct_exit;
	}
	dhexdump("kdk", kdk, 32);

	status = sp800_108_kdf(derived_key, derived_key_length, kdk, 32, NULL, 0,
			fixed_info, fixed_info_length, work_area + (32 * sizeof(uint8_t)));

direct_exit:
	return status;
}

int32_t kdf_component_extraction_expansion(uint8_t *derived_key,
		uint32_t derived_key_length,
		uint8_t *salt,
		uint32_t salt_length,
		uint8_t *z,
		uint32_t z_length,
		uint8_t *label,
		uint32_t label_length,
		uint8_t *component,
		uint32_t component_length,
		uint8_t *work_area)
{
	int32_t status;

	uint8_t *fixed_info;
	uint32_t fixed_info_length;
	uint32_t offset = 0;

	if (work_area == NULL) {
		fixed_info = (uint8_t *)workcontext;
	} else {
		fixed_info = (uint8_t *)ALIGN_32_BIT_POINTER(work_area);
	}

	memcpy(fixed_info, label, label_length * sizeof(uint8_t));
	fixed_info[label_length] = 0x00;
	offset = label_length + 1;
	memcpy(fixed_info + offset, component, component_length * sizeof(uint8_t));
	offset += component_length;
	fixed_info[offset] = 0;
	fixed_info[offset + 1] = (derived_key_length >> 13);
	fixed_info[offset + 2] = (derived_key_length >> 5) & 0xff;
	fixed_info[offset + 3] = (derived_key_length << 3) & 0xff;

	fixed_info_length = offset + 4;
	dhexdump("Fixed info", fixed_info, fixed_info_length);

	status = kdf_data_extraction_expansion(derived_key, derived_key_length, salt,
			salt_length, z, z_length, fixed_info, fixed_info_length,
			fixed_info + fixed_info_length);

	return status;
}

static int32_t fips_instanstiate_other_info(teec_abi_invokecommand_t *h,
		uint32_t index,
		fips_other_info *other_info,
		fips_fixed_info_components *components,
		fips_fixed_info_data *data)
{
	int32_t status = 0;

	uint32_t offset = 0;

	uint8_t *ptr = (uint8_t *) (h->params[index].memref.offset + SAC_MEMORY_BASE);

	dhexdump("Fixed info", ptr, h->params[index].memref.size);

	GET_32_BIT_WORD(other_info->fixed_info_type, ptr, offset);
	GET_32_BIT_WORD(other_info->output_bit_length, ptr, offset);
	other_info->output_key_length = (other_info->output_bit_length + 7) >> 3;
	dprintk("%08x\n", other_info->output_key_length);
	GET_32_BIT_WORD(other_info->salt_size, ptr, offset);

	if (other_info->salt_size != 0) {
		other_info->salt = ptr + offset;
		dhexdump("Salt", other_info->salt, other_info->salt_size);
	} else {
		other_info->salt = NULL;
	}
	offset += other_info->salt_size;

	switch (other_info->fixed_info_type) {
	case FIPS_KDF_FIXED_INFO_NONE:
		dprintk("FIPS_KDF_FIXED_INFO_NONE\n");
		break;

	case FIPS_KDF_FIXED_INFO_COMPONENTS:
		dprintk("FIPS_KDF_FIXED_INFO_COMPONENTS\n");
		GET_32_BIT_WORD(components->label_size, ptr, offset);

		if (components->label_size != 0) {
			components->label = ptr + offset;
		} else {
			components->label = NULL;
		}
		offset += components->label_size;

		GET_32_BIT_WORD(components->context_size, ptr, offset);

		if (components->context_size != 0) {
			components->context = ptr + offset;
		} else {
			components->context = NULL;
		}
		offset += components->context_size;

		break;

	case FIPS_KDF_FIXED_INFO_DATA:
		dprintk("FIPS_KDF_FIXED_INFO_DATA\n");
		GET_32_BIT_WORD(data->data_size, ptr, offset);

		if (data->data_size != 0) {
			data->data = ptr + offset;
		} else {
			data->data = NULL;
		}
		offset += data->data_size;

		dhexdump("data", data->data, data->data_size);

		break;
	default:
		dprintk("Unexpected fixed_info_type\n");
		status = -EINVAL;
		goto out;
	}

	if (h->params[index].memref.size != offset) {
		dprintk("Unexpected fixed_info_type size: %i != %i\n", h->params[index].memref.size, offset);
		status = -EINVAL;
	}

out:
	return status;
}

int32_t fips_derive_symmetric_key(fips_state_t *state, teec_abi_invokecommand_t *h, uint8_t step)
{
	int32_t status = 0;
	int32_t res = -EACCES;

	uint32_t shared_secret_length = 0;
	uint32_t z_length;
	uint32_t salt_length;
	uint32_t asset_length = 0;

	uint8_t *shared_secret = workcontext + 4;
	uint8_t *z;
	uint8_t *salt;
	uint8_t *asset = NULL;
	uint8_t *work_area;

	fips_other_info *other_info;
	fips_fixed_info_components *components;
	fips_fixed_info_data *data;

	if (((uint32_t *) workcontext)[0] != 0x00000000) {
		dprintk("Working context is not empty, cleaning now\n");
		status = -EPERM;
		goto out;
	}

	switch (step) {
	case DERIVE_KEY_ONE_STEP:
		dprintk("FIPS_SERVICE_DERIVE_SYMM_KEY\n");
		((uint32_t *) workcontext)[0] = (uint32_t) FIPS_SERVICE_DERIVE_SYMM_KEY;
		break;
	case DERIVE_KEY_TWO_STEP:
		dprintk("FIPS_SERVICE_DERIVE_SYMM_KEY_TWO_STEP\n");
		((uint32_t *) workcontext)[0] = (uint32_t) FIPS_SERVICE_DERIVE_SYMM_KEY_TWO_STEP;
		break;
	default:
		status = -EINVAL;
		goto out;
	}

	if (h->params[0].memref.size > 0) {
		fips_asset_identifier *shared_secret_ptr = (fips_asset_identifier *)
				(h->params[0].memref.offset + SAC_MEMORY_BASE);

		if (shared_secret_ptr->location != FIPS_ASSET_DYNAMIC) {
			status = -EPERM;
			goto out;
		}

		res = fips_read_asset_of_type_from_teefs(state,
				(fips_asset_identifier *) (h->params[0].memref.offset + SAC_MEMORY_BASE),
				h->params[0].memref.size, shared_secret, &shared_secret_length,
				FIPS_TYPE_SHARED_SECRET);
		if (res) {
			dprintk("Teefs read not successful\n");
			goto out;
		}

		z_length = ((uint32_t *)shared_secret)[3];
		if (shared_secret_length != z_length + (4 * sizeof(uint32_t))) {
			dprintk("Shared secret asset is the wrong length\n");
			status = -EINVAL;
			goto out;
		}
		z = GET_SHARED_SECRET_FROM_ASSET(shared_secret);

		if (GET_ASSET_INTERNAL_FLAG_FROM_ASSET(shared_secret) != FIPS_INTERNAL_ASSET) {
			dprintk("Shared secret not generated in approved mode\n");
			state->approved_mode = 0;
		}

		dhexdump("Shared secret", z, z_length);
	} else {
		if (step == DERIVE_KEY_ONE_STEP) {
			z = NULL;
			z_length = 0;
		} else {
			status = -EINVAL;
			goto out;
		}
	}

	if (h->params[2].value.b != 0) {
		status = -EINVAL;
		goto out;
	}

	switch (h->params[2].value.a) {
	case FIPS_TYPE_AES:
	case FIPS_TYPE_AES_GCM_ENCRYPT:
	case FIPS_TYPE_AES_GCM_DECRYPT:
	case FIPS_TYPE_HMAC_SHA224:
	case FIPS_TYPE_HMAC_SHA256:
	case FIPS_TYPE_HMAC_SHA384:
	case FIPS_TYPE_HMAC_SHA512:
#if (defined CONFIG_CMRT_S3HC || defined CONFIG_CMRT_S3HC2)
	case FIPS_TYPE_HMAC_SHA3_224:
	case FIPS_TYPE_HMAC_SHA3_256:
	case FIPS_TYPE_HMAC_SHA3_384:
	case FIPS_TYPE_HMAC_SHA3_512:
#endif
	case FIPS_TYPE_SECRET:
	case FIPS_TYPE_WRAP_KEY:
		break;
	default:
		status = -EINVAL;
		goto out;
	}

	other_info = (fips_other_info *)(uint8_t *)ALIGN_32_BIT_POINTER(shared_secret + shared_secret_length);
	components = (fips_fixed_info_components *)((uint8_t *)other_info + sizeof(fips_other_info));
	data = (fips_fixed_info_data *)((uint8_t *)components + sizeof(fips_fixed_info_components));

	status = fips_instanstiate_other_info(h, 1, other_info, components, data);
	if (status) {
		goto out;
	}

	status = fips_check_valid_key_length(h->params[2].value.a, other_info->output_key_length);
	if (status) {
		dprintk("Algorithm and key length not consistent\n");
		goto out;
	}

	salt = (uint8_t *)ALIGN_32_BIT_POINTER((uint8_t *)data + sizeof(fips_fixed_info_data));
	memset(salt, 0x00, 32 * sizeof(uint8_t));

	if (other_info->salt_size == 0) {
		salt_length = 32;
	} else if (other_info->salt_size <= 32) {
		memcpy(salt, other_info->salt, other_info->salt_size * sizeof(uint8_t));
		salt_length = other_info->salt_size;
	} else {
		fips_hash(other_info->salt, other_info->salt_size, FIPS_HASH_SHA256, salt, &salt_length);
	}

	dhexdump("Salt", salt, salt_length);

	asset = salt + (32 * sizeof(uint8_t));
	SET_FIPS_HEADER(asset, state->user, h->params[2].value.a);
	SET_FIPS_KDF_HEADER_LENGTH(asset, other_info->output_key_length);

	asset_length = 4 * sizeof(uint32_t) + other_info->output_key_length;
	work_area = (uint8_t *)ALIGN_32_BIT_POINTER(asset + asset_length);

	switch (step) {
	case DERIVE_KEY_ONE_STEP:
		switch (other_info->fixed_info_type) {
		case FIPS_KDF_FIXED_INFO_NONE:
			dprintk("FIPS_KDF_FIXED_INFO_NONE");
			status = sp800_108_kdf(GET_FIPS_KDF_KEY(asset), other_info->output_key_length,
					salt, salt_length, z, z_length, NULL, 0, work_area);
			break;
		case FIPS_KDF_FIXED_INFO_DATA:
			status = sp800_108_kdf(GET_FIPS_KDF_KEY(asset), other_info->output_key_length,
					salt, salt_length, z, z_length, data->data, data->data_size, work_area);
			break;
		default:
			status = -EINVAL;
			goto out;
		}
		break;
	case DERIVE_KEY_TWO_STEP:
		switch (other_info->fixed_info_type) {
		case FIPS_KDF_FIXED_INFO_NONE:
			dprintk("FIPS_KDF_FIXED_INFO_NONE");
			status = kdf_data_extraction_expansion(GET_FIPS_KDF_KEY(asset), other_info->output_key_length,
					salt, salt_length, z, z_length, NULL, 0, work_area);
			break;
		case FIPS_KDF_FIXED_INFO_DATA:
			status = kdf_data_extraction_expansion(GET_FIPS_KDF_KEY(asset), other_info->output_key_length,
					salt, salt_length, z, z_length, data->data, data->data_size, work_area);
			break;
		case FIPS_KDF_FIXED_INFO_COMPONENTS:
			status = kdf_component_extraction_expansion(GET_FIPS_KDF_KEY(asset), other_info->output_key_length,
					salt, salt_length, z, z_length, components->label, components->label_size,
					components->context, components->context_size, work_area);
			break;
		default:
			status = -EINVAL;
			goto out;
		}
		break;
	default:
		status = -EINVAL;
		goto out;
	}

	status = fips_write_asset_to_teefs(state,
			(fips_asset_identifier *) (h->params[3].memref.offset + SAC_MEMORY_BASE),
			h->params[3].memref.size, asset, asset_length);

out:
	destroy_workcontext(status);
	return status;
}
