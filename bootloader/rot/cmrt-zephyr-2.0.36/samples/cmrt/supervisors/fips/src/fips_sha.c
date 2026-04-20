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
#include <cri/cmrt/hc.h>
#include <cri/cmrt.h>

#include <tee_client_api.h>
#include <tee_client_abi.h>

#include <cri/cmrt/fips/fips_types.h>

#include "teec_cmvp.h"
#include "teefs_cmvp.h"
#include "fips_asset.h"
#include "fips.h"
#include "cmvp_sw.h"
#include "cri_utils.h"

static int32_t aes_cmac_update_int(aes_work_struct *aes,
		uint8_t *data, uint32_t length)
{
	int32_t status = 0;

	uint8_t *input = data;

	if ((length & 0x0F) != 0) {
		status = -EINVAL;
		goto err;
	}

	for (int i = length; i >= AES_BLOCK_BYTES; i -= AES_BLOCK_BYTES) {
		printk("multiple updates(%u)...\n", i);
		status = cri_aes_update_aad(aes->aesengine, input, AES_BLOCK_BYTES);
		input += AES_BLOCK_BYTES;
		if (status != 0) {
			goto err;
		}
	}

err:
	return status;
}

static int32_t aes_cmac_init_int(aes_work_struct *aes,
		uint8_t *datain, uint32_t size,
		void *key, size_t keylen)
{
	int32_t status = 0;

	aes->aesengine = CRI_INVALID_HANDLE;
	aes->aesengine = cri_aes_open(0);

	if (!cri_is_valid(aes->aesengine)) {
		dprintk("Cannot open AES\n");
		status = -ENOENT;
		goto out1;
	}

	status = cri_aes_init(aes->aesengine, AES_ENCRYPT, AES_CMAC, key, keylen, NULL, 0, 16);
	if (status != 0) {
		dprintk("Cannot init aes - %d\n", status);
		status = -EIO;
		goto out1;
	}

	status = aes_cmac_update_int(aes, datain, size);

	goto out;
out1:
	destroy_workcontext(status);
out:
	return status;
}

static int32_t aes_cmac_final_int(aes_work_struct *aes,
		uint8_t *datain, uint32_t size,
		uint8_t *dest, uint32_t dest_size)
{
	int32_t status = 0;
	int32_t i;

	uint8_t *input = datain;
	uint8_t mac[16];

	uint32_t taglen = 16;

	if (dest_size < aes->taglen) {
		dprintk("Output buffer too small: %d < %d\n", dest_size, aes->taglen);
		status = -EINVAL;
		goto out;
	}

	for (i = size; i > AES_BLOCK_BYTES; i -= AES_BLOCK_BYTES) {
		printk("multiple updates(%u)...\n", i);
		status = cri_aes_update_aad(aes->aesengine, input, AES_BLOCK_BYTES);
		input += AES_BLOCK_BYTES;
		if (status != 0) {
			goto out;
		}
	}

	if (i > 0) {
		printk("last update(%u)...\n", i);
		status = cri_aes_final_aad(aes->aesengine, input, i);
		printk("aad = %d\n", status);
		if (status != 0) {
			goto out;
		}
	}

	if (i >= 0) {
		printk("cri_aes_ae_final(0)...\n");
		status = cri_aes_ae_final(aes->aesengine, NULL, 0, NULL, mac, &taglen);
		printk("final(%u) = %d, taglen = %u\n", i, status, taglen);
		if (status != 0) {
			goto out;
		}
	}

	memcpy(dest, mac, aes->taglen);
out:
	cri_aes_close(aes->aesengine);
	return status;
}

/* mac_work_struct (mackey_work_struct + hash_work_struct ) || asset || key_struct || value */
static int32_t hash_update_int(hash_work_struct *sha, uint8_t *data, uint32_t length)
{
	u32_t offs = 0;
	u32_t len = length;
	int32_t status = 0;

	while (len && sha->buffer_offset + len >= SHA_BUF_MAX_SIZE) {
		u32_t copy = SHA_BUF_MAX_SIZE - sha->buffer_offset;

		memcpy(sha->hash_buffer + sha->buffer_offset, data + offs, copy);
		offs += copy;
		len -= copy;

		status = cri_hc_update(sha->hashengine, sha->hash_buffer,
		SHA_BUF_MAX_SIZE);
		if (status != 0) {
			dprintk("Cannot update hash\n");
			goto out;
		}
		sha->buffer_offset = 0;
	}

	if (len) {
		memcpy(sha->hash_buffer + sha->buffer_offset, data + offs, len);
		sha->buffer_offset += len;
	}

out:
	return status;
}

