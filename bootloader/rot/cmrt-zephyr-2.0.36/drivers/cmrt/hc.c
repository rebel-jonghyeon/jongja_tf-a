/*
 * Copyright (c) 2018-2023 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

#define DT_DRV_COMPAT rambus_cmrt_hc

#include <device.h>
#include <init.h>
#include <sys/sys_io.h>
#include <drivers/cmrt/dd.h>
#include <drivers/cmrt/hc.h>
#include <drivers/cmrt/sac.h>
#if CONFIG_CMRT_DMAC_THRESHOLD > 0
#include <drivers/cmrt/dmac.h>
#include "dmac_int.h"
#endif
#include <stdalign.h>
#include <string.h>
#include <errno.h>
#include <assert.h>

#if defined(CONFIG_CMRT_ASIL_B_MODE) || defined(CONFIG_CMRT_FIPS_140_MODE)
#include "kat/hc_kat.h"
#endif
#include "hc_int.h"

typedef struct cmrt_hc_context {
	cmrt_dd_context_t ddc;
	uint32_t inlen; /* for shake to make correct padding */
	bool padded; /* padding can be done in HW or here in the driver */
	/* eventually, context stores HC state so it can be restored */
} cmrt_hc_context_t;

#define HC_CONTEXTS 1 /* only one active at a time for each hash core */
#ifdef CONFIG_CMRT_HC
CMRT_DD_CONTEXT static cmrt_hc_context_t hc_contexts[HC_CONTEXTS];
#endif
#ifdef CONFIG_CMRT_CSHC
CMRT_DD_CONTEXT static cmrt_hc_context_t cshc_contexts[HC_CONTEXTS];
#endif
#ifdef CONFIG_CMRT_WHC
CMRT_DD_CONTEXT static cmrt_hc_context_t whc_contexts[HC_CONTEXTS];
#endif
#ifdef CONFIG_CMRT_HC2
CMRT_DD_CONTEXT static cmrt_hc_context_t hc2_contexts[HC_CONTEXTS];
#endif


static const struct hashinfo {
	uint16_t algo;
	uint8_t len;
} s_hash_algos[] = {
	{ HC_HASH_ALGO_SHA_224, SHA224_BYTES },
	{ HC_HASH_ALGO_SHA_256, SHA256_BYTES },
	{ HC_HASH_ALGO_SHA_384, SHA384_BYTES },
	{ HC_HASH_ALGO_SHA_512, SHA512_BYTES },
	{ HC_HASH_ALGO_SHA_512_224, SHA224_BYTES },
	{ HC_HASH_ALGO_SHA_512_256, SHA256_BYTES },
	{ HC_HASH_ALGO_SHA3_224, SHA3_224_BYTES },
	{ HC_HASH_ALGO_SHA3_256, SHA3_256_BYTES },
	{ HC_HASH_ALGO_SHA3_384, SHA3_384_BYTES },
	{ HC_HASH_ALGO_SHA3_512, SHA3_512_BYTES },
};

static int sha_hash_size(cmrt_hash_algo_t halgo) {
	for (uint32_t i = 0; i < sizeof(s_hash_algos) / sizeof(s_hash_algos[0]); ++i) {
		if (halgo == s_hash_algos[i].algo) {
			return s_hash_algos[i].len;
		}
	}
	return 0; /* invalid value */
}

size_t cmrt_hc_hash_size(cmrt_hash_algo_t halgo, bool whirlpool, size_t bsize)
{
#if IS_ENABLED(CMRT_HC_HAS_SHAKE128)
	if (halgo == HC_HASH_ALGO_SHAKE128) {
		return bsize;
	}
#endif
#if IS_ENABLED(CMRT_HC_HAS_SHAKE256)
	if (halgo == HC_HASH_ALGO_SHAKE256) {
		return bsize;
	}
#endif
	if (whirlpool) {
		if (halgo == HC_HASH_ALGO_WHIRLPOOL) {
			return WHIRLPOOL_BYTES;
		}
	} else {
		return sha_hash_size(halgo);
	}
	return 0;
}

