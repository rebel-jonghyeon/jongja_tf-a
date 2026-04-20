/*
 * Copyright (c) 2018-2024 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

#define DT_DRV_COMPAT rambus_cmrt_aes

#include <device.h>
#include <init.h>
#include <sys/sys_io.h>
#include <sys/byteorder.h>
#include <drivers/cmrt/dd.h>
#include <drivers/cmrt/aes.h>
#include <string.h>
#include <errno.h>
#include <assert.h>

#include "cipher_int.h"

#if defined(CONFIG_CMRT_ASIL_B_MODE) || defined(CONFIG_CMRT_FIPS_140_MODE)
#include "kat/aes_kat.h"
#endif

#define R_BASE DT_INST_REG_ADDR(0)
static_assert(R_BASE == CMRT_AES_BASE); /* device tree must match headers */

static uint32_t block_size(uint32_t ctrl)
{
	(void)ctrl;
	return AES_BLOCK_BYTES;
}

static uint32_t last_block(uint32_t inbytes)
{
	return (1UL << inbytes) - 1u;
}

static int get_taglen(uint32_t ctrl)
{
	int len = -1;
	int mode = (ctrl & AES_MODE_MASK) >> AES_MODE_SHIFT;
	if (mode == CMRT_AES_GCM || mode == CMRT_AES_CCM || mode == CMRT_AES_CMAC) {
		switch (ctrl & AES_TAG_LENGTH_MASK) {
		case AES_TAG_LENGTH_128:
			len = 128 / 8;
			break;
		case AES_TAG_LENGTH_120:
			len = 120 / 8;
			break;
		case AES_TAG_LENGTH_112:
			len = 112 / 8;
			break;
		case AES_TAG_LENGTH_104:
			len = 104 / 8;
			break;
		case AES_TAG_LENGTH_96:
			len = 96 / 8;
			break;
		case AES_TAG_LENGTH_64:
			len = 64 / 8;
			break;
		case AES_TAG_LENGTH_48:
			len = 48 / 8;
			break;
		case AES_TAG_LENGTH_32:
			len = 32 / 8;
			break;
		default:
			break;
		}
	}
	return len;
}

static const struct cmrt_cipher_io cipher_ctl = {
	.base_addr = R_BASE,
	.block_size = block_size,
	.last_block = last_block,
	.tag_len = get_taglen,
};

typedef struct cmrt_aes_context {
	struct cmrt_cipher_context ccc;
#if IS_ENABLED(CMRT_AES_HAS_XTS)
	/* Because we have a streaming API (update/final) we need to
	 * keep count of the processed blocks in XTS mode.
	 */
	uint32_t num_blocks;
	/* A hardware implementation detail of XTS requires saving the
	 * original tweak.
	 */
	uint32_t orig_tweak[AES_BLOCK_WORDS];
#endif
	cmrt_aes_mode_t mode;
} cmrt_aes_context_t;

#define AES_CONTEXTS 1 /* only one active at a time */
CMRT_DD_CONTEXT static cmrt_aes_context_t aes_contexts[AES_CONTEXTS];

