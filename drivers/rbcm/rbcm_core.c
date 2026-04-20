/*
 * [Rebellions Inc.]("Rebellions") CONFIDENTIAL
 * Unpublished Copyright (c) 2025 [Rebellions Inc.], All Rights Reserved.
 *
 * NOTICE: All information contained herein is, and remains the property of Rebellions.
 * The intellectual and technical concepts contained herein are proprietary to Rebellions
 * and may be covered by Republic of Korea, U.S., and other countries' Patents, patents
 * in process, and are protected by trade secret or copyright law.
 *
 * Dissemination of this information or reproduction of this material is strictly forbidden
 * unless prior written permission is obtained from Rebellions. Access to the source code
 * contained herein is hereby forbidden to anyone except current Rebellions employees, managers
 * or contractors who have executed Confidentiality and Non-disclosure agreements explicitly
 * covering such access.
 *
 * The copyright notice above does not evidence any actual or intended publication or disclosure
 * of this source code, which includes information that is confidential and/or proprietary, and
 * is a trade secret, of Rebellions.
 *
 * ANY REPRODUCTION, MODIFICATION, DISTRIBUTION, PUBLIC PERFORMANCE, OR PUBLIC DISPLAY OF OR
 * THROUGH USE OF THIS SOURCE CODE WITHOUT THE EXPRESS WRITTEN CONSENT OF REBELLIONS IS STRICTLY
 * PROHIBITED, AND IN VIOLATION OF APPLICABLE LAWS AND INTERNATIONAL TREATIES. THE RECEIPT OR
 * POSSESSION OF THIS SOURCE CODE AND/OR RELATED INFORMATION DOES NOT CONVEY OR IMPLY ANY RIGHTS
 * TO REPRODUCE, DISCLOSE OR DISTRIBUTE ITS CONTENTS, OR TO MANUFACTURE, USE, OR SELL ANYTHING
 * THAT IT MAY DESCRIBE, IN WHOLE OR IN PART.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <ctype.h>

#include "FreeRTOS.h"
#include "task.h"
#include "rbcm_core.h"
#include "rbcm_reg_model.h"
#include "rl_errors.h"
#include "rbcm_common.h"
#include "rl_utils.h"
#include "rbcm_reg_addr.h"

#define dev_fmt(fmt)	"[UCIe] " fmt

#define RBCM_TTREG_ACC_CHK_ACC_ACPT (0x80000000)
#define RBCM_TTREG_RET_0_ACC_DONE (0x1)
#define RBCM_INVALID_ADDRESS (0xffffffffffULL)
#define RBCM_TIMEOUT_TICK_MASK (0xffff)
#define RBCM_TIMEOUT_WINDOW_MASK (0xffff)
#define RBCM_TIMEOUT_TICK_SHIFT (0)
#define RBCM_TIMEOUT_WINDOW_SHIFT (16)
#define RBCM_TTREG_ADDR_SHIFT (24)
#define RBCM_CTL_CLEAR_VAL (0x01010101)
/*
 * Clearing Port2 of the remote RBC_M may cause unexpected results,
 * so Port2 will not be cleared
 */
#define RBCM_DISABLE_CLEAR_PORT2

/* Dead Lock Issue */
#define NOC_REMAP_DISCONNECT_C2_C3

static const char * const ltsm_state_str[] = {
	"RESET",
	"SBINIT",
	"MBINIT_PARAM",
	"MBINIT_CAL",
	"MBINIT_REPAIRCLK",
	"MBINIT_REPAIRVAL",
	"MBINIT_REVERSALMB",
	"MBINIT_REPAIRMB",
	"MBTRAIN_VALVREF",
	"MBTRAIN_DATAVREF",
	"MBTRAIN_SPEEDIDLE",
	"MBTRAIN_TXSELFCAL",
	"MBTRAIN_RXSELFCAL",
	"MBTRAIN_VALTRAINCENTER",
	"MBTRAIN_VALTRAINVREF",
	"MBTRAIN_DATATRAINCENTER1",
	"MBTRAIN_DATATRAINVREF",
	"MBTRAIN_RXDESKEW",
	"MBTRAIN_DATATRAINCENTER2",
	"MBTRAIN_LINKSPEED",
	"MBTRAIN_REPAIR",
	"PHYRETRAIN",
	"LINKINIT",
	"ACTIVE",
	"TRAINERROR",
	"L1_L2"
};

static const char * const link_speed_str[] = {
	"4 GT/s",
	"8 GT/s",
	"12 GT/s",
	"16 GT/s",
	"24 GT/s",
	"32 GT/s",
	"Reserved"
};

static const char * const link_width_str[] = {
	"Reserved",
	"x8",
	"x16",
	"x32",
	"x64",
	"x128",
	"x256"
};

/*
 * UCIe Clk MHz Freq table according to UCIe Link Speed
 *  4 GT/s, 8 TG/s, 12 GT/s, 16 GT/s, 24 GT/s 32 GT/s
 */
static const uint32_t link_freq_mhz_tbl[] = {
	250, 500, 750, 1000, 1500, 2000
};

static const char *rbcm_ltsm_state_to_string(const uint32_t state)
{
	if (state < ARRAY_SIZE(ltsm_state_str))
		return ltsm_state_str[state];

	return "UNKNOWN";
}

static const char *rbcm_rdi_state_to_string(const uint32_t state)
{
	switch (state) {
	case 0:
		return "RESET";
	case 1:
		return "ACTIVE";
	case 3:
		return "ACTIVE_PMNAK";
	case 4:
		return "L1";
	case 8:
		return "L2";
	case 9:
		return "LINK_RESET";
	case 10:
		return "LINK_ERROR";
	case 11:
		return "RETRAIN";
	case 12:
		return "DISABLED";
	default:
		return "RESERVED";
	}
}

static const char *rbcm_link_speed_to_string(enum rbcm_link_speed speed)
{
	if (speed > TARGET_LINK_SPEED_32GT)
		return link_speed_str[TARGET_LINK_SPEED_32GT + 1];

	return link_speed_str[speed];
}

static const char *rbcm_link_width_to_string(enum rbcm_link_width width)
{
	if (width < TARGET_LINK_WIDTH_X8 || width > TARGET_LINK_WIDTH_X256)
		return link_width_str[0];

	return link_width_str[width];
}

static inline const char rbcm_yes_no(uint32_t enabled)
{
	return enabled ? 'Y' : 'N';
}

static void rbcm_log_ucie_crc(const struct rbcm_data *entry)
{
	volatile union aw_ucie_adapter_d2d_reg_reg_adapter_d2d_corr_err_stat *crc_stat;
	volatile union aw_ucie_adapter_imp_spec_rdi_reg_adapter_crc_err_log_reg0 *crc_log_0;
	volatile union aw_ucie_adapter_imp_spec_rdi_reg_adapter_crc_err_log_reg1 *crc_log_1;

	if (!entry || !entry->ucie)
		return;

	crc_stat = &entry->ucie->adapter_d2d_reg_reg_adapter_d2d_corr_err_stat;
	crc_log_0 = &entry->ucie->adapter_imp_spec_rdi_reg_adapter_crc_err_log_reg0;
	crc_log_1 = &entry->ucie->adapter_imp_spec_rdi_reg_adapter_crc_err_log_reg1;

	if (!crc_stat->crc_err_detected) {
		RBCM_LOGI("[%s] No CRC errors\r\n", entry->name);
		return;
	}

	RBCM_LOGE("[%s] CRC errors: log0=0x%08x log1=0x%08x\r\n",
			  entry->name, crc_log_0->val, crc_log_1->val);
}

