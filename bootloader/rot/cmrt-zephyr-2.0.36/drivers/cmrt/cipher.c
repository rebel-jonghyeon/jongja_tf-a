/*
 * Copyright (c) 2018-2023 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

#include <stdalign.h>
#include <device.h>
#include <sys/sys_io.h>
#include <drivers/cmrt/dd.h>
#include <drivers/cmrt/sac.h>
#include <cipher_reg.h>
#if CONFIG_CMRT_DMAC_THRESHOLD > 0
#include <drivers/cmrt/dmac.h>
#include "dmac_int.h"
#endif
#include <string.h>
#include <errno.h>
#include "cipher_int.h"

#define CIPHER_IV_MAX 64UL

static uint32_t cipher_status(uint32_t base_addr, uint32_t *inwords, uint32_t *outwords)
{
	uint32_t status = cmrt_core_status(base_addr);
	*inwords = (status & HWC_STATUS_INWORDS_MASK) >> HWC_STATUS_INWORDS_SHIFT;
	*outwords = (status & HWC_STATUS_OUTWORDS_MASK) >> HWC_STATUS_OUTWORDS_SHIFT;
	return status & HWC_STATUS_STATUS_MASK;
}

int cmrt_cipher_copy(cmrt_cio_t ctl, const uint32_t *input, size_t len,
		     uint32_t *output, bool is_final, bool setup)
{
	uint32_t control = sys_read32((mm_reg_t)(ctl->base_addr + R_CORE_CONTROL));
	uint32_t block_size = ctl->block_size(control);
	if (block_size == 0u ||
	    !is_in_4gb((uintptr_t)input, len) ||
	    !is_in_4gb((uintptr_t)output, len)) {
		return -EINVAL;
	}
	uint32_t block_words = block_size / 4u;
	bool final_fix = (len & (block_size - 1u)) == 0u &&
		is_final && len >= block_size;

	if (final_fix) {
		/*
		 * In case we are copying aad data the last block must
		 * come with last block command. We cannot copy the data and
		 * write a null last block, that will raise an error.
		 * See key_fix in HC, this is similar. There's no harm in
		 * doing the same for all final input, in fact, it is better
		 * this way not having to feed additional zeros.
		 */
		len -= block_size;
	}
#if CONFIG_CMRT_DMAC_THRESHOLD > 0
	if (len >= (uint32_t)CONFIG_CMRT_DMAC_THRESHOLD) {
		int rc = 0;
		if (setup) {
			/* Use DMAC data descriptor for aad, key, etc. */
			if (input != NULL) {
				rc = cmrt_dmac_helper(0, (uint32_t)input, ctl->base_addr, len, block_size, 0);
			} else {
				rc = cmrt_dmac_helper(0, ctl->base_addr, (uint32_t)output, len, block_size, 0);
			}
		} else {
			/* Normal operation uses DMAC crypto descriptor. */
			rc = cmrt_dmac_helper(ctl->base_addr, (uint32_t)input, (uint32_t)output, len, block_size, 0);
		}
		if (rc < 0) { return rc; }
		size_t done = len - (size_t)rc;
		if (input != NULL) {
			input += done >> 2;
		}
		if (output != NULL) {
			output += done >> 2;
		}
		len = (size_t)rc;
	}
#endif
	/* Full blocks first if possible. */
	size_t inlen = (input != NULL) ? len : 0u;
	size_t outlen = (output != NULL) ? len : 0u;

	uint32_t inwords, outwords;
	while (inlen >= block_size || outlen >= block_size) {
		uint32_t status = cipher_status(ctl->base_addr, &inwords, &outwords);
		if (IS_HWC_ERROR(status)) { return -EIO; }
		if (inlen >= block_size && inwords >= block_words) {
			for (uint32_t i = 0; i < block_words; ++i) {
				uint32_t word = cmrt_read32(input++);
				sys_write32(word, (mm_reg_t)(ctl->base_addr + R_CORE_INPUT));
			}
			inlen -= block_words * 4u;
		}
		if ((output != NULL) && outlen >= block_size && outwords >= block_words) {
			for (uint32_t i = 0; i < block_words; ++i) {
				uint32_t word = sys_read32((mm_reg_t)(ctl->base_addr + R_CORE_OUTPUT));
				cmrt_write32(word, output++);
			}
			outlen -= block_words * 4u;
		}
	}

	if (is_final) {
		if (final_fix) { /* see above */
			if (input != NULL) { inlen = block_size; }
			if (output != NULL) { outlen = block_size; }
		}
		uint32_t byte_select = (ctl->last_block != NULL) ? ctl->last_block(inlen) : inlen;
		sys_write32(CIPHER_LAST_BLOCK_IS_LAST | byte_select,
			    (mm_reg_t)(ctl->base_addr + R_CORE_LAST_BLOCK));
	}

	/* Rest of the data one word at a time. */
	while (true) {
		uint32_t status = cipher_status(ctl->base_addr, &inwords, &outwords);
		if (IS_HWC_ERROR(status) ||
		    status == HWC_STATUS_UNAVAILABLE) { return -EIO; }
		/* We may read/write null data below to keep the core happy. */
		if ((inlen != 0u || is_final || setup) && inwords != 0u) {
			uint32_t word = inlen != 0u ? cmrt_read32(input++) : 0u;
			if (inlen < sizeof(uint32_t)) {
				word &= ((1UL << (inlen * 8u)) - 1u);
				inlen = 0;
			} else { inlen -= sizeof(uint32_t); }
			sys_write32(word, (mm_reg_t)(ctl->base_addr + R_CORE_INPUT));
		} else {
			if (status == CIPHER_STATUS_ACCEPT) { break; }
		}
		if ((outlen != 0u || is_final || setup) && outwords != 0u) {
			uint32_t word = sys_read32((mm_reg_t)(ctl->base_addr + R_CORE_OUTPUT));
			if (outlen != 0u) { cmrt_write32(word, output++); }
			if (outlen < sizeof(uint32_t)) {
				outlen = 0;
			} else {
				outlen -= sizeof(uint32_t);
			}
		} else {
			if (status == CIPHER_STATUS_IDLE_WITH_KEY) { break; }
		}
	}

	return ((inlen == 0u) && (outlen == 0u)) ? 0 : -EIO;
}