static uint32_t aes_make_control(cmrt_aes_operation_t operation, cmrt_aes_mode_t mode, size_t keylen, size_t taglen)
{
	if ((operation != CMRT_AES_ENCRYPT) && (operation != CMRT_AES_DECRYPT)) {
		return (uint32_t)-1;
	}
	uint32_t control = (uint32_t)operation << AES_OPERATION_SHIFT;

#if IS_ENABLED(CMRT_AES_HAS_XTS)
	if (mode == CMRT_AES_XTS) {
		/* XTS uses two keys, but the HW needs to be
		 * programmed for the size of a single key.
		 */
		keylen /= 2;
	}
#endif
	switch (keylen) {
	case 16:
		control |= AES_KEY_SIZE_128;
		break;
#if IS_ENABLED(CMRT_AES_HAS_192)
	case 24:
		control |= AES_KEY_SIZE_192;
		break;
#endif
	case 32:
		control |= AES_KEY_SIZE_256;
		break;
	default:
		goto out;
	}
	switch (mode) {
	case CMRT_AES_ECB:
	case CMRT_AES_CBC:
	case CMRT_AES_CFB:
	case CMRT_AES_CTR:
	case CMRT_AES_GCM:
#if IS_ENABLED(CMRT_AES_HAS_CCM)
	case CMRT_AES_CCM:
#endif
#if IS_ENABLED(CMRT_AES_HAS_XTS)
	case CMRT_AES_XTS:
#endif
#if IS_ENABLED(CMRT_AES_HAS_CMAC)
	case CMRT_AES_CMAC:
#endif
		control |= (uint32_t)mode << AES_MODE_SHIFT;
		break;
	default:
		goto out;
	}
	/* tag length can be specified in cmac, ccm and gcm encrypt */
	bool is_gcm = (mode == CMRT_AES_GCM);
	bool is_ccm = (mode == CMRT_AES_CCM);
	bool is_cmac = (mode == CMRT_AES_CMAC);
	if (is_gcm || is_cmac || is_ccm) {
		uint32_t tag_ctl;
		switch (taglen) {
		case 16:
			tag_ctl = AES_TAG_LENGTH_128;
			break;
		case 15:
			tag_ctl = AES_TAG_LENGTH_120;
			break;
		case 14:
			tag_ctl = AES_TAG_LENGTH_112;
			break;
		case 13:
			tag_ctl = AES_TAG_LENGTH_104;
			break;
		case 12:
			tag_ctl = AES_TAG_LENGTH_96;
			break;
		case 8:
			tag_ctl = AES_TAG_LENGTH_64;
			break;
		case 6:
			tag_ctl = AES_TAG_LENGTH_48;
			break;
		case 4:
			tag_ctl = AES_TAG_LENGTH_32;
			break;
		default:
			goto out;
		}
		bool gcm_cmac_tag_ok = ((is_gcm || is_cmac) && taglen >= 12 && taglen <= 16);
		bool ccm_tag_ok = (is_ccm && (taglen == 16 || taglen == 14 || taglen == 12 ||
					      taglen == 8 || taglen == 6 || taglen == 4));
		bool tag_ok = (gcm_cmac_tag_ok || ccm_tag_ok);
		if (!tag_ok) {
			goto out;
		}
		control |= tag_ctl;
	}
	return control;
 out:
	return (uint32_t)-1;
}

#ifdef CONFIG_CMRT_KDC
int z_impl_cmrt_aes_kdc_cmd(cmrt_aes_t context, cmrt_aes_operation_t operation, cmrt_aes_mode_t mode, size_t keylen, size_t taglen, cmrt_kdc_cmd_t *cmd)
{
	size_t kl = keylen;
#if IS_ENABLED(CMRT_AES_HAS_XTS)
	if (mode == CMRT_AES_XTS) {
		kl /= 2u;
	}
#endif
	if (!cmrt_dd_valid(context) ||
	    (cmd == NULL) || ((kl != 16u) && (kl != 32u))) {
		return -EINVAL;
	}
	uint32_t control = aes_make_control(operation, mode, keylen, taglen);
	if ((int)control == -1) { return -EINVAL; }
	if ((context->ccc.ddc.flags & CMRT_O_HWC_KEYED) == 0u) {
		/* Invalid context for KDC operation. */
		return -EFAULT;
	}
	cmd->command0 = control;
	cmd->command1 = HWC_LOCK_MASTER_CPU;
	cmd->dest = KDC_DEST_AES;
	cmd->key_size = (keylen == 16u) ? KDC_SIZE_128 : KDC_SIZE_256;
	return 0;
}

int cmrt_aes_load_kdc_key(cmrt_aes_t context, cmrt_kdc_t kdc, cmrt_kdc_cmd_t *cmd)
{
	/* Needs keyed mode */
	if ((context->ccc.ddc.flags & CMRT_O_HWC_KEYED) == 0u) {
		return -EFAULT;
	}

	int rc;
	if ((cmd->command0 & AES_MODE_MASK) == AES_MODE_XTS &&
	    (cmd->command0 & AES_KEY_SIZE_MASK) == AES_KEY_SIZE_256) {
		/*
		 * We need to do an extra key derivation, so let's
		 * copy the command and:
		 * - modify COMMAND1 to retain lock for KDC
		 * - invert the first byte of diversify path to ensure
		 *   different subkeys
		 */
		cmrt_kdc_cmd_t cmd0;
		(void)memcpy(&cmd0, cmd, sizeof(cmd0));
		cmd0.command1 = HWC_LOCK_MASTER_KDC;
		cmd0.diversify_path[0] ^= 0xffU;
		rc = cmrt_kdc_derive_key(kdc, &cmd0);
		if (rc != 0) {
			goto out;
		}
		rc = cmrt_kdc_sync(kdc);
		if (rc != 0) {
			goto out;
		}
	}
	rc = cmrt_kdc_derive_key(kdc, cmd);
	if (rc != 0) {
		goto out;
	}
	rc = cmrt_kdc_sync(kdc);
	if (rc != 0) {
		goto out;
	}
out:
	return rc;
}
#endif	/* CONFIG_CMRT_KDC */