static uint32_t hc_get_status(uint32_t base, uint32_t *inwords, uint32_t *outwords)
{
	uint32_t status = cmrt_core_status(base);
	*inwords = (status & HWC_STATUS_INWORDS_MASK) >>
		HWC_STATUS_INWORDS_SHIFT;
	*outwords = (status & HWC_STATUS_OUTWORDS_MASK) >>
		HWC_STATUS_OUTWORDS_SHIFT;
	return status & HWC_STATUS_STATUS_MASK;
}

static int hc_copy(uint32_t base, const uint32_t *input, size_t inlen, uint32_t *output, size_t outlen, bool final)
{
	if (((!is_aligned(outlen, 4u) || !is_aligned(inlen, 4u)) && !final) ||
	    !is_in_4gb((uintptr_t)input, inlen) || !is_in_4gb((uintptr_t)output, outlen)) {
		return -EINVAL;
	}

	bool key_fix = (inlen & 0x3u) == 0u && final && inlen > sizeof(uint32_t);
	if (key_fix) {
		/*
		 * In case we are copying a full size key the last word must
		 * come in the last block. We cannot copy the whole key and
		 * write a null last block, that will raise an error in the hc.
		 * There's no harm doing this for normal hash input too.
		 */
		inlen -= sizeof(uint32_t);
	}
	uint32_t inwords, outwords;
#if CONFIG_CMRT_DMAC_THRESHOLD > 0
	if (inlen > (uint32_t)CONFIG_CMRT_DMAC_THRESHOLD) {
	    int rc = cmrt_dmac_helper(0, (uint32_t)input, base, inlen, sizeof(uint32_t), 0);
	    if (rc < 0) { return rc; }
	    size_t done = inlen - (size_t)rc;
	    input += done >> 2;
	    inlen = (size_t)rc;
	}
#endif
	/* Input data with CPU. */
	while (inlen >= sizeof(uint32_t)) {
		uint32_t status = hc_get_status(base, &inwords, &outwords);
		if (IS_HWC_ERROR(status)) { return -EIO; }
		while (inlen >= sizeof(uint32_t) && inwords != 0u) {
			uint32_t word = cmrt_read32(input++);
			sys_write32(word, base + R_CORE_INPUT);
			inlen -= sizeof(uint32_t);
			inwords--;
		}
	}

	/* Input anything left with CPU */
	if (final) {
		if (key_fix) { inlen += sizeof(uint32_t); } /* see above */
		uint32_t byte_select = (1UL << inlen) - 1u;
		sys_write32(HC_LAST_BLOCK_IS_LAST | byte_select,
			    base + R_CORE_LAST_BLOCK);
		while (true) {
			uint32_t status = hc_get_status(base, &inwords, &outwords);
			if (IS_HWC_ERROR(status)) { return -EIO; }
			if (status == HC_STATUS_ACCEPT_LAST && (inwords != 0u)) {
				uint32_t word = inlen != 0u ? cmrt_read32(input) : 0u;
				sys_write32(word, base + R_CORE_INPUT);
				break;
			}
		}
	}
	/* Wait for status and get result if asked for. */
	while (true) {
		uint32_t status = hc_get_status(base, &inwords, &outwords);
		if (IS_HWC_ERROR(status)) { return -EIO; }
		if (status == HWC_STATUS_IDLE_LOCKED ||
		    status == HC_STATUS_IDLE_WITH_KEY ||
		    status == HC_STATUS_ACCEPT) { break; }
		while (outlen >= sizeof(uint32_t) && outwords != 0u) {
			uint32_t word = sys_read32((mm_reg_t)(base + R_CORE_OUTPUT));
			cmrt_write32(word, output++);
			outlen -= sizeof(uint32_t);
			outwords--;
		}
		if (outlen < sizeof(uint32_t)) { break; }
	}
	return 0;
}