static void rbcm_log_ucie_link_status(const struct rbcm_data *entry)
{
	volatile union aw_ucie_dvsec1_reg_reg_global_dvsec1_ucie_link_status *link_stat;
	const char *speed_str;
	const char *width_str;
	bool link_up;

	link_stat = &entry->ucie->dvsec1_reg_reg_global_dvsec1_ucie_link_status;
	link_up = link_stat->lstatus_link_status;
	speed_str = rbcm_link_speed_to_string(link_stat->lstatus_link_speed_en);
	width_str = rbcm_link_width_to_string(link_stat->lstatus_link_width_en);

	RBCM_LOGD("[%s] LinkStatus raw=0x%08x\r\n", entry->name, link_stat->val);
	RBCM_LOGD("[%s] status=%s training=%c change=%c auto_bw_change=%c\r\n",
			  entry->name,
			  link_up ? "UP" : "DOWN",
			  rbcm_yes_no(link_stat->lstatus_link_train_or_retrain),
			  rbcm_yes_no(link_stat->lstatus_link_status_change),
			  rbcm_yes_no(link_stat->lstatus_hw_autonomous_bw_change));
	RBCM_LOGD("[%s] width=%s(0x%x) speed=%s(0x%x) flit_fmt=0x%x\r\n",
			  entry->name,
			  width_str, link_stat->lstatus_link_width_en,
			  speed_str, link_stat->lstatus_link_speed_en,
			  link_stat->lstatus_flit_format_status);
	RBCM_LOGD("[%s] raw_fmt=%c multi_stack=%c enhanced_mp=%c adv_pkg_x32=%c\r\n",
			  entry->name,
			  rbcm_yes_no(link_stat->lstatus_raw_format_en),
			  rbcm_yes_no(link_stat->lstatus_multi_stack_en),
			  rbcm_yes_no(link_stat->lstatus_enhanced_multi_protocol_en),
			  rbcm_yes_no(link_stat->lstatus_adv_pkg_mod_size));

	if (!link_up)
		RBCM_LOGW("[%s] Link DOWN (width/speed invalid)\r\n",
				  entry->name);
	else if (link_stat->lstatus_link_train_or_retrain)
		RBCM_LOGI("[%s] Link Training/Retrain in progress\r\n", entry->name);

	if (link_stat->lstatus_link_status_change)
		RBCM_LOGI("[%s] Link status change asserted\r\n", entry->name);

	if (link_stat->lstatus_hw_autonomous_bw_change)
		RBCM_LOGI("[%s] HW auto BW change detected\r\n", entry->name);

	if (link_stat->lstatus_ucie_link_corr_err ||
		link_stat->lstatus_ucie_link_uncorr_non_fatal_err ||
		link_stat->lstatus_ucie_link_uncorr_fatal_err) {
		RBCM_LOGW("[%s] Err corr=%u non_fatal=%u fatal=%u\r\n",
				  entry->name, link_stat->lstatus_ucie_link_corr_err,
				  link_stat->lstatus_ucie_link_uncorr_non_fatal_err,
				  link_stat->lstatus_ucie_link_uncorr_fatal_err);
	} else {
		RBCM_LOGD("[%s] No link errors\r\n", entry->name);
	}
}

static void rbcm_log_phy_state(const struct rbcm_data *entry)
{
	volatile union aw_ucie_phy_d2d_reg_reg_phy_d2d_m0_err_log0 *err_log0_m0;
	volatile union aw_ucie_phy_d2d_reg_reg_phy_d2d_m0_err_log1 *err_log1_m0;
	volatile union aw_ucie_phy_d2d_reg_reg_phy_d2d_m1_err_log0 *err_log0_m1;
	volatile union aw_ucie_phy_d2d_reg_reg_phy_d2d_m1_err_log1 *err_log1_m1;

	err_log0_m0 = &entry->ucie->phy_d2d_reg_reg_phy_d2d_m0_err_log0;
	err_log1_m0 = &entry->ucie->phy_d2d_reg_reg_phy_d2d_m0_err_log1;
	RBCM_LOGD("[%s][M0] LTSM cur=%s(%u) prev=%s/%s lane_rev=%u width_deg=%u\r\n",
			  entry->name,
			  rbcm_ltsm_state_to_string(err_log0_m0->m0_state_n), err_log0_m0->m0_state_n,
			  rbcm_ltsm_state_to_string(err_log0_m0->m0_state_n1),
			  rbcm_ltsm_state_to_string(err_log0_m0->m0_state_n2),
			  err_log0_m0->m0_lane_rev, err_log0_m0->m0_width_deg);
	RBCM_LOGD("[%s][M0] timeout=%u sb_timeout=%u remote_err=%u internal_err=%u\r\n",
			  entry->name,
			  err_log1_m0->m0_state_time_out, err_log1_m0->m0_sb_time_out,
			  err_log1_m0->m0_remote_link_err, err_log1_m0->m0_internal_err);

	err_log0_m1 = &entry->ucie->phy_d2d_reg_reg_phy_d2d_m1_err_log0;
	err_log1_m1 = &entry->ucie->phy_d2d_reg_reg_phy_d2d_m1_err_log1;
	RBCM_LOGD("[%s][M1] LTSM cur=%s(%u) prev=%s/%s lane_rev=%u width_deg=%u\r\n",
			  entry->name,
			  rbcm_ltsm_state_to_string(err_log0_m1->m1_state_n), err_log0_m1->m1_state_n,
			  rbcm_ltsm_state_to_string(err_log0_m1->m1_state_n1),
			  rbcm_ltsm_state_to_string(err_log0_m1->m1_state_n2),
			  err_log0_m1->m1_lane_rev, err_log0_m1->m1_width_deg);
	RBCM_LOGD("[%s][M1] timeout=%u sb_timeout=%u remote_err=%u internal_err=%u\r\n",
			  entry->name,
			  err_log1_m1->m1_state_time_out, err_log1_m1->m1_sb_time_out,
			  err_log1_m1->m1_remote_link_err, err_log1_m1->m1_internal_err);
}

