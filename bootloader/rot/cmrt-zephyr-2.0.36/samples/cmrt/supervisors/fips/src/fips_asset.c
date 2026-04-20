/*
 * Copyright (c) 2020-2023 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

#include <zephyr.h>
#include <device.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <ctype.h>

#include <errno.h>
#include <hexutil.h>

#include <cri/cmrt/teedev_dmac.h>
#include <cri/cmrt/sac.h>
#include <cri/cmrt/sic.h>
#include <cri/cmrt/aes.h>
#include <cri/cmrt/tee_client_api.h> /* TEEC_MEMREF values */
#include <cri/cmrt/tee_client_abi.h>
#include <cri/cmrt.h>
#include <cri/cmrt/omc.h>
#include <cri/cmrt/omc_reg.h>

#include <cri/cmrt/fips/fips_types.h>

#include "teec_cmvp.h"
#include "teefs_cmvp.h"
#include "fips_asset.h"
#include "fips.h"
#include "cri_utils.h"
#include "cmvp_sw.h"

const uint32_t rsa_element_lengths[] = { 256, 384, 512 };
const uint32_t rsa_crt_element_lengths[] = { 128, 192, 256 };

void fips_get_rsa_type(uint32_t type,
		uint8_t *rsa_type,
		uint8_t *fips_rsa_type)
{
	*fips_rsa_type = type;
	switch (type) {
	case FIPS_RSA_2K:
	case FIPS_RSA_3K:
	case FIPS_RSA_4K:
		*rsa_type = FIPS_RSA;
		break;
	case FIPS_RSA_PF_2K:
	case FIPS_RSA_PF_3K:
	case FIPS_RSA_PF_4K:
		*rsa_type = FIPS_RSA_PF;
		break;
	case FIPS_RSA_CRT_2K:
	case FIPS_RSA_CRT_3K:
	case FIPS_RSA_CRT_4K:
		*rsa_type = FIPS_RSA_CRT;
		break;
	default:
		*rsa_type = FIPS_INVALID;
	}
}

int32_t fips_read_asset_from_teefs(fips_state_t *state,
		fips_asset_identifier *source_asset,
		uint32_t size,
		uint8_t *asset,
		uint32_t *asset_length)
{
	int32_t status = 0;

	teefs_command_t cmd;

	if (size != sizeof(fips_asset_identifier)) {
		status = -EINVAL;
		goto out;
	}

	switch (source_asset->location) {
	case FIPS_ASSET_DYNAMIC:
		cmd = READ_FILE_RAM;
		break;
	case FIPS_ASSET_STATIC:
		cmd = READ_FILE_OTP;
		break;
	default:
		status = -EINVAL;
		goto out;
	}

	dprintk("Going to read from buffer\n");
	status = process_teefs_request(cmd, source_asset->asset_name_length,
			source_asset->asset_name, asset, asset_length);
	dprintk("Teefs read: %d\n", status);
	if (status) goto out;

	if (TEST_MAGIC(asset) || TEST_VER_MINOR(asset) || TEST_VER_MAJOR(asset)) {
		dprintk("Error in header\n");
		status = -EINVAL;
		goto out;
	}

	if ((fips_get_asset_permissions((fips_owner_user) state->user,
			(fips_owner_user)GET_ASSET_OWNER_FROM_ASSET(asset)) & FIPS_READ) != FIPS_READ) {
		dprintk("Requested asset not readable by user %i\n", state->user);
		status = -EACCES;
		goto out;
	}

out:
	return status;
}

int32_t fips_read_asset_of_type_from_teefs(fips_state_t *state,
		fips_asset_identifier *source_asset,
		uint32_t size,
		uint8_t *asset,
		uint32_t *asset_length,
		uint8_t asset_type)
{
	int32_t status = 0;

	status = fips_read_asset_from_teefs(state, source_asset, size, asset, asset_length);
	if (status) goto out;

	if (GET_ASSET_TYPE_FROM_ASSET(asset) != asset_type) {
		dprintk("Requested asset not of type %i\n", asset_type);
		status = -EPERM;
	}

out:
	return status;
}

