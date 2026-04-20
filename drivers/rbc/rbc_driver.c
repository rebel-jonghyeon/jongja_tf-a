/*
 * Copyright 2024 Samsung Electronics Co., Ltd. All Rights Reserved.
 *
 * PROPRIETARY/CONFIDENTIAL
 *
 * This software is the confidential and proprietary information of
 * Samsung Electronics Co., Ltd. ("Confidential Information").
 * You shall not disclose such Confidential Information and shall use it only
 * in accordance with the terms of the license agreement you entered into with
 * Samsung Electronics Co., Ltd. ("SAMSUNG").
 *
 * SAMSUNG MAKES NO REPRESENTATIONS OR WARRANTIES ABOUT THE SUITABILITY OF
 * THE SOFTWARE, EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, OR
 * NON-INFRINGEMENT. SAMSUNG SHALL NOT BE LIABLE FOR ANY DAMAGES SUFFERED BY
 * LICENSEE AS A RESULT OF USING, MODIFYING OR DISTRIBUTING THIS SOFTWARE OR
 * ITS DERIVATIVES.
 *
 */
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <rebel_h_platform.h>
#include <cmu.h>
#include <pmu.h>
#include "sysreg_rbc.h"
#include "sysreg_ebus_r.h"
#include "sysreg_nbus_u.h"
#include "sysreg_sbus_d.h"
#include "aw_ucie.h"
#include "aw_ucie_reg.h"
#include "rbc_driver.h"
#include <rl_errors.h>
#include <printf.h>

static void * const cmu_rbc_base_arr[NUM_OF_BLK_RBC_ID] = {
	(void *)CMU_RBC_H00_PRIVATE, (void *)CMU_RBC_H01_PRIVATE,
	(void *)CMU_RBC_V00_PRIVATE, (void *)CMU_RBC_V01_PRIVATE,
	(void *)CMU_RBC_V10_PRIVATE, (void *)CMU_RBC_V11_PRIVATE};
static void * const sysreg_rbc_base_arr[NUM_OF_BLK_RBC_ID] = {
	(void *)SYSREG_RBC_H00_PRIVATE, (void *)SYSREG_RBC_H01_PRIVATE,
	(void *)SYSREG_RBC_V00_PRIVATE, (void *)SYSREG_RBC_V01_PRIVATE,
	(void *)SYSREG_RBC_V10_PRIVATE, (void *)SYSREG_RBC_V11_PRIVATE};
static void * const ucie_ss_base_arr[NUM_OF_BLK_RBC_ID] = {
	(void *)UCIE_SS0_H_PRIVATE, (void *)UCIE_SS1_H_PRIVATE,
	(void *)UCIE_SS0_V0_PRIVATE, (void *)UCIE_SS1_V0_PRIVATE,
	(void *)UCIE_SS0_V1_PRIVATE, (void *)UCIE_SS1_V1_PRIVATE};

#ifdef USE_DILIGENT_PTR
	#include "diligent_ptr.h"
	struct diligent_ptr < struct cmu_rbc > cmu_rbc_reg[NUM_OF_BLK_RBC_ID];
	struct diligent_ptr < struct cmu_rbc > target_cmu_rbc;
	struct diligent_ptr < struct sysreg_rbc > sysreg_rbc_reg[NUM_OF_BLK_RBC_ID];
	struct diligent_ptr < struct sysreg_rbc > target_sysreg_rbc;
#else
	#include <FreeRTOS.h>
	#include <driver.h>
	volatile struct cmu_rbc *cmu_rbc_reg[NUM_OF_BLK_RBC_ID];
	static volatile struct cmu_rbc *target_cmu_rbc;
	volatile struct sysreg_rbc *sysreg_rbc_reg[NUM_OF_BLK_RBC_ID];
	static volatile struct sysreg_rbc *target_sysreg_rbc;
#endif

static int32_t target_blk_id = -1;

#define CHECK_TARGET_RBC_BLK_ID()	do { \
										if (target_blk_id == -1) { \
											return RL_NOTREADY; } \
									} while (0)

int32_t rbc_driver_init(int32_t blk_id,
						void * const cmu_rbc_base, void * const sysreg_rbc_base, void * const ucie_ss_base)
{
	if (blk_id >= NUM_OF_BLK_RBC_ID) {
		return RL_BADARG;
	}
	cmu_rbc_reg[blk_id] = (struct cmu_rbc *)cmu_rbc_base;
	sysreg_rbc_reg[blk_id] = (struct sysreg_rbc *)sysreg_rbc_base;

	return aw_ucie_init(blk_id, ucie_ss_base);
}

