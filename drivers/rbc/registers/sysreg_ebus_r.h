/*
 * Copyright 2024 Samsung Electronics Co., Ltd. All Rights Reserved.
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

union sysreg_ebus_r_user_reg0 {
	struct {
		uint32_t spare; /* [31:0] */
	};
	uint32_t val;
};

union sysreg_ebus_r_user_reg1 {
	struct {
		uint32_t spare; /* [31:0] */
	};
	uint32_t val;
};

union sysreg_ebus_r_user_reg2 {
	struct {
		uint32_t spare; /* [31:0] */
	};
	uint32_t val;
};

union sysreg_ebus_r_user_reg3 {
	struct {
		uint32_t spare; /* [31:0] */
	};
	uint32_t val;
};

union sysreg_ebus_r_user_reg4 {
	struct {
		uint32_t spare; /* [31:0] */
	};
	uint32_t val;
};

union sysreg_ebus_r_sfr_apb {
	struct {
		uint32_t en_timeout:1; /* [0:0] */
	};
	uint32_t val;
};

union sysreg_ebus_r_bus_component_drcg_en {
	struct {
		uint32_t reserved_bit_0:6;
		uint32_t ast_ebus_rs_ast1_drcg_en:1; /* [6:6] */
		uint32_t ast_ebus_rs_ast0_drcg_en:1; /* [7:7] */
		uint32_t ast_ebus_rm_ast1_drcg_en:1; /* [8:8] */
		uint32_t ast_ebus_rm_ast0_drcg_en:1; /* [9:9] */
		uint32_t p_dcl1s_dp3_drcg_en:1; /* [10:10] */
		uint32_t p_dcl0s_dp3_drcg_en:1; /* [11:11] */
		uint32_t p_dcl1s_p_drcg_en:1; /* [12:12] */
		uint32_t p_dcl0s_p_drcg_en:1; /* [13:13] */
		uint32_t p_rbc_h01s_p0_drcg_en:1; /* [14:14] */
		uint32_t p_rbc_h00s_p0_drcg_en:1; /* [15:15] */
		uint32_t p_rbc_h01m_p0_drcg_en:1; /* [16:16] */
		uint32_t p_rbc_h00m_p0_drcg_en:1; /* [17:17] */
		uint32_t p_rbc_h01s_p_drcg_en:1; /* [18:18] */
		uint32_t p_rbc_h00s_p_drcg_en:1; /* [19:19] */
		uint32_t d_dcl1s_dd3_drcg_en:1; /* [20:20] */
		uint32_t d_dcl0s_dd3_drcg_en:1; /* [21:21] */
		uint32_t d_dcl1m_dd3_drcg_en:1; /* [22:22] */
		uint32_t d_dcl0m_dd3_drcg_en:1; /* [23:23] */
		uint32_t d_rbc_h01m_d1_drcg_en:1; /* [24:24] */
		uint32_t d_rbc_h01s_d1_drcg_en:1; /* [25:25] */
		uint32_t d_rbc_h01m_d0_drcg_en:1; /* [26:26] */
		uint32_t d_rbc_h01s_d0_drcg_en:1; /* [27:27] */
		uint32_t d_rbc_h00m_d1_drcg_en:1; /* [28:28] */
		uint32_t d_rbc_h00s_d1_drcg_en:1; /* [29:29] */
		uint32_t d_rbc_h00m_d0_drcg_en:1; /* [30:30] */
		uint32_t d_rbc_h00s_d0_drcg_en:1; /* [31:31] */
	};
	uint32_t val;
};