int32_t fips_write_asset_to_teefs(fips_state_t *state,
		fips_asset_identifier *destination_asset,
		uint32_t size,
		uint8_t *asset,
		uint32_t asset_length)
{
	int32_t status;

	teefs_command_t cmd;

	uint32_t length = asset_length;

	if (size != sizeof(fips_asset_identifier)) {
		status = -EINVAL;
		goto out;
	}

	switch (destination_asset->location) {
	case FIPS_ASSET_DYNAMIC:
		cmd = WRITE_FILE_RAM;
		break;
	case FIPS_ASSET_STATIC:
		cmd = WRITE_FILE_OTP;
		break;
	default:
		status = -EINVAL;
		goto out;
	}

	if ((fips_get_asset_permissions((fips_owner_user) state->user,
			(fips_owner_user)GET_ASSET_OWNER_FROM_ASSET(asset)) & FIPS_WRITE) != FIPS_WRITE) {
		dprintk("Requested asset not writable by user %i\n", state->user);
		status = -EACCES;
		goto out;
	}

	if (!fips_check_valid_asset_size((fips_asset *)asset,
		GET_ASSET_TYPE_FROM_ASSET(asset), asset_length)) {
		dprintk("The asset size and type are not coherent\n");
		status = -EINVAL;
		goto out;
	}

	dprintk("Going to write the buffer\n");
	status = process_teefs_request(cmd, destination_asset->asset_name_length,
			destination_asset->asset_name, asset, &length);
	dprintk("Teefs write: %d\n", status);

out:
	return status;
}

int32_t fips_read_asset_from_shared_memory(fips_state_t *state,
		teec_abi_invokecommand_t *h,
		uint32_t index,
		uint8_t *asset,
		uint32_t *asset_length)
{
	int32_t status;

	status = fips_read_from_shared_memory(h, index, asset, asset_length);
	if (status) goto out;

	if (TEST_MAGIC(asset) || TEST_VER_MINOR(asset) || TEST_VER_MAJOR(asset)) {
		dprintk("Error in header\n");
		status = -EINVAL;
		goto out;
	}

	/* Enforce imported asset as external */
	SET_ASSET_INTERNAL_FLAG_IN_ASSET(asset, FIPS_EXTERNAL_ASSET);

	dhexdump("asset", asset, *asset_length);

	if ((fips_get_asset_permissions((fips_owner_user) state->user,
			(fips_owner_user)GET_ASSET_OWNER_FROM_ASSET(asset)) & FIPS_READ) != FIPS_READ) {
		dprintk("Requested asset readable by user %i\n", state->user);
		status = -EACCES;
		goto out;
	}

out:
	return status;
}

int32_t fips_delete_asset(fips_state_t *state, teec_abi_invokecommand_t *h, fips_asset_location location)
{
	int status;

	fips_asset_identifier *asset;

	uint8_t *loaded_asset;

	uint32_t loaded_asset_length = 0;

	dprintk("FIPS_DELETE_DYNAMIC_ASSET\n");
	CHECK_COMMAND(FIPS_DELETE_DYNAMIC_ASSET);

	switch (location) {
	case FIPS_ASSET_DYNAMIC:
		((uint32_t *)workcontext)[0] = FIPS_DELETE_DYNAMIC_ASSET;
		break;
	case FIPS_ASSET_STATIC:
		((uint32_t *)workcontext)[0] = FIPS_DELETE_STATIC_ASSET;
		break;
	default:
		status = -EPERM;
		goto out;
	}

	loaded_asset = workcontext + sizeof(uint32_t);

	asset = (fips_asset_identifier *) (h->params[0].memref.offset
				+ SAC_MEMORY_BASE);

	if (asset->location != location) {
		dprintk("Wrong asset location\n");
		status = -EPERM;
		goto out;
	}

	status = fips_read_asset_from_teefs(state, asset, h->params[0].memref.size,
			loaded_asset, &loaded_asset_length);
	if (status) goto out;

	if ((fips_get_asset_permissions((fips_owner_user) state->user,
			(fips_owner_user)GET_ASSET_OWNER_FROM_ASSET(loaded_asset)) & FIPS_WRITE) != FIPS_WRITE) {
		dprintk("Requested asset not writable by user %i\n", state->user);
		status = -EACCES;
		goto out;
	}

	switch (location) {
	case FIPS_ASSET_DYNAMIC:
		status = process_teefs_request(DELETE_RAM, asset->asset_name_length, asset->asset_name, NULL, NULL);
		break;
	case FIPS_ASSET_STATIC:
		status = process_teefs_request(DELETE_OTP, asset->asset_name_length, asset->asset_name, NULL, NULL);
		break;
	default:
		status = -EPERM;
		goto out;
	}

out:
	destroy_workcontext(sizeof(uint32_t) + loaded_asset_length);
	return status;
}

