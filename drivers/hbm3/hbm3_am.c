#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include "hbm3.h"
#include "ddr_csr.h"
#include "hbm3_am.h"

#define AM_INTERVAL 0xFFFF /* TODO: Check interval */

struct hbm3_am_config {
	uint32_t ch;
	struct ddr_csr *csr;
	bool is_repeat_interval;
};

struct hbm3_am_config hbm3_am_cfg[] = {
	{0, (struct ddr_csr *)(HBM3_CON_0_BASE), true},
	{1, (struct ddr_csr *)(HBM3_CON_1_BASE), true},
	{2, (struct ddr_csr *)(HBM3_CON_2_BASE), true},
	{3, (struct ddr_csr *)(HBM3_CON_3_BASE), true},
	{4, (struct ddr_csr *)(HBM3_CON_4_BASE), true},
	{5, (struct ddr_csr *)(HBM3_CON_5_BASE), true},
	{6, (struct ddr_csr *)(HBM3_CON_6_BASE), true},
	{7, (struct ddr_csr *)(HBM3_CON_7_BASE), true},
	{8, (struct ddr_csr *)(HBM3_CON_8_BASE), true},
	{9, (struct ddr_csr *)(HBM3_CON_9_BASE), true},
	{10, (struct ddr_csr *)(HBM3_CON_10_BASE), true},
	{11, (struct ddr_csr *)(HBM3_CON_11_BASE), true},
	{12, (struct ddr_csr *)(HBM3_CON_12_BASE), true},
	{13, (struct ddr_csr *)(HBM3_CON_13_BASE), true},
	{14, (struct ddr_csr *)(HBM3_CON_14_BASE), true},
	{15, (struct ddr_csr *)(HBM3_CON_15_BASE), true},
};

static void hbm3_activity_monitor_init(struct hbm3_am_config *cfg)
{
	volatile struct ddr_csr *hbm3_mc = (struct ddr_csr *)cfg->csr;

	hbm3_mc->mc_base3_init_am_interval.init_am_interval = AM_INTERVAL;

	if (cfg->is_repeat_interval) {
		hbm3_mc->mc_base3_init_am_single_en.init_am_single_en = 0x0;
		hbm3_mc->mc_base3_init_am_repeat_en.init_am_repeat_en = 0x1;
		printf("HBM3 channel %d: Activity monitor init with Repeat mode\n", cfg->ch);
	} else {
		hbm3_mc->mc_base3_init_am_repeat_en.init_am_repeat_en = 0x0;
		hbm3_mc->mc_base3_init_am_single_en.init_am_single_en = 0x1;
		printf("HBM3 channel %d: Activity monitor init with Single mode\n", cfg->ch);
	}
}

static void hbm3_activity_monitor_wait_complete(struct hbm3_am_config *cfg)
{
	volatile struct ddr_csr *hbm3_mc = (struct ddr_csr *)cfg->csr;
	volatile uint32_t complete;

	do {
		udelay(1); // FIXME: busy waiting?
		complete = hbm3_mc->mc_base3_stat_am_complete.stat_am_complete;
	} while (!complete);
}

static void hbm3_activity_monitor_result_axi_activity(struct hbm3_am_config *cfg)
{
	volatile struct ddr_csr *hbm3_mc = (struct ddr_csr *)cfg->csr;

	printf("HBM3 channel %d: AXI interface activity\n", cfg->ch);
	PRINT_INFO_VAL(hbm3_mc->act_mon_am_interval_count_axi1.am_interval_count_axi1);
	PRINT_INFO_VAL(hbm3_mc->act_mon_am_wac_active_axi1.am_wac_active_axi1);
	PRINT_INFO_VAL(hbm3_mc->act_mon_am_wac_stall_axi1.am_wac_stall_axi1);
	PRINT_INFO_VAL(hbm3_mc->act_mon_am_rac_active_axi1.am_rac_active_axi1);
	PRINT_INFO_VAL(hbm3_mc->act_mon_am_rac_stall_axi1.am_rac_stall_axi1);
	PRINT_INFO_VAL(hbm3_mc->act_mon_am_wdc_active_axi1.am_wdc_active_axi1);
	PRINT_INFO_VAL(hbm3_mc->act_mon_am_wdc_stall_axi1.am_wdc_stall_axi1);
	PRINT_INFO_VAL(hbm3_mc->act_mon_am_rdc_active_axi1.am_rdc_active_axi1);
	PRINT_INFO_VAL(hbm3_mc->act_mon_am_rdc_stall_axi1.am_rdc_stall_axi1);
}