union sysreg_ebus_r_tzpc_prot0stat {
	struct {
		uint32_t tzpc0:1; /* [0:0] */
		uint32_t tzpc1:1; /* [1:1] */
		uint32_t tzpc2:1; /* [2:2] */
		uint32_t tzpc3:1; /* [3:3] */
		uint32_t tzpc4:1; /* [4:4] */
		uint32_t tzpc5:1; /* [5:5] */
		uint32_t tzpc6:1; /* [6:6] */
		uint32_t tzpc7:1; /* [7:7] */
		uint32_t tzpc8:1; /* [8:8] */
		uint32_t tzpc9:1; /* [9:9] */
		uint32_t tzpc10:1; /* [10:10] */
		uint32_t tzpc11:1; /* [11:11] */
		uint32_t tzpc12:1; /* [12:12] */
		uint32_t tzpc13:1; /* [13:13] */
		uint32_t tzpc14:1; /* [14:14] */
		uint32_t tzpc15:1; /* [15:15] */
		uint32_t tzpc16:1; /* [16:16] */
		uint32_t tzpc17:1; /* [17:17] */
		uint32_t tzpc18:1; /* [18:18] */
		uint32_t tzpc19:1; /* [19:19] */
		uint32_t tzpc20:1; /* [20:20] */
		uint32_t tzpc21:1; /* [21:21] */
		uint32_t tzpc22:1; /* [22:22] */
		uint32_t tzpc23:1; /* [23:23] */
		uint32_t tzpc24:1; /* [24:24] */
		uint32_t tzpc25:1; /* [25:25] */
		uint32_t tzpc26:1; /* [26:26] */
		uint32_t tzpc27:1; /* [27:27] */
		uint32_t tzpc28:1; /* [28:28] */
		uint32_t tzpc29:1; /* [29:29] */
		uint32_t tzpc30:1; /* [30:30] */
		uint32_t tzpc31:1; /* [31:31] */
	};
	uint32_t val;
};

union sysreg_ebus_r_tzpc_prot0set {
	struct {
		uint32_t protset; /* [31:0] */
	};
	uint32_t val;
};

union sysreg_ebus_r_tzpc_prot0clr {
	struct {
		uint32_t protclr; /* [31:0] */
	};
	uint32_t val;
};

union sysreg_ebus_r_tzpc_prot1stat {
	struct {
		uint32_t tzpc0:1; /* [0:0] */
		uint32_t tzpc1:1; /* [1:1] */
		uint32_t tzpc2:1; /* [2:2] */
		uint32_t tzpc3:1; /* [3:3] */
		uint32_t tzpc4:1; /* [4:4] */
		uint32_t tzpc5:1; /* [5:5] */
		uint32_t tzpc6:1; /* [6:6] */
		uint32_t tzpc7:1; /* [7:7] */
		uint32_t tzpc8:1; /* [8:8] */
		uint32_t tzpc9:1; /* [9:9] */
		uint32_t tzpc10:1; /* [10:10] */
		uint32_t tzpc11:1; /* [11:11] */
		uint32_t tzpc12:1; /* [12:12] */
		uint32_t tzpc13:1; /* [13:13] */
		uint32_t tzpc14:1; /* [14:14] */
		uint32_t tzpc15:1; /* [15:15] */
		uint32_t tzpc16:1; /* [16:16] */
		uint32_t tzpc17:1; /* [17:17] */
		uint32_t tzpc18:1; /* [18:18] */
		uint32_t tzpc19:1; /* [19:19] */
		uint32_t tzpc20:1; /* [20:20] */
		uint32_t tzpc21:1; /* [21:21] */
		uint32_t tzpc22:1; /* [22:22] */
		uint32_t tzpc23:1; /* [23:23] */
		uint32_t tzpc24:1; /* [24:24] */
		uint32_t tzpc25:1; /* [25:25] */
		uint32_t tzpc26:1; /* [26:26] */
		uint32_t tzpc27:1; /* [27:27] */
		uint32_t tzpc28:1; /* [28:28] */
		uint32_t tzpc29:1; /* [29:29] */
		uint32_t tzpc30:1; /* [30:30] */
		uint32_t tzpc31:1; /* [31:31] */
	};
	uint32_t val;
};

union sysreg_ebus_r_tzpc_prot1set {
	struct {
		uint32_t protset; /* [31:0] */
	};
	uint32_t val;
};

union sysreg_ebus_r_tzpc_prot1clr {
	struct {
		uint32_t protclr; /* [31:0] */
	};
	uint32_t val;
};

union sysreg_ebus_r_tzpc_r0size {
	struct {
		uint32_t r0size:10; /* [9:0] */
	};
	uint32_t val;
};