static void rbcm_log_rdi_status(const struct rbcm_data *entry)
{
	volatile union aw_ucie_phy_imp_spec_reg_phy_rdi_pl_cfg1 *rdi_pl;

	rdi_pl = &entry->ucie->phy_imp_spec_reg_phy_rdi_pl_cfg1;
	RBCM_LOGD("[%s][RDI] state=%s(%u) inband=%u phy_retrain=%u speed=0x%x width=0x%x\r\n",
			  entry->name,
			  rbcm_rdi_state_to_string(rdi_pl->rdi_pl_state_sts), rdi_pl->rdi_pl_state_sts,
			  rdi_pl->rdi_pl_inband_pres, rdi_pl->rdi_pl_phyinrecenter,
			  rdi_pl->rdi_pl_speedmode, rdi_pl->rdi_pl_lnk_cfg);
	RBCM_LOGD("[%s][RDI] clk_req=%u wake_ack=%u stall=%u err=%u corr=%u non_fatal=%u train=%u\r\n",
			  entry->name,
			  rdi_pl->rdi_pl_clk_req, rdi_pl->rdi_pl_wake_ack, rdi_pl->rdi_pl_stallreq,
			  rdi_pl->rdi_pl_error, rdi_pl->rdi_pl_cerror,
			  rdi_pl->rdi_pl_nferror, rdi_pl->rdi_pl_trainerror);
}

int32_t rbcm_core_dump_ucie_link_health(struct rbcm_data *entry)
{
	if (!entry || !entry->ucie)
		return RL_BADARG;

	rbcm_log_ucie_link_status(entry);
	rbcm_log_phy_state(entry);
	rbcm_log_rdi_status(entry);

	return RL_OK;
}

int32_t rbcm_core_dump_ucie_crc(struct rbcm_data *entry)
{
	if (!entry || !entry->ucie)
		return RL_BADARG;

	rbcm_log_ucie_crc(entry);

	return RL_OK;
}

static struct user_transaction_config *
get_utg_cfg_block(struct rbc_reg *reg, enum rbc_port port, int read_access)
{
	switch (port) {
	case RBC_PORT0:
		return (struct user_transaction_config *)(read_access ?
				(void *)&reg->user_transaction_p0_r_config0 :
				(void *)&reg->user_transaction_p0_w_config0);
	case RBC_PORT1:
		return (struct user_transaction_config *)(read_access ?
				(void *)&reg->user_transaction_p1_r_config0 :
				(void *)&reg->user_transaction_p1_w_config0);
	case RBC_PORT2:
		return (struct user_transaction_config *)(read_access ?
				(void *)&reg->user_transaction_p2_r_config0 :
				(void *)&reg->user_transaction_p2_w_config0);
	default:
		RBCM_LOGE("Invalid RBC port %d\r\n", port);
		break;
	}

	return NULL;
}

static enum rbcm_ttreg_status get_ttreg_status(struct rbc_reg_ttreg_ret_0_t status)
{
	if (!status.acc_done)
		return RBCM_TTREG_ACC_FAIL;

	if (status.detect_double_error)
		return RBCM_TTREG_DBL_BIT_ERR;

	if (!status.valid)
		return RBCM_TTREG_IDLE;

	if (status.ttreg_error)
		return RBCM_TTREG_ERROR;

	return RBCM_TTREG_PENDING;
}

static const char *rbcm_ttreg_status_to_str(enum rbcm_ttreg_status status)
{
	switch (status) {
	case RBCM_TTREG_PENDING:
		return "PENDING    ";
	case RBCM_TTREG_ACC_FAIL:
		return "ACC_FAIL   ";
	case RBCM_TTREG_DBL_BIT_ERR:
		return "DBL_BIT_ERR";
	case RBCM_TTREG_ERROR:
		return "ERROR      ";
	case RBCM_TTREG_IDLE:
		return "IDLE       ";
	case RBCM_TTREG_BUSY:
		return "BUSY       ";
	case RBCM_TTREG_COMPLETED:
		return "COMPLETED  ";
	default:
		return "UNKNOWN    ";
	}
}

static inline void rbcm_core_start_utg_transaction(struct rbc_reg *reg, enum rbc_port port,
												   int read_access)
{
	/* Start the transaction */
	rbcm_reg_writel(reg, user_transaction_ctl, (1 << (port * 2 + read_access)));
}

static void rbcm_core_set_utg_config(struct user_transaction_config *utg_cfg,
									 enum rbc_port port,
									 uint64_t target_address,
									 int next_user_transaction_id)
{
	struct user_transaction_config utg_val;

	utg_val.config0.value = 0;
	utg_val.config0.id = next_user_transaction_id;
	utg_val.config0.size = (port == RBC_PORT2) ? 2 : 7;
	utg_val.config0.burst = 1;
	utg_val.config0.cache = 0;
	utg_val.config0.lock = 0;
	utg_val.config0.prot = 0;
	utg_val.config0.blen = (port == RBC_PORT2) ? 0 : 7;
	utg_val.config0.qos = 0;

	utg_val.config1.value = 0;
	utg_val.config1.addr_l = (uint32_t)target_address;

	utg_val.config2.value = 0;
	utg_val.config2.addr_h = (uint32_t)(target_address >> 32);
	utg_val.config2.user = 0;

	utg_val.config3.value = 0;
	utg_val.config3.config = 0x4000000f;

	utg_cfg->config0.value = utg_val.config0.value;
	utg_cfg->config1.value = utg_val.config1.value;
	utg_cfg->config2.value = utg_val.config2.value;
	utg_cfg->config3.value = utg_val.config3.value;
}

int32_t rbcm_core_user_traffic_generation(struct rbcm_data *entry, enum rbc_port port,
										  int read_access, uint64_t target_address,
										  int next_user_transaction_id)
{
	struct rbc_reg_rbc_config_t rbc_config_val;
	struct user_transaction_config *utg_cfg;
	struct rbc_reg *reg;
	int poll_timeout;

	reg = entry->reg;
	rbc_config_val.value = rbcm_reg_readl(reg, rbc_config);
	rbc_config_val.transaction_mode = 0;
	rbc_config_val.lb_usr_en = 0;
	rbcm_reg_writel(reg, rbc_config, rbc_config_val.value);

	utg_cfg = get_utg_cfg_block(reg, port, read_access);
	if (!utg_cfg) {
		RBCM_LOGE("Fail to get user trans config port %d\r\n", port);
		return RL_BADARG;
	}
	rbcm_core_set_utg_config(utg_cfg, port, target_address,
							 next_user_transaction_id);
	rbcm_core_start_utg_transaction(reg, port, read_access);

	poll_timeout = RBCM_DEFAULT_POLL_TIMEOUT;
	while ((rbcm_reg_readl(reg, user_transaction_status) & RBCM_UTG_DONE_ALL_MASK) &&
		   poll_timeout-- > 0)
		mdelay(1);

	if (poll_timeout == 0) {
		RBCM_LOGE("Timeout waiting for UTG on port %d %s to complete.\r\n",
				  port, read_access ? "read" : "write");
		return RL_TIMEOUT;
	}

	return RL_OK;
}