int z_impl_cmrt_aes_init(cmrt_aes_t context, cmrt_aes_operation_t operation, cmrt_aes_mode_t mode, const void *key, size_t keylen, const void *iv, size_t ivlen, size_t taglen)
{
	int rc = -EINVAL;

	if (!cmrt_dd_valid(context) || !is_aligned(key, 4u) || !is_aligned(iv, 4u)) { return -EINVAL; }

	if (((ivlen != 0u)) && ((mode == CMRT_AES_ECB) || (iv == NULL))) {
		return -EINVAL;
	}

	if ((keylen != 0u) && (key == NULL)) {
		return -EINVAL;
	}

	if ((taglen != 0u) && ((mode != CMRT_AES_CCM) && (mode != CMRT_AES_GCM) && (mode != CMRT_AES_CMAC))) {
		return -EINVAL;
	}

	uint32_t status = cmrt_core_status(R_BASE) & HWC_STATUS_STATUS_MASK;
	if (keylen != 0u) {
		if (status != HWC_STATUS_IDLE_LOCKED) {
			if (cmrt_dd_flush((cmrt_dd_context_t *)context) != 0) {
				return -EIO;
			}
		}
	} else {
		if (status != CIPHER_STATUS_IDLE_WITH_KEY) {
			return -EIO;
		}
	}

	cmrt_dd_t *dd = context->ccc.ddc.dd;
	uint32_t mask = cmrt_dd_lock(dd);

	context->ccc.flags = 0;
	if (keylen != 0u) {
#if IS_ENABLED(CMRT_AES_HAS_XTS)
		uint8_t keyswap[512 / 8];
		if (mode == CMRT_AES_XTS) {
			/* The AES core expects the two XTS keys in
			 * Key2 || Key1 order.  Key1 != Key2.
			 */
			if (keylen > sizeof(keyswap)) {
				goto out;
			}
			size_t hlen = keylen / 2;
			uint8_t *key2 = (uint8_t *)key + hlen;
			memcpy(keyswap, key2, hlen);
			memcpy(keyswap + hlen, (uint8_t *)key, hlen);
			if (memcmp(keyswap, keyswap + hlen, hlen) == 0) {
				rc = -EINVAL;
				goto out;
			}
			key = keyswap;
		}
#endif
		uint32_t control = aes_make_control(operation, mode,
						    keylen, taglen);
		if (control == (uint32_t)-1) { goto out; }
		sys_write32(control | CIPHER_CMD_INIT, R_BASE + R_CORE_CONTROL);
		rc = cipher_load_key(&context->ccc, key, keylen);
		if (rc != 0) { goto out; }
	}
	if (mode == CMRT_AES_CMAC) {
		context->ccc.flags = (uint32_t)CIPHER_SKIP_LAST_BLOCK;
	} else if (mode == CMRT_AES_CCM) {
		context->ccc.flags = (uint32_t)CIPHER_SKIP_EMPTY_LAST_BLOCK;
	}

#if IS_ENABLED(CMRT_AES_HAS_XTS)
	context->num_blocks = 0;
	if (mode == CMRT_AES_XTS) {
		/* XTS requires a tweak (passed as the IV). */
		if (iv == NULL || ivlen != AES_BLOCK_BYTES) {
			rc = -EINVAL;
			goto out;
		}
		/* Save original tweak for XTS. */
		memcpy(context->orig_tweak, iv, AES_BLOCK_BYTES);
	}
#endif
	if (ivlen != 0) {
		rc = cipher_load_iv(&context->ccc, ivlen, iv, AES_BLOCK_BYTES);
		if (rc != 0) { goto out; }
	}
	status = CIPHER_STATUS_IDLE_WITH_KEY;
	rc = cmrt_wait_status_to(R_BASE, &status, 1);

	context->mode = mode;

	if ((keylen == 0) && (ivlen == 0)) {
		/* We end up here due to either a KDC derived key, or,
		 * a reinit after a previously finished operation,
		 * which can be either a final encrypt/decrypt, or
		 * final AAD. Force initialization by rewriting the
		 * next control word.
		 */
		context->ccc.force_cmd = true;
	}
out:
	cmrt_dd_unlock(dd, mask);
	return rc;
}

