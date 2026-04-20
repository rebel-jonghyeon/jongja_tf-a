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
#include <stdalign.h>

#include <errno.h>
#include <hexutil.h>

#include <drivers/cmrt/cmrt.h>
#include <drivers/cmrt/tmc.h>
#include <drivers/cmrt/util.h>

#include <cri/cmrt/teedev_dmac.h>
#include <cri/cmrt/sac.h>
#include <cri/cmrt/aes.h>
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

#define FIPS_IVlen 16
#define AES_BS 16;

/* workcontext: identifier - aes_work_struct - asset */

static int32_t generate_gcm_IV(uint8_t *loc);

static int32_t read_aes_asset_and_prep(fips_state_t *state,
		teec_abi_invokecommand_t *h, int assetloc, int ivloc, int dirloc,
		uint32_t cipher, fips_asset_type type, aes_work_struct *aes)
{
	int32_t status;
	fips_asset_identifier *asset;
	fips_asset *aeskeyasset;
	teefs_command_t cmd;
	aeskey_work_struct *aeskey_work;
	fips_aes_key *key;
	uint8_t *keyval;

	asset = (fips_asset_identifier *) (h->params[assetloc].memref.offset
			+ SAC_MEMORY_BASE);
	dprintk("AES asset name length %d\n", asset->asset_name_length);
	dprintk("AES asset name %s\n", asset->asset_name);
	if (asset->location == FIPS_ASSET_DYNAMIC) {
		cmd = READ_FILE_RAM;
	} else if (asset->location == FIPS_ASSET_STATIC) {
		cmd = READ_FILE_OTP;
	} else {
		status = -EPERM;
		goto out;
	}

	status = process_teefs_request(cmd, asset->asset_name_length,
			asset->asset_name, g_inout_buffer, &g_inout_buffer_len);
	if (status) {
		dprintk("Asset read status: %d\n", status);
		goto out;
	}

	status = buffer_to_fips_asset((uint8_t *) g_inout_buffer, &g_inout_buffer_len,
			workcontext + sizeof(uint32_t) + sizeof(aes_work_struct), workcontext);
	if (status) {
		dprintk("Buffer to fips asset status: %d\n", status);
		goto out;
	}
	aeskey_work = (aeskey_work_struct *) aes;
	key = aeskey_work->key;
	keyval = aeskey_work->keyvalue;
	aeskeyasset = (fips_asset *) aeskey_work->asset;

	if (GET_ASSET_TYPE(aeskeyasset->metadata) != type) {
		dprintk("Wrong meta data type read for an AES key\n");
		status = -EPERM;
		goto out;
	}

	if (fips_get_asset_permissions(state->user,
			GET_ASSET_OWNER(aeskeyasset->metadata)) == 0) {
		dprintk(
				"The currently logged in user cannot use the asset just opened\n");
		status = -EACCES;
		goto out;
	}

	aeskey_work = (aeskey_work_struct *) aes;
	key = aeskey_work->key;
	keyval = aeskey_work->keyvalue;

	/* direction */
	if (cipher == AES_CTR) { /* ctr case */
		aes->direction = AES_ENCRYPT;
	} else {
		if (h->params[dirloc].value.a == FIPS_CIPHER_ENCRYPT) {
			aes->direction = AES_ENCRYPT;
		} else if (h->params[dirloc].value.a == FIPS_CIPHER_DECRYPT) {
			aes->direction = AES_DECRYPT;
		} else {
			status = -EINVAL;
			goto out;
		}
	}

	/*copy IV*/
	if (cipher == AES_GCM) {
		if (h->params[dirloc].value.a == FIPS_CIPHER_ENCRYPT) {
			/*generateIV & copy into workcontext 96 bits*/
			if (h->params[ivloc].memref.size != 0) {
				dprintk("IV parameter for AES_GCM ENCRYPT is wrong:%d\n",
						h->params[ivloc].memref.size);
				status = -EINVAL;
				goto out;
			}
			status = generate_gcm_IV(keyval + key->size);
			aes->IV = (uint8_t *) keyval + key->size;
			aes->IVlen = 12;
			dhexdump("IV", aes->IV, aes->IVlen);
			dhexdump("keyval", keyval, 16);
			if (status != 0) {
				dprintk("The IV generation failed:%d\n", status);
				goto out;
			}
		}
		if (h->params[dirloc].value.a == FIPS_CIPHER_DECRYPT) {
			/*getIV & copy into workcontext [size] bits*/
			memcpy(keyval + key->size,
					(uint8_t *) (h->params[ivloc].memref.offset
							+ SAC_MEMORY_BASE), h->params[ivloc].memref.size);
			aes->IV = (uint8_t *) keyval + key->size;
			aes->IVlen = (uint32_t) h->params[ivloc].memref.size;
			dhexdump("IV in", aes->IV, aes->IVlen);
		}
	} else {
		if (cipher == AES_ECB) {
			aes->IV = NULL;
			aes->IVlen = 0;
		} else {
			memcpy(keyval + key->size,
					(uint8_t *) (h->params[ivloc].memref.offset + SAC_MEMORY_BASE),
					h->params[ivloc].memref.size);
			aes->IV = (uint8_t *) (keyval + key->size);
			aes->IVlen = h->params[ivloc].memref.size;
			dhexdump("AES IN value", aes->IV, h->params[ivloc].memref.size);
		}
	}

	dprintk("Let's open the AES engine\n");

	aes->aesengine = cri_aes_open(0);
	if (!cri_is_valid(aes->aesengine)) {
		dprintk("Cannot open %s\n", CONFIG_CRI_AES_NAME);
		status = -EIO;
		goto out;
	}

	int tag_size;

	if (cipher == AES_GCM) {
		tag_size = h->params[0].value.b;
		aes->taglen = tag_size;
	} else {
		aes->taglen = 0;
	}

	status = cri_aes_init(aes->aesengine, aes->direction, cipher, keyval,
			key->size, aes->IV, aes->IVlen, aes->taglen);
	if (status) {
		dprintk("Cannot initialize %s\n", CONFIG_CRI_AES_NAME);
		status = -EIO;
		goto out;
	}

out:
	return status;
}

