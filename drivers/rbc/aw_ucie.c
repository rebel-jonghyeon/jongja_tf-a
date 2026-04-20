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

#include "aw_ucie.h"
#include "registers/aw_ucie_reg.h"
#include "timer.h"
#include "rl_errors.h"
#include "rl_utils.h"
#include "gic.h"
#include <stdbool.h>
#include <driver.h>
#ifdef USE_DILIGENT_PTR
	#include "diligent_ptr.h"
	struct diligent_ptr < struct aw_ucie > reg[NUM_OF_UCIE_SS_ID];
	struct diligent_ptr < struct aw_ucie > target_ss;
#else
	static volatile struct aw_ucie *reg[NUM_OF_UCIE_SS_ID];
	static volatile struct aw_ucie *target_ss;
#endif
static int32_t target_ss_id = -1;

#define FATAL						(1)
#define NON_FATAL					(0)
#define UCIE_SS_INTR_PRIORITY		(1)
#define CHECK_TARGET_UCIE_SS()	do { \
									if (target_ss_id == -1)	\
										return RL_NOTREADY;	\
								} while (0)
#define CHECK_UCIE_MBOX_ARG(op)	\
		do { \
			if (rl > 0x3 || !buf)	\
				return RL_BADARG;	\
			if (((op) == UCIE_SB_32B_MEM_RD || (op) == UCIE_SB_32B_MEM_WR) || \
				((op) == UCIE_SB_64B_MEM_RD || (op) == UCIE_SB_64B_MEM_WR)) {	\
				if ((offset & ~((1 << 20) - 1)) != 0)	\
					return RL_BADARG; \
				}	\
			else if (((op) == UCIE_SB_32B_CONFIG_RD || (op) == UCIE_SB_32B_CONFIG_WR) ||	\
					((op) == UCIE_SB_64B_CONFIG_RD || (op) == UCIE_SB_64B_CONFIG_WR)) {	\
				if ((offset & ~((1 << 12) - 1)) != 0)	\
					return RL_BADARG; \
				}	\
			else {	\
				/* do nothing */	\
				} \
		} while (0)

static const uint32_t ucie_ss_intr_id[] = {
	BLK_RBC_H00_UCIE_INTR_ID,
	BLK_RBC_H01_UCIE_INTR_ID,
	BLK_RBC_V00_UCIE_INTR_ID,
	BLK_RBC_V01_UCIE_INTR_ID,
	BLK_RBC_V10_UCIE_INTR_ID,
	BLK_RBC_V11_UCIE_INTR_ID,
};

/* This must be maintained to match the string array(UCIE_INTR_STRING) below. */
enum {
	LINK_STAT_CHANGED = 0,
	HW_AUTO_BW_CHANGED,
	ADAPTER_TIMEOUT,
	RECEIVER_OVERFLOW,
	INTERNAL_ERROR,
	SB_FATAL_ERR_MSG_RCV,
	SB_NON_FATAL_ERR_MSG_RCV,
	INVALID_PARAM_EXCHANGE,
	CRC_ERROR_DETECTED,
	ADAPTER_LSM_TRANS_TO_RETRAIN,
	CORRECTABLE_INTERNAL_ERROR,
	SB_CORRECTABLE_ERR_MSG_RCV,
	RUNTIME_LINK_TESTING_PARITY_ERR,
	NUM_OF_UCIE_INTR_REASON,
	UNKNOWN_REASON,
	INVALID_CORR_ERR,
	INVALID_NON_FATAL_UNCORR_ERR,
	INVALID_FATAL_UNCORR_ERR,
	EMPTY_LOG,
};

static const char * const UCIE_INTR_STRING[NUM_OF_UCIE_INTR_REASON] = {
	"Link Status changed.",
	"HW autonomous BW changed.",
	"Adapter Timeout.",
	"Receiver Overflow.",
	"Internal Error.",
	"Sideband Fatal Error Message received.",
	"Sideband Non-Fatal Error Message received.",
	"Invalid Parameter Exchange.",
	"CRC Error Detected.",
	"Adapter LSM transition to Retrain.",
	"Correctable Internal Error.",
	"Sideband Correctable Error Message received.",
	"Runtime Link Testing Parity Error."
};

static const char * const UNKNOWN_INTR_STRING = "Unknown interrupt source.";
static const char * const INV_CORR_ERR_INTR_STR = "Corr err asserted but all status are clean.";
static const char * const INV_NON_FATAL_UNCORR_ERR_INTR_STR = "Non-fatal Uncorr err asserted but all status are clean.";
static const char * const INV_FATAL_UNCORR_ERR_INTR_STR = "Fatal Uncorr err asserted but all status are clean.";
static const char * const EMPTY_STRING = "Empty log.";

struct intr_log_data {
	uint32_t reason_id;
	uint32_t hdr_log[3];
	uint32_t err_log[4][2];
};

static struct intr_log_data intr_log_arr[UCIE_INTR_LOG_SIZE];
static uint32_t cur_empty_log_idx;
static uint32_t intr_counter[EMPTY_LOG];

int32_t aw_ucie_clear_intr_log(void)
{
	CHECK_TARGET_UCIE_SS();

	for (uint32_t i = 0; i < UCIE_INTR_LOG_SIZE; i++) {
		intr_log_arr[i].reason_id = EMPTY_LOG;
	}

	for (uint32_t i = 0; i < EMPTY_LOG; i++) {
		intr_counter[i] = 0;
	}

	cur_empty_log_idx = 0;

	return RL_OK;
}

int32_t aw_ucie_get_intr_log_count(uint32_t * const log_cnt)
{
	if (intr_log_arr[cur_empty_log_idx].reason_id != EMPTY_LOG)
		*log_cnt = UCIE_INTR_LOG_SIZE;
	else
		*log_cnt = cur_empty_log_idx;

	return RL_OK;
}

static void _set_target_log_index_and_cnt(uint32_t *log_cnt, uint32_t *start_idx, uint32_t *active_log_cnt)
{
	if (*log_cnt > UCIE_INTR_LOG_SIZE)
		*log_cnt = UCIE_INTR_LOG_SIZE;

	if (intr_log_arr[cur_empty_log_idx].reason_id != EMPTY_LOG) {
		*active_log_cnt = UCIE_INTR_LOG_SIZE;
		*start_idx = cur_empty_log_idx;
	} else {
		*active_log_cnt = (cur_empty_log_idx < *log_cnt) ? cur_empty_log_idx : *log_cnt;
		*start_idx = 0;
	}
}

static void _get_log_string_from_reason(const uint32_t reason_id, const char **log_string)
{
	if (reason_id < NUM_OF_UCIE_INTR_REASON)
		*log_string = UCIE_INTR_STRING[reason_id];
	else if (reason_id == EMPTY_LOG)
		*log_string = EMPTY_STRING;
	else if (reason_id == INVALID_CORR_ERR)
		*log_string = INV_CORR_ERR_INTR_STR;
	else if (reason_id == INVALID_NON_FATAL_UNCORR_ERR)
		*log_string = INV_NON_FATAL_UNCORR_ERR_INTR_STR;
	else if (reason_id == INVALID_FATAL_UNCORR_ERR)
		*log_string = INV_FATAL_UNCORR_ERR_INTR_STR;
	else
		*log_string = UNKNOWN_INTR_STRING;
}

int32_t aw_ucie_get_intr_log_arr(char log_buf[][UCIE_INTR_LOG_LEN], uint32_t log_cnt)
{
	CHECK_TARGET_UCIE_SS();

	uint32_t active_log_cnt = 0;
	uint32_t start_idx = 0;

	_set_target_log_index_and_cnt(&log_cnt, &start_idx, &active_log_cnt);

	for (uint32_t idx = start_idx, cnt = 0; cnt < active_log_cnt; idx++, cnt++) {
		const char *log_string = EMPTY_STRING;

		if (idx == UCIE_INTR_LOG_SIZE)
			idx = 0;

		_get_log_string_from_reason(intr_log_arr[idx].reason_id, &log_string);

		memcpy(log_buf[cnt], log_string, strlen(log_string));
	}

	return RL_OK;
}

int32_t aw_ucie_get_log_data(uint32_t hdr_log[][3], uint32_t err_log[][4][2], uint32_t log_cnt)
{
	CHECK_TARGET_UCIE_SS();

	uint32_t active_log_cnt = 0;
	uint32_t start_idx = 0;

	_set_target_log_index_and_cnt(&log_cnt, &start_idx, &active_log_cnt);

	for (uint32_t idx = start_idx, cnt = 0; cnt < active_log_cnt; idx++, cnt++) {
		if (idx == UCIE_INTR_LOG_SIZE)
			idx = 0;

		struct intr_log_data *intr_log = &intr_log_arr[idx];

		hdr_log[cnt][0] = intr_log->hdr_log[0];
		hdr_log[cnt][1] = intr_log->hdr_log[1];
		hdr_log[cnt][2] = intr_log->hdr_log[2];

		err_log[cnt][0][0] = intr_log->err_log[0][0];
		err_log[cnt][0][1] = intr_log->err_log[0][1];
		err_log[cnt][1][0] = intr_log->err_log[1][0];
		err_log[cnt][1][1] = intr_log->err_log[1][1];
		err_log[cnt][2][0] = intr_log->err_log[2][0];
		err_log[cnt][2][1] = intr_log->err_log[2][1];
		err_log[cnt][3][0] = intr_log->err_log[3][0];
		err_log[cnt][3][1] = intr_log->err_log[3][1];
	}

	return RL_OK;
}

int32_t aw_ucie_show_intr_counter(void)
{
	for (uint32_t reason_id = 0; reason_id < EMPTY_LOG; reason_id++) {
		const char *log_string = EMPTY_STRING;

		if (reason_id == NUM_OF_UCIE_INTR_REASON)
			continue;

		_get_log_string_from_reason(reason_id, &log_string);

		printf("%s : %d\n", log_string, intr_counter[reason_id]);
	}

	return RL_OK;
}

static void _log_intr(const uint32_t reason)
{
	intr_counter[reason]++;
	intr_log_arr[cur_empty_log_idx].reason_id = reason;

	const char *log_str = 0;

	_get_log_string_from_reason(reason, &log_str);
	printf("reason %d -> %s\n", reason, log_str);

	intr_log_arr[cur_empty_log_idx].hdr_log[0] = target_ss->adapter_d2d_reg_reg_adapter_d2d_hdr_log1_1.val;
	intr_log_arr[cur_empty_log_idx].hdr_log[1] = target_ss->adapter_d2d_reg_reg_adapter_d2d_hdr_log1_2.val;
	intr_log_arr[cur_empty_log_idx].hdr_log[2] = target_ss->adapter_d2d_reg_reg_adapter_d2d_hdr_log2.val;

	intr_log_arr[cur_empty_log_idx].err_log[0][0] = target_ss->phy_d2d_reg_reg_phy_d2d_m0_err_log0.val;
	intr_log_arr[cur_empty_log_idx].err_log[0][1] = target_ss->phy_d2d_reg_reg_phy_d2d_m0_err_log1.val;
	intr_log_arr[cur_empty_log_idx].err_log[1][0] = target_ss->phy_d2d_reg_reg_phy_d2d_m1_err_log0.val;
	intr_log_arr[cur_empty_log_idx].err_log[1][1] = target_ss->phy_d2d_reg_reg_phy_d2d_m1_err_log1.val;
	intr_log_arr[cur_empty_log_idx].err_log[2][0] = target_ss->phy_d2d_reg_reg_phy_d2d_m2_err_log0.val;
	intr_log_arr[cur_empty_log_idx].err_log[2][1] = target_ss->phy_d2d_reg_reg_phy_d2d_m2_err_log1.val;
	intr_log_arr[cur_empty_log_idx].err_log[3][0] = target_ss->phy_d2d_reg_reg_phy_d2d_m3_err_log0.val;
	intr_log_arr[cur_empty_log_idx].err_log[3][1] = target_ss->phy_d2d_reg_reg_phy_d2d_m3_err_log1.val;

	cur_empty_log_idx++;
	if (cur_empty_log_idx == UCIE_INTR_LOG_SIZE)
		cur_empty_log_idx = 0;
}

