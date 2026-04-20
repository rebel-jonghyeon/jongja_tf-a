/*
 * Copyright (c) 2020-2023 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

#define DT_DRV_COMPAT rambus_cmrt_ccp

#include <device.h>
#include <sys/sys_io.h>
#include <drivers/cmrt/dd.h>
#include <drivers/cmrt/ccp.h>
#include <string.h>
#include <errno.h>
#include <assert.h>

#include "cipher_int.h"

#define R_BASE DT_INST_REG_ADDR(0)
static_assert(R_BASE == CMRT_CCP_BASE); /* device tree must match headers */

static uint32_t block_size(uint32_t ctrl)
{
	ccp_ctrl_t ctl;

	ctl.val = ctrl;
	switch (ctl.ctl.mode_2) {
	case CCP_MODE_CHACHA:
	case CCP_MODE_CHACHA_POLY_AEAD:
		return CHACHA_BLOCK_BYTES;
	case CCP_MODE_POLY:
		return POLY_BLOCK_BYTES;
	default:
		break;
	}
	return -1;
}

static int get_taglen(uint32_t ctrl)
{
	ccp_ctrl_t ctl;
	ctl.val = ctrl;
	if (ctl.ctl.mode_2 == CCP_MODE_CHACHA) { return -1; }
	/* CCP_TAG_LEN_128 */
	return 128 / 8;
}

static const struct cmrt_cipher_io cipher_ctl = {
	.base_addr = R_BASE,
	.block_size = block_size,
	.last_block = NULL,
	.tag_len = get_taglen,
};

typedef struct cmrt_ccp_context {
	struct cmrt_cipher_context ccc;
} cmrt_ccp_context_t;

#define CCP_CONTEXTS 1 /* only one active at a time */
CMRT_DD_CONTEXT static cmrt_ccp_context_t ccp_contexts[CCP_CONTEXTS];

int z_impl_cmrt_ccp_init(cmrt_ccp_t context, int operation, int mode, const void *key, size_t keylen, const void *iv, size_t ivlen, size_t taglen)
{
	int rc = -EINVAL;

	if (!cmrt_dd_valid(context) || key == NULL || (keylen != 16 && keylen != 32)) {
		return -EINVAL;
	}
	if (iv && ivlen != CCP_IV_LEN) {
		return -EINVAL;
	}

	/* TODO check core status, make sure there is no key left in core */

	cmrt_dd_t *dd = context->ccc.ddc.dd;
	uint32_t mask = cmrt_dd_lock(dd);

	ccp_ctrl_t cmd = { 0 };
	cmd.val = 0;
	cmd.ctl.cmd = CIPHER_CMD_INIT;
	cmd.ctl.mode_1 = CCP_MODE_1;
	cmd.ctl.cipher_op = operation;
	cmd.ctl.key_size = keylen == 32 ? CCP_KEY_SIZE_256 : CCP_KEY_SIZE_128;
	/* Tag Length can be only 16B or ignored for modes of operation that
	 *  do not require a tag */
	if (taglen == POLY_TAG_LENGTH_BYTES) {
		cmd.ctl.tag_len = CCP_TAG_LEN_128;
	}
	cmd.ctl.cnt_len = CCP_COUNTER_LEN_32; /* fixed so far */
	cmd.ctl.mode_2 = mode;
	cmd.ctl.reserved = 0;

	sys_write32(cmd.val, (mm_reg_t)(R_BASE + R_CORE_CONTROL));
	uint32_t status = HWC_STATUS_IDLE_LOCKED;
	rc = cmrt_wait_status_to(R_BASE, &status, 1);
	if (rc != 0) {
		goto out;
	}

	rc = cipher_load_key(&context->ccc, key, keylen);
	if (rc != 0) {
		goto out;
	}
	context->ccc.flags = 0;
	if (cmd.ctl.mode_2 == CCP_MODE_POLY) {
		context->ccc.flags = CIPHER_SKIP_LAST_BLOCK;
	}
	if (iv) {
		rc = cipher_load_iv(&context->ccc, ivlen, iv, CCP_IV_LEN);
		if (rc) {
			goto out;
		}
	}
	status = CIPHER_STATUS_IDLE_WITH_KEY;
	rc = cmrt_wait_status_to(R_BASE, &status, 1);
out:
	cmrt_dd_unlock(dd, mask);
	return rc;
}