static void hbm3_activity_monitor_result_command_data_fifo_level(struct hbm3_am_config *cfg)
{
	volatile struct ddr_csr *hbm3_mc = (struct ddr_csr *)cfg->csr;

	printf("HBM3 channel %d: Command/Data FIFO level\n", cfg->ch);
	PRINT_INFO_VAL(hbm3_mc->act_mon_am_wcf_sum_axi1_0.am_wcf_sum_axi1_31_0);
	PRINT_INFO_VAL(hbm3_mc->act_mon_am_wcf_sum_axi1_1.am_wcf_sum_axi1_37_32);
	PRINT_INFO_VAL(hbm3_mc->act_mon_am_wcf_max_axi1_0.am_wcf_max_axi1);
	PRINT_INFO_VAL(hbm3_mc->act_mon_am_wcf_min_axi1_0.am_wcf_min_axi1);
	PRINT_INFO_VAL(hbm3_mc->act_mon_am_rcf_sum_axi1_0.am_rcf_sum_axi1_31_0);
	PRINT_INFO_VAL(hbm3_mc->act_mon_am_rcf_sum_axi1_1.am_rcf_sum_axi1_37_32);
	PRINT_INFO_VAL(hbm3_mc->act_mon_am_rcf_max_axi1_0.am_rcf_max_axi1);
	PRINT_INFO_VAL(hbm3_mc->act_mon_am_rcf_min_axi1_0.am_rcf_min_axi1);
	PRINT_INFO_VAL(hbm3_mc->act_mon_am_wdf_sum_axi1_0.am_wdf_sum_axi1_31_0);
	PRINT_INFO_VAL(hbm3_mc->act_mon_am_wdf_sum_axi1_1.am_wdf_sum_axi1_40_32);
	PRINT_INFO_VAL(hbm3_mc->act_mon_am_wdf_max_axi1_0.am_wdf_max_axi1);
	PRINT_INFO_VAL(hbm3_mc->act_mon_am_wdf_min_axi1_0.am_wdf_min_axi1);
	PRINT_INFO_VAL(hbm3_mc->act_mon_am_rdf_sum_axi1_0.am_rdf_sum_axi1_31_0);
	PRINT_INFO_VAL(hbm3_mc->act_mon_am_rdf_sum_axi1_1.am_rdf_sum_axi1_40_32);
	PRINT_INFO_VAL(hbm3_mc->act_mon_am_rdf_max_axi1_0.am_rdf_max_axi1);
	PRINT_INFO_VAL(hbm3_mc->act_mon_am_rdf_min_axi1_0.am_rdf_min_axi1);
}

static void hbm3_activity_monitor_reordering_queue_level(struct hbm3_am_config *cfg)
{
	volatile struct ddr_csr *hbm3_mc = (struct ddr_csr *)cfg->csr;

	printf("HBM3 channel %d: Re-ordering queue level\n", cfg->ch);
	PRINT_INFO_VAL(hbm3_mc->act_mon_am_ctrlr_queue_sum_0.am_ctrlr_queue_sum_31_0);
	PRINT_INFO_VAL(hbm3_mc->act_mon_am_ctrlr_queue_sum_1.am_ctrlr_queue_sum_38_32);
	PRINT_INFO_VAL(hbm3_mc->act_mon_am_ctrlr_queue_max_0.am_ctrlr_queue_max);
	PRINT_INFO_VAL(hbm3_mc->act_mon_am_ctrlr_queue_min_0.am_ctrlr_queue_min);
	PRINT_INFO_VAL(hbm3_mc->act_mon_am_rd_to_wr_switch.am_rd_to_wr_switch);
	PRINT_INFO_VAL(hbm3_mc->act_mon_am_ro_age_limit.am_ro_age_limit);
}