static bool rbcm_core_read_ttreg_ret(struct rbc_reg *reg, struct rbcm_ttreg_ret_data *data)
{
	data->ret_0.value = rbcm_reg_readl(reg, TTReg_ret_0);
	data->ret_1.value = rbcm_reg_readl(reg, TTReg_ret_1);
	data->ret_2.value = rbcm_reg_readl(reg, TTReg_ret_2);
	data->ret_3.value = rbcm_reg_readl(reg, TTReg_ret_3);

	data->status = get_ttreg_status(data->ret_0);
	data->address = (uint64_t)data->ret_1.ttreg_addr;
	data->address += (((uint64_t)data->ret_2.ttreg_addr) << RBCM_TTREG_ADDR_SHIFT);

	if (data->status == RBCM_TTREG_IDLE) {
		if (data->address != RBCM_INVALID_ADDRESS) {
			if (data->ret_0.request_valid && data->ret_0.response_valid)
				data->status = RBCM_TTREG_COMPLETED;
		}
	}

	/* Return false if reading failed or invalid */
	if (data->status == RBCM_TTREG_ACC_FAIL)
		return false;

	if (data->status == RBCM_TTREG_DBL_BIT_ERR)
		return false;

	if (data->status == RBCM_TTREG_IDLE && data->address == RBCM_INVALID_ADDRESS)
		return false;

	return true;
}

static uint32_t convert_tick_to_ns(struct rbcm_data *entry, uint16_t ticks)
{
	volatile union aw_ucie_dvsec1_reg_reg_global_dvsec1_ucie_link_status *link_stat;
	struct rbc_reg_timeout_window_config0_t timeout_config;
	/* Default 500MHz (8GT/s) */
	uint32_t link_freq_mhz = link_freq_mhz_tbl[TARGET_LINK_SPEED_8GT];

	uint32_t tick_cfg = 0;

	if (entry && entry->ucie) {
		link_stat = &entry->ucie->dvsec1_reg_reg_global_dvsec1_ucie_link_status;

		if (link_stat->lstatus_link_speed_en <= TARGET_LINK_SPEED_32GT)
			link_freq_mhz = link_freq_mhz_tbl[link_stat->lstatus_link_speed_en];
	}

	/* Tick is 0 because the duration is shorter than the timer resolution */
	if (ticks == 0)
		ticks = 1;
	timeout_config.value = rbcm_reg_readl(entry->reg, Timeout_window_config0);
	tick_cfg = timeout_config.tick;

	/*
	 * Each counter tick = (tick_cfg + 1) * Tclk.
	 * Tclk period(ns) = 1000 / link_freq_mhz.
	 */
	return (uint32_t)(((uint64_t)ticks * ((uint64_t)tick_cfg + 1) * 1000) / link_freq_mhz);
}

static uint32_t rbcm_core_calc_duration_ns(struct rbcm_data *entry, uint16_t start_t,
										   uint16_t end_t, bool *under_resolution)
{
	uint16_t diff_ticks;

	diff_ticks = end_t - start_t;
	if (diff_ticks == 0)
		*under_resolution = true;

	return convert_tick_to_ns(entry, diff_ticks);
}

static uint32_t rbcm_core_print_ttreg(struct rbcm_data *entry, int axi_id, int read_access)
{
	char buf[256];
	int offset = 0;
	uint32_t duration_ns;
	bool under_resolution = false;
	struct rbcm_ttreg_ret_data data = {0, };

	if (!rbcm_core_read_ttreg_ret(entry->reg, &data))
		return RL_ERROR;

	offset += snprintf(buf + offset, sizeof(buf) - offset,
					   "%s  [0x%02x]    %s  [%c%c%c%c%c%c]    0x%010lx",
					   read_access ? "RD" : "WR",
					   axi_id, rbcm_ttreg_status_to_str(data.status),
					   data.ret_0.request_valid ? 'Q' : '.',
					   data.ret_0.response_valid ? 'S' : '.',
					   data.ret_0.request_timeout ? 'T' : '.',
					   data.ret_0.response_timeout ? 't' : '.',
					   data.ret_0.output_request_valid ? 'q' : '.',
					   data.ret_0.output_response_valid ? 's' : '.',
					   (unsigned long)data.address);

	if (data.ret_0.request_valid)
		offset += snprintf(buf + offset, sizeof(buf) - offset, "  %8d", data.ret_2.ttreg_ttst);
	else
		offset += snprintf(buf + offset, sizeof(buf) - offset, "          ");

	if (data.ret_0.response_valid)
		offset += snprintf(buf + offset, sizeof(buf) - offset, " -> %8d", data.ret_3.ttreg_ttet);
	else
		offset += snprintf(buf + offset, sizeof(buf) - offset, "            ");

	/* Duration */
	if (data.ret_0.request_valid && data.ret_0.response_valid) {
		duration_ns = rbcm_core_calc_duration_ns(entry, data.ret_2.ttreg_ttst,
												 data.ret_3.ttreg_ttet,
												 &under_resolution);

		offset += snprintf(buf + offset, sizeof(buf) - offset, "    %8u%s",
						   duration_ns, under_resolution ? "*" : " ");
	}

	snprintf(buf + offset, sizeof(buf) - offset, "\r\n");
	RBCM_PRINTF("%s", buf);

	return RL_OK;
}

static void rbcm_core_select_ttreg_ch(struct rbc_reg *reg, int port, int inbound,
									  int read_access)
{
	uint32_t val = (port << 2) + (inbound << 1) + read_access;

	rbcm_reg_writel(reg, TTReg_sel, val);
}

static bool rbcm_core_select_ttreg_entry(struct rbc_reg *reg, int axi_id)
{
	struct rbc_reg_ttreg_acc_t ttreg_acc_val;
	int timeout;

	ttreg_acc_val.value = rbcm_reg_readl(reg, TTReg_acc);
	ttreg_acc_val.id = axi_id;
	ttreg_acc_val.id_type = 0;
	ttreg_acc_val.acc_req = 1;
	rbcm_reg_writel(reg, TTReg_acc, ttreg_acc_val.value);

	timeout = RBCM_TTREG_POLL_TIMEOUT;
	while (timeout-- > 0) {
		if (rbcm_reg_readl(reg, TTReg_acc_chk) & RBCM_TTREG_ACC_CHK_ACC_ACPT)
			break;

		mdelay(1);
	}
	if (timeout == 0) {
		RBCM_LOGE("Timeout on TTReg_acc_chk for AXID %d\r\n", axi_id);
		return false;
	}

	timeout = RBCM_TTREG_POLL_TIMEOUT;
	while (timeout-- > 0) {
		if (rbcm_reg_readl(reg, TTReg_ret_0) & RBCM_TTREG_RET_0_ACC_DONE)
			break;

		mdelay(1);
	}
	if (timeout == 0) {
		RBCM_LOGE("Timeout on TTReg_ret_0.acc_done for AXID %d\r\n", axi_id);
		return false;
	}

	return true;
}

static void rbcm_core_print_ttreg_header(void)
{
	RBCM_PRINTF("\r\n");
	RBCM_PRINTF("------------------------------------------------------------------------------------------------\r\n");
	RBCM_PRINTF("Access [AXID]    Result       Status      Address       StartT ->   EndT        Duration(ns)\r\n");
	RBCM_PRINTF("------------------------------------------------------------------------------------------------\r\n");
}

