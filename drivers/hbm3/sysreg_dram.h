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

union sysreg_dram_user_reg0 {
	struct {
		uint32_t spare; /* [31:0] */
	};
	uint32_t val;
};

union sysreg_dram_user_reg1 {
	struct {
		uint32_t spare; /* [31:0] */
	};
	uint32_t val;
};

union sysreg_dram_user_reg2 {
	struct {
		uint32_t spare; /* [31:0] */
	};
	uint32_t val;
};

union sysreg_dram_user_reg3 {
	struct {
		uint32_t spare; /* [31:0] */
	};
	uint32_t val;
};

union sysreg_dram_user_reg4 {
	struct {
		uint32_t spare; /* [31:0] */
	};
	uint32_t val;
};

union sysreg_dram_sfr_apb {
	struct {
		uint32_t en_timeout:1; /* [0:0] */
	};
	uint32_t val;
};

union sysreg_dram_bus_component_drcg_en {
	struct {
		uint32_t reserved_bit_0:15;
		uint32_t p_drcg_en:1; /* [15:15] */
		uint32_t d_p_drcg_en:1; /* [16:16] */
		uint32_t d_o_drcg_en:1; /* [17:17] */
		uint32_t d_n_drcg_en:1; /* [18:18] */
		uint32_t d_m_drcg_en:1; /* [19:19] */
		uint32_t d_l_drcg_en:1; /* [20:20] */
		uint32_t d_k_drcg_en:1; /* [21:21] */
		uint32_t d_j_drcg_en:1; /* [22:22] */
		uint32_t d_i_drcg_en:1; /* [23:23] */
		uint32_t d_h_drcg_en:1; /* [24:24] */
		uint32_t d_g_drcg_en:1; /* [25:25] */
		uint32_t d_f_drcg_en:1; /* [26:26] */
		uint32_t d_e_drcg_en:1; /* [27:27] */
		uint32_t d_d_drcg_en:1; /* [28:28] */
		uint32_t d_c_drcg_en:1; /* [29:29] */
		uint32_t d_b_drcg_en:1; /* [30:30] */
		uint32_t d_a_drcg_en:1; /* [31:31] */
	};
	uint32_t val;
};