static void _uncorr_err_handling(const bool fatal_err)
{
	if (fatal_err)
		target_ss->dvsec1_reg_reg_global_dvsec1_ucie_link_status.lstatus_ucie_link_uncorr_fatal_err = true;
	else
		target_ss->dvsec1_reg_reg_global_dvsec1_ucie_link_status.lstatus_ucie_link_uncorr_non_fatal_err = true;

	union aw_ucie_adapter_d2d_reg_reg_adapter_d2d_uncorr_err_mask err_mask =
		target_ss->adapter_d2d_reg_reg_adapter_d2d_uncorr_err_mask;
	union aw_ucie_adapter_d2d_reg_reg_adapter_d2d_uncorr_err_stat err_stat =
		target_ss->adapter_d2d_reg_reg_adapter_d2d_uncorr_err_stat;
	uint32_t log_idx_bk = cur_empty_log_idx;

	target_ss->adapter_d2d_reg_reg_adapter_d2d_uncorr_err_stat = err_stat;

	if (!err_mask.adpt_timeout_mask && err_stat.adpt_timeout)
		_log_intr(ADAPTER_TIMEOUT);

	if (!err_mask.rcvr_overflow_mask && err_stat.rcvr_overflow)
		_log_intr(RECEIVER_OVERFLOW);

	if (!err_mask.internal_err_mask && err_stat.internal_err)
		_log_intr(INTERNAL_ERROR);

	if (!err_mask.sb_fatal_err_msg_rcvd_mask && err_stat.sb_fatal_err_msg_rcvd)
		_log_intr(SB_FATAL_ERR_MSG_RCV);

	if (!err_mask.sb_nonfatal_err_msg_rcvd_mask && err_stat.sb_nonfatal_err_msg_rcvd)
		_log_intr(SB_NON_FATAL_ERR_MSG_RCV);

	if (!err_mask.invld_param_exchange_mask && err_stat.invld_param_exchange)
		_log_intr(INVALID_PARAM_EXCHANGE);

	if (log_idx_bk == cur_empty_log_idx) {
		if (fatal_err)
			_log_intr(INVALID_FATAL_UNCORR_ERR);
		else
			_log_intr(INVALID_NON_FATAL_UNCORR_ERR);
	}
}

static void _corr_err_handling(void)
{
	target_ss->dvsec1_reg_reg_global_dvsec1_ucie_link_status.lstatus_ucie_link_corr_err = true;

	union aw_ucie_adapter_d2d_reg_reg_adapter_d2d_corr_err_mask corr_err_mask =
		target_ss->adapter_d2d_reg_reg_adapter_d2d_corr_err_mask;
	union aw_ucie_adapter_d2d_reg_reg_adapter_d2d_corr_err_stat corr_err_stat =
		target_ss->adapter_d2d_reg_reg_adapter_d2d_corr_err_stat;
	uint32_t log_idx_bk = cur_empty_log_idx;

	if (!corr_err_mask.crc_err_detected_mask && corr_err_stat.crc_err_detected)
		_log_intr(CRC_ERROR_DETECTED);

	if (!corr_err_mask.adpt_lsm_trns_to_retrain_mask && corr_err_stat.adpt_lsm_trans_retrain)
		_log_intr(ADAPTER_LSM_TRANS_TO_RETRAIN);

	if (!corr_err_mask.corr_internal_err_mask && corr_err_stat.corr_internal_err)
		_log_intr(CORRECTABLE_INTERNAL_ERROR);

	if (!corr_err_mask.device_corr_err_msg_recv_mask && corr_err_stat.sb_corr_err_msg_rcvd)
		_log_intr(SB_CORRECTABLE_ERR_MSG_RCV);

	if (!corr_err_mask.runtime_link_tstng_parity_err_mask && corr_err_stat.run_time_link_testing_parity_err)
		_log_intr(RUNTIME_LINK_TESTING_PARITY_ERR);

	if (log_idx_bk == cur_empty_log_idx)
		_log_intr(INVALID_CORR_ERR);
	else
		target_ss->adapter_d2d_reg_reg_adapter_d2d_corr_err_stat = corr_err_stat;
}

static void _link_event_handling(void)
{
	target_ss->dvsec1_reg_reg_global_dvsec1_ucie_link_status.lstatus_link_status_change = true;
	_log_intr(LINK_STAT_CHANGED);
}

static void _empty_intr_handling(void)
{
	_log_intr(UNKNOWN_REASON);
}

void ucie_irq_handler(void *data)
{
	uint64_t ucie_ss_id = (uint64_t)data;
	uint32_t target_ss_id_bk = target_ss_id;
	uint32_t log_idx_bk = cur_empty_log_idx;
	bool retrain_required = false;

	printf("irq ucie_ss_id %d\n", ucie_ss_id);
	aw_ucie_set_target_ss(ucie_ss_id);

	union aw_ucie_dvsec1_reg_reg_global_dvsec1_link_evnt_err_nf_ctrl nf_ctrl =
		target_ss->dvsec1_reg_reg_global_dvsec1_link_evnt_err_nf_ctrl;
	union aw_ucie_dvsec1_reg_reg_global_dvsec1_ucie_link_status link_stat =
		target_ss->dvsec1_reg_reg_global_dvsec1_ucie_link_status;

#if !WA_SKIP_CHECK_LINK_STAT_ERROR
	if (nf_ctrl.err_nf_ctrl_uncorr_fatal_err_ucie_link_err_intr_en &&
		link_stat.lstatus_ucie_link_uncorr_fatal_err) {
		_uncorr_err_handling(FATAL);
		retrain_required = true;
	}

	if (nf_ctrl.err_nf_ctrl_uncorr_non_fatal_err_ucie_link_err_intr_en &&
		link_stat.lstatus_ucie_link_uncorr_non_fatal_err) {
		_uncorr_err_handling(NON_FATAL);
		retrain_required = true;
	}

	if (nf_ctrl.err_nf_ctrl_corr_err_ucie_link_err_intr_en && link_stat.lstatus_ucie_link_corr_err) {
		_corr_err_handling();
		retrain_required = true;
	}
#else
	union aw_ucie_adapter_d2d_reg_reg_adapter_d2d_uncorr_err_stat uncorr_err_stat =
		target_ss->adapter_d2d_reg_reg_adapter_d2d_uncorr_err_stat;
	union aw_ucie_adapter_d2d_reg_reg_adapter_d2d_corr_err_stat corr_err_stat =
		target_ss->adapter_d2d_reg_reg_adapter_d2d_corr_err_stat;

	if (uncorr_err_stat.val) {
		_uncorr_err_handling(FATAL);
		retrain_required = true;
	}

	if (corr_err_stat.val) {
		_corr_err_handling();
		retrain_required = true;
	}

#endif /* WA_SKIP_CHECK_LINK_STAT_ERROR */
	if (nf_ctrl.link_status_change_ucie_link_event_intr_en && link_stat.lstatus_link_status_change) {
		_link_event_handling();
	}

	if (log_idx_bk == cur_empty_log_idx) {
		_empty_intr_handling();
	}

#if !WA_SKIP_RETRAIN_FOR_HANDLING_ERR
	if (retrain_required)
		aw_ucie_link_retraining();
#endif /* WA_SKIP_RETRAIN_FOR_HANDLING_ERR */
	aw_ucie_set_target_ss(target_ss_id_bk);
}

static int32_t check_reg_blk_header(const uint32_t blk_id, void * const hdr_addr)
{
	union aw_ucie_adapter_d2d_reg_reg_adapter_d2d_ucie_blk_hdr_reg1 *reg_hdr1 =
		(union aw_ucie_adapter_d2d_reg_reg_adapter_d2d_ucie_blk_hdr_reg1 *)hdr_addr;

	if (reg_hdr1->vndr_id != DVSEC_VENDOR_ID_FOR_UCIE)
		return RL_ERROR;
	if (reg_hdr1->vndr_id_reg_block != blk_id)
		return RL_ERROR;

	union aw_ucie_adapter_d2d_reg_reg_adapter_d2d_ucie_blk_hdr_reg2 *reg_hdr2 =
		(union aw_ucie_adapter_d2d_reg_reg_adapter_d2d_ucie_blk_hdr_reg2 *)(reg_hdr1 + 1);

	if (reg_hdr2->vndr_reg_block_version != 0)
		return RL_ERROR;

	union aw_ucie_adapter_d2d_reg_reg_adapter_d2d_ucie_blk_hdr_reg3 *reg_hdr3 =
		(union aw_ucie_adapter_d2d_reg_reg_adapter_d2d_ucie_blk_hdr_reg3 *)(reg_hdr2 + 1);
	uint32_t blk_len = (blk_id >= UCIE_REG_BLK_ID_D2D_IMP) ? 0x1000 : 0x2000;/* for AW Rigel */

	if (reg_hdr3->vndr_reg_block_length != blk_len)
		return RL_ERROR;

	return RL_OK;
}

static int32_t aw_ucie_init_impl(int32_t ucie_ss_id, void * const base_address)
{
	if (ucie_ss_id >= NUM_OF_UCIE_SS_ID) {
		return RL_BADARG;
	}
	reg[ucie_ss_id] = (struct aw_ucie *)(base_address);
	target_ss = reg[ucie_ss_id];
#if !WA_SKIP_UCIE_INIT_COND
	if (target_ss->dvsec1_reg_reg_global_dvsec1_pcie_extnd_cap_hdr.pcie_extnd_cap_hdr_cap_id
		!= PCIE_EXT_CAP_ID || target_ss->dvsec1_reg_reg_global_dvsec1_hdr1.hdr1_dvsec_vndr_id
		!= DVSEC_VENDOR_ID_FOR_UCIE) {

		return RL_NOT_FOUND;
	}

	/**
	 * In the case of REBEL-H, the register block is used as if it were whole one,
	 * so check if the reg loc is the correct value and do not use it.
	 **/
	uint64_t reg_blk[NUM_OF_REG_LOC] = {
		(uint64_t)base_address + UCIE_SRAM_SIZE, (uint64_t)base_address + UCIE_SRAM_SIZE,
		(uint64_t)base_address + UCIE_SRAM_SIZE, (uint64_t)base_address + UCIE_SRAM_SIZE};
	volatile union aw_ucie_dvsec1_reg_reg_global_dvsec1_reg_loc0_low *reg_loc;

	reg_loc = &target_ss->dvsec1_reg_reg_global_dvsec1_reg_loc0_low;
	for (uint32_t loc_idx = 0; loc_idx < NUM_OF_REG_LOC; loc_idx++) {
		uint32_t blk_id = reg_loc->reg_loc0_low_reg_blk_identifier;

		reg_blk[blk_id] += reg_loc->reg_loc0_low_reg_blk_offset << 12;
		if (blk_id == UCIE_REG_BLK_ID_D2D_IMP) {
			reg_blk[blk_id] += 0x800;/* RAIL-35 */
		}

		if (check_reg_blk_header(blk_id, (void *)reg_blk[blk_id]) != RL_OK) {
			return RL_ERROR;
		}
		reg_loc += 2;/* reg loc is 64bit register. low 32bit, high 32bit */
	}
	if (reg_blk[0] != (uint64_t)&target_ss->adapter_d2d_reg_reg_adapter_d2d_ucie_blk_hdr_reg1)
		return RL_ERROR;
	if (reg_blk[1] != (uint64_t)&target_ss->test_comp_reg_reg_glbl_tstcmp_ucie_blk_hdr1)
		return RL_ERROR;
	else {
		union aw_ucie_test_comp_reg_reg_glbl_d2d_adapter_testcompl_reg_blk_offset d2d_testcomp_blk_offset;

		d2d_testcomp_blk_offset.val = target_ss->test_comp_reg_reg_glbl_d2d_adapter_testcompl_reg_blk_offset.val;
		if (d2d_testcomp_blk_offset.d2d_adapter_testcompl_blk_offset != 0 ||
			d2d_testcomp_blk_offset.d2d_adapter_testcompl_blk_len != 1)
			return RL_ERROR;

		union aw_ucie_test_comp_reg_reg_glbl_phy_testcompl_reg_blk_offset phy_testcomp_blk_offset;

		phy_testcomp_blk_offset.val = target_ss->test_comp_reg_reg_glbl_phy_testcompl_reg_blk_offset.val;
		if (phy_testcomp_blk_offset.phy_testcompl_blk_offset != 1 ||
			phy_testcomp_blk_offset.phy_testcompl_blk_len != 1)
			return RL_ERROR;
	}
	if (reg_blk[2] != (uint64_t)&target_ss->adapter_imp_spec_rdi_reg_reg_adapter_impsp_ucie_blk_hdr1)
		return RL_ERROR;
	if (reg_blk[3] != (uint64_t)&target_ss->phy_imp_spec_reg_reg_phy_impsp_ucie_blk_hdr1)
		return RL_ERROR;
#endif /* WA_SKIP_UCIE_INIT_COND */
	gic_irq_connect(ucie_ss_intr_id[ucie_ss_id], ucie_irq_handler, (void *)(uint64_t)ucie_ss_id);
	gic_irq_enable(ucie_ss_intr_id[ucie_ss_id]);
	return RL_OK;
}

int32_t aw_ucie_set_target_ss(const uint32_t ucie_ss_id)
{
	if (ucie_ss_id >= NUM_OF_UCIE_SS_ID) {
		return RL_BADARG;
	} else if (reg[ucie_ss_id] == 0) {
		return RL_NOTREADY;
	}

	target_ss_id = ucie_ss_id;
	target_ss = reg[target_ss_id];

	return RL_OK;
}

int32_t aw_ucie_get_target_ss(void)
{
	return target_ss_id;
}

