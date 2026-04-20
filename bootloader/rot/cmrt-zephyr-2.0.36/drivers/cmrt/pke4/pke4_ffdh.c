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
#include "pke4_hash.h"
#else

#include "pke.h"
#include "pke_dpasl.h"
#include "pke_common.h"

#include "pke4_driver.h"
#include "pke4_math.h"
#endif
#include "pke4_random.h"
#include "pke_internal.h"

#include <logging/log.h>
LOG_MODULE_DECLARE(cmrt, CONFIG_CMRT_LOG_LEVEL);

#define FFDH_ERR(e) LOG_DBG("%s:%d %d", __func__, __LINE__, (e))

/* Support up to 4K bits */
#define MAX_DH_GROUP_SIZE (4096 / 8)

static int maucmp(unsigned a, unsigned b, unsigned length)
{
	uint32_t cmds[] = {
		SLOT_CMD(SET_RAM_SLOTS, MAU_SRAM_OFFSET),
		SLOT_CMD(LOAD, a),
		SLOT_CMD(COMPARE, b)
	};
	int ret = cmrt_pke_mau_command_sequence(cmds, 3, length);
	if (ret == 0) {
		ret = MAU_GET_COMPARE_RESULT();
	}
	return ret;
}

int z_impl_cmrt_pke_ffdh(cmrt_pke_t pke,
			 const struct cmrt_ffdh_param *param,
			 const uint8_t *priv_key, const uint8_t *peer_key,
			 uint8_t *pub_key, uint8_t *shared_key)
{
	int ret = -EIO;

	if (!param) {
		FFDH_ERR(-EINVAL);
		return -EINVAL;
	}

	size_t mod_size = param->mod_size;
	const uint8_t *p = param->p;
	size_t q_size = param->grp_size;
	const uint8_t *q = param->q;
	size_t g_size = param->gen_size;
	const uint8_t *g = param->g;

	/* Validate arguments */
	if (mod_size > MAX_DH_GROUP_SIZE) {
		FFDH_ERR(-EINVAL);
		return -EINVAL;
	}

	if (!pke || !p || !q || !g || !priv_key) {
		FFDH_ERR(-EINVAL);
		return -EINVAL;
	}

	if (!pub_key && !shared_key) {
		FFDH_ERR(-EINVAL);
		return -EINVAL;
	}

	if (shared_key && !peer_key) {
		FFDH_ERR(-EINVAL);
		return -EINVAL;
	}

	ret = cmrt_pke_clear_ram();
	if (ret != 0) {
		goto err;
	}

	uint32_t swords = ((mod_size + 7) & (~7)) / 4;
#ifdef CONFIG_CMRT_PKE_32_BIT
	uint32_t length = mod_size / sizeof(uint32_t);
#else /* 64-bit */
	uint32_t length = ((mod_size - 1) / sizeof(uint64_t) + 1);
#endif

	memcpy(pke_addr(ffdh_p, NULL, swords * 32), p, mod_size);
	memcpy(pke_addr(ffdh_q, NULL, swords * 32), q, q_size);
	memcpy(pke_addr(ffdh_g, NULL, swords * 32), g, g_size);
	memcpy(pke_addr(ffdh_pri, NULL, swords * 32), priv_key, q_size);

	if (peer_key) {
		memcpy(pke_addr(ffdh_peer, NULL, swords * 32), peer_key, mod_size);
	}

	if (maucmp(SLOT(ffdh_p), SLOT(ffdh_q), length) != MAU_GT) {
		FFDH_ERR(-EINVAL);
		ret = -EINVAL;
		goto err;
	}

	if (maucmp(SLOT(ffdh_p), SLOT(ffdh_pri), length) != MAU_GT) {
		FFDH_ERR(-EINVAL);
		ret = -EINVAL;
		goto err;
	}

	if (peer_key != NULL) {
		if (maucmp(SLOT(ffdh_p), SLOT(ffdh_peer), length) != MAU_GT) {
			FFDH_ERR(-EINVAL);
			ret = -EINVAL;
			goto err;
		}
	}

	if (maucmp(SLOT(ffdh_pri), R_MAU_ONE, length) != MAU_GT) {
		FFDH_ERR(-EINVAL);
		ret = -EINVAL;
		goto err;
	}

	/* peer_key^q = 1 mod p.
	 * Because peer_key^q= (g^b)^q = (g^q)^b = 1 mod p.
	 */
	if (peer_key) {
		static const uint32_t cmds_peer_copy[] = {
			SLOT_CMD(SET_MAND,      SLOT(ffdh_in)),
			SLOT_CMD(COPY,          SLOT(ffdh_peer)),
			SLOT_CMD(SET_MAND,      SLOT(ffdh_mod)),
			SLOT_CMD(COPY,          SLOT(ffdh_p)),
			SLOT_CMD(SET_MAND,      SLOT(ffdh_exp)),
			SLOT_CMD(COPY,          SLOT(ffdh_q)),
		};

		ret = cmrt_pke_mau_command_sequence(cmds_peer_copy, sizeof(cmds_peer_copy)/sizeof(uint32_t), length);
		if (ret != 0) {
			goto err;
		}

		ret = cmrt_pke_run_mcg_command(pke, MCG_PREPARE_COMMAND(MOD_EXP, 0, 0, length));
		if (ret != 0) {
			goto err;
		}

		if (maucmp(SLOT(ffdh_in), R_MAU_ONE, length) != MAU_EQ) {
			FFDH_ERR(-EINVAL);
			ret = -EINVAL;
			goto err;
		}
	}

	/* pub_key = (g^priv_key) mod p */
	if (pub_key) {
		static const uint32_t cmds_pub_copy[] = {
			SLOT_CMD(SET_MAND,      SLOT(ffdh_in)),
			SLOT_CMD(COPY,          SLOT(ffdh_g)),
			SLOT_CMD(SET_MAND,      SLOT(ffdh_mod)),
			SLOT_CMD(COPY,          SLOT(ffdh_p)),
			SLOT_CMD(SET_MAND,      SLOT(ffdh_exp)),
			SLOT_CMD(COPY,          SLOT(ffdh_pri)),
		};

		ret = cmrt_pke_mau_command_sequence(cmds_pub_copy, sizeof(cmds_pub_copy)/sizeof(uint32_t), length);
		if (ret != 0) {
			goto err;
		}

		ret = cmrt_pke_run_mcg_command(pke, MCG_PREPARE_COMMAND(MOD_EXP, 0, 0, length));
		if (ret != 0) {
			goto err;
		}

		memcpy(pub_key, pke_addr(out_ffdh_pub, NULL, swords * 32), mod_size);
	}

	/* shared_key = (peer_key^priv_key) mod p */
	if (shared_key && peer_key) {
		static const uint32_t cmds_shared_copy[] = {
			SLOT_CMD(SET_MAND,      SLOT(ffdh_in)),
			SLOT_CMD(COPY,          SLOT(ffdh_peer)),
			SLOT_CMD(SET_MAND,      SLOT(ffdh_mod)),
			SLOT_CMD(COPY,          SLOT(ffdh_p)),
			SLOT_CMD(SET_MAND,      SLOT(ffdh_exp)),
			SLOT_CMD(COPY,          SLOT(ffdh_pri)),
		};

		ret = cmrt_pke_mau_command_sequence(cmds_shared_copy, sizeof(cmds_shared_copy)/sizeof(uint32_t), length);
		if (ret != 0) {
			goto err;
		}

		cmrt_pke_response_t *const resp = &pke->response;
		resp->curve = NULL;
		resp->bits = 8u * mod_size;
		resp->copies_to_make = 1;
		resp->slot = out_ecdsaSign_rnd;
		resp->ret_param[0].bits = 8u * mod_size;
		resp->ret_param[0].rAddr = shared_key;
		resp->ret_param[0].pkeAddr
			= pke_addr(out_ffdh_sh, NULL, swords * 32);

		cmrt_pke_issue_mcg_command(pke, MCG_PREPARE_COMMAND(MOD_EXP, 0, 0, length));
		ret = cmrt_dd_autosync(&pke->ddc, ret);
		if (ret != 0) {
			goto err;
		}
	} else if (ret >= 0) {
		ret = cmrt_pke_complete(pke);
		if (ret != 0) {
			goto err;
		}
	}

err:
	return ret;
}