static void rbcm_core_print_ttreg_footer(void)
{
	RBCM_PRINTF("------------------------------------------------------------------------------------------------\r\n");
}

static int32_t __rbcm_core_dump_ttreg(struct rbcm_data *entry, enum rbc_port port,
									  int mode, int read_access)
{
	struct rbc_reg *reg;
	int reported_count = 0;

	reg = entry->reg;
	rbcm_core_print_ttreg_header();
	rbcm_core_select_ttreg_ch(reg, port, mode, read_access);

	for (int axi_id = 0; axi_id < TTREG_MAX_ENTRIES; axi_id++) {
		if (!rbcm_core_select_ttreg_entry(reg, axi_id))
			return RL_ERROR;

		if (rbcm_core_print_ttreg(entry, axi_id, read_access) != RL_OK)
			continue;
		else
			reported_count++;
	}

	if (reported_count == 0)
		RBCM_LOGE("No valid %s TTREG entries reported for this channel.\r\n",
				  read_access ? "READ " : "WRITE");

	rbcm_core_print_ttreg_footer();

	return RL_OK;
}

void rbcm_core_dump_incomplete_ttreg(struct rbcm_data *entry)
{
	struct rbc_reg *reg = entry->reg;
	struct rbcm_ttreg_ret_data data = {0, };
	int port, inbound, read_access, axi_id;
	const char *access_result;

	/* Skip Port 2, Dump port2 has issue */
	for (port = 0; port < RBC_PORT_COUNT - 1; port++) {
		for (inbound = 0; inbound <= 1; inbound++) {
			for (read_access = 0; read_access <= 1; read_access++) {
				rbcm_core_select_ttreg_ch(reg, port, inbound, read_access);

				for (axi_id = 0; axi_id < TTREG_MAX_ENTRIES; axi_id++) {
					if (!rbcm_core_select_ttreg_entry(reg, axi_id))
						continue;

					if (!rbcm_core_read_ttreg_ret(reg, &data))
						continue;

					if (data.status != RBCM_TTREG_COMPLETED) {
						access_result = rbcm_ttreg_status_to_str(data.status);
						RBCM_LOGE("%s P%d %s %s [0x%02x] %s [%c%c%c%c%c%c] 0x%lx %d\r\n",
								  entry->name, port,
								  inbound ? "IB" : "OB",
								  read_access ? "RD" : "WR",
								  axi_id,
								  access_result,
								  data.ret_0.request_valid ? 'Q' : '.',
								  data.ret_0.response_valid ? 'S' : '.',
								  data.ret_0.request_timeout ? 'T' : '.',
								  data.ret_0.response_timeout ? 't' : '.',
								  data.ret_0.output_request_valid ? 'q' : '.',
								  data.ret_0.output_response_valid ? 's' : '.',
								  (unsigned long)data.address,
								  data.ret_2.ttreg_ttst);
					}
				}
			}
		}
	}
}

void rbcm_core_dump_chiplet_incomplete_ttreg(int chiplet_id)
{
	extern struct rbcm_data rbcm[RBC_MODULE_COUNT];

	for (int i = 0; i < RBC_MODULE_COUNT; i++) {
		if (rbcm[i].chiplet_id != chiplet_id)
			continue;
		rbcm_core_dump_incomplete_ttreg(&rbcm[i]);
	}
}

bool rbcm_core_is_link_up(struct rbcm_data *entry)
{
	volatile union aw_ucie_dvsec1_reg_reg_global_dvsec1_ucie_link_status *link_stat;

	if (!entry || !entry->ucie)
		return false;

	link_stat = &entry->ucie->dvsec1_reg_reg_global_dvsec1_ucie_link_status;
	return link_stat->lstatus_link_status ? true : false;
}

static const struct rbcm_direct_link direct_links[] = {
	/* Chiplet 0 */
	{0, 1, RBC_C0S0}, {0, 1, RBC_C0S1},
	{0, 2, RBC_C0E0}, {0, 2, RBC_C0E1},
	/* Chiplet 1 */
	{1, 0, RBC_C1N1}, {1, 0, RBC_C1N0},
	{1, 3, RBC_C1E0}, {1, 3, RBC_C1E1},
	/* Chiplet 2 */
	{2, 0, RBC_C2E1}, {2, 0, RBC_C2E0},
#ifndef NOC_REMAP_DISCONNECT_C2_C3
	{2, 3, RBC_C2N0}, {2, 3, RBC_C2N1},
	/* Chiplet 3 */
	{3, 2, RBC_C3S1}, {3, 2, RBC_C3S0},
#endif
	{3, 1, RBC_C3E1}, {3, 1, RBC_C3E0},
};

bool rbcm_core_check_all_chiplet_link_up(int32_t chiplet_id)
{
	extern struct rbcm_data rbcm[RBC_MODULE_COUNT];
	bool reachable[CHIPLET_COUNT] = {false, };
	int queue[CHIPLET_COUNT];
	int head = 0, tail = 0;

	/* BFS Initialization */
	reachable[chiplet_id] = true;
	queue[tail++] = chiplet_id;

	while (head != tail) {
		int curr_id = queue[head++];

		/* Check all outgoing links from curr_id */
		for (int i = 0; i < (int)ARRAY_SIZE(direct_links); i++) {
			if (direct_links[i].src_id != curr_id)
				continue;

			/*
			 * Check if the link is UP.
			 * access rbcm[module] because curr_id is reachable.
			 */
			if (!rbcm_core_is_link_up(&rbcm[direct_links[i].module])) {
				RBCM_LOGE("RBCM[%s] Link %d->%d is DOWN\r\n",
						  rbcm[direct_links[i].module].name,
						  direct_links[i].src_id, direct_links[i].dst_id);
				return false;
			}

			/* If neighbor is not visited, add to queue */
			int neighbor_id = direct_links[i].dst_id;

			if (!reachable[neighbor_id]) {
				reachable[neighbor_id] = true;
				queue[tail++] = neighbor_id;
			}
		}
	}

	RBCM_LOGD("All links reachable from chiplet %d are UP\r\n", chiplet_id);
	return true;
}

void rbcm_core_dump_all_chiplet_incomplete_ttreg(void)
{
	int chiplet_cnt = CHIPLET_CNT;

	for (int i = 0; i < chiplet_cnt; i++)
		rbcm_core_dump_chiplet_incomplete_ttreg(i);
}

int32_t rbcm_core_dump_ttreg(struct rbcm_data *entry, enum rbc_port port, int mode)
{
	int32_t ret;

	ret = __rbcm_core_dump_ttreg(entry, port, mode, RBCM_WR_TRANS);
	if (ret != RL_OK)
		return ret;

	ret = __rbcm_core_dump_ttreg(entry, port, mode, RBCM_RD_TRANS);
	if (ret != RL_OK)
		return ret;

	return RL_OK;
}