int32_t fips_aes_ecb(fips_state_t *state, teec_abi_invokecommand_t *h)
{
	int32_t status = 0;

	aes_work_struct *aes;
	int blocks, bytelen, i;

	dprintk("FIPS_SERVICE_AES_ECB\n");
	CHECK_COMMAND(FIPS_SERVICE_AES_ECB);

	aes = (aes_work_struct *) (workcontext + sizeof(uint32_t));

	/* check asset location type , zero param value, IV size correctness and size fips asset */
	if (!fips_is_fips_direction(h->params[0].value.a)
			| (h->params[0].value.b != 0)
			| (h->params[1].memref.size != sizeof(fips_asset_identifier))) {
		status = -EINVAL;
		goto out;
	}

	status = read_aes_asset_and_prep(state, h, 1, 2, 0, AES_ECB, FIPS_TYPE_AES, aes);
	if (status != 0) {
		goto out;
	}

	if (h->params[2].memref.size != h->params[3].memref.size) {
		dprintk("The input and output buffer in the shared memory are not sized equally\n");
		status = -EINVAL;
		goto out;
	}

	if ((h->params[2].memref.size % 16) != 0) {
		dprintk("The input byte length is not a multiple of the AES block size\n");
		status = -EINVAL;
		goto out;
	}

	bytelen = h->params[2].memref.size;
	blocks = (int) (bytelen / 16);

	for (i = 0; i < blocks; ++i) {
		if (i == blocks - 1) {
			status = cri_aes_final(aes->aesengine,
					(uint8_t *) (h->params[2].memref.offset + SAC_MEMORY_BASE + i * 16), 16,
					(uint8_t *) (h->params[3].memref.offset + SAC_MEMORY_BASE + i * 16));
			if (status) {
				printk("Cannot final AES: %d\n", status);
				status = -EIO;
				goto out;
			}
		} else {
			status = cri_aes_update(aes->aesengine,
					(uint8_t *) (h->params[2].memref.offset + SAC_MEMORY_BASE
							+ i * 16), 16,
					(uint8_t *) (h->params[3].memref.offset + SAC_MEMORY_BASE
							+ i * 16));
			if (status) {
				printk("Cannot update AES: %d\n", status);
				status = -EIO;
				goto out;
			}
		}
	}

out:
	destroy_workcontext(status);
	return status;
}

int32_t fips_aes_cbc_init(fips_state_t *state, teec_abi_invokecommand_t *h)
{
	int32_t status = 0;

	aes_work_struct *aes;

	dprintk("FIPS_SERVICE_AES_CBC_INIT\n");
	CHECK_COMMAND(FIPS_SERVICE_AES_CBC_INIT);

	aes = (aes_work_struct *) (workcontext + sizeof(uint32_t));

	/* check asset location type , zero param value, IV size correctness and size fips asset */
	if (!fips_is_fips_direction(h->params[0].value.a) ||
		(h->params[0].value.b != 0) ||
		(h->params[2].memref.size != FIPS_IVlen) ||
		(h->params[1].memref.size != sizeof(fips_asset_identifier))) {
		status = -EINVAL;
		goto out1;
	}

	status = read_aes_asset_and_prep(state, h, 1, 2, 0, AES_CBC, FIPS_TYPE_AES, aes);
	if (status) {
		goto out1;
	}

	goto out;

out1:
	destroy_workcontext(status);
out:
	return status;
}