uint32_t cipher_set_command(cmrt_cipher_t cipher, uint32_t cmd)
{
	uint32_t base_addr = cipher->cio->base_addr;
	uint32_t control = sys_read32((mm_reg_t)(base_addr + R_CORE_CONTROL));
	if (cipher->force_cmd || ((control & HWC_CONTROL_CMD_MASK) != cmd)) {
		control = (control & ~HWC_CONTROL_CMD_MASK) | cmd;
		sys_write32(control, (mm_reg_t)(base_addr + R_CORE_CONTROL));
	}
	cipher->force_cmd = false; /* should save the command */
	return control;
}

int cipher_load_key(cmrt_cipher_t cipher, const void *key, size_t keylen)
{
	cmrt_cio_t ctl = cipher->cio;
	uint32_t status = HWC_STATUS_IDLE_LOCKED;
	int rc = cmrt_wait_status_to(ctl->base_addr, &status, 1);
	if (rc != 0) { return rc; }

	(void)cipher_set_command(cipher, CIPHER_CMD_LOAD_KEY);

	return cmrt_cipher_copy(ctl, key, keylen, NULL, false, true);
}

int cipher_load_iv(cmrt_cipher_t cipher, size_t ivlen, const void *iv, size_t bsize)
{
	cmrt_cio_t ctl = cipher->cio;
	uint32_t status = CIPHER_STATUS_IDLE_WITH_KEY;
	int rc = cmrt_wait_status_to(ctl->base_addr, &status, 1);
	if (rc != 0) { return rc; }

	if ((ivlen > CIPHER_IV_MAX) || (bsize > CIPHER_IV_MAX)) {
		return -EINVAL;
	}

	uint32_t padded_iv[CIPHER_IV_MAX/4] = {0};
	(void)cmrt_memcpy((uint8_t *)padded_iv, iv, ivlen);

	(void)cipher_set_command(cipher, CIPHER_CMD_LOAD_IV);

	return cmrt_cipher_copy(ctl, padded_iv, bsize, NULL, false, true);
}

int cipher_load_aad(cmrt_cipher_t cipher, const void *ad, size_t adlen, bool final)
{
	cmrt_cio_t ctl = cipher->cio;
	const uint32_t statuses[] = { CIPHER_STATUS_IDLE_WITH_KEY,
				      CIPHER_STATUS_ACCEPT };
	int rc = cmrt_wait_status_to(ctl->base_addr, statuses,
				     sizeof(statuses) / sizeof(statuses[0]));
	if (rc < 0) { return rc; }
	if (rc == 0) {
		if (adlen != 0) {
			/* Only set AD mode once. */
			(void)cipher_set_command(cipher, CIPHER_CMD_LOAD_AD);
		} else if (final) {
			/* Never had any AD. */
			return 0;
		}
	}
	bool setup = final;
	return cmrt_cipher_copy(ctl, ad, adlen, NULL, final, setup);
}

int cipher_update(cmrt_cipher_t context, const void *input, size_t inlen, void *output)
{
	if (inlen == 0u) { return 0; }
	if (!cmrt_dd_valid(context) || input == NULL) { return -EINVAL; }
	if (!is_aligned(input, 4u) || !is_aligned(output, 4u)) {
		return -EINVAL;
	}

	cmrt_dd_t *dd = context->ddc.dd;
	uint32_t mask = cmrt_dd_lock(dd);

	cmrt_cio_t ctl = context->cio;

	(void)cipher_set_command(context, CIPHER_CMD_ENC_DEC);
	int rc = cmrt_cipher_copy(ctl, input, inlen, output, false, false);

	cmrt_dd_unlock(dd, mask);
	return rc;
}

