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
#include <stdalign.h>

#include <errno.h>

#include <cri/cmrt/teedev_dmac.h>
#include <cri/cmrt/sac.h>
#include <cri/cmrt/sic.h>
#include <cri/cmrt/aes.h>
#include <cri/cmrt/tee_client_api.h> /* TEEC_MEMREF values */
#include <cri/cmrt/tee_client_abi.h>

#include <cri/cmrt/fips/fips_types.h>

#include "teec_cmvp.h"
#include "teefs_cmvp.h"
#include "fips_asset.h"
#include "fips.h"
#include "cmvp_sw.h"
#include "cri_utils.h"

#define AES_BLOCK_LENGTH 16
#define SEMI_BLOCK (AES_BLOCK_LENGTH/2)

/*
 * WORKCONTEXT:
 * identifier | import_work_struct ( aes_work_struct + scratch_pointer ) | fips_asset | keyvalue
 * identifier | export_work_struct ( aes_work_struct + export_asset_pointer + scratch_pointer ) | fips_asset_aes | keyvalue_aes | fips_asset_export | keyvalue_export
 *
 * Warning: This implementation does not use uint64_t for some variables despite the fact that if you were to rigorously implement
 * the spec, they may need to be, since our payloads are limited in size, a uint32_t is more than sufficient. External memory will
 * protest before a uint64_t is needed.
 */
static int32_t winv_keywrap(fips_state_t *state, cri_aes_t aes_engine,
		uint8_t *output, uint32_t *outlen, uint8_t *input, uint32_t *inlen)
{
	int32_t status;

	uint32_t Rpointerbase;
	uint32_t Apointerbase;

	uint32_t a_new, a_old;
	uint32_t r_in;
	alignas(4) uint8_t aes_out[AES_BLOCK_LENGTH];
	alignas(4) uint8_t aes_in[AES_BLOCK_LENGTH];

	Apointerbase = (uint32_t) (state->scratch);
	Rpointerbase = (uint32_t) ((state->scratch) + 2 * SEMI_BLOCK);

	uint32_t n = (*inlen) / (SEMI_BLOCK);
	uint32_t s = 6 * (n - 1);
	uint64_t t64;
	a_new = 0;
	a_old = 0;
	status = 0;

	dprintk("Setting up variables\n");
	/* setup A */
	memcpy((uint8_t *) Apointerbase, input, SEMI_BLOCK);

	/* setup R */
	memcpy((uint8_t *) (Rpointerbase), input + SEMI_BLOCK, *inlen - SEMI_BLOCK);

	r_in = 0;

	for (int t = s; t >= 1; t--) {
		a_new = ((t + 1) % 2);
		a_old = (t % 2);
		r_in = (r_in + n - 2) % (n - 1);
		t64 = (uint64_t) t;

		memcpy(aes_in, (uint8_t *) (Apointerbase + a_old * SEMI_BLOCK), SEMI_BLOCK);
		memcpy(aes_in + SEMI_BLOCK, (uint8_t *) (Rpointerbase + r_in * SEMI_BLOCK), SEMI_BLOCK);
		for (int i = 0; i < 8; i++)
			aes_in[i] = aes_in[i] ^ ((t64 >> (56 - i * 8)) & 0xff);

		status = cri_aes_update(aes_engine, aes_in, AES_BLOCK_LENGTH, aes_out);
		if (status) {
			printk("Cannot update AES: %d\n", status);
			status = -EIO;
		}

		memcpy((uint8_t *) (Apointerbase + a_new * SEMI_BLOCK), aes_out, SEMI_BLOCK);
		memcpy((uint8_t *) (Rpointerbase + r_in * SEMI_BLOCK),
				aes_out + SEMI_BLOCK, SEMI_BLOCK);
	}

	memcpy(output, (uint8_t *) (Apointerbase + a_new * SEMI_BLOCK), SEMI_BLOCK);
	for (int i = 1; i < n; i++) {
		memcpy(output + i * SEMI_BLOCK,
				(uint8_t *) (Rpointerbase + r_in * SEMI_BLOCK), SEMI_BLOCK);
		r_in = (r_in + 1) % (n - 1);
	}

	*outlen = *inlen;

	return status;
}