int32_t aw_ucie_get_pcie_cap_hdr(uint32_t * const val)
{
	CHECK_TARGET_UCIE_SS();
	*val = target_ss->dvsec1_reg_reg_global_dvsec1_pcie_extnd_cap_hdr.val;
	return RL_OK;
}

int32_t aw_ucie_get_dvs_hdr1(uint32_t * const val)
{
	CHECK_TARGET_UCIE_SS();
	*val =  target_ss->dvsec1_reg_reg_global_dvsec1_hdr1.val;
	return RL_OK;
}

int32_t aw_ucie_get_dvs_hdr2_cap_desc(uint32_t * const val)
{
	CHECK_TARGET_UCIE_SS();
	*val = target_ss->dvsec1_reg_reg_global_dvsec1_hdr2_and_cap_descriptor.val;
	return RL_OK;
}

int32_t aw_ucie_set_corr_err_noti(const uint32_t prot_based_en, const uint32_t link_err_intr_en)
{
	CHECK_TARGET_UCIE_SS();

	union aw_ucie_dvsec1_reg_reg_global_dvsec1_link_evnt_err_nf_ctrl nf_ctrl =
		target_ss->dvsec1_reg_reg_global_dvsec1_link_evnt_err_nf_ctrl;

	nf_ctrl.err_nf_ctrl_corr_err_prtcl_layer_report_en = prot_based_en;
	nf_ctrl.err_nf_ctrl_corr_err_ucie_link_err_intr_en = link_err_intr_en;
	target_ss->dvsec1_reg_reg_global_dvsec1_link_evnt_err_nf_ctrl = nf_ctrl;

	return RL_OK;
}

int32_t aw_ucie_set_non_fatal_uncorr_err_noti(const uint32_t prot_based_en, const uint32_t link_err_intr_en)
{
	CHECK_TARGET_UCIE_SS();

	union aw_ucie_dvsec1_reg_reg_global_dvsec1_link_evnt_err_nf_ctrl nf_ctrl =
		target_ss->dvsec1_reg_reg_global_dvsec1_link_evnt_err_nf_ctrl;

	nf_ctrl.err_nf_ctrl_uncorr_non_fatal_err_ptcl_lyr_rpt_en = prot_based_en;
	nf_ctrl.err_nf_ctrl_uncorr_non_fatal_err_ucie_link_err_intr_en = link_err_intr_en;
	target_ss->dvsec1_reg_reg_global_dvsec1_link_evnt_err_nf_ctrl = nf_ctrl;

	return RL_OK;
}

int32_t aw_ucie_set_fatal_uncorr_err_noti(const uint32_t prot_based_en, const uint32_t link_err_intr_en)
{
	CHECK_TARGET_UCIE_SS();

	union aw_ucie_dvsec1_reg_reg_global_dvsec1_link_evnt_err_nf_ctrl nf_ctrl =
		target_ss->dvsec1_reg_reg_global_dvsec1_link_evnt_err_nf_ctrl;

	nf_ctrl.err_nf_ctrl_uncorr_fatal_err_ptcl_lyr_report_en = prot_based_en;
	nf_ctrl.err_nf_ctrl_uncorr_fatal_err_ucie_link_err_intr_en = link_err_intr_en;
	target_ss->dvsec1_reg_reg_global_dvsec1_link_evnt_err_nf_ctrl = nf_ctrl;

	return RL_OK;
}

int32_t aw_ucie_set_link_cap_APMW(void)
{
	CHECK_TARGET_UCIE_SS();
	target_ss->dvsec1_reg_reg_global_dvsec1_ucie_link_cap.lcap_apmw = 1;
	return RL_OK;
}

int32_t aw_ucie_clear_link_cap_APMW(void)
{
	CHECK_TARGET_UCIE_SS();
	target_ss->dvsec1_reg_reg_global_dvsec1_ucie_link_cap.lcap_apmw = 0;
	return RL_OK;
}

int32_t aw_ucie_get_link_capability(uint32_t * const val)
{
	CHECK_TARGET_UCIE_SS();
	*val = target_ss->dvsec1_reg_reg_global_dvsec1_ucie_link_cap.val;
	return RL_OK;
}

int32_t aw_ucie_get_link_control(uint32_t * const val)
{
	CHECK_TARGET_UCIE_SS();
	*val = target_ss->dvsec1_reg_reg_global_dvsec1_ucie_link_cntrl.val;
	return RL_OK;
}

int32_t aw_ucie_set_link_control(const uint32_t val)
{
	CHECK_TARGET_UCIE_SS();
	target_ss->dvsec1_reg_reg_global_dvsec1_ucie_link_cntrl.val = val;
	return RL_OK;
}

int32_t aw_ucie_get_link_status(uint32_t * const val)
{
	CHECK_TARGET_UCIE_SS();
	*val = target_ss->dvsec1_reg_reg_global_dvsec1_ucie_link_status.val;
	return RL_OK;
}

int32_t aw_ucie_set_link_event_noti(const uint32_t link_stat_chg, const uint32_t hw_auto_bw_chg)
{
	CHECK_TARGET_UCIE_SS();
	union aw_ucie_dvsec1_reg_reg_global_dvsec1_link_evnt_err_nf_ctrl nf_ctrl =
		target_ss->dvsec1_reg_reg_global_dvsec1_link_evnt_err_nf_ctrl;

	nf_ctrl.link_status_change_ucie_link_event_intr_en = link_stat_chg;
	nf_ctrl.hw_autonomous_bw_change_ucie_link_event_intr_en = hw_auto_bw_chg;

	target_ss->dvsec1_reg_reg_global_dvsec1_link_evnt_err_nf_ctrl.val = nf_ctrl.val;
	return RL_OK;
}

int32_t aw_ucie_set_phy_init_debug(const uint32_t val)
{
	CHECK_TARGET_UCIE_SS();
	target_ss->phy_d2d_reg_reg_phy_d2d_phy_init_debug.val = val;
	return RL_OK;
}

int32_t aw_ucie_set_phy_control(const uint32_t val)
{
	CHECK_TARGET_UCIE_SS();
	target_ss->phy_d2d_reg_reg_phy_d2d_phy_cntrl.val = val;
	return RL_OK;
}

int32_t aw_ucie_get_phy_control(uint32_t * const val)
{
	CHECK_TARGET_UCIE_SS();
	*val = target_ss->phy_d2d_reg_reg_phy_d2d_phy_cntrl.val;
	return RL_OK;
}

int32_t aw_ucie_get_phy_status(uint32_t * const val)
{
	CHECK_TARGET_UCIE_SS();
	*val = target_ss->phy_d2d_reg_reg_phy_d2d_phy_stat.val;
	return RL_OK;
}

int32_t aw_ucie_set_phy_train_setup_1(const uint32_t mod_id, const uint32_t val)
{
	CHECK_TARGET_UCIE_SS();
	switch (mod_id) {
	case 0:
		target_ss->phy_d2d_reg_reg_phy_d2d_m0_train_setup1.val = val;
		break;
	case 1:
		target_ss->phy_d2d_reg_reg_phy_d2d_m1_train_setup1.val = val;
		break;
	case 2:
		target_ss->phy_d2d_reg_reg_phy_d2d_m2_train_setup1.val = val;
		break;
	case 3:
		target_ss->phy_d2d_reg_reg_phy_d2d_m3_train_setup1.val = val;
		break;
	default:
		return RL_BADARG;
	}

	return RL_OK;
}

int32_t aw_ucie_get_phy_train_setup_1(const uint32_t mod_id, uint32_t * const val)
{
	CHECK_TARGET_UCIE_SS();
	switch (mod_id) {
	case 0:
		*val = target_ss->phy_d2d_reg_reg_phy_d2d_m0_train_setup1.val;
		break;
	case 1:
		*val = target_ss->phy_d2d_reg_reg_phy_d2d_m1_train_setup1.val;
		break;
	case 2:
		*val = target_ss->phy_d2d_reg_reg_phy_d2d_m2_train_setup1.val;
		break;
	case 3:
		*val = target_ss->phy_d2d_reg_reg_phy_d2d_m3_train_setup1.val;
		break;
	default:
		return RL_BADARG;
	}

	return RL_OK;
}

int32_t aw_ucie_get_phy_err_log0(const uint32_t mod_id, uint32_t * const val)
{
	CHECK_TARGET_UCIE_SS();
	switch (mod_id) {
	case 0:
		*val = target_ss->phy_d2d_reg_reg_phy_d2d_m0_err_log0.val;
		break;
	case 1:
		*val = target_ss->phy_d2d_reg_reg_phy_d2d_m1_err_log0.val;
		break;
	case 2:
		*val = target_ss->phy_d2d_reg_reg_phy_d2d_m2_err_log0.val;
		break;
	case 3:
		*val = target_ss->phy_d2d_reg_reg_phy_d2d_m3_err_log0.val;
		break;
	default:
		return RL_BADARG;
	}

	return RL_OK;
}

int32_t aw_ucie_get_aw_ucie_ltsm_state(const uint32_t mod_id, uint32_t * const state)
{
	CHECK_TARGET_UCIE_SS();
	switch (mod_id) {
	case 0:
		*state = target_ss->phy_d2d_reg_reg_phy_d2d_m0_err_log0.m0_state_n;
		break;
	case 1:
		*state = target_ss->phy_d2d_reg_reg_phy_d2d_m1_err_log0.m1_state_n;
		break;
	case 2:
		*state = target_ss->phy_d2d_reg_reg_phy_d2d_m2_err_log0.m2_state_n;
		break;
	case 3:
		*state = target_ss->phy_d2d_reg_reg_phy_d2d_m3_err_log0.m3_state_n;
		break;
	default:
		return RL_BADARG;
	}

	return RL_OK;
}

int32_t aw_ucie_get_phy_err_log1(const uint32_t mod_id, uint32_t * const val)
{
	CHECK_TARGET_UCIE_SS();
	switch (mod_id) {
	case 0:
		*val = target_ss->phy_d2d_reg_reg_phy_d2d_m0_err_log1.val;
		break;
	case 1:
		*val = target_ss->phy_d2d_reg_reg_phy_d2d_m1_err_log1.val;
		break;
	case 2:
		*val = target_ss->phy_d2d_reg_reg_phy_d2d_m2_err_log1.val;
		break;
	case 3:
		*val = target_ss->phy_d2d_reg_reg_phy_d2d_m3_err_log1.val;
		break;
	default:
		return RL_BADARG;
	}

	return RL_OK;
}

int32_t aw_ucie_set_intr_summary_mask(const uint32_t val)
{
	CHECK_TARGET_UCIE_SS();
	target_ss->global_reg_reg_global_intr1_summary_mask.val = val;
	return RL_OK;
}

int32_t aw_ucie_get_intr_summary_mask(uint32_t * const val)
{
	CHECK_TARGET_UCIE_SS();
	*val = target_ss->global_reg_reg_global_intr1_summary_mask.val;
	return RL_OK;
}

int32_t aw_ucie_set_d2d_uncorr_err_status(const uint32_t val)
{
	CHECK_TARGET_UCIE_SS();
	target_ss->adapter_d2d_reg_reg_adapter_d2d_uncorr_err_stat.val = val;
	return RL_OK;
}

int32_t aw_ucie_get_d2d_uncorr_err_status(uint32_t * const val)
{
	CHECK_TARGET_UCIE_SS();
	*val = target_ss->adapter_d2d_reg_reg_adapter_d2d_uncorr_err_stat.val;
	return RL_OK;
}

int32_t aw_ucie_set_d2d_uncorr_err_mask(const uint32_t val)
{
	CHECK_TARGET_UCIE_SS();
	target_ss->adapter_d2d_reg_reg_adapter_d2d_uncorr_err_mask.val = val;
	return RL_OK;
}

int32_t aw_ucie_set_uncorr_err_mask(const uint32_t adap_to, const uint32_t rcv_of,
									const uint32_t internal, const uint32_t sb_fatal,
									const uint32_t sb_nfatal, const uint32_t inv_param)
{
	CHECK_TARGET_UCIE_SS();
	union aw_ucie_adapter_d2d_reg_reg_adapter_d2d_uncorr_err_mask err_mask = {};

	err_mask.adpt_timeout_mask = adap_to;
	err_mask.rcvr_overflow_mask = rcv_of;
	err_mask.internal_err_mask = internal;
	err_mask.sb_fatal_err_msg_rcvd_mask = sb_fatal;
	err_mask.sb_nonfatal_err_msg_rcvd_mask = sb_nfatal;
	err_mask.invld_param_exchange_mask = inv_param;
	target_ss->adapter_d2d_reg_reg_adapter_d2d_uncorr_err_mask = err_mask;

	return RL_OK;
}

int32_t aw_ucie_get_d2d_uncorr_err_mask(uint32_t * const val)
{
	CHECK_TARGET_UCIE_SS();
	*val = target_ss->adapter_d2d_reg_reg_adapter_d2d_uncorr_err_mask.val;
	return RL_OK;
}