static void hbm3_activity_monitor_dram_command(struct hbm3_am_config *cfg)
{
	volatile struct ddr_csr *hbm3_mc = (struct ddr_csr *)cfg->csr;

	printf("HBM3 channel %d: DRAM command\n", cfg->ch);
	PRINT_INFO_VAL(hbm3_mc->act_mon_am_wr_cmd.am_wr_cmd);
	PRINT_INFO_VAL(hbm3_mc->act_mon_am_wr_ap_cmd.am_wr_ap_cmd);
	PRINT_INFO_VAL(hbm3_mc->act_mon_am_rd_cmd.am_rd_cmd);
	PRINT_INFO_VAL(hbm3_mc->act_mon_am_rd_ap_cmd.am_rd_ap_cmd);
	PRINT_INFO_VAL(hbm3_mc->act_mon_am_refresh_cmd.am_refresh_cmd);
	PRINT_INFO_VAL(hbm3_mc->act_mon_am_act_cmd.am_act_cmd);
	PRINT_INFO_VAL(hbm3_mc->act_mon_am_precharge_cmd.am_precharge_cmd);
	PRINT_INFO_VAL(hbm3_mc->act_mon_am_precharge_all_cmd.am_precharge_all_cmd);
	PRINT_INFO_VAL(hbm3_mc->act_mon_am_power_down.am_power_down);
	PRINT_INFO_VAL(hbm3_mc->act_mon_am_rmw_cycle.am_rmw_cycle);
	PRINT_INFO_VAL(hbm3_mc->act_mon_am_self_refresh.am_self_refresh);
	PRINT_INFO_VAL(hbm3_mc->act_mon_am_rfm_cmd.am_rfm_cmd);
}

static void hbm3_activity_monitor_power_down(struct hbm3_am_config *cfg)
{
	volatile struct ddr_csr *hbm3_mc = (struct ddr_csr *)cfg->csr;

	printf("HBM3 channel %d: Power down\n", cfg->ch);
	PRINT_INFO_VAL(hbm3_mc->act_mon_am_power_down_transition_count.am_power_down_transition_count);
	PRINT_INFO_VAL(hbm3_mc->act_mon_am_lp_data_1.am_lp_data_1);
	PRINT_INFO_VAL(hbm3_mc->act_mon_am_lp_data_transition_count_1.am_lp_data_transition_count_1);
	PRINT_INFO_VAL(hbm3_mc->act_mon_am_lp_data_2.am_lp_data_2);
	PRINT_INFO_VAL(hbm3_mc->act_mon_am_lp_data_transition_count_2.am_lp_data_transition_count_2);
	PRINT_INFO_VAL(hbm3_mc->act_mon_am_lp_data_3.am_lp_data_3);
	PRINT_INFO_VAL(hbm3_mc->act_mon_am_lp_data_transition_count_3.am_lp_data_transition_count_3);
}

void hbm3_activity_monitor_result_print(struct hbm3_am_config *cfg)
{
	hbm3_activity_monitor_result_axi_activity(cfg);
	hbm3_activity_monitor_result_command_data_fifo_level(cfg);
	hbm3_activity_monitor_reordering_queue_level(cfg);
	hbm3_activity_monitor_dram_command(cfg);
	hbm3_activity_monitor_power_down(cfg);
}

void hbm3_activity_monitor_enable(void)
{
	uint32_t ch;

	for (ch = 0; ch < HBM3_NUM_CH; ch++)
		hbm3_activity_monitor_init(&hbm3_am_cfg[ch]);
}

void hbm3_activity_monitor_report(void)
{
	uint32_t ch;

	for (ch = 0; ch < HBM3_NUM_CH; ch++)
		hbm3_activity_monitor_wait_complete(&hbm3_am_cfg[ch]);

	for (ch = 0; ch < HBM3_NUM_CH; ch++)
		hbm3_activity_monitor_result_print(&hbm3_am_cfg[ch]);
}