#ifdef CONFIG_CMRT_KDC
int z_impl_cmrt_hc_kdc_cmd(cmrt_hc_t context, cmrt_hash_algo_t algo, size_t keylen, cmrt_kdc_cmd_t *cmd)
{
	ARG_UNUSED(keylen);
	if (!cmrt_dd_valid(context) || cmd == NULL) { return -EINVAL; }

	if ((context->ddc.flags & CMRT_O_HWC_KEYED) == 0u) {
		/* Invalid context for KDC operation. */
		return -EFAULT;
	}
	cmd->command0 = HC_CONTROL_HMAC | (uint32_t)algo;
	cmd->command1 = HWC_LOCK_MASTER_CPU;
	uint32_t base = context->ddc.dd->base;
	cmd->dest = (base == CMRT_HC2_BASE) ?
		KDC_DEST_HMAC2 : KDC_DEST_HMAC;
	cmd->key_size = KDC_SIZE_256;
	return 0;
}
#endif


static inline void write_shake_padding_control(uint32_t base, uint32_t algov)
{
#if IS_ENABLED(CMRT_HC_HAS_SHAKE128) || IS_ENABLED(CMRT_HC_HAS_SHAKE256)
#if IS_ENABLED(CMRT_HC_SHAKE_HW_PADDING)
	sys_write32(HC_CONTROL_HASH | algov,
		    base + R_CORE_CONTROL);
#else
	sys_write32(HC_CONTROL_HASH_RAW | algov,
		    base + R_CORE_CONTROL);
#endif
#endif
}


int z_impl_cmrt_hc_init(cmrt_hc_t context, cmrt_hash_algo_t algo, const void *key, size_t keylen)
{
	if (!cmrt_dd_valid(context) || !is_aligned(key, 4u)) {
	    return -EINVAL;
	}

	int rc = -EINVAL;
	cmrt_dd_t *dd = context->ddc.dd;
	uint32_t mask = cmrt_dd_lock(dd);
	uint32_t base = dd->base;
	uint32_t algov = (uint32_t)algo;
	context->inlen = 0;
	context->padded = false;
	if ((context->ddc.flags & CMRT_O_HWC_KEYED) != 0u) {
		/*
		 * If KDC sends key to HC, HC must not issue
		 * HC_CONTROL_INIT, otherwise the key will get
		 * lost.
		 */
		if (key != NULL) { goto out; } /* cannot give key as parameter */
	} else {
		sys_write32(HC_CONTROL_INIT | (uint32_t)algo,
			    base + R_CORE_CONTROL);

		if (key != NULL) {
			sys_write32(HC_CONTROL_LOAD_KEY | algov,
				    base + R_CORE_CONTROL);
			rc = hc_copy(base, key, keylen, NULL, 0, true);
			if (rc != 0) { goto out; }
		}
	}
	if ((key != NULL) || (context->ddc.flags & CMRT_O_HWC_KEYED) != 0u) {
		uint32_t status = HC_STATUS_IDLE_WITH_KEY;
		rc = cmrt_wait_status_to(dd->base, &status, 1);
		if (rc != 0) { goto out; }
		sys_write32(HC_CONTROL_HMAC | algov,
			    base + R_CORE_CONTROL);
#if IS_ENABLED(CMRT_HC_HAS_SHAKE128)
	} else if (algov == HC_HASH_ALGO_SHAKE128) {
		write_shake_padding_control(base, algov);
#endif
#if IS_ENABLED(CMRT_HC_HAS_SHAKE256)
	} else if (algov == HC_HASH_ALGO_SHAKE256) {
		write_shake_padding_control(base, algov);
#endif
	} else {
		sys_write32(HC_CONTROL_HASH | algov,
			    base + R_CORE_CONTROL);
	}
	uint32_t status = HC_STATUS_ACCEPT;
	rc = cmrt_wait_status_to(dd->base, &status, 1);
out:
	cmrt_dd_unlock(dd, mask);
	return rc;
}

int z_impl_cmrt_hc_update(cmrt_hc_t context, const void *input, size_t inlen)
{
	if (!cmrt_dd_valid(context) || input == NULL || !is_aligned(input, 4u)) {
		return -EINVAL;
	}

	cmrt_dd_t *dd = context->ddc.dd;
	uint32_t mask = cmrt_dd_lock(dd);

	uint32_t base = dd->base;
	int rc = hc_copy(base, input, inlen, NULL, 0, false);
	if (rc != 0) { goto out; }
	context->inlen += inlen;
 out:
	cmrt_dd_unlock(dd, mask);
	return rc;
}