int32_t rbc_set_target_blk_id(int32_t blk_id)
{
	if (blk_id >= NUM_OF_BLK_RBC_ID) {
		return RL_BADARG;
	} else if (cmu_rbc_reg[blk_id] == 0 || sysreg_rbc_reg[blk_id] == 0) {
		return RL_NOTREADY;
	}

	target_blk_id = blk_id;
	target_cmu_rbc = cmu_rbc_reg[target_blk_id];
	target_sysreg_rbc = sysreg_rbc_reg[target_blk_id];

	return aw_ucie_set_target_ss(blk_id);
}

int32_t rbc_get_target_blk_id(void)
{
	return target_blk_id;
}

int32_t rbc_set_lp_mode(uint32_t lp_mode)
{
	CHECK_TARGET_RBC_BLK_ID();

	if (lp_mode == 1)
		aw_ucie_clear_link_cap_APMW();
	else if (lp_mode == 2)
		aw_ucie_set_link_cap_APMW();
	else
		return RL_BADARG;

	return RL_OK;
}

static int32_t _lp_trigger(void)
{
	CHECK_TARGET_RBC_BLK_ID();

	target_sysreg_rbc->ucie_ss0_int2.ext_int2 = 1;
	target_sysreg_rbc->ucie_ss0_int2.ext_int2 = 0;

	uint32_t rdata = 0;

	do {
		aw_ucie_get_cmn_mcu_scratch_reg1(&rdata);
	} while (rdata != 0xFFFFFFFF);

	return RL_OK;
}

int32_t rbc_lp_entry(void)
{
	return _lp_trigger();
}

int32_t rbc_lp_exit(void)
{
	return _lp_trigger();
}

int32_t rbc_pch_mux_on(void)
{
	CHECK_TARGET_RBC_BLK_ID();
	volatile struct sysreg_ebus_r *target_sysreg_xbus = NULL;
	uint64_t base_addr = 0;

	switch (target_blk_id) {
	case BLK_RBC_H00_ID:
	case BLK_RBC_H01_ID:
		base_addr = SYSREG_EBUS_R;
		break;
	case BLK_RBC_V00_ID:
	case BLK_RBC_V01_ID:
		base_addr = SYSREG_NBUS_U;
		break;
	case BLK_RBC_V10_ID:
	case BLK_RBC_V11_ID:
		base_addr = SYSREG_SBUS_D;
		break;
	default:
		return RL_ERROR;
	}

	/* For convenience, the ebus_r structure is used for common use. */
	target_sysreg_xbus = (volatile struct sysreg_ebus_r *)(base_addr);

	if (target_blk_id & 0x1) {
		while (target_sysreg_xbus->rbc_h01_pch_mux_ro.o_paccept_sfr) {
			}
		target_sysreg_xbus->rbc_h01_pch_mux_sel.i_pch_mux_sel = 1;
		target_sysreg_xbus->rbc_h01_pch_mux_pstate.i_pstate_sfr = 1;
		target_sysreg_xbus->rbc_h01_pch_mux_preq.i_preq_sfr = 1;
		while (!target_sysreg_xbus->rbc_h01_pch_mux_ro.o_paccept_sfr) {
			}
		target_sysreg_xbus->rbc_h01_pch_mux_preq.i_preq_sfr = 0;
		while (target_sysreg_xbus->rbc_h01_pch_mux_ro.o_paccept_sfr) {
			}
	} else {
		while (target_sysreg_xbus->rbc_h00_pch_mux_ro.o_paccept_sfr) {
			}
		target_sysreg_xbus->rbc_h00_pch_mux_sel.i_pch_mux_sel = 1;
		target_sysreg_xbus->rbc_h00_pch_mux_pstate.i_pstate_sfr = 1;
		target_sysreg_xbus->rbc_h00_pch_mux_preq.i_preq_sfr = 1;
		while (!target_sysreg_xbus->rbc_h00_pch_mux_ro.o_paccept_sfr) {
			}
		target_sysreg_xbus->rbc_h00_pch_mux_preq.i_preq_sfr = 0;
		while (target_sysreg_xbus->rbc_h00_pch_mux_ro.o_paccept_sfr) {
			}
	}

	return RL_OK;
}