int32_t aw_ucie_get_d2d_uncorr_err_severity(uint32_t * const val)
{
	CHECK_TARGET_UCIE_SS();
	*val = target_ss->adapter_d2d_reg_reg_adapter_d2d_uncorr_err_severity.val;
	return RL_OK;
}

int32_t aw_ucie_set_d2d_uncorr_err_severity(const uint32_t val)
{
	CHECK_TARGET_UCIE_SS();
	target_ss->adapter_d2d_reg_reg_adapter_d2d_uncorr_err_severity.val = val;
	return RL_OK;
}

int32_t aw_ucie_set_uncorr_err_severity(const uint32_t adap_to, const uint32_t rcv_of,
										const uint32_t internal, const uint32_t sb_fatal,
										const uint32_t sb_nfatal, const uint32_t inv_param)
{
	CHECK_TARGET_UCIE_SS();

	union aw_ucie_adapter_d2d_reg_reg_adapter_d2d_uncorr_err_severity uncorr_err_severity = {};

	uncorr_err_severity.adpt_timeout_severity = adap_to;
	uncorr_err_severity.internal_err_severity = internal;
	uncorr_err_severity.invld_param_exchange_severity = inv_param;
	uncorr_err_severity.rcvr_overflow_severity = rcv_of;
	uncorr_err_severity.sb_fatal_err_msg_rcvd_severity = sb_fatal;
	uncorr_err_severity.sb_nonfatal_err_msg_rcvd_severity = sb_nfatal;

	target_ss->adapter_d2d_reg_reg_adapter_d2d_uncorr_err_severity = uncorr_err_severity;

	return RL_OK;
}

int32_t aw_ucie_set_d2d_corr_err_status(const uint32_t val)
{
	CHECK_TARGET_UCIE_SS();
	target_ss->adapter_d2d_reg_reg_adapter_d2d_corr_err_stat.val = val;
	return RL_OK;
}

int32_t aw_ucie_get_d2d_corr_err_status(uint32_t * const val)
{
	CHECK_TARGET_UCIE_SS();
	*val = target_ss->adapter_d2d_reg_reg_adapter_d2d_corr_err_stat.val;
	return RL_OK;
}

int32_t aw_ucie_set_corr_err_mask(const bool crc_err, const bool adap_retrain, const bool internal,
								  const bool dev_corr_err_msg_rcv, const bool runtime_link_test)
{
	CHECK_TARGET_UCIE_SS();
	union aw_ucie_adapter_d2d_reg_reg_adapter_d2d_corr_err_mask err_mask = {};

	err_mask.crc_err_detected_mask = crc_err;
	err_mask.adpt_lsm_trns_to_retrain_mask = adap_retrain;
	err_mask.corr_internal_err_mask = internal;
	err_mask.device_corr_err_msg_recv_mask = dev_corr_err_msg_rcv;
	err_mask.runtime_link_tstng_parity_err_mask = runtime_link_test;
	target_ss->adapter_d2d_reg_reg_adapter_d2d_corr_err_mask = err_mask;

	return RL_OK;
}

int32_t aw_ucie_get_crc_err_detected(bool * const crc_err_detected)
{
	CHECK_TARGET_UCIE_SS();
	*crc_err_detected = target_ss->dvsec1_reg_reg_global_dvsec1_ucie_link_status.lstatus_ucie_link_corr_err;

	return RL_OK;
}

int32_t aw_ucie_get_d2d_runtime_link_parity_log(const uint32_t module_id, const bool low, uint32_t * const val)
{
	CHECK_TARGET_UCIE_SS();
	switch (module_id) {
	case 0:
		if (low)
			*val = target_ss->adapter_d2d_reg_reg_adapter_d2d_runtime_link_test_parity_log0_1.val;
		else
			*val = target_ss->adapter_d2d_reg_reg_adapter_d2d_runtime_link_test_parity_log0_2.val;
		break;
	case 1:
		if (low)
			*val = target_ss->adapter_d2d_reg_reg_adapter_d2d_runtime_link_test_parity_log1_1.val;
		else
			*val = target_ss->adapter_d2d_reg_reg_adapter_d2d_runtime_link_test_parity_log1_2.val;
		break;
	case 2:
		if (low)
			*val = target_ss->adapter_d2d_reg_reg_adapter_d2d_runtime_link_test_parity_log2_1.val;
		else
			*val = target_ss->adapter_d2d_reg_reg_adapter_d2d_runtime_link_test_parity_log2_2.val;
		break;
	case 3:
		if (low)
			*val = target_ss->adapter_d2d_reg_reg_adapter_d2d_runtime_link_test_parity_log3_1.val;
		else
			*val = target_ss->adapter_d2d_reg_reg_adapter_d2d_runtime_link_test_parity_log3_2.val;
		break;
	default:
		return RL_BADARG;
	}

	return RL_OK;
}

int32_t aw_ucie_set_d2d_adv_adp_log1(const uint32_t val)
{
	CHECK_TARGET_UCIE_SS();
	target_ss->adapter_d2d_reg_reg_adapter_d2d_adv_adapter_capability_log1.val = val;
	return RL_OK;
}

int32_t aw_ucie_get_d2d_adv_adp_log1(uint32_t * const val)
{
	CHECK_TARGET_UCIE_SS();
	*val = target_ss->adapter_d2d_reg_reg_adapter_d2d_adv_adapter_capability_log1.val;
	return RL_OK;
}

int32_t aw_ucie_get_d2d_fin_adp_log1(uint32_t * const val)
{
	CHECK_TARGET_UCIE_SS();
	*val = target_ss->adapter_d2d_reg_reg_adapter_d2d_fin_adapter_capability_log1.val;
	return RL_OK;
}

int32_t aw_ucie_get_phy_cap(uint32_t * const val)
{
	CHECK_TARGET_UCIE_SS();
	*val = target_ss->phy_d2d_reg_reg_phy_d2d_phy_cap.val;
	return RL_OK;
}

int32_t aw_ucie_get_phy_extnd_cap_hdr(uint32_t * const val)
{
	CHECK_TARGET_UCIE_SS();
	*val = target_ss->phy_d2d_reg_reg_phy_d2d_pcie_extnd_cap_hdr.val;
	return RL_OK;
}

int32_t aw_ucie_get_uhm_dvsec_hdr1(uint32_t * const val)
{
	CHECK_TARGET_UCIE_SS();
	*val = target_ss->phy_d2d_reg_reg_phy_d2d_dvsec_hdr1.val;
	return RL_OK;
}

int32_t aw_ucie_get_uhm_dvsec_hdr2(uint32_t * const val)
{
	CHECK_TARGET_UCIE_SS();
	*val = target_ss->phy_d2d_reg_reg_phy_d2d_dvsec_hdr2.val;
	return RL_OK;
}

int32_t aw_ucie_get_d2d_hdr_log1_1(uint32_t * const val)
{
	CHECK_TARGET_UCIE_SS();
	*val = target_ss->adapter_d2d_reg_reg_adapter_d2d_hdr_log1_1.val;
	return RL_OK;
}

int32_t aw_ucie_get_d2d_hdr_log1_2(uint32_t * const val)
{
	CHECK_TARGET_UCIE_SS();
	*val = target_ss->adapter_d2d_reg_reg_adapter_d2d_hdr_log1_2.val;
	return RL_OK;
}

int32_t aw_ucie_get_d2d_hdr_log2(uint32_t * const val)
{
	CHECK_TARGET_UCIE_SS();
	*val = target_ss->adapter_d2d_reg_reg_adapter_d2d_hdr_log2.val;
	return RL_OK;
}

int32_t aw_ucie_set_d2d_runtime_link_test_cntrl(const uint32_t val)
{
	CHECK_TARGET_UCIE_SS();
	target_ss->adapter_d2d_reg_reg_adapter_d2d_err_and_link_test_cntrl.val = val;
	return RL_OK;
}

int32_t aw_ucie_get_d2d_runtime_link_test_cntrl(uint32_t * const val)
{
	CHECK_TARGET_UCIE_SS();
	*val = target_ss->adapter_d2d_reg_reg_adapter_d2d_err_and_link_test_cntrl.val;
	return RL_OK;
}

int32_t aw_ucie_set_adap_test_comp_ctrl(const uint32_t val)
{
	CHECK_TARGET_UCIE_SS();
	target_ss->adapter_test_comp_reg_reg_adapter_tstcmp_compliance_ctrl.val = val;
	return RL_OK;
}

int32_t aw_ucie_get_adap_test_comp_ctrl(uint32_t * const val)
{
	CHECK_TARGET_UCIE_SS();
	*val = target_ss->adapter_test_comp_reg_reg_adapter_tstcmp_compliance_ctrl.val;
	return RL_OK;
}

int32_t aw_ucie_get_adap_test_comp_stat(uint32_t * const val)
{
	CHECK_TARGET_UCIE_SS();
	*val = target_ss->adapter_test_comp_reg_reg_adapter_tstcmp_test_sts.val;
	return RL_OK;
}

int32_t aw_ucie_set_adap_test_comp_phy_only_mode(void)
{
	CHECK_TARGET_UCIE_SS();
	target_ss->adapter_test_comp_reg_reg_adapter_tstcmp_compliance_ctrl.compliance_mode =
		ADAP_COMPLIANCE_MODE_PHY_ONLY;
	return RL_OK;
}

int32_t aw_ucie_set_adap_test_comp_adap_mode(void)
{
	CHECK_TARGET_UCIE_SS();
	target_ss->adapter_test_comp_reg_reg_adapter_tstcmp_compliance_ctrl.compliance_mode =
		ADAP_COMPLIANCE_MODE_ADAPTER;
	return RL_OK;
}

int32_t aw_ucie_set_adap_test_comp_normal_mode(void)
{
	CHECK_TARGET_UCIE_SS();
	target_ss->adapter_test_comp_reg_reg_adapter_tstcmp_compliance_ctrl.compliance_mode =
		ADAP_COMPLIANCE_MODE_NORMAL;
	return RL_OK;
}

int32_t aw_ucie_adap_test_comp_force_reset(void)
{
	CHECK_TARGET_UCIE_SS();
	target_ss->adapter_test_comp_reg_reg_adapter_tstcmp_compliance_ctrl.compliance_force_link_reset = 1;

	while (!target_ss->dvsec1_reg_reg_global_dvsec1_ucie_link_status.lstatus_link_status) {
	}
	return RL_OK;
}

int32_t aw_ucie_set_adap_test_comp_flit_injt_ctrl(const uint32_t val)
{
	CHECK_TARGET_UCIE_SS();
	target_ss->adapter_test_comp_reg_reg_adapter_tstcmp_flit_tx_inj_ctrl1.val = val;
	return RL_OK;
}

int32_t aw_ucie_get_cmn_mcu_scratch_reg1(uint32_t * const val)
{
	CHECK_TARGET_UCIE_SS();
	*val = target_ss->global_reg_cmn_mcu_scratch_reg1.val;
	return RL_OK;
}

int32_t aw_ucie_link_training_impl(void)
{
	union aw_ucie_dvsec1_reg_reg_global_dvsec1_ucie_link_status link_stat;
	union aw_ucie_dvsec1_reg_reg_global_dvsec1_ucie_link_cntrl link_ctrl;

	CHECK_TARGET_UCIE_SS();

	link_stat.val = target_ss->dvsec1_reg_reg_global_dvsec1_ucie_link_status.val;
	if (link_stat.lstatus_link_train_or_retrain == 1) {
		return RL_BUSY;
	}
	uint64_t is_already_link_up = link_stat.lstatus_link_status;

	/* clear previous status data */
	target_ss->dvsec1_reg_reg_global_dvsec1_ucie_link_status.val = link_stat.val;

	target_ss->dvsec1_reg_reg_global_dvsec1_ucie_link_cntrl.lcntrl_start_ucie_link_training = 1;

	link_stat.val = target_ss->dvsec1_reg_reg_global_dvsec1_ucie_link_status.val;
	if (is_already_link_up) {
		if (link_stat.lstatus_link_status_change != 1) {
			/* in case of using Start UCIe Link training,
			 * the Link will go through full training through Link Down state.
			 * so after updating control register,
			 * it is expected that this bit set because transition from up to down occurred
			 * If the Link is actively retraining, this bit reflects a value of 1b.
			 */
			return RL_ERROR;
		}
		/* clear link status change */
		target_ss->dvsec1_reg_reg_global_dvsec1_ucie_link_status.val = link_stat.val;
	}

	do {
		link_ctrl.val = target_ss->dvsec1_reg_reg_global_dvsec1_ucie_link_cntrl.val;
	} while (link_ctrl.lcntrl_start_ucie_link_training == 1);

	link_stat.val = target_ss->dvsec1_reg_reg_global_dvsec1_ucie_link_status.val;
	if (link_stat.lstatus_link_train_or_retrain == 1) {
		return RL_ERROR;
	}

	if (link_stat.lstatus_link_status == 0) {
		/* Error checking logic is implemented separately outside this function.
		 * This function do not check and analize detailed error result.
		 */
		return RL_ERROR;
	}

	return RL_OK;
}