static cmrt_dd_t aes_dd = {
	.base = CMRT_AES_BASE,
	.is_locking = 1,
	.context_count = AES_CONTEXTS,
	.context_size = sizeof(cmrt_aes_context_t),
	.irq_mask = 0,
	.contexts = aes_contexts,
};

#if IS_ENABLED(CMRT_AES_HAS_XTS)
static void aes_close_cb(cmrt_dd_context_t *context)
{
	cmrt_aes_t aes = (void *)context;
	memset(&aes->num_blocks, 0,
	       sizeof(struct cmrt_aes_context)
	       - offsetof(struct cmrt_aes_context, num_blocks));
}
#endif

static int aes_open_cb(cmrt_dd_context_t *ddc, void *arg)
{
	ARG_UNUSED(arg);
	cmrt_aes_t aes = (cmrt_aes_t)ddc;
	aes->ccc.cio = &cipher_ctl;
	return 0;
}

static const struct cmrt_driver_api aes_driver_api = {
	.open_cb = aes_open_cb,
#if defined(CONFIG_CMRT_ASIL_B_MODE) || defined(CONFIG_CMRT_FIPS_140_MODE)
	.open_kat = aes_open_kat,
#endif
	.find_cb = NULL,
	.poll_cb = NULL,
	.sync_cb = NULL,
#if IS_ENABLED(CMRT_AES_HAS_XTS)
	.close_cb = aes_close_cb,
#else
	.close_cb = NULL,
#endif
};

DEVICE_DT_INST_DEFINE(0, cmrt_dev_init, NULL, &aes_dd, NULL,
		      PRE_KERNEL_1, CONFIG_KERNEL_INIT_PRIORITY_DEVICE,
		      &aes_driver_api);

#if defined(CONFIG_CMRT_ASIL_B_MODE) || defined(CONFIG_CMRT_FIPS_140_MODE)
SYS_INIT(aes_init_kat, POST_KERNEL, CONFIG_APPLICATION_INIT_PRIORITY);
#endif

cmrt_aes_t z_impl_cmrt_aes_open(uint32_t flags)
{
	return (cmrt_aes_t)cmrt_dd_open(DEVICE_DT_INST_GET(0), flags, NULL);
}

void z_impl_cmrt_aes_close(cmrt_aes_t context)
{
	if (cmrt_dd_valid(context)) {
		cmrt_dd_close((cmrt_dd_context_t *)context);
	}
}

int z_impl_cmrt_aes_update(cmrt_aes_t context, const void *input, size_t inlen, void *output)
{
#if IS_ENABLED(CMRT_AES_HAS_XTS)
	/* Keep track how many blocks have been processed, it is
	 * needed at decryption in XTS mode.
	 */
	if (cmrt_dd_valid(context)) {
		context->num_blocks += inlen / AES_BLOCK_BYTES;
	}
#endif
	return cipher_update((cmrt_cipher_t)context, input, inlen, output);
}

int z_impl_cmrt_aes_update_aad(cmrt_aes_t context, const void *aad, size_t aadlen)
{
	return cipher_update_aad((cmrt_cipher_t)context, aad, aadlen, false);
}

int z_impl_cmrt_aes_final_aad(cmrt_aes_t context, const void *aad, size_t aadlen)
{
	return cipher_update_aad((cmrt_cipher_t)context, aad, aadlen, true);
}

#if IS_ENABLED(CMRT_AES_HAS_XTS)
static int cmrt_aes_xts_load_j(cmrt_aes_t aes, uint32_t j)
{
	uint32_t status = CIPHER_STATUS_IDLE_WITH_KEY;
	int rc = cmrt_wait_status_to(R_BASE, &status, 1);
	if (rc != 0) { return rc; }

	/* The XTS-AES specification allows at most 2^20 blocks in a
	 * single data unit.
	 */
	if (j > AES_XTS_MAX_J) {
		return -EINVAL;
	}
	/* HW expects the J value aligned to the MSB. */
	j = sys_cpu_to_be32(j << 12);
	(void)cipher_set_command(&aes->ccc, AES_CMD_LOAD_J);
	cmrt_cio_t ctl = aes->ccc.cio;
	return cmrt_cipher_copy(ctl, &j, 4, NULL, false, true);
}