union sysreg_ebus_r_lpp_mcs {
	struct {
		uint32_t rf1_hs_mcs:2; /* [1:0] */
		uint32_t reserved_bit_0:2;
		uint32_t ra1_hs_mcs:2; /* [5:4] */
		uint32_t reserved_bit_1:2;
		uint32_t rf1_uhd_mcs:2; /* [9:8] */
		uint32_t reserved_bit_2:2;
		uint32_t ra1_uhd_mcs:2; /* [13:12] */
		uint32_t reserved_bit_3:2;
		uint32_t vrom_hd_mcs:1; /* [16:16] */
		uint32_t reserved_bit_4:3;
		uint32_t ra1_uhs_mcs:2; /* [21:20] */
	};
	uint32_t val;
};

union sysreg_ebus_r_lpp_mcsw {
	struct {
		uint32_t rf1_hs_mcsw:1; /* [0:0] */
		uint32_t reserved_bit_0:3;
		uint32_t ra1_hs_mcsw:1; /* [4:4] */
		uint32_t reserved_bit_1:3;
		uint32_t rf1_uhd_mcsw:1; /* [8:8] */
		uint32_t reserved_bit_2:3;
		uint32_t ra1_uhd_mcsw:1; /* [12:12] */
		uint32_t reserved_bit_3:3;
		uint32_t ra1_uhs_mcsw:1; /* [16:16] */
	};
	uint32_t val;
};

union sysreg_ebus_r_lpp_mcsrd {
	struct {
		uint32_t rf2_hs_mcsrd:2; /* [1:0] */
		uint32_t reserved_bit_0:2;
		uint32_t rd2_uhd_mcsrd:2; /* [5:4] */
		uint32_t reserved_bit_1:2;
		uint32_t rd2_hs_mcsrd:2; /* [9:8] */
		uint32_t reserved_bit_2:2;
		uint32_t rf2_uhs_mcsrd:2; /* [13:12] */
		uint32_t reserved_bit_3:2;
		uint32_t rd2_uhs_mcsrd:2; /* [17:16] */
	};
	uint32_t val;
};

union sysreg_ebus_r_lpp_mcswr {
	struct {
		uint32_t rf2_hs_mcswr:2; /* [1:0] */
		uint32_t reserved_bit_0:2;
		uint32_t rd2_uhd_mcswr:2; /* [5:4] */
		uint32_t reserved_bit_1:2;
		uint32_t rd2_hs_mcswr:2; /* [9:8] */
		uint32_t reserved_bit_2:2;
		uint32_t rf2_uhs_mcswr:2; /* [13:12] */
		uint32_t reserved_bit_3:2;
		uint32_t rd2_uhs_mcswr:2; /* [17:16] */
	};
	uint32_t val;
};

union sysreg_ebus_r_lpp_mcscc {
	struct {
		uint32_t rd2_uhs_mcscc:2; /* [1:0] */
	};
	uint32_t val;
};

union sysreg_ebus_r_lpp_kcs {
	struct {
		uint32_t rf2_hs_kcs:1; /* [0:0] */
		uint32_t reserved_bit_0:3;
		uint32_t vrom_hd_kcs:1; /* [4:4] */
		uint32_t reserved_bit_1:3;
		uint32_t rf2_uhs_kcs:1; /* [8:8] */
	};
	uint32_t val;
};

union sysreg_ebus_r_lpp_adme {
	struct {
		uint32_t rf2_uhs_adme:3; /* [2:0] */
		uint32_t rd2_uhs_adme:3; /* [5:3] */
		uint32_t ra1_uhs_adme:3; /* [8:6] */
		uint32_t rf2_hs_adme:3; /* [11:9] */
		uint32_t rd2_hs_adme:3; /* [14:12] */
		uint32_t rf1_hs_adme:3; /* [17:15] */
		uint32_t ra1_hs_adme:3; /* [20:18] */
		uint32_t rd2_uhd_adme:3; /* [23:21] */
		uint32_t rf1_uhd_adme:3; /* [26:24] */
		uint32_t ra1_uhd_adme:3; /* [29:27] */
	};
	uint32_t val;
};

union sysreg_ebus_r_lpp_wrme {
	struct {
		uint32_t rd2_uhd_wrme:2; /* [1:0] */
		uint32_t reserved_bit_0:2;
		uint32_t rf1_uhd_wrme:2; /* [5:4] */
		uint32_t reserved_bit_1:2;
		uint32_t ra1_uhd_wrme:2; /* [9:8] */
	};
	uint32_t val;
};

