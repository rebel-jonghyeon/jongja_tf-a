/*
 * Copyright (c) 2020-2024 Cryptography Research, Inc. (CRI).
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
#include <smcalls.h>

#include <cri/cmrt/teedev_dmac.h>
#include <cri/cmrt/aes.h>
#include <cri/cmrt/hc.h>
#include <cri/cmrt/dd.h>
#include <cri/cmrt/eac.h>
#include <cri/cmrt/tee_client_api.h> /* TEEC_MEMREF values */
#include <cri/cmrt/tee_client_abi.h>
#include <cri/cmrt/pke.h>
#include <cri/cmrt.h>

#include <cri/cmrt/fips/fips_types.h>

#include "teec_cmvp.h"
#include "teefs_cmvp.h"
#include "fips_asset.h"
#include "cmvp_sw.h"

/*
 * By Column, we have CO, User and Anonymous. Corresponding to the
 * table on page 43 of the specification.
 */
static uint8_t permission_table[NUMBER_OF_SERVICES][4] = {
		{ 0, 0, 0, 0 }, /* FIPS_SERVICE_INVALID_COMMAND */
		{ 1, 1, 0, 1 }, /* FIPS_SERVICE_LOGIN_FINAL */
		{ 1, 0, 0, 0 }, /* FIPS_SERVICE_CREATE_USER */
		{ 1, 0, 0, 0 }, /* FIPS_SERVICE_DELETE_USER */
		{ 1, 1, 0, 1 }, /* FIPS_SERVICE_GEN_SYMM_KEY */
		{ 1, 1, 0, 1 }, /* FIPS_SERVICE_DERIVE_SYMM_KEY */
		{ 1, 1, 0, 1 }, /* FIPS_SERVICE_DERIVE_SYMM_KEY_TWO_STEP */
		{ 1, 1, 0, 1 }, /* FIPS_SERVICE_GEN_EC_KEYPAIR */
		{ 1, 1, 0, 1 }, /* FIPS_SERVICE_GEN_RSA_KEYPAIR */
		{ 1, 1, 0, 1 }, /* FIPS_SERVICE_IMPORT_KEY */
		{ 1, 1, 0, 1 }, /* FIPS_SERVICE_EXPORT_KEY */
		{ 1, 1, 0, 0 }, /* FIPS_SERVICE_EXPORT_KEY_KTC */
		{ 1, 1, 0, 1 }, /* FIPS_SERVICE_AES_ECB */
		{ 1, 1, 0, 1 }, /* FIPS_SERVICE_AES_GCM_INIT */
		{ 1, 1, 0, 1 }, /* FIPS_SERVICE_AES_GCM_AAD_UPDATE */
		{ 1, 1, 0, 1 }, /* FIPS_SERVICE_AES_GCM_UPDATE */
		{ 1, 1, 0, 1 }, /* FIPS_SERVICE_AES_GCM_ENCRYPT_FINAL */
		{ 1, 1, 0, 1 }, /* FIPS_SERVICE_AES_GCM_DECRYPT_FINAL */
		{ 1, 1, 0, 1 }, /* FIPS_SERVICE_AES_CBC_INIT */
		{ 1, 1, 0, 1 }, /* FIPS_SERVICE_AES_CBC_UPDATE */
		{ 1, 1, 0, 1 }, /* FIPS_SERVICE_AES_CBC_FINAL */
		{ 1, 1, 0, 1 }, /* FIPS_SERVICE_AES_CTR_INIT */
		{ 1, 1, 0, 1 }, /* FIPS_SERVICE_AES_CTR_UPDATE */
		{ 1, 1, 0, 1 }, /* FIPS_SERVICE_AES_CTR_FINAL */
		{ 1, 1, 0, 1 }, /* FIPS_SERVICE_AES_CFB128_INIT */
		{ 1, 1, 0, 1 }, /* FIPS_SERVICE_AES_CFB128_UPDATE */
		{ 1, 1, 0, 1 }, /* FIPS_SERVICE_AES_CFB128_FINAL */
		{ 1, 1, 0, 1 }, /* FIPS_SERVICE_ECDSA_SIGN */
		{ 1, 1, 0, 1 }, /* FIPS_SERVICE_ECDSA_VERIFY */
		{ 1, 1, 0, 1 }, /* FIPS_SERVICE_ECDSA_PK_TEST */
		{ 1, 1, 0, 1 }, /* FIPS_SERVICE_ECDH */
		{ 1, 1, 0, 1 }, /* FIPS_SERVICE_RSA_SIGN */
		{ 1, 1, 0, 1 }, /* FIPS_SERVICE_RSA_VERIFY */
		{ 1, 1, 0, 1 }, /* FIPS_SERVICE_MAC_GEN_INIT */
		{ 1, 1, 0, 1 }, /* FIPS_SERVICE_MAC_GEN_FINAL */
		{ 1, 1, 0, 1 }, /* FIPS_SERVICE_MAC_VERIFY_INIT */
		{ 1, 1, 0, 1 }, /* FIPS_SERVICE_MAC_VERIFY_FINAL */
		{ 1, 1, 0, 1 }, /* FIPS_SERVICE_MAC_UPDATE */
		{ 1, 1, 0, 1 }, /* FIPS_SERVICE_HASH_INIT */
		{ 1, 1, 0, 1 }, /* FIPS_SERVICE_HASH_UPDATE */
		{ 1, 1, 0, 1 }, /* FIPS_SERVICE_HASH_FINAL */
		{ 1, 1, 0, 1 }, /* FIPS_SERVICE_GET_TRNG */
		{ 1, 1, 0, 0 }, /* FIPS_SERVICE_LIST_ASSETS */
		{ 1, 1, 0, 0 }, /* FIPS_SERVICE_MOVE_ASSET */
		{ 1, 1, 0, 0 }, /* FIPS_DELETE_DYNAMIC_ASSET */
		{ 1, 1, 0, 0 }, /* FIPS_DELETE_STATIC_ASSET */
		{ 1, 0, 0, 0 }, /* FIPS_SERVICE_ZEROIZE */
		{ 1, 1, 1, 1 }, /* FIPS_SERVICE_SELF_TEST */
		{ 1, 1, 1, 0 }, /* FIPS_SERVICE_RESET */
		{ 1, 1, 1, 0 }, /* FIPS_SERVICE_SHOW_STATUS */
		{ 1, 0, 0, 1 }, /* FIPS_SERVICE_DRBG */
		{ 1, 1, 0, 1 }, /* FIPS_SERVICE_GEN_DILITHIUM_KEYPAIR */
		{ 1, 1, 0, 1 }, /* FIPS_SERVICE_DILITHIUM_SIGN */
		{ 1, 1, 0, 1 }, /* FIPS_SERVICE_DILITHIUM_VERIFY */
		{ 1, 1, 0, 1 }, /* FIPS_SERVICE_GEN_KYBER_KEM_KEYPAIR */
		{ 1, 1, 0, 1 }, /* FIPS_SERVICE_KYBER_KEM_ENC */
		{ 1, 1, 0, 1 }, /* FIPS_SERVICE_KYBER_KEM_DEC */
		{ 1, 1, 0, 1 }, /* FIPS_SERVICE_LMS_VERIFY */
		{ 1, 1, 0, 1 }, /* FIPS_SERVICE_HSS_VERIFY */
		{ 1, 1, 0, 1 }, /* FIPS_SERVICE_XMSS_VERIFY */
		{ 1, 1, 0, 1 }  /* FIPS_SERVICE_XMSSMT_VERIFY */
};