static int cmrt_aes_xts_final(cmrt_aes_t context, const void *input, size_t inlen, void *output)
{
	if (!cmrt_dd_valid(context)) { return -EINVAL; }

	int rc = 0;
	uint32_t status = CIPHER_STATUS_IDLE_WITH_KEY;

	cmrt_dd_t *dd = context->ccc.ddc.dd;
	uint32_t mask = cmrt_dd_lock(dd);
	cmrt_cio_t ctl = context->ccc.cio;

	if ((inlen % AES_BLOCK_BYTES) == 0u) {
		/* If the input length is a multiple of the blocksize,
		 * then we don't need to do ciphertext stealing.
		 * Nevertheless, we cannot call cipher_final()
		 * directly because it sets LAST_BLOCK, which has
		 * special effects in XTS mode (it regresses the
		 * tweak).  Therefore we issue an explicit INIT after
		 * the operation.
		 */
		(void)cipher_set_command(&context->ccc, CIPHER_CMD_ENC_DEC);
		rc = cmrt_cipher_copy(ctl, input, inlen, output, false, false);
		if (rc != 0) {
			goto out;
		}
		(void)cipher_set_command(&context->ccc, CIPHER_CMD_INIT);
		goto out;
	}

	/* Ciphertext stealing requires that we get at least a full
	 * block of data.
	 */
	if (inlen <= AES_BLOCK_BYTES) {
		rc = -EINVAL;
		goto out;
	}

	/* See the figures and notation in IEEE Std 1619.  They help
	 * in understanding the mechanism and the terms are used in
	 * the comments below.
	 */
	size_t remainder = inlen % AES_BLOCK_BYTES;
	size_t fulls = inlen - remainder;
	uint32_t control = sys_read32(R_BASE + R_CORE_CONTROL);
	if ((control & CIPHER_OPERATION_MASK) == CIPHER_OPERATION_ENCRYPT) {
		/* Encrypt blocks before the last as a normal
		 * "non-final" update and then steal ciphertext from
		 * the previous-to-last block to pad the final, uneven
		 * block.
		 */
		(void)cipher_set_command(&context->ccc, CIPHER_CMD_ENC_DEC);
		rc = cmrt_cipher_copy(ctl, input, fulls, output, false, false);
		if (rc != 0) {
			goto out;
		}

		/* Copy the previous-to-last output block to temp:
		 *
		 * PP = CC
		 */
		uint32_t pp[AES_BLOCK_WORDS];
		memcpy(pp, (uint8_t *)output + fulls - AES_BLOCK_BYTES, AES_BLOCK_BYTES);

		/* Overwrite with partial last plaintext block at beginning:
		 *
		 * PP = P_m || CP
		 */
		memcpy(pp, (uint8_t *)input + fulls, remainder);

		/* Encrypt the last block PP in-place.
		 *
		 * C_m-1 = XTS-AES-blockEnc(PP)
		 */
		(void)cipher_set_command(&context->ccc, CIPHER_CMD_ENC_DEC);
		rc = cmrt_cipher_copy(ctl, pp, AES_BLOCK_BYTES, pp, true, false);
		if (rc != 0) {
			goto out;
		}
		/* Copy the start of partial C_m to the end of output. */
		memcpy((uint8_t *)output + fulls, (uint8_t *)output + fulls - AES_BLOCK_BYTES, remainder);
		/* Copy C_m-1 to the previous-to-last output block. */
		memcpy((uint8_t *)output + fulls - AES_BLOCK_BYTES, pp, AES_BLOCK_BYTES);
	} else {
		/* Decrypt normally until C_m-2, so we get fulls == 16
		 * and remainder < 16.
		 */
		if (fulls >= 2 * AES_BLOCK_BYTES) {
			(void)cipher_set_command(&context->ccc,
						 CIPHER_CMD_ENC_DEC);
			rc = cmrt_cipher_copy(ctl, input, fulls - AES_BLOCK_BYTES,
					      output, false, false);
			if (rc != 0) {
				goto out;
			}
			context->num_blocks += (fulls - AES_BLOCK_BYTES) / AES_BLOCK_BYTES;
		}

		/* The previous-to-last block must be decrypted using
		 * the tweak from the last block (j == m).  To skip
		 * over j == m-1, we decrypt a dummy block.
		 *
		 * XTS-AES-blockDec(dummy, tweak, m-1)
		 */
		uint32_t pp[AES_BLOCK_WORDS];
		(void)cipher_set_command(&context->ccc, CIPHER_CMD_ENC_DEC);
		rc = cmrt_cipher_copy(ctl, pp, AES_BLOCK_BYTES, pp, false, false);
		if (rc != 0) {
			goto out;
		}

		/* Decrypt the previous-to-last block.
		 *
		 * PP = XTS-AES-blockDec(C_m-1, tweak, m)
		 */
		(void)cipher_set_command(&context->ccc, CIPHER_CMD_ENC_DEC);
		rc = cmrt_cipher_copy(ctl, (uint32_t *)((uint8_t *)input + fulls - AES_BLOCK_BYTES), AES_BLOCK_BYTES, pp, false, false);
		if (rc != 0) {
			goto out;
		}

		/* Copy P_m as the final (partial) block in the
		 * output.
		 *
		 * Save the last partial input block, in case the
		 * input and buffers are the same, since the copy
		 * would then overwrite.
		 */
		uint32_t input_last_partial[AES_BLOCK_WORDS];
		memcpy(input_last_partial, (uint8_t *)input + fulls, remainder);
		memcpy((uint8_t *)output + fulls, pp, remainder);

		/* Copy over the ciphertext of the last partial block
		 * into the previously decrypted block.
		 *
		 * CC = C_m || CP
		 */
		memcpy(pp, input_last_partial, remainder);

		/* Finally, we can decrypt the last block into the
		 * place of the previous-to-last block in the output
		 * (swapping).
		 *
		 * P_m-1 = XTS-AES-blockDec(CC, tweak, m-1)
		 */
		(void)cipher_set_command(&context->ccc, CIPHER_CMD_ENC_DEC);
		rc = cmrt_cipher_copy(ctl, pp, AES_BLOCK_BYTES,
				      (uint32_t *)((uint8_t *)output + fulls - AES_BLOCK_BYTES),
				      true, false);
		if (rc != 0) {
			goto out;
		}
	}
out:
	rc = cmrt_wait_status_to(R_BASE, &status, 1);
	cmrt_dd_unlock(dd, mask);
	return rc;
}