static int32_t hash_init_int(hash_work_struct *sha,
		uint8_t *datain, uint32_t size,
		void *key, size_t keylen, const fips_hc_id hc_id)
{
	int32_t status = 0;
	uint32_t hashtype;

	sha->hashengine = CRI_INVALID_HANDLE;
	if (hc_id == FIPS_HC_1) {
		sha->hashengine = cri_hc_open(0);
	} else if (hc_id == FIPS_HC_2) {
#ifdef CONFIG_CMRT_HC2
		sha->hashengine = cri_hc2_open(0);
#endif
	}
	if (!cri_is_valid(sha->hashengine)) {
		dprintk("Cannot open HC%u!\n", hc_id);
		status = -ENOENT;
		goto out1;
	}

	switch (sha->hashtype) {
	case FIPS_HASH_SHA224:
		hashtype = HC_HASH_ALGO_SHA_224;
		break;
	case FIPS_HASH_SHA256:
		hashtype = HC_HASH_ALGO_SHA_256;
		break;
	case FIPS_HASH_SHA384:
		hashtype = HC_HASH_ALGO_SHA_384;
		break;
	case FIPS_HASH_SHA512:
		hashtype = HC_HASH_ALGO_SHA_512;
		break;
	case FIPS_HASH_SHA512_224:
		hashtype = HC_HASH_ALGO_SHA_512_224;
		break;
	case FIPS_HASH_SHA512_256:
		hashtype = HC_HASH_ALGO_SHA_512_256;
		break;
#if (defined CONFIG_CMRT_S3HC || defined CONFIG_CMRT_S3HC2)
	case FIPS_HASH_SHA3_224:
		hashtype = HC_HASH_ALGO_SHA3_224;
		break;
	case FIPS_HASH_SHA3_256:
		hashtype = HC_HASH_ALGO_SHA3_256;
		break;
	case FIPS_HASH_SHA3_384:
		hashtype = HC_HASH_ALGO_SHA3_384;
		break;
	case FIPS_HASH_SHA3_512:
		hashtype = HC_HASH_ALGO_SHA3_512;
		break;
#endif
	default:
		status = -EINVAL;
		goto out1;
	}

	status = cri_hc_init(sha->hashengine, hashtype, key, keylen);
	if (status != 0) {
		dprintk("Cannot init hash %08X - %d\n", status, status);
		status = -EIO;
		goto out1;
	}

	memset(sha->hash_buffer, 0, sizeof(sha->hash_buffer));
	sha->buffer_offset = 0;

	status = hash_update_int(sha, datain, size);
	if (status != 0) {
		goto out1;
	}

	goto out;
out1:
	destroy_workcontext(status);
out:
	return status;
}

static int32_t hash_final_int(hash_work_struct *sha,
		uint8_t *datain, uint32_t size,
		uint8_t *dest, uint32_t dest_size)
{
	int32_t status = 0;

	if (dest_size < sha->hashlen) {
		dprintk("The output buffer in the shared memory is not large enough for the requested digest\n");
		status = -EINVAL;
		goto out;
	}

	status = hash_update_int(sha, datain, size);
	if (status) {
		goto out;
	}

	uint8_t *data;
	uint32_t len;

	len = 0;
	data = NULL;

	if (sha->buffer_offset) {
		status = cri_hc_update(sha->hashengine, sha->hash_buffer, sha->buffer_offset & ~3);
		if (status) {
			status = -EIO;
			goto out;
		}
		data = sha->hash_buffer + (sha->buffer_offset & ~3);
		len = sha->buffer_offset & 3;
	}

	status = cri_hc_final(sha->hashengine, data, len, dest, &(sha->hashlen));
	dprintk("Hash length: %d\n", sha->hashlen);
	if (status) {
		dprintk("Cannot final hash\n");
	}

	cri_hc_close(sha->hashengine);

out:
	return status;
}

int32_t cri_hash(hash_work_struct *sha, uint8_t *in_dataarray, size_t inlen,
		 uint8_t *out_hash, size_t outlen, const fips_hc_id hc_id)
{
	int32_t status;

	status = hash_init_int(sha, in_dataarray, inlen, NULL, 0, hc_id);
	if (status) {
		dprintk("status: %d\n", status);
		goto direct_exit;
	}
	status = hash_final_int(sha, NULL, 0, out_hash, outlen);
	if (status) {
		dprintk("status: %d\n", status);
		goto direct_exit;
	}

direct_exit:
	return status;
}

int32_t cri_mac_gen(hash_work_struct *sha, uint8_t *in_dataarray, size_t inlen, uint8_t *key, size_t keylen, uint8_t *out_hash, size_t outlen)
{
	int32_t status;

	status = hash_init_int(sha, in_dataarray, inlen, key, keylen, FIPS_HC_1);
	if (status) {
		dprintk("status: %d\n", status);
		goto direct_exit;
	}
	status = hash_final_int(sha, NULL, 0, out_hash, outlen);
	if (status) {
		dprintk("status: %d\n", status);
		goto direct_exit;
	}

direct_exit:
	return status;
}