int32_t fips_aes_cbc_update(fips_state_t *state, teec_abi_invokecommand_t *h)
{

	int32_t status = 0;

	aes_work_struct *aes;
	aeskey_work_struct *aeskey_work;
	fips_asset *aeskeyasset;
	fips_aes_key *key;
	uint8_t *keyval;

	int bytelen;
	int blocks;
	int i;

	dprintk("FIPS_SERVICE_AES_CBC_UPDATE\n");

	if ((((uint32_t *) workcontext)[0] != FIPS_SERVICE_AES_CBC_INIT) &&
		(((uint32_t *) workcontext)[0] != FIPS_SERVICE_AES_CBC_UPDATE)) {
		dprintk("Previous command was not FIPS_SERVICE_AES_CBC_INIT or FIPS_SERVICE_AES_CBC_UPDATE: %d\n",
				(uint32_t) workcontext[0]);
		status = -EPERM;
		goto out1;
	}

	((uint32_t *) workcontext)[0] = FIPS_SERVICE_AES_CBC_UPDATE;

	aes = (aes_work_struct *) (workcontext + sizeof(uint32_t));
	aeskey_work = (aeskey_work_struct *) aes;
	aeskeyasset = aeskey_work->asset;
	key = aeskey_work->key;
	keyval = aeskey_work->keyvalue;

	if (h->params[0].memref.size != h->params[1].memref.size) {
		dprintk("The input and output buffer in the shared memory are not sized equally\n");
		status = -EINVAL;
		goto out;
	}

	if ((h->params[0].memref.size % 16) != 0) {
		dprintk("The input byte length is not a multiple of the AES block size\n");
		status = -EINVAL;
		goto out1;
	}

	bytelen = h->params[0].memref.size;
	blocks = (int) (bytelen / 16);

	for (i = 0; i < blocks; i++) {
		status = cri_aes_update(aes->aesengine,
				(uint8_t *) (h->params[0].memref.offset + SAC_MEMORY_BASE + i * 16), 16,
				(uint8_t *) (h->params[1].memref.offset + SAC_MEMORY_BASE + i * 16));
		if (status) {
			printk("Cannot update AES: %d\n", status);
			status = -EIO;
			goto out1;
		}
	}
	goto out;

out1:
	destroy_workcontext(status);
out:
	return status;
}

int32_t fips_aes_cbc_final(fips_state_t *state, teec_abi_invokecommand_t *h)
{

	int32_t status = 0;

	aes_work_struct *aes;
	aeskey_work_struct *aeskey_work;
	fips_asset *aeskeyasset;
	fips_aes_key *key;
	uint8_t *keyval;

	int bytelen;
	int blocks;
	int i;

	dprintk("FIPS_SERVICE_AES_CBC_FINAL\n");

	if ((((uint32_t *) workcontext)[0] != FIPS_SERVICE_AES_CBC_INIT) &&
		(((uint32_t *) workcontext)[0] != FIPS_SERVICE_AES_CBC_UPDATE)) {
		dprintk("Previous command was not FIPS_SERVICE_AES_CBC_INIT or FIPS_SERVICE_AES_CBC_UPDATE: %d\n",
				(uint32_t) workcontext[0]);
		status = -EPERM;
		goto out;
	}

	((uint32_t *) workcontext)[0] = FIPS_SERVICE_AES_CBC_FINAL;

	aes = (aes_work_struct *) (workcontext + sizeof(uint32_t));
	aeskey_work = (aeskey_work_struct *) aes;
	aeskeyasset = aeskey_work->asset;
	key = aeskey_work->key;
	keyval = aeskey_work->keyvalue;

	if (h->params[0].memref.size != h->params[1].memref.size) {
		dprintk("The input and output buffer in the shared memory are not sized equally\n");
		status = -EINVAL;
		goto out;
	}

	if ((h->params[0].memref.size % 16) != 0) {
		dprintk("The input byte length is not a multiple of the AES block size\n");
		status = -EINVAL;
		goto out;
	}

	bytelen = h->params[0].memref.size;
	blocks = (int) (bytelen / 16);

	for (i = 0; i < blocks; ++i) {
		if (i == blocks - 1) {
			status = cri_aes_final(aes->aesengine,
					(uint8_t *) (h->params[0].memref.offset + SAC_MEMORY_BASE + i * 16), 16,
					(uint8_t *) (h->params[1].memref.offset + SAC_MEMORY_BASE + i * 16));
			if (status) {
				printk("Cannot final AES: %d\n", status);
				status = -EIO;
				goto out;
			}
		} else {
			status = cri_aes_update(aes->aesengine,
					(uint8_t *) (h->params[0].memref.offset + SAC_MEMORY_BASE + i * 16), 16,
					(uint8_t *) (h->params[1].memref.offset + SAC_MEMORY_BASE + i * 16));
			if (status) {
				printk("Cannot update AES: %d\n", status);
				status = -EIO;
				goto out;
			}
		}
	}

out:
	destroy_workcontext(status);
	return status;
}

