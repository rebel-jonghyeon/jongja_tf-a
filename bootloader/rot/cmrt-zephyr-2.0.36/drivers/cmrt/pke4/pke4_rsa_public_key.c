/*
 * Copyright (c) 2019-2023 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <errno.h>

#ifndef CRI_PKE_STANDALONE
#include <device.h>
#include <init.h>
#include <kernel.h>
#include <drivers/cmrt/dd.h>
#include <drivers/cmrt/pke.h>
#include <drivers/cmrt/cmrt.h>

#include <drivers/cmrt/crypto/pke_dpasl.h>
#include <drivers/cmrt/crypto/pke_common.h>

#include <drivers/cmrt/pke4/pke4_driver.h>
#include <drivers/cmrt/pke4/pke4_math.h>
#else

#include "pke.h"
#include "pke_dpasl.h"
#include "pke_common.h"

#include "pke4_driver.h"
#include "pke4_math.h"
#endif
#include "pke4_random.h"

static int __pke_rsa_public_key_primitive(cmrt_pke_t pke,
					  struct cmrt_rsa_ctx *ctx)
{
	int ret = -EIO;

	if (!pke || !ctx) {
		return -EINVAL;
	}

#ifndef CRI_PKE_STANDALONE
	cmrt_dd_t *dd = pke->ddc.dd;
	uint32_t mask = cmrt_dd_lock(dd);
#endif

	struct cmrt_rsa_key *key = &ctx->key;

	if (IS_PKE_IDLE()) {
		goto err;
	}

	ret = cmrt_pke_clear_ram();
	if (ret) {
		goto err;
	}

	memcpy(pke_addr(rsa_public_e, NULL, key->bits), key->e, key->elength);
	memcpy(pke_addr(rsa_public_m, NULL, key->bits), ctx->signature, key->bits / 8);
	memcpy(pke_addr(rsa_public_n, NULL, key->bits), key->n, key->bits / 8);

#ifdef CONFIG_CMRT_PKE_32_BIT
	cmrt_pke_issue_mcg_command(pke, MCG_PREPARE_COMMAND(RSA_PUBLIC, 0, 0, (key->bits / 8) / sizeof(uint32_t)));
#else /* 64-bit */
	cmrt_pke_issue_mcg_command(pke, MCG_PREPARE_COMMAND(RSA_PUBLIC, 0, 0, (key->bits / 8) / sizeof(uint64_t)));
#endif

	cmrt_pke_response_t *const resp = &pke->response;
	resp->curve = NULL;
	resp->bits = key->bits;
	resp->copies_to_make = 1;
	resp->slot = out_rsa_public_rnd;
	resp->ret_param[0].bits = key->bits;
	resp->ret_param[0].rAddr = ctx->message;
	resp->ret_param[0].pkeAddr = pke_addr(out_rsa_public_c, NULL, key->bits);

err:
#ifndef CRI_PKE_STANDALONE
	cmrt_dd_unlock(dd, mask);
#endif
	return ret;
}

int cmrt_pke_rsa_pub(cmrt_pke_t pke, struct cmrt_rsa_ctx *ctx)
{
	int ret = __pke_rsa_public_key_primitive(pke, ctx);
	if (ret) {
		goto err;
	}

	ret = cmrt_pke_sync(pke);
err:
	return ret;
}

int z_impl_cmrt_pke_rsa_public_key_primitive(cmrt_pke_t pke,
					     uint32_t bits,
					     const uint8_t *mod,
					     const uint8_t *public_key,
					     const uint8_t *signature,
					     uint8_t *message)
{
	struct cmrt_rsa_ctx ctx;

	memset(&ctx, 0, sizeof(ctx));
	ctx.key.bits = bits;
	ctx.key.flags = 0;
	ctx.key.n = (uint8_t *)mod;
	ctx.key.e = (uint8_t *)public_key;
	ctx.key.elength = 4;
	ctx.message = message;
	ctx.signature = (uint8_t *)signature;

	int ret = __pke_rsa_public_key_primitive(pke, &ctx);
	return cmrt_dd_autosync(&pke->ddc, ret);
}

#ifdef CONFIG_CMRT_RSA_CRT
int cmrt_pke_rsa_crt_pub(cmrt_pke_t pke, struct cmrt_rsa_ctx *ctx)
{
	int ret = __pke_rsa_public_key_primitive(pke, ctx);
	if (ret) {
		goto err;
	}

	ret = cmrt_pke_sync(pke);
err:
	return ret;
}
#endif

#ifdef CONFIG_USERSPACE
#include <syscall_handler.h>

extern void z_syscall_verify_pke_context(cmrt_pke_t context);

static inline int z_vrfy_cmrt_pke_rsa_public_key_primitive(cmrt_pke_t context, uint32_t bits,
		const uint8_t *mod, const uint8_t *public_key,
		const uint8_t *signature, uint8_t *message)

{
	z_syscall_verify_pke_context(context);

	/* Assuming RSA, if RSA-CRT then aux_size = bits / 16 */
	uint32_t aux_size = bits / 8;
	Z_OOPS(Z_SYSCALL_MEMORY_READ(mod, aux_size));
	Z_OOPS(Z_SYSCALL_MEMORY_READ(public_key, aux_size));
	Z_OOPS(Z_SYSCALL_MEMORY_READ(signature, aux_size));
	Z_OOPS(Z_SYSCALL_MEMORY_WRITE(message, aux_size));

	return z_impl_cmrt_pke_rsa_public_key_primitive(context, bits, mod, public_key, signature, message);

}
#include <syscalls/cmrt_pke_rsa_public_key_primitive_mrsh.c>

#endif /* CONFIG_USERSPACE */