#if !IS_ENABLED(CMRT_HC_SHAKE_HW_PADDING)
static inline size_t hc_padlen(size_t blocksize, size_t inlen) {
	size_t padlen = blocksize - (inlen % blocksize);
	if (padlen == 0) {
		/* Inlen is block size aligned, add new padding block. */
		padlen = blocksize;
	}
	return padlen;
}
#endif

int z_impl_cmrt_hc_final(cmrt_hc_t context, const void *input, size_t inlen, void *output, size_t *outlen)
{
	if (!cmrt_dd_valid(context) || output == NULL || outlen == NULL ||
	    !is_aligned(input, 4u) || !is_aligned(output, 4u) ||
	    (inlen > 0 && context->padded)) {
		return -EINVAL;
	}

	cmrt_dd_t *dd = context->ddc.dd;
	uint32_t mask = cmrt_dd_lock(dd);

	uint32_t base = dd->base;
	uint32_t algo = sys_read32(base + R_CORE_CONTROL) & HC_CONTROL_ALGO_MASK;

	int rc = 0;
#if !IS_ENABLED(CMRT_HC_SHAKE_HW_PADDING)
	alignas(4) uint8_t padding[MAX(SHAKE128_BLOCKSIZE, SHAKE256_BLOCKSIZE)];
	if ((algo == HC_HASH_ALGO_SHAKE128 || algo == HC_HASH_ALGO_SHAKE256) &&
	    !context->padded) { /* add padding only once */
		/* Add padding here in software. */
		if (input != NULL && inlen != 0) {
			/* First update the last word aligned data. */
			rc = hc_copy(base, input, inlen & ~0x3u, NULL, 0, false);
			if (rc != 0) { goto out; }
			/* Copy the remaining bytes into the padding buffer. */
			(void)cmrt_memcpy(padding, (uint8_t *)input + (inlen & ~0x3u), inlen & 0x3u);
			context->inlen += inlen;
		}
		size_t padlen = (algo == HC_HASH_ALGO_SHAKE128) ?
			hc_padlen(SHAKE128_BLOCKSIZE, context->inlen) :
			hc_padlen(SHAKE256_BLOCKSIZE, context->inlen);
		memset(padding + (inlen & 0x3u), 0, padlen);
		padding[inlen & 0x3u] |= 0x1F;
		padding[(inlen & 0x3u) + padlen - 1] |= 0x80;
		input = padding;
		inlen = padlen + (inlen & 0x3u);
		/* Last bytes and padding will be the last input. */
	}
#endif
	rc = hc_copy(base, input, inlen, output, *outlen, !context->padded);
	if (rc != 0) { goto out; }
	context->inlen += inlen;

	size_t len = cmrt_hc_hash_size(algo, base == CMRT_WHC_BASE, *outlen);
	if (*outlen > len) { *outlen = len; }
	context->padded = true;
 out:
	cmrt_dd_unlock(dd, mask);
	return rc;
}

static const struct cmrt_driver_api hc_driver_api = {
	.open_cb = NULL,
#if defined(CONFIG_CMRT_ASIL_B_MODE) || defined(CONFIG_CMRT_FIPS_140_MODE)
	.open_kat = hc_open_kat,
#endif
	.find_cb = NULL,
	.poll_cb = NULL,
	.sync_cb = NULL,
	.close_cb = NULL,
};

#ifdef CONFIG_CMRT_HC
static cmrt_hc_dd_t hc_dd = {
	.dd = {
		.base = CMRT_HC_BASE,
		.is_locking = 1,
		.context_count = HC_CONTEXTS,
		.context_size = sizeof(cmrt_hc_context_t),
		.irq_mask = 0,
		.contexts = hc_contexts
	},
#if defined(CONFIG_CMRT_ASIL_B_MODE) || defined(CONFIG_CMRT_FIPS_140_MODE)
	.kat = (DT_INST_PROP(0, has_sha3_256)) ? &s3hc_known : &s2hc_known
#endif
};