static cmrt_dd_t ccp_dd = {
	.base = CMRT_CCP_BASE,
	.is_locking = 1,
	.context_count = CCP_CONTEXTS,
	.context_size = sizeof(cmrt_ccp_context_t),
	.irq_mask = 0,
	.contexts = ccp_contexts,
};

static int ccp_open_cb(cmrt_dd_context_t *ddc, void *arg)
{
	ARG_UNUSED(arg);
	cmrt_ccp_t ccp = (cmrt_ccp_t)ddc;
	ccp->ccc.cio = &cipher_ctl;
	return 0;
}

static const struct cmrt_driver_api ccp_driver_api = {
	.open_cb = ccp_open_cb,
	.find_cb = NULL,
	.poll_cb = NULL,
	.sync_cb = NULL,
	.close_cb = NULL,
};

DEVICE_DT_INST_DEFINE(0, cmrt_dev_init, NULL, &ccp_dd, NULL,
		      PRE_KERNEL_1, CONFIG_KERNEL_INIT_PRIORITY_DEVICE,
		      &ccp_driver_api);

cmrt_ccp_t z_impl_cmrt_ccp_open(uint32_t flags)
{
	return (cmrt_ccp_t)cmrt_dd_open(DEVICE_DT_INST_GET(0), flags, NULL);
}

void z_impl_cmrt_ccp_close(cmrt_ccp_t context)
{
	if (cmrt_dd_valid(context)) {
		cmrt_dd_close((cmrt_dd_context_t *)context);
	}
}

int z_impl_cmrt_ccp_update(cmrt_ccp_t context, const void *input, size_t inlen, void *output)
{
	return cipher_update((cmrt_cipher_t)context, input, inlen, output);
}

int z_impl_cmrt_ccp_update_aad(cmrt_ccp_t context, const void *aad, size_t aadlen)
{
	return cipher_update_aad((cmrt_cipher_t)context, aad, aadlen, false);
}

int z_impl_cmrt_ccp_final_aad(cmrt_ccp_t context, const void *aad, size_t aadlen)
{
	return cipher_update_aad((cmrt_cipher_t)context, aad, aadlen, true);
}

int z_impl_cmrt_ccp_final(cmrt_ccp_t context, const void *input, size_t inlen, void *output)
{
	return cipher_final((cmrt_cipher_t)context, input, inlen, output);
}

int z_impl_cmrt_ccp_ae_final(cmrt_ccp_t context, const void *input, size_t inlen, void *output, void *tag, size_t *taglen)
{
	return cipher_ae_final((cmrt_cipher_t)context, input, inlen, output, tag, taglen);
}

int z_impl_cmrt_ccp_invalidate_key(cmrt_ccp_t context, uint32_t flags)
{
	return cipher_invalidate_key((cmrt_cipher_t)context, flags);
}

#ifdef CONFIG_USERSPACE
#include <syscall_handler.h>

static inline void z_syscall_verify_ccp_context(cmrt_ccp_t context)
{
	cmrt_dd_syscall_verify((cmrt_dd_context_t *)context, &ccp_driver_api);
}

static inline cmrt_ccp_t z_vrfy_cmrt_ccp_open(uint32_t flags)
{
	return z_impl_cmrt_ccp_open(flags);
}
#include <syscalls/cmrt_ccp_open_mrsh.c>