/* Warning: This implementation does not use uint64_t for some variables despite the fact that if you were to rigorously implement
 * the spec, they may need to be, since our payloads are limited in size, a uint32_t is more than sufficient. External memory will
 * protest before a uint64_t is needed. */
static int32_t w_keywrap(fips_state_t *state, cri_aes_t aes_engine,
		uint8_t *output, uint32_t *outlen, uint8_t *input, uint32_t *inlen)
{
	int32_t status;

	uint32_t ICV2 = 0xA65959A6;
	uint32_t padlen;
	uint32_t tmp = (*inlen / 8);

	if (*inlen == tmp * 8) {
		padlen = 0;
	} else {
		padlen = (8 * (tmp + 1)) - *inlen;
	}
	size_t totallen = padlen + 4 + 4 + *inlen;

	uint32_t Rpointerbase;
	uint32_t Apointerbase;

	uint32_t a_new, a_old;
	uint32_t r_in;
	alignas(4) uint8_t aes_out[AES_BLOCK_LENGTH];
	alignas(4) uint8_t aes_in[AES_BLOCK_LENGTH];

	Apointerbase = (uint32_t) (state->scratch);
	Rpointerbase = (uint32_t) ((state->scratch) + 2 * SEMI_BLOCK);

	uint32_t n = (totallen) / (SEMI_BLOCK);
	dprintk("New n = %d\n", n);
	uint32_t s = 6 * (n - 1);
	uint64_t t64;
	a_new = 0;
	a_old = 0;
	status = 0;

	dprintk("Setting up variables\n");
	/* setup A */
	memcpy((uint8_t *) Apointerbase, &ICV2, 4);
	memset((uint8_t *) (Apointerbase + 4), (*inlen >> 24) & 0xff, 1);
	memset((uint8_t *) (Apointerbase + 5), (*inlen >> 16) & 0xff, 1);
	memset((uint8_t *) (Apointerbase + 6), (*inlen >> 8) & 0xff, 1);
	memset((uint8_t *) (Apointerbase + 7), (*inlen >> 0) & 0xff, 1);

	/* setup R */
	memcpy((uint8_t *) (Rpointerbase), input, *inlen);
	memset((uint8_t *) (Rpointerbase + *inlen), 0x00, padlen);

	dhexdump("a", (uint8_t *)Apointerbase, 8);
	dhexdump("r", (uint8_t *)Rpointerbase, *inlen + padlen);

	r_in = 0;

	for (int t = 0; t < s; t++) {
		a_new = ((t + 1) % 2);
		a_old = (t % 2);
		t64 = (uint64_t) (t + 1);

		memcpy(aes_in, (uint8_t *) (Apointerbase + (a_old * SEMI_BLOCK)), SEMI_BLOCK);
		memcpy(aes_in + SEMI_BLOCK, (uint8_t *) (Rpointerbase + (r_in * SEMI_BLOCK)), SEMI_BLOCK);

		status = cri_aes_update(aes_engine, aes_in, AES_BLOCK_LENGTH, aes_out);
		if (status) {
			printk("Cannot update AES: %d\n", status);
			status = -EIO;
		}

		for (int i = 0; i < 8; i++)
			aes_out[i] = aes_out[i] ^ ((t64 >> (56 - i * 8)) & 0xff);

		memcpy((uint8_t *) (Apointerbase + (a_new * SEMI_BLOCK)), aes_out, SEMI_BLOCK);

		memcpy((uint8_t *) (Rpointerbase + (r_in * SEMI_BLOCK)),
				aes_out + SEMI_BLOCK, SEMI_BLOCK);

		r_in = (r_in + 1) % (n - 1);
	}

	memcpy(output, (uint8_t *) (Apointerbase + a_new * SEMI_BLOCK), SEMI_BLOCK);
	for (int i = 1; i < n; i++) {
		memcpy(output + i * SEMI_BLOCK, (uint8_t *) (Rpointerbase + r_in * SEMI_BLOCK), SEMI_BLOCK);
		r_in = (r_in + 1) % (n - 1);
	}
	*outlen = totallen;

	printk("totallen: %i\n", totallen);

	return status;
}