int32_t fips_hash_init(fips_state_t *state, teec_abi_invokecommand_t *h)
{
	int status = 0;

	hash_work_struct *sha = NULL;

	dprintk("FIPS_SERVICE_HASH_INIT\n");
	CHECK_COMMAND(FIPS_SERVICE_HASH_INIT);

	sha = (hash_work_struct *) (workcontext + sizeof(uint32_t));

	/* check validity of core id , asset location type , zero param value,
	 * IV size correctness and size fips asset */
	if ((h->params[0].value.b != FIPS_HC_1)
#ifdef CONFIG_CMRT_HC2
	    && (h->params[0].value.b != FIPS_HC_2)
#endif
	    ) {
		status = -EINVAL;
		goto out1;
	}

	switch (h->params[0].value.a) {
	case FIPS_HASH_SHA224:
		sha->hashlen = 28;
		break;
	case FIPS_HASH_SHA256:
		sha->hashlen = 32;
		break;
	case FIPS_HASH_SHA384:
		sha->hashlen = 48;
		break;
	case FIPS_HASH_SHA512:
		sha->hashlen = 64;
		break;
	case FIPS_HASH_SHA512_224:
		sha->hashlen = 28;
		break;
	case FIPS_HASH_SHA512_256:
		sha->hashlen = 32;
		break;
#if (defined CONFIG_CMRT_S3HC || defined CONFIG_CMRT_S3HC2)
	case FIPS_HASH_SHA3_224:
		sha->hashlen = 28;
		break;
	case FIPS_HASH_SHA3_256:
		sha->hashlen = 32;
		break;
	case FIPS_HASH_SHA3_384:
		sha->hashlen = 48;
		break;
	case FIPS_HASH_SHA3_512:
		sha->hashlen = 64;
		break;
#endif
	default:
		status = -EINVAL;
		goto out1;
	}
	dprintk("Hashlen:%d\n", sha->hashlen);

	sha->hashtype = h->params[0].value.a;

	status = hash_init_int(sha, (uint8_t *) (h->params[1].memref.offset + SAC_MEMORY_BASE),
			h->params[1].memref.size, NULL, 0, h->params[0].value.b);
	if (status) {
		goto out1;
	}

	goto out;
out1:
	destroy_workcontext(status);
out:
	return status;
}

int32_t fips_hash_update(fips_state_t *state, teec_abi_invokecommand_t *h)
{
	int status = 0;

	hash_work_struct *sha = NULL;

	dprintk("FIPS_SERVICE_HASH_UPDATE\n");

	if ((((uint32_t *) workcontext)[0] != FIPS_SERVICE_HASH_INIT) &&
		(((uint32_t *) workcontext)[0] != FIPS_SERVICE_HASH_UPDATE)) {
		dprintk("Previous command was not FIPS_SERVICE_HASH_INIT or FIPS_SERVICE_HASH_UPDATE: %d\n",
				(uint32_t) workcontext[0]);
		status = -EPERM;
		goto out1;
	}

	((uint32_t *) workcontext)[0] = FIPS_SERVICE_HASH_UPDATE;

	sha = (hash_work_struct *) (workcontext + sizeof(uint32_t));

	status = hash_update_int(sha, (uint8_t *) (h->params[0].memref.offset + SAC_MEMORY_BASE),
			h->params[0].memref.size);
	if (status) {
		goto out1;
	}

	goto out;
out1:
	destroy_workcontext(status);
out:
	return status;
}

int32_t fips_hash_final(fips_state_t *state, teec_abi_invokecommand_t *h)
{
	int32_t status = 0;

	hash_work_struct *sha = NULL;

	dprintk("FIPS_SERVICE_SHA_FINAL\n");

	if ((((uint32_t *) workcontext)[0] != FIPS_SERVICE_HASH_INIT) &&
		(((uint32_t *) workcontext)[0] != FIPS_SERVICE_HASH_UPDATE)) {
		dprintk("Previous command was not FIPS_SERVICE_HASH_INIT or FIPS_SERVICE_HASH_UPDATE: %d\n",
				(uint32_t) workcontext[0]);
		status = -EPERM;
		goto out;
	}

	((uint32_t *) workcontext)[0] = FIPS_SERVICE_HASH_FINAL;

	sha = (hash_work_struct *) (workcontext + sizeof(uint32_t));

	status = hash_final_int(sha, (uint8_t *) (h->params[0].memref.offset + SAC_MEMORY_BASE),
			h->params[0].memref.size,
			(uint8_t *) (h->params[1].memref.offset + SAC_MEMORY_BASE),
			h->params[1].memref.size);

out:
	destroy_workcontext(status);
	return status;
}