bool rbcm_core_is_utg_recorded(struct rbcm_data *entry, enum rbc_port port, int inbound,
							   int read_access, int axi_id)
{
	struct rbcm_ttreg_ret_data data = {0, };
	struct rbc_reg *reg;

	if (!entry || !entry->reg)
		return false;

	reg = entry->reg;
	rbcm_core_select_ttreg_ch(reg, port, inbound, read_access);
	if (!rbcm_core_select_ttreg_entry(reg, axi_id))
		return false;

	if (!rbcm_core_read_ttreg_ret(reg, &data))
		return false;

	if (!data.ret_0.request_valid || !data.ret_0.response_valid)
		return false;

	return true;
}

int32_t rbcm_core_configure_interrupts(struct rbcm_data *entry, int disable, int port_err,
									   int timeout, int cbus_err, int utg_err,
									   int ttreg_err, int utg_done)
{
	struct rbc_reg_rbc_intr_mask_t rbc_intr_mask_val;

	if (!entry || !entry->reg) {
		RBCM_LOGE("Invalid RBCM entry for interrupt configuration\r\n");
		return RL_BADARG;
	}

	rbc_intr_mask_val.value = rbcm_reg_readl(entry->reg, rbc_intr_mask);

	if (port_err)
		rbc_intr_mask_val.port_err = disable;
	if (timeout)
		rbc_intr_mask_val.timeout = disable;
	if (cbus_err)
		rbc_intr_mask_val.cbus_error = disable;
	if (utg_err)
		rbc_intr_mask_val.utg_error = disable;
	if (ttreg_err)
		rbc_intr_mask_val.ttreg = disable;

	if (utg_done) {
		if (disable)
			rbc_intr_mask_val.utg_done = RBCM_UTG_DONE_ALL_MASK;
		else
			rbc_intr_mask_val.utg_done = 0x00;
	}

	rbcm_reg_writel(entry->reg, rbc_intr_mask, rbc_intr_mask_val.value);

	RBCM_LOGI("[%s] Interrupt masking status:\r\n", entry->name);
	RBCM_LOGI("[%s] Port Error     : %c\r\n", entry->name,
			  rbc_intr_mask_val.port_err ? 'X' : 'O');
	RBCM_LOGI("[%s] Timeout        : %c\r\n", entry->name,
			  rbc_intr_mask_val.timeout ? 'X' : 'O');
	RBCM_LOGI("[%s] CBUS Error     : %c\r\n", entry->name,
			  rbc_intr_mask_val.cbus_error ? 'X' : 'O');
	RBCM_LOGI("[%s] UTG Error      : %c\r\n", entry->name,
			  rbc_intr_mask_val.utg_error ? 'X' : 'O');
	RBCM_LOGI("[%s] TTREG Error    : %c\r\n", entry->name,
			  rbc_intr_mask_val.ttreg ? 'X' : 'O');
	RBCM_LOGI("[%s] UTG Done (p0_w): %c\r\n", entry->name,
			  (rbc_intr_mask_val.utg_done >> 0) & 0x1 ? 'X' : 'O');
	RBCM_LOGI("[%s] UTG Done (p0_r): %c\r\n", entry->name,
			  (rbc_intr_mask_val.utg_done >> 1) & 0x1 ? 'X' : 'O');
	RBCM_LOGI("[%s] UTG Done (p1_w): %c\r\n", entry->name,
			  (rbc_intr_mask_val.utg_done >> 2) & 0x1 ? 'X' : 'O');
	RBCM_LOGI("[%s] UTG Done (p1_r): %c\r\n", entry->name,
			  (rbc_intr_mask_val.utg_done >> 3) & 0x1 ? 'X' : 'O');
	RBCM_LOGI("[%s] UTG Done (p2_w): %c\r\n", entry->name,
			  (rbc_intr_mask_val.utg_done >> 4) & 0x1 ? 'X' : 'O');
	RBCM_LOGI("[%s] UTG Done (p2_r): %c\r\n", entry->name,
			  (rbc_intr_mask_val.utg_done >> 5) & 0x1 ? 'X' : 'O');

	return RL_OK;
}

void rbcm_core_clear_ttreg(struct rbcm_data *entry)
{
	rbcm_reg_writel(entry->reg, rbc_glue_ctl_0, RBCM_CTL_CLEAR_VAL);
	rbcm_reg_writel(entry->reg, rbc_glue_ctl_1, RBCM_CTL_CLEAR_VAL);
#ifndef RBCM_DISABLE_CLEAR_PORT2
	rbcm_reg_writel(entry->reg, rbc_glue_ctl_2, RBCM_CTL_CLEAR_VAL);
#endif
}

int32_t rbcm_core_set_loopback_mode(struct rbcm_data *entry, enum rbc_lb_type lb_type,
									uint32_t lb_val)
{
	switch (lb_type) {
	case RBC_LB_PORT:
		rbcm_reg_field_write(entry->reg, lb_ctl, lb_port, lb_val);
		break;
	case RBC_LB_INNER:
		rbcm_reg_field_write(entry->reg, lb_ctl, ilb, lb_val);
		break;
	case RBC_LB_OUTER:
		rbcm_reg_field_write(entry->reg, lb_ctl, olb, lb_val);
		break;
	default:
		RBCM_LOGE("Invalid loopback type %d\r\n", lb_type);
		return RL_ERROR;
	}

	return RL_OK;
}

void rbcm_core_sw_reset(struct rbcm_data *entry)
{
	rbcm_reg_field_write(entry->reg, rbc_ctl, sw_reset, 1);
}

void rbcm_core_recover_from_reset(struct rbcm_data *entry)
{
	struct rbc_reg_rbc_config_t rbc_config;

	rbc_config.value = 0;
	rbc_config.rbc_en = 1;
	rbc_config.secded_en = 1;
	rbc_config.ttreg_en = 1;
	rbc_config.lb_usr_en = 1;
	rbc_config.trl = 1;
	rbc_config.bp = 1;

	rbcm_reg_writel(entry->reg, rbc_config, rbc_config.value);
}

int32_t rbcm_core_addr_remap(struct rbcm_data *entry, uint32_t msb_from,
							 uint32_t msb_to)
{
	uint64_t mask;
	uint32_t val;

	mask = (0xfULL << (msb_from * 4));
	entry->addr_remap_out_val &= (~mask);
	entry->addr_remap_out_val += ((uint64_t)msb_to << (msb_from * 4));

	val = (uint32_t)entry->addr_remap_out_val;
	rbcm_reg_writel(entry->reg, rbc_rtbl_out_0, val);
	val = (uint32_t)(entry->addr_remap_out_val >> 32);
	rbcm_reg_writel(entry->reg, rbc_rtbl_out_1, val);
	rbcm_reg_field_write(entry->reg, rbc_config, rtbl_en, 1);

	return RL_OK;
}