int z_impl_cmrt_pke_ffdh_private_keygen(cmrt_pke_t pke, size_t q_size, const uint8_t *q, uint8_t *priv_key)
{
	int ret = -EIO;

	/* Validate arguments */
	if (q_size > MAX_DH_GROUP_SIZE) {
		FFDH_ERR(-EINVAL);
		return -EINVAL;
	}

	if (!pke || !q || !priv_key) {
		FFDH_ERR(-EINVAL);
		return -EINVAL;
	}

	ret = cmrt_pke_clear_ram();
	if (ret != 0) {
		goto err;
	}

	uint32_t swords = ((q_size + 7) & (~7)) / 4;
#ifdef CONFIG_CMRT_PKE_32_BIT
	uint32_t length = swords;
#else /* 64-bit */
	uint32_t length = ((q_size - 1) / sizeof(uint64_t) + 1);
#endif

	ret = cmrt_pke_get_true_random(priv_key, q_size);
	if (ret != 0) {
		goto err;
	}

	ISSUE_MAU_COMMAND(SET_RAM_SLOTS, MAU_SRAM_OFFSET, length);
	ISSUE_MAU_COMMAND(LOAD, R_MAU_ZERO, length);
	ISSUE_MAU_COMMAND(STORE, SLOT(ffdh_keygen_k), length);
	ret = cmrt_pke_wait();
	if (ret != 0) {
		goto err;
	}

	memcpy(pke_addr(ffdh_keygen_q, NULL, swords * 32), q, q_size);
	memcpy(pke_addr(ffdh_keygen_k, NULL, swords * 32), priv_key, q_size);

	/* Let priv = rnd * R mod q */
	static const uint32_t norm_cmds[] = {
		SLOT_CMD(SET_PARAMS, SLOT(ffdh_keygen_q)),
		SLOT_CMD(SET_MAND, SLOT(ffdh_keygen_k)),
		SLOT_CMD(MONT_MUL, R_MAU_ONE),
		SLOT_CMD(CANON, 0),
		SLOT_CMD(STORE, SLOT(ffdh_keygen_k))
	};
	enum { num_norm_cmds = sizeof(norm_cmds) / sizeof(norm_cmds[0]) };
	ret = cmrt_pke_mau_command_sequence(norm_cmds, num_norm_cmds, length);
	if (ret != 0) {
		goto err;
	}
	memcpy(priv_key, pke_addr(ffdh_keygen_k, NULL, swords * 32), q_size);
	pke->response.copies_to_make = 0;
	ret = cmrt_pke_complete(pke);
err:
	return ret;
}

