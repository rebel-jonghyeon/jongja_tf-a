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

int cmrt_pke_blind_rsa_crt_key_internal(cmrt_pke_t pke, cmrt_rsa_key_t ctx, uint8_t update)
{
	int status;

	uint32_t mask;
	uint32_t iqmask;
	uint32_t mask_length;
	uint32_t blength;
	uint32_t pke_length;
	uint32_t copy_length;

	uint32_t *new_mask;
	uint32_t *old_mask;
	uint32_t *iq_mask;

	if (!pke || !ctx) {
		status = -EINVAL;
		goto err;
	}

	blength = (ctx->bits / 8) / sizeof(uint8_t);
#ifdef CONFIG_CMRT_PKE_32_BIT
	mask_length = ((ctx->bits / 16) / sizeof(uint32_t)) + 2;
#else /* 64-bit */
	mask_length = ((ctx->bits / 16) / sizeof(uint64_t)) + 1;
#endif
	pke_length = ((ctx->bits / 16) / sizeof(uint32_t)) + 2;

	old_mask = pke_addr(rsa_blind_old_mask, NULL, pke_length * 32);
	new_mask = pke_addr(rsa_blind_new_mask, NULL, pke_length * 32);
	iq_mask = pke_addr(rsa_blind_iq_mask, NULL, pke_length * 32);

	/* ------------------------------------------------------------------------------------------------------------------
	 * Start PRNG and Generate masks
	 * ----------------------------------------------------------------------------------------------------------------*/
	status = cmrt_pke_get_pseudo_random((uint8_t *)&mask, sizeof(uint32_t), CMRT_PKE_NO_SLOT, 0);
	if (status) {
		goto err;
	}
	/* mask is required to be odd, and an extra bit is zeroed to catch any carry from additions */
	mask = (mask | 0x40000001) & 0x7FFFFFFF;

	if (ctx->iq != NULL) {
		status = cmrt_pke_get_pseudo_random((uint8_t *)&iqmask, sizeof(uint32_t), CMRT_PKE_NO_SLOT, 0);
		if (status) {
			goto err;
		}
		iqmask = iqmask & 0x0FFFFFFF;
	}

	status = cmrt_pke_clear_ram();
	if (status) {
		goto err;
	}
	/* ------------------------------------------------------------------------------------------------------------------
	 * Load Parameters
	 * ----------------------------------------------------------------------------------------------------------------*/
	ISSUE_MAU_COMMAND(SET_RAM_SLOTS, MAU_SRAM_OFFSET, mask_length);

	status = cmrt_pke_wait();
	if (status) {
		goto err;
	}

	old_mask[0] = ((uint32_t *)ctx->mask)[0];
	if (*old_mask == 0) {
		copy_length = blength / 2;
	} else {
		copy_length = blength / 2 + 4 * sizeof(uint8_t);
	}

	memcpy(pke_addr(rsa_blind_p, NULL, pke_length * 32), ctx->p, copy_length);
	memcpy(pke_addr(rsa_blind_q, NULL, pke_length * 32), ctx->q, copy_length);
	memcpy(pke_addr(rsa_blind_dp, NULL, pke_length * 32), ctx->dp, copy_length);
	memcpy(pke_addr(rsa_blind_dq, NULL, pke_length * 32), ctx->dq, copy_length);

	if (ctx->iq != NULL) {
		memcpy(pke_addr(rsa_blind_iq, NULL, pke_length * 32), ctx->iq, copy_length);
	}

	*new_mask = mask;
	*iq_mask = iqmask;

	ISSUE_MAU_COMMAND(SET_RAM_SLOTS, MAU_SRAM_OFFSET, mask_length);

	static const uint32_t command_sequence_1[] = {
		SLOT_CMD(LOAD,          SLOT(rsa_blind_p)),
		SLOT_CMD(INT_ADD,       SLOT(rsa_blind_dp)),
		SLOT_CMD(INT_SUB,       R_MAU_ONE),
		SLOT_CMD(STORE,         SLOT(rsa_blind_dp)),
		SLOT_CMD(LOAD,          SLOT(rsa_blind_q)),
		SLOT_CMD(INT_ADD,       SLOT(rsa_blind_dq)),
		SLOT_CMD(INT_SUB,       R_MAU_ONE),
		SLOT_CMD(STORE,         SLOT(rsa_blind_dq)),
	};

	if (*old_mask == 0) {
		*old_mask = 1;
		status = cmrt_pke_mau_command_sequence(command_sequence_1, sizeof(command_sequence_1)/sizeof(uint32_t), mask_length);
		if (status) {
			goto err;
		}
	}

	static const uint32_t  command_sequence_2[] = {
		/* ------------------------------------------------------------------------------------------------------------------
		 * Reblind p
		 * ----------------------------------------------------------------------------------------------------------------*/
		SLOT_CMD(SET_MAND,            SLOT(rsa_blind_tmp)),
		SLOT_CMD(COPY,                SLOT(rsa_blind_p)),
		SLOT_CMD(INT_MUL,             SLOT(rsa_blind_new_mask)),
		SLOT_CMD(INT_DIV_SMALL_EXACT, SLOT(rsa_blind_old_mask)),
		SLOT_CMD(SET_MAND,            SLOT(rsa_blind_tmp2)),
		SLOT_CMD(COPY,                R_MAU_ADDR_RNG),
		SLOT_CMD(COPY,                SLOT(rsa_blind_p)),
		SLOT_CMD(INT_MUL,             SLOT(rsa_blind_iq_mask)),
		SLOT_CMD(INT_DIV_SMALL_EXACT, SLOT(rsa_blind_old_mask)),
		/* ------------------------------------------------------------------------------------------------------------------
		 * Replace multiples of p
		 * ----------------------------------------------------------------------------------------------------------------*/
		SLOT_CMD(SET_PARAMS,          SLOT(rsa_blind_tmp)),
		SLOT_CMD(LOAD,                SLOT(rsa_blind_iq)),
		SLOT_CMD(MOD_ADD,             SLOT(rsa_blind_tmp2)),
		SLOT_CMD(CANON,               0),
		SLOT_CMD(SET_MAND,            SLOT(rsa_blind_iq)),
		SLOT_CMD(COPY,                R_MAU_ADDR_RNG),
		SLOT_CMD(STORE,               SLOT(rsa_blind_iq)),

		SLOT_CMD(SET_MAND,            SLOT(rsa_blind_tmp2)),
		SLOT_CMD(COPY,                R_MAU_ADDR_RNG),
		SLOT_CMD(MONT_MUL,            SLOT(rsa_blind_tmp2)), /* dummy multiplication */

		SLOT_CMD(LOAD,                SLOT(rsa_blind_dp)),
		SLOT_CMD(INT_ADD,             SLOT(rsa_blind_tmp)),
		SLOT_CMD(INT_SUB,             SLOT(rsa_blind_new_mask)),
		SLOT_CMD(INT_SUB,             SLOT(rsa_blind_p)),
		SLOT_CMD(INT_ADD,             SLOT(rsa_blind_old_mask)),
		SLOT_CMD(SET_MAND,            SLOT(rsa_blind_dp)),
		SLOT_CMD(COPY,                R_MAU_ADDR_RNG),
		SLOT_CMD(STORE,               SLOT(rsa_blind_dp)),
		/* ------------------------------------------------------------------------------------------------------------------
		 * Overwrite p
		 * ----------------------------------------------------------------------------------------------------------------*/
		SLOT_CMD(SET_MAND,            SLOT(rsa_blind_p)),
		SLOT_CMD(COPY,                R_MAU_ADDR_RNG),
		SLOT_CMD(COPY,                SLOT(rsa_blind_tmp)),
		/* ------------------------------------------------------------------------------------------------------------------
		 * Reblind q
		 * ----------------------------------------------------------------------------------------------------------------*/
		SLOT_CMD(SET_MAND,            SLOT(rsa_blind_tmp)),
		SLOT_CMD(COPY,                R_MAU_ADDR_RNG),
		SLOT_CMD(COPY,                SLOT(rsa_blind_q)),
		SLOT_CMD(INT_MUL,             SLOT(rsa_blind_new_mask)),
		SLOT_CMD(INT_DIV_SMALL_EXACT, SLOT(rsa_blind_old_mask)),
		/* ------------------------------------------------------------------------------------------------------------------
		 * Replace multiples of q
		 * ----------------------------------------------------------------------------------------------------------------*/
		SLOT_CMD(LOAD,                SLOT(rsa_blind_dq)),
		SLOT_CMD(INT_ADD,             SLOT(rsa_blind_tmp)),
		SLOT_CMD(INT_SUB,             SLOT(rsa_blind_new_mask)),
		SLOT_CMD(INT_SUB,             SLOT(rsa_blind_q)),
		SLOT_CMD(INT_ADD,             SLOT(rsa_blind_old_mask)),
		SLOT_CMD(SET_MAND,            SLOT(rsa_blind_dq)),
		SLOT_CMD(COPY,                R_MAU_ADDR_RNG),
		SLOT_CMD(STORE,               SLOT(rsa_blind_dq)),
		/* ------------------------------------------------------------------------------------------------------------------
		 * Overwrite q
		 * ----------------------------------------------------------------------------------------------------------------*/
		SLOT_CMD(SET_MAND,            SLOT(rsa_blind_q)),
		SLOT_CMD(COPY,                R_MAU_ADDR_RNG),
		SLOT_CMD(COPY,                SLOT(rsa_blind_tmp)),
	};

	status = cmrt_pke_mau_command_sequence(command_sequence_2, sizeof(command_sequence_2)/sizeof(uint32_t), mask_length);
	if (status) {
		goto err;
	}

	/* ------------------------------------------------------------------------------------------------------------------
	 * Update Key
	 * ----------------------------------------------------------------------------------------------------------------*/
	if (update == 1) {
		copy_length = blength / 2 + 4 * sizeof(uint8_t);

		((uint32_t *)ctx->mask)[0] = new_mask[0];

		memcpy(ctx->p, pke_addr(rsa_blind_p, NULL, pke_length * 32), copy_length);
		memcpy (ctx->q, pke_addr(rsa_blind_q, NULL, pke_length * 32), copy_length);
		memcpy (ctx->dp, pke_addr(rsa_blind_dp, NULL, pke_length * 32), copy_length);
		memcpy (ctx->dq, pke_addr(rsa_blind_dq, NULL, pke_length * 32), copy_length);

		if (ctx->iq != NULL) {
			memcpy (ctx->iq, pke_addr(rsa_blind_iq, NULL, pke_length * 32), copy_length);
		}

		memcpy (ctx->mask, pke_addr(rsa_blind_new_mask, NULL, pke_length * 32), 4);

		status = cmrt_pke_clear_ram();
#ifdef CONFIG_CMRT_PKE_32_BIT
	} else { /* repack values for shorter slot length */
		ISSUE_MAU_COMMAND(SET_RAM_SLOTS, MAU_SRAM_OFFSET, mask_length);
		ISSUE_MAU_COMMAND(LOAD, SLOT(0), mask_length - 1);
		ISSUE_MAU_COMMAND(SET_MAND, SLOT(7), mask_length - 1);
		ISSUE_MAU_COMMAND(COPY, R_MAU_ADDR_RNG, mask_length - 1);
		ISSUE_MAU_COMMAND(STORE, SLOT(7), mask_length - 1);

		for (int i = 1; i < 6; i++) {
			ISSUE_MAU_COMMAND(SET_RAM_SLOTS, MAU_SRAM_OFFSET, mask_length);
			ISSUE_MAU_COMMAND(LOAD, SLOT(i), mask_length - 1);
			ISSUE_MAU_COMMAND(SET_MAND, SLOT(0), mask_length - 1);
			ISSUE_MAU_COMMAND(COPY, R_MAU_ADDR_RNG, mask_length - 1);
			ISSUE_MAU_COMMAND(STORE, SLOT(0), mask_length - 1);
			ISSUE_MAU_COMMAND(SET_RAM_SLOTS, MAU_SRAM_OFFSET, mask_length - 1);
			ISSUE_MAU_COMMAND(LOAD, SLOT(0), mask_length - 1);
			ISSUE_MAU_COMMAND(SET_MAND, SLOT(i), mask_length - 1);
			ISSUE_MAU_COMMAND(COPY, R_MAU_ADDR_RNG, mask_length - 1);
			ISSUE_MAU_COMMAND(STORE, SLOT(i), mask_length - 1);
		}

		ISSUE_MAU_COMMAND(SET_RAM_SLOTS, MAU_SRAM_OFFSET, mask_length);
		ISSUE_MAU_COMMAND(LOAD, SLOT(7), mask_length - 1);
		ISSUE_MAU_COMMAND(SET_MAND, SLOT(0), mask_length - 1);
		ISSUE_MAU_COMMAND(COPY, R_MAU_ADDR_RNG, mask_length - 1);
		ISSUE_MAU_COMMAND(STORE, SLOT(0), mask_length - 1);

		status = cmrt_pke_wait();
		if (status) {
			goto err;
		}
#endif
	}

err:
	return(status);
}

int cmrt_pke_blind_rsa_crt_key(cmrt_pke_t pke, cmrt_rsa_key_t ctx)
{
	if (!pke || !ctx) {
		return -EINVAL;
	}

	return cmrt_pke_blind_rsa_crt_key_internal(pke, ctx, 1);
}