void fips_intialize_state(fips_state_t *state)
{
	state->user = FIPS_OWNER_ANONYMOUS;
	state->teec_session = 0;
	state->user_session = 0;
	state->authenticated_login_started = 0;
	state->approved_mode = 0;
	state->key_length = 0;
	state->key_value = NULL;
	state->scratch = NULL;
	state->do_reset = false;
}

void destroy_workcontext_and_halt(int32_t status)
{
	destroy_workcontext(status);
	cri_mcall_exit(-EFAULT, status, false);
}

int32_t destroy_workcontext_and_reset(fips_state_t *state)
{
	int32_t status = 0;

	destroy_workcontext(status);
	status = dismantle_teefs_RAM();
	if (status) { goto out; }

	state->do_reset = true;
out:
	return status;
}

void destroy_workcontext(int32_t length)
{
	uint32_t cmd;
	uint32_t overwrite_length = 0;

	cmd = (uint32_t) workcontext[0];

	if (length <= 0) {
		overwrite_length = MAX_WORKCONTEXT_LEN - 2;
	} else if (length < MAX_WORKCONTEXT_LEN - 1) {
		overwrite_length = length;
	} else {
		destroy_workcontext_and_halt(-EINVAL);
	}

	switch (cmd) {
	case FIPS_SERVICE_AES_ECB:
	case FIPS_SERVICE_AES_CBC_INIT:
	case FIPS_SERVICE_AES_CBC_UPDATE:
	case FIPS_SERVICE_AES_CBC_FINAL:
	case FIPS_SERVICE_AES_GCM_INIT:
	case FIPS_SERVICE_AES_GCM_AAD_UPDATE:
	case FIPS_SERVICE_AES_GCM_UPDATE:
	case FIPS_SERVICE_AES_GCM_ENCRYPT_FINAL:
	case FIPS_SERVICE_AES_GCM_DECRYPT_FINAL:
	case FIPS_SERVICE_AES_CTR_INIT:
	case FIPS_SERVICE_AES_CTR_UPDATE:
	case FIPS_SERVICE_AES_CTR_FINAL:
	case FIPS_SERVICE_AES_CFB128_INIT:
	case FIPS_SERVICE_AES_CFB128_UPDATE:
	case FIPS_SERVICE_AES_CFB128_FINAL:
		;
		aes_work_struct *aes;
		aes = (aes_work_struct *) (workcontext + sizeof(uint32_t));
		if (cri_is_valid(aes->aesengine))
			cri_aes_close(aes->aesengine);
		memset(g_inout_buffer, 0x00, MAX_TEEFS_BUFFER_LEN * sizeof(uint8_t));
		break;
	case FIPS_SERVICE_HASH_INIT:
	case FIPS_SERVICE_HASH_UPDATE:
	case FIPS_SERVICE_HASH_FINAL:
		;
		hash_work_struct *sha;
		sha = (hash_work_struct *) (workcontext + sizeof(uint32_t));
		if (cri_is_valid(sha->hashengine)) {
			dprintk("Closing the hash engine\n");
			cri_hc_close(sha->hashengine);
		}
		memset(g_inout_buffer, 0x00, MAX_TEEFS_BUFFER_LEN * sizeof(uint8_t));
		break;
	case FIPS_SERVICE_MAC_GEN_INIT:
	case FIPS_SERVICE_MAC_GEN_FINAL:
	case FIPS_SERVICE_MAC_VERIFY_INIT:
	case FIPS_SERVICE_MAC_VERIFY_FINAL:
	case FIPS_SERVICE_MAC_UPDATE:
		;
		mac_work_struct *mac;
		hash_work_struct *hsha;
		mac = (mac_work_struct *) (workcontext + sizeof(uint32_t));
		hsha = (hash_work_struct *) &(mac->sha);
		if (cri_is_valid(hsha->hashengine)) {
			dprintk("Closing the hash engine\n");
			cri_hc_close(hsha->hashengine);
		}
		memset(g_inout_buffer, 0x00, MAX_TEEFS_BUFFER_LEN * sizeof(uint8_t));
		break;
	}

	if (overwrite_length != 0) {
		memset(workcontext, 0x00, overwrite_length);
	}
}