/* Returns 0 on success, otherwise negative values. */
int z_impl_cmrt_pke_ffdh_verify(cmrt_pke_t pke, const struct cmrt_ffdh_param *param)
{
	int ret = -EIO;

	if (!param) {
		FFDH_ERR(-EINVAL);
		return -EINVAL;
	}

	size_t psize = param->mod_size;
	const uint8_t *p = param->p;
	size_t qsize = param->grp_size;
	const uint8_t *q = param->q;
	size_t gsize = param->gen_size;
	const uint8_t *g = param->g;

	uint32_t prime = 0;
	uint32_t min_length;

	if (psize > MAX_DH_GROUP_SIZE) {
		FFDH_ERR(-EINVAL);
		return -EINVAL;
	}

	if (!pke || !p || !q || !g) {
		FFDH_ERR(-EINVAL);
		return -EINVAL;
	}

	ret = cmrt_pke_clear_ram();
	if (ret) {
		goto err;
	}

	/* p and q must be prime, and g^q = 1 mod p. */
	uint32_t swords = psize / 4;
#ifdef CONFIG_CMRT_PKE_32_BIT
	uint32_t length = swords;
	uint32_t param_length = length;
#else /* 64-bit */
	uint32_t length = ((swords - 1) / 2) + 1;
	uint32_t param_length = length * 2;
#endif

	memcpy(pke_addr(ffdh_verify_p, NULL, param_length * 32), p, psize);

	prime = 0;
	ret = cmrt_pke_is_probable_prime(pke, psize * 8, ffdh_verify_p, &prime);
	if (ret) {
		goto err;
	}

	if (prime == 0) {
		FFDH_ERR(-EINVAL);
		ret = -EINVAL;
		goto err;
	}

	ret = cmrt_pke_clear_ram();
	if (ret) {
		goto err;
	}

	min_length = MAU_READ_REG(R_MAU_MIN_LEN);
	/* p and q must be prime, and g^q = 1 mod p. */
	swords = qsize / 4;
	if (swords < min_length) {
		swords = min_length;
	}
#ifdef CONFIG_CMRT_PKE_32_BIT
	length = swords;
	param_length = length;
#else /* 64-bit */
	length = ((swords - 1) / 2) + 1;
	param_length = length * 2;
#endif

	memcpy(pke_addr(ffdh_verify_q, NULL, param_length * 32), q, qsize);

	prime = 0;
	ret = cmrt_pke_is_probable_prime(pke, param_length * 32, ffdh_verify_q, &prime);
	if (ret) {
		goto err;
	}

	if (prime == 0) {
		FFDH_ERR(-EINVAL);
		ret = -EINVAL;
		goto err;
	}

	ret = cmrt_pke_clear_ram();
	if (ret) {
		goto err;
	}

	swords = psize / 4;
#ifdef CONFIG_CMRT_PKE_32_BIT
	length = swords;
	param_length = length;
#else /* 64-bit */
	length = ((swords - 1) / 2) + 1;
	param_length = length * 2;
#endif

	memcpy(pke_addr(ffdh_verify_mod_p, NULL, param_length * 32), p, psize);
	memcpy(pke_addr(ffdh_verify_exp_q, NULL, param_length * 32), q, qsize);
	memcpy(pke_addr(ffdh_verify_g, NULL, param_length * 32), g, gsize);

	cmrt_pke_issue_mcg_command(pke, MCG_PREPARE_COMMAND(MOD_EXP, 0, 0, length));

	ret = cmrt_pke_wait();
	if (ret) {
		goto err;
	}

	if (maucmp(R_MAU_ONE, SLOT(0), length) != MAU_EQ) {
		FFDH_ERR(-EINVAL);
		ret = -EINVAL;
	} else {
		ret = cmrt_pke_complete(pke);
	}

err:
	return ret;
}