/*encrypt a key with kwp */
static int32_t kwp_ae(fips_state_t *state, uint8_t *ct, uint32_t *ctlen, uint8_t *pt, uint32_t *ptlen)
{
	int32_t status;

	cri_aes_t aes_engine;

	aes_engine = cri_aes_open(0);
	if (!cri_is_valid(aes_engine)) {
		dprintk("Cannot open %s\n", CONFIG_CRI_AES_NAME);
		status = -EIO;
		goto out;
	}

#ifdef CONFIG_CMRT_AES_192BIT
	if ((state->key_length != 16) && (state->key_length != 24) && (state->key_length != 32)) {
#else
	if ((state->key_length != 16) && (state->key_length != 32)) {
#endif
		dprintk("The KEK has an inappropriate length %d\n", state->key_length);
		status = -EINVAL;
		goto out;
	}

	status = cri_aes_init(aes_engine, AES_ENCRYPT, AES_ECB, state->key_value,
			state->key_length, NULL, 0, 0);
	if (status != 0) {
		dprintk("Cannot initialize %s\n", CONFIG_CRI_AES_NAME);
		status = -EIO;
		goto out1;
	}

	int n = *ptlen * 8;
	uint32_t ICV2 = 0xA65959A6;
	uint32_t padlen = 8 * ((*ptlen) * 8 + 63) / 64 - (*ptlen);

	if (n <= 64) {
		uint8_t *fr = state->scratch;
		size_t totallen = 0;
		memcpy(fr, &ICV2, sizeof(ICV2));
		fr += sizeof(ICV2);
		totallen += sizeof(ICV2);
		memset(fr, (*ptlen >> 24) & 0xff, 1);
		memset(fr + 1, (*ptlen >> 16) & 0xff, 1);
		memset(fr + 2, (*ptlen >> 8) & 0xff, 1);
		memset(fr + 3, (*ptlen >> 0) & 0xff, 1);
		fr += 4;
		totallen += 4;
		memcpy(fr, pt, *ptlen);
		fr += *ptlen;
		totallen += *ptlen;
		memset(fr, 0x00, padlen);
		totallen += padlen;

		dhexdump("In:", state->scratch, totallen);

		status = cri_aes_final(aes_engine, state->scratch, totallen, ct);
		if (status) {
			printk("Cannot final AES: %d\n", status);
			status = -EIO;
			goto out1;
		}
		*ctlen = totallen;
	} else {
		status = w_keywrap(state, aes_engine, ct, ctlen, pt, ptlen);
		if (status) {
			printk("Cannot final AES in keywrap: %d\n", status);
			status = -EIO;
			goto out1;
		}
	}

out1:
	cri_aes_close(aes_engine);
out:
	return status;
}

static int32_t kwp_ad(fips_state_t *state,
		uint8_t *pt, uint32_t *ptlen, uint8_t **ptstart,
		uint8_t *ct, uint32_t *ctlen)
{
	int32_t status;

	cri_aes_t aes_engine;

	aes_engine = cri_aes_open(0);
	if (!cri_is_valid(aes_engine)) {
		dprintk("Cannot open %s\n", CONFIG_CRI_AES_NAME);
		status = -EIO;
		goto out;
	}

#ifdef CONFIG_CMRT_AES_192BIT
	if ((state->key_length != 16) && (state->key_length != 24) && (state->key_length != 32)) {
#else
	if ((state->key_length != 16) && (state->key_length != 32)) {
#endif
		dprintk("The KEK has an inappropriate length %d\n", state->key_length);
		status = -EINVAL;
		goto out;
	}

	status = cri_aes_init(aes_engine, AES_DECRYPT, AES_ECB, state->key_value,
			state->key_length, NULL, 0, 0);
	if (status != 0) {
		dprintk("Cannot initialize %s\n", CONFIG_CRI_AES_NAME);
		goto out1;
	}

	uint32_t n = (*ctlen) / (AES_BLOCK_LENGTH / 2);
	uint32_t ICV2 = 0xA65959A6;
	if (n == 2) {
		status = cri_aes_final(aes_engine, ct, *ctlen, pt);
		*ptlen = *ctlen;
		if (status) {
			printk("Cannot final AES: %d\n", status);
			status = -EIO;
			goto out1;
		}
	} else {
		status = winv_keywrap(state, aes_engine, pt, ptlen, ct, ctlen);
		if (status) {
			printk("Cannot final AES in keywrap: %d\n", status);
			status = -EIO;
			goto out1;
		}
	}

	uint32_t *pt32;
	pt32 = (uint32_t *) pt;

	if (pt32[0] != ICV2) {
		dprintk("First word is not correct %08X, should be %08X\n", pt32[0], ICV2);
		status = -EIO;
		goto out1;
	}

	uint32_t Plen = (((uint32_t) pt[4]) << 24) | (((uint32_t) pt[5]) << 16)
			| (((uint32_t) pt[6]) << 8) | (((uint32_t) pt[7]) << 0);
	int32_t padlen = 8 * (n - 1) - Plen;
	dprintk("Plen; %d, padlen: %d\n", Plen, padlen);
	if ((padlen < 0) | (padlen > 7)) {
		dprintk("padlen is out of range:%d\n", padlen);
		status = -EIO;
		goto out1;
	}

	int errs = 0;
	for (int i = 0; i < padlen; i++) {
		if (pt[*ptlen - 1 - i] != 0x00)
			errs += 1;
	}
	if (errs != 0) {
		status = -EIO;
		goto out1;
	}

	*ptstart = pt + *ctlen - (n - 1) * SEMI_BLOCK;
	*ptlen = Plen;

out1:
	cri_aes_close(aes_engine);
out:
	return status;
}

static int32_t wp_decrypt_asset(fips_state_t *state, uint8_t *outbuffer, uint32_t *outlen,
		uint8_t **outstart, uint8_t *inbuffer, uint32_t *inlen)
{
	int32_t status;

	status = kwp_ad(state, outbuffer, outlen, outstart, inbuffer, inlen);
	if (status != 0) {
		goto out;
	}

out:
	return status;
}

static int32_t wp_encrypt_asset(fips_state_t *state, uint8_t *outbuffer, uint32_t *outlen,
		uint8_t *inbuffer, uint32_t *inlen)
{

	int32_t status;
	status = kwp_ae(state, outbuffer, outlen, inbuffer, inlen);
	if (status != 0) {
		goto out;
	}

out:
	return status;
}

int32_t fips_key_import_export(fips_state_t *state, teec_abi_invokecommand_t *h, uint8_t direction)
{
	int32_t status;

	uint8_t *wrap_key_asset = NULL;
	uint8_t *input_asset = NULL;
	uint8_t *output_asset = NULL;
	uint8_t *store_asset = NULL;
	uint8_t *pt_start = NULL;

	uint32_t wrap_key_asset_length = 0;
	uint32_t input_asset_length = 0;
	uint32_t output_asset_length = 0;
	uint32_t encryption_length = 0;
	uint32_t store_asset_length = 0;
	uint32_t total_overhead = 0;

	dprintk("FIPS_SERVICE_IMPORT/EXPORT_KEY\n");
	CHECK_COMMAND(FIPS_SERVICE_IMPORT_KEY);

	/* read wrap key asset */
	wrap_key_asset = (workcontext + sizeof(uint32_t));
	wrap_key_asset_length = GET_MAX_ASSET_SIZE();
	status = fips_read_asset_of_type_from_teefs(state,
			(fips_asset_identifier *) (h->params[0].memref.offset + SAC_MEMORY_BASE),
			h->params[0].memref.size, wrap_key_asset, &wrap_key_asset_length,
			FIPS_TYPE_WRAP_KEY);
	if (status) goto out;

	if (GET_ASSET_TYPE_FROM_ASSET(wrap_key_asset) != FIPS_TYPE_WRAP_KEY) {
		status = -EPERM;
		goto out;
	}

	state->key_length = GET_SECRET_KEY_LENGTH_FROM_ASSET(wrap_key_asset);
	state->key_value = GET_SECRET_KEY_FROM_ASSET(wrap_key_asset);

	/* read asset */
	input_asset = (uint8_t *)ALIGN_32_BIT_POINTER(wrap_key_asset + wrap_key_asset_length);
	input_asset_length = GET_MAX_ASSET_SIZE() + wrap_key_asset_length;
	switch (direction) {
	case FIPS_IMPORT:
		status = fips_read_asset_from_shared_memory(state, h, 1, input_asset, &input_asset_length);
		if (status) goto out;
		break;
	case FIPS_EXPORT:
		status = fips_read_asset_from_teefs(state,
				(fips_asset_identifier *) (h->params[1].memref.offset + SAC_MEMORY_BASE),
				h->params[1].memref.size, input_asset, &input_asset_length);
		if (status) goto out;

		/* Enforce asset to export as external */
		SET_ASSET_INTERNAL_FLAG_IN_ASSET(input_asset, FIPS_EXTERNAL_ASSET);
		break;
	default:
		status = -EINVAL;
		goto out;
	}

	state->scratch = (uint8_t *)ALIGN_32_BIT_POINTER(workcontext + wrap_key_asset_length + 3 * input_asset_length);

	/* encrypt/decrypt asset */
	fips_asset_type asset_type = GET_ASSET_TYPE_FROM_ASSET(input_asset);
	dprintk("encrypt/decrypt asset %s (%d)\n",
		fips_asset_type_str(asset_type), asset_type);
	total_overhead = 12 + asset_overhead[asset_type];
	output_asset = (uint8_t *)ALIGN_32_BIT_POINTER(input_asset + input_asset_length);

	if (input_asset_length <= total_overhead) {
		dprintk("input_asset_length:%u total_overhead:%u\n", input_asset_length, total_overhead);
		status = -EIO;
		goto out;
	}
	encryption_length = input_asset_length - total_overhead;

	dhexdump("Data to en/decrypt:", (uint8_t *) (input_asset + total_overhead), encryption_length);
	switch (direction) {
	case FIPS_IMPORT:
		output_asset_length = encryption_length;
		status = wp_decrypt_asset(state, output_asset, &output_asset_length, &pt_start,
				(uint8_t *) (input_asset + total_overhead), &encryption_length);
		dhexdump("Output:", (uint8_t *)output_asset, output_asset_length + 2 * sizeof(uint32_t));
		break;
	case FIPS_EXPORT:
		output_asset_length = encryption_length + 2 * sizeof(uint32_t);
		status = wp_encrypt_asset(state, output_asset, &output_asset_length,
				(uint8_t *) (input_asset + total_overhead), &encryption_length);
		dhexdump("Output:", (uint8_t *)output_asset, output_asset_length);
		break;
	}

	if (status != 0) {
		dprintk("En/decryption of the asset failed\n");
		status = -EIO;
		goto out;
	}

	/* write asset */
	store_asset = (uint8_t *)ALIGN_32_BIT_POINTER(output_asset + input_asset_length);
	memcpy(store_asset, input_asset, total_overhead);
	store_asset_length = total_overhead + output_asset_length;

	switch (direction) {
	case FIPS_IMPORT:
		memcpy(store_asset + total_overhead, output_asset + 2 * sizeof(uint32_t), output_asset_length);
		if (GET_SECRET_KEY_LENGTH_FROM_ASSET(input_asset) == (input_asset_length - total_overhead)) {
			SET_SECRET_KEY_LENGTH_IN_ASSET(store_asset, output_asset_length);
		}
		dhexdump("Store:", (uint8_t *)store_asset, store_asset_length);
		status = fips_write_asset_to_teefs(state,
			(fips_asset_identifier *) (h->params[2].memref.offset + SAC_MEMORY_BASE),
			h->params[2].memref.size, store_asset, store_asset_length);
		break;
	case FIPS_EXPORT:
		memcpy(store_asset + total_overhead, output_asset, output_asset_length);
		if (GET_SECRET_KEY_LENGTH_FROM_ASSET(input_asset) == (input_asset_length - total_overhead)) {
			SET_SECRET_KEY_LENGTH_IN_ASSET(store_asset, output_asset_length);
		}
		dhexdump("Store:", (uint8_t *)store_asset, store_asset_length);
		status = fips_write_to_shared_memory(store_asset, store_asset_length, h, 2);
		break;
	}

out:
	destroy_workcontext(status);
	return status;
}