int32_t get_approved_mode(fips_command operation, uint8_t *approved_mode)
{
	u32_t value = cri_read_reg(CMRT_SIC_BASE, R_FIPS_MODE);
	if (((value & FIPS_MODE_RUNNING_FLAG) == FIPS_MODE_RUNNING_FLAG) &&
		(operation < NUMBER_OF_SERVICES)) {
		*approved_mode = permission_table[operation][3];
	} else {
		*approved_mode = 0;
	}

	return 0;
}

uint32_t fips_get_permissions(fips_owner_user user, fips_command operation)
{
	int column;

	switch (user) {
	case FIPS_OWNER_ANONYMOUS:
		column = 2;
		return permission_table[operation][column];
		break;

	case FIPS_OWNER_CRYPTO_OFFICER:
		column = 0;
		return permission_table[operation][column];
		break;

	case FIPS_OWNER_USER_0:
	case FIPS_OWNER_USER_1:
	case FIPS_OWNER_USER_2:
	case FIPS_OWNER_USER_3:
	case FIPS_OWNER_USER_4:
	case FIPS_OWNER_USER_5:
		column = 1;
		return permission_table[operation][column];
		break;

	default:
		return 0;
	}
}

/*
 * FIPS_DENIED no access
 * FIPS_READ read access
 * FIPS_WRITE write access
 */