union sysreg_ebus_r_lpp_bpe {
	struct {
		uint32_t rd2_uhs_bpe:1; /* [0:0] */
	};
	uint32_t val;
};

union sysreg_ebus_r_lpp_bce {
	struct {
		uint32_t rd2_uhs_bce:1; /* [0:0] */
	};
	uint32_t val;
};

union sysreg_ebus_r_rbcsw_cntl {
	struct {
		uint32_t i_rbc_ch0_sw:1; /* [0:0] */
		uint32_t reserved_bit_0:7;
		uint32_t i_rbc_ch1_sw:1; /* [8:8] */
		uint32_t reserved_bit_1:7;
		uint32_t i_rbc_ch2_sw:1; /* [16:16] */
		uint32_t reserved_bit_2:7;
		uint32_t i_rbc_ch3_sw:1; /* [24:24] */
	};
	uint32_t val;
};

union sysreg_ebus_r_rbcsw_detour {
	struct {
		uint32_t i_detour_ch0_en:1; /* [0:0] */
		uint32_t reserved_bit_0:7;
		uint32_t i_detour_ch1_en:1; /* [8:8] */
		uint32_t reserved_bit_1:7;
		uint32_t i_detour_ch2_en:1; /* [16:16] */
		uint32_t reserved_bit_2:7;
		uint32_t i_detour_ch3_en:1; /* [24:24] */
	};
	uint32_t val;
};

union sysreg_ebus_r_axi_demux_detour {
	struct {
		uint32_t i_detour_en:1; /* [0:0] */
	};
	uint32_t val;
};

union sysreg_ebus_r_noc_timeout_refclk_div {
	struct {
		uint32_t refclk_div:3; /* [2:0] */
	};
	uint32_t val;
};

union sysreg_ebus_r_noc_timeout_ext_en {
	struct {
		uint32_t rbce_ch0_r:1; /* [0:0] */
		uint32_t rbce_ch1_r:1; /* [1:1] */
		uint32_t rbce_ch2_r:1; /* [2:2] */
		uint32_t rbce_ch3_r:1; /* [3:3] */
		uint32_t t_dnc_cl0_ch3_r:1; /* [4:4] */
		uint32_t t_dnc_cl1_ch3_r:1; /* [5:5] */
		uint32_t rbce_ch0_w:1; /* [6:6] */
		uint32_t rbce_ch1_w:1; /* [7:7] */
		uint32_t rbce_ch2_w:1; /* [8:8] */
		uint32_t rbce_ch3_w:1; /* [9:9] */
		uint32_t t_dnc_cl0_ch3_w:1; /* [10:10] */
		uint32_t t_dnc_cl1_ch3_w:1; /* [11:11] */
		uint32_t t_axi2apb_dcl0:1; /* [12:12] */
		uint32_t t_axi2apb_dcl1:1; /* [13:13] */
		uint32_t t_axi2apb_ebus:1; /* [14:14] */
		uint32_t t_axi2apb_rbce0:1; /* [15:15] */
		uint32_t t_axi2apb_rbce1:1; /* [16:16] */
		uint32_t t_rbces:1; /* [17:17] */
		uint32_t t_axi2apb_dbg:1; /* [18:18] */
	};
	uint32_t val;
};

union sysreg_ebus_r_noc_timeout_ext_en2 {
	struct {
		uint32_t t_dcl0_ch3:1; /* [0:0] */
		uint32_t t_dcl1_ch3:1; /* [1:1] */
	};
	uint32_t val;
};

union sysreg_ebus_r_noc_probe_status {
	struct {
		uint32_t probe_status_dnc0_w_mainstatalarm:1; /* [0:0] */
		uint32_t probe_status_dnc1_w_mainstatalarm:1; /* [1:1] */
		uint32_t probe_status_dnc0_r_mainstatalarm:1; /* [2:2] */
		uint32_t probe_status_dnc1_r_mainstatalarm:1; /* [3:3] */
	};
	uint32_t val;
};

union sysreg_ebus_r_tbu_smmu_pmu_snapshot_req {
	struct {
		uint32_t snapshot_req_cl0:1; /* [0:0] */
		uint32_t snapshot_req_cl1:1; /* [1:1] */
		uint32_t snapshot_req:6; /* [7:2] */
	};
	uint32_t val;
};