int32_t aw_ucie_link_retraining_impl(void)
{
	union aw_ucie_dvsec1_reg_reg_global_dvsec1_ucie_link_status link_stat;
	union aw_ucie_dvsec1_reg_reg_global_dvsec1_ucie_link_cntrl link_ctrl;

	CHECK_TARGET_UCIE_SS();

	link_stat.val = target_ss->dvsec1_reg_reg_global_dvsec1_ucie_link_status.val;

	if (link_stat.lstatus_link_status == 0) {
		return RL_NOTREADY;
	}
	if (link_stat.lstatus_link_train_or_retrain == 1) {
		return RL_BUSY;
	}
	target_ss->dvsec1_reg_reg_global_dvsec1_ucie_link_status.val = link_stat.val;

	target_ss->dvsec1_reg_reg_global_dvsec1_ucie_link_cntrl.lcntrl_retrain_ucie_link = 1;
	do {
		link_ctrl.val = target_ss->dvsec1_reg_reg_global_dvsec1_ucie_link_cntrl.val;

	} while (link_ctrl.lcntrl_retrain_ucie_link == 1);

	link_stat.val = target_ss->dvsec1_reg_reg_global_dvsec1_ucie_link_status.val;

	if (link_stat.lstatus_link_status == 0 ||
		link_stat.lstatus_link_train_or_retrain == 1) {
		return RL_ERROR;
	}

	return RL_OK;
}

static bool _is_sideband_mailbox_busy(void)
{
	return target_ss->dvsec1_reg_reg_global_dvsec1_sb_mailbox_ctrl_stats.sb_mailbox_ctrl_wr_or_rd_trigger == 1;
}

static void _set_sb_mbox_msg_header(const uint32_t opcode, const uint32_t rl, const uint32_t offset)
{
	union aw_ucie_dvsec1_reg_reg_global_dvsec1_sb_mailbox_index_low sb_mbox_idx_low = {};
	union aw_ucie_dvsec1_reg_reg_global_dvsec1_sb_mailbox_index_high sb_mbox_idx_high = {};

	sb_mbox_idx_low.sb_mailbox_index_low_opcode = opcode & RL_GENMASK(4, 0);
	sb_mbox_idx_low.sb_mailbox_index_low_be = 0xF;
	if (opcode == UCIE_SB_32B_MEM_RD || opcode == UCIE_SB_32B_MEM_WR ||
		opcode == UCIE_SB_64B_MEM_RD || opcode == UCIE_SB_64B_MEM_WR) {
		sb_mbox_idx_low.sb_mailbox_index_low_addr |= RL_BITFIELD_GET(RL_GENMASK(18, 0), offset);
		sb_mbox_idx_high.sb_mailbox_index_high_addr |= RL_BITFIELD_GET(RL_BIT(19), offset);
	} else {
		sb_mbox_idx_low.sb_mailbox_index_low_addr |= RL_BITFIELD_GET(RL_GENMASK(11, 0), offset);
	}
	sb_mbox_idx_high.sb_mailbox_index_high_addr |= RL_BITFIELD_GET(RL_GENMASK(3, 0), rl) << 1;

	target_ss->dvsec1_reg_reg_global_dvsec1_sb_mailbox_index_low.val = sb_mbox_idx_low.val;
	target_ss->dvsec1_reg_reg_global_dvsec1_sb_mailbox_index_high.val = sb_mbox_idx_high.val;
}

static uint32_t _trigger_sb_mbox(void)
{
	union aw_ucie_dvsec1_reg_reg_global_dvsec1_sb_mailbox_ctrl_stats sb_mbox_ctrl_stat = {};

	sb_mbox_ctrl_stat.sb_mailbox_ctrl_wr_or_rd_trigger = 1;
	target_ss->dvsec1_reg_reg_global_dvsec1_sb_mailbox_ctrl_stats.val = sb_mbox_ctrl_stat.val;

	do {
		sb_mbox_ctrl_stat.val = target_ss->dvsec1_reg_reg_global_dvsec1_sb_mailbox_ctrl_stats.val;
	} while (sb_mbox_ctrl_stat.sb_mailbox_ctrl_wr_or_rd_trigger == 1);

	return sb_mbox_ctrl_stat.val;
}

static void _set_sb_mbox_msg_out_data(const uint32_t opcode, uint32_t * const buf)
{
	if (opcode == UCIE_SB_32B_MEM_WR || opcode == UCIE_SB_32B_CONFIG_WR) {
		target_ss->dvsec1_reg_reg_global_dvsec1_sb_mailbox_data_low.val = buf[0];
	} else if (opcode == UCIE_SB_64B_MEM_WR || opcode == UCIE_SB_64B_CONFIG_WR) {
		target_ss->dvsec1_reg_reg_global_dvsec1_sb_mailbox_data_low.val = buf[0];
		target_ss->dvsec1_reg_reg_global_dvsec1_sb_mailbox_data_high.val = buf[1];
	} else {
		/* do nothing */
	}
}

static void _get_sb_mbox_msg_in_data(const uint32_t opcode, uint32_t * const buf)
{
	if (opcode == UCIE_SB_32B_MEM_RD || opcode == UCIE_SB_32B_CONFIG_RD) {
		buf[0] = target_ss->dvsec1_reg_reg_global_dvsec1_sb_mailbox_data_low.val;
	} else if (opcode == UCIE_SB_64B_MEM_RD || opcode == UCIE_SB_64B_CONFIG_RD) {
		buf[0] = target_ss->dvsec1_reg_reg_global_dvsec1_sb_mailbox_data_low.val;
		buf[1] = target_ss->dvsec1_reg_reg_global_dvsec1_sb_mailbox_data_high.val;
	} else {
		/* do nothing */
	}
}

static int32_t _send_sb_mbox_msg(const uint32_t opcode, const uint32_t rl, const uint32_t offset,
								 uint32_t * const buf)
{
	CHECK_TARGET_UCIE_SS();
	CHECK_UCIE_MBOX_ARG(opcode);

	if (_is_sideband_mailbox_busy())
		return RL_BUSY;

	_set_sb_mbox_msg_header(opcode, rl, offset);
	_set_sb_mbox_msg_out_data(opcode, buf);

	union aw_ucie_dvsec1_reg_reg_global_dvsec1_sb_mailbox_ctrl_stats sb_mbox_ctrl_stat = {};

	sb_mbox_ctrl_stat.val = _trigger_sb_mbox();
	if (sb_mbox_ctrl_stat.sb_mailbox_stats_wr_or_rd_status != UCIE_SB_MBOX_STAT_SUCCESS) {
		buf[0] = target_ss->dvsec1_reg_reg_global_dvsec1_sb_mailbox_data_low.val;
		buf[1] = target_ss->dvsec1_reg_reg_global_dvsec1_sb_mailbox_data_high.val;
		return RL_ERROR;
	}

	_get_sb_mbox_msg_in_data(opcode, buf);

	return RL_OK;
}

int32_t aw_ucie_sb_mbox_manual(const uint32_t opcode, const uint32_t be,
							   const uint32_t addr_18_0, const uint32_t addr_23_19,
							   uint32_t * const out_buf, uint32_t * const in_buf)
{
	CHECK_TARGET_UCIE_SS();

	if (_is_sideband_mailbox_busy())
		return RL_BUSY;

	union aw_ucie_dvsec1_reg_reg_global_dvsec1_sb_mailbox_index_low index_low = {};
	union aw_ucie_dvsec1_reg_reg_global_dvsec1_sb_mailbox_index_high index_high = {};
	union aw_ucie_dvsec1_reg_reg_global_dvsec1_sb_mailbox_ctrl_stats ctrl_stat = {};

	/* Set Header */
	index_low.sb_mailbox_index_low_opcode = opcode;
	index_low.sb_mailbox_index_low_be = be;
	index_low.sb_mailbox_index_low_addr = addr_18_0;
	target_ss->dvsec1_reg_reg_global_dvsec1_sb_mailbox_index_low.val = index_low.val;

	index_high.sb_mailbox_index_high_addr = addr_23_19;
	target_ss->dvsec1_reg_reg_global_dvsec1_sb_mailbox_index_high.val = index_high.val;

	/* Set Out-Data */
	if (out_buf) {
		target_ss->dvsec1_reg_reg_global_dvsec1_sb_mailbox_data_low.val = out_buf[0];
		target_ss->dvsec1_reg_reg_global_dvsec1_sb_mailbox_data_high.val = out_buf[1];
	}
	/* Trigger */
	ctrl_stat.val = _trigger_sb_mbox();

	/* Get In-Data */
	if (in_buf) {
		in_buf[0] = target_ss->dvsec1_reg_reg_global_dvsec1_sb_mailbox_data_low.val;
		in_buf[1] = target_ss->dvsec1_reg_reg_global_dvsec1_sb_mailbox_data_high.val;
	}

	return ctrl_stat.sb_mailbox_stats_wr_or_rd_status;
}

static int32_t aw_ucie_sb_mem_rd32_impl(const uint32_t rl, const uint32_t offset, uint32_t * const buf)
{
	return _send_sb_mbox_msg(UCIE_SB_32B_MEM_RD, rl, offset, buf);
}

static int32_t aw_ucie_sb_mem_wr32_impl(const uint32_t rl, const uint32_t offset, uint32_t * const buf)
{
	return _send_sb_mbox_msg(UCIE_SB_32B_MEM_WR, rl, offset, buf);
}

int32_t aw_ucie_sb_mem_rd64(const uint32_t rl, const uint32_t offset, uint32_t * const buf)
{
	return _send_sb_mbox_msg(UCIE_SB_64B_MEM_RD, rl, offset, buf);
}

int32_t aw_ucie_sb_mem_wr64(const uint32_t rl, const uint32_t offset, uint32_t * const buf)
{
	return _send_sb_mbox_msg(UCIE_SB_64B_MEM_WR, rl, offset, buf);
}

int32_t aw_ucie_sb_config_rd32(const uint32_t rl, const uint32_t offset, uint32_t * const buf)
{
	return _send_sb_mbox_msg(UCIE_SB_32B_CONFIG_RD, rl, offset, buf);
}

int32_t aw_ucie_sb_config_wr32(const uint32_t rl, const uint32_t offset, uint32_t * const buf)
{
	return _send_sb_mbox_msg(UCIE_SB_32B_CONFIG_WR, rl, offset, buf);
}

int32_t aw_ucie_sb_config_rd64(const uint32_t rl, const uint32_t offset, uint32_t * const buf)
{
	return _send_sb_mbox_msg(UCIE_SB_64B_CONFIG_RD, rl, offset, buf);
}

int32_t aw_ucie_sb_config_wr64(const uint32_t rl, const uint32_t offset, uint32_t * const buf)
{
	return _send_sb_mbox_msg(UCIE_SB_64B_CONFIG_WR, rl, offset, buf);
}

int32_t aw_ucie_get_sb_mbox_status(uint8_t * const val)
{
	CHECK_TARGET_UCIE_SS();
	*val =
	target_ss->dvsec1_reg_reg_global_dvsec1_sb_mailbox_ctrl_stats.sb_mailbox_stats_wr_or_rd_status;

	return RL_OK;
}

int32_t aw_ucie_mb_runtime_link_test_enable(const uint32_t num_of_parity_bytes)
{
	CHECK_TARGET_UCIE_SS();
	int32_t result = RL_OK;
	union aw_ucie_adapter_d2d_reg_reg_adapter_d2d_err_and_link_test_cntrl cntrl = {};

	if (num_of_parity_bytes > NUM_OF_INSERTED_FOUR_64BYTES)
		return RL_BADARG;

	cntrl.val = target_ss->adapter_d2d_reg_reg_adapter_d2d_err_and_link_test_cntrl.val;
	cntrl.no_of_64b_inserts = num_of_parity_bytes;
	cntrl.runtime_link_testing_tx_en = true;
	target_ss->adapter_d2d_reg_reg_adapter_d2d_err_and_link_test_cntrl.val = cntrl.val;

	cntrl.val = 0;
	cntrl.runtime_link_testing_rx_en = true;
	result = aw_ucie_sb_mem_wr32(UCIE_REG_BLK_ID_D2D_PHY, 0x30/*err and link cntrl*/, &cntrl.val);
	if (result != RL_OK)
		return result;

	result = aw_ucie_link_retraining();
	if (result != RL_OK)
		return result;

	if (target_ss->adapter_d2d_reg_reg_adapter_d2d_err_and_link_test_cntrl.parity_feature_nak_rcvd)
		return RL_EPERM;

	return RL_OK;
}

int32_t aw_ucie_mb_runtime_link_test_disable(void)
{
	CHECK_TARGET_UCIE_SS();

	target_ss->adapter_d2d_reg_reg_adapter_d2d_err_and_link_test_cntrl.runtime_link_testing_tx_en = false;
	return RL_OK;
}