uint32_t fips_get_asset_permissions(fips_owner_user session_user,
		fips_owner_user asset_owner)
{

	switch (session_user) {
	case FIPS_OWNER_ANONYMOUS:
		return (FIPS_DENIED);
		break;

	case FIPS_OWNER_CRYPTO_OFFICER:
		if ((asset_owner == FIPS_OWNER_CRYPTO_OFFICER)
				|| (asset_owner == FIPS_OWNER_ALL)) {
			return (FIPS_WRITE | FIPS_READ);
		} else {
			return FIPS_DENIED;
		}
		break;

	case FIPS_OWNER_USER_0:
	case FIPS_OWNER_USER_1:
	case FIPS_OWNER_USER_2:
	case FIPS_OWNER_USER_3:
	case FIPS_OWNER_USER_4:
	case FIPS_OWNER_USER_5:
		if (asset_owner == session_user) {
			return (FIPS_WRITE | FIPS_READ);
		} else if (asset_owner == FIPS_OWNER_ALL) {
			return FIPS_READ;
		} else {
			return FIPS_DENIED;
		}
		break;

	default:
		return FIPS_DENIED;
	}
}

int32_t fips_is_fips_asset_location(int asset)
{
	int32_t valid = 0;

	switch (asset) {
	case FIPS_ASSET_DYNAMIC:
	case FIPS_ASSET_STATIC:
		valid = 1;
	};

	return valid;

}

int32_t fips_is_fips_direction(int direction)
{
	int32_t valid = 0;

	switch (direction) {
	case FIPS_CIPHER_ENCRYPT:
	case FIPS_CIPHER_DECRYPT:
		valid = 1;
	};

	return valid;

}

int32_t fips_is_valid_tag_length(uint32_t length)
{
	if ((length == 16) ||
		(length == 15) ||
		(length == 14) ||
		(length == 13) ||
		(length == 12))
		return 1;
	else
		return 0;
}

int32_t fips_asset_to_buffer(fips_asset *asset, uint8_t *inout_buffer,
		uint32_t *inout_buffer_len)
{
	fips_asset_type type;
	type = (asset->metadata) & 0xff;
	int32_t status = 0;

	size_t size;
	size_t total_len;
	uint8_t *tmp_bf = inout_buffer;
	uint32_t remainder;

	total_len = 0;

	size = sizeof(fips_asset) - sizeof(asset->asset_data);
	total_len += size;
	if (total_len < (MAX_TEEFS_BUFFER_LEN))
		memcpy(tmp_bf, (uint8_t *) asset, size);
	else {
		dprintk("TEEFS buffer too small for asset\n");
		status = 1;
		goto out;
	}
	tmp_bf += size;

	switch (type) {
	case FIPS_TYPE_AES:
	case FIPS_TYPE_AES_GCM_ENCRYPT:
	case FIPS_TYPE_AES_GCM_DECRYPT:
	case FIPS_TYPE_WRAP_KEY:
		;
		fips_aes_key *aeskey;
		aeskey = (fips_aes_key *) asset->asset_data;
		size = sizeof(fips_aes_key) - sizeof(aeskey->key);
		total_len += size;
		if (total_len < (MAX_TEEFS_BUFFER_LEN))
			memcpy(tmp_bf, (uint8_t *) aeskey, size);
		else {
			dprintk("TEEFS buffer too small for asset\n");
			status = 1;
			goto out;
		}
		tmp_bf += size;
		if (total_len < (MAX_TEEFS_BUFFER_LEN))
			memcpy(tmp_bf, aeskey->key, aeskey->size);
		else {
			dprintk("TEEFS buffer too small for asset\n");
			status = 1;
			goto out;
		}
		tmp_bf += aeskey->size;
		total_len += aeskey->size;
		status = 0;
		break;
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
		;
		fips_hmac_key *hmackey;
		hmackey = (fips_hmac_key *) asset->asset_data;
		size = sizeof(fips_hmac_key) - sizeof(hmackey->key);
		total_len += size;
		if (total_len < (MAX_TEEFS_BUFFER_LEN))
			memcpy(tmp_bf, (uint8_t *) hmackey, size);
		else {
			dprintk("TEEFS buffer too small for asset\n");
			status = 1;
			goto out;
		}
		tmp_bf += size;
		if (total_len < (MAX_TEEFS_BUFFER_LEN))
			memcpy(tmp_bf, hmackey->key, hmackey->size);
		else {
			dprintk("TEEFS buffer too small for asset\n");
			status = 1;
			goto out;
		}
		tmp_bf += hmackey->size;
		total_len += hmackey->size;
		status = 0;
		break;
	default:
		dprintk("Unknown asset type\n");
		goto out;
	}

	remainder = total_len % 4;
	if (remainder != 0) {
		total_len += remainder;
		if (total_len < (MAX_TEEFS_BUFFER_LEN))
			memset(tmp_bf, 0x00, remainder);
		else {
			dprintk("TEEFS buffer too small for asset\n");
			status = 1;
			goto out;
		}

	}

	*inout_buffer_len = total_len;
	dhexdump("In the buffer", inout_buffer, *inout_buffer_len);
	goto out1;

out:
	memset(inout_buffer, 0x00, MAX_TEEFS_BUFFER_LEN);
out1:
	return status;
}

