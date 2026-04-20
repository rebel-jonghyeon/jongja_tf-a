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

union sysreg_pcie_user_reg0 {
	struct {
		uint32_t spare; /* [31:0] */
	};
	uint32_t val;
};

union sysreg_pcie_user_reg1 {
	struct {
		uint32_t spare; /* [31:0] */
	};
	uint32_t val;
};

union sysreg_pcie_user_reg2 {
	struct {
		uint32_t spare; /* [31:0] */
	};
	uint32_t val;
};

union sysreg_pcie_user_reg3 {
	struct {
		uint32_t spare; /* [31:0] */
	};
	uint32_t val;
};

union sysreg_pcie_user_reg4 {
	struct {
		uint32_t spare; /* [31:0] */
	};
	uint32_t val;
};

union sysreg_pcie_sfr_apb {
	struct {
		uint32_t en_timeout:1; /* [0:0] */
	};
	uint32_t val;
};

union sysreg_pcie_bus_component_drcg_en {
	struct {
		uint32_t lh_pcies_p_mi:1; /* [0:0] */
		uint32_t lh_pcies_d_mi:1; /* [1:1] */
		uint32_t lh_pciem_d_si:1; /* [2:2] */
		uint32_t lh_pcies_ast_mi:1; /* [3:3] */
		uint32_t lh_pciem_ast_si:1; /* [4:4] */
		uint32_t lh_pciem_t_si:1; /* [5:5] */
	};
	uint32_t val;
};