int32_t fips_aes_gcm_init(fips_state_t *state, teec_abi_invokecommand_t *h)
{
	int32_t status = 0;

	aes_work_struct *aes;
	fips_asset_type type;

	dprintk("FIPS_SERVICE_AES_GCM_INIT\n");
	CHECK_COMMAND(FIPS_SERVICE_AES_GCM_INIT);

	aes = (aes_work_struct *) (workcontext + sizeof(uint32_t));

	/* check asset location type , zero param value, IV size correctness and size fips asset */
	if (!fips_is_fips_direction(h->params[0].value.a) ||
		!fips_is_valid_tag_length(h->params[0].value.b) ||
		(h->params[1].memref.size != sizeof(fips_asset_identifier))) {
		status = -EINVAL;
		goto out;
	}

	if (h->params[0].value.a == FIPS_CIPHER_ENCRYPT) {
		type = FIPS_TYPE_AES_GCM_ENCRYPT;
	} else if (h->params[0].value.a == FIPS_CIPHER_DECRYPT) {
		type = FIPS_TYPE_AES_GCM_DECRYPT;
	} else {
		status = -EINVAL;
		goto out;
	}

	status = read_aes_asset_and_prep(state, h, 1, 2, 0, AES_GCM, type, aes);
	if (status) {
		goto out1;
	}

	dhexdump("AAD", (uint8_t *) (h->params[3].memref.offset + SAC_MEMORY_BASE), h->params[3].memref.size);
	dprintk("memory location AAD: %08X\n", (unsigned int)(h->params[3].memref.offset + SAC_MEMORY_BASE));
	dprintk("memory size AAD: %d\n", h->params[3].memref.size);

	if (h->params[3].memref.size != 0) {
		status = cri_aes_final_aad(aes->aesengine,
				(uint8_t *) (h->params[3].memref.offset + SAC_MEMORY_BASE),
				h->params[3].memref.size);
		if (status != 0) {
			dprintk("Cannot update the AAD %d\n", status);
			goto out1;
		}
	}

	goto out;

out1:
	destroy_workcontext(status);
out:
	return status;
}

int32_t fips_aes_gcm_aad_update(fips_state_t *state,
		teec_abi_invokecommand_t *h)
{

	int32_t status = 0;

	aes_work_struct *aes;
	aeskey_work_struct *aeskey_work;
	fips_asset *aeskeyasset;
	fips_aes_key *key;
	uint8_t *keyval;

	int bytelen;

	dprintk("FIPS_SERVICE_AES_GCM_AAD_UPDATE\n");

	if ((((uint32_t *) workcontext)[0] != FIPS_SERVICE_AES_GCM_INIT) &&
		(((uint32_t *) workcontext)[0] != FIPS_SERVICE_AES_GCM_AAD_UPDATE)) {
		dprintk("Previous command was not FIPS_SERVICE_AES_GCM_INIT or FIPS_SERVICE_AES_GCM_AAD_UPDATE: %d\n",
				((uint32_t *) workcontext)[0]);
		status = -EPERM;
		goto out1;
	}

	((uint32_t *) workcontext)[0] = FIPS_SERVICE_AES_GCM_AAD_UPDATE;

	aes = (aes_work_struct *) (workcontext + sizeof(uint32_t));
	aeskey_work = (aeskey_work_struct *) aes;
	aeskeyasset = aeskey_work->asset;
	key = aeskey_work->key;
	keyval = aeskey_work->keyvalue;

	if ((h->params[0].memref.size % 16) != 0) {
		dprintk("The input byte length is not a multiple of the AES block size\n");
		status = -EINVAL;
		goto out1;
	}

	bytelen = h->params[0].memref.size;
	dprintk("bytelen %d\n", bytelen);

	if (bytelen != 0) {
		status = cri_aes_final_aad(aes->aesengine,
				(uint8_t *) (h->params[0].memref.offset + SAC_MEMORY_BASE),
				bytelen);
		dhexdump("AAD", (uint8_t *) (h->params[0].memref.offset + SAC_MEMORY_BASE), bytelen);
		if (status) {
			dprintk("Cannot update AES AAD: %d\n", status);
			status = -EIO;
			goto out1;
		}
	}
	goto out;

out1:
	destroy_workcontext(status);
out:
	return status;
}

int32_t fips_aes_gcm_update(fips_state_t *state, teec_abi_invokecommand_t *h)
{
	int32_t status = 0;

	aes_work_struct *aes;
	aeskey_work_struct *aeskey_work;
	fips_asset *aeskeyasset;
	fips_aes_key *key;
	uint8_t *keyval;

	int bytelen;
	int blocks;
	int i;

	dprintk("FIPS_SERVICE_AES_GCM_UPDATE\n");

	if ((((uint32_t *) workcontext)[0] != FIPS_SERVICE_AES_GCM_INIT) &&
		(((uint32_t *) workcontext)[0] != FIPS_SERVICE_AES_GCM_UPDATE) &&
		(((uint32_t *) workcontext)[0] != FIPS_SERVICE_AES_GCM_AAD_UPDATE)) {
		dprintk("Previous command was not FIPS_SERVICE_AES_GCM_INIT, FIPS_SERVICE_AES_GCM_AAD_UPDATE or FIPS_SERVICE_AES_GCM_UPDATE: %d\n",
				((uint32_t *) workcontext)[0]);
		status = -EPERM;
		goto out1;
	}

	((uint32_t *) workcontext)[0] = FIPS_SERVICE_AES_GCM_UPDATE;

	aes = (aes_work_struct *) (workcontext + sizeof(uint32_t));
	aeskey_work = (aeskey_work_struct *) aes;
	aeskeyasset = aeskey_work->asset;
	key = aeskey_work->key;
	keyval = aeskey_work->keyvalue;

	if (h->params[0].memref.size != h->params[1].memref.size) {
		dprintk(
				"The input and output buffer in the shared memory are not sized equally\n");
		status = -EINVAL;
		goto out;
	}

	if ((h->params[0].memref.size % 16) != 0) {
		dprintk(
				"The input byte length is not a multiple of the AES block size\n");
		status = -EINVAL;
		goto out;
	}

	bytelen = h->params[0].memref.size;
	blocks = (int) (bytelen / 16);
	dprintk("AES Update bytelen %d\n", bytelen);
	dprintk("AES Update blocks %d\n", blocks);

	dprintk("aes->aesengine %d\n", (int) aes->aesengine);
	for (i = 0; i < blocks; i++) {
		status = cri_aes_update(aes->aesengine,
				(uint8_t *) (h->params[0].memref.offset + SAC_MEMORY_BASE + i * 16), 16,
				(uint8_t *) (h->params[1].memref.offset + SAC_MEMORY_BASE + i * 16));
		dhexdump("INPUT", (uint8_t *) (h->params[0].memref.offset + SAC_MEMORY_BASE + i * 16), 16);
		dhexdump("OUTPUT", (uint8_t *) (h->params[1].memref.offset + SAC_MEMORY_BASE + i * 16), 16);
		if (status) {
			dprintk("Cannot update AES: %d\n", status);
			status = -EIO;
			goto out1;
		}
	}
	goto out;

out1:
	destroy_workcontext(status);
out:
	return status;
}