int32_t rbc_pch_mux_off(void)
{
	CHECK_TARGET_RBC_BLK_ID();
	volatile struct sysreg_ebus_r *target_sysreg_xbus = NULL;
	uint64_t base_addr = 0;

	switch (target_blk_id) {
	case BLK_RBC_H00_ID:
	case BLK_RBC_H01_ID:
		base_addr = SYSREG_EBUS_R;
		break;
	case BLK_RBC_V00_ID:
	case BLK_RBC_V01_ID:
		base_addr = SYSREG_NBUS_U;
		break;
	case BLK_RBC_V10_ID:
	case BLK_RBC_V11_ID:
		base_addr = SYSREG_SBUS_D;
		break;
	default:
		return RL_ERROR;
	}

	/* For convenience, the ebus_r structure is used for common use. */
	target_sysreg_xbus = (volatile struct sysreg_ebus_r *)(base_addr);

	if (target_blk_id & 0x1) {
		while (target_sysreg_xbus->rbc_h01_pch_mux_ro.o_paccept_sfr) {
			}
		target_sysreg_xbus->rbc_h01_pch_mux_pstate.i_pstate_sfr = 0;
		target_sysreg_xbus->rbc_h01_pch_mux_preq.i_preq_sfr = 1;
		while (!target_sysreg_xbus->rbc_h01_pch_mux_ro.o_paccept_sfr) {
			}
		target_sysreg_xbus->rbc_h01_pch_mux_preq.i_preq_sfr = 0;
		while (target_sysreg_xbus->rbc_h01_pch_mux_ro.o_paccept_sfr) {
			}
		target_sysreg_xbus->rbc_h01_pch_mux_sel.i_pch_mux_sel = 0;
	} else {
		while (target_sysreg_xbus->rbc_h00_pch_mux_ro.o_paccept_sfr) {
			}
		target_sysreg_xbus->rbc_h00_pch_mux_pstate.i_pstate_sfr = 0;
		target_sysreg_xbus->rbc_h00_pch_mux_preq.i_preq_sfr = 1;
		while (!target_sysreg_xbus->rbc_h00_pch_mux_ro.o_paccept_sfr) {
			}
		target_sysreg_xbus->rbc_h00_pch_mux_preq.i_preq_sfr = 0;
		while (target_sysreg_xbus->rbc_h00_pch_mux_ro.o_paccept_sfr) {
			}
		target_sysreg_xbus->rbc_h00_pch_mux_sel.i_pch_mux_sel = 0;
	}

	return RL_OK;
}

static void _print_line(const uint32_t **eom_diagram_plot, uint32_t module_sel, uint32_t lane_id)
{
	for (int i = 0; i < INIT_VREF_OFFSET * 2 + 1; i++) {
		for (int j = 0; j < EOM_LINE_LENGTH; j++) {
			printf("%d ", eom_diagram_plot[i][j]);
		}
		printf("\n");
	}
}

int32_t rbc_aw_ucie_print_eye_diagram(uint32_t module_sel, uint32_t lane_id, uint32_t iter_max)
{
	CHECK_TARGET_RBC_BLK_ID();

	uint32_t **eom_diagram_plot;
#ifdef USE_DILIGENT_PTR
	eom_diagram_plot = (uint32_t **)malloc(sizeof(uint32_t *) * (2 * INIT_VREF_OFFSET + 1));
	if (!eom_diagram_plot) {
		return RL_NOMEM;
	}
	for (int i = 0; i < 2 * INIT_VREF_OFFSET + 1; i++) {
		eom_diagram_plot[i] = (uint32_t *)malloc(sizeof(uint32_t) * EOM_LINE_LENGTH);
		if (!eom_diagram_plot[i]) {
			for (int j = 0; j < i; j++) {
				free(eom_diagram_plot[j]);
			}
			free(eom_diagram_plot);
			return RL_NOMEM;
		}
	}
#else
	eom_diagram_plot = (uint32_t **)pvPortMalloc(sizeof(uint32_t *) * (2 * INIT_VREF_OFFSET + 1));
	if (!eom_diagram_plot) {
		return RL_NOMEM;
	}
	for (int i = 0; i < 2 * INIT_VREF_OFFSET + 1; i++) {
		eom_diagram_plot[i] = (uint32_t *)pvPortMalloc(sizeof(uint32_t) * EOM_LINE_LENGTH);
		if (!eom_diagram_plot[i]) {
			for (int j = 0; j < i; j++) {
				free(eom_diagram_plot[j]);
			}
			free(eom_diagram_plot);
			return RL_NOMEM;
		}
	}
#endif /* USE_DILIGENT_PTR */
	for (int i = 0; i < 2 * INIT_VREF_OFFSET + 1; i++) {
		memset(eom_diagram_plot[i], 0, sizeof(uint32_t) * EOM_LINE_LENGTH);
	}
	uint32_t eml;
	uint32_t emr;

	for (uint32_t iter_cnt = 0; iter_cnt < iter_max; iter_cnt++) {
		for (int i = INIT_VREF_OFFSET; i > 0; i--) {
			aw_ucie_set_rx_vref_offset(module_sel, RX_VREF_OFFSET_EN_ADD);
			aw_ucie_set_rx_vref_offset_enable(module_sel, i);
			aw_ucie_retrain_and_get_new_eml_emr(module_sel, &eml, &emr, lane_id);
			eom_diagram_plot[INIT_VREF_OFFSET + i][EOM_LINE_LENGTH / 2 - 1 - eml]++;
			eom_diagram_plot[INIT_VREF_OFFSET + i][EOM_LINE_LENGTH / 2 + emr]++;
		}
		for (int i = 0; i < INIT_VREF_OFFSET; i++) {
			aw_ucie_set_rx_vref_offset(module_sel, RX_VREF_OFFSET_EN_SUB);
			aw_ucie_set_rx_vref_offset_enable(module_sel, i);
			aw_ucie_retrain_and_get_new_eml_emr(module_sel, &eml, &emr, lane_id);
			eom_diagram_plot[INIT_VREF_OFFSET - i][EOM_LINE_LENGTH / 2 - 1 - eml]++;
			eom_diagram_plot[INIT_VREF_OFFSET - i][EOM_LINE_LENGTH / 2 + emr]++;
		}
		_print_line((const uint32_t **)eom_diagram_plot, module_sel, lane_id);
	}

#ifdef USE_DILIGENT_PTR
	for (int i = 0; i < 2 * INIT_VREF_OFFSET + 1; i++) {
		if (eom_diagram_plot[i]) {
			free(eom_diagram_plot[i]);
		}
	}
	free(eom_diagram_plot);
#else
	for (int i = 0; i < 2 * INIT_VREF_OFFSET + 1; i++) {
		if (eom_diagram_plot[i]) {
			vPortFree(eom_diagram_plot[i]);
		}
	}
	vPortFree(eom_diagram_plot);
#endif /* USE_DILIGENT_PTR */

	return RL_OK;
}