int32_t rbcm_core_set_timeout_interval(struct rbcm_data *entry, uint32_t timeout_ns)
{
	struct rbc_reg_timeout_window_config0_t timeout_config;
	volatile union aw_ucie_dvsec1_reg_reg_global_dvsec1_ucie_link_status *link_stat;
	/* Default RBCM clk: 500MHz (8GT/s / 16) */
	uint32_t link_freq_mhz = link_freq_mhz_tbl[TARGET_LINK_SPEED_8GT];
	uint64_t cycles_needed;
	uint64_t tick_plus1;
	uint64_t window_plus1;
	uint32_t tick;
	uint32_t window;
	uint64_t programmed_timeout_ns;

	if (!entry || !entry->reg)
		return RL_BADARG;

	/*
	 * Timeout Window Time = (window+1) * (tick+1) * Tclk
	 * Tclk is RBC_M operation clock period.
	 * NOTE: link_freq_mhz here is already derived from link speed as (link_clk / 16) in MHz.
	 */
	if (entry->ucie) {
		link_stat = &entry->ucie->dvsec1_reg_reg_global_dvsec1_ucie_link_status;

		if (link_stat->lstatus_link_speed_en <= TARGET_LINK_SPEED_32GT)
			link_freq_mhz = link_freq_mhz_tbl[link_stat->lstatus_link_speed_en];
	}

	/* Compute required cycles = ceil(timeout_ns / Tclk) with Tclk(ns) = 1000 / link_freq_mhz */
	if (timeout_ns == 0) {
		cycles_needed = 1;
	} else {
		cycles_needed = ((uint64_t)timeout_ns * link_freq_mhz + 1000 - 1) / 1000;
		if (cycles_needed == 0)
			cycles_needed = 1;
	}

	/*
	 * Prefer smaller tick (better resolution):
	 *  pick largest possible window first, then derive tick.
	 */
	window_plus1 = cycles_needed;
	if (window_plus1 == 0)
		window_plus1 = 1;
	if (window_plus1 > 0x10000ULL)
		window_plus1 = 0x10000ULL;

	tick_plus1 = (cycles_needed + window_plus1 - 1) / window_plus1;
	if (tick_plus1 == 0)
		tick_plus1 = 1;
	if (tick_plus1 > 0x10000ULL)
		tick_plus1 = 0x10000ULL;

	tick = (uint32_t)(tick_plus1 - 1);
	window = (uint32_t)(window_plus1 - 1);

	/* Log programmed timeout in ns (ceil to avoid rounding down in the log) */
	programmed_timeout_ns = (window_plus1 * tick_plus1 * 1000 + link_freq_mhz - 1) / link_freq_mhz;

	timeout_config.value = rbcm_reg_readl(entry->reg, Timeout_window_config0);
	timeout_config.tick = tick;
	timeout_config.window = window;

	rbcm_reg_writel(entry->reg, Timeout_window_config0, timeout_config.value);
	RBCM_LOGD("[%s] TimeoutWindow req=%u ns prog=%llu ns (tick=%u window=%u rbcm_clk=%uMHz)\r\n",
			  entry->name, timeout_ns,
			  (unsigned long long)programmed_timeout_ns,
			  tick, window, link_freq_mhz);

	return RL_OK;
}

int32_t rbcm_core_get_timeout_interval(struct rbcm_data *entry,
									   uint32_t *tick,
									   uint32_t *window,
									   uint64_t *timeout_ns,
									   uint32_t *rbcm_clk_mhz)
{
	struct rbc_reg_timeout_window_config0_t timeout_config;
	volatile union aw_ucie_dvsec1_reg_reg_global_dvsec1_ucie_link_status *link_stat;
	/* Default RBCM clk: 500MHz (8GT/s / 16) */
	uint32_t link_freq_mhz = link_freq_mhz_tbl[TARGET_LINK_SPEED_8GT];
	uint32_t local_tick;
	uint32_t local_window;

	if (!entry || !entry->reg || !tick || !window)
		return RL_BADARG;

	/* NOTE: link_freq_mhz here is already derived from link speed as (link_clk / 16) in MHz. */
	if (entry->ucie) {
		link_stat = &entry->ucie->dvsec1_reg_reg_global_dvsec1_ucie_link_status;

		if (link_stat->lstatus_link_speed_en <= TARGET_LINK_SPEED_32GT)
			link_freq_mhz = link_freq_mhz_tbl[link_stat->lstatus_link_speed_en];
	}

	timeout_config.value = rbcm_reg_readl(entry->reg, Timeout_window_config0);
	local_tick = timeout_config.tick;
	local_window = timeout_config.window;

	*tick = local_tick;
	*window = local_window;
	if (rbcm_clk_mhz)
		*rbcm_clk_mhz = link_freq_mhz;

	if (timeout_ns) {
		/*
		 * Timeout Window Time = (window+1) * (tick+1) * Tclk
		 * Tclk period(ns) = 1000 / link_freq_mhz
		 * Use ceil division to avoid rounding down.
		 */
		uint64_t cycles = ((uint64_t)local_window + 1) * ((uint64_t)local_tick + 1);
		uint64_t number = cycles * 1000ULL;

		*timeout_ns = (number + link_freq_mhz - 1) / link_freq_mhz;
	}

	return RL_OK;
}

static inline uint32_t get_timeout_status_reg(struct rbc_reg *reg, int ch_idx)
{
	uint32_t offset;

	offset = OFFSET_OF(struct rbc_reg, Timeout_status_0) + ch_idx * sizeof(uint32_t);
	return *((volatile uint32_t *)((void *)reg + offset));
}

static void rbcm_report_timeout_irq_status(struct rbcm_data *entry)
{
	int ch;
	int poll_timeout;
	struct rbc_reg_timeout_intr_status_t status;

	if (!entry)
		return;

	status.value = rbcm_reg_readl(entry->reg, Timeout_intr_status);
	RBCM_LOGE("[%s] Timeout Interrupt Status: 0x%08x\r\n", entry->name, status.value);

	for (ch = 0; ch < RBCM_CHANNEL_COUNT; ch++) {
		if (!((status.value >> ch) & 0x1))
			continue;

		int port = ch / 4;
		const char *path = ((ch / 2) % 2) ? "Inbound" : "Outbound";
		const char *access_type = (ch % 2) ? "Read" : "Write";
		struct timeout_status_reg_t timeout_status;

		RBCM_LOGE("[%s] Port%d Path %s %s (Ch%d)\r\n", entry->name, port, path, access_type, ch);

		do {
			poll_timeout = RBCM_DEFAULT_POLL_TIMEOUT;
			timeout_status.value = get_timeout_status_reg(entry->reg, ch);
			while (timeout_status.access_done == 0 && poll_timeout-- > 0) {
				timeout_status.value = get_timeout_status_reg(entry->reg, ch);
				mdelay(1);
			}
			if (poll_timeout == 0) {
				RBCM_LOGE("Timeout waiting for timeout access done\r\n");
				return;
			}

			RBCM_LOGE("AXID:0x%02x SrcID:0x%04x TO:%d Entry:%d SBE:%d DBE:%d Done:%d\r\n",
					  timeout_status.axid,
					  timeout_status.srcid,
					  timeout_status.to_flag,
					  timeout_status.to_entry_number,
					  timeout_status.detect_single_error,
					  timeout_status.detect_double_error,
					  timeout_status.access_done);
		} while (timeout_status.to_entry_number > 1);
	}
}