int32_t fips_aes_gcm_encrypt_final(fips_state_t *state,
		teec_abi_invokecommand_t *h)
{
	int32_t status = 0;

	aes_work_struct *aes;
	aeskey_work_struct *aeskey_work;
	fips_asset *aeskeyasset;
	fips_aes_key *key;
	uint8_t *keyval;

	dprintk("FIPS_SERVICE_AES_GCM_ENCRYPT_FINAL\n");

	if ((((uint32_t *) workcontext)[0] != FIPS_SERVICE_AES_GCM_INIT) &&
		(((uint32_t *) workcontext)[0] != FIPS_SERVICE_AES_GCM_UPDATE) &&
		(((uint32_t *) workcontext)[0] != FIPS_SERVICE_AES_GCM_AAD_UPDATE)) {
		dprintk("Previous command was not FIPS_SERVICE_AES_GCM_INIT, FIPS_SERVICE_AES_GCM_AAD_UPDATE or FIPS_SERVICE_AES_CBC_UPDATE: %d\n",
				((uint32_t *) workcontext)[0]);
		status = -EPERM;
		goto out1;
	}

	((uint32_t *) workcontext)[0] = FIPS_SERVICE_AES_GCM_ENCRYPT_FINAL;

	aes = (aes_work_struct *) (workcontext + sizeof(uint32_t));
	aeskey_work = (aeskey_work_struct *) aes;
	aeskeyasset = aeskey_work->asset;
	key = aeskey_work->key;
	keyval = aeskey_work->keyvalue;

	dprintk("Direction %d\n", aes->direction);
	if (aes->direction != AES_ENCRYPT) {
		status = -EINVAL;
		goto out1;
	}

	/*need space in working context for tagsize & direction*/
	if (h->params[2].memref.size < aes->taglen) {
		dprintk("The space in memory is not large enough for the tag length: %d, needed: %d\n",
				h->params[2].memref.size, aes->taglen);
		status = -EINVAL;
		goto out1;
	}
	if (h->params[3].memref.size < 12) {
		dprintk("The space in memory for the IV needs to at least 12 bytes, it is %d\n",
				h->params[3].memref.size);
		status = -EINVAL;
		goto out1;
	}

	if (h->params[1].memref.size < h->params[0].memref.size) {
		dprintk("The space in memory for the output needs larger or equal to the input size, it is %d\n",
				h->params[1].memref.size);
		status = -EINVAL;
		goto out1;

	}
	uint32_t taglen = aes->taglen;
	if (h->params[0].memref.size == 0) {
		dprintk("No input\n");
		status = cri_aes_ae_final(aes->aesengine, NULL, 0, NULL,
				(uint8_t *) (h->params[2].memref.offset + SAC_MEMORY_BASE), &taglen);
	} else {
		status = cri_aes_ae_final(aes->aesengine, (uint8_t *) (h->params[0].memref.offset + SAC_MEMORY_BASE),
					h->params[0].memref.size, (uint8_t *) (h->params[1].memref.offset + SAC_MEMORY_BASE),
					(uint8_t *) (h->params[2].memref.offset + SAC_MEMORY_BASE), &taglen);
	}
	if (status) {
		printk("Cannot final AES: %d\n", status);
		status = -EIO;
		goto out1;
	}
	memcpy((uint8_t *) (h->params[3].memref.offset + SAC_MEMORY_BASE), aes->IV, aes->IVlen);
	aes->taglen = taglen;

out1:
	destroy_workcontext(status);
	return status;
}