static inline void z_vrfy_cmrt_ccp_close(cmrt_ccp_t context)
{
	z_syscall_verify_ccp_context(context);
	z_impl_cmrt_ccp_close(context);
}
#include <syscalls/cmrt_ccp_close_mrsh.c>

static inline int z_vrfy_cmrt_ccp_init(cmrt_ccp_t context, int operation, int mode, const void *key, size_t keylen, const void *iv, size_t ivlen, size_t taglen)
{
	z_syscall_verify_ccp_context(context);
	Z_OOPS(Z_SYSCALL_MEMORY_READ(key, keylen));
	Z_OOPS(Z_SYSCALL_MEMORY_READ(iv, ivlen));
	return z_impl_cmrt_ccp_init(context, operation, mode, key, keylen, iv, ivlen, taglen);
}
#include <syscalls/cmrt_ccp_init_mrsh.c>

static inline int z_vrfy_cmrt_ccp_update(cmrt_ccp_t context, const void *input, size_t inlen, void *output)
{
	z_syscall_verify_ccp_context(context);
	Z_OOPS(Z_SYSCALL_MEMORY_READ(input, inlen));
	Z_OOPS(Z_SYSCALL_MEMORY_WRITE(output, inlen));
	return z_impl_cmrt_ccp_update(context, input, inlen, output);
}
#include <syscalls/cmrt_ccp_update_mrsh.c>

static inline int z_vrfy_cmrt_ccp_update_aad(cmrt_ccp_t context, const void *aad, size_t aadlen)
{
	z_syscall_verify_ccp_context(context);
	Z_OOPS(Z_SYSCALL_MEMORY_READ(aad, aadlen));
	return z_impl_cmrt_ccp_update_aad(context, aad, aadlen);
}
#include <syscalls/cmrt_ccp_update_aad_mrsh.c>

static inline int z_vrfy_cmrt_ccp_final_aad(cmrt_ccp_t context, const void *aad, size_t aadlen)
{
	z_syscall_verify_ccp_context(context);
	Z_OOPS(Z_SYSCALL_MEMORY_READ(aad, aadlen));
	return z_impl_cmrt_ccp_final_aad(context, aad, aadlen);
}
#include <syscalls/cmrt_ccp_final_aad_mrsh.c>

static inline int z_vrfy_cmrt_ccp_final(cmrt_ccp_t context, const void *input, size_t inlen, void *output)
{
	z_syscall_verify_ccp_context(context);
	Z_OOPS(Z_SYSCALL_MEMORY_READ(input, inlen));
	Z_OOPS(Z_SYSCALL_MEMORY_WRITE(output, inlen));
	return z_impl_cmrt_ccp_final(context, input, inlen, output);
}
#include <syscalls/cmrt_ccp_final_mrsh.c>

static inline int z_vrfy_cmrt_ccp_ae_final(cmrt_ccp_t context, const void *input, size_t inlen, void *output, void *tag, size_t *taglen)
{
	z_syscall_verify_ccp_context(context);
	Z_OOPS(Z_SYSCALL_MEMORY_READ(input, inlen));
	Z_OOPS(Z_SYSCALL_MEMORY_WRITE(output, inlen));
	Z_OOPS(Z_SYSCALL_MEMORY_WRITE(tag, *taglen));
	Z_OOPS(Z_SYSCALL_MEMORY_WRITE(taglen, sizeof(*taglen)));
	return z_impl_cmrt_ccp_ae_final(context, input, inlen, output, tag, taglen);
}
#include <syscalls/cmrt_ccp_ae_final_mrsh.c>

static inline int z_vrfy_cmrt_ccp_invalidate_key(cmrt_ccp_t context, uint32_t flags)
{
	z_syscall_verify_ccp_context(context);
	return z_impl_cmrt_ccp_invalidate_key(context, flags);
}
#include <syscalls/cmrt_ccp_invalidate_key_mrsh.c>

#endif /* CONFIG_USERSPACE */