union sysreg_dram_tzpc_prot0stat {
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

union sysreg_dram_tzpc_prot0set {
	struct {
		uint32_t protset; /* [31:0] */
	};
	uint32_t val;
};

union sysreg_dram_tzpc_prot0clr {
	struct {
		uint32_t protclr; /* [31:0] */
	};
	uint32_t val;
};

union sysreg_dram_tzpc_prot1stat {
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

union sysreg_dram_tzpc_prot1set {
	struct {
		uint32_t protset; /* [31:0] */
	};
	uint32_t val;
};

union sysreg_dram_tzpc_prot1clr {
	struct {
		uint32_t protclr; /* [31:0] */
	};
	uint32_t val;
};

union sysreg_dram_tzpc_r0size {
	struct {
		uint32_t r0size:10; /* [9:0] */
	};
	uint32_t val;
};

union sysreg_dram_clk_enable {
	struct {
		uint32_t hbmphy_clken_per_ch0:1; /* [0:0] */
		uint32_t hbmphy_clken_per_ch1:1; /* [1:1] */
		uint32_t hbmphy_clken_per_ch2:1; /* [2:2] */
		uint32_t hbmphy_clken_per_ch3:1; /* [3:3] */
		uint32_t hbmphy_clken_per_ch4:1; /* [4:4] */
		uint32_t hbmphy_clken_per_ch5:1; /* [5:5] */
		uint32_t hbmphy_clken_per_ch6:1; /* [6:6] */
		uint32_t hbmphy_clken_per_ch7:1; /* [7:7] */
		uint32_t hbmphy_clken_per_ch8:1; /* [8:8] */
		uint32_t hbmphy_clken_per_ch9:1; /* [9:9] */
		uint32_t hbmphy_clken_per_ch10:1; /* [10:10] */
		uint32_t hbmphy_clken_per_ch11:1; /* [11:11] */
		uint32_t hbmphy_clken_per_ch12:1; /* [12:12] */
		uint32_t hbmphy_clken_per_ch13:1; /* [13:13] */
		uint32_t hbmphy_clken_per_ch14:1; /* [14:14] */
		uint32_t hbmphy_clken_per_ch15:1; /* [15:15] */
	};
	uint32_t val;
};

union sysreg_dram_icon_wrstn {
	struct {
		uint32_t rst_ctrl:1; /* [0:0] */
	};
	uint32_t val;
};

union sysreg_dram_zq_icon_reg0 {
	struct {
		uint32_t o_zctrl_pmon:3; /* [2:0] */
		uint32_t o_zctrl_nmon:3; /* [5:3] */
		uint32_t o_zctrl_ack:1; /* [6:6] */
	};
	uint32_t val;
};

union sysreg_dram_zq_icon_reg1 {
	struct {
		uint32_t i_zctrl_req_short:1; /* [0:0] */
		uint32_t i_zctrl_req_long:1; /* [1:1] */
		uint32_t i_zctrl_req_force:1; /* [2:2] */
		uint32_t i_zctrl_pu_mode_sel:1; /* [3:3] */
		uint32_t i_zctrl_force_impp:3; /* [6:4] */
		uint32_t i_zctrl_force_impn:3; /* [9:7] */
		uint32_t i_reset:1; /* [10:10] */
		uint32_t i_testizq:4; /* [14:11] */
	};
	uint32_t val;
};

union sysreg_dram_bypass_ctrl {
	struct {
		uint32_t phy2x_bypass:16; /* [15:0] */
	};
	uint32_t val;
};

union sysreg_dram_lpp_mcs {
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

union sysreg_dram_lpp_mcsw {
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

union sysreg_dram_lpp_mcsrd {
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

union sysreg_dram_lpp_mcswr {
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

union sysreg_dram_lpp_mcscc {
	struct {
		uint32_t rd2_uhs_mcscc:2; /* [1:0] */
	};
	uint32_t val;
};

union sysreg_dram_lpp_kcs {
	struct {
		uint32_t rf2_hs_kcs:1; /* [0:0] */
		uint32_t reserved_bit_0:3;
		uint32_t vrom_hd_kcs:1; /* [4:4] */
		uint32_t reserved_bit_1:3;
		uint32_t rf2_uhs_kcs:1; /* [8:8] */
	};
	uint32_t val;
};

union sysreg_dram_lpp_adme {
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

union sysreg_dram_lpp_wrme {
	struct {
		uint32_t rd2_uhd_wrme:2; /* [1:0] */
		uint32_t reserved_bit_0:2;
		uint32_t rf1_uhd_wrme:2; /* [5:4] */
		uint32_t reserved_bit_1:2;
		uint32_t ra1_uhd_wrme:2; /* [9:8] */
	};
	uint32_t val;
};

union sysreg_dram_lpp_bpe {
	struct {
		uint32_t rd2_uhs_bpe:1; /* [0:0] */
	};
	uint32_t val;
};

union sysreg_dram_lpp_bce {
	struct {
		uint32_t rd2_uhs_bce:1; /* [0:0] */
	};
	uint32_t val;
};

union sysreg_dram_hbmc_paddr_select_all {
	struct {
		uint32_t en:1; /* [0:0] */
	};
	uint32_t val;
};

union sysreg_dram_cfg_custom_hash_ctrl {
	struct {
		uint32_t enable:1; /* [0:0] */
	};
	uint32_t val;
};

union sysreg_dram_cfg_custom_hash_bitmask_0 {
	struct {
		uint32_t value:22; /* [21:0] */
	};
	uint32_t val;
};

union sysreg_dram_cfg_custom_hash_bitmask_1 {
	struct {
		uint32_t value:22; /* [21:0] */
	};
	uint32_t val;
};

union sysreg_dram_cfg_custom_hash_bitmask_2 {
	struct {
		uint32_t value:22; /* [21:0] */
	};
	uint32_t val;
};

union sysreg_dram_cfg_custom_hash_bitmask_3 {
	struct {
		uint32_t value:22; /* [21:0] */
	};
	uint32_t val;
};

union sysreg_dram_cfg_custom_hash_bitmask_4 {
	struct {
		uint32_t value:22; /* [21:0] */
	};
	uint32_t val;
};

union sysreg_dram_ruser_enable {
	struct {
		uint32_t c0:1; /* [0:0] */
		uint32_t c1:1; /* [1:1] */
		uint32_t c2:1; /* [2:2] */
		uint32_t c3:1; /* [3:3] */
		uint32_t c4:1; /* [4:4] */
		uint32_t c5:1; /* [5:5] */
		uint32_t c6:1; /* [6:6] */
		uint32_t c7:1; /* [7:7] */
		uint32_t c8:1; /* [8:8] */
		uint32_t c9:1; /* [9:9] */
		uint32_t c10:1; /* [10:10] */
		uint32_t c11:1; /* [11:11] */
		uint32_t c12:1; /* [12:12] */
		uint32_t c13:1; /* [13:13] */
		uint32_t c14:1; /* [14:14] */
		uint32_t c15:1; /* [15:15] */
	};
	uint32_t val;
};

union sysreg_dram_ddrphy_dtb_0 {
	struct {
		uint32_t c0:4; /* [3:0] */
		uint32_t c1:4; /* [7:4] */
		uint32_t c2:4; /* [11:8] */
		uint32_t c3:4; /* [15:12] */
	};
	uint32_t val;
};

union sysreg_dram_ddrphy_dtb_1 {
	struct {
		uint32_t c4:4; /* [3:0] */
		uint32_t c5:4; /* [7:4] */
		uint32_t c6:4; /* [11:8] */
		uint32_t c7:4; /* [15:12] */
	};
	uint32_t val;
};

union sysreg_dram_ddrphy_dtb_2 {
	struct {
		uint32_t c8:4; /* [3:0] */
		uint32_t c9:4; /* [7:4] */
		uint32_t c10:4; /* [11:8] */
		uint32_t c11:4; /* [15:12] */
	};
	uint32_t val;
};

union sysreg_dram_ddrphy_dtb_3 {
	struct {
		uint32_t c12:4; /* [3:0] */
		uint32_t c13:4; /* [7:4] */
		uint32_t c14:4; /* [11:8] */
		uint32_t c15:4; /* [15:12] */
	};
	uint32_t val;
};

union sysreg_dram_zq_icon_i_reset {
	struct {
		uint32_t i_reset:1; /* [0:0] */
	};
	uint32_t val;
};

struct sysreg_dram {
	union sysreg_dram_user_reg0 user_reg0; /* offset : 0x0 */
	union sysreg_dram_user_reg1 user_reg1; /* offset : 0x4 */
	union sysreg_dram_user_reg2 user_reg2; /* offset : 0x8 */
	union sysreg_dram_user_reg3 user_reg3; /* offset : 0xc */
	union sysreg_dram_user_reg4 user_reg4; /* offset : 0x10 */
	uint32_t reserved_1[59];
	union sysreg_dram_sfr_apb sfr_apb; /* offset : 0x100 */
	union sysreg_dram_bus_component_drcg_en bus_component_drcg_en; /* offset : 0x104 */
	uint32_t reserved_2[62];
	union sysreg_dram_tzpc_prot0stat tzpc_prot0stat; /* offset : 0x200 */
	union sysreg_dram_tzpc_prot0set tzpc_prot0set; /* offset : 0x204 */
	union sysreg_dram_tzpc_prot0clr tzpc_prot0clr; /* offset : 0x208 */
	uint32_t reserved_3;
	union sysreg_dram_tzpc_prot1stat tzpc_prot1stat; /* offset : 0x210 */
	union sysreg_dram_tzpc_prot1set tzpc_prot1set; /* offset : 0x214 */
	union sysreg_dram_tzpc_prot1clr tzpc_prot1clr; /* offset : 0x218 */
	uint32_t reserved_4;
	union sysreg_dram_tzpc_r0size tzpc_r0size; /* offset : 0x220 */
	uint32_t reserved_5[5];
	union sysreg_dram_clk_enable clk_enable; /* offset : 0x238 */
	uint32_t reserved_6[2];
	union sysreg_dram_icon_wrstn icon_wrstn; /* offset : 0x244 */
	uint32_t reserved_7;
	union sysreg_dram_zq_icon_reg0 evt0_zq_icon_reg0; /* offset : 0x24c */
	union sysreg_dram_zq_icon_reg1 evt0_zq_icon_reg1; /* offset : 0x250 */
	union sysreg_dram_bypass_ctrl bypass_ctrl; /* offset : 0x254 */
	uint32_t reserved_8[2];
	union sysreg_dram_lpp_mcs lpp_mcs; /* offset : 0x260 */
	union sysreg_dram_lpp_mcsw lpp_mcsw; /* offset : 0x264 */
	union sysreg_dram_lpp_mcsrd lpp_mcsrd; /* offset : 0x268 */
	union sysreg_dram_lpp_mcswr lpp_mcswr; /* offset : 0x26c */
	union sysreg_dram_lpp_mcscc lpp_mcscc; /* offset : 0x270 */
	union sysreg_dram_lpp_kcs lpp_kcs; /* offset : 0x274 */
	union sysreg_dram_lpp_adme lpp_adme; /* offset : 0x278 */
	union sysreg_dram_lpp_wrme lpp_wrme; /* offset : 0x27c */
	union sysreg_dram_lpp_bpe lpp_bpe; /* offset : 0x280 */
	union sysreg_dram_lpp_bce lpp_bce; /* offset : 0x284 */
	uint32_t reserved_9[2];
	union sysreg_dram_hbmc_paddr_select_all hbmc_paddr_select_all; /* offset : 0x290 */
	union sysreg_dram_cfg_custom_hash_ctrl cfg_custom_hash_ctrl; /* offset : 0x294 */
	union sysreg_dram_cfg_custom_hash_bitmask_0 cfg_custom_hash_bitmask_0; /* offset : 0x298 */
	union sysreg_dram_cfg_custom_hash_bitmask_1 cfg_custom_hash_bitmask_1; /* offset : 0x29c */
	union sysreg_dram_cfg_custom_hash_bitmask_2 cfg_custom_hash_bitmask_2; /* offset : 0x2a0 */
	union sysreg_dram_cfg_custom_hash_bitmask_3 cfg_custom_hash_bitmask_3; /* offset : 0x2a4 */
	union sysreg_dram_cfg_custom_hash_bitmask_4 cfg_custom_hash_bitmask_4; /* offset : 0x2a8 */
	union sysreg_dram_ruser_enable ruser_enable; /* offset : 0x2ac */
	union sysreg_dram_ddrphy_dtb_0 evt1_ddrphy_dtb_0; /* offset : 0x2b0 */
	union sysreg_dram_ddrphy_dtb_1 evt1_ddrphy_dtb_1; /* offset : 0x2b4 */
	union sysreg_dram_ddrphy_dtb_2 evt1_ddrphy_dtb_2; /* offset : 0x2b8 */
	union sysreg_dram_ddrphy_dtb_3 evt1_ddrphy_dtb_3; /* offset : 0x2bc */
	union sysreg_dram_zq_icon_i_reset evt1_i_reset;
};