int32_t fips_check_valid_key_length(fips_asset_type type, size_t checksize)
{
	int32_t status = -EINVAL;

	dprintk("type: %d, length: %d\n", type, checksize);

	if (checksize == 0) {
		goto err;
	}

	switch (type) {
	case FIPS_TYPE_SECRET:
		if (checksize <= 512) {
			status = 0;
		}
		break;
	case FIPS_TYPE_AES:
#ifdef CONFIG_CMRT_AES_192BIT
		if ((checksize == 16) || (checksize == 24) || (checksize == 32)) {
#else
		if ((checksize == 16) || (checksize == 32)) {
#endif
			status = 0;
		}
		break;
	case FIPS_TYPE_WRAP_KEY:
	case FIPS_TYPE_AES_GCM_ENCRYPT:
	case FIPS_TYPE_AES_GCM_DECRYPT:
#ifdef CONFIG_CMRT_AES_192BIT
		if ((checksize == 16) || (checksize == 24) || (checksize == 32)) {
#else
		if ((checksize == 16) || (checksize == 32)) {
#endif
			status = 0;
		}
		break;
	case FIPS_TYPE_HMAC_SHA224:
		if (checksize <= 64) {
			status = 0;
		}
		break;
	case FIPS_TYPE_HMAC_SHA256:
		if (checksize <= 64) {
			status = 0;
		}
		break;
	case FIPS_TYPE_HMAC_SHA384:
		if (checksize <= 128) {
			status = 0;
		}
		break;
	case FIPS_TYPE_HMAC_SHA512:
		if (checksize <= 128) {
			status = 0;
		}
		break;
#if (defined CONFIG_CMRT_S3HC || defined CONFIG_CMRT_S3HC2)
	case FIPS_TYPE_HMAC_SHA3_224:
		if (checksize <= 144) {
			status = 0;
		}
		break;
	case FIPS_TYPE_HMAC_SHA3_256:
		if (checksize <= 136) {
			status = 0;
		}
		break;
	case FIPS_TYPE_HMAC_SHA3_384:
		if (checksize <= 104) {
			status = 0;
		}
		break;
	case FIPS_TYPE_HMAC_SHA3_512:
		if (checksize <= 72) {
			status = 0;
		}
		break;
#endif
	default:
		dprintk("Unknown asset type\n");
	}

err:
	return status;
}

int32_t buffer_to_fips_asset(uint8_t *inout_buffer,
		uint32_t *inout_buffer_len, uint8_t *destination,
		uint8_t *workbuffer)
{
	fips_asset *asset;
	fips_asset_type type;
	size_t len;
	uint8_t *tmp_destination;
	uint8_t *tmp_source;
	int32_t status;
	fips_command workcontext_type = 0;
	uint32_t *workcontext_32;
	void *workcontext_struct = NULL;

	status = 0;

	if ((destination == NULL) | (inout_buffer == NULL)) {
		dprintk("Buffer pointers are not valid\n");
		status = 1;
		goto out;
	}

	if (workbuffer != NULL) {
		workcontext_32 = (uint32_t *) workbuffer;
		workcontext_type = workcontext_32[0];
		dprintk("Workcontext_type %d\n", workcontext_type);
		workcontext_struct = (void *) (workbuffer + 4);
	}

	tmp_destination = destination;
	tmp_source = inout_buffer;

	asset = (fips_asset *) tmp_destination;
	len = sizeof(fips_asset) - sizeof(asset->asset_data);
	memcpy(tmp_destination, tmp_source, len);
	tmp_destination += len;
	tmp_source += len;

	type = GET_ASSET_TYPE(asset->metadata);

	switch (type) {
	case FIPS_TYPE_AES:
	case FIPS_TYPE_AES_GCM_ENCRYPT:
	case FIPS_TYPE_AES_GCM_DECRYPT:
	case FIPS_TYPE_WRAP_KEY:
		;
		aeskey_work_struct *aeskey_work = NULL;
		if (((workcontext_type >= FIPS_SERVICE_AES_ECB)
				&& (workcontext_type <= FIPS_SERVICE_AES_CFB128_FINAL))
				|| (workcontext_type == FIPS_SERVICE_IMPORT_KEY)
				|| (workcontext_type == FIPS_SERVICE_EXPORT_KEY)
				|| (workcontext_type == FIPS_SERVICE_MAC_GEN_INIT)
				|| (workcontext_type == FIPS_SERVICE_MAC_VERIFY_INIT)) {
			aeskey_work = (aeskey_work_struct *) workcontext_struct;
			aeskey_work->asset = (fips_asset *) (tmp_destination - len);
			asset->asset_data = tmp_destination + sizeof(asset->asset_data);
		}
		tmp_destination += PTR_SIZE;
		fips_aes_key *aeskey;
		fips_aes_key *aeskeys;
		aeskeys = (fips_aes_key *) tmp_source;
		aeskey = (fips_aes_key *) tmp_destination;
		if (((workcontext_type >= FIPS_SERVICE_AES_ECB)
				&& (workcontext_type <= FIPS_SERVICE_AES_CFB128_FINAL))
				|| (workcontext_type == FIPS_SERVICE_IMPORT_KEY)
				|| (workcontext_type == FIPS_SERVICE_EXPORT_KEY)
				|| (workcontext_type == FIPS_SERVICE_MAC_GEN_INIT)
				|| (workcontext_type == FIPS_SERVICE_MAC_VERIFY_INIT)) {
			aeskey_work->key = (fips_aes_key *) tmp_destination;
		}
		len = sizeof(fips_aes_key) - PTR_SIZE;
		memcpy(tmp_destination, tmp_source, len);
		tmp_destination += len;
		tmp_source += len;
		if (((workcontext_type >= FIPS_SERVICE_AES_ECB)
				&& (workcontext_type <= FIPS_SERVICE_AES_CFB128_FINAL))
				|| (workcontext_type == FIPS_SERVICE_IMPORT_KEY)
				|| (workcontext_type == FIPS_SERVICE_EXPORT_KEY)
				|| (workcontext_type == FIPS_SERVICE_MAC_GEN_INIT)
				|| (workcontext_type == FIPS_SERVICE_MAC_VERIFY_INIT)) {
			aeskey->key = tmp_destination + sizeof(aeskey->key);
		}
		tmp_destination += PTR_SIZE;
		memcpy(tmp_destination, tmp_source, aeskeys->size);
		if (((workcontext_type >= FIPS_SERVICE_AES_ECB)
				&& (workcontext_type <= FIPS_SERVICE_AES_CFB128_FINAL))
				|| (workcontext_type == FIPS_SERVICE_IMPORT_KEY)
				|| (workcontext_type == FIPS_SERVICE_EXPORT_KEY)
				|| (workcontext_type == FIPS_SERVICE_MAC_GEN_INIT)
				|| (workcontext_type == FIPS_SERVICE_MAC_VERIFY_INIT)) {
			aeskey_work->keyvalue = (uint8_t *) tmp_destination;
		}
		break;
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
		;
		mackey_work_struct *mackey_work;
		if ((workcontext_type >= FIPS_SERVICE_MAC_GEN_INIT)
				&& (workcontext_type <= FIPS_SERVICE_MAC_UPDATE)) {
			mackey_work = (mackey_work_struct *) workcontext_struct;
			mackey_work->asset = (fips_asset *) (tmp_destination - len);
			asset->asset_data = tmp_destination + sizeof(asset->asset_data);
		}
		tmp_destination += PTR_SIZE;
		fips_hmac_key *hmackey;
		fips_hmac_key *hmackeys;
		hmackey = (fips_hmac_key *) tmp_destination;
		hmackeys = (fips_hmac_key *) tmp_source;
		if ((workcontext_type >= FIPS_SERVICE_MAC_GEN_INIT)
				&& (workcontext_type <= FIPS_SERVICE_MAC_UPDATE)) {
			mackey_work->key = (fips_hmac_key *) tmp_destination;
		}
		len = sizeof(fips_hmac_key) - PTR_SIZE;
		memcpy(tmp_destination, tmp_source, len);
		tmp_destination += len;
		tmp_source += len;
		if ((workcontext_type >= FIPS_SERVICE_MAC_GEN_INIT)
				&& (workcontext_type <= FIPS_SERVICE_MAC_UPDATE)) {
			hmackey->key = tmp_destination + sizeof(hmackey->key);
		}
		tmp_destination += PTR_SIZE;
		memcpy(tmp_destination, tmp_source, hmackeys->size);
		if ((workcontext_type >= FIPS_SERVICE_MAC_GEN_INIT)
				&& (workcontext_type <= FIPS_SERVICE_MAC_UPDATE)) {
			mackey_work->keyvalue = (uint8_t *) tmp_destination;
		}
		break;
	default:
		printk("No valid data in buffer\n");
		status = -EINVAL;
	}

out:
	return status;
}

uint8_t asset_overhead[FIPS_TYPE_NUM] = {0,
					 4, /* FIPS_TYPE_AES */
					 4, /* FIPS_TYPE_HMAC_SHA224 */
					 4, /* FIPS_TYPE_HMAC_SHA256 */
					 4, /* FIPS_TYPE_HMAC_SHA384 */
					 4, /* FIPS_TYPE_HMAC_SHA512 */
					 8, /* FIPS_TYPE_RSA_PUBLIC_KEY */
					 8, /* FIPS_TYPE_RSA_KEYPAIR */
					 8, /* FIPS_TYPE_RSA_PF_KEYPAIR */
					 8, /* FIPS_TYPE_RSA_CRT_KEYPAIR */
					 4, /* FIPS_TYPE_ECDSA_PUBLIC_KEY */
					 4, /* FIPS_TYPE_ECDSA_KEYPAIR */
					 4, /* FIPS_TYPE_ECDH_PUBLIC_KEY */
					 4, /* FIPS_TYPE_ECDH_KEYPAIR */
					 4, /* FIPS_TYPE_SHARED_SECRET */
					 4, /* FIPS_TYPE_AES_GCM_ENCRYPT */
					 4, /* FIPS_TYPE_AES_GCM_DECRYPT */
					 4, /* FIPS_TYPE_WRAP_KEY */
					 4, /* FIPS_TYPE_SECRET */
					 4, /* FIPS_TYPE_HMAC_SHA3_224 */
					 4, /* FIPS_TYPE_HMAC_SHA3_256 */
					 4, /* FIPS_TYPE_HMAC_SHA3_384 */
					 4, /* FIPS_TYPE_HMAC_SHA3_512 */
					 4, /* FIPS_TYPE_DILITHIUM_PUBLIC_KEY */
					 4, /* FIPS_TYPE_DILITHIUM_KEYPAIR */
					 4, /* FIPS_TYPE_KYBER_ENCAP_KEY */
					 4  /* FIPS_TYPE_KYBER_KEYPAIR */
					};