int32_t fips_aes_gcm_decrypt_final(fips_state_t *state,
		teec_abi_invokecommand_t *h)
{
	int32_t status = 0;

	aes_work_struct *aes;
	alignas(4) uint8_t tag[16];
	uint32_t taglen = sizeof(tag);
	uint8_t *tagin;

	dprintk("FIPS_SERVICE_AES_GCM_DECRYPT_FINAL\n");

	if ((((uint32_t *) workcontext)[0] != FIPS_SERVICE_AES_GCM_INIT) &&
		(((uint32_t *) workcontext)[0] != FIPS_SERVICE_AES_GCM_UPDATE) &&
		(((uint32_t *) workcontext)[0] != FIPS_SERVICE_AES_GCM_AAD_UPDATE)) {
		dprintk("Previous command was not FIPS_SERVICE_AES_CBC_INIT, FIPS_SERVICE_AES_GCM_AAD_UPDATE or FIPS_SERVICE_AES_CBC_UPDATE: %d\n",
				((uint32_t *) workcontext)[0]);
		status = -EPERM;
		goto out1;
	}

	((uint32_t *) workcontext)[0] = FIPS_SERVICE_AES_GCM_DECRYPT_FINAL;

	aes = (aes_work_struct *) (workcontext + sizeof(uint32_t));

	dprintk("Direction %d\n", aes->direction);
	if (aes->direction != AES_DECRYPT) {
		status = -EINVAL;
		goto out1;
	}

	/*need space in working context for tagsize & direction*/
	if (h->params[0].memref.size != aes->taglen) {
		dprintk("The space in memory is not the correct size for the tag length: %d, needed: %d\n",
				h->params[0].memref.size, aes->taglen);
		status = -EINVAL;
		goto out1;
	}
	taglen = aes->taglen;

	tagin = (uint8_t *) (h->params[0].memref.offset + SAC_MEMORY_BASE);
	memcpy(tag, tagin, h->params[0].memref.size);

	if (h->params[2].memref.size < h->params[1].memref.size) {
		dprintk("The space in memory for the output has to be larger or equal to the input size, it is %d\n",
				h->params[2].memref.size);
		status = -EINVAL;
		goto out1;
	}

	if (h->params[1].memref.size == 0) {
		status = cri_aes_ae_final(aes->aesengine, NULL, 0, NULL, tag, &taglen);
	} else {
		status = cri_aes_ae_final(aes->aesengine, (uint8_t *) (h->params[1].memref.offset + SAC_MEMORY_BASE), h->params[1].memref.size, (uint8_t *) (h->params[2].memref.offset + SAC_MEMORY_BASE), tag, &taglen);
	}
	dprintk("tag:");
	hexdump(tag, taglen);
	dprintk("taglen: %d\n", taglen);
	dprintk("aes->aesengine: %d\n", (uint32_t) aes->aesengine);
	dprintk("Address tag %08x\n", (unsigned int)&(tag[0]));
	if (status) {
		dprintk("Cannot final AES: %d\n", status);
		status = -EIO;
		goto out1;
	}

out1:
	destroy_workcontext(status);
	return status;
}

int32_t fips_aes_ctr_init(fips_state_t *state, teec_abi_invokecommand_t *h)
{
	int32_t status = 0;

	aes_work_struct *aes;

	dprintk("FIPS_SERVICE_AES_CTR_INIT\n");
	CHECK_COMMAND(FIPS_SERVICE_AES_CTR_INIT);

	aes = (aes_work_struct *) (workcontext + sizeof(uint32_t));

	/* check asset location type , IV size correctness and size fips asset */
	if ((h->params[1].memref.size != FIPS_IVlen)
			| (h->params[0].memref.size != sizeof(fips_asset_identifier))) {
		status = -EINVAL;
		goto out1;
	}

	status = read_aes_asset_and_prep(state, h, 0, 1, 0, AES_CTR, FIPS_TYPE_AES, aes);
	if (status) {
		goto out1;
	}

	goto out;

out1:
	destroy_workcontext(status);
out:
	return status;
}

int32_t fips_aes_ctr_update(fips_state_t *state, teec_abi_invokecommand_t *h)
{
	int32_t status = 0;

	aes_work_struct *aes;
	aeskey_work_struct *aeskey_work;
	fips_asset *aeskeyasset;
	fips_aes_key *key;
	uint8_t *keyval;

	int bytelen;
	int blocks;
	int i;

	dprintk("FIPS_SERVICE_AES_CTR_UPDATE\n");

	if ((((uint32_t *) workcontext)[0] != FIPS_SERVICE_AES_CTR_INIT) &&
		(((uint32_t *) workcontext)[0] != FIPS_SERVICE_AES_CTR_UPDATE)) {
		dprintk("Previous command was not FIPS_SERVICE_AES_CTR_INIT or FIPS_SERVICE_AES_CTR_UPDATE: %d\n",
				(uint32_t) workcontext[0]);
		status = -EPERM;
		goto out1;
	}

	((uint32_t *) workcontext)[0] = FIPS_SERVICE_AES_CTR_UPDATE;

	aes = (aes_work_struct *) (workcontext + sizeof(uint32_t));
	aeskey_work = (aeskey_work_struct *) aes;
	aeskeyasset = aeskey_work->asset;
	key = aeskey_work->key;
	keyval = aeskey_work->keyvalue;

	if (h->params[0].memref.size != h->params[1].memref.size) {
		dprintk("The input and output buffer in the shared memory are not sized equally\n");
		status = -EINVAL;
		goto out;
	}

	if ((h->params[0].memref.size % 16) != 0) {
		dprintk("The input byte length is not a multiple of the AES block size\n");
		status = -EINVAL;
		goto out1;
	}

	bytelen = h->params[0].memref.size;
	blocks = (int) (bytelen / 16);

	for (i = 0; i < blocks; i++) {
		status = cri_aes_update(aes->aesengine,
				(uint8_t *) (h->params[0].memref.offset + SAC_MEMORY_BASE
						+ i * 16), 16,
				(uint8_t *) (h->params[1].memref.offset + SAC_MEMORY_BASE
						+ i * 16));
		if (status) {
			printk("Cannot update AES: %d\n", status);
			status = -EIO;
			goto out1;
		}
	}
	goto out;

out1:
	destroy_workcontext(status);
out:
	return status;
}