static_assert(DT_INST_REG_ADDR(0) == CMRT_HC_BASE); /* device tree must match headers */

DEVICE_DT_INST_DEFINE(0, cmrt_dev_init, NULL, &hc_dd, NULL,
		      PRE_KERNEL_1, CONFIG_KERNEL_INIT_PRIORITY_DEVICE,
		      &hc_driver_api);
#endif

#ifdef CONFIG_CMRT_CSHC
static cmrt_dd_t cshc_dd = {
	.base = CMRT_CSHC_BASE,
	.is_locking = 1,
	.context_count = HC_CONTEXTS,
	.context_size = sizeof(cmrt_hc_context_t),
	.irq_mask = 0,
	.contexts = cshc_contexts,
};

static_assert(DT_INST_REG_ADDR(1) == CMRT_CSHC_BASE); /* device tree must match headers */

DEVICE_DT_INST_DEFINE(1, cmrt_dev_init, NULL, &cshc_dd, NULL,
		      PRE_KERNEL_1, CONFIG_KERNEL_INIT_PRIORITY_DEVICE,
		      &hc_driver_api);
#endif

#ifdef CONFIG_CMRT_WHC
static cmrt_dd_t whc_dd = {
	.base = CMRT_WHC_BASE,
	.is_locking = 1,
	.context_count = HC_CONTEXTS,
	.context_size = sizeof(cmrt_hc_context_t),
	.irq_mask = 0,
	.contexts = whc_contexts,
};

static_assert(DT_INST_REG_ADDR(2) == CMRT_WHC_BASE); /* device tree must match headers */

DEVICE_DT_INST_DEFINE(2, cmrt_dev_init, NULL, &whc_dd, NULL,
		      PRE_KERNEL_1, CONFIG_KERNEL_INIT_PRIORITY_DEVICE,
		      &hc_driver_api);
#endif

#ifdef CONFIG_CMRT_HC2
static cmrt_hc_dd_t hc2_dd = {
	.dd = {
		.base = CMRT_HC2_BASE,
		.is_locking = 1,
		.context_count = HC_CONTEXTS,
		.context_size = sizeof(cmrt_hc_context_t),
		.irq_mask = 0,
		.contexts = hc2_contexts,
	},
#if defined(CONFIG_CMRT_ASIL_B_MODE) || defined(CONFIG_CMRT_FIPS_140_MODE)
	.kat = (bool)DT_INST_PROP(3, has_sha3_256) ? &s3hc_known : &s2hc_known
#endif
};

static_assert(DT_INST_REG_ADDR(3) == CMRT_HC2_BASE); /* device tree must match headers */

DEVICE_DT_INST_DEFINE(3, cmrt_dev_init, NULL, &hc2_dd, NULL,
		      PRE_KERNEL_1, CONFIG_KERNEL_INIT_PRIORITY_DEVICE,
		      &hc_driver_api);
#endif

#if defined(CONFIG_CMRT_ASIL_B_MODE) || defined(CONFIG_CMRT_FIPS_140_MODE)
SYS_INIT(hc_init_kat, POST_KERNEL, CONFIG_APPLICATION_INIT_PRIORITY);
#endif

cmrt_hc_t z_impl_cmrt_hc_open(const char *name, uint32_t flags)
{
	if (name == NULL) {
		return (cmrt_hc_t)cmrt_dd_open(DEVICE_DT_INST_GET(0), flags, NULL);
	}
	return (cmrt_hc_t)cmrt_dd_open(device_get_binding(name), flags, NULL);
}

cmrt_hc_t z_impl_cmrt_cshc_open(uint32_t flags)
{
#ifdef CONFIG_CMRT_CSHC
	return (cmrt_hc_t)cmrt_dd_open(DEVICE_DT_INST_GET(1), flags, NULL);
#else
	return NULL;
#endif
}


cmrt_hc_t z_impl_cmrt_whc_open(uint32_t flags)
{
#ifdef CONFIG_CMRT_WHC
	return (cmrt_hc_t)cmrt_dd_open(DEVICE_DT_INST_GET(2), flags, NULL);
#else
	return NULL;
#endif
}