int32_t aw_ucie_mb_crc_err_inject_impl(const uint32_t inverted_bits, const uint32_t injection_cnt)
{
	CHECK_TARGET_UCIE_SS();

	if (inverted_bits == CRC_ERR_INJ_DISABLE) {
		target_ss->adapter_d2d_reg_reg_adapter_d2d_err_and_link_test_cntrl.crc_injection_en = false;
		return RL_OK;
	}

	if (inverted_bits > CRC_ERR_INJ_3BIT_INVERTED || injection_cnt > CRC_ERR_INJ_COUNT_PER_64_FLIT)
		return RL_BADARG;

	union aw_ucie_adapter_d2d_reg_reg_adapter_d2d_err_and_link_test_cntrl cntrl = {};

	cntrl.val = target_ss->adapter_d2d_reg_reg_adapter_d2d_err_and_link_test_cntrl.val;
	cntrl.crc_injection_en = inverted_bits;
	cntrl.crc_injection_count = injection_cnt;
	target_ss->adapter_d2d_reg_reg_adapter_d2d_err_and_link_test_cntrl.val = cntrl.val;

	while (!target_ss->adapter_d2d_reg_reg_adapter_d2d_err_and_link_test_cntrl.crc_injection_busy) {

	}

	return RL_OK;
}

int32_t aw_ucie_mb_inject_flit_disable(void)
{
	CHECK_TARGET_UCIE_SS();

	target_ss->adapter_test_comp_reg_reg_adapter_tstcmp_flit_tx_inj_ctrl1.flit_tx_inj_enable = false;

	return RL_OK;
}

static void _wait_flit_injection_done(const uint32_t inj_mode)
{
	union aw_ucie_adapter_test_comp_reg_reg_adapter_tstcmp_test_sts test_sts = {};

	if (inj_mode != FLIT_INJECT_MODE_CONT) {
		do {
			test_sts.val = target_ss->adapter_test_comp_reg_reg_adapter_tstcmp_test_sts.val;
		} while (test_sts.flit_tx_inj_sts != FLIT_INJECT_STAT_DONE);

		target_ss->adapter_test_comp_reg_reg_adapter_tstcmp_flit_tx_inj_ctrl1.flit_tx_inj_enable =
			false;
	} else {
		do {
			test_sts.val = target_ss->adapter_test_comp_reg_reg_adapter_tstcmp_test_sts.val;
		} while (test_sts.flit_tx_inj_sts != FLIT_INJECT_STAT_ONGOING);
	}
}

static int32_t aw_ucie_mb_inject_nop_flit_impl(const uint32_t inj_mode, const uint32_t flit_num)
{
	CHECK_TARGET_UCIE_SS();
	union aw_ucie_adapter_test_comp_reg_reg_adapter_tstcmp_flit_tx_inj_ctrl1 injt_ctrl1 = {};

	injt_ctrl1.flit_tx_inj_enable = true;
	injt_ctrl1.flit_type = FLIT_INJECT_FLIT_TYPE_NOP;
	injt_ctrl1.inj_mode = inj_mode;
	injt_ctrl1.flit_inj_number = flit_num;
	target_ss->adapter_test_comp_reg_reg_adapter_tstcmp_flit_tx_inj_ctrl1.val = injt_ctrl1.val;

	_wait_flit_injection_done(inj_mode);

	return RL_OK;
}

static int32_t aw_ucie_mb_inject_test_flit_impl(const uint32_t inj_mode, const uint32_t flit_num,
												const uint32_t payload_type, const uint32_t pattern,
												const uint32_t offset, const uint32_t repetition)
{
	CHECK_TARGET_UCIE_SS();
	union aw_ucie_adapter_test_comp_reg_reg_adapter_tstcmp_flit_tx_inj_ctrl1 injt_ctrl1 = {};

	injt_ctrl1.flit_tx_inj_enable = true;
	injt_ctrl1.flit_type = FLIT_INJECT_FLIT_TYPE_TEST;
	injt_ctrl1.inj_mode = inj_mode;
	injt_ctrl1.flit_inj_number = flit_num;
	injt_ctrl1.payload_type = payload_type;
	injt_ctrl1.flit_byte_offset = offset;
	injt_ctrl1.pattern_repetition = repetition;
	target_ss->adapter_test_comp_reg_reg_adapter_tstcmp_flit_tx_inj_ctrl1.val = injt_ctrl1.val;
	target_ss->adapter_test_comp_reg_reg_adapter_tstcmp_flit_tx_inj_ctrl2.payload_fixed_pattern	=
		pattern;

	_wait_flit_injection_done(inj_mode);

	return RL_OK;
}

int32_t aw_ucie_mb_inject_alt_flit(const uint32_t inj_mode, const uint32_t flit_num,
								   const uint32_t payload_type, const uint32_t pattern,
								   const uint32_t offset, const uint32_t repetition)
{
	CHECK_TARGET_UCIE_SS();
	union aw_ucie_adapter_test_comp_reg_reg_adapter_tstcmp_flit_tx_inj_ctrl1 injt_ctrl1 = {};

	injt_ctrl1.flit_tx_inj_enable = true;
	injt_ctrl1.flit_type = FLIT_INJECT_FLIT_TYPE_ALT;
	injt_ctrl1.inj_mode = inj_mode;
	injt_ctrl1.flit_inj_number = flit_num;
	injt_ctrl1.payload_type = payload_type;
	injt_ctrl1.flit_byte_offset = offset;
	injt_ctrl1.pattern_repetition = repetition;
	target_ss->adapter_test_comp_reg_reg_adapter_tstcmp_flit_tx_inj_ctrl1.val = injt_ctrl1.val;
	target_ss->adapter_test_comp_reg_reg_adapter_tstcmp_flit_tx_inj_ctrl2.payload_fixed_pattern	=
		pattern;

	_wait_flit_injection_done(inj_mode);

	return RL_OK;
}

int32_t aw_ucie_link_state_req_inject_stack0(const uint32_t state)
{
	CHECK_TARGET_UCIE_SS();
	union aw_ucie_adapter_test_comp_reg_reg_adapter_tstcmp_link_state_inj_ctrl_stack0 inj_ctrl = {};
	union aw_ucie_adapter_test_comp_reg_reg_adapter_tstcmp_test_sts test_sts = {};

	inj_ctrl.stack0_link_req = state;
	inj_ctrl.stack0_inj_type = LINK_STATE_INJ_TYPE_REQ;
	target_ss->adapter_test_comp_reg_reg_adapter_tstcmp_link_state_inj_ctrl_stack0.val =
			inj_ctrl.val;

	inj_ctrl.stack0_req_or_resp_inj_en_at_tx = 1;
	target_ss->adapter_test_comp_reg_reg_adapter_tstcmp_link_state_inj_ctrl_stack0.val =
		inj_ctrl.val;

	do {
		test_sts.val =
			target_ss->adapter_test_comp_reg_reg_adapter_tstcmp_test_sts.val;
	} while (test_sts.lstate_req_inj_sts_for_stack0 != 1);

	inj_ctrl.stack0_req_or_resp_inj_en_at_tx = 0;
	target_ss->adapter_test_comp_reg_reg_adapter_tstcmp_link_state_inj_ctrl_stack0.val =
			inj_ctrl.val;

	return RL_OK;
}

int32_t aw_ucie_link_state_resp_inject_stack0(const uint32_t state)
{
	CHECK_TARGET_UCIE_SS();
	union aw_ucie_adapter_test_comp_reg_reg_adapter_tstcmp_link_state_inj_ctrl_stack0 inj_ctrl = {};
	union aw_ucie_adapter_test_comp_reg_reg_adapter_tstcmp_test_sts test_sts = {};

	inj_ctrl.stack0_link_resp = state;
	inj_ctrl.stack0_inj_type = LINK_STATE_INJ_TYPE_RESP;
	target_ss->adapter_test_comp_reg_reg_adapter_tstcmp_link_state_inj_ctrl_stack0.val =
			inj_ctrl.val;

	inj_ctrl.stack0_req_or_resp_inj_en_at_tx = 1;
	target_ss->adapter_test_comp_reg_reg_adapter_tstcmp_link_state_inj_ctrl_stack0.val =
		inj_ctrl.val;

	do {
		test_sts.val =
			target_ss->adapter_test_comp_reg_reg_adapter_tstcmp_test_sts.val;
	} while (test_sts.lstate_resp_inj_sts_for_stack0 != 1);

	inj_ctrl.stack0_req_or_resp_inj_en_at_tx = 0;
	target_ss->adapter_test_comp_reg_reg_adapter_tstcmp_link_state_inj_ctrl_stack0.val =
			inj_ctrl.val;

	return RL_OK;
}

int32_t aw_ucie_mb_inject_error(const uint32_t error_type, const uint32_t byte_offset,
								const uint32_t num_btwn_err, const uint32_t num_err_flits,
								const uint32_t flit_type, const uint32_t retry_threshold)
{
	CHECK_TARGET_UCIE_SS();
	union aw_ucie_adapter_test_comp_reg_reg_adapter_tstcmp_retry_inj_ctrl1 inj_ctrl1 = {};
	union aw_ucie_adapter_test_comp_reg_reg_adapter_tstcmp_retry_inj_ctrl2 inj_ctrl2 = {};
	union aw_ucie_adapter_test_comp_reg_reg_adapter_tstcmp_test_sts test_sts = {};

	inj_ctrl1.error_inj_type_on_txd_flits = error_type;
	inj_ctrl1.byte_offset = byte_offset;
	inj_ctrl1.num_of_errs_btwn_inj_errs = num_btwn_err;
	inj_ctrl1.num_of_errs_inj = num_err_flits;
	inj_ctrl1.flit_type_for_err_inj = flit_type;
	inj_ctrl2.tx_retry_err_th = retry_threshold;

	target_ss->adapter_test_comp_reg_reg_adapter_tstcmp_retry_inj_ctrl1.val = inj_ctrl1.val;
	target_ss->adapter_test_comp_reg_reg_adapter_tstcmp_retry_inj_ctrl2.val = inj_ctrl2.val;

	target_ss->adapter_test_comp_reg_reg_adapter_tstcmp_retry_inj_ctrl1.retry_inj_enable = 1;
	do {
		test_sts.val = target_ss->adapter_test_comp_reg_reg_adapter_tstcmp_test_sts.val;
	} while (test_sts.retry_inj_sts != RETRY_INJECT_STAT_DONE);
	target_ss->adapter_test_comp_reg_reg_adapter_tstcmp_retry_inj_ctrl1.retry_inj_enable = 0;

	return RL_OK;
}

int32_t do_runtime_link_test(const uint32_t m0_repair, const uint32_t m1_repair, const uint32_t m0_lane_id,
							 const uint32_t m1_lane_id, const uint32_t stuck_at_fault)
{
	CHECK_TARGET_UCIE_SS();
	union aw_ucie_phy_d2d_reg_reg_phy_d2d_runtime_link_test_cntrl_reg1 cntrl = {};

	cntrl.m0_lane_repair = m0_repair;
	cntrl.m1_lane_repair = m1_repair;
	cntrl.m0_lane_repair_id = m0_lane_id;
	cntrl.m1_lane_repair_id = m1_lane_id;
	cntrl.inj_stuck_at_fault = stuck_at_fault;
	target_ss->phy_d2d_reg_reg_phy_d2d_runtime_link_test_cntrl_reg1.val = cntrl.val;

	cntrl.start = true;
	target_ss->phy_d2d_reg_reg_phy_d2d_runtime_link_test_cntrl_reg1.start = cntrl.start;

	uint32_t busy = true;

	do {
		busy = target_ss->phy_d2d_reg_reg_phy_d2d_runtime_link_status_reg2.busy;
	} while (busy);
	return RL_OK;
}

/* Device driver to verify "inject stuck at fault" later
 * int32_t aw_ucie_inject_stuck_at_fault_in_runtime_link_test(const uint32_t val){
 * CHECK_TARGET_UCIE_SS();
 * target_ss->phy_d2d_reg_reg_phy_d2d_runtime_link_test_cntrl_reg1.val = val;
 * return RL_OK;
 * }
 */

int32_t aw_ucie_get_m0_lane_repair_stat(uint32_t * const trd_val, uint32_t * const rrd_val)
{
	CHECK_TARGET_UCIE_SS();
	*trd_val = target_ss->phy_d2d_reg_reg_phy_d2d_m0_mb_data_repair_reg1.val;
	*rrd_val = target_ss->phy_d2d_reg_reg_phy_d2d_m0_mb_data_repair_reg2.val;
	return RL_OK;
}

int32_t aw_ucie_get_m1_lane_repair_stat(uint32_t * const trd_val, uint32_t * const rrd_val)
{
	CHECK_TARGET_UCIE_SS();
	*trd_val = target_ss->phy_d2d_reg_reg_phy_d2d_m1_mb_data_repair_reg1.val;
	*rrd_val = target_ss->phy_d2d_reg_reg_phy_d2d_m1_mb_data_repair_reg2.val;
	return RL_OK;
}