int32_t fips_move_asset(fips_state_t *state, teec_abi_invokecommand_t *h)
{
	int32_t status;

	fips_asset_identifier *asset_id;

	uint8_t *asset;
	uint32_t asset_len = 0;

	status = 0;
	dprintk("FIPS_SERVICE_MOVE_ASSET\n");
	CHECK_COMMAND(FIPS_SERVICE_MOVE_ASSET);

	asset_id = (fips_asset_identifier *) (h->params[0].memref.offset + SAC_MEMORY_BASE);
	asset = workcontext + sizeof(uint32_t);

	if (asset_id->location != FIPS_ASSET_DYNAMIC) {
		status = -EPERM;
		goto out;
	}

	status = fips_read_asset_from_teefs(state, asset_id, h->params[0].memref.size, asset, &asset_len);
	if (status) goto out;

	asset_id->location = FIPS_ASSET_STATIC;

	status = fips_write_asset_to_teefs(state, asset_id, h->params[0].memref.size, asset, asset_len);
	if (status) goto out;

	asset_id->location = FIPS_ASSET_DYNAMIC;
	status = process_teefs_request(DELETE_RAM, asset_id->asset_name_length, asset_id->asset_name, NULL, NULL);

out:
	destroy_workcontext(4 + 4 + asset_len);
	return status;
}

static int32_t obliterate_all_roots(void)
{
	int32_t res;

	cri_otp_t omc = cri_otp_open(CRI_O_SYNC);
	if (!cri_is_valid(omc)) {
		dprintk("Failed to open omc\n");
		res = -EIO;
		goto out1;
	}

	int i;

	for (i = 0; i < CONFIG_CRI_OMC_ROOTS_NUM; i++) {
		res = cri_otp_obliterate_root(omc, i);
		if (res) {
			dprintk("Root %d: error %d\n", i, res);
			res = -EIO;
		}
	}

out1:
	cri_otp_close(omc);
	return res;
}

int32_t fips_zeroize_assets(fips_state_t *state, teec_abi_invokecommand_t *h)
{
	int32_t status;

	dprintk("FIPS_SERVICE_ZEROIZE\n");
	CHECK_COMMAND(FIPS_SERVICE_ZEROIZE);

	if (h->params[0].value.b != 0) {
		status = -EINVAL;
		goto out;
	}

	switch (h->params[0].value.a) {
	case FIPS_ZEROIZE_DYNAMIC:
		status = dismantle_teefs_RAM();
		if (status) goto out;

		status = setup_teefs_RAM();
		break;
#if CONFIG_FIPS_OTP_TEEFS_SIZE > 0
	case FIPS_ZEROIZE_STATIC:
		status = dismantle_teefs_OTP();
		if (status) goto out;
		break;
#endif
	case FIPS_ZEROIZE_ALL:
		obliterate_all_roots();

		status = dismantle_teefs_RAM();
		if (status) goto out;
#if CONFIG_FIPS_OTP_TEEFS_SIZE > 0
		status = dismantle_teefs_OTP();
		if (status) goto out;
#endif
		break;

	default:
		status = -EINVAL;
		goto out;
	}

out:
	destroy_workcontext(sizeof(uint32_t));
	return status;
}

int32_t fips_list_asset_service(fips_state_t *state, teec_abi_invokecommand_t *h)
{
	int32_t status;

	uint32_t found;

	dprintk("FIPS_SERVICE_LIST_ASSETS\n");
	CHECK_COMMAND(FIPS_SERVICE_LIST_ASSETS);

	if ((h->params[0].value.b != 0) || (h->params[1].value.b != 0)) {
		status = -EINVAL;
		goto out;
	}

	h->params[1].value.a = 0;
	status = fips_list_assets_loc((uint8_t *) (h->params[2].memref.offset + SAC_MEMORY_BASE),
			h->params[2].memref.size, &found, h->params[0].value.a);

	if (status == -EMSGSIZE) {
		dprintk("Ran out of memory\n");
		memset((uint8_t *) (h->params[1].memref.offset + SAC_MEMORY_BASE), 0x00, h->params[1].memref.size);
		goto out;
	}

	dprintk("Found %i assets\n", found);
	h->params[1].value.a = found;

out:
	destroy_workcontext(sizeof(uint32_t));
	return status;
}

cri_ecc_curve_t cri_pke_get_fips_curve_from_asset(fips_asset *asset)
{
	return cri_pke_get_fips_curve(((uint32_t *) asset)[3]);
}

cri_ecc_curve_t cri_pke_get_fips_curve(fips_curves type)
{
	uint8_t pke_curve;
	cri_ecc_curve_t curve = NULL;

	switch (type) {
	case FIPS_ECC_NIST_P224:
		pke_curve = CRI_ECC_CURVE_NIST_P224;
		break;

	case FIPS_ECC_NIST_P256:
		pke_curve = CRI_ECC_CURVE_NIST_P256;
		break;

	case FIPS_ECC_NIST_P384:
		pke_curve = CRI_ECC_CURVE_NIST_P384;
		break;

	case FIPS_ECC_NIST_P521:
		pke_curve = CRI_ECC_CURVE_NIST_P521;
		break;

	default:
		dprintk("Curve identifier not known\n");
		goto out;
	}

	curve = cri_pke_get_curve(pke_curve);
out:
	return curve;
}