int z_impl_cmrt_aes_xts_set_offset(cmrt_aes_t context, uint32_t offset)
{
	if (!cmrt_dd_valid(context) || !is_aligned(offset, AES_BLOCK_BYTES)) {
		return -EINVAL;
	}
	uint32_t control = sys_read32(R_BASE + R_CORE_CONTROL);
	if ((control & AES_MODE_MASK) != AES_MODE_XTS) {
		return -ENOTSUP;
	}
	return cmrt_aes_xts_load_j(context, offset / AES_BLOCK_BYTES);
}
#endif

int z_impl_cmrt_aes_final(cmrt_aes_t context, const void *input, size_t inlen, void *output)
{
	if (!cmrt_dd_valid(context)) {
		return -EINVAL;
	}
#if IS_ENABLED(CMRT_AES_HAS_XTS)
	if (context->mode == CMRT_AES_XTS) {
		int rc = cmrt_aes_xts_final(context, input, inlen, output);
		/* Reset the block count after final input. */
		context->num_blocks = 0;
		return rc;
	}
#endif
	return cipher_final((cmrt_cipher_t)context, input, inlen, output);
}

static bool hastag(cmrt_aes_mode_t mode)
{
	return (mode == CMRT_AES_GCM) || (mode == CMRT_AES_CCM)
		|| (mode == CMRT_AES_CMAC);
}

int z_impl_cmrt_aes_ae_final(cmrt_aes_t context, const void *input, size_t inlen, void *output, void *tag, size_t *taglen)
{
	int ret = -EFAULT; /* non-authenticated */
	if (hastag(context->mode)) {
		ret = cipher_ae_final((cmrt_cipher_t)context, input, inlen,
				      output, tag, taglen);
		if ((ret < 0) && (output != NULL)) {
			/* clear output on tag check failure */
			memset(output, 0, inlen);
		}
	}
	return ret;
}