int32_t aw_ucie_set_phy_compliance_enable(const uint32_t module_sel, const uint32_t m0_compl_en)
{
	CHECK_TARGET_UCIE_SS();
	if (!module_sel)
		target_ss->phy_test_comp_reg_reg_phy_tstcmp_m0_compl_ctrl1_1.m0_compl_en = m0_compl_en;
	else
		target_ss->phy_test_comp_reg_reg_phy_tstcmp_m1_compl_ctrl1_1.m1_compl_en = m0_compl_en;

	return RL_OK;
}

int32_t aw_ucie_get_phy_compliance_mode(const uint32_t module_sel, uint32_t * const mode)
{
	CHECK_TARGET_UCIE_SS();
	if (!module_sel)
		*mode = target_ss->phy_test_comp_reg_reg_phy_tstcmp_m0_compl_status1.m0_mode;
	else
		*mode = target_ss->phy_test_comp_reg_reg_phy_tstcmp_m1_compl_stat1.m1_mode;

	return RL_OK;
}

int32_t aw_ucie_set_scrambling_disable(const uint32_t module_sel, const uint32_t scram_disabled)
{
	CHECK_TARGET_UCIE_SS();
	if (!module_sel)
		target_ss->phy_test_comp_reg_reg_phy_tstcmp_m0_compl_ctrl1_1.m0_scram_disabled = scram_disabled;
	else
		target_ss->phy_test_comp_reg_reg_phy_tstcmp_m1_compl_ctrl1_1.m1_scram_disabled = scram_disabled;

	return RL_OK;
}

int32_t aw_ucie_get_scrambling_disable(const uint32_t module_sel, uint32_t * const scram_disabled)
{
	CHECK_TARGET_UCIE_SS();
	if (!module_sel)
		*scram_disabled = target_ss->phy_test_comp_reg_reg_phy_tstcmp_m0_compl_ctrl1_1.m0_scram_disabled;
	else
		*scram_disabled = target_ss->phy_test_comp_reg_reg_phy_tstcmp_m1_compl_ctrl1_1.m1_scram_disabled;

	return RL_OK;
}

int32_t aw_ucie_do_phy_compliance_operation(const uint32_t module_sel, const uint32_t operation_trigger,
											const uint32_t operation_type)
{
	CHECK_TARGET_UCIE_SS();
	if (!module_sel) {
		target_ss->phy_test_comp_reg_reg_phy_tstcmp_m0_compl_ctrl1_1.m0_operation_type = operation_type;
		target_ss->phy_test_comp_reg_reg_phy_tstcmp_m0_compl_ctrl1_1.m0_operation_trigger = operation_trigger;
	} else {
		target_ss->phy_test_comp_reg_reg_phy_tstcmp_m1_compl_ctrl1_1.m1_operation_type = operation_type;
		target_ss->phy_test_comp_reg_reg_phy_tstcmp_m1_compl_ctrl1_1.m1_operation_trigger = operation_trigger;

	}
	return RL_OK;
}

int32_t aw_ucie_get_phy_compliance_operation_status(const uint32_t module_sel, uint32_t * const operation_status)
{
	CHECK_TARGET_UCIE_SS();
	if (!module_sel)
		*operation_status = target_ss->phy_test_comp_reg_reg_phy_tstcmp_m0_compl_status1.m0_operation_status;
	else
		*operation_status = target_ss->phy_test_comp_reg_reg_phy_tstcmp_m1_compl_stat1.m1_operation_status;

	return RL_OK;
}

int32_t aw_ucie_set_data_pattern_of_train_setup1(const uint32_t module_sel, const uint32_t data_pattern)
{
	CHECK_TARGET_UCIE_SS();
	if (!module_sel)
		target_ss->phy_d2d_reg_reg_phy_d2d_m0_train_setup1.m0_data_pattern = data_pattern;
	else
		target_ss->phy_d2d_reg_reg_phy_d2d_m1_train_setup1.m1_data_pattern = data_pattern;

	return RL_OK;
}

int32_t aw_ucie_get_data_pattern_of_train_setup1(const uint32_t module_sel, uint32_t * const data_pattern)
{
	CHECK_TARGET_UCIE_SS();
	if (!module_sel)
		*data_pattern = target_ss->phy_d2d_reg_reg_phy_d2d_m0_train_setup1.m0_data_pattern;
	else
		*data_pattern = target_ss->phy_d2d_reg_reg_phy_d2d_m1_train_setup1.m1_data_pattern;

	return RL_OK;
}

int32_t aw_ucie_set_valid_pattern_of_train_setup1(const uint32_t module_sel, const uint32_t valid_pattern)
{
	CHECK_TARGET_UCIE_SS();
	if (!module_sel)
		target_ss->phy_d2d_reg_reg_phy_d2d_m0_train_setup1.m0_valid_pattern = valid_pattern;
	else
		target_ss->phy_d2d_reg_reg_phy_d2d_m1_train_setup1.m1_valid_pattern = valid_pattern;

	return RL_OK;
}

int32_t aw_ucie_get_valid_pattern_of_train_setup1(const uint32_t module_sel, uint32_t * const valid_pattern)
{
	CHECK_TARGET_UCIE_SS();
	if (!module_sel)
		*valid_pattern = target_ss->phy_d2d_reg_reg_phy_d2d_m0_train_setup1.m0_valid_pattern;
	else
		*valid_pattern = target_ss->phy_d2d_reg_reg_phy_d2d_m1_train_setup1.m1_valid_pattern;

	return RL_OK;
}

int32_t aw_ucie_set_clk_phase_cntrl_of_train_setup1(const uint32_t module_sel, const uint32_t clk_phase_cntrl)
{
	CHECK_TARGET_UCIE_SS();
	if (!module_sel)
		target_ss->phy_d2d_reg_reg_phy_d2d_m0_train_setup1.m0_clk_phase_cntrl = clk_phase_cntrl;
	else
		target_ss->phy_d2d_reg_reg_phy_d2d_m1_train_setup1.m1_clk_phase_cntrl = clk_phase_cntrl;

	return RL_OK;
}

int32_t aw_ucie_get_clk_phase_cntrl_of_train_setup1(const uint32_t module_sel, uint32_t * const clk_phase_cntrl)
{
	CHECK_TARGET_UCIE_SS();
	if (!module_sel)
		*clk_phase_cntrl = target_ss->phy_d2d_reg_reg_phy_d2d_m0_train_setup1.m0_clk_phase_cntrl;
	else
		*clk_phase_cntrl = target_ss->phy_d2d_reg_reg_phy_d2d_m1_train_setup1.m1_clk_phase_cntrl;

	return RL_OK;
}

int32_t aw_ucie_set_train_mode_of_train_setup1(const uint32_t module_sel, const uint32_t train_mode)
{
	CHECK_TARGET_UCIE_SS();
	if (!module_sel)
		target_ss->phy_d2d_reg_reg_phy_d2d_m0_train_setup1.m0_train_mode = train_mode;
	else
		target_ss->phy_d2d_reg_reg_phy_d2d_m1_train_setup1.m1_train_mode = train_mode;

	return RL_OK;
}

int32_t aw_ucie_get_train_mode_of_train_setup1(const uint32_t module_sel, uint32_t * const train_mode)
{
	CHECK_TARGET_UCIE_SS();
	if (!module_sel)
		*train_mode = target_ss->phy_d2d_reg_reg_phy_d2d_m0_train_setup1.m0_train_mode;
	else
		*train_mode = target_ss->phy_d2d_reg_reg_phy_d2d_m1_train_setup1.m1_train_mode;

	return RL_OK;
}

int32_t aw_ucie_set_burst_cnt_of_train_setup1(const uint32_t module_sel, const uint32_t burst_cnt)
{
	CHECK_TARGET_UCIE_SS();
	if (!module_sel)
		target_ss->phy_d2d_reg_reg_phy_d2d_m0_train_setup1.m0_burst_cnt = burst_cnt;
	else
		target_ss->phy_d2d_reg_reg_phy_d2d_m1_train_setup1.m1_burst_cnt = burst_cnt;

	return RL_OK;
}

int32_t aw_ucie_get_burst_cnt_of_train_setup1(const uint32_t module_sel, uint32_t * const burst_cnt)
{
	CHECK_TARGET_UCIE_SS();
	if (!module_sel)
		*burst_cnt = target_ss->phy_d2d_reg_reg_phy_d2d_m0_train_setup1.m0_burst_cnt;
	else
		*burst_cnt = target_ss->phy_d2d_reg_reg_phy_d2d_m1_train_setup1.m1_burst_cnt;

	return RL_OK;
}

int32_t aw_ucie_set_idle_cnt_of_train_setup2(const uint32_t module_sel, const uint32_t idle_cnt)
{
	CHECK_TARGET_UCIE_SS();
	if (!module_sel)
		target_ss->phy_d2d_reg_reg_phy_d2d_m0_train_setup2.m0_idle_cnt = idle_cnt;
	else
		target_ss->phy_d2d_reg_reg_phy_d2d_m1_train_setup2.m1_idle_cnt = idle_cnt;

	return RL_OK;
}

int32_t aw_ucie_get_idle_cnt_of_train_setup2(const uint32_t module_sel, uint32_t * const idle_cnt)
{
	CHECK_TARGET_UCIE_SS();
	if (!module_sel)
		*idle_cnt = target_ss->phy_d2d_reg_reg_phy_d2d_m0_train_setup2.m0_idle_cnt;
	else
		*idle_cnt = target_ss->phy_d2d_reg_reg_phy_d2d_m1_train_setup2.m1_idle_cnt;

	return RL_OK;
}

int32_t aw_ucie_set_iterations_of_train_setup2(const uint32_t module_sel, const uint32_t iterations)
{
	CHECK_TARGET_UCIE_SS();
	if (!module_sel)
		target_ss->phy_d2d_reg_reg_phy_d2d_m0_train_setup2.m0_iterations = iterations;
	else
		target_ss->phy_d2d_reg_reg_phy_d2d_m1_train_setup2.m1_iterations = iterations;

	return RL_OK;
}

int32_t aw_ucie_get_iterations_of_train_setup2(const uint32_t module_sel, uint32_t * const iterations)
{
	CHECK_TARGET_UCIE_SS();
	if (!module_sel)
		*iterations = target_ss->phy_d2d_reg_reg_phy_d2d_m0_train_setup2.m0_iterations;
	else
		*iterations = target_ss->phy_d2d_reg_reg_phy_d2d_m1_train_setup2.m1_iterations;

	return RL_OK;
}

int32_t aw_ucie_set_lane_mask_of_train_setup3(const uint32_t module_sel, const uint64_t reg_lane_mask)
{
	CHECK_TARGET_UCIE_SS();
	if (!module_sel) {
		target_ss->phy_d2d_reg_reg_phy_d2d_m0_train_setup3_1.m0_reg1_lane_mask = (uint32_t)(reg_lane_mask & 0xFFFFFFFF);
		target_ss->phy_d2d_reg_reg_phy_d2d_m0_train_setup3_2.m0_reg2_lane_mask =
																		(uint32_t)((reg_lane_mask >> 32) & 0xFFFFFFFF);
	} else {
		target_ss->phy_d2d_reg_reg_phy_d2d_m1_train_setup3_1.m1_reg1_lane_mask = (uint32_t)(reg_lane_mask & 0xFFFFFFFF);
		target_ss->phy_d2d_reg_reg_phy_d2d_m1_train_setup3_2.m1_reg2_lane_mask =
																		(uint32_t)((reg_lane_mask >> 32) & 0xFFFFFFFF);
	}
	return RL_OK;
}

int32_t aw_ucie_get_lane_mask_of_train_setup3(const uint32_t module_sel, uint64_t * const reg_lane_mask)
{
	CHECK_TARGET_UCIE_SS();
	if (!module_sel) {
		*reg_lane_mask =
				((uint64_t)target_ss->phy_d2d_reg_reg_phy_d2d_m0_train_setup3_2.m0_reg2_lane_mask << 32) |
				target_ss->phy_d2d_reg_reg_phy_d2d_m0_train_setup3_1.m0_reg1_lane_mask;
	} else {
		*reg_lane_mask =
				((uint64_t)target_ss->phy_d2d_reg_reg_phy_d2d_m1_train_setup3_2.m1_reg2_lane_mask << 32) |
				target_ss->phy_d2d_reg_reg_phy_d2d_m1_train_setup3_1.m1_reg1_lane_mask;
	}
	return RL_OK;
}

int32_t aw_ucie_set_repair_lane_mask_of_train_setup4(const uint32_t module_sel, const uint32_t repair_lane_mask)
{
	CHECK_TARGET_UCIE_SS();
	if (!module_sel)
		target_ss->phy_d2d_reg_reg_phy_d2d_m0_train_setup4.m0_repair_lane_mask = repair_lane_mask;
	else
		target_ss->phy_d2d_reg_reg_phy_d2d_m1_train_setup4.m1_repair_lane_mask = repair_lane_mask;
	return RL_OK;
}