static int32_t fips_check_valid_ecc_asset_size(fips_asset_type type,
		cri_ecc_curve_t curve,
		size_t checksize)
{
	int32_t status = 0;

	switch (type) {
	case FIPS_TYPE_ECDSA_PUBLIC_KEY:
		if (checksize == GET_ECDSA_PUBLIC_KEY_ASSET_SIZE(curve)) {
			status = 1;
		}
		break;
	case FIPS_TYPE_ECDSA_KEYPAIR:
		if (checksize == GET_ECDSA_KEYPAIR_ASSET_SIZE(curve)) {
			status = 1;
		}
		break;
	case FIPS_TYPE_ECDH_PUBLIC_KEY:
		if (checksize == GET_ECDH_PUBLIC_KEY_ASSET_SIZE(curve)) {
			status = 1;
		}
		break;
	case FIPS_TYPE_ECDH_KEYPAIR:
		if (checksize == GET_ECDH_KEYPAIR_ASSET_SIZE(curve)) {
			status = 1;
		}
		break;
	default:
		status = 0;
	}

	return status;
}

int32_t fips_check_valid_asset_size(fips_asset *asset,
		fips_asset_type type,
		size_t checksize)
{
	int32_t status = 0;

	uint8_t rsa_type = 0;
	uint8_t fips_rsa_type = 0;

	size_t size;

	uint8_t *ptr = NULL;

	uint32_t secret_key_length;

	cri_ecc_curve_t curve;

	size = checksize - GET_HEADER_SIZE();
	secret_key_length = GET_SECRET_KEY_LENGTH_FROM_ASSET(asset);

	switch (type) {
	case FIPS_TYPE_AES:
	case FIPS_TYPE_WRAP_KEY:
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
		size = size - sizeof(uint32_t);
		if (!fips_check_valid_key_length(type, size) && (size == secret_key_length)) {
			status = 1;
		}
		break;
	case FIPS_TYPE_SECRET:
		size = size - sizeof(uint32_t);
		if ((size >= 1) && (size <= 512) && (size == secret_key_length)) {
			status = 1;
		}
		break;
	case FIPS_TYPE_SHARED_SECRET:
		size = size - sizeof(uint32_t);
		if ((size >= 16) && (size <= 66) && (size == secret_key_length)) {
			if (size == 66) {
				ptr = (uint8_t *) GET_SHARED_SECRET_FROM_ASSET(asset);
				if ((ptr[0] == 0) || (ptr[0] == 1)) {
					status = 1;
				}
			} else {
				status = 1;
			}
		}
		break;
	case FIPS_TYPE_RSA_PUBLIC_KEY:
		GET_RSA_KEY_TYPE_FROM_ASSET(asset, rsa_type, fips_rsa_type);
		if (checksize == GET_RSA_PUBLIC_KEY_ASSET_SIZE(fips_rsa_type)) {
			status = 1;
		}
		break;
	case FIPS_TYPE_RSA_KEYPAIR:
		GET_RSA_KEY_TYPE_FROM_ASSET(asset, rsa_type, fips_rsa_type);
		if (checksize == GET_RSA_ASSET_SIZE(fips_rsa_type)) {
			status = 1;
		}
		break;
	case FIPS_TYPE_RSA_PF_KEYPAIR:
		GET_RSA_KEY_TYPE_FROM_ASSET(asset, rsa_type, fips_rsa_type);
		if (checksize == GET_RSA_PF_ASSET_SIZE(fips_rsa_type)) {
			status = 1;
		}
		break;
	case FIPS_TYPE_RSA_CRT_KEYPAIR:
		GET_RSA_KEY_TYPE_FROM_ASSET(asset, rsa_type, fips_rsa_type);
		if (checksize == GET_RSA_CRT_ASSET_SIZE(fips_rsa_type)) {
			status = 1;
		}
		break;
	case FIPS_TYPE_ECDSA_PUBLIC_KEY:
	case FIPS_TYPE_ECDSA_KEYPAIR:
	case FIPS_TYPE_ECDH_PUBLIC_KEY:
	case FIPS_TYPE_ECDH_KEYPAIR:
		curve = cri_pke_get_fips_curve_from_asset(asset);
		if (!curve) {
			dprintk("Failed to obtain a curve\n");
			status = -EIO;
			goto out;
		}

		status = fips_check_valid_ecc_asset_size(type, curve, checksize);
		if (status == 1) {
			break;
		}
		break;
	default:
		dprintk("Unknown asset type\n");
	}

out:
	return status;
}