#if IS_ENABLED(CMRT_AES_HAS_CCM)
int z_impl_cmrt_aes_ccm_encode_nonce(void *buf, size_t buflen, const void *nonce, size_t noncelen, size_t ptlen, size_t taglen, int hasaad)
{
	if (((uintptr_t)buf & 0x3u) != 0u) {
		return -1;
	}
	if (buflen < 16) {
		return -1;
	}
	/* 2 <= L <= 8 implies 7 <= noncelen <= 13 */
	if (noncelen < 7 || noncelen > 13) {
		return -1;
	}
	/* tag length can be an even value in [4, 16] */
	if ((taglen & 1) != 0 || taglen < 4 || taglen > 16) {
		return -1;
	}
	hasaad &= 1;

	int L = 15 - noncelen;
	int M = taglen;
	/* flags uses up to 8 bits, with proof in RFC3610 2.2 */
	int flags = 64 * hasaad + 8 * (M - 2) / 2 + L - 1;
	uint8_t *b0 = buf;
	const uint8_t *iv = nonce;

	b0[0] = (uint8_t)flags;
	for (int i = 1; i <= 15 - L; i++) {
		b0[i] = iv[i - 1];
	}
	for (int i = 15; i >= 16 - L; i--) {
		b0[i] = ptlen & 0xFF;
		ptlen >>= 8;
	}

	return 16;
}

int z_impl_cmrt_aes_ccm_encode_aad(void *buf, size_t buflen, const void *aad, size_t aadlen)
{
	if (((uintptr_t)buf & 0x3u) != 0u) {
		return -1;
	}
	if (aadlen == 0) {
		return 0;
	}

	size_t offset;
	uint8_t bi[6];

	if (aadlen < 65280) { /* 2^16-2^8 */
		if (buflen < 2u + aadlen) {
			return -1;
		}
		bi[0] = (aadlen >> 8) & 0xff;
		bi[1] = aadlen & 0xff;
		offset = 2;
	} else {
		if (buflen < 6u + aadlen) {
			return -1;
		}
		bi[0] = 0xff;
		bi[1] = 0xfe;
		bi[2] = (aadlen >> 24) & 0xff;
		bi[3] = (aadlen >> 16) & 0xff;
		bi[4] = (aadlen >> 8) & 0xff;
		bi[5] = aadlen & 0xff;
		offset = 6;
	}

	memmove((uint8_t*)buf + offset, aad, aadlen);
	memcpy((uint8_t*)buf, bi, offset);
	offset += aadlen;
	return offset;
}
#endif

#ifdef CONFIG_USERSPACE
#include <syscall_handler.h>

static inline void z_syscall_verify_aes_context(cmrt_aes_t context)
{
	cmrt_dd_syscall_verify((cmrt_dd_context_t *)context, &aes_driver_api);
}

static inline cmrt_aes_t z_vrfy_cmrt_aes_open(uint32_t flags)
{
	return z_impl_cmrt_aes_open(flags);
}
#include <syscalls/cmrt_aes_open_mrsh.c>

static inline void z_vrfy_cmrt_aes_close(cmrt_aes_t context)
{
	z_syscall_verify_aes_context(context);
	z_impl_cmrt_aes_close(context);
}
#include <syscalls/cmrt_aes_close_mrsh.c>

static inline int z_vrfy_cmrt_aes_kdc_cmd(cmrt_aes_t context, cmrt_aes_operation_t operation, cmrt_aes_mode_t mode, size_t keylen, size_t taglen, cmrt_kdc_cmd_t *cmd)
{
	z_syscall_verify_aes_context(context);
	Z_OOPS(Z_SYSCALL_MEMORY_WRITE(cmd, sizeof(*cmd)));
	return z_impl_cmrt_aes_kdc_cmd(context, operation, mode, keylen, taglen, cmd);
}
#include <syscalls/cmrt_aes_kdc_cmd_mrsh.c>

static inline int z_vrfy_cmrt_aes_init(cmrt_aes_t context, cmrt_aes_operation_t operation, cmrt_aes_mode_t mode, const void *key, size_t keylen, const void *iv, size_t ivlen, size_t taglen)
{
	z_syscall_verify_aes_context(context);
	Z_OOPS(Z_SYSCALL_MEMORY_READ(key, keylen));
	Z_OOPS(Z_SYSCALL_MEMORY_READ(iv, ivlen));
	return z_impl_cmrt_aes_init(context, operation, mode, key, keylen, iv, ivlen, taglen);
}
#include <syscalls/cmrt_aes_init_mrsh.c>

