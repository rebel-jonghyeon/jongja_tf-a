/*
 * Copyright 2025 Samsung Electronics Co., Ltd. All Rights Reserved.
 *
 * PROPRIETARY/CONFIDENTIAL
 *
 * This software is the confidential and proprietary information of Samsung
 * Electronics Co., Ltd. ("Confidential Information"). You shall not disclose such
 * Confidential Information and shall use it only in accordance with the terms of
 * the license agreement you entered into with Samsung Electronics Co., Ltd. (“SAMSUNG”).
 *
 * SAMSUNG MAKES NO REPRESENTATIONS OR WARRANTIES ABOUT THE SUITABILITY OF THE SOFTWARE,
 * EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, OR NON-INFRINGEMENT.
 *
 * SAMSUNG SHALL NOT BE LIABLE FOR ANY DAMAGES SUFFERED BY LICENSEE AS A RESULT OF USING,
 * MODIFYING OR DISTRIBUTING THIS SOFTWARE OR ITS DERIVATIVES.
 */

#pragma once

union pmu_om_stat {
	struct {
		uint32_t om:3; /* [2:0] */
		uint32_t rsvd0:28; /* [30:3] */
		uint32_t valid_life_cycle_override:1; /* [31:31] */
	};
	uint32_t val;
};

union pmu_xxit_pad_con {
	struct {
		uint32_t sf0:1; /* [0:0] */
		uint32_t sf1:1; /* [1:1] */
		uint32_t sf2:1; /* [2:2] */
		uint32_t sf3:1; /* [3:3] */
		uint32_t rsvd0:28; /* [31:4] */
	};
	uint32_t val;
};

union pmu_lpi_dram_ctrl0 {
	struct {
		uint32_t rsvd0:16; /* [15:0] */
		uint32_t ignore_denial_smc_0:1; /* [16:16] */
		uint32_t ignore_denial_smc_1:1; /* [17:17] */
		uint32_t ignore_denial_smc_2:1; /* [18:18] */
		uint32_t ignore_denial_smc_3:1; /* [19:19] */
		uint32_t ignore_denial_smc_4:1; /* [20:20] */
		uint32_t ignore_denial_smc_5:1; /* [21:21] */
		uint32_t ignore_denial_smc_6:1; /* [22:22] */
		uint32_t ignore_denial_smc_7:1; /* [23:23] */
		uint32_t ignore_denial_smc_8:1; /* [24:24] */
		uint32_t ignore_denial_smc_9:1; /* [25:25] */
		uint32_t ignore_denial_smc_10:1; /* [26:26] */
		uint32_t ignore_denial_smc_11:1; /* [27:27] */
		uint32_t ignore_denial_smc_12:1; /* [28:28] */
		uint32_t ignore_denial_smc_13:1; /* [29:29] */
		uint32_t ignore_denial_smc_14:1; /* [30:30] */
		uint32_t ignore_denial_smc_15:1; /* [31:31] */
	};
	uint32_t val;
};

union pmu_lpi_dram_ctrl1 {
	struct {
		uint32_t mif0_busy:1; /* [0:0] */
		uint32_t mif1_busy:1; /* [1:1] */
		uint32_t mif2_busy:1; /* [2:2] */
		uint32_t mif3_busy:1; /* [3:3] */
		uint32_t mif4_busy:1; /* [4:4] */
		uint32_t mif5_busy:1; /* [5:5] */
		uint32_t mif6_busy:1; /* [6:6] */
		uint32_t mif7_busy:1; /* [7:7] */
		uint32_t mif8_busy:1; /* [8:8] */
		uint32_t mif9_busy:1; /* [9:9] */
		uint32_t mif10_busy:1; /* [10:10] */
		uint32_t mif11_busy:1; /* [11:11] */
		uint32_t mif12_busy:1; /* [12:12] */
		uint32_t mif13_busy:1; /* [13:13] */
		uint32_t mif14_busy:1; /* [14:14] */
		uint32_t mif15_busy:1; /* [15:15] */
		uint32_t ignore_lpi_smc_0:1; /* [16:16] */
		uint32_t ignore_lpi_smc_1:1; /* [17:17] */
		uint32_t ignore_lpi_smc_2:1; /* [18:18] */
		uint32_t ignore_lpi_smc_3:1; /* [19:19] */
		uint32_t ignore_lpi_smc_4:1; /* [20:20] */
		uint32_t ignore_lpi_smc_5:1; /* [21:21] */
		uint32_t ignore_lpi_smc_6:1; /* [22:22] */
		uint32_t ignore_lpi_smc_7:1; /* [23:23] */
		uint32_t ignore_lpi_smc_8:1; /* [24:24] */
		uint32_t ignore_lpi_smc_9:1; /* [25:25] */
		uint32_t ignore_lpi_smc_10:1; /* [26:26] */
		uint32_t ignore_lpi_smc_11:1; /* [27:27] */
		uint32_t ignore_lpi_smc_12:1; /* [28:28] */
		uint32_t ignore_lpi_smc_13:1; /* [29:29] */
		uint32_t ignore_lpi_smc_14:1; /* [30:30] */
		uint32_t ignore_lpi_smc_15:1; /* [31:31] */
	};
	uint32_t val;
};

union pmu_hbm_reset_mask {
	struct {
		uint32_t phy_dram:1; /* [0:0] */
		uint32_t csr_dram:1; /* [1:1] */
		uint32_t hbmc_dram:1; /* [2:2] */
		uint32_t rsvd0:29; /* [31:3] */
	};
	uint32_t val;
};

union pmu_up_scheduler {
	struct {
		uint32_t enable_cluster0_cpu:1; /* [0:0] */
		uint32_t rsvd1:3; /* [3:1] */
		uint32_t enable_cluster1_cpu:1; /* [4:4] */
		uint32_t rsvd0:27; /* [31:5] */
	};
	uint32_t val;
};

union pmu_swreset {
	struct {
		uint32_t system:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_rst_stat {
	struct {
		uint32_t cluster0_dbgrstreq0:1; /* [0:0] */
		uint32_t cluster0_dbgrstreq1:1; /* [1:1] */
		uint32_t cluster0_dbgrstreq2:1; /* [2:2] */
		uint32_t cluster0_dbgrstreq3:1; /* [3:3] */
		uint32_t cluster1_dbgrstreq0:1; /* [4:4] */
		uint32_t cluster1_dbgrstreq1:1; /* [5:5] */
		uint32_t cluster1_dbgrstreq2:1; /* [6:6] */
		uint32_t cluster1_dbgrstreq3:1; /* [7:7] */
		uint32_t cluster0_warmrstreq0:1; /* [8:8] */
		uint32_t cluster0_warmrstreq1:1; /* [9:9] */
		uint32_t cluster0_warmrstreq2:1; /* [10:10] */
		uint32_t cluster0_warmrstreq3:1; /* [11:11] */
		uint32_t cluster1_warmrstreq0:1; /* [12:12] */
		uint32_t cluster1_warmrstreq1:1; /* [13:13] */
		uint32_t cluster1_warmrstreq2:1; /* [14:14] */
		uint32_t cluster1_warmrstreq3:1; /* [15:15] */
		uint32_t pinreset:1; /* [16:16] */
		uint32_t rsvd3:3; /* [19:17] */
		uint32_t pcie_perst:1; /* [20:20] */
		uint32_t hotreset_global:1; /* [21:21] */
		uint32_t rsvd2:1; /* [22:22] */
		uint32_t cluster0_wdtreset_l1:1; /* [23:23] */
		uint32_t cluster1_wdtreset_l1:1; /* [24:24] */
		uint32_t cluster0_wdtreset_l2:1; /* [25:25] */
		uint32_t cluster1_wdtreset_l2:1; /* [26:26] */
		uint32_t rsvd1:1; /* [27:27] */
		uint32_t wreset:1; /* [28:28] */
		uint32_t swreset:1; /* [29:29] */
		uint32_t rsvd0:2; /* [31:30] */
	};
	uint32_t val;
};

union pmu_automatic_disable_wdt {
	struct {
		uint32_t cluster0_wdt:1; /* [0:0] */
		uint32_t cluster1_wdt:1; /* [1:1] */
		uint32_t cm7_wdt:1; /* [2:2] */
		uint32_t rsvd1:1; /* [3:3] */
		uint32_t cluster0_wdt_en:1; /* [4:4] */
		uint32_t cluster1_wdt_en:1; /* [5:5] */
		uint32_t cm7_wdt_en:1; /* [6:6] */
		uint32_t rsvd0:25; /* [31:7] */
	};
	uint32_t val;
};

union pmu_mask_wdt_reset_request {
	struct {
		uint32_t cluster0_wdtreset_l1:1; /* [0:0] */
		uint32_t cluster1_wdtreset_l1:1; /* [1:1] */
		uint32_t rsvd2:2; /* [3:2] */
		uint32_t cluster0_wdtreset_l2:1; /* [4:4] */
		uint32_t cluster1_wdtreset_l2:1; /* [5:5] */
		uint32_t rsvd1:2; /* [7:6] */
		uint32_t pcie_perst:1; /* [8:8] */
		uint32_t hotreset_global:1; /* [9:9] */
		uint32_t rsvd0:22; /* [31:10] */
	};
	uint32_t val;
};

union pmu_mask_wreset_request {
	struct {
		uint32_t cluster0_dbgrstreq0:1; /* [0:0] */
		uint32_t cluster0_dbgrstreq1:1; /* [1:1] */
		uint32_t cluster0_dbgrstreq2:1; /* [2:2] */
		uint32_t cluster0_dbgrstreq3:1; /* [3:3] */
		uint32_t cluster1_dbgrstreq0:1; /* [4:4] */
		uint32_t cluster1_dbgrstreq1:1; /* [5:5] */
		uint32_t cluster1_dbgrstreq2:1; /* [6:6] */
		uint32_t cluster1_dbgrstreq3:1; /* [7:7] */
		uint32_t cluster0_warmrstreq0:1; /* [8:8] */
		uint32_t cluster0_warmrstreq1:1; /* [9:9] */
		uint32_t cluster0_warmrstreq2:1; /* [10:10] */
		uint32_t cluster0_warmrstreq3:1; /* [11:11] */
		uint32_t cluster1_warmrstreq0:1; /* [12:12] */
		uint32_t cluster1_warmrstreq1:1; /* [13:13] */
		uint32_t cluster1_warmrstreq2:1; /* [14:14] */
		uint32_t cluster1_warmrstreq3:1; /* [15:15] */
		uint32_t rsvd0:16; /* [31:16] */
	};
	uint32_t val;
};

union pmu_cpu_reset_disable_from_level1reset {
	struct {
		uint32_t pend_cluster0:1; /* [0:0] */
		uint32_t pend_cluster1:1; /* [1:1] */
		uint32_t pend_cm7:1; /* [2:2] */
		uint32_t pend_cmrt:1; /* [3:3] */
		uint32_t rsvd0:28; /* [31:4] */
	};
	uint32_t val;
};

union pmu_cpu_reset_disable_from_level2reset {
	struct {
		uint32_t pend_cluster0:1; /* [0:0] */
		uint32_t pend_cluster1:1; /* [1:1] */
		uint32_t pend_cm7:1; /* [2:2] */
		uint32_t pend_cmrt:1; /* [3:3] */
		uint32_t rsvd0:28; /* [31:4] */
	};
	uint32_t val;
};

union pmu_cpu_reset_disable_from_level3reset {
	struct {
		uint32_t pend_cluster0:1; /* [0:0] */
		uint32_t pend_cluster1:1; /* [1:1] */
		uint32_t pend_cm7:1; /* [2:2] */
		uint32_t pend_cmrt:1; /* [3:3] */
		uint32_t rsvd0:28; /* [31:4] */
	};
	uint32_t val;
};

union pmu_wdtreset_lpi {
	struct {
		uint32_t enable_lpi:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_reset_lpi_timeout {
	struct {
		uint32_t timeout_enable:1; /* [0:0] */
		uint32_t rsvd1:3; /* [3:1] */
		uint32_t status:1; /* [4:4] */
		uint32_t rsvd0:11; /* [15:5] */
		uint32_t timeout_duration:16; /* [31:16] */
	};
	uint32_t val;
};

union pmu_reset_sequencer_configuration {
	struct {
		uint32_t edpcsr_dump_en:1; /* [0:0] */
		uint32_t rsvd1:3; /* [3:1] */
		uint32_t clear_dbgl1rstdisable_cluster0:1; /* [4:4] */
		uint32_t clear_l2rstdisable_cluster0:1; /* [5:5] */
		uint32_t enable_dbgl1rstdisable_cluster0:1; /* [6:6] */
		uint32_t enable_l2rstdisable_cluster0:1; /* [7:7] */
		uint32_t clear_dbgl1rstdisable_cluster1:1; /* [8:8] */
		uint32_t clear_l2rstdisable_cluster1:1; /* [9:9] */
		uint32_t enable_dbgl1rstdisable_cluster1:1; /* [10:10] */
		uint32_t enable_l2rstdisable_cluster1:1; /* [11:11] */
		uint32_t rsvd0:20; /* [31:12] */
	};
	uint32_t val;
};

union pmu_reset_sequencer_duration0 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_reset_sequencer_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_reset_sequencer_duration2 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_reset_sequencer_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_inform0 {
	struct {
		uint32_t inform; /* [31:0] */
	};
	uint32_t val;
};

union pmu_inform1 {
	struct {
		uint32_t inform; /* [31:0] */
	};
	uint32_t val;
};

union pmu_inform2 {
	struct {
		uint32_t inform; /* [31:0] */
	};
	uint32_t val;
};

union pmu_inform3 {
	struct {
		uint32_t inform; /* [31:0] */
	};
	uint32_t val;
};

union pmu_sysip_dat0 {
	struct {
		uint32_t data; /* [31:0] */
	};
	uint32_t val;
};

union pmu_sysip_dat1 {
	struct {
		uint32_t data; /* [31:0] */
	};
	uint32_t val;
};

union pmu_sysip_dat2 {
	struct {
		uint32_t data; /* [31:0] */
	};
	uint32_t val;
};

union pmu_sysip_dat3 {
	struct {
		uint32_t data; /* [31:0] */
	};
	uint32_t val;
};

union pmu_inform4 {
	struct {
		uint32_t inform; /* [31:0] */
	};
	uint32_t val;
};

union pmu_inform5 {
	struct {
		uint32_t inform; /* [31:0] */
	};
	uint32_t val;
};

union pmu_inform6 {
	struct {
		uint32_t inform; /* [31:0] */
	};
	uint32_t val;
};

union pmu_inform7 {
	struct {
		uint32_t inform; /* [31:0] */
	};
	uint32_t val;
};

union pmu_inform8 {
	struct {
		uint32_t inform; /* [31:0] */
	};
	uint32_t val;
};

union pmu_inform9 {
	struct {
		uint32_t inform; /* [31:0] */
	};
	uint32_t val;
};

union pmu_inform10 {
	struct {
		uint32_t inform; /* [31:0] */
	};
	uint32_t val;
};

union pmu_inform11 {
	struct {
		uint32_t inform; /* [31:0] */
	};
	uint32_t val;
};

union pmu_pmu_spare0 {
	struct {
		uint32_t spare; /* [31:0] */
	};
	uint32_t val;
};

union pmu_pmu_spare1 {
	struct {
		uint32_t spare; /* [31:0] */
	};
	uint32_t val;
};

union pmu_pmu_spare2 {
	struct {
		uint32_t spare; /* [31:0] */
	};
	uint32_t val;
};

union pmu_pmu_spare3 {
	struct {
		uint32_t spare; /* [31:0] */
	};
	uint32_t val;
};

union pmu_ack_last_cpu {
	struct {
		uint32_t active_cluster0_cpu0:1; /* [0:0] */
		uint32_t active_cluster0_cpu1:1; /* [1:1] */
		uint32_t active_cluster0_cpu2:1; /* [2:2] */
		uint32_t active_cluster0_cpu3:1; /* [3:3] */
		uint32_t active_cluster1_cpu0:1; /* [4:4] */
		uint32_t active_cluster1_cpu1:1; /* [5:5] */
		uint32_t active_cluster1_cpu2:1; /* [6:6] */
		uint32_t active_cluster1_cpu3:1; /* [7:7] */
		uint32_t active_cluster0_noncpu:1; /* [8:8] */
		uint32_t active_cluster1_noncpu:1; /* [9:9] */
		uint32_t rsvd0:22; /* [31:10] */
	};
	uint32_t val;
};

union pmu_irom_data_reg0 {
	struct {
		uint32_t irom_data; /* [31:0] */
	};
	uint32_t val;
};

union pmu_irom_data_reg1 {
	struct {
		uint32_t irom_data; /* [31:0] */
	};
	uint32_t val;
};

union pmu_irom_data_reg2 {
	struct {
		uint32_t irom_data; /* [31:0] */
	};
	uint32_t val;
};

union pmu_irom_data_reg3 {
	struct {
		uint32_t irom_data; /* [31:0] */
	};
	uint32_t val;
};

union pmu_pmu_debug {
	struct {
		uint32_t clkout0_enable:1; /* [0:0] */
		uint32_t rsvd3:5; /* [5:1] */
		uint32_t clkout0_invert:1; /* [6:6] */
		uint32_t rsvd2:1; /* [7:7] */
		uint32_t clkout0_sel:6; /* [13:8] */
		uint32_t rsvd1:1; /* [14:14] */
		uint32_t dbg_sel:5; /* [19:15] */
		uint32_t select_serial_debug_output_port:5; /* [24:20] */
		uint32_t rsvd0:1; /* [25:25] */
		uint32_t select_power_down_state_output_port:5; /* [30:26] */
		uint32_t enable_serial_debug:1; /* [31:31] */
	};
	uint32_t val;
};

union pmu_arm_control_option {
	struct {
		uint32_t dbgack_mask_cluster0_cpu0:1; /* [0:0] */
		uint32_t dbgack_mask_cluster0_cpu1:1; /* [1:1] */
		uint32_t dbgack_mask_cluster0_cpu2:1; /* [2:2] */
		uint32_t dbgack_mask_cluster0_cpu3:1; /* [3:3] */
		uint32_t dbgack_mask_cluster1_cpu0:1; /* [4:4] */
		uint32_t dbgack_mask_cluster1_cpu1:1; /* [5:5] */
		uint32_t dbgack_mask_cluster1_cpu2:1; /* [6:6] */
		uint32_t dbgack_mask_cluster1_cpu3:1; /* [7:7] */
		uint32_t rsvd0:24; /* [31:8] */
	};
	uint32_t val;
};

union pmu_burnin_ctrl {
	struct {
		uint32_t enable_seq_pwron_feedback:1; /* [0:0] */
		uint32_t enable_seq_pwron_counter:1; /* [1:1] */
		uint32_t enable_oscclk_run:1; /* [2:2] */
		uint32_t enable_cpu_corereset_extension:1; /* [3:3] */
		uint32_t rsvd0:4; /* [7:4] */
		uint32_t dur_sc:8; /* [15:8] */
		uint32_t dbgsel_dur_flt:8; /* [23:16] */
		uint32_t enable_dbgsel_cluster0:1; /* [24:24] */
		uint32_t enable_dbgsel_cluster1:1; /* [25:25] */
		uint32_t enable_dbgsel_wdtreset:1; /* [26:26] */
		uint32_t dbgsel_detect_cond:3; /* [29:27] */
		uint32_t dbgsel_flten:1; /* [30:30] */
		uint32_t enable_burnin:1; /* [31:31] */
	};
	uint32_t val;
};

union pmu_pmudbg_cluster0_cpu0_status {
	struct {
		uint32_t rsvd2:16; /* [15:0] */
		uint32_t states:8; /* [23:16] */
		uint32_t rsvd1:4; /* [27:24] */
		uint32_t standbywfi:1; /* [28:28] */
		uint32_t standbywfe:1; /* [29:29] */
		uint32_t rsvd0:2; /* [31:30] */
	};
	uint32_t val;
};

union pmu_pmudbg_cluster0_cpu1_status {
	struct {
		uint32_t rsvd2:16; /* [15:0] */
		uint32_t states:8; /* [23:16] */
		uint32_t rsvd1:4; /* [27:24] */
		uint32_t standbywfi:1; /* [28:28] */
		uint32_t standbywfe:1; /* [29:29] */
		uint32_t rsvd0:2; /* [31:30] */
	};
	uint32_t val;
};

union pmu_pmudbg_cluster0_cpu2_status {
	struct {
		uint32_t rsvd2:16; /* [15:0] */
		uint32_t states:8; /* [23:16] */
		uint32_t rsvd1:4; /* [27:24] */
		uint32_t standbywfi:1; /* [28:28] */
		uint32_t standbywfe:1; /* [29:29] */
		uint32_t rsvd0:2; /* [31:30] */
	};
	uint32_t val;
};

union pmu_pmudbg_cluster0_cpu3_status {
	struct {
		uint32_t rsvd2:16; /* [15:0] */
		uint32_t states:8; /* [23:16] */
		uint32_t rsvd1:4; /* [27:24] */
		uint32_t standbywfi:1; /* [28:28] */
		uint32_t standbywfe:1; /* [29:29] */
		uint32_t rsvd0:2; /* [31:30] */
	};
	uint32_t val;
};

union pmu_pmudbg_cluster0_l2_status {
	struct {
		uint32_t rsvd2:16; /* [15:0] */
		uint32_t states:7; /* [22:16] */
		uint32_t rsvd1:5; /* [27:23] */
		uint32_t standbywfil2:1; /* [28:28] */
		uint32_t rsvd0:3; /* [31:29] */
	};
	uint32_t val;
};

union pmu_pmudbg_cluster0_noncpu_status {
	struct {
		uint32_t rsvd1:16; /* [15:0] */
		uint32_t states:12; /* [27:16] */
		uint32_t rsvd0:4; /* [31:28] */
	};
	uint32_t val;
};

union pmu_pmudbg_cluster1_cpu0_status {
	struct {
		uint32_t rsvd2:16; /* [15:0] */
		uint32_t states:8; /* [23:16] */
		uint32_t rsvd1:4; /* [27:24] */
		uint32_t standbywfi:1; /* [28:28] */
		uint32_t standbywfe:1; /* [29:29] */
		uint32_t rsvd0:2; /* [31:30] */
	};
	uint32_t val;
};

union pmu_pmudbg_cluster1_cpu1_status {
	struct {
		uint32_t rsvd2:16; /* [15:0] */
		uint32_t states:8; /* [23:16] */
		uint32_t rsvd1:4; /* [27:24] */
		uint32_t standbywfi:1; /* [28:28] */
		uint32_t standbywfe:1; /* [29:29] */
		uint32_t rsvd0:2; /* [31:30] */
	};
	uint32_t val;
};

union pmu_pmudbg_cluster1_cpu2_status {
	struct {
		uint32_t rsvd2:16; /* [15:0] */
		uint32_t states:8; /* [23:16] */
		uint32_t rsvd1:4; /* [27:24] */
		uint32_t standbywfi:1; /* [28:28] */
		uint32_t standbywfe:1; /* [29:29] */
		uint32_t rsvd0:2; /* [31:30] */
	};
	uint32_t val;
};

union pmu_pmudbg_cluster1_cpu3_status {
	struct {
		uint32_t rsvd2:16; /* [15:0] */
		uint32_t states:8; /* [23:16] */
		uint32_t rsvd1:4; /* [27:24] */
		uint32_t standbywfi:1; /* [28:28] */
		uint32_t standbywfe:1; /* [29:29] */
		uint32_t rsvd0:2; /* [31:30] */
	};
	uint32_t val;
};

union pmu_pmudbg_cluster1_l2_status {
	struct {
		uint32_t rsvd2:16; /* [15:0] */
		uint32_t states:7; /* [22:16] */
		uint32_t rsvd1:5; /* [27:23] */
		uint32_t standbywfil2:1; /* [28:28] */
		uint32_t rsvd0:3; /* [31:29] */
	};
	uint32_t val;
};

union pmu_pmudbg_cluster1_noncpu_status {
	struct {
		uint32_t rsvd1:16; /* [15:0] */
		uint32_t states:12; /* [27:16] */
		uint32_t rsvd0:4; /* [31:28] */
	};
	uint32_t val;
};

union pmu_otp_status {
	struct {
		uint32_t otp_ready0:1; /* [0:0] */
		uint32_t otp_ready1:1; /* [1:1] */
		uint32_t otp_ready2:1; /* [2:2] */
		uint32_t otp_ready3:1; /* [3:3] */
		uint32_t otp_ready4:1; /* [4:4] */
		uint32_t rsvd0:27; /* [31:5] */
	};
	uint32_t val;
};

union pmu_pmudbg_pmlink_busy_status0 {
	struct {
		uint32_t cp0:11; /* [10:0] */
		uint32_t rsvd1:5; /* [15:11] */
		uint32_t cp1:11; /* [26:16] */
		uint32_t rsvd0:5; /* [31:27] */
	};
	uint32_t val;
};

union pmu_pmudbg_pmlink_busy_status1 {
	struct {
		uint32_t pcie:11; /* [10:0] */
		uint32_t rsvd1:5; /* [15:11] */
		uint32_t dram:11; /* [26:16] */
		uint32_t rsvd0:5; /* [31:27] */
	};
	uint32_t val;
};

union pmu_pmudbg_pmlink_busy_status2 {
	struct {
		uint32_t dcl0:11; /* [10:0] */
		uint32_t rsvd1:5; /* [15:11] */
		uint32_t dcl1:11; /* [26:16] */
		uint32_t rsvd0:5; /* [31:27] */
	};
	uint32_t val;
};

union pmu_pmudbg_pmlink_busy_status3 {
	struct {
		uint32_t rbch00:11; /* [10:0] */
		uint32_t rsvd1:5; /* [15:11] */
		uint32_t rbch01:11; /* [26:16] */
		uint32_t rsvd0:5; /* [31:27] */
	};
	uint32_t val;
};

union pmu_pmudbg_pmlink_busy_status4 {
	struct {
		uint32_t rbcv00:11; /* [10:0] */
		uint32_t rsvd1:5; /* [15:11] */
		uint32_t rbcv01:11; /* [26:16] */
		uint32_t rsvd0:5; /* [31:27] */
	};
	uint32_t val;
};

union pmu_pmudbg_pmlink_busy_status5 {
	struct {
		uint32_t rbcv10:11; /* [10:0] */
		uint32_t rsvd1:5; /* [15:11] */
		uint32_t rbcv11:11; /* [26:16] */
		uint32_t rsvd0:5; /* [31:27] */
	};
	uint32_t val;
};

union pmu_pmudbg_pmlink_busy_status6 {
	struct {
		uint32_t rot:11; /* [10:0] */
		uint32_t rsvd1:5; /* [15:11] */
		uint32_t peri0:11; /* [26:16] */
		uint32_t rsvd0:5; /* [31:27] */
	};
	uint32_t val;
};

union pmu_pmudbg_pmlink_busy_status7 {
	struct {
		uint32_t peri1:11; /* [10:0] */
		uint32_t rsvd1:5; /* [15:11] */
		uint32_t sbus_u:11; /* [26:16] */
		uint32_t rsvd0:5; /* [31:27] */
	};
	uint32_t val;
};

union pmu_pmudbg_pmlink_busy_status8 {
	struct {
		uint32_t sbus_d:11; /* [10:0] */
		uint32_t rsvd1:5; /* [15:11] */
		uint32_t sbus_l:11; /* [26:16] */
		uint32_t rsvd0:5; /* [31:27] */
	};
	uint32_t val;
};

union pmu_pmudbg_pmlink_busy_status9 {
	struct {
		uint32_t nbus_u:11; /* [10:0] */
		uint32_t rsvd1:5; /* [15:11] */
		uint32_t nbus_d:11; /* [26:16] */
		uint32_t rsvd0:5; /* [31:27] */
	};
	uint32_t val;
};

union pmu_pmudbg_pmlink_busy_status10 {
	struct {
		uint32_t nbus_l:11; /* [10:0] */
		uint32_t rsvd1:5; /* [15:11] */
		uint32_t wbus_u:11; /* [26:16] */
		uint32_t rsvd0:5; /* [31:27] */
	};
	uint32_t val;
};

union pmu_pmudbg_pmlink_busy_status11 {
	struct {
		uint32_t wbus_d:11; /* [10:0] */
		uint32_t rsvd1:5; /* [15:11] */
		uint32_t ebus_u:11; /* [26:16] */
		uint32_t rsvd0:5; /* [31:27] */
	};
	uint32_t val;
};

union pmu_pmudbg_pmlink_busy_status12 {
	struct {
		uint32_t ebus_d:11; /* [10:0] */
		uint32_t rsvd1:5; /* [15:11] */
		uint32_t ebus_r:11; /* [26:16] */
		uint32_t rsvd0:5; /* [31:27] */
	};
	uint32_t val;
};

union pmu_dis_irq_cluster0_cpu0_local_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_dis_irq_cluster0_cpu0_cpusequencer_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_dis_irq_cluster0_cpu1_local_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_dis_irq_cluster0_cpu1_cpusequencer_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_dis_irq_cluster0_cpu2_local_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_dis_irq_cluster0_cpu2_cpusequencer_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_dis_irq_cluster0_cpu3_local_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_dis_irq_cluster0_cpu3_cpusequencer_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_dis_irq_cluster1_cpu0_local_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_dis_irq_cluster1_cpu0_cpusequencer_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_dis_irq_cluster1_cpu1_local_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_dis_irq_cluster1_cpu1_cpusequencer_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_dis_irq_cluster1_cpu2_local_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_dis_irq_cluster1_cpu2_cpusequencer_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_dis_irq_cluster1_cpu3_local_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_dis_irq_cluster1_cpu3_cpusequencer_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_reset_cpuclkstop0_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:2; /* [1:0] */
		uint32_t rsvd0:30; /* [31:2] */
	};
	uint32_t val;
};

union pmu_reset_cpuclkstop1_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:2; /* [1:0] */
		uint32_t rsvd0:30; /* [31:2] */
	};
	uint32_t val;
};

union pmu_clkstop_open_cmu_cp0_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:2; /* [1:0] */
		uint32_t rsvd0:30; /* [31:2] */
	};
	uint32_t val;
};

union pmu_clkstop_open_cmu_cp1_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:2; /* [1:0] */
		uint32_t rsvd0:30; /* [31:2] */
	};
	uint32_t val;
};

union pmu_clkstop_open_cmu_pcie_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:2; /* [1:0] */
		uint32_t rsvd0:30; /* [31:2] */
	};
	uint32_t val;
};

union pmu_clkstop_open_cmu_dram_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:2; /* [1:0] */
		uint32_t rsvd0:30; /* [31:2] */
	};
	uint32_t val;
};

union pmu_clkstop_open_cmu_dcl0_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:2; /* [1:0] */
		uint32_t rsvd0:30; /* [31:2] */
	};
	uint32_t val;
};

union pmu_clkstop_open_cmu_dcl1_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:2; /* [1:0] */
		uint32_t rsvd0:30; /* [31:2] */
	};
	uint32_t val;
};

union pmu_clkstop_open_cmu_rbch00_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:2; /* [1:0] */
		uint32_t rsvd0:30; /* [31:2] */
	};
	uint32_t val;
};

union pmu_clkstop_open_cmu_rbch01_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:2; /* [1:0] */
		uint32_t rsvd0:30; /* [31:2] */
	};
	uint32_t val;
};

union pmu_clkstop_open_cmu_rbcv00_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:2; /* [1:0] */
		uint32_t rsvd0:30; /* [31:2] */
	};
	uint32_t val;
};

union pmu_clkstop_open_cmu_rbcv01_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:2; /* [1:0] */
		uint32_t rsvd0:30; /* [31:2] */
	};
	uint32_t val;
};

union pmu_clkstop_open_cmu_rbcv10_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:2; /* [1:0] */
		uint32_t rsvd0:30; /* [31:2] */
	};
	uint32_t val;
};

union pmu_clkstop_open_cmu_rbcv11_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:2; /* [1:0] */
		uint32_t rsvd0:30; /* [31:2] */
	};
	uint32_t val;
};

union pmu_clkstop_open_cmu_rot_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:2; /* [1:0] */
		uint32_t rsvd0:30; /* [31:2] */
	};
	uint32_t val;
};

union pmu_clkstop_open_cmu_peri0_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:2; /* [1:0] */
		uint32_t rsvd0:30; /* [31:2] */
	};
	uint32_t val;
};

union pmu_clkstop_open_cmu_peri1_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:2; /* [1:0] */
		uint32_t rsvd0:30; /* [31:2] */
	};
	uint32_t val;
};

union pmu_clkstop_open_cmu_sbus_u_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:2; /* [1:0] */
		uint32_t rsvd0:30; /* [31:2] */
	};
	uint32_t val;
};

union pmu_clkstop_open_cmu_sbus_d_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:2; /* [1:0] */
		uint32_t rsvd0:30; /* [31:2] */
	};
	uint32_t val;
};

union pmu_clkstop_open_cmu_sbus_l_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:2; /* [1:0] */
		uint32_t rsvd0:30; /* [31:2] */
	};
	uint32_t val;
};

union pmu_clkstop_open_cmu_nbus_u_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:2; /* [1:0] */
		uint32_t rsvd0:30; /* [31:2] */
	};
	uint32_t val;
};

union pmu_clkstop_open_cmu_nbus_d_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:2; /* [1:0] */
		uint32_t rsvd0:30; /* [31:2] */
	};
	uint32_t val;
};

union pmu_clkstop_open_cmu_nbus_l_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:2; /* [1:0] */
		uint32_t rsvd0:30; /* [31:2] */
	};
	uint32_t val;
};

union pmu_clkstop_open_cmu_wbus_u_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:2; /* [1:0] */
		uint32_t rsvd0:30; /* [31:2] */
	};
	uint32_t val;
};

union pmu_clkstop_open_cmu_wbus_d_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:2; /* [1:0] */
		uint32_t rsvd0:30; /* [31:2] */
	};
	uint32_t val;
};

union pmu_clkstop_open_cmu_ebus_u_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:2; /* [1:0] */
		uint32_t rsvd0:30; /* [31:2] */
	};
	uint32_t val;
};

union pmu_clkstop_open_cmu_ebus_d_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:2; /* [1:0] */
		uint32_t rsvd0:30; /* [31:2] */
	};
	uint32_t val;
};

union pmu_clkstop_open_cmu_ebus_r_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:2; /* [1:0] */
		uint32_t rsvd0:30; /* [31:2] */
	};
	uint32_t val;
};

union pmu_force_autoclkgate_cmu_cp0_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_force_autoclkgate_cmu_cp1_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_force_autoclkgate_cmu_pcie_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_force_autoclkgate_cmu_dram_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_force_autoclkgate_cmu_dcl0_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_force_autoclkgate_cmu_dcl1_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_force_autoclkgate_cmu_rbch00_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_force_autoclkgate_cmu_rbch01_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_force_autoclkgate_cmu_rbcv00_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_force_autoclkgate_cmu_rbcv01_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_force_autoclkgate_cmu_rbcv10_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_force_autoclkgate_cmu_rbcv11_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_force_autoclkgate_cmu_rot_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_force_autoclkgate_cmu_peri0_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_force_autoclkgate_cmu_peri1_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_force_autoclkgate_cmu_sbus_u_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_force_autoclkgate_cmu_sbus_d_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_force_autoclkgate_cmu_sbus_l_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_force_autoclkgate_cmu_nbus_u_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_force_autoclkgate_cmu_nbus_d_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_force_autoclkgate_cmu_nbus_l_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_force_autoclkgate_cmu_wbus_u_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_force_autoclkgate_cmu_wbus_d_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_force_autoclkgate_cmu_ebus_u_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_force_autoclkgate_cmu_ebus_d_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_force_autoclkgate_cmu_ebus_r_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_clkstop_cmu_cp0_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_clkstop_cmu_cp1_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_clkstop_cmu_pcie_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_clkstop_cmu_dram_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_clkstop_cmu_dcl0_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_clkstop_cmu_dcl1_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_clkstop_cmu_rbch00_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_clkstop_cmu_rbch01_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_clkstop_cmu_rbcv00_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_clkstop_cmu_rbcv01_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_clkstop_cmu_rbcv10_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_clkstop_cmu_rbcv11_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_clkstop_cmu_rot_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_clkstop_cmu_peri0_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_clkstop_cmu_peri1_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_clkstop_cmu_sbus_u_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_clkstop_cmu_sbus_d_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_clkstop_cmu_sbus_l_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_clkstop_cmu_nbus_u_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_clkstop_cmu_nbus_d_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_clkstop_cmu_nbus_l_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_clkstop_cmu_wbus_u_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_clkstop_cmu_wbus_d_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_clkstop_cmu_ebus_u_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_clkstop_cmu_ebus_d_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_clkstop_cmu_ebus_r_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_disable_pll_cmu_cp0_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_disable_pll_cmu_cp1_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_disable_pll_cmu_pcie_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_disable_pll_cmu_dram_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_disable_pll_cmu_dcl0_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_disable_pll_cmu_dcl1_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_disable_pll_cmu_rbch00_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_disable_pll_cmu_rbch01_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_disable_pll_cmu_rbcv00_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_disable_pll_cmu_rbcv01_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_disable_pll_cmu_rbcv10_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_disable_pll_cmu_rbcv11_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_disable_pll_cmu_rot_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_disable_pll_cmu_peri0_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_disable_pll_cmu_peri1_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_disable_pll_cmu_sbus_u_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_disable_pll_cmu_sbus_d_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_disable_pll_cmu_sbus_l_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_disable_pll_cmu_nbus_u_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_disable_pll_cmu_nbus_d_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_disable_pll_cmu_nbus_l_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_disable_pll_cmu_wbus_u_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_disable_pll_cmu_wbus_d_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_disable_pll_cmu_ebus_u_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_disable_pll_cmu_ebus_d_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_disable_pll_cmu_ebus_r_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_reset_logic_cp0_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:2; /* [1:0] */
		uint32_t rsvd0:30; /* [31:2] */
	};
	uint32_t val;
};

union pmu_reset_logic_cp1_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:2; /* [1:0] */
		uint32_t rsvd0:30; /* [31:2] */
	};
	uint32_t val;
};

union pmu_reset_logic_pcie_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:2; /* [1:0] */
		uint32_t rsvd0:30; /* [31:2] */
	};
	uint32_t val;
};

union pmu_reset_logic_dram_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:2; /* [1:0] */
		uint32_t rsvd0:30; /* [31:2] */
	};
	uint32_t val;
};

union pmu_reset_logic_dcl0_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:2; /* [1:0] */
		uint32_t rsvd0:30; /* [31:2] */
	};
	uint32_t val;
};

union pmu_reset_logic_dcl1_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:2; /* [1:0] */
		uint32_t rsvd0:30; /* [31:2] */
	};
	uint32_t val;
};

union pmu_reset_logic_rbch00_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:2; /* [1:0] */
		uint32_t rsvd0:30; /* [31:2] */
	};
	uint32_t val;
};

union pmu_reset_logic_rbch01_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:2; /* [1:0] */
		uint32_t rsvd0:30; /* [31:2] */
	};
	uint32_t val;
};

union pmu_reset_logic_rbcv00_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:2; /* [1:0] */
		uint32_t rsvd0:30; /* [31:2] */
	};
	uint32_t val;
};

union pmu_reset_logic_rbcv01_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:2; /* [1:0] */
		uint32_t rsvd0:30; /* [31:2] */
	};
	uint32_t val;
};

union pmu_reset_logic_rbcv10_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:2; /* [1:0] */
		uint32_t rsvd0:30; /* [31:2] */
	};
	uint32_t val;
};

union pmu_reset_logic_rbcv11_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:2; /* [1:0] */
		uint32_t rsvd0:30; /* [31:2] */
	};
	uint32_t val;
};

union pmu_reset_logic_rot_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:2; /* [1:0] */
		uint32_t rsvd0:30; /* [31:2] */
	};
	uint32_t val;
};

union pmu_reset_logic_peri0_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:2; /* [1:0] */
		uint32_t rsvd0:30; /* [31:2] */
	};
	uint32_t val;
};

union pmu_reset_logic_peri1_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:2; /* [1:0] */
		uint32_t rsvd0:30; /* [31:2] */
	};
	uint32_t val;
};

union pmu_reset_logic_sbus_u_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:2; /* [1:0] */
		uint32_t rsvd0:30; /* [31:2] */
	};
	uint32_t val;
};

union pmu_reset_logic_sbus_d_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:2; /* [1:0] */
		uint32_t rsvd0:30; /* [31:2] */
	};
	uint32_t val;
};

union pmu_reset_logic_sbus_l_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:2; /* [1:0] */
		uint32_t rsvd0:30; /* [31:2] */
	};
	uint32_t val;
};

union pmu_reset_logic_nbus_u_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:2; /* [1:0] */
		uint32_t rsvd0:30; /* [31:2] */
	};
	uint32_t val;
};

union pmu_reset_logic_nbus_d_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:2; /* [1:0] */
		uint32_t rsvd0:30; /* [31:2] */
	};
	uint32_t val;
};

union pmu_reset_logic_nbus_l_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:2; /* [1:0] */
		uint32_t rsvd0:30; /* [31:2] */
	};
	uint32_t val;
};

union pmu_reset_logic_wbus_u_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:2; /* [1:0] */
		uint32_t rsvd0:30; /* [31:2] */
	};
	uint32_t val;
};

union pmu_reset_logic_wbus_d_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:2; /* [1:0] */
		uint32_t rsvd0:30; /* [31:2] */
	};
	uint32_t val;
};

union pmu_reset_logic_ebus_u_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:2; /* [1:0] */
		uint32_t rsvd0:30; /* [31:2] */
	};
	uint32_t val;
};

union pmu_reset_logic_ebus_d_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:2; /* [1:0] */
		uint32_t rsvd0:30; /* [31:2] */
	};
	uint32_t val;
};

union pmu_reset_logic_ebus_r_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:2; /* [1:0] */
		uint32_t rsvd0:30; /* [31:2] */
	};
	uint32_t val;
};

union pmu_reset_cmu_cp0_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:2; /* [1:0] */
		uint32_t rsvd0:30; /* [31:2] */
	};
	uint32_t val;
};

union pmu_reset_cmu_cp1_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:2; /* [1:0] */
		uint32_t rsvd0:30; /* [31:2] */
	};
	uint32_t val;
};

union pmu_reset_cmu_pcie_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:2; /* [1:0] */
		uint32_t rsvd0:30; /* [31:2] */
	};
	uint32_t val;
};

union pmu_reset_cmu_dram_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:2; /* [1:0] */
		uint32_t rsvd0:30; /* [31:2] */
	};
	uint32_t val;
};

union pmu_reset_cmu_dcl0_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:2; /* [1:0] */
		uint32_t rsvd0:30; /* [31:2] */
	};
	uint32_t val;
};

union pmu_reset_cmu_dcl1_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:2; /* [1:0] */
		uint32_t rsvd0:30; /* [31:2] */
	};
	uint32_t val;
};

union pmu_reset_cmu_rbch00_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:2; /* [1:0] */
		uint32_t rsvd0:30; /* [31:2] */
	};
	uint32_t val;
};

union pmu_reset_cmu_rbch01_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:2; /* [1:0] */
		uint32_t rsvd0:30; /* [31:2] */
	};
	uint32_t val;
};

union pmu_reset_cmu_rbcv00_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:2; /* [1:0] */
		uint32_t rsvd0:30; /* [31:2] */
	};
	uint32_t val;
};

union pmu_reset_cmu_rbcv01_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:2; /* [1:0] */
		uint32_t rsvd0:30; /* [31:2] */
	};
	uint32_t val;
};

union pmu_reset_cmu_rbcv10_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:2; /* [1:0] */
		uint32_t rsvd0:30; /* [31:2] */
	};
	uint32_t val;
};

union pmu_reset_cmu_rbcv11_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:2; /* [1:0] */
		uint32_t rsvd0:30; /* [31:2] */
	};
	uint32_t val;
};

union pmu_reset_cmu_rot_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:2; /* [1:0] */
		uint32_t rsvd0:30; /* [31:2] */
	};
	uint32_t val;
};

union pmu_reset_cmu_peri0_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:2; /* [1:0] */
		uint32_t rsvd0:30; /* [31:2] */
	};
	uint32_t val;
};

union pmu_reset_cmu_peri1_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:2; /* [1:0] */
		uint32_t rsvd0:30; /* [31:2] */
	};
	uint32_t val;
};

union pmu_reset_cmu_sbus_u_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:2; /* [1:0] */
		uint32_t rsvd0:30; /* [31:2] */
	};
	uint32_t val;
};

union pmu_reset_cmu_sbus_d_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:2; /* [1:0] */
		uint32_t rsvd0:30; /* [31:2] */
	};
	uint32_t val;
};

union pmu_reset_cmu_sbus_l_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:2; /* [1:0] */
		uint32_t rsvd0:30; /* [31:2] */
	};
	uint32_t val;
};

union pmu_reset_cmu_nbus_u_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:2; /* [1:0] */
		uint32_t rsvd0:30; /* [31:2] */
	};
	uint32_t val;
};

union pmu_reset_cmu_nbus_d_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:2; /* [1:0] */
		uint32_t rsvd0:30; /* [31:2] */
	};
	uint32_t val;
};

union pmu_reset_cmu_nbus_l_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:2; /* [1:0] */
		uint32_t rsvd0:30; /* [31:2] */
	};
	uint32_t val;
};

union pmu_reset_cmu_wbus_u_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:2; /* [1:0] */
		uint32_t rsvd0:30; /* [31:2] */
	};
	uint32_t val;
};

union pmu_reset_cmu_wbus_d_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:2; /* [1:0] */
		uint32_t rsvd0:30; /* [31:2] */
	};
	uint32_t val;
};

union pmu_reset_cmu_ebus_u_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:2; /* [1:0] */
		uint32_t rsvd0:30; /* [31:2] */
	};
	uint32_t val;
};

union pmu_reset_cmu_ebus_d_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:2; /* [1:0] */
		uint32_t rsvd0:30; /* [31:2] */
	};
	uint32_t val;
};

union pmu_reset_cmu_ebus_r_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:2; /* [1:0] */
		uint32_t rsvd0:30; /* [31:2] */
	};
	uint32_t val;
};

union pmu_lpi_residual_cmu_cp0_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_lpi_residual_cmu_cp1_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_lpi_residual_cmu_pcie_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_lpi_residual_cmu_dram_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_lpi_residual_cmu_dcl0_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_lpi_residual_cmu_dcl1_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_lpi_residual_cmu_rbch00_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_lpi_residual_cmu_rbch01_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_lpi_residual_cmu_rbcv00_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_lpi_residual_cmu_rbcv01_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_lpi_residual_cmu_rbcv10_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_lpi_residual_cmu_rbcv11_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_lpi_residual_cmu_rot_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_lpi_residual_cmu_peri0_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_lpi_residual_cmu_peri1_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_lpi_residual_cmu_sbus_u_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_lpi_residual_cmu_sbus_d_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_lpi_residual_cmu_sbus_l_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_lpi_residual_cmu_nbus_u_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_lpi_residual_cmu_nbus_d_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_lpi_residual_cmu_nbus_l_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_lpi_residual_cmu_wbus_u_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_lpi_residual_cmu_wbus_d_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_lpi_residual_cmu_ebus_u_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_lpi_residual_cmu_ebus_d_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_lpi_residual_cmu_ebus_r_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_lpi_bus_cmu_cp0_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_lpi_bus_cmu_cp1_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_lpi_bus_cmu_pcie_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_lpi_bus_cmu_dram_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_lpi_bus_cmu_dcl0_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_lpi_bus_cmu_dcl1_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_lpi_bus_cmu_rbch00_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_lpi_bus_cmu_rbch01_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_lpi_bus_cmu_rbcv00_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_lpi_bus_cmu_rbcv01_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_lpi_bus_cmu_rbcv10_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_lpi_bus_cmu_rbcv11_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_lpi_bus_cmu_rot_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_lpi_bus_cmu_peri0_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_lpi_bus_cmu_peri1_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_lpi_bus_cmu_sbus_u_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_lpi_bus_cmu_sbus_d_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_lpi_bus_cmu_sbus_l_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_lpi_bus_cmu_nbus_u_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_lpi_bus_cmu_nbus_d_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_lpi_bus_cmu_nbus_l_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_lpi_bus_cmu_wbus_u_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_lpi_bus_cmu_wbus_d_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_lpi_bus_cmu_ebus_u_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_lpi_bus_cmu_ebus_d_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_lpi_bus_cmu_ebus_r_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_lpi_busmaster_cmu_cp0_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_lpi_busmaster_cmu_cp1_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_lpi_busmaster_cmu_pcie_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_lpi_busmaster_cmu_dram_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_lpi_busmaster_cmu_dcl0_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_lpi_busmaster_cmu_dcl1_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_lpi_busmaster_cmu_rbch00_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_lpi_busmaster_cmu_rbch01_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_lpi_busmaster_cmu_rbcv00_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_lpi_busmaster_cmu_rbcv01_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_lpi_busmaster_cmu_rbcv10_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_lpi_busmaster_cmu_rbcv11_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_lpi_busmaster_cmu_rot_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_lpi_busmaster_cmu_peri0_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_lpi_busmaster_cmu_peri1_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_lpi_busmaster_cmu_sbus_u_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_lpi_busmaster_cmu_sbus_d_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_lpi_busmaster_cmu_sbus_l_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_lpi_busmaster_cmu_nbus_u_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_lpi_busmaster_cmu_nbus_d_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_lpi_busmaster_cmu_nbus_l_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_lpi_busmaster_cmu_wbus_u_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_lpi_busmaster_cmu_wbus_d_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_lpi_busmaster_cmu_ebus_u_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_lpi_busmaster_cmu_ebus_d_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_lpi_busmaster_cmu_ebus_r_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_lpi_hbm_cmu_dram_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_cm7_cpu_pcie_sys_pwr_reg {
	struct {
		uint32_t sys_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_cluster0_cpu0_configuration {
	struct {
		uint32_t local_pwr_cfg:4; /* [3:0] */
		uint32_t rsvd1:12; /* [15:4] */
		uint32_t initiate_wakeup_from_lowpwr:4; /* [19:16] */
		uint32_t rsvd0:11; /* [30:20] */
		uint32_t automatic_wakeup:1; /* [31:31] */
	};
	uint32_t val;
};

union pmu_cluster0_cpu0_status {
	struct {
		uint32_t status:4; /* [3:0] */
		uint32_t scall_feedback_o_fail:4; /* [7:4] */
		uint32_t wakeup_from_local_cfg:4; /* [11:8] */
		uint32_t status_wakeup_from_reset:1; /* [12:12] */
		uint32_t rsvd2:3; /* [15:13] */
		uint32_t states:8; /* [23:16] */
		uint32_t scall_feedback_a_fail:1; /* [24:24] */
		uint32_t scpre_feedback_fail:1; /* [25:25] */
		uint32_t rsvd1:2; /* [27:26] */
		uint32_t standbywfi:1; /* [28:28] */
		uint32_t standbywfe:1; /* [29:29] */
		uint32_t rsvd0:2; /* [31:30] */
	};
	uint32_t val;
};

union pmu_cluster0_cpu0_option {
	struct {
		uint32_t use_sc_feedback:4; /* [3:0] */
		uint32_t use_sc_counter:1; /* [4:4] */
		uint32_t use_sc_both:1; /* [5:5] */
		uint32_t use_mempwr_counter:1; /* [6:6] */
		uint32_t use_mempwr_feedback:1; /* [7:7] */
		uint32_t enable_automatic_wakeup_with_interrupt_request:1; /* [8:8] */
		uint32_t enable_gpr_cpupwrup:1; /* [9:9] */
		uint32_t use_irqcpu_for_pwrdown:1; /* [10:10] */
		uint32_t use_irqcpu_for_pwrup:1; /* [11:11] */
		uint32_t use_delayed_reset_assertion:1; /* [12:12] */
		uint32_t rsvd3:2; /* [14:13] */
		uint32_t skip_dbgpwrdwn:1; /* [15:15] */
		uint32_t use_standbywfi:1; /* [16:16] */
		uint32_t req_last_cpu:1; /* [17:17] */
		uint32_t rsvd2:2; /* [19:18] */
		uint32_t ignore_output_update_done:1; /* [20:20] */
		uint32_t rsvd1:3; /* [23:21] */
		uint32_t use_standbywfe:1; /* [24:24] */
		uint32_t clamp_emulation:1; /* [25:25] */
		uint32_t reset_emulation:1; /* [26:26] */
		uint32_t dbgpwrdwnreq_emulation:1; /* [27:27] */
		uint32_t use_smpen:1; /* [28:28] */
		uint32_t rsvd0:1; /* [29:29] */
		uint32_t enable_dbgnopwrdwn:1; /* [30:30] */
		uint32_t emulation:1; /* [31:31] */
	};
	uint32_t val;
};

union pmu_cluster0_cpu0_reset {
	struct {
		uint32_t swreset_cpuporeset:1; /* [0:0] */
		uint32_t swreset_corereset:1; /* [1:1] */
		uint32_t rsvd5:2; /* [3:2] */
		uint32_t swreset_use_standbywfi:1; /* [4:4] */
		uint32_t swreset_use_standbywfe:1; /* [5:5] */
		uint32_t rsvd4:2; /* [7:6] */
		uint32_t disable_level3_cpuporeset:1; /* [8:8] */
		uint32_t disable_level3_corereset:1; /* [9:9] */
		uint32_t disable_level2_cpuporeset:1; /* [10:10] */
		uint32_t disable_level2_corereset:1; /* [11:11] */
		uint32_t disable_level1_cpuporeset:1; /* [12:12] */
		uint32_t disable_level1_corereset:1; /* [13:13] */
		uint32_t rsvd3:1; /* [14:14] */
		uint32_t enable_gpr_reset:1; /* [15:15] */
		uint32_t rsvd2:8; /* [23:16] */
		uint32_t warmrstreq_use_standbywfi:1; /* [24:24] */
		uint32_t warmrstreq_use_standbywfe:1; /* [25:25] */
		uint32_t rsvd1:1; /* [26:26] */
		uint32_t enable_warmrstreq:1; /* [27:27] */
		uint32_t dbgrstreq_use_standbywfi:1; /* [28:28] */
		uint32_t dbgrstreq_use_standbywfe:1; /* [29:29] */
		uint32_t rsvd0:1; /* [30:30] */
		uint32_t enable_dbgrstreq:1; /* [31:31] */
	};
	uint32_t val;
};

union pmu_cluster0_cpu0_duration0 {
	struct {
		uint32_t dur_scpre_wait:4; /* [3:0] */
		uint32_t dur_scall:4; /* [7:4] */
		uint32_t dur_scpre:4; /* [11:8] */
		uint32_t dur_mempwr:4; /* [15:12] */
		uint32_t dur_chg_reset:4; /* [19:16] */
		uint32_t dur_wait_reset:4; /* [23:20] */
		uint32_t rsvd0:8; /* [31:24] */
	};
	uint32_t val;
};

union pmu_cluster0_cpu0_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_cluster0_cpu0_duration2 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_cluster0_cpu0_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_dis_irq_cluster0_cpu0_local_configuration {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_dis_irq_cluster0_cpu0_local_status {
	struct {
		uint32_t status:1; /* [0:0] */
		uint32_t rsvd1:15; /* [15:1] */
		uint32_t states:1; /* [16:16] */
		uint32_t rsvd0:15; /* [31:17] */
	};
	uint32_t val;
};

union pmu_dis_irq_cluster0_cpu0_local_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_dis_irq_cluster0_cpu0_local_duration0 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_dis_irq_cluster0_cpu0_local_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_dis_irq_cluster0_cpu0_local_duration2 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_dis_irq_cluster0_cpu0_local_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_dis_irq_cluster0_cpu0_cpusequencer_configuration {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_dis_irq_cluster0_cpu0_cpusequencer_status {
	struct {
		uint32_t status:1; /* [0:0] */
		uint32_t rsvd1:15; /* [15:1] */
		uint32_t states:1; /* [16:16] */
		uint32_t rsvd0:15; /* [31:17] */
	};
	uint32_t val;
};

union pmu_dis_irq_cluster0_cpu0_cpusequencer_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_dis_irq_cluster0_cpu0_cpusequencer_duration0 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_dis_irq_cluster0_cpu0_cpusequencer_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_dis_irq_cluster0_cpu0_cpusequencer_duration2 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_dis_irq_cluster0_cpu0_cpusequencer_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_cluster0_cpu1_configuration {
	struct {
		uint32_t local_pwr_cfg:4; /* [3:0] */
		uint32_t rsvd1:12; /* [15:4] */
		uint32_t initiate_wakeup_from_lowpwr:4; /* [19:16] */
		uint32_t rsvd0:11; /* [30:20] */
		uint32_t automatic_wakeup:1; /* [31:31] */
	};
	uint32_t val;
};

union pmu_cluster0_cpu1_status {
	struct {
		uint32_t status:4; /* [3:0] */
		uint32_t scall_feedback_o_fail:4; /* [7:4] */
		uint32_t wakeup_from_local_cfg:4; /* [11:8] */
		uint32_t status_wakeup_from_reset:1; /* [12:12] */
		uint32_t rsvd2:3; /* [15:13] */
		uint32_t states:8; /* [23:16] */
		uint32_t scall_feedback_a_fail:1; /* [24:24] */
		uint32_t scpre_feedback_fail:1; /* [25:25] */
		uint32_t rsvd1:2; /* [27:26] */
		uint32_t standbywfi:1; /* [28:28] */
		uint32_t standbywfe:1; /* [29:29] */
		uint32_t rsvd0:2; /* [31:30] */
	};
	uint32_t val;
};

union pmu_cluster0_cpu1_option {
	struct {
		uint32_t use_sc_feedback:4; /* [3:0] */
		uint32_t use_sc_counter:1; /* [4:4] */
		uint32_t use_sc_both:1; /* [5:5] */
		uint32_t use_mempwr_counter:1; /* [6:6] */
		uint32_t use_mempwr_feedback:1; /* [7:7] */
		uint32_t enable_automatic_wakeup_with_interrupt_request:1; /* [8:8] */
		uint32_t enable_gpr_cpupwrup:1; /* [9:9] */
		uint32_t use_irqcpu_for_pwrdown:1; /* [10:10] */
		uint32_t use_irqcpu_for_pwrup:1; /* [11:11] */
		uint32_t use_delayed_reset_assertion:1; /* [12:12] */
		uint32_t rsvd3:2; /* [14:13] */
		uint32_t skip_dbgpwrdwn:1; /* [15:15] */
		uint32_t use_standbywfi:1; /* [16:16] */
		uint32_t req_last_cpu:1; /* [17:17] */
		uint32_t rsvd2:2; /* [19:18] */
		uint32_t ignore_output_update_done:1; /* [20:20] */
		uint32_t rsvd1:3; /* [23:21] */
		uint32_t use_standbywfe:1; /* [24:24] */
		uint32_t clamp_emulation:1; /* [25:25] */
		uint32_t reset_emulation:1; /* [26:26] */
		uint32_t dbgpwrdwnreq_emulation:1; /* [27:27] */
		uint32_t use_smpen:1; /* [28:28] */
		uint32_t rsvd0:1; /* [29:29] */
		uint32_t enable_dbgnopwrdwn:1; /* [30:30] */
		uint32_t emulation:1; /* [31:31] */
	};
	uint32_t val;
};

union pmu_cluster0_cpu1_reset {
	struct {
		uint32_t swreset_cpuporeset:1; /* [0:0] */
		uint32_t swreset_corereset:1; /* [1:1] */
		uint32_t rsvd5:2; /* [3:2] */
		uint32_t swreset_use_standbywfi:1; /* [4:4] */
		uint32_t swreset_use_standbywfe:1; /* [5:5] */
		uint32_t rsvd4:2; /* [7:6] */
		uint32_t disable_level3_cpuporeset:1; /* [8:8] */
		uint32_t disable_level3_corereset:1; /* [9:9] */
		uint32_t disable_level2_cpuporeset:1; /* [10:10] */
		uint32_t disable_level2_corereset:1; /* [11:11] */
		uint32_t disable_level1_cpuporeset:1; /* [12:12] */
		uint32_t disable_level1_corereset:1; /* [13:13] */
		uint32_t rsvd3:1; /* [14:14] */
		uint32_t enable_gpr_reset:1; /* [15:15] */
		uint32_t rsvd2:8; /* [23:16] */
		uint32_t warmrstreq_use_standbywfi:1; /* [24:24] */
		uint32_t warmrstreq_use_standbywfe:1; /* [25:25] */
		uint32_t rsvd1:1; /* [26:26] */
		uint32_t enable_warmrstreq:1; /* [27:27] */
		uint32_t dbgrstreq_use_standbywfi:1; /* [28:28] */
		uint32_t dbgrstreq_use_standbywfe:1; /* [29:29] */
		uint32_t rsvd0:1; /* [30:30] */
		uint32_t enable_dbgrstreq:1; /* [31:31] */
	};
	uint32_t val;
};

union pmu_cluster0_cpu1_duration0 {
	struct {
		uint32_t dur_scpre_wait:4; /* [3:0] */
		uint32_t dur_scall:4; /* [7:4] */
		uint32_t dur_scpre:4; /* [11:8] */
		uint32_t dur_mempwr:4; /* [15:12] */
		uint32_t dur_chg_reset:4; /* [19:16] */
		uint32_t dur_wait_reset:4; /* [23:20] */
		uint32_t rsvd0:8; /* [31:24] */
	};
	uint32_t val;
};

union pmu_cluster0_cpu1_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_cluster0_cpu1_duration2 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_cluster0_cpu1_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_dis_irq_cluster0_cpu1_local_configuration {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_dis_irq_cluster0_cpu1_local_status {
	struct {
		uint32_t status:1; /* [0:0] */
		uint32_t rsvd1:15; /* [15:1] */
		uint32_t states:1; /* [16:16] */
		uint32_t rsvd0:15; /* [31:17] */
	};
	uint32_t val;
};

union pmu_dis_irq_cluster0_cpu1_local_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_dis_irq_cluster0_cpu1_local_duration0 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_dis_irq_cluster0_cpu1_local_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_dis_irq_cluster0_cpu1_local_duration2 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_dis_irq_cluster0_cpu1_local_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_dis_irq_cluster0_cpu1_cpusequencer_configuration {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_dis_irq_cluster0_cpu1_cpusequencer_status {
	struct {
		uint32_t status:1; /* [0:0] */
		uint32_t rsvd1:15; /* [15:1] */
		uint32_t states:1; /* [16:16] */
		uint32_t rsvd0:15; /* [31:17] */
	};
	uint32_t val;
};

union pmu_dis_irq_cluster0_cpu1_cpusequencer_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_dis_irq_cluster0_cpu1_cpusequencer_duration0 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_dis_irq_cluster0_cpu1_cpusequencer_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_dis_irq_cluster0_cpu1_cpusequencer_duration2 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_dis_irq_cluster0_cpu1_cpusequencer_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_cluster0_cpu2_configuration {
	struct {
		uint32_t local_pwr_cfg:4; /* [3:0] */
		uint32_t rsvd1:12; /* [15:4] */
		uint32_t initiate_wakeup_from_lowpwr:4; /* [19:16] */
		uint32_t rsvd0:11; /* [30:20] */
		uint32_t automatic_wakeup:1; /* [31:31] */
	};
	uint32_t val;
};

union pmu_cluster0_cpu2_status {
	struct {
		uint32_t status:4; /* [3:0] */
		uint32_t scall_feedback_o_fail:4; /* [7:4] */
		uint32_t wakeup_from_local_cfg:4; /* [11:8] */
		uint32_t status_wakeup_from_reset:1; /* [12:12] */
		uint32_t rsvd2:3; /* [15:13] */
		uint32_t states:8; /* [23:16] */
		uint32_t scall_feedback_a_fail:1; /* [24:24] */
		uint32_t scpre_feedback_fail:1; /* [25:25] */
		uint32_t rsvd1:2; /* [27:26] */
		uint32_t standbywfi:1; /* [28:28] */
		uint32_t standbywfe:1; /* [29:29] */
		uint32_t rsvd0:2; /* [31:30] */
	};
	uint32_t val;
};

union pmu_cluster0_cpu2_option {
	struct {
		uint32_t use_sc_feedback:4; /* [3:0] */
		uint32_t use_sc_counter:1; /* [4:4] */
		uint32_t use_sc_both:1; /* [5:5] */
		uint32_t use_mempwr_counter:1; /* [6:6] */
		uint32_t use_mempwr_feedback:1; /* [7:7] */
		uint32_t enable_automatic_wakeup_with_interrupt_request:1; /* [8:8] */
		uint32_t enable_gpr_cpupwrup:1; /* [9:9] */
		uint32_t use_irqcpu_for_pwrdown:1; /* [10:10] */
		uint32_t use_irqcpu_for_pwrup:1; /* [11:11] */
		uint32_t use_delayed_reset_assertion:1; /* [12:12] */
		uint32_t rsvd3:2; /* [14:13] */
		uint32_t skip_dbgpwrdwn:1; /* [15:15] */
		uint32_t use_standbywfi:1; /* [16:16] */
		uint32_t req_last_cpu:1; /* [17:17] */
		uint32_t rsvd2:2; /* [19:18] */
		uint32_t ignore_output_update_done:1; /* [20:20] */
		uint32_t rsvd1:3; /* [23:21] */
		uint32_t use_standbywfe:1; /* [24:24] */
		uint32_t clamp_emulation:1; /* [25:25] */
		uint32_t reset_emulation:1; /* [26:26] */
		uint32_t dbgpwrdwnreq_emulation:1; /* [27:27] */
		uint32_t use_smpen:1; /* [28:28] */
		uint32_t rsvd0:1; /* [29:29] */
		uint32_t enable_dbgnopwrdwn:1; /* [30:30] */
		uint32_t emulation:1; /* [31:31] */
	};
	uint32_t val;
};

union pmu_cluster0_cpu2_reset {
	struct {
		uint32_t swreset_cpuporeset:1; /* [0:0] */
		uint32_t swreset_corereset:1; /* [1:1] */
		uint32_t rsvd5:2; /* [3:2] */
		uint32_t swreset_use_standbywfi:1; /* [4:4] */
		uint32_t swreset_use_standbywfe:1; /* [5:5] */
		uint32_t rsvd4:2; /* [7:6] */
		uint32_t disable_level3_cpuporeset:1; /* [8:8] */
		uint32_t disable_level3_corereset:1; /* [9:9] */
		uint32_t disable_level2_cpuporeset:1; /* [10:10] */
		uint32_t disable_level2_corereset:1; /* [11:11] */
		uint32_t disable_level1_cpuporeset:1; /* [12:12] */
		uint32_t disable_level1_corereset:1; /* [13:13] */
		uint32_t rsvd3:1; /* [14:14] */
		uint32_t enable_gpr_reset:1; /* [15:15] */
		uint32_t rsvd2:8; /* [23:16] */
		uint32_t warmrstreq_use_standbywfi:1; /* [24:24] */
		uint32_t warmrstreq_use_standbywfe:1; /* [25:25] */
		uint32_t rsvd1:1; /* [26:26] */
		uint32_t enable_warmrstreq:1; /* [27:27] */
		uint32_t dbgrstreq_use_standbywfi:1; /* [28:28] */
		uint32_t dbgrstreq_use_standbywfe:1; /* [29:29] */
		uint32_t rsvd0:1; /* [30:30] */
		uint32_t enable_dbgrstreq:1; /* [31:31] */
	};
	uint32_t val;
};

union pmu_cluster0_cpu2_duration0 {
	struct {
		uint32_t dur_scpre_wait:4; /* [3:0] */
		uint32_t dur_scall:4; /* [7:4] */
		uint32_t dur_scpre:4; /* [11:8] */
		uint32_t dur_mempwr:4; /* [15:12] */
		uint32_t dur_chg_reset:4; /* [19:16] */
		uint32_t dur_wait_reset:4; /* [23:20] */
		uint32_t rsvd0:8; /* [31:24] */
	};
	uint32_t val;
};

union pmu_cluster0_cpu2_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_cluster0_cpu2_duration2 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_cluster0_cpu2_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_dis_irq_cluster0_cpu2_local_configuration {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_dis_irq_cluster0_cpu2_local_status {
	struct {
		uint32_t status:1; /* [0:0] */
		uint32_t rsvd1:15; /* [15:1] */
		uint32_t states:1; /* [16:16] */
		uint32_t rsvd0:15; /* [31:17] */
	};
	uint32_t val;
};

union pmu_dis_irq_cluster0_cpu2_local_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_dis_irq_cluster0_cpu2_local_duration0 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_dis_irq_cluster0_cpu2_local_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_dis_irq_cluster0_cpu2_local_duration2 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_dis_irq_cluster0_cpu2_local_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_dis_irq_cluster0_cpu2_cpusequencer_configuration {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_dis_irq_cluster0_cpu2_cpusequencer_status {
	struct {
		uint32_t status:1; /* [0:0] */
		uint32_t rsvd1:15; /* [15:1] */
		uint32_t states:1; /* [16:16] */
		uint32_t rsvd0:15; /* [31:17] */
	};
	uint32_t val;
};

union pmu_dis_irq_cluster0_cpu2_cpusequencer_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_dis_irq_cluster0_cpu2_cpusequencer_duration0 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_dis_irq_cluster0_cpu2_cpusequencer_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_dis_irq_cluster0_cpu2_cpusequencer_duration2 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_dis_irq_cluster0_cpu2_cpusequencer_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_cluster0_cpu3_configuration {
	struct {
		uint32_t local_pwr_cfg:4; /* [3:0] */
		uint32_t rsvd1:12; /* [15:4] */
		uint32_t initiate_wakeup_from_lowpwr:4; /* [19:16] */
		uint32_t rsvd0:11; /* [30:20] */
		uint32_t automatic_wakeup:1; /* [31:31] */
	};
	uint32_t val;
};

union pmu_cluster0_cpu3_status {
	struct {
		uint32_t status:4; /* [3:0] */
		uint32_t scall_feedback_o_fail:4; /* [7:4] */
		uint32_t wakeup_from_local_cfg:4; /* [11:8] */
		uint32_t status_wakeup_from_reset:1; /* [12:12] */
		uint32_t rsvd2:3; /* [15:13] */
		uint32_t states:8; /* [23:16] */
		uint32_t scall_feedback_a_fail:1; /* [24:24] */
		uint32_t scpre_feedback_fail:1; /* [25:25] */
		uint32_t rsvd1:2; /* [27:26] */
		uint32_t standbywfi:1; /* [28:28] */
		uint32_t standbywfe:1; /* [29:29] */
		uint32_t rsvd0:2; /* [31:30] */
	};
	uint32_t val;
};

union pmu_cluster0_cpu3_option {
	struct {
		uint32_t use_sc_feedback:4; /* [3:0] */
		uint32_t use_sc_counter:1; /* [4:4] */
		uint32_t use_sc_both:1; /* [5:5] */
		uint32_t use_mempwr_counter:1; /* [6:6] */
		uint32_t use_mempwr_feedback:1; /* [7:7] */
		uint32_t enable_automatic_wakeup_with_interrupt_request:1; /* [8:8] */
		uint32_t enable_gpr_cpupwrup:1; /* [9:9] */
		uint32_t use_irqcpu_for_pwrdown:1; /* [10:10] */
		uint32_t use_irqcpu_for_pwrup:1; /* [11:11] */
		uint32_t use_delayed_reset_assertion:1; /* [12:12] */
		uint32_t rsvd3:2; /* [14:13] */
		uint32_t skip_dbgpwrdwn:1; /* [15:15] */
		uint32_t use_standbywfi:1; /* [16:16] */
		uint32_t req_last_cpu:1; /* [17:17] */
		uint32_t rsvd2:2; /* [19:18] */
		uint32_t ignore_output_update_done:1; /* [20:20] */
		uint32_t rsvd1:3; /* [23:21] */
		uint32_t use_standbywfe:1; /* [24:24] */
		uint32_t clamp_emulation:1; /* [25:25] */
		uint32_t reset_emulation:1; /* [26:26] */
		uint32_t dbgpwrdwnreq_emulation:1; /* [27:27] */
		uint32_t use_smpen:1; /* [28:28] */
		uint32_t rsvd0:1; /* [29:29] */
		uint32_t enable_dbgnopwrdwn:1; /* [30:30] */
		uint32_t emulation:1; /* [31:31] */
	};
	uint32_t val;
};

union pmu_cluster0_cpu3_reset {
	struct {
		uint32_t swreset_cpuporeset:1; /* [0:0] */
		uint32_t swreset_corereset:1; /* [1:1] */
		uint32_t rsvd5:2; /* [3:2] */
		uint32_t swreset_use_standbywfi:1; /* [4:4] */
		uint32_t swreset_use_standbywfe:1; /* [5:5] */
		uint32_t rsvd4:2; /* [7:6] */
		uint32_t disable_level3_cpuporeset:1; /* [8:8] */
		uint32_t disable_level3_corereset:1; /* [9:9] */
		uint32_t disable_level2_cpuporeset:1; /* [10:10] */
		uint32_t disable_level2_corereset:1; /* [11:11] */
		uint32_t disable_level1_cpuporeset:1; /* [12:12] */
		uint32_t disable_level1_corereset:1; /* [13:13] */
		uint32_t rsvd3:1; /* [14:14] */
		uint32_t enable_gpr_reset:1; /* [15:15] */
		uint32_t rsvd2:8; /* [23:16] */
		uint32_t warmrstreq_use_standbywfi:1; /* [24:24] */
		uint32_t warmrstreq_use_standbywfe:1; /* [25:25] */
		uint32_t rsvd1:1; /* [26:26] */
		uint32_t enable_warmrstreq:1; /* [27:27] */
		uint32_t dbgrstreq_use_standbywfi:1; /* [28:28] */
		uint32_t dbgrstreq_use_standbywfe:1; /* [29:29] */
		uint32_t rsvd0:1; /* [30:30] */
		uint32_t enable_dbgrstreq:1; /* [31:31] */
	};
	uint32_t val;
};

union pmu_cluster0_cpu3_duration0 {
	struct {
		uint32_t dur_scpre_wait:4; /* [3:0] */
		uint32_t dur_scall:4; /* [7:4] */
		uint32_t dur_scpre:4; /* [11:8] */
		uint32_t dur_mempwr:4; /* [15:12] */
		uint32_t dur_chg_reset:4; /* [19:16] */
		uint32_t dur_wait_reset:4; /* [23:20] */
		uint32_t rsvd0:8; /* [31:24] */
	};
	uint32_t val;
};

union pmu_cluster0_cpu3_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_cluster0_cpu3_duration2 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_cluster0_cpu3_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_dis_irq_cluster0_cpu3_local_configuration {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_dis_irq_cluster0_cpu3_local_status {
	struct {
		uint32_t status:1; /* [0:0] */
		uint32_t rsvd1:15; /* [15:1] */
		uint32_t states:1; /* [16:16] */
		uint32_t rsvd0:15; /* [31:17] */
	};
	uint32_t val;
};

union pmu_dis_irq_cluster0_cpu3_local_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_dis_irq_cluster0_cpu3_local_duration0 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_dis_irq_cluster0_cpu3_local_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_dis_irq_cluster0_cpu3_local_duration2 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_dis_irq_cluster0_cpu3_local_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_dis_irq_cluster0_cpu3_cpusequencer_configuration {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_dis_irq_cluster0_cpu3_cpusequencer_status {
	struct {
		uint32_t status:1; /* [0:0] */
		uint32_t rsvd1:15; /* [15:1] */
		uint32_t states:1; /* [16:16] */
		uint32_t rsvd0:15; /* [31:17] */
	};
	uint32_t val;
};

union pmu_dis_irq_cluster0_cpu3_cpusequencer_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_dis_irq_cluster0_cpu3_cpusequencer_duration0 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_dis_irq_cluster0_cpu3_cpusequencer_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_dis_irq_cluster0_cpu3_cpusequencer_duration2 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_dis_irq_cluster0_cpu3_cpusequencer_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_cluster1_cpu0_configuration {
	struct {
		uint32_t local_pwr_cfg:4; /* [3:0] */
		uint32_t rsvd1:12; /* [15:4] */
		uint32_t initiate_wakeup_from_lowpwr:4; /* [19:16] */
		uint32_t rsvd0:11; /* [30:20] */
		uint32_t automatic_wakeup:1; /* [31:31] */
	};
	uint32_t val;
};

union pmu_cluster1_cpu0_status {
	struct {
		uint32_t status:4; /* [3:0] */
		uint32_t scall_feedback_o_fail:4; /* [7:4] */
		uint32_t wakeup_from_local_cfg:4; /* [11:8] */
		uint32_t status_wakeup_from_reset:1; /* [12:12] */
		uint32_t rsvd2:3; /* [15:13] */
		uint32_t states:8; /* [23:16] */
		uint32_t scall_feedback_a_fail:1; /* [24:24] */
		uint32_t scpre_feedback_fail:1; /* [25:25] */
		uint32_t rsvd1:2; /* [27:26] */
		uint32_t standbywfi:1; /* [28:28] */
		uint32_t standbywfe:1; /* [29:29] */
		uint32_t rsvd0:2; /* [31:30] */
	};
	uint32_t val;
};

union pmu_cluster1_cpu0_option {
	struct {
		uint32_t use_sc_feedback:4; /* [3:0] */
		uint32_t use_sc_counter:1; /* [4:4] */
		uint32_t use_sc_both:1; /* [5:5] */
		uint32_t use_mempwr_counter:1; /* [6:6] */
		uint32_t use_mempwr_feedback:1; /* [7:7] */
		uint32_t enable_automatic_wakeup_with_interrupt_request:1; /* [8:8] */
		uint32_t enable_gpr_cpupwrup:1; /* [9:9] */
		uint32_t use_irqcpu_for_pwrdown:1; /* [10:10] */
		uint32_t use_irqcpu_for_pwrup:1; /* [11:11] */
		uint32_t use_delayed_reset_assertion:1; /* [12:12] */
		uint32_t rsvd3:2; /* [14:13] */
		uint32_t skip_dbgpwrdwn:1; /* [15:15] */
		uint32_t use_standbywfi:1; /* [16:16] */
		uint32_t req_last_cpu:1; /* [17:17] */
		uint32_t rsvd2:2; /* [19:18] */
		uint32_t ignore_output_update_done:1; /* [20:20] */
		uint32_t rsvd1:3; /* [23:21] */
		uint32_t use_standbywfe:1; /* [24:24] */
		uint32_t clamp_emulation:1; /* [25:25] */
		uint32_t reset_emulation:1; /* [26:26] */
		uint32_t dbgpwrdwnreq_emulation:1; /* [27:27] */
		uint32_t use_smpen:1; /* [28:28] */
		uint32_t rsvd0:1; /* [29:29] */
		uint32_t enable_dbgnopwrdwn:1; /* [30:30] */
		uint32_t emulation:1; /* [31:31] */
	};
	uint32_t val;
};

union pmu_cluster1_cpu0_reset {
	struct {
		uint32_t swreset_cpuporeset:1; /* [0:0] */
		uint32_t swreset_corereset:1; /* [1:1] */
		uint32_t rsvd5:2; /* [3:2] */
		uint32_t swreset_use_standbywfi:1; /* [4:4] */
		uint32_t swreset_use_standbywfe:1; /* [5:5] */
		uint32_t rsvd4:2; /* [7:6] */
		uint32_t disable_level3_cpuporeset:1; /* [8:8] */
		uint32_t disable_level3_corereset:1; /* [9:9] */
		uint32_t disable_level2_cpuporeset:1; /* [10:10] */
		uint32_t disable_level2_corereset:1; /* [11:11] */
		uint32_t disable_level1_cpuporeset:1; /* [12:12] */
		uint32_t disable_level1_corereset:1; /* [13:13] */
		uint32_t rsvd3:1; /* [14:14] */
		uint32_t enable_gpr_reset:1; /* [15:15] */
		uint32_t rsvd2:8; /* [23:16] */
		uint32_t warmrstreq_use_standbywfi:1; /* [24:24] */
		uint32_t warmrstreq_use_standbywfe:1; /* [25:25] */
		uint32_t rsvd1:1; /* [26:26] */
		uint32_t enable_warmrstreq:1; /* [27:27] */
		uint32_t dbgrstreq_use_standbywfi:1; /* [28:28] */
		uint32_t dbgrstreq_use_standbywfe:1; /* [29:29] */
		uint32_t rsvd0:1; /* [30:30] */
		uint32_t enable_dbgrstreq:1; /* [31:31] */
	};
	uint32_t val;
};

union pmu_cluster1_cpu0_duration0 {
	struct {
		uint32_t dur_scpre_wait:4; /* [3:0] */
		uint32_t dur_scall:4; /* [7:4] */
		uint32_t dur_scpre:4; /* [11:8] */
		uint32_t dur_mempwr:4; /* [15:12] */
		uint32_t dur_chg_reset:4; /* [19:16] */
		uint32_t dur_wait_reset:4; /* [23:20] */
		uint32_t rsvd0:8; /* [31:24] */
	};
	uint32_t val;
};

union pmu_cluster1_cpu0_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_cluster1_cpu0_duration2 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_cluster1_cpu0_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_dis_irq_cluster1_cpu0_local_configuration {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_dis_irq_cluster1_cpu0_local_status {
	struct {
		uint32_t status:1; /* [0:0] */
		uint32_t rsvd1:15; /* [15:1] */
		uint32_t states:1; /* [16:16] */
		uint32_t rsvd0:15; /* [31:17] */
	};
	uint32_t val;
};

union pmu_dis_irq_cluster1_cpu0_local_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_dis_irq_cluster1_cpu0_local_duration0 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_dis_irq_cluster1_cpu0_local_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_dis_irq_cluster1_cpu0_local_duration2 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_dis_irq_cluster1_cpu0_local_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_dis_irq_cluster1_cpu0_cpusequencer_configuration {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_dis_irq_cluster1_cpu0_cpusequencer_status {
	struct {
		uint32_t status:1; /* [0:0] */
		uint32_t rsvd1:15; /* [15:1] */
		uint32_t states:1; /* [16:16] */
		uint32_t rsvd0:15; /* [31:17] */
	};
	uint32_t val;
};

union pmu_dis_irq_cluster1_cpu0_cpusequencer_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_dis_irq_cluster1_cpu0_cpusequencer_duration0 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_dis_irq_cluster1_cpu0_cpusequencer_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_dis_irq_cluster1_cpu0_cpusequencer_duration2 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_dis_irq_cluster1_cpu0_cpusequencer_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_cluster1_cpu1_configuration {
	struct {
		uint32_t local_pwr_cfg:4; /* [3:0] */
		uint32_t rsvd1:12; /* [15:4] */
		uint32_t initiate_wakeup_from_lowpwr:4; /* [19:16] */
		uint32_t rsvd0:11; /* [30:20] */
		uint32_t automatic_wakeup:1; /* [31:31] */
	};
	uint32_t val;
};

union pmu_cluster1_cpu1_status {
	struct {
		uint32_t status:4; /* [3:0] */
		uint32_t scall_feedback_o_fail:4; /* [7:4] */
		uint32_t wakeup_from_local_cfg:4; /* [11:8] */
		uint32_t status_wakeup_from_reset:1; /* [12:12] */
		uint32_t rsvd2:3; /* [15:13] */
		uint32_t states:8; /* [23:16] */
		uint32_t scall_feedback_a_fail:1; /* [24:24] */
		uint32_t scpre_feedback_fail:1; /* [25:25] */
		uint32_t rsvd1:2; /* [27:26] */
		uint32_t standbywfi:1; /* [28:28] */
		uint32_t standbywfe:1; /* [29:29] */
		uint32_t rsvd0:2; /* [31:30] */
	};
	uint32_t val;
};

union pmu_cluster1_cpu1_option {
	struct {
		uint32_t use_sc_feedback:4; /* [3:0] */
		uint32_t use_sc_counter:1; /* [4:4] */
		uint32_t use_sc_both:1; /* [5:5] */
		uint32_t use_mempwr_counter:1; /* [6:6] */
		uint32_t use_mempwr_feedback:1; /* [7:7] */
		uint32_t enable_automatic_wakeup_with_interrupt_request:1; /* [8:8] */
		uint32_t enable_gpr_cpupwrup:1; /* [9:9] */
		uint32_t use_irqcpu_for_pwrdown:1; /* [10:10] */
		uint32_t use_irqcpu_for_pwrup:1; /* [11:11] */
		uint32_t use_delayed_reset_assertion:1; /* [12:12] */
		uint32_t rsvd3:2; /* [14:13] */
		uint32_t skip_dbgpwrdwn:1; /* [15:15] */
		uint32_t use_standbywfi:1; /* [16:16] */
		uint32_t req_last_cpu:1; /* [17:17] */
		uint32_t rsvd2:2; /* [19:18] */
		uint32_t ignore_output_update_done:1; /* [20:20] */
		uint32_t rsvd1:3; /* [23:21] */
		uint32_t use_standbywfe:1; /* [24:24] */
		uint32_t clamp_emulation:1; /* [25:25] */
		uint32_t reset_emulation:1; /* [26:26] */
		uint32_t dbgpwrdwnreq_emulation:1; /* [27:27] */
		uint32_t use_smpen:1; /* [28:28] */
		uint32_t rsvd0:1; /* [29:29] */
		uint32_t enable_dbgnopwrdwn:1; /* [30:30] */
		uint32_t emulation:1; /* [31:31] */
	};
	uint32_t val;
};

union pmu_cluster1_cpu1_reset {
	struct {
		uint32_t swreset_cpuporeset:1; /* [0:0] */
		uint32_t swreset_corereset:1; /* [1:1] */
		uint32_t rsvd5:2; /* [3:2] */
		uint32_t swreset_use_standbywfi:1; /* [4:4] */
		uint32_t swreset_use_standbywfe:1; /* [5:5] */
		uint32_t rsvd4:2; /* [7:6] */
		uint32_t disable_level3_cpuporeset:1; /* [8:8] */
		uint32_t disable_level3_corereset:1; /* [9:9] */
		uint32_t disable_level2_cpuporeset:1; /* [10:10] */
		uint32_t disable_level2_corereset:1; /* [11:11] */
		uint32_t disable_level1_cpuporeset:1; /* [12:12] */
		uint32_t disable_level1_corereset:1; /* [13:13] */
		uint32_t rsvd3:1; /* [14:14] */
		uint32_t enable_gpr_reset:1; /* [15:15] */
		uint32_t rsvd2:8; /* [23:16] */
		uint32_t warmrstreq_use_standbywfi:1; /* [24:24] */
		uint32_t warmrstreq_use_standbywfe:1; /* [25:25] */
		uint32_t rsvd1:1; /* [26:26] */
		uint32_t enable_warmrstreq:1; /* [27:27] */
		uint32_t dbgrstreq_use_standbywfi:1; /* [28:28] */
		uint32_t dbgrstreq_use_standbywfe:1; /* [29:29] */
		uint32_t rsvd0:1; /* [30:30] */
		uint32_t enable_dbgrstreq:1; /* [31:31] */
	};
	uint32_t val;
};

union pmu_cluster1_cpu1_duration0 {
	struct {
		uint32_t dur_scpre_wait:4; /* [3:0] */
		uint32_t dur_scall:4; /* [7:4] */
		uint32_t dur_scpre:4; /* [11:8] */
		uint32_t dur_mempwr:4; /* [15:12] */
		uint32_t dur_chg_reset:4; /* [19:16] */
		uint32_t dur_wait_reset:4; /* [23:20] */
		uint32_t rsvd0:8; /* [31:24] */
	};
	uint32_t val;
};

union pmu_cluster1_cpu1_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_cluster1_cpu1_duration2 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_cluster1_cpu1_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_dis_irq_cluster1_cpu1_local_configuration {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_dis_irq_cluster1_cpu1_local_status {
	struct {
		uint32_t status:1; /* [0:0] */
		uint32_t rsvd1:15; /* [15:1] */
		uint32_t states:1; /* [16:16] */
		uint32_t rsvd0:15; /* [31:17] */
	};
	uint32_t val;
};

union pmu_dis_irq_cluster1_cpu1_local_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_dis_irq_cluster1_cpu1_local_duration0 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_dis_irq_cluster1_cpu1_local_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_dis_irq_cluster1_cpu1_local_duration2 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_dis_irq_cluster1_cpu1_local_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_dis_irq_cluster1_cpu1_cpusequencer_configuration {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_dis_irq_cluster1_cpu1_cpusequencer_status {
	struct {
		uint32_t status:1; /* [0:0] */
		uint32_t rsvd1:15; /* [15:1] */
		uint32_t states:1; /* [16:16] */
		uint32_t rsvd0:15; /* [31:17] */
	};
	uint32_t val;
};

union pmu_dis_irq_cluster1_cpu1_cpusequencer_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_dis_irq_cluster1_cpu1_cpusequencer_duration0 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_dis_irq_cluster1_cpu1_cpusequencer_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_dis_irq_cluster1_cpu1_cpusequencer_duration2 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_dis_irq_cluster1_cpu1_cpusequencer_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_cluster1_cpu2_configuration {
	struct {
		uint32_t local_pwr_cfg:4; /* [3:0] */
		uint32_t rsvd1:12; /* [15:4] */
		uint32_t initiate_wakeup_from_lowpwr:4; /* [19:16] */
		uint32_t rsvd0:11; /* [30:20] */
		uint32_t automatic_wakeup:1; /* [31:31] */
	};
	uint32_t val;
};

union pmu_cluster1_cpu2_status {
	struct {
		uint32_t status:4; /* [3:0] */
		uint32_t scall_feedback_o_fail:4; /* [7:4] */
		uint32_t wakeup_from_local_cfg:4; /* [11:8] */
		uint32_t status_wakeup_from_reset:1; /* [12:12] */
		uint32_t rsvd2:3; /* [15:13] */
		uint32_t states:8; /* [23:16] */
		uint32_t scall_feedback_a_fail:1; /* [24:24] */
		uint32_t scpre_feedback_fail:1; /* [25:25] */
		uint32_t rsvd1:2; /* [27:26] */
		uint32_t standbywfi:1; /* [28:28] */
		uint32_t standbywfe:1; /* [29:29] */
		uint32_t rsvd0:2; /* [31:30] */
	};
	uint32_t val;
};

union pmu_cluster1_cpu2_option {
	struct {
		uint32_t use_sc_feedback:4; /* [3:0] */
		uint32_t use_sc_counter:1; /* [4:4] */
		uint32_t use_sc_both:1; /* [5:5] */
		uint32_t use_mempwr_counter:1; /* [6:6] */
		uint32_t use_mempwr_feedback:1; /* [7:7] */
		uint32_t enable_automatic_wakeup_with_interrupt_request:1; /* [8:8] */
		uint32_t enable_gpr_cpupwrup:1; /* [9:9] */
		uint32_t use_irqcpu_for_pwrdown:1; /* [10:10] */
		uint32_t use_irqcpu_for_pwrup:1; /* [11:11] */
		uint32_t use_delayed_reset_assertion:1; /* [12:12] */
		uint32_t rsvd3:2; /* [14:13] */
		uint32_t skip_dbgpwrdwn:1; /* [15:15] */
		uint32_t use_standbywfi:1; /* [16:16] */
		uint32_t req_last_cpu:1; /* [17:17] */
		uint32_t rsvd2:2; /* [19:18] */
		uint32_t ignore_output_update_done:1; /* [20:20] */
		uint32_t rsvd1:3; /* [23:21] */
		uint32_t use_standbywfe:1; /* [24:24] */
		uint32_t clamp_emulation:1; /* [25:25] */
		uint32_t reset_emulation:1; /* [26:26] */
		uint32_t dbgpwrdwnreq_emulation:1; /* [27:27] */
		uint32_t use_smpen:1; /* [28:28] */
		uint32_t rsvd0:1; /* [29:29] */
		uint32_t enable_dbgnopwrdwn:1; /* [30:30] */
		uint32_t emulation:1; /* [31:31] */
	};
	uint32_t val;
};

union pmu_cluster1_cpu2_reset {
	struct {
		uint32_t swreset_cpuporeset:1; /* [0:0] */
		uint32_t swreset_corereset:1; /* [1:1] */
		uint32_t rsvd5:2; /* [3:2] */
		uint32_t swreset_use_standbywfi:1; /* [4:4] */
		uint32_t swreset_use_standbywfe:1; /* [5:5] */
		uint32_t rsvd4:2; /* [7:6] */
		uint32_t disable_level3_cpuporeset:1; /* [8:8] */
		uint32_t disable_level3_corereset:1; /* [9:9] */
		uint32_t disable_level2_cpuporeset:1; /* [10:10] */
		uint32_t disable_level2_corereset:1; /* [11:11] */
		uint32_t disable_level1_cpuporeset:1; /* [12:12] */
		uint32_t disable_level1_corereset:1; /* [13:13] */
		uint32_t rsvd3:1; /* [14:14] */
		uint32_t enable_gpr_reset:1; /* [15:15] */
		uint32_t rsvd2:8; /* [23:16] */
		uint32_t warmrstreq_use_standbywfi:1; /* [24:24] */
		uint32_t warmrstreq_use_standbywfe:1; /* [25:25] */
		uint32_t rsvd1:1; /* [26:26] */
		uint32_t enable_warmrstreq:1; /* [27:27] */
		uint32_t dbgrstreq_use_standbywfi:1; /* [28:28] */
		uint32_t dbgrstreq_use_standbywfe:1; /* [29:29] */
		uint32_t rsvd0:1; /* [30:30] */
		uint32_t enable_dbgrstreq:1; /* [31:31] */
	};
	uint32_t val;
};

union pmu_cluster1_cpu2_duration0 {
	struct {
		uint32_t dur_scpre_wait:4; /* [3:0] */
		uint32_t dur_scall:4; /* [7:4] */
		uint32_t dur_scpre:4; /* [11:8] */
		uint32_t dur_mempwr:4; /* [15:12] */
		uint32_t dur_chg_reset:4; /* [19:16] */
		uint32_t dur_wait_reset:4; /* [23:20] */
		uint32_t rsvd0:8; /* [31:24] */
	};
	uint32_t val;
};

union pmu_cluster1_cpu2_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_cluster1_cpu2_duration2 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_cluster1_cpu2_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_dis_irq_cluster1_cpu2_local_configuration {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_dis_irq_cluster1_cpu2_local_status {
	struct {
		uint32_t status:1; /* [0:0] */
		uint32_t rsvd1:15; /* [15:1] */
		uint32_t states:1; /* [16:16] */
		uint32_t rsvd0:15; /* [31:17] */
	};
	uint32_t val;
};

union pmu_dis_irq_cluster1_cpu2_local_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_dis_irq_cluster1_cpu2_local_duration0 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_dis_irq_cluster1_cpu2_local_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_dis_irq_cluster1_cpu2_local_duration2 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_dis_irq_cluster1_cpu2_local_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_dis_irq_cluster1_cpu2_cpusequencer_configuration {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_dis_irq_cluster1_cpu2_cpusequencer_status {
	struct {
		uint32_t status:1; /* [0:0] */
		uint32_t rsvd1:15; /* [15:1] */
		uint32_t states:1; /* [16:16] */
		uint32_t rsvd0:15; /* [31:17] */
	};
	uint32_t val;
};

union pmu_dis_irq_cluster1_cpu2_cpusequencer_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_dis_irq_cluster1_cpu2_cpusequencer_duration0 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_dis_irq_cluster1_cpu2_cpusequencer_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_dis_irq_cluster1_cpu2_cpusequencer_duration2 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_dis_irq_cluster1_cpu2_cpusequencer_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_cluster1_cpu3_configuration {
	struct {
		uint32_t local_pwr_cfg:4; /* [3:0] */
		uint32_t rsvd1:12; /* [15:4] */
		uint32_t initiate_wakeup_from_lowpwr:4; /* [19:16] */
		uint32_t rsvd0:11; /* [30:20] */
		uint32_t automatic_wakeup:1; /* [31:31] */
	};
	uint32_t val;
};

union pmu_cluster1_cpu3_status {
	struct {
		uint32_t status:4; /* [3:0] */
		uint32_t scall_feedback_o_fail:4; /* [7:4] */
		uint32_t wakeup_from_local_cfg:4; /* [11:8] */
		uint32_t status_wakeup_from_reset:1; /* [12:12] */
		uint32_t rsvd2:3; /* [15:13] */
		uint32_t states:8; /* [23:16] */
		uint32_t scall_feedback_a_fail:1; /* [24:24] */
		uint32_t scpre_feedback_fail:1; /* [25:25] */
		uint32_t rsvd1:2; /* [27:26] */
		uint32_t standbywfi:1; /* [28:28] */
		uint32_t standbywfe:1; /* [29:29] */
		uint32_t rsvd0:2; /* [31:30] */
	};
	uint32_t val;
};

union pmu_cluster1_cpu3_option {
	struct {
		uint32_t use_sc_feedback:4; /* [3:0] */
		uint32_t use_sc_counter:1; /* [4:4] */
		uint32_t use_sc_both:1; /* [5:5] */
		uint32_t use_mempwr_counter:1; /* [6:6] */
		uint32_t use_mempwr_feedback:1; /* [7:7] */
		uint32_t enable_automatic_wakeup_with_interrupt_request:1; /* [8:8] */
		uint32_t enable_gpr_cpupwrup:1; /* [9:9] */
		uint32_t use_irqcpu_for_pwrdown:1; /* [10:10] */
		uint32_t use_irqcpu_for_pwrup:1; /* [11:11] */
		uint32_t use_delayed_reset_assertion:1; /* [12:12] */
		uint32_t rsvd3:2; /* [14:13] */
		uint32_t skip_dbgpwrdwn:1; /* [15:15] */
		uint32_t use_standbywfi:1; /* [16:16] */
		uint32_t req_last_cpu:1; /* [17:17] */
		uint32_t rsvd2:2; /* [19:18] */
		uint32_t ignore_output_update_done:1; /* [20:20] */
		uint32_t rsvd1:3; /* [23:21] */
		uint32_t use_standbywfe:1; /* [24:24] */
		uint32_t clamp_emulation:1; /* [25:25] */
		uint32_t reset_emulation:1; /* [26:26] */
		uint32_t dbgpwrdwnreq_emulation:1; /* [27:27] */
		uint32_t use_smpen:1; /* [28:28] */
		uint32_t rsvd0:1; /* [29:29] */
		uint32_t enable_dbgnopwrdwn:1; /* [30:30] */
		uint32_t emulation:1; /* [31:31] */
	};
	uint32_t val;
};

union pmu_cluster1_cpu3_reset {
	struct {
		uint32_t swreset_cpuporeset:1; /* [0:0] */
		uint32_t swreset_corereset:1; /* [1:1] */
		uint32_t rsvd5:2; /* [3:2] */
		uint32_t swreset_use_standbywfi:1; /* [4:4] */
		uint32_t swreset_use_standbywfe:1; /* [5:5] */
		uint32_t rsvd4:2; /* [7:6] */
		uint32_t disable_level3_cpuporeset:1; /* [8:8] */
		uint32_t disable_level3_corereset:1; /* [9:9] */
		uint32_t disable_level2_cpuporeset:1; /* [10:10] */
		uint32_t disable_level2_corereset:1; /* [11:11] */
		uint32_t disable_level1_cpuporeset:1; /* [12:12] */
		uint32_t disable_level1_corereset:1; /* [13:13] */
		uint32_t rsvd3:1; /* [14:14] */
		uint32_t enable_gpr_reset:1; /* [15:15] */
		uint32_t rsvd2:8; /* [23:16] */
		uint32_t warmrstreq_use_standbywfi:1; /* [24:24] */
		uint32_t warmrstreq_use_standbywfe:1; /* [25:25] */
		uint32_t rsvd1:1; /* [26:26] */
		uint32_t enable_warmrstreq:1; /* [27:27] */
		uint32_t dbgrstreq_use_standbywfi:1; /* [28:28] */
		uint32_t dbgrstreq_use_standbywfe:1; /* [29:29] */
		uint32_t rsvd0:1; /* [30:30] */
		uint32_t enable_dbgrstreq:1; /* [31:31] */
	};
	uint32_t val;
};

union pmu_cluster1_cpu3_duration0 {
	struct {
		uint32_t dur_scpre_wait:4; /* [3:0] */
		uint32_t dur_scall:4; /* [7:4] */
		uint32_t dur_scpre:4; /* [11:8] */
		uint32_t dur_mempwr:4; /* [15:12] */
		uint32_t dur_chg_reset:4; /* [19:16] */
		uint32_t dur_wait_reset:4; /* [23:20] */
		uint32_t rsvd0:8; /* [31:24] */
	};
	uint32_t val;
};

union pmu_cluster1_cpu3_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_cluster1_cpu3_duration2 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_cluster1_cpu3_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_dis_irq_cluster1_cpu3_local_configuration {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_dis_irq_cluster1_cpu3_local_status {
	struct {
		uint32_t status:1; /* [0:0] */
		uint32_t rsvd1:15; /* [15:1] */
		uint32_t states:1; /* [16:16] */
		uint32_t rsvd0:15; /* [31:17] */
	};
	uint32_t val;
};

union pmu_dis_irq_cluster1_cpu3_local_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_dis_irq_cluster1_cpu3_local_duration0 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_dis_irq_cluster1_cpu3_local_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_dis_irq_cluster1_cpu3_local_duration2 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_dis_irq_cluster1_cpu3_local_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_dis_irq_cluster1_cpu3_cpusequencer_configuration {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_dis_irq_cluster1_cpu3_cpusequencer_status {
	struct {
		uint32_t status:1; /* [0:0] */
		uint32_t rsvd1:15; /* [15:1] */
		uint32_t states:1; /* [16:16] */
		uint32_t rsvd0:15; /* [31:17] */
	};
	uint32_t val;
};

union pmu_dis_irq_cluster1_cpu3_cpusequencer_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_dis_irq_cluster1_cpu3_cpusequencer_duration0 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_dis_irq_cluster1_cpu3_cpusequencer_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_dis_irq_cluster1_cpu3_cpusequencer_duration2 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_dis_irq_cluster1_cpu3_cpusequencer_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_cluster0_noncpu_configuration {
	struct {
		uint32_t local_pwr_cfg:4; /* [3:0] */
		uint32_t rsvd2:4; /* [7:4] */
		uint32_t local_pwr_cfg1:4; /* [11:8] */
		uint32_t rsvd1:4; /* [15:12] */
		uint32_t initiate_wakeup_from_lowpwr:4; /* [19:16] */
		uint32_t rsvd0:12; /* [31:20] */
	};
	uint32_t val;
};

union pmu_cluster0_noncpu_status {
	struct {
		uint32_t status:4; /* [3:0] */
		uint32_t scall_feedback_o_fail:4; /* [7:4] */
		uint32_t scall_feedback_a_fail:1; /* [8:8] */
		uint32_t scpre_feedback_fail:1; /* [9:9] */
		uint32_t rsvd1:6; /* [15:10] */
		uint32_t states:12; /* [27:16] */
		uint32_t rsvd0:4; /* [31:28] */
	};
	uint32_t val;
};

union pmu_cluster0_noncpu_option {
	struct {
		uint32_t rsvd3:3; /* [2:0] */
		uint32_t use_l2retention:1; /* [3:3] */
		uint32_t skip_otp_shifting_done:1; /* [4:4] */
		uint32_t use_retn_bisr:1; /* [5:5] */
		uint32_t use_single_state_reset_clamp:1; /* [6:6] */
		uint32_t enable_crpportpwrdn_based_sci_reset:1; /* [7:7] */
		uint32_t use_sc_feedback:4; /* [11:8] */
		uint32_t use_sc_counter:1; /* [12:12] */
		uint32_t use_sc_both:1; /* [13:13] */
		uint32_t rsvd2:6; /* [19:14] */
		uint32_t ignore_output_update_done:1; /* [20:20] */
		uint32_t rsvd1:3; /* [23:21] */
		uint32_t l2pwr_emulation:1; /* [24:24] */
		uint32_t clamp_emulation:1; /* [25:25] */
		uint32_t reset_emulation:1; /* [26:26] */
		uint32_t rsvd0:4; /* [30:27] */
		uint32_t emulation:1; /* [31:31] */
	};
	uint32_t val;
};

union pmu_cluster0_noncpu_reset {
	struct {
		uint32_t swreset_l2reset:1; /* [0:0] */
		uint32_t swreset_mbistreset:1; /* [1:1] */
		uint32_t swreset_presetdbg:1; /* [2:2] */
		uint32_t rsvd2:12; /* [14:3] */
		uint32_t enable_gpr_reset:1; /* [15:15] */
		uint32_t disable_l2reset:1; /* [16:16] */
		uint32_t disable_mbistreset:1; /* [17:17] */
		uint32_t disable_presetdbg:1; /* [18:18] */
		uint32_t rsvd1:5; /* [23:19] */
		uint32_t dbgl1rstdisable:1; /* [24:24] */
		uint32_t rsvd0:1; /* [25:25] */
		uint32_t disable_level3_presetdbg:1; /* [26:26] */
		uint32_t disable_level3_l2reset:1; /* [27:27] */
		uint32_t disable_level2_presetdbg:1; /* [28:28] */
		uint32_t disable_level2_l2reset:1; /* [29:29] */
		uint32_t disable_level1_presetdbg:1; /* [30:30] */
		uint32_t disable_level1_l2reset:1; /* [31:31] */
	};
	uint32_t val;
};

union pmu_cluster0_noncpu_duration0 {
	struct {
		uint32_t dur_scpre_wait:4; /* [3:0] */
		uint32_t dur_scall:4; /* [7:4] */
		uint32_t dur_scpre:4; /* [11:8] */
		uint32_t rsvd1:4; /* [15:12] */
		uint32_t dur_chg_reset:4; /* [19:16] */
		uint32_t dur_wait_reset:4; /* [23:20] */
		uint32_t rsvd0:8; /* [31:24] */
	};
	uint32_t val;
};

union pmu_cluster0_noncpu_duration1 {
	struct {
		uint32_t dur_l2pwr:4; /* [3:0] */
		uint32_t dur_clamp:4; /* [7:4] */
		uint32_t rsvd0:24; /* [31:8] */
	};
	uint32_t val;
};

union pmu_cluster0_noncpu_duration2 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_cluster0_noncpu_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_cluster1_noncpu_configuration {
	struct {
		uint32_t local_pwr_cfg:4; /* [3:0] */
		uint32_t rsvd2:4; /* [7:4] */
		uint32_t local_pwr_cfg1:4; /* [11:8] */
		uint32_t rsvd1:4; /* [15:12] */
		uint32_t initiate_wakeup_from_lowpwr:4; /* [19:16] */
		uint32_t rsvd0:12; /* [31:20] */
	};
	uint32_t val;
};

union pmu_cluster1_noncpu_status {
	struct {
		uint32_t status:4; /* [3:0] */
		uint32_t scall_feedback_o_fail:4; /* [7:4] */
		uint32_t scall_feedback_a_fail:1; /* [8:8] */
		uint32_t scpre_feedback_fail:1; /* [9:9] */
		uint32_t rsvd1:6; /* [15:10] */
		uint32_t states:12; /* [27:16] */
		uint32_t rsvd0:4; /* [31:28] */
	};
	uint32_t val;
};

union pmu_cluster1_noncpu_option {
	struct {
		uint32_t rsvd3:3; /* [2:0] */
		uint32_t use_l2retention:1; /* [3:3] */
		uint32_t skip_otp_shifting_done:1; /* [4:4] */
		uint32_t use_retn_bisr:1; /* [5:5] */
		uint32_t use_single_state_reset_clamp:1; /* [6:6] */
		uint32_t enable_crpportpwrdn_based_sci_reset:1; /* [7:7] */
		uint32_t use_sc_feedback:4; /* [11:8] */
		uint32_t use_sc_counter:1; /* [12:12] */
		uint32_t use_sc_both:1; /* [13:13] */
		uint32_t rsvd2:6; /* [19:14] */
		uint32_t ignore_output_update_done:1; /* [20:20] */
		uint32_t rsvd1:3; /* [23:21] */
		uint32_t l2pwr_emulation:1; /* [24:24] */
		uint32_t clamp_emulation:1; /* [25:25] */
		uint32_t reset_emulation:1; /* [26:26] */
		uint32_t rsvd0:4; /* [30:27] */
		uint32_t emulation:1; /* [31:31] */
	};
	uint32_t val;
};

union pmu_cluster1_noncpu_reset {
	struct {
		uint32_t swreset_l2reset:1; /* [0:0] */
		uint32_t swreset_mbistreset:1; /* [1:1] */
		uint32_t swreset_presetdbg:1; /* [2:2] */
		uint32_t rsvd2:12; /* [14:3] */
		uint32_t enable_gpr_reset:1; /* [15:15] */
		uint32_t disable_l2reset:1; /* [16:16] */
		uint32_t disable_mbistreset:1; /* [17:17] */
		uint32_t disable_presetdbg:1; /* [18:18] */
		uint32_t rsvd1:5; /* [23:19] */
		uint32_t dbgl1rstdisable:1; /* [24:24] */
		uint32_t rsvd0:1; /* [25:25] */
		uint32_t disable_level3_presetdbg:1; /* [26:26] */
		uint32_t disable_level3_l2reset:1; /* [27:27] */
		uint32_t disable_level2_presetdbg:1; /* [28:28] */
		uint32_t disable_level2_l2reset:1; /* [29:29] */
		uint32_t disable_level1_presetdbg:1; /* [30:30] */
		uint32_t disable_level1_l2reset:1; /* [31:31] */
	};
	uint32_t val;
};

union pmu_cluster1_noncpu_duration0 {
	struct {
		uint32_t dur_scpre_wait:4; /* [3:0] */
		uint32_t dur_scall:4; /* [7:4] */
		uint32_t dur_scpre:4; /* [11:8] */
		uint32_t rsvd1:4; /* [15:12] */
		uint32_t dur_chg_reset:4; /* [19:16] */
		uint32_t dur_wait_reset:4; /* [23:20] */
		uint32_t rsvd0:8; /* [31:24] */
	};
	uint32_t val;
};

union pmu_cluster1_noncpu_duration1 {
	struct {
		uint32_t dur_l2pwr:4; /* [3:0] */
		uint32_t dur_clamp:4; /* [7:4] */
		uint32_t rsvd0:24; /* [31:8] */
	};
	uint32_t val;
};

union pmu_cluster1_noncpu_duration2 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_cluster1_noncpu_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_cluster0_cpusequencer_configuration {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_cluster0_cpusequencer_status {
	struct {
		uint32_t status:1; /* [0:0] */
		uint32_t rsvd1:15; /* [15:1] */
		uint32_t states:4; /* [19:16] */
		uint32_t rsvd0:12; /* [31:20] */
	};
	uint32_t val;
};

union pmu_cluster0_cpusequencer_option {
	struct {
		uint32_t use_automatic_pwrctrl:1; /* [0:0] */
		uint32_t clear_automatic_pwrctrl:1; /* [1:1] */
		uint32_t rsvd3:2; /* [3:2] */
		uint32_t initiate_wakeup_from_lowpwr:1; /* [4:4] */
		uint32_t rsvd2:4; /* [8:5] */
		uint32_t enable_gpr_cpupwrup:1; /* [9:9] */
		uint32_t rsvd1:6; /* [15:10] */
		uint32_t use_irqcpu_for_pwrdown:1; /* [16:16] */
		uint32_t use_irqcpu_for_pwrup:1; /* [17:17] */
		uint32_t rsvd0:14; /* [31:18] */
	};
	uint32_t val;
};

union pmu_cluster0_cpusequencer_reset {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_cluster0_cpusequencer_duration0 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_cluster0_cpusequencer_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_cluster0_cpusequencer_duration2 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_cluster0_cpusequencer_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_cluster1_cpusequencer_configuration {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_cluster1_cpusequencer_status {
	struct {
		uint32_t status:1; /* [0:0] */
		uint32_t rsvd1:15; /* [15:1] */
		uint32_t states:4; /* [19:16] */
		uint32_t rsvd0:12; /* [31:20] */
	};
	uint32_t val;
};

union pmu_cluster1_cpusequencer_option {
	struct {
		uint32_t use_automatic_pwrctrl:1; /* [0:0] */
		uint32_t clear_automatic_pwrctrl:1; /* [1:1] */
		uint32_t rsvd3:2; /* [3:2] */
		uint32_t initiate_wakeup_from_lowpwr:1; /* [4:4] */
		uint32_t rsvd2:4; /* [8:5] */
		uint32_t enable_gpr_cpupwrup:1; /* [9:9] */
		uint32_t rsvd1:6; /* [15:10] */
		uint32_t use_irqcpu_for_pwrdown:1; /* [16:16] */
		uint32_t use_irqcpu_for_pwrup:1; /* [17:17] */
		uint32_t rsvd0:14; /* [31:18] */
	};
	uint32_t val;
};

union pmu_cluster1_cpusequencer_reset {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_cluster1_cpusequencer_duration0 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_cluster1_cpusequencer_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_cluster1_cpusequencer_duration2 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_cluster1_cpusequencer_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_cluster0_l2_configuration {
	struct {
		uint32_t local_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd1:7; /* [7:1] */
		uint32_t local_pwr_cfg1:1; /* [8:8] */
		uint32_t rsvd0:23; /* [31:9] */
	};
	uint32_t val;
};

union pmu_cluster0_l2_status {
	struct {
		uint32_t status:1; /* [0:0] */
		uint32_t rsvd2:15; /* [15:1] */
		uint32_t states:4; /* [19:16] */
		uint32_t rsvd1:8; /* [27:20] */
		uint32_t standbywfil2:1; /* [28:28] */
		uint32_t rsvd0:3; /* [31:29] */
	};
	uint32_t val;
};

union pmu_cluster0_l2_option {
	struct {
		uint32_t manual_ainacts_control:1; /* [0:0] */
		uint32_t manual_ainacts_value:1; /* [1:1] */
		uint32_t manual_acinactm_control:1; /* [2:2] */
		uint32_t manual_acinactm_value:1; /* [3:3] */
		uint32_t automatic_l2rstdisable_value:1; /* [4:4] */
		uint32_t rsvd3:3; /* [7:5] */
		uint32_t manual_l2rstdisable_control:1; /* [8:8] */
		uint32_t manual_l2rstdisable_value:1; /* [9:9] */
		uint32_t rsvd2:6; /* [15:10] */
		uint32_t use_standbywfil2:1; /* [16:16] */
		uint32_t use_automatic_l2flushreq:1; /* [17:17] */
		uint32_t rsvd1:2; /* [19:18] */
		uint32_t ignore_output_update_done:1; /* [20:20] */
		uint32_t rsvd0:11; /* [31:21] */
	};
	uint32_t val;
};

union pmu_cluster0_l2_duration0 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_cluster0_l2_duration1 {
	struct {
		uint32_t rsvd1:4; /* [3:0] */
		uint32_t dur_l2rstdisable:4; /* [7:4] */
		uint32_t rsvd0:24; /* [31:8] */
	};
	uint32_t val;
};

union pmu_cluster0_l2_duration2 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_cluster0_l2_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_cluster1_l2_configuration {
	struct {
		uint32_t local_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd1:7; /* [7:1] */
		uint32_t local_pwr_cfg1:1; /* [8:8] */
		uint32_t rsvd0:23; /* [31:9] */
	};
	uint32_t val;
};

union pmu_cluster1_l2_status {
	struct {
		uint32_t status:1; /* [0:0] */
		uint32_t rsvd2:15; /* [15:1] */
		uint32_t states:4; /* [19:16] */
		uint32_t rsvd1:8; /* [27:20] */
		uint32_t standbywfil2:1; /* [28:28] */
		uint32_t rsvd0:3; /* [31:29] */
	};
	uint32_t val;
};

union pmu_cluster1_l2_option {
	struct {
		uint32_t manual_ainacts_control:1; /* [0:0] */
		uint32_t manual_ainacts_value:1; /* [1:1] */
		uint32_t manual_acinactm_control:1; /* [2:2] */
		uint32_t manual_acinactm_value:1; /* [3:3] */
		uint32_t automatic_l2rstdisable_value:1; /* [4:4] */
		uint32_t rsvd3:3; /* [7:5] */
		uint32_t manual_l2rstdisable_control:1; /* [8:8] */
		uint32_t manual_l2rstdisable_value:1; /* [9:9] */
		uint32_t rsvd2:6; /* [15:10] */
		uint32_t use_standbywfil2:1; /* [16:16] */
		uint32_t use_automatic_l2flushreq:1; /* [17:17] */
		uint32_t rsvd1:2; /* [19:18] */
		uint32_t ignore_output_update_done:1; /* [20:20] */
		uint32_t rsvd0:11; /* [31:21] */
	};
	uint32_t val;
};

union pmu_cluster1_l2_duration0 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_cluster1_l2_duration1 {
	struct {
		uint32_t rsvd1:4; /* [3:0] */
		uint32_t dur_l2rstdisable:4; /* [7:4] */
		uint32_t rsvd0:24; /* [31:8] */
	};
	uint32_t val;
};

union pmu_cluster1_l2_duration2 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_cluster1_l2_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_reset_cpuclkstop0_configuration {
	struct {
		uint32_t local_pwr_cfg:2; /* [1:0] */
		uint32_t rsvd0:30; /* [31:2] */
	};
	uint32_t val;
};

union pmu_reset_cpuclkstop0_status {
	struct {
		uint32_t status:2; /* [1:0] */
		uint32_t rsvd1:14; /* [15:2] */
		uint32_t states:4; /* [19:16] */
		uint32_t rsvd0:12; /* [31:20] */
	};
	uint32_t val;
};

union pmu_reset_cpuclkstop0_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_reset_cpuclkstop0_duration0 {
	struct {
		uint32_t rsvd1:16; /* [15:0] */
		uint32_t dur_chg_reset:4; /* [19:16] */
		uint32_t dur_wait_reset:4; /* [23:20] */
		uint32_t rsvd0:8; /* [31:24] */
	};
	uint32_t val;
};

union pmu_reset_cpuclkstop0_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_reset_cpuclkstop0_duration2 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_reset_cpuclkstop0_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_reset_cpuclkstop1_configuration {
	struct {
		uint32_t local_pwr_cfg:2; /* [1:0] */
		uint32_t rsvd0:30; /* [31:2] */
	};
	uint32_t val;
};

union pmu_reset_cpuclkstop1_status {
	struct {
		uint32_t status:2; /* [1:0] */
		uint32_t rsvd1:14; /* [15:2] */
		uint32_t states:4; /* [19:16] */
		uint32_t rsvd0:12; /* [31:20] */
	};
	uint32_t val;
};

union pmu_reset_cpuclkstop1_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_reset_cpuclkstop1_duration0 {
	struct {
		uint32_t rsvd1:16; /* [15:0] */
		uint32_t dur_chg_reset:4; /* [19:16] */
		uint32_t dur_wait_reset:4; /* [23:20] */
		uint32_t rsvd0:8; /* [31:24] */
	};
	uint32_t val;
};

union pmu_reset_cpuclkstop1_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_reset_cpuclkstop1_duration2 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_reset_cpuclkstop1_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_rot_poresetn_configuration {
	struct {
		uint32_t local_pwr_cfg:2; /* [1:0] */
		uint32_t rsvd0:30; /* [31:2] */
	};
	uint32_t val;
};

union pmu_rot_poresetn_status {
	struct {
		uint32_t status:2; /* [1:0] */
		uint32_t rsvd1:14; /* [15:2] */
		uint32_t states:4; /* [19:16] */
		uint32_t rsvd0:12; /* [31:20] */
	};
	uint32_t val;
};

union pmu_rot_poresetn_reset {
	struct {
		uint32_t swreset_poresetn:1; /* [0:0] */
		uint32_t rsvd1:3; /* [3:1] */
		uint32_t disable_level3_cmrt_poresetn:1; /* [4:4] */
		uint32_t disable_level2_cmrt_poresetn:1; /* [5:5] */
		uint32_t disable_level1_cmrt_poresetn:1; /* [6:6] */
		uint32_t rsvd0:25; /* [31:7] */
	};
	uint32_t val;
};

union pmu_rot_poresetn_duration0 {
	struct {
		uint32_t rsvd1:16; /* [15:0] */
		uint32_t dur_chg_reset:4; /* [19:16] */
		uint32_t dur_wait_reset:4; /* [23:20] */
		uint32_t rsvd0:8; /* [31:24] */
	};
	uint32_t val;
};

union pmu_rot_poresetn_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_rot_poresetn_duration2 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_rot_poresetn_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_rot_hresetn_configuration {
	struct {
		uint32_t local_pwr_cfg:2; /* [1:0] */
		uint32_t rsvd0:30; /* [31:2] */
	};
	uint32_t val;
};

union pmu_rot_hresetn_status {
	struct {
		uint32_t status:2; /* [1:0] */
		uint32_t rsvd1:14; /* [15:2] */
		uint32_t states:4; /* [19:16] */
		uint32_t rsvd0:12; /* [31:20] */
	};
	uint32_t val;
};

union pmu_rot_hresetn_reset {
	struct {
		uint32_t swreset_hresetn:1; /* [0:0] */
		uint32_t rsvd1:3; /* [3:1] */
		uint32_t disable_level3_cmrt_hresetn:1; /* [4:4] */
		uint32_t disable_level2_cmrt_hresetn:1; /* [5:5] */
		uint32_t disable_level1_cmrt_hresetn:1; /* [6:6] */
		uint32_t rsvd0:25; /* [31:7] */
	};
	uint32_t val;
};

union pmu_rot_hresetn_duration0 {
	struct {
		uint32_t rsvd1:16; /* [15:0] */
		uint32_t dur_chg_reset:4; /* [19:16] */
		uint32_t dur_wait_reset:4; /* [23:20] */
		uint32_t rsvd0:8; /* [31:24] */
	};
	uint32_t val;
};

union pmu_rot_hresetn_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_rot_hresetn_duration2 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_rot_hresetn_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_oscclk_gate_configuration {
	struct {
		uint32_t local_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_oscclk_gate_status {
	struct {
		uint32_t status:1; /* [0:0] */
		uint32_t rsvd1:15; /* [15:1] */
		uint32_t states:1; /* [16:16] */
		uint32_t rsvd0:15; /* [31:17] */
	};
	uint32_t val;
};

union pmu_oscclk_gate_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_oscclk_gate_duration0 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_oscclk_gate_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_oscclk_gate_duration2 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_oscclk_gate_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_ext_regulator_configuration {
	struct {
		uint32_t local_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_ext_regulator_status {
	struct {
		uint32_t status:1; /* [0:0] */
		uint32_t rsvd1:15; /* [15:1] */
		uint32_t states:4; /* [19:16] */
		uint32_t rsvd0:12; /* [31:20] */
	};
	uint32_t val;
};

union pmu_ext_regulator_option {
	struct {
		uint32_t rsvd0:31; /* [30:0] */
		uint32_t emulation:1; /* [31:31] */
	};
	uint32_t val;
};

union pmu_ext_regulator_duration0 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_ext_regulator_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_ext_regulator_duration2 {
	struct {
		uint32_t dur_iso:4; /* [3:0] */
		uint32_t dur_down:4; /* [7:4] */
		uint32_t rsvd0:24; /* [31:8] */
	};
	uint32_t val;
};

union pmu_ext_regulator_duration3 {
	struct {
		uint32_t dur_stable:20; /* [19:0] */
		uint32_t rsvd0:12; /* [31:20] */
	};
	uint32_t val;
};

union pmu_clkstop_open_cmu_cp0_configuration {
	struct {
		uint32_t local_pwr_cfg:2; /* [1:0] */
		uint32_t rsvd0:30; /* [31:2] */
	};
	uint32_t val;
};

union pmu_clkstop_open_cmu_cp0_status {
	struct {
		uint32_t status:2; /* [1:0] */
		uint32_t rsvd1:14; /* [15:2] */
		uint32_t states:4; /* [19:16] */
		uint32_t rsvd0:12; /* [31:20] */
	};
	uint32_t val;
};

union pmu_clkstop_open_cmu_cp0_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_clkstop_open_cmu_cp0_duration0 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_clkstop_open_cmu_cp0_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_clkstop_open_cmu_cp0_duration2 {
	struct {
		uint32_t rsvd1:16; /* [15:0] */
		uint32_t dur_wait:4; /* [19:16] */
		uint32_t rsvd0:12; /* [31:20] */
	};
	uint32_t val;
};

union pmu_clkstop_open_cmu_cp0_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_clkstop_open_cmu_cp1_configuration {
	struct {
		uint32_t local_pwr_cfg:2; /* [1:0] */
		uint32_t rsvd0:30; /* [31:2] */
	};
	uint32_t val;
};

union pmu_clkstop_open_cmu_cp1_status {
	struct {
		uint32_t status:2; /* [1:0] */
		uint32_t rsvd1:14; /* [15:2] */
		uint32_t states:4; /* [19:16] */
		uint32_t rsvd0:12; /* [31:20] */
	};
	uint32_t val;
};

union pmu_clkstop_open_cmu_cp1_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_clkstop_open_cmu_cp1_duration0 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_clkstop_open_cmu_cp1_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_clkstop_open_cmu_cp1_duration2 {
	struct {
		uint32_t rsvd1:16; /* [15:0] */
		uint32_t dur_wait:4; /* [19:16] */
		uint32_t rsvd0:12; /* [31:20] */
	};
	uint32_t val;
};

union pmu_clkstop_open_cmu_cp1_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_clkstop_open_cmu_pcie_configuration {
	struct {
		uint32_t local_pwr_cfg:2; /* [1:0] */
		uint32_t rsvd0:30; /* [31:2] */
	};
	uint32_t val;
};

union pmu_clkstop_open_cmu_pcie_status {
	struct {
		uint32_t status:2; /* [1:0] */
		uint32_t rsvd1:14; /* [15:2] */
		uint32_t states:4; /* [19:16] */
		uint32_t rsvd0:12; /* [31:20] */
	};
	uint32_t val;
};

union pmu_clkstop_open_cmu_pcie_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_clkstop_open_cmu_pcie_duration0 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_clkstop_open_cmu_pcie_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_clkstop_open_cmu_pcie_duration2 {
	struct {
		uint32_t rsvd1:16; /* [15:0] */
		uint32_t dur_wait:4; /* [19:16] */
		uint32_t rsvd0:12; /* [31:20] */
	};
	uint32_t val;
};

union pmu_clkstop_open_cmu_pcie_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_clkstop_open_cmu_dram_configuration {
	struct {
		uint32_t local_pwr_cfg:2; /* [1:0] */
		uint32_t rsvd0:30; /* [31:2] */
	};
	uint32_t val;
};

union pmu_clkstop_open_cmu_dram_status {
	struct {
		uint32_t status:2; /* [1:0] */
		uint32_t rsvd1:14; /* [15:2] */
		uint32_t states:4; /* [19:16] */
		uint32_t rsvd0:12; /* [31:20] */
	};
	uint32_t val;
};

union pmu_clkstop_open_cmu_dram_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_clkstop_open_cmu_dram_duration0 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_clkstop_open_cmu_dram_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_clkstop_open_cmu_dram_duration2 {
	struct {
		uint32_t rsvd1:16; /* [15:0] */
		uint32_t dur_wait:4; /* [19:16] */
		uint32_t rsvd0:12; /* [31:20] */
	};
	uint32_t val;
};

union pmu_clkstop_open_cmu_dram_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_clkstop_open_cmu_dcl0_configuration {
	struct {
		uint32_t local_pwr_cfg:2; /* [1:0] */
		uint32_t rsvd0:30; /* [31:2] */
	};
	uint32_t val;
};

union pmu_clkstop_open_cmu_dcl0_status {
	struct {
		uint32_t status:2; /* [1:0] */
		uint32_t rsvd1:14; /* [15:2] */
		uint32_t states:4; /* [19:16] */
		uint32_t rsvd0:12; /* [31:20] */
	};
	uint32_t val;
};

union pmu_clkstop_open_cmu_dcl0_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_clkstop_open_cmu_dcl0_duration0 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_clkstop_open_cmu_dcl0_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_clkstop_open_cmu_dcl0_duration2 {
	struct {
		uint32_t rsvd1:16; /* [15:0] */
		uint32_t dur_wait:4; /* [19:16] */
		uint32_t rsvd0:12; /* [31:20] */
	};
	uint32_t val;
};

union pmu_clkstop_open_cmu_dcl0_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_clkstop_open_cmu_dcl1_configuration {
	struct {
		uint32_t local_pwr_cfg:2; /* [1:0] */
		uint32_t rsvd0:30; /* [31:2] */
	};
	uint32_t val;
};

union pmu_clkstop_open_cmu_dcl1_status {
	struct {
		uint32_t status:2; /* [1:0] */
		uint32_t rsvd1:14; /* [15:2] */
		uint32_t states:4; /* [19:16] */
		uint32_t rsvd0:12; /* [31:20] */
	};
	uint32_t val;
};

union pmu_clkstop_open_cmu_dcl1_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_clkstop_open_cmu_dcl1_duration0 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_clkstop_open_cmu_dcl1_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_clkstop_open_cmu_dcl1_duration2 {
	struct {
		uint32_t rsvd1:16; /* [15:0] */
		uint32_t dur_wait:4; /* [19:16] */
		uint32_t rsvd0:12; /* [31:20] */
	};
	uint32_t val;
};

union pmu_clkstop_open_cmu_dcl1_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_clkstop_open_cmu_rbch00_configuration {
	struct {
		uint32_t local_pwr_cfg:2; /* [1:0] */
		uint32_t rsvd0:30; /* [31:2] */
	};
	uint32_t val;
};

union pmu_clkstop_open_cmu_rbch00_status {
	struct {
		uint32_t status:2; /* [1:0] */
		uint32_t rsvd1:14; /* [15:2] */
		uint32_t states:4; /* [19:16] */
		uint32_t rsvd0:12; /* [31:20] */
	};
	uint32_t val;
};

union pmu_clkstop_open_cmu_rbch00_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_clkstop_open_cmu_rbch00_duration0 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_clkstop_open_cmu_rbch00_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_clkstop_open_cmu_rbch00_duration2 {
	struct {
		uint32_t rsvd1:16; /* [15:0] */
		uint32_t dur_wait:4; /* [19:16] */
		uint32_t rsvd0:12; /* [31:20] */
	};
	uint32_t val;
};

union pmu_clkstop_open_cmu_rbch00_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_clkstop_open_cmu_rbch01_configuration {
	struct {
		uint32_t local_pwr_cfg:2; /* [1:0] */
		uint32_t rsvd0:30; /* [31:2] */
	};
	uint32_t val;
};

union pmu_clkstop_open_cmu_rbch01_status {
	struct {
		uint32_t status:2; /* [1:0] */
		uint32_t rsvd1:14; /* [15:2] */
		uint32_t states:4; /* [19:16] */
		uint32_t rsvd0:12; /* [31:20] */
	};
	uint32_t val;
};

union pmu_clkstop_open_cmu_rbch01_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_clkstop_open_cmu_rbch01_duration0 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_clkstop_open_cmu_rbch01_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_clkstop_open_cmu_rbch01_duration2 {
	struct {
		uint32_t rsvd1:16; /* [15:0] */
		uint32_t dur_wait:4; /* [19:16] */
		uint32_t rsvd0:12; /* [31:20] */
	};
	uint32_t val;
};

union pmu_clkstop_open_cmu_rbch01_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_clkstop_open_cmu_rbcv00_configuration {
	struct {
		uint32_t local_pwr_cfg:2; /* [1:0] */
		uint32_t rsvd0:30; /* [31:2] */
	};
	uint32_t val;
};

union pmu_clkstop_open_cmu_rbcv00_status {
	struct {
		uint32_t status:2; /* [1:0] */
		uint32_t rsvd1:14; /* [15:2] */
		uint32_t states:4; /* [19:16] */
		uint32_t rsvd0:12; /* [31:20] */
	};
	uint32_t val;
};

union pmu_clkstop_open_cmu_rbcv00_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_clkstop_open_cmu_rbcv00_duration0 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_clkstop_open_cmu_rbcv00_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_clkstop_open_cmu_rbcv00_duration2 {
	struct {
		uint32_t rsvd1:16; /* [15:0] */
		uint32_t dur_wait:4; /* [19:16] */
		uint32_t rsvd0:12; /* [31:20] */
	};
	uint32_t val;
};

union pmu_clkstop_open_cmu_rbcv00_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_clkstop_open_cmu_rbcv01_configuration {
	struct {
		uint32_t local_pwr_cfg:2; /* [1:0] */
		uint32_t rsvd0:30; /* [31:2] */
	};
	uint32_t val;
};

union pmu_clkstop_open_cmu_rbcv01_status {
	struct {
		uint32_t status:2; /* [1:0] */
		uint32_t rsvd1:14; /* [15:2] */
		uint32_t states:4; /* [19:16] */
		uint32_t rsvd0:12; /* [31:20] */
	};
	uint32_t val;
};

union pmu_clkstop_open_cmu_rbcv01_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_clkstop_open_cmu_rbcv01_duration0 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_clkstop_open_cmu_rbcv01_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_clkstop_open_cmu_rbcv01_duration2 {
	struct {
		uint32_t rsvd1:16; /* [15:0] */
		uint32_t dur_wait:4; /* [19:16] */
		uint32_t rsvd0:12; /* [31:20] */
	};
	uint32_t val;
};

union pmu_clkstop_open_cmu_rbcv01_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_clkstop_open_cmu_rbcv10_configuration {
	struct {
		uint32_t local_pwr_cfg:2; /* [1:0] */
		uint32_t rsvd0:30; /* [31:2] */
	};
	uint32_t val;
};

union pmu_clkstop_open_cmu_rbcv10_status {
	struct {
		uint32_t status:2; /* [1:0] */
		uint32_t rsvd1:14; /* [15:2] */
		uint32_t states:4; /* [19:16] */
		uint32_t rsvd0:12; /* [31:20] */
	};
	uint32_t val;
};

union pmu_clkstop_open_cmu_rbcv10_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_clkstop_open_cmu_rbcv10_duration0 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_clkstop_open_cmu_rbcv10_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_clkstop_open_cmu_rbcv10_duration2 {
	struct {
		uint32_t rsvd1:16; /* [15:0] */
		uint32_t dur_wait:4; /* [19:16] */
		uint32_t rsvd0:12; /* [31:20] */
	};
	uint32_t val;
};

union pmu_clkstop_open_cmu_rbcv10_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_clkstop_open_cmu_rbcv11_configuration {
	struct {
		uint32_t local_pwr_cfg:2; /* [1:0] */
		uint32_t rsvd0:30; /* [31:2] */
	};
	uint32_t val;
};

union pmu_clkstop_open_cmu_rbcv11_status {
	struct {
		uint32_t status:2; /* [1:0] */
		uint32_t rsvd1:14; /* [15:2] */
		uint32_t states:4; /* [19:16] */
		uint32_t rsvd0:12; /* [31:20] */
	};
	uint32_t val;
};

union pmu_clkstop_open_cmu_rbcv11_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_clkstop_open_cmu_rbcv11_duration0 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_clkstop_open_cmu_rbcv11_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_clkstop_open_cmu_rbcv11_duration2 {
	struct {
		uint32_t rsvd1:16; /* [15:0] */
		uint32_t dur_wait:4; /* [19:16] */
		uint32_t rsvd0:12; /* [31:20] */
	};
	uint32_t val;
};

union pmu_clkstop_open_cmu_rbcv11_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_clkstop_open_cmu_rot_configuration {
	struct {
		uint32_t local_pwr_cfg:2; /* [1:0] */
		uint32_t rsvd0:30; /* [31:2] */
	};
	uint32_t val;
};

union pmu_clkstop_open_cmu_rot_status {
	struct {
		uint32_t status:2; /* [1:0] */
		uint32_t rsvd1:14; /* [15:2] */
		uint32_t states:4; /* [19:16] */
		uint32_t rsvd0:12; /* [31:20] */
	};
	uint32_t val;
};

union pmu_clkstop_open_cmu_rot_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_clkstop_open_cmu_rot_duration0 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_clkstop_open_cmu_rot_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_clkstop_open_cmu_rot_duration2 {
	struct {
		uint32_t rsvd1:16; /* [15:0] */
		uint32_t dur_wait:4; /* [19:16] */
		uint32_t rsvd0:12; /* [31:20] */
	};
	uint32_t val;
};

union pmu_clkstop_open_cmu_rot_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_clkstop_open_cmu_peri0_configuration {
	struct {
		uint32_t local_pwr_cfg:2; /* [1:0] */
		uint32_t rsvd0:30; /* [31:2] */
	};
	uint32_t val;
};

union pmu_clkstop_open_cmu_peri0_status {
	struct {
		uint32_t status:2; /* [1:0] */
		uint32_t rsvd1:14; /* [15:2] */
		uint32_t states:4; /* [19:16] */
		uint32_t rsvd0:12; /* [31:20] */
	};
	uint32_t val;
};

union pmu_clkstop_open_cmu_peri0_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_clkstop_open_cmu_peri0_duration0 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_clkstop_open_cmu_peri0_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_clkstop_open_cmu_peri0_duration2 {
	struct {
		uint32_t rsvd1:16; /* [15:0] */
		uint32_t dur_wait:4; /* [19:16] */
		uint32_t rsvd0:12; /* [31:20] */
	};
	uint32_t val;
};

union pmu_clkstop_open_cmu_peri0_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_clkstop_open_cmu_peri1_configuration {
	struct {
		uint32_t local_pwr_cfg:2; /* [1:0] */
		uint32_t rsvd0:30; /* [31:2] */
	};
	uint32_t val;
};

union pmu_clkstop_open_cmu_peri1_status {
	struct {
		uint32_t status:2; /* [1:0] */
		uint32_t rsvd1:14; /* [15:2] */
		uint32_t states:4; /* [19:16] */
		uint32_t rsvd0:12; /* [31:20] */
	};
	uint32_t val;
};

union pmu_clkstop_open_cmu_peri1_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_clkstop_open_cmu_peri1_duration0 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_clkstop_open_cmu_peri1_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_clkstop_open_cmu_peri1_duration2 {
	struct {
		uint32_t rsvd1:16; /* [15:0] */
		uint32_t dur_wait:4; /* [19:16] */
		uint32_t rsvd0:12; /* [31:20] */
	};
	uint32_t val;
};

union pmu_clkstop_open_cmu_peri1_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_clkstop_open_cmu_sbus_u_configuration {
	struct {
		uint32_t local_pwr_cfg:2; /* [1:0] */
		uint32_t rsvd0:30; /* [31:2] */
	};
	uint32_t val;
};

union pmu_clkstop_open_cmu_sbus_u_status {
	struct {
		uint32_t status:2; /* [1:0] */
		uint32_t rsvd1:14; /* [15:2] */
		uint32_t states:4; /* [19:16] */
		uint32_t rsvd0:12; /* [31:20] */
	};
	uint32_t val;
};

union pmu_clkstop_open_cmu_sbus_u_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_clkstop_open_cmu_sbus_u_duration0 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_clkstop_open_cmu_sbus_u_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_clkstop_open_cmu_sbus_u_duration2 {
	struct {
		uint32_t rsvd1:16; /* [15:0] */
		uint32_t dur_wait:4; /* [19:16] */
		uint32_t rsvd0:12; /* [31:20] */
	};
	uint32_t val;
};

union pmu_clkstop_open_cmu_sbus_u_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_clkstop_open_cmu_sbus_d_configuration {
	struct {
		uint32_t local_pwr_cfg:2; /* [1:0] */
		uint32_t rsvd0:30; /* [31:2] */
	};
	uint32_t val;
};

union pmu_clkstop_open_cmu_sbus_d_status {
	struct {
		uint32_t status:2; /* [1:0] */
		uint32_t rsvd1:14; /* [15:2] */
		uint32_t states:4; /* [19:16] */
		uint32_t rsvd0:12; /* [31:20] */
	};
	uint32_t val;
};

union pmu_clkstop_open_cmu_sbus_d_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_clkstop_open_cmu_sbus_d_duration0 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_clkstop_open_cmu_sbus_d_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_clkstop_open_cmu_sbus_d_duration2 {
	struct {
		uint32_t rsvd1:16; /* [15:0] */
		uint32_t dur_wait:4; /* [19:16] */
		uint32_t rsvd0:12; /* [31:20] */
	};
	uint32_t val;
};

union pmu_clkstop_open_cmu_sbus_d_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_clkstop_open_cmu_sbus_l_configuration {
	struct {
		uint32_t local_pwr_cfg:2; /* [1:0] */
		uint32_t rsvd0:30; /* [31:2] */
	};
	uint32_t val;
};

union pmu_clkstop_open_cmu_sbus_l_status {
	struct {
		uint32_t status:2; /* [1:0] */
		uint32_t rsvd1:14; /* [15:2] */
		uint32_t states:4; /* [19:16] */
		uint32_t rsvd0:12; /* [31:20] */
	};
	uint32_t val;
};

union pmu_clkstop_open_cmu_sbus_l_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_clkstop_open_cmu_sbus_l_duration0 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_clkstop_open_cmu_sbus_l_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_clkstop_open_cmu_sbus_l_duration2 {
	struct {
		uint32_t rsvd1:16; /* [15:0] */
		uint32_t dur_wait:4; /* [19:16] */
		uint32_t rsvd0:12; /* [31:20] */
	};
	uint32_t val;
};

union pmu_clkstop_open_cmu_sbus_l_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_clkstop_open_cmu_nbus_u_configuration {
	struct {
		uint32_t local_pwr_cfg:2; /* [1:0] */
		uint32_t rsvd0:30; /* [31:2] */
	};
	uint32_t val;
};

union pmu_clkstop_open_cmu_nbus_u_status {
	struct {
		uint32_t status:2; /* [1:0] */
		uint32_t rsvd1:14; /* [15:2] */
		uint32_t states:4; /* [19:16] */
		uint32_t rsvd0:12; /* [31:20] */
	};
	uint32_t val;
};

union pmu_clkstop_open_cmu_nbus_u_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_clkstop_open_cmu_nbus_u_duration0 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_clkstop_open_cmu_nbus_u_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_clkstop_open_cmu_nbus_u_duration2 {
	struct {
		uint32_t rsvd1:16; /* [15:0] */
		uint32_t dur_wait:4; /* [19:16] */
		uint32_t rsvd0:12; /* [31:20] */
	};
	uint32_t val;
};

union pmu_clkstop_open_cmu_nbus_u_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_clkstop_open_cmu_nbus_d_configuration {
	struct {
		uint32_t local_pwr_cfg:2; /* [1:0] */
		uint32_t rsvd0:30; /* [31:2] */
	};
	uint32_t val;
};

union pmu_clkstop_open_cmu_nbus_d_status {
	struct {
		uint32_t status:2; /* [1:0] */
		uint32_t rsvd1:14; /* [15:2] */
		uint32_t states:4; /* [19:16] */
		uint32_t rsvd0:12; /* [31:20] */
	};
	uint32_t val;
};

union pmu_clkstop_open_cmu_nbus_d_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_clkstop_open_cmu_nbus_d_duration0 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_clkstop_open_cmu_nbus_d_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_clkstop_open_cmu_nbus_d_duration2 {
	struct {
		uint32_t rsvd1:16; /* [15:0] */
		uint32_t dur_wait:4; /* [19:16] */
		uint32_t rsvd0:12; /* [31:20] */
	};
	uint32_t val;
};

union pmu_clkstop_open_cmu_nbus_d_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_clkstop_open_cmu_nbus_l_configuration {
	struct {
		uint32_t local_pwr_cfg:2; /* [1:0] */
		uint32_t rsvd0:30; /* [31:2] */
	};
	uint32_t val;
};

union pmu_clkstop_open_cmu_nbus_l_status {
	struct {
		uint32_t status:2; /* [1:0] */
		uint32_t rsvd1:14; /* [15:2] */
		uint32_t states:4; /* [19:16] */
		uint32_t rsvd0:12; /* [31:20] */
	};
	uint32_t val;
};

union pmu_clkstop_open_cmu_nbus_l_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_clkstop_open_cmu_nbus_l_duration0 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_clkstop_open_cmu_nbus_l_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_clkstop_open_cmu_nbus_l_duration2 {
	struct {
		uint32_t rsvd1:16; /* [15:0] */
		uint32_t dur_wait:4; /* [19:16] */
		uint32_t rsvd0:12; /* [31:20] */
	};
	uint32_t val;
};

union pmu_clkstop_open_cmu_nbus_l_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_clkstop_open_cmu_wbus_u_configuration {
	struct {
		uint32_t local_pwr_cfg:2; /* [1:0] */
		uint32_t rsvd0:30; /* [31:2] */
	};
	uint32_t val;
};

union pmu_clkstop_open_cmu_wbus_u_status {
	struct {
		uint32_t status:2; /* [1:0] */
		uint32_t rsvd1:14; /* [15:2] */
		uint32_t states:4; /* [19:16] */
		uint32_t rsvd0:12; /* [31:20] */
	};
	uint32_t val;
};

union pmu_clkstop_open_cmu_wbus_u_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_clkstop_open_cmu_wbus_u_duration0 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_clkstop_open_cmu_wbus_u_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_clkstop_open_cmu_wbus_u_duration2 {
	struct {
		uint32_t rsvd1:16; /* [15:0] */
		uint32_t dur_wait:4; /* [19:16] */
		uint32_t rsvd0:12; /* [31:20] */
	};
	uint32_t val;
};

union pmu_clkstop_open_cmu_wbus_u_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_clkstop_open_cmu_wbus_d_configuration {
	struct {
		uint32_t local_pwr_cfg:2; /* [1:0] */
		uint32_t rsvd0:30; /* [31:2] */
	};
	uint32_t val;
};

union pmu_clkstop_open_cmu_wbus_d_status {
	struct {
		uint32_t status:2; /* [1:0] */
		uint32_t rsvd1:14; /* [15:2] */
		uint32_t states:4; /* [19:16] */
		uint32_t rsvd0:12; /* [31:20] */
	};
	uint32_t val;
};

union pmu_clkstop_open_cmu_wbus_d_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_clkstop_open_cmu_wbus_d_duration0 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_clkstop_open_cmu_wbus_d_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_clkstop_open_cmu_wbus_d_duration2 {
	struct {
		uint32_t rsvd1:16; /* [15:0] */
		uint32_t dur_wait:4; /* [19:16] */
		uint32_t rsvd0:12; /* [31:20] */
	};
	uint32_t val;
};

union pmu_clkstop_open_cmu_wbus_d_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_clkstop_open_cmu_ebus_u_configuration {
	struct {
		uint32_t local_pwr_cfg:2; /* [1:0] */
		uint32_t rsvd0:30; /* [31:2] */
	};
	uint32_t val;
};

union pmu_clkstop_open_cmu_ebus_u_status {
	struct {
		uint32_t status:2; /* [1:0] */
		uint32_t rsvd1:14; /* [15:2] */
		uint32_t states:4; /* [19:16] */
		uint32_t rsvd0:12; /* [31:20] */
	};
	uint32_t val;
};

union pmu_clkstop_open_cmu_ebus_u_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_clkstop_open_cmu_ebus_u_duration0 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_clkstop_open_cmu_ebus_u_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_clkstop_open_cmu_ebus_u_duration2 {
	struct {
		uint32_t rsvd1:16; /* [15:0] */
		uint32_t dur_wait:4; /* [19:16] */
		uint32_t rsvd0:12; /* [31:20] */
	};
	uint32_t val;
};

union pmu_clkstop_open_cmu_ebus_u_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_clkstop_open_cmu_ebus_d_configuration {
	struct {
		uint32_t local_pwr_cfg:2; /* [1:0] */
		uint32_t rsvd0:30; /* [31:2] */
	};
	uint32_t val;
};

union pmu_clkstop_open_cmu_ebus_d_status {
	struct {
		uint32_t status:2; /* [1:0] */
		uint32_t rsvd1:14; /* [15:2] */
		uint32_t states:4; /* [19:16] */
		uint32_t rsvd0:12; /* [31:20] */
	};
	uint32_t val;
};

union pmu_clkstop_open_cmu_ebus_d_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_clkstop_open_cmu_ebus_d_duration0 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_clkstop_open_cmu_ebus_d_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_clkstop_open_cmu_ebus_d_duration2 {
	struct {
		uint32_t rsvd1:16; /* [15:0] */
		uint32_t dur_wait:4; /* [19:16] */
		uint32_t rsvd0:12; /* [31:20] */
	};
	uint32_t val;
};

union pmu_clkstop_open_cmu_ebus_d_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_clkstop_open_cmu_ebus_r_configuration {
	struct {
		uint32_t local_pwr_cfg:2; /* [1:0] */
		uint32_t rsvd0:30; /* [31:2] */
	};
	uint32_t val;
};

union pmu_clkstop_open_cmu_ebus_r_status {
	struct {
		uint32_t status:2; /* [1:0] */
		uint32_t rsvd1:14; /* [15:2] */
		uint32_t states:4; /* [19:16] */
		uint32_t rsvd0:12; /* [31:20] */
	};
	uint32_t val;
};

union pmu_clkstop_open_cmu_ebus_r_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_clkstop_open_cmu_ebus_r_duration0 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_clkstop_open_cmu_ebus_r_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_clkstop_open_cmu_ebus_r_duration2 {
	struct {
		uint32_t rsvd1:16; /* [15:0] */
		uint32_t dur_wait:4; /* [19:16] */
		uint32_t rsvd0:12; /* [31:20] */
	};
	uint32_t val;
};

union pmu_clkstop_open_cmu_ebus_r_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_cp0_configuration {
	struct {
		uint32_t local_pwr_cfg:4; /* [3:0] */
		uint32_t local_pwr_cfg1:4; /* [7:4] */
		uint32_t rsvd0:24; /* [31:8] */
	};
	uint32_t val;
};

union pmu_cp0_status {
	struct {
		uint32_t status:4; /* [3:0] */
		uint32_t rsvd1:12; /* [15:4] */
		uint32_t states:6; /* [21:16] */
		uint32_t rsvd0:10; /* [31:22] */
	};
	uint32_t val;
};

union pmu_cp0_option {
	struct {
		uint32_t use_sc_counter:1; /* [0:0] */
		uint32_t use_sc_feedback:1; /* [1:1] */
		uint32_t rsvd1:2; /* [3:2] */
		uint32_t reset_aft_sleep:1; /* [4:4] */
		uint32_t pwr_on_aft_sleep:1; /* [5:5] */
		uint32_t pwr_restore_aft_sleep:1; /* [6:6] */
		uint32_t rsvd0:23; /* [29:7] */
		uint32_t clamp_emulation:1; /* [30:30] */
		uint32_t emulation:1; /* [31:31] */
	};
	uint32_t val;
};

union pmu_cp0_duration0 {
	struct {
		uint32_t dur_scpre_wait:4; /* [3:0] */
		uint32_t dur_scall:4; /* [7:4] */
		uint32_t dur_scpre:4; /* [11:8] */
		uint32_t rsvd0:20; /* [31:12] */
	};
	uint32_t val;
};

union pmu_cp0_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_cp0_duration2 {
	struct {
		uint32_t dur_iso:4; /* [3:0] */
		uint32_t rsvd0:28; /* [31:4] */
	};
	uint32_t val;
};

union pmu_cp0_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_cp1_configuration {
	struct {
		uint32_t local_pwr_cfg:4; /* [3:0] */
		uint32_t local_pwr_cfg1:4; /* [7:4] */
		uint32_t rsvd0:24; /* [31:8] */
	};
	uint32_t val;
};

union pmu_cp1_status {
	struct {
		uint32_t status:4; /* [3:0] */
		uint32_t rsvd1:12; /* [15:4] */
		uint32_t states:6; /* [21:16] */
		uint32_t rsvd0:10; /* [31:22] */
	};
	uint32_t val;
};

union pmu_cp1_option {
	struct {
		uint32_t use_sc_counter:1; /* [0:0] */
		uint32_t use_sc_feedback:1; /* [1:1] */
		uint32_t rsvd1:2; /* [3:2] */
		uint32_t reset_aft_sleep:1; /* [4:4] */
		uint32_t pwr_on_aft_sleep:1; /* [5:5] */
		uint32_t pwr_restore_aft_sleep:1; /* [6:6] */
		uint32_t rsvd0:23; /* [29:7] */
		uint32_t clamp_emulation:1; /* [30:30] */
		uint32_t emulation:1; /* [31:31] */
	};
	uint32_t val;
};

union pmu_cp1_duration0 {
	struct {
		uint32_t dur_scpre_wait:4; /* [3:0] */
		uint32_t dur_scall:4; /* [7:4] */
		uint32_t dur_scpre:4; /* [11:8] */
		uint32_t rsvd0:20; /* [31:12] */
	};
	uint32_t val;
};

union pmu_cp1_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_cp1_duration2 {
	struct {
		uint32_t dur_iso:4; /* [3:0] */
		uint32_t rsvd0:28; /* [31:4] */
	};
	uint32_t val;
};

union pmu_cp1_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_pcie_configuration {
	struct {
		uint32_t local_pwr_cfg:4; /* [3:0] */
		uint32_t rsvd0:28; /* [31:4] */
	};
	uint32_t val;
};

union pmu_pcie_status {
	struct {
		uint32_t status:4; /* [3:0] */
		uint32_t rsvd1:12; /* [15:4] */
		uint32_t states:6; /* [21:16] */
		uint32_t rsvd0:10; /* [31:22] */
	};
	uint32_t val;
};

union pmu_pcie_option {
	struct {
		uint32_t use_sc_counter:1; /* [0:0] */
		uint32_t use_sc_feedback:1; /* [1:1] */
		uint32_t rsvd2:2; /* [3:2] */
		uint32_t reset_aft_sleep:1; /* [4:4] */
		uint32_t pwr_on_aft_sleep:1; /* [5:5] */
		uint32_t pwr_restore_aft_sleep:1; /* [6:6] */
		uint32_t rsvd1:18; /* [24:7] */
		uint32_t use_standbywfi:1; /* [25:25] */
		uint32_t rsvd0:3; /* [28:26] */
		uint32_t pcie_isolation:1; /* [29:29] */
		uint32_t clamp_emulation:1; /* [30:30] */
		uint32_t emulation:1; /* [31:31] */
	};
	uint32_t val;
};

union pmu_pcie_duration0 {
	struct {
		uint32_t dur_scpre_wait:4; /* [3:0] */
		uint32_t dur_scall:4; /* [7:4] */
		uint32_t dur_scpre:4; /* [11:8] */
		uint32_t rsvd0:20; /* [31:12] */
	};
	uint32_t val;
};

union pmu_pcie_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_pcie_duration2 {
	struct {
		uint32_t dur_iso:4; /* [3:0] */
		uint32_t rsvd0:28; /* [31:4] */
	};
	uint32_t val;
};

union pmu_pcie_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_dram_configuration {
	struct {
		uint32_t local_pwr_cfg:4; /* [3:0] */
		uint32_t rsvd0:28; /* [31:4] */
	};
	uint32_t val;
};

union pmu_dram_status {
	struct {
		uint32_t status:4; /* [3:0] */
		uint32_t rsvd1:12; /* [15:4] */
		uint32_t states:6; /* [21:16] */
		uint32_t rsvd0:10; /* [31:22] */
	};
	uint32_t val;
};

union pmu_dram_option {
	struct {
		uint32_t use_sc_counter:1; /* [0:0] */
		uint32_t use_sc_feedback:1; /* [1:1] */
		uint32_t rsvd1:2; /* [3:2] */
		uint32_t reset_aft_sleep:1; /* [4:4] */
		uint32_t pwr_on_aft_sleep:1; /* [5:5] */
		uint32_t pwr_restore_aft_sleep:1; /* [6:6] */
		uint32_t rsvd0:23; /* [29:7] */
		uint32_t clamp_emulation:1; /* [30:30] */
		uint32_t emulation:1; /* [31:31] */
	};
	uint32_t val;
};

union pmu_dram_duration0 {
	struct {
		uint32_t dur_scpre_wait:4; /* [3:0] */
		uint32_t dur_scall:4; /* [7:4] */
		uint32_t dur_scpre:4; /* [11:8] */
		uint32_t rsvd0:20; /* [31:12] */
	};
	uint32_t val;
};

union pmu_dram_duration1 {
	struct {
		uint32_t dur_retention:4; /* [3:0] */
		uint32_t dur_separation:4; /* [7:4] */
		uint32_t rsvd0:24; /* [31:8] */
	};
	uint32_t val;
};

union pmu_dram_duration2 {
	struct {
		uint32_t dur_iso:4; /* [3:0] */
		uint32_t rsvd0:28; /* [31:4] */
	};
	uint32_t val;
};

union pmu_dram_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_dcl0_configuration {
	struct {
		uint32_t local_pwr_cfg:4; /* [3:0] */
		uint32_t rsvd0:28; /* [31:4] */
	};
	uint32_t val;
};

union pmu_dcl0_status {
	struct {
		uint32_t status:4; /* [3:0] */
		uint32_t rsvd1:12; /* [15:4] */
		uint32_t states:6; /* [21:16] */
		uint32_t rsvd0:10; /* [31:22] */
	};
	uint32_t val;
};

union pmu_dcl0_option {
	struct {
		uint32_t use_sc_counter:1; /* [0:0] */
		uint32_t use_sc_feedback:1; /* [1:1] */
		uint32_t rsvd1:2; /* [3:2] */
		uint32_t reset_aft_sleep:1; /* [4:4] */
		uint32_t pwr_on_aft_sleep:1; /* [5:5] */
		uint32_t pwr_restore_aft_sleep:1; /* [6:6] */
		uint32_t rsvd0:23; /* [29:7] */
		uint32_t clamp_emulation:1; /* [30:30] */
		uint32_t emulation:1; /* [31:31] */
	};
	uint32_t val;
};

union pmu_dcl0_duration0 {
	struct {
		uint32_t dur_scpre_wait:4; /* [3:0] */
		uint32_t dur_scall:4; /* [7:4] */
		uint32_t dur_scpre:4; /* [11:8] */
		uint32_t rsvd0:20; /* [31:12] */
	};
	uint32_t val;
};

union pmu_dcl0_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_dcl0_duration2 {
	struct {
		uint32_t dur_iso:4; /* [3:0] */
		uint32_t rsvd0:28; /* [31:4] */
	};
	uint32_t val;
};

union pmu_dcl0_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_dcl1_configuration {
	struct {
		uint32_t local_pwr_cfg:4; /* [3:0] */
		uint32_t rsvd0:28; /* [31:4] */
	};
	uint32_t val;
};

union pmu_dcl1_status {
	struct {
		uint32_t status:4; /* [3:0] */
		uint32_t rsvd1:12; /* [15:4] */
		uint32_t states:6; /* [21:16] */
		uint32_t rsvd0:10; /* [31:22] */
	};
	uint32_t val;
};

union pmu_dcl1_option {
	struct {
		uint32_t use_sc_counter:1; /* [0:0] */
		uint32_t use_sc_feedback:1; /* [1:1] */
		uint32_t rsvd1:2; /* [3:2] */
		uint32_t reset_aft_sleep:1; /* [4:4] */
		uint32_t pwr_on_aft_sleep:1; /* [5:5] */
		uint32_t pwr_restore_aft_sleep:1; /* [6:6] */
		uint32_t rsvd0:23; /* [29:7] */
		uint32_t clamp_emulation:1; /* [30:30] */
		uint32_t emulation:1; /* [31:31] */
	};
	uint32_t val;
};

union pmu_dcl1_duration0 {
	struct {
		uint32_t dur_scpre_wait:4; /* [3:0] */
		uint32_t dur_scall:4; /* [7:4] */
		uint32_t dur_scpre:4; /* [11:8] */
		uint32_t rsvd0:20; /* [31:12] */
	};
	uint32_t val;
};

union pmu_dcl1_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_dcl1_duration2 {
	struct {
		uint32_t dur_iso:4; /* [3:0] */
		uint32_t rsvd0:28; /* [31:4] */
	};
	uint32_t val;
};

union pmu_dcl1_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_rbch00_configuration {
	struct {
		uint32_t local_pwr_cfg:4; /* [3:0] */
		uint32_t rsvd0:27; /* [30:4] */
		uint32_t initiate_wakeup_from_lowpwr:1; /* [31:31] */
	};
	uint32_t val;
};

union pmu_rbch00_status {
	struct {
		uint32_t status:4; /* [3:0] */
		uint32_t rsvd1:12; /* [15:4] */
		uint32_t states:6; /* [21:16] */
		uint32_t rsvd0:9; /* [30:22] */
		uint32_t initiate_wakeup_from_lowpwr:1; /* [31:31] */
	};
	uint32_t val;
};

union pmu_rbch00_option {
	struct {
		uint32_t use_sc_counter:1; /* [0:0] */
		uint32_t use_sc_feedback:1; /* [1:1] */
		uint32_t rsvd1:2; /* [3:2] */
		uint32_t reset_aft_sleep:1; /* [4:4] */
		uint32_t pwr_on_aft_sleep:1; /* [5:5] */
		uint32_t pwr_restore_aft_sleep:1; /* [6:6] */
		uint32_t rsvd0:22; /* [28:7] */
		uint32_t ucie_isolation:1; /* [29:29] */
		uint32_t clamp_emulation:1; /* [30:30] */
		uint32_t emulation:1; /* [31:31] */
	};
	uint32_t val;
};

union pmu_rbch00_duration0 {
	struct {
		uint32_t dur_scpre_wait:4; /* [3:0] */
		uint32_t dur_scall:4; /* [7:4] */
		uint32_t dur_scpre:4; /* [11:8] */
		uint32_t rsvd0:20; /* [31:12] */
	};
	uint32_t val;
};

union pmu_rbch00_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_rbch00_duration2 {
	struct {
		uint32_t dur_iso:4; /* [3:0] */
		uint32_t rsvd0:28; /* [31:4] */
	};
	uint32_t val;
};

union pmu_rbch00_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_rbch01_configuration {
	struct {
		uint32_t local_pwr_cfg:4; /* [3:0] */
		uint32_t rsvd0:27; /* [30:4] */
		uint32_t initiate_wakeup_from_lowpwr:1; /* [31:31] */
	};
	uint32_t val;
};

union pmu_rbch01_status {
	struct {
		uint32_t status:4; /* [3:0] */
		uint32_t rsvd1:12; /* [15:4] */
		uint32_t states:6; /* [21:16] */
		uint32_t rsvd0:9; /* [30:22] */
		uint32_t initiate_wakeup_from_lowpwr:1; /* [31:31] */
	};
	uint32_t val;
};

union pmu_rbch01_option {
	struct {
		uint32_t use_sc_counter:1; /* [0:0] */
		uint32_t use_sc_feedback:1; /* [1:1] */
		uint32_t rsvd1:2; /* [3:2] */
		uint32_t reset_aft_sleep:1; /* [4:4] */
		uint32_t pwr_on_aft_sleep:1; /* [5:5] */
		uint32_t pwr_restore_aft_sleep:1; /* [6:6] */
		uint32_t rsvd0:22; /* [28:7] */
		uint32_t ucie_isolation:1; /* [29:29] */
		uint32_t clamp_emulation:1; /* [30:30] */
		uint32_t emulation:1; /* [31:31] */
	};
	uint32_t val;
};

union pmu_rbch01_duration0 {
	struct {
		uint32_t dur_scpre_wait:4; /* [3:0] */
		uint32_t dur_scall:4; /* [7:4] */
		uint32_t dur_scpre:4; /* [11:8] */
		uint32_t rsvd0:20; /* [31:12] */
	};
	uint32_t val;
};

union pmu_rbch01_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_rbch01_duration2 {
	struct {
		uint32_t dur_iso:4; /* [3:0] */
		uint32_t rsvd0:28; /* [31:4] */
	};
	uint32_t val;
};

union pmu_rbch01_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_rbcv00_configuration {
	struct {
		uint32_t local_pwr_cfg:4; /* [3:0] */
		uint32_t rsvd0:27; /* [30:4] */
		uint32_t initiate_wakeup_from_lowpwr:1; /* [31:31] */
	};
	uint32_t val;
};

union pmu_rbcv00_status {
	struct {
		uint32_t status:4; /* [3:0] */
		uint32_t rsvd1:12; /* [15:4] */
		uint32_t states:6; /* [21:16] */
		uint32_t rsvd0:9; /* [30:22] */
		uint32_t initiate_wakeup_from_lowpwr:1; /* [31:31] */
	};
	uint32_t val;
};

union pmu_rbcv00_option {
	struct {
		uint32_t use_sc_counter:1; /* [0:0] */
		uint32_t use_sc_feedback:1; /* [1:1] */
		uint32_t rsvd1:2; /* [3:2] */
		uint32_t reset_aft_sleep:1; /* [4:4] */
		uint32_t pwr_on_aft_sleep:1; /* [5:5] */
		uint32_t pwr_restore_aft_sleep:1; /* [6:6] */
		uint32_t rsvd0:22; /* [28:7] */
		uint32_t ucie_isolation:1; /* [29:29] */
		uint32_t clamp_emulation:1; /* [30:30] */
		uint32_t emulation:1; /* [31:31] */
	};
	uint32_t val;
};

union pmu_rbcv00_duration0 {
	struct {
		uint32_t dur_scpre_wait:4; /* [3:0] */
		uint32_t dur_scall:4; /* [7:4] */
		uint32_t dur_scpre:4; /* [11:8] */
		uint32_t rsvd0:20; /* [31:12] */
	};
	uint32_t val;
};

union pmu_rbcv00_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_rbcv00_duration2 {
	struct {
		uint32_t dur_iso:4; /* [3:0] */
		uint32_t rsvd0:28; /* [31:4] */
	};
	uint32_t val;
};

union pmu_rbcv00_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_rbcv01_configuration {
	struct {
		uint32_t local_pwr_cfg:4; /* [3:0] */
		uint32_t rsvd0:27; /* [30:4] */
		uint32_t initiate_wakeup_from_lowpwr:1; /* [31:31] */
	};
	uint32_t val;
};

union pmu_rbcv01_status {
	struct {
		uint32_t status:4; /* [3:0] */
		uint32_t rsvd1:12; /* [15:4] */
		uint32_t states:6; /* [21:16] */
		uint32_t rsvd0:9; /* [30:22] */
		uint32_t initiate_wakeup_from_lowpwr:1; /* [31:31] */
	};
	uint32_t val;
};

union pmu_rbcv01_option {
	struct {
		uint32_t use_sc_counter:1; /* [0:0] */
		uint32_t use_sc_feedback:1; /* [1:1] */
		uint32_t rsvd1:2; /* [3:2] */
		uint32_t reset_aft_sleep:1; /* [4:4] */
		uint32_t pwr_on_aft_sleep:1; /* [5:5] */
		uint32_t pwr_restore_aft_sleep:1; /* [6:6] */
		uint32_t rsvd0:22; /* [28:7] */
		uint32_t ucie_isolation:1; /* [29:29] */
		uint32_t clamp_emulation:1; /* [30:30] */
		uint32_t emulation:1; /* [31:31] */
	};
	uint32_t val;
};

union pmu_rbcv01_duration0 {
	struct {
		uint32_t dur_scpre_wait:4; /* [3:0] */
		uint32_t dur_scall:4; /* [7:4] */
		uint32_t dur_scpre:4; /* [11:8] */
		uint32_t rsvd0:20; /* [31:12] */
	};
	uint32_t val;
};

union pmu_rbcv01_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_rbcv01_duration2 {
	struct {
		uint32_t dur_iso:4; /* [3:0] */
		uint32_t rsvd0:28; /* [31:4] */
	};
	uint32_t val;
};

union pmu_rbcv01_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_rbcv10_configuration {
	struct {
		uint32_t local_pwr_cfg:4; /* [3:0] */
		uint32_t rsvd0:27; /* [30:4] */
		uint32_t initiate_wakeup_from_lowpwr:1; /* [31:31] */
	};
	uint32_t val;
};

union pmu_rbcv10_status {
	struct {
		uint32_t status:4; /* [3:0] */
		uint32_t rsvd1:12; /* [15:4] */
		uint32_t states:6; /* [21:16] */
		uint32_t rsvd0:9; /* [30:22] */
		uint32_t initiate_wakeup_from_lowpwr:1; /* [31:31] */
	};
	uint32_t val;
};

union pmu_rbcv10_option {
	struct {
		uint32_t use_sc_counter:1; /* [0:0] */
		uint32_t use_sc_feedback:1; /* [1:1] */
		uint32_t rsvd1:2; /* [3:2] */
		uint32_t reset_aft_sleep:1; /* [4:4] */
		uint32_t pwr_on_aft_sleep:1; /* [5:5] */
		uint32_t pwr_restore_aft_sleep:1; /* [6:6] */
		uint32_t rsvd0:22; /* [28:7] */
		uint32_t ucie_isolation:1; /* [29:29] */
		uint32_t clamp_emulation:1; /* [30:30] */
		uint32_t emulation:1; /* [31:31] */
	};
	uint32_t val;
};

union pmu_rbcv10_duration0 {
	struct {
		uint32_t dur_scpre_wait:4; /* [3:0] */
		uint32_t dur_scall:4; /* [7:4] */
		uint32_t dur_scpre:4; /* [11:8] */
		uint32_t rsvd0:20; /* [31:12] */
	};
	uint32_t val;
};

union pmu_rbcv10_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_rbcv10_duration2 {
	struct {
		uint32_t dur_iso:4; /* [3:0] */
		uint32_t rsvd0:28; /* [31:4] */
	};
	uint32_t val;
};

union pmu_rbcv10_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_rbcv11_configuration {
	struct {
		uint32_t local_pwr_cfg:4; /* [3:0] */
		uint32_t rsvd0:27; /* [30:4] */
		uint32_t initiate_wakeup_from_lowpwr:1; /* [31:31] */
	};
	uint32_t val;
};

union pmu_rbcv11_status {
	struct {
		uint32_t status:4; /* [3:0] */
		uint32_t rsvd1:12; /* [15:4] */
		uint32_t states:6; /* [21:16] */
		uint32_t rsvd0:9; /* [30:22] */
		uint32_t initiate_wakeup_from_lowpwr:1; /* [31:31] */
	};
	uint32_t val;
};

union pmu_rbcv11_option {
	struct {
		uint32_t use_sc_counter:1; /* [0:0] */
		uint32_t use_sc_feedback:1; /* [1:1] */
		uint32_t rsvd1:2; /* [3:2] */
		uint32_t reset_aft_sleep:1; /* [4:4] */
		uint32_t pwr_on_aft_sleep:1; /* [5:5] */
		uint32_t pwr_restore_aft_sleep:1; /* [6:6] */
		uint32_t rsvd0:22; /* [28:7] */
		uint32_t ucie_isolation:1; /* [29:29] */
		uint32_t clamp_emulation:1; /* [30:30] */
		uint32_t emulation:1; /* [31:31] */
	};
	uint32_t val;
};

union pmu_rbcv11_duration0 {
	struct {
		uint32_t dur_scpre_wait:4; /* [3:0] */
		uint32_t dur_scall:4; /* [7:4] */
		uint32_t dur_scpre:4; /* [11:8] */
		uint32_t rsvd0:20; /* [31:12] */
	};
	uint32_t val;
};

union pmu_rbcv11_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_rbcv11_duration2 {
	struct {
		uint32_t dur_iso:4; /* [3:0] */
		uint32_t rsvd0:28; /* [31:4] */
	};
	uint32_t val;
};

union pmu_rbcv11_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_rot_configuration {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_rot_status {
	struct {
		uint32_t status:4; /* [3:0] */
		uint32_t rsvd1:12; /* [15:4] */
		uint32_t states:6; /* [21:16] */
		uint32_t rsvd0:10; /* [31:22] */
	};
	uint32_t val;
};

union pmu_rot_option {
	struct {
		uint32_t use_sc_counter:1; /* [0:0] */
		uint32_t use_sc_feedback:1; /* [1:1] */
		uint32_t rsvd1:2; /* [3:2] */
		uint32_t reset_aft_sleep:1; /* [4:4] */
		uint32_t pwr_on_aft_sleep:1; /* [5:5] */
		uint32_t pwr_restore_aft_sleep:1; /* [6:6] */
		uint32_t rsvd0:23; /* [29:7] */
		uint32_t clamp_emulation:1; /* [30:30] */
		uint32_t emulation:1; /* [31:31] */
	};
	uint32_t val;
};

union pmu_rot_duration0 {
	struct {
		uint32_t dur_scpre_wait:4; /* [3:0] */
		uint32_t dur_scall:4; /* [7:4] */
		uint32_t dur_scpre:4; /* [11:8] */
		uint32_t rsvd0:20; /* [31:12] */
	};
	uint32_t val;
};

union pmu_rot_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_rot_duration2 {
	struct {
		uint32_t dur_iso:4; /* [3:0] */
		uint32_t rsvd0:28; /* [31:4] */
	};
	uint32_t val;
};

union pmu_rot_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_peri0_configuration {
	struct {
		uint32_t local_pwr_cfg:4; /* [3:0] */
		uint32_t rsvd0:28; /* [31:4] */
	};
	uint32_t val;
};

union pmu_peri0_status {
	struct {
		uint32_t status:4; /* [3:0] */
		uint32_t rsvd1:12; /* [15:4] */
		uint32_t states:6; /* [21:16] */
		uint32_t rsvd0:10; /* [31:22] */
	};
	uint32_t val;
};

union pmu_peri0_option {
	struct {
		uint32_t use_sc_counter:1; /* [0:0] */
		uint32_t use_sc_feedback:1; /* [1:1] */
		uint32_t rsvd1:2; /* [3:2] */
		uint32_t reset_aft_sleep:1; /* [4:4] */
		uint32_t pwr_on_aft_sleep:1; /* [5:5] */
		uint32_t pwr_restore_aft_sleep:1; /* [6:6] */
		uint32_t rsvd0:23; /* [29:7] */
		uint32_t clamp_emulation:1; /* [30:30] */
		uint32_t emulation:1; /* [31:31] */
	};
	uint32_t val;
};

union pmu_peri0_duration0 {
	struct {
		uint32_t dur_scpre_wait:4; /* [3:0] */
		uint32_t dur_scall:4; /* [7:4] */
		uint32_t dur_scpre:4; /* [11:8] */
		uint32_t rsvd0:20; /* [31:12] */
	};
	uint32_t val;
};

union pmu_peri0_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_peri0_duration2 {
	struct {
		uint32_t dur_iso:4; /* [3:0] */
		uint32_t rsvd0:28; /* [31:4] */
	};
	uint32_t val;
};

union pmu_peri0_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_peri1_configuration {
	struct {
		uint32_t local_pwr_cfg:4; /* [3:0] */
		uint32_t rsvd0:28; /* [31:4] */
	};
	uint32_t val;
};

union pmu_peri1_status {
	struct {
		uint32_t status:4; /* [3:0] */
		uint32_t rsvd1:12; /* [15:4] */
		uint32_t states:6; /* [21:16] */
		uint32_t rsvd0:10; /* [31:22] */
	};
	uint32_t val;
};

union pmu_peri1_option {
	struct {
		uint32_t use_sc_counter:1; /* [0:0] */
		uint32_t use_sc_feedback:1; /* [1:1] */
		uint32_t rsvd1:2; /* [3:2] */
		uint32_t reset_aft_sleep:1; /* [4:4] */
		uint32_t pwr_on_aft_sleep:1; /* [5:5] */
		uint32_t pwr_restore_aft_sleep:1; /* [6:6] */
		uint32_t rsvd0:23; /* [29:7] */
		uint32_t clamp_emulation:1; /* [30:30] */
		uint32_t emulation:1; /* [31:31] */
	};
	uint32_t val;
};

union pmu_peri1_duration0 {
	struct {
		uint32_t dur_scpre_wait:4; /* [3:0] */
		uint32_t dur_scall:4; /* [7:4] */
		uint32_t dur_scpre:4; /* [11:8] */
		uint32_t rsvd0:20; /* [31:12] */
	};
	uint32_t val;
};

union pmu_peri1_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_peri1_duration2 {
	struct {
		uint32_t dur_iso:4; /* [3:0] */
		uint32_t rsvd0:28; /* [31:4] */
	};
	uint32_t val;
};

union pmu_peri1_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_sbus_u_configuration {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_sbus_u_status {
	struct {
		uint32_t status:4; /* [3:0] */
		uint32_t rsvd1:12; /* [15:4] */
		uint32_t states:6; /* [21:16] */
		uint32_t rsvd0:10; /* [31:22] */
	};
	uint32_t val;
};

union pmu_sbus_u_option {
	struct {
		uint32_t use_sc_counter:1; /* [0:0] */
		uint32_t use_sc_feedback:1; /* [1:1] */
		uint32_t rsvd1:2; /* [3:2] */
		uint32_t reset_aft_sleep:1; /* [4:4] */
		uint32_t pwr_on_aft_sleep:1; /* [5:5] */
		uint32_t pwr_restore_aft_sleep:1; /* [6:6] */
		uint32_t rsvd0:23; /* [29:7] */
		uint32_t clamp_emulation:1; /* [30:30] */
		uint32_t emulation:1; /* [31:31] */
	};
	uint32_t val;
};

union pmu_sbus_u_duration0 {
	struct {
		uint32_t dur_scpre_wait:4; /* [3:0] */
		uint32_t dur_scall:4; /* [7:4] */
		uint32_t dur_scpre:4; /* [11:8] */
		uint32_t rsvd0:20; /* [31:12] */
	};
	uint32_t val;
};

union pmu_sbus_u_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_sbus_u_duration2 {
	struct {
		uint32_t dur_iso:4; /* [3:0] */
		uint32_t rsvd0:28; /* [31:4] */
	};
	uint32_t val;
};

union pmu_sbus_u_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_sbus_d_configuration {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_sbus_d_status {
	struct {
		uint32_t status:4; /* [3:0] */
		uint32_t rsvd1:12; /* [15:4] */
		uint32_t states:6; /* [21:16] */
		uint32_t rsvd0:10; /* [31:22] */
	};
	uint32_t val;
};

union pmu_sbus_d_option {
	struct {
		uint32_t use_sc_counter:1; /* [0:0] */
		uint32_t use_sc_feedback:1; /* [1:1] */
		uint32_t rsvd1:2; /* [3:2] */
		uint32_t reset_aft_sleep:1; /* [4:4] */
		uint32_t pwr_on_aft_sleep:1; /* [5:5] */
		uint32_t pwr_restore_aft_sleep:1; /* [6:6] */
		uint32_t rsvd0:23; /* [29:7] */
		uint32_t clamp_emulation:1; /* [30:30] */
		uint32_t emulation:1; /* [31:31] */
	};
	uint32_t val;
};

union pmu_sbus_d_duration0 {
	struct {
		uint32_t dur_scpre_wait:4; /* [3:0] */
		uint32_t dur_scall:4; /* [7:4] */
		uint32_t dur_scpre:4; /* [11:8] */
		uint32_t rsvd0:20; /* [31:12] */
	};
	uint32_t val;
};

union pmu_sbus_d_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_sbus_d_duration2 {
	struct {
		uint32_t dur_iso:4; /* [3:0] */
		uint32_t rsvd0:28; /* [31:4] */
	};
	uint32_t val;
};

union pmu_sbus_d_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_sbus_l_configuration {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_sbus_l_status {
	struct {
		uint32_t status:4; /* [3:0] */
		uint32_t rsvd1:12; /* [15:4] */
		uint32_t states:6; /* [21:16] */
		uint32_t rsvd0:10; /* [31:22] */
	};
	uint32_t val;
};

union pmu_sbus_l_option {
	struct {
		uint32_t use_sc_counter:1; /* [0:0] */
		uint32_t use_sc_feedback:1; /* [1:1] */
		uint32_t rsvd1:2; /* [3:2] */
		uint32_t reset_aft_sleep:1; /* [4:4] */
		uint32_t pwr_on_aft_sleep:1; /* [5:5] */
		uint32_t pwr_restore_aft_sleep:1; /* [6:6] */
		uint32_t rsvd0:23; /* [29:7] */
		uint32_t clamp_emulation:1; /* [30:30] */
		uint32_t emulation:1; /* [31:31] */
	};
	uint32_t val;
};

union pmu_sbus_l_duration0 {
	struct {
		uint32_t dur_scpre_wait:4; /* [3:0] */
		uint32_t dur_scall:4; /* [7:4] */
		uint32_t dur_scpre:4; /* [11:8] */
		uint32_t rsvd0:20; /* [31:12] */
	};
	uint32_t val;
};

union pmu_sbus_l_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_sbus_l_duration2 {
	struct {
		uint32_t dur_iso:4; /* [3:0] */
		uint32_t rsvd0:28; /* [31:4] */
	};
	uint32_t val;
};

union pmu_sbus_l_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_nbus_u_configuration {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_nbus_u_status {
	struct {
		uint32_t status:4; /* [3:0] */
		uint32_t rsvd1:12; /* [15:4] */
		uint32_t states:6; /* [21:16] */
		uint32_t rsvd0:10; /* [31:22] */
	};
	uint32_t val;
};

union pmu_nbus_u_option {
	struct {
		uint32_t use_sc_counter:1; /* [0:0] */
		uint32_t use_sc_feedback:1; /* [1:1] */
		uint32_t rsvd1:2; /* [3:2] */
		uint32_t reset_aft_sleep:1; /* [4:4] */
		uint32_t pwr_on_aft_sleep:1; /* [5:5] */
		uint32_t pwr_restore_aft_sleep:1; /* [6:6] */
		uint32_t rsvd0:23; /* [29:7] */
		uint32_t clamp_emulation:1; /* [30:30] */
		uint32_t emulation:1; /* [31:31] */
	};
	uint32_t val;
};

union pmu_nbus_u_duration0 {
	struct {
		uint32_t dur_scpre_wait:4; /* [3:0] */
		uint32_t dur_scall:4; /* [7:4] */
		uint32_t dur_scpre:4; /* [11:8] */
		uint32_t rsvd0:20; /* [31:12] */
	};
	uint32_t val;
};

union pmu_nbus_u_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_nbus_u_duration2 {
	struct {
		uint32_t dur_iso:4; /* [3:0] */
		uint32_t rsvd0:28; /* [31:4] */
	};
	uint32_t val;
};

union pmu_nbus_u_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_nbus_d_configuration {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_nbus_d_status {
	struct {
		uint32_t status:4; /* [3:0] */
		uint32_t rsvd1:12; /* [15:4] */
		uint32_t states:6; /* [21:16] */
		uint32_t rsvd0:10; /* [31:22] */
	};
	uint32_t val;
};

union pmu_nbus_d_option {
	struct {
		uint32_t use_sc_counter:1; /* [0:0] */
		uint32_t use_sc_feedback:1; /* [1:1] */
		uint32_t rsvd1:2; /* [3:2] */
		uint32_t reset_aft_sleep:1; /* [4:4] */
		uint32_t pwr_on_aft_sleep:1; /* [5:5] */
		uint32_t pwr_restore_aft_sleep:1; /* [6:6] */
		uint32_t rsvd0:23; /* [29:7] */
		uint32_t clamp_emulation:1; /* [30:30] */
		uint32_t emulation:1; /* [31:31] */
	};
	uint32_t val;
};

union pmu_nbus_d_duration0 {
	struct {
		uint32_t dur_scpre_wait:4; /* [3:0] */
		uint32_t dur_scall:4; /* [7:4] */
		uint32_t dur_scpre:4; /* [11:8] */
		uint32_t rsvd0:20; /* [31:12] */
	};
	uint32_t val;
};

union pmu_nbus_d_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_nbus_d_duration2 {
	struct {
		uint32_t dur_iso:4; /* [3:0] */
		uint32_t rsvd0:28; /* [31:4] */
	};
	uint32_t val;
};

union pmu_nbus_d_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_nbus_l_configuration {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_nbus_l_status {
	struct {
		uint32_t status:4; /* [3:0] */
		uint32_t rsvd1:12; /* [15:4] */
		uint32_t states:6; /* [21:16] */
		uint32_t rsvd0:10; /* [31:22] */
	};
	uint32_t val;
};

union pmu_nbus_l_option {
	struct {
		uint32_t use_sc_counter:1; /* [0:0] */
		uint32_t use_sc_feedback:1; /* [1:1] */
		uint32_t rsvd1:2; /* [3:2] */
		uint32_t reset_aft_sleep:1; /* [4:4] */
		uint32_t pwr_on_aft_sleep:1; /* [5:5] */
		uint32_t pwr_restore_aft_sleep:1; /* [6:6] */
		uint32_t rsvd0:23; /* [29:7] */
		uint32_t clamp_emulation:1; /* [30:30] */
		uint32_t emulation:1; /* [31:31] */
	};
	uint32_t val;
};

union pmu_nbus_l_duration0 {
	struct {
		uint32_t dur_scpre_wait:4; /* [3:0] */
		uint32_t dur_scall:4; /* [7:4] */
		uint32_t dur_scpre:4; /* [11:8] */
		uint32_t rsvd0:20; /* [31:12] */
	};
	uint32_t val;
};

union pmu_nbus_l_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_nbus_l_duration2 {
	struct {
		uint32_t dur_iso:4; /* [3:0] */
		uint32_t rsvd0:28; /* [31:4] */
	};
	uint32_t val;
};

union pmu_nbus_l_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_wbus_u_configuration {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_wbus_u_status {
	struct {
		uint32_t status:4; /* [3:0] */
		uint32_t rsvd1:12; /* [15:4] */
		uint32_t states:6; /* [21:16] */
		uint32_t rsvd0:10; /* [31:22] */
	};
	uint32_t val;
};

union pmu_wbus_u_option {
	struct {
		uint32_t use_sc_counter:1; /* [0:0] */
		uint32_t use_sc_feedback:1; /* [1:1] */
		uint32_t rsvd1:2; /* [3:2] */
		uint32_t reset_aft_sleep:1; /* [4:4] */
		uint32_t pwr_on_aft_sleep:1; /* [5:5] */
		uint32_t pwr_restore_aft_sleep:1; /* [6:6] */
		uint32_t rsvd0:23; /* [29:7] */
		uint32_t clamp_emulation:1; /* [30:30] */
		uint32_t emulation:1; /* [31:31] */
	};
	uint32_t val;
};

union pmu_wbus_u_duration0 {
	struct {
		uint32_t dur_scpre_wait:4; /* [3:0] */
		uint32_t dur_scall:4; /* [7:4] */
		uint32_t dur_scpre:4; /* [11:8] */
		uint32_t rsvd0:20; /* [31:12] */
	};
	uint32_t val;
};

union pmu_wbus_u_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_wbus_u_duration2 {
	struct {
		uint32_t dur_iso:4; /* [3:0] */
		uint32_t rsvd0:28; /* [31:4] */
	};
	uint32_t val;
};

union pmu_wbus_u_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_wbus_d_configuration {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_wbus_d_status {
	struct {
		uint32_t status:4; /* [3:0] */
		uint32_t rsvd1:12; /* [15:4] */
		uint32_t states:6; /* [21:16] */
		uint32_t rsvd0:10; /* [31:22] */
	};
	uint32_t val;
};

union pmu_wbus_d_option {
	struct {
		uint32_t use_sc_counter:1; /* [0:0] */
		uint32_t use_sc_feedback:1; /* [1:1] */
		uint32_t rsvd1:2; /* [3:2] */
		uint32_t reset_aft_sleep:1; /* [4:4] */
		uint32_t pwr_on_aft_sleep:1; /* [5:5] */
		uint32_t pwr_restore_aft_sleep:1; /* [6:6] */
		uint32_t rsvd0:23; /* [29:7] */
		uint32_t clamp_emulation:1; /* [30:30] */
		uint32_t emulation:1; /* [31:31] */
	};
	uint32_t val;
};

union pmu_wbus_d_duration0 {
	struct {
		uint32_t dur_scpre_wait:4; /* [3:0] */
		uint32_t dur_scall:4; /* [7:4] */
		uint32_t dur_scpre:4; /* [11:8] */
		uint32_t rsvd0:20; /* [31:12] */
	};
	uint32_t val;
};

union pmu_wbus_d_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_wbus_d_duration2 {
	struct {
		uint32_t dur_iso:4; /* [3:0] */
		uint32_t rsvd0:28; /* [31:4] */
	};
	uint32_t val;
};

union pmu_wbus_d_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_ebus_u_configuration {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_ebus_u_status {
	struct {
		uint32_t status:4; /* [3:0] */
		uint32_t rsvd1:12; /* [15:4] */
		uint32_t states:6; /* [21:16] */
		uint32_t rsvd0:10; /* [31:22] */
	};
	uint32_t val;
};

union pmu_ebus_u_option {
	struct {
		uint32_t use_sc_counter:1; /* [0:0] */
		uint32_t use_sc_feedback:1; /* [1:1] */
		uint32_t rsvd1:2; /* [3:2] */
		uint32_t reset_aft_sleep:1; /* [4:4] */
		uint32_t pwr_on_aft_sleep:1; /* [5:5] */
		uint32_t pwr_restore_aft_sleep:1; /* [6:6] */
		uint32_t rsvd0:23; /* [29:7] */
		uint32_t clamp_emulation:1; /* [30:30] */
		uint32_t emulation:1; /* [31:31] */
	};
	uint32_t val;
};

union pmu_ebus_u_duration0 {
	struct {
		uint32_t dur_scpre_wait:4; /* [3:0] */
		uint32_t dur_scall:4; /* [7:4] */
		uint32_t dur_scpre:4; /* [11:8] */
		uint32_t rsvd0:20; /* [31:12] */
	};
	uint32_t val;
};

union pmu_ebus_u_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_ebus_u_duration2 {
	struct {
		uint32_t dur_iso:4; /* [3:0] */
		uint32_t rsvd0:28; /* [31:4] */
	};
	uint32_t val;
};

union pmu_ebus_u_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_ebus_d_configuration {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_ebus_d_status {
	struct {
		uint32_t status:4; /* [3:0] */
		uint32_t rsvd1:12; /* [15:4] */
		uint32_t states:6; /* [21:16] */
		uint32_t rsvd0:10; /* [31:22] */
	};
	uint32_t val;
};

union pmu_ebus_d_option {
	struct {
		uint32_t use_sc_counter:1; /* [0:0] */
		uint32_t use_sc_feedback:1; /* [1:1] */
		uint32_t rsvd1:2; /* [3:2] */
		uint32_t reset_aft_sleep:1; /* [4:4] */
		uint32_t pwr_on_aft_sleep:1; /* [5:5] */
		uint32_t pwr_restore_aft_sleep:1; /* [6:6] */
		uint32_t rsvd0:23; /* [29:7] */
		uint32_t clamp_emulation:1; /* [30:30] */
		uint32_t emulation:1; /* [31:31] */
	};
	uint32_t val;
};

union pmu_ebus_d_duration0 {
	struct {
		uint32_t dur_scpre_wait:4; /* [3:0] */
		uint32_t dur_scall:4; /* [7:4] */
		uint32_t dur_scpre:4; /* [11:8] */
		uint32_t rsvd0:20; /* [31:12] */
	};
	uint32_t val;
};

union pmu_ebus_d_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_ebus_d_duration2 {
	struct {
		uint32_t dur_iso:4; /* [3:0] */
		uint32_t rsvd0:28; /* [31:4] */
	};
	uint32_t val;
};

union pmu_ebus_d_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_ebus_r_configuration {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_ebus_r_status {
	struct {
		uint32_t status:4; /* [3:0] */
		uint32_t rsvd1:12; /* [15:4] */
		uint32_t states:6; /* [21:16] */
		uint32_t rsvd0:10; /* [31:22] */
	};
	uint32_t val;
};

union pmu_ebus_r_option {
	struct {
		uint32_t use_sc_counter:1; /* [0:0] */
		uint32_t use_sc_feedback:1; /* [1:1] */
		uint32_t rsvd1:2; /* [3:2] */
		uint32_t reset_aft_sleep:1; /* [4:4] */
		uint32_t pwr_on_aft_sleep:1; /* [5:5] */
		uint32_t pwr_restore_aft_sleep:1; /* [6:6] */
		uint32_t rsvd0:23; /* [29:7] */
		uint32_t clamp_emulation:1; /* [30:30] */
		uint32_t emulation:1; /* [31:31] */
	};
	uint32_t val;
};

union pmu_ebus_r_duration0 {
	struct {
		uint32_t dur_scpre_wait:4; /* [3:0] */
		uint32_t dur_scall:4; /* [7:4] */
		uint32_t dur_scpre:4; /* [11:8] */
		uint32_t rsvd0:20; /* [31:12] */
	};
	uint32_t val;
};

union pmu_ebus_r_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_ebus_r_duration2 {
	struct {
		uint32_t dur_iso:4; /* [3:0] */
		uint32_t rsvd0:28; /* [31:4] */
	};
	uint32_t val;
};

union pmu_ebus_r_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_force_autoclkgate_cmu_cp0_configuration {
	struct {
		uint32_t local_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_force_autoclkgate_cmu_cp0_status {
	struct {
		uint32_t status:1; /* [0:0] */
		uint32_t rsvd1:15; /* [15:1] */
		uint32_t states:2; /* [17:16] */
		uint32_t rsvd0:14; /* [31:18] */
	};
	uint32_t val;
};

union pmu_force_autoclkgate_cmu_cp0_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_force_autoclkgate_cmu_cp0_duration0 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_force_autoclkgate_cmu_cp0_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_force_autoclkgate_cmu_cp0_duration2 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_force_autoclkgate_cmu_cp0_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_force_autoclkgate_cmu_cp1_configuration {
	struct {
		uint32_t local_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_force_autoclkgate_cmu_cp1_status {
	struct {
		uint32_t status:1; /* [0:0] */
		uint32_t rsvd1:15; /* [15:1] */
		uint32_t states:2; /* [17:16] */
		uint32_t rsvd0:14; /* [31:18] */
	};
	uint32_t val;
};

union pmu_force_autoclkgate_cmu_cp1_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_force_autoclkgate_cmu_cp1_duration0 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_force_autoclkgate_cmu_cp1_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_force_autoclkgate_cmu_cp1_duration2 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_force_autoclkgate_cmu_cp1_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_force_autoclkgate_cmu_pcie_configuration {
	struct {
		uint32_t local_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_force_autoclkgate_cmu_pcie_status {
	struct {
		uint32_t status:1; /* [0:0] */
		uint32_t rsvd1:15; /* [15:1] */
		uint32_t states:2; /* [17:16] */
		uint32_t rsvd0:14; /* [31:18] */
	};
	uint32_t val;
};

union pmu_force_autoclkgate_cmu_pcie_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_force_autoclkgate_cmu_pcie_duration0 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_force_autoclkgate_cmu_pcie_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_force_autoclkgate_cmu_pcie_duration2 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_force_autoclkgate_cmu_pcie_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_force_autoclkgate_cmu_dram_configuration {
	struct {
		uint32_t local_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_force_autoclkgate_cmu_dram_status {
	struct {
		uint32_t status:1; /* [0:0] */
		uint32_t rsvd1:15; /* [15:1] */
		uint32_t states:2; /* [17:16] */
		uint32_t rsvd0:14; /* [31:18] */
	};
	uint32_t val;
};

union pmu_force_autoclkgate_cmu_dram_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_force_autoclkgate_cmu_dram_duration0 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_force_autoclkgate_cmu_dram_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_force_autoclkgate_cmu_dram_duration2 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_force_autoclkgate_cmu_dram_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_force_autoclkgate_cmu_dcl0_configuration {
	struct {
		uint32_t local_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_force_autoclkgate_cmu_dcl0_status {
	struct {
		uint32_t status:1; /* [0:0] */
		uint32_t rsvd1:15; /* [15:1] */
		uint32_t states:2; /* [17:16] */
		uint32_t rsvd0:14; /* [31:18] */
	};
	uint32_t val;
};

union pmu_force_autoclkgate_cmu_dcl0_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_force_autoclkgate_cmu_dcl0_duration0 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_force_autoclkgate_cmu_dcl0_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_force_autoclkgate_cmu_dcl0_duration2 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_force_autoclkgate_cmu_dcl0_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_force_autoclkgate_cmu_dcl1_configuration {
	struct {
		uint32_t local_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_force_autoclkgate_cmu_dcl1_status {
	struct {
		uint32_t status:1; /* [0:0] */
		uint32_t rsvd1:15; /* [15:1] */
		uint32_t states:2; /* [17:16] */
		uint32_t rsvd0:14; /* [31:18] */
	};
	uint32_t val;
};

union pmu_force_autoclkgate_cmu_dcl1_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_force_autoclkgate_cmu_dcl1_duration0 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_force_autoclkgate_cmu_dcl1_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_force_autoclkgate_cmu_dcl1_duration2 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_force_autoclkgate_cmu_dcl1_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_force_autoclkgate_cmu_rbch00_configuration {
	struct {
		uint32_t local_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_force_autoclkgate_cmu_rbch00_status {
	struct {
		uint32_t status:1; /* [0:0] */
		uint32_t rsvd1:15; /* [15:1] */
		uint32_t states:2; /* [17:16] */
		uint32_t rsvd0:14; /* [31:18] */
	};
	uint32_t val;
};

union pmu_force_autoclkgate_cmu_rbch00_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_force_autoclkgate_cmu_rbch00_duration0 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_force_autoclkgate_cmu_rbch00_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_force_autoclkgate_cmu_rbch00_duration2 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_force_autoclkgate_cmu_rbch00_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_force_autoclkgate_cmu_rbch01_configuration {
	struct {
		uint32_t local_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_force_autoclkgate_cmu_rbch01_status {
	struct {
		uint32_t status:1; /* [0:0] */
		uint32_t rsvd1:15; /* [15:1] */
		uint32_t states:2; /* [17:16] */
		uint32_t rsvd0:14; /* [31:18] */
	};
	uint32_t val;
};

union pmu_force_autoclkgate_cmu_rbch01_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_force_autoclkgate_cmu_rbch01_duration0 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_force_autoclkgate_cmu_rbch01_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_force_autoclkgate_cmu_rbch01_duration2 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_force_autoclkgate_cmu_rbch01_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_force_autoclkgate_cmu_rbcv00_configuration {
	struct {
		uint32_t local_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_force_autoclkgate_cmu_rbcv00_status {
	struct {
		uint32_t status:1; /* [0:0] */
		uint32_t rsvd1:15; /* [15:1] */
		uint32_t states:2; /* [17:16] */
		uint32_t rsvd0:14; /* [31:18] */
	};
	uint32_t val;
};

union pmu_force_autoclkgate_cmu_rbcv00_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_force_autoclkgate_cmu_rbcv00_duration0 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_force_autoclkgate_cmu_rbcv00_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_force_autoclkgate_cmu_rbcv00_duration2 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_force_autoclkgate_cmu_rbcv00_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_force_autoclkgate_cmu_rbcv01_configuration {
	struct {
		uint32_t local_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_force_autoclkgate_cmu_rbcv01_status {
	struct {
		uint32_t status:1; /* [0:0] */
		uint32_t rsvd1:15; /* [15:1] */
		uint32_t states:2; /* [17:16] */
		uint32_t rsvd0:14; /* [31:18] */
	};
	uint32_t val;
};

union pmu_force_autoclkgate_cmu_rbcv01_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_force_autoclkgate_cmu_rbcv01_duration0 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_force_autoclkgate_cmu_rbcv01_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_force_autoclkgate_cmu_rbcv01_duration2 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_force_autoclkgate_cmu_rbcv01_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_force_autoclkgate_cmu_rbcv10_configuration {
	struct {
		uint32_t local_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_force_autoclkgate_cmu_rbcv10_status {
	struct {
		uint32_t status:1; /* [0:0] */
		uint32_t rsvd1:15; /* [15:1] */
		uint32_t states:2; /* [17:16] */
		uint32_t rsvd0:14; /* [31:18] */
	};
	uint32_t val;
};

union pmu_force_autoclkgate_cmu_rbcv10_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_force_autoclkgate_cmu_rbcv10_duration0 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_force_autoclkgate_cmu_rbcv10_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_force_autoclkgate_cmu_rbcv10_duration2 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_force_autoclkgate_cmu_rbcv10_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_force_autoclkgate_cmu_rbcv11_configuration {
	struct {
		uint32_t local_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_force_autoclkgate_cmu_rbcv11_status {
	struct {
		uint32_t status:1; /* [0:0] */
		uint32_t rsvd1:15; /* [15:1] */
		uint32_t states:2; /* [17:16] */
		uint32_t rsvd0:14; /* [31:18] */
	};
	uint32_t val;
};

union pmu_force_autoclkgate_cmu_rbcv11_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_force_autoclkgate_cmu_rbcv11_duration0 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_force_autoclkgate_cmu_rbcv11_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_force_autoclkgate_cmu_rbcv11_duration2 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_force_autoclkgate_cmu_rbcv11_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_force_autoclkgate_cmu_rot_configuration {
	struct {
		uint32_t local_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_force_autoclkgate_cmu_rot_status {
	struct {
		uint32_t status:1; /* [0:0] */
		uint32_t rsvd1:15; /* [15:1] */
		uint32_t states:2; /* [17:16] */
		uint32_t rsvd0:14; /* [31:18] */
	};
	uint32_t val;
};

union pmu_force_autoclkgate_cmu_rot_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_force_autoclkgate_cmu_rot_duration0 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_force_autoclkgate_cmu_rot_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_force_autoclkgate_cmu_rot_duration2 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_force_autoclkgate_cmu_rot_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_force_autoclkgate_cmu_peri0_configuration {
	struct {
		uint32_t local_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_force_autoclkgate_cmu_peri0_status {
	struct {
		uint32_t status:1; /* [0:0] */
		uint32_t rsvd1:15; /* [15:1] */
		uint32_t states:2; /* [17:16] */
		uint32_t rsvd0:14; /* [31:18] */
	};
	uint32_t val;
};

union pmu_force_autoclkgate_cmu_peri0_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_force_autoclkgate_cmu_peri0_duration0 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_force_autoclkgate_cmu_peri0_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_force_autoclkgate_cmu_peri0_duration2 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_force_autoclkgate_cmu_peri0_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_force_autoclkgate_cmu_peri1_configuration {
	struct {
		uint32_t local_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_force_autoclkgate_cmu_peri1_status {
	struct {
		uint32_t status:1; /* [0:0] */
		uint32_t rsvd1:15; /* [15:1] */
		uint32_t states:2; /* [17:16] */
		uint32_t rsvd0:14; /* [31:18] */
	};
	uint32_t val;
};

union pmu_force_autoclkgate_cmu_peri1_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_force_autoclkgate_cmu_peri1_duration0 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_force_autoclkgate_cmu_peri1_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_force_autoclkgate_cmu_peri1_duration2 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_force_autoclkgate_cmu_peri1_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_force_autoclkgate_cmu_sbus_u_configuration {
	struct {
		uint32_t local_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_force_autoclkgate_cmu_sbus_u_status {
	struct {
		uint32_t status:1; /* [0:0] */
		uint32_t rsvd1:15; /* [15:1] */
		uint32_t states:2; /* [17:16] */
		uint32_t rsvd0:14; /* [31:18] */
	};
	uint32_t val;
};

union pmu_force_autoclkgate_cmu_sbus_u_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_force_autoclkgate_cmu_sbus_u_duration0 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_force_autoclkgate_cmu_sbus_u_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_force_autoclkgate_cmu_sbus_u_duration2 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_force_autoclkgate_cmu_sbus_u_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_force_autoclkgate_cmu_sbus_d_configuration {
	struct {
		uint32_t local_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_force_autoclkgate_cmu_sbus_d_status {
	struct {
		uint32_t status:1; /* [0:0] */
		uint32_t rsvd1:15; /* [15:1] */
		uint32_t states:2; /* [17:16] */
		uint32_t rsvd0:14; /* [31:18] */
	};
	uint32_t val;
};

union pmu_force_autoclkgate_cmu_sbus_d_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_force_autoclkgate_cmu_sbus_d_duration0 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_force_autoclkgate_cmu_sbus_d_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_force_autoclkgate_cmu_sbus_d_duration2 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_force_autoclkgate_cmu_sbus_d_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_force_autoclkgate_cmu_sbus_l_configuration {
	struct {
		uint32_t local_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_force_autoclkgate_cmu_sbus_l_status {
	struct {
		uint32_t status:1; /* [0:0] */
		uint32_t rsvd1:15; /* [15:1] */
		uint32_t states:2; /* [17:16] */
		uint32_t rsvd0:14; /* [31:18] */
	};
	uint32_t val;
};

union pmu_force_autoclkgate_cmu_sbus_l_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_force_autoclkgate_cmu_sbus_l_duration0 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_force_autoclkgate_cmu_sbus_l_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_force_autoclkgate_cmu_sbus_l_duration2 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_force_autoclkgate_cmu_sbus_l_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_force_autoclkgate_cmu_nbus_u_configuration {
	struct {
		uint32_t local_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_force_autoclkgate_cmu_nbus_u_status {
	struct {
		uint32_t status:1; /* [0:0] */
		uint32_t rsvd1:15; /* [15:1] */
		uint32_t states:2; /* [17:16] */
		uint32_t rsvd0:14; /* [31:18] */
	};
	uint32_t val;
};

union pmu_force_autoclkgate_cmu_nbus_u_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_force_autoclkgate_cmu_nbus_u_duration0 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_force_autoclkgate_cmu_nbus_u_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_force_autoclkgate_cmu_nbus_u_duration2 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_force_autoclkgate_cmu_nbus_u_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_force_autoclkgate_cmu_nbus_d_configuration {
	struct {
		uint32_t local_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_force_autoclkgate_cmu_nbus_d_status {
	struct {
		uint32_t status:1; /* [0:0] */
		uint32_t rsvd1:15; /* [15:1] */
		uint32_t states:2; /* [17:16] */
		uint32_t rsvd0:14; /* [31:18] */
	};
	uint32_t val;
};

union pmu_force_autoclkgate_cmu_nbus_d_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_force_autoclkgate_cmu_nbus_d_duration0 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_force_autoclkgate_cmu_nbus_d_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_force_autoclkgate_cmu_nbus_d_duration2 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_force_autoclkgate_cmu_nbus_d_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_force_autoclkgate_cmu_nbus_l_configuration {
	struct {
		uint32_t local_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_force_autoclkgate_cmu_nbus_l_status {
	struct {
		uint32_t status:1; /* [0:0] */
		uint32_t rsvd1:15; /* [15:1] */
		uint32_t states:2; /* [17:16] */
		uint32_t rsvd0:14; /* [31:18] */
	};
	uint32_t val;
};

union pmu_force_autoclkgate_cmu_nbus_l_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_force_autoclkgate_cmu_nbus_l_duration0 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_force_autoclkgate_cmu_nbus_l_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_force_autoclkgate_cmu_nbus_l_duration2 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_force_autoclkgate_cmu_nbus_l_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_force_autoclkgate_cmu_wbus_u_configuration {
	struct {
		uint32_t local_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_force_autoclkgate_cmu_wbus_u_status {
	struct {
		uint32_t status:1; /* [0:0] */
		uint32_t rsvd1:15; /* [15:1] */
		uint32_t states:2; /* [17:16] */
		uint32_t rsvd0:14; /* [31:18] */
	};
	uint32_t val;
};

union pmu_force_autoclkgate_cmu_wbus_u_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_force_autoclkgate_cmu_wbus_u_duration0 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_force_autoclkgate_cmu_wbus_u_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_force_autoclkgate_cmu_wbus_u_duration2 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_force_autoclkgate_cmu_wbus_u_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_force_autoclkgate_cmu_wbus_d_configuration {
	struct {
		uint32_t local_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_force_autoclkgate_cmu_wbus_d_status {
	struct {
		uint32_t status:1; /* [0:0] */
		uint32_t rsvd1:15; /* [15:1] */
		uint32_t states:2; /* [17:16] */
		uint32_t rsvd0:14; /* [31:18] */
	};
	uint32_t val;
};

union pmu_force_autoclkgate_cmu_wbus_d_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_force_autoclkgate_cmu_wbus_d_duration0 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_force_autoclkgate_cmu_wbus_d_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_force_autoclkgate_cmu_wbus_d_duration2 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_force_autoclkgate_cmu_wbus_d_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_force_autoclkgate_cmu_ebus_u_configuration {
	struct {
		uint32_t local_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_force_autoclkgate_cmu_ebus_u_status {
	struct {
		uint32_t status:1; /* [0:0] */
		uint32_t rsvd1:15; /* [15:1] */
		uint32_t states:2; /* [17:16] */
		uint32_t rsvd0:14; /* [31:18] */
	};
	uint32_t val;
};

union pmu_force_autoclkgate_cmu_ebus_u_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_force_autoclkgate_cmu_ebus_u_duration0 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_force_autoclkgate_cmu_ebus_u_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_force_autoclkgate_cmu_ebus_u_duration2 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_force_autoclkgate_cmu_ebus_u_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_force_autoclkgate_cmu_ebus_d_configuration {
	struct {
		uint32_t local_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_force_autoclkgate_cmu_ebus_d_status {
	struct {
		uint32_t status:1; /* [0:0] */
		uint32_t rsvd1:15; /* [15:1] */
		uint32_t states:2; /* [17:16] */
		uint32_t rsvd0:14; /* [31:18] */
	};
	uint32_t val;
};

union pmu_force_autoclkgate_cmu_ebus_d_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_force_autoclkgate_cmu_ebus_d_duration0 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_force_autoclkgate_cmu_ebus_d_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_force_autoclkgate_cmu_ebus_d_duration2 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_force_autoclkgate_cmu_ebus_d_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_force_autoclkgate_cmu_ebus_r_configuration {
	struct {
		uint32_t local_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_force_autoclkgate_cmu_ebus_r_status {
	struct {
		uint32_t status:1; /* [0:0] */
		uint32_t rsvd1:15; /* [15:1] */
		uint32_t states:2; /* [17:16] */
		uint32_t rsvd0:14; /* [31:18] */
	};
	uint32_t val;
};

union pmu_force_autoclkgate_cmu_ebus_r_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_force_autoclkgate_cmu_ebus_r_duration0 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_force_autoclkgate_cmu_ebus_r_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_force_autoclkgate_cmu_ebus_r_duration2 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_force_autoclkgate_cmu_ebus_r_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_clkstop_cmu_cp0_configuration {
	struct {
		uint32_t local_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_clkstop_cmu_cp0_status {
	struct {
		uint32_t status:1; /* [0:0] */
		uint32_t rsvd1:15; /* [15:1] */
		uint32_t states:2; /* [17:16] */
		uint32_t rsvd0:14; /* [31:18] */
	};
	uint32_t val;
};

union pmu_clkstop_cmu_cp0_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_clkstop_cmu_cp0_duration0 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_clkstop_cmu_cp0_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_clkstop_cmu_cp0_duration2 {
	struct {
		uint32_t rsvd1:16; /* [15:0] */
		uint32_t dur_up_clkstop:4; /* [19:16] */
		uint32_t rsvd0:12; /* [31:20] */
	};
	uint32_t val;
};

union pmu_clkstop_cmu_cp0_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_clkstop_cmu_cp1_configuration {
	struct {
		uint32_t local_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_clkstop_cmu_cp1_status {
	struct {
		uint32_t status:1; /* [0:0] */
		uint32_t rsvd1:15; /* [15:1] */
		uint32_t states:2; /* [17:16] */
		uint32_t rsvd0:14; /* [31:18] */
	};
	uint32_t val;
};

union pmu_clkstop_cmu_cp1_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_clkstop_cmu_cp1_duration0 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_clkstop_cmu_cp1_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_clkstop_cmu_cp1_duration2 {
	struct {
		uint32_t rsvd1:16; /* [15:0] */
		uint32_t dur_up_clkstop:4; /* [19:16] */
		uint32_t rsvd0:12; /* [31:20] */
	};
	uint32_t val;
};

union pmu_clkstop_cmu_cp1_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_clkstop_cmu_pcie_configuration {
	struct {
		uint32_t local_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_clkstop_cmu_pcie_status {
	struct {
		uint32_t status:1; /* [0:0] */
		uint32_t rsvd1:15; /* [15:1] */
		uint32_t states:2; /* [17:16] */
		uint32_t rsvd0:14; /* [31:18] */
	};
	uint32_t val;
};

union pmu_clkstop_cmu_pcie_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_clkstop_cmu_pcie_duration0 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_clkstop_cmu_pcie_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_clkstop_cmu_pcie_duration2 {
	struct {
		uint32_t rsvd1:16; /* [15:0] */
		uint32_t dur_up_clkstop:4; /* [19:16] */
		uint32_t rsvd0:12; /* [31:20] */
	};
	uint32_t val;
};

union pmu_clkstop_cmu_pcie_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_clkstop_cmu_dram_configuration {
	struct {
		uint32_t local_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_clkstop_cmu_dram_status {
	struct {
		uint32_t status:1; /* [0:0] */
		uint32_t rsvd1:15; /* [15:1] */
		uint32_t states:2; /* [17:16] */
		uint32_t rsvd0:14; /* [31:18] */
	};
	uint32_t val;
};

union pmu_clkstop_cmu_dram_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_clkstop_cmu_dram_duration0 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_clkstop_cmu_dram_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_clkstop_cmu_dram_duration2 {
	struct {
		uint32_t rsvd1:16; /* [15:0] */
		uint32_t dur_up_clkstop:4; /* [19:16] */
		uint32_t rsvd0:12; /* [31:20] */
	};
	uint32_t val;
};

union pmu_clkstop_cmu_dram_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_clkstop_cmu_dcl0_configuration {
	struct {
		uint32_t local_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_clkstop_cmu_dcl0_status {
	struct {
		uint32_t status:1; /* [0:0] */
		uint32_t rsvd1:15; /* [15:1] */
		uint32_t states:2; /* [17:16] */
		uint32_t rsvd0:14; /* [31:18] */
	};
	uint32_t val;
};

union pmu_clkstop_cmu_dcl0_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_clkstop_cmu_dcl0_duration0 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_clkstop_cmu_dcl0_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_clkstop_cmu_dcl0_duration2 {
	struct {
		uint32_t rsvd1:16; /* [15:0] */
		uint32_t dur_up_clkstop:4; /* [19:16] */
		uint32_t rsvd0:12; /* [31:20] */
	};
	uint32_t val;
};

union pmu_clkstop_cmu_dcl0_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_clkstop_cmu_dcl1_configuration {
	struct {
		uint32_t local_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_clkstop_cmu_dcl1_status {
	struct {
		uint32_t status:1; /* [0:0] */
		uint32_t rsvd1:15; /* [15:1] */
		uint32_t states:2; /* [17:16] */
		uint32_t rsvd0:14; /* [31:18] */
	};
	uint32_t val;
};

union pmu_clkstop_cmu_dcl1_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_clkstop_cmu_dcl1_duration0 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_clkstop_cmu_dcl1_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_clkstop_cmu_dcl1_duration2 {
	struct {
		uint32_t rsvd1:16; /* [15:0] */
		uint32_t dur_up_clkstop:4; /* [19:16] */
		uint32_t rsvd0:12; /* [31:20] */
	};
	uint32_t val;
};

union pmu_clkstop_cmu_dcl1_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_clkstop_cmu_rbch00_configuration {
	struct {
		uint32_t local_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_clkstop_cmu_rbch00_status {
	struct {
		uint32_t status:1; /* [0:0] */
		uint32_t rsvd1:15; /* [15:1] */
		uint32_t states:2; /* [17:16] */
		uint32_t rsvd0:14; /* [31:18] */
	};
	uint32_t val;
};

union pmu_clkstop_cmu_rbch00_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_clkstop_cmu_rbch00_duration0 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_clkstop_cmu_rbch00_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_clkstop_cmu_rbch00_duration2 {
	struct {
		uint32_t rsvd1:16; /* [15:0] */
		uint32_t dur_up_clkstop:4; /* [19:16] */
		uint32_t rsvd0:12; /* [31:20] */
	};
	uint32_t val;
};

union pmu_clkstop_cmu_rbch00_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_clkstop_cmu_rbch01_configuration {
	struct {
		uint32_t local_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_clkstop_cmu_rbch01_status {
	struct {
		uint32_t status:1; /* [0:0] */
		uint32_t rsvd1:15; /* [15:1] */
		uint32_t states:2; /* [17:16] */
		uint32_t rsvd0:14; /* [31:18] */
	};
	uint32_t val;
};

union pmu_clkstop_cmu_rbch01_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_clkstop_cmu_rbch01_duration0 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_clkstop_cmu_rbch01_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_clkstop_cmu_rbch01_duration2 {
	struct {
		uint32_t rsvd1:16; /* [15:0] */
		uint32_t dur_up_clkstop:4; /* [19:16] */
		uint32_t rsvd0:12; /* [31:20] */
	};
	uint32_t val;
};

union pmu_clkstop_cmu_rbch01_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_clkstop_cmu_rbcv00_configuration {
	struct {
		uint32_t local_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_clkstop_cmu_rbcv00_status {
	struct {
		uint32_t status:1; /* [0:0] */
		uint32_t rsvd1:15; /* [15:1] */
		uint32_t states:2; /* [17:16] */
		uint32_t rsvd0:14; /* [31:18] */
	};
	uint32_t val;
};

union pmu_clkstop_cmu_rbcv00_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_clkstop_cmu_rbcv00_duration0 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_clkstop_cmu_rbcv00_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_clkstop_cmu_rbcv00_duration2 {
	struct {
		uint32_t rsvd1:16; /* [15:0] */
		uint32_t dur_up_clkstop:4; /* [19:16] */
		uint32_t rsvd0:12; /* [31:20] */
	};
	uint32_t val;
};

union pmu_clkstop_cmu_rbcv00_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_clkstop_cmu_rbcv01_configuration {
	struct {
		uint32_t local_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_clkstop_cmu_rbcv01_status {
	struct {
		uint32_t status:1; /* [0:0] */
		uint32_t rsvd1:15; /* [15:1] */
		uint32_t states:2; /* [17:16] */
		uint32_t rsvd0:14; /* [31:18] */
	};
	uint32_t val;
};

union pmu_clkstop_cmu_rbcv01_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_clkstop_cmu_rbcv01_duration0 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_clkstop_cmu_rbcv01_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_clkstop_cmu_rbcv01_duration2 {
	struct {
		uint32_t rsvd1:16; /* [15:0] */
		uint32_t dur_up_clkstop:4; /* [19:16] */
		uint32_t rsvd0:12; /* [31:20] */
	};
	uint32_t val;
};

union pmu_clkstop_cmu_rbcv01_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_clkstop_cmu_rbcv10_configuration {
	struct {
		uint32_t local_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_clkstop_cmu_rbcv10_status {
	struct {
		uint32_t status:1; /* [0:0] */
		uint32_t rsvd1:15; /* [15:1] */
		uint32_t states:2; /* [17:16] */
		uint32_t rsvd0:14; /* [31:18] */
	};
	uint32_t val;
};

union pmu_clkstop_cmu_rbcv10_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_clkstop_cmu_rbcv10_duration0 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_clkstop_cmu_rbcv10_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_clkstop_cmu_rbcv10_duration2 {
	struct {
		uint32_t rsvd1:16; /* [15:0] */
		uint32_t dur_up_clkstop:4; /* [19:16] */
		uint32_t rsvd0:12; /* [31:20] */
	};
	uint32_t val;
};

union pmu_clkstop_cmu_rbcv10_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_clkstop_cmu_rbcv11_configuration {
	struct {
		uint32_t local_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_clkstop_cmu_rbcv11_status {
	struct {
		uint32_t status:1; /* [0:0] */
		uint32_t rsvd1:15; /* [15:1] */
		uint32_t states:2; /* [17:16] */
		uint32_t rsvd0:14; /* [31:18] */
	};
	uint32_t val;
};

union pmu_clkstop_cmu_rbcv11_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_clkstop_cmu_rbcv11_duration0 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_clkstop_cmu_rbcv11_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_clkstop_cmu_rbcv11_duration2 {
	struct {
		uint32_t rsvd1:16; /* [15:0] */
		uint32_t dur_up_clkstop:4; /* [19:16] */
		uint32_t rsvd0:12; /* [31:20] */
	};
	uint32_t val;
};

union pmu_clkstop_cmu_rbcv11_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_clkstop_cmu_rot_configuration {
	struct {
		uint32_t local_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_clkstop_cmu_rot_status {
	struct {
		uint32_t status:1; /* [0:0] */
		uint32_t rsvd1:15; /* [15:1] */
		uint32_t states:2; /* [17:16] */
		uint32_t rsvd0:14; /* [31:18] */
	};
	uint32_t val;
};

union pmu_clkstop_cmu_rot_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_clkstop_cmu_rot_duration0 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_clkstop_cmu_rot_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_clkstop_cmu_rot_duration2 {
	struct {
		uint32_t rsvd1:16; /* [15:0] */
		uint32_t dur_up_clkstop:4; /* [19:16] */
		uint32_t rsvd0:12; /* [31:20] */
	};
	uint32_t val;
};

union pmu_clkstop_cmu_rot_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_clkstop_cmu_peri0_configuration {
	struct {
		uint32_t local_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_clkstop_cmu_peri0_status {
	struct {
		uint32_t status:1; /* [0:0] */
		uint32_t rsvd1:15; /* [15:1] */
		uint32_t states:2; /* [17:16] */
		uint32_t rsvd0:14; /* [31:18] */
	};
	uint32_t val;
};

union pmu_clkstop_cmu_peri0_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_clkstop_cmu_peri0_duration0 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_clkstop_cmu_peri0_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_clkstop_cmu_peri0_duration2 {
	struct {
		uint32_t rsvd1:16; /* [15:0] */
		uint32_t dur_up_clkstop:4; /* [19:16] */
		uint32_t rsvd0:12; /* [31:20] */
	};
	uint32_t val;
};

union pmu_clkstop_cmu_peri0_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_clkstop_cmu_peri1_configuration {
	struct {
		uint32_t local_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_clkstop_cmu_peri1_status {
	struct {
		uint32_t status:1; /* [0:0] */
		uint32_t rsvd1:15; /* [15:1] */
		uint32_t states:2; /* [17:16] */
		uint32_t rsvd0:14; /* [31:18] */
	};
	uint32_t val;
};

union pmu_clkstop_cmu_peri1_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_clkstop_cmu_peri1_duration0 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_clkstop_cmu_peri1_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_clkstop_cmu_peri1_duration2 {
	struct {
		uint32_t rsvd1:16; /* [15:0] */
		uint32_t dur_up_clkstop:4; /* [19:16] */
		uint32_t rsvd0:12; /* [31:20] */
	};
	uint32_t val;
};

union pmu_clkstop_cmu_peri1_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_clkstop_cmu_sbus_u_configuration {
	struct {
		uint32_t local_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_clkstop_cmu_sbus_u_status {
	struct {
		uint32_t status:1; /* [0:0] */
		uint32_t rsvd1:15; /* [15:1] */
		uint32_t states:2; /* [17:16] */
		uint32_t rsvd0:14; /* [31:18] */
	};
	uint32_t val;
};

union pmu_clkstop_cmu_sbus_u_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_clkstop_cmu_sbus_u_duration0 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_clkstop_cmu_sbus_u_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_clkstop_cmu_sbus_u_duration2 {
	struct {
		uint32_t rsvd1:16; /* [15:0] */
		uint32_t dur_up_clkstop:4; /* [19:16] */
		uint32_t rsvd0:12; /* [31:20] */
	};
	uint32_t val;
};

union pmu_clkstop_cmu_sbus_u_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_clkstop_cmu_sbus_d_configuration {
	struct {
		uint32_t local_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_clkstop_cmu_sbus_d_status {
	struct {
		uint32_t status:1; /* [0:0] */
		uint32_t rsvd1:15; /* [15:1] */
		uint32_t states:2; /* [17:16] */
		uint32_t rsvd0:14; /* [31:18] */
	};
	uint32_t val;
};

union pmu_clkstop_cmu_sbus_d_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_clkstop_cmu_sbus_d_duration0 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_clkstop_cmu_sbus_d_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_clkstop_cmu_sbus_d_duration2 {
	struct {
		uint32_t rsvd1:16; /* [15:0] */
		uint32_t dur_up_clkstop:4; /* [19:16] */
		uint32_t rsvd0:12; /* [31:20] */
	};
	uint32_t val;
};

union pmu_clkstop_cmu_sbus_d_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_clkstop_cmu_sbus_l_configuration {
	struct {
		uint32_t local_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_clkstop_cmu_sbus_l_status {
	struct {
		uint32_t status:1; /* [0:0] */
		uint32_t rsvd1:15; /* [15:1] */
		uint32_t states:2; /* [17:16] */
		uint32_t rsvd0:14; /* [31:18] */
	};
	uint32_t val;
};

union pmu_clkstop_cmu_sbus_l_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_clkstop_cmu_sbus_l_duration0 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_clkstop_cmu_sbus_l_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_clkstop_cmu_sbus_l_duration2 {
	struct {
		uint32_t rsvd1:16; /* [15:0] */
		uint32_t dur_up_clkstop:4; /* [19:16] */
		uint32_t rsvd0:12; /* [31:20] */
	};
	uint32_t val;
};

union pmu_clkstop_cmu_sbus_l_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_clkstop_cmu_nbus_u_configuration {
	struct {
		uint32_t local_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_clkstop_cmu_nbus_u_status {
	struct {
		uint32_t status:1; /* [0:0] */
		uint32_t rsvd1:15; /* [15:1] */
		uint32_t states:2; /* [17:16] */
		uint32_t rsvd0:14; /* [31:18] */
	};
	uint32_t val;
};

union pmu_clkstop_cmu_nbus_u_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_clkstop_cmu_nbus_u_duration0 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_clkstop_cmu_nbus_u_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_clkstop_cmu_nbus_u_duration2 {
	struct {
		uint32_t rsvd1:16; /* [15:0] */
		uint32_t dur_up_clkstop:4; /* [19:16] */
		uint32_t rsvd0:12; /* [31:20] */
	};
	uint32_t val;
};

union pmu_clkstop_cmu_nbus_u_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_clkstop_cmu_nbus_d_configuration {
	struct {
		uint32_t local_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_clkstop_cmu_nbus_d_status {
	struct {
		uint32_t status:1; /* [0:0] */
		uint32_t rsvd1:15; /* [15:1] */
		uint32_t states:2; /* [17:16] */
		uint32_t rsvd0:14; /* [31:18] */
	};
	uint32_t val;
};

union pmu_clkstop_cmu_nbus_d_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_clkstop_cmu_nbus_d_duration0 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_clkstop_cmu_nbus_d_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_clkstop_cmu_nbus_d_duration2 {
	struct {
		uint32_t rsvd1:16; /* [15:0] */
		uint32_t dur_up_clkstop:4; /* [19:16] */
		uint32_t rsvd0:12; /* [31:20] */
	};
	uint32_t val;
};

union pmu_clkstop_cmu_nbus_d_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_clkstop_cmu_nbus_l_configuration {
	struct {
		uint32_t local_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_clkstop_cmu_nbus_l_status {
	struct {
		uint32_t status:1; /* [0:0] */
		uint32_t rsvd1:15; /* [15:1] */
		uint32_t states:2; /* [17:16] */
		uint32_t rsvd0:14; /* [31:18] */
	};
	uint32_t val;
};

union pmu_clkstop_cmu_nbus_l_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_clkstop_cmu_nbus_l_duration0 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_clkstop_cmu_nbus_l_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_clkstop_cmu_nbus_l_duration2 {
	struct {
		uint32_t rsvd1:16; /* [15:0] */
		uint32_t dur_up_clkstop:4; /* [19:16] */
		uint32_t rsvd0:12; /* [31:20] */
	};
	uint32_t val;
};

union pmu_clkstop_cmu_nbus_l_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_clkstop_cmu_wbus_u_configuration {
	struct {
		uint32_t local_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_clkstop_cmu_wbus_u_status {
	struct {
		uint32_t status:1; /* [0:0] */
		uint32_t rsvd1:15; /* [15:1] */
		uint32_t states:2; /* [17:16] */
		uint32_t rsvd0:14; /* [31:18] */
	};
	uint32_t val;
};

union pmu_clkstop_cmu_wbus_u_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_clkstop_cmu_wbus_u_duration0 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_clkstop_cmu_wbus_u_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_clkstop_cmu_wbus_u_duration2 {
	struct {
		uint32_t rsvd1:16; /* [15:0] */
		uint32_t dur_up_clkstop:4; /* [19:16] */
		uint32_t rsvd0:12; /* [31:20] */
	};
	uint32_t val;
};

union pmu_clkstop_cmu_wbus_u_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_clkstop_cmu_wbus_d_configuration {
	struct {
		uint32_t local_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_clkstop_cmu_wbus_d_status {
	struct {
		uint32_t status:1; /* [0:0] */
		uint32_t rsvd1:15; /* [15:1] */
		uint32_t states:2; /* [17:16] */
		uint32_t rsvd0:14; /* [31:18] */
	};
	uint32_t val;
};

union pmu_clkstop_cmu_wbus_d_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_clkstop_cmu_wbus_d_duration0 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_clkstop_cmu_wbus_d_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_clkstop_cmu_wbus_d_duration2 {
	struct {
		uint32_t rsvd1:16; /* [15:0] */
		uint32_t dur_up_clkstop:4; /* [19:16] */
		uint32_t rsvd0:12; /* [31:20] */
	};
	uint32_t val;
};

union pmu_clkstop_cmu_wbus_d_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_clkstop_cmu_ebus_u_configuration {
	struct {
		uint32_t local_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_clkstop_cmu_ebus_u_status {
	struct {
		uint32_t status:1; /* [0:0] */
		uint32_t rsvd1:15; /* [15:1] */
		uint32_t states:2; /* [17:16] */
		uint32_t rsvd0:14; /* [31:18] */
	};
	uint32_t val;
};

union pmu_clkstop_cmu_ebus_u_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_clkstop_cmu_ebus_u_duration0 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_clkstop_cmu_ebus_u_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_clkstop_cmu_ebus_u_duration2 {
	struct {
		uint32_t rsvd1:16; /* [15:0] */
		uint32_t dur_up_clkstop:4; /* [19:16] */
		uint32_t rsvd0:12; /* [31:20] */
	};
	uint32_t val;
};

union pmu_clkstop_cmu_ebus_u_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_clkstop_cmu_ebus_d_configuration {
	struct {
		uint32_t local_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_clkstop_cmu_ebus_d_status {
	struct {
		uint32_t status:1; /* [0:0] */
		uint32_t rsvd1:15; /* [15:1] */
		uint32_t states:2; /* [17:16] */
		uint32_t rsvd0:14; /* [31:18] */
	};
	uint32_t val;
};

union pmu_clkstop_cmu_ebus_d_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_clkstop_cmu_ebus_d_duration0 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_clkstop_cmu_ebus_d_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_clkstop_cmu_ebus_d_duration2 {
	struct {
		uint32_t rsvd1:16; /* [15:0] */
		uint32_t dur_up_clkstop:4; /* [19:16] */
		uint32_t rsvd0:12; /* [31:20] */
	};
	uint32_t val;
};

union pmu_clkstop_cmu_ebus_d_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_clkstop_cmu_ebus_r_configuration {
	struct {
		uint32_t local_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_clkstop_cmu_ebus_r_status {
	struct {
		uint32_t status:1; /* [0:0] */
		uint32_t rsvd1:15; /* [15:1] */
		uint32_t states:2; /* [17:16] */
		uint32_t rsvd0:14; /* [31:18] */
	};
	uint32_t val;
};

union pmu_clkstop_cmu_ebus_r_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_clkstop_cmu_ebus_r_duration0 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_clkstop_cmu_ebus_r_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_clkstop_cmu_ebus_r_duration2 {
	struct {
		uint32_t rsvd1:16; /* [15:0] */
		uint32_t dur_up_clkstop:4; /* [19:16] */
		uint32_t rsvd0:12; /* [31:20] */
	};
	uint32_t val;
};

union pmu_clkstop_cmu_ebus_r_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_disable_pll_cmu_cp0_configuration {
	struct {
		uint32_t local_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_disable_pll_cmu_cp0_status {
	struct {
		uint32_t status:1; /* [0:0] */
		uint32_t rsvd1:15; /* [15:1] */
		uint32_t states:2; /* [17:16] */
		uint32_t rsvd0:14; /* [31:18] */
	};
	uint32_t val;
};

union pmu_disable_pll_cmu_cp0_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_disable_pll_cmu_cp0_duration0 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_disable_pll_cmu_cp0_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_disable_pll_cmu_cp0_duration2 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_disable_pll_cmu_cp0_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_disable_pll_cmu_cp1_configuration {
	struct {
		uint32_t local_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_disable_pll_cmu_cp1_status {
	struct {
		uint32_t status:1; /* [0:0] */
		uint32_t rsvd1:15; /* [15:1] */
		uint32_t states:2; /* [17:16] */
		uint32_t rsvd0:14; /* [31:18] */
	};
	uint32_t val;
};

union pmu_disable_pll_cmu_cp1_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_disable_pll_cmu_cp1_duration0 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_disable_pll_cmu_cp1_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_disable_pll_cmu_cp1_duration2 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_disable_pll_cmu_cp1_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_disable_pll_cmu_pcie_configuration {
	struct {
		uint32_t local_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_disable_pll_cmu_pcie_status {
	struct {
		uint32_t status:1; /* [0:0] */
		uint32_t rsvd1:15; /* [15:1] */
		uint32_t states:2; /* [17:16] */
		uint32_t rsvd0:14; /* [31:18] */
	};
	uint32_t val;
};

union pmu_disable_pll_cmu_pcie_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_disable_pll_cmu_pcie_duration0 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_disable_pll_cmu_pcie_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_disable_pll_cmu_pcie_duration2 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_disable_pll_cmu_pcie_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_disable_pll_cmu_dram_configuration {
	struct {
		uint32_t local_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_disable_pll_cmu_dram_status {
	struct {
		uint32_t status:1; /* [0:0] */
		uint32_t rsvd1:15; /* [15:1] */
		uint32_t states:2; /* [17:16] */
		uint32_t rsvd0:14; /* [31:18] */
	};
	uint32_t val;
};

union pmu_disable_pll_cmu_dram_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_disable_pll_cmu_dram_duration0 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_disable_pll_cmu_dram_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_disable_pll_cmu_dram_duration2 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_disable_pll_cmu_dram_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_disable_pll_cmu_dcl0_configuration {
	struct {
		uint32_t local_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_disable_pll_cmu_dcl0_status {
	struct {
		uint32_t status:1; /* [0:0] */
		uint32_t rsvd1:15; /* [15:1] */
		uint32_t states:2; /* [17:16] */
		uint32_t rsvd0:14; /* [31:18] */
	};
	uint32_t val;
};

union pmu_disable_pll_cmu_dcl0_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_disable_pll_cmu_dcl0_duration0 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_disable_pll_cmu_dcl0_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_disable_pll_cmu_dcl0_duration2 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_disable_pll_cmu_dcl0_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_disable_pll_cmu_dcl1_configuration {
	struct {
		uint32_t local_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_disable_pll_cmu_dcl1_status {
	struct {
		uint32_t status:1; /* [0:0] */
		uint32_t rsvd1:15; /* [15:1] */
		uint32_t states:2; /* [17:16] */
		uint32_t rsvd0:14; /* [31:18] */
	};
	uint32_t val;
};

union pmu_disable_pll_cmu_dcl1_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_disable_pll_cmu_dcl1_duration0 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_disable_pll_cmu_dcl1_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_disable_pll_cmu_dcl1_duration2 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_disable_pll_cmu_dcl1_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_disable_pll_cmu_rbch00_configuration {
	struct {
		uint32_t local_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_disable_pll_cmu_rbch00_status {
	struct {
		uint32_t status:1; /* [0:0] */
		uint32_t rsvd1:15; /* [15:1] */
		uint32_t states:2; /* [17:16] */
		uint32_t rsvd0:14; /* [31:18] */
	};
	uint32_t val;
};

union pmu_disable_pll_cmu_rbch00_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_disable_pll_cmu_rbch00_duration0 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_disable_pll_cmu_rbch00_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_disable_pll_cmu_rbch00_duration2 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_disable_pll_cmu_rbch00_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_disable_pll_cmu_rbch01_configuration {
	struct {
		uint32_t local_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_disable_pll_cmu_rbch01_status {
	struct {
		uint32_t status:1; /* [0:0] */
		uint32_t rsvd1:15; /* [15:1] */
		uint32_t states:2; /* [17:16] */
		uint32_t rsvd0:14; /* [31:18] */
	};
	uint32_t val;
};

union pmu_disable_pll_cmu_rbch01_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_disable_pll_cmu_rbch01_duration0 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_disable_pll_cmu_rbch01_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_disable_pll_cmu_rbch01_duration2 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_disable_pll_cmu_rbch01_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_disable_pll_cmu_rbcv00_configuration {
	struct {
		uint32_t local_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_disable_pll_cmu_rbcv00_status {
	struct {
		uint32_t status:1; /* [0:0] */
		uint32_t rsvd1:15; /* [15:1] */
		uint32_t states:2; /* [17:16] */
		uint32_t rsvd0:14; /* [31:18] */
	};
	uint32_t val;
};

union pmu_disable_pll_cmu_rbcv00_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_disable_pll_cmu_rbcv00_duration0 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_disable_pll_cmu_rbcv00_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_disable_pll_cmu_rbcv00_duration2 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_disable_pll_cmu_rbcv00_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_disable_pll_cmu_rbcv01_configuration {
	struct {
		uint32_t local_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_disable_pll_cmu_rbcv01_status {
	struct {
		uint32_t status:1; /* [0:0] */
		uint32_t rsvd1:15; /* [15:1] */
		uint32_t states:2; /* [17:16] */
		uint32_t rsvd0:14; /* [31:18] */
	};
	uint32_t val;
};

union pmu_disable_pll_cmu_rbcv01_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_disable_pll_cmu_rbcv01_duration0 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_disable_pll_cmu_rbcv01_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_disable_pll_cmu_rbcv01_duration2 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_disable_pll_cmu_rbcv01_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_disable_pll_cmu_rbcv10_configuration {
	struct {
		uint32_t local_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_disable_pll_cmu_rbcv10_status {
	struct {
		uint32_t status:1; /* [0:0] */
		uint32_t rsvd1:15; /* [15:1] */
		uint32_t states:2; /* [17:16] */
		uint32_t rsvd0:14; /* [31:18] */
	};
	uint32_t val;
};

union pmu_disable_pll_cmu_rbcv10_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_disable_pll_cmu_rbcv10_duration0 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_disable_pll_cmu_rbcv10_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_disable_pll_cmu_rbcv10_duration2 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_disable_pll_cmu_rbcv10_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_disable_pll_cmu_rbcv11_configuration {
	struct {
		uint32_t local_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_disable_pll_cmu_rbcv11_status {
	struct {
		uint32_t status:1; /* [0:0] */
		uint32_t rsvd1:15; /* [15:1] */
		uint32_t states:2; /* [17:16] */
		uint32_t rsvd0:14; /* [31:18] */
	};
	uint32_t val;
};

union pmu_disable_pll_cmu_rbcv11_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_disable_pll_cmu_rbcv11_duration0 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_disable_pll_cmu_rbcv11_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_disable_pll_cmu_rbcv11_duration2 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_disable_pll_cmu_rbcv11_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_disable_pll_cmu_rot_configuration {
	struct {
		uint32_t local_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_disable_pll_cmu_rot_status {
	struct {
		uint32_t status:1; /* [0:0] */
		uint32_t rsvd1:15; /* [15:1] */
		uint32_t states:2; /* [17:16] */
		uint32_t rsvd0:14; /* [31:18] */
	};
	uint32_t val;
};

union pmu_disable_pll_cmu_rot_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_disable_pll_cmu_rot_duration0 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_disable_pll_cmu_rot_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_disable_pll_cmu_rot_duration2 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_disable_pll_cmu_rot_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_disable_pll_cmu_peri0_configuration {
	struct {
		uint32_t local_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_disable_pll_cmu_peri0_status {
	struct {
		uint32_t status:1; /* [0:0] */
		uint32_t rsvd1:15; /* [15:1] */
		uint32_t states:2; /* [17:16] */
		uint32_t rsvd0:14; /* [31:18] */
	};
	uint32_t val;
};

union pmu_disable_pll_cmu_peri0_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_disable_pll_cmu_peri0_duration0 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_disable_pll_cmu_peri0_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_disable_pll_cmu_peri0_duration2 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_disable_pll_cmu_peri0_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_disable_pll_cmu_peri1_configuration {
	struct {
		uint32_t local_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_disable_pll_cmu_peri1_status {
	struct {
		uint32_t status:1; /* [0:0] */
		uint32_t rsvd1:15; /* [15:1] */
		uint32_t states:2; /* [17:16] */
		uint32_t rsvd0:14; /* [31:18] */
	};
	uint32_t val;
};

union pmu_disable_pll_cmu_peri1_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_disable_pll_cmu_peri1_duration0 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_disable_pll_cmu_peri1_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_disable_pll_cmu_peri1_duration2 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_disable_pll_cmu_peri1_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_disable_pll_cmu_sbus_u_configuration {
	struct {
		uint32_t local_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_disable_pll_cmu_sbus_u_status {
	struct {
		uint32_t status:1; /* [0:0] */
		uint32_t rsvd1:15; /* [15:1] */
		uint32_t states:2; /* [17:16] */
		uint32_t rsvd0:14; /* [31:18] */
	};
	uint32_t val;
};

union pmu_disable_pll_cmu_sbus_u_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_disable_pll_cmu_sbus_u_duration0 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_disable_pll_cmu_sbus_u_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_disable_pll_cmu_sbus_u_duration2 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_disable_pll_cmu_sbus_u_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_disable_pll_cmu_sbus_d_configuration {
	struct {
		uint32_t local_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_disable_pll_cmu_sbus_d_status {
	struct {
		uint32_t status:1; /* [0:0] */
		uint32_t rsvd1:15; /* [15:1] */
		uint32_t states:2; /* [17:16] */
		uint32_t rsvd0:14; /* [31:18] */
	};
	uint32_t val;
};

union pmu_disable_pll_cmu_sbus_d_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_disable_pll_cmu_sbus_d_duration0 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_disable_pll_cmu_sbus_d_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_disable_pll_cmu_sbus_d_duration2 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_disable_pll_cmu_sbus_d_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_disable_pll_cmu_sbus_l_configuration {
	struct {
		uint32_t local_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_disable_pll_cmu_sbus_l_status {
	struct {
		uint32_t status:1; /* [0:0] */
		uint32_t rsvd1:15; /* [15:1] */
		uint32_t states:2; /* [17:16] */
		uint32_t rsvd0:14; /* [31:18] */
	};
	uint32_t val;
};

union pmu_disable_pll_cmu_sbus_l_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_disable_pll_cmu_sbus_l_duration0 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_disable_pll_cmu_sbus_l_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_disable_pll_cmu_sbus_l_duration2 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_disable_pll_cmu_sbus_l_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_disable_pll_cmu_nbus_u_configuration {
	struct {
		uint32_t local_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_disable_pll_cmu_nbus_u_status {
	struct {
		uint32_t status:1; /* [0:0] */
		uint32_t rsvd1:15; /* [15:1] */
		uint32_t states:2; /* [17:16] */
		uint32_t rsvd0:14; /* [31:18] */
	};
	uint32_t val;
};

union pmu_disable_pll_cmu_nbus_u_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_disable_pll_cmu_nbus_u_duration0 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_disable_pll_cmu_nbus_u_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_disable_pll_cmu_nbus_u_duration2 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_disable_pll_cmu_nbus_u_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_disable_pll_cmu_nbus_d_configuration {
	struct {
		uint32_t local_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_disable_pll_cmu_nbus_d_status {
	struct {
		uint32_t status:1; /* [0:0] */
		uint32_t rsvd1:15; /* [15:1] */
		uint32_t states:2; /* [17:16] */
		uint32_t rsvd0:14; /* [31:18] */
	};
	uint32_t val;
};

union pmu_disable_pll_cmu_nbus_d_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_disable_pll_cmu_nbus_d_duration0 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_disable_pll_cmu_nbus_d_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_disable_pll_cmu_nbus_d_duration2 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_disable_pll_cmu_nbus_d_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_disable_pll_cmu_nbus_l_configuration {
	struct {
		uint32_t local_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_disable_pll_cmu_nbus_l_status {
	struct {
		uint32_t status:1; /* [0:0] */
		uint32_t rsvd1:15; /* [15:1] */
		uint32_t states:2; /* [17:16] */
		uint32_t rsvd0:14; /* [31:18] */
	};
	uint32_t val;
};

union pmu_disable_pll_cmu_nbus_l_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_disable_pll_cmu_nbus_l_duration0 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_disable_pll_cmu_nbus_l_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_disable_pll_cmu_nbus_l_duration2 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_disable_pll_cmu_nbus_l_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_disable_pll_cmu_wbus_u_configuration {
	struct {
		uint32_t local_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_disable_pll_cmu_wbus_u_status {
	struct {
		uint32_t status:1; /* [0:0] */
		uint32_t rsvd1:15; /* [15:1] */
		uint32_t states:2; /* [17:16] */
		uint32_t rsvd0:14; /* [31:18] */
	};
	uint32_t val;
};

union pmu_disable_pll_cmu_wbus_u_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_disable_pll_cmu_wbus_u_duration0 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_disable_pll_cmu_wbus_u_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_disable_pll_cmu_wbus_u_duration2 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_disable_pll_cmu_wbus_u_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_disable_pll_cmu_wbus_d_configuration {
	struct {
		uint32_t local_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_disable_pll_cmu_wbus_d_status {
	struct {
		uint32_t status:1; /* [0:0] */
		uint32_t rsvd1:15; /* [15:1] */
		uint32_t states:2; /* [17:16] */
		uint32_t rsvd0:14; /* [31:18] */
	};
	uint32_t val;
};

union pmu_disable_pll_cmu_wbus_d_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_disable_pll_cmu_wbus_d_duration0 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_disable_pll_cmu_wbus_d_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_disable_pll_cmu_wbus_d_duration2 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_disable_pll_cmu_wbus_d_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_disable_pll_cmu_ebus_u_configuration {
	struct {
		uint32_t local_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_disable_pll_cmu_ebus_u_status {
	struct {
		uint32_t status:1; /* [0:0] */
		uint32_t rsvd1:15; /* [15:1] */
		uint32_t states:2; /* [17:16] */
		uint32_t rsvd0:14; /* [31:18] */
	};
	uint32_t val;
};

union pmu_disable_pll_cmu_ebus_u_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_disable_pll_cmu_ebus_u_duration0 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_disable_pll_cmu_ebus_u_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_disable_pll_cmu_ebus_u_duration2 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_disable_pll_cmu_ebus_u_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_disable_pll_cmu_ebus_d_configuration {
	struct {
		uint32_t local_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_disable_pll_cmu_ebus_d_status {
	struct {
		uint32_t status:1; /* [0:0] */
		uint32_t rsvd1:15; /* [15:1] */
		uint32_t states:2; /* [17:16] */
		uint32_t rsvd0:14; /* [31:18] */
	};
	uint32_t val;
};

union pmu_disable_pll_cmu_ebus_d_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_disable_pll_cmu_ebus_d_duration0 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_disable_pll_cmu_ebus_d_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_disable_pll_cmu_ebus_d_duration2 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_disable_pll_cmu_ebus_d_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_disable_pll_cmu_ebus_r_configuration {
	struct {
		uint32_t local_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_disable_pll_cmu_ebus_r_status {
	struct {
		uint32_t status:1; /* [0:0] */
		uint32_t rsvd1:15; /* [15:1] */
		uint32_t states:2; /* [17:16] */
		uint32_t rsvd0:14; /* [31:18] */
	};
	uint32_t val;
};

union pmu_disable_pll_cmu_ebus_r_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_disable_pll_cmu_ebus_r_duration0 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_disable_pll_cmu_ebus_r_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_disable_pll_cmu_ebus_r_duration2 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_disable_pll_cmu_ebus_r_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_reset_logic_cp0_configuration {
	struct {
		uint32_t local_pwr_cfg:2; /* [1:0] */
		uint32_t rsvd0:30; /* [31:2] */
	};
	uint32_t val;
};

union pmu_reset_logic_cp0_status {
	struct {
		uint32_t status:2; /* [1:0] */
		uint32_t rsvd1:14; /* [15:2] */
		uint32_t states:4; /* [19:16] */
		uint32_t rsvd0:12; /* [31:20] */
	};
	uint32_t val;
};

union pmu_reset_logic_cp0_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_reset_logic_cp0_duration0 {
	struct {
		uint32_t rsvd1:16; /* [15:0] */
		uint32_t dur_chg_reset:4; /* [19:16] */
		uint32_t dur_wait_reset:4; /* [23:20] */
		uint32_t rsvd0:8; /* [31:24] */
	};
	uint32_t val;
};

union pmu_reset_logic_cp0_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_reset_logic_cp0_duration2 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_reset_logic_cp0_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_reset_logic_cp1_configuration {
	struct {
		uint32_t local_pwr_cfg:2; /* [1:0] */
		uint32_t rsvd0:30; /* [31:2] */
	};
	uint32_t val;
};

union pmu_reset_logic_cp1_status {
	struct {
		uint32_t status:2; /* [1:0] */
		uint32_t rsvd1:14; /* [15:2] */
		uint32_t states:4; /* [19:16] */
		uint32_t rsvd0:12; /* [31:20] */
	};
	uint32_t val;
};

union pmu_reset_logic_cp1_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_reset_logic_cp1_duration0 {
	struct {
		uint32_t rsvd1:16; /* [15:0] */
		uint32_t dur_chg_reset:4; /* [19:16] */
		uint32_t dur_wait_reset:4; /* [23:20] */
		uint32_t rsvd0:8; /* [31:24] */
	};
	uint32_t val;
};

union pmu_reset_logic_cp1_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_reset_logic_cp1_duration2 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_reset_logic_cp1_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_reset_logic_pcie_configuration {
	struct {
		uint32_t local_pwr_cfg:2; /* [1:0] */
		uint32_t rsvd0:30; /* [31:2] */
	};
	uint32_t val;
};

union pmu_reset_logic_pcie_status {
	struct {
		uint32_t status:2; /* [1:0] */
		uint32_t rsvd1:14; /* [15:2] */
		uint32_t states:4; /* [19:16] */
		uint32_t rsvd0:12; /* [31:20] */
	};
	uint32_t val;
};

union pmu_reset_logic_pcie_option {
	struct {
		uint32_t rsvd1:15; /* [14:0] */
		uint32_t disable_level3_cssys_presetdbgn:1; /* [15:15] */
		uint32_t disable_level2_cssys_presetdbgn:1; /* [16:16] */
		uint32_t disable_level1_cssys_presetdbgn:1; /* [17:17] */
		uint32_t rsvd0:14; /* [31:18] */
	};
	uint32_t val;
};

union pmu_reset_logic_pcie_duration0 {
	struct {
		uint32_t rsvd1:16; /* [15:0] */
		uint32_t dur_chg_reset:4; /* [19:16] */
		uint32_t dur_wait_reset:4; /* [23:20] */
		uint32_t rsvd0:8; /* [31:24] */
	};
	uint32_t val;
};

union pmu_reset_logic_pcie_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_reset_logic_pcie_duration2 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_reset_logic_pcie_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_reset_logic_dram_configuration {
	struct {
		uint32_t local_pwr_cfg:2; /* [1:0] */
		uint32_t rsvd0:30; /* [31:2] */
	};
	uint32_t val;
};

union pmu_reset_logic_dram_status {
	struct {
		uint32_t status:2; /* [1:0] */
		uint32_t rsvd1:14; /* [15:2] */
		uint32_t states:4; /* [19:16] */
		uint32_t rsvd0:12; /* [31:20] */
	};
	uint32_t val;
};

union pmu_reset_logic_dram_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_reset_logic_dram_duration0 {
	struct {
		uint32_t rsvd1:16; /* [15:0] */
		uint32_t dur_chg_reset:4; /* [19:16] */
		uint32_t dur_wait_reset:4; /* [23:20] */
		uint32_t rsvd0:8; /* [31:24] */
	};
	uint32_t val;
};

union pmu_reset_logic_dram_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_reset_logic_dram_duration2 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_reset_logic_dram_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_reset_logic_dcl0_configuration {
	struct {
		uint32_t local_pwr_cfg:2; /* [1:0] */
		uint32_t rsvd0:30; /* [31:2] */
	};
	uint32_t val;
};

union pmu_reset_logic_dcl0_status {
	struct {
		uint32_t status:2; /* [1:0] */
		uint32_t rsvd1:14; /* [15:2] */
		uint32_t states:4; /* [19:16] */
		uint32_t rsvd0:12; /* [31:20] */
	};
	uint32_t val;
};

union pmu_reset_logic_dcl0_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_reset_logic_dcl0_duration0 {
	struct {
		uint32_t rsvd1:16; /* [15:0] */
		uint32_t dur_chg_reset:4; /* [19:16] */
		uint32_t dur_wait_reset:4; /* [23:20] */
		uint32_t rsvd0:8; /* [31:24] */
	};
	uint32_t val;
};

union pmu_reset_logic_dcl0_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_reset_logic_dcl0_duration2 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_reset_logic_dcl0_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_reset_logic_dcl1_configuration {
	struct {
		uint32_t local_pwr_cfg:2; /* [1:0] */
		uint32_t rsvd0:30; /* [31:2] */
	};
	uint32_t val;
};

union pmu_reset_logic_dcl1_status {
	struct {
		uint32_t status:2; /* [1:0] */
		uint32_t rsvd1:14; /* [15:2] */
		uint32_t states:4; /* [19:16] */
		uint32_t rsvd0:12; /* [31:20] */
	};
	uint32_t val;
};

union pmu_reset_logic_dcl1_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_reset_logic_dcl1_duration0 {
	struct {
		uint32_t rsvd1:16; /* [15:0] */
		uint32_t dur_chg_reset:4; /* [19:16] */
		uint32_t dur_wait_reset:4; /* [23:20] */
		uint32_t rsvd0:8; /* [31:24] */
	};
	uint32_t val;
};

union pmu_reset_logic_dcl1_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_reset_logic_dcl1_duration2 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_reset_logic_dcl1_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_reset_logic_rbch00_configuration {
	struct {
		uint32_t local_pwr_cfg:2; /* [1:0] */
		uint32_t rsvd0:30; /* [31:2] */
	};
	uint32_t val;
};

union pmu_reset_logic_rbch00_status {
	struct {
		uint32_t status:2; /* [1:0] */
		uint32_t rsvd1:14; /* [15:2] */
		uint32_t states:4; /* [19:16] */
		uint32_t rsvd0:12; /* [31:20] */
	};
	uint32_t val;
};

union pmu_reset_logic_rbch00_option {
	struct {
		uint32_t reset_mask:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_reset_logic_rbch00_duration0 {
	struct {
		uint32_t rsvd1:16; /* [15:0] */
		uint32_t dur_chg_reset:4; /* [19:16] */
		uint32_t dur_wait_reset:4; /* [23:20] */
		uint32_t rsvd0:8; /* [31:24] */
	};
	uint32_t val;
};

union pmu_reset_logic_rbch00_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_reset_logic_rbch00_duration2 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_reset_logic_rbch00_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_reset_logic_rbch01_configuration {
	struct {
		uint32_t local_pwr_cfg:2; /* [1:0] */
		uint32_t rsvd0:30; /* [31:2] */
	};
	uint32_t val;
};

union pmu_reset_logic_rbch01_status {
	struct {
		uint32_t status:2; /* [1:0] */
		uint32_t rsvd1:14; /* [15:2] */
		uint32_t states:4; /* [19:16] */
		uint32_t rsvd0:12; /* [31:20] */
	};
	uint32_t val;
};

union pmu_reset_logic_rbch01_option {
	struct {
		uint32_t reset_mask:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_reset_logic_rbch01_duration0 {
	struct {
		uint32_t rsvd1:16; /* [15:0] */
		uint32_t dur_chg_reset:4; /* [19:16] */
		uint32_t dur_wait_reset:4; /* [23:20] */
		uint32_t rsvd0:8; /* [31:24] */
	};
	uint32_t val;
};

union pmu_reset_logic_rbch01_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_reset_logic_rbch01_duration2 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_reset_logic_rbch01_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_reset_logic_rbcv00_configuration {
	struct {
		uint32_t local_pwr_cfg:2; /* [1:0] */
		uint32_t rsvd0:30; /* [31:2] */
	};
	uint32_t val;
};

union pmu_reset_logic_rbcv00_status {
	struct {
		uint32_t status:2; /* [1:0] */
		uint32_t rsvd1:14; /* [15:2] */
		uint32_t states:4; /* [19:16] */
		uint32_t rsvd0:12; /* [31:20] */
	};
	uint32_t val;
};

union pmu_reset_logic_rbcv00_option {
	struct {
		uint32_t reset_mask:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_reset_logic_rbcv00_duration0 {
	struct {
		uint32_t rsvd1:16; /* [15:0] */
		uint32_t dur_chg_reset:4; /* [19:16] */
		uint32_t dur_wait_reset:4; /* [23:20] */
		uint32_t rsvd0:8; /* [31:24] */
	};
	uint32_t val;
};

union pmu_reset_logic_rbcv00_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_reset_logic_rbcv00_duration2 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_reset_logic_rbcv00_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_reset_logic_rbcv01_configuration {
	struct {
		uint32_t local_pwr_cfg:2; /* [1:0] */
		uint32_t rsvd0:30; /* [31:2] */
	};
	uint32_t val;
};

union pmu_reset_logic_rbcv01_status {
	struct {
		uint32_t status:2; /* [1:0] */
		uint32_t rsvd1:14; /* [15:2] */
		uint32_t states:4; /* [19:16] */
		uint32_t rsvd0:12; /* [31:20] */
	};
	uint32_t val;
};

union pmu_reset_logic_rbcv01_option {
	struct {
		uint32_t reset_mask:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_reset_logic_rbcv01_duration0 {
	struct {
		uint32_t rsvd1:16; /* [15:0] */
		uint32_t dur_chg_reset:4; /* [19:16] */
		uint32_t dur_wait_reset:4; /* [23:20] */
		uint32_t rsvd0:8; /* [31:24] */
	};
	uint32_t val;
};

union pmu_reset_logic_rbcv01_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_reset_logic_rbcv01_duration2 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_reset_logic_rbcv01_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_reset_logic_rbcv10_configuration {
	struct {
		uint32_t local_pwr_cfg:2; /* [1:0] */
		uint32_t rsvd0:30; /* [31:2] */
	};
	uint32_t val;
};

union pmu_reset_logic_rbcv10_status {
	struct {
		uint32_t status:2; /* [1:0] */
		uint32_t rsvd1:14; /* [15:2] */
		uint32_t states:4; /* [19:16] */
		uint32_t rsvd0:12; /* [31:20] */
	};
	uint32_t val;
};

union pmu_reset_logic_rbcv10_option {
	struct {
		uint32_t reset_mask:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_reset_logic_rbcv10_duration0 {
	struct {
		uint32_t rsvd1:16; /* [15:0] */
		uint32_t dur_chg_reset:4; /* [19:16] */
		uint32_t dur_wait_reset:4; /* [23:20] */
		uint32_t rsvd0:8; /* [31:24] */
	};
	uint32_t val;
};

union pmu_reset_logic_rbcv10_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_reset_logic_rbcv10_duration2 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_reset_logic_rbcv10_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_reset_logic_rbcv11_configuration {
	struct {
		uint32_t local_pwr_cfg:2; /* [1:0] */
		uint32_t rsvd0:30; /* [31:2] */
	};
	uint32_t val;
};

union pmu_reset_logic_rbcv11_status {
	struct {
		uint32_t status:2; /* [1:0] */
		uint32_t rsvd1:14; /* [15:2] */
		uint32_t states:4; /* [19:16] */
		uint32_t rsvd0:12; /* [31:20] */
	};
	uint32_t val;
};

union pmu_reset_logic_rbcv11_option {
	struct {
		uint32_t reset_mask:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_reset_logic_rbcv11_duration0 {
	struct {
		uint32_t rsvd1:16; /* [15:0] */
		uint32_t dur_chg_reset:4; /* [19:16] */
		uint32_t dur_wait_reset:4; /* [23:20] */
		uint32_t rsvd0:8; /* [31:24] */
	};
	uint32_t val;
};

union pmu_reset_logic_rbcv11_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_reset_logic_rbcv11_duration2 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_reset_logic_rbcv11_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_reset_logic_rot_configuration {
	struct {
		uint32_t local_pwr_cfg:2; /* [1:0] */
		uint32_t rsvd0:30; /* [31:2] */
	};
	uint32_t val;
};

union pmu_reset_logic_rot_status {
	struct {
		uint32_t status:2; /* [1:0] */
		uint32_t rsvd1:14; /* [15:2] */
		uint32_t states:4; /* [19:16] */
		uint32_t rsvd0:12; /* [31:20] */
	};
	uint32_t val;
};

union pmu_reset_logic_rot_option {
	struct {
		uint32_t rsvd1:12; /* [11:0] */
		uint32_t disable_level3_cssys_poresetn:1; /* [12:12] */
		uint32_t disable_level2_cssys_poresetn:1; /* [13:13] */
		uint32_t disable_level1_cssys_poresetn:1; /* [14:14] */
		uint32_t disable_level3_cssys_presetdbgn:1; /* [15:15] */
		uint32_t disable_level2_cssys_presetdbgn:1; /* [16:16] */
		uint32_t disable_level1_cssys_presetdbgn:1; /* [17:17] */
		uint32_t rsvd0:13; /* [30:18] */
		uint32_t enable_cdbgrstreq:1; /* [31:31] */
	};
	uint32_t val;
};

union pmu_reset_logic_rot_duration0 {
	struct {
		uint32_t rsvd1:16; /* [15:0] */
		uint32_t dur_chg_reset:4; /* [19:16] */
		uint32_t dur_wait_reset:4; /* [23:20] */
		uint32_t rsvd0:8; /* [31:24] */
	};
	uint32_t val;
};

union pmu_reset_logic_rot_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_reset_logic_rot_duration2 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_reset_logic_rot_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_reset_logic_peri0_configuration {
	struct {
		uint32_t local_pwr_cfg:2; /* [1:0] */
		uint32_t rsvd0:30; /* [31:2] */
	};
	uint32_t val;
};

union pmu_reset_logic_peri0_status {
	struct {
		uint32_t status:2; /* [1:0] */
		uint32_t rsvd1:14; /* [15:2] */
		uint32_t states:4; /* [19:16] */
		uint32_t rsvd0:12; /* [31:20] */
	};
	uint32_t val;
};

union pmu_reset_logic_peri0_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_reset_logic_peri0_duration0 {
	struct {
		uint32_t rsvd1:16; /* [15:0] */
		uint32_t dur_chg_reset:4; /* [19:16] */
		uint32_t dur_wait_reset:4; /* [23:20] */
		uint32_t rsvd0:8; /* [31:24] */
	};
	uint32_t val;
};

union pmu_reset_logic_peri0_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_reset_logic_peri0_duration2 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_reset_logic_peri0_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_reset_logic_peri1_configuration {
	struct {
		uint32_t local_pwr_cfg:2; /* [1:0] */
		uint32_t rsvd0:30; /* [31:2] */
	};
	uint32_t val;
};

union pmu_reset_logic_peri1_status {
	struct {
		uint32_t status:2; /* [1:0] */
		uint32_t rsvd1:14; /* [15:2] */
		uint32_t states:4; /* [19:16] */
		uint32_t rsvd0:12; /* [31:20] */
	};
	uint32_t val;
};

union pmu_reset_logic_peri1_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_reset_logic_peri1_duration0 {
	struct {
		uint32_t rsvd1:16; /* [15:0] */
		uint32_t dur_chg_reset:4; /* [19:16] */
		uint32_t dur_wait_reset:4; /* [23:20] */
		uint32_t rsvd0:8; /* [31:24] */
	};
	uint32_t val;
};

union pmu_reset_logic_peri1_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_reset_logic_peri1_duration2 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_reset_logic_peri1_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_reset_logic_sbus_u_configuration {
	struct {
		uint32_t local_pwr_cfg:2; /* [1:0] */
		uint32_t rsvd0:30; /* [31:2] */
	};
	uint32_t val;
};

union pmu_reset_logic_sbus_u_status {
	struct {
		uint32_t status:2; /* [1:0] */
		uint32_t rsvd1:14; /* [15:2] */
		uint32_t states:4; /* [19:16] */
		uint32_t rsvd0:12; /* [31:20] */
	};
	uint32_t val;
};

union pmu_reset_logic_sbus_u_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_reset_logic_sbus_u_duration0 {
	struct {
		uint32_t rsvd1:16; /* [15:0] */
		uint32_t dur_chg_reset:4; /* [19:16] */
		uint32_t dur_wait_reset:4; /* [23:20] */
		uint32_t rsvd0:8; /* [31:24] */
	};
	uint32_t val;
};

union pmu_reset_logic_sbus_u_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_reset_logic_sbus_u_duration2 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_reset_logic_sbus_u_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_reset_logic_sbus_d_configuration {
	struct {
		uint32_t local_pwr_cfg:2; /* [1:0] */
		uint32_t rsvd0:30; /* [31:2] */
	};
	uint32_t val;
};

union pmu_reset_logic_sbus_d_status {
	struct {
		uint32_t status:2; /* [1:0] */
		uint32_t rsvd1:14; /* [15:2] */
		uint32_t states:4; /* [19:16] */
		uint32_t rsvd0:12; /* [31:20] */
	};
	uint32_t val;
};

union pmu_reset_logic_sbus_d_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_reset_logic_sbus_d_duration0 {
	struct {
		uint32_t rsvd1:16; /* [15:0] */
		uint32_t dur_chg_reset:4; /* [19:16] */
		uint32_t dur_wait_reset:4; /* [23:20] */
		uint32_t rsvd0:8; /* [31:24] */
	};
	uint32_t val;
};

union pmu_reset_logic_sbus_d_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_reset_logic_sbus_d_duration2 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_reset_logic_sbus_d_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_reset_logic_sbus_l_configuration {
	struct {
		uint32_t local_pwr_cfg:2; /* [1:0] */
		uint32_t rsvd0:30; /* [31:2] */
	};
	uint32_t val;
};

union pmu_reset_logic_sbus_l_status {
	struct {
		uint32_t status:2; /* [1:0] */
		uint32_t rsvd1:14; /* [15:2] */
		uint32_t states:4; /* [19:16] */
		uint32_t rsvd0:12; /* [31:20] */
	};
	uint32_t val;
};

union pmu_reset_logic_sbus_l_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_reset_logic_sbus_l_duration0 {
	struct {
		uint32_t rsvd1:16; /* [15:0] */
		uint32_t dur_chg_reset:4; /* [19:16] */
		uint32_t dur_wait_reset:4; /* [23:20] */
		uint32_t rsvd0:8; /* [31:24] */
	};
	uint32_t val;
};

union pmu_reset_logic_sbus_l_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_reset_logic_sbus_l_duration2 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_reset_logic_sbus_l_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_reset_logic_nbus_u_configuration {
	struct {
		uint32_t local_pwr_cfg:2; /* [1:0] */
		uint32_t rsvd0:30; /* [31:2] */
	};
	uint32_t val;
};

union pmu_reset_logic_nbus_u_status {
	struct {
		uint32_t status:2; /* [1:0] */
		uint32_t rsvd1:14; /* [15:2] */
		uint32_t states:4; /* [19:16] */
		uint32_t rsvd0:12; /* [31:20] */
	};
	uint32_t val;
};

union pmu_reset_logic_nbus_u_option {
	struct {
		uint32_t rsvd1:15; /* [14:0] */
		uint32_t disable_level3_cssys_presetdbgn:1; /* [15:15] */
		uint32_t disable_level2_cssys_presetdbgn:1; /* [16:16] */
		uint32_t disable_level1_cssys_presetdbgn:1; /* [17:17] */
		uint32_t rsvd0:14; /* [31:18] */
	};
	uint32_t val;
};

union pmu_reset_logic_nbus_u_duration0 {
	struct {
		uint32_t rsvd1:16; /* [15:0] */
		uint32_t dur_chg_reset:4; /* [19:16] */
		uint32_t dur_wait_reset:4; /* [23:20] */
		uint32_t rsvd0:8; /* [31:24] */
	};
	uint32_t val;
};

union pmu_reset_logic_nbus_u_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_reset_logic_nbus_u_duration2 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_reset_logic_nbus_u_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_reset_logic_nbus_d_configuration {
	struct {
		uint32_t local_pwr_cfg:2; /* [1:0] */
		uint32_t rsvd0:30; /* [31:2] */
	};
	uint32_t val;
};

union pmu_reset_logic_nbus_d_status {
	struct {
		uint32_t status:2; /* [1:0] */
		uint32_t rsvd1:14; /* [15:2] */
		uint32_t states:4; /* [19:16] */
		uint32_t rsvd0:12; /* [31:20] */
	};
	uint32_t val;
};

union pmu_reset_logic_nbus_d_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_reset_logic_nbus_d_duration0 {
	struct {
		uint32_t rsvd1:16; /* [15:0] */
		uint32_t dur_chg_reset:4; /* [19:16] */
		uint32_t dur_wait_reset:4; /* [23:20] */
		uint32_t rsvd0:8; /* [31:24] */
	};
	uint32_t val;
};

union pmu_reset_logic_nbus_d_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_reset_logic_nbus_d_duration2 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_reset_logic_nbus_d_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_reset_logic_nbus_l_configuration {
	struct {
		uint32_t local_pwr_cfg:2; /* [1:0] */
		uint32_t rsvd0:30; /* [31:2] */
	};
	uint32_t val;
};

union pmu_reset_logic_nbus_l_status {
	struct {
		uint32_t status:2; /* [1:0] */
		uint32_t rsvd1:14; /* [15:2] */
		uint32_t states:4; /* [19:16] */
		uint32_t rsvd0:12; /* [31:20] */
	};
	uint32_t val;
};

union pmu_reset_logic_nbus_l_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_reset_logic_nbus_l_duration0 {
	struct {
		uint32_t rsvd1:16; /* [15:0] */
		uint32_t dur_chg_reset:4; /* [19:16] */
		uint32_t dur_wait_reset:4; /* [23:20] */
		uint32_t rsvd0:8; /* [31:24] */
	};
	uint32_t val;
};

union pmu_reset_logic_nbus_l_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_reset_logic_nbus_l_duration2 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_reset_logic_nbus_l_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_reset_logic_wbus_u_configuration {
	struct {
		uint32_t local_pwr_cfg:2; /* [1:0] */
		uint32_t rsvd0:30; /* [31:2] */
	};
	uint32_t val;
};

union pmu_reset_logic_wbus_u_status {
	struct {
		uint32_t status:2; /* [1:0] */
		uint32_t rsvd1:14; /* [15:2] */
		uint32_t states:4; /* [19:16] */
		uint32_t rsvd0:12; /* [31:20] */
	};
	uint32_t val;
};

union pmu_reset_logic_wbus_u_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_reset_logic_wbus_u_duration0 {
	struct {
		uint32_t rsvd1:16; /* [15:0] */
		uint32_t dur_chg_reset:4; /* [19:16] */
		uint32_t dur_wait_reset:4; /* [23:20] */
		uint32_t rsvd0:8; /* [31:24] */
	};
	uint32_t val;
};

union pmu_reset_logic_wbus_u_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_reset_logic_wbus_u_duration2 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_reset_logic_wbus_u_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_reset_logic_wbus_d_configuration {
	struct {
		uint32_t local_pwr_cfg:2; /* [1:0] */
		uint32_t rsvd0:30; /* [31:2] */
	};
	uint32_t val;
};

union pmu_reset_logic_wbus_d_status {
	struct {
		uint32_t status:2; /* [1:0] */
		uint32_t rsvd1:14; /* [15:2] */
		uint32_t states:4; /* [19:16] */
		uint32_t rsvd0:12; /* [31:20] */
	};
	uint32_t val;
};

union pmu_reset_logic_wbus_d_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_reset_logic_wbus_d_duration0 {
	struct {
		uint32_t rsvd1:16; /* [15:0] */
		uint32_t dur_chg_reset:4; /* [19:16] */
		uint32_t dur_wait_reset:4; /* [23:20] */
		uint32_t rsvd0:8; /* [31:24] */
	};
	uint32_t val;
};

union pmu_reset_logic_wbus_d_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_reset_logic_wbus_d_duration2 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_reset_logic_wbus_d_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_reset_logic_ebus_u_configuration {
	struct {
		uint32_t local_pwr_cfg:2; /* [1:0] */
		uint32_t rsvd0:30; /* [31:2] */
	};
	uint32_t val;
};

union pmu_reset_logic_ebus_u_status {
	struct {
		uint32_t status:2; /* [1:0] */
		uint32_t rsvd1:14; /* [15:2] */
		uint32_t states:4; /* [19:16] */
		uint32_t rsvd0:12; /* [31:20] */
	};
	uint32_t val;
};

union pmu_reset_logic_ebus_u_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_reset_logic_ebus_u_duration0 {
	struct {
		uint32_t rsvd1:16; /* [15:0] */
		uint32_t dur_chg_reset:4; /* [19:16] */
		uint32_t dur_wait_reset:4; /* [23:20] */
		uint32_t rsvd0:8; /* [31:24] */
	};
	uint32_t val;
};

union pmu_reset_logic_ebus_u_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_reset_logic_ebus_u_duration2 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_reset_logic_ebus_u_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_reset_logic_ebus_d_configuration {
	struct {
		uint32_t local_pwr_cfg:2; /* [1:0] */
		uint32_t rsvd0:30; /* [31:2] */
	};
	uint32_t val;
};

union pmu_reset_logic_ebus_d_status {
	struct {
		uint32_t status:2; /* [1:0] */
		uint32_t rsvd1:14; /* [15:2] */
		uint32_t states:4; /* [19:16] */
		uint32_t rsvd0:12; /* [31:20] */
	};
	uint32_t val;
};

union pmu_reset_logic_ebus_d_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_reset_logic_ebus_d_duration0 {
	struct {
		uint32_t rsvd1:16; /* [15:0] */
		uint32_t dur_chg_reset:4; /* [19:16] */
		uint32_t dur_wait_reset:4; /* [23:20] */
		uint32_t rsvd0:8; /* [31:24] */
	};
	uint32_t val;
};

union pmu_reset_logic_ebus_d_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_reset_logic_ebus_d_duration2 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_reset_logic_ebus_d_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_reset_logic_ebus_r_configuration {
	struct {
		uint32_t local_pwr_cfg:2; /* [1:0] */
		uint32_t rsvd0:30; /* [31:2] */
	};
	uint32_t val;
};

union pmu_reset_logic_ebus_r_status {
	struct {
		uint32_t status:2; /* [1:0] */
		uint32_t rsvd1:14; /* [15:2] */
		uint32_t states:4; /* [19:16] */
		uint32_t rsvd0:12; /* [31:20] */
	};
	uint32_t val;
};

union pmu_reset_logic_ebus_r_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_reset_logic_ebus_r_duration0 {
	struct {
		uint32_t rsvd1:16; /* [15:0] */
		uint32_t dur_chg_reset:4; /* [19:16] */
		uint32_t dur_wait_reset:4; /* [23:20] */
		uint32_t rsvd0:8; /* [31:24] */
	};
	uint32_t val;
};

union pmu_reset_logic_ebus_r_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_reset_logic_ebus_r_duration2 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_reset_logic_ebus_r_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_reset_cmu_cp0_configuration {
	struct {
		uint32_t local_pwr_cfg:2; /* [1:0] */
		uint32_t rsvd0:30; /* [31:2] */
	};
	uint32_t val;
};

union pmu_reset_cmu_cp0_status {
	struct {
		uint32_t status:2; /* [1:0] */
		uint32_t rsvd1:14; /* [15:2] */
		uint32_t states:4; /* [19:16] */
		uint32_t rsvd0:12; /* [31:20] */
	};
	uint32_t val;
};

union pmu_reset_cmu_cp0_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_reset_cmu_cp0_duration0 {
	struct {
		uint32_t rsvd1:16; /* [15:0] */
		uint32_t dur_chg_reset:4; /* [19:16] */
		uint32_t dur_wait_reset:4; /* [23:20] */
		uint32_t rsvd0:8; /* [31:24] */
	};
	uint32_t val;
};

union pmu_reset_cmu_cp0_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_reset_cmu_cp0_duration2 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_reset_cmu_cp0_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_reset_cmu_cp1_configuration {
	struct {
		uint32_t local_pwr_cfg:2; /* [1:0] */
		uint32_t rsvd0:30; /* [31:2] */
	};
	uint32_t val;
};

union pmu_reset_cmu_cp1_status {
	struct {
		uint32_t status:2; /* [1:0] */
		uint32_t rsvd1:14; /* [15:2] */
		uint32_t states:4; /* [19:16] */
		uint32_t rsvd0:12; /* [31:20] */
	};
	uint32_t val;
};

union pmu_reset_cmu_cp1_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_reset_cmu_cp1_duration0 {
	struct {
		uint32_t rsvd1:16; /* [15:0] */
		uint32_t dur_chg_reset:4; /* [19:16] */
		uint32_t dur_wait_reset:4; /* [23:20] */
		uint32_t rsvd0:8; /* [31:24] */
	};
	uint32_t val;
};

union pmu_reset_cmu_cp1_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_reset_cmu_cp1_duration2 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_reset_cmu_cp1_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_reset_cmu_pcie_configuration {
	struct {
		uint32_t local_pwr_cfg:2; /* [1:0] */
		uint32_t rsvd0:30; /* [31:2] */
	};
	uint32_t val;
};

union pmu_reset_cmu_pcie_status {
	struct {
		uint32_t status:2; /* [1:0] */
		uint32_t rsvd1:14; /* [15:2] */
		uint32_t states:4; /* [19:16] */
		uint32_t rsvd0:12; /* [31:20] */
	};
	uint32_t val;
};

union pmu_reset_cmu_pcie_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_reset_cmu_pcie_duration0 {
	struct {
		uint32_t rsvd1:16; /* [15:0] */
		uint32_t dur_chg_reset:4; /* [19:16] */
		uint32_t dur_wait_reset:4; /* [23:20] */
		uint32_t rsvd0:8; /* [31:24] */
	};
	uint32_t val;
};

union pmu_reset_cmu_pcie_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_reset_cmu_pcie_duration2 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_reset_cmu_pcie_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_reset_cmu_dram_configuration {
	struct {
		uint32_t local_pwr_cfg:2; /* [1:0] */
		uint32_t rsvd0:30; /* [31:2] */
	};
	uint32_t val;
};

union pmu_reset_cmu_dram_status {
	struct {
		uint32_t status:2; /* [1:0] */
		uint32_t rsvd1:14; /* [15:2] */
		uint32_t states:4; /* [19:16] */
		uint32_t rsvd0:12; /* [31:20] */
	};
	uint32_t val;
};

union pmu_reset_cmu_dram_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_reset_cmu_dram_duration0 {
	struct {
		uint32_t rsvd1:16; /* [15:0] */
		uint32_t dur_chg_reset:4; /* [19:16] */
		uint32_t dur_wait_reset:4; /* [23:20] */
		uint32_t rsvd0:8; /* [31:24] */
	};
	uint32_t val;
};

union pmu_reset_cmu_dram_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_reset_cmu_dram_duration2 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_reset_cmu_dram_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_reset_cmu_dcl0_configuration {
	struct {
		uint32_t local_pwr_cfg:2; /* [1:0] */
		uint32_t rsvd0:30; /* [31:2] */
	};
	uint32_t val;
};

union pmu_reset_cmu_dcl0_status {
	struct {
		uint32_t status:2; /* [1:0] */
		uint32_t rsvd1:14; /* [15:2] */
		uint32_t states:4; /* [19:16] */
		uint32_t rsvd0:12; /* [31:20] */
	};
	uint32_t val;
};

union pmu_reset_cmu_dcl0_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_reset_cmu_dcl0_duration0 {
	struct {
		uint32_t rsvd1:16; /* [15:0] */
		uint32_t dur_chg_reset:4; /* [19:16] */
		uint32_t dur_wait_reset:4; /* [23:20] */
		uint32_t rsvd0:8; /* [31:24] */
	};
	uint32_t val;
};

union pmu_reset_cmu_dcl0_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_reset_cmu_dcl0_duration2 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_reset_cmu_dcl0_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_reset_cmu_dcl1_configuration {
	struct {
		uint32_t local_pwr_cfg:2; /* [1:0] */
		uint32_t rsvd0:30; /* [31:2] */
	};
	uint32_t val;
};

union pmu_reset_cmu_dcl1_status {
	struct {
		uint32_t status:2; /* [1:0] */
		uint32_t rsvd1:14; /* [15:2] */
		uint32_t states:4; /* [19:16] */
		uint32_t rsvd0:12; /* [31:20] */
	};
	uint32_t val;
};

union pmu_reset_cmu_dcl1_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_reset_cmu_dcl1_duration0 {
	struct {
		uint32_t rsvd1:16; /* [15:0] */
		uint32_t dur_chg_reset:4; /* [19:16] */
		uint32_t dur_wait_reset:4; /* [23:20] */
		uint32_t rsvd0:8; /* [31:24] */
	};
	uint32_t val;
};

union pmu_reset_cmu_dcl1_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_reset_cmu_dcl1_duration2 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_reset_cmu_dcl1_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_reset_cmu_rbch00_configuration {
	struct {
		uint32_t local_pwr_cfg:2; /* [1:0] */
		uint32_t rsvd0:30; /* [31:2] */
	};
	uint32_t val;
};

union pmu_reset_cmu_rbch00_status {
	struct {
		uint32_t status:2; /* [1:0] */
		uint32_t rsvd1:14; /* [15:2] */
		uint32_t states:4; /* [19:16] */
		uint32_t rsvd0:12; /* [31:20] */
	};
	uint32_t val;
};

union pmu_reset_cmu_rbch00_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_reset_cmu_rbch00_duration0 {
	struct {
		uint32_t rsvd1:16; /* [15:0] */
		uint32_t dur_chg_reset:4; /* [19:16] */
		uint32_t dur_wait_reset:4; /* [23:20] */
		uint32_t rsvd0:8; /* [31:24] */
	};
	uint32_t val;
};

union pmu_reset_cmu_rbch00_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_reset_cmu_rbch00_duration2 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_reset_cmu_rbch00_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_reset_cmu_rbch01_configuration {
	struct {
		uint32_t local_pwr_cfg:2; /* [1:0] */
		uint32_t rsvd0:30; /* [31:2] */
	};
	uint32_t val;
};

union pmu_reset_cmu_rbch01_status {
	struct {
		uint32_t status:2; /* [1:0] */
		uint32_t rsvd1:14; /* [15:2] */
		uint32_t states:4; /* [19:16] */
		uint32_t rsvd0:12; /* [31:20] */
	};
	uint32_t val;
};

union pmu_reset_cmu_rbch01_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_reset_cmu_rbch01_duration0 {
	struct {
		uint32_t rsvd1:16; /* [15:0] */
		uint32_t dur_chg_reset:4; /* [19:16] */
		uint32_t dur_wait_reset:4; /* [23:20] */
		uint32_t rsvd0:8; /* [31:24] */
	};
	uint32_t val;
};

union pmu_reset_cmu_rbch01_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_reset_cmu_rbch01_duration2 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_reset_cmu_rbch01_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_reset_cmu_rbcv00_configuration {
	struct {
		uint32_t local_pwr_cfg:2; /* [1:0] */
		uint32_t rsvd0:30; /* [31:2] */
	};
	uint32_t val;
};

union pmu_reset_cmu_rbcv00_status {
	struct {
		uint32_t status:2; /* [1:0] */
		uint32_t rsvd1:14; /* [15:2] */
		uint32_t states:4; /* [19:16] */
		uint32_t rsvd0:12; /* [31:20] */
	};
	uint32_t val;
};

union pmu_reset_cmu_rbcv00_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_reset_cmu_rbcv00_duration0 {
	struct {
		uint32_t rsvd1:16; /* [15:0] */
		uint32_t dur_chg_reset:4; /* [19:16] */
		uint32_t dur_wait_reset:4; /* [23:20] */
		uint32_t rsvd0:8; /* [31:24] */
	};
	uint32_t val;
};

union pmu_reset_cmu_rbcv00_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_reset_cmu_rbcv00_duration2 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_reset_cmu_rbcv00_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_reset_cmu_rbcv01_configuration {
	struct {
		uint32_t local_pwr_cfg:2; /* [1:0] */
		uint32_t rsvd0:30; /* [31:2] */
	};
	uint32_t val;
};

union pmu_reset_cmu_rbcv01_status {
	struct {
		uint32_t status:2; /* [1:0] */
		uint32_t rsvd1:14; /* [15:2] */
		uint32_t states:4; /* [19:16] */
		uint32_t rsvd0:12; /* [31:20] */
	};
	uint32_t val;
};

union pmu_reset_cmu_rbcv01_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_reset_cmu_rbcv01_duration0 {
	struct {
		uint32_t rsvd1:16; /* [15:0] */
		uint32_t dur_chg_reset:4; /* [19:16] */
		uint32_t dur_wait_reset:4; /* [23:20] */
		uint32_t rsvd0:8; /* [31:24] */
	};
	uint32_t val;
};

union pmu_reset_cmu_rbcv01_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_reset_cmu_rbcv01_duration2 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_reset_cmu_rbcv01_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_reset_cmu_rbcv10_configuration {
	struct {
		uint32_t local_pwr_cfg:2; /* [1:0] */
		uint32_t rsvd0:30; /* [31:2] */
	};
	uint32_t val;
};

union pmu_reset_cmu_rbcv10_status {
	struct {
		uint32_t status:2; /* [1:0] */
		uint32_t rsvd1:14; /* [15:2] */
		uint32_t states:4; /* [19:16] */
		uint32_t rsvd0:12; /* [31:20] */
	};
	uint32_t val;
};

union pmu_reset_cmu_rbcv10_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_reset_cmu_rbcv10_duration0 {
	struct {
		uint32_t rsvd1:16; /* [15:0] */
		uint32_t dur_chg_reset:4; /* [19:16] */
		uint32_t dur_wait_reset:4; /* [23:20] */
		uint32_t rsvd0:8; /* [31:24] */
	};
	uint32_t val;
};

union pmu_reset_cmu_rbcv10_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_reset_cmu_rbcv10_duration2 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_reset_cmu_rbcv10_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_reset_cmu_rbcv11_configuration {
	struct {
		uint32_t local_pwr_cfg:2; /* [1:0] */
		uint32_t rsvd0:30; /* [31:2] */
	};
	uint32_t val;
};

union pmu_reset_cmu_rbcv11_status {
	struct {
		uint32_t status:2; /* [1:0] */
		uint32_t rsvd1:14; /* [15:2] */
		uint32_t states:4; /* [19:16] */
		uint32_t rsvd0:12; /* [31:20] */
	};
	uint32_t val;
};

union pmu_reset_cmu_rbcv11_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_reset_cmu_rbcv11_duration0 {
	struct {
		uint32_t rsvd1:16; /* [15:0] */
		uint32_t dur_chg_reset:4; /* [19:16] */
		uint32_t dur_wait_reset:4; /* [23:20] */
		uint32_t rsvd0:8; /* [31:24] */
	};
	uint32_t val;
};

union pmu_reset_cmu_rbcv11_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_reset_cmu_rbcv11_duration2 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_reset_cmu_rbcv11_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_reset_cmu_rot_configuration {
	struct {
		uint32_t local_pwr_cfg:2; /* [1:0] */
		uint32_t rsvd0:30; /* [31:2] */
	};
	uint32_t val;
};

union pmu_reset_cmu_rot_status {
	struct {
		uint32_t status:2; /* [1:0] */
		uint32_t rsvd1:14; /* [15:2] */
		uint32_t states:4; /* [19:16] */
		uint32_t rsvd0:12; /* [31:20] */
	};
	uint32_t val;
};

union pmu_reset_cmu_rot_option {
	struct {
		uint32_t otp_sense_parallel:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_reset_cmu_rot_duration0 {
	struct {
		uint32_t rsvd1:16; /* [15:0] */
		uint32_t dur_chg_reset:4; /* [19:16] */
		uint32_t dur_wait_reset:4; /* [23:20] */
		uint32_t rsvd0:8; /* [31:24] */
	};
	uint32_t val;
};

union pmu_reset_cmu_rot_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_reset_cmu_rot_duration2 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_reset_cmu_rot_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_reset_cmu_peri0_configuration {
	struct {
		uint32_t local_pwr_cfg:2; /* [1:0] */
		uint32_t rsvd0:30; /* [31:2] */
	};
	uint32_t val;
};

union pmu_reset_cmu_peri0_status {
	struct {
		uint32_t status:2; /* [1:0] */
		uint32_t rsvd1:14; /* [15:2] */
		uint32_t states:4; /* [19:16] */
		uint32_t rsvd0:12; /* [31:20] */
	};
	uint32_t val;
};

union pmu_reset_cmu_peri0_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_reset_cmu_peri0_duration0 {
	struct {
		uint32_t rsvd1:16; /* [15:0] */
		uint32_t dur_chg_reset:4; /* [19:16] */
		uint32_t dur_wait_reset:4; /* [23:20] */
		uint32_t rsvd0:8; /* [31:24] */
	};
	uint32_t val;
};

union pmu_reset_cmu_peri0_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_reset_cmu_peri0_duration2 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_reset_cmu_peri0_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_reset_cmu_peri1_configuration {
	struct {
		uint32_t local_pwr_cfg:2; /* [1:0] */
		uint32_t rsvd0:30; /* [31:2] */
	};
	uint32_t val;
};

union pmu_reset_cmu_peri1_status {
	struct {
		uint32_t status:2; /* [1:0] */
		uint32_t rsvd1:14; /* [15:2] */
		uint32_t states:4; /* [19:16] */
		uint32_t rsvd0:12; /* [31:20] */
	};
	uint32_t val;
};

union pmu_reset_cmu_peri1_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_reset_cmu_peri1_duration0 {
	struct {
		uint32_t rsvd1:16; /* [15:0] */
		uint32_t dur_chg_reset:4; /* [19:16] */
		uint32_t dur_wait_reset:4; /* [23:20] */
		uint32_t rsvd0:8; /* [31:24] */
	};
	uint32_t val;
};

union pmu_reset_cmu_peri1_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_reset_cmu_peri1_duration2 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_reset_cmu_peri1_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_reset_cmu_sbus_u_configuration {
	struct {
		uint32_t local_pwr_cfg:2; /* [1:0] */
		uint32_t rsvd0:30; /* [31:2] */
	};
	uint32_t val;
};

union pmu_reset_cmu_sbus_u_status {
	struct {
		uint32_t status:2; /* [1:0] */
		uint32_t rsvd1:14; /* [15:2] */
		uint32_t states:4; /* [19:16] */
		uint32_t rsvd0:12; /* [31:20] */
	};
	uint32_t val;
};

union pmu_reset_cmu_sbus_u_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_reset_cmu_sbus_u_duration0 {
	struct {
		uint32_t rsvd1:16; /* [15:0] */
		uint32_t dur_chg_reset:4; /* [19:16] */
		uint32_t dur_wait_reset:4; /* [23:20] */
		uint32_t rsvd0:8; /* [31:24] */
	};
	uint32_t val;
};

union pmu_reset_cmu_sbus_u_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_reset_cmu_sbus_u_duration2 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_reset_cmu_sbus_u_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_reset_cmu_sbus_d_configuration {
	struct {
		uint32_t local_pwr_cfg:2; /* [1:0] */
		uint32_t rsvd0:30; /* [31:2] */
	};
	uint32_t val;
};

union pmu_reset_cmu_sbus_d_status {
	struct {
		uint32_t status:2; /* [1:0] */
		uint32_t rsvd1:14; /* [15:2] */
		uint32_t states:4; /* [19:16] */
		uint32_t rsvd0:12; /* [31:20] */
	};
	uint32_t val;
};

union pmu_reset_cmu_sbus_d_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_reset_cmu_sbus_d_duration0 {
	struct {
		uint32_t rsvd1:16; /* [15:0] */
		uint32_t dur_chg_reset:4; /* [19:16] */
		uint32_t dur_wait_reset:4; /* [23:20] */
		uint32_t rsvd0:8; /* [31:24] */
	};
	uint32_t val;
};

union pmu_reset_cmu_sbus_d_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_reset_cmu_sbus_d_duration2 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_reset_cmu_sbus_d_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_reset_cmu_sbus_l_configuration {
	struct {
		uint32_t local_pwr_cfg:2; /* [1:0] */
		uint32_t rsvd0:30; /* [31:2] */
	};
	uint32_t val;
};

union pmu_reset_cmu_sbus_l_status {
	struct {
		uint32_t status:2; /* [1:0] */
		uint32_t rsvd1:14; /* [15:2] */
		uint32_t states:4; /* [19:16] */
		uint32_t rsvd0:12; /* [31:20] */
	};
	uint32_t val;
};

union pmu_reset_cmu_sbus_l_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_reset_cmu_sbus_l_duration0 {
	struct {
		uint32_t rsvd1:16; /* [15:0] */
		uint32_t dur_chg_reset:4; /* [19:16] */
		uint32_t dur_wait_reset:4; /* [23:20] */
		uint32_t rsvd0:8; /* [31:24] */
	};
	uint32_t val;
};

union pmu_reset_cmu_sbus_l_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_reset_cmu_sbus_l_duration2 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_reset_cmu_sbus_l_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_reset_cmu_nbus_u_configuration {
	struct {
		uint32_t local_pwr_cfg:2; /* [1:0] */
		uint32_t rsvd0:30; /* [31:2] */
	};
	uint32_t val;
};

union pmu_reset_cmu_nbus_u_status {
	struct {
		uint32_t status:2; /* [1:0] */
		uint32_t rsvd1:14; /* [15:2] */
		uint32_t states:4; /* [19:16] */
		uint32_t rsvd0:12; /* [31:20] */
	};
	uint32_t val;
};

union pmu_reset_cmu_nbus_u_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_reset_cmu_nbus_u_duration0 {
	struct {
		uint32_t rsvd1:16; /* [15:0] */
		uint32_t dur_chg_reset:4; /* [19:16] */
		uint32_t dur_wait_reset:4; /* [23:20] */
		uint32_t rsvd0:8; /* [31:24] */
	};
	uint32_t val;
};

union pmu_reset_cmu_nbus_u_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_reset_cmu_nbus_u_duration2 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_reset_cmu_nbus_u_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_reset_cmu_nbus_d_configuration {
	struct {
		uint32_t local_pwr_cfg:2; /* [1:0] */
		uint32_t rsvd0:30; /* [31:2] */
	};
	uint32_t val;
};

union pmu_reset_cmu_nbus_d_status {
	struct {
		uint32_t status:2; /* [1:0] */
		uint32_t rsvd1:14; /* [15:2] */
		uint32_t states:4; /* [19:16] */
		uint32_t rsvd0:12; /* [31:20] */
	};
	uint32_t val;
};

union pmu_reset_cmu_nbus_d_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_reset_cmu_nbus_d_duration0 {
	struct {
		uint32_t rsvd1:16; /* [15:0] */
		uint32_t dur_chg_reset:4; /* [19:16] */
		uint32_t dur_wait_reset:4; /* [23:20] */
		uint32_t rsvd0:8; /* [31:24] */
	};
	uint32_t val;
};

union pmu_reset_cmu_nbus_d_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_reset_cmu_nbus_d_duration2 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_reset_cmu_nbus_d_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_reset_cmu_nbus_l_configuration {
	struct {
		uint32_t local_pwr_cfg:2; /* [1:0] */
		uint32_t rsvd0:30; /* [31:2] */
	};
	uint32_t val;
};

union pmu_reset_cmu_nbus_l_status {
	struct {
		uint32_t status:2; /* [1:0] */
		uint32_t rsvd1:14; /* [15:2] */
		uint32_t states:4; /* [19:16] */
		uint32_t rsvd0:12; /* [31:20] */
	};
	uint32_t val;
};

union pmu_reset_cmu_nbus_l_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_reset_cmu_nbus_l_duration0 {
	struct {
		uint32_t rsvd1:16; /* [15:0] */
		uint32_t dur_chg_reset:4; /* [19:16] */
		uint32_t dur_wait_reset:4; /* [23:20] */
		uint32_t rsvd0:8; /* [31:24] */
	};
	uint32_t val;
};

union pmu_reset_cmu_nbus_l_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_reset_cmu_nbus_l_duration2 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_reset_cmu_nbus_l_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_reset_cmu_wbus_u_configuration {
	struct {
		uint32_t local_pwr_cfg:2; /* [1:0] */
		uint32_t rsvd0:30; /* [31:2] */
	};
	uint32_t val;
};

union pmu_reset_cmu_wbus_u_status {
	struct {
		uint32_t status:2; /* [1:0] */
		uint32_t rsvd1:14; /* [15:2] */
		uint32_t states:4; /* [19:16] */
		uint32_t rsvd0:12; /* [31:20] */
	};
	uint32_t val;
};

union pmu_reset_cmu_wbus_u_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_reset_cmu_wbus_u_duration0 {
	struct {
		uint32_t rsvd1:16; /* [15:0] */
		uint32_t dur_chg_reset:4; /* [19:16] */
		uint32_t dur_wait_reset:4; /* [23:20] */
		uint32_t rsvd0:8; /* [31:24] */
	};
	uint32_t val;
};

union pmu_reset_cmu_wbus_u_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_reset_cmu_wbus_u_duration2 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_reset_cmu_wbus_u_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_reset_cmu_wbus_d_configuration {
	struct {
		uint32_t local_pwr_cfg:2; /* [1:0] */
		uint32_t rsvd0:30; /* [31:2] */
	};
	uint32_t val;
};

union pmu_reset_cmu_wbus_d_status {
	struct {
		uint32_t status:2; /* [1:0] */
		uint32_t rsvd1:14; /* [15:2] */
		uint32_t states:4; /* [19:16] */
		uint32_t rsvd0:12; /* [31:20] */
	};
	uint32_t val;
};

union pmu_reset_cmu_wbus_d_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_reset_cmu_wbus_d_duration0 {
	struct {
		uint32_t rsvd1:16; /* [15:0] */
		uint32_t dur_chg_reset:4; /* [19:16] */
		uint32_t dur_wait_reset:4; /* [23:20] */
		uint32_t rsvd0:8; /* [31:24] */
	};
	uint32_t val;
};

union pmu_reset_cmu_wbus_d_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_reset_cmu_wbus_d_duration2 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_reset_cmu_wbus_d_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_reset_cmu_ebus_u_configuration {
	struct {
		uint32_t local_pwr_cfg:2; /* [1:0] */
		uint32_t rsvd0:30; /* [31:2] */
	};
	uint32_t val;
};

union pmu_reset_cmu_ebus_u_status {
	struct {
		uint32_t status:2; /* [1:0] */
		uint32_t rsvd1:14; /* [15:2] */
		uint32_t states:4; /* [19:16] */
		uint32_t rsvd0:12; /* [31:20] */
	};
	uint32_t val;
};

union pmu_reset_cmu_ebus_u_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_reset_cmu_ebus_u_duration0 {
	struct {
		uint32_t rsvd1:16; /* [15:0] */
		uint32_t dur_chg_reset:4; /* [19:16] */
		uint32_t dur_wait_reset:4; /* [23:20] */
		uint32_t rsvd0:8; /* [31:24] */
	};
	uint32_t val;
};

union pmu_reset_cmu_ebus_u_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_reset_cmu_ebus_u_duration2 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_reset_cmu_ebus_u_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_reset_cmu_ebus_d_configuration {
	struct {
		uint32_t local_pwr_cfg:2; /* [1:0] */
		uint32_t rsvd0:30; /* [31:2] */
	};
	uint32_t val;
};

union pmu_reset_cmu_ebus_d_status {
	struct {
		uint32_t status:2; /* [1:0] */
		uint32_t rsvd1:14; /* [15:2] */
		uint32_t states:4; /* [19:16] */
		uint32_t rsvd0:12; /* [31:20] */
	};
	uint32_t val;
};

union pmu_reset_cmu_ebus_d_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_reset_cmu_ebus_d_duration0 {
	struct {
		uint32_t rsvd1:16; /* [15:0] */
		uint32_t dur_chg_reset:4; /* [19:16] */
		uint32_t dur_wait_reset:4; /* [23:20] */
		uint32_t rsvd0:8; /* [31:24] */
	};
	uint32_t val;
};

union pmu_reset_cmu_ebus_d_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_reset_cmu_ebus_d_duration2 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_reset_cmu_ebus_d_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_reset_cmu_ebus_r_configuration {
	struct {
		uint32_t local_pwr_cfg:2; /* [1:0] */
		uint32_t rsvd0:30; /* [31:2] */
	};
	uint32_t val;
};

union pmu_reset_cmu_ebus_r_status {
	struct {
		uint32_t status:2; /* [1:0] */
		uint32_t rsvd1:14; /* [15:2] */
		uint32_t states:4; /* [19:16] */
		uint32_t rsvd0:12; /* [31:20] */
	};
	uint32_t val;
};

union pmu_reset_cmu_ebus_r_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_reset_cmu_ebus_r_duration0 {
	struct {
		uint32_t rsvd1:16; /* [15:0] */
		uint32_t dur_chg_reset:4; /* [19:16] */
		uint32_t dur_wait_reset:4; /* [23:20] */
		uint32_t rsvd0:8; /* [31:24] */
	};
	uint32_t val;
};

union pmu_reset_cmu_ebus_r_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_reset_cmu_ebus_r_duration2 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_reset_cmu_ebus_r_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_residual_cmu_cp0_configuration {
	struct {
		uint32_t local_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_lpi_residual_cmu_cp0_status {
	struct {
		uint32_t status:1; /* [0:0] */
		uint32_t rsvd1:15; /* [15:1] */
		uint32_t states:2; /* [17:16] */
		uint32_t rsvd0:14; /* [31:18] */
	};
	uint32_t val;
};

union pmu_lpi_residual_cmu_cp0_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_residual_cmu_cp0_duration0 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_residual_cmu_cp0_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_residual_cmu_cp0_duration2 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_residual_cmu_cp0_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_residual_cmu_cp1_configuration {
	struct {
		uint32_t local_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_lpi_residual_cmu_cp1_status {
	struct {
		uint32_t status:1; /* [0:0] */
		uint32_t rsvd1:15; /* [15:1] */
		uint32_t states:2; /* [17:16] */
		uint32_t rsvd0:14; /* [31:18] */
	};
	uint32_t val;
};

union pmu_lpi_residual_cmu_cp1_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_residual_cmu_cp1_duration0 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_residual_cmu_cp1_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_residual_cmu_cp1_duration2 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_residual_cmu_cp1_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_residual_cmu_pcie_configuration {
	struct {
		uint32_t local_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_lpi_residual_cmu_pcie_status {
	struct {
		uint32_t status:1; /* [0:0] */
		uint32_t rsvd1:15; /* [15:1] */
		uint32_t states:2; /* [17:16] */
		uint32_t rsvd0:14; /* [31:18] */
	};
	uint32_t val;
};

union pmu_lpi_residual_cmu_pcie_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_residual_cmu_pcie_duration0 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_residual_cmu_pcie_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_residual_cmu_pcie_duration2 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_residual_cmu_pcie_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_residual_cmu_dram_configuration {
	struct {
		uint32_t local_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_lpi_residual_cmu_dram_status {
	struct {
		uint32_t status:1; /* [0:0] */
		uint32_t rsvd1:15; /* [15:1] */
		uint32_t states:2; /* [17:16] */
		uint32_t rsvd0:14; /* [31:18] */
	};
	uint32_t val;
};

union pmu_lpi_residual_cmu_dram_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_residual_cmu_dram_duration0 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_residual_cmu_dram_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_residual_cmu_dram_duration2 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_residual_cmu_dram_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_residual_cmu_dcl0_configuration {
	struct {
		uint32_t local_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_lpi_residual_cmu_dcl0_status {
	struct {
		uint32_t status:1; /* [0:0] */
		uint32_t rsvd1:15; /* [15:1] */
		uint32_t states:2; /* [17:16] */
		uint32_t rsvd0:14; /* [31:18] */
	};
	uint32_t val;
};

union pmu_lpi_residual_cmu_dcl0_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_residual_cmu_dcl0_duration0 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_residual_cmu_dcl0_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_residual_cmu_dcl0_duration2 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_residual_cmu_dcl0_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_residual_cmu_dcl1_configuration {
	struct {
		uint32_t local_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_lpi_residual_cmu_dcl1_status {
	struct {
		uint32_t status:1; /* [0:0] */
		uint32_t rsvd1:15; /* [15:1] */
		uint32_t states:2; /* [17:16] */
		uint32_t rsvd0:14; /* [31:18] */
	};
	uint32_t val;
};

union pmu_lpi_residual_cmu_dcl1_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_residual_cmu_dcl1_duration0 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_residual_cmu_dcl1_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_residual_cmu_dcl1_duration2 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_residual_cmu_dcl1_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_residual_cmu_rbch00_configuration {
	struct {
		uint32_t local_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_lpi_residual_cmu_rbch00_status {
	struct {
		uint32_t status:1; /* [0:0] */
		uint32_t rsvd1:15; /* [15:1] */
		uint32_t states:2; /* [17:16] */
		uint32_t rsvd0:14; /* [31:18] */
	};
	uint32_t val;
};

union pmu_lpi_residual_cmu_rbch00_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_residual_cmu_rbch00_duration0 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_residual_cmu_rbch00_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_residual_cmu_rbch00_duration2 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_residual_cmu_rbch00_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_residual_cmu_rbch01_configuration {
	struct {
		uint32_t local_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_lpi_residual_cmu_rbch01_status {
	struct {
		uint32_t status:1; /* [0:0] */
		uint32_t rsvd1:15; /* [15:1] */
		uint32_t states:2; /* [17:16] */
		uint32_t rsvd0:14; /* [31:18] */
	};
	uint32_t val;
};

union pmu_lpi_residual_cmu_rbch01_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_residual_cmu_rbch01_duration0 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_residual_cmu_rbch01_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_residual_cmu_rbch01_duration2 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_residual_cmu_rbch01_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_residual_cmu_rbcv00_configuration {
	struct {
		uint32_t local_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_lpi_residual_cmu_rbcv00_status {
	struct {
		uint32_t status:1; /* [0:0] */
		uint32_t rsvd1:15; /* [15:1] */
		uint32_t states:2; /* [17:16] */
		uint32_t rsvd0:14; /* [31:18] */
	};
	uint32_t val;
};

union pmu_lpi_residual_cmu_rbcv00_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_residual_cmu_rbcv00_duration0 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_residual_cmu_rbcv00_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_residual_cmu_rbcv00_duration2 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_residual_cmu_rbcv00_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_residual_cmu_rbcv01_configuration {
	struct {
		uint32_t local_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_lpi_residual_cmu_rbcv01_status {
	struct {
		uint32_t status:1; /* [0:0] */
		uint32_t rsvd1:15; /* [15:1] */
		uint32_t states:2; /* [17:16] */
		uint32_t rsvd0:14; /* [31:18] */
	};
	uint32_t val;
};

union pmu_lpi_residual_cmu_rbcv01_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_residual_cmu_rbcv01_duration0 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_residual_cmu_rbcv01_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_residual_cmu_rbcv01_duration2 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_residual_cmu_rbcv01_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_residual_cmu_rbcv10_configuration {
	struct {
		uint32_t local_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_lpi_residual_cmu_rbcv10_status {
	struct {
		uint32_t status:1; /* [0:0] */
		uint32_t rsvd1:15; /* [15:1] */
		uint32_t states:2; /* [17:16] */
		uint32_t rsvd0:14; /* [31:18] */
	};
	uint32_t val;
};

union pmu_lpi_residual_cmu_rbcv10_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_residual_cmu_rbcv10_duration0 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_residual_cmu_rbcv10_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_residual_cmu_rbcv10_duration2 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_residual_cmu_rbcv10_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_residual_cmu_rbcv11_configuration {
	struct {
		uint32_t local_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_lpi_residual_cmu_rbcv11_status {
	struct {
		uint32_t status:1; /* [0:0] */
		uint32_t rsvd1:15; /* [15:1] */
		uint32_t states:2; /* [17:16] */
		uint32_t rsvd0:14; /* [31:18] */
	};
	uint32_t val;
};

union pmu_lpi_residual_cmu_rbcv11_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_residual_cmu_rbcv11_duration0 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_residual_cmu_rbcv11_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_residual_cmu_rbcv11_duration2 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_residual_cmu_rbcv11_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_residual_cmu_rot_configuration {
	struct {
		uint32_t local_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_lpi_residual_cmu_rot_status {
	struct {
		uint32_t status:1; /* [0:0] */
		uint32_t rsvd1:15; /* [15:1] */
		uint32_t states:2; /* [17:16] */
		uint32_t rsvd0:14; /* [31:18] */
	};
	uint32_t val;
};

union pmu_lpi_residual_cmu_rot_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_residual_cmu_rot_duration0 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_residual_cmu_rot_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_residual_cmu_rot_duration2 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_residual_cmu_rot_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_residual_cmu_peri0_configuration {
	struct {
		uint32_t local_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_lpi_residual_cmu_peri0_status {
	struct {
		uint32_t status:1; /* [0:0] */
		uint32_t rsvd1:15; /* [15:1] */
		uint32_t states:2; /* [17:16] */
		uint32_t rsvd0:14; /* [31:18] */
	};
	uint32_t val;
};

union pmu_lpi_residual_cmu_peri0_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_residual_cmu_peri0_duration0 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_residual_cmu_peri0_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_residual_cmu_peri0_duration2 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_residual_cmu_peri0_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_residual_cmu_peri1_configuration {
	struct {
		uint32_t local_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_lpi_residual_cmu_peri1_status {
	struct {
		uint32_t status:1; /* [0:0] */
		uint32_t rsvd1:15; /* [15:1] */
		uint32_t states:2; /* [17:16] */
		uint32_t rsvd0:14; /* [31:18] */
	};
	uint32_t val;
};

union pmu_lpi_residual_cmu_peri1_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_residual_cmu_peri1_duration0 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_residual_cmu_peri1_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_residual_cmu_peri1_duration2 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_residual_cmu_peri1_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_residual_cmu_sbus_u_configuration {
	struct {
		uint32_t local_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_lpi_residual_cmu_sbus_u_status {
	struct {
		uint32_t status:1; /* [0:0] */
		uint32_t rsvd1:15; /* [15:1] */
		uint32_t states:2; /* [17:16] */
		uint32_t rsvd0:14; /* [31:18] */
	};
	uint32_t val;
};

union pmu_lpi_residual_cmu_sbus_u_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_residual_cmu_sbus_u_duration0 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_residual_cmu_sbus_u_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_residual_cmu_sbus_u_duration2 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_residual_cmu_sbus_u_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_residual_cmu_sbus_d_configuration {
	struct {
		uint32_t local_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_lpi_residual_cmu_sbus_d_status {
	struct {
		uint32_t status:1; /* [0:0] */
		uint32_t rsvd1:15; /* [15:1] */
		uint32_t states:2; /* [17:16] */
		uint32_t rsvd0:14; /* [31:18] */
	};
	uint32_t val;
};

union pmu_lpi_residual_cmu_sbus_d_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_residual_cmu_sbus_d_duration0 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_residual_cmu_sbus_d_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_residual_cmu_sbus_d_duration2 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_residual_cmu_sbus_d_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_residual_cmu_sbus_l_configuration {
	struct {
		uint32_t local_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_lpi_residual_cmu_sbus_l_status {
	struct {
		uint32_t status:1; /* [0:0] */
		uint32_t rsvd1:15; /* [15:1] */
		uint32_t states:2; /* [17:16] */
		uint32_t rsvd0:14; /* [31:18] */
	};
	uint32_t val;
};

union pmu_lpi_residual_cmu_sbus_l_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_residual_cmu_sbus_l_duration0 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_residual_cmu_sbus_l_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_residual_cmu_sbus_l_duration2 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_residual_cmu_sbus_l_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_residual_cmu_nbus_u_configuration {
	struct {
		uint32_t local_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_lpi_residual_cmu_nbus_u_status {
	struct {
		uint32_t status:1; /* [0:0] */
		uint32_t rsvd1:15; /* [15:1] */
		uint32_t states:2; /* [17:16] */
		uint32_t rsvd0:14; /* [31:18] */
	};
	uint32_t val;
};

union pmu_lpi_residual_cmu_nbus_u_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_residual_cmu_nbus_u_duration0 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_residual_cmu_nbus_u_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_residual_cmu_nbus_u_duration2 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_residual_cmu_nbus_u_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_residual_cmu_nbus_d_configuration {
	struct {
		uint32_t local_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_lpi_residual_cmu_nbus_d_status {
	struct {
		uint32_t status:1; /* [0:0] */
		uint32_t rsvd1:15; /* [15:1] */
		uint32_t states:2; /* [17:16] */
		uint32_t rsvd0:14; /* [31:18] */
	};
	uint32_t val;
};

union pmu_lpi_residual_cmu_nbus_d_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_residual_cmu_nbus_d_duration0 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_residual_cmu_nbus_d_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_residual_cmu_nbus_d_duration2 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_residual_cmu_nbus_d_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_residual_cmu_nbus_l_configuration {
	struct {
		uint32_t local_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_lpi_residual_cmu_nbus_l_status {
	struct {
		uint32_t status:1; /* [0:0] */
		uint32_t rsvd1:15; /* [15:1] */
		uint32_t states:2; /* [17:16] */
		uint32_t rsvd0:14; /* [31:18] */
	};
	uint32_t val;
};

union pmu_lpi_residual_cmu_nbus_l_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_residual_cmu_nbus_l_duration0 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_residual_cmu_nbus_l_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_residual_cmu_nbus_l_duration2 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_residual_cmu_nbus_l_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_residual_cmu_wbus_u_configuration {
	struct {
		uint32_t local_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_lpi_residual_cmu_wbus_u_status {
	struct {
		uint32_t status:1; /* [0:0] */
		uint32_t rsvd1:15; /* [15:1] */
		uint32_t states:2; /* [17:16] */
		uint32_t rsvd0:14; /* [31:18] */
	};
	uint32_t val;
};

union pmu_lpi_residual_cmu_wbus_u_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_residual_cmu_wbus_u_duration0 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_residual_cmu_wbus_u_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_residual_cmu_wbus_u_duration2 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_residual_cmu_wbus_u_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_residual_cmu_wbus_d_configuration {
	struct {
		uint32_t local_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_lpi_residual_cmu_wbus_d_status {
	struct {
		uint32_t status:1; /* [0:0] */
		uint32_t rsvd1:15; /* [15:1] */
		uint32_t states:2; /* [17:16] */
		uint32_t rsvd0:14; /* [31:18] */
	};
	uint32_t val;
};

union pmu_lpi_residual_cmu_wbus_d_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_residual_cmu_wbus_d_duration0 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_residual_cmu_wbus_d_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_residual_cmu_wbus_d_duration2 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_residual_cmu_wbus_d_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_residual_cmu_ebus_u_configuration {
	struct {
		uint32_t local_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_lpi_residual_cmu_ebus_u_status {
	struct {
		uint32_t status:1; /* [0:0] */
		uint32_t rsvd1:15; /* [15:1] */
		uint32_t states:2; /* [17:16] */
		uint32_t rsvd0:14; /* [31:18] */
	};
	uint32_t val;
};

union pmu_lpi_residual_cmu_ebus_u_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_residual_cmu_ebus_u_duration0 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_residual_cmu_ebus_u_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_residual_cmu_ebus_u_duration2 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_residual_cmu_ebus_u_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_residual_cmu_ebus_d_configuration {
	struct {
		uint32_t local_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_lpi_residual_cmu_ebus_d_status {
	struct {
		uint32_t status:1; /* [0:0] */
		uint32_t rsvd1:15; /* [15:1] */
		uint32_t states:2; /* [17:16] */
		uint32_t rsvd0:14; /* [31:18] */
	};
	uint32_t val;
};

union pmu_lpi_residual_cmu_ebus_d_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_residual_cmu_ebus_d_duration0 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_residual_cmu_ebus_d_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_residual_cmu_ebus_d_duration2 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_residual_cmu_ebus_d_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_residual_cmu_ebus_r_configuration {
	struct {
		uint32_t local_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_lpi_residual_cmu_ebus_r_status {
	struct {
		uint32_t status:1; /* [0:0] */
		uint32_t rsvd1:15; /* [15:1] */
		uint32_t states:2; /* [17:16] */
		uint32_t rsvd0:14; /* [31:18] */
	};
	uint32_t val;
};

union pmu_lpi_residual_cmu_ebus_r_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_residual_cmu_ebus_r_duration0 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_residual_cmu_ebus_r_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_residual_cmu_ebus_r_duration2 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_residual_cmu_ebus_r_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_bus_cmu_cp0_configuration {
	struct {
		uint32_t local_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_lpi_bus_cmu_cp0_status {
	struct {
		uint32_t status:1; /* [0:0] */
		uint32_t rsvd1:15; /* [15:1] */
		uint32_t states:2; /* [17:16] */
		uint32_t rsvd0:14; /* [31:18] */
	};
	uint32_t val;
};

union pmu_lpi_bus_cmu_cp0_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_bus_cmu_cp0_duration0 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_bus_cmu_cp0_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_bus_cmu_cp0_duration2 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_bus_cmu_cp0_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_bus_cmu_cp1_configuration {
	struct {
		uint32_t local_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_lpi_bus_cmu_cp1_status {
	struct {
		uint32_t status:1; /* [0:0] */
		uint32_t rsvd1:15; /* [15:1] */
		uint32_t states:2; /* [17:16] */
		uint32_t rsvd0:14; /* [31:18] */
	};
	uint32_t val;
};

union pmu_lpi_bus_cmu_cp1_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_bus_cmu_cp1_duration0 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_bus_cmu_cp1_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_bus_cmu_cp1_duration2 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_bus_cmu_cp1_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_bus_cmu_pcie_configuration {
	struct {
		uint32_t local_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_lpi_bus_cmu_pcie_status {
	struct {
		uint32_t status:1; /* [0:0] */
		uint32_t rsvd1:15; /* [15:1] */
		uint32_t states:2; /* [17:16] */
		uint32_t rsvd0:14; /* [31:18] */
	};
	uint32_t val;
};

union pmu_lpi_bus_cmu_pcie_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_bus_cmu_pcie_duration0 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_bus_cmu_pcie_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_bus_cmu_pcie_duration2 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_bus_cmu_pcie_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_bus_cmu_dram_configuration {
	struct {
		uint32_t local_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_lpi_bus_cmu_dram_status {
	struct {
		uint32_t status:1; /* [0:0] */
		uint32_t rsvd1:15; /* [15:1] */
		uint32_t states:2; /* [17:16] */
		uint32_t rsvd0:14; /* [31:18] */
	};
	uint32_t val;
};

union pmu_lpi_bus_cmu_dram_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_bus_cmu_dram_duration0 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_bus_cmu_dram_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_bus_cmu_dram_duration2 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_bus_cmu_dram_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_bus_cmu_dcl0_configuration {
	struct {
		uint32_t local_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_lpi_bus_cmu_dcl0_status {
	struct {
		uint32_t status:1; /* [0:0] */
		uint32_t rsvd1:15; /* [15:1] */
		uint32_t states:2; /* [17:16] */
		uint32_t rsvd0:14; /* [31:18] */
	};
	uint32_t val;
};

union pmu_lpi_bus_cmu_dcl0_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_bus_cmu_dcl0_duration0 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_bus_cmu_dcl0_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_bus_cmu_dcl0_duration2 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_bus_cmu_dcl0_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_bus_cmu_dcl1_configuration {
	struct {
		uint32_t local_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_lpi_bus_cmu_dcl1_status {
	struct {
		uint32_t status:1; /* [0:0] */
		uint32_t rsvd1:15; /* [15:1] */
		uint32_t states:2; /* [17:16] */
		uint32_t rsvd0:14; /* [31:18] */
	};
	uint32_t val;
};

union pmu_lpi_bus_cmu_dcl1_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_bus_cmu_dcl1_duration0 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_bus_cmu_dcl1_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_bus_cmu_dcl1_duration2 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_bus_cmu_dcl1_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_bus_cmu_rbch00_configuration {
	struct {
		uint32_t local_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_lpi_bus_cmu_rbch00_status {
	struct {
		uint32_t status:1; /* [0:0] */
		uint32_t rsvd1:15; /* [15:1] */
		uint32_t states:2; /* [17:16] */
		uint32_t rsvd0:14; /* [31:18] */
	};
	uint32_t val;
};

union pmu_lpi_bus_cmu_rbch00_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_bus_cmu_rbch00_duration0 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_bus_cmu_rbch00_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_bus_cmu_rbch00_duration2 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_bus_cmu_rbch00_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_bus_cmu_rbch01_configuration {
	struct {
		uint32_t local_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_lpi_bus_cmu_rbch01_status {
	struct {
		uint32_t status:1; /* [0:0] */
		uint32_t rsvd1:15; /* [15:1] */
		uint32_t states:2; /* [17:16] */
		uint32_t rsvd0:14; /* [31:18] */
	};
	uint32_t val;
};

union pmu_lpi_bus_cmu_rbch01_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_bus_cmu_rbch01_duration0 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_bus_cmu_rbch01_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_bus_cmu_rbch01_duration2 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_bus_cmu_rbch01_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_bus_cmu_rbcv00_configuration {
	struct {
		uint32_t local_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_lpi_bus_cmu_rbcv00_status {
	struct {
		uint32_t status:1; /* [0:0] */
		uint32_t rsvd1:15; /* [15:1] */
		uint32_t states:2; /* [17:16] */
		uint32_t rsvd0:14; /* [31:18] */
	};
	uint32_t val;
};

union pmu_lpi_bus_cmu_rbcv00_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_bus_cmu_rbcv00_duration0 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_bus_cmu_rbcv00_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_bus_cmu_rbcv00_duration2 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_bus_cmu_rbcv00_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_bus_cmu_rbcv01_configuration {
	struct {
		uint32_t local_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_lpi_bus_cmu_rbcv01_status {
	struct {
		uint32_t status:1; /* [0:0] */
		uint32_t rsvd1:15; /* [15:1] */
		uint32_t states:2; /* [17:16] */
		uint32_t rsvd0:14; /* [31:18] */
	};
	uint32_t val;
};

union pmu_lpi_bus_cmu_rbcv01_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_bus_cmu_rbcv01_duration0 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_bus_cmu_rbcv01_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_bus_cmu_rbcv01_duration2 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_bus_cmu_rbcv01_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_bus_cmu_rbcv10_configuration {
	struct {
		uint32_t local_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_lpi_bus_cmu_rbcv10_status {
	struct {
		uint32_t status:1; /* [0:0] */
		uint32_t rsvd1:15; /* [15:1] */
		uint32_t states:2; /* [17:16] */
		uint32_t rsvd0:14; /* [31:18] */
	};
	uint32_t val;
};

union pmu_lpi_bus_cmu_rbcv10_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_bus_cmu_rbcv10_duration0 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_bus_cmu_rbcv10_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_bus_cmu_rbcv10_duration2 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_bus_cmu_rbcv10_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_bus_cmu_rbcv11_configuration {
	struct {
		uint32_t local_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_lpi_bus_cmu_rbcv11_status {
	struct {
		uint32_t status:1; /* [0:0] */
		uint32_t rsvd1:15; /* [15:1] */
		uint32_t states:2; /* [17:16] */
		uint32_t rsvd0:14; /* [31:18] */
	};
	uint32_t val;
};

union pmu_lpi_bus_cmu_rbcv11_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_bus_cmu_rbcv11_duration0 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_bus_cmu_rbcv11_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_bus_cmu_rbcv11_duration2 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_bus_cmu_rbcv11_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_bus_cmu_rot_configuration {
	struct {
		uint32_t local_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_lpi_bus_cmu_rot_status {
	struct {
		uint32_t status:1; /* [0:0] */
		uint32_t rsvd1:15; /* [15:1] */
		uint32_t states:2; /* [17:16] */
		uint32_t rsvd0:14; /* [31:18] */
	};
	uint32_t val;
};

union pmu_lpi_bus_cmu_rot_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_bus_cmu_rot_duration0 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_bus_cmu_rot_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_bus_cmu_rot_duration2 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_bus_cmu_rot_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_bus_cmu_peri0_configuration {
	struct {
		uint32_t local_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_lpi_bus_cmu_peri0_status {
	struct {
		uint32_t status:1; /* [0:0] */
		uint32_t rsvd1:15; /* [15:1] */
		uint32_t states:2; /* [17:16] */
		uint32_t rsvd0:14; /* [31:18] */
	};
	uint32_t val;
};

union pmu_lpi_bus_cmu_peri0_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_bus_cmu_peri0_duration0 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_bus_cmu_peri0_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_bus_cmu_peri0_duration2 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_bus_cmu_peri0_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_bus_cmu_peri1_configuration {
	struct {
		uint32_t local_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_lpi_bus_cmu_peri1_status {
	struct {
		uint32_t status:1; /* [0:0] */
		uint32_t rsvd1:15; /* [15:1] */
		uint32_t states:2; /* [17:16] */
		uint32_t rsvd0:14; /* [31:18] */
	};
	uint32_t val;
};

union pmu_lpi_bus_cmu_peri1_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_bus_cmu_peri1_duration0 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_bus_cmu_peri1_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_bus_cmu_peri1_duration2 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_bus_cmu_peri1_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_bus_cmu_sbus_u_configuration {
	struct {
		uint32_t local_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_lpi_bus_cmu_sbus_u_status {
	struct {
		uint32_t status:1; /* [0:0] */
		uint32_t rsvd1:15; /* [15:1] */
		uint32_t states:2; /* [17:16] */
		uint32_t rsvd0:14; /* [31:18] */
	};
	uint32_t val;
};

union pmu_lpi_bus_cmu_sbus_u_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_bus_cmu_sbus_u_duration0 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_bus_cmu_sbus_u_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_bus_cmu_sbus_u_duration2 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_bus_cmu_sbus_u_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_bus_cmu_sbus_d_configuration {
	struct {
		uint32_t local_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_lpi_bus_cmu_sbus_d_status {
	struct {
		uint32_t status:1; /* [0:0] */
		uint32_t rsvd1:15; /* [15:1] */
		uint32_t states:2; /* [17:16] */
		uint32_t rsvd0:14; /* [31:18] */
	};
	uint32_t val;
};

union pmu_lpi_bus_cmu_sbus_d_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_bus_cmu_sbus_d_duration0 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_bus_cmu_sbus_d_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_bus_cmu_sbus_d_duration2 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_bus_cmu_sbus_d_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_bus_cmu_sbus_l_configuration {
	struct {
		uint32_t local_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_lpi_bus_cmu_sbus_l_status {
	struct {
		uint32_t status:1; /* [0:0] */
		uint32_t rsvd1:15; /* [15:1] */
		uint32_t states:2; /* [17:16] */
		uint32_t rsvd0:14; /* [31:18] */
	};
	uint32_t val;
};

union pmu_lpi_bus_cmu_sbus_l_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_bus_cmu_sbus_l_duration0 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_bus_cmu_sbus_l_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_bus_cmu_sbus_l_duration2 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_bus_cmu_sbus_l_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_bus_cmu_nbus_u_configuration {
	struct {
		uint32_t local_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_lpi_bus_cmu_nbus_u_status {
	struct {
		uint32_t status:1; /* [0:0] */
		uint32_t rsvd1:15; /* [15:1] */
		uint32_t states:2; /* [17:16] */
		uint32_t rsvd0:14; /* [31:18] */
	};
	uint32_t val;
};

union pmu_lpi_bus_cmu_nbus_u_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_bus_cmu_nbus_u_duration0 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_bus_cmu_nbus_u_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_bus_cmu_nbus_u_duration2 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_bus_cmu_nbus_u_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_bus_cmu_nbus_d_configuration {
	struct {
		uint32_t local_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_lpi_bus_cmu_nbus_d_status {
	struct {
		uint32_t status:1; /* [0:0] */
		uint32_t rsvd1:15; /* [15:1] */
		uint32_t states:2; /* [17:16] */
		uint32_t rsvd0:14; /* [31:18] */
	};
	uint32_t val;
};

union pmu_lpi_bus_cmu_nbus_d_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_bus_cmu_nbus_d_duration0 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_bus_cmu_nbus_d_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_bus_cmu_nbus_d_duration2 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_bus_cmu_nbus_d_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_bus_cmu_nbus_l_configuration {
	struct {
		uint32_t local_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_lpi_bus_cmu_nbus_l_status {
	struct {
		uint32_t status:1; /* [0:0] */
		uint32_t rsvd1:15; /* [15:1] */
		uint32_t states:2; /* [17:16] */
		uint32_t rsvd0:14; /* [31:18] */
	};
	uint32_t val;
};

union pmu_lpi_bus_cmu_nbus_l_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_bus_cmu_nbus_l_duration0 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_bus_cmu_nbus_l_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_bus_cmu_nbus_l_duration2 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_bus_cmu_nbus_l_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_bus_cmu_wbus_u_configuration {
	struct {
		uint32_t local_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_lpi_bus_cmu_wbus_u_status {
	struct {
		uint32_t status:1; /* [0:0] */
		uint32_t rsvd1:15; /* [15:1] */
		uint32_t states:2; /* [17:16] */
		uint32_t rsvd0:14; /* [31:18] */
	};
	uint32_t val;
};

union pmu_lpi_bus_cmu_wbus_u_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_bus_cmu_wbus_u_duration0 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_bus_cmu_wbus_u_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_bus_cmu_wbus_u_duration2 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_bus_cmu_wbus_u_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_bus_cmu_wbus_d_configuration {
	struct {
		uint32_t local_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_lpi_bus_cmu_wbus_d_status {
	struct {
		uint32_t status:1; /* [0:0] */
		uint32_t rsvd1:15; /* [15:1] */
		uint32_t states:2; /* [17:16] */
		uint32_t rsvd0:14; /* [31:18] */
	};
	uint32_t val;
};

union pmu_lpi_bus_cmu_wbus_d_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_bus_cmu_wbus_d_duration0 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_bus_cmu_wbus_d_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_bus_cmu_wbus_d_duration2 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_bus_cmu_wbus_d_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_bus_cmu_ebus_u_configuration {
	struct {
		uint32_t local_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_lpi_bus_cmu_ebus_u_status {
	struct {
		uint32_t status:1; /* [0:0] */
		uint32_t rsvd1:15; /* [15:1] */
		uint32_t states:2; /* [17:16] */
		uint32_t rsvd0:14; /* [31:18] */
	};
	uint32_t val;
};

union pmu_lpi_bus_cmu_ebus_u_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_bus_cmu_ebus_u_duration0 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_bus_cmu_ebus_u_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_bus_cmu_ebus_u_duration2 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_bus_cmu_ebus_u_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_bus_cmu_ebus_d_configuration {
	struct {
		uint32_t local_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_lpi_bus_cmu_ebus_d_status {
	struct {
		uint32_t status:1; /* [0:0] */
		uint32_t rsvd1:15; /* [15:1] */
		uint32_t states:2; /* [17:16] */
		uint32_t rsvd0:14; /* [31:18] */
	};
	uint32_t val;
};

union pmu_lpi_bus_cmu_ebus_d_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_bus_cmu_ebus_d_duration0 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_bus_cmu_ebus_d_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_bus_cmu_ebus_d_duration2 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_bus_cmu_ebus_d_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_bus_cmu_ebus_r_configuration {
	struct {
		uint32_t local_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_lpi_bus_cmu_ebus_r_status {
	struct {
		uint32_t status:1; /* [0:0] */
		uint32_t rsvd1:15; /* [15:1] */
		uint32_t states:2; /* [17:16] */
		uint32_t rsvd0:14; /* [31:18] */
	};
	uint32_t val;
};

union pmu_lpi_bus_cmu_ebus_r_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_bus_cmu_ebus_r_duration0 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_bus_cmu_ebus_r_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_bus_cmu_ebus_r_duration2 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_bus_cmu_ebus_r_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_busmaster_cmu_cp0_configuration {
	struct {
		uint32_t local_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_lpi_busmaster_cmu_cp0_status {
	struct {
		uint32_t status:1; /* [0:0] */
		uint32_t rsvd1:15; /* [15:1] */
		uint32_t states:2; /* [17:16] */
		uint32_t rsvd0:14; /* [31:18] */
	};
	uint32_t val;
};

union pmu_lpi_busmaster_cmu_cp0_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_busmaster_cmu_cp0_duration0 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_busmaster_cmu_cp0_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_busmaster_cmu_cp0_duration2 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_busmaster_cmu_cp0_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_busmaster_cmu_cp1_configuration {
	struct {
		uint32_t local_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_lpi_busmaster_cmu_cp1_status {
	struct {
		uint32_t status:1; /* [0:0] */
		uint32_t rsvd1:15; /* [15:1] */
		uint32_t states:2; /* [17:16] */
		uint32_t rsvd0:14; /* [31:18] */
	};
	uint32_t val;
};

union pmu_lpi_busmaster_cmu_cp1_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_busmaster_cmu_cp1_duration0 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_busmaster_cmu_cp1_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_busmaster_cmu_cp1_duration2 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_busmaster_cmu_cp1_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_busmaster_cmu_pcie_configuration {
	struct {
		uint32_t local_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_lpi_busmaster_cmu_pcie_status {
	struct {
		uint32_t status:1; /* [0:0] */
		uint32_t rsvd1:15; /* [15:1] */
		uint32_t states:2; /* [17:16] */
		uint32_t rsvd0:14; /* [31:18] */
	};
	uint32_t val;
};

union pmu_lpi_busmaster_cmu_pcie_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_busmaster_cmu_pcie_duration0 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_busmaster_cmu_pcie_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_busmaster_cmu_pcie_duration2 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_busmaster_cmu_pcie_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_busmaster_cmu_dram_configuration {
	struct {
		uint32_t local_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_lpi_busmaster_cmu_dram_status {
	struct {
		uint32_t status:1; /* [0:0] */
		uint32_t rsvd1:15; /* [15:1] */
		uint32_t states:2; /* [17:16] */
		uint32_t rsvd0:14; /* [31:18] */
	};
	uint32_t val;
};

union pmu_lpi_busmaster_cmu_dram_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_busmaster_cmu_dram_duration0 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_busmaster_cmu_dram_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_busmaster_cmu_dram_duration2 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_busmaster_cmu_dram_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_busmaster_cmu_dcl0_configuration {
	struct {
		uint32_t local_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_lpi_busmaster_cmu_dcl0_status {
	struct {
		uint32_t status:1; /* [0:0] */
		uint32_t rsvd1:15; /* [15:1] */
		uint32_t states:2; /* [17:16] */
		uint32_t rsvd0:14; /* [31:18] */
	};
	uint32_t val;
};

union pmu_lpi_busmaster_cmu_dcl0_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_busmaster_cmu_dcl0_duration0 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_busmaster_cmu_dcl0_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_busmaster_cmu_dcl0_duration2 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_busmaster_cmu_dcl0_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_busmaster_cmu_dcl1_configuration {
	struct {
		uint32_t local_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_lpi_busmaster_cmu_dcl1_status {
	struct {
		uint32_t status:1; /* [0:0] */
		uint32_t rsvd1:15; /* [15:1] */
		uint32_t states:2; /* [17:16] */
		uint32_t rsvd0:14; /* [31:18] */
	};
	uint32_t val;
};

union pmu_lpi_busmaster_cmu_dcl1_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_busmaster_cmu_dcl1_duration0 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_busmaster_cmu_dcl1_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_busmaster_cmu_dcl1_duration2 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_busmaster_cmu_dcl1_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_busmaster_cmu_rbch00_configuration {
	struct {
		uint32_t local_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_lpi_busmaster_cmu_rbch00_status {
	struct {
		uint32_t status:1; /* [0:0] */
		uint32_t rsvd1:15; /* [15:1] */
		uint32_t states:2; /* [17:16] */
		uint32_t rsvd0:14; /* [31:18] */
	};
	uint32_t val;
};

union pmu_lpi_busmaster_cmu_rbch00_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_busmaster_cmu_rbch00_duration0 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_busmaster_cmu_rbch00_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_busmaster_cmu_rbch00_duration2 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_busmaster_cmu_rbch00_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_busmaster_cmu_rbch01_configuration {
	struct {
		uint32_t local_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_lpi_busmaster_cmu_rbch01_status {
	struct {
		uint32_t status:1; /* [0:0] */
		uint32_t rsvd1:15; /* [15:1] */
		uint32_t states:2; /* [17:16] */
		uint32_t rsvd0:14; /* [31:18] */
	};
	uint32_t val;
};

union pmu_lpi_busmaster_cmu_rbch01_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_busmaster_cmu_rbch01_duration0 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_busmaster_cmu_rbch01_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_busmaster_cmu_rbch01_duration2 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_busmaster_cmu_rbch01_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_busmaster_cmu_rbcv00_configuration {
	struct {
		uint32_t local_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_lpi_busmaster_cmu_rbcv00_status {
	struct {
		uint32_t status:1; /* [0:0] */
		uint32_t rsvd1:15; /* [15:1] */
		uint32_t states:2; /* [17:16] */
		uint32_t rsvd0:14; /* [31:18] */
	};
	uint32_t val;
};

union pmu_lpi_busmaster_cmu_rbcv00_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_busmaster_cmu_rbcv00_duration0 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_busmaster_cmu_rbcv00_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_busmaster_cmu_rbcv00_duration2 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_busmaster_cmu_rbcv00_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_busmaster_cmu_rbcv01_configuration {
	struct {
		uint32_t local_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_lpi_busmaster_cmu_rbcv01_status {
	struct {
		uint32_t status:1; /* [0:0] */
		uint32_t rsvd1:15; /* [15:1] */
		uint32_t states:2; /* [17:16] */
		uint32_t rsvd0:14; /* [31:18] */
	};
	uint32_t val;
};

union pmu_lpi_busmaster_cmu_rbcv01_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_busmaster_cmu_rbcv01_duration0 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_busmaster_cmu_rbcv01_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_busmaster_cmu_rbcv01_duration2 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_busmaster_cmu_rbcv01_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_busmaster_cmu_rbcv10_configuration {
	struct {
		uint32_t local_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_lpi_busmaster_cmu_rbcv10_status {
	struct {
		uint32_t status:1; /* [0:0] */
		uint32_t rsvd1:15; /* [15:1] */
		uint32_t states:2; /* [17:16] */
		uint32_t rsvd0:14; /* [31:18] */
	};
	uint32_t val;
};

union pmu_lpi_busmaster_cmu_rbcv10_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_busmaster_cmu_rbcv10_duration0 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_busmaster_cmu_rbcv10_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_busmaster_cmu_rbcv10_duration2 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_busmaster_cmu_rbcv10_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_busmaster_cmu_rbcv11_configuration {
	struct {
		uint32_t local_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_lpi_busmaster_cmu_rbcv11_status {
	struct {
		uint32_t status:1; /* [0:0] */
		uint32_t rsvd1:15; /* [15:1] */
		uint32_t states:2; /* [17:16] */
		uint32_t rsvd0:14; /* [31:18] */
	};
	uint32_t val;
};

union pmu_lpi_busmaster_cmu_rbcv11_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_busmaster_cmu_rbcv11_duration0 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_busmaster_cmu_rbcv11_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_busmaster_cmu_rbcv11_duration2 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_busmaster_cmu_rbcv11_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_busmaster_cmu_rot_configuration {
	struct {
		uint32_t local_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_lpi_busmaster_cmu_rot_status {
	struct {
		uint32_t status:1; /* [0:0] */
		uint32_t rsvd1:15; /* [15:1] */
		uint32_t states:2; /* [17:16] */
		uint32_t rsvd0:14; /* [31:18] */
	};
	uint32_t val;
};

union pmu_lpi_busmaster_cmu_rot_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_busmaster_cmu_rot_duration0 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_busmaster_cmu_rot_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_busmaster_cmu_rot_duration2 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_busmaster_cmu_rot_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_busmaster_cmu_peri0_configuration {
	struct {
		uint32_t local_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_lpi_busmaster_cmu_peri0_status {
	struct {
		uint32_t status:1; /* [0:0] */
		uint32_t rsvd1:15; /* [15:1] */
		uint32_t states:2; /* [17:16] */
		uint32_t rsvd0:14; /* [31:18] */
	};
	uint32_t val;
};

union pmu_lpi_busmaster_cmu_peri0_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_busmaster_cmu_peri0_duration0 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_busmaster_cmu_peri0_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_busmaster_cmu_peri0_duration2 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_busmaster_cmu_peri0_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_busmaster_cmu_peri1_configuration {
	struct {
		uint32_t local_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_lpi_busmaster_cmu_peri1_status {
	struct {
		uint32_t status:1; /* [0:0] */
		uint32_t rsvd1:15; /* [15:1] */
		uint32_t states:2; /* [17:16] */
		uint32_t rsvd0:14; /* [31:18] */
	};
	uint32_t val;
};

union pmu_lpi_busmaster_cmu_peri1_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_busmaster_cmu_peri1_duration0 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_busmaster_cmu_peri1_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_busmaster_cmu_peri1_duration2 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_busmaster_cmu_peri1_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_busmaster_cmu_sbus_u_configuration {
	struct {
		uint32_t local_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_lpi_busmaster_cmu_sbus_u_status {
	struct {
		uint32_t status:1; /* [0:0] */
		uint32_t rsvd1:15; /* [15:1] */
		uint32_t states:2; /* [17:16] */
		uint32_t rsvd0:14; /* [31:18] */
	};
	uint32_t val;
};

union pmu_lpi_busmaster_cmu_sbus_u_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_busmaster_cmu_sbus_u_duration0 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_busmaster_cmu_sbus_u_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_busmaster_cmu_sbus_u_duration2 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_busmaster_cmu_sbus_u_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_busmaster_cmu_sbus_d_configuration {
	struct {
		uint32_t local_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_lpi_busmaster_cmu_sbus_d_status {
	struct {
		uint32_t status:1; /* [0:0] */
		uint32_t rsvd1:15; /* [15:1] */
		uint32_t states:2; /* [17:16] */
		uint32_t rsvd0:14; /* [31:18] */
	};
	uint32_t val;
};

union pmu_lpi_busmaster_cmu_sbus_d_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_busmaster_cmu_sbus_d_duration0 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_busmaster_cmu_sbus_d_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_busmaster_cmu_sbus_d_duration2 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_busmaster_cmu_sbus_d_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_busmaster_cmu_sbus_l_configuration {
	struct {
		uint32_t local_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_lpi_busmaster_cmu_sbus_l_status {
	struct {
		uint32_t status:1; /* [0:0] */
		uint32_t rsvd1:15; /* [15:1] */
		uint32_t states:2; /* [17:16] */
		uint32_t rsvd0:14; /* [31:18] */
	};
	uint32_t val;
};

union pmu_lpi_busmaster_cmu_sbus_l_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_busmaster_cmu_sbus_l_duration0 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_busmaster_cmu_sbus_l_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_busmaster_cmu_sbus_l_duration2 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_busmaster_cmu_sbus_l_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_busmaster_cmu_nbus_u_configuration {
	struct {
		uint32_t local_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_lpi_busmaster_cmu_nbus_u_status {
	struct {
		uint32_t status:1; /* [0:0] */
		uint32_t rsvd1:15; /* [15:1] */
		uint32_t states:2; /* [17:16] */
		uint32_t rsvd0:14; /* [31:18] */
	};
	uint32_t val;
};

union pmu_lpi_busmaster_cmu_nbus_u_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_busmaster_cmu_nbus_u_duration0 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_busmaster_cmu_nbus_u_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_busmaster_cmu_nbus_u_duration2 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_busmaster_cmu_nbus_u_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_busmaster_cmu_nbus_d_configuration {
	struct {
		uint32_t local_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_lpi_busmaster_cmu_nbus_d_status {
	struct {
		uint32_t status:1; /* [0:0] */
		uint32_t rsvd1:15; /* [15:1] */
		uint32_t states:2; /* [17:16] */
		uint32_t rsvd0:14; /* [31:18] */
	};
	uint32_t val;
};

union pmu_lpi_busmaster_cmu_nbus_d_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_busmaster_cmu_nbus_d_duration0 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_busmaster_cmu_nbus_d_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_busmaster_cmu_nbus_d_duration2 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_busmaster_cmu_nbus_d_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_busmaster_cmu_nbus_l_configuration {
	struct {
		uint32_t local_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_lpi_busmaster_cmu_nbus_l_status {
	struct {
		uint32_t status:1; /* [0:0] */
		uint32_t rsvd1:15; /* [15:1] */
		uint32_t states:2; /* [17:16] */
		uint32_t rsvd0:14; /* [31:18] */
	};
	uint32_t val;
};

union pmu_lpi_busmaster_cmu_nbus_l_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_busmaster_cmu_nbus_l_duration0 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_busmaster_cmu_nbus_l_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_busmaster_cmu_nbus_l_duration2 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_busmaster_cmu_nbus_l_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_busmaster_cmu_wbus_u_configuration {
	struct {
		uint32_t local_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_lpi_busmaster_cmu_wbus_u_status {
	struct {
		uint32_t status:1; /* [0:0] */
		uint32_t rsvd1:15; /* [15:1] */
		uint32_t states:2; /* [17:16] */
		uint32_t rsvd0:14; /* [31:18] */
	};
	uint32_t val;
};

union pmu_lpi_busmaster_cmu_wbus_u_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_busmaster_cmu_wbus_u_duration0 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_busmaster_cmu_wbus_u_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_busmaster_cmu_wbus_u_duration2 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_busmaster_cmu_wbus_u_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_busmaster_cmu_wbus_d_configuration {
	struct {
		uint32_t local_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_lpi_busmaster_cmu_wbus_d_status {
	struct {
		uint32_t status:1; /* [0:0] */
		uint32_t rsvd1:15; /* [15:1] */
		uint32_t states:2; /* [17:16] */
		uint32_t rsvd0:14; /* [31:18] */
	};
	uint32_t val;
};

union pmu_lpi_busmaster_cmu_wbus_d_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_busmaster_cmu_wbus_d_duration0 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_busmaster_cmu_wbus_d_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_busmaster_cmu_wbus_d_duration2 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_busmaster_cmu_wbus_d_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_busmaster_cmu_ebus_u_configuration {
	struct {
		uint32_t local_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_lpi_busmaster_cmu_ebus_u_status {
	struct {
		uint32_t status:1; /* [0:0] */
		uint32_t rsvd1:15; /* [15:1] */
		uint32_t states:2; /* [17:16] */
		uint32_t rsvd0:14; /* [31:18] */
	};
	uint32_t val;
};

union pmu_lpi_busmaster_cmu_ebus_u_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_busmaster_cmu_ebus_u_duration0 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_busmaster_cmu_ebus_u_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_busmaster_cmu_ebus_u_duration2 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_busmaster_cmu_ebus_u_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_busmaster_cmu_ebus_d_configuration {
	struct {
		uint32_t local_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_lpi_busmaster_cmu_ebus_d_status {
	struct {
		uint32_t status:1; /* [0:0] */
		uint32_t rsvd1:15; /* [15:1] */
		uint32_t states:2; /* [17:16] */
		uint32_t rsvd0:14; /* [31:18] */
	};
	uint32_t val;
};

union pmu_lpi_busmaster_cmu_ebus_d_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_busmaster_cmu_ebus_d_duration0 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_busmaster_cmu_ebus_d_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_busmaster_cmu_ebus_d_duration2 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_busmaster_cmu_ebus_d_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_busmaster_cmu_ebus_r_configuration {
	struct {
		uint32_t local_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_lpi_busmaster_cmu_ebus_r_status {
	struct {
		uint32_t status:1; /* [0:0] */
		uint32_t rsvd1:15; /* [15:1] */
		uint32_t states:2; /* [17:16] */
		uint32_t rsvd0:14; /* [31:18] */
	};
	uint32_t val;
};

union pmu_lpi_busmaster_cmu_ebus_r_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_busmaster_cmu_ebus_r_duration0 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_busmaster_cmu_ebus_r_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_busmaster_cmu_ebus_r_duration2 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_busmaster_cmu_ebus_r_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_hbm_cmu_dram_configuration {
	struct {
		uint32_t local_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_lpi_hbm_cmu_dram_status {
	struct {
		uint32_t status:1; /* [0:0] */
		uint32_t rsvd1:15; /* [15:1] */
		uint32_t states:2; /* [17:16] */
		uint32_t rsvd0:14; /* [31:18] */
	};
	uint32_t val;
};

union pmu_lpi_hbm_cmu_dram_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_hbm_cmu_dram_duration0 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_hbm_cmu_dram_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_hbm_cmu_dram_duration2 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_lpi_hbm_cmu_dram_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_cm7_cpu_pcie_configuration {
	struct {
		uint32_t local_pwr_cfg:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_cm7_cpu_pcie_status {
	struct {
		uint32_t status:1; /* [0:0] */
		uint32_t rsvd1:15; /* [15:1] */
		uint32_t states:2; /* [17:16] */
		uint32_t rsvd0:14; /* [31:18] */
	};
	uint32_t val;
};

union pmu_cm7_cpu_pcie_option {
	struct {
		uint32_t enable_cpu:1; /* [0:0] */
		uint32_t rsvd1:3; /* [3:1] */
		uint32_t lpi_reqeuset:1; /* [4:4] */
		uint32_t lpi_acknowledge:1; /* [5:5] */
		uint32_t rsvd0:26; /* [31:6] */
	};
	uint32_t val;
};

union pmu_cm7_cpu_pcie_reset {
	struct {
		uint32_t swreset_poreset:1; /* [0:0] */
		uint32_t swreset_sysreset:1; /* [1:1] */
		uint32_t swreset_etmreset:1; /* [2:2] */
		uint32_t rsvd5:1; /* [3:3] */
		uint32_t swreset_use_standbywfi:1; /* [4:4] */
		uint32_t rsvd4:1; /* [5:5] */
		uint32_t disable_hotreset_sysresetreq_lockup_poreset:1; /* [6:6] */
		uint32_t disable_hotreset_sysresetreq_lockup_etmreset:1; /* [7:7] */
		uint32_t disable_level3_poreset:1; /* [8:8] */
		uint32_t disable_level3_sysreset:1; /* [9:9] */
		uint32_t disable_level3_etmreset:1; /* [10:10] */
		uint32_t rsvd3:1; /* [11:11] */
		uint32_t disable_level2_poreset:1; /* [12:12] */
		uint32_t disable_level2_sysreset:1; /* [13:13] */
		uint32_t disable_level2_etmreset:1; /* [14:14] */
		uint32_t rsvd2:1; /* [15:15] */
		uint32_t disable_level1_poreset:1; /* [16:16] */
		uint32_t disable_level1_sysreset:1; /* [17:17] */
		uint32_t disable_level1_etmreset:1; /* [18:18] */
		uint32_t rsvd1:9; /* [27:19] */
		uint32_t sysresetreq_use_standbywfi:1; /* [28:28] */
		uint32_t main_resetn_use_standbywfi:1; /* [29:29] */
		uint32_t rsvd0:1; /* [30:30] */
		uint32_t enable_sysresetreq:1; /* [31:31] */
	};
	uint32_t val;
};

union pmu_cm7_cpu_pcie_duration0 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_cm7_cpu_pcie_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_cm7_cpu_pcie_duration2 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_cm7_cpu_pcie_duration3 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_jtag_dbg_det {
	struct {
		uint32_t hot_insert_en:1; /* [0:0] */
		uint32_t use_cpu_mode:1; /* [1:1] */
		uint32_t use_ss_dbg_mode:1; /* [2:2] */
		uint32_t rsvd2:1; /* [3:3] */
		uint32_t sw_dbg_pwr_mode:1; /* [4:4] */
		uint32_t rsvd1:11; /* [15:5] */
		uint32_t hot_insert_clr:1; /* [16:16] */
		uint32_t rsvd0:15; /* [31:17] */
	};
	uint32_t val;
};

union pmu_cluster0_corerst_lock {
	struct {
		uint32_t hold_en:4; /* [3:0] */
		uint32_t hold_ctrl:4; /* [7:4] */
		uint32_t rsvd1:8; /* [15:8] */
		uint32_t hold_status:4; /* [19:16] */
		uint32_t rsvd0:12; /* [31:20] */
	};
	uint32_t val;
};

union pmu_cluster1_corerst_lock {
	struct {
		uint32_t hold_en:4; /* [3:0] */
		uint32_t hold_ctrl:4; /* [7:4] */
		uint32_t rsvd1:8; /* [15:8] */
		uint32_t hold_status:4; /* [19:16] */
		uint32_t rsvd0:12; /* [31:20] */
	};
	uint32_t val;
};

union pmu_cm7_corerst_lock {
	struct {
		uint32_t hold_en:1; /* [0:0] */
		uint32_t rsvd2:3; /* [3:1] */
		uint32_t hold_ctrl:1; /* [4:4] */
		uint32_t rsvd1:11; /* [15:5] */
		uint32_t hold_status:1; /* [16:16] */
		uint32_t rsvd0:15; /* [31:17] */
	};
	uint32_t val;
};

union pmu_irq_selection {
	struct {
		uint32_t use_dis_irq:1; /* [0:0] */
		uint32_t rsvd0:31; /* [31:1] */
	};
	uint32_t val;
};

union pmu_tcxo_status {
	struct {
		uint32_t status:1; /* [0:0] */
		uint32_t rsvd1:15; /* [15:1] */
		uint32_t states:2; /* [17:16] */
		uint32_t rsvd0:13; /* [30:18] */
		uint32_t stable:1; /* [31:31] */
	};
	uint32_t val;
};

union pmu_tcxo_option {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_tcxo_duration0 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_tcxo_duration1 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_tcxo_duration2 {
	struct {
		uint32_t rsvd0; /* [31:0] */
	};
	uint32_t val;
};

union pmu_tcxo_duration3 {
	struct {
		uint32_t dur_stable:20; /* [19:0] */
		uint32_t rsvd0:12; /* [31:20] */
	};
	uint32_t val;
};

struct pmu {
	union pmu_om_stat om_stat; /* offset : 0x0 */
	uint32_t reserved_1;
	union pmu_xxit_pad_con xxit_pad_con; /* offset : 0x8 */
	uint32_t reserved_2[18];
	union pmu_lpi_dram_ctrl0 lpi_dram_ctrl0; /* offset : 0x54 */
	union pmu_lpi_dram_ctrl1 lpi_dram_ctrl1; /* offset : 0x58 */
	union pmu_hbm_reset_mask hbm_reset_mask; /* offset : 0x5c */
	uint32_t reserved_3[48];
	union pmu_up_scheduler up_scheduler; /* offset : 0x120 */
	uint32_t reserved_4[183];
	union pmu_swreset swreset; /* offset : 0x400 */
	union pmu_rst_stat rst_stat; /* offset : 0x404 */
	union pmu_automatic_disable_wdt automatic_disable_wdt; /* offset : 0x408 */
	union pmu_mask_wdt_reset_request mask_wdt_reset_request; /* offset : 0x40c */
	union pmu_mask_wreset_request mask_wreset_request; /* offset : 0x410 */
	union pmu_cpu_reset_disable_from_level1reset cpu_reset_disable_from_level1reset; /* offset : 0x414 */
	union pmu_cpu_reset_disable_from_level2reset cpu_reset_disable_from_level2reset; /* offset : 0x418 */
	union pmu_cpu_reset_disable_from_level3reset cpu_reset_disable_from_level3reset; /* offset : 0x41c */
	union pmu_wdtreset_lpi wdtreset_lpi; /* offset : 0x420 */
	union pmu_reset_lpi_timeout reset_lpi_timeout; /* offset : 0x424 */
	uint32_t reserved_5[54];
	union pmu_reset_sequencer_configuration reset_sequencer_configuration; /* offset : 0x500 */
	uint32_t reserved_6[3];
	union pmu_reset_sequencer_duration0 reset_sequencer_duration0; /* offset : 0x510 */
	union pmu_reset_sequencer_duration1 reset_sequencer_duration1; /* offset : 0x514 */
	union pmu_reset_sequencer_duration2 reset_sequencer_duration2; /* offset : 0x518 */
	union pmu_reset_sequencer_duration3 reset_sequencer_duration3; /* offset : 0x51c */
	uint32_t reserved_7[184];
	union pmu_inform0 inform0; /* offset : 0x800 */
	union pmu_inform1 inform1; /* offset : 0x804 */
	union pmu_inform2 inform2; /* offset : 0x808 */
	union pmu_inform3 inform3; /* offset : 0x80c */
	union pmu_sysip_dat0 sysip_dat0; /* offset : 0x810 */
	union pmu_sysip_dat1 sysip_dat1; /* offset : 0x814 */
	union pmu_sysip_dat2 sysip_dat2; /* offset : 0x818 */
	union pmu_sysip_dat3 sysip_dat3; /* offset : 0x81c */
	uint32_t reserved_8[8];
	union pmu_inform4 inform4; /* offset : 0x840 */
	union pmu_inform5 inform5; /* offset : 0x844 */
	union pmu_inform6 inform6; /* offset : 0x848 */
	union pmu_inform7 inform7; /* offset : 0x84c */
	union pmu_inform8 inform8; /* offset : 0x850 */
	union pmu_inform9 inform9; /* offset : 0x854 */
	union pmu_inform10 inform10; /* offset : 0x858 */
	union pmu_inform11 inform11; /* offset : 0x85c */
	uint32_t reserved_9[40];
	union pmu_pmu_spare0 pmu_spare0; /* offset : 0x900 */
	union pmu_pmu_spare1 pmu_spare1; /* offset : 0x904 */
	union pmu_pmu_spare2 pmu_spare2; /* offset : 0x908 */
	union pmu_pmu_spare3 pmu_spare3; /* offset : 0x90c */
	uint32_t reserved_10[12];
	union pmu_ack_last_cpu ack_last_cpu; /* offset : 0x940 */
	uint32_t reserved_11[15];
	union pmu_irom_data_reg0 irom_data_reg0; /* offset : 0x980 */
	union pmu_irom_data_reg1 irom_data_reg1; /* offset : 0x984 */
	union pmu_irom_data_reg2 irom_data_reg2; /* offset : 0x988 */
	union pmu_irom_data_reg3 irom_data_reg3; /* offset : 0x98c */
	uint32_t reserved_12[28];
	union pmu_pmu_debug pmu_debug; /* offset : 0xa00 */
	union pmu_arm_control_option arm_control_option; /* offset : 0xa04 */
	union pmu_burnin_ctrl burnin_ctrl; /* offset : 0xa08 */
	uint32_t reserved_13[319];
	union pmu_pmudbg_cluster0_cpu0_status pmudbg_cluster0_cpu0_status; /* offset : 0xf08 */
	union pmu_pmudbg_cluster0_cpu1_status pmudbg_cluster0_cpu1_status; /* offset : 0xf0c */
	union pmu_pmudbg_cluster0_cpu2_status pmudbg_cluster0_cpu2_status; /* offset : 0xf10 */
	union pmu_pmudbg_cluster0_cpu3_status pmudbg_cluster0_cpu3_status; /* offset : 0xf14 */
	uint32_t reserved_14[6];
	union pmu_pmudbg_cluster0_l2_status pmudbg_cluster0_l2_status; /* offset : 0xf30 */
	uint32_t reserved_15;
	union pmu_pmudbg_cluster0_noncpu_status pmudbg_cluster0_noncpu_status; /* offset : 0xf38 */
	union pmu_pmudbg_cluster1_cpu0_status pmudbg_cluster1_cpu0_status; /* offset : 0xf3c */
	union pmu_pmudbg_cluster1_cpu1_status pmudbg_cluster1_cpu1_status; /* offset : 0xf40 */
	union pmu_pmudbg_cluster1_cpu2_status pmudbg_cluster1_cpu2_status; /* offset : 0xf44 */
	union pmu_pmudbg_cluster1_cpu3_status pmudbg_cluster1_cpu3_status; /* offset : 0xf48 */
	union pmu_pmudbg_cluster1_l2_status pmudbg_cluster1_l2_status; /* offset : 0xf4c */
	union pmu_pmudbg_cluster1_noncpu_status pmudbg_cluster1_noncpu_status; /* offset : 0xf50 */
	union pmu_otp_status otp_status; /* offset : 0xf54 */
	union pmu_pmudbg_pmlink_busy_status0 pmudbg_pmlink_busy_status0; /* offset : 0xf58 */
	union pmu_pmudbg_pmlink_busy_status1 pmudbg_pmlink_busy_status1; /* offset : 0xf5c */
	union pmu_pmudbg_pmlink_busy_status2 pmudbg_pmlink_busy_status2; /* offset : 0xf60 */
	union pmu_pmudbg_pmlink_busy_status3 pmudbg_pmlink_busy_status3; /* offset : 0xf64 */
	union pmu_pmudbg_pmlink_busy_status4 pmudbg_pmlink_busy_status4; /* offset : 0xf68 */
	union pmu_pmudbg_pmlink_busy_status5 pmudbg_pmlink_busy_status5; /* offset : 0xf6c */
	union pmu_pmudbg_pmlink_busy_status6 pmudbg_pmlink_busy_status6; /* offset : 0xf70 */
	union pmu_pmudbg_pmlink_busy_status7 pmudbg_pmlink_busy_status7; /* offset : 0xf74 */
	union pmu_pmudbg_pmlink_busy_status8 pmudbg_pmlink_busy_status8; /* offset : 0xf78 */
	union pmu_pmudbg_pmlink_busy_status9 pmudbg_pmlink_busy_status9; /* offset : 0xf7c */
	union pmu_pmudbg_pmlink_busy_status10 pmudbg_pmlink_busy_status10; /* offset : 0xf80 */
	union pmu_pmudbg_pmlink_busy_status11 pmudbg_pmlink_busy_status11; /* offset : 0xf84 */
	union pmu_pmudbg_pmlink_busy_status12 pmudbg_pmlink_busy_status12; /* offset : 0xf88 */
	uint32_t reserved_16[30];
	union pmu_dis_irq_cluster0_cpu0_local_sys_pwr_reg
			dis_irq_cluster0_cpu0_local_sys_pwr_reg; /* offset : 0x1004 */
	uint32_t reserved_17;
	union pmu_dis_irq_cluster0_cpu0_cpusequencer_sys_pwr_reg
			dis_irq_cluster0_cpu0_cpusequencer_sys_pwr_reg; /* offset : 0x100c */
	uint32_t reserved_18;
	union pmu_dis_irq_cluster0_cpu1_local_sys_pwr_reg
			dis_irq_cluster0_cpu1_local_sys_pwr_reg; /* offset : 0x1014 */
	uint32_t reserved_19;
	union pmu_dis_irq_cluster0_cpu1_cpusequencer_sys_pwr_reg
			dis_irq_cluster0_cpu1_cpusequencer_sys_pwr_reg; /* offset : 0x101c */
	uint32_t reserved_20;
	union pmu_dis_irq_cluster0_cpu2_local_sys_pwr_reg
			dis_irq_cluster0_cpu2_local_sys_pwr_reg; /* offset : 0x1024 */
	uint32_t reserved_21;
	union pmu_dis_irq_cluster0_cpu2_cpusequencer_sys_pwr_reg
			dis_irq_cluster0_cpu2_cpusequencer_sys_pwr_reg; /* offset : 0x102c */
	uint32_t reserved_22;
	union pmu_dis_irq_cluster0_cpu3_local_sys_pwr_reg
			dis_irq_cluster0_cpu3_local_sys_pwr_reg; /* offset : 0x1034 */
	uint32_t reserved_23;
	union pmu_dis_irq_cluster0_cpu3_cpusequencer_sys_pwr_reg
			dis_irq_cluster0_cpu3_cpusequencer_sys_pwr_reg; /* offset : 0x103c */
	uint32_t reserved_24;
	union pmu_dis_irq_cluster1_cpu0_local_sys_pwr_reg
			dis_irq_cluster1_cpu0_local_sys_pwr_reg; /* offset : 0x1044 */
	uint32_t reserved_25;
	union pmu_dis_irq_cluster1_cpu0_cpusequencer_sys_pwr_reg
			dis_irq_cluster1_cpu0_cpusequencer_sys_pwr_reg; /* offset : 0x104c */
	uint32_t reserved_26;
	union pmu_dis_irq_cluster1_cpu1_local_sys_pwr_reg
			dis_irq_cluster1_cpu1_local_sys_pwr_reg; /* offset : 0x1054 */
	uint32_t reserved_27;
	union pmu_dis_irq_cluster1_cpu1_cpusequencer_sys_pwr_reg
			dis_irq_cluster1_cpu1_cpusequencer_sys_pwr_reg; /* offset : 0x105c */
	uint32_t reserved_28;
	union pmu_dis_irq_cluster1_cpu2_local_sys_pwr_reg
			dis_irq_cluster1_cpu2_local_sys_pwr_reg; /* offset : 0x1064 */
	uint32_t reserved_29;
	union pmu_dis_irq_cluster1_cpu2_cpusequencer_sys_pwr_reg
			dis_irq_cluster1_cpu2_cpusequencer_sys_pwr_reg; /* offset : 0x106c */
	uint32_t reserved_30;
	union pmu_dis_irq_cluster1_cpu3_local_sys_pwr_reg
			dis_irq_cluster1_cpu3_local_sys_pwr_reg; /* offset : 0x1074 */
	uint32_t reserved_31;
	union pmu_dis_irq_cluster1_cpu3_cpusequencer_sys_pwr_reg
			dis_irq_cluster1_cpu3_cpusequencer_sys_pwr_reg; /* offset : 0x107c */
	uint32_t reserved_32[80];
	union pmu_reset_cpuclkstop0_sys_pwr_reg reset_cpuclkstop0_sys_pwr_reg; /* offset : 0x11c0 */
	uint32_t reserved_33[15];
	union pmu_reset_cpuclkstop1_sys_pwr_reg reset_cpuclkstop1_sys_pwr_reg; /* offset : 0x1200 */
	uint32_t reserved_34[111];
	union pmu_clkstop_open_cmu_cp0_sys_pwr_reg clkstop_open_cmu_cp0_sys_pwr_reg; /* offset : 0x13c0 */
	union pmu_clkstop_open_cmu_cp1_sys_pwr_reg clkstop_open_cmu_cp1_sys_pwr_reg; /* offset : 0x13c4 */
	union pmu_clkstop_open_cmu_pcie_sys_pwr_reg clkstop_open_cmu_pcie_sys_pwr_reg; /* offset : 0x13c8 */
	union pmu_clkstop_open_cmu_dram_sys_pwr_reg clkstop_open_cmu_dram_sys_pwr_reg; /* offset : 0x13cc */
	union pmu_clkstop_open_cmu_dcl0_sys_pwr_reg clkstop_open_cmu_dcl0_sys_pwr_reg; /* offset : 0x13d0 */
	union pmu_clkstop_open_cmu_dcl1_sys_pwr_reg clkstop_open_cmu_dcl1_sys_pwr_reg; /* offset : 0x13d4 */
	union pmu_clkstop_open_cmu_rbch00_sys_pwr_reg
			clkstop_open_cmu_rbch00_sys_pwr_reg; /* offset : 0x13d8 */
	union pmu_clkstop_open_cmu_rbch01_sys_pwr_reg
			clkstop_open_cmu_rbch01_sys_pwr_reg; /* offset : 0x13dc */
	union pmu_clkstop_open_cmu_rbcv00_sys_pwr_reg
			clkstop_open_cmu_rbcv00_sys_pwr_reg; /* offset : 0x13e0 */
	union pmu_clkstop_open_cmu_rbcv01_sys_pwr_reg
			clkstop_open_cmu_rbcv01_sys_pwr_reg; /* offset : 0x13e4 */
	union pmu_clkstop_open_cmu_rbcv10_sys_pwr_reg
			clkstop_open_cmu_rbcv10_sys_pwr_reg; /* offset : 0x13e8 */
	union pmu_clkstop_open_cmu_rbcv11_sys_pwr_reg
			clkstop_open_cmu_rbcv11_sys_pwr_reg; /* offset : 0x13ec */
	union pmu_clkstop_open_cmu_rot_sys_pwr_reg clkstop_open_cmu_rot_sys_pwr_reg; /* offset : 0x13f0 */
	union pmu_clkstop_open_cmu_peri0_sys_pwr_reg clkstop_open_cmu_peri0_sys_pwr_reg; /* offset : 0x13f4 */
	union pmu_clkstop_open_cmu_peri1_sys_pwr_reg clkstop_open_cmu_peri1_sys_pwr_reg; /* offset : 0x13f8 */
	union pmu_clkstop_open_cmu_sbus_u_sys_pwr_reg
			clkstop_open_cmu_sbus_u_sys_pwr_reg; /* offset : 0x13fc */
	union pmu_clkstop_open_cmu_sbus_d_sys_pwr_reg
			clkstop_open_cmu_sbus_d_sys_pwr_reg; /* offset : 0x1400 */
	union pmu_clkstop_open_cmu_sbus_l_sys_pwr_reg
			clkstop_open_cmu_sbus_l_sys_pwr_reg; /* offset : 0x1404 */
	union pmu_clkstop_open_cmu_nbus_u_sys_pwr_reg
			clkstop_open_cmu_nbus_u_sys_pwr_reg; /* offset : 0x1408 */
	union pmu_clkstop_open_cmu_nbus_d_sys_pwr_reg
			clkstop_open_cmu_nbus_d_sys_pwr_reg; /* offset : 0x140c */
	union pmu_clkstop_open_cmu_nbus_l_sys_pwr_reg
			clkstop_open_cmu_nbus_l_sys_pwr_reg; /* offset : 0x1410 */
	union pmu_clkstop_open_cmu_wbus_u_sys_pwr_reg
			clkstop_open_cmu_wbus_u_sys_pwr_reg; /* offset : 0x1414 */
	union pmu_clkstop_open_cmu_wbus_d_sys_pwr_reg
			clkstop_open_cmu_wbus_d_sys_pwr_reg; /* offset : 0x1418 */
	union pmu_clkstop_open_cmu_ebus_u_sys_pwr_reg
			clkstop_open_cmu_ebus_u_sys_pwr_reg; /* offset : 0x141c */
	union pmu_clkstop_open_cmu_ebus_d_sys_pwr_reg
			clkstop_open_cmu_ebus_d_sys_pwr_reg; /* offset : 0x1420 */
	union pmu_clkstop_open_cmu_ebus_r_sys_pwr_reg
			clkstop_open_cmu_ebus_r_sys_pwr_reg; /* offset : 0x1424 */
	uint32_t reserved_35[38];
	union pmu_force_autoclkgate_cmu_cp0_sys_pwr_reg
			force_autoclkgate_cmu_cp0_sys_pwr_reg; /* offset : 0x14c0 */
	union pmu_force_autoclkgate_cmu_cp1_sys_pwr_reg
			force_autoclkgate_cmu_cp1_sys_pwr_reg; /* offset : 0x14c4 */
	union pmu_force_autoclkgate_cmu_pcie_sys_pwr_reg
			force_autoclkgate_cmu_pcie_sys_pwr_reg; /* offset : 0x14c8 */
	union pmu_force_autoclkgate_cmu_dram_sys_pwr_reg
			force_autoclkgate_cmu_dram_sys_pwr_reg; /* offset : 0x14cc */
	union pmu_force_autoclkgate_cmu_dcl0_sys_pwr_reg
			force_autoclkgate_cmu_dcl0_sys_pwr_reg; /* offset : 0x14d0 */
	union pmu_force_autoclkgate_cmu_dcl1_sys_pwr_reg
			force_autoclkgate_cmu_dcl1_sys_pwr_reg; /* offset : 0x14d4 */
	union pmu_force_autoclkgate_cmu_rbch00_sys_pwr_reg
			force_autoclkgate_cmu_rbch00_sys_pwr_reg; /* offset : 0x14d8 */
	union pmu_force_autoclkgate_cmu_rbch01_sys_pwr_reg
			force_autoclkgate_cmu_rbch01_sys_pwr_reg; /* offset : 0x14dc */
	union pmu_force_autoclkgate_cmu_rbcv00_sys_pwr_reg
			force_autoclkgate_cmu_rbcv00_sys_pwr_reg; /* offset : 0x14e0 */
	union pmu_force_autoclkgate_cmu_rbcv01_sys_pwr_reg
			force_autoclkgate_cmu_rbcv01_sys_pwr_reg; /* offset : 0x14e4 */
	union pmu_force_autoclkgate_cmu_rbcv10_sys_pwr_reg
			force_autoclkgate_cmu_rbcv10_sys_pwr_reg; /* offset : 0x14e8 */
	union pmu_force_autoclkgate_cmu_rbcv11_sys_pwr_reg
			force_autoclkgate_cmu_rbcv11_sys_pwr_reg; /* offset : 0x14ec */
	union pmu_force_autoclkgate_cmu_rot_sys_pwr_reg
			force_autoclkgate_cmu_rot_sys_pwr_reg; /* offset : 0x14f0 */
	union pmu_force_autoclkgate_cmu_peri0_sys_pwr_reg
			force_autoclkgate_cmu_peri0_sys_pwr_reg; /* offset : 0x14f4 */
	union pmu_force_autoclkgate_cmu_peri1_sys_pwr_reg
			force_autoclkgate_cmu_peri1_sys_pwr_reg; /* offset : 0x14f8 */
	union pmu_force_autoclkgate_cmu_sbus_u_sys_pwr_reg
			force_autoclkgate_cmu_sbus_u_sys_pwr_reg; /* offset : 0x14fc */
	union pmu_force_autoclkgate_cmu_sbus_d_sys_pwr_reg
			force_autoclkgate_cmu_sbus_d_sys_pwr_reg; /* offset : 0x1500 */
	union pmu_force_autoclkgate_cmu_sbus_l_sys_pwr_reg
			force_autoclkgate_cmu_sbus_l_sys_pwr_reg; /* offset : 0x1504 */
	union pmu_force_autoclkgate_cmu_nbus_u_sys_pwr_reg
			force_autoclkgate_cmu_nbus_u_sys_pwr_reg; /* offset : 0x1508 */
	union pmu_force_autoclkgate_cmu_nbus_d_sys_pwr_reg
			force_autoclkgate_cmu_nbus_d_sys_pwr_reg; /* offset : 0x150c */
	union pmu_force_autoclkgate_cmu_nbus_l_sys_pwr_reg
			force_autoclkgate_cmu_nbus_l_sys_pwr_reg; /* offset : 0x1510 */
	union pmu_force_autoclkgate_cmu_wbus_u_sys_pwr_reg
			force_autoclkgate_cmu_wbus_u_sys_pwr_reg; /* offset : 0x1514 */
	union pmu_force_autoclkgate_cmu_wbus_d_sys_pwr_reg
			force_autoclkgate_cmu_wbus_d_sys_pwr_reg; /* offset : 0x1518 */
	union pmu_force_autoclkgate_cmu_ebus_u_sys_pwr_reg
			force_autoclkgate_cmu_ebus_u_sys_pwr_reg; /* offset : 0x151c */
	union pmu_force_autoclkgate_cmu_ebus_d_sys_pwr_reg
			force_autoclkgate_cmu_ebus_d_sys_pwr_reg; /* offset : 0x1520 */
	union pmu_force_autoclkgate_cmu_ebus_r_sys_pwr_reg
			force_autoclkgate_cmu_ebus_r_sys_pwr_reg; /* offset : 0x1524 */
	uint32_t reserved_36[6];
	union pmu_clkstop_cmu_cp0_sys_pwr_reg clkstop_cmu_cp0_sys_pwr_reg; /* offset : 0x1540 */
	union pmu_clkstop_cmu_cp1_sys_pwr_reg clkstop_cmu_cp1_sys_pwr_reg; /* offset : 0x1544 */
	union pmu_clkstop_cmu_pcie_sys_pwr_reg clkstop_cmu_pcie_sys_pwr_reg; /* offset : 0x1548 */
	union pmu_clkstop_cmu_dram_sys_pwr_reg clkstop_cmu_dram_sys_pwr_reg; /* offset : 0x154c */
	union pmu_clkstop_cmu_dcl0_sys_pwr_reg clkstop_cmu_dcl0_sys_pwr_reg; /* offset : 0x1550 */
	union pmu_clkstop_cmu_dcl1_sys_pwr_reg clkstop_cmu_dcl1_sys_pwr_reg; /* offset : 0x1554 */
	union pmu_clkstop_cmu_rbch00_sys_pwr_reg clkstop_cmu_rbch00_sys_pwr_reg; /* offset : 0x1558 */
	union pmu_clkstop_cmu_rbch01_sys_pwr_reg clkstop_cmu_rbch01_sys_pwr_reg; /* offset : 0x155c */
	union pmu_clkstop_cmu_rbcv00_sys_pwr_reg clkstop_cmu_rbcv00_sys_pwr_reg; /* offset : 0x1560 */
	union pmu_clkstop_cmu_rbcv01_sys_pwr_reg clkstop_cmu_rbcv01_sys_pwr_reg; /* offset : 0x1564 */
	union pmu_clkstop_cmu_rbcv10_sys_pwr_reg clkstop_cmu_rbcv10_sys_pwr_reg; /* offset : 0x1568 */
	union pmu_clkstop_cmu_rbcv11_sys_pwr_reg clkstop_cmu_rbcv11_sys_pwr_reg; /* offset : 0x156c */
	union pmu_clkstop_cmu_rot_sys_pwr_reg clkstop_cmu_rot_sys_pwr_reg; /* offset : 0x1570 */
	union pmu_clkstop_cmu_peri0_sys_pwr_reg clkstop_cmu_peri0_sys_pwr_reg; /* offset : 0x1574 */
	union pmu_clkstop_cmu_peri1_sys_pwr_reg clkstop_cmu_peri1_sys_pwr_reg; /* offset : 0x1578 */
	union pmu_clkstop_cmu_sbus_u_sys_pwr_reg clkstop_cmu_sbus_u_sys_pwr_reg; /* offset : 0x157c */
	union pmu_clkstop_cmu_sbus_d_sys_pwr_reg clkstop_cmu_sbus_d_sys_pwr_reg; /* offset : 0x1580 */
	union pmu_clkstop_cmu_sbus_l_sys_pwr_reg clkstop_cmu_sbus_l_sys_pwr_reg; /* offset : 0x1584 */
	union pmu_clkstop_cmu_nbus_u_sys_pwr_reg clkstop_cmu_nbus_u_sys_pwr_reg; /* offset : 0x1588 */
	union pmu_clkstop_cmu_nbus_d_sys_pwr_reg clkstop_cmu_nbus_d_sys_pwr_reg; /* offset : 0x158c */
	union pmu_clkstop_cmu_nbus_l_sys_pwr_reg clkstop_cmu_nbus_l_sys_pwr_reg; /* offset : 0x1590 */
	union pmu_clkstop_cmu_wbus_u_sys_pwr_reg clkstop_cmu_wbus_u_sys_pwr_reg; /* offset : 0x1594 */
	union pmu_clkstop_cmu_wbus_d_sys_pwr_reg clkstop_cmu_wbus_d_sys_pwr_reg; /* offset : 0x1598 */
	union pmu_clkstop_cmu_ebus_u_sys_pwr_reg clkstop_cmu_ebus_u_sys_pwr_reg; /* offset : 0x159c */
	union pmu_clkstop_cmu_ebus_d_sys_pwr_reg clkstop_cmu_ebus_d_sys_pwr_reg; /* offset : 0x15a0 */
	union pmu_clkstop_cmu_ebus_r_sys_pwr_reg clkstop_cmu_ebus_r_sys_pwr_reg; /* offset : 0x15a4 */
	uint32_t reserved_37[6];
	union pmu_disable_pll_cmu_cp0_sys_pwr_reg disable_pll_cmu_cp0_sys_pwr_reg; /* offset : 0x15c0 */
	union pmu_disable_pll_cmu_cp1_sys_pwr_reg disable_pll_cmu_cp1_sys_pwr_reg; /* offset : 0x15c4 */
	union pmu_disable_pll_cmu_pcie_sys_pwr_reg disable_pll_cmu_pcie_sys_pwr_reg; /* offset : 0x15c8 */
	union pmu_disable_pll_cmu_dram_sys_pwr_reg disable_pll_cmu_dram_sys_pwr_reg; /* offset : 0x15cc */
	union pmu_disable_pll_cmu_dcl0_sys_pwr_reg disable_pll_cmu_dcl0_sys_pwr_reg; /* offset : 0x15d0 */
	union pmu_disable_pll_cmu_dcl1_sys_pwr_reg disable_pll_cmu_dcl1_sys_pwr_reg; /* offset : 0x15d4 */
	union pmu_disable_pll_cmu_rbch00_sys_pwr_reg disable_pll_cmu_rbch00_sys_pwr_reg; /* offset : 0x15d8 */
	union pmu_disable_pll_cmu_rbch01_sys_pwr_reg disable_pll_cmu_rbch01_sys_pwr_reg; /* offset : 0x15dc */
	union pmu_disable_pll_cmu_rbcv00_sys_pwr_reg disable_pll_cmu_rbcv00_sys_pwr_reg; /* offset : 0x15e0 */
	union pmu_disable_pll_cmu_rbcv01_sys_pwr_reg disable_pll_cmu_rbcv01_sys_pwr_reg; /* offset : 0x15e4 */
	union pmu_disable_pll_cmu_rbcv10_sys_pwr_reg disable_pll_cmu_rbcv10_sys_pwr_reg; /* offset : 0x15e8 */
	union pmu_disable_pll_cmu_rbcv11_sys_pwr_reg disable_pll_cmu_rbcv11_sys_pwr_reg; /* offset : 0x15ec */
	union pmu_disable_pll_cmu_rot_sys_pwr_reg disable_pll_cmu_rot_sys_pwr_reg; /* offset : 0x15f0 */
	union pmu_disable_pll_cmu_peri0_sys_pwr_reg disable_pll_cmu_peri0_sys_pwr_reg; /* offset : 0x15f4 */
	union pmu_disable_pll_cmu_peri1_sys_pwr_reg disable_pll_cmu_peri1_sys_pwr_reg; /* offset : 0x15f8 */
	union pmu_disable_pll_cmu_sbus_u_sys_pwr_reg disable_pll_cmu_sbus_u_sys_pwr_reg; /* offset : 0x15fc */
	union pmu_disable_pll_cmu_sbus_d_sys_pwr_reg disable_pll_cmu_sbus_d_sys_pwr_reg; /* offset : 0x1600 */
	union pmu_disable_pll_cmu_sbus_l_sys_pwr_reg disable_pll_cmu_sbus_l_sys_pwr_reg; /* offset : 0x1604 */
	union pmu_disable_pll_cmu_nbus_u_sys_pwr_reg disable_pll_cmu_nbus_u_sys_pwr_reg; /* offset : 0x1608 */
	union pmu_disable_pll_cmu_nbus_d_sys_pwr_reg disable_pll_cmu_nbus_d_sys_pwr_reg; /* offset : 0x160c */
	union pmu_disable_pll_cmu_nbus_l_sys_pwr_reg disable_pll_cmu_nbus_l_sys_pwr_reg; /* offset : 0x1610 */
	union pmu_disable_pll_cmu_wbus_u_sys_pwr_reg disable_pll_cmu_wbus_u_sys_pwr_reg; /* offset : 0x1614 */
	union pmu_disable_pll_cmu_wbus_d_sys_pwr_reg disable_pll_cmu_wbus_d_sys_pwr_reg; /* offset : 0x1618 */
	union pmu_disable_pll_cmu_ebus_u_sys_pwr_reg disable_pll_cmu_ebus_u_sys_pwr_reg; /* offset : 0x161c */
	union pmu_disable_pll_cmu_ebus_d_sys_pwr_reg disable_pll_cmu_ebus_d_sys_pwr_reg; /* offset : 0x1620 */
	union pmu_disable_pll_cmu_ebus_r_sys_pwr_reg disable_pll_cmu_ebus_r_sys_pwr_reg; /* offset : 0x1624 */
	uint32_t reserved_38[6];
	union pmu_reset_logic_cp0_sys_pwr_reg reset_logic_cp0_sys_pwr_reg; /* offset : 0x1640 */
	union pmu_reset_logic_cp1_sys_pwr_reg reset_logic_cp1_sys_pwr_reg; /* offset : 0x1644 */
	union pmu_reset_logic_pcie_sys_pwr_reg reset_logic_pcie_sys_pwr_reg; /* offset : 0x1648 */
	union pmu_reset_logic_dram_sys_pwr_reg reset_logic_dram_sys_pwr_reg; /* offset : 0x164c */
	union pmu_reset_logic_dcl0_sys_pwr_reg reset_logic_dcl0_sys_pwr_reg; /* offset : 0x1650 */
	union pmu_reset_logic_dcl1_sys_pwr_reg reset_logic_dcl1_sys_pwr_reg; /* offset : 0x1654 */
	union pmu_reset_logic_rbch00_sys_pwr_reg reset_logic_rbch00_sys_pwr_reg; /* offset : 0x1658 */
	union pmu_reset_logic_rbch01_sys_pwr_reg reset_logic_rbch01_sys_pwr_reg; /* offset : 0x165c */
	union pmu_reset_logic_rbcv00_sys_pwr_reg reset_logic_rbcv00_sys_pwr_reg; /* offset : 0x1660 */
	union pmu_reset_logic_rbcv01_sys_pwr_reg reset_logic_rbcv01_sys_pwr_reg; /* offset : 0x1664 */
	union pmu_reset_logic_rbcv10_sys_pwr_reg reset_logic_rbcv10_sys_pwr_reg; /* offset : 0x1668 */
	union pmu_reset_logic_rbcv11_sys_pwr_reg reset_logic_rbcv11_sys_pwr_reg; /* offset : 0x166c */
	union pmu_reset_logic_rot_sys_pwr_reg reset_logic_rot_sys_pwr_reg; /* offset : 0x1670 */
	union pmu_reset_logic_peri0_sys_pwr_reg reset_logic_peri0_sys_pwr_reg; /* offset : 0x1674 */
	union pmu_reset_logic_peri1_sys_pwr_reg reset_logic_peri1_sys_pwr_reg; /* offset : 0x1678 */
	union pmu_reset_logic_sbus_u_sys_pwr_reg reset_logic_sbus_u_sys_pwr_reg; /* offset : 0x167c */
	union pmu_reset_logic_sbus_d_sys_pwr_reg reset_logic_sbus_d_sys_pwr_reg; /* offset : 0x1680 */
	union pmu_reset_logic_sbus_l_sys_pwr_reg reset_logic_sbus_l_sys_pwr_reg; /* offset : 0x1684 */
	union pmu_reset_logic_nbus_u_sys_pwr_reg reset_logic_nbus_u_sys_pwr_reg; /* offset : 0x1688 */
	union pmu_reset_logic_nbus_d_sys_pwr_reg reset_logic_nbus_d_sys_pwr_reg; /* offset : 0x168c */
	union pmu_reset_logic_nbus_l_sys_pwr_reg reset_logic_nbus_l_sys_pwr_reg; /* offset : 0x1690 */
	union pmu_reset_logic_wbus_u_sys_pwr_reg reset_logic_wbus_u_sys_pwr_reg; /* offset : 0x1694 */
	union pmu_reset_logic_wbus_d_sys_pwr_reg reset_logic_wbus_d_sys_pwr_reg; /* offset : 0x1698 */
	union pmu_reset_logic_ebus_u_sys_pwr_reg reset_logic_ebus_u_sys_pwr_reg; /* offset : 0x169c */
	union pmu_reset_logic_ebus_d_sys_pwr_reg reset_logic_ebus_d_sys_pwr_reg; /* offset : 0x16a0 */
	union pmu_reset_logic_ebus_r_sys_pwr_reg reset_logic_ebus_r_sys_pwr_reg; /* offset : 0x16a4 */
	uint32_t reserved_39[6];
	union pmu_reset_cmu_cp0_sys_pwr_reg reset_cmu_cp0_sys_pwr_reg; /* offset : 0x16c0 */
	union pmu_reset_cmu_cp1_sys_pwr_reg reset_cmu_cp1_sys_pwr_reg; /* offset : 0x16c4 */
	union pmu_reset_cmu_pcie_sys_pwr_reg reset_cmu_pcie_sys_pwr_reg; /* offset : 0x16c8 */
	union pmu_reset_cmu_dram_sys_pwr_reg reset_cmu_dram_sys_pwr_reg; /* offset : 0x16cc */
	union pmu_reset_cmu_dcl0_sys_pwr_reg reset_cmu_dcl0_sys_pwr_reg; /* offset : 0x16d0 */
	union pmu_reset_cmu_dcl1_sys_pwr_reg reset_cmu_dcl1_sys_pwr_reg; /* offset : 0x16d4 */
	union pmu_reset_cmu_rbch00_sys_pwr_reg reset_cmu_rbch00_sys_pwr_reg; /* offset : 0x16d8 */
	union pmu_reset_cmu_rbch01_sys_pwr_reg reset_cmu_rbch01_sys_pwr_reg; /* offset : 0x16dc */
	union pmu_reset_cmu_rbcv00_sys_pwr_reg reset_cmu_rbcv00_sys_pwr_reg; /* offset : 0x16e0 */
	union pmu_reset_cmu_rbcv01_sys_pwr_reg reset_cmu_rbcv01_sys_pwr_reg; /* offset : 0x16e4 */
	union pmu_reset_cmu_rbcv10_sys_pwr_reg reset_cmu_rbcv10_sys_pwr_reg; /* offset : 0x16e8 */
	union pmu_reset_cmu_rbcv11_sys_pwr_reg reset_cmu_rbcv11_sys_pwr_reg; /* offset : 0x16ec */
	union pmu_reset_cmu_rot_sys_pwr_reg reset_cmu_rot_sys_pwr_reg; /* offset : 0x16f0 */
	union pmu_reset_cmu_peri0_sys_pwr_reg reset_cmu_peri0_sys_pwr_reg; /* offset : 0x16f4 */
	union pmu_reset_cmu_peri1_sys_pwr_reg reset_cmu_peri1_sys_pwr_reg; /* offset : 0x16f8 */
	union pmu_reset_cmu_sbus_u_sys_pwr_reg reset_cmu_sbus_u_sys_pwr_reg; /* offset : 0x16fc */
	union pmu_reset_cmu_sbus_d_sys_pwr_reg reset_cmu_sbus_d_sys_pwr_reg; /* offset : 0x1700 */
	union pmu_reset_cmu_sbus_l_sys_pwr_reg reset_cmu_sbus_l_sys_pwr_reg; /* offset : 0x1704 */
	union pmu_reset_cmu_nbus_u_sys_pwr_reg reset_cmu_nbus_u_sys_pwr_reg; /* offset : 0x1708 */
	union pmu_reset_cmu_nbus_d_sys_pwr_reg reset_cmu_nbus_d_sys_pwr_reg; /* offset : 0x170c */
	union pmu_reset_cmu_nbus_l_sys_pwr_reg reset_cmu_nbus_l_sys_pwr_reg; /* offset : 0x1710 */
	union pmu_reset_cmu_wbus_u_sys_pwr_reg reset_cmu_wbus_u_sys_pwr_reg; /* offset : 0x1714 */
	union pmu_reset_cmu_wbus_d_sys_pwr_reg reset_cmu_wbus_d_sys_pwr_reg; /* offset : 0x1718 */
	union pmu_reset_cmu_ebus_u_sys_pwr_reg reset_cmu_ebus_u_sys_pwr_reg; /* offset : 0x171c */
	union pmu_reset_cmu_ebus_d_sys_pwr_reg reset_cmu_ebus_d_sys_pwr_reg; /* offset : 0x1720 */
	union pmu_reset_cmu_ebus_r_sys_pwr_reg reset_cmu_ebus_r_sys_pwr_reg; /* offset : 0x1724 */
	uint32_t reserved_40[6];
	union pmu_lpi_residual_cmu_cp0_sys_pwr_reg lpi_residual_cmu_cp0_sys_pwr_reg; /* offset : 0x1740 */
	union pmu_lpi_residual_cmu_cp1_sys_pwr_reg lpi_residual_cmu_cp1_sys_pwr_reg; /* offset : 0x1744 */
	union pmu_lpi_residual_cmu_pcie_sys_pwr_reg lpi_residual_cmu_pcie_sys_pwr_reg; /* offset : 0x1748 */
	union pmu_lpi_residual_cmu_dram_sys_pwr_reg lpi_residual_cmu_dram_sys_pwr_reg; /* offset : 0x174c */
	union pmu_lpi_residual_cmu_dcl0_sys_pwr_reg lpi_residual_cmu_dcl0_sys_pwr_reg; /* offset : 0x1750 */
	union pmu_lpi_residual_cmu_dcl1_sys_pwr_reg lpi_residual_cmu_dcl1_sys_pwr_reg; /* offset : 0x1754 */
	union pmu_lpi_residual_cmu_rbch00_sys_pwr_reg
			lpi_residual_cmu_rbch00_sys_pwr_reg; /* offset : 0x1758 */
	union pmu_lpi_residual_cmu_rbch01_sys_pwr_reg
			lpi_residual_cmu_rbch01_sys_pwr_reg; /* offset : 0x175c */
	union pmu_lpi_residual_cmu_rbcv00_sys_pwr_reg
			lpi_residual_cmu_rbcv00_sys_pwr_reg; /* offset : 0x1760 */
	union pmu_lpi_residual_cmu_rbcv01_sys_pwr_reg
			lpi_residual_cmu_rbcv01_sys_pwr_reg; /* offset : 0x1764 */
	union pmu_lpi_residual_cmu_rbcv10_sys_pwr_reg
			lpi_residual_cmu_rbcv10_sys_pwr_reg; /* offset : 0x1768 */
	union pmu_lpi_residual_cmu_rbcv11_sys_pwr_reg
			lpi_residual_cmu_rbcv11_sys_pwr_reg; /* offset : 0x176c */
	union pmu_lpi_residual_cmu_rot_sys_pwr_reg lpi_residual_cmu_rot_sys_pwr_reg; /* offset : 0x1770 */
	union pmu_lpi_residual_cmu_peri0_sys_pwr_reg lpi_residual_cmu_peri0_sys_pwr_reg; /* offset : 0x1774 */
	union pmu_lpi_residual_cmu_peri1_sys_pwr_reg lpi_residual_cmu_peri1_sys_pwr_reg; /* offset : 0x1778 */
	union pmu_lpi_residual_cmu_sbus_u_sys_pwr_reg
			lpi_residual_cmu_sbus_u_sys_pwr_reg; /* offset : 0x177c */
	union pmu_lpi_residual_cmu_sbus_d_sys_pwr_reg
			lpi_residual_cmu_sbus_d_sys_pwr_reg; /* offset : 0x1780 */
	union pmu_lpi_residual_cmu_sbus_l_sys_pwr_reg
			lpi_residual_cmu_sbus_l_sys_pwr_reg; /* offset : 0x1784 */
	union pmu_lpi_residual_cmu_nbus_u_sys_pwr_reg
			lpi_residual_cmu_nbus_u_sys_pwr_reg; /* offset : 0x1788 */
	union pmu_lpi_residual_cmu_nbus_d_sys_pwr_reg
			lpi_residual_cmu_nbus_d_sys_pwr_reg; /* offset : 0x178c */
	union pmu_lpi_residual_cmu_nbus_l_sys_pwr_reg
			lpi_residual_cmu_nbus_l_sys_pwr_reg; /* offset : 0x1790 */
	union pmu_lpi_residual_cmu_wbus_u_sys_pwr_reg
			lpi_residual_cmu_wbus_u_sys_pwr_reg; /* offset : 0x1794 */
	union pmu_lpi_residual_cmu_wbus_d_sys_pwr_reg
			lpi_residual_cmu_wbus_d_sys_pwr_reg; /* offset : 0x1798 */
	union pmu_lpi_residual_cmu_ebus_u_sys_pwr_reg
			lpi_residual_cmu_ebus_u_sys_pwr_reg; /* offset : 0x179c */
	union pmu_lpi_residual_cmu_ebus_d_sys_pwr_reg
			lpi_residual_cmu_ebus_d_sys_pwr_reg; /* offset : 0x17a0 */
	union pmu_lpi_residual_cmu_ebus_r_sys_pwr_reg
			lpi_residual_cmu_ebus_r_sys_pwr_reg; /* offset : 0x17a4 */
	uint32_t reserved_41[6];
	union pmu_lpi_bus_cmu_cp0_sys_pwr_reg lpi_bus_cmu_cp0_sys_pwr_reg; /* offset : 0x17c0 */
	union pmu_lpi_bus_cmu_cp1_sys_pwr_reg lpi_bus_cmu_cp1_sys_pwr_reg; /* offset : 0x17c4 */
	union pmu_lpi_bus_cmu_pcie_sys_pwr_reg lpi_bus_cmu_pcie_sys_pwr_reg; /* offset : 0x17c8 */
	union pmu_lpi_bus_cmu_dram_sys_pwr_reg lpi_bus_cmu_dram_sys_pwr_reg; /* offset : 0x17cc */
	union pmu_lpi_bus_cmu_dcl0_sys_pwr_reg lpi_bus_cmu_dcl0_sys_pwr_reg; /* offset : 0x17d0 */
	union pmu_lpi_bus_cmu_dcl1_sys_pwr_reg lpi_bus_cmu_dcl1_sys_pwr_reg; /* offset : 0x17d4 */
	union pmu_lpi_bus_cmu_rbch00_sys_pwr_reg lpi_bus_cmu_rbch00_sys_pwr_reg; /* offset : 0x17d8 */
	union pmu_lpi_bus_cmu_rbch01_sys_pwr_reg lpi_bus_cmu_rbch01_sys_pwr_reg; /* offset : 0x17dc */
	union pmu_lpi_bus_cmu_rbcv00_sys_pwr_reg lpi_bus_cmu_rbcv00_sys_pwr_reg; /* offset : 0x17e0 */
	union pmu_lpi_bus_cmu_rbcv01_sys_pwr_reg lpi_bus_cmu_rbcv01_sys_pwr_reg; /* offset : 0x17e4 */
	union pmu_lpi_bus_cmu_rbcv10_sys_pwr_reg lpi_bus_cmu_rbcv10_sys_pwr_reg; /* offset : 0x17e8 */
	union pmu_lpi_bus_cmu_rbcv11_sys_pwr_reg lpi_bus_cmu_rbcv11_sys_pwr_reg; /* offset : 0x17ec */
	union pmu_lpi_bus_cmu_rot_sys_pwr_reg lpi_bus_cmu_rot_sys_pwr_reg; /* offset : 0x17f0 */
	union pmu_lpi_bus_cmu_peri0_sys_pwr_reg lpi_bus_cmu_peri0_sys_pwr_reg; /* offset : 0x17f4 */
	union pmu_lpi_bus_cmu_peri1_sys_pwr_reg lpi_bus_cmu_peri1_sys_pwr_reg; /* offset : 0x17f8 */
	union pmu_lpi_bus_cmu_sbus_u_sys_pwr_reg lpi_bus_cmu_sbus_u_sys_pwr_reg; /* offset : 0x17fc */
	union pmu_lpi_bus_cmu_sbus_d_sys_pwr_reg lpi_bus_cmu_sbus_d_sys_pwr_reg; /* offset : 0x1800 */
	union pmu_lpi_bus_cmu_sbus_l_sys_pwr_reg lpi_bus_cmu_sbus_l_sys_pwr_reg; /* offset : 0x1804 */
	union pmu_lpi_bus_cmu_nbus_u_sys_pwr_reg lpi_bus_cmu_nbus_u_sys_pwr_reg; /* offset : 0x1808 */
	union pmu_lpi_bus_cmu_nbus_d_sys_pwr_reg lpi_bus_cmu_nbus_d_sys_pwr_reg; /* offset : 0x180c */
	union pmu_lpi_bus_cmu_nbus_l_sys_pwr_reg lpi_bus_cmu_nbus_l_sys_pwr_reg; /* offset : 0x1810 */
	union pmu_lpi_bus_cmu_wbus_u_sys_pwr_reg lpi_bus_cmu_wbus_u_sys_pwr_reg; /* offset : 0x1814 */
	union pmu_lpi_bus_cmu_wbus_d_sys_pwr_reg lpi_bus_cmu_wbus_d_sys_pwr_reg; /* offset : 0x1818 */
	union pmu_lpi_bus_cmu_ebus_u_sys_pwr_reg lpi_bus_cmu_ebus_u_sys_pwr_reg; /* offset : 0x181c */
	union pmu_lpi_bus_cmu_ebus_d_sys_pwr_reg lpi_bus_cmu_ebus_d_sys_pwr_reg; /* offset : 0x1820 */
	union pmu_lpi_bus_cmu_ebus_r_sys_pwr_reg lpi_bus_cmu_ebus_r_sys_pwr_reg; /* offset : 0x1824 */
	uint32_t reserved_42[6];
	union pmu_lpi_busmaster_cmu_cp0_sys_pwr_reg lpi_busmaster_cmu_cp0_sys_pwr_reg; /* offset : 0x1840 */
	union pmu_lpi_busmaster_cmu_cp1_sys_pwr_reg lpi_busmaster_cmu_cp1_sys_pwr_reg; /* offset : 0x1844 */
	union pmu_lpi_busmaster_cmu_pcie_sys_pwr_reg lpi_busmaster_cmu_pcie_sys_pwr_reg; /* offset : 0x1848 */
	union pmu_lpi_busmaster_cmu_dram_sys_pwr_reg lpi_busmaster_cmu_dram_sys_pwr_reg; /* offset : 0x184c */
	union pmu_lpi_busmaster_cmu_dcl0_sys_pwr_reg lpi_busmaster_cmu_dcl0_sys_pwr_reg; /* offset : 0x1850 */
	union pmu_lpi_busmaster_cmu_dcl1_sys_pwr_reg lpi_busmaster_cmu_dcl1_sys_pwr_reg; /* offset : 0x1854 */
	union pmu_lpi_busmaster_cmu_rbch00_sys_pwr_reg
			lpi_busmaster_cmu_rbch00_sys_pwr_reg; /* offset : 0x1858 */
	union pmu_lpi_busmaster_cmu_rbch01_sys_pwr_reg
			lpi_busmaster_cmu_rbch01_sys_pwr_reg; /* offset : 0x185c */
	union pmu_lpi_busmaster_cmu_rbcv00_sys_pwr_reg
			lpi_busmaster_cmu_rbcv00_sys_pwr_reg; /* offset : 0x1860 */
	union pmu_lpi_busmaster_cmu_rbcv01_sys_pwr_reg
			lpi_busmaster_cmu_rbcv01_sys_pwr_reg; /* offset : 0x1864 */
	union pmu_lpi_busmaster_cmu_rbcv10_sys_pwr_reg
			lpi_busmaster_cmu_rbcv10_sys_pwr_reg; /* offset : 0x1868 */
	union pmu_lpi_busmaster_cmu_rbcv11_sys_pwr_reg
			lpi_busmaster_cmu_rbcv11_sys_pwr_reg; /* offset : 0x186c */
	union pmu_lpi_busmaster_cmu_rot_sys_pwr_reg lpi_busmaster_cmu_rot_sys_pwr_reg; /* offset : 0x1870 */
	union pmu_lpi_busmaster_cmu_peri0_sys_pwr_reg
			lpi_busmaster_cmu_peri0_sys_pwr_reg; /* offset : 0x1874 */
	union pmu_lpi_busmaster_cmu_peri1_sys_pwr_reg
			lpi_busmaster_cmu_peri1_sys_pwr_reg; /* offset : 0x1878 */
	union pmu_lpi_busmaster_cmu_sbus_u_sys_pwr_reg
			lpi_busmaster_cmu_sbus_u_sys_pwr_reg; /* offset : 0x187c */
	union pmu_lpi_busmaster_cmu_sbus_d_sys_pwr_reg
			lpi_busmaster_cmu_sbus_d_sys_pwr_reg; /* offset : 0x1880 */
	union pmu_lpi_busmaster_cmu_sbus_l_sys_pwr_reg
			lpi_busmaster_cmu_sbus_l_sys_pwr_reg; /* offset : 0x1884 */
	union pmu_lpi_busmaster_cmu_nbus_u_sys_pwr_reg
			lpi_busmaster_cmu_nbus_u_sys_pwr_reg; /* offset : 0x1888 */
	union pmu_lpi_busmaster_cmu_nbus_d_sys_pwr_reg
			lpi_busmaster_cmu_nbus_d_sys_pwr_reg; /* offset : 0x188c */
	union pmu_lpi_busmaster_cmu_nbus_l_sys_pwr_reg
			lpi_busmaster_cmu_nbus_l_sys_pwr_reg; /* offset : 0x1890 */
	union pmu_lpi_busmaster_cmu_wbus_u_sys_pwr_reg
			lpi_busmaster_cmu_wbus_u_sys_pwr_reg; /* offset : 0x1894 */
	union pmu_lpi_busmaster_cmu_wbus_d_sys_pwr_reg
			lpi_busmaster_cmu_wbus_d_sys_pwr_reg; /* offset : 0x1898 */
	union pmu_lpi_busmaster_cmu_ebus_u_sys_pwr_reg
			lpi_busmaster_cmu_ebus_u_sys_pwr_reg; /* offset : 0x189c */
	union pmu_lpi_busmaster_cmu_ebus_d_sys_pwr_reg
			lpi_busmaster_cmu_ebus_d_sys_pwr_reg; /* offset : 0x18a0 */
	union pmu_lpi_busmaster_cmu_ebus_r_sys_pwr_reg
			lpi_busmaster_cmu_ebus_r_sys_pwr_reg; /* offset : 0x18a4 */
	uint32_t reserved_43[9];
	union pmu_lpi_hbm_cmu_dram_sys_pwr_reg lpi_hbm_cmu_dram_sys_pwr_reg; /* offset : 0x18cc */
	uint32_t reserved_44[62];
	union pmu_cm7_cpu_pcie_sys_pwr_reg cm7_cpu_pcie_sys_pwr_reg; /* offset : 0x19c8 */
	uint32_t reserved_45[397];
	union pmu_cluster0_cpu0_configuration cluster0_cpu0_configuration; /* offset : 0x2000 */
	union pmu_cluster0_cpu0_status cluster0_cpu0_status; /* offset : 0x2004 */
	union pmu_cluster0_cpu0_option cluster0_cpu0_option; /* offset : 0x2008 */
	union pmu_cluster0_cpu0_reset cluster0_cpu0_reset; /* offset : 0x200c */
	union pmu_cluster0_cpu0_duration0 cluster0_cpu0_duration0; /* offset : 0x2010 */
	union pmu_cluster0_cpu0_duration1 cluster0_cpu0_duration1; /* offset : 0x2014 */
	union pmu_cluster0_cpu0_duration2 cluster0_cpu0_duration2; /* offset : 0x2018 */
	union pmu_cluster0_cpu0_duration3 cluster0_cpu0_duration3; /* offset : 0x201c */
	union pmu_dis_irq_cluster0_cpu0_local_configuration
			dis_irq_cluster0_cpu0_local_configuration; /* offset : 0x2020 */
	union pmu_dis_irq_cluster0_cpu0_local_status dis_irq_cluster0_cpu0_local_status; /* offset : 0x2024 */
	union pmu_dis_irq_cluster0_cpu0_local_option dis_irq_cluster0_cpu0_local_option; /* offset : 0x2028 */
	uint32_t reserved_46;
	union pmu_dis_irq_cluster0_cpu0_local_duration0
			dis_irq_cluster0_cpu0_local_duration0; /* offset : 0x2030 */
	union pmu_dis_irq_cluster0_cpu0_local_duration1
			dis_irq_cluster0_cpu0_local_duration1; /* offset : 0x2034 */
	union pmu_dis_irq_cluster0_cpu0_local_duration2
			dis_irq_cluster0_cpu0_local_duration2; /* offset : 0x2038 */
	union pmu_dis_irq_cluster0_cpu0_local_duration3
			dis_irq_cluster0_cpu0_local_duration3; /* offset : 0x203c */
	uint32_t reserved_47[8];
	union pmu_dis_irq_cluster0_cpu0_cpusequencer_configuration
			dis_irq_cluster0_cpu0_cpusequencer_configuration; /* offset : 0x2060 */
	union pmu_dis_irq_cluster0_cpu0_cpusequencer_status
			dis_irq_cluster0_cpu0_cpusequencer_status; /* offset : 0x2064 */
	union pmu_dis_irq_cluster0_cpu0_cpusequencer_option
			dis_irq_cluster0_cpu0_cpusequencer_option; /* offset : 0x2068 */
	uint32_t reserved_48;
	union pmu_dis_irq_cluster0_cpu0_cpusequencer_duration0
			dis_irq_cluster0_cpu0_cpusequencer_duration0; /* offset : 0x2070 */
	union pmu_dis_irq_cluster0_cpu0_cpusequencer_duration1
			dis_irq_cluster0_cpu0_cpusequencer_duration1; /* offset : 0x2074 */
	union pmu_dis_irq_cluster0_cpu0_cpusequencer_duration2
			dis_irq_cluster0_cpu0_cpusequencer_duration2; /* offset : 0x2078 */
	union pmu_dis_irq_cluster0_cpu0_cpusequencer_duration3
			dis_irq_cluster0_cpu0_cpusequencer_duration3; /* offset : 0x207c */
	union pmu_cluster0_cpu1_configuration cluster0_cpu1_configuration; /* offset : 0x2080 */
	union pmu_cluster0_cpu1_status cluster0_cpu1_status; /* offset : 0x2084 */
	union pmu_cluster0_cpu1_option cluster0_cpu1_option; /* offset : 0x2088 */
	union pmu_cluster0_cpu1_reset cluster0_cpu1_reset; /* offset : 0x208c */
	union pmu_cluster0_cpu1_duration0 cluster0_cpu1_duration0; /* offset : 0x2090 */
	union pmu_cluster0_cpu1_duration1 cluster0_cpu1_duration1; /* offset : 0x2094 */
	union pmu_cluster0_cpu1_duration2 cluster0_cpu1_duration2; /* offset : 0x2098 */
	union pmu_cluster0_cpu1_duration3 cluster0_cpu1_duration3; /* offset : 0x209c */
	union pmu_dis_irq_cluster0_cpu1_local_configuration
			dis_irq_cluster0_cpu1_local_configuration; /* offset : 0x20a0 */
	union pmu_dis_irq_cluster0_cpu1_local_status dis_irq_cluster0_cpu1_local_status; /* offset : 0x20a4 */
	union pmu_dis_irq_cluster0_cpu1_local_option dis_irq_cluster0_cpu1_local_option; /* offset : 0x20a8 */
	uint32_t reserved_49;
	union pmu_dis_irq_cluster0_cpu1_local_duration0
			dis_irq_cluster0_cpu1_local_duration0; /* offset : 0x20b0 */
	union pmu_dis_irq_cluster0_cpu1_local_duration1
			dis_irq_cluster0_cpu1_local_duration1; /* offset : 0x20b4 */
	union pmu_dis_irq_cluster0_cpu1_local_duration2
			dis_irq_cluster0_cpu1_local_duration2; /* offset : 0x20b8 */
	union pmu_dis_irq_cluster0_cpu1_local_duration3
			dis_irq_cluster0_cpu1_local_duration3; /* offset : 0x20bc */
	uint32_t reserved_50[8];
	union pmu_dis_irq_cluster0_cpu1_cpusequencer_configuration
			dis_irq_cluster0_cpu1_cpusequencer_configuration; /* offset : 0x20e0 */
	union pmu_dis_irq_cluster0_cpu1_cpusequencer_status
			dis_irq_cluster0_cpu1_cpusequencer_status; /* offset : 0x20e4 */
	union pmu_dis_irq_cluster0_cpu1_cpusequencer_option
			dis_irq_cluster0_cpu1_cpusequencer_option; /* offset : 0x20e8 */
	uint32_t reserved_51;
	union pmu_dis_irq_cluster0_cpu1_cpusequencer_duration0
			dis_irq_cluster0_cpu1_cpusequencer_duration0; /* offset : 0x20f0 */
	union pmu_dis_irq_cluster0_cpu1_cpusequencer_duration1
			dis_irq_cluster0_cpu1_cpusequencer_duration1; /* offset : 0x20f4 */
	union pmu_dis_irq_cluster0_cpu1_cpusequencer_duration2
			dis_irq_cluster0_cpu1_cpusequencer_duration2; /* offset : 0x20f8 */
	union pmu_dis_irq_cluster0_cpu1_cpusequencer_duration3
			dis_irq_cluster0_cpu1_cpusequencer_duration3; /* offset : 0x20fc */
	union pmu_cluster0_cpu2_configuration cluster0_cpu2_configuration; /* offset : 0x2100 */
	union pmu_cluster0_cpu2_status cluster0_cpu2_status; /* offset : 0x2104 */
	union pmu_cluster0_cpu2_option cluster0_cpu2_option; /* offset : 0x2108 */
	union pmu_cluster0_cpu2_reset cluster0_cpu2_reset; /* offset : 0x210c */
	union pmu_cluster0_cpu2_duration0 cluster0_cpu2_duration0; /* offset : 0x2110 */
	union pmu_cluster0_cpu2_duration1 cluster0_cpu2_duration1; /* offset : 0x2114 */
	union pmu_cluster0_cpu2_duration2 cluster0_cpu2_duration2; /* offset : 0x2118 */
	union pmu_cluster0_cpu2_duration3 cluster0_cpu2_duration3; /* offset : 0x211c */
	union pmu_dis_irq_cluster0_cpu2_local_configuration
			dis_irq_cluster0_cpu2_local_configuration; /* offset : 0x2120 */
	union pmu_dis_irq_cluster0_cpu2_local_status dis_irq_cluster0_cpu2_local_status; /* offset : 0x2124 */
	union pmu_dis_irq_cluster0_cpu2_local_option dis_irq_cluster0_cpu2_local_option; /* offset : 0x2128 */
	uint32_t reserved_52;
	union pmu_dis_irq_cluster0_cpu2_local_duration0
			dis_irq_cluster0_cpu2_local_duration0; /* offset : 0x2130 */
	union pmu_dis_irq_cluster0_cpu2_local_duration1
			dis_irq_cluster0_cpu2_local_duration1; /* offset : 0x2134 */
	union pmu_dis_irq_cluster0_cpu2_local_duration2
			dis_irq_cluster0_cpu2_local_duration2; /* offset : 0x2138 */
	union pmu_dis_irq_cluster0_cpu2_local_duration3
			dis_irq_cluster0_cpu2_local_duration3; /* offset : 0x213c */
	uint32_t reserved_53[8];
	union pmu_dis_irq_cluster0_cpu2_cpusequencer_configuration
			dis_irq_cluster0_cpu2_cpusequencer_configuration; /* offset : 0x2160 */
	union pmu_dis_irq_cluster0_cpu2_cpusequencer_status
			dis_irq_cluster0_cpu2_cpusequencer_status; /* offset : 0x2164 */
	union pmu_dis_irq_cluster0_cpu2_cpusequencer_option
			dis_irq_cluster0_cpu2_cpusequencer_option; /* offset : 0x2168 */
	uint32_t reserved_54;
	union pmu_dis_irq_cluster0_cpu2_cpusequencer_duration0
			dis_irq_cluster0_cpu2_cpusequencer_duration0; /* offset : 0x2170 */
	union pmu_dis_irq_cluster0_cpu2_cpusequencer_duration1
			dis_irq_cluster0_cpu2_cpusequencer_duration1; /* offset : 0x2174 */
	union pmu_dis_irq_cluster0_cpu2_cpusequencer_duration2
			dis_irq_cluster0_cpu2_cpusequencer_duration2; /* offset : 0x2178 */
	union pmu_dis_irq_cluster0_cpu2_cpusequencer_duration3
			dis_irq_cluster0_cpu2_cpusequencer_duration3; /* offset : 0x217c */
	union pmu_cluster0_cpu3_configuration cluster0_cpu3_configuration; /* offset : 0x2180 */
	union pmu_cluster0_cpu3_status cluster0_cpu3_status; /* offset : 0x2184 */
	union pmu_cluster0_cpu3_option cluster0_cpu3_option; /* offset : 0x2188 */
	union pmu_cluster0_cpu3_reset cluster0_cpu3_reset; /* offset : 0x218c */
	union pmu_cluster0_cpu3_duration0 cluster0_cpu3_duration0; /* offset : 0x2190 */
	union pmu_cluster0_cpu3_duration1 cluster0_cpu3_duration1; /* offset : 0x2194 */
	union pmu_cluster0_cpu3_duration2 cluster0_cpu3_duration2; /* offset : 0x2198 */
	union pmu_cluster0_cpu3_duration3 cluster0_cpu3_duration3; /* offset : 0x219c */
	union pmu_dis_irq_cluster0_cpu3_local_configuration
			dis_irq_cluster0_cpu3_local_configuration; /* offset : 0x21a0 */
	union pmu_dis_irq_cluster0_cpu3_local_status dis_irq_cluster0_cpu3_local_status; /* offset : 0x21a4 */
	union pmu_dis_irq_cluster0_cpu3_local_option dis_irq_cluster0_cpu3_local_option; /* offset : 0x21a8 */
	uint32_t reserved_55;
	union pmu_dis_irq_cluster0_cpu3_local_duration0
			dis_irq_cluster0_cpu3_local_duration0; /* offset : 0x21b0 */
	union pmu_dis_irq_cluster0_cpu3_local_duration1
			dis_irq_cluster0_cpu3_local_duration1; /* offset : 0x21b4 */
	union pmu_dis_irq_cluster0_cpu3_local_duration2
			dis_irq_cluster0_cpu3_local_duration2; /* offset : 0x21b8 */
	union pmu_dis_irq_cluster0_cpu3_local_duration3
			dis_irq_cluster0_cpu3_local_duration3; /* offset : 0x21bc */
	uint32_t reserved_56[8];
	union pmu_dis_irq_cluster0_cpu3_cpusequencer_configuration
			dis_irq_cluster0_cpu3_cpusequencer_configuration; /* offset : 0x21e0 */
	union pmu_dis_irq_cluster0_cpu3_cpusequencer_status
			dis_irq_cluster0_cpu3_cpusequencer_status; /* offset : 0x21e4 */
	union pmu_dis_irq_cluster0_cpu3_cpusequencer_option
			dis_irq_cluster0_cpu3_cpusequencer_option; /* offset : 0x21e8 */
	uint32_t reserved_57;
	union pmu_dis_irq_cluster0_cpu3_cpusequencer_duration0
			dis_irq_cluster0_cpu3_cpusequencer_duration0; /* offset : 0x21f0 */
	union pmu_dis_irq_cluster0_cpu3_cpusequencer_duration1
			dis_irq_cluster0_cpu3_cpusequencer_duration1; /* offset : 0x21f4 */
	union pmu_dis_irq_cluster0_cpu3_cpusequencer_duration2
			dis_irq_cluster0_cpu3_cpusequencer_duration2; /* offset : 0x21f8 */
	union pmu_dis_irq_cluster0_cpu3_cpusequencer_duration3
			dis_irq_cluster0_cpu3_cpusequencer_duration3; /* offset : 0x21fc */
	union pmu_cluster1_cpu0_configuration cluster1_cpu0_configuration; /* offset : 0x2200 */
	union pmu_cluster1_cpu0_status cluster1_cpu0_status; /* offset : 0x2204 */
	union pmu_cluster1_cpu0_option cluster1_cpu0_option; /* offset : 0x2208 */
	union pmu_cluster1_cpu0_reset cluster1_cpu0_reset; /* offset : 0x220c */
	union pmu_cluster1_cpu0_duration0 cluster1_cpu0_duration0; /* offset : 0x2210 */
	union pmu_cluster1_cpu0_duration1 cluster1_cpu0_duration1; /* offset : 0x2214 */
	union pmu_cluster1_cpu0_duration2 cluster1_cpu0_duration2; /* offset : 0x2218 */
	union pmu_cluster1_cpu0_duration3 cluster1_cpu0_duration3; /* offset : 0x221c */
	union pmu_dis_irq_cluster1_cpu0_local_configuration
			dis_irq_cluster1_cpu0_local_configuration; /* offset : 0x2220 */
	union pmu_dis_irq_cluster1_cpu0_local_status dis_irq_cluster1_cpu0_local_status; /* offset : 0x2224 */
	union pmu_dis_irq_cluster1_cpu0_local_option dis_irq_cluster1_cpu0_local_option; /* offset : 0x2228 */
	uint32_t reserved_58;
	union pmu_dis_irq_cluster1_cpu0_local_duration0
			dis_irq_cluster1_cpu0_local_duration0; /* offset : 0x2230 */
	union pmu_dis_irq_cluster1_cpu0_local_duration1
			dis_irq_cluster1_cpu0_local_duration1; /* offset : 0x2234 */
	union pmu_dis_irq_cluster1_cpu0_local_duration2
			dis_irq_cluster1_cpu0_local_duration2; /* offset : 0x2238 */
	union pmu_dis_irq_cluster1_cpu0_local_duration3
			dis_irq_cluster1_cpu0_local_duration3; /* offset : 0x223c */
	uint32_t reserved_59[8];
	union pmu_dis_irq_cluster1_cpu0_cpusequencer_configuration
			dis_irq_cluster1_cpu0_cpusequencer_configuration; /* offset : 0x2260 */
	union pmu_dis_irq_cluster1_cpu0_cpusequencer_status
			dis_irq_cluster1_cpu0_cpusequencer_status; /* offset : 0x2264 */
	union pmu_dis_irq_cluster1_cpu0_cpusequencer_option
			dis_irq_cluster1_cpu0_cpusequencer_option; /* offset : 0x2268 */
	uint32_t reserved_60;
	union pmu_dis_irq_cluster1_cpu0_cpusequencer_duration0
			dis_irq_cluster1_cpu0_cpusequencer_duration0; /* offset : 0x2270 */
	union pmu_dis_irq_cluster1_cpu0_cpusequencer_duration1
			dis_irq_cluster1_cpu0_cpusequencer_duration1; /* offset : 0x2274 */
	union pmu_dis_irq_cluster1_cpu0_cpusequencer_duration2
			dis_irq_cluster1_cpu0_cpusequencer_duration2; /* offset : 0x2278 */
	union pmu_dis_irq_cluster1_cpu0_cpusequencer_duration3
			dis_irq_cluster1_cpu0_cpusequencer_duration3; /* offset : 0x227c */
	union pmu_cluster1_cpu1_configuration cluster1_cpu1_configuration; /* offset : 0x2280 */
	union pmu_cluster1_cpu1_status cluster1_cpu1_status; /* offset : 0x2284 */
	union pmu_cluster1_cpu1_option cluster1_cpu1_option; /* offset : 0x2288 */
	union pmu_cluster1_cpu1_reset cluster1_cpu1_reset; /* offset : 0x228c */
	union pmu_cluster1_cpu1_duration0 cluster1_cpu1_duration0; /* offset : 0x2290 */
	union pmu_cluster1_cpu1_duration1 cluster1_cpu1_duration1; /* offset : 0x2294 */
	union pmu_cluster1_cpu1_duration2 cluster1_cpu1_duration2; /* offset : 0x2298 */
	union pmu_cluster1_cpu1_duration3 cluster1_cpu1_duration3; /* offset : 0x229c */
	union pmu_dis_irq_cluster1_cpu1_local_configuration
			dis_irq_cluster1_cpu1_local_configuration; /* offset : 0x22a0 */
	union pmu_dis_irq_cluster1_cpu1_local_status dis_irq_cluster1_cpu1_local_status; /* offset : 0x22a4 */
	union pmu_dis_irq_cluster1_cpu1_local_option dis_irq_cluster1_cpu1_local_option; /* offset : 0x22a8 */
	uint32_t reserved_61;
	union pmu_dis_irq_cluster1_cpu1_local_duration0
			dis_irq_cluster1_cpu1_local_duration0; /* offset : 0x22b0 */
	union pmu_dis_irq_cluster1_cpu1_local_duration1
			dis_irq_cluster1_cpu1_local_duration1; /* offset : 0x22b4 */
	union pmu_dis_irq_cluster1_cpu1_local_duration2
			dis_irq_cluster1_cpu1_local_duration2; /* offset : 0x22b8 */
	union pmu_dis_irq_cluster1_cpu1_local_duration3
			dis_irq_cluster1_cpu1_local_duration3; /* offset : 0x22bc */
	uint32_t reserved_62[8];
	union pmu_dis_irq_cluster1_cpu1_cpusequencer_configuration
			dis_irq_cluster1_cpu1_cpusequencer_configuration; /* offset : 0x22e0 */
	union pmu_dis_irq_cluster1_cpu1_cpusequencer_status
			dis_irq_cluster1_cpu1_cpusequencer_status; /* offset : 0x22e4 */
	union pmu_dis_irq_cluster1_cpu1_cpusequencer_option
			dis_irq_cluster1_cpu1_cpusequencer_option; /* offset : 0x22e8 */
	uint32_t reserved_63;
	union pmu_dis_irq_cluster1_cpu1_cpusequencer_duration0
			dis_irq_cluster1_cpu1_cpusequencer_duration0; /* offset : 0x22f0 */
	union pmu_dis_irq_cluster1_cpu1_cpusequencer_duration1
			dis_irq_cluster1_cpu1_cpusequencer_duration1; /* offset : 0x22f4 */
	union pmu_dis_irq_cluster1_cpu1_cpusequencer_duration2
			dis_irq_cluster1_cpu1_cpusequencer_duration2; /* offset : 0x22f8 */
	union pmu_dis_irq_cluster1_cpu1_cpusequencer_duration3
			dis_irq_cluster1_cpu1_cpusequencer_duration3; /* offset : 0x22fc */
	union pmu_cluster1_cpu2_configuration cluster1_cpu2_configuration; /* offset : 0x2300 */
	union pmu_cluster1_cpu2_status cluster1_cpu2_status; /* offset : 0x2304 */
	union pmu_cluster1_cpu2_option cluster1_cpu2_option; /* offset : 0x2308 */
	union pmu_cluster1_cpu2_reset cluster1_cpu2_reset; /* offset : 0x230c */
	union pmu_cluster1_cpu2_duration0 cluster1_cpu2_duration0; /* offset : 0x2310 */
	union pmu_cluster1_cpu2_duration1 cluster1_cpu2_duration1; /* offset : 0x2314 */
	union pmu_cluster1_cpu2_duration2 cluster1_cpu2_duration2; /* offset : 0x2318 */
	union pmu_cluster1_cpu2_duration3 cluster1_cpu2_duration3; /* offset : 0x231c */
	union pmu_dis_irq_cluster1_cpu2_local_configuration
			dis_irq_cluster1_cpu2_local_configuration; /* offset : 0x2320 */
	union pmu_dis_irq_cluster1_cpu2_local_status dis_irq_cluster1_cpu2_local_status; /* offset : 0x2324 */
	union pmu_dis_irq_cluster1_cpu2_local_option dis_irq_cluster1_cpu2_local_option; /* offset : 0x2328 */
	uint32_t reserved_64;
	union pmu_dis_irq_cluster1_cpu2_local_duration0
			dis_irq_cluster1_cpu2_local_duration0; /* offset : 0x2330 */
	union pmu_dis_irq_cluster1_cpu2_local_duration1
			dis_irq_cluster1_cpu2_local_duration1; /* offset : 0x2334 */
	union pmu_dis_irq_cluster1_cpu2_local_duration2
			dis_irq_cluster1_cpu2_local_duration2; /* offset : 0x2338 */
	union pmu_dis_irq_cluster1_cpu2_local_duration3
			dis_irq_cluster1_cpu2_local_duration3; /* offset : 0x233c */
	uint32_t reserved_65[8];
	union pmu_dis_irq_cluster1_cpu2_cpusequencer_configuration
			dis_irq_cluster1_cpu2_cpusequencer_configuration; /* offset : 0x2360 */
	union pmu_dis_irq_cluster1_cpu2_cpusequencer_status
			dis_irq_cluster1_cpu2_cpusequencer_status; /* offset : 0x2364 */
	union pmu_dis_irq_cluster1_cpu2_cpusequencer_option
			dis_irq_cluster1_cpu2_cpusequencer_option; /* offset : 0x2368 */
	uint32_t reserved_66;
	union pmu_dis_irq_cluster1_cpu2_cpusequencer_duration0
			dis_irq_cluster1_cpu2_cpusequencer_duration0; /* offset : 0x2370 */
	union pmu_dis_irq_cluster1_cpu2_cpusequencer_duration1
			dis_irq_cluster1_cpu2_cpusequencer_duration1; /* offset : 0x2374 */
	union pmu_dis_irq_cluster1_cpu2_cpusequencer_duration2
			dis_irq_cluster1_cpu2_cpusequencer_duration2; /* offset : 0x2378 */
	union pmu_dis_irq_cluster1_cpu2_cpusequencer_duration3
			dis_irq_cluster1_cpu2_cpusequencer_duration3; /* offset : 0x237c */
	union pmu_cluster1_cpu3_configuration cluster1_cpu3_configuration; /* offset : 0x2380 */
	union pmu_cluster1_cpu3_status cluster1_cpu3_status; /* offset : 0x2384 */
	union pmu_cluster1_cpu3_option cluster1_cpu3_option; /* offset : 0x2388 */
	union pmu_cluster1_cpu3_reset cluster1_cpu3_reset; /* offset : 0x238c */
	union pmu_cluster1_cpu3_duration0 cluster1_cpu3_duration0; /* offset : 0x2390 */
	union pmu_cluster1_cpu3_duration1 cluster1_cpu3_duration1; /* offset : 0x2394 */
	union pmu_cluster1_cpu3_duration2 cluster1_cpu3_duration2; /* offset : 0x2398 */
	union pmu_cluster1_cpu3_duration3 cluster1_cpu3_duration3; /* offset : 0x239c */
	union pmu_dis_irq_cluster1_cpu3_local_configuration
			dis_irq_cluster1_cpu3_local_configuration; /* offset : 0x23a0 */
	union pmu_dis_irq_cluster1_cpu3_local_status dis_irq_cluster1_cpu3_local_status; /* offset : 0x23a4 */
	union pmu_dis_irq_cluster1_cpu3_local_option dis_irq_cluster1_cpu3_local_option; /* offset : 0x23a8 */
	uint32_t reserved_67;
	union pmu_dis_irq_cluster1_cpu3_local_duration0
			dis_irq_cluster1_cpu3_local_duration0; /* offset : 0x23b0 */
	union pmu_dis_irq_cluster1_cpu3_local_duration1
			dis_irq_cluster1_cpu3_local_duration1; /* offset : 0x23b4 */
	union pmu_dis_irq_cluster1_cpu3_local_duration2
			dis_irq_cluster1_cpu3_local_duration2; /* offset : 0x23b8 */
	union pmu_dis_irq_cluster1_cpu3_local_duration3
			dis_irq_cluster1_cpu3_local_duration3; /* offset : 0x23bc */
	uint32_t reserved_68[8];
	union pmu_dis_irq_cluster1_cpu3_cpusequencer_configuration
			dis_irq_cluster1_cpu3_cpusequencer_configuration; /* offset : 0x23e0 */
	union pmu_dis_irq_cluster1_cpu3_cpusequencer_status
			dis_irq_cluster1_cpu3_cpusequencer_status; /* offset : 0x23e4 */
	union pmu_dis_irq_cluster1_cpu3_cpusequencer_option
			dis_irq_cluster1_cpu3_cpusequencer_option; /* offset : 0x23e8 */
	uint32_t reserved_69;
	union pmu_dis_irq_cluster1_cpu3_cpusequencer_duration0
			dis_irq_cluster1_cpu3_cpusequencer_duration0; /* offset : 0x23f0 */
	union pmu_dis_irq_cluster1_cpu3_cpusequencer_duration1
			dis_irq_cluster1_cpu3_cpusequencer_duration1; /* offset : 0x23f4 */
	union pmu_dis_irq_cluster1_cpu3_cpusequencer_duration2
			dis_irq_cluster1_cpu3_cpusequencer_duration2; /* offset : 0x23f8 */
	union pmu_dis_irq_cluster1_cpu3_cpusequencer_duration3
			dis_irq_cluster1_cpu3_cpusequencer_duration3; /* offset : 0x23fc */
	union pmu_cluster0_noncpu_configuration cluster0_noncpu_configuration; /* offset : 0x2400 */
	union pmu_cluster0_noncpu_status cluster0_noncpu_status; /* offset : 0x2404 */
	union pmu_cluster0_noncpu_option cluster0_noncpu_option; /* offset : 0x2408 */
	union pmu_cluster0_noncpu_reset cluster0_noncpu_reset; /* offset : 0x240c */
	union pmu_cluster0_noncpu_duration0 cluster0_noncpu_duration0; /* offset : 0x2410 */
	union pmu_cluster0_noncpu_duration1 cluster0_noncpu_duration1; /* offset : 0x2414 */
	union pmu_cluster0_noncpu_duration2 cluster0_noncpu_duration2; /* offset : 0x2418 */
	union pmu_cluster0_noncpu_duration3 cluster0_noncpu_duration3; /* offset : 0x241c */
	uint32_t reserved_70[8];
	union pmu_cluster1_noncpu_configuration cluster1_noncpu_configuration; /* offset : 0x2440 */
	union pmu_cluster1_noncpu_status cluster1_noncpu_status; /* offset : 0x2444 */
	union pmu_cluster1_noncpu_option cluster1_noncpu_option; /* offset : 0x2448 */
	union pmu_cluster1_noncpu_reset cluster1_noncpu_reset; /* offset : 0x244c */
	union pmu_cluster1_noncpu_duration0 cluster1_noncpu_duration0; /* offset : 0x2450 */
	union pmu_cluster1_noncpu_duration1 cluster1_noncpu_duration1; /* offset : 0x2454 */
	union pmu_cluster1_noncpu_duration2 cluster1_noncpu_duration2; /* offset : 0x2458 */
	union pmu_cluster1_noncpu_duration3 cluster1_noncpu_duration3; /* offset : 0x245c */
	uint32_t reserved_71[8];
	union pmu_cluster0_cpusequencer_configuration
			cluster0_cpusequencer_configuration; /* offset : 0x2480 */
	union pmu_cluster0_cpusequencer_status cluster0_cpusequencer_status; /* offset : 0x2484 */
	union pmu_cluster0_cpusequencer_option cluster0_cpusequencer_option; /* offset : 0x2488 */
	union pmu_cluster0_cpusequencer_reset cluster0_cpusequencer_reset; /* offset : 0x248c */
	union pmu_cluster0_cpusequencer_duration0 cluster0_cpusequencer_duration0; /* offset : 0x2490 */
	union pmu_cluster0_cpusequencer_duration1 cluster0_cpusequencer_duration1; /* offset : 0x2494 */
	union pmu_cluster0_cpusequencer_duration2 cluster0_cpusequencer_duration2; /* offset : 0x2498 */
	union pmu_cluster0_cpusequencer_duration3 cluster0_cpusequencer_duration3; /* offset : 0x249c */
	union pmu_cluster1_cpusequencer_configuration
			cluster1_cpusequencer_configuration; /* offset : 0x24a0 */
	union pmu_cluster1_cpusequencer_status cluster1_cpusequencer_status; /* offset : 0x24a4 */
	union pmu_cluster1_cpusequencer_option cluster1_cpusequencer_option; /* offset : 0x24a8 */
	union pmu_cluster1_cpusequencer_reset cluster1_cpusequencer_reset; /* offset : 0x24ac */
	union pmu_cluster1_cpusequencer_duration0 cluster1_cpusequencer_duration0; /* offset : 0x24b0 */
	union pmu_cluster1_cpusequencer_duration1 cluster1_cpusequencer_duration1; /* offset : 0x24b4 */
	union pmu_cluster1_cpusequencer_duration2 cluster1_cpusequencer_duration2; /* offset : 0x24b8 */
	union pmu_cluster1_cpusequencer_duration3 cluster1_cpusequencer_duration3; /* offset : 0x24bc */
	uint32_t reserved_72[80];
	union pmu_cluster0_l2_configuration cluster0_l2_configuration; /* offset : 0x2600 */
	union pmu_cluster0_l2_status cluster0_l2_status; /* offset : 0x2604 */
	union pmu_cluster0_l2_option cluster0_l2_option; /* offset : 0x2608 */
	uint32_t reserved_73;
	union pmu_cluster0_l2_duration0 cluster0_l2_duration0; /* offset : 0x2610 */
	union pmu_cluster0_l2_duration1 cluster0_l2_duration1; /* offset : 0x2614 */
	union pmu_cluster0_l2_duration2 cluster0_l2_duration2; /* offset : 0x2618 */
	union pmu_cluster0_l2_duration3 cluster0_l2_duration3; /* offset : 0x261c */
	union pmu_cluster1_l2_configuration cluster1_l2_configuration; /* offset : 0x2620 */
	union pmu_cluster1_l2_status cluster1_l2_status; /* offset : 0x2624 */
	union pmu_cluster1_l2_option cluster1_l2_option; /* offset : 0x2628 */
	uint32_t reserved_74;
	union pmu_cluster1_l2_duration0 cluster1_l2_duration0; /* offset : 0x2630 */
	union pmu_cluster1_l2_duration1 cluster1_l2_duration1; /* offset : 0x2634 */
	union pmu_cluster1_l2_duration2 cluster1_l2_duration2; /* offset : 0x2638 */
	union pmu_cluster1_l2_duration3 cluster1_l2_duration3; /* offset : 0x263c */
	uint32_t reserved_75[168];
	union pmu_reset_cpuclkstop0_configuration reset_cpuclkstop0_configuration; /* offset : 0x28e0 */
	union pmu_reset_cpuclkstop0_status reset_cpuclkstop0_status; /* offset : 0x28e4 */
	union pmu_reset_cpuclkstop0_option reset_cpuclkstop0_option; /* offset : 0x28e8 */
	uint32_t reserved_76;
	union pmu_reset_cpuclkstop0_duration0 reset_cpuclkstop0_duration0; /* offset : 0x28f0 */
	union pmu_reset_cpuclkstop0_duration1 reset_cpuclkstop0_duration1; /* offset : 0x28f4 */
	union pmu_reset_cpuclkstop0_duration2 reset_cpuclkstop0_duration2; /* offset : 0x28f8 */
	union pmu_reset_cpuclkstop0_duration3 reset_cpuclkstop0_duration3; /* offset : 0x28fc */
	union pmu_reset_cpuclkstop1_configuration reset_cpuclkstop1_configuration; /* offset : 0x2900 */
	union pmu_reset_cpuclkstop1_status reset_cpuclkstop1_status; /* offset : 0x2904 */
	union pmu_reset_cpuclkstop1_option reset_cpuclkstop1_option; /* offset : 0x2908 */
	uint32_t reserved_77;
	union pmu_reset_cpuclkstop1_duration0 reset_cpuclkstop1_duration0; /* offset : 0x2910 */
	union pmu_reset_cpuclkstop1_duration1 reset_cpuclkstop1_duration1; /* offset : 0x2914 */
	union pmu_reset_cpuclkstop1_duration2 reset_cpuclkstop1_duration2; /* offset : 0x2918 */
	union pmu_reset_cpuclkstop1_duration3 reset_cpuclkstop1_duration3; /* offset : 0x291c */
	uint32_t reserved_78[184];
	union pmu_rot_poresetn_configuration rot_poresetn_configuration; /* offset : 0x2c00 */
	union pmu_rot_poresetn_status rot_poresetn_status; /* offset : 0x2c04 */
	union pmu_rot_poresetn_reset rot_poresetn_reset; /* offset : 0x2c08 */
	uint32_t reserved_79;
	union pmu_rot_poresetn_duration0 rot_poresetn_duration0; /* offset : 0x2c10 */
	union pmu_rot_poresetn_duration1 rot_poresetn_duration1; /* offset : 0x2c14 */
	union pmu_rot_poresetn_duration2 rot_poresetn_duration2; /* offset : 0x2c18 */
	union pmu_rot_poresetn_duration3 rot_poresetn_duration3; /* offset : 0x2c1c */
	union pmu_rot_hresetn_configuration rot_hresetn_configuration; /* offset : 0x2c20 */
	union pmu_rot_hresetn_status rot_hresetn_status; /* offset : 0x2c24 */
	union pmu_rot_hresetn_reset rot_hresetn_reset; /* offset : 0x2c28 */
	uint32_t reserved_80;
	union pmu_rot_hresetn_duration0 rot_hresetn_duration0; /* offset : 0x2c30 */
	union pmu_rot_hresetn_duration1 rot_hresetn_duration1; /* offset : 0x2c34 */
	union pmu_rot_hresetn_duration2 rot_hresetn_duration2; /* offset : 0x2c38 */
	union pmu_rot_hresetn_duration3 rot_hresetn_duration3; /* offset : 0x2c3c */
	uint32_t reserved_81[56];
	union pmu_oscclk_gate_configuration oscclk_gate_configuration; /* offset : 0x2d20 */
	union pmu_oscclk_gate_status oscclk_gate_status; /* offset : 0x2d24 */
	union pmu_oscclk_gate_option oscclk_gate_option; /* offset : 0x2d28 */
	uint32_t reserved_82;
	union pmu_oscclk_gate_duration0 oscclk_gate_duration0; /* offset : 0x2d30 */
	union pmu_oscclk_gate_duration1 oscclk_gate_duration1; /* offset : 0x2d34 */
	union pmu_oscclk_gate_duration2 oscclk_gate_duration2; /* offset : 0x2d38 */
	union pmu_oscclk_gate_duration3 oscclk_gate_duration3; /* offset : 0x2d3c */
	uint32_t reserved_83[560];
	union pmu_ext_regulator_configuration ext_regulator_configuration; /* offset : 0x3600 */
	union pmu_ext_regulator_status ext_regulator_status; /* offset : 0x3604 */
	union pmu_ext_regulator_option ext_regulator_option; /* offset : 0x3608 */
	uint32_t reserved_84;
	union pmu_ext_regulator_duration0 ext_regulator_duration0; /* offset : 0x3610 */
	union pmu_ext_regulator_duration1 ext_regulator_duration1; /* offset : 0x3614 */
	union pmu_ext_regulator_duration2 ext_regulator_duration2; /* offset : 0x3618 */
	union pmu_ext_regulator_duration3 ext_regulator_duration3; /* offset : 0x361c */
	uint32_t reserved_85[504];
	union pmu_clkstop_open_cmu_cp0_configuration clkstop_open_cmu_cp0_configuration; /* offset : 0x3e00 */
	union pmu_clkstop_open_cmu_cp0_status clkstop_open_cmu_cp0_status; /* offset : 0x3e04 */
	union pmu_clkstop_open_cmu_cp0_option clkstop_open_cmu_cp0_option; /* offset : 0x3e08 */
	uint32_t reserved_86;
	union pmu_clkstop_open_cmu_cp0_duration0 clkstop_open_cmu_cp0_duration0; /* offset : 0x3e10 */
	union pmu_clkstop_open_cmu_cp0_duration1 clkstop_open_cmu_cp0_duration1; /* offset : 0x3e14 */
	union pmu_clkstop_open_cmu_cp0_duration2 clkstop_open_cmu_cp0_duration2; /* offset : 0x3e18 */
	union pmu_clkstop_open_cmu_cp0_duration3 clkstop_open_cmu_cp0_duration3; /* offset : 0x3e1c */
	union pmu_clkstop_open_cmu_cp1_configuration clkstop_open_cmu_cp1_configuration; /* offset : 0x3e20 */
	union pmu_clkstop_open_cmu_cp1_status clkstop_open_cmu_cp1_status; /* offset : 0x3e24 */
	union pmu_clkstop_open_cmu_cp1_option clkstop_open_cmu_cp1_option; /* offset : 0x3e28 */
	uint32_t reserved_87;
	union pmu_clkstop_open_cmu_cp1_duration0 clkstop_open_cmu_cp1_duration0; /* offset : 0x3e30 */
	union pmu_clkstop_open_cmu_cp1_duration1 clkstop_open_cmu_cp1_duration1; /* offset : 0x3e34 */
	union pmu_clkstop_open_cmu_cp1_duration2 clkstop_open_cmu_cp1_duration2; /* offset : 0x3e38 */
	union pmu_clkstop_open_cmu_cp1_duration3 clkstop_open_cmu_cp1_duration3; /* offset : 0x3e3c */
	union pmu_clkstop_open_cmu_pcie_configuration
			clkstop_open_cmu_pcie_configuration; /* offset : 0x3e40 */
	union pmu_clkstop_open_cmu_pcie_status clkstop_open_cmu_pcie_status; /* offset : 0x3e44 */
	union pmu_clkstop_open_cmu_pcie_option clkstop_open_cmu_pcie_option; /* offset : 0x3e48 */
	uint32_t reserved_88;
	union pmu_clkstop_open_cmu_pcie_duration0 clkstop_open_cmu_pcie_duration0; /* offset : 0x3e50 */
	union pmu_clkstop_open_cmu_pcie_duration1 clkstop_open_cmu_pcie_duration1; /* offset : 0x3e54 */
	union pmu_clkstop_open_cmu_pcie_duration2 clkstop_open_cmu_pcie_duration2; /* offset : 0x3e58 */
	union pmu_clkstop_open_cmu_pcie_duration3 clkstop_open_cmu_pcie_duration3; /* offset : 0x3e5c */
	union pmu_clkstop_open_cmu_dram_configuration
			clkstop_open_cmu_dram_configuration; /* offset : 0x3e60 */
	union pmu_clkstop_open_cmu_dram_status clkstop_open_cmu_dram_status; /* offset : 0x3e64 */
	union pmu_clkstop_open_cmu_dram_option clkstop_open_cmu_dram_option; /* offset : 0x3e68 */
	uint32_t reserved_89;
	union pmu_clkstop_open_cmu_dram_duration0 clkstop_open_cmu_dram_duration0; /* offset : 0x3e70 */
	union pmu_clkstop_open_cmu_dram_duration1 clkstop_open_cmu_dram_duration1; /* offset : 0x3e74 */
	union pmu_clkstop_open_cmu_dram_duration2 clkstop_open_cmu_dram_duration2; /* offset : 0x3e78 */
	union pmu_clkstop_open_cmu_dram_duration3 clkstop_open_cmu_dram_duration3; /* offset : 0x3e7c */
	union pmu_clkstop_open_cmu_dcl0_configuration
			clkstop_open_cmu_dcl0_configuration; /* offset : 0x3e80 */
	union pmu_clkstop_open_cmu_dcl0_status clkstop_open_cmu_dcl0_status; /* offset : 0x3e84 */
	union pmu_clkstop_open_cmu_dcl0_option clkstop_open_cmu_dcl0_option; /* offset : 0x3e88 */
	uint32_t reserved_90;
	union pmu_clkstop_open_cmu_dcl0_duration0 clkstop_open_cmu_dcl0_duration0; /* offset : 0x3e90 */
	union pmu_clkstop_open_cmu_dcl0_duration1 clkstop_open_cmu_dcl0_duration1; /* offset : 0x3e94 */
	union pmu_clkstop_open_cmu_dcl0_duration2 clkstop_open_cmu_dcl0_duration2; /* offset : 0x3e98 */
	union pmu_clkstop_open_cmu_dcl0_duration3 clkstop_open_cmu_dcl0_duration3; /* offset : 0x3e9c */
	union pmu_clkstop_open_cmu_dcl1_configuration
			clkstop_open_cmu_dcl1_configuration; /* offset : 0x3ea0 */
	union pmu_clkstop_open_cmu_dcl1_status clkstop_open_cmu_dcl1_status; /* offset : 0x3ea4 */
	union pmu_clkstop_open_cmu_dcl1_option clkstop_open_cmu_dcl1_option; /* offset : 0x3ea8 */
	uint32_t reserved_91;
	union pmu_clkstop_open_cmu_dcl1_duration0 clkstop_open_cmu_dcl1_duration0; /* offset : 0x3eb0 */
	union pmu_clkstop_open_cmu_dcl1_duration1 clkstop_open_cmu_dcl1_duration1; /* offset : 0x3eb4 */
	union pmu_clkstop_open_cmu_dcl1_duration2 clkstop_open_cmu_dcl1_duration2; /* offset : 0x3eb8 */
	union pmu_clkstop_open_cmu_dcl1_duration3 clkstop_open_cmu_dcl1_duration3; /* offset : 0x3ebc */
	union pmu_clkstop_open_cmu_rbch00_configuration
			clkstop_open_cmu_rbch00_configuration; /* offset : 0x3ec0 */
	union pmu_clkstop_open_cmu_rbch00_status clkstop_open_cmu_rbch00_status; /* offset : 0x3ec4 */
	union pmu_clkstop_open_cmu_rbch00_option clkstop_open_cmu_rbch00_option; /* offset : 0x3ec8 */
	uint32_t reserved_92;
	union pmu_clkstop_open_cmu_rbch00_duration0 clkstop_open_cmu_rbch00_duration0; /* offset : 0x3ed0 */
	union pmu_clkstop_open_cmu_rbch00_duration1 clkstop_open_cmu_rbch00_duration1; /* offset : 0x3ed4 */
	union pmu_clkstop_open_cmu_rbch00_duration2 clkstop_open_cmu_rbch00_duration2; /* offset : 0x3ed8 */
	union pmu_clkstop_open_cmu_rbch00_duration3 clkstop_open_cmu_rbch00_duration3; /* offset : 0x3edc */
	union pmu_clkstop_open_cmu_rbch01_configuration
			clkstop_open_cmu_rbch01_configuration; /* offset : 0x3ee0 */
	union pmu_clkstop_open_cmu_rbch01_status clkstop_open_cmu_rbch01_status; /* offset : 0x3ee4 */
	union pmu_clkstop_open_cmu_rbch01_option clkstop_open_cmu_rbch01_option; /* offset : 0x3ee8 */
	uint32_t reserved_93;
	union pmu_clkstop_open_cmu_rbch01_duration0 clkstop_open_cmu_rbch01_duration0; /* offset : 0x3ef0 */
	union pmu_clkstop_open_cmu_rbch01_duration1 clkstop_open_cmu_rbch01_duration1; /* offset : 0x3ef4 */
	union pmu_clkstop_open_cmu_rbch01_duration2 clkstop_open_cmu_rbch01_duration2; /* offset : 0x3ef8 */
	union pmu_clkstop_open_cmu_rbch01_duration3 clkstop_open_cmu_rbch01_duration3; /* offset : 0x3efc */
	union pmu_clkstop_open_cmu_rbcv00_configuration
			clkstop_open_cmu_rbcv00_configuration; /* offset : 0x3f00 */
	union pmu_clkstop_open_cmu_rbcv00_status clkstop_open_cmu_rbcv00_status; /* offset : 0x3f04 */
	union pmu_clkstop_open_cmu_rbcv00_option clkstop_open_cmu_rbcv00_option; /* offset : 0x3f08 */
	uint32_t reserved_94;
	union pmu_clkstop_open_cmu_rbcv00_duration0 clkstop_open_cmu_rbcv00_duration0; /* offset : 0x3f10 */
	union pmu_clkstop_open_cmu_rbcv00_duration1 clkstop_open_cmu_rbcv00_duration1; /* offset : 0x3f14 */
	union pmu_clkstop_open_cmu_rbcv00_duration2 clkstop_open_cmu_rbcv00_duration2; /* offset : 0x3f18 */
	union pmu_clkstop_open_cmu_rbcv00_duration3 clkstop_open_cmu_rbcv00_duration3; /* offset : 0x3f1c */
	union pmu_clkstop_open_cmu_rbcv01_configuration
			clkstop_open_cmu_rbcv01_configuration; /* offset : 0x3f20 */
	union pmu_clkstop_open_cmu_rbcv01_status clkstop_open_cmu_rbcv01_status; /* offset : 0x3f24 */
	union pmu_clkstop_open_cmu_rbcv01_option clkstop_open_cmu_rbcv01_option; /* offset : 0x3f28 */
	uint32_t reserved_95;
	union pmu_clkstop_open_cmu_rbcv01_duration0 clkstop_open_cmu_rbcv01_duration0; /* offset : 0x3f30 */
	union pmu_clkstop_open_cmu_rbcv01_duration1 clkstop_open_cmu_rbcv01_duration1; /* offset : 0x3f34 */
	union pmu_clkstop_open_cmu_rbcv01_duration2 clkstop_open_cmu_rbcv01_duration2; /* offset : 0x3f38 */
	union pmu_clkstop_open_cmu_rbcv01_duration3 clkstop_open_cmu_rbcv01_duration3; /* offset : 0x3f3c */
	union pmu_clkstop_open_cmu_rbcv10_configuration
			clkstop_open_cmu_rbcv10_configuration; /* offset : 0x3f40 */
	union pmu_clkstop_open_cmu_rbcv10_status clkstop_open_cmu_rbcv10_status; /* offset : 0x3f44 */
	union pmu_clkstop_open_cmu_rbcv10_option clkstop_open_cmu_rbcv10_option; /* offset : 0x3f48 */
	uint32_t reserved_96;
	union pmu_clkstop_open_cmu_rbcv10_duration0 clkstop_open_cmu_rbcv10_duration0; /* offset : 0x3f50 */
	union pmu_clkstop_open_cmu_rbcv10_duration1 clkstop_open_cmu_rbcv10_duration1; /* offset : 0x3f54 */
	union pmu_clkstop_open_cmu_rbcv10_duration2 clkstop_open_cmu_rbcv10_duration2; /* offset : 0x3f58 */
	union pmu_clkstop_open_cmu_rbcv10_duration3 clkstop_open_cmu_rbcv10_duration3; /* offset : 0x3f5c */
	union pmu_clkstop_open_cmu_rbcv11_configuration
			clkstop_open_cmu_rbcv11_configuration; /* offset : 0x3f60 */
	union pmu_clkstop_open_cmu_rbcv11_status clkstop_open_cmu_rbcv11_status; /* offset : 0x3f64 */
	union pmu_clkstop_open_cmu_rbcv11_option clkstop_open_cmu_rbcv11_option; /* offset : 0x3f68 */
	uint32_t reserved_97;
	union pmu_clkstop_open_cmu_rbcv11_duration0 clkstop_open_cmu_rbcv11_duration0; /* offset : 0x3f70 */
	union pmu_clkstop_open_cmu_rbcv11_duration1 clkstop_open_cmu_rbcv11_duration1; /* offset : 0x3f74 */
	union pmu_clkstop_open_cmu_rbcv11_duration2 clkstop_open_cmu_rbcv11_duration2; /* offset : 0x3f78 */
	union pmu_clkstop_open_cmu_rbcv11_duration3 clkstop_open_cmu_rbcv11_duration3; /* offset : 0x3f7c */
	union pmu_clkstop_open_cmu_rot_configuration clkstop_open_cmu_rot_configuration; /* offset : 0x3f80 */
	union pmu_clkstop_open_cmu_rot_status clkstop_open_cmu_rot_status; /* offset : 0x3f84 */
	union pmu_clkstop_open_cmu_rot_option clkstop_open_cmu_rot_option; /* offset : 0x3f88 */
	uint32_t reserved_98;
	union pmu_clkstop_open_cmu_rot_duration0 clkstop_open_cmu_rot_duration0; /* offset : 0x3f90 */
	union pmu_clkstop_open_cmu_rot_duration1 clkstop_open_cmu_rot_duration1; /* offset : 0x3f94 */
	union pmu_clkstop_open_cmu_rot_duration2 clkstop_open_cmu_rot_duration2; /* offset : 0x3f98 */
	union pmu_clkstop_open_cmu_rot_duration3 clkstop_open_cmu_rot_duration3; /* offset : 0x3f9c */
	union pmu_clkstop_open_cmu_peri0_configuration
			clkstop_open_cmu_peri0_configuration; /* offset : 0x3fa0 */
	union pmu_clkstop_open_cmu_peri0_status clkstop_open_cmu_peri0_status; /* offset : 0x3fa4 */
	union pmu_clkstop_open_cmu_peri0_option clkstop_open_cmu_peri0_option; /* offset : 0x3fa8 */
	uint32_t reserved_99;
	union pmu_clkstop_open_cmu_peri0_duration0 clkstop_open_cmu_peri0_duration0; /* offset : 0x3fb0 */
	union pmu_clkstop_open_cmu_peri0_duration1 clkstop_open_cmu_peri0_duration1; /* offset : 0x3fb4 */
	union pmu_clkstop_open_cmu_peri0_duration2 clkstop_open_cmu_peri0_duration2; /* offset : 0x3fb8 */
	union pmu_clkstop_open_cmu_peri0_duration3 clkstop_open_cmu_peri0_duration3; /* offset : 0x3fbc */
	union pmu_clkstop_open_cmu_peri1_configuration
			clkstop_open_cmu_peri1_configuration; /* offset : 0x3fc0 */
	union pmu_clkstop_open_cmu_peri1_status clkstop_open_cmu_peri1_status; /* offset : 0x3fc4 */
	union pmu_clkstop_open_cmu_peri1_option clkstop_open_cmu_peri1_option; /* offset : 0x3fc8 */
	uint32_t reserved_100;
	union pmu_clkstop_open_cmu_peri1_duration0 clkstop_open_cmu_peri1_duration0; /* offset : 0x3fd0 */
	union pmu_clkstop_open_cmu_peri1_duration1 clkstop_open_cmu_peri1_duration1; /* offset : 0x3fd4 */
	union pmu_clkstop_open_cmu_peri1_duration2 clkstop_open_cmu_peri1_duration2; /* offset : 0x3fd8 */
	union pmu_clkstop_open_cmu_peri1_duration3 clkstop_open_cmu_peri1_duration3; /* offset : 0x3fdc */
	union pmu_clkstop_open_cmu_sbus_u_configuration
			clkstop_open_cmu_sbus_u_configuration; /* offset : 0x3fe0 */
	union pmu_clkstop_open_cmu_sbus_u_status clkstop_open_cmu_sbus_u_status; /* offset : 0x3fe4 */
	union pmu_clkstop_open_cmu_sbus_u_option clkstop_open_cmu_sbus_u_option; /* offset : 0x3fe8 */
	uint32_t reserved_101;
	union pmu_clkstop_open_cmu_sbus_u_duration0 clkstop_open_cmu_sbus_u_duration0; /* offset : 0x3ff0 */
	union pmu_clkstop_open_cmu_sbus_u_duration1 clkstop_open_cmu_sbus_u_duration1; /* offset : 0x3ff4 */
	union pmu_clkstop_open_cmu_sbus_u_duration2 clkstop_open_cmu_sbus_u_duration2; /* offset : 0x3ff8 */
	union pmu_clkstop_open_cmu_sbus_u_duration3 clkstop_open_cmu_sbus_u_duration3; /* offset : 0x3ffc */
	union pmu_clkstop_open_cmu_sbus_d_configuration
			clkstop_open_cmu_sbus_d_configuration; /* offset : 0x4000 */
	union pmu_clkstop_open_cmu_sbus_d_status clkstop_open_cmu_sbus_d_status; /* offset : 0x4004 */
	union pmu_clkstop_open_cmu_sbus_d_option clkstop_open_cmu_sbus_d_option; /* offset : 0x4008 */
	uint32_t reserved_102;
	union pmu_clkstop_open_cmu_sbus_d_duration0 clkstop_open_cmu_sbus_d_duration0; /* offset : 0x4010 */
	union pmu_clkstop_open_cmu_sbus_d_duration1 clkstop_open_cmu_sbus_d_duration1; /* offset : 0x4014 */
	union pmu_clkstop_open_cmu_sbus_d_duration2 clkstop_open_cmu_sbus_d_duration2; /* offset : 0x4018 */
	union pmu_clkstop_open_cmu_sbus_d_duration3 clkstop_open_cmu_sbus_d_duration3; /* offset : 0x401c */
	union pmu_clkstop_open_cmu_sbus_l_configuration
			clkstop_open_cmu_sbus_l_configuration; /* offset : 0x4020 */
	union pmu_clkstop_open_cmu_sbus_l_status clkstop_open_cmu_sbus_l_status; /* offset : 0x4024 */
	union pmu_clkstop_open_cmu_sbus_l_option clkstop_open_cmu_sbus_l_option; /* offset : 0x4028 */
	uint32_t reserved_103;
	union pmu_clkstop_open_cmu_sbus_l_duration0 clkstop_open_cmu_sbus_l_duration0; /* offset : 0x4030 */
	union pmu_clkstop_open_cmu_sbus_l_duration1 clkstop_open_cmu_sbus_l_duration1; /* offset : 0x4034 */
	union pmu_clkstop_open_cmu_sbus_l_duration2 clkstop_open_cmu_sbus_l_duration2; /* offset : 0x4038 */
	union pmu_clkstop_open_cmu_sbus_l_duration3 clkstop_open_cmu_sbus_l_duration3; /* offset : 0x403c */
	union pmu_clkstop_open_cmu_nbus_u_configuration
			clkstop_open_cmu_nbus_u_configuration; /* offset : 0x4040 */
	union pmu_clkstop_open_cmu_nbus_u_status clkstop_open_cmu_nbus_u_status; /* offset : 0x4044 */
	union pmu_clkstop_open_cmu_nbus_u_option clkstop_open_cmu_nbus_u_option; /* offset : 0x4048 */
	uint32_t reserved_104;
	union pmu_clkstop_open_cmu_nbus_u_duration0 clkstop_open_cmu_nbus_u_duration0; /* offset : 0x4050 */
	union pmu_clkstop_open_cmu_nbus_u_duration1 clkstop_open_cmu_nbus_u_duration1; /* offset : 0x4054 */
	union pmu_clkstop_open_cmu_nbus_u_duration2 clkstop_open_cmu_nbus_u_duration2; /* offset : 0x4058 */
	union pmu_clkstop_open_cmu_nbus_u_duration3 clkstop_open_cmu_nbus_u_duration3; /* offset : 0x405c */
	union pmu_clkstop_open_cmu_nbus_d_configuration
			clkstop_open_cmu_nbus_d_configuration; /* offset : 0x4060 */
	union pmu_clkstop_open_cmu_nbus_d_status clkstop_open_cmu_nbus_d_status; /* offset : 0x4064 */
	union pmu_clkstop_open_cmu_nbus_d_option clkstop_open_cmu_nbus_d_option; /* offset : 0x4068 */
	uint32_t reserved_105;
	union pmu_clkstop_open_cmu_nbus_d_duration0 clkstop_open_cmu_nbus_d_duration0; /* offset : 0x4070 */
	union pmu_clkstop_open_cmu_nbus_d_duration1 clkstop_open_cmu_nbus_d_duration1; /* offset : 0x4074 */
	union pmu_clkstop_open_cmu_nbus_d_duration2 clkstop_open_cmu_nbus_d_duration2; /* offset : 0x4078 */
	union pmu_clkstop_open_cmu_nbus_d_duration3 clkstop_open_cmu_nbus_d_duration3; /* offset : 0x407c */
	union pmu_clkstop_open_cmu_nbus_l_configuration
			clkstop_open_cmu_nbus_l_configuration; /* offset : 0x4080 */
	union pmu_clkstop_open_cmu_nbus_l_status clkstop_open_cmu_nbus_l_status; /* offset : 0x4084 */
	union pmu_clkstop_open_cmu_nbus_l_option clkstop_open_cmu_nbus_l_option; /* offset : 0x4088 */
	uint32_t reserved_106;
	union pmu_clkstop_open_cmu_nbus_l_duration0 clkstop_open_cmu_nbus_l_duration0; /* offset : 0x4090 */
	union pmu_clkstop_open_cmu_nbus_l_duration1 clkstop_open_cmu_nbus_l_duration1; /* offset : 0x4094 */
	union pmu_clkstop_open_cmu_nbus_l_duration2 clkstop_open_cmu_nbus_l_duration2; /* offset : 0x4098 */
	union pmu_clkstop_open_cmu_nbus_l_duration3 clkstop_open_cmu_nbus_l_duration3; /* offset : 0x409c */
	union pmu_clkstop_open_cmu_wbus_u_configuration
			clkstop_open_cmu_wbus_u_configuration; /* offset : 0x40a0 */
	union pmu_clkstop_open_cmu_wbus_u_status clkstop_open_cmu_wbus_u_status; /* offset : 0x40a4 */
	union pmu_clkstop_open_cmu_wbus_u_option clkstop_open_cmu_wbus_u_option; /* offset : 0x40a8 */
	uint32_t reserved_107;
	union pmu_clkstop_open_cmu_wbus_u_duration0 clkstop_open_cmu_wbus_u_duration0; /* offset : 0x40b0 */
	union pmu_clkstop_open_cmu_wbus_u_duration1 clkstop_open_cmu_wbus_u_duration1; /* offset : 0x40b4 */
	union pmu_clkstop_open_cmu_wbus_u_duration2 clkstop_open_cmu_wbus_u_duration2; /* offset : 0x40b8 */
	union pmu_clkstop_open_cmu_wbus_u_duration3 clkstop_open_cmu_wbus_u_duration3; /* offset : 0x40bc */
	union pmu_clkstop_open_cmu_wbus_d_configuration
			clkstop_open_cmu_wbus_d_configuration; /* offset : 0x40c0 */
	union pmu_clkstop_open_cmu_wbus_d_status clkstop_open_cmu_wbus_d_status; /* offset : 0x40c4 */
	union pmu_clkstop_open_cmu_wbus_d_option clkstop_open_cmu_wbus_d_option; /* offset : 0x40c8 */
	uint32_t reserved_108;
	union pmu_clkstop_open_cmu_wbus_d_duration0 clkstop_open_cmu_wbus_d_duration0; /* offset : 0x40d0 */
	union pmu_clkstop_open_cmu_wbus_d_duration1 clkstop_open_cmu_wbus_d_duration1; /* offset : 0x40d4 */
	union pmu_clkstop_open_cmu_wbus_d_duration2 clkstop_open_cmu_wbus_d_duration2; /* offset : 0x40d8 */
	union pmu_clkstop_open_cmu_wbus_d_duration3 clkstop_open_cmu_wbus_d_duration3; /* offset : 0x40dc */
	union pmu_clkstop_open_cmu_ebus_u_configuration
			clkstop_open_cmu_ebus_u_configuration; /* offset : 0x40e0 */
	union pmu_clkstop_open_cmu_ebus_u_status clkstop_open_cmu_ebus_u_status; /* offset : 0x40e4 */
	union pmu_clkstop_open_cmu_ebus_u_option clkstop_open_cmu_ebus_u_option; /* offset : 0x40e8 */
	uint32_t reserved_109;
	union pmu_clkstop_open_cmu_ebus_u_duration0 clkstop_open_cmu_ebus_u_duration0; /* offset : 0x40f0 */
	union pmu_clkstop_open_cmu_ebus_u_duration1 clkstop_open_cmu_ebus_u_duration1; /* offset : 0x40f4 */
	union pmu_clkstop_open_cmu_ebus_u_duration2 clkstop_open_cmu_ebus_u_duration2; /* offset : 0x40f8 */
	union pmu_clkstop_open_cmu_ebus_u_duration3 clkstop_open_cmu_ebus_u_duration3; /* offset : 0x40fc */
	union pmu_clkstop_open_cmu_ebus_d_configuration
			clkstop_open_cmu_ebus_d_configuration; /* offset : 0x4100 */
	union pmu_clkstop_open_cmu_ebus_d_status clkstop_open_cmu_ebus_d_status; /* offset : 0x4104 */
	union pmu_clkstop_open_cmu_ebus_d_option clkstop_open_cmu_ebus_d_option; /* offset : 0x4108 */
	uint32_t reserved_110;
	union pmu_clkstop_open_cmu_ebus_d_duration0 clkstop_open_cmu_ebus_d_duration0; /* offset : 0x4110 */
	union pmu_clkstop_open_cmu_ebus_d_duration1 clkstop_open_cmu_ebus_d_duration1; /* offset : 0x4114 */
	union pmu_clkstop_open_cmu_ebus_d_duration2 clkstop_open_cmu_ebus_d_duration2; /* offset : 0x4118 */
	union pmu_clkstop_open_cmu_ebus_d_duration3 clkstop_open_cmu_ebus_d_duration3; /* offset : 0x411c */
	union pmu_clkstop_open_cmu_ebus_r_configuration
			clkstop_open_cmu_ebus_r_configuration; /* offset : 0x4120 */
	union pmu_clkstop_open_cmu_ebus_r_status clkstop_open_cmu_ebus_r_status; /* offset : 0x4124 */
	union pmu_clkstop_open_cmu_ebus_r_option clkstop_open_cmu_ebus_r_option; /* offset : 0x4128 */
	uint32_t reserved_111;
	union pmu_clkstop_open_cmu_ebus_r_duration0 clkstop_open_cmu_ebus_r_duration0; /* offset : 0x4130 */
	union pmu_clkstop_open_cmu_ebus_r_duration1 clkstop_open_cmu_ebus_r_duration1; /* offset : 0x4134 */
	union pmu_clkstop_open_cmu_ebus_r_duration2 clkstop_open_cmu_ebus_r_duration2; /* offset : 0x4138 */
	union pmu_clkstop_open_cmu_ebus_r_duration3 clkstop_open_cmu_ebus_r_duration3; /* offset : 0x413c */
	uint32_t reserved_112[48];
	union pmu_cp0_configuration cp0_configuration; /* offset : 0x4200 */
	union pmu_cp0_status cp0_status; /* offset : 0x4204 */
	union pmu_cp0_option cp0_option; /* offset : 0x4208 */
	uint32_t reserved_113;
	union pmu_cp0_duration0 cp0_duration0; /* offset : 0x4210 */
	union pmu_cp0_duration1 cp0_duration1; /* offset : 0x4214 */
	union pmu_cp0_duration2 cp0_duration2; /* offset : 0x4218 */
	union pmu_cp0_duration3 cp0_duration3; /* offset : 0x421c */
	union pmu_cp1_configuration cp1_configuration; /* offset : 0x4220 */
	union pmu_cp1_status cp1_status; /* offset : 0x4224 */
	union pmu_cp1_option cp1_option; /* offset : 0x4228 */
	uint32_t reserved_114;
	union pmu_cp1_duration0 cp1_duration0; /* offset : 0x4230 */
	union pmu_cp1_duration1 cp1_duration1; /* offset : 0x4234 */
	union pmu_cp1_duration2 cp1_duration2; /* offset : 0x4238 */
	union pmu_cp1_duration3 cp1_duration3; /* offset : 0x423c */
	union pmu_pcie_configuration pcie_configuration; /* offset : 0x4240 */
	union pmu_pcie_status pcie_status; /* offset : 0x4244 */
	union pmu_pcie_option pcie_option; /* offset : 0x4248 */
	uint32_t reserved_115;
	union pmu_pcie_duration0 pcie_duration0; /* offset : 0x4250 */
	union pmu_pcie_duration1 pcie_duration1; /* offset : 0x4254 */
	union pmu_pcie_duration2 pcie_duration2; /* offset : 0x4258 */
	union pmu_pcie_duration3 pcie_duration3; /* offset : 0x425c */
	union pmu_dram_configuration dram_configuration; /* offset : 0x4260 */
	union pmu_dram_status dram_status; /* offset : 0x4264 */
	union pmu_dram_option dram_option; /* offset : 0x4268 */
	uint32_t reserved_116;
	union pmu_dram_duration0 dram_duration0; /* offset : 0x4270 */
	union pmu_dram_duration1 dram_duration1; /* offset : 0x4274 */
	union pmu_dram_duration2 dram_duration2; /* offset : 0x4278 */
	union pmu_dram_duration3 dram_duration3; /* offset : 0x427c */
	union pmu_dcl0_configuration dcl0_configuration; /* offset : 0x4280 */
	union pmu_dcl0_status dcl0_status; /* offset : 0x4284 */
	union pmu_dcl0_option dcl0_option; /* offset : 0x4288 */
	uint32_t reserved_117;
	union pmu_dcl0_duration0 dcl0_duration0; /* offset : 0x4290 */
	union pmu_dcl0_duration1 dcl0_duration1; /* offset : 0x4294 */
	union pmu_dcl0_duration2 dcl0_duration2; /* offset : 0x4298 */
	union pmu_dcl0_duration3 dcl0_duration3; /* offset : 0x429c */
	union pmu_dcl1_configuration dcl1_configuration; /* offset : 0x42a0 */
	union pmu_dcl1_status dcl1_status; /* offset : 0x42a4 */
	union pmu_dcl1_option dcl1_option; /* offset : 0x42a8 */
	uint32_t reserved_118;
	union pmu_dcl1_duration0 dcl1_duration0; /* offset : 0x42b0 */
	union pmu_dcl1_duration1 dcl1_duration1; /* offset : 0x42b4 */
	union pmu_dcl1_duration2 dcl1_duration2; /* offset : 0x42b8 */
	union pmu_dcl1_duration3 dcl1_duration3; /* offset : 0x42bc */
	union pmu_rbch00_configuration rbch00_configuration; /* offset : 0x42c0 */
	union pmu_rbch00_status rbch00_status; /* offset : 0x42c4 */
	union pmu_rbch00_option rbch00_option; /* offset : 0x42c8 */
	uint32_t reserved_119;
	union pmu_rbch00_duration0 rbch00_duration0; /* offset : 0x42d0 */
	union pmu_rbch00_duration1 rbch00_duration1; /* offset : 0x42d4 */
	union pmu_rbch00_duration2 rbch00_duration2; /* offset : 0x42d8 */
	union pmu_rbch00_duration3 rbch00_duration3; /* offset : 0x42dc */
	union pmu_rbch01_configuration rbch01_configuration; /* offset : 0x42e0 */
	union pmu_rbch01_status rbch01_status; /* offset : 0x42e4 */
	union pmu_rbch01_option rbch01_option; /* offset : 0x42e8 */
	uint32_t reserved_120;
	union pmu_rbch01_duration0 rbch01_duration0; /* offset : 0x42f0 */
	union pmu_rbch01_duration1 rbch01_duration1; /* offset : 0x42f4 */
	union pmu_rbch01_duration2 rbch01_duration2; /* offset : 0x42f8 */
	union pmu_rbch01_duration3 rbch01_duration3; /* offset : 0x42fc */
	union pmu_rbcv00_configuration rbcv00_configuration; /* offset : 0x4300 */
	union pmu_rbcv00_status rbcv00_status; /* offset : 0x4304 */
	union pmu_rbcv00_option rbcv00_option; /* offset : 0x4308 */
	uint32_t reserved_121;
	union pmu_rbcv00_duration0 rbcv00_duration0; /* offset : 0x4310 */
	union pmu_rbcv00_duration1 rbcv00_duration1; /* offset : 0x4314 */
	union pmu_rbcv00_duration2 rbcv00_duration2; /* offset : 0x4318 */
	union pmu_rbcv00_duration3 rbcv00_duration3; /* offset : 0x431c */
	union pmu_rbcv01_configuration rbcv01_configuration; /* offset : 0x4320 */
	union pmu_rbcv01_status rbcv01_status; /* offset : 0x4324 */
	union pmu_rbcv01_option rbcv01_option; /* offset : 0x4328 */
	uint32_t reserved_122;
	union pmu_rbcv01_duration0 rbcv01_duration0; /* offset : 0x4330 */
	union pmu_rbcv01_duration1 rbcv01_duration1; /* offset : 0x4334 */
	union pmu_rbcv01_duration2 rbcv01_duration2; /* offset : 0x4338 */
	union pmu_rbcv01_duration3 rbcv01_duration3; /* offset : 0x433c */
	union pmu_rbcv10_configuration rbcv10_configuration; /* offset : 0x4340 */
	union pmu_rbcv10_status rbcv10_status; /* offset : 0x4344 */
	union pmu_rbcv10_option rbcv10_option; /* offset : 0x4348 */
	uint32_t reserved_123;
	union pmu_rbcv10_duration0 rbcv10_duration0; /* offset : 0x4350 */
	union pmu_rbcv10_duration1 rbcv10_duration1; /* offset : 0x4354 */
	union pmu_rbcv10_duration2 rbcv10_duration2; /* offset : 0x4358 */
	union pmu_rbcv10_duration3 rbcv10_duration3; /* offset : 0x435c */
	union pmu_rbcv11_configuration rbcv11_configuration; /* offset : 0x4360 */
	union pmu_rbcv11_status rbcv11_status; /* offset : 0x4364 */
	union pmu_rbcv11_option rbcv11_option; /* offset : 0x4368 */
	uint32_t reserved_124;
	union pmu_rbcv11_duration0 rbcv11_duration0; /* offset : 0x4370 */
	union pmu_rbcv11_duration1 rbcv11_duration1; /* offset : 0x4374 */
	union pmu_rbcv11_duration2 rbcv11_duration2; /* offset : 0x4378 */
	union pmu_rbcv11_duration3 rbcv11_duration3; /* offset : 0x437c */
	union pmu_rot_configuration rot_configuration; /* offset : 0x4380 */
	union pmu_rot_status rot_status; /* offset : 0x4384 */
	union pmu_rot_option rot_option; /* offset : 0x4388 */
	uint32_t reserved_125;
	union pmu_rot_duration0 rot_duration0; /* offset : 0x4390 */
	union pmu_rot_duration1 rot_duration1; /* offset : 0x4394 */
	union pmu_rot_duration2 rot_duration2; /* offset : 0x4398 */
	union pmu_rot_duration3 rot_duration3; /* offset : 0x439c */
	union pmu_peri0_configuration peri0_configuration; /* offset : 0x43a0 */
	union pmu_peri0_status peri0_status; /* offset : 0x43a4 */
	union pmu_peri0_option peri0_option; /* offset : 0x43a8 */
	uint32_t reserved_126;
	union pmu_peri0_duration0 peri0_duration0; /* offset : 0x43b0 */
	union pmu_peri0_duration1 peri0_duration1; /* offset : 0x43b4 */
	union pmu_peri0_duration2 peri0_duration2; /* offset : 0x43b8 */
	union pmu_peri0_duration3 peri0_duration3; /* offset : 0x43bc */
	union pmu_peri1_configuration peri1_configuration; /* offset : 0x43c0 */
	union pmu_peri1_status peri1_status; /* offset : 0x43c4 */
	union pmu_peri1_option peri1_option; /* offset : 0x43c8 */
	uint32_t reserved_127;
	union pmu_peri1_duration0 peri1_duration0; /* offset : 0x43d0 */
	union pmu_peri1_duration1 peri1_duration1; /* offset : 0x43d4 */
	union pmu_peri1_duration2 peri1_duration2; /* offset : 0x43d8 */
	union pmu_peri1_duration3 peri1_duration3; /* offset : 0x43dc */
	union pmu_sbus_u_configuration sbus_u_configuration; /* offset : 0x43e0 */
	union pmu_sbus_u_status sbus_u_status; /* offset : 0x43e4 */
	union pmu_sbus_u_option sbus_u_option; /* offset : 0x43e8 */
	uint32_t reserved_128;
	union pmu_sbus_u_duration0 sbus_u_duration0; /* offset : 0x43f0 */
	union pmu_sbus_u_duration1 sbus_u_duration1; /* offset : 0x43f4 */
	union pmu_sbus_u_duration2 sbus_u_duration2; /* offset : 0x43f8 */
	union pmu_sbus_u_duration3 sbus_u_duration3; /* offset : 0x43fc */
	union pmu_sbus_d_configuration sbus_d_configuration; /* offset : 0x4400 */
	union pmu_sbus_d_status sbus_d_status; /* offset : 0x4404 */
	union pmu_sbus_d_option sbus_d_option; /* offset : 0x4408 */
	uint32_t reserved_129;
	union pmu_sbus_d_duration0 sbus_d_duration0; /* offset : 0x4410 */
	union pmu_sbus_d_duration1 sbus_d_duration1; /* offset : 0x4414 */
	union pmu_sbus_d_duration2 sbus_d_duration2; /* offset : 0x4418 */
	union pmu_sbus_d_duration3 sbus_d_duration3; /* offset : 0x441c */
	union pmu_sbus_l_configuration sbus_l_configuration; /* offset : 0x4420 */
	union pmu_sbus_l_status sbus_l_status; /* offset : 0x4424 */
	union pmu_sbus_l_option sbus_l_option; /* offset : 0x4428 */
	uint32_t reserved_130;
	union pmu_sbus_l_duration0 sbus_l_duration0; /* offset : 0x4430 */
	union pmu_sbus_l_duration1 sbus_l_duration1; /* offset : 0x4434 */
	union pmu_sbus_l_duration2 sbus_l_duration2; /* offset : 0x4438 */
	union pmu_sbus_l_duration3 sbus_l_duration3; /* offset : 0x443c */
	union pmu_nbus_u_configuration nbus_u_configuration; /* offset : 0x4440 */
	union pmu_nbus_u_status nbus_u_status; /* offset : 0x4444 */
	union pmu_nbus_u_option nbus_u_option; /* offset : 0x4448 */
	uint32_t reserved_131;
	union pmu_nbus_u_duration0 nbus_u_duration0; /* offset : 0x4450 */
	union pmu_nbus_u_duration1 nbus_u_duration1; /* offset : 0x4454 */
	union pmu_nbus_u_duration2 nbus_u_duration2; /* offset : 0x4458 */
	union pmu_nbus_u_duration3 nbus_u_duration3; /* offset : 0x445c */
	union pmu_nbus_d_configuration nbus_d_configuration; /* offset : 0x4460 */
	union pmu_nbus_d_status nbus_d_status; /* offset : 0x4464 */
	union pmu_nbus_d_option nbus_d_option; /* offset : 0x4468 */
	uint32_t reserved_132;
	union pmu_nbus_d_duration0 nbus_d_duration0; /* offset : 0x4470 */
	union pmu_nbus_d_duration1 nbus_d_duration1; /* offset : 0x4474 */
	union pmu_nbus_d_duration2 nbus_d_duration2; /* offset : 0x4478 */
	union pmu_nbus_d_duration3 nbus_d_duration3; /* offset : 0x447c */
	union pmu_nbus_l_configuration nbus_l_configuration; /* offset : 0x4480 */
	union pmu_nbus_l_status nbus_l_status; /* offset : 0x4484 */
	union pmu_nbus_l_option nbus_l_option; /* offset : 0x4488 */
	uint32_t reserved_133;
	union pmu_nbus_l_duration0 nbus_l_duration0; /* offset : 0x4490 */
	union pmu_nbus_l_duration1 nbus_l_duration1; /* offset : 0x4494 */
	union pmu_nbus_l_duration2 nbus_l_duration2; /* offset : 0x4498 */
	union pmu_nbus_l_duration3 nbus_l_duration3; /* offset : 0x449c */
	union pmu_wbus_u_configuration wbus_u_configuration; /* offset : 0x44a0 */
	union pmu_wbus_u_status wbus_u_status; /* offset : 0x44a4 */
	union pmu_wbus_u_option wbus_u_option; /* offset : 0x44a8 */
	uint32_t reserved_134;
	union pmu_wbus_u_duration0 wbus_u_duration0; /* offset : 0x44b0 */
	union pmu_wbus_u_duration1 wbus_u_duration1; /* offset : 0x44b4 */
	union pmu_wbus_u_duration2 wbus_u_duration2; /* offset : 0x44b8 */
	union pmu_wbus_u_duration3 wbus_u_duration3; /* offset : 0x44bc */
	union pmu_wbus_d_configuration wbus_d_configuration; /* offset : 0x44c0 */
	union pmu_wbus_d_status wbus_d_status; /* offset : 0x44c4 */
	union pmu_wbus_d_option wbus_d_option; /* offset : 0x44c8 */
	uint32_t reserved_135;
	union pmu_wbus_d_duration0 wbus_d_duration0; /* offset : 0x44d0 */
	union pmu_wbus_d_duration1 wbus_d_duration1; /* offset : 0x44d4 */
	union pmu_wbus_d_duration2 wbus_d_duration2; /* offset : 0x44d8 */
	union pmu_wbus_d_duration3 wbus_d_duration3; /* offset : 0x44dc */
	union pmu_ebus_u_configuration ebus_u_configuration; /* offset : 0x44e0 */
	union pmu_ebus_u_status ebus_u_status; /* offset : 0x44e4 */
	union pmu_ebus_u_option ebus_u_option; /* offset : 0x44e8 */
	uint32_t reserved_136;
	union pmu_ebus_u_duration0 ebus_u_duration0; /* offset : 0x44f0 */
	union pmu_ebus_u_duration1 ebus_u_duration1; /* offset : 0x44f4 */
	union pmu_ebus_u_duration2 ebus_u_duration2; /* offset : 0x44f8 */
	union pmu_ebus_u_duration3 ebus_u_duration3; /* offset : 0x44fc */
	union pmu_ebus_d_configuration ebus_d_configuration; /* offset : 0x4500 */
	union pmu_ebus_d_status ebus_d_status; /* offset : 0x4504 */
	union pmu_ebus_d_option ebus_d_option; /* offset : 0x4508 */
	uint32_t reserved_137;
	union pmu_ebus_d_duration0 ebus_d_duration0; /* offset : 0x4510 */
	union pmu_ebus_d_duration1 ebus_d_duration1; /* offset : 0x4514 */
	union pmu_ebus_d_duration2 ebus_d_duration2; /* offset : 0x4518 */
	union pmu_ebus_d_duration3 ebus_d_duration3; /* offset : 0x451c */
	union pmu_ebus_r_configuration ebus_r_configuration; /* offset : 0x4520 */
	union pmu_ebus_r_status ebus_r_status; /* offset : 0x4524 */
	union pmu_ebus_r_option ebus_r_option; /* offset : 0x4528 */
	uint32_t reserved_138;
	union pmu_ebus_r_duration0 ebus_r_duration0; /* offset : 0x4530 */
	union pmu_ebus_r_duration1 ebus_r_duration1; /* offset : 0x4534 */
	union pmu_ebus_r_duration2 ebus_r_duration2; /* offset : 0x4538 */
	union pmu_ebus_r_duration3 ebus_r_duration3; /* offset : 0x453c */
	uint32_t reserved_139[48];
	union pmu_force_autoclkgate_cmu_cp0_configuration
			force_autoclkgate_cmu_cp0_configuration; /* offset : 0x4600 */
	union pmu_force_autoclkgate_cmu_cp0_status force_autoclkgate_cmu_cp0_status; /* offset : 0x4604 */
	union pmu_force_autoclkgate_cmu_cp0_option force_autoclkgate_cmu_cp0_option; /* offset : 0x4608 */
	uint32_t reserved_140;
	union pmu_force_autoclkgate_cmu_cp0_duration0
			force_autoclkgate_cmu_cp0_duration0; /* offset : 0x4610 */
	union pmu_force_autoclkgate_cmu_cp0_duration1
			force_autoclkgate_cmu_cp0_duration1; /* offset : 0x4614 */
	union pmu_force_autoclkgate_cmu_cp0_duration2
			force_autoclkgate_cmu_cp0_duration2; /* offset : 0x4618 */
	union pmu_force_autoclkgate_cmu_cp0_duration3
			force_autoclkgate_cmu_cp0_duration3; /* offset : 0x461c */
	union pmu_force_autoclkgate_cmu_cp1_configuration
			force_autoclkgate_cmu_cp1_configuration; /* offset : 0x4620 */
	union pmu_force_autoclkgate_cmu_cp1_status force_autoclkgate_cmu_cp1_status; /* offset : 0x4624 */
	union pmu_force_autoclkgate_cmu_cp1_option force_autoclkgate_cmu_cp1_option; /* offset : 0x4628 */
	uint32_t reserved_141;
	union pmu_force_autoclkgate_cmu_cp1_duration0
			force_autoclkgate_cmu_cp1_duration0; /* offset : 0x4630 */
	union pmu_force_autoclkgate_cmu_cp1_duration1
			force_autoclkgate_cmu_cp1_duration1; /* offset : 0x4634 */
	union pmu_force_autoclkgate_cmu_cp1_duration2
			force_autoclkgate_cmu_cp1_duration2; /* offset : 0x4638 */
	union pmu_force_autoclkgate_cmu_cp1_duration3
			force_autoclkgate_cmu_cp1_duration3; /* offset : 0x463c */
	union pmu_force_autoclkgate_cmu_pcie_configuration
			force_autoclkgate_cmu_pcie_configuration; /* offset : 0x4640 */
	union pmu_force_autoclkgate_cmu_pcie_status force_autoclkgate_cmu_pcie_status; /* offset : 0x4644 */
	union pmu_force_autoclkgate_cmu_pcie_option force_autoclkgate_cmu_pcie_option; /* offset : 0x4648 */
	uint32_t reserved_142;
	union pmu_force_autoclkgate_cmu_pcie_duration0
			force_autoclkgate_cmu_pcie_duration0; /* offset : 0x4650 */
	union pmu_force_autoclkgate_cmu_pcie_duration1
			force_autoclkgate_cmu_pcie_duration1; /* offset : 0x4654 */
	union pmu_force_autoclkgate_cmu_pcie_duration2
			force_autoclkgate_cmu_pcie_duration2; /* offset : 0x4658 */
	union pmu_force_autoclkgate_cmu_pcie_duration3
			force_autoclkgate_cmu_pcie_duration3; /* offset : 0x465c */
	union pmu_force_autoclkgate_cmu_dram_configuration
			force_autoclkgate_cmu_dram_configuration; /* offset : 0x4660 */
	union pmu_force_autoclkgate_cmu_dram_status force_autoclkgate_cmu_dram_status; /* offset : 0x4664 */
	union pmu_force_autoclkgate_cmu_dram_option force_autoclkgate_cmu_dram_option; /* offset : 0x4668 */
	uint32_t reserved_143;
	union pmu_force_autoclkgate_cmu_dram_duration0
			force_autoclkgate_cmu_dram_duration0; /* offset : 0x4670 */
	union pmu_force_autoclkgate_cmu_dram_duration1
			force_autoclkgate_cmu_dram_duration1; /* offset : 0x4674 */
	union pmu_force_autoclkgate_cmu_dram_duration2
			force_autoclkgate_cmu_dram_duration2; /* offset : 0x4678 */
	union pmu_force_autoclkgate_cmu_dram_duration3
			force_autoclkgate_cmu_dram_duration3; /* offset : 0x467c */
	union pmu_force_autoclkgate_cmu_dcl0_configuration
			force_autoclkgate_cmu_dcl0_configuration; /* offset : 0x4680 */
	union pmu_force_autoclkgate_cmu_dcl0_status force_autoclkgate_cmu_dcl0_status; /* offset : 0x4684 */
	union pmu_force_autoclkgate_cmu_dcl0_option force_autoclkgate_cmu_dcl0_option; /* offset : 0x4688 */
	uint32_t reserved_144;
	union pmu_force_autoclkgate_cmu_dcl0_duration0
			force_autoclkgate_cmu_dcl0_duration0; /* offset : 0x4690 */
	union pmu_force_autoclkgate_cmu_dcl0_duration1
			force_autoclkgate_cmu_dcl0_duration1; /* offset : 0x4694 */
	union pmu_force_autoclkgate_cmu_dcl0_duration2
			force_autoclkgate_cmu_dcl0_duration2; /* offset : 0x4698 */
	union pmu_force_autoclkgate_cmu_dcl0_duration3
			force_autoclkgate_cmu_dcl0_duration3; /* offset : 0x469c */
	union pmu_force_autoclkgate_cmu_dcl1_configuration
			force_autoclkgate_cmu_dcl1_configuration; /* offset : 0x46a0 */
	union pmu_force_autoclkgate_cmu_dcl1_status force_autoclkgate_cmu_dcl1_status; /* offset : 0x46a4 */
	union pmu_force_autoclkgate_cmu_dcl1_option force_autoclkgate_cmu_dcl1_option; /* offset : 0x46a8 */
	uint32_t reserved_145;
	union pmu_force_autoclkgate_cmu_dcl1_duration0
			force_autoclkgate_cmu_dcl1_duration0; /* offset : 0x46b0 */
	union pmu_force_autoclkgate_cmu_dcl1_duration1
			force_autoclkgate_cmu_dcl1_duration1; /* offset : 0x46b4 */
	union pmu_force_autoclkgate_cmu_dcl1_duration2
			force_autoclkgate_cmu_dcl1_duration2; /* offset : 0x46b8 */
	union pmu_force_autoclkgate_cmu_dcl1_duration3
			force_autoclkgate_cmu_dcl1_duration3; /* offset : 0x46bc */
	union pmu_force_autoclkgate_cmu_rbch00_configuration
			force_autoclkgate_cmu_rbch00_configuration; /* offset : 0x46c0 */
	union pmu_force_autoclkgate_cmu_rbch00_status
			force_autoclkgate_cmu_rbch00_status; /* offset : 0x46c4 */
	union pmu_force_autoclkgate_cmu_rbch00_option
			force_autoclkgate_cmu_rbch00_option; /* offset : 0x46c8 */
	uint32_t reserved_146;
	union pmu_force_autoclkgate_cmu_rbch00_duration0
			force_autoclkgate_cmu_rbch00_duration0; /* offset : 0x46d0 */
	union pmu_force_autoclkgate_cmu_rbch00_duration1
			force_autoclkgate_cmu_rbch00_duration1; /* offset : 0x46d4 */
	union pmu_force_autoclkgate_cmu_rbch00_duration2
			force_autoclkgate_cmu_rbch00_duration2; /* offset : 0x46d8 */
	union pmu_force_autoclkgate_cmu_rbch00_duration3
			force_autoclkgate_cmu_rbch00_duration3; /* offset : 0x46dc */
	union pmu_force_autoclkgate_cmu_rbch01_configuration
			force_autoclkgate_cmu_rbch01_configuration; /* offset : 0x46e0 */
	union pmu_force_autoclkgate_cmu_rbch01_status
			force_autoclkgate_cmu_rbch01_status; /* offset : 0x46e4 */
	union pmu_force_autoclkgate_cmu_rbch01_option
			force_autoclkgate_cmu_rbch01_option; /* offset : 0x46e8 */
	uint32_t reserved_147;
	union pmu_force_autoclkgate_cmu_rbch01_duration0
			force_autoclkgate_cmu_rbch01_duration0; /* offset : 0x46f0 */
	union pmu_force_autoclkgate_cmu_rbch01_duration1
			force_autoclkgate_cmu_rbch01_duration1; /* offset : 0x46f4 */
	union pmu_force_autoclkgate_cmu_rbch01_duration2
			force_autoclkgate_cmu_rbch01_duration2; /* offset : 0x46f8 */
	union pmu_force_autoclkgate_cmu_rbch01_duration3
			force_autoclkgate_cmu_rbch01_duration3; /* offset : 0x46fc */
	union pmu_force_autoclkgate_cmu_rbcv00_configuration
			force_autoclkgate_cmu_rbcv00_configuration; /* offset : 0x4700 */
	union pmu_force_autoclkgate_cmu_rbcv00_status
			force_autoclkgate_cmu_rbcv00_status; /* offset : 0x4704 */
	union pmu_force_autoclkgate_cmu_rbcv00_option
			force_autoclkgate_cmu_rbcv00_option; /* offset : 0x4708 */
	uint32_t reserved_148;
	union pmu_force_autoclkgate_cmu_rbcv00_duration0
			force_autoclkgate_cmu_rbcv00_duration0; /* offset : 0x4710 */
	union pmu_force_autoclkgate_cmu_rbcv00_duration1
			force_autoclkgate_cmu_rbcv00_duration1; /* offset : 0x4714 */
	union pmu_force_autoclkgate_cmu_rbcv00_duration2
			force_autoclkgate_cmu_rbcv00_duration2; /* offset : 0x4718 */
	union pmu_force_autoclkgate_cmu_rbcv00_duration3
			force_autoclkgate_cmu_rbcv00_duration3; /* offset : 0x471c */
	union pmu_force_autoclkgate_cmu_rbcv01_configuration
			force_autoclkgate_cmu_rbcv01_configuration; /* offset : 0x4720 */
	union pmu_force_autoclkgate_cmu_rbcv01_status
			force_autoclkgate_cmu_rbcv01_status; /* offset : 0x4724 */
	union pmu_force_autoclkgate_cmu_rbcv01_option
			force_autoclkgate_cmu_rbcv01_option; /* offset : 0x4728 */
	uint32_t reserved_149;
	union pmu_force_autoclkgate_cmu_rbcv01_duration0
			force_autoclkgate_cmu_rbcv01_duration0; /* offset : 0x4730 */
	union pmu_force_autoclkgate_cmu_rbcv01_duration1
			force_autoclkgate_cmu_rbcv01_duration1; /* offset : 0x4734 */
	union pmu_force_autoclkgate_cmu_rbcv01_duration2
			force_autoclkgate_cmu_rbcv01_duration2; /* offset : 0x4738 */
	union pmu_force_autoclkgate_cmu_rbcv01_duration3
			force_autoclkgate_cmu_rbcv01_duration3; /* offset : 0x473c */
	union pmu_force_autoclkgate_cmu_rbcv10_configuration
			force_autoclkgate_cmu_rbcv10_configuration; /* offset : 0x4740 */
	union pmu_force_autoclkgate_cmu_rbcv10_status
			force_autoclkgate_cmu_rbcv10_status; /* offset : 0x4744 */
	union pmu_force_autoclkgate_cmu_rbcv10_option
			force_autoclkgate_cmu_rbcv10_option; /* offset : 0x4748 */
	uint32_t reserved_150;
	union pmu_force_autoclkgate_cmu_rbcv10_duration0
			force_autoclkgate_cmu_rbcv10_duration0; /* offset : 0x4750 */
	union pmu_force_autoclkgate_cmu_rbcv10_duration1
			force_autoclkgate_cmu_rbcv10_duration1; /* offset : 0x4754 */
	union pmu_force_autoclkgate_cmu_rbcv10_duration2
			force_autoclkgate_cmu_rbcv10_duration2; /* offset : 0x4758 */
	union pmu_force_autoclkgate_cmu_rbcv10_duration3
			force_autoclkgate_cmu_rbcv10_duration3; /* offset : 0x475c */
	union pmu_force_autoclkgate_cmu_rbcv11_configuration
			force_autoclkgate_cmu_rbcv11_configuration; /* offset : 0x4760 */
	union pmu_force_autoclkgate_cmu_rbcv11_status
			force_autoclkgate_cmu_rbcv11_status; /* offset : 0x4764 */
	union pmu_force_autoclkgate_cmu_rbcv11_option
			force_autoclkgate_cmu_rbcv11_option; /* offset : 0x4768 */
	uint32_t reserved_151;
	union pmu_force_autoclkgate_cmu_rbcv11_duration0
			force_autoclkgate_cmu_rbcv11_duration0; /* offset : 0x4770 */
	union pmu_force_autoclkgate_cmu_rbcv11_duration1
			force_autoclkgate_cmu_rbcv11_duration1; /* offset : 0x4774 */
	union pmu_force_autoclkgate_cmu_rbcv11_duration2
			force_autoclkgate_cmu_rbcv11_duration2; /* offset : 0x4778 */
	union pmu_force_autoclkgate_cmu_rbcv11_duration3
			force_autoclkgate_cmu_rbcv11_duration3; /* offset : 0x477c */
	union pmu_force_autoclkgate_cmu_rot_configuration
			force_autoclkgate_cmu_rot_configuration; /* offset : 0x4780 */
	union pmu_force_autoclkgate_cmu_rot_status force_autoclkgate_cmu_rot_status; /* offset : 0x4784 */
	union pmu_force_autoclkgate_cmu_rot_option force_autoclkgate_cmu_rot_option; /* offset : 0x4788 */
	uint32_t reserved_152;
	union pmu_force_autoclkgate_cmu_rot_duration0
			force_autoclkgate_cmu_rot_duration0; /* offset : 0x4790 */
	union pmu_force_autoclkgate_cmu_rot_duration1
			force_autoclkgate_cmu_rot_duration1; /* offset : 0x4794 */
	union pmu_force_autoclkgate_cmu_rot_duration2
			force_autoclkgate_cmu_rot_duration2; /* offset : 0x4798 */
	union pmu_force_autoclkgate_cmu_rot_duration3
			force_autoclkgate_cmu_rot_duration3; /* offset : 0x479c */
	union pmu_force_autoclkgate_cmu_peri0_configuration
			force_autoclkgate_cmu_peri0_configuration; /* offset : 0x47a0 */
	union pmu_force_autoclkgate_cmu_peri0_status force_autoclkgate_cmu_peri0_status; /* offset : 0x47a4 */
	union pmu_force_autoclkgate_cmu_peri0_option force_autoclkgate_cmu_peri0_option; /* offset : 0x47a8 */
	uint32_t reserved_153;
	union pmu_force_autoclkgate_cmu_peri0_duration0
			force_autoclkgate_cmu_peri0_duration0; /* offset : 0x47b0 */
	union pmu_force_autoclkgate_cmu_peri0_duration1
			force_autoclkgate_cmu_peri0_duration1; /* offset : 0x47b4 */
	union pmu_force_autoclkgate_cmu_peri0_duration2
			force_autoclkgate_cmu_peri0_duration2; /* offset : 0x47b8 */
	union pmu_force_autoclkgate_cmu_peri0_duration3
			force_autoclkgate_cmu_peri0_duration3; /* offset : 0x47bc */
	union pmu_force_autoclkgate_cmu_peri1_configuration
			force_autoclkgate_cmu_peri1_configuration; /* offset : 0x47c0 */
	union pmu_force_autoclkgate_cmu_peri1_status force_autoclkgate_cmu_peri1_status; /* offset : 0x47c4 */
	union pmu_force_autoclkgate_cmu_peri1_option force_autoclkgate_cmu_peri1_option; /* offset : 0x47c8 */
	uint32_t reserved_154;
	union pmu_force_autoclkgate_cmu_peri1_duration0
			force_autoclkgate_cmu_peri1_duration0; /* offset : 0x47d0 */
	union pmu_force_autoclkgate_cmu_peri1_duration1
			force_autoclkgate_cmu_peri1_duration1; /* offset : 0x47d4 */
	union pmu_force_autoclkgate_cmu_peri1_duration2
			force_autoclkgate_cmu_peri1_duration2; /* offset : 0x47d8 */
	union pmu_force_autoclkgate_cmu_peri1_duration3
			force_autoclkgate_cmu_peri1_duration3; /* offset : 0x47dc */
	union pmu_force_autoclkgate_cmu_sbus_u_configuration
			force_autoclkgate_cmu_sbus_u_configuration; /* offset : 0x47e0 */
	union pmu_force_autoclkgate_cmu_sbus_u_status
			force_autoclkgate_cmu_sbus_u_status; /* offset : 0x47e4 */
	union pmu_force_autoclkgate_cmu_sbus_u_option
			force_autoclkgate_cmu_sbus_u_option; /* offset : 0x47e8 */
	uint32_t reserved_155;
	union pmu_force_autoclkgate_cmu_sbus_u_duration0
			force_autoclkgate_cmu_sbus_u_duration0; /* offset : 0x47f0 */
	union pmu_force_autoclkgate_cmu_sbus_u_duration1
			force_autoclkgate_cmu_sbus_u_duration1; /* offset : 0x47f4 */
	union pmu_force_autoclkgate_cmu_sbus_u_duration2
			force_autoclkgate_cmu_sbus_u_duration2; /* offset : 0x47f8 */
	union pmu_force_autoclkgate_cmu_sbus_u_duration3
			force_autoclkgate_cmu_sbus_u_duration3; /* offset : 0x47fc */
	union pmu_force_autoclkgate_cmu_sbus_d_configuration
			force_autoclkgate_cmu_sbus_d_configuration; /* offset : 0x4800 */
	union pmu_force_autoclkgate_cmu_sbus_d_status
			force_autoclkgate_cmu_sbus_d_status; /* offset : 0x4804 */
	union pmu_force_autoclkgate_cmu_sbus_d_option
			force_autoclkgate_cmu_sbus_d_option; /* offset : 0x4808 */
	uint32_t reserved_156;
	union pmu_force_autoclkgate_cmu_sbus_d_duration0
			force_autoclkgate_cmu_sbus_d_duration0; /* offset : 0x4810 */
	union pmu_force_autoclkgate_cmu_sbus_d_duration1
			force_autoclkgate_cmu_sbus_d_duration1; /* offset : 0x4814 */
	union pmu_force_autoclkgate_cmu_sbus_d_duration2
			force_autoclkgate_cmu_sbus_d_duration2; /* offset : 0x4818 */
	union pmu_force_autoclkgate_cmu_sbus_d_duration3
			force_autoclkgate_cmu_sbus_d_duration3; /* offset : 0x481c */
	union pmu_force_autoclkgate_cmu_sbus_l_configuration
			force_autoclkgate_cmu_sbus_l_configuration; /* offset : 0x4820 */
	union pmu_force_autoclkgate_cmu_sbus_l_status
			force_autoclkgate_cmu_sbus_l_status; /* offset : 0x4824 */
	union pmu_force_autoclkgate_cmu_sbus_l_option
			force_autoclkgate_cmu_sbus_l_option; /* offset : 0x4828 */
	uint32_t reserved_157;
	union pmu_force_autoclkgate_cmu_sbus_l_duration0
			force_autoclkgate_cmu_sbus_l_duration0; /* offset : 0x4830 */
	union pmu_force_autoclkgate_cmu_sbus_l_duration1
			force_autoclkgate_cmu_sbus_l_duration1; /* offset : 0x4834 */
	union pmu_force_autoclkgate_cmu_sbus_l_duration2
			force_autoclkgate_cmu_sbus_l_duration2; /* offset : 0x4838 */
	union pmu_force_autoclkgate_cmu_sbus_l_duration3
			force_autoclkgate_cmu_sbus_l_duration3; /* offset : 0x483c */
	union pmu_force_autoclkgate_cmu_nbus_u_configuration
			force_autoclkgate_cmu_nbus_u_configuration; /* offset : 0x4840 */
	union pmu_force_autoclkgate_cmu_nbus_u_status
			force_autoclkgate_cmu_nbus_u_status; /* offset : 0x4844 */
	union pmu_force_autoclkgate_cmu_nbus_u_option
			force_autoclkgate_cmu_nbus_u_option; /* offset : 0x4848 */
	uint32_t reserved_158;
	union pmu_force_autoclkgate_cmu_nbus_u_duration0
			force_autoclkgate_cmu_nbus_u_duration0; /* offset : 0x4850 */
	union pmu_force_autoclkgate_cmu_nbus_u_duration1
			force_autoclkgate_cmu_nbus_u_duration1; /* offset : 0x4854 */
	union pmu_force_autoclkgate_cmu_nbus_u_duration2
			force_autoclkgate_cmu_nbus_u_duration2; /* offset : 0x4858 */
	union pmu_force_autoclkgate_cmu_nbus_u_duration3
			force_autoclkgate_cmu_nbus_u_duration3; /* offset : 0x485c */
	union pmu_force_autoclkgate_cmu_nbus_d_configuration
			force_autoclkgate_cmu_nbus_d_configuration; /* offset : 0x4860 */
	union pmu_force_autoclkgate_cmu_nbus_d_status
			force_autoclkgate_cmu_nbus_d_status; /* offset : 0x4864 */
	union pmu_force_autoclkgate_cmu_nbus_d_option
			force_autoclkgate_cmu_nbus_d_option; /* offset : 0x4868 */
	uint32_t reserved_159;
	union pmu_force_autoclkgate_cmu_nbus_d_duration0
			force_autoclkgate_cmu_nbus_d_duration0; /* offset : 0x4870 */
	union pmu_force_autoclkgate_cmu_nbus_d_duration1
			force_autoclkgate_cmu_nbus_d_duration1; /* offset : 0x4874 */
	union pmu_force_autoclkgate_cmu_nbus_d_duration2
			force_autoclkgate_cmu_nbus_d_duration2; /* offset : 0x4878 */
	union pmu_force_autoclkgate_cmu_nbus_d_duration3
			force_autoclkgate_cmu_nbus_d_duration3; /* offset : 0x487c */
	union pmu_force_autoclkgate_cmu_nbus_l_configuration
			force_autoclkgate_cmu_nbus_l_configuration; /* offset : 0x4880 */
	union pmu_force_autoclkgate_cmu_nbus_l_status
			force_autoclkgate_cmu_nbus_l_status; /* offset : 0x4884 */
	union pmu_force_autoclkgate_cmu_nbus_l_option
			force_autoclkgate_cmu_nbus_l_option; /* offset : 0x4888 */
	uint32_t reserved_160;
	union pmu_force_autoclkgate_cmu_nbus_l_duration0
			force_autoclkgate_cmu_nbus_l_duration0; /* offset : 0x4890 */
	union pmu_force_autoclkgate_cmu_nbus_l_duration1
			force_autoclkgate_cmu_nbus_l_duration1; /* offset : 0x4894 */
	union pmu_force_autoclkgate_cmu_nbus_l_duration2
			force_autoclkgate_cmu_nbus_l_duration2; /* offset : 0x4898 */
	union pmu_force_autoclkgate_cmu_nbus_l_duration3
			force_autoclkgate_cmu_nbus_l_duration3; /* offset : 0x489c */
	union pmu_force_autoclkgate_cmu_wbus_u_configuration
			force_autoclkgate_cmu_wbus_u_configuration; /* offset : 0x48a0 */
	union pmu_force_autoclkgate_cmu_wbus_u_status
			force_autoclkgate_cmu_wbus_u_status; /* offset : 0x48a4 */
	union pmu_force_autoclkgate_cmu_wbus_u_option
			force_autoclkgate_cmu_wbus_u_option; /* offset : 0x48a8 */
	uint32_t reserved_161;
	union pmu_force_autoclkgate_cmu_wbus_u_duration0
			force_autoclkgate_cmu_wbus_u_duration0; /* offset : 0x48b0 */
	union pmu_force_autoclkgate_cmu_wbus_u_duration1
			force_autoclkgate_cmu_wbus_u_duration1; /* offset : 0x48b4 */
	union pmu_force_autoclkgate_cmu_wbus_u_duration2
			force_autoclkgate_cmu_wbus_u_duration2; /* offset : 0x48b8 */
	union pmu_force_autoclkgate_cmu_wbus_u_duration3
			force_autoclkgate_cmu_wbus_u_duration3; /* offset : 0x48bc */
	union pmu_force_autoclkgate_cmu_wbus_d_configuration
			force_autoclkgate_cmu_wbus_d_configuration; /* offset : 0x48c0 */
	union pmu_force_autoclkgate_cmu_wbus_d_status
			force_autoclkgate_cmu_wbus_d_status; /* offset : 0x48c4 */
	union pmu_force_autoclkgate_cmu_wbus_d_option
			force_autoclkgate_cmu_wbus_d_option; /* offset : 0x48c8 */
	uint32_t reserved_162;
	union pmu_force_autoclkgate_cmu_wbus_d_duration0
			force_autoclkgate_cmu_wbus_d_duration0; /* offset : 0x48d0 */
	union pmu_force_autoclkgate_cmu_wbus_d_duration1
			force_autoclkgate_cmu_wbus_d_duration1; /* offset : 0x48d4 */
	union pmu_force_autoclkgate_cmu_wbus_d_duration2
			force_autoclkgate_cmu_wbus_d_duration2; /* offset : 0x48d8 */
	union pmu_force_autoclkgate_cmu_wbus_d_duration3
			force_autoclkgate_cmu_wbus_d_duration3; /* offset : 0x48dc */
	union pmu_force_autoclkgate_cmu_ebus_u_configuration
			force_autoclkgate_cmu_ebus_u_configuration; /* offset : 0x48e0 */
	union pmu_force_autoclkgate_cmu_ebus_u_status
			force_autoclkgate_cmu_ebus_u_status; /* offset : 0x48e4 */
	union pmu_force_autoclkgate_cmu_ebus_u_option
			force_autoclkgate_cmu_ebus_u_option; /* offset : 0x48e8 */
	uint32_t reserved_163;
	union pmu_force_autoclkgate_cmu_ebus_u_duration0
			force_autoclkgate_cmu_ebus_u_duration0; /* offset : 0x48f0 */
	union pmu_force_autoclkgate_cmu_ebus_u_duration1
			force_autoclkgate_cmu_ebus_u_duration1; /* offset : 0x48f4 */
	union pmu_force_autoclkgate_cmu_ebus_u_duration2
			force_autoclkgate_cmu_ebus_u_duration2; /* offset : 0x48f8 */
	union pmu_force_autoclkgate_cmu_ebus_u_duration3
			force_autoclkgate_cmu_ebus_u_duration3; /* offset : 0x48fc */
	union pmu_force_autoclkgate_cmu_ebus_d_configuration
			force_autoclkgate_cmu_ebus_d_configuration; /* offset : 0x4900 */
	union pmu_force_autoclkgate_cmu_ebus_d_status
			force_autoclkgate_cmu_ebus_d_status; /* offset : 0x4904 */
	union pmu_force_autoclkgate_cmu_ebus_d_option
			force_autoclkgate_cmu_ebus_d_option; /* offset : 0x4908 */
	uint32_t reserved_164;
	union pmu_force_autoclkgate_cmu_ebus_d_duration0
			force_autoclkgate_cmu_ebus_d_duration0; /* offset : 0x4910 */
	union pmu_force_autoclkgate_cmu_ebus_d_duration1
			force_autoclkgate_cmu_ebus_d_duration1; /* offset : 0x4914 */
	union pmu_force_autoclkgate_cmu_ebus_d_duration2
			force_autoclkgate_cmu_ebus_d_duration2; /* offset : 0x4918 */
	union pmu_force_autoclkgate_cmu_ebus_d_duration3
			force_autoclkgate_cmu_ebus_d_duration3; /* offset : 0x491c */
	union pmu_force_autoclkgate_cmu_ebus_r_configuration
			force_autoclkgate_cmu_ebus_r_configuration; /* offset : 0x4920 */
	union pmu_force_autoclkgate_cmu_ebus_r_status
			force_autoclkgate_cmu_ebus_r_status; /* offset : 0x4924 */
	union pmu_force_autoclkgate_cmu_ebus_r_option
			force_autoclkgate_cmu_ebus_r_option; /* offset : 0x4928 */
	uint32_t reserved_165;
	union pmu_force_autoclkgate_cmu_ebus_r_duration0
			force_autoclkgate_cmu_ebus_r_duration0; /* offset : 0x4930 */
	union pmu_force_autoclkgate_cmu_ebus_r_duration1
			force_autoclkgate_cmu_ebus_r_duration1; /* offset : 0x4934 */
	union pmu_force_autoclkgate_cmu_ebus_r_duration2
			force_autoclkgate_cmu_ebus_r_duration2; /* offset : 0x4938 */
	union pmu_force_autoclkgate_cmu_ebus_r_duration3
			force_autoclkgate_cmu_ebus_r_duration3; /* offset : 0x493c */
	uint32_t reserved_166[48];
	union pmu_clkstop_cmu_cp0_configuration clkstop_cmu_cp0_configuration; /* offset : 0x4a00 */
	union pmu_clkstop_cmu_cp0_status clkstop_cmu_cp0_status; /* offset : 0x4a04 */
	union pmu_clkstop_cmu_cp0_option clkstop_cmu_cp0_option; /* offset : 0x4a08 */
	uint32_t reserved_167;
	union pmu_clkstop_cmu_cp0_duration0 clkstop_cmu_cp0_duration0; /* offset : 0x4a10 */
	union pmu_clkstop_cmu_cp0_duration1 clkstop_cmu_cp0_duration1; /* offset : 0x4a14 */
	union pmu_clkstop_cmu_cp0_duration2 clkstop_cmu_cp0_duration2; /* offset : 0x4a18 */
	union pmu_clkstop_cmu_cp0_duration3 clkstop_cmu_cp0_duration3; /* offset : 0x4a1c */
	union pmu_clkstop_cmu_cp1_configuration clkstop_cmu_cp1_configuration; /* offset : 0x4a20 */
	union pmu_clkstop_cmu_cp1_status clkstop_cmu_cp1_status; /* offset : 0x4a24 */
	union pmu_clkstop_cmu_cp1_option clkstop_cmu_cp1_option; /* offset : 0x4a28 */
	uint32_t reserved_168;
	union pmu_clkstop_cmu_cp1_duration0 clkstop_cmu_cp1_duration0; /* offset : 0x4a30 */
	union pmu_clkstop_cmu_cp1_duration1 clkstop_cmu_cp1_duration1; /* offset : 0x4a34 */
	union pmu_clkstop_cmu_cp1_duration2 clkstop_cmu_cp1_duration2; /* offset : 0x4a38 */
	union pmu_clkstop_cmu_cp1_duration3 clkstop_cmu_cp1_duration3; /* offset : 0x4a3c */
	union pmu_clkstop_cmu_pcie_configuration clkstop_cmu_pcie_configuration; /* offset : 0x4a40 */
	union pmu_clkstop_cmu_pcie_status clkstop_cmu_pcie_status; /* offset : 0x4a44 */
	union pmu_clkstop_cmu_pcie_option clkstop_cmu_pcie_option; /* offset : 0x4a48 */
	uint32_t reserved_169;
	union pmu_clkstop_cmu_pcie_duration0 clkstop_cmu_pcie_duration0; /* offset : 0x4a50 */
	union pmu_clkstop_cmu_pcie_duration1 clkstop_cmu_pcie_duration1; /* offset : 0x4a54 */
	union pmu_clkstop_cmu_pcie_duration2 clkstop_cmu_pcie_duration2; /* offset : 0x4a58 */
	union pmu_clkstop_cmu_pcie_duration3 clkstop_cmu_pcie_duration3; /* offset : 0x4a5c */
	union pmu_clkstop_cmu_dram_configuration clkstop_cmu_dram_configuration; /* offset : 0x4a60 */
	union pmu_clkstop_cmu_dram_status clkstop_cmu_dram_status; /* offset : 0x4a64 */
	union pmu_clkstop_cmu_dram_option clkstop_cmu_dram_option; /* offset : 0x4a68 */
	uint32_t reserved_170;
	union pmu_clkstop_cmu_dram_duration0 clkstop_cmu_dram_duration0; /* offset : 0x4a70 */
	union pmu_clkstop_cmu_dram_duration1 clkstop_cmu_dram_duration1; /* offset : 0x4a74 */
	union pmu_clkstop_cmu_dram_duration2 clkstop_cmu_dram_duration2; /* offset : 0x4a78 */
	union pmu_clkstop_cmu_dram_duration3 clkstop_cmu_dram_duration3; /* offset : 0x4a7c */
	union pmu_clkstop_cmu_dcl0_configuration clkstop_cmu_dcl0_configuration; /* offset : 0x4a80 */
	union pmu_clkstop_cmu_dcl0_status clkstop_cmu_dcl0_status; /* offset : 0x4a84 */
	union pmu_clkstop_cmu_dcl0_option clkstop_cmu_dcl0_option; /* offset : 0x4a88 */
	uint32_t reserved_171;
	union pmu_clkstop_cmu_dcl0_duration0 clkstop_cmu_dcl0_duration0; /* offset : 0x4a90 */
	union pmu_clkstop_cmu_dcl0_duration1 clkstop_cmu_dcl0_duration1; /* offset : 0x4a94 */
	union pmu_clkstop_cmu_dcl0_duration2 clkstop_cmu_dcl0_duration2; /* offset : 0x4a98 */
	union pmu_clkstop_cmu_dcl0_duration3 clkstop_cmu_dcl0_duration3; /* offset : 0x4a9c */
	union pmu_clkstop_cmu_dcl1_configuration clkstop_cmu_dcl1_configuration; /* offset : 0x4aa0 */
	union pmu_clkstop_cmu_dcl1_status clkstop_cmu_dcl1_status; /* offset : 0x4aa4 */
	union pmu_clkstop_cmu_dcl1_option clkstop_cmu_dcl1_option; /* offset : 0x4aa8 */
	uint32_t reserved_172;
	union pmu_clkstop_cmu_dcl1_duration0 clkstop_cmu_dcl1_duration0; /* offset : 0x4ab0 */
	union pmu_clkstop_cmu_dcl1_duration1 clkstop_cmu_dcl1_duration1; /* offset : 0x4ab4 */
	union pmu_clkstop_cmu_dcl1_duration2 clkstop_cmu_dcl1_duration2; /* offset : 0x4ab8 */
	union pmu_clkstop_cmu_dcl1_duration3 clkstop_cmu_dcl1_duration3; /* offset : 0x4abc */
	union pmu_clkstop_cmu_rbch00_configuration clkstop_cmu_rbch00_configuration; /* offset : 0x4ac0 */
	union pmu_clkstop_cmu_rbch00_status clkstop_cmu_rbch00_status; /* offset : 0x4ac4 */
	union pmu_clkstop_cmu_rbch00_option clkstop_cmu_rbch00_option; /* offset : 0x4ac8 */
	uint32_t reserved_173;
	union pmu_clkstop_cmu_rbch00_duration0 clkstop_cmu_rbch00_duration0; /* offset : 0x4ad0 */
	union pmu_clkstop_cmu_rbch00_duration1 clkstop_cmu_rbch00_duration1; /* offset : 0x4ad4 */
	union pmu_clkstop_cmu_rbch00_duration2 clkstop_cmu_rbch00_duration2; /* offset : 0x4ad8 */
	union pmu_clkstop_cmu_rbch00_duration3 clkstop_cmu_rbch00_duration3; /* offset : 0x4adc */
	union pmu_clkstop_cmu_rbch01_configuration clkstop_cmu_rbch01_configuration; /* offset : 0x4ae0 */
	union pmu_clkstop_cmu_rbch01_status clkstop_cmu_rbch01_status; /* offset : 0x4ae4 */
	union pmu_clkstop_cmu_rbch01_option clkstop_cmu_rbch01_option; /* offset : 0x4ae8 */
	uint32_t reserved_174;
	union pmu_clkstop_cmu_rbch01_duration0 clkstop_cmu_rbch01_duration0; /* offset : 0x4af0 */
	union pmu_clkstop_cmu_rbch01_duration1 clkstop_cmu_rbch01_duration1; /* offset : 0x4af4 */
	union pmu_clkstop_cmu_rbch01_duration2 clkstop_cmu_rbch01_duration2; /* offset : 0x4af8 */
	union pmu_clkstop_cmu_rbch01_duration3 clkstop_cmu_rbch01_duration3; /* offset : 0x4afc */
	union pmu_clkstop_cmu_rbcv00_configuration clkstop_cmu_rbcv00_configuration; /* offset : 0x4b00 */
	union pmu_clkstop_cmu_rbcv00_status clkstop_cmu_rbcv00_status; /* offset : 0x4b04 */
	union pmu_clkstop_cmu_rbcv00_option clkstop_cmu_rbcv00_option; /* offset : 0x4b08 */
	uint32_t reserved_175;
	union pmu_clkstop_cmu_rbcv00_duration0 clkstop_cmu_rbcv00_duration0; /* offset : 0x4b10 */
	union pmu_clkstop_cmu_rbcv00_duration1 clkstop_cmu_rbcv00_duration1; /* offset : 0x4b14 */
	union pmu_clkstop_cmu_rbcv00_duration2 clkstop_cmu_rbcv00_duration2; /* offset : 0x4b18 */
	union pmu_clkstop_cmu_rbcv00_duration3 clkstop_cmu_rbcv00_duration3; /* offset : 0x4b1c */
	union pmu_clkstop_cmu_rbcv01_configuration clkstop_cmu_rbcv01_configuration; /* offset : 0x4b20 */
	union pmu_clkstop_cmu_rbcv01_status clkstop_cmu_rbcv01_status; /* offset : 0x4b24 */
	union pmu_clkstop_cmu_rbcv01_option clkstop_cmu_rbcv01_option; /* offset : 0x4b28 */
	uint32_t reserved_176;
	union pmu_clkstop_cmu_rbcv01_duration0 clkstop_cmu_rbcv01_duration0; /* offset : 0x4b30 */
	union pmu_clkstop_cmu_rbcv01_duration1 clkstop_cmu_rbcv01_duration1; /* offset : 0x4b34 */
	union pmu_clkstop_cmu_rbcv01_duration2 clkstop_cmu_rbcv01_duration2; /* offset : 0x4b38 */
	union pmu_clkstop_cmu_rbcv01_duration3 clkstop_cmu_rbcv01_duration3; /* offset : 0x4b3c */
	union pmu_clkstop_cmu_rbcv10_configuration clkstop_cmu_rbcv10_configuration; /* offset : 0x4b40 */
	union pmu_clkstop_cmu_rbcv10_status clkstop_cmu_rbcv10_status; /* offset : 0x4b44 */
	union pmu_clkstop_cmu_rbcv10_option clkstop_cmu_rbcv10_option; /* offset : 0x4b48 */
	uint32_t reserved_177;
	union pmu_clkstop_cmu_rbcv10_duration0 clkstop_cmu_rbcv10_duration0; /* offset : 0x4b50 */
	union pmu_clkstop_cmu_rbcv10_duration1 clkstop_cmu_rbcv10_duration1; /* offset : 0x4b54 */
	union pmu_clkstop_cmu_rbcv10_duration2 clkstop_cmu_rbcv10_duration2; /* offset : 0x4b58 */
	union pmu_clkstop_cmu_rbcv10_duration3 clkstop_cmu_rbcv10_duration3; /* offset : 0x4b5c */
	union pmu_clkstop_cmu_rbcv11_configuration clkstop_cmu_rbcv11_configuration; /* offset : 0x4b60 */
	union pmu_clkstop_cmu_rbcv11_status clkstop_cmu_rbcv11_status; /* offset : 0x4b64 */
	union pmu_clkstop_cmu_rbcv11_option clkstop_cmu_rbcv11_option; /* offset : 0x4b68 */
	uint32_t reserved_178;
	union pmu_clkstop_cmu_rbcv11_duration0 clkstop_cmu_rbcv11_duration0; /* offset : 0x4b70 */
	union pmu_clkstop_cmu_rbcv11_duration1 clkstop_cmu_rbcv11_duration1; /* offset : 0x4b74 */
	union pmu_clkstop_cmu_rbcv11_duration2 clkstop_cmu_rbcv11_duration2; /* offset : 0x4b78 */
	union pmu_clkstop_cmu_rbcv11_duration3 clkstop_cmu_rbcv11_duration3; /* offset : 0x4b7c */
	union pmu_clkstop_cmu_rot_configuration clkstop_cmu_rot_configuration; /* offset : 0x4b80 */
	union pmu_clkstop_cmu_rot_status clkstop_cmu_rot_status; /* offset : 0x4b84 */
	union pmu_clkstop_cmu_rot_option clkstop_cmu_rot_option; /* offset : 0x4b88 */
	uint32_t reserved_179;
	union pmu_clkstop_cmu_rot_duration0 clkstop_cmu_rot_duration0; /* offset : 0x4b90 */
	union pmu_clkstop_cmu_rot_duration1 clkstop_cmu_rot_duration1; /* offset : 0x4b94 */
	union pmu_clkstop_cmu_rot_duration2 clkstop_cmu_rot_duration2; /* offset : 0x4b98 */
	union pmu_clkstop_cmu_rot_duration3 clkstop_cmu_rot_duration3; /* offset : 0x4b9c */
	union pmu_clkstop_cmu_peri0_configuration clkstop_cmu_peri0_configuration; /* offset : 0x4ba0 */
	union pmu_clkstop_cmu_peri0_status clkstop_cmu_peri0_status; /* offset : 0x4ba4 */
	union pmu_clkstop_cmu_peri0_option clkstop_cmu_peri0_option; /* offset : 0x4ba8 */
	uint32_t reserved_180;
	union pmu_clkstop_cmu_peri0_duration0 clkstop_cmu_peri0_duration0; /* offset : 0x4bb0 */
	union pmu_clkstop_cmu_peri0_duration1 clkstop_cmu_peri0_duration1; /* offset : 0x4bb4 */
	union pmu_clkstop_cmu_peri0_duration2 clkstop_cmu_peri0_duration2; /* offset : 0x4bb8 */
	union pmu_clkstop_cmu_peri0_duration3 clkstop_cmu_peri0_duration3; /* offset : 0x4bbc */
	union pmu_clkstop_cmu_peri1_configuration clkstop_cmu_peri1_configuration; /* offset : 0x4bc0 */
	union pmu_clkstop_cmu_peri1_status clkstop_cmu_peri1_status; /* offset : 0x4bc4 */
	union pmu_clkstop_cmu_peri1_option clkstop_cmu_peri1_option; /* offset : 0x4bc8 */
	uint32_t reserved_181;
	union pmu_clkstop_cmu_peri1_duration0 clkstop_cmu_peri1_duration0; /* offset : 0x4bd0 */
	union pmu_clkstop_cmu_peri1_duration1 clkstop_cmu_peri1_duration1; /* offset : 0x4bd4 */
	union pmu_clkstop_cmu_peri1_duration2 clkstop_cmu_peri1_duration2; /* offset : 0x4bd8 */
	union pmu_clkstop_cmu_peri1_duration3 clkstop_cmu_peri1_duration3; /* offset : 0x4bdc */
	union pmu_clkstop_cmu_sbus_u_configuration clkstop_cmu_sbus_u_configuration; /* offset : 0x4be0 */
	union pmu_clkstop_cmu_sbus_u_status clkstop_cmu_sbus_u_status; /* offset : 0x4be4 */
	union pmu_clkstop_cmu_sbus_u_option clkstop_cmu_sbus_u_option; /* offset : 0x4be8 */
	uint32_t reserved_182;
	union pmu_clkstop_cmu_sbus_u_duration0 clkstop_cmu_sbus_u_duration0; /* offset : 0x4bf0 */
	union pmu_clkstop_cmu_sbus_u_duration1 clkstop_cmu_sbus_u_duration1; /* offset : 0x4bf4 */
	union pmu_clkstop_cmu_sbus_u_duration2 clkstop_cmu_sbus_u_duration2; /* offset : 0x4bf8 */
	union pmu_clkstop_cmu_sbus_u_duration3 clkstop_cmu_sbus_u_duration3; /* offset : 0x4bfc */
	union pmu_clkstop_cmu_sbus_d_configuration clkstop_cmu_sbus_d_configuration; /* offset : 0x4c00 */
	union pmu_clkstop_cmu_sbus_d_status clkstop_cmu_sbus_d_status; /* offset : 0x4c04 */
	union pmu_clkstop_cmu_sbus_d_option clkstop_cmu_sbus_d_option; /* offset : 0x4c08 */
	uint32_t reserved_183;
	union pmu_clkstop_cmu_sbus_d_duration0 clkstop_cmu_sbus_d_duration0; /* offset : 0x4c10 */
	union pmu_clkstop_cmu_sbus_d_duration1 clkstop_cmu_sbus_d_duration1; /* offset : 0x4c14 */
	union pmu_clkstop_cmu_sbus_d_duration2 clkstop_cmu_sbus_d_duration2; /* offset : 0x4c18 */
	union pmu_clkstop_cmu_sbus_d_duration3 clkstop_cmu_sbus_d_duration3; /* offset : 0x4c1c */
	union pmu_clkstop_cmu_sbus_l_configuration clkstop_cmu_sbus_l_configuration; /* offset : 0x4c20 */
	union pmu_clkstop_cmu_sbus_l_status clkstop_cmu_sbus_l_status; /* offset : 0x4c24 */
	union pmu_clkstop_cmu_sbus_l_option clkstop_cmu_sbus_l_option; /* offset : 0x4c28 */
	uint32_t reserved_184;
	union pmu_clkstop_cmu_sbus_l_duration0 clkstop_cmu_sbus_l_duration0; /* offset : 0x4c30 */
	union pmu_clkstop_cmu_sbus_l_duration1 clkstop_cmu_sbus_l_duration1; /* offset : 0x4c34 */
	union pmu_clkstop_cmu_sbus_l_duration2 clkstop_cmu_sbus_l_duration2; /* offset : 0x4c38 */
	union pmu_clkstop_cmu_sbus_l_duration3 clkstop_cmu_sbus_l_duration3; /* offset : 0x4c3c */
	union pmu_clkstop_cmu_nbus_u_configuration clkstop_cmu_nbus_u_configuration; /* offset : 0x4c40 */
	union pmu_clkstop_cmu_nbus_u_status clkstop_cmu_nbus_u_status; /* offset : 0x4c44 */
	union pmu_clkstop_cmu_nbus_u_option clkstop_cmu_nbus_u_option; /* offset : 0x4c48 */
	uint32_t reserved_185;
	union pmu_clkstop_cmu_nbus_u_duration0 clkstop_cmu_nbus_u_duration0; /* offset : 0x4c50 */
	union pmu_clkstop_cmu_nbus_u_duration1 clkstop_cmu_nbus_u_duration1; /* offset : 0x4c54 */
	union pmu_clkstop_cmu_nbus_u_duration2 clkstop_cmu_nbus_u_duration2; /* offset : 0x4c58 */
	union pmu_clkstop_cmu_nbus_u_duration3 clkstop_cmu_nbus_u_duration3; /* offset : 0x4c5c */
	union pmu_clkstop_cmu_nbus_d_configuration clkstop_cmu_nbus_d_configuration; /* offset : 0x4c60 */
	union pmu_clkstop_cmu_nbus_d_status clkstop_cmu_nbus_d_status; /* offset : 0x4c64 */
	union pmu_clkstop_cmu_nbus_d_option clkstop_cmu_nbus_d_option; /* offset : 0x4c68 */
	uint32_t reserved_186;
	union pmu_clkstop_cmu_nbus_d_duration0 clkstop_cmu_nbus_d_duration0; /* offset : 0x4c70 */
	union pmu_clkstop_cmu_nbus_d_duration1 clkstop_cmu_nbus_d_duration1; /* offset : 0x4c74 */
	union pmu_clkstop_cmu_nbus_d_duration2 clkstop_cmu_nbus_d_duration2; /* offset : 0x4c78 */
	union pmu_clkstop_cmu_nbus_d_duration3 clkstop_cmu_nbus_d_duration3; /* offset : 0x4c7c */
	union pmu_clkstop_cmu_nbus_l_configuration clkstop_cmu_nbus_l_configuration; /* offset : 0x4c80 */
	union pmu_clkstop_cmu_nbus_l_status clkstop_cmu_nbus_l_status; /* offset : 0x4c84 */
	union pmu_clkstop_cmu_nbus_l_option clkstop_cmu_nbus_l_option; /* offset : 0x4c88 */
	uint32_t reserved_187;
	union pmu_clkstop_cmu_nbus_l_duration0 clkstop_cmu_nbus_l_duration0; /* offset : 0x4c90 */
	union pmu_clkstop_cmu_nbus_l_duration1 clkstop_cmu_nbus_l_duration1; /* offset : 0x4c94 */
	union pmu_clkstop_cmu_nbus_l_duration2 clkstop_cmu_nbus_l_duration2; /* offset : 0x4c98 */
	union pmu_clkstop_cmu_nbus_l_duration3 clkstop_cmu_nbus_l_duration3; /* offset : 0x4c9c */
	union pmu_clkstop_cmu_wbus_u_configuration clkstop_cmu_wbus_u_configuration; /* offset : 0x4ca0 */
	union pmu_clkstop_cmu_wbus_u_status clkstop_cmu_wbus_u_status; /* offset : 0x4ca4 */
	union pmu_clkstop_cmu_wbus_u_option clkstop_cmu_wbus_u_option; /* offset : 0x4ca8 */
	uint32_t reserved_188;
	union pmu_clkstop_cmu_wbus_u_duration0 clkstop_cmu_wbus_u_duration0; /* offset : 0x4cb0 */
	union pmu_clkstop_cmu_wbus_u_duration1 clkstop_cmu_wbus_u_duration1; /* offset : 0x4cb4 */
	union pmu_clkstop_cmu_wbus_u_duration2 clkstop_cmu_wbus_u_duration2; /* offset : 0x4cb8 */
	union pmu_clkstop_cmu_wbus_u_duration3 clkstop_cmu_wbus_u_duration3; /* offset : 0x4cbc */
	union pmu_clkstop_cmu_wbus_d_configuration clkstop_cmu_wbus_d_configuration; /* offset : 0x4cc0 */
	union pmu_clkstop_cmu_wbus_d_status clkstop_cmu_wbus_d_status; /* offset : 0x4cc4 */
	union pmu_clkstop_cmu_wbus_d_option clkstop_cmu_wbus_d_option; /* offset : 0x4cc8 */
	uint32_t reserved_189;
	union pmu_clkstop_cmu_wbus_d_duration0 clkstop_cmu_wbus_d_duration0; /* offset : 0x4cd0 */
	union pmu_clkstop_cmu_wbus_d_duration1 clkstop_cmu_wbus_d_duration1; /* offset : 0x4cd4 */
	union pmu_clkstop_cmu_wbus_d_duration2 clkstop_cmu_wbus_d_duration2; /* offset : 0x4cd8 */
	union pmu_clkstop_cmu_wbus_d_duration3 clkstop_cmu_wbus_d_duration3; /* offset : 0x4cdc */
	union pmu_clkstop_cmu_ebus_u_configuration clkstop_cmu_ebus_u_configuration; /* offset : 0x4ce0 */
	union pmu_clkstop_cmu_ebus_u_status clkstop_cmu_ebus_u_status; /* offset : 0x4ce4 */
	union pmu_clkstop_cmu_ebus_u_option clkstop_cmu_ebus_u_option; /* offset : 0x4ce8 */
	uint32_t reserved_190;
	union pmu_clkstop_cmu_ebus_u_duration0 clkstop_cmu_ebus_u_duration0; /* offset : 0x4cf0 */
	union pmu_clkstop_cmu_ebus_u_duration1 clkstop_cmu_ebus_u_duration1; /* offset : 0x4cf4 */
	union pmu_clkstop_cmu_ebus_u_duration2 clkstop_cmu_ebus_u_duration2; /* offset : 0x4cf8 */
	union pmu_clkstop_cmu_ebus_u_duration3 clkstop_cmu_ebus_u_duration3; /* offset : 0x4cfc */
	union pmu_clkstop_cmu_ebus_d_configuration clkstop_cmu_ebus_d_configuration; /* offset : 0x4d00 */
	union pmu_clkstop_cmu_ebus_d_status clkstop_cmu_ebus_d_status; /* offset : 0x4d04 */
	union pmu_clkstop_cmu_ebus_d_option clkstop_cmu_ebus_d_option; /* offset : 0x4d08 */
	uint32_t reserved_191;
	union pmu_clkstop_cmu_ebus_d_duration0 clkstop_cmu_ebus_d_duration0; /* offset : 0x4d10 */
	union pmu_clkstop_cmu_ebus_d_duration1 clkstop_cmu_ebus_d_duration1; /* offset : 0x4d14 */
	union pmu_clkstop_cmu_ebus_d_duration2 clkstop_cmu_ebus_d_duration2; /* offset : 0x4d18 */
	union pmu_clkstop_cmu_ebus_d_duration3 clkstop_cmu_ebus_d_duration3; /* offset : 0x4d1c */
	union pmu_clkstop_cmu_ebus_r_configuration clkstop_cmu_ebus_r_configuration; /* offset : 0x4d20 */
	union pmu_clkstop_cmu_ebus_r_status clkstop_cmu_ebus_r_status; /* offset : 0x4d24 */
	union pmu_clkstop_cmu_ebus_r_option clkstop_cmu_ebus_r_option; /* offset : 0x4d28 */
	uint32_t reserved_192;
	union pmu_clkstop_cmu_ebus_r_duration0 clkstop_cmu_ebus_r_duration0; /* offset : 0x4d30 */
	union pmu_clkstop_cmu_ebus_r_duration1 clkstop_cmu_ebus_r_duration1; /* offset : 0x4d34 */
	union pmu_clkstop_cmu_ebus_r_duration2 clkstop_cmu_ebus_r_duration2; /* offset : 0x4d38 */
	union pmu_clkstop_cmu_ebus_r_duration3 clkstop_cmu_ebus_r_duration3; /* offset : 0x4d3c */
	uint32_t reserved_193[48];
	union pmu_disable_pll_cmu_cp0_configuration disable_pll_cmu_cp0_configuration; /* offset : 0x4e00 */
	union pmu_disable_pll_cmu_cp0_status disable_pll_cmu_cp0_status; /* offset : 0x4e04 */
	union pmu_disable_pll_cmu_cp0_option disable_pll_cmu_cp0_option; /* offset : 0x4e08 */
	uint32_t reserved_194;
	union pmu_disable_pll_cmu_cp0_duration0 disable_pll_cmu_cp0_duration0; /* offset : 0x4e10 */
	union pmu_disable_pll_cmu_cp0_duration1 disable_pll_cmu_cp0_duration1; /* offset : 0x4e14 */
	union pmu_disable_pll_cmu_cp0_duration2 disable_pll_cmu_cp0_duration2; /* offset : 0x4e18 */
	union pmu_disable_pll_cmu_cp0_duration3 disable_pll_cmu_cp0_duration3; /* offset : 0x4e1c */
	union pmu_disable_pll_cmu_cp1_configuration disable_pll_cmu_cp1_configuration; /* offset : 0x4e20 */
	union pmu_disable_pll_cmu_cp1_status disable_pll_cmu_cp1_status; /* offset : 0x4e24 */
	union pmu_disable_pll_cmu_cp1_option disable_pll_cmu_cp1_option; /* offset : 0x4e28 */
	uint32_t reserved_195;
	union pmu_disable_pll_cmu_cp1_duration0 disable_pll_cmu_cp1_duration0; /* offset : 0x4e30 */
	union pmu_disable_pll_cmu_cp1_duration1 disable_pll_cmu_cp1_duration1; /* offset : 0x4e34 */
	union pmu_disable_pll_cmu_cp1_duration2 disable_pll_cmu_cp1_duration2; /* offset : 0x4e38 */
	union pmu_disable_pll_cmu_cp1_duration3 disable_pll_cmu_cp1_duration3; /* offset : 0x4e3c */
	union pmu_disable_pll_cmu_pcie_configuration disable_pll_cmu_pcie_configuration; /* offset : 0x4e40 */
	union pmu_disable_pll_cmu_pcie_status disable_pll_cmu_pcie_status; /* offset : 0x4e44 */
	union pmu_disable_pll_cmu_pcie_option disable_pll_cmu_pcie_option; /* offset : 0x4e48 */
	uint32_t reserved_196;
	union pmu_disable_pll_cmu_pcie_duration0 disable_pll_cmu_pcie_duration0; /* offset : 0x4e50 */
	union pmu_disable_pll_cmu_pcie_duration1 disable_pll_cmu_pcie_duration1; /* offset : 0x4e54 */
	union pmu_disable_pll_cmu_pcie_duration2 disable_pll_cmu_pcie_duration2; /* offset : 0x4e58 */
	union pmu_disable_pll_cmu_pcie_duration3 disable_pll_cmu_pcie_duration3; /* offset : 0x4e5c */
	union pmu_disable_pll_cmu_dram_configuration disable_pll_cmu_dram_configuration; /* offset : 0x4e60 */
	union pmu_disable_pll_cmu_dram_status disable_pll_cmu_dram_status; /* offset : 0x4e64 */
	union pmu_disable_pll_cmu_dram_option disable_pll_cmu_dram_option; /* offset : 0x4e68 */
	uint32_t reserved_197;
	union pmu_disable_pll_cmu_dram_duration0 disable_pll_cmu_dram_duration0; /* offset : 0x4e70 */
	union pmu_disable_pll_cmu_dram_duration1 disable_pll_cmu_dram_duration1; /* offset : 0x4e74 */
	union pmu_disable_pll_cmu_dram_duration2 disable_pll_cmu_dram_duration2; /* offset : 0x4e78 */
	union pmu_disable_pll_cmu_dram_duration3 disable_pll_cmu_dram_duration3; /* offset : 0x4e7c */
	union pmu_disable_pll_cmu_dcl0_configuration disable_pll_cmu_dcl0_configuration; /* offset : 0x4e80 */
	union pmu_disable_pll_cmu_dcl0_status disable_pll_cmu_dcl0_status; /* offset : 0x4e84 */
	union pmu_disable_pll_cmu_dcl0_option disable_pll_cmu_dcl0_option; /* offset : 0x4e88 */
	uint32_t reserved_198;
	union pmu_disable_pll_cmu_dcl0_duration0 disable_pll_cmu_dcl0_duration0; /* offset : 0x4e90 */
	union pmu_disable_pll_cmu_dcl0_duration1 disable_pll_cmu_dcl0_duration1; /* offset : 0x4e94 */
	union pmu_disable_pll_cmu_dcl0_duration2 disable_pll_cmu_dcl0_duration2; /* offset : 0x4e98 */
	union pmu_disable_pll_cmu_dcl0_duration3 disable_pll_cmu_dcl0_duration3; /* offset : 0x4e9c */
	union pmu_disable_pll_cmu_dcl1_configuration disable_pll_cmu_dcl1_configuration; /* offset : 0x4ea0 */
	union pmu_disable_pll_cmu_dcl1_status disable_pll_cmu_dcl1_status; /* offset : 0x4ea4 */
	union pmu_disable_pll_cmu_dcl1_option disable_pll_cmu_dcl1_option; /* offset : 0x4ea8 */
	uint32_t reserved_199;
	union pmu_disable_pll_cmu_dcl1_duration0 disable_pll_cmu_dcl1_duration0; /* offset : 0x4eb0 */
	union pmu_disable_pll_cmu_dcl1_duration1 disable_pll_cmu_dcl1_duration1; /* offset : 0x4eb4 */
	union pmu_disable_pll_cmu_dcl1_duration2 disable_pll_cmu_dcl1_duration2; /* offset : 0x4eb8 */
	union pmu_disable_pll_cmu_dcl1_duration3 disable_pll_cmu_dcl1_duration3; /* offset : 0x4ebc */
	union pmu_disable_pll_cmu_rbch00_configuration
			disable_pll_cmu_rbch00_configuration; /* offset : 0x4ec0 */
	union pmu_disable_pll_cmu_rbch00_status disable_pll_cmu_rbch00_status; /* offset : 0x4ec4 */
	union pmu_disable_pll_cmu_rbch00_option disable_pll_cmu_rbch00_option; /* offset : 0x4ec8 */
	uint32_t reserved_200;
	union pmu_disable_pll_cmu_rbch00_duration0 disable_pll_cmu_rbch00_duration0; /* offset : 0x4ed0 */
	union pmu_disable_pll_cmu_rbch00_duration1 disable_pll_cmu_rbch00_duration1; /* offset : 0x4ed4 */
	union pmu_disable_pll_cmu_rbch00_duration2 disable_pll_cmu_rbch00_duration2; /* offset : 0x4ed8 */
	union pmu_disable_pll_cmu_rbch00_duration3 disable_pll_cmu_rbch00_duration3; /* offset : 0x4edc */
	union pmu_disable_pll_cmu_rbch01_configuration
			disable_pll_cmu_rbch01_configuration; /* offset : 0x4ee0 */
	union pmu_disable_pll_cmu_rbch01_status disable_pll_cmu_rbch01_status; /* offset : 0x4ee4 */
	union pmu_disable_pll_cmu_rbch01_option disable_pll_cmu_rbch01_option; /* offset : 0x4ee8 */
	uint32_t reserved_201;
	union pmu_disable_pll_cmu_rbch01_duration0 disable_pll_cmu_rbch01_duration0; /* offset : 0x4ef0 */
	union pmu_disable_pll_cmu_rbch01_duration1 disable_pll_cmu_rbch01_duration1; /* offset : 0x4ef4 */
	union pmu_disable_pll_cmu_rbch01_duration2 disable_pll_cmu_rbch01_duration2; /* offset : 0x4ef8 */
	union pmu_disable_pll_cmu_rbch01_duration3 disable_pll_cmu_rbch01_duration3; /* offset : 0x4efc */
	union pmu_disable_pll_cmu_rbcv00_configuration
			disable_pll_cmu_rbcv00_configuration; /* offset : 0x4f00 */
	union pmu_disable_pll_cmu_rbcv00_status disable_pll_cmu_rbcv00_status; /* offset : 0x4f04 */
	union pmu_disable_pll_cmu_rbcv00_option disable_pll_cmu_rbcv00_option; /* offset : 0x4f08 */
	uint32_t reserved_202;
	union pmu_disable_pll_cmu_rbcv00_duration0 disable_pll_cmu_rbcv00_duration0; /* offset : 0x4f10 */
	union pmu_disable_pll_cmu_rbcv00_duration1 disable_pll_cmu_rbcv00_duration1; /* offset : 0x4f14 */
	union pmu_disable_pll_cmu_rbcv00_duration2 disable_pll_cmu_rbcv00_duration2; /* offset : 0x4f18 */
	union pmu_disable_pll_cmu_rbcv00_duration3 disable_pll_cmu_rbcv00_duration3; /* offset : 0x4f1c */
	union pmu_disable_pll_cmu_rbcv01_configuration
			disable_pll_cmu_rbcv01_configuration; /* offset : 0x4f20 */
	union pmu_disable_pll_cmu_rbcv01_status disable_pll_cmu_rbcv01_status; /* offset : 0x4f24 */
	union pmu_disable_pll_cmu_rbcv01_option disable_pll_cmu_rbcv01_option; /* offset : 0x4f28 */
	uint32_t reserved_203;
	union pmu_disable_pll_cmu_rbcv01_duration0 disable_pll_cmu_rbcv01_duration0; /* offset : 0x4f30 */
	union pmu_disable_pll_cmu_rbcv01_duration1 disable_pll_cmu_rbcv01_duration1; /* offset : 0x4f34 */
	union pmu_disable_pll_cmu_rbcv01_duration2 disable_pll_cmu_rbcv01_duration2; /* offset : 0x4f38 */
	union pmu_disable_pll_cmu_rbcv01_duration3 disable_pll_cmu_rbcv01_duration3; /* offset : 0x4f3c */
	union pmu_disable_pll_cmu_rbcv10_configuration
			disable_pll_cmu_rbcv10_configuration; /* offset : 0x4f40 */
	union pmu_disable_pll_cmu_rbcv10_status disable_pll_cmu_rbcv10_status; /* offset : 0x4f44 */
	union pmu_disable_pll_cmu_rbcv10_option disable_pll_cmu_rbcv10_option; /* offset : 0x4f48 */
	uint32_t reserved_204;
	union pmu_disable_pll_cmu_rbcv10_duration0 disable_pll_cmu_rbcv10_duration0; /* offset : 0x4f50 */
	union pmu_disable_pll_cmu_rbcv10_duration1 disable_pll_cmu_rbcv10_duration1; /* offset : 0x4f54 */
	union pmu_disable_pll_cmu_rbcv10_duration2 disable_pll_cmu_rbcv10_duration2; /* offset : 0x4f58 */
	union pmu_disable_pll_cmu_rbcv10_duration3 disable_pll_cmu_rbcv10_duration3; /* offset : 0x4f5c */
	union pmu_disable_pll_cmu_rbcv11_configuration
			disable_pll_cmu_rbcv11_configuration; /* offset : 0x4f60 */
	union pmu_disable_pll_cmu_rbcv11_status disable_pll_cmu_rbcv11_status; /* offset : 0x4f64 */
	union pmu_disable_pll_cmu_rbcv11_option disable_pll_cmu_rbcv11_option; /* offset : 0x4f68 */
	uint32_t reserved_205;
	union pmu_disable_pll_cmu_rbcv11_duration0 disable_pll_cmu_rbcv11_duration0; /* offset : 0x4f70 */
	union pmu_disable_pll_cmu_rbcv11_duration1 disable_pll_cmu_rbcv11_duration1; /* offset : 0x4f74 */
	union pmu_disable_pll_cmu_rbcv11_duration2 disable_pll_cmu_rbcv11_duration2; /* offset : 0x4f78 */
	union pmu_disable_pll_cmu_rbcv11_duration3 disable_pll_cmu_rbcv11_duration3; /* offset : 0x4f7c */
	union pmu_disable_pll_cmu_rot_configuration disable_pll_cmu_rot_configuration; /* offset : 0x4f80 */
	union pmu_disable_pll_cmu_rot_status disable_pll_cmu_rot_status; /* offset : 0x4f84 */
	union pmu_disable_pll_cmu_rot_option disable_pll_cmu_rot_option; /* offset : 0x4f88 */
	uint32_t reserved_206;
	union pmu_disable_pll_cmu_rot_duration0 disable_pll_cmu_rot_duration0; /* offset : 0x4f90 */
	union pmu_disable_pll_cmu_rot_duration1 disable_pll_cmu_rot_duration1; /* offset : 0x4f94 */
	union pmu_disable_pll_cmu_rot_duration2 disable_pll_cmu_rot_duration2; /* offset : 0x4f98 */
	union pmu_disable_pll_cmu_rot_duration3 disable_pll_cmu_rot_duration3; /* offset : 0x4f9c */
	union pmu_disable_pll_cmu_peri0_configuration
			disable_pll_cmu_peri0_configuration; /* offset : 0x4fa0 */
	union pmu_disable_pll_cmu_peri0_status disable_pll_cmu_peri0_status; /* offset : 0x4fa4 */
	union pmu_disable_pll_cmu_peri0_option disable_pll_cmu_peri0_option; /* offset : 0x4fa8 */
	uint32_t reserved_207;
	union pmu_disable_pll_cmu_peri0_duration0 disable_pll_cmu_peri0_duration0; /* offset : 0x4fb0 */
	union pmu_disable_pll_cmu_peri0_duration1 disable_pll_cmu_peri0_duration1; /* offset : 0x4fb4 */
	union pmu_disable_pll_cmu_peri0_duration2 disable_pll_cmu_peri0_duration2; /* offset : 0x4fb8 */
	union pmu_disable_pll_cmu_peri0_duration3 disable_pll_cmu_peri0_duration3; /* offset : 0x4fbc */
	union pmu_disable_pll_cmu_peri1_configuration
			disable_pll_cmu_peri1_configuration; /* offset : 0x4fc0 */
	union pmu_disable_pll_cmu_peri1_status disable_pll_cmu_peri1_status; /* offset : 0x4fc4 */
	union pmu_disable_pll_cmu_peri1_option disable_pll_cmu_peri1_option; /* offset : 0x4fc8 */
	uint32_t reserved_208;
	union pmu_disable_pll_cmu_peri1_duration0 disable_pll_cmu_peri1_duration0; /* offset : 0x4fd0 */
	union pmu_disable_pll_cmu_peri1_duration1 disable_pll_cmu_peri1_duration1; /* offset : 0x4fd4 */
	union pmu_disable_pll_cmu_peri1_duration2 disable_pll_cmu_peri1_duration2; /* offset : 0x4fd8 */
	union pmu_disable_pll_cmu_peri1_duration3 disable_pll_cmu_peri1_duration3; /* offset : 0x4fdc */
	union pmu_disable_pll_cmu_sbus_u_configuration
			disable_pll_cmu_sbus_u_configuration; /* offset : 0x4fe0 */
	union pmu_disable_pll_cmu_sbus_u_status disable_pll_cmu_sbus_u_status; /* offset : 0x4fe4 */
	union pmu_disable_pll_cmu_sbus_u_option disable_pll_cmu_sbus_u_option; /* offset : 0x4fe8 */
	uint32_t reserved_209;
	union pmu_disable_pll_cmu_sbus_u_duration0 disable_pll_cmu_sbus_u_duration0; /* offset : 0x4ff0 */
	union pmu_disable_pll_cmu_sbus_u_duration1 disable_pll_cmu_sbus_u_duration1; /* offset : 0x4ff4 */
	union pmu_disable_pll_cmu_sbus_u_duration2 disable_pll_cmu_sbus_u_duration2; /* offset : 0x4ff8 */
	union pmu_disable_pll_cmu_sbus_u_duration3 disable_pll_cmu_sbus_u_duration3; /* offset : 0x4ffc */
	union pmu_disable_pll_cmu_sbus_d_configuration
			disable_pll_cmu_sbus_d_configuration; /* offset : 0x5000 */
	union pmu_disable_pll_cmu_sbus_d_status disable_pll_cmu_sbus_d_status; /* offset : 0x5004 */
	union pmu_disable_pll_cmu_sbus_d_option disable_pll_cmu_sbus_d_option; /* offset : 0x5008 */
	uint32_t reserved_210;
	union pmu_disable_pll_cmu_sbus_d_duration0 disable_pll_cmu_sbus_d_duration0; /* offset : 0x5010 */
	union pmu_disable_pll_cmu_sbus_d_duration1 disable_pll_cmu_sbus_d_duration1; /* offset : 0x5014 */
	union pmu_disable_pll_cmu_sbus_d_duration2 disable_pll_cmu_sbus_d_duration2; /* offset : 0x5018 */
	union pmu_disable_pll_cmu_sbus_d_duration3 disable_pll_cmu_sbus_d_duration3; /* offset : 0x501c */
	union pmu_disable_pll_cmu_sbus_l_configuration
			disable_pll_cmu_sbus_l_configuration; /* offset : 0x5020 */
	union pmu_disable_pll_cmu_sbus_l_status disable_pll_cmu_sbus_l_status; /* offset : 0x5024 */
	union pmu_disable_pll_cmu_sbus_l_option disable_pll_cmu_sbus_l_option; /* offset : 0x5028 */
	uint32_t reserved_211;
	union pmu_disable_pll_cmu_sbus_l_duration0 disable_pll_cmu_sbus_l_duration0; /* offset : 0x5030 */
	union pmu_disable_pll_cmu_sbus_l_duration1 disable_pll_cmu_sbus_l_duration1; /* offset : 0x5034 */
	union pmu_disable_pll_cmu_sbus_l_duration2 disable_pll_cmu_sbus_l_duration2; /* offset : 0x5038 */
	union pmu_disable_pll_cmu_sbus_l_duration3 disable_pll_cmu_sbus_l_duration3; /* offset : 0x503c */
	union pmu_disable_pll_cmu_nbus_u_configuration
			disable_pll_cmu_nbus_u_configuration; /* offset : 0x5040 */
	union pmu_disable_pll_cmu_nbus_u_status disable_pll_cmu_nbus_u_status; /* offset : 0x5044 */
	union pmu_disable_pll_cmu_nbus_u_option disable_pll_cmu_nbus_u_option; /* offset : 0x5048 */
	uint32_t reserved_212;
	union pmu_disable_pll_cmu_nbus_u_duration0 disable_pll_cmu_nbus_u_duration0; /* offset : 0x5050 */
	union pmu_disable_pll_cmu_nbus_u_duration1 disable_pll_cmu_nbus_u_duration1; /* offset : 0x5054 */
	union pmu_disable_pll_cmu_nbus_u_duration2 disable_pll_cmu_nbus_u_duration2; /* offset : 0x5058 */
	union pmu_disable_pll_cmu_nbus_u_duration3 disable_pll_cmu_nbus_u_duration3; /* offset : 0x505c */
	union pmu_disable_pll_cmu_nbus_d_configuration
			disable_pll_cmu_nbus_d_configuration; /* offset : 0x5060 */
	union pmu_disable_pll_cmu_nbus_d_status disable_pll_cmu_nbus_d_status; /* offset : 0x5064 */
	union pmu_disable_pll_cmu_nbus_d_option disable_pll_cmu_nbus_d_option; /* offset : 0x5068 */
	uint32_t reserved_213;
	union pmu_disable_pll_cmu_nbus_d_duration0 disable_pll_cmu_nbus_d_duration0; /* offset : 0x5070 */
	union pmu_disable_pll_cmu_nbus_d_duration1 disable_pll_cmu_nbus_d_duration1; /* offset : 0x5074 */
	union pmu_disable_pll_cmu_nbus_d_duration2 disable_pll_cmu_nbus_d_duration2; /* offset : 0x5078 */
	union pmu_disable_pll_cmu_nbus_d_duration3 disable_pll_cmu_nbus_d_duration3; /* offset : 0x507c */
	union pmu_disable_pll_cmu_nbus_l_configuration
			disable_pll_cmu_nbus_l_configuration; /* offset : 0x5080 */
	union pmu_disable_pll_cmu_nbus_l_status disable_pll_cmu_nbus_l_status; /* offset : 0x5084 */
	union pmu_disable_pll_cmu_nbus_l_option disable_pll_cmu_nbus_l_option; /* offset : 0x5088 */
	uint32_t reserved_214;
	union pmu_disable_pll_cmu_nbus_l_duration0 disable_pll_cmu_nbus_l_duration0; /* offset : 0x5090 */
	union pmu_disable_pll_cmu_nbus_l_duration1 disable_pll_cmu_nbus_l_duration1; /* offset : 0x5094 */
	union pmu_disable_pll_cmu_nbus_l_duration2 disable_pll_cmu_nbus_l_duration2; /* offset : 0x5098 */
	union pmu_disable_pll_cmu_nbus_l_duration3 disable_pll_cmu_nbus_l_duration3; /* offset : 0x509c */
	union pmu_disable_pll_cmu_wbus_u_configuration
			disable_pll_cmu_wbus_u_configuration; /* offset : 0x50a0 */
	union pmu_disable_pll_cmu_wbus_u_status disable_pll_cmu_wbus_u_status; /* offset : 0x50a4 */
	union pmu_disable_pll_cmu_wbus_u_option disable_pll_cmu_wbus_u_option; /* offset : 0x50a8 */
	uint32_t reserved_215;
	union pmu_disable_pll_cmu_wbus_u_duration0 disable_pll_cmu_wbus_u_duration0; /* offset : 0x50b0 */
	union pmu_disable_pll_cmu_wbus_u_duration1 disable_pll_cmu_wbus_u_duration1; /* offset : 0x50b4 */
	union pmu_disable_pll_cmu_wbus_u_duration2 disable_pll_cmu_wbus_u_duration2; /* offset : 0x50b8 */
	union pmu_disable_pll_cmu_wbus_u_duration3 disable_pll_cmu_wbus_u_duration3; /* offset : 0x50bc */
	union pmu_disable_pll_cmu_wbus_d_configuration
			disable_pll_cmu_wbus_d_configuration; /* offset : 0x50c0 */
	union pmu_disable_pll_cmu_wbus_d_status disable_pll_cmu_wbus_d_status; /* offset : 0x50c4 */
	union pmu_disable_pll_cmu_wbus_d_option disable_pll_cmu_wbus_d_option; /* offset : 0x50c8 */
	uint32_t reserved_216;
	union pmu_disable_pll_cmu_wbus_d_duration0 disable_pll_cmu_wbus_d_duration0; /* offset : 0x50d0 */
	union pmu_disable_pll_cmu_wbus_d_duration1 disable_pll_cmu_wbus_d_duration1; /* offset : 0x50d4 */
	union pmu_disable_pll_cmu_wbus_d_duration2 disable_pll_cmu_wbus_d_duration2; /* offset : 0x50d8 */
	union pmu_disable_pll_cmu_wbus_d_duration3 disable_pll_cmu_wbus_d_duration3; /* offset : 0x50dc */
	union pmu_disable_pll_cmu_ebus_u_configuration
			disable_pll_cmu_ebus_u_configuration; /* offset : 0x50e0 */
	union pmu_disable_pll_cmu_ebus_u_status disable_pll_cmu_ebus_u_status; /* offset : 0x50e4 */
	union pmu_disable_pll_cmu_ebus_u_option disable_pll_cmu_ebus_u_option; /* offset : 0x50e8 */
	uint32_t reserved_217;
	union pmu_disable_pll_cmu_ebus_u_duration0 disable_pll_cmu_ebus_u_duration0; /* offset : 0x50f0 */
	union pmu_disable_pll_cmu_ebus_u_duration1 disable_pll_cmu_ebus_u_duration1; /* offset : 0x50f4 */
	union pmu_disable_pll_cmu_ebus_u_duration2 disable_pll_cmu_ebus_u_duration2; /* offset : 0x50f8 */
	union pmu_disable_pll_cmu_ebus_u_duration3 disable_pll_cmu_ebus_u_duration3; /* offset : 0x50fc */
	union pmu_disable_pll_cmu_ebus_d_configuration
			disable_pll_cmu_ebus_d_configuration; /* offset : 0x5100 */
	union pmu_disable_pll_cmu_ebus_d_status disable_pll_cmu_ebus_d_status; /* offset : 0x5104 */
	union pmu_disable_pll_cmu_ebus_d_option disable_pll_cmu_ebus_d_option; /* offset : 0x5108 */
	uint32_t reserved_218;
	union pmu_disable_pll_cmu_ebus_d_duration0 disable_pll_cmu_ebus_d_duration0; /* offset : 0x5110 */
	union pmu_disable_pll_cmu_ebus_d_duration1 disable_pll_cmu_ebus_d_duration1; /* offset : 0x5114 */
	union pmu_disable_pll_cmu_ebus_d_duration2 disable_pll_cmu_ebus_d_duration2; /* offset : 0x5118 */
	union pmu_disable_pll_cmu_ebus_d_duration3 disable_pll_cmu_ebus_d_duration3; /* offset : 0x511c */
	union pmu_disable_pll_cmu_ebus_r_configuration
			disable_pll_cmu_ebus_r_configuration; /* offset : 0x5120 */
	union pmu_disable_pll_cmu_ebus_r_status disable_pll_cmu_ebus_r_status; /* offset : 0x5124 */
	union pmu_disable_pll_cmu_ebus_r_option disable_pll_cmu_ebus_r_option; /* offset : 0x5128 */
	uint32_t reserved_219;
	union pmu_disable_pll_cmu_ebus_r_duration0 disable_pll_cmu_ebus_r_duration0; /* offset : 0x5130 */
	union pmu_disable_pll_cmu_ebus_r_duration1 disable_pll_cmu_ebus_r_duration1; /* offset : 0x5134 */
	union pmu_disable_pll_cmu_ebus_r_duration2 disable_pll_cmu_ebus_r_duration2; /* offset : 0x5138 */
	union pmu_disable_pll_cmu_ebus_r_duration3 disable_pll_cmu_ebus_r_duration3; /* offset : 0x513c */
	uint32_t reserved_220[48];
	union pmu_reset_logic_cp0_configuration reset_logic_cp0_configuration; /* offset : 0x5200 */
	union pmu_reset_logic_cp0_status reset_logic_cp0_status; /* offset : 0x5204 */
	union pmu_reset_logic_cp0_option reset_logic_cp0_option; /* offset : 0x5208 */
	uint32_t reserved_221;
	union pmu_reset_logic_cp0_duration0 reset_logic_cp0_duration0; /* offset : 0x5210 */
	union pmu_reset_logic_cp0_duration1 reset_logic_cp0_duration1; /* offset : 0x5214 */
	union pmu_reset_logic_cp0_duration2 reset_logic_cp0_duration2; /* offset : 0x5218 */
	union pmu_reset_logic_cp0_duration3 reset_logic_cp0_duration3; /* offset : 0x521c */
	union pmu_reset_logic_cp1_configuration reset_logic_cp1_configuration; /* offset : 0x5220 */
	union pmu_reset_logic_cp1_status reset_logic_cp1_status; /* offset : 0x5224 */
	union pmu_reset_logic_cp1_option reset_logic_cp1_option; /* offset : 0x5228 */
	uint32_t reserved_222;
	union pmu_reset_logic_cp1_duration0 reset_logic_cp1_duration0; /* offset : 0x5230 */
	union pmu_reset_logic_cp1_duration1 reset_logic_cp1_duration1; /* offset : 0x5234 */
	union pmu_reset_logic_cp1_duration2 reset_logic_cp1_duration2; /* offset : 0x5238 */
	union pmu_reset_logic_cp1_duration3 reset_logic_cp1_duration3; /* offset : 0x523c */
	union pmu_reset_logic_pcie_configuration reset_logic_pcie_configuration; /* offset : 0x5240 */
	union pmu_reset_logic_pcie_status reset_logic_pcie_status; /* offset : 0x5244 */
	union pmu_reset_logic_pcie_option reset_logic_pcie_option; /* offset : 0x5248 */
	uint32_t reserved_223;
	union pmu_reset_logic_pcie_duration0 reset_logic_pcie_duration0; /* offset : 0x5250 */
	union pmu_reset_logic_pcie_duration1 reset_logic_pcie_duration1; /* offset : 0x5254 */
	union pmu_reset_logic_pcie_duration2 reset_logic_pcie_duration2; /* offset : 0x5258 */
	union pmu_reset_logic_pcie_duration3 reset_logic_pcie_duration3; /* offset : 0x525c */
	union pmu_reset_logic_dram_configuration reset_logic_dram_configuration; /* offset : 0x5260 */
	union pmu_reset_logic_dram_status reset_logic_dram_status; /* offset : 0x5264 */
	union pmu_reset_logic_dram_option reset_logic_dram_option; /* offset : 0x5268 */
	uint32_t reserved_224;
	union pmu_reset_logic_dram_duration0 reset_logic_dram_duration0; /* offset : 0x5270 */
	union pmu_reset_logic_dram_duration1 reset_logic_dram_duration1; /* offset : 0x5274 */
	union pmu_reset_logic_dram_duration2 reset_logic_dram_duration2; /* offset : 0x5278 */
	union pmu_reset_logic_dram_duration3 reset_logic_dram_duration3; /* offset : 0x527c */
	union pmu_reset_logic_dcl0_configuration reset_logic_dcl0_configuration; /* offset : 0x5280 */
	union pmu_reset_logic_dcl0_status reset_logic_dcl0_status; /* offset : 0x5284 */
	union pmu_reset_logic_dcl0_option reset_logic_dcl0_option; /* offset : 0x5288 */
	uint32_t reserved_225;
	union pmu_reset_logic_dcl0_duration0 reset_logic_dcl0_duration0; /* offset : 0x5290 */
	union pmu_reset_logic_dcl0_duration1 reset_logic_dcl0_duration1; /* offset : 0x5294 */
	union pmu_reset_logic_dcl0_duration2 reset_logic_dcl0_duration2; /* offset : 0x5298 */
	union pmu_reset_logic_dcl0_duration3 reset_logic_dcl0_duration3; /* offset : 0x529c */
	union pmu_reset_logic_dcl1_configuration reset_logic_dcl1_configuration; /* offset : 0x52a0 */
	union pmu_reset_logic_dcl1_status reset_logic_dcl1_status; /* offset : 0x52a4 */
	union pmu_reset_logic_dcl1_option reset_logic_dcl1_option; /* offset : 0x52a8 */
	uint32_t reserved_226;
	union pmu_reset_logic_dcl1_duration0 reset_logic_dcl1_duration0; /* offset : 0x52b0 */
	union pmu_reset_logic_dcl1_duration1 reset_logic_dcl1_duration1; /* offset : 0x52b4 */
	union pmu_reset_logic_dcl1_duration2 reset_logic_dcl1_duration2; /* offset : 0x52b8 */
	union pmu_reset_logic_dcl1_duration3 reset_logic_dcl1_duration3; /* offset : 0x52bc */
	union pmu_reset_logic_rbch00_configuration reset_logic_rbch00_configuration; /* offset : 0x52c0 */
	union pmu_reset_logic_rbch00_status reset_logic_rbch00_status; /* offset : 0x52c4 */
	union pmu_reset_logic_rbch00_option reset_logic_rbch00_option; /* offset : 0x52c8 */
	uint32_t reserved_227;
	union pmu_reset_logic_rbch00_duration0 reset_logic_rbch00_duration0; /* offset : 0x52d0 */
	union pmu_reset_logic_rbch00_duration1 reset_logic_rbch00_duration1; /* offset : 0x52d4 */
	union pmu_reset_logic_rbch00_duration2 reset_logic_rbch00_duration2; /* offset : 0x52d8 */
	union pmu_reset_logic_rbch00_duration3 reset_logic_rbch00_duration3; /* offset : 0x52dc */
	union pmu_reset_logic_rbch01_configuration reset_logic_rbch01_configuration; /* offset : 0x52e0 */
	union pmu_reset_logic_rbch01_status reset_logic_rbch01_status; /* offset : 0x52e4 */
	union pmu_reset_logic_rbch01_option reset_logic_rbch01_option; /* offset : 0x52e8 */
	uint32_t reserved_228;
	union pmu_reset_logic_rbch01_duration0 reset_logic_rbch01_duration0; /* offset : 0x52f0 */
	union pmu_reset_logic_rbch01_duration1 reset_logic_rbch01_duration1; /* offset : 0x52f4 */
	union pmu_reset_logic_rbch01_duration2 reset_logic_rbch01_duration2; /* offset : 0x52f8 */
	union pmu_reset_logic_rbch01_duration3 reset_logic_rbch01_duration3; /* offset : 0x52fc */
	union pmu_reset_logic_rbcv00_configuration reset_logic_rbcv00_configuration; /* offset : 0x5300 */
	union pmu_reset_logic_rbcv00_status reset_logic_rbcv00_status; /* offset : 0x5304 */
	union pmu_reset_logic_rbcv00_option reset_logic_rbcv00_option; /* offset : 0x5308 */
	uint32_t reserved_229;
	union pmu_reset_logic_rbcv00_duration0 reset_logic_rbcv00_duration0; /* offset : 0x5310 */
	union pmu_reset_logic_rbcv00_duration1 reset_logic_rbcv00_duration1; /* offset : 0x5314 */
	union pmu_reset_logic_rbcv00_duration2 reset_logic_rbcv00_duration2; /* offset : 0x5318 */
	union pmu_reset_logic_rbcv00_duration3 reset_logic_rbcv00_duration3; /* offset : 0x531c */
	union pmu_reset_logic_rbcv01_configuration reset_logic_rbcv01_configuration; /* offset : 0x5320 */
	union pmu_reset_logic_rbcv01_status reset_logic_rbcv01_status; /* offset : 0x5324 */
	union pmu_reset_logic_rbcv01_option reset_logic_rbcv01_option; /* offset : 0x5328 */
	uint32_t reserved_230;
	union pmu_reset_logic_rbcv01_duration0 reset_logic_rbcv01_duration0; /* offset : 0x5330 */
	union pmu_reset_logic_rbcv01_duration1 reset_logic_rbcv01_duration1; /* offset : 0x5334 */
	union pmu_reset_logic_rbcv01_duration2 reset_logic_rbcv01_duration2; /* offset : 0x5338 */
	union pmu_reset_logic_rbcv01_duration3 reset_logic_rbcv01_duration3; /* offset : 0x533c */
	union pmu_reset_logic_rbcv10_configuration reset_logic_rbcv10_configuration; /* offset : 0x5340 */
	union pmu_reset_logic_rbcv10_status reset_logic_rbcv10_status; /* offset : 0x5344 */
	union pmu_reset_logic_rbcv10_option reset_logic_rbcv10_option; /* offset : 0x5348 */
	uint32_t reserved_231;
	union pmu_reset_logic_rbcv10_duration0 reset_logic_rbcv10_duration0; /* offset : 0x5350 */
	union pmu_reset_logic_rbcv10_duration1 reset_logic_rbcv10_duration1; /* offset : 0x5354 */
	union pmu_reset_logic_rbcv10_duration2 reset_logic_rbcv10_duration2; /* offset : 0x5358 */
	union pmu_reset_logic_rbcv10_duration3 reset_logic_rbcv10_duration3; /* offset : 0x535c */
	union pmu_reset_logic_rbcv11_configuration reset_logic_rbcv11_configuration; /* offset : 0x5360 */
	union pmu_reset_logic_rbcv11_status reset_logic_rbcv11_status; /* offset : 0x5364 */
	union pmu_reset_logic_rbcv11_option reset_logic_rbcv11_option; /* offset : 0x5368 */
	uint32_t reserved_232;
	union pmu_reset_logic_rbcv11_duration0 reset_logic_rbcv11_duration0; /* offset : 0x5370 */
	union pmu_reset_logic_rbcv11_duration1 reset_logic_rbcv11_duration1; /* offset : 0x5374 */
	union pmu_reset_logic_rbcv11_duration2 reset_logic_rbcv11_duration2; /* offset : 0x5378 */
	union pmu_reset_logic_rbcv11_duration3 reset_logic_rbcv11_duration3; /* offset : 0x537c */
	union pmu_reset_logic_rot_configuration reset_logic_rot_configuration; /* offset : 0x5380 */
	union pmu_reset_logic_rot_status reset_logic_rot_status; /* offset : 0x5384 */
	union pmu_reset_logic_rot_option reset_logic_rot_option; /* offset : 0x5388 */
	uint32_t reserved_233;
	union pmu_reset_logic_rot_duration0 reset_logic_rot_duration0; /* offset : 0x5390 */
	union pmu_reset_logic_rot_duration1 reset_logic_rot_duration1; /* offset : 0x5394 */
	union pmu_reset_logic_rot_duration2 reset_logic_rot_duration2; /* offset : 0x5398 */
	union pmu_reset_logic_rot_duration3 reset_logic_rot_duration3; /* offset : 0x539c */
	union pmu_reset_logic_peri0_configuration reset_logic_peri0_configuration; /* offset : 0x53a0 */
	union pmu_reset_logic_peri0_status reset_logic_peri0_status; /* offset : 0x53a4 */
	union pmu_reset_logic_peri0_option reset_logic_peri0_option; /* offset : 0x53a8 */
	uint32_t reserved_234;
	union pmu_reset_logic_peri0_duration0 reset_logic_peri0_duration0; /* offset : 0x53b0 */
	union pmu_reset_logic_peri0_duration1 reset_logic_peri0_duration1; /* offset : 0x53b4 */
	union pmu_reset_logic_peri0_duration2 reset_logic_peri0_duration2; /* offset : 0x53b8 */
	union pmu_reset_logic_peri0_duration3 reset_logic_peri0_duration3; /* offset : 0x53bc */
	union pmu_reset_logic_peri1_configuration reset_logic_peri1_configuration; /* offset : 0x53c0 */
	union pmu_reset_logic_peri1_status reset_logic_peri1_status; /* offset : 0x53c4 */
	union pmu_reset_logic_peri1_option reset_logic_peri1_option; /* offset : 0x53c8 */
	uint32_t reserved_235;
	union pmu_reset_logic_peri1_duration0 reset_logic_peri1_duration0; /* offset : 0x53d0 */
	union pmu_reset_logic_peri1_duration1 reset_logic_peri1_duration1; /* offset : 0x53d4 */
	union pmu_reset_logic_peri1_duration2 reset_logic_peri1_duration2; /* offset : 0x53d8 */
	union pmu_reset_logic_peri1_duration3 reset_logic_peri1_duration3; /* offset : 0x53dc */
	union pmu_reset_logic_sbus_u_configuration reset_logic_sbus_u_configuration; /* offset : 0x53e0 */
	union pmu_reset_logic_sbus_u_status reset_logic_sbus_u_status; /* offset : 0x53e4 */
	union pmu_reset_logic_sbus_u_option reset_logic_sbus_u_option; /* offset : 0x53e8 */
	uint32_t reserved_236;
	union pmu_reset_logic_sbus_u_duration0 reset_logic_sbus_u_duration0; /* offset : 0x53f0 */
	union pmu_reset_logic_sbus_u_duration1 reset_logic_sbus_u_duration1; /* offset : 0x53f4 */
	union pmu_reset_logic_sbus_u_duration2 reset_logic_sbus_u_duration2; /* offset : 0x53f8 */
	union pmu_reset_logic_sbus_u_duration3 reset_logic_sbus_u_duration3; /* offset : 0x53fc */
	union pmu_reset_logic_sbus_d_configuration reset_logic_sbus_d_configuration; /* offset : 0x5400 */
	union pmu_reset_logic_sbus_d_status reset_logic_sbus_d_status; /* offset : 0x5404 */
	union pmu_reset_logic_sbus_d_option reset_logic_sbus_d_option; /* offset : 0x5408 */
	uint32_t reserved_237;
	union pmu_reset_logic_sbus_d_duration0 reset_logic_sbus_d_duration0; /* offset : 0x5410 */
	union pmu_reset_logic_sbus_d_duration1 reset_logic_sbus_d_duration1; /* offset : 0x5414 */
	union pmu_reset_logic_sbus_d_duration2 reset_logic_sbus_d_duration2; /* offset : 0x5418 */
	union pmu_reset_logic_sbus_d_duration3 reset_logic_sbus_d_duration3; /* offset : 0x541c */
	union pmu_reset_logic_sbus_l_configuration reset_logic_sbus_l_configuration; /* offset : 0x5420 */
	union pmu_reset_logic_sbus_l_status reset_logic_sbus_l_status; /* offset : 0x5424 */
	union pmu_reset_logic_sbus_l_option reset_logic_sbus_l_option; /* offset : 0x5428 */
	uint32_t reserved_238;
	union pmu_reset_logic_sbus_l_duration0 reset_logic_sbus_l_duration0; /* offset : 0x5430 */
	union pmu_reset_logic_sbus_l_duration1 reset_logic_sbus_l_duration1; /* offset : 0x5434 */
	union pmu_reset_logic_sbus_l_duration2 reset_logic_sbus_l_duration2; /* offset : 0x5438 */
	union pmu_reset_logic_sbus_l_duration3 reset_logic_sbus_l_duration3; /* offset : 0x543c */
	union pmu_reset_logic_nbus_u_configuration reset_logic_nbus_u_configuration; /* offset : 0x5440 */
	union pmu_reset_logic_nbus_u_status reset_logic_nbus_u_status; /* offset : 0x5444 */
	union pmu_reset_logic_nbus_u_option reset_logic_nbus_u_option; /* offset : 0x5448 */
	uint32_t reserved_239;
	union pmu_reset_logic_nbus_u_duration0 reset_logic_nbus_u_duration0; /* offset : 0x5450 */
	union pmu_reset_logic_nbus_u_duration1 reset_logic_nbus_u_duration1; /* offset : 0x5454 */
	union pmu_reset_logic_nbus_u_duration2 reset_logic_nbus_u_duration2; /* offset : 0x5458 */
	union pmu_reset_logic_nbus_u_duration3 reset_logic_nbus_u_duration3; /* offset : 0x545c */
	union pmu_reset_logic_nbus_d_configuration reset_logic_nbus_d_configuration; /* offset : 0x5460 */
	union pmu_reset_logic_nbus_d_status reset_logic_nbus_d_status; /* offset : 0x5464 */
	union pmu_reset_logic_nbus_d_option reset_logic_nbus_d_option; /* offset : 0x5468 */
	uint32_t reserved_240;
	union pmu_reset_logic_nbus_d_duration0 reset_logic_nbus_d_duration0; /* offset : 0x5470 */
	union pmu_reset_logic_nbus_d_duration1 reset_logic_nbus_d_duration1; /* offset : 0x5474 */
	union pmu_reset_logic_nbus_d_duration2 reset_logic_nbus_d_duration2; /* offset : 0x5478 */
	union pmu_reset_logic_nbus_d_duration3 reset_logic_nbus_d_duration3; /* offset : 0x547c */
	union pmu_reset_logic_nbus_l_configuration reset_logic_nbus_l_configuration; /* offset : 0x5480 */
	union pmu_reset_logic_nbus_l_status reset_logic_nbus_l_status; /* offset : 0x5484 */
	union pmu_reset_logic_nbus_l_option reset_logic_nbus_l_option; /* offset : 0x5488 */
	uint32_t reserved_241;
	union pmu_reset_logic_nbus_l_duration0 reset_logic_nbus_l_duration0; /* offset : 0x5490 */
	union pmu_reset_logic_nbus_l_duration1 reset_logic_nbus_l_duration1; /* offset : 0x5494 */
	union pmu_reset_logic_nbus_l_duration2 reset_logic_nbus_l_duration2; /* offset : 0x5498 */
	union pmu_reset_logic_nbus_l_duration3 reset_logic_nbus_l_duration3; /* offset : 0x549c */
	union pmu_reset_logic_wbus_u_configuration reset_logic_wbus_u_configuration; /* offset : 0x54a0 */
	union pmu_reset_logic_wbus_u_status reset_logic_wbus_u_status; /* offset : 0x54a4 */
	union pmu_reset_logic_wbus_u_option reset_logic_wbus_u_option; /* offset : 0x54a8 */
	uint32_t reserved_242;
	union pmu_reset_logic_wbus_u_duration0 reset_logic_wbus_u_duration0; /* offset : 0x54b0 */
	union pmu_reset_logic_wbus_u_duration1 reset_logic_wbus_u_duration1; /* offset : 0x54b4 */
	union pmu_reset_logic_wbus_u_duration2 reset_logic_wbus_u_duration2; /* offset : 0x54b8 */
	union pmu_reset_logic_wbus_u_duration3 reset_logic_wbus_u_duration3; /* offset : 0x54bc */
	union pmu_reset_logic_wbus_d_configuration reset_logic_wbus_d_configuration; /* offset : 0x54c0 */
	union pmu_reset_logic_wbus_d_status reset_logic_wbus_d_status; /* offset : 0x54c4 */
	union pmu_reset_logic_wbus_d_option reset_logic_wbus_d_option; /* offset : 0x54c8 */
	uint32_t reserved_243;
	union pmu_reset_logic_wbus_d_duration0 reset_logic_wbus_d_duration0; /* offset : 0x54d0 */
	union pmu_reset_logic_wbus_d_duration1 reset_logic_wbus_d_duration1; /* offset : 0x54d4 */
	union pmu_reset_logic_wbus_d_duration2 reset_logic_wbus_d_duration2; /* offset : 0x54d8 */
	union pmu_reset_logic_wbus_d_duration3 reset_logic_wbus_d_duration3; /* offset : 0x54dc */
	union pmu_reset_logic_ebus_u_configuration reset_logic_ebus_u_configuration; /* offset : 0x54e0 */
	union pmu_reset_logic_ebus_u_status reset_logic_ebus_u_status; /* offset : 0x54e4 */
	union pmu_reset_logic_ebus_u_option reset_logic_ebus_u_option; /* offset : 0x54e8 */
	uint32_t reserved_244;
	union pmu_reset_logic_ebus_u_duration0 reset_logic_ebus_u_duration0; /* offset : 0x54f0 */
	union pmu_reset_logic_ebus_u_duration1 reset_logic_ebus_u_duration1; /* offset : 0x54f4 */
	union pmu_reset_logic_ebus_u_duration2 reset_logic_ebus_u_duration2; /* offset : 0x54f8 */
	union pmu_reset_logic_ebus_u_duration3 reset_logic_ebus_u_duration3; /* offset : 0x54fc */
	union pmu_reset_logic_ebus_d_configuration reset_logic_ebus_d_configuration; /* offset : 0x5500 */
	union pmu_reset_logic_ebus_d_status reset_logic_ebus_d_status; /* offset : 0x5504 */
	union pmu_reset_logic_ebus_d_option reset_logic_ebus_d_option; /* offset : 0x5508 */
	uint32_t reserved_245;
	union pmu_reset_logic_ebus_d_duration0 reset_logic_ebus_d_duration0; /* offset : 0x5510 */
	union pmu_reset_logic_ebus_d_duration1 reset_logic_ebus_d_duration1; /* offset : 0x5514 */
	union pmu_reset_logic_ebus_d_duration2 reset_logic_ebus_d_duration2; /* offset : 0x5518 */
	union pmu_reset_logic_ebus_d_duration3 reset_logic_ebus_d_duration3; /* offset : 0x551c */
	union pmu_reset_logic_ebus_r_configuration reset_logic_ebus_r_configuration; /* offset : 0x5520 */
	union pmu_reset_logic_ebus_r_status reset_logic_ebus_r_status; /* offset : 0x5524 */
	union pmu_reset_logic_ebus_r_option reset_logic_ebus_r_option; /* offset : 0x5528 */
	uint32_t reserved_246;
	union pmu_reset_logic_ebus_r_duration0 reset_logic_ebus_r_duration0; /* offset : 0x5530 */
	union pmu_reset_logic_ebus_r_duration1 reset_logic_ebus_r_duration1; /* offset : 0x5534 */
	union pmu_reset_logic_ebus_r_duration2 reset_logic_ebus_r_duration2; /* offset : 0x5538 */
	union pmu_reset_logic_ebus_r_duration3 reset_logic_ebus_r_duration3; /* offset : 0x553c */
	uint32_t reserved_247[48];
	union pmu_reset_cmu_cp0_configuration reset_cmu_cp0_configuration; /* offset : 0x5600 */
	union pmu_reset_cmu_cp0_status reset_cmu_cp0_status; /* offset : 0x5604 */
	union pmu_reset_cmu_cp0_option reset_cmu_cp0_option; /* offset : 0x5608 */
	uint32_t reserved_248;
	union pmu_reset_cmu_cp0_duration0 reset_cmu_cp0_duration0; /* offset : 0x5610 */
	union pmu_reset_cmu_cp0_duration1 reset_cmu_cp0_duration1; /* offset : 0x5614 */
	union pmu_reset_cmu_cp0_duration2 reset_cmu_cp0_duration2; /* offset : 0x5618 */
	union pmu_reset_cmu_cp0_duration3 reset_cmu_cp0_duration3; /* offset : 0x561c */
	union pmu_reset_cmu_cp1_configuration reset_cmu_cp1_configuration; /* offset : 0x5620 */
	union pmu_reset_cmu_cp1_status reset_cmu_cp1_status; /* offset : 0x5624 */
	union pmu_reset_cmu_cp1_option reset_cmu_cp1_option; /* offset : 0x5628 */
	uint32_t reserved_249;
	union pmu_reset_cmu_cp1_duration0 reset_cmu_cp1_duration0; /* offset : 0x5630 */
	union pmu_reset_cmu_cp1_duration1 reset_cmu_cp1_duration1; /* offset : 0x5634 */
	union pmu_reset_cmu_cp1_duration2 reset_cmu_cp1_duration2; /* offset : 0x5638 */
	union pmu_reset_cmu_cp1_duration3 reset_cmu_cp1_duration3; /* offset : 0x563c */
	union pmu_reset_cmu_pcie_configuration reset_cmu_pcie_configuration; /* offset : 0x5640 */
	union pmu_reset_cmu_pcie_status reset_cmu_pcie_status; /* offset : 0x5644 */
	union pmu_reset_cmu_pcie_option reset_cmu_pcie_option; /* offset : 0x5648 */
	uint32_t reserved_250;
	union pmu_reset_cmu_pcie_duration0 reset_cmu_pcie_duration0; /* offset : 0x5650 */
	union pmu_reset_cmu_pcie_duration1 reset_cmu_pcie_duration1; /* offset : 0x5654 */
	union pmu_reset_cmu_pcie_duration2 reset_cmu_pcie_duration2; /* offset : 0x5658 */
	union pmu_reset_cmu_pcie_duration3 reset_cmu_pcie_duration3; /* offset : 0x565c */
	union pmu_reset_cmu_dram_configuration reset_cmu_dram_configuration; /* offset : 0x5660 */
	union pmu_reset_cmu_dram_status reset_cmu_dram_status; /* offset : 0x5664 */
	union pmu_reset_cmu_dram_option reset_cmu_dram_option; /* offset : 0x5668 */
	uint32_t reserved_251;
	union pmu_reset_cmu_dram_duration0 reset_cmu_dram_duration0; /* offset : 0x5670 */
	union pmu_reset_cmu_dram_duration1 reset_cmu_dram_duration1; /* offset : 0x5674 */
	union pmu_reset_cmu_dram_duration2 reset_cmu_dram_duration2; /* offset : 0x5678 */
	union pmu_reset_cmu_dram_duration3 reset_cmu_dram_duration3; /* offset : 0x567c */
	union pmu_reset_cmu_dcl0_configuration reset_cmu_dcl0_configuration; /* offset : 0x5680 */
	union pmu_reset_cmu_dcl0_status reset_cmu_dcl0_status; /* offset : 0x5684 */
	union pmu_reset_cmu_dcl0_option reset_cmu_dcl0_option; /* offset : 0x5688 */
	uint32_t reserved_252;
	union pmu_reset_cmu_dcl0_duration0 reset_cmu_dcl0_duration0; /* offset : 0x5690 */
	union pmu_reset_cmu_dcl0_duration1 reset_cmu_dcl0_duration1; /* offset : 0x5694 */
	union pmu_reset_cmu_dcl0_duration2 reset_cmu_dcl0_duration2; /* offset : 0x5698 */
	union pmu_reset_cmu_dcl0_duration3 reset_cmu_dcl0_duration3; /* offset : 0x569c */
	union pmu_reset_cmu_dcl1_configuration reset_cmu_dcl1_configuration; /* offset : 0x56a0 */
	union pmu_reset_cmu_dcl1_status reset_cmu_dcl1_status; /* offset : 0x56a4 */
	union pmu_reset_cmu_dcl1_option reset_cmu_dcl1_option; /* offset : 0x56a8 */
	uint32_t reserved_253;
	union pmu_reset_cmu_dcl1_duration0 reset_cmu_dcl1_duration0; /* offset : 0x56b0 */
	union pmu_reset_cmu_dcl1_duration1 reset_cmu_dcl1_duration1; /* offset : 0x56b4 */
	union pmu_reset_cmu_dcl1_duration2 reset_cmu_dcl1_duration2; /* offset : 0x56b8 */
	union pmu_reset_cmu_dcl1_duration3 reset_cmu_dcl1_duration3; /* offset : 0x56bc */
	union pmu_reset_cmu_rbch00_configuration reset_cmu_rbch00_configuration; /* offset : 0x56c0 */
	union pmu_reset_cmu_rbch00_status reset_cmu_rbch00_status; /* offset : 0x56c4 */
	union pmu_reset_cmu_rbch00_option reset_cmu_rbch00_option; /* offset : 0x56c8 */
	uint32_t reserved_254;
	union pmu_reset_cmu_rbch00_duration0 reset_cmu_rbch00_duration0; /* offset : 0x56d0 */
	union pmu_reset_cmu_rbch00_duration1 reset_cmu_rbch00_duration1; /* offset : 0x56d4 */
	union pmu_reset_cmu_rbch00_duration2 reset_cmu_rbch00_duration2; /* offset : 0x56d8 */
	union pmu_reset_cmu_rbch00_duration3 reset_cmu_rbch00_duration3; /* offset : 0x56dc */
	union pmu_reset_cmu_rbch01_configuration reset_cmu_rbch01_configuration; /* offset : 0x56e0 */
	union pmu_reset_cmu_rbch01_status reset_cmu_rbch01_status; /* offset : 0x56e4 */
	union pmu_reset_cmu_rbch01_option reset_cmu_rbch01_option; /* offset : 0x56e8 */
	uint32_t reserved_255;
	union pmu_reset_cmu_rbch01_duration0 reset_cmu_rbch01_duration0; /* offset : 0x56f0 */
	union pmu_reset_cmu_rbch01_duration1 reset_cmu_rbch01_duration1; /* offset : 0x56f4 */
	union pmu_reset_cmu_rbch01_duration2 reset_cmu_rbch01_duration2; /* offset : 0x56f8 */
	union pmu_reset_cmu_rbch01_duration3 reset_cmu_rbch01_duration3; /* offset : 0x56fc */
	union pmu_reset_cmu_rbcv00_configuration reset_cmu_rbcv00_configuration; /* offset : 0x5700 */
	union pmu_reset_cmu_rbcv00_status reset_cmu_rbcv00_status; /* offset : 0x5704 */
	union pmu_reset_cmu_rbcv00_option reset_cmu_rbcv00_option; /* offset : 0x5708 */
	uint32_t reserved_256;
	union pmu_reset_cmu_rbcv00_duration0 reset_cmu_rbcv00_duration0; /* offset : 0x5710 */
	union pmu_reset_cmu_rbcv00_duration1 reset_cmu_rbcv00_duration1; /* offset : 0x5714 */
	union pmu_reset_cmu_rbcv00_duration2 reset_cmu_rbcv00_duration2; /* offset : 0x5718 */
	union pmu_reset_cmu_rbcv00_duration3 reset_cmu_rbcv00_duration3; /* offset : 0x571c */
	union pmu_reset_cmu_rbcv01_configuration reset_cmu_rbcv01_configuration; /* offset : 0x5720 */
	union pmu_reset_cmu_rbcv01_status reset_cmu_rbcv01_status; /* offset : 0x5724 */
	union pmu_reset_cmu_rbcv01_option reset_cmu_rbcv01_option; /* offset : 0x5728 */
	uint32_t reserved_257;
	union pmu_reset_cmu_rbcv01_duration0 reset_cmu_rbcv01_duration0; /* offset : 0x5730 */
	union pmu_reset_cmu_rbcv01_duration1 reset_cmu_rbcv01_duration1; /* offset : 0x5734 */
	union pmu_reset_cmu_rbcv01_duration2 reset_cmu_rbcv01_duration2; /* offset : 0x5738 */
	union pmu_reset_cmu_rbcv01_duration3 reset_cmu_rbcv01_duration3; /* offset : 0x573c */
	union pmu_reset_cmu_rbcv10_configuration reset_cmu_rbcv10_configuration; /* offset : 0x5740 */
	union pmu_reset_cmu_rbcv10_status reset_cmu_rbcv10_status; /* offset : 0x5744 */
	union pmu_reset_cmu_rbcv10_option reset_cmu_rbcv10_option; /* offset : 0x5748 */
	uint32_t reserved_258;
	union pmu_reset_cmu_rbcv10_duration0 reset_cmu_rbcv10_duration0; /* offset : 0x5750 */
	union pmu_reset_cmu_rbcv10_duration1 reset_cmu_rbcv10_duration1; /* offset : 0x5754 */
	union pmu_reset_cmu_rbcv10_duration2 reset_cmu_rbcv10_duration2; /* offset : 0x5758 */
	union pmu_reset_cmu_rbcv10_duration3 reset_cmu_rbcv10_duration3; /* offset : 0x575c */
	union pmu_reset_cmu_rbcv11_configuration reset_cmu_rbcv11_configuration; /* offset : 0x5760 */
	union pmu_reset_cmu_rbcv11_status reset_cmu_rbcv11_status; /* offset : 0x5764 */
	union pmu_reset_cmu_rbcv11_option reset_cmu_rbcv11_option; /* offset : 0x5768 */
	uint32_t reserved_259;
	union pmu_reset_cmu_rbcv11_duration0 reset_cmu_rbcv11_duration0; /* offset : 0x5770 */
	union pmu_reset_cmu_rbcv11_duration1 reset_cmu_rbcv11_duration1; /* offset : 0x5774 */
	union pmu_reset_cmu_rbcv11_duration2 reset_cmu_rbcv11_duration2; /* offset : 0x5778 */
	union pmu_reset_cmu_rbcv11_duration3 reset_cmu_rbcv11_duration3; /* offset : 0x577c */
	union pmu_reset_cmu_rot_configuration reset_cmu_rot_configuration; /* offset : 0x5780 */
	union pmu_reset_cmu_rot_status reset_cmu_rot_status; /* offset : 0x5784 */
	union pmu_reset_cmu_rot_option reset_cmu_rot_option; /* offset : 0x5788 */
	uint32_t reserved_260;
	union pmu_reset_cmu_rot_duration0 reset_cmu_rot_duration0; /* offset : 0x5790 */
	union pmu_reset_cmu_rot_duration1 reset_cmu_rot_duration1; /* offset : 0x5794 */
	union pmu_reset_cmu_rot_duration2 reset_cmu_rot_duration2; /* offset : 0x5798 */
	union pmu_reset_cmu_rot_duration3 reset_cmu_rot_duration3; /* offset : 0x579c */
	union pmu_reset_cmu_peri0_configuration reset_cmu_peri0_configuration; /* offset : 0x57a0 */
	union pmu_reset_cmu_peri0_status reset_cmu_peri0_status; /* offset : 0x57a4 */
	union pmu_reset_cmu_peri0_option reset_cmu_peri0_option; /* offset : 0x57a8 */
	uint32_t reserved_261;
	union pmu_reset_cmu_peri0_duration0 reset_cmu_peri0_duration0; /* offset : 0x57b0 */
	union pmu_reset_cmu_peri0_duration1 reset_cmu_peri0_duration1; /* offset : 0x57b4 */
	union pmu_reset_cmu_peri0_duration2 reset_cmu_peri0_duration2; /* offset : 0x57b8 */
	union pmu_reset_cmu_peri0_duration3 reset_cmu_peri0_duration3; /* offset : 0x57bc */
	union pmu_reset_cmu_peri1_configuration reset_cmu_peri1_configuration; /* offset : 0x57c0 */
	union pmu_reset_cmu_peri1_status reset_cmu_peri1_status; /* offset : 0x57c4 */
	union pmu_reset_cmu_peri1_option reset_cmu_peri1_option; /* offset : 0x57c8 */
	uint32_t reserved_262;
	union pmu_reset_cmu_peri1_duration0 reset_cmu_peri1_duration0; /* offset : 0x57d0 */
	union pmu_reset_cmu_peri1_duration1 reset_cmu_peri1_duration1; /* offset : 0x57d4 */
	union pmu_reset_cmu_peri1_duration2 reset_cmu_peri1_duration2; /* offset : 0x57d8 */
	union pmu_reset_cmu_peri1_duration3 reset_cmu_peri1_duration3; /* offset : 0x57dc */
	union pmu_reset_cmu_sbus_u_configuration reset_cmu_sbus_u_configuration; /* offset : 0x57e0 */
	union pmu_reset_cmu_sbus_u_status reset_cmu_sbus_u_status; /* offset : 0x57e4 */
	union pmu_reset_cmu_sbus_u_option reset_cmu_sbus_u_option; /* offset : 0x57e8 */
	uint32_t reserved_263;
	union pmu_reset_cmu_sbus_u_duration0 reset_cmu_sbus_u_duration0; /* offset : 0x57f0 */
	union pmu_reset_cmu_sbus_u_duration1 reset_cmu_sbus_u_duration1; /* offset : 0x57f4 */
	union pmu_reset_cmu_sbus_u_duration2 reset_cmu_sbus_u_duration2; /* offset : 0x57f8 */
	union pmu_reset_cmu_sbus_u_duration3 reset_cmu_sbus_u_duration3; /* offset : 0x57fc */
	union pmu_reset_cmu_sbus_d_configuration reset_cmu_sbus_d_configuration; /* offset : 0x5800 */
	union pmu_reset_cmu_sbus_d_status reset_cmu_sbus_d_status; /* offset : 0x5804 */
	union pmu_reset_cmu_sbus_d_option reset_cmu_sbus_d_option; /* offset : 0x5808 */
	uint32_t reserved_264;
	union pmu_reset_cmu_sbus_d_duration0 reset_cmu_sbus_d_duration0; /* offset : 0x5810 */
	union pmu_reset_cmu_sbus_d_duration1 reset_cmu_sbus_d_duration1; /* offset : 0x5814 */
	union pmu_reset_cmu_sbus_d_duration2 reset_cmu_sbus_d_duration2; /* offset : 0x5818 */
	union pmu_reset_cmu_sbus_d_duration3 reset_cmu_sbus_d_duration3; /* offset : 0x581c */
	union pmu_reset_cmu_sbus_l_configuration reset_cmu_sbus_l_configuration; /* offset : 0x5820 */
	union pmu_reset_cmu_sbus_l_status reset_cmu_sbus_l_status; /* offset : 0x5824 */
	union pmu_reset_cmu_sbus_l_option reset_cmu_sbus_l_option; /* offset : 0x5828 */
	uint32_t reserved_265;
	union pmu_reset_cmu_sbus_l_duration0 reset_cmu_sbus_l_duration0; /* offset : 0x5830 */
	union pmu_reset_cmu_sbus_l_duration1 reset_cmu_sbus_l_duration1; /* offset : 0x5834 */
	union pmu_reset_cmu_sbus_l_duration2 reset_cmu_sbus_l_duration2; /* offset : 0x5838 */
	union pmu_reset_cmu_sbus_l_duration3 reset_cmu_sbus_l_duration3; /* offset : 0x583c */
	union pmu_reset_cmu_nbus_u_configuration reset_cmu_nbus_u_configuration; /* offset : 0x5840 */
	union pmu_reset_cmu_nbus_u_status reset_cmu_nbus_u_status; /* offset : 0x5844 */
	union pmu_reset_cmu_nbus_u_option reset_cmu_nbus_u_option; /* offset : 0x5848 */
	uint32_t reserved_266;
	union pmu_reset_cmu_nbus_u_duration0 reset_cmu_nbus_u_duration0; /* offset : 0x5850 */
	union pmu_reset_cmu_nbus_u_duration1 reset_cmu_nbus_u_duration1; /* offset : 0x5854 */
	union pmu_reset_cmu_nbus_u_duration2 reset_cmu_nbus_u_duration2; /* offset : 0x5858 */
	union pmu_reset_cmu_nbus_u_duration3 reset_cmu_nbus_u_duration3; /* offset : 0x585c */
	union pmu_reset_cmu_nbus_d_configuration reset_cmu_nbus_d_configuration; /* offset : 0x5860 */
	union pmu_reset_cmu_nbus_d_status reset_cmu_nbus_d_status; /* offset : 0x5864 */
	union pmu_reset_cmu_nbus_d_option reset_cmu_nbus_d_option; /* offset : 0x5868 */
	uint32_t reserved_267;
	union pmu_reset_cmu_nbus_d_duration0 reset_cmu_nbus_d_duration0; /* offset : 0x5870 */
	union pmu_reset_cmu_nbus_d_duration1 reset_cmu_nbus_d_duration1; /* offset : 0x5874 */
	union pmu_reset_cmu_nbus_d_duration2 reset_cmu_nbus_d_duration2; /* offset : 0x5878 */
	union pmu_reset_cmu_nbus_d_duration3 reset_cmu_nbus_d_duration3; /* offset : 0x587c */
	union pmu_reset_cmu_nbus_l_configuration reset_cmu_nbus_l_configuration; /* offset : 0x5880 */
	union pmu_reset_cmu_nbus_l_status reset_cmu_nbus_l_status; /* offset : 0x5884 */
	union pmu_reset_cmu_nbus_l_option reset_cmu_nbus_l_option; /* offset : 0x5888 */
	uint32_t reserved_268;
	union pmu_reset_cmu_nbus_l_duration0 reset_cmu_nbus_l_duration0; /* offset : 0x5890 */
	union pmu_reset_cmu_nbus_l_duration1 reset_cmu_nbus_l_duration1; /* offset : 0x5894 */
	union pmu_reset_cmu_nbus_l_duration2 reset_cmu_nbus_l_duration2; /* offset : 0x5898 */
	union pmu_reset_cmu_nbus_l_duration3 reset_cmu_nbus_l_duration3; /* offset : 0x589c */
	union pmu_reset_cmu_wbus_u_configuration reset_cmu_wbus_u_configuration; /* offset : 0x58a0 */
	union pmu_reset_cmu_wbus_u_status reset_cmu_wbus_u_status; /* offset : 0x58a4 */
	union pmu_reset_cmu_wbus_u_option reset_cmu_wbus_u_option; /* offset : 0x58a8 */
	uint32_t reserved_269;
	union pmu_reset_cmu_wbus_u_duration0 reset_cmu_wbus_u_duration0; /* offset : 0x58b0 */
	union pmu_reset_cmu_wbus_u_duration1 reset_cmu_wbus_u_duration1; /* offset : 0x58b4 */
	union pmu_reset_cmu_wbus_u_duration2 reset_cmu_wbus_u_duration2; /* offset : 0x58b8 */
	union pmu_reset_cmu_wbus_u_duration3 reset_cmu_wbus_u_duration3; /* offset : 0x58bc */
	union pmu_reset_cmu_wbus_d_configuration reset_cmu_wbus_d_configuration; /* offset : 0x58c0 */
	union pmu_reset_cmu_wbus_d_status reset_cmu_wbus_d_status; /* offset : 0x58c4 */
	union pmu_reset_cmu_wbus_d_option reset_cmu_wbus_d_option; /* offset : 0x58c8 */
	uint32_t reserved_270;
	union pmu_reset_cmu_wbus_d_duration0 reset_cmu_wbus_d_duration0; /* offset : 0x58d0 */
	union pmu_reset_cmu_wbus_d_duration1 reset_cmu_wbus_d_duration1; /* offset : 0x58d4 */
	union pmu_reset_cmu_wbus_d_duration2 reset_cmu_wbus_d_duration2; /* offset : 0x58d8 */
	union pmu_reset_cmu_wbus_d_duration3 reset_cmu_wbus_d_duration3; /* offset : 0x58dc */
	union pmu_reset_cmu_ebus_u_configuration reset_cmu_ebus_u_configuration; /* offset : 0x58e0 */
	union pmu_reset_cmu_ebus_u_status reset_cmu_ebus_u_status; /* offset : 0x58e4 */
	union pmu_reset_cmu_ebus_u_option reset_cmu_ebus_u_option; /* offset : 0x58e8 */
	uint32_t reserved_271;
	union pmu_reset_cmu_ebus_u_duration0 reset_cmu_ebus_u_duration0; /* offset : 0x58f0 */
	union pmu_reset_cmu_ebus_u_duration1 reset_cmu_ebus_u_duration1; /* offset : 0x58f4 */
	union pmu_reset_cmu_ebus_u_duration2 reset_cmu_ebus_u_duration2; /* offset : 0x58f8 */
	union pmu_reset_cmu_ebus_u_duration3 reset_cmu_ebus_u_duration3; /* offset : 0x58fc */
	union pmu_reset_cmu_ebus_d_configuration reset_cmu_ebus_d_configuration; /* offset : 0x5900 */
	union pmu_reset_cmu_ebus_d_status reset_cmu_ebus_d_status; /* offset : 0x5904 */
	union pmu_reset_cmu_ebus_d_option reset_cmu_ebus_d_option; /* offset : 0x5908 */
	uint32_t reserved_272;
	union pmu_reset_cmu_ebus_d_duration0 reset_cmu_ebus_d_duration0; /* offset : 0x5910 */
	union pmu_reset_cmu_ebus_d_duration1 reset_cmu_ebus_d_duration1; /* offset : 0x5914 */
	union pmu_reset_cmu_ebus_d_duration2 reset_cmu_ebus_d_duration2; /* offset : 0x5918 */
	union pmu_reset_cmu_ebus_d_duration3 reset_cmu_ebus_d_duration3; /* offset : 0x591c */
	union pmu_reset_cmu_ebus_r_configuration reset_cmu_ebus_r_configuration; /* offset : 0x5920 */
	union pmu_reset_cmu_ebus_r_status reset_cmu_ebus_r_status; /* offset : 0x5924 */
	union pmu_reset_cmu_ebus_r_option reset_cmu_ebus_r_option; /* offset : 0x5928 */
	uint32_t reserved_273;
	union pmu_reset_cmu_ebus_r_duration0 reset_cmu_ebus_r_duration0; /* offset : 0x5930 */
	union pmu_reset_cmu_ebus_r_duration1 reset_cmu_ebus_r_duration1; /* offset : 0x5934 */
	union pmu_reset_cmu_ebus_r_duration2 reset_cmu_ebus_r_duration2; /* offset : 0x5938 */
	union pmu_reset_cmu_ebus_r_duration3 reset_cmu_ebus_r_duration3; /* offset : 0x593c */
	uint32_t reserved_274[48];
	union pmu_lpi_residual_cmu_cp0_configuration lpi_residual_cmu_cp0_configuration; /* offset : 0x5a00 */
	union pmu_lpi_residual_cmu_cp0_status lpi_residual_cmu_cp0_status; /* offset : 0x5a04 */
	union pmu_lpi_residual_cmu_cp0_option lpi_residual_cmu_cp0_option; /* offset : 0x5a08 */
	uint32_t reserved_275;
	union pmu_lpi_residual_cmu_cp0_duration0 lpi_residual_cmu_cp0_duration0; /* offset : 0x5a10 */
	union pmu_lpi_residual_cmu_cp0_duration1 lpi_residual_cmu_cp0_duration1; /* offset : 0x5a14 */
	union pmu_lpi_residual_cmu_cp0_duration2 lpi_residual_cmu_cp0_duration2; /* offset : 0x5a18 */
	union pmu_lpi_residual_cmu_cp0_duration3 lpi_residual_cmu_cp0_duration3; /* offset : 0x5a1c */
	union pmu_lpi_residual_cmu_cp1_configuration lpi_residual_cmu_cp1_configuration; /* offset : 0x5a20 */
	union pmu_lpi_residual_cmu_cp1_status lpi_residual_cmu_cp1_status; /* offset : 0x5a24 */
	union pmu_lpi_residual_cmu_cp1_option lpi_residual_cmu_cp1_option; /* offset : 0x5a28 */
	uint32_t reserved_276;
	union pmu_lpi_residual_cmu_cp1_duration0 lpi_residual_cmu_cp1_duration0; /* offset : 0x5a30 */
	union pmu_lpi_residual_cmu_cp1_duration1 lpi_residual_cmu_cp1_duration1; /* offset : 0x5a34 */
	union pmu_lpi_residual_cmu_cp1_duration2 lpi_residual_cmu_cp1_duration2; /* offset : 0x5a38 */
	union pmu_lpi_residual_cmu_cp1_duration3 lpi_residual_cmu_cp1_duration3; /* offset : 0x5a3c */
	union pmu_lpi_residual_cmu_pcie_configuration
			lpi_residual_cmu_pcie_configuration; /* offset : 0x5a40 */
	union pmu_lpi_residual_cmu_pcie_status lpi_residual_cmu_pcie_status; /* offset : 0x5a44 */
	union pmu_lpi_residual_cmu_pcie_option lpi_residual_cmu_pcie_option; /* offset : 0x5a48 */
	uint32_t reserved_277;
	union pmu_lpi_residual_cmu_pcie_duration0 lpi_residual_cmu_pcie_duration0; /* offset : 0x5a50 */
	union pmu_lpi_residual_cmu_pcie_duration1 lpi_residual_cmu_pcie_duration1; /* offset : 0x5a54 */
	union pmu_lpi_residual_cmu_pcie_duration2 lpi_residual_cmu_pcie_duration2; /* offset : 0x5a58 */
	union pmu_lpi_residual_cmu_pcie_duration3 lpi_residual_cmu_pcie_duration3; /* offset : 0x5a5c */
	union pmu_lpi_residual_cmu_dram_configuration
			lpi_residual_cmu_dram_configuration; /* offset : 0x5a60 */
	union pmu_lpi_residual_cmu_dram_status lpi_residual_cmu_dram_status; /* offset : 0x5a64 */
	union pmu_lpi_residual_cmu_dram_option lpi_residual_cmu_dram_option; /* offset : 0x5a68 */
	uint32_t reserved_278;
	union pmu_lpi_residual_cmu_dram_duration0 lpi_residual_cmu_dram_duration0; /* offset : 0x5a70 */
	union pmu_lpi_residual_cmu_dram_duration1 lpi_residual_cmu_dram_duration1; /* offset : 0x5a74 */
	union pmu_lpi_residual_cmu_dram_duration2 lpi_residual_cmu_dram_duration2; /* offset : 0x5a78 */
	union pmu_lpi_residual_cmu_dram_duration3 lpi_residual_cmu_dram_duration3; /* offset : 0x5a7c */
	union pmu_lpi_residual_cmu_dcl0_configuration
			lpi_residual_cmu_dcl0_configuration; /* offset : 0x5a80 */
	union pmu_lpi_residual_cmu_dcl0_status lpi_residual_cmu_dcl0_status; /* offset : 0x5a84 */
	union pmu_lpi_residual_cmu_dcl0_option lpi_residual_cmu_dcl0_option; /* offset : 0x5a88 */
	uint32_t reserved_279;
	union pmu_lpi_residual_cmu_dcl0_duration0 lpi_residual_cmu_dcl0_duration0; /* offset : 0x5a90 */
	union pmu_lpi_residual_cmu_dcl0_duration1 lpi_residual_cmu_dcl0_duration1; /* offset : 0x5a94 */
	union pmu_lpi_residual_cmu_dcl0_duration2 lpi_residual_cmu_dcl0_duration2; /* offset : 0x5a98 */
	union pmu_lpi_residual_cmu_dcl0_duration3 lpi_residual_cmu_dcl0_duration3; /* offset : 0x5a9c */
	union pmu_lpi_residual_cmu_dcl1_configuration
			lpi_residual_cmu_dcl1_configuration; /* offset : 0x5aa0 */
	union pmu_lpi_residual_cmu_dcl1_status lpi_residual_cmu_dcl1_status; /* offset : 0x5aa4 */
	union pmu_lpi_residual_cmu_dcl1_option lpi_residual_cmu_dcl1_option; /* offset : 0x5aa8 */
	uint32_t reserved_280;
	union pmu_lpi_residual_cmu_dcl1_duration0 lpi_residual_cmu_dcl1_duration0; /* offset : 0x5ab0 */
	union pmu_lpi_residual_cmu_dcl1_duration1 lpi_residual_cmu_dcl1_duration1; /* offset : 0x5ab4 */
	union pmu_lpi_residual_cmu_dcl1_duration2 lpi_residual_cmu_dcl1_duration2; /* offset : 0x5ab8 */
	union pmu_lpi_residual_cmu_dcl1_duration3 lpi_residual_cmu_dcl1_duration3; /* offset : 0x5abc */
	union pmu_lpi_residual_cmu_rbch00_configuration
			lpi_residual_cmu_rbch00_configuration; /* offset : 0x5ac0 */
	union pmu_lpi_residual_cmu_rbch00_status lpi_residual_cmu_rbch00_status; /* offset : 0x5ac4 */
	union pmu_lpi_residual_cmu_rbch00_option lpi_residual_cmu_rbch00_option; /* offset : 0x5ac8 */
	uint32_t reserved_281;
	union pmu_lpi_residual_cmu_rbch00_duration0 lpi_residual_cmu_rbch00_duration0; /* offset : 0x5ad0 */
	union pmu_lpi_residual_cmu_rbch00_duration1 lpi_residual_cmu_rbch00_duration1; /* offset : 0x5ad4 */
	union pmu_lpi_residual_cmu_rbch00_duration2 lpi_residual_cmu_rbch00_duration2; /* offset : 0x5ad8 */
	union pmu_lpi_residual_cmu_rbch00_duration3 lpi_residual_cmu_rbch00_duration3; /* offset : 0x5adc */
	union pmu_lpi_residual_cmu_rbch01_configuration
			lpi_residual_cmu_rbch01_configuration; /* offset : 0x5ae0 */
	union pmu_lpi_residual_cmu_rbch01_status lpi_residual_cmu_rbch01_status; /* offset : 0x5ae4 */
	union pmu_lpi_residual_cmu_rbch01_option lpi_residual_cmu_rbch01_option; /* offset : 0x5ae8 */
	uint32_t reserved_282;
	union pmu_lpi_residual_cmu_rbch01_duration0 lpi_residual_cmu_rbch01_duration0; /* offset : 0x5af0 */
	union pmu_lpi_residual_cmu_rbch01_duration1 lpi_residual_cmu_rbch01_duration1; /* offset : 0x5af4 */
	union pmu_lpi_residual_cmu_rbch01_duration2 lpi_residual_cmu_rbch01_duration2; /* offset : 0x5af8 */
	union pmu_lpi_residual_cmu_rbch01_duration3 lpi_residual_cmu_rbch01_duration3; /* offset : 0x5afc */
	union pmu_lpi_residual_cmu_rbcv00_configuration
			lpi_residual_cmu_rbcv00_configuration; /* offset : 0x5b00 */
	union pmu_lpi_residual_cmu_rbcv00_status lpi_residual_cmu_rbcv00_status; /* offset : 0x5b04 */
	union pmu_lpi_residual_cmu_rbcv00_option lpi_residual_cmu_rbcv00_option; /* offset : 0x5b08 */
	uint32_t reserved_283;
	union pmu_lpi_residual_cmu_rbcv00_duration0 lpi_residual_cmu_rbcv00_duration0; /* offset : 0x5b10 */
	union pmu_lpi_residual_cmu_rbcv00_duration1 lpi_residual_cmu_rbcv00_duration1; /* offset : 0x5b14 */
	union pmu_lpi_residual_cmu_rbcv00_duration2 lpi_residual_cmu_rbcv00_duration2; /* offset : 0x5b18 */
	union pmu_lpi_residual_cmu_rbcv00_duration3 lpi_residual_cmu_rbcv00_duration3; /* offset : 0x5b1c */
	union pmu_lpi_residual_cmu_rbcv01_configuration
			lpi_residual_cmu_rbcv01_configuration; /* offset : 0x5b20 */
	union pmu_lpi_residual_cmu_rbcv01_status lpi_residual_cmu_rbcv01_status; /* offset : 0x5b24 */
	union pmu_lpi_residual_cmu_rbcv01_option lpi_residual_cmu_rbcv01_option; /* offset : 0x5b28 */
	uint32_t reserved_284;
	union pmu_lpi_residual_cmu_rbcv01_duration0 lpi_residual_cmu_rbcv01_duration0; /* offset : 0x5b30 */
	union pmu_lpi_residual_cmu_rbcv01_duration1 lpi_residual_cmu_rbcv01_duration1; /* offset : 0x5b34 */
	union pmu_lpi_residual_cmu_rbcv01_duration2 lpi_residual_cmu_rbcv01_duration2; /* offset : 0x5b38 */
	union pmu_lpi_residual_cmu_rbcv01_duration3 lpi_residual_cmu_rbcv01_duration3; /* offset : 0x5b3c */
	union pmu_lpi_residual_cmu_rbcv10_configuration
			lpi_residual_cmu_rbcv10_configuration; /* offset : 0x5b40 */
	union pmu_lpi_residual_cmu_rbcv10_status lpi_residual_cmu_rbcv10_status; /* offset : 0x5b44 */
	union pmu_lpi_residual_cmu_rbcv10_option lpi_residual_cmu_rbcv10_option; /* offset : 0x5b48 */
	uint32_t reserved_285;
	union pmu_lpi_residual_cmu_rbcv10_duration0 lpi_residual_cmu_rbcv10_duration0; /* offset : 0x5b50 */
	union pmu_lpi_residual_cmu_rbcv10_duration1 lpi_residual_cmu_rbcv10_duration1; /* offset : 0x5b54 */
	union pmu_lpi_residual_cmu_rbcv10_duration2 lpi_residual_cmu_rbcv10_duration2; /* offset : 0x5b58 */
	union pmu_lpi_residual_cmu_rbcv10_duration3 lpi_residual_cmu_rbcv10_duration3; /* offset : 0x5b5c */
	union pmu_lpi_residual_cmu_rbcv11_configuration
			lpi_residual_cmu_rbcv11_configuration; /* offset : 0x5b60 */
	union pmu_lpi_residual_cmu_rbcv11_status lpi_residual_cmu_rbcv11_status; /* offset : 0x5b64 */
	union pmu_lpi_residual_cmu_rbcv11_option lpi_residual_cmu_rbcv11_option; /* offset : 0x5b68 */
	uint32_t reserved_286;
	union pmu_lpi_residual_cmu_rbcv11_duration0 lpi_residual_cmu_rbcv11_duration0; /* offset : 0x5b70 */
	union pmu_lpi_residual_cmu_rbcv11_duration1 lpi_residual_cmu_rbcv11_duration1; /* offset : 0x5b74 */
	union pmu_lpi_residual_cmu_rbcv11_duration2 lpi_residual_cmu_rbcv11_duration2; /* offset : 0x5b78 */
	union pmu_lpi_residual_cmu_rbcv11_duration3 lpi_residual_cmu_rbcv11_duration3; /* offset : 0x5b7c */
	union pmu_lpi_residual_cmu_rot_configuration lpi_residual_cmu_rot_configuration; /* offset : 0x5b80 */
	union pmu_lpi_residual_cmu_rot_status lpi_residual_cmu_rot_status; /* offset : 0x5b84 */
	union pmu_lpi_residual_cmu_rot_option lpi_residual_cmu_rot_option; /* offset : 0x5b88 */
	uint32_t reserved_287;
	union pmu_lpi_residual_cmu_rot_duration0 lpi_residual_cmu_rot_duration0; /* offset : 0x5b90 */
	union pmu_lpi_residual_cmu_rot_duration1 lpi_residual_cmu_rot_duration1; /* offset : 0x5b94 */
	union pmu_lpi_residual_cmu_rot_duration2 lpi_residual_cmu_rot_duration2; /* offset : 0x5b98 */
	union pmu_lpi_residual_cmu_rot_duration3 lpi_residual_cmu_rot_duration3; /* offset : 0x5b9c */
	union pmu_lpi_residual_cmu_peri0_configuration
			lpi_residual_cmu_peri0_configuration; /* offset : 0x5ba0 */
	union pmu_lpi_residual_cmu_peri0_status lpi_residual_cmu_peri0_status; /* offset : 0x5ba4 */
	union pmu_lpi_residual_cmu_peri0_option lpi_residual_cmu_peri0_option; /* offset : 0x5ba8 */
	uint32_t reserved_288;
	union pmu_lpi_residual_cmu_peri0_duration0 lpi_residual_cmu_peri0_duration0; /* offset : 0x5bb0 */
	union pmu_lpi_residual_cmu_peri0_duration1 lpi_residual_cmu_peri0_duration1; /* offset : 0x5bb4 */
	union pmu_lpi_residual_cmu_peri0_duration2 lpi_residual_cmu_peri0_duration2; /* offset : 0x5bb8 */
	union pmu_lpi_residual_cmu_peri0_duration3 lpi_residual_cmu_peri0_duration3; /* offset : 0x5bbc */
	union pmu_lpi_residual_cmu_peri1_configuration
			lpi_residual_cmu_peri1_configuration; /* offset : 0x5bc0 */
	union pmu_lpi_residual_cmu_peri1_status lpi_residual_cmu_peri1_status; /* offset : 0x5bc4 */
	union pmu_lpi_residual_cmu_peri1_option lpi_residual_cmu_peri1_option; /* offset : 0x5bc8 */
	uint32_t reserved_289;
	union pmu_lpi_residual_cmu_peri1_duration0 lpi_residual_cmu_peri1_duration0; /* offset : 0x5bd0 */
	union pmu_lpi_residual_cmu_peri1_duration1 lpi_residual_cmu_peri1_duration1; /* offset : 0x5bd4 */
	union pmu_lpi_residual_cmu_peri1_duration2 lpi_residual_cmu_peri1_duration2; /* offset : 0x5bd8 */
	union pmu_lpi_residual_cmu_peri1_duration3 lpi_residual_cmu_peri1_duration3; /* offset : 0x5bdc */
	union pmu_lpi_residual_cmu_sbus_u_configuration
			lpi_residual_cmu_sbus_u_configuration; /* offset : 0x5be0 */
	union pmu_lpi_residual_cmu_sbus_u_status lpi_residual_cmu_sbus_u_status; /* offset : 0x5be4 */
	union pmu_lpi_residual_cmu_sbus_u_option lpi_residual_cmu_sbus_u_option; /* offset : 0x5be8 */
	uint32_t reserved_290;
	union pmu_lpi_residual_cmu_sbus_u_duration0 lpi_residual_cmu_sbus_u_duration0; /* offset : 0x5bf0 */
	union pmu_lpi_residual_cmu_sbus_u_duration1 lpi_residual_cmu_sbus_u_duration1; /* offset : 0x5bf4 */
	union pmu_lpi_residual_cmu_sbus_u_duration2 lpi_residual_cmu_sbus_u_duration2; /* offset : 0x5bf8 */
	union pmu_lpi_residual_cmu_sbus_u_duration3 lpi_residual_cmu_sbus_u_duration3; /* offset : 0x5bfc */
	union pmu_lpi_residual_cmu_sbus_d_configuration
			lpi_residual_cmu_sbus_d_configuration; /* offset : 0x5c00 */
	union pmu_lpi_residual_cmu_sbus_d_status lpi_residual_cmu_sbus_d_status; /* offset : 0x5c04 */
	union pmu_lpi_residual_cmu_sbus_d_option lpi_residual_cmu_sbus_d_option; /* offset : 0x5c08 */
	uint32_t reserved_291;
	union pmu_lpi_residual_cmu_sbus_d_duration0 lpi_residual_cmu_sbus_d_duration0; /* offset : 0x5c10 */
	union pmu_lpi_residual_cmu_sbus_d_duration1 lpi_residual_cmu_sbus_d_duration1; /* offset : 0x5c14 */
	union pmu_lpi_residual_cmu_sbus_d_duration2 lpi_residual_cmu_sbus_d_duration2; /* offset : 0x5c18 */
	union pmu_lpi_residual_cmu_sbus_d_duration3 lpi_residual_cmu_sbus_d_duration3; /* offset : 0x5c1c */
	union pmu_lpi_residual_cmu_sbus_l_configuration
			lpi_residual_cmu_sbus_l_configuration; /* offset : 0x5c20 */
	union pmu_lpi_residual_cmu_sbus_l_status lpi_residual_cmu_sbus_l_status; /* offset : 0x5c24 */
	union pmu_lpi_residual_cmu_sbus_l_option lpi_residual_cmu_sbus_l_option; /* offset : 0x5c28 */
	uint32_t reserved_292;
	union pmu_lpi_residual_cmu_sbus_l_duration0 lpi_residual_cmu_sbus_l_duration0; /* offset : 0x5c30 */
	union pmu_lpi_residual_cmu_sbus_l_duration1 lpi_residual_cmu_sbus_l_duration1; /* offset : 0x5c34 */
	union pmu_lpi_residual_cmu_sbus_l_duration2 lpi_residual_cmu_sbus_l_duration2; /* offset : 0x5c38 */
	union pmu_lpi_residual_cmu_sbus_l_duration3 lpi_residual_cmu_sbus_l_duration3; /* offset : 0x5c3c */
	union pmu_lpi_residual_cmu_nbus_u_configuration
			lpi_residual_cmu_nbus_u_configuration; /* offset : 0x5c40 */
	union pmu_lpi_residual_cmu_nbus_u_status lpi_residual_cmu_nbus_u_status; /* offset : 0x5c44 */
	union pmu_lpi_residual_cmu_nbus_u_option lpi_residual_cmu_nbus_u_option; /* offset : 0x5c48 */
	uint32_t reserved_293;
	union pmu_lpi_residual_cmu_nbus_u_duration0 lpi_residual_cmu_nbus_u_duration0; /* offset : 0x5c50 */
	union pmu_lpi_residual_cmu_nbus_u_duration1 lpi_residual_cmu_nbus_u_duration1; /* offset : 0x5c54 */
	union pmu_lpi_residual_cmu_nbus_u_duration2 lpi_residual_cmu_nbus_u_duration2; /* offset : 0x5c58 */
	union pmu_lpi_residual_cmu_nbus_u_duration3 lpi_residual_cmu_nbus_u_duration3; /* offset : 0x5c5c */
	union pmu_lpi_residual_cmu_nbus_d_configuration
			lpi_residual_cmu_nbus_d_configuration; /* offset : 0x5c60 */
	union pmu_lpi_residual_cmu_nbus_d_status lpi_residual_cmu_nbus_d_status; /* offset : 0x5c64 */
	union pmu_lpi_residual_cmu_nbus_d_option lpi_residual_cmu_nbus_d_option; /* offset : 0x5c68 */
	uint32_t reserved_294;
	union pmu_lpi_residual_cmu_nbus_d_duration0 lpi_residual_cmu_nbus_d_duration0; /* offset : 0x5c70 */
	union pmu_lpi_residual_cmu_nbus_d_duration1 lpi_residual_cmu_nbus_d_duration1; /* offset : 0x5c74 */
	union pmu_lpi_residual_cmu_nbus_d_duration2 lpi_residual_cmu_nbus_d_duration2; /* offset : 0x5c78 */
	union pmu_lpi_residual_cmu_nbus_d_duration3 lpi_residual_cmu_nbus_d_duration3; /* offset : 0x5c7c */
	union pmu_lpi_residual_cmu_nbus_l_configuration
			lpi_residual_cmu_nbus_l_configuration; /* offset : 0x5c80 */
	union pmu_lpi_residual_cmu_nbus_l_status lpi_residual_cmu_nbus_l_status; /* offset : 0x5c84 */
	union pmu_lpi_residual_cmu_nbus_l_option lpi_residual_cmu_nbus_l_option; /* offset : 0x5c88 */
	uint32_t reserved_295;
	union pmu_lpi_residual_cmu_nbus_l_duration0 lpi_residual_cmu_nbus_l_duration0; /* offset : 0x5c90 */
	union pmu_lpi_residual_cmu_nbus_l_duration1 lpi_residual_cmu_nbus_l_duration1; /* offset : 0x5c94 */
	union pmu_lpi_residual_cmu_nbus_l_duration2 lpi_residual_cmu_nbus_l_duration2; /* offset : 0x5c98 */
	union pmu_lpi_residual_cmu_nbus_l_duration3 lpi_residual_cmu_nbus_l_duration3; /* offset : 0x5c9c */
	union pmu_lpi_residual_cmu_wbus_u_configuration
			lpi_residual_cmu_wbus_u_configuration; /* offset : 0x5ca0 */
	union pmu_lpi_residual_cmu_wbus_u_status lpi_residual_cmu_wbus_u_status; /* offset : 0x5ca4 */
	union pmu_lpi_residual_cmu_wbus_u_option lpi_residual_cmu_wbus_u_option; /* offset : 0x5ca8 */
	uint32_t reserved_296;
	union pmu_lpi_residual_cmu_wbus_u_duration0 lpi_residual_cmu_wbus_u_duration0; /* offset : 0x5cb0 */
	union pmu_lpi_residual_cmu_wbus_u_duration1 lpi_residual_cmu_wbus_u_duration1; /* offset : 0x5cb4 */
	union pmu_lpi_residual_cmu_wbus_u_duration2 lpi_residual_cmu_wbus_u_duration2; /* offset : 0x5cb8 */
	union pmu_lpi_residual_cmu_wbus_u_duration3 lpi_residual_cmu_wbus_u_duration3; /* offset : 0x5cbc */
	union pmu_lpi_residual_cmu_wbus_d_configuration
			lpi_residual_cmu_wbus_d_configuration; /* offset : 0x5cc0 */
	union pmu_lpi_residual_cmu_wbus_d_status lpi_residual_cmu_wbus_d_status; /* offset : 0x5cc4 */
	union pmu_lpi_residual_cmu_wbus_d_option lpi_residual_cmu_wbus_d_option; /* offset : 0x5cc8 */
	uint32_t reserved_297;
	union pmu_lpi_residual_cmu_wbus_d_duration0 lpi_residual_cmu_wbus_d_duration0; /* offset : 0x5cd0 */
	union pmu_lpi_residual_cmu_wbus_d_duration1 lpi_residual_cmu_wbus_d_duration1; /* offset : 0x5cd4 */
	union pmu_lpi_residual_cmu_wbus_d_duration2 lpi_residual_cmu_wbus_d_duration2; /* offset : 0x5cd8 */
	union pmu_lpi_residual_cmu_wbus_d_duration3 lpi_residual_cmu_wbus_d_duration3; /* offset : 0x5cdc */
	union pmu_lpi_residual_cmu_ebus_u_configuration
			lpi_residual_cmu_ebus_u_configuration; /* offset : 0x5ce0 */
	union pmu_lpi_residual_cmu_ebus_u_status lpi_residual_cmu_ebus_u_status; /* offset : 0x5ce4 */
	union pmu_lpi_residual_cmu_ebus_u_option lpi_residual_cmu_ebus_u_option; /* offset : 0x5ce8 */
	uint32_t reserved_298;
	union pmu_lpi_residual_cmu_ebus_u_duration0 lpi_residual_cmu_ebus_u_duration0; /* offset : 0x5cf0 */
	union pmu_lpi_residual_cmu_ebus_u_duration1 lpi_residual_cmu_ebus_u_duration1; /* offset : 0x5cf4 */
	union pmu_lpi_residual_cmu_ebus_u_duration2 lpi_residual_cmu_ebus_u_duration2; /* offset : 0x5cf8 */
	union pmu_lpi_residual_cmu_ebus_u_duration3 lpi_residual_cmu_ebus_u_duration3; /* offset : 0x5cfc */
	union pmu_lpi_residual_cmu_ebus_d_configuration
			lpi_residual_cmu_ebus_d_configuration; /* offset : 0x5d00 */
	union pmu_lpi_residual_cmu_ebus_d_status lpi_residual_cmu_ebus_d_status; /* offset : 0x5d04 */
	union pmu_lpi_residual_cmu_ebus_d_option lpi_residual_cmu_ebus_d_option; /* offset : 0x5d08 */
	uint32_t reserved_299;
	union pmu_lpi_residual_cmu_ebus_d_duration0 lpi_residual_cmu_ebus_d_duration0; /* offset : 0x5d10 */
	union pmu_lpi_residual_cmu_ebus_d_duration1 lpi_residual_cmu_ebus_d_duration1; /* offset : 0x5d14 */
	union pmu_lpi_residual_cmu_ebus_d_duration2 lpi_residual_cmu_ebus_d_duration2; /* offset : 0x5d18 */
	union pmu_lpi_residual_cmu_ebus_d_duration3 lpi_residual_cmu_ebus_d_duration3; /* offset : 0x5d1c */
	union pmu_lpi_residual_cmu_ebus_r_configuration
			lpi_residual_cmu_ebus_r_configuration; /* offset : 0x5d20 */
	union pmu_lpi_residual_cmu_ebus_r_status lpi_residual_cmu_ebus_r_status; /* offset : 0x5d24 */
	union pmu_lpi_residual_cmu_ebus_r_option lpi_residual_cmu_ebus_r_option; /* offset : 0x5d28 */
	uint32_t reserved_300;
	union pmu_lpi_residual_cmu_ebus_r_duration0 lpi_residual_cmu_ebus_r_duration0; /* offset : 0x5d30 */
	union pmu_lpi_residual_cmu_ebus_r_duration1 lpi_residual_cmu_ebus_r_duration1; /* offset : 0x5d34 */
	union pmu_lpi_residual_cmu_ebus_r_duration2 lpi_residual_cmu_ebus_r_duration2; /* offset : 0x5d38 */
	union pmu_lpi_residual_cmu_ebus_r_duration3 lpi_residual_cmu_ebus_r_duration3; /* offset : 0x5d3c */
	uint32_t reserved_301[48];
	union pmu_lpi_bus_cmu_cp0_configuration lpi_bus_cmu_cp0_configuration; /* offset : 0x5e00 */
	union pmu_lpi_bus_cmu_cp0_status lpi_bus_cmu_cp0_status; /* offset : 0x5e04 */
	union pmu_lpi_bus_cmu_cp0_option lpi_bus_cmu_cp0_option; /* offset : 0x5e08 */
	uint32_t reserved_302;
	union pmu_lpi_bus_cmu_cp0_duration0 lpi_bus_cmu_cp0_duration0; /* offset : 0x5e10 */
	union pmu_lpi_bus_cmu_cp0_duration1 lpi_bus_cmu_cp0_duration1; /* offset : 0x5e14 */
	union pmu_lpi_bus_cmu_cp0_duration2 lpi_bus_cmu_cp0_duration2; /* offset : 0x5e18 */
	union pmu_lpi_bus_cmu_cp0_duration3 lpi_bus_cmu_cp0_duration3; /* offset : 0x5e1c */
	union pmu_lpi_bus_cmu_cp1_configuration lpi_bus_cmu_cp1_configuration; /* offset : 0x5e20 */
	union pmu_lpi_bus_cmu_cp1_status lpi_bus_cmu_cp1_status; /* offset : 0x5e24 */
	union pmu_lpi_bus_cmu_cp1_option lpi_bus_cmu_cp1_option; /* offset : 0x5e28 */
	uint32_t reserved_303;
	union pmu_lpi_bus_cmu_cp1_duration0 lpi_bus_cmu_cp1_duration0; /* offset : 0x5e30 */
	union pmu_lpi_bus_cmu_cp1_duration1 lpi_bus_cmu_cp1_duration1; /* offset : 0x5e34 */
	union pmu_lpi_bus_cmu_cp1_duration2 lpi_bus_cmu_cp1_duration2; /* offset : 0x5e38 */
	union pmu_lpi_bus_cmu_cp1_duration3 lpi_bus_cmu_cp1_duration3; /* offset : 0x5e3c */
	union pmu_lpi_bus_cmu_pcie_configuration lpi_bus_cmu_pcie_configuration; /* offset : 0x5e40 */
	union pmu_lpi_bus_cmu_pcie_status lpi_bus_cmu_pcie_status; /* offset : 0x5e44 */
	union pmu_lpi_bus_cmu_pcie_option lpi_bus_cmu_pcie_option; /* offset : 0x5e48 */
	uint32_t reserved_304;
	union pmu_lpi_bus_cmu_pcie_duration0 lpi_bus_cmu_pcie_duration0; /* offset : 0x5e50 */
	union pmu_lpi_bus_cmu_pcie_duration1 lpi_bus_cmu_pcie_duration1; /* offset : 0x5e54 */
	union pmu_lpi_bus_cmu_pcie_duration2 lpi_bus_cmu_pcie_duration2; /* offset : 0x5e58 */
	union pmu_lpi_bus_cmu_pcie_duration3 lpi_bus_cmu_pcie_duration3; /* offset : 0x5e5c */
	union pmu_lpi_bus_cmu_dram_configuration lpi_bus_cmu_dram_configuration; /* offset : 0x5e60 */
	union pmu_lpi_bus_cmu_dram_status lpi_bus_cmu_dram_status; /* offset : 0x5e64 */
	union pmu_lpi_bus_cmu_dram_option lpi_bus_cmu_dram_option; /* offset : 0x5e68 */
	uint32_t reserved_305;
	union pmu_lpi_bus_cmu_dram_duration0 lpi_bus_cmu_dram_duration0; /* offset : 0x5e70 */
	union pmu_lpi_bus_cmu_dram_duration1 lpi_bus_cmu_dram_duration1; /* offset : 0x5e74 */
	union pmu_lpi_bus_cmu_dram_duration2 lpi_bus_cmu_dram_duration2; /* offset : 0x5e78 */
	union pmu_lpi_bus_cmu_dram_duration3 lpi_bus_cmu_dram_duration3; /* offset : 0x5e7c */
	union pmu_lpi_bus_cmu_dcl0_configuration lpi_bus_cmu_dcl0_configuration; /* offset : 0x5e80 */
	union pmu_lpi_bus_cmu_dcl0_status lpi_bus_cmu_dcl0_status; /* offset : 0x5e84 */
	union pmu_lpi_bus_cmu_dcl0_option lpi_bus_cmu_dcl0_option; /* offset : 0x5e88 */
	uint32_t reserved_306;
	union pmu_lpi_bus_cmu_dcl0_duration0 lpi_bus_cmu_dcl0_duration0; /* offset : 0x5e90 */
	union pmu_lpi_bus_cmu_dcl0_duration1 lpi_bus_cmu_dcl0_duration1; /* offset : 0x5e94 */
	union pmu_lpi_bus_cmu_dcl0_duration2 lpi_bus_cmu_dcl0_duration2; /* offset : 0x5e98 */
	union pmu_lpi_bus_cmu_dcl0_duration3 lpi_bus_cmu_dcl0_duration3; /* offset : 0x5e9c */
	union pmu_lpi_bus_cmu_dcl1_configuration lpi_bus_cmu_dcl1_configuration; /* offset : 0x5ea0 */
	union pmu_lpi_bus_cmu_dcl1_status lpi_bus_cmu_dcl1_status; /* offset : 0x5ea4 */
	union pmu_lpi_bus_cmu_dcl1_option lpi_bus_cmu_dcl1_option; /* offset : 0x5ea8 */
	uint32_t reserved_307;
	union pmu_lpi_bus_cmu_dcl1_duration0 lpi_bus_cmu_dcl1_duration0; /* offset : 0x5eb0 */
	union pmu_lpi_bus_cmu_dcl1_duration1 lpi_bus_cmu_dcl1_duration1; /* offset : 0x5eb4 */
	union pmu_lpi_bus_cmu_dcl1_duration2 lpi_bus_cmu_dcl1_duration2; /* offset : 0x5eb8 */
	union pmu_lpi_bus_cmu_dcl1_duration3 lpi_bus_cmu_dcl1_duration3; /* offset : 0x5ebc */
	union pmu_lpi_bus_cmu_rbch00_configuration lpi_bus_cmu_rbch00_configuration; /* offset : 0x5ec0 */
	union pmu_lpi_bus_cmu_rbch00_status lpi_bus_cmu_rbch00_status; /* offset : 0x5ec4 */
	union pmu_lpi_bus_cmu_rbch00_option lpi_bus_cmu_rbch00_option; /* offset : 0x5ec8 */
	uint32_t reserved_308;
	union pmu_lpi_bus_cmu_rbch00_duration0 lpi_bus_cmu_rbch00_duration0; /* offset : 0x5ed0 */
	union pmu_lpi_bus_cmu_rbch00_duration1 lpi_bus_cmu_rbch00_duration1; /* offset : 0x5ed4 */
	union pmu_lpi_bus_cmu_rbch00_duration2 lpi_bus_cmu_rbch00_duration2; /* offset : 0x5ed8 */
	union pmu_lpi_bus_cmu_rbch00_duration3 lpi_bus_cmu_rbch00_duration3; /* offset : 0x5edc */
	union pmu_lpi_bus_cmu_rbch01_configuration lpi_bus_cmu_rbch01_configuration; /* offset : 0x5ee0 */
	union pmu_lpi_bus_cmu_rbch01_status lpi_bus_cmu_rbch01_status; /* offset : 0x5ee4 */
	union pmu_lpi_bus_cmu_rbch01_option lpi_bus_cmu_rbch01_option; /* offset : 0x5ee8 */
	uint32_t reserved_309;
	union pmu_lpi_bus_cmu_rbch01_duration0 lpi_bus_cmu_rbch01_duration0; /* offset : 0x5ef0 */
	union pmu_lpi_bus_cmu_rbch01_duration1 lpi_bus_cmu_rbch01_duration1; /* offset : 0x5ef4 */
	union pmu_lpi_bus_cmu_rbch01_duration2 lpi_bus_cmu_rbch01_duration2; /* offset : 0x5ef8 */
	union pmu_lpi_bus_cmu_rbch01_duration3 lpi_bus_cmu_rbch01_duration3; /* offset : 0x5efc */
	union pmu_lpi_bus_cmu_rbcv00_configuration lpi_bus_cmu_rbcv00_configuration; /* offset : 0x5f00 */
	union pmu_lpi_bus_cmu_rbcv00_status lpi_bus_cmu_rbcv00_status; /* offset : 0x5f04 */
	union pmu_lpi_bus_cmu_rbcv00_option lpi_bus_cmu_rbcv00_option; /* offset : 0x5f08 */
	uint32_t reserved_310;
	union pmu_lpi_bus_cmu_rbcv00_duration0 lpi_bus_cmu_rbcv00_duration0; /* offset : 0x5f10 */
	union pmu_lpi_bus_cmu_rbcv00_duration1 lpi_bus_cmu_rbcv00_duration1; /* offset : 0x5f14 */
	union pmu_lpi_bus_cmu_rbcv00_duration2 lpi_bus_cmu_rbcv00_duration2; /* offset : 0x5f18 */
	union pmu_lpi_bus_cmu_rbcv00_duration3 lpi_bus_cmu_rbcv00_duration3; /* offset : 0x5f1c */
	union pmu_lpi_bus_cmu_rbcv01_configuration lpi_bus_cmu_rbcv01_configuration; /* offset : 0x5f20 */
	union pmu_lpi_bus_cmu_rbcv01_status lpi_bus_cmu_rbcv01_status; /* offset : 0x5f24 */
	union pmu_lpi_bus_cmu_rbcv01_option lpi_bus_cmu_rbcv01_option; /* offset : 0x5f28 */
	uint32_t reserved_311;
	union pmu_lpi_bus_cmu_rbcv01_duration0 lpi_bus_cmu_rbcv01_duration0; /* offset : 0x5f30 */
	union pmu_lpi_bus_cmu_rbcv01_duration1 lpi_bus_cmu_rbcv01_duration1; /* offset : 0x5f34 */
	union pmu_lpi_bus_cmu_rbcv01_duration2 lpi_bus_cmu_rbcv01_duration2; /* offset : 0x5f38 */
	union pmu_lpi_bus_cmu_rbcv01_duration3 lpi_bus_cmu_rbcv01_duration3; /* offset : 0x5f3c */
	union pmu_lpi_bus_cmu_rbcv10_configuration lpi_bus_cmu_rbcv10_configuration; /* offset : 0x5f40 */
	union pmu_lpi_bus_cmu_rbcv10_status lpi_bus_cmu_rbcv10_status; /* offset : 0x5f44 */
	union pmu_lpi_bus_cmu_rbcv10_option lpi_bus_cmu_rbcv10_option; /* offset : 0x5f48 */
	uint32_t reserved_312;
	union pmu_lpi_bus_cmu_rbcv10_duration0 lpi_bus_cmu_rbcv10_duration0; /* offset : 0x5f50 */
	union pmu_lpi_bus_cmu_rbcv10_duration1 lpi_bus_cmu_rbcv10_duration1; /* offset : 0x5f54 */
	union pmu_lpi_bus_cmu_rbcv10_duration2 lpi_bus_cmu_rbcv10_duration2; /* offset : 0x5f58 */
	union pmu_lpi_bus_cmu_rbcv10_duration3 lpi_bus_cmu_rbcv10_duration3; /* offset : 0x5f5c */
	union pmu_lpi_bus_cmu_rbcv11_configuration lpi_bus_cmu_rbcv11_configuration; /* offset : 0x5f60 */
	union pmu_lpi_bus_cmu_rbcv11_status lpi_bus_cmu_rbcv11_status; /* offset : 0x5f64 */
	union pmu_lpi_bus_cmu_rbcv11_option lpi_bus_cmu_rbcv11_option; /* offset : 0x5f68 */
	uint32_t reserved_313;
	union pmu_lpi_bus_cmu_rbcv11_duration0 lpi_bus_cmu_rbcv11_duration0; /* offset : 0x5f70 */
	union pmu_lpi_bus_cmu_rbcv11_duration1 lpi_bus_cmu_rbcv11_duration1; /* offset : 0x5f74 */
	union pmu_lpi_bus_cmu_rbcv11_duration2 lpi_bus_cmu_rbcv11_duration2; /* offset : 0x5f78 */
	union pmu_lpi_bus_cmu_rbcv11_duration3 lpi_bus_cmu_rbcv11_duration3; /* offset : 0x5f7c */
	union pmu_lpi_bus_cmu_rot_configuration lpi_bus_cmu_rot_configuration; /* offset : 0x5f80 */
	union pmu_lpi_bus_cmu_rot_status lpi_bus_cmu_rot_status; /* offset : 0x5f84 */
	union pmu_lpi_bus_cmu_rot_option lpi_bus_cmu_rot_option; /* offset : 0x5f88 */
	uint32_t reserved_314;
	union pmu_lpi_bus_cmu_rot_duration0 lpi_bus_cmu_rot_duration0; /* offset : 0x5f90 */
	union pmu_lpi_bus_cmu_rot_duration1 lpi_bus_cmu_rot_duration1; /* offset : 0x5f94 */
	union pmu_lpi_bus_cmu_rot_duration2 lpi_bus_cmu_rot_duration2; /* offset : 0x5f98 */
	union pmu_lpi_bus_cmu_rot_duration3 lpi_bus_cmu_rot_duration3; /* offset : 0x5f9c */
	union pmu_lpi_bus_cmu_peri0_configuration lpi_bus_cmu_peri0_configuration; /* offset : 0x5fa0 */
	union pmu_lpi_bus_cmu_peri0_status lpi_bus_cmu_peri0_status; /* offset : 0x5fa4 */
	union pmu_lpi_bus_cmu_peri0_option lpi_bus_cmu_peri0_option; /* offset : 0x5fa8 */
	uint32_t reserved_315;
	union pmu_lpi_bus_cmu_peri0_duration0 lpi_bus_cmu_peri0_duration0; /* offset : 0x5fb0 */
	union pmu_lpi_bus_cmu_peri0_duration1 lpi_bus_cmu_peri0_duration1; /* offset : 0x5fb4 */
	union pmu_lpi_bus_cmu_peri0_duration2 lpi_bus_cmu_peri0_duration2; /* offset : 0x5fb8 */
	union pmu_lpi_bus_cmu_peri0_duration3 lpi_bus_cmu_peri0_duration3; /* offset : 0x5fbc */
	union pmu_lpi_bus_cmu_peri1_configuration lpi_bus_cmu_peri1_configuration; /* offset : 0x5fc0 */
	union pmu_lpi_bus_cmu_peri1_status lpi_bus_cmu_peri1_status; /* offset : 0x5fc4 */
	union pmu_lpi_bus_cmu_peri1_option lpi_bus_cmu_peri1_option; /* offset : 0x5fc8 */
	uint32_t reserved_316;
	union pmu_lpi_bus_cmu_peri1_duration0 lpi_bus_cmu_peri1_duration0; /* offset : 0x5fd0 */
	union pmu_lpi_bus_cmu_peri1_duration1 lpi_bus_cmu_peri1_duration1; /* offset : 0x5fd4 */
	union pmu_lpi_bus_cmu_peri1_duration2 lpi_bus_cmu_peri1_duration2; /* offset : 0x5fd8 */
	union pmu_lpi_bus_cmu_peri1_duration3 lpi_bus_cmu_peri1_duration3; /* offset : 0x5fdc */
	union pmu_lpi_bus_cmu_sbus_u_configuration lpi_bus_cmu_sbus_u_configuration; /* offset : 0x5fe0 */
	union pmu_lpi_bus_cmu_sbus_u_status lpi_bus_cmu_sbus_u_status; /* offset : 0x5fe4 */
	union pmu_lpi_bus_cmu_sbus_u_option lpi_bus_cmu_sbus_u_option; /* offset : 0x5fe8 */
	uint32_t reserved_317;
	union pmu_lpi_bus_cmu_sbus_u_duration0 lpi_bus_cmu_sbus_u_duration0; /* offset : 0x5ff0 */
	union pmu_lpi_bus_cmu_sbus_u_duration1 lpi_bus_cmu_sbus_u_duration1; /* offset : 0x5ff4 */
	union pmu_lpi_bus_cmu_sbus_u_duration2 lpi_bus_cmu_sbus_u_duration2; /* offset : 0x5ff8 */
	union pmu_lpi_bus_cmu_sbus_u_duration3 lpi_bus_cmu_sbus_u_duration3; /* offset : 0x5ffc */
	union pmu_lpi_bus_cmu_sbus_d_configuration lpi_bus_cmu_sbus_d_configuration; /* offset : 0x6000 */
	union pmu_lpi_bus_cmu_sbus_d_status lpi_bus_cmu_sbus_d_status; /* offset : 0x6004 */
	union pmu_lpi_bus_cmu_sbus_d_option lpi_bus_cmu_sbus_d_option; /* offset : 0x6008 */
	uint32_t reserved_318;
	union pmu_lpi_bus_cmu_sbus_d_duration0 lpi_bus_cmu_sbus_d_duration0; /* offset : 0x6010 */
	union pmu_lpi_bus_cmu_sbus_d_duration1 lpi_bus_cmu_sbus_d_duration1; /* offset : 0x6014 */
	union pmu_lpi_bus_cmu_sbus_d_duration2 lpi_bus_cmu_sbus_d_duration2; /* offset : 0x6018 */
	union pmu_lpi_bus_cmu_sbus_d_duration3 lpi_bus_cmu_sbus_d_duration3; /* offset : 0x601c */
	union pmu_lpi_bus_cmu_sbus_l_configuration lpi_bus_cmu_sbus_l_configuration; /* offset : 0x6020 */
	union pmu_lpi_bus_cmu_sbus_l_status lpi_bus_cmu_sbus_l_status; /* offset : 0x6024 */
	union pmu_lpi_bus_cmu_sbus_l_option lpi_bus_cmu_sbus_l_option; /* offset : 0x6028 */
	uint32_t reserved_319;
	union pmu_lpi_bus_cmu_sbus_l_duration0 lpi_bus_cmu_sbus_l_duration0; /* offset : 0x6030 */
	union pmu_lpi_bus_cmu_sbus_l_duration1 lpi_bus_cmu_sbus_l_duration1; /* offset : 0x6034 */
	union pmu_lpi_bus_cmu_sbus_l_duration2 lpi_bus_cmu_sbus_l_duration2; /* offset : 0x6038 */
	union pmu_lpi_bus_cmu_sbus_l_duration3 lpi_bus_cmu_sbus_l_duration3; /* offset : 0x603c */
	union pmu_lpi_bus_cmu_nbus_u_configuration lpi_bus_cmu_nbus_u_configuration; /* offset : 0x6040 */
	union pmu_lpi_bus_cmu_nbus_u_status lpi_bus_cmu_nbus_u_status; /* offset : 0x6044 */
	union pmu_lpi_bus_cmu_nbus_u_option lpi_bus_cmu_nbus_u_option; /* offset : 0x6048 */
	uint32_t reserved_320;
	union pmu_lpi_bus_cmu_nbus_u_duration0 lpi_bus_cmu_nbus_u_duration0; /* offset : 0x6050 */
	union pmu_lpi_bus_cmu_nbus_u_duration1 lpi_bus_cmu_nbus_u_duration1; /* offset : 0x6054 */
	union pmu_lpi_bus_cmu_nbus_u_duration2 lpi_bus_cmu_nbus_u_duration2; /* offset : 0x6058 */
	union pmu_lpi_bus_cmu_nbus_u_duration3 lpi_bus_cmu_nbus_u_duration3; /* offset : 0x605c */
	union pmu_lpi_bus_cmu_nbus_d_configuration lpi_bus_cmu_nbus_d_configuration; /* offset : 0x6060 */
	union pmu_lpi_bus_cmu_nbus_d_status lpi_bus_cmu_nbus_d_status; /* offset : 0x6064 */
	union pmu_lpi_bus_cmu_nbus_d_option lpi_bus_cmu_nbus_d_option; /* offset : 0x6068 */
	uint32_t reserved_321;
	union pmu_lpi_bus_cmu_nbus_d_duration0 lpi_bus_cmu_nbus_d_duration0; /* offset : 0x6070 */
	union pmu_lpi_bus_cmu_nbus_d_duration1 lpi_bus_cmu_nbus_d_duration1; /* offset : 0x6074 */
	union pmu_lpi_bus_cmu_nbus_d_duration2 lpi_bus_cmu_nbus_d_duration2; /* offset : 0x6078 */
	union pmu_lpi_bus_cmu_nbus_d_duration3 lpi_bus_cmu_nbus_d_duration3; /* offset : 0x607c */
	union pmu_lpi_bus_cmu_nbus_l_configuration lpi_bus_cmu_nbus_l_configuration; /* offset : 0x6080 */
	union pmu_lpi_bus_cmu_nbus_l_status lpi_bus_cmu_nbus_l_status; /* offset : 0x6084 */
	union pmu_lpi_bus_cmu_nbus_l_option lpi_bus_cmu_nbus_l_option; /* offset : 0x6088 */
	uint32_t reserved_322;
	union pmu_lpi_bus_cmu_nbus_l_duration0 lpi_bus_cmu_nbus_l_duration0; /* offset : 0x6090 */
	union pmu_lpi_bus_cmu_nbus_l_duration1 lpi_bus_cmu_nbus_l_duration1; /* offset : 0x6094 */
	union pmu_lpi_bus_cmu_nbus_l_duration2 lpi_bus_cmu_nbus_l_duration2; /* offset : 0x6098 */
	union pmu_lpi_bus_cmu_nbus_l_duration3 lpi_bus_cmu_nbus_l_duration3; /* offset : 0x609c */
	union pmu_lpi_bus_cmu_wbus_u_configuration lpi_bus_cmu_wbus_u_configuration; /* offset : 0x60a0 */
	union pmu_lpi_bus_cmu_wbus_u_status lpi_bus_cmu_wbus_u_status; /* offset : 0x60a4 */
	union pmu_lpi_bus_cmu_wbus_u_option lpi_bus_cmu_wbus_u_option; /* offset : 0x60a8 */
	uint32_t reserved_323;
	union pmu_lpi_bus_cmu_wbus_u_duration0 lpi_bus_cmu_wbus_u_duration0; /* offset : 0x60b0 */
	union pmu_lpi_bus_cmu_wbus_u_duration1 lpi_bus_cmu_wbus_u_duration1; /* offset : 0x60b4 */
	union pmu_lpi_bus_cmu_wbus_u_duration2 lpi_bus_cmu_wbus_u_duration2; /* offset : 0x60b8 */
	union pmu_lpi_bus_cmu_wbus_u_duration3 lpi_bus_cmu_wbus_u_duration3; /* offset : 0x60bc */
	union pmu_lpi_bus_cmu_wbus_d_configuration lpi_bus_cmu_wbus_d_configuration; /* offset : 0x60c0 */
	union pmu_lpi_bus_cmu_wbus_d_status lpi_bus_cmu_wbus_d_status; /* offset : 0x60c4 */
	union pmu_lpi_bus_cmu_wbus_d_option lpi_bus_cmu_wbus_d_option; /* offset : 0x60c8 */
	uint32_t reserved_324;
	union pmu_lpi_bus_cmu_wbus_d_duration0 lpi_bus_cmu_wbus_d_duration0; /* offset : 0x60d0 */
	union pmu_lpi_bus_cmu_wbus_d_duration1 lpi_bus_cmu_wbus_d_duration1; /* offset : 0x60d4 */
	union pmu_lpi_bus_cmu_wbus_d_duration2 lpi_bus_cmu_wbus_d_duration2; /* offset : 0x60d8 */
	union pmu_lpi_bus_cmu_wbus_d_duration3 lpi_bus_cmu_wbus_d_duration3; /* offset : 0x60dc */
	union pmu_lpi_bus_cmu_ebus_u_configuration lpi_bus_cmu_ebus_u_configuration; /* offset : 0x60e0 */
	union pmu_lpi_bus_cmu_ebus_u_status lpi_bus_cmu_ebus_u_status; /* offset : 0x60e4 */
	union pmu_lpi_bus_cmu_ebus_u_option lpi_bus_cmu_ebus_u_option; /* offset : 0x60e8 */
	uint32_t reserved_325;
	union pmu_lpi_bus_cmu_ebus_u_duration0 lpi_bus_cmu_ebus_u_duration0; /* offset : 0x60f0 */
	union pmu_lpi_bus_cmu_ebus_u_duration1 lpi_bus_cmu_ebus_u_duration1; /* offset : 0x60f4 */
	union pmu_lpi_bus_cmu_ebus_u_duration2 lpi_bus_cmu_ebus_u_duration2; /* offset : 0x60f8 */
	union pmu_lpi_bus_cmu_ebus_u_duration3 lpi_bus_cmu_ebus_u_duration3; /* offset : 0x60fc */
	union pmu_lpi_bus_cmu_ebus_d_configuration lpi_bus_cmu_ebus_d_configuration; /* offset : 0x6100 */
	union pmu_lpi_bus_cmu_ebus_d_status lpi_bus_cmu_ebus_d_status; /* offset : 0x6104 */
	union pmu_lpi_bus_cmu_ebus_d_option lpi_bus_cmu_ebus_d_option; /* offset : 0x6108 */
	uint32_t reserved_326;
	union pmu_lpi_bus_cmu_ebus_d_duration0 lpi_bus_cmu_ebus_d_duration0; /* offset : 0x6110 */
	union pmu_lpi_bus_cmu_ebus_d_duration1 lpi_bus_cmu_ebus_d_duration1; /* offset : 0x6114 */
	union pmu_lpi_bus_cmu_ebus_d_duration2 lpi_bus_cmu_ebus_d_duration2; /* offset : 0x6118 */
	union pmu_lpi_bus_cmu_ebus_d_duration3 lpi_bus_cmu_ebus_d_duration3; /* offset : 0x611c */
	union pmu_lpi_bus_cmu_ebus_r_configuration lpi_bus_cmu_ebus_r_configuration; /* offset : 0x6120 */
	union pmu_lpi_bus_cmu_ebus_r_status lpi_bus_cmu_ebus_r_status; /* offset : 0x6124 */
	union pmu_lpi_bus_cmu_ebus_r_option lpi_bus_cmu_ebus_r_option; /* offset : 0x6128 */
	uint32_t reserved_327;
	union pmu_lpi_bus_cmu_ebus_r_duration0 lpi_bus_cmu_ebus_r_duration0; /* offset : 0x6130 */
	union pmu_lpi_bus_cmu_ebus_r_duration1 lpi_bus_cmu_ebus_r_duration1; /* offset : 0x6134 */
	union pmu_lpi_bus_cmu_ebus_r_duration2 lpi_bus_cmu_ebus_r_duration2; /* offset : 0x6138 */
	union pmu_lpi_bus_cmu_ebus_r_duration3 lpi_bus_cmu_ebus_r_duration3; /* offset : 0x613c */
	uint32_t reserved_328[48];
	union pmu_lpi_busmaster_cmu_cp0_configuration
			lpi_busmaster_cmu_cp0_configuration; /* offset : 0x6200 */
	union pmu_lpi_busmaster_cmu_cp0_status lpi_busmaster_cmu_cp0_status; /* offset : 0x6204 */
	union pmu_lpi_busmaster_cmu_cp0_option lpi_busmaster_cmu_cp0_option; /* offset : 0x6208 */
	uint32_t reserved_329;
	union pmu_lpi_busmaster_cmu_cp0_duration0 lpi_busmaster_cmu_cp0_duration0; /* offset : 0x6210 */
	union pmu_lpi_busmaster_cmu_cp0_duration1 lpi_busmaster_cmu_cp0_duration1; /* offset : 0x6214 */
	union pmu_lpi_busmaster_cmu_cp0_duration2 lpi_busmaster_cmu_cp0_duration2; /* offset : 0x6218 */
	union pmu_lpi_busmaster_cmu_cp0_duration3 lpi_busmaster_cmu_cp0_duration3; /* offset : 0x621c */
	union pmu_lpi_busmaster_cmu_cp1_configuration
			lpi_busmaster_cmu_cp1_configuration; /* offset : 0x6220 */
	union pmu_lpi_busmaster_cmu_cp1_status lpi_busmaster_cmu_cp1_status; /* offset : 0x6224 */
	union pmu_lpi_busmaster_cmu_cp1_option lpi_busmaster_cmu_cp1_option; /* offset : 0x6228 */
	uint32_t reserved_330;
	union pmu_lpi_busmaster_cmu_cp1_duration0 lpi_busmaster_cmu_cp1_duration0; /* offset : 0x6230 */
	union pmu_lpi_busmaster_cmu_cp1_duration1 lpi_busmaster_cmu_cp1_duration1; /* offset : 0x6234 */
	union pmu_lpi_busmaster_cmu_cp1_duration2 lpi_busmaster_cmu_cp1_duration2; /* offset : 0x6238 */
	union pmu_lpi_busmaster_cmu_cp1_duration3 lpi_busmaster_cmu_cp1_duration3; /* offset : 0x623c */
	union pmu_lpi_busmaster_cmu_pcie_configuration
			lpi_busmaster_cmu_pcie_configuration; /* offset : 0x6240 */
	union pmu_lpi_busmaster_cmu_pcie_status lpi_busmaster_cmu_pcie_status; /* offset : 0x6244 */
	union pmu_lpi_busmaster_cmu_pcie_option lpi_busmaster_cmu_pcie_option; /* offset : 0x6248 */
	uint32_t reserved_331;
	union pmu_lpi_busmaster_cmu_pcie_duration0 lpi_busmaster_cmu_pcie_duration0; /* offset : 0x6250 */
	union pmu_lpi_busmaster_cmu_pcie_duration1 lpi_busmaster_cmu_pcie_duration1; /* offset : 0x6254 */
	union pmu_lpi_busmaster_cmu_pcie_duration2 lpi_busmaster_cmu_pcie_duration2; /* offset : 0x6258 */
	union pmu_lpi_busmaster_cmu_pcie_duration3 lpi_busmaster_cmu_pcie_duration3; /* offset : 0x625c */
	union pmu_lpi_busmaster_cmu_dram_configuration
			lpi_busmaster_cmu_dram_configuration; /* offset : 0x6260 */
	union pmu_lpi_busmaster_cmu_dram_status lpi_busmaster_cmu_dram_status; /* offset : 0x6264 */
	union pmu_lpi_busmaster_cmu_dram_option lpi_busmaster_cmu_dram_option; /* offset : 0x6268 */
	uint32_t reserved_332;
	union pmu_lpi_busmaster_cmu_dram_duration0 lpi_busmaster_cmu_dram_duration0; /* offset : 0x6270 */
	union pmu_lpi_busmaster_cmu_dram_duration1 lpi_busmaster_cmu_dram_duration1; /* offset : 0x6274 */
	union pmu_lpi_busmaster_cmu_dram_duration2 lpi_busmaster_cmu_dram_duration2; /* offset : 0x6278 */
	union pmu_lpi_busmaster_cmu_dram_duration3 lpi_busmaster_cmu_dram_duration3; /* offset : 0x627c */
	union pmu_lpi_busmaster_cmu_dcl0_configuration
			lpi_busmaster_cmu_dcl0_configuration; /* offset : 0x6280 */
	union pmu_lpi_busmaster_cmu_dcl0_status lpi_busmaster_cmu_dcl0_status; /* offset : 0x6284 */
	union pmu_lpi_busmaster_cmu_dcl0_option lpi_busmaster_cmu_dcl0_option; /* offset : 0x6288 */
	uint32_t reserved_333;
	union pmu_lpi_busmaster_cmu_dcl0_duration0 lpi_busmaster_cmu_dcl0_duration0; /* offset : 0x6290 */
	union pmu_lpi_busmaster_cmu_dcl0_duration1 lpi_busmaster_cmu_dcl0_duration1; /* offset : 0x6294 */
	union pmu_lpi_busmaster_cmu_dcl0_duration2 lpi_busmaster_cmu_dcl0_duration2; /* offset : 0x6298 */
	union pmu_lpi_busmaster_cmu_dcl0_duration3 lpi_busmaster_cmu_dcl0_duration3; /* offset : 0x629c */
	union pmu_lpi_busmaster_cmu_dcl1_configuration
			lpi_busmaster_cmu_dcl1_configuration; /* offset : 0x62a0 */
	union pmu_lpi_busmaster_cmu_dcl1_status lpi_busmaster_cmu_dcl1_status; /* offset : 0x62a4 */
	union pmu_lpi_busmaster_cmu_dcl1_option lpi_busmaster_cmu_dcl1_option; /* offset : 0x62a8 */
	uint32_t reserved_334;
	union pmu_lpi_busmaster_cmu_dcl1_duration0 lpi_busmaster_cmu_dcl1_duration0; /* offset : 0x62b0 */
	union pmu_lpi_busmaster_cmu_dcl1_duration1 lpi_busmaster_cmu_dcl1_duration1; /* offset : 0x62b4 */
	union pmu_lpi_busmaster_cmu_dcl1_duration2 lpi_busmaster_cmu_dcl1_duration2; /* offset : 0x62b8 */
	union pmu_lpi_busmaster_cmu_dcl1_duration3 lpi_busmaster_cmu_dcl1_duration3; /* offset : 0x62bc */
	union pmu_lpi_busmaster_cmu_rbch00_configuration
			lpi_busmaster_cmu_rbch00_configuration; /* offset : 0x62c0 */
	union pmu_lpi_busmaster_cmu_rbch00_status lpi_busmaster_cmu_rbch00_status; /* offset : 0x62c4 */
	union pmu_lpi_busmaster_cmu_rbch00_option lpi_busmaster_cmu_rbch00_option; /* offset : 0x62c8 */
	uint32_t reserved_335;
	union pmu_lpi_busmaster_cmu_rbch00_duration0 lpi_busmaster_cmu_rbch00_duration0; /* offset : 0x62d0 */
	union pmu_lpi_busmaster_cmu_rbch00_duration1 lpi_busmaster_cmu_rbch00_duration1; /* offset : 0x62d4 */
	union pmu_lpi_busmaster_cmu_rbch00_duration2 lpi_busmaster_cmu_rbch00_duration2; /* offset : 0x62d8 */
	union pmu_lpi_busmaster_cmu_rbch00_duration3 lpi_busmaster_cmu_rbch00_duration3; /* offset : 0x62dc */
	union pmu_lpi_busmaster_cmu_rbch01_configuration
			lpi_busmaster_cmu_rbch01_configuration; /* offset : 0x62e0 */
	union pmu_lpi_busmaster_cmu_rbch01_status lpi_busmaster_cmu_rbch01_status; /* offset : 0x62e4 */
	union pmu_lpi_busmaster_cmu_rbch01_option lpi_busmaster_cmu_rbch01_option; /* offset : 0x62e8 */
	uint32_t reserved_336;
	union pmu_lpi_busmaster_cmu_rbch01_duration0 lpi_busmaster_cmu_rbch01_duration0; /* offset : 0x62f0 */
	union pmu_lpi_busmaster_cmu_rbch01_duration1 lpi_busmaster_cmu_rbch01_duration1; /* offset : 0x62f4 */
	union pmu_lpi_busmaster_cmu_rbch01_duration2 lpi_busmaster_cmu_rbch01_duration2; /* offset : 0x62f8 */
	union pmu_lpi_busmaster_cmu_rbch01_duration3 lpi_busmaster_cmu_rbch01_duration3; /* offset : 0x62fc */
	union pmu_lpi_busmaster_cmu_rbcv00_configuration
			lpi_busmaster_cmu_rbcv00_configuration; /* offset : 0x6300 */
	union pmu_lpi_busmaster_cmu_rbcv00_status lpi_busmaster_cmu_rbcv00_status; /* offset : 0x6304 */
	union pmu_lpi_busmaster_cmu_rbcv00_option lpi_busmaster_cmu_rbcv00_option; /* offset : 0x6308 */
	uint32_t reserved_337;
	union pmu_lpi_busmaster_cmu_rbcv00_duration0 lpi_busmaster_cmu_rbcv00_duration0; /* offset : 0x6310 */
	union pmu_lpi_busmaster_cmu_rbcv00_duration1 lpi_busmaster_cmu_rbcv00_duration1; /* offset : 0x6314 */
	union pmu_lpi_busmaster_cmu_rbcv00_duration2 lpi_busmaster_cmu_rbcv00_duration2; /* offset : 0x6318 */
	union pmu_lpi_busmaster_cmu_rbcv00_duration3 lpi_busmaster_cmu_rbcv00_duration3; /* offset : 0x631c */
	union pmu_lpi_busmaster_cmu_rbcv01_configuration
			lpi_busmaster_cmu_rbcv01_configuration; /* offset : 0x6320 */
	union pmu_lpi_busmaster_cmu_rbcv01_status lpi_busmaster_cmu_rbcv01_status; /* offset : 0x6324 */
	union pmu_lpi_busmaster_cmu_rbcv01_option lpi_busmaster_cmu_rbcv01_option; /* offset : 0x6328 */
	uint32_t reserved_338;
	union pmu_lpi_busmaster_cmu_rbcv01_duration0 lpi_busmaster_cmu_rbcv01_duration0; /* offset : 0x6330 */
	union pmu_lpi_busmaster_cmu_rbcv01_duration1 lpi_busmaster_cmu_rbcv01_duration1; /* offset : 0x6334 */
	union pmu_lpi_busmaster_cmu_rbcv01_duration2 lpi_busmaster_cmu_rbcv01_duration2; /* offset : 0x6338 */
	union pmu_lpi_busmaster_cmu_rbcv01_duration3 lpi_busmaster_cmu_rbcv01_duration3; /* offset : 0x633c */
	union pmu_lpi_busmaster_cmu_rbcv10_configuration
			lpi_busmaster_cmu_rbcv10_configuration; /* offset : 0x6340 */
	union pmu_lpi_busmaster_cmu_rbcv10_status lpi_busmaster_cmu_rbcv10_status; /* offset : 0x6344 */
	union pmu_lpi_busmaster_cmu_rbcv10_option lpi_busmaster_cmu_rbcv10_option; /* offset : 0x6348 */
	uint32_t reserved_339;
	union pmu_lpi_busmaster_cmu_rbcv10_duration0 lpi_busmaster_cmu_rbcv10_duration0; /* offset : 0x6350 */
	union pmu_lpi_busmaster_cmu_rbcv10_duration1 lpi_busmaster_cmu_rbcv10_duration1; /* offset : 0x6354 */
	union pmu_lpi_busmaster_cmu_rbcv10_duration2 lpi_busmaster_cmu_rbcv10_duration2; /* offset : 0x6358 */
	union pmu_lpi_busmaster_cmu_rbcv10_duration3 lpi_busmaster_cmu_rbcv10_duration3; /* offset : 0x635c */
	union pmu_lpi_busmaster_cmu_rbcv11_configuration
			lpi_busmaster_cmu_rbcv11_configuration; /* offset : 0x6360 */
	union pmu_lpi_busmaster_cmu_rbcv11_status lpi_busmaster_cmu_rbcv11_status; /* offset : 0x6364 */
	union pmu_lpi_busmaster_cmu_rbcv11_option lpi_busmaster_cmu_rbcv11_option; /* offset : 0x6368 */
	uint32_t reserved_340;
	union pmu_lpi_busmaster_cmu_rbcv11_duration0 lpi_busmaster_cmu_rbcv11_duration0; /* offset : 0x6370 */
	union pmu_lpi_busmaster_cmu_rbcv11_duration1 lpi_busmaster_cmu_rbcv11_duration1; /* offset : 0x6374 */
	union pmu_lpi_busmaster_cmu_rbcv11_duration2 lpi_busmaster_cmu_rbcv11_duration2; /* offset : 0x6378 */
	union pmu_lpi_busmaster_cmu_rbcv11_duration3 lpi_busmaster_cmu_rbcv11_duration3; /* offset : 0x637c */
	union pmu_lpi_busmaster_cmu_rot_configuration
			lpi_busmaster_cmu_rot_configuration; /* offset : 0x6380 */
	union pmu_lpi_busmaster_cmu_rot_status lpi_busmaster_cmu_rot_status; /* offset : 0x6384 */
	union pmu_lpi_busmaster_cmu_rot_option lpi_busmaster_cmu_rot_option; /* offset : 0x6388 */
	uint32_t reserved_341;
	union pmu_lpi_busmaster_cmu_rot_duration0 lpi_busmaster_cmu_rot_duration0; /* offset : 0x6390 */
	union pmu_lpi_busmaster_cmu_rot_duration1 lpi_busmaster_cmu_rot_duration1; /* offset : 0x6394 */
	union pmu_lpi_busmaster_cmu_rot_duration2 lpi_busmaster_cmu_rot_duration2; /* offset : 0x6398 */
	union pmu_lpi_busmaster_cmu_rot_duration3 lpi_busmaster_cmu_rot_duration3; /* offset : 0x639c */
	union pmu_lpi_busmaster_cmu_peri0_configuration
			lpi_busmaster_cmu_peri0_configuration; /* offset : 0x63a0 */
	union pmu_lpi_busmaster_cmu_peri0_status lpi_busmaster_cmu_peri0_status; /* offset : 0x63a4 */
	union pmu_lpi_busmaster_cmu_peri0_option lpi_busmaster_cmu_peri0_option; /* offset : 0x63a8 */
	uint32_t reserved_342;
	union pmu_lpi_busmaster_cmu_peri0_duration0 lpi_busmaster_cmu_peri0_duration0; /* offset : 0x63b0 */
	union pmu_lpi_busmaster_cmu_peri0_duration1 lpi_busmaster_cmu_peri0_duration1; /* offset : 0x63b4 */
	union pmu_lpi_busmaster_cmu_peri0_duration2 lpi_busmaster_cmu_peri0_duration2; /* offset : 0x63b8 */
	union pmu_lpi_busmaster_cmu_peri0_duration3 lpi_busmaster_cmu_peri0_duration3; /* offset : 0x63bc */
	union pmu_lpi_busmaster_cmu_peri1_configuration
			lpi_busmaster_cmu_peri1_configuration; /* offset : 0x63c0 */
	union pmu_lpi_busmaster_cmu_peri1_status lpi_busmaster_cmu_peri1_status; /* offset : 0x63c4 */
	union pmu_lpi_busmaster_cmu_peri1_option lpi_busmaster_cmu_peri1_option; /* offset : 0x63c8 */
	uint32_t reserved_343;
	union pmu_lpi_busmaster_cmu_peri1_duration0 lpi_busmaster_cmu_peri1_duration0; /* offset : 0x63d0 */
	union pmu_lpi_busmaster_cmu_peri1_duration1 lpi_busmaster_cmu_peri1_duration1; /* offset : 0x63d4 */
	union pmu_lpi_busmaster_cmu_peri1_duration2 lpi_busmaster_cmu_peri1_duration2; /* offset : 0x63d8 */
	union pmu_lpi_busmaster_cmu_peri1_duration3 lpi_busmaster_cmu_peri1_duration3; /* offset : 0x63dc */
	union pmu_lpi_busmaster_cmu_sbus_u_configuration
			lpi_busmaster_cmu_sbus_u_configuration; /* offset : 0x63e0 */
	union pmu_lpi_busmaster_cmu_sbus_u_status lpi_busmaster_cmu_sbus_u_status; /* offset : 0x63e4 */
	union pmu_lpi_busmaster_cmu_sbus_u_option lpi_busmaster_cmu_sbus_u_option; /* offset : 0x63e8 */
	uint32_t reserved_344;
	union pmu_lpi_busmaster_cmu_sbus_u_duration0 lpi_busmaster_cmu_sbus_u_duration0; /* offset : 0x63f0 */
	union pmu_lpi_busmaster_cmu_sbus_u_duration1 lpi_busmaster_cmu_sbus_u_duration1; /* offset : 0x63f4 */
	union pmu_lpi_busmaster_cmu_sbus_u_duration2 lpi_busmaster_cmu_sbus_u_duration2; /* offset : 0x63f8 */
	union pmu_lpi_busmaster_cmu_sbus_u_duration3 lpi_busmaster_cmu_sbus_u_duration3; /* offset : 0x63fc */
	union pmu_lpi_busmaster_cmu_sbus_d_configuration
			lpi_busmaster_cmu_sbus_d_configuration; /* offset : 0x6400 */
	union pmu_lpi_busmaster_cmu_sbus_d_status lpi_busmaster_cmu_sbus_d_status; /* offset : 0x6404 */
	union pmu_lpi_busmaster_cmu_sbus_d_option lpi_busmaster_cmu_sbus_d_option; /* offset : 0x6408 */
	uint32_t reserved_345;
	union pmu_lpi_busmaster_cmu_sbus_d_duration0 lpi_busmaster_cmu_sbus_d_duration0; /* offset : 0x6410 */
	union pmu_lpi_busmaster_cmu_sbus_d_duration1 lpi_busmaster_cmu_sbus_d_duration1; /* offset : 0x6414 */
	union pmu_lpi_busmaster_cmu_sbus_d_duration2 lpi_busmaster_cmu_sbus_d_duration2; /* offset : 0x6418 */
	union pmu_lpi_busmaster_cmu_sbus_d_duration3 lpi_busmaster_cmu_sbus_d_duration3; /* offset : 0x641c */
	union pmu_lpi_busmaster_cmu_sbus_l_configuration
			lpi_busmaster_cmu_sbus_l_configuration; /* offset : 0x6420 */
	union pmu_lpi_busmaster_cmu_sbus_l_status lpi_busmaster_cmu_sbus_l_status; /* offset : 0x6424 */
	union pmu_lpi_busmaster_cmu_sbus_l_option lpi_busmaster_cmu_sbus_l_option; /* offset : 0x6428 */
	uint32_t reserved_346;
	union pmu_lpi_busmaster_cmu_sbus_l_duration0 lpi_busmaster_cmu_sbus_l_duration0; /* offset : 0x6430 */
	union pmu_lpi_busmaster_cmu_sbus_l_duration1 lpi_busmaster_cmu_sbus_l_duration1; /* offset : 0x6434 */
	union pmu_lpi_busmaster_cmu_sbus_l_duration2 lpi_busmaster_cmu_sbus_l_duration2; /* offset : 0x6438 */
	union pmu_lpi_busmaster_cmu_sbus_l_duration3 lpi_busmaster_cmu_sbus_l_duration3; /* offset : 0x643c */
	union pmu_lpi_busmaster_cmu_nbus_u_configuration
			lpi_busmaster_cmu_nbus_u_configuration; /* offset : 0x6440 */
	union pmu_lpi_busmaster_cmu_nbus_u_status lpi_busmaster_cmu_nbus_u_status; /* offset : 0x6444 */
	union pmu_lpi_busmaster_cmu_nbus_u_option lpi_busmaster_cmu_nbus_u_option; /* offset : 0x6448 */
	uint32_t reserved_347;
	union pmu_lpi_busmaster_cmu_nbus_u_duration0 lpi_busmaster_cmu_nbus_u_duration0; /* offset : 0x6450 */
	union pmu_lpi_busmaster_cmu_nbus_u_duration1 lpi_busmaster_cmu_nbus_u_duration1; /* offset : 0x6454 */
	union pmu_lpi_busmaster_cmu_nbus_u_duration2 lpi_busmaster_cmu_nbus_u_duration2; /* offset : 0x6458 */
	union pmu_lpi_busmaster_cmu_nbus_u_duration3 lpi_busmaster_cmu_nbus_u_duration3; /* offset : 0x645c */
	union pmu_lpi_busmaster_cmu_nbus_d_configuration
			lpi_busmaster_cmu_nbus_d_configuration; /* offset : 0x6460 */
	union pmu_lpi_busmaster_cmu_nbus_d_status lpi_busmaster_cmu_nbus_d_status; /* offset : 0x6464 */
	union pmu_lpi_busmaster_cmu_nbus_d_option lpi_busmaster_cmu_nbus_d_option; /* offset : 0x6468 */
	uint32_t reserved_348;
	union pmu_lpi_busmaster_cmu_nbus_d_duration0 lpi_busmaster_cmu_nbus_d_duration0; /* offset : 0x6470 */
	union pmu_lpi_busmaster_cmu_nbus_d_duration1 lpi_busmaster_cmu_nbus_d_duration1; /* offset : 0x6474 */
	union pmu_lpi_busmaster_cmu_nbus_d_duration2 lpi_busmaster_cmu_nbus_d_duration2; /* offset : 0x6478 */
	union pmu_lpi_busmaster_cmu_nbus_d_duration3 lpi_busmaster_cmu_nbus_d_duration3; /* offset : 0x647c */
	union pmu_lpi_busmaster_cmu_nbus_l_configuration
			lpi_busmaster_cmu_nbus_l_configuration; /* offset : 0x6480 */
	union pmu_lpi_busmaster_cmu_nbus_l_status lpi_busmaster_cmu_nbus_l_status; /* offset : 0x6484 */
	union pmu_lpi_busmaster_cmu_nbus_l_option lpi_busmaster_cmu_nbus_l_option; /* offset : 0x6488 */
	uint32_t reserved_349;
	union pmu_lpi_busmaster_cmu_nbus_l_duration0 lpi_busmaster_cmu_nbus_l_duration0; /* offset : 0x6490 */
	union pmu_lpi_busmaster_cmu_nbus_l_duration1 lpi_busmaster_cmu_nbus_l_duration1; /* offset : 0x6494 */
	union pmu_lpi_busmaster_cmu_nbus_l_duration2 lpi_busmaster_cmu_nbus_l_duration2; /* offset : 0x6498 */
	union pmu_lpi_busmaster_cmu_nbus_l_duration3 lpi_busmaster_cmu_nbus_l_duration3; /* offset : 0x649c */
	union pmu_lpi_busmaster_cmu_wbus_u_configuration
			lpi_busmaster_cmu_wbus_u_configuration; /* offset : 0x64a0 */
	union pmu_lpi_busmaster_cmu_wbus_u_status lpi_busmaster_cmu_wbus_u_status; /* offset : 0x64a4 */
	union pmu_lpi_busmaster_cmu_wbus_u_option lpi_busmaster_cmu_wbus_u_option; /* offset : 0x64a8 */
	uint32_t reserved_350;
	union pmu_lpi_busmaster_cmu_wbus_u_duration0 lpi_busmaster_cmu_wbus_u_duration0; /* offset : 0x64b0 */
	union pmu_lpi_busmaster_cmu_wbus_u_duration1 lpi_busmaster_cmu_wbus_u_duration1; /* offset : 0x64b4 */
	union pmu_lpi_busmaster_cmu_wbus_u_duration2 lpi_busmaster_cmu_wbus_u_duration2; /* offset : 0x64b8 */
	union pmu_lpi_busmaster_cmu_wbus_u_duration3 lpi_busmaster_cmu_wbus_u_duration3; /* offset : 0x64bc */
	union pmu_lpi_busmaster_cmu_wbus_d_configuration
			lpi_busmaster_cmu_wbus_d_configuration; /* offset : 0x64c0 */
	union pmu_lpi_busmaster_cmu_wbus_d_status lpi_busmaster_cmu_wbus_d_status; /* offset : 0x64c4 */
	union pmu_lpi_busmaster_cmu_wbus_d_option lpi_busmaster_cmu_wbus_d_option; /* offset : 0x64c8 */
	uint32_t reserved_351;
	union pmu_lpi_busmaster_cmu_wbus_d_duration0 lpi_busmaster_cmu_wbus_d_duration0; /* offset : 0x64d0 */
	union pmu_lpi_busmaster_cmu_wbus_d_duration1 lpi_busmaster_cmu_wbus_d_duration1; /* offset : 0x64d4 */
	union pmu_lpi_busmaster_cmu_wbus_d_duration2 lpi_busmaster_cmu_wbus_d_duration2; /* offset : 0x64d8 */
	union pmu_lpi_busmaster_cmu_wbus_d_duration3 lpi_busmaster_cmu_wbus_d_duration3; /* offset : 0x64dc */
	union pmu_lpi_busmaster_cmu_ebus_u_configuration
			lpi_busmaster_cmu_ebus_u_configuration; /* offset : 0x64e0 */
	union pmu_lpi_busmaster_cmu_ebus_u_status lpi_busmaster_cmu_ebus_u_status; /* offset : 0x64e4 */
	union pmu_lpi_busmaster_cmu_ebus_u_option lpi_busmaster_cmu_ebus_u_option; /* offset : 0x64e8 */
	uint32_t reserved_352;
	union pmu_lpi_busmaster_cmu_ebus_u_duration0 lpi_busmaster_cmu_ebus_u_duration0; /* offset : 0x64f0 */
	union pmu_lpi_busmaster_cmu_ebus_u_duration1 lpi_busmaster_cmu_ebus_u_duration1; /* offset : 0x64f4 */
	union pmu_lpi_busmaster_cmu_ebus_u_duration2 lpi_busmaster_cmu_ebus_u_duration2; /* offset : 0x64f8 */
	union pmu_lpi_busmaster_cmu_ebus_u_duration3 lpi_busmaster_cmu_ebus_u_duration3; /* offset : 0x64fc */
	union pmu_lpi_busmaster_cmu_ebus_d_configuration
			lpi_busmaster_cmu_ebus_d_configuration; /* offset : 0x6500 */
	union pmu_lpi_busmaster_cmu_ebus_d_status lpi_busmaster_cmu_ebus_d_status; /* offset : 0x6504 */
	union pmu_lpi_busmaster_cmu_ebus_d_option lpi_busmaster_cmu_ebus_d_option; /* offset : 0x6508 */
	uint32_t reserved_353;
	union pmu_lpi_busmaster_cmu_ebus_d_duration0 lpi_busmaster_cmu_ebus_d_duration0; /* offset : 0x6510 */
	union pmu_lpi_busmaster_cmu_ebus_d_duration1 lpi_busmaster_cmu_ebus_d_duration1; /* offset : 0x6514 */
	union pmu_lpi_busmaster_cmu_ebus_d_duration2 lpi_busmaster_cmu_ebus_d_duration2; /* offset : 0x6518 */
	union pmu_lpi_busmaster_cmu_ebus_d_duration3 lpi_busmaster_cmu_ebus_d_duration3; /* offset : 0x651c */
	union pmu_lpi_busmaster_cmu_ebus_r_configuration
			lpi_busmaster_cmu_ebus_r_configuration; /* offset : 0x6520 */
	union pmu_lpi_busmaster_cmu_ebus_r_status lpi_busmaster_cmu_ebus_r_status; /* offset : 0x6524 */
	union pmu_lpi_busmaster_cmu_ebus_r_option lpi_busmaster_cmu_ebus_r_option; /* offset : 0x6528 */
	uint32_t reserved_354;
	union pmu_lpi_busmaster_cmu_ebus_r_duration0 lpi_busmaster_cmu_ebus_r_duration0; /* offset : 0x6530 */
	union pmu_lpi_busmaster_cmu_ebus_r_duration1 lpi_busmaster_cmu_ebus_r_duration1; /* offset : 0x6534 */
	union pmu_lpi_busmaster_cmu_ebus_r_duration2 lpi_busmaster_cmu_ebus_r_duration2; /* offset : 0x6538 */
	union pmu_lpi_busmaster_cmu_ebus_r_duration3 lpi_busmaster_cmu_ebus_r_duration3; /* offset : 0x653c */
	uint32_t reserved_355[72];
	union pmu_lpi_hbm_cmu_dram_configuration lpi_hbm_cmu_dram_configuration; /* offset : 0x6660 */
	union pmu_lpi_hbm_cmu_dram_status lpi_hbm_cmu_dram_status; /* offset : 0x6664 */
	union pmu_lpi_hbm_cmu_dram_option lpi_hbm_cmu_dram_option; /* offset : 0x6668 */
	uint32_t reserved_356;
	union pmu_lpi_hbm_cmu_dram_duration0 lpi_hbm_cmu_dram_duration0; /* offset : 0x6670 */
	union pmu_lpi_hbm_cmu_dram_duration1 lpi_hbm_cmu_dram_duration1; /* offset : 0x6674 */
	union pmu_lpi_hbm_cmu_dram_duration2 lpi_hbm_cmu_dram_duration2; /* offset : 0x6678 */
	union pmu_lpi_hbm_cmu_dram_duration3 lpi_hbm_cmu_dram_duration3; /* offset : 0x667c */
	uint32_t reserved_357[496];
	union pmu_cm7_cpu_pcie_configuration cm7_cpu_pcie_configuration; /* offset : 0x6e40 */
	union pmu_cm7_cpu_pcie_status cm7_cpu_pcie_status; /* offset : 0x6e44 */
	union pmu_cm7_cpu_pcie_option cm7_cpu_pcie_option; /* offset : 0x6e48 */
	union pmu_cm7_cpu_pcie_reset cm7_cpu_pcie_reset; /* offset : 0x6e4c */
	union pmu_cm7_cpu_pcie_duration0 cm7_cpu_pcie_duration0; /* offset : 0x6e50 */
	union pmu_cm7_cpu_pcie_duration1 cm7_cpu_pcie_duration1; /* offset : 0x6e54 */
	union pmu_cm7_cpu_pcie_duration2 cm7_cpu_pcie_duration2; /* offset : 0x6e58 */
	union pmu_cm7_cpu_pcie_duration3 cm7_cpu_pcie_duration3; /* offset : 0x6e5c */
	uint32_t reserved_358[104];
	union pmu_jtag_dbg_det jtag_dbg_det; /* offset : 0x7000 */
	union pmu_cluster0_corerst_lock cluster0_corerst_lock; /* offset : 0x7004 */
	union pmu_cluster1_corerst_lock cluster1_corerst_lock; /* offset : 0x7008 */
	union pmu_cm7_corerst_lock cm7_corerst_lock; /* offset : 0x700c */
	uint32_t reserved_359[508];
	union pmu_irq_selection irq_selection; /* offset : 0x7800 */
	uint32_t reserved_360[696];
	union pmu_tcxo_status tcxo_status; /* offset : 0x82e4 */
	union pmu_tcxo_option tcxo_option; /* offset : 0x82e8 */
	uint32_t reserved_361;
	union pmu_tcxo_duration0 tcxo_duration0; /* offset : 0x82f0 */
	union pmu_tcxo_duration1 tcxo_duration1; /* offset : 0x82f4 */
	union pmu_tcxo_duration2 tcxo_duration2; /* offset : 0x82f8 */
	union pmu_tcxo_duration3 tcxo_duration3; /* offset : 0x82fc */
};

uint32_t pmu_get_bootmode(void);
void pmu_sw_reset(void);
void pmu_rbc_lpi_entry(uint32_t blk_rbc_id);
void pmu_rbc_lpi_exit(uint32_t blk_rbc_id);
uint32_t pmu_get_num_of_secondary_chiplet(void);
