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

static int __pke_rsa_private_key_primitive(cmrt_pke_t pke,
					   const struct cmrt_rsa_ctx *ctx)
{
	int ret = -EIO;

	if (!pke || !ctx) {
		return -EINVAL;
	}

	const struct cmrt_rsa_key *key = &ctx->key;

#ifndef CRI_PKE_STANDALONE
	cmrt_dd_t *dd = pke->ddc.dd;
	uint32_t mask = cmrt_dd_lock(dd);
#endif

	if (IS_PKE_IDLE()) {
		goto err;
	}

	ret = cmrt_pke_clear_ram();
	if (ret) {
		goto err;
	}

	memcpy(pke_addr(rsa_sign_e, NULL, key->bits), key->e, key->elength);

	cmrt_pke_copy_command copy_commands[] = {
		{
			.in = ctx->message,
			.out = pke_addr(rsa_sign_c, NULL, key->bits),
		},
		{
			.in = key->n,
			.out = pke_addr(rsa_sign_n, NULL, key->bits),
		},
		{
			.in = key->d,
			.out = pke_addr(rsa_sign_d0, NULL, key->bits),
		},
	};

	cmrt_pke_copy_inputs cp_inputs = {
		.length = key->bits / 8,
		.copies_to_make = 3,
		.slot = rsa_sign_rnd,
		.copy_command = copy_commands
	};

	ret = copy_rsa_parameters_to_pke(&cp_inputs);
	if (ret) {
		goto err;
	}

#ifdef CONFIG_CMRT_PKE_32_BIT
	cmrt_pke_issue_mcg_command(pke, MCG_PREPARE_COMMAND(RSA_SIGN, 0, 0, cp_inputs.length / sizeof(uint32_t)));
#else /* 64-bit */
	cmrt_pke_issue_mcg_command(pke, MCG_PREPARE_COMMAND(RSA_SIGN, 0, 0, cp_inputs.length / sizeof(uint64_t)));
#endif

	cmrt_pke_response_t *const resp = &pke->response;
	resp->curve = NULL;
	resp->bits = key->bits;
	resp->copies_to_make = 1;
	resp->slot = rsa_sign_rnd;
	resp->ret_param[0].bits = key->bits;
	resp->ret_param[0].rAddr = ctx->signature;
	resp->ret_param[0].pkeAddr = pke_addr(out_rsa_sign_m, NULL, key->bits);

err:
#ifndef CRI_PKE_STANDALONE
	cmrt_dd_unlock(dd, mask);
#endif
	return ret;
}

int z_impl_cmrt_pke_rsa_sign(cmrt_pke_t pke, struct cmrt_rsa_ctx *ctx)
{
	int ret = __pke_rsa_private_key_primitive(pke, ctx);
	return cmrt_dd_autosync(&pke->ddc, ret);
}

#ifdef CONFIG_USERSPACE
#include <syscall_handler.h>

extern void z_syscall_verify_pke_context(cmrt_pke_t context);

static inline int z_vrfy_cmrt_pke_rsa_sign(cmrt_pke_t pke, struct cmrt_rsa_ctx *ctx)
{
	z_syscall_verify_pke_context(pke);

	Z_OOPS(Z_SYSCALL_MEMORY_WRITE(ctx, sizeof(struct cmrt_rsa_ctx)));
	return z_impl_cmrt_pke_rsa_sign(pke, ctx);
}
#include <syscalls/cmrt_pke_rsa_sign_mrsh.c>

#endif /* CONFIG_USERSPACE  */