int32_t fips_mac_gen_init(fips_state_t *state, teec_abi_invokecommand_t *h)
{
	int status = 0;

	mac_work_struct *mac = NULL;
	hash_work_struct *sha = NULL;
	aes_work_struct *aes = NULL;
	fips_asset_identifier *asset = NULL;
	fips_asset *mackeyasset = NULL;
	teefs_command_t cmd;
	mackey_work_struct *mackey_work = NULL;
	aeskey_work_struct *aeskey_work = NULL;
	fips_hmac_key *hmac_key = NULL;
	fips_aes_key *cmac_key = NULL;
	uint8_t *keyval = NULL;

	dprintk("FIPS_SERVICE_MAC_GEN_INIT\n");
	CHECK_COMMAND(FIPS_SERVICE_MAC_GEN_INIT);

	mac = (mac_work_struct *) (workcontext + sizeof(uint32_t));

	/* check asset location type , zero param value, IV size correctness and size fips asset */
	if ((h->params[0].value.b != FIPS_HC_1) && (h->params[0].value.b != FIPS_HC_NONE)
#ifdef CONFIG_CMRT_HC2
	    && (h->params[0].value.b != FIPS_HC_2)
#endif
	    ) {
		status = -EINVAL;
		goto out1;
	}

	if (h->params[1].memref.size != sizeof(fips_asset_identifier)) {
		status = -EINVAL;
		goto out1;
	}

	asset = (fips_asset_identifier *) (h->params[1].memref.offset + SAC_MEMORY_BASE);
	dprintk("MAC key asset name length %d\n", asset->asset_name_length);
	dprintk("MAC key asset name %s\n", asset->asset_name);
	if (asset->location == FIPS_ASSET_DYNAMIC) {
		cmd = READ_FILE_RAM;
	} else if (asset->location == FIPS_ASSET_STATIC) {
		cmd = READ_FILE_OTP;
	} else {
		status = -EINVAL;
		goto out;
	}

	status = process_teefs_request(cmd, asset->asset_name_length,
			asset->asset_name, g_inout_buffer, &g_inout_buffer_len);
	if (status) {
		dprintk("Asset read status: %d\n", status);
		goto out;
	}

	status = buffer_to_fips_asset((uint8_t *) g_inout_buffer, &g_inout_buffer_len,
			workcontext + sizeof(uint32_t) + sizeof(mac_work_struct), workcontext);
	if (status) {
		dprintk("Buffer to fips asset status: %d\n", status);
		goto out;
	}

	if (h->params[0].value.b == FIPS_HC_NONE) {
		if (h->params[0].value.a != FIPS_HASH_NONE) {
			status = -EPERM;
			goto out1;
		}

		aeskey_work = (aeskey_work_struct *) mac;
		keyval = (uint8_t *) aeskey_work->keyvalue;
		mackeyasset = (fips_asset *) aeskey_work->asset;
		cmac_key = (fips_aes_key *) aeskey_work->key;
		aes = &(mac->aes);
	} else {
		mackey_work = (mackey_work_struct *) mac;
		keyval = (uint8_t *) mackey_work->keyvalue;
		mackeyasset = (fips_asset *) mackey_work->asset;
		hmac_key = (fips_hmac_key *) mackey_work->key;
		sha = &(mac->sha);
	}

	uint32_t assettype = GET_ASSET_TYPE(mackeyasset->metadata);
	dprintk("FIPS TYPE = %d\n", assettype);

	if (fips_get_asset_permissions(state->user,
			GET_ASSET_OWNER(mackeyasset->metadata)) == 0) {
		dprintk("The currently logged in user cannot use the asset just opened\n");
		status = -EACCES;
		goto out1;
	}

	if (h->params[0].value.b == FIPS_HC_NONE) {
		if (assettype != FIPS_TYPE_AES) {
			status = -EPERM;
			goto out1;
		}

		if (!fips_is_valid_tag_length(h->params[3].value.a) ||
				(h->params[3].value.b != 0)) {
			dprintk("Incorrect tag length: %d\n", h->params[3].value.a);
			status = -EINVAL;
			goto out1;
		}
		aes->taglen = h->params[3].value.a;

		/* For debug */
		dprintk("FIPS AES CMAC: key of size %d taglen: %d\n", cmac_key->size, aes->taglen);
		dhexdump("CMAC key value", keyval, cmac_key->size);

		status = aes_cmac_init_int(aes, (uint8_t *) (h->params[2].memref.offset + SAC_MEMORY_BASE),
				h->params[2].memref.size, keyval, cmac_key->size);
		if (status) {
			goto out1;
		}
	} else {
		if ((h->params[3].value.a != 0) || (h->params[3].value.b != 0)) {
			status = -EINVAL;
			goto out1;
		}

		switch (h->params[0].value.a) {
		case FIPS_HASH_SHA224:
			if (assettype != FIPS_TYPE_HMAC_SHA224) {
				status = -EPERM;
				goto out1;
			}
			sha->hashlen = 28;
			break;
		case FIPS_HASH_SHA256:
			if (assettype != FIPS_TYPE_HMAC_SHA256) {
				status = -EPERM;
				goto out1;
			}
			sha->hashlen = 32;
			break;
		case FIPS_HASH_SHA384:
			if (assettype != FIPS_TYPE_HMAC_SHA384) {
				status = -EPERM;
				goto out1;
			}
			sha->hashlen = 48;
			break;
		case FIPS_HASH_SHA512:
			if (assettype != FIPS_TYPE_HMAC_SHA512) {
				status = -EPERM;
				goto out1;
			}
			sha->hashlen = 64;
			break;
		case FIPS_HASH_SHA512_224:
			if (assettype != FIPS_TYPE_HMAC_SHA512) {
				status = -EPERM;
				goto out1;
			}
			sha->hashlen = 28;
			break;
		case FIPS_HASH_SHA512_256:
			if (assettype != FIPS_TYPE_HMAC_SHA512) {
				status = -EPERM;
				goto out1;
			}
			sha->hashlen = 32;
			break;
#if (defined CONFIG_CMRT_S3HC || defined CONFIG_CMRT_S3HC2)
		case FIPS_HASH_SHA3_224:
			if (assettype != FIPS_TYPE_HMAC_SHA3_224) {
				status = -EPERM;
				goto out1;
			}
			sha->hashlen = 28;
			break;
		case FIPS_HASH_SHA3_256:
			if (assettype != FIPS_TYPE_HMAC_SHA3_256) {
				status = -EPERM;
				goto out1;
			}
			sha->hashlen = 32;
			break;
		case FIPS_HASH_SHA3_384:
			if (assettype != FIPS_TYPE_HMAC_SHA3_384) {
				status = -EPERM;
				goto out1;
			}
			sha->hashlen = 48;
			break;
		case FIPS_HASH_SHA3_512:
			if (assettype != FIPS_TYPE_HMAC_SHA3_512) {
				status = -EPERM;
				goto out1;
			}
			sha->hashlen = 64;
			break;
#endif
		default:
			dprintk("Hash identifier is not valid %d\n", h->params[0].value.a);
			status = -EPERM;
			goto out1;
		}

		sha->hashtype = h->params[0].value.a;

		/* For debug */
		dprintk("FIPS SHA: HMAC key of size %d read\n:", hmac_key->size);
		dhexdump("HMAC key value", keyval, hmac_key->size);

		status = hash_init_int(sha, (uint8_t *) (h->params[2].memref.offset + SAC_MEMORY_BASE),
				h->params[2].memref.size, keyval, hmac_key->size, h->params[0].value.b);
		if (status) {
			goto out1;
		}
	}

	goto out;
out1:
	destroy_workcontext(status);
out:
	return status;
}