union sysreg_pcie_tzpc_prot0stat {
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

union sysreg_pcie_tzpc_prot0set {
	struct {
		uint32_t protset; /* [31:0] */
	};
	uint32_t val;
};

union sysreg_pcie_tzpc_prot0clr {
	struct {
		uint32_t protclr; /* [31:0] */
	};
	uint32_t val;
};

union sysreg_pcie_tzpc_prot1stat {
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

union sysreg_pcie_tzpc_prot1set {
	struct {
		uint32_t protset; /* [31:0] */
	};
	uint32_t val;
};

union sysreg_pcie_tzpc_prot1clr {
	struct {
		uint32_t protclr; /* [31:0] */
	};
	uint32_t val;
};

union sysreg_pcie_tzpc_r0size {
	struct {
		uint32_t intmem_pcie_r0size1:7; /* [6:0] */
	};
	uint32_t val;
};

union sysreg_pcie_lpp_mcs {
	struct {
		uint32_t rf1_hs_mcs:2; /* [1:0] */
		uint32_t reserved_bit_0:2;
		uint32_t ra1_hs_mcs:2; /* [5:4] */
		uint32_t reserved_bit_1:2;
		uint32_t rf1_uhd_mcs:2; /* [9:8] */
		uint32_t reserved_bit_2:2;
		uint32_t ra1_uhd_mcs:2; /* [13:12] */
		uint32_t reserved_bit_3:2;
		uint32_t ra1_uhs_mcs:2; /* [17:16] */
		uint32_t reserved_bit_4:2;
		uint32_t vrom_hd_mcs:1; /* [20:20] */
	};
	uint32_t val;
};

union sysreg_pcie_lpp_mcsw {
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

union sysreg_pcie_lpp_mcsrd {
	struct {
		uint32_t rf2_hs_mcsrd:2; /* [1:0] */
		uint32_t reserved_bit_0:2;
		uint32_t rd2_uhd_mcsrd:2; /* [5:4] */
		uint32_t reserved_bit_1:2;
		uint32_t rd2_hs_mcsrd:2; /* [9:8] */
		uint32_t reserved_bit_2:2;
		uint32_t rd2_uhs_mcsrd:2; /* [13:12] */
		uint32_t reserved_bit_3:2;
		uint32_t rf2_uhs_mcsrd:2; /* [17:16] */
	};
	uint32_t val;
};

union sysreg_pcie_lpp_mcswr {
	struct {
		uint32_t rf2_hs_mcswr:2; /* [1:0] */
		uint32_t reserved_bit_0:2;
		uint32_t rd2_uhd_mcswr:2; /* [5:4] */
		uint32_t reserved_bit_1:2;
		uint32_t rd2_hs_mcswr:2; /* [9:8] */
		uint32_t reserved_bit_2:2;
		uint32_t rd2_uhs_mcswr:2; /* [13:12] */
		uint32_t reserved_bit_3:2;
		uint32_t rf2_uhs_mcswr:2; /* [17:16] */
	};
	uint32_t val;
};

union sysreg_pcie_lpp_kcs {
	struct {
		uint32_t rf2_hs_kcs:1; /* [0:0] */
		uint32_t reserved_bit_0:3;
		uint32_t rf2_uhs_kcs:1; /* [4:4] */
		uint32_t reserved_bit_1:3;
		uint32_t vrom_hd_kcs:1; /* [8:8] */
	};
	uint32_t val;
};

union sysreg_pcie_lpp_adme {
	struct {
		uint32_t rf2_hs_adme:3; /* [2:0] */
		uint32_t rd2_hs_adme:3; /* [5:3] */
		uint32_t rf1_hs_adme:3; /* [8:6] */
		uint32_t ra1_hs_adme:3; /* [11:9] */
		uint32_t rd2_uhd_adme:3; /* [14:12] */
		uint32_t rf1_uhd_adme:3; /* [17:15] */
		uint32_t ra1_uhd_adme:3; /* [20:18] */
		uint32_t ra1_uhs_adme:3; /* [23:21] */
		uint32_t rd2_uhs_adme:3; /* [26:24] */
		uint32_t rf2_uhs_adme:3; /* [29:27] */
	};
	uint32_t val;
};

union sysreg_pcie_lpp_wrme {
	struct {
		uint32_t rd2_uhd_wrme:2; /* [1:0] */
		uint32_t reserved_bit_0:2;
		uint32_t rf1_uhd_wrme:2; /* [5:4] */
		uint32_t reserved_bit_1:2;
		uint32_t ra1_uhd_wrme:2; /* [9:8] */
	};
	uint32_t val;
};

union sysreg_pcie_lpp_bpe {
	struct {
		uint32_t rd2_uhs_bpe:1; /* [0:0] */
	};
	uint32_t val;
};

union sysreg_pcie_lpp_bce {
	struct {
		uint32_t rd2_uhs_bce:1; /* [0:0] */
	};
	uint32_t val;
};

union sysreg_pcie_lpp_mcscc {
	struct {
		uint32_t rd2_uhs_mcscc:2; /* [1:0] */
	};
	uint32_t val;
};

union sysreg_pcie_pll_pcie_cntrl {
	struct {
		uint32_t feed_en:1; /* [0:0] */
		uint32_t fsel:1; /* [1:1] */
	};
	uint32_t val;
};

union sysreg_pcie_wdt_pcie_control {
	struct {
		uint32_t speed_up:1; /* [0:0] */
		uint32_t pause:1; /* [1:1] */
	};
	uint32_t val;
};

union sysreg_pcie_dbi_addr_32_22 {
	struct {
		uint32_t dbi_addr_32_22:11; /* [10:0] */
	};
	uint32_t val;
};

union sysreg_pcie_sw_reset_ctrl_reg {
	struct {
		uint32_t core_rst_n:1; /* [0:0] */
		uint32_t dbi_axi_resetn:1; /* [1:1] */
		uint32_t slv_axi_resetn:1; /* [2:2] */
		uint32_t mstr_axi_resetn:1; /* [3:3] */
		uint32_t phy_rst_n:1; /* [4:4] */
		uint32_t button_rst_n:1; /* [5:5] */
	};
	uint32_t val;
};

union sysreg_pcie_cm7_halted {
	struct {
		uint32_t halted:1; /* [0:0] */
	};
	uint32_t val;
};

union sysreg_pcie_cm7_dbgrestarted {
	struct {
		uint32_t dbgrestarted:1; /* [0:0] */
	};
	uint32_t val;
};

union sysreg_pcie_cm7_lockup {
	struct {
		uint32_t lockup:1; /* [0:0] */
	};
	uint32_t val;
};

union sysreg_pcie_cm7_fpu_exception_flag {
	struct {
		uint32_t fpioc:1; /* [0:0] */
		uint32_t fpdzc:1; /* [1:1] */
		uint32_t fpufc:1; /* [2:2] */
		uint32_t fpofc:1; /* [3:3] */
		uint32_t fpidc:1; /* [4:4] */
		uint32_t fpixc:1; /* [5:5] */
	};
	uint32_t val;
};

union sysreg_pcie_cm7_ctlppblock {
	struct {
		uint32_t ctlppblock:4; /* [3:0] */
	};
	uint32_t val;
};

union sysreg_pcie_tbu_pcie_awdomain_s {
	struct {
		uint32_t awdomain_s:2; /* [1:0] */
	};
	uint32_t val;
};

union sysreg_pcie_tbu_pcie_ardomain_s {
	struct {
		uint32_t ardomain_s:2; /* [1:0] */
	};
	uint32_t val;
};

union sysreg_pcie_tbu_pcie_awmmussid_s {
	struct {
		uint32_t awmmussid_s:20; /* [19:0] */
	};
	uint32_t val;
};

union sysreg_pcie_tbu_pcie_armmussid_s {
	struct {
		uint32_t armmussid_s:20; /* [19:0] */
	};
	uint32_t val;
};

union sysreg_pcie_tbu_pcie_awmmusid_s {
	struct {
		uint32_t awmmusid_s:16; /* [15:0] */
	};
	uint32_t val;
};

union sysreg_pcie_tbu_pcie_armmusid_s {
	struct {
		uint32_t armmusid_s:16; /* [15:0] */
	};
	uint32_t val;
};

union sysreg_pcie_tbu_pcie_pmusnapshot_req {
	struct {
		uint32_t pmusnapshot_req:1; /* [0:0] */
	};
	uint32_t val;
};

union sysreg_pcie_tbu_pcie_pmusnapshot_ack {
	struct {
		uint32_t pmusnapshot_ack:1; /* [0:0] */
	};
	uint32_t val;
};

union sysreg_pcie_pcie_perst_n {
	struct {
		uint32_t cntl:1; /* [0:0] */
	};
	uint32_t val;
};

union sysreg_pcie_pcie_cr_sel {
	struct {
		uint32_t phy0_cr_para_sel:1; /* [0:0] */
		uint32_t phy1_cr_para_sel:1; /* [1:1] */
		uint32_t phy2_cr_para_sel:1; /* [2:2] */
		uint32_t phy3_cr_para_sel:1; /* [3:3] */
	};
	uint32_t val;
};

union sysreg_pcie_axi_mux_top_sel {
	struct {
		uint32_t i_detour_en:1; /* [0:0] */
	};
	uint32_t val;
};

union sysreg_pcie_axi_demux_top_sel {
	struct {
		uint32_t i_detour_en:1; /* [0:0] */
	};
	uint32_t val;
};

union sysreg_pcie_perst_control_mux1 {
	struct {
		uint32_t select:1; /* [0:0] */
	};
	uint32_t val;
};

union sysreg_pcie_perst_control_mux2 {
	struct {
		uint32_t select:1; /* [0:0] */
	};
	uint32_t val;
};

union sysreg_pcie_pcie_power_up_rst_n {
	struct {
		uint32_t cntl:1; /* [0:0] */
	};
	uint32_t val;
};

union sysreg_pcie_power_up_rst_n_control_mux1 {
	struct {
		uint32_t select:1; /* [0:0] */
	};
	uint32_t val;
};

union sysreg_pcie_power_up_rst_n_control_mux2 {
	struct {
		uint32_t select:1; /* [0:0] */
	};
	uint32_t val;
};

union sysreg_pcie_bat_m7_page1_src_addr {
	struct {
		uint32_t page1_source:20; /* [19:0] */
	};
	uint32_t val;
};

union sysreg_pcie_bat_m7_page1_tgt_addr {
	struct {
		uint32_t page1_target:28; /* [27:0] */
	};
	uint32_t val;
};

union sysreg_pcie_bat_m7_page1_mask {
	struct {
		uint32_t page1_mask:20; /* [19:0] */
	};
	uint32_t val;
};

union sysreg_pcie_bat_m7_page2_src_addr {
	struct {
		uint32_t page2_source:20; /* [19:0] */
	};
	uint32_t val;
};

union sysreg_pcie_bat_m7_page2_tgt_addr {
	struct {
		uint32_t page2_target:28; /* [27:0] */
	};
	uint32_t val;
};

union sysreg_pcie_bat_m7_page2_mask {
	struct {
		uint32_t page2_mask:20; /* [19:0] */
	};
	uint32_t val;
};

union sysreg_pcie_bat_m7_page3_src_addr {
	struct {
		uint32_t page3_source:20; /* [19:0] */
	};
	uint32_t val;
};

union sysreg_pcie_bat_m7_page3_tgt_addr {
	struct {
		uint32_t page3_target:28; /* [27:0] */
	};
	uint32_t val;
};

union sysreg_pcie_bat_m7_page3_mask {
	struct {
		uint32_t page3_mask:20; /* [19:0] */
	};
	uint32_t val;
};

union sysreg_pcie_bat_m7_page4_src_addr {
	struct {
		uint32_t page4_source:20; /* [19:0] */
	};
	uint32_t val;
};

union sysreg_pcie_bat_m7_page4_tgt_addr {
	struct {
		uint32_t page4_target:28; /* [27:0] */
	};
	uint32_t val;
};

union sysreg_pcie_bat_m7_page4_mask {
	struct {
		uint32_t page4_mask:20; /* [19:0] */
	};
	uint32_t val;
};

union sysreg_pcie_bat_m7_page5_src_addr {
	struct {
		uint32_t page5_source:20; /* [19:0] */
	};
	uint32_t val;
};

union sysreg_pcie_bat_m7_page5_tgt_addr {
	struct {
		uint32_t page5_target:28; /* [27:0] */
	};
	uint32_t val;
};

union sysreg_pcie_bat_m7_page5_mask {
	struct {
		uint32_t page5_mask:20; /* [19:0] */
	};
	uint32_t val;
};

union sysreg_pcie_bat_m7_page6_src_addr {
	struct {
		uint32_t page6_source:20; /* [19:0] */
	};
	uint32_t val;
};

union sysreg_pcie_bat_m7_page6_tgt_addr {
	struct {
		uint32_t page6_target:28; /* [27:0] */
	};
	uint32_t val;
};

union sysreg_pcie_bat_m7_page6_mask {
	struct {
		uint32_t page6_mask:20; /* [19:0] */
	};
	uint32_t val;
};

union sysreg_pcie_bat_m7_page7_src_addr {
	struct {
		uint32_t page7_source:20; /* [19:0] */
	};
	uint32_t val;
};

union sysreg_pcie_bat_m7_page7_tgt_addr {
	struct {
		uint32_t page7_target:28; /* [27:0] */
	};
	uint32_t val;
};

union sysreg_pcie_bat_m7_page7_mask {
	struct {
		uint32_t page7_mask:20; /* [19:0] */
	};
	uint32_t val;
};

union sysreg_pcie_bat_m7_page8_src_addr {
	struct {
		uint32_t page8_source:20; /* [19:0] */
	};
	uint32_t val;
};

union sysreg_pcie_bat_m7_page8_tgt_addr {
	struct {
		uint32_t page8_target:28; /* [27:0] */
	};
	uint32_t val;
};

union sysreg_pcie_bat_m7_page8_mask {
	struct {
		uint32_t page8_mask:20; /* [19:0] */
	};
	uint32_t val;
};

union sysreg_pcie_bat_m7_page9_src_addr {
	struct {
		uint32_t page9_source:20; /* [19:0] */
	};
	uint32_t val;
};

union sysreg_pcie_bat_m7_page9_tgt_addr {
	struct {
		uint32_t page9_target:28; /* [27:0] */
	};
	uint32_t val;
};

union sysreg_pcie_bat_m7_page9_mask {
	struct {
		uint32_t page9_mask:20; /* [19:0] */
	};
	uint32_t val;
};

union sysreg_pcie_bat_m7_page10_src_addr {
	struct {
		uint32_t page10_source:20; /* [19:0] */
	};
	uint32_t val;
};

union sysreg_pcie_bat_m7_page10_tgt_addr {
	struct {
		uint32_t page10_target:28; /* [27:0] */
	};
	uint32_t val;
};

union sysreg_pcie_bat_m7_page10_mask {
	struct {
		uint32_t page10_mask:20; /* [19:0] */
	};
	uint32_t val;
};

union sysreg_pcie_bat_m7_page11_src_addr {
	struct {
		uint32_t page11_source:20; /* [19:0] */
	};
	uint32_t val;
};

union sysreg_pcie_bat_m7_page11_tgt_addr {
	struct {
		uint32_t page11_target:28; /* [27:0] */
	};
	uint32_t val;
};

union sysreg_pcie_bat_m7_page11_mask {
	struct {
		uint32_t page11_mask:20; /* [19:0] */
	};
	uint32_t val;
};

union sysreg_pcie_bat_m7_page12_src_addr {
	struct {
		uint32_t page12_source:20; /* [19:0] */
	};
	uint32_t val;
};

union sysreg_pcie_bat_m7_page12_tgt_addr {
	struct {
		uint32_t page12_target:28; /* [27:0] */
	};
	uint32_t val;
};

union sysreg_pcie_bat_m7_page12_mask {
	struct {
		uint32_t page12_mask:20; /* [19:0] */
	};
	uint32_t val;
};

union sysreg_pcie_bat_m7_page13_src_addr {
	struct {
		uint32_t page13_source:20; /* [19:0] */
	};
	uint32_t val;
};

union sysreg_pcie_bat_m7_page13_tgt_addr {
	struct {
		uint32_t page13_target:28; /* [27:0] */
	};
	uint32_t val;
};

union sysreg_pcie_bat_m7_page13_mask {
	struct {
		uint32_t page13_mask:20; /* [19:0] */
	};
	uint32_t val;
};

union sysreg_pcie_bat_m7_page14_src_addr {
	struct {
		uint32_t page14_source:20; /* [19:0] */
	};
	uint32_t val;
};

union sysreg_pcie_bat_m7_page14_tgt_addr {
	struct {
		uint32_t page14_target:28; /* [27:0] */
	};
	uint32_t val;
};

union sysreg_pcie_bat_m7_page14_mask {
	struct {
		uint32_t page14_mask:20; /* [19:0] */
	};
	uint32_t val;
};

union sysreg_pcie_bat_m7_page15_src_addr {
	struct {
		uint32_t page15_source:20; /* [19:0] */
	};
	uint32_t val;
};

union sysreg_pcie_bat_m7_page15_tgt_addr {
	struct {
		uint32_t page15_target:28; /* [27:0] */
	};
	uint32_t val;
};

union sysreg_pcie_bat_m7_page15_mask {
	struct {
		uint32_t page15_mask:20; /* [19:0] */
	};
	uint32_t val;
};

union sysreg_pcie_bat_m7_page16_src_addr {
	struct {
		uint32_t page16_source:20; /* [19:0] */
	};
	uint32_t val;
};

union sysreg_pcie_bat_m7_page16_tgt_addr {
	struct {
		uint32_t page16_target:28; /* [27:0] */
	};
	uint32_t val;
};

union sysreg_pcie_bat_m7_page16_mask {
	struct {
		uint32_t page16_mask:20; /* [19:0] */
	};
	uint32_t val;
};

union sysreg_pcie_bat_m7_page17_src_addr {
	struct {
		uint32_t page17_source:20; /* [19:0] */
	};
	uint32_t val;
};

union sysreg_pcie_bat_m7_page17_tgt_addr {
	struct {
		uint32_t page17_target:28; /* [27:0] */
	};
	uint32_t val;
};

union sysreg_pcie_bat_m7_page17_mask {
	struct {
		uint32_t page17_mask:20; /* [19:0] */
	};
	uint32_t val;
};

union sysreg_pcie_bat_m7_page18_src_addr {
	struct {
		uint32_t page18_source:20; /* [19:0] */
	};
	uint32_t val;
};

union sysreg_pcie_bat_m7_page18_tgt_addr {
	struct {
		uint32_t page18_target:28; /* [27:0] */
	};
	uint32_t val;
};

union sysreg_pcie_bat_m7_page18_mask {
	struct {
		uint32_t page18_mask:20; /* [19:0] */
	};
	uint32_t val;
};

union sysreg_pcie_bat_m7_page19_src_addr {
	struct {
		uint32_t page19_source:20; /* [19:0] */
	};
	uint32_t val;
};

union sysreg_pcie_bat_m7_page19_tgt_addr {
	struct {
		uint32_t page19_target:28; /* [27:0] */
	};
	uint32_t val;
};

union sysreg_pcie_bat_m7_page19_mask {
	struct {
		uint32_t page19_mask:20; /* [19:0] */
	};
	uint32_t val;
};

union sysreg_pcie_bat_m7_page20_src_addr {
	struct {
		uint32_t page20_source:20; /* [19:0] */
	};
	uint32_t val;
};

union sysreg_pcie_bat_m7_page20_tgt_addr {
	struct {
		uint32_t page20_target:28; /* [27:0] */
	};
	uint32_t val;
};

union sysreg_pcie_bat_m7_page20_mask {
	struct {
		uint32_t page20_mask:20; /* [19:0] */
	};
	uint32_t val;
};

union sysreg_pcie_bat_m7_page21_src_addr {
	struct {
		uint32_t page21_source:20; /* [19:0] */
	};
	uint32_t val;
};

union sysreg_pcie_bat_m7_page21_tgt_addr {
	struct {
		uint32_t page21_target:28; /* [27:0] */
	};
	uint32_t val;
};

union sysreg_pcie_bat_m7_page21_mask {
	struct {
		uint32_t page21_mask:20; /* [19:0] */
	};
	uint32_t val;
};

union sysreg_pcie_bat_m7_page22_src_addr {
	struct {
		uint32_t page22_source:20; /* [19:0] */
	};
	uint32_t val;
};

union sysreg_pcie_bat_m7_page22_tgt_addr {
	struct {
		uint32_t page22_target:28; /* [27:0] */
	};
	uint32_t val;
};

union sysreg_pcie_bat_m7_page22_mask {
	struct {
		uint32_t page22_mask:20; /* [19:0] */
	};
	uint32_t val;
};

union sysreg_pcie_bat_m7_page23_src_addr {
	struct {
		uint32_t page23_source:20; /* [19:0] */
	};
	uint32_t val;
};

union sysreg_pcie_bat_m7_page23_tgt_addr {
	struct {
		uint32_t page23_target:28; /* [27:0] */
	};
	uint32_t val;
};

union sysreg_pcie_bat_m7_page23_mask {
	struct {
		uint32_t page23_mask:20; /* [19:0] */
	};
	uint32_t val;
};

union sysreg_pcie_bat_m7_page24_src_addr {
	struct {
		uint32_t page24_source:20; /* [19:0] */
	};
	uint32_t val;
};

union sysreg_pcie_bat_m7_page24_tgt_addr {
	struct {
		uint32_t page24_target:28; /* [27:0] */
	};
	uint32_t val;
};

union sysreg_pcie_bat_m7_page24_mask {
	struct {
		uint32_t page24_mask:20; /* [19:0] */
	};
	uint32_t val;
};

union sysreg_pcie_bat_m7_page25_src_addr {
	struct {
		uint32_t page25_source:20; /* [19:0] */
	};
	uint32_t val;
};

union sysreg_pcie_bat_m7_page25_tgt_addr {
	struct {
		uint32_t page25_target:28; /* [27:0] */
	};
	uint32_t val;
};

union sysreg_pcie_bat_m7_page25_mask {
	struct {
		uint32_t page25_mask:20; /* [19:0] */
	};
	uint32_t val;
};

union sysreg_pcie_bat_m7_page26_src_addr {
	struct {
		uint32_t page26_source:20; /* [19:0] */
	};
	uint32_t val;
};

union sysreg_pcie_bat_m7_page26_tgt_addr {
	struct {
		uint32_t page26_target:28; /* [27:0] */
	};
	uint32_t val;
};

union sysreg_pcie_bat_m7_page26_mask {
	struct {
		uint32_t page26_mask:20; /* [19:0] */
	};
	uint32_t val;
};

union sysreg_pcie_bat_m7_page27_src_addr {
	struct {
		uint32_t page27_source:20; /* [19:0] */
	};
	uint32_t val;
};

union sysreg_pcie_bat_m7_page27_tgt_addr {
	struct {
		uint32_t page27_target:28; /* [27:0] */
	};
	uint32_t val;
};

union sysreg_pcie_bat_m7_page27_mask {
	struct {
		uint32_t page27_mask:20; /* [19:0] */
	};
	uint32_t val;
};

union sysreg_pcie_bat_m7_page28_src_addr {
	struct {
		uint32_t page28_source:20; /* [19:0] */
	};
	uint32_t val;
};

union sysreg_pcie_bat_m7_page28_tgt_addr {
	struct {
		uint32_t page28_target:28; /* [27:0] */
	};
	uint32_t val;
};

union sysreg_pcie_bat_m7_page28_mask {
	struct {
		uint32_t page28_mask:20; /* [19:0] */
	};
	uint32_t val;
};

union sysreg_pcie_bat_m7_page29_src_addr {
	struct {
		uint32_t page29_source:20; /* [19:0] */
	};
	uint32_t val;
};

union sysreg_pcie_bat_m7_page29_tgt_addr {
	struct {
		uint32_t page29_target:28; /* [27:0] */
	};
	uint32_t val;
};

union sysreg_pcie_bat_m7_page29_mask {
	struct {
		uint32_t page29_mask:20; /* [19:0] */
	};
	uint32_t val;
};

union sysreg_pcie_bat_m7_page30_src_addr {
	struct {
		uint32_t page30_source:20; /* [19:0] */
	};
	uint32_t val;
};

union sysreg_pcie_bat_m7_page30_tgt_addr {
	struct {
		uint32_t page30_target:28; /* [27:0] */
	};
	uint32_t val;
};

union sysreg_pcie_bat_m7_page30_mask {
	struct {
		uint32_t page30_mask:20; /* [19:0] */
	};
	uint32_t val;
};

union sysreg_pcie_bat_m7_page31_src_addr {
	struct {
		uint32_t page31_source:20; /* [19:0] */
	};
	uint32_t val;
};

union sysreg_pcie_bat_m7_page31_tgt_addr {
	struct {
		uint32_t page31_target:28; /* [27:0] */
	};
	uint32_t val;
};

union sysreg_pcie_bat_m7_page31_mask {
	struct {
		uint32_t page31_mask:20; /* [19:0] */
	};
	uint32_t val;
};

union sysreg_pcie_cm7_initvtor {
	struct {
		uint32_t cm7_iniit_vtor; /* [31:0] */
	};
	uint32_t val;
};

union sysreg_pcie_cm7_cfgbigend {
	struct {
		uint32_t cm7_cfgbigend:1; /* [0:0] */
	};
	uint32_t val;
};

union sysreg_pcie_cm7_edbgrq {
	struct {
		uint32_t cm7_edb_grq:1; /* [0:0] */
	};
	uint32_t val;
};

union sysreg_pcie_cm7_cfgstcalib {
	struct {
		uint32_t cm7_cfg_stcalib_23_0:24; /* [23:0] */
		uint32_t cm7_cfg_stcalib_24:1; /* [24:24] */
		uint32_t cm7_cfg_stcalib_25:1; /* [25:25] */
	};
	uint32_t val;
};

union sysreg_pcie_cm7_tsclkchange {
	struct {
		uint32_t tsclkchange:1; /* [0:0] */
	};
	uint32_t val;
};

union sysreg_pcie_cm7_cpuwait {
	struct {
		uint32_t cpuwait:1; /* [0:0] */
	};
	uint32_t val;
};

union sysreg_pcie_noc_i_ext_oscdiv_cfg {
	struct {
		uint32_t i_ext_oscdiv_cfg:3; /* [2:0] */
	};
	uint32_t val;
};

union sysreg_pcie_noc_pcie_axi2apb_pcie_m_t_mainexten {
	struct {
		uint32_t axi2apb_pcie_m_t_mainexten:1; /* [0:0] */
	};
	uint32_t val;
};

union sysreg_pcie_noc_pcie_dbi_m_t_mainexten {
	struct {
		uint32_t dbi_m_t_mainexten:1; /* [0:0] */
	};
	uint32_t val;
};

union sysreg_pcie_noc_pcie_pcie_m_t_mainexten {
	struct {
		uint32_t pcie_m_t_mainexten:1; /* [0:0] */
	};
	uint32_t val;
};

union sysreg_pcie_noc_pcie_intmem_m_t_mainexten {
	struct {
		uint32_t intmem_m_t_mainexten:1; /* [0:0] */
	};
	uint32_t val;
};

union sysreg_pcie_noc_pcie_axi2apb_phy_m_t_mainexten {
	struct {
		uint32_t axi2apb_phy_m_t_mainexten:1; /* [0:0] */
	};
	uint32_t val;
};

union sysreg_pcie_noc_pcie_d_pcie_s_aruser {
	struct {
		uint32_t d_pcie_s_aruser:1; /* [0:0] */
	};
	uint32_t val;
};

union sysreg_pcie_noc_pcie_d_pcie_s_awuser {
	struct {
		uint32_t d_pcie_s_awuser:1; /* [0:0] */
	};
	uint32_t val;
};

union sysreg_pcie_noc_pcie_tzpc_dbi {
	struct {
		uint32_t tzpc_dbi:1; /* [0:0] */
	};
	uint32_t val;
};

union sysreg_pcie_cm7_dbgrestart {
	struct {
		uint32_t dbgrestart:1; /* [0:0] */
	};
	uint32_t val;
};

union sysreg_pcie_cm7_icerr {
	struct {
		uint32_t icerr:22; /* [21:0] */
	};
	uint32_t val;
};

union sysreg_pcie_cm7_dcerr {
	struct {
		uint32_t dcerr:22; /* [21:0] */
	};
	uint32_t val;
};

union sysreg_pcie_cm7_icdet {
	struct {
		uint32_t icdet:4; /* [3:0] */
	};
	uint32_t val;
};

union sysreg_pcie_cm7_dcdet {
	struct {
		uint32_t dcdet:4; /* [3:0] */
	};
	uint32_t val;
};

union sysreg_pcie_pcie_cr_para_sel {
	struct {
		uint32_t cr_para_sel:1; /* [0:0] */
	};
	uint32_t val;
};

struct sysreg_pcie_register {
	union sysreg_pcie_user_reg0 user_reg0; /* offset : 0x0 */
	union sysreg_pcie_user_reg1 user_reg1; /* offset : 0x4 */
	union sysreg_pcie_user_reg2 user_reg2; /* offset : 0x8 */
	union sysreg_pcie_user_reg3 user_reg3; /* offset : 0xc */
	union sysreg_pcie_user_reg4 user_reg4; /* offset : 0x10 */
	uint32_t reserved_1[59];
	union sysreg_pcie_sfr_apb sfr_apb; /* offset : 0x100 */
	union sysreg_pcie_bus_component_drcg_en bus_component_drcg_en; /* offset : 0x104 */
	uint32_t reserved_2[62];
	union sysreg_pcie_tzpc_prot0stat tzpc_prot0stat; /* offset : 0x200 */
	union sysreg_pcie_tzpc_prot0set tzpc_prot0set; /* offset : 0x204 */
	union sysreg_pcie_tzpc_prot0clr tzpc_prot0clr; /* offset : 0x208 */
	uint32_t reserved_3;
	union sysreg_pcie_tzpc_prot1stat tzpc_prot1stat; /* offset : 0x210 */
	union sysreg_pcie_tzpc_prot1set tzpc_prot1set; /* offset : 0x214 */
	union sysreg_pcie_tzpc_prot1clr tzpc_prot1clr; /* offset : 0x218 */
	uint32_t reserved_4;
	union sysreg_pcie_tzpc_r0size tzpc_r0size; /* offset : 0x220 */
	uint32_t reserved_5[3];
	union sysreg_pcie_lpp_mcs lpp_mcs; /* offset : 0x230 */
	union sysreg_pcie_lpp_mcsw lpp_mcsw; /* offset : 0x234 */
	union sysreg_pcie_lpp_mcsrd lpp_mcsrd; /* offset : 0x238 */
	union sysreg_pcie_lpp_mcswr lpp_mcswr; /* offset : 0x23c */
	union sysreg_pcie_lpp_kcs lpp_kcs; /* offset : 0x240 */
	union sysreg_pcie_lpp_adme lpp_adme; /* offset : 0x244 */
	union sysreg_pcie_lpp_wrme lpp_wrme; /* offset : 0x248 */
	union sysreg_pcie_lpp_bpe lpp_bpe; /* offset : 0x24c */
	union sysreg_pcie_lpp_bce lpp_bce; /* offset : 0x250 */
	union sysreg_pcie_lpp_mcscc lpp_mcscc; /* offset : 0x254 */
	uint32_t reserved_6[42];
	union sysreg_pcie_pll_pcie_cntrl pll_pcie_cntrl; /* offset : 0x300 */
	union sysreg_pcie_wdt_pcie_control wdt_pcie_control; /* offset : 0x304 */
	union sysreg_pcie_dbi_addr_32_22 dbi_addr_32_22; /* offset : 0x308 */
	union sysreg_pcie_sw_reset_ctrl_reg sw_reset_ctrl_reg; /* offset : 0x30c */
	union sysreg_pcie_cm7_halted cm7_halted; /* offset : 0x310 */
	union sysreg_pcie_cm7_dbgrestarted cm7_dbgrestarted; /* offset : 0x314 */
	union sysreg_pcie_cm7_lockup cm7_lockup; /* offset : 0x318 */
	union sysreg_pcie_cm7_fpu_exception_flag cm7_fpu_exception_flag; /* offset : 0x31c */
	union sysreg_pcie_cm7_ctlppblock cm7_ctlppblock; /* offset : 0x320 */
	union sysreg_pcie_tbu_pcie_awdomain_s tbu_pcie_awdomain_s; /* offset : 0x324 */
	union sysreg_pcie_tbu_pcie_ardomain_s tbu_pcie_ardomain_s; /* offset : 0x328 */
	union sysreg_pcie_tbu_pcie_awmmussid_s tbu_pcie_awmmussid_s; /* offset : 0x32c */
	union sysreg_pcie_tbu_pcie_armmussid_s tbu_pcie_armmussid_s; /* offset : 0x330 */
	union sysreg_pcie_tbu_pcie_awmmusid_s tbu_pcie_awmmusid_s; /* offset : 0x334 */
	union sysreg_pcie_tbu_pcie_armmusid_s tbu_pcie_armmusid_s; /* offset : 0x338 */
	union sysreg_pcie_tbu_pcie_pmusnapshot_req tbu_pcie_pmusnapshot_req; /* offset : 0x33c */
	union sysreg_pcie_tbu_pcie_pmusnapshot_ack tbu_pcie_pmusnapshot_ack; /* offset : 0x340 */
	union sysreg_pcie_pcie_perst_n pcie_perst_n; /* offset : 0x344 */
	union sysreg_pcie_pcie_cr_sel pcie_cr_sel; /* offset : 0x348 */
	union sysreg_pcie_axi_mux_top_sel axi_mux_top_sel; /* offset : 0x34c */
	union sysreg_pcie_axi_demux_top_sel axi_demux_top_sel; /* offset : 0x350 */
	union sysreg_pcie_perst_control_mux1 perst_control_mux1; /* offset : 0x354 */
	union sysreg_pcie_perst_control_mux2 perst_control_mux2; /* offset : 0x358 */
	union sysreg_pcie_pcie_power_up_rst_n pcie_power_up_rst_n; /* offset : 0x35c */
	union sysreg_pcie_power_up_rst_n_control_mux1 power_up_rst_n_control_mux1; /* offset : 0x360 */
	union sysreg_pcie_power_up_rst_n_control_mux2 power_up_rst_n_control_mux2; /* offset : 0x364 */
	uint32_t reserved_7[38];
	union sysreg_pcie_bat_m7_page1_src_addr bat_m7_page1_src_addr; /* offset : 0x400 */
	union sysreg_pcie_bat_m7_page1_tgt_addr bat_m7_page1_tgt_addr; /* offset : 0x404 */
	union sysreg_pcie_bat_m7_page1_mask bat_m7_page1_mask; /* offset : 0x408 */
	uint32_t reserved_8;
	union sysreg_pcie_bat_m7_page2_src_addr bat_m7_page2_src_addr; /* offset : 0x410 */
	union sysreg_pcie_bat_m7_page2_tgt_addr bat_m7_page2_tgt_addr; /* offset : 0x414 */
	union sysreg_pcie_bat_m7_page2_mask bat_m7_page2_mask; /* offset : 0x418 */
	uint32_t reserved_9;
	union sysreg_pcie_bat_m7_page3_src_addr bat_m7_page3_src_addr; /* offset : 0x420 */
	union sysreg_pcie_bat_m7_page3_tgt_addr bat_m7_page3_tgt_addr; /* offset : 0x424 */
	union sysreg_pcie_bat_m7_page3_mask bat_m7_page3_mask; /* offset : 0x428 */
	uint32_t reserved_10;
	union sysreg_pcie_bat_m7_page4_src_addr bat_m7_page4_src_addr; /* offset : 0x430 */
	union sysreg_pcie_bat_m7_page4_tgt_addr bat_m7_page4_tgt_addr; /* offset : 0x434 */
	union sysreg_pcie_bat_m7_page4_mask bat_m7_page4_mask; /* offset : 0x438 */
	uint32_t reserved_11;
	union sysreg_pcie_bat_m7_page5_src_addr bat_m7_page5_src_addr; /* offset : 0x440 */
	union sysreg_pcie_bat_m7_page5_tgt_addr bat_m7_page5_tgt_addr; /* offset : 0x444 */
	union sysreg_pcie_bat_m7_page5_mask bat_m7_page5_mask; /* offset : 0x448 */
	uint32_t reserved_12;
	union sysreg_pcie_bat_m7_page6_src_addr bat_m7_page6_src_addr; /* offset : 0x450 */
	union sysreg_pcie_bat_m7_page6_tgt_addr bat_m7_page6_tgt_addr; /* offset : 0x454 */
	union sysreg_pcie_bat_m7_page6_mask bat_m7_page6_mask; /* offset : 0x458 */
	uint32_t reserved_13;
	union sysreg_pcie_bat_m7_page7_src_addr bat_m7_page7_src_addr; /* offset : 0x460 */
	union sysreg_pcie_bat_m7_page7_tgt_addr bat_m7_page7_tgt_addr; /* offset : 0x464 */
	union sysreg_pcie_bat_m7_page7_mask bat_m7_page7_mask; /* offset : 0x468 */
	uint32_t reserved_14;
	union sysreg_pcie_bat_m7_page8_src_addr bat_m7_page8_src_addr; /* offset : 0x470 */
	union sysreg_pcie_bat_m7_page8_tgt_addr bat_m7_page8_tgt_addr; /* offset : 0x474 */
	union sysreg_pcie_bat_m7_page8_mask bat_m7_page8_mask; /* offset : 0x478 */
	uint32_t reserved_15;
	union sysreg_pcie_bat_m7_page9_src_addr bat_m7_page9_src_addr; /* offset : 0x480 */
	union sysreg_pcie_bat_m7_page9_tgt_addr bat_m7_page9_tgt_addr; /* offset : 0x484 */
	union sysreg_pcie_bat_m7_page9_mask bat_m7_page9_mask; /* offset : 0x488 */
	uint32_t reserved_16;
	union sysreg_pcie_bat_m7_page10_src_addr bat_m7_page10_src_addr; /* offset : 0x490 */
	union sysreg_pcie_bat_m7_page10_tgt_addr bat_m7_page10_tgt_addr; /* offset : 0x494 */
	union sysreg_pcie_bat_m7_page10_mask bat_m7_page10_mask; /* offset : 0x498 */
	uint32_t reserved_17;
	union sysreg_pcie_bat_m7_page11_src_addr bat_m7_page11_src_addr; /* offset : 0x4a0 */
	union sysreg_pcie_bat_m7_page11_tgt_addr bat_m7_page11_tgt_addr; /* offset : 0x4a4 */
	union sysreg_pcie_bat_m7_page11_mask bat_m7_page11_mask; /* offset : 0x4a8 */
	uint32_t reserved_18;
	union sysreg_pcie_bat_m7_page12_src_addr bat_m7_page12_src_addr; /* offset : 0x4b0 */
	union sysreg_pcie_bat_m7_page12_tgt_addr bat_m7_page12_tgt_addr; /* offset : 0x4b4 */
	union sysreg_pcie_bat_m7_page12_mask bat_m7_page12_mask; /* offset : 0x4b8 */
	uint32_t reserved_19;
	union sysreg_pcie_bat_m7_page13_src_addr bat_m7_page13_src_addr; /* offset : 0x4c0 */
	union sysreg_pcie_bat_m7_page13_tgt_addr bat_m7_page13_tgt_addr; /* offset : 0x4c4 */
	union sysreg_pcie_bat_m7_page13_mask bat_m7_page13_mask; /* offset : 0x4c8 */
	uint32_t reserved_20;
	union sysreg_pcie_bat_m7_page14_src_addr bat_m7_page14_src_addr; /* offset : 0x4d0 */
	union sysreg_pcie_bat_m7_page14_tgt_addr bat_m7_page14_tgt_addr; /* offset : 0x4d4 */
	union sysreg_pcie_bat_m7_page14_mask bat_m7_page14_mask; /* offset : 0x4d8 */
	uint32_t reserved_21;
	union sysreg_pcie_bat_m7_page15_src_addr bat_m7_page15_src_addr; /* offset : 0x4e0 */
	union sysreg_pcie_bat_m7_page15_tgt_addr bat_m7_page15_tgt_addr; /* offset : 0x4e4 */
	union sysreg_pcie_bat_m7_page15_mask bat_m7_page15_mask; /* offset : 0x4e8 */
	uint32_t reserved_22;
	union sysreg_pcie_bat_m7_page16_src_addr bat_m7_page16_src_addr; /* offset : 0x4f0 */
	union sysreg_pcie_bat_m7_page16_tgt_addr bat_m7_page16_tgt_addr; /* offset : 0x4f4 */
	union sysreg_pcie_bat_m7_page16_mask bat_m7_page16_mask; /* offset : 0x4f8 */
	uint32_t reserved_23;
	union sysreg_pcie_bat_m7_page17_src_addr bat_m7_page17_src_addr; /* offset : 0x500 */
	union sysreg_pcie_bat_m7_page17_tgt_addr bat_m7_page17_tgt_addr; /* offset : 0x504 */
	union sysreg_pcie_bat_m7_page17_mask bat_m7_page17_mask; /* offset : 0x508 */
	uint32_t reserved_24;
	union sysreg_pcie_bat_m7_page18_src_addr bat_m7_page18_src_addr; /* offset : 0x510 */
	union sysreg_pcie_bat_m7_page18_tgt_addr bat_m7_page18_tgt_addr; /* offset : 0x514 */
	union sysreg_pcie_bat_m7_page18_mask bat_m7_page18_mask; /* offset : 0x518 */
	uint32_t reserved_25;
	union sysreg_pcie_bat_m7_page19_src_addr bat_m7_page19_src_addr; /* offset : 0x520 */
	union sysreg_pcie_bat_m7_page19_tgt_addr bat_m7_page19_tgt_addr; /* offset : 0x524 */
	union sysreg_pcie_bat_m7_page19_mask bat_m7_page19_mask; /* offset : 0x528 */
	uint32_t reserved_26;
	union sysreg_pcie_bat_m7_page20_src_addr bat_m7_page20_src_addr; /* offset : 0x530 */
	union sysreg_pcie_bat_m7_page20_tgt_addr bat_m7_page20_tgt_addr; /* offset : 0x534 */
	union sysreg_pcie_bat_m7_page20_mask bat_m7_page20_mask; /* offset : 0x538 */
	uint32_t reserved_27;
	union sysreg_pcie_bat_m7_page21_src_addr bat_m7_page21_src_addr; /* offset : 0x540 */
	union sysreg_pcie_bat_m7_page21_tgt_addr bat_m7_page21_tgt_addr; /* offset : 0x544 */
	union sysreg_pcie_bat_m7_page21_mask bat_m7_page21_mask; /* offset : 0x548 */
	uint32_t reserved_28;
	union sysreg_pcie_bat_m7_page22_src_addr bat_m7_page22_src_addr; /* offset : 0x550 */
	union sysreg_pcie_bat_m7_page22_tgt_addr bat_m7_page22_tgt_addr; /* offset : 0x554 */
	union sysreg_pcie_bat_m7_page22_mask bat_m7_page22_mask; /* offset : 0x558 */
	uint32_t reserved_29;
	union sysreg_pcie_bat_m7_page23_src_addr bat_m7_page23_src_addr; /* offset : 0x560 */
	union sysreg_pcie_bat_m7_page23_tgt_addr bat_m7_page23_tgt_addr; /* offset : 0x564 */
	union sysreg_pcie_bat_m7_page23_mask bat_m7_page23_mask; /* offset : 0x568 */
	uint32_t reserved_30;
	union sysreg_pcie_bat_m7_page24_src_addr bat_m7_page24_src_addr; /* offset : 0x570 */
	union sysreg_pcie_bat_m7_page24_tgt_addr bat_m7_page24_tgt_addr; /* offset : 0x574 */
	union sysreg_pcie_bat_m7_page24_mask bat_m7_page24_mask; /* offset : 0x578 */
	uint32_t reserved_31;
	union sysreg_pcie_bat_m7_page25_src_addr bat_m7_page25_src_addr; /* offset : 0x580 */
	union sysreg_pcie_bat_m7_page25_tgt_addr bat_m7_page25_tgt_addr; /* offset : 0x584 */
	union sysreg_pcie_bat_m7_page25_mask bat_m7_page25_mask; /* offset : 0x588 */
	uint32_t reserved_32;
	union sysreg_pcie_bat_m7_page26_src_addr bat_m7_page26_src_addr; /* offset : 0x590 */
	union sysreg_pcie_bat_m7_page26_tgt_addr bat_m7_page26_tgt_addr; /* offset : 0x594 */
	union sysreg_pcie_bat_m7_page26_mask bat_m7_page26_mask; /* offset : 0x598 */
	uint32_t reserved_33;
	union sysreg_pcie_bat_m7_page27_src_addr bat_m7_page27_src_addr; /* offset : 0x5a0 */
	union sysreg_pcie_bat_m7_page27_tgt_addr bat_m7_page27_tgt_addr; /* offset : 0x5a4 */
	union sysreg_pcie_bat_m7_page27_mask bat_m7_page27_mask; /* offset : 0x5a8 */
	uint32_t reserved_34;
	union sysreg_pcie_bat_m7_page28_src_addr bat_m7_page28_src_addr; /* offset : 0x5b0 */
	union sysreg_pcie_bat_m7_page28_tgt_addr bat_m7_page28_tgt_addr; /* offset : 0x5b4 */
	union sysreg_pcie_bat_m7_page28_mask bat_m7_page28_mask; /* offset : 0x5b8 */
	uint32_t reserved_35;
	union sysreg_pcie_bat_m7_page29_src_addr bat_m7_page29_src_addr; /* offset : 0x5c0 */
	union sysreg_pcie_bat_m7_page29_tgt_addr bat_m7_page29_tgt_addr; /* offset : 0x5c4 */
	union sysreg_pcie_bat_m7_page29_mask bat_m7_page29_mask; /* offset : 0x5c8 */
	uint32_t reserved_36;
	union sysreg_pcie_bat_m7_page30_src_addr bat_m7_page30_src_addr; /* offset : 0x5d0 */
	union sysreg_pcie_bat_m7_page30_tgt_addr bat_m7_page30_tgt_addr; /* offset : 0x5d4 */
	union sysreg_pcie_bat_m7_page30_mask bat_m7_page30_mask; /* offset : 0x5d8 */
	uint32_t reserved_37;
	union sysreg_pcie_bat_m7_page31_src_addr bat_m7_page31_src_addr; /* offset : 0x5e0 */
	union sysreg_pcie_bat_m7_page31_tgt_addr bat_m7_page31_tgt_addr; /* offset : 0x5e4 */
	union sysreg_pcie_bat_m7_page31_mask bat_m7_page31_mask; /* offset : 0x5e8 */
	uint32_t reserved_38;
	union sysreg_pcie_cm7_initvtor cm7_initvtor; /* offset : 0x5f0 */
	union sysreg_pcie_cm7_cfgbigend cm7_cfgbigend; /* offset : 0x5f4 */
	union sysreg_pcie_cm7_edbgrq cm7_edbgrq; /* offset : 0x5f8 */
	union sysreg_pcie_cm7_cfgstcalib cm7_cfgstcalib; /* offset : 0x5fc */
	union sysreg_pcie_cm7_tsclkchange cm7_tsclkchange; /* offset : 0x600 */
	union sysreg_pcie_cm7_cpuwait cm7_cpuwait; /* offset : 0x604 */
	uint32_t reserved_39;
	union sysreg_pcie_noc_i_ext_oscdiv_cfg noc_i_ext_oscdiv_cfg; /* offset : 0x60c */
	union sysreg_pcie_noc_pcie_axi2apb_pcie_m_t_mainexten noc_pcie_axi2apb_pcie_m_t_mainexten; /* offset : 0x610 */
	union sysreg_pcie_noc_pcie_dbi_m_t_mainexten noc_pcie_dbi_m_t_mainexten; /* offset : 0x614 */
	union sysreg_pcie_noc_pcie_pcie_m_t_mainexten noc_pcie_pcie_m_t_mainexten; /* offset : 0x618 */
	union sysreg_pcie_noc_pcie_intmem_m_t_mainexten noc_pcie_intmem_m_t_mainexten; /* offset : 0x61c */
	union sysreg_pcie_noc_pcie_axi2apb_phy_m_t_mainexten noc_pcie_axi2apb_phy_m_t_mainexten; /* offset : 0x620 */
	union sysreg_pcie_noc_pcie_d_pcie_s_aruser noc_pcie_d_pcie_s_aruser; /* offset : 0x624 */
	union sysreg_pcie_noc_pcie_d_pcie_s_awuser noc_pcie_d_pcie_s_awuser; /* offset : 0x628 */
	union sysreg_pcie_noc_pcie_tzpc_dbi noc_pcie_tzpc_dbi; /* offset : 0x62c */
	union sysreg_pcie_cm7_dbgrestart cm7_dbgrestart; /* offset : 0x630 */
	union sysreg_pcie_cm7_icerr cm7_icerr; /* offset : 0x634 */
	union sysreg_pcie_cm7_dcerr cm7_dcerr; /* offset : 0x638 */
	union sysreg_pcie_cm7_icdet cm7_icdet; /* offset : 0x63c */
	union sysreg_pcie_cm7_dcdet cm7_dcdet; /* offset : 0x640 */
	union sysreg_pcie_pcie_cr_para_sel pcie_cr_para_sel; /* offset : 0x644 */
};