cmrt_hc_t z_impl_cmrt_hc2_open(uint32_t flags)
{
#ifdef CONFIG_CMRT_HC2
	return (cmrt_hc_t)cmrt_dd_open(DEVICE_DT_INST_GET(3), flags, NULL);
#else
	return NULL;
#endif
}

void z_impl_cmrt_hc_close(cmrt_hc_t context)
{
	if (cmrt_dd_valid(context)) {
		cmrt_dd_close((cmrt_dd_context_t *)context);
	}
}

#ifdef CONFIG_USERSPACE
#include <syscall_handler.h>

static inline void z_syscall_verify_hc_context(cmrt_hc_t context)
{
	cmrt_dd_syscall_verify((cmrt_dd_context_t *)context, &hc_driver_api);
}

static inline cmrt_hc_t z_vrfy_cmrt_hc_open(const char *name, uint32_t flags)
{
	return z_impl_cmrt_hc_open(name, flags);
}
#include <syscalls/cmrt_hc_open_mrsh.c>

static inline cmrt_hc_t z_vrfy_cmrt_cshc_open(uint32_t flags)
{
	return z_impl_cmrt_cshc_open(flags);
}
#include <syscalls/cmrt_cshc_open_mrsh.c>

static inline cmrt_hc_t z_vrfy_cmrt_whc_open(uint32_t flags)
{
	return z_impl_cmrt_whc_open(flags);
}
#include <syscalls/cmrt_whc_open_mrsh.c>

static inline cmrt_hc_t z_vrfy_cmrt_hc2_open(uint32_t flags)
{
	return z_impl_cmrt_hc2_open(flags);
}
#include <syscalls/cmrt_hc2_open_mrsh.c>

static inline void z_vrfy_cmrt_hc_close(cmrt_hc_t context)
{
	z_syscall_verify_hc_context(context);
	z_impl_cmrt_hc_close(context);
}
#include <syscalls/cmrt_hc_close_mrsh.c>

static inline int z_vrfy_cmrt_hc_kdc_cmd(cmrt_hc_t context, cmrt_hash_algo_t algo, size_t keylen, cmrt_kdc_cmd_t *cmd)
{
	z_syscall_verify_hc_context(context);
	Z_OOPS(Z_SYSCALL_MEMORY_WRITE(cmd, sizeof(*cmd)));
	return z_impl_cmrt_hc_kdc_cmd(context, algo, keylen, cmd);
}
#include <syscalls/cmrt_hc_kdc_cmd_mrsh.c>

static inline int z_vrfy_cmrt_hc_init(cmrt_hc_t context, cmrt_hash_algo_t algo, const void *key, size_t keylen)
{
	z_syscall_verify_hc_context(context);
	Z_OOPS(Z_SYSCALL_MEMORY_READ(key, keylen));
	return z_impl_cmrt_hc_init(context, algo, key, keylen);
}
#include <syscalls/cmrt_hc_init_mrsh.c>

static inline int z_vrfy_cmrt_hc_update(cmrt_hc_t context, const void *input, size_t inlen)
{
	z_syscall_verify_hc_context(context);
	Z_OOPS(Z_SYSCALL_MEMORY_READ(input, inlen));
	return z_impl_cmrt_hc_update(context, input, inlen);
}
#include <syscalls/cmrt_hc_update_mrsh.c>

static inline int z_vrfy_cmrt_hc_final(cmrt_hc_t context, const void *input, size_t inlen, void *output, size_t *outlen)
{
	z_syscall_verify_hc_context(context);
	Z_OOPS(Z_SYSCALL_MEMORY_READ(input, inlen));
	Z_OOPS(Z_SYSCALL_MEMORY_WRITE(outlen, sizeof(*outlen)));
	Z_OOPS(Z_SYSCALL_MEMORY_WRITE(output, *outlen));
	return z_impl_cmrt_hc_final(context, input, inlen, output, outlen);
}
#include <syscalls/cmrt_hc_final_mrsh.c>

#endif /* CONFIG_USERSPACE */