int32_t fips_mac_update(fips_state_t *state, teec_abi_invokecommand_t *h)
{
	int status = 0;

	mac_work_struct *mac = NULL;
	hash_work_struct *sha = NULL;
	aes_work_struct *aes = NULL;

	dprintk("FIPS_SERVICE_MAC_UPDATE\n");

	if ((((uint32_t *) workcontext)[0] != FIPS_SERVICE_MAC_GEN_INIT) &&
		(((uint32_t *) workcontext)[0] != FIPS_SERVICE_MAC_UPDATE) &&
		(((uint32_t *) workcontext)[0] != FIPS_SERVICE_MAC_VERIFY_INIT)) {
		dprintk("Previous command was not FIPS_SERVICE_MAC_GEN/VERIFY_INIT or FIPS_SERVICE_MAC_UPDATE: %d\n",
				((uint32_t *) workcontext)[0]);
		status = -EPERM;
		goto out1;
	}

	((uint32_t *) workcontext)[0] = FIPS_SERVICE_MAC_UPDATE;

	mac = (mac_work_struct *) (workcontext + sizeof(uint32_t));
	sha = &(mac->sha);
	aes = &(mac->aes);

	if (cri_is_valid(aes->aesengine)) {
		status = aes_cmac_update_int(aes, (uint8_t *) (h->params[0].memref.offset + SAC_MEMORY_BASE),
						h->params[0].memref.size);
	} else if (cri_is_valid(sha->hashengine)) {
		status = hash_update_int(sha, (uint8_t *) (h->params[0].memref.offset + SAC_MEMORY_BASE),
						h->params[0].memref.size);
	} else {
		status = -EIO;
	}
	if (status) {
		goto out1;
	}

	goto out;
out1:
	destroy_workcontext(status);
out:
	return status;
}