int cipher_final(cmrt_cipher_t context, const void *input, size_t inlen, void *output)
{
	if (!cmrt_dd_valid(context) || !is_aligned(input, 4u) || !is_aligned(output, 4u)) {
		return -EINVAL;
	}

	cmrt_dd_t *dd = context->ddc.dd;
	uint32_t mask = cmrt_dd_lock(dd);

	cmrt_cio_t ctl = context->cio;

	uint32_t control = cipher_set_command(context, CIPHER_CMD_ENC_DEC);
	int rc = -EFAULT;
	if (ctl->tag_len(control) > 0) {
	    /* Should call cipher_ae_final. */
	    goto out;
	}
	rc = cmrt_cipher_copy(ctl, input, inlen, output, true, false);
	if (rc != 0) { goto out; }
	uint32_t status = CIPHER_STATUS_IDLE_WITH_KEY;
	rc = cmrt_wait_status_to(ctl->base_addr, &status, 1);
out:
	cmrt_dd_unlock(dd, mask);
	return rc;
}

int cipher_update_aad(cmrt_cipher_t context, const void *aad, size_t aadlen, bool final)
{
	if (!cmrt_dd_valid(context) || !is_aligned(aad, 4u)) { return -EINVAL; }

	cmrt_dd_t *dd = context->ddc.dd;
	uint32_t mask = cmrt_dd_lock(dd);

	int rc = cipher_load_aad(context, aad, aadlen, final);

	cmrt_dd_unlock(dd, mask);
	return rc;
}


/* We can load the tag in either status of ACCEPT, or IDLE_WITH_KEY.
 */
static int cipher_load_tag(cmrt_cipher_t cipher, void *tag, size_t *taglen)
{
	cmrt_cio_t ctl = cipher->cio;
	uint32_t status[2] = {
		CIPHER_STATUS_ACCEPT, CIPHER_STATUS_IDLE_WITH_KEY
	};
	int rc = cmrt_wait_status_to(ctl->base_addr, status, 2);
	if (rc < 0) { return rc; }

	uint32_t control = cipher_set_command(cipher, CIPHER_CMD_AUTH);
	int len = ctl->tag_len(control);
	uint32_t tagbuf[8];
	if ((len < 0) || (len > sizeof(tagbuf)) || ((size_t)len > *taglen)) {
		return -EINVAL;
	}

	int res = -1;
	if ((control & CIPHER_OPERATION_MASK) == CIPHER_OP_ENCRYPT) {
		res = cmrt_cipher_copy(ctl, NULL, (size_t)len, tagbuf, false, true);
		if (res >= 0) {
			memcpy(tag, tagbuf, len);
		} else {
			len = 0;
		}
	} else {
		memcpy(tagbuf, tag, len);
		res = cmrt_cipher_copy(ctl, tagbuf, (size_t)len, NULL, false, true);
	}
	*taglen = len;
	return res;
}

int cipher_ae_final(cmrt_cipher_t context, const void *input, size_t inlen, void *output, void *tag, size_t *taglen)
{
	if (!cmrt_dd_valid(context) || !is_aligned(input, 4u) ||
	    !is_aligned(output, 4u) || (tag == NULL) || (taglen == NULL)) {
		return -EINVAL;
	}

	cmrt_dd_t *dd = context->ddc.dd;
	uint32_t mask = cmrt_dd_lock(dd);

	int rc = 0;
	cmrt_cio_t ctl = context->cio;
	uint32_t flags = context->flags;
	if ((flags & (uint32_t)CIPHER_SKIP_LAST_BLOCK) != 0u) {
		/* AES-CMAC requires this path to be taken, no input
		 * can be supplied.  The core can directly transition
		 * from the state.
		 */
		if (inlen != 0u) {
			rc = -EINVAL;
		}
	} else if (((flags & CIPHER_SKIP_EMPTY_LAST_BLOCK) == 0u)
		   || (inlen != 0u)) {
		/* AES-CCM will return erronous output if an empty
		 * last block is requested, and the tag shall be
		 * requested directly.
		 */
		uint32_t control =
			cipher_set_command(context, CIPHER_CMD_ENC_DEC);
		if (ctl->tag_len(control) <= 0) {
		    /* Should call cipher_final. */
		    rc = -EFAULT;
		    goto out;
		}
		rc = cmrt_cipher_copy(ctl, input, inlen, output, true, false);
	}
	if (rc != 0) { goto out; }
	rc = cipher_load_tag(context, tag, taglen);
	if (rc != 0) { goto out; }
	uint32_t status = CIPHER_STATUS_IDLE_WITH_KEY;
	rc = cmrt_wait_status_to(ctl->base_addr, &status, 1);
out:
	cmrt_dd_unlock(dd, mask);
	return rc;
}

int cipher_invalidate_key(cmrt_cipher_t context, uint32_t flags)
{
	/* Not used atm, available for further extentions. */
	if (flags != 0u) { return -EINVAL; }

	cmrt_dd_t *dd = context->ddc.dd;
	uint32_t mask = cmrt_dd_lock(dd);

	(void)cipher_set_command(context, CIPHER_CMD_INVALIDATE_KEY);
	cmrt_cio_t ctl = context->cio;
	uint32_t status = HWC_STATUS_IDLE_LOCKED;
	int rc = cmrt_wait_status_to(ctl->base_addr, &status, 1);

	cmrt_dd_unlock(dd, mask);
	return rc;
}