static void rbcm_report_port_err_intr_status(struct rbcm_data *entry)
{
	int i;
	char buf[256];
	int offset = 0;
	struct rbc_reg_port_err_intr_status_t status;

	status.value = rbcm_reg_readl(entry->reg, port_err_intr_status);

	for (i = 0; i < RBC_PORT_COUNT; i++) {
		if (!((status.value >> (i * 8)) & 0xFF))
			continue;

		offset += snprintf(buf + offset, sizeof(buf) - offset, " P%d:[", i);
		if (status.value & (RBCM_PORT_ERR_N2U_OUT_WR_REQ << (i * 8)))
			offset += snprintf(buf + offset, sizeof(buf) - offset, "OB_WR_REQ ");
		if (status.value & (RBCM_PORT_ERR_N2U_OUT_WR_RESP << (i * 8)))
			offset += snprintf(buf + offset, sizeof(buf) - offset, "OB_WR_RESP ");
		if (status.value & (RBCM_PORT_ERR_N2U_OUT_RD_REQ << (i * 8)))
			offset += snprintf(buf + offset, sizeof(buf) - offset, "OB_RD_REQ ");
		if (status.value & (RBCM_PORT_ERR_N2U_OUT_RD_RESP << (i * 8)))
			offset += snprintf(buf + offset, sizeof(buf) - offset, "OB_RD_RESP ");
		if (status.value & (RBCM_PORT_ERR_U2N_IN_WR_REQ << (i * 8)))
			offset += snprintf(buf + offset, sizeof(buf) - offset, "IB_WR_REQ ");
		if (status.value & (RBCM_PORT_ERR_U2N_IN_WR_RESP << (i * 8)))
			offset += snprintf(buf + offset, sizeof(buf) - offset, "IB_WR_RESP ");
		if (status.value & (RBCM_PORT_ERR_U2N_IN_RD_REQ << (i * 8)))
			offset += snprintf(buf + offset, sizeof(buf) - offset, "IB_RD_REQ ");
		if (status.value & (RBCM_PORT_ERR_U2N_IN_RD_RESP << (i * 8)))
			offset += snprintf(buf + offset, sizeof(buf) - offset, "IB_RD_RESP ");

		/* Remove trailing space */
		if (offset > 0 && buf[offset - 1] == ' ')
			offset--;
		offset += snprintf(buf + offset, sizeof(buf) - offset, "]");
	}

	RBCM_LOGE("[%s] Port Error (0x%08x):%s\r\n", entry->name, status.value, buf);
}

static void rbcm_report_ttreg_intr_err_status(struct rbcm_data *entry)
{
	int i;
	char buf[256];
	int offset = 0;
	struct rbc_reg_ttreg_err_intr_status_t status;

	buf[0] = '\0';
	status.value = rbcm_reg_readl(entry->reg, ttreg_err_intr_status);
	for (i = 0; i < RBC_PORT_COUNT; i++) {
		if (!((status.value >> (i * 4)) & 0xF))
			continue;

		offset += snprintf(buf + offset, sizeof(buf) - offset, " P%d:[", i);
		if (status.value & (RBCM_TTREG_ERR_OB_WR << (i * 4)))
			offset += snprintf(buf + offset, sizeof(buf) - offset, "OB_WR ");
		if (status.value & (RBCM_TTREG_ERR_OB_RD << (i * 4)))
			offset += snprintf(buf + offset, sizeof(buf) - offset, "OB_RD ");
		if (status.value & (RBCM_TTREG_ERR_IB_WR << (i * 4)))
			offset += snprintf(buf + offset, sizeof(buf) - offset, "IB_WR ");
		if (status.value & (RBCM_TTREG_ERR_IB_RD << (i * 4)))
			offset += snprintf(buf + offset, sizeof(buf) - offset, "IB_RD ");

		/* Remove trailing space */
		if (offset > 0 && buf[offset - 1] == ' ')
			offset--;
		offset += snprintf(buf + offset, sizeof(buf) - offset, "]");
	}

	RBCM_LOGE("[%s] TTREG Error (0x%08x):%s\r\n", entry->name, status.value, buf);
}

static void rbcm_report_utg_done_status(struct rbcm_data *entry, uint32_t utg_done)
{
	char buf[256];
	int offset = 0;

	buf[0] = '\0';
	if (utg_done & RBCM_UTG_DONE_P0_W)
		offset += snprintf(buf + offset, sizeof(buf) - offset, " P0_WR");
	if (utg_done & RBCM_UTG_DONE_P0_R)
		offset += snprintf(buf + offset, sizeof(buf) - offset, " P0_RD");
	if (utg_done & RBCM_UTG_DONE_P1_W)
		offset += snprintf(buf + offset, sizeof(buf) - offset, " P1_WR");
	if (utg_done & RBCM_UTG_DONE_P1_R)
		offset += snprintf(buf + offset, sizeof(buf) - offset, " P1_RD");
	if (utg_done & RBCM_UTG_DONE_P2_W)
		offset += snprintf(buf + offset, sizeof(buf) - offset, " P2_WR");
	if (utg_done & RBCM_UTG_DONE_P2_R)
		offset += snprintf(buf + offset, sizeof(buf) - offset, " P2_RD");

	RBCM_LOGD("[%s] UTG Done (0x%x):%s\r\n", entry->name, utg_done, buf);
}

static inline void rbcm_report_cbus_err(struct rbcm_data *entry)
{
	RBCM_LOGE("[%s] CBus Error Interrupt reported\r\n", entry->name);
}

static inline void rbcm_report_utg_err(struct rbcm_data *entry)
{
	RBCM_LOGE("[%s] UTG Error Interrupt reported\r\n", entry->name);
}

void rbcm_irq_handler(void *arg)
{
	struct rbcm_data *entry = (struct rbcm_data *)arg;
	struct rbc_reg_rbc_intr_status_t intr_status;

	if (!entry || !entry->reg)
		return;

	intr_status.value = rbcm_reg_readl(entry->reg, rbc_intr_status);
	RBCM_LOGD("[%s] RBC_M Interrupt Handler (Chiplet %d)\r\n", entry->name, entry->chiplet_id);
	/* clear interrupt */
	rbcm_reg_writel(entry->reg, rbc_intr_clr, intr_status.value);

	if (intr_status.port_err)
		rbcm_report_port_err_intr_status(entry);

	if (intr_status.timeout) {
		rbcm_report_timeout_irq_status(entry);
		if (rbcm_core_check_all_chiplet_link_up(entry->chiplet_id))
			rbcm_core_dump_all_chiplet_incomplete_ttreg();
		else
			rbcm_core_dump_chiplet_incomplete_ttreg(entry->chiplet_id);
		rbcm_core_dump_ucie_link_health(entry);
		rbcm_core_dump_ucie_crc(entry);
	}

	if (intr_status.cbus_error)
		rbcm_report_cbus_err(entry);

	if (intr_status.utg_error)
		rbcm_report_utg_err(entry);

	if (intr_status.ttreg)
		rbcm_report_ttreg_intr_err_status(entry);

	if (intr_status.utg_done)
		rbcm_report_utg_done_status(entry, intr_status.utg_done);
}