int32_t fips_mac_gen_final(fips_state_t *state, teec_abi_invokecommand_t *h)
{
	int32_t status = -EIO;

	mac_work_struct *mac = NULL;
	hash_work_struct *sha = NULL;
	aes_work_struct *aes = NULL;

	dprintk("FIPS_SERVICE_MAC_GEN_FINAL\n");

	if ((((uint32_t *) workcontext)[0] != FIPS_SERVICE_MAC_GEN_INIT) &&
		(((uint32_t *) workcontext)[0] != FIPS_SERVICE_MAC_UPDATE)) {
		dprintk("Previous command was not FIPS_SERVICE_MAC_GEN_INIT or FIPS_SERVICE_MAC_UPDATE: %d\n",
				(uint32_t) workcontext[0]);
		status = -EPERM;
		goto out1;
	}

	((uint32_t *) workcontext)[0] = (uint32_t) FIPS_SERVICE_MAC_GEN_FINAL;

	mac = (mac_work_struct *) (workcontext + sizeof(uint32_t));
	sha = &(mac->sha);
	aes = &(mac->aes);

	if (cri_is_valid(aes->aesengine)) {
		status = aes_cmac_final_int(aes, (uint8_t *) (h->params[0].memref.offset + SAC_MEMORY_BASE),
				h->params[0].memref.size,
				(uint8_t *) (h->params[1].memref.offset + SAC_MEMORY_BASE),
				h->params[1].memref.size);
	} else if (cri_is_valid(sha->hashengine)) {
		status = hash_final_int(sha, (uint8_t *) (h->params[0].memref.offset + SAC_MEMORY_BASE),
				h->params[0].memref.size,
				(uint8_t *) (h->params[1].memref.offset + SAC_MEMORY_BASE),
				h->params[1].memref.size);
	} else {
		status = -EIO;
	}

out1:
	destroy_workcontext(status);
	return status;
}