union sysreg_ebus_r_tbu_smmu_pmu_snapshot_ack {
	struct {
		uint32_t snapshot_ack_cl0:1; /* [0:0] */
		uint32_t snapshot_ack_cl1:1; /* [1:1] */
		uint32_t snapshot_ack:6; /* [7:2] */
	};
	uint32_t val;
};

union sysreg_ebus_r_smmu_pcie_mode {
	struct {
		uint32_t pcie_mode_cl0:1; /* [0:0] */
		uint32_t pcie_mode_cl1:1; /* [1:1] */
	};
	uint32_t val;
};

union sysreg_ebus_r_smmu_max_tok_trans {
	struct {
		uint32_t max_tok_trans_tbu_dglue_cl0:3; /* [2:0] */
		uint32_t reserved_bit_0:1;
		uint32_t max_tok_trans_tbu_dglue_cl1:3; /* [6:4] */
	};
	uint32_t val;
};

union sysreg_ebus_r_smmu_etc {
	struct {
		uint32_t tbu_if_en_cl0:1; /* [0:0] */
		uint32_t err_irpt_enable_cl0:1; /* [1:1] */
		uint32_t tbu_if_en_cl1:1; /* [2:2] */
		uint32_t err_irpt_enable_cl1:1; /* [3:3] */
	};
	uint32_t val;
};

union sysreg_ebus_r_rbc_h00_pch_mux_preq {
	struct {
		uint32_t i_preq_sfr:1; /* [0:0] */
	};
	uint32_t val;
};

union sysreg_ebus_r_rbc_h00_pch_mux_pstate {
	struct {
		uint32_t i_pstate_sfr:1; /* [0:0] */
	};
	uint32_t val;
};

union sysreg_ebus_r_rbc_h00_pch_mux_sel {
	struct {
		uint32_t i_pch_mux_sel:1; /* [0:0] */
	};
	uint32_t val;
};

union sysreg_ebus_r_rbc_h00_pch_mux_ro {
	struct {
		uint32_t o_pch_mon_sfr:2; /* [1:0] */
		uint32_t o_paccept_sfr:1; /* [2:2] */
	};
	uint32_t val;
};

union sysreg_ebus_r_rbc_h01_pch_mux_preq {
	struct {
		uint32_t i_preq_sfr:1; /* [0:0] */
	};
	uint32_t val;
};

union sysreg_ebus_r_rbc_h01_pch_mux_pstate {
	struct {
		uint32_t i_pstate_sfr:1; /* [0:0] */
	};
	uint32_t val;
};

union sysreg_ebus_r_rbc_h01_pch_mux_sel {
	struct {
		uint32_t i_pch_mux_sel:1; /* [0:0] */
	};
	uint32_t val;
};

union sysreg_ebus_r_rbc_h01_pch_mux_ro {
	struct {
		uint32_t o_pch_mon_sfr:2; /* [1:0] */
		uint32_t o_paccept_sfr:1; /* [2:2] */
	};
	uint32_t val;
};