static inline int z_vrfy_cmrt_aes_xts_set_offset(cmrt_aes_t context, uint32_t offset)
{
	z_syscall_verify_aes_context(context);
	return z_impl_cmrt_aes_xts_set_offset(context, offset);
}
#include <syscalls/cmrt_aes_xts_set_offset_mrsh.c>

static inline int z_vrfy_cmrt_aes_update(cmrt_aes_t context, const void *input, size_t inlen, void *output)
{
	z_syscall_verify_aes_context(context);
	Z_OOPS(Z_SYSCALL_MEMORY_READ(input, inlen));
	Z_OOPS(Z_SYSCALL_MEMORY_WRITE(output, inlen));
	return z_impl_cmrt_aes_update(context, input, inlen, output);
}
#include <syscalls/cmrt_aes_update_mrsh.c>

static inline int z_vrfy_cmrt_aes_update_aad(cmrt_aes_t context, const void *aad, size_t aadlen)
{
	z_syscall_verify_aes_context(context);
	Z_OOPS(Z_SYSCALL_MEMORY_READ(aad, aadlen));
	return z_impl_cmrt_aes_update_aad(context, aad, aadlen);
}
#include <syscalls/cmrt_aes_update_aad_mrsh.c>

static inline int z_vrfy_cmrt_aes_final_aad(cmrt_aes_t context, const void *aad, size_t aadlen)
{
	z_syscall_verify_aes_context(context);
	Z_OOPS(Z_SYSCALL_MEMORY_READ(aad, aadlen));
	return z_impl_cmrt_aes_final_aad(context, aad, aadlen);
}
#include <syscalls/cmrt_aes_final_aad_mrsh.c>

static inline int z_vrfy_cmrt_aes_final(cmrt_aes_t context, const void *input, size_t inlen, void *output)
{
	z_syscall_verify_aes_context(context);
	Z_OOPS(Z_SYSCALL_MEMORY_READ(input, inlen));
	Z_OOPS(Z_SYSCALL_MEMORY_WRITE(output, inlen));
	return z_impl_cmrt_aes_final(context, input, inlen, output);
}
#include <syscalls/cmrt_aes_final_mrsh.c>

static inline int z_vrfy_cmrt_aes_ae_final(cmrt_aes_t context, const void *input, size_t inlen, void *output, void *tag, size_t *taglen)
{
	z_syscall_verify_aes_context(context);
	Z_OOPS(Z_SYSCALL_MEMORY_READ(input, inlen));
	Z_OOPS(Z_SYSCALL_MEMORY_WRITE(output, inlen));
	Z_OOPS(Z_SYSCALL_MEMORY_WRITE(tag, *taglen));
	Z_OOPS(Z_SYSCALL_MEMORY_WRITE(taglen, sizeof(*taglen)));
	return z_impl_cmrt_aes_ae_final(context, input, inlen, output, tag, taglen);
}
#include <syscalls/cmrt_aes_ae_final_mrsh.c>

static inline int z_vrfy_cmrt_aes_ccm_encode_nonce(void *buf, size_t buflen, const void *nonce, size_t noncelen, size_t ptlen, size_t taglen, int hasaad)
{
	Z_OOPS(Z_SYSCALL_MEMORY_WRITE(buf, buflen));
	Z_OOPS(Z_SYSCALL_MEMORY_READ(nonce, noncelen));
	return z_impl_cmrt_aes_ccm_encode_nonce(buf, buflen, nonce, noncelen, ptlen, taglen, hasaad);
}
#include <syscalls/cmrt_aes_ccm_encode_nonce_mrsh.c>

static inline int z_vrfy_cmrt_aes_ccm_encode_aad(void *buf, size_t buflen, const void *aad, size_t aadlen)
{
	Z_OOPS(Z_SYSCALL_MEMORY_WRITE(buf, buflen));
	Z_OOPS(Z_SYSCALL_MEMORY_READ(aad, aadlen));
	return z_impl_cmrt_aes_ccm_encode_aad(buf, buflen, aad, aadlen);
}
#include <syscalls/cmrt_aes_ccm_encode_aad_mrsh.c>

#endif /* CONFIG_USERSPACE */