int32_t fips_mac_ver_init(fips_state_t *state, teec_abi_invokecommand_t *h)
{
	int status = 0;

	mac_work_struct *mac = NULL;
	hash_work_struct *sha = NULL;
	aes_work_struct *aes = NULL;
	fips_asset_identifier *asset = NULL;
	fips_asset *mackeyasset = NULL;
	teefs_command_t cmd;
	mackey_work_struct *mackey_work = NULL;
	aeskey_work_struct *aeskey_work = NULL;
	fips_hmac_key *hmac_key = NULL;
	fips_aes_key *cmac_key = NULL;
	uint8_t *keyval = NULL;

	dprintk("FIPS_SERVICE_MAC_VERIFY_INIT\n");
	CHECK_COMMAND(FIPS_SERVICE_MAC_VERIFY_INIT);

	mac = (mac_work_struct *) (workcontext + sizeof(uint32_t));

	/* check asset location type , zero param value, IV size correctness and size fips asset */
	if ((h->params[0].value.b != FIPS_HC_1) && (h->params[0].value.b != FIPS_HC_NONE)
#ifdef CONFIG_CMRT_HC2
	    && (h->params[0].value.b != FIPS_HC_2)
#endif
	    ) {
		status = -EINVAL;
		goto out1;
	}

	if (h->params[1].memref.size != sizeof(fips_asset_identifier)) {
		status = -EINVAL;
		goto out1;
	}

	asset = (fips_asset_identifier *) (h->params[1].memref.offset + SAC_MEMORY_BASE);
	dprintk("MAC key asset name length %d\n", asset->asset_name_length);
	dprintk("MAC key asset name %s\n", asset->asset_name);
	if (asset->location == FIPS_ASSET_DYNAMIC) {
		cmd = READ_FILE_RAM;
	} else if (asset->location == FIPS_ASSET_STATIC) {
		cmd = READ_FILE_OTP;
	} else {
		status = -EINVAL;
		goto out;
	}

	status = process_teefs_request(cmd, asset->asset_name_length,
			asset->asset_name, g_inout_buffer, &g_inout_buffer_len);
	if (status) {
		dprintk("Asset read status: %d\n", status);
		goto out;
	}

	status = buffer_to_fips_asset((uint8_t *) g_inout_buffer, &g_inout_buffer_len,
			workcontext + sizeof(uint32_t) + sizeof(mac_work_struct), workcontext);
	if (status) {
		dprintk("Buffer to fips asset status: %d\n", status);
		goto out1;
	}

	if (h->params[0].value.b == FIPS_HC_NONE) {
		if (h->params[0].value.a != FIPS_HASH_NONE) {
			status = -EPERM;
			goto out1;
		}

		aeskey_work = (aeskey_work_struct *) mac;
		keyval = (uint8_t *) aeskey_work->keyvalue;
		mackeyasset = (fips_asset *) aeskey_work->asset;
		cmac_key = (fips_aes_key *) aeskey_work->key;
		aes = &(mac->aes);
	} else {
		mackey_work = (mackey_work_struct *) mac;
		keyval = (uint8_t *) mackey_work->keyvalue;
		mackeyasset = (fips_asset *) mackey_work->asset;
		hmac_key = (fips_hmac_key *) mackey_work->key;
		sha = &(mac->sha);
	}

	uint32_t assettype = GET_ASSET_TYPE(mackeyasset->metadata);
	dprintk("FIPS TYPE = %d\n", assettype);

	if (fips_get_asset_permissions(state->user,
			GET_ASSET_OWNER(mackeyasset->metadata)) == 0) {
		dprintk("The currently logged in user cannot use the asset just opened\n");
		status = -EACCES;
		goto out1;
	}

	if (h->params[0].value.b == FIPS_HC_NONE) {
		if (assettype != FIPS_TYPE_AES) {
			status = -EPERM;
			goto out1;
		}

		if (!fips_is_valid_tag_length(h->params[2].memref.size)) {
			dprintk("Incorrect tag length: %d\n", h->params[2].memref.size);
			status = -EINVAL;
			goto out1;
		}
		aes->taglen = h->params[2].memref.size;
		/* For debug */
		dprintk("FIPS AES CMAC: key of size %d taglen: %d\n", cmac_key->size, aes->taglen);
		dhexdump("CMAC key value", keyval, cmac_key->size);
		dprintk("memory %p, size %d\n", (uint8_t *) (h->params[3].memref.offset + SAC_MEMORY_BASE),
				h->params[3].memref.size);

		status = aes_cmac_init_int(aes, (uint8_t *) (h->params[3].memref.offset + SAC_MEMORY_BASE),
				h->params[3].memref.size, keyval, cmac_key->size);
		if (status) {
			goto out1;
		}

		/* cache the digest */
		memcpy((uint8_t *) (keyval + cmac_key->size), (uint8_t *) (h->params[2].memref.offset + SAC_MEMORY_BASE),
						h->params[2].memref.size);
	} else {
		switch (h->params[0].value.a) {
		case FIPS_HASH_SHA224:
			if (assettype != FIPS_TYPE_HMAC_SHA224) {
				dprintk("Wrong assettype\n");
				status = -EPERM;
				goto out1;
			}
			sha->hashlen = 28;
			break;
		case FIPS_HASH_SHA256:
			if (assettype != FIPS_TYPE_HMAC_SHA256) {
				status = -EPERM;
				dprintk("Wrong assettype\n");
				goto out1;
			}
			sha->hashlen = 32;
			break;
		case FIPS_HASH_SHA384:
			if (assettype != FIPS_TYPE_HMAC_SHA384) {
				status = -EPERM;
				dprintk("Wrong assettype\n");
				goto out1;
			}
			sha->hashlen = 48;
			break;
		case FIPS_HASH_SHA512:
			if (assettype != FIPS_TYPE_HMAC_SHA512) {
				status = -EPERM;
				dprintk("Wrong assettype\n");
				goto out1;
			}
			sha->hashlen = 64;
			break;
		case FIPS_HASH_SHA512_224:
			if (assettype != FIPS_TYPE_HMAC_SHA512) {
				dprintk("Wrong assettype\n");
				status = -EPERM;
				goto out1;
			}
			sha->hashlen = 28;
			break;
		case FIPS_HASH_SHA512_256:
			if (assettype != FIPS_TYPE_HMAC_SHA512) {
				dprintk("Wrong assettype\n");
				status = -EPERM;
				goto out1;
			}
			sha->hashlen = 32;
			break;
#if (defined CONFIG_CMRT_S3HC || defined CONFIG_CMRT_S3HC2)
		case FIPS_HASH_SHA3_224:
			if (assettype != FIPS_TYPE_HMAC_SHA3_224) {
				dprintk("Wrong assettype\n");
				status = -EPERM;
				goto out1;
			}
			sha->hashlen = 28;
			break;
		case FIPS_HASH_SHA3_256:
			if (assettype != FIPS_TYPE_HMAC_SHA3_256) {
				status = -EPERM;
				dprintk("Wrong assettype\n");
				goto out1;
			}
			sha->hashlen = 32;
			break;
		case FIPS_HASH_SHA3_384:
			if (assettype != FIPS_TYPE_HMAC_SHA3_384) {
				status = -EPERM;
				dprintk("Wrong assettype\n");
				goto out1;
			}
			sha->hashlen = 48;
			break;
		case FIPS_HASH_SHA3_512:
			if (assettype != FIPS_TYPE_HMAC_SHA3_512) {
				status = -EPERM;
				dprintk("Wrong assettype\n");
				goto out1;
			}
			sha->hashlen = 64;
			break;
#endif
		default:
			dprintk("Hash identifier is not valid %d\n", h->params[0].value.a);
			status = -EPERM;
			goto out1;
		}

		sha->hashtype = h->params[0].value.a;

		/* For debug */
		dprintk("HMAC key of size %d read\n:", hmac_key->size);
		dhexdump("HMAC key value", keyval, hmac_key->size);

		status = hash_init_int(&(mac->sha), (uint8_t *) (h->params[3].memref.offset + SAC_MEMORY_BASE),
				h->params[3].memref.size, keyval, hmac_key->size, h->params[0].value.b);
		if (status) {
			goto out1;
		}

		/* cache the digest */
		if (h->params[2].memref.size != sha->hashlen) {
			dprintk("The provided digest length %d does not match the digest len of the requested asset %d\n",
					h->params[2].memref.size, sha->hashlen);
			status = -EINVAL;
			goto out1;
		}
		memcpy((uint8_t *) (keyval + hmac_key->size), (uint8_t *) (h->params[2].memref.offset + SAC_MEMORY_BASE),
				h->params[2].memref.size);
	}

	goto out;
out1:
	destroy_workcontext(status);
out:
	return status;
}