#if defined(__RUN_RTOS)
#define NUM_OF_CHIPS		(4)
#define NUM_OF_ACTIVE_RBC	(4)

int32_t rbc_init_ret[NUM_OF_BLK_RBC_ID + 1];

int rebel_h_rbc_init(void)
{
	static const uint64_t active_rbc_base[NUM_OF_CHIPS/* chip id */][NUM_OF_ACTIVE_RBC] = {
	{
		BLK_RBC_V10_ID, BLK_RBC_V11_ID,
		BLK_RBC_H00_ID, BLK_RBC_H01_ID
	},
	{
		BLK_RBC_V01_ID, BLK_RBC_V00_ID,
		BLK_RBC_H00_ID, BLK_RBC_H01_ID
	},
	{
		BLK_RBC_V00_ID, BLK_RBC_V01_ID,
		BLK_RBC_H00_ID, BLK_RBC_H01_ID
	},
	{
		BLK_RBC_V11_ID, BLK_RBC_V10_ID,
		BLK_RBC_H00_ID, BLK_RBC_H01_ID
	}};

	uint64_t chiplet_id = CHIPLET_ID;
	uint32_t num_of_chips = pmu_get_num_of_secondary_chiplet() + 1;
	uint32_t num_of_active_rbc = 0;

	if (num_of_chips == 1) {
		num_of_active_rbc = 0;
	} else if (num_of_chips == 2) {
		num_of_active_rbc = 2;
	} else {
		num_of_active_rbc = 4;
	}

	for (uint32_t idx = 0; idx < num_of_active_rbc; idx++) {
		const uint32_t blk_id = active_rbc_base[chiplet_id][idx];

		rbc_init_ret[blk_id] = rbc_driver_init(blk_id, cmu_rbc_base_arr[blk_id],
											   sysreg_rbc_base_arr[blk_id], ucie_ss_base_arr[blk_id]);

		if (!rbc_init_ret[blk_id]) {
			aw_ucie_set_target_ss(blk_id);

			aw_ucie_set_corr_err_mask(0, 0, 0, 0, 0);
			aw_ucie_set_uncorr_err_mask(0, 0, 0, 0, 0, 0);

			union aw_ucie_global_reg_reg_global_intr1_summary_mask intr_mask;

			aw_ucie_get_intr_summary_mask(&intr_mask.val);
			intr_mask.val = 0;/* WA for REBELH-796 */
			aw_ucie_set_intr_summary_mask(intr_mask.val);

			aw_ucie_set_corr_err_noti(1, 1);
			aw_ucie_set_non_fatal_uncorr_err_noti(1, 1);
			aw_ucie_set_fatal_uncorr_err_noti(1, 1);
		}
	}

	return 0;
}

DRIVER_INIT_ENTRY_DEFINE(1, rebel_h_rbc_init);
#endif