int32_t fips_aes_ctr_final(fips_state_t *state, teec_abi_invokecommand_t *h)
{

	int32_t status = 0;

	aes_work_struct *aes;
	aeskey_work_struct *aeskey_work;
	fips_asset *aeskeyasset;
	fips_aes_key *key;
	uint8_t *keyval;

	int bytelen;
	int blocks;
	int i;

	dprintk("FIPS_SERVICE_AES_CTR_FINAL\n");

	if ((((uint32_t *) workcontext)[0] != FIPS_SERVICE_AES_CTR_INIT) &&
		(((uint32_t *) workcontext)[0] != FIPS_SERVICE_AES_CTR_UPDATE)) {
		dprintk("Previous command was not FIPS_SERVICE_AES_CTR_INIT or FIPS_SERVICE_AES_CTR_UPDATE: %d\n",
				(uint32_t) workcontext[0]);
		status = -EPERM;
		goto out;
	}

	((uint32_t *) workcontext)[0] = FIPS_SERVICE_AES_CTR_FINAL;

	aes = (aes_work_struct *) (workcontext + sizeof(uint32_t));
	aeskey_work = (aeskey_work_struct *) aes;
	aeskeyasset = aeskey_work->asset;
	key = aeskey_work->key;
	keyval = aeskey_work->keyvalue;

	if (h->params[0].memref.size != h->params[1].memref.size) {
		dprintk("The input and output buffer in the shared memory are not sized equally\n");
		status = -EINVAL;
		goto out;
	}

	if ((h->params[0].memref.size % 16) != 0) {
		dprintk("The input byte length is not a multiple of the AES block size\n");
		status = -EINVAL;
		goto out;
	}

	bytelen = h->params[0].memref.size;
	blocks = (int) (bytelen / 16);

	for (i = 0; i < blocks; ++i) {
		if (i == blocks - 1) {
			status = cri_aes_final(aes->aesengine,
					(uint8_t *) (h->params[0].memref.offset + SAC_MEMORY_BASE + i * 16), 16,
					(uint8_t *) (h->params[1].memref.offset + SAC_MEMORY_BASE + i * 16));
			if (status) {
				printk("Cannot final AES: %d\n", status);
				status = -EIO;
				goto out;
			}
		} else {
			status = cri_aes_update(aes->aesengine,
					(uint8_t *) (h->params[0].memref.offset + SAC_MEMORY_BASE + i * 16), 16,
					(uint8_t *) (h->params[1].memref.offset + SAC_MEMORY_BASE + i * 16));
			if (status) {
				printk("Cannot update AES: %d\n", status);
				status = -EIO;
				goto out;
			}
		}
	}

out:
	destroy_workcontext(status);
	return status;
}

int32_t fips_aes_cfb128_init(fips_state_t *state, teec_abi_invokecommand_t *h)
{
	int32_t status = 0;

	aes_work_struct *aes;

	dprintk("FIPS_SERVICE_AES_CFB128_INIT\n");
	CHECK_COMMAND(FIPS_SERVICE_AES_CFB128_INIT);

	aes = (aes_work_struct *) (workcontext + sizeof(uint32_t));

	/* check asset location type , zero param value, IV size correctness and size fips asset */
	if (!fips_is_fips_direction(h->params[0].value.a) ||
		(h->params[0].value.b != 0) ||
		(h->params[2].memref.size != FIPS_IVlen) ||
		(h->params[1].memref.size != sizeof(fips_asset_identifier))) {
		status = -EINVAL;
		goto out1;
	}

	status = read_aes_asset_and_prep(state, h, 1, 2, 0, AES_CFB, FIPS_TYPE_AES, aes);
	if (status) {
		goto out1;
	}

	goto out;

out1:
	destroy_workcontext(status);
out:
	return status;
}