int32_t fips_mac_ver_final(fips_state_t *state, teec_abi_invokecommand_t *h)
{
	int32_t status = -EIO;

	mac_work_struct *mac = NULL;
	hash_work_struct *sha = NULL;
	aes_work_struct *aes = NULL;
	mackey_work_struct *mackey_work = NULL;
	aeskey_work_struct *aeskey_work = NULL;
	fips_hmac_key *hmac_key = NULL;
	fips_aes_key *cmac_key = NULL;
	uint8_t *keyval = NULL;
	uint8_t *cashed_digest = NULL;
	uint32_t digest_length;
	int errs = 0;

	dprintk("FIPS_SERVICE_MAC_VERIFY_FINAL\n");

	if ((((uint32_t *) workcontext)[0] != FIPS_SERVICE_MAC_VERIFY_INIT) &&
		(((uint32_t *) workcontext)[0] != FIPS_SERVICE_MAC_UPDATE)) {
		dprintk("Previous command was not FIPS_SERVICE_MAC_VERIFY_INIT or FIPS_SERVICE_MAC_UPDATE: %d\n",
				(uint32_t) workcontext[0]);
		status = -EPERM;
		goto out1;
	}

	((uint32_t *) workcontext)[0] = FIPS_SERVICE_MAC_VERIFY_FINAL;

	mac = (mac_work_struct *) (workcontext + sizeof(uint32_t));
	sha = &(mac->sha);
	aes = &(mac->aes);

	uint8_t digest[64];
	if (cri_is_valid(aes->aesengine)) {
		aeskey_work = (aeskey_work_struct *) mac;
		cmac_key = (fips_aes_key *) aeskey_work->key;
		keyval = (uint8_t *) aeskey_work->keyvalue;
		cashed_digest = (uint8_t *) (keyval + cmac_key->size);
		digest_length = aes->taglen;

		status = aes_cmac_final_int(aes, (uint8_t *) (h->params[0].memref.offset + SAC_MEMORY_BASE),
				h->params[0].memref.size, digest, digest_length);
	} else if (cri_is_valid(sha->hashengine)) {
		mackey_work = (mackey_work_struct *) mac;
		hmac_key = mackey_work->key;
		keyval = mackey_work->keyvalue;
		cashed_digest = (uint8_t *) (keyval + hmac_key->size);
		digest_length = sha->hashlen;

		status = hash_final_int(sha, (uint8_t *) (h->params[0].memref.offset + SAC_MEMORY_BASE),
				h->params[0].memref.size, digest, digest_length);
	} else {
		status = -EIO;
	}
	if (status) {
		goto out1;
	}

	for (int i = 0; i < digest_length; i++) {
		if (cashed_digest[i] != digest[i])
			errs += 1;
	}
	if (errs != 0) {
		dprintk("MAC verification failed\n");
		status = -EPERM;
		goto out1;
	}
	dprintk("MAC verification passed\n");

out1:
	destroy_workcontext(status);
	return status;
}