int32_t aw_ucie_get_repair_lane_mask_of_train_setup4(const uint32_t module_sel, uint32_t * const repair_lane_mask)
{
	CHECK_TARGET_UCIE_SS();
	if (!module_sel)
		*repair_lane_mask = target_ss->phy_d2d_reg_reg_phy_d2d_m0_train_setup4.m0_repair_lane_mask;
	else
		*repair_lane_mask = target_ss->phy_d2d_reg_reg_phy_d2d_m1_train_setup4.m1_repair_lane_mask;
	return RL_OK;
}

int32_t aw_ucie_set_max_err_th_per_lane_of_train_setup4(const uint32_t module_sel, const uint32_t max_err_th_per_lane)
{
	CHECK_TARGET_UCIE_SS();
	if (!module_sel)
		target_ss->phy_d2d_reg_reg_phy_d2d_m0_train_setup4.m0_max_err_th_per_lane = max_err_th_per_lane;
	else
		target_ss->phy_d2d_reg_reg_phy_d2d_m1_train_setup4.m1_max_err_th_per_lane = max_err_th_per_lane;
	return RL_OK;
}

int32_t aw_ucie_get_max_err_th_per_lane_of_train_setup4(const uint32_t module_sel, uint32_t * const max_err_th_per_lane)
{
	CHECK_TARGET_UCIE_SS();
	if (!module_sel)
		*max_err_th_per_lane = target_ss->phy_d2d_reg_reg_phy_d2d_m0_train_setup4.m0_max_err_th_per_lane;
	else
		*max_err_th_per_lane = target_ss->phy_d2d_reg_reg_phy_d2d_m1_train_setup4.m1_max_err_th_per_lane;

	return RL_OK;
}

int32_t aw_ucie_set_max_err_th_aggregate_of_train_setup4(const uint32_t module_sel, const uint32_t max_err_th_aggregate)
{
	CHECK_TARGET_UCIE_SS();
	if (!module_sel)
		target_ss->phy_d2d_reg_reg_phy_d2d_m0_train_setup4.m0_max_err_th_aggregate = max_err_th_aggregate;
	else
		target_ss->phy_d2d_reg_reg_phy_d2d_m1_train_setup4.m1_max_err_th_aggregate = max_err_th_aggregate;
	return RL_OK;
}

int32_t aw_ucie_get_max_err_th_aggregate_of_train_setup4(const uint32_t module_sel,
														 uint32_t * const max_err_th_aggregate)
{
	CHECK_TARGET_UCIE_SS();
	if (!module_sel)
		*max_err_th_aggregate = target_ss->phy_d2d_reg_reg_phy_d2d_m0_train_setup4.m0_max_err_th_aggregate;
	else
		*max_err_th_aggregate = target_ss->phy_d2d_reg_reg_phy_d2d_m1_train_setup4.m1_max_err_th_aggregate;
	return RL_OK;
}

static int32_t aw_ucie_set_rx_vref_offset_enable_impl(const uint32_t module_sel, const uint32_t rx_vref_offset_enable)
{
	CHECK_TARGET_UCIE_SS();
	if (!module_sel)
		target_ss->phy_test_comp_reg_reg_phy_tstcmp_m0_compl_ctrl1_1.m0_rx_vref_offset_enable = rx_vref_offset_enable;
	else
		target_ss->phy_test_comp_reg_reg_phy_tstcmp_m1_compl_ctrl1_1.m1_rx_vref_offset_enable = rx_vref_offset_enable;

	return RL_OK;
}

static int32_t aw_ucie_set_rx_vref_offset_impl(const uint32_t module_sel, const uint32_t rx_vref_offset)
{
	CHECK_TARGET_UCIE_SS();
	if (!module_sel)
		target_ss->phy_test_comp_reg_reg_phy_tstcmp_m0_compl_ctrl1_1.m0_rx_vref_offset = rx_vref_offset;
	else
		target_ss->phy_test_comp_reg_reg_phy_tstcmp_m1_compl_ctrl1_1.m1_rx_vref_offset = rx_vref_offset;
	return RL_OK;
}

int32_t aw_ucie_get_rx_vref_offset_operation_status(const uint32_t module_sel,
													uint32_t * const rx_vref_offset_operation_status)
{
	CHECK_TARGET_UCIE_SS();
	if (!module_sel)
		*rx_vref_offset_operation_status =
		target_ss->phy_test_comp_reg_reg_phy_tstcmp_m0_compl_status1.m0_rx_vref_offset_operation_status;
	else
		*rx_vref_offset_operation_status =
		target_ss->phy_test_comp_reg_reg_phy_tstcmp_m1_compl_stat1.m1_rx_vref_offset_operation_status;
	return RL_OK;
}

int32_t aw_ucie_set_even_ui_compare_mask(const uint32_t module_sel, const uint32_t even_ui_compare_mask)
{
	CHECK_TARGET_UCIE_SS();
	if (!module_sel)
		target_ss->phy_test_comp_reg_reg_phy_tstcmp_m0_compl_ctrl2.m0_even_ui_compare_mask = even_ui_compare_mask;
	else
		target_ss->phy_test_comp_reg_reg_phy_tstcmp_m1_compl_ctrl2.m1_even_ui_compare_mask = even_ui_compare_mask;
	return RL_OK;
}

int32_t aw_ucie_get_even_ui_compare_mask(const uint32_t module_sel, uint32_t * const even_ui_compare_mask)
{
	CHECK_TARGET_UCIE_SS();
	if (!module_sel)
		*even_ui_compare_mask = target_ss->phy_test_comp_reg_reg_phy_tstcmp_m0_compl_ctrl2.m0_even_ui_compare_mask;
	else
		*even_ui_compare_mask = target_ss->phy_test_comp_reg_reg_phy_tstcmp_m1_compl_ctrl2.m1_even_ui_compare_mask;
	return RL_OK;
}

int32_t aw_ucie_set_odd_ui_compare_mask(const uint32_t module_sel, const uint32_t odd_ui_compare_mask)
{
	CHECK_TARGET_UCIE_SS();
	if (!module_sel)
		target_ss->phy_test_comp_reg_reg_phy_tstcmp_m0_compl_ctrl2.m0_odd_ui_compare_mask = odd_ui_compare_mask;
	else
		target_ss->phy_test_comp_reg_reg_phy_tstcmp_m1_compl_ctrl2.m1_odd_ui_compare_mask = odd_ui_compare_mask;
	return RL_OK;
}

int32_t aw_ucie_get_odd_ui_compare_mask(const uint32_t module_sel, uint32_t * const odd_ui_compare_mask)
{
	CHECK_TARGET_UCIE_SS();
	if (!module_sel)
		*odd_ui_compare_mask = target_ss->phy_test_comp_reg_reg_phy_tstcmp_m0_compl_ctrl2.m0_odd_ui_compare_mask;
	else
		*odd_ui_compare_mask = target_ss->phy_test_comp_reg_reg_phy_tstcmp_m1_compl_ctrl2.m1_odd_ui_compare_mask;
	return RL_OK;
}

int32_t aw_ucie_set_track_enable(const uint32_t module_sel, const uint32_t track_enable)
{
	CHECK_TARGET_UCIE_SS();
	if (!module_sel)
		target_ss->phy_test_comp_reg_reg_phy_tstcmp_m0_compl_ctrl2.m0_track_enable = track_enable;
	else
		target_ss->phy_test_comp_reg_reg_phy_tstcmp_m1_compl_ctrl2.m1_track_enable = track_enable;
	return RL_OK;
}

int32_t aw_ucie_get_track_enable(const uint32_t module_sel, uint32_t * const track_enable)
{
	CHECK_TARGET_UCIE_SS();
	if (!module_sel)
		*track_enable = target_ss->phy_test_comp_reg_reg_phy_tstcmp_m0_compl_ctrl2.m0_track_enable;
	else
		*track_enable = target_ss->phy_test_comp_reg_reg_phy_tstcmp_m1_compl_ctrl2.m1_track_enable;
	return RL_OK;
}

int32_t aw_ucie_set_compare_setup(const uint32_t module_sel, const uint32_t compare_setup)
{
	CHECK_TARGET_UCIE_SS();
	if (!module_sel)
		target_ss->phy_test_comp_reg_reg_phy_tstcmp_m0_compl_ctrl2.m0_compare_setup = compare_setup;
	else
		target_ss->phy_test_comp_reg_reg_phy_tstcmp_m1_compl_ctrl2.m1_compare_setup = compare_setup;
	return RL_OK;
}

int32_t aw_ucie_get_compare_setup(const uint32_t module_sel, uint32_t * const compare_setup)
{
	CHECK_TARGET_UCIE_SS();
	if (!module_sel)
		*compare_setup = target_ss->phy_test_comp_reg_reg_phy_tstcmp_m0_compl_ctrl2.m0_compare_setup;
	else
		*compare_setup = target_ss->phy_test_comp_reg_reg_phy_tstcmp_m1_compl_ctrl2.m1_compare_setup;

	return RL_OK;
}

static int32_t aw_ucie_retrain_and_get_new_eml_emr_impl(const uint32_t module_sel, uint32_t * const eml,
														uint32_t * const emr, const uint32_t lane_id)
{
	union aw_ucie_phy_d2d_reg_reg_phy_d2d_uhm_status uhm_status = {};

	CHECK_TARGET_UCIE_SS();

	uhm_status.val = target_ss->phy_d2d_reg_reg_phy_d2d_uhm_status.val;

	/* clear previous status data */
	target_ss->phy_d2d_reg_reg_phy_d2d_uhm_status.val = uhm_status.val;

	aw_ucie_link_retraining();

	uhm_status.val = target_ss->phy_d2d_reg_reg_phy_d2d_uhm_status.val;

	if (uhm_status.status_emv == 0) {
		return RL_ERROR;
	}
	uint32_t offset = lane_id / 2;
	uint32_t parity = lane_id % 2;

	if (module_sel == 0) {
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln0_ln1_m0 *eml_emr_m0 =
			(union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln0_ln1_m0 *)
			(&target_ss->phy_d2d_reg_reg_phy_d2d_eml_emr_ln0_ln1_m0 + offset);

		if (parity == 0) {
			*eml = eml_emr_m0->val & 0xFF;
			*emr = (eml_emr_m0->val >> 8) & 0xFF;
		} else {
			*eml = (eml_emr_m0->val >> 16) & 0xFF;
			*emr = (eml_emr_m0->val >> 24) & 0xFF;
		}
		return RL_OK;

	} else if (module_sel == 1) {
		union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln0_ln1_m1 *eml_emr_m1 =
			(union aw_ucie_phy_d2d_reg_reg_phy_d2d_eml_emr_ln0_ln1_m1 *)
			(&target_ss->phy_d2d_reg_reg_phy_d2d_eml_emr_ln0_ln1_m1 + offset);

		if (parity == 0) {
			*eml = eml_emr_m1->val & 0xFF;
			*emr = (eml_emr_m1->val >> 8) & 0xFF;
		} else {
			*eml = (eml_emr_m1->val >> 16) & 0xFF;
			*emr = (eml_emr_m1->val >> 24) & 0xFF;
		}
		return RL_OK;

	} else {
		return RL_ERROR;
	}
}

int32_t (*aw_ucie_init)(const int32_t ucie_ss_id, void * const base_address) = aw_ucie_init_impl;

int32_t (*aw_ucie_link_training)(void) = aw_ucie_link_training_impl;
int32_t (*aw_ucie_link_retraining)(void) = aw_ucie_link_retraining_impl;
int32_t (*aw_ucie_sb_mem_rd32)(const uint32_t, const uint32_t, uint32_t * const) = aw_ucie_sb_mem_rd32_impl;
int32_t (*aw_ucie_sb_mem_wr32)(const uint32_t, const uint32_t, uint32_t * const) = aw_ucie_sb_mem_wr32_impl;

int32_t (*aw_ucie_mb_crc_err_inject)(const uint32_t, const uint32_t) = aw_ucie_mb_crc_err_inject_impl;
int32_t (*aw_ucie_mb_inject_nop_flit)(const uint32_t, const uint32_t) = aw_ucie_mb_inject_nop_flit_impl;
int32_t (*aw_ucie_mb_inject_test_flit)(const uint32_t, const uint32_t,
									   const uint32_t, const uint32_t,
									   const uint32_t, const uint32_t) = aw_ucie_mb_inject_test_flit_impl;
int32_t (*aw_ucie_set_rx_vref_offset)(const uint32_t module_sel,
									  const uint32_t rx_vref_offset) = aw_ucie_set_rx_vref_offset_impl;
int32_t (*aw_ucie_set_rx_vref_offset_enable)(const uint32_t module_sel,
											 const uint32_t rx_vref_offset_enable) =
											 aw_ucie_set_rx_vref_offset_enable_impl;
int32_t (*aw_ucie_retrain_and_get_new_eml_emr)(const uint32_t module_sel, uint32_t * const eml, uint32_t * const emr,
											   const uint32_t lane_id) =
											   aw_ucie_retrain_and_get_new_eml_emr_impl;