int32_t fips_aes_cfb128_update(fips_state_t *state,
		teec_abi_invokecommand_t *h)
{

	int32_t status = 0;

	aes_work_struct *aes;
	aeskey_work_struct *aeskey_work;
	fips_asset *aeskeyasset;
	fips_aes_key *key;
	uint8_t *keyval;

	int bytelen;
	int blocks;
	int i;

	dprintk("FIPS_SERVICE_AES_CFB128_UPDATE\n");

	if ((((uint32_t *) workcontext)[0] != FIPS_SERVICE_AES_CFB128_INIT) &&
		(((uint32_t *) workcontext)[0] != FIPS_SERVICE_AES_CFB128_UPDATE)) {
		dprintk("Previous command was not FIPS_SERVICE_AES_CFB128_INIT or FIPS_SERVICE_AES_CFB128_UPDATE: %d\n",
				(uint32_t) workcontext[0]);
		status = -EPERM;
		goto out1;
	}

	((uint32_t *) workcontext)[0] = FIPS_SERVICE_AES_CFB128_UPDATE;

	aes = (aes_work_struct *) (workcontext + sizeof(uint32_t));
	aeskey_work = (aeskey_work_struct *) aes;
	aeskeyasset = aeskey_work->asset;
	key = aeskey_work->key;
	keyval = aeskey_work->keyvalue;

	if (h->params[0].memref.size != h->params[1].memref.size) {
		dprintk("The input and output buffer in the shared memory are not sized equally\n");
		status = -EINVAL;
		goto out;
	}

	if ((h->params[0].memref.size % 16) != 0) {
		dprintk("The input byte length is not a multiple of the AES block size\n");
		status = -EINVAL;
		goto out1;
	}

	bytelen = h->params[0].memref.size;
	blocks = (int) (bytelen / 16);

	for (i = 0; i < blocks; i++) {
		status = cri_aes_update(aes->aesengine,
				(uint8_t *) (h->params[0].memref.offset + SAC_MEMORY_BASE + i * 16), 16,
				(uint8_t *) (h->params[1].memref.offset + SAC_MEMORY_BASE + i * 16));
		if (status) {
			printk("Cannot update AES: %d\n", status);
			status = -EIO;
			goto out1;
		}
	}
	goto out;

out1:
	destroy_workcontext(status);
out:
	return status;
}

int32_t fips_aes_cfb128_final(fips_state_t *state,
		teec_abi_invokecommand_t *h)
{
	int32_t status = 0;

	aes_work_struct *aes;
	aeskey_work_struct *aeskey_work;
	fips_asset *aeskeyasset;
	fips_aes_key *key;
	uint8_t *keyval;

	int bytelen;
	int blocks;
	int i;

	dprintk("FIPS_SERVICE_AES_CFB128_FINAL\n");

	if ((((uint32_t) workcontext[0]) != FIPS_SERVICE_AES_CFB128_INIT) &&
		(((uint32_t) workcontext[0]) != FIPS_SERVICE_AES_CFB128_UPDATE)) {
		dprintk("Previous command was not FIPS_SERVICE_AES_CFB128_INIT or FIPS_SERVICE_AES_CFB128_UPDATE: %d\n",
				(uint32_t) workcontext[0]);
		status = -EPERM;
		goto out;
	}

	((uint32_t *) workcontext)[0] = (uint32_t) FIPS_SERVICE_AES_CFB128_FINAL;

	aes = (aes_work_struct *) (workcontext + sizeof(uint32_t));
	aeskey_work = (aeskey_work_struct *) aes;
	aeskeyasset = aeskey_work->asset;
	key = aeskey_work->key;
	keyval = aeskey_work->keyvalue;

	if (h->params[0].memref.size != h->params[1].memref.size) {
		dprintk("The input and output buffer in the shared memory are not sized equally\n");
		status = -EINVAL;
		goto out;
	}

	if ((h->params[0].memref.size % 16) != 0) {
		dprintk("The input byte length is not a multiple of the AES block size\n");
		status = -EINVAL;
		goto out;
	}

	bytelen = h->params[0].memref.size;
	blocks = (int) (bytelen / 16);

	for (i = 0; i < blocks; ++i) {
		if (i == blocks - 1) {
			status = cri_aes_final(aes->aesengine,
					(uint8_t *) (h->params[0].memref.offset + SAC_MEMORY_BASE + i * 16), 16,
					(uint8_t *) (h->params[1].memref.offset + SAC_MEMORY_BASE + i * 16));
			if (status) {
				printk("Cannot final AES: %d\n", status);
				status = -EIO;
				goto out;
			}
		} else {
			status = cri_aes_update(aes->aesengine,
					(uint8_t *) (h->params[0].memref.offset + SAC_MEMORY_BASE + i * 16), 16,
					(uint8_t *) (h->params[1].memref.offset + SAC_MEMORY_BASE + i * 16));
			if (status) {
				printk("Cannot update AES: %d\n", status);
				status = -EIO;
				goto out;
			}
		}
	}

out:
	destroy_workcontext(status);
	return status;
}

static int32_t generate_gcm_IV(uint8_t *loc)
{
	int32_t status = 0;

	int res = cmrt_get_random(loc, 12);
	if (res) {
		status = -EIO;
	}

	return status;
}