#ifdef CONFIG_USERSPACE
#include <syscall_handler.h>

extern void z_syscall_verify_pke_context(cmrt_pke_t context);

static inline int z_vrfy_cmrt_pke_ffdh(cmrt_pke_t pke, const struct cmrt_ffdh_param *param,
		  const uint8_t *priv_key, const uint8_t *peer_key,
		  uint8_t *pub_key, uint8_t *shared_key)
{
	z_syscall_verify_pke_context(pke);

	Z_OOPS(Z_SYSCALL_MEMORY_READ(param, sizeof(struct cmrt_ffdh_param)));

	size_t mod_size = param->mod_size;
	size_t q_size = param->grp_size;
	/* size_t g_size = param->gen_size; */

	Z_OOPS(Z_SYSCALL_MEMORY_READ(priv_key, q_size));

	if (peer_key != NULL) {
		Z_OOPS(Z_SYSCALL_MEMORY_READ(peer_key, mod_size));
	}

	if (pub_key != NULL) {
		Z_OOPS(Z_SYSCALL_MEMORY_WRITE(pub_key, mod_size));
	}

	if (shared_key != NULL) {
		Z_OOPS(Z_SYSCALL_MEMORY_WRITE(shared_key, mod_size));
	}

	return z_impl_cmrt_pke_ffdh(pke, param, priv_key, peer_key, pub_key, shared_key);
}
#include <syscalls/cmrt_pke_ffdh_mrsh.c>

static inline int z_vrfy_cmrt_pke_ffdh_private_keygen(cmrt_pke_t pke, size_t q_size, const uint8_t *q, uint8_t *priv_key)
{
	z_syscall_verify_pke_context(pke);

	Z_OOPS(Z_SYSCALL_MEMORY_READ(q, q_size));
	Z_OOPS(Z_SYSCALL_MEMORY_WRITE(priv_key, q_size));

	return z_impl_cmrt_pke_ffdh_private_keygen(pke, q_size, q, priv_key);
}
#include <syscalls/cmrt_pke_ffdh_private_keygen_mrsh.c>

static inline int z_vrfy_cmrt_pke_ffdh_verify(cmrt_pke_t pke, const struct cmrt_ffdh_param *param)
{
	z_syscall_verify_pke_context(pke);

	Z_OOPS(Z_SYSCALL_MEMORY_READ(param, sizeof(struct cmrt_ffdh_param)));

	return z_impl_cmrt_pke_ffdh_verify(pke, param);
}
#include <syscalls/cmrt_pke_ffdh_verify_mrsh.c>

#endif /* CONFIG_USERSPACE */