struct sysreg_ebus_r {
	union sysreg_ebus_r_user_reg0 user_reg0; /* offset : 0x0 */
	union sysreg_ebus_r_user_reg1 user_reg1; /* offset : 0x4 */
	union sysreg_ebus_r_user_reg2 user_reg2; /* offset : 0x8 */
	union sysreg_ebus_r_user_reg3 user_reg3; /* offset : 0xc */
	union sysreg_ebus_r_user_reg4 user_reg4; /* offset : 0x10 */
	uint32_t reserved_1[59];
	union sysreg_ebus_r_sfr_apb sfr_apb; /* offset : 0x100 */
	union sysreg_ebus_r_bus_component_drcg_en bus_component_drcg_en; /* offset : 0x104 */
	uint32_t reserved_2[62];
	union sysreg_ebus_r_tzpc_prot0stat tzpc_prot0stat; /* offset : 0x200 */
	union sysreg_ebus_r_tzpc_prot0set tzpc_prot0set; /* offset : 0x204 */
	union sysreg_ebus_r_tzpc_prot0clr tzpc_prot0clr; /* offset : 0x208 */
	uint32_t reserved_3;
	union sysreg_ebus_r_tzpc_prot1stat tzpc_prot1stat; /* offset : 0x210 */
	union sysreg_ebus_r_tzpc_prot1set tzpc_prot1set; /* offset : 0x214 */
	union sysreg_ebus_r_tzpc_prot1clr tzpc_prot1clr; /* offset : 0x218 */
	uint32_t reserved_4;
	union sysreg_ebus_r_tzpc_r0size tzpc_r0size; /* offset : 0x220 */
	uint32_t reserved_5[3];
	union sysreg_ebus_r_lpp_mcs lpp_mcs; /* offset : 0x230 */
	union sysreg_ebus_r_lpp_mcsw lpp_mcsw; /* offset : 0x234 */
	union sysreg_ebus_r_lpp_mcsrd lpp_mcsrd; /* offset : 0x238 */
	union sysreg_ebus_r_lpp_mcswr lpp_mcswr; /* offset : 0x23c */
	union sysreg_ebus_r_lpp_mcscc lpp_mcscc; /* offset : 0x240 */
	union sysreg_ebus_r_lpp_kcs lpp_kcs; /* offset : 0x244 */
	union sysreg_ebus_r_lpp_adme lpp_adme; /* offset : 0x248 */
	union sysreg_ebus_r_lpp_wrme lpp_wrme; /* offset : 0x24c */
	union sysreg_ebus_r_lpp_bpe lpp_bpe; /* offset : 0x250 */
	union sysreg_ebus_r_lpp_bce lpp_bce; /* offset : 0x254 */
	uint32_t reserved_6[106];
	union sysreg_ebus_r_rbcsw_cntl rbcsw_cntl; /* offset : 0x400 */
	union sysreg_ebus_r_rbcsw_detour rbcsw_detour; /* offset : 0x404 */
	union sysreg_ebus_r_axi_demux_detour axi_demux_detour; /* offset : 0x408 */
	uint32_t reserved_7;
	union sysreg_ebus_r_noc_timeout_refclk_div noc_timeout_refclk_div; /* offset : 0x410 */
	union sysreg_ebus_r_noc_timeout_ext_en noc_timeout_ext_en; /* offset : 0x414 */
	union sysreg_ebus_r_noc_timeout_ext_en2 noc_timeout_ext_en2; /* offset : 0x418 */
	union sysreg_ebus_r_noc_probe_status noc_probe_status; /* offset : 0x41c */
	uint32_t reserved_8[56];
	union sysreg_ebus_r_tbu_smmu_pmu_snapshot_req tbu_smmu_pmu_snapshot_req; /* offset : 0x500 */
	union sysreg_ebus_r_tbu_smmu_pmu_snapshot_ack tbu_smmu_pmu_snapshot_ack; /* offset : 0x504 */
	uint32_t reserved_9[2];
	union sysreg_ebus_r_smmu_pcie_mode smmu_pcie_mode; /* offset : 0x510 */
	union sysreg_ebus_r_smmu_max_tok_trans smmu_max_tok_trans; /* offset : 0x514 */
	union sysreg_ebus_r_smmu_etc smmu_etc; /* offset : 0x518 */
	uint32_t reserved_10[57];
	union sysreg_ebus_r_rbc_h00_pch_mux_preq rbc_h00_pch_mux_preq; /* offset : 0x600 */
	union sysreg_ebus_r_rbc_h00_pch_mux_pstate rbc_h00_pch_mux_pstate; /* offset : 0x604 */
	union sysreg_ebus_r_rbc_h00_pch_mux_sel rbc_h00_pch_mux_sel; /* offset : 0x608 */
	union sysreg_ebus_r_rbc_h00_pch_mux_ro rbc_h00_pch_mux_ro; /* offset : 0x60c */
	union sysreg_ebus_r_rbc_h01_pch_mux_preq rbc_h01_pch_mux_preq; /* offset : 0x610 */
	union sysreg_ebus_r_rbc_h01_pch_mux_pstate rbc_h01_pch_mux_pstate; /* offset : 0x614 */
	union sysreg_ebus_r_rbc_h01_pch_mux_sel rbc_h01_pch_mux_sel; /* offset : 0x618 */
	union sysreg_ebus_r_rbc_h01_pch_mux_ro rbc_h01_pch_mux_ro; /* offset : 0x61c */
};