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

union sysreg_buscsr_pcie_m0_cache_ovrd_value {
	struct {
		uint32_t arcache_sfr:4; /* [3:0] */
		uint32_t reserved_bit_0:4;
		uint32_t awcache_sfr:4; /* [11:8] */
		uint32_t reserved_bit_1:4;
		uint32_t arcache_sfr_en:4; /* [19:16] */
		uint32_t reserved_bit_2:4;
		uint32_t awcache_sfr_en:4; /* [27:24] */
	};
	uint32_t val;
};

union sysreg_buscsr_pcie_m0_qos_ovrd_value {
	struct {
		uint32_t arqos_sfr:4; /* [3:0] */
		uint32_t reserved_bit_0:4;
		uint32_t awqos_sfr:4; /* [11:8] */
		uint32_t reserved_bit_1:4;
		uint32_t arqos_sfr_en:4; /* [19:16] */
		uint32_t reserved_bit_2:4;
		uint32_t awqos_sfr_en:4; /* [27:24] */
	};
	uint32_t val;
};

union sysreg_buscsr_pcie_m0_prot_ovrd_value {
	struct {
		uint32_t arprot1_sfr:1; /* [0:0] */
		uint32_t reserved_bit_0:7;
		uint32_t awprot1_sfr:1; /* [8:8] */
	};
	uint32_t val;
};

union sysreg_buscsr_pcie_m0_user_ovrd_value {
	struct {
		uint32_t aruser_sfr:1; /* [0:0] */
		uint32_t reserved_bit_0:7;
		uint32_t awuser_sfr:1; /* [8:8] */
		uint32_t reserved_bit_1:7;
		uint32_t aruser_sfr_en:1; /* [16:16] */
		uint32_t reserved_bit_2:7;
		uint32_t awuser_sfr_en:1; /* [24:24] */
	};
	uint32_t val;
};

union sysreg_buscsr_pcie_m0_cache_ovrd_sel {
	struct {
		uint32_t arcache_ovrd_sel:1; /* [0:0] */
		uint32_t reserved_bit_0:15;
		uint32_t awcache_ovrd_sel:1; /* [16:16] */
	};
	uint32_t val;
};

union sysreg_buscsr_pcie_m0_qos_ovrd_sel {
	struct {
		uint32_t arqos_ovrd_sel:1; /* [0:0] */
		uint32_t reserved_bit_0:15;
		uint32_t awqos_ovrd_sel:1; /* [16:16] */
	};
	uint32_t val;
};

union sysreg_buscsr_pcie_m0_prot_ovrd_sel {
	struct {
		uint32_t arprot1_ovrd_sel:1; /* [0:0] */
		uint32_t reserved_bit_0:15;
		uint32_t awprot1_ovrd_sel:1; /* [16:16] */
	};
	uint32_t val;
};

union sysreg_buscsr_pcie_m0_user_ovrd_sel {
	struct {
		uint32_t aruser_ovrd_sel:1; /* [0:0] */
		uint32_t reserved_bit_0:15;
		uint32_t awuser_ovrd_sel:1; /* [16:16] */
	};
	uint32_t val;
};

union sysreg_buscsr_pcie_m0_sel_pnd {
	struct {
		uint32_t status:1; /* [0:0] */
	};
	uint32_t val;
};

union sysreg_buscsr_pcie_m0_mon_status {
	struct {
		uint32_t value; /* [31:0] */
	};
	uint32_t val;
};

union sysreg_buscsr_pcie_m1_cache_ovrd_value {
	struct {
		uint32_t arcache_sfr:4; /* [3:0] */
		uint32_t reserved_bit_0:4;
		uint32_t awcache_sfr:4; /* [11:8] */
		uint32_t reserved_bit_1:4;
		uint32_t arcache_sfr_en:4; /* [19:16] */
		uint32_t reserved_bit_2:4;
		uint32_t awcache_sfr_en:4; /* [27:24] */
	};
	uint32_t val;
};

union sysreg_buscsr_pcie_m1_qos_ovrd_value {
	struct {
		uint32_t arqos_sfr:4; /* [3:0] */
		uint32_t reserved_bit_0:4;
		uint32_t awqos_sfr:4; /* [11:8] */
		uint32_t reserved_bit_1:4;
		uint32_t arqos_sfr_en:4; /* [19:16] */
		uint32_t reserved_bit_2:4;
		uint32_t awqos_sfr_en:4; /* [27:24] */
	};
	uint32_t val;
};

union sysreg_buscsr_pcie_m1_prot_ovrd_value {
	struct {
		uint32_t arprot1_sfr:1; /* [0:0] */
		uint32_t reserved_bit_0:7;
		uint32_t awprot1_sfr:1; /* [8:8] */
	};
	uint32_t val;
};

union sysreg_buscsr_pcie_m1_user_ovrd_value {
	struct {
		uint32_t aruser_sfr:1; /* [0:0] */
		uint32_t reserved_bit_0:7;
		uint32_t awuser_sfr:1; /* [8:8] */
		uint32_t reserved_bit_1:7;
		uint32_t aruser_sfr_en:1; /* [16:16] */
		uint32_t reserved_bit_2:7;
		uint32_t awuser_sfr_en:1; /* [24:24] */
	};
	uint32_t val;
};

union sysreg_buscsr_pcie_m1_cache_ovrd_sel {
	struct {
		uint32_t arcache_ovrd_sel:1; /* [0:0] */
		uint32_t reserved_bit_0:15;
		uint32_t awcache_ovrd_sel:1; /* [16:16] */
	};
	uint32_t val;
};

union sysreg_buscsr_pcie_m1_qos_ovrd_sel {
	struct {
		uint32_t arqos_ovrd_sel:1; /* [0:0] */
		uint32_t reserved_bit_0:15;
		uint32_t awqos_ovrd_sel:1; /* [16:16] */
	};
	uint32_t val;
};

union sysreg_buscsr_pcie_m1_prot_ovrd_sel {
	struct {
		uint32_t arprot1_ovrd_sel:1; /* [0:0] */
		uint32_t reserved_bit_0:15;
		uint32_t awprot1_ovrd_sel:1; /* [16:16] */
	};
	uint32_t val;
};

union sysreg_buscsr_pcie_m1_user_ovrd_sel {
	struct {
		uint32_t aruser_ovrd_sel:1; /* [0:0] */
		uint32_t reserved_bit_0:15;
		uint32_t awuser_ovrd_sel:1; /* [16:16] */
	};
	uint32_t val;
};

union sysreg_buscsr_pcie_m1_sel_pnd {
	struct {
		uint32_t status:1; /* [0:0] */
	};
	uint32_t val;
};

union sysreg_buscsr_pcie_m1_mon_status {
	struct {
		uint32_t value; /* [31:0] */
	};
	uint32_t val;
};

union sysreg_buscsr_pcie_m1_mon_ctrl {
	struct {
		uint32_t sel:4; /* [3:0] */
	};
	uint32_t val;
};

union sysreg_buscsr_pcie_s0_aruser_sfr0_m0 {
	struct {
		uint32_t reserved_bit_0:10;
		uint32_t pcie_slv_armisc_info:22; /* [31:10] */
	};
	uint32_t val;
};

union sysreg_buscsr_pcie_s0_aruser_sfr1_m0 {
	struct {
		uint32_t pcie_slv_armisc_info_tlpprfx_31_0; /* [31:0] */
	};
	uint32_t val;
};

union sysreg_buscsr_pcie_s0_aruser_sfr2_m0 {
	struct {
		uint32_t pcie_slv_armisc_info_tlpprfx_63_32; /* [31:0] */
	};
	uint32_t val;
};

union sysreg_buscsr_pcie_s0_aruser_sfr3_m0 {
	struct {
		uint32_t pcie_slv_armisc_info_tph:11; /* [10:0] */
		uint32_t reserved_bit_0:1;
		uint32_t pcie_slv_armisc_info_ats:2; /* [13:12] */
		uint32_t pcie_slv_armisc_info_atu_bypass:1; /* [14:14] */
		uint32_t reserved_bit_1:1;
		uint32_t pcie_slv_armisc_info_ido:1; /* [16:16] */
		uint32_t pcie_slv_armisc_info_nw:1; /* [17:17] */
		uint32_t pcie_slv_armisc_info_vfunc_active:1; /* [18:18] */
		uint32_t pcie_slv_armisc_info_func_num:1; /* [19:19] */
		uint32_t pcie_slv_armisc_info_vfunc_num:4; /* [23:20] */
		uint32_t pcie_slv_armisc_info_tlpprfx_71_64:8; /* [31:24] */
	};
	uint32_t val;
};

union sysreg_buscsr_pcie_s0_aruser_sfr0_m1 {
	struct {
		uint32_t reserved_bit_0:10;
		uint32_t pcie_slv_armisc_info:22; /* [31:10] */
	};
	uint32_t val;
};

union sysreg_buscsr_pcie_s0_aruser_sfr1_m1 {
	struct {
		uint32_t pcie_slv_armisc_info_tlpprfx_31_0; /* [31:0] */
	};
	uint32_t val;
};

union sysreg_buscsr_pcie_s0_aruser_sfr2_m1 {
	struct {
		uint32_t pcie_slv_armisc_info_tlpprfx_63_32; /* [31:0] */
	};
	uint32_t val;
};

union sysreg_buscsr_pcie_s0_aruser_sfr3_m1 {
	struct {
		uint32_t pcie_slv_armisc_info_tph:11; /* [10:0] */
		uint32_t reserved_bit_0:1;
		uint32_t pcie_slv_armisc_info_ats:2; /* [13:12] */
		uint32_t pcie_slv_armisc_info_atu_bypass:1; /* [14:14] */
		uint32_t reserved_bit_1:1;
		uint32_t pcie_slv_armisc_info_ido:1; /* [16:16] */
		uint32_t pcie_slv_armisc_info_nw:1; /* [17:17] */
		uint32_t pcie_slv_armisc_info_vfunc_active:1; /* [18:18] */
		uint32_t pcie_slv_armisc_info_func_num:1; /* [19:19] */
		uint32_t pcie_slv_armisc_info_vfunc_num:4; /* [23:20] */
		uint32_t pcie_slv_armisc_info_tlpprfx_71_64:8; /* [31:24] */
	};
	uint32_t val;
};

union sysreg_buscsr_pcie_s0_awuser_sfr0_m0 {
	struct {
		uint32_t pcie_slv_awmisc_info_p_tag:10; /* [9:0] */
		uint32_t pcie_slv_awmisc_info:22; /* [31:10] */
	};
	uint32_t val;
};

union sysreg_buscsr_pcie_s0_awuser_sfr1_m0 {
	struct {
		uint32_t pcie_slv_awmisc_info_tlpprfx_31_0; /* [31:0] */
	};
	uint32_t val;
};

union sysreg_buscsr_pcie_s0_awuser_sfr2_m0 {
	struct {
		uint32_t pcie_slv_awmisc_info_tlpprfx_63_32; /* [31:0] */
	};
	uint32_t val;
};

union sysreg_buscsr_pcie_s0_awuser_sfr3_m0 {
	struct {
		uint32_t pcie_slv_awmisc_info_tph:11; /* [10:0] */
		uint32_t reserved_bit_0:1;
		uint32_t pcie_slv_awmisc_info_ats:2; /* [13:12] */
		uint32_t pcie_slv_awmisc_info_atu_bypass:1; /* [14:14] */
		uint32_t reserved_bit_1:1;
		uint32_t pcie_slv_awmisc_info_ido:1; /* [16:16] */
		uint32_t pcie_slv_awmisc_info_nw:1; /* [17:17] */
		uint32_t pcie_slv_awmisc_info_vfunc_active:1; /* [18:18] */
		uint32_t pcie_slv_awmisc_info_func_num:1; /* [19:19] */
		uint32_t pcie_slv_awmisc_info_vfunc_num:4; /* [23:20] */
		uint32_t pcie_slv_awmisc_info_tlpprfx_71_64:8; /* [31:24] */
	};
	uint32_t val;
};

union sysreg_buscsr_pcie_s0_awuser_sfr4_m0 {
	struct {
		uint32_t pcie_slv_awmisc_info_hdr_34dw_31_0; /* [31:0] */
	};
	uint32_t val;
};

union sysreg_buscsr_pcie_s0_awuser_sfr5_m0 {
	struct {
		uint32_t pcie_slv_awmisc_info_hdr_34dw_63_32; /* [31:0] */
	};
	uint32_t val;
};

union sysreg_buscsr_pcie_s0_awuser_sfr0_m1 {
	struct {
		uint32_t pcie_slv_awmisc_info_p_tag:10; /* [9:0] */
		uint32_t pcie_slv_awmisc_info:22; /* [31:10] */
	};
	uint32_t val;
};

union sysreg_buscsr_pcie_s0_awuser_sfr1_m1 {
	struct {
		uint32_t pcie_slv_awmisc_info_tlpprfx_31_0; /* [31:0] */
	};
	uint32_t val;
};

union sysreg_buscsr_pcie_s0_awuser_sfr2_m1 {
	struct {
		uint32_t pcie_slv_awmisc_info_tlpprfx_63_32; /* [31:0] */
	};
	uint32_t val;
};

union sysreg_buscsr_pcie_s0_awuser_sfr3_m1 {
	struct {
		uint32_t pcie_slv_awmisc_info_tph:11; /* [10:0] */
		uint32_t reserved_bit_0:1;
		uint32_t pcie_slv_awmisc_info_ats:2; /* [13:12] */
		uint32_t pcie_slv_awmisc_info_atu_bypass:1; /* [14:14] */
		uint32_t reserved_bit_1:1;
		uint32_t pcie_slv_awmisc_info_ido:1; /* [16:16] */
		uint32_t pcie_slv_awmisc_info_nw:1; /* [17:17] */
		uint32_t pcie_slv_awmisc_info_vfunc_active:1; /* [18:18] */
		uint32_t pcie_slv_awmisc_info_func_num:1; /* [19:19] */
		uint32_t pcie_slv_awmisc_info_vfunc_num:4; /* [23:20] */
		uint32_t pcie_slv_awmisc_info_tlpprfx_71_64:8; /* [31:24] */
	};
	uint32_t val;
};

union sysreg_buscsr_pcie_s0_awuser_sfr4_m1 {
	struct {
		uint32_t pcie_slv_awmisc_info_hdr_34dw_31_0; /* [31:0] */
	};
	uint32_t val;
};

union sysreg_buscsr_pcie_s0_awuser_sfr5_m1 {
	struct {
		uint32_t pcie_slv_awmisc_info_hdr_34dw_63_32; /* [31:0] */
	};
	uint32_t val;
};

union sysreg_buscsr_pcie_s0_user_ovrd_sel {
	struct {
		uint32_t aruser_ovrd_sel:1; /* [0:0] */
		uint32_t reserved_bit_0:15;
		uint32_t awuser_ovrd_sel:1; /* [16:16] */
	};
	uint32_t val;
};

union sysreg_buscsr_pcie_s0_sel_pnd {
	struct {
		uint32_t status:1; /* [0:0] */
	};
	uint32_t val;
};

union sysreg_buscsr_pcie_sm_sid_ovrd_value {
	struct {
		uint32_t arsid_sfr:8; /* [7:0] */
		uint32_t awsid_sfr:8; /* [15:8] */
		uint32_t arsid_sfr_en:8; /* [23:16] */
		uint32_t awsid_sfr_en:8; /* [31:24] */
	};
	uint32_t val;
};

union sysreg_buscsr_pcie_sm_ssid_ovrd_value {
	struct {
		uint32_t arssid_sfr:8; /* [7:0] */
		uint32_t awssid_sfr:8; /* [15:8] */
		uint32_t arssid_sfr_en:8; /* [23:16] */
		uint32_t awssid_sfr_en:8; /* [31:24] */
	};
	uint32_t val;
};

union sysreg_buscsr_pcie_sm_ssidv_ovrd_value {
	struct {
		uint32_t arssidv_sfr:1; /* [0:0] */
		uint32_t reserved_bit_0:7;
		uint32_t awssidv_sfr:1; /* [8:8] */
	};
	uint32_t val;
};

union sysreg_buscsr_pcie_sm_secsid_ovrd_value {
	struct {
		uint32_t arsecsid_sfr:1; /* [0:0] */
		uint32_t reserved_bit_0:7;
		uint32_t awsecsid_sfr:1; /* [8:8] */
	};
	uint32_t val;
};

union sysreg_buscsr_pcie_sm_sid_ovrd_sel {
	struct {
		uint32_t arsid_ovrd_sel:1; /* [0:0] */
		uint32_t reserved_bit_0:15;
		uint32_t awsid_ovrd_sel:1; /* [16:16] */
	};
	uint32_t val;
};

union sysreg_buscsr_pcie_sm_ssid_ovrd_sel {
	struct {
		uint32_t arssid_ovrd_sel:1; /* [0:0] */
		uint32_t reserved_bit_0:15;
		uint32_t awssid_ovrd_sel:1; /* [16:16] */
	};
	uint32_t val;
};

union sysreg_buscsr_pcie_sm_ssidv_ovrd_sel {
	struct {
		uint32_t arssidv_ovrd_sel:1; /* [0:0] */
		uint32_t reserved_bit_0:15;
		uint32_t awssidv_ovrd_sel:1; /* [16:16] */
	};
	uint32_t val;
};

union sysreg_buscsr_pcie_sm_secsid_ovrd_sel {
	struct {
		uint32_t arsecsid_ovrd_sel:1; /* [0:0] */
		uint32_t reserved_bit_0:15;
		uint32_t awsecsid_ovrd_sel:1; /* [16:16] */
	};
	uint32_t val;
};

union sysreg_buscsr_pcie_sm_sel_pnd {
	struct {
		uint32_t status:1; /* [0:0] */
	};
	uint32_t val;
};

union sysreg_buscsr_pcie_sm_hdma_sid_lut0 {
	struct {
		uint32_t data:14; /* [13:0] */
	};
	uint32_t val;
};

union sysreg_buscsr_pcie_sm_hdma_sid_lut1 {
	struct {
		uint32_t data:14; /* [13:0] */
	};
	uint32_t val;
};

union sysreg_buscsr_pcie_sm_hdma_sid_lut2 {
	struct {
		uint32_t data:14; /* [13:0] */
	};
	uint32_t val;
};

union sysreg_buscsr_pcie_sm_hdma_sid_lut3 {
	struct {
		uint32_t data:14; /* [13:0] */
	};
	uint32_t val;
};

union sysreg_buscsr_pcie_sm_hdma_sid_lut4 {
	struct {
		uint32_t data:14; /* [13:0] */
	};
	uint32_t val;
};

union sysreg_buscsr_pcie_sm_hdma_sid_lut5 {
	struct {
		uint32_t data:14; /* [13:0] */
	};
	uint32_t val;
};

union sysreg_buscsr_pcie_sm_hdma_sid_lut6 {
	struct {
		uint32_t data:14; /* [13:0] */
	};
	uint32_t val;
};

union sysreg_buscsr_pcie_sm_hdma_sid_lut7 {
	struct {
		uint32_t data:14; /* [13:0] */
	};
	uint32_t val;
};

union sysreg_buscsr_pcie_sm_hdma_sid_lut8 {
	struct {
		uint32_t data:14; /* [13:0] */
	};
	uint32_t val;
};

union sysreg_buscsr_pcie_sm_hdma_sid_lut9 {
	struct {
		uint32_t data:14; /* [13:0] */
	};
	uint32_t val;
};

union sysreg_buscsr_pcie_sm_hdma_sid_lut10 {
	struct {
		uint32_t data:14; /* [13:0] */
	};
	uint32_t val;
};

union sysreg_buscsr_pcie_sm_hdma_sid_lut11 {
	struct {
		uint32_t data:14; /* [13:0] */
	};
	uint32_t val;
};

union sysreg_buscsr_pcie_sm_hdma_sid_lut12 {
	struct {
		uint32_t data:14; /* [13:0] */
	};
	uint32_t val;
};

union sysreg_buscsr_pcie_sm_hdma_sid_lut13 {
	struct {
		uint32_t data:14; /* [13:0] */
	};
	uint32_t val;
};

union sysreg_buscsr_pcie_sm_hdma_sid_lut14 {
	struct {
		uint32_t data:14; /* [13:0] */
	};
	uint32_t val;
};

union sysreg_buscsr_pcie_sm_hdma_sid_lut15 {
	struct {
		uint32_t data:14; /* [13:0] */
	};
	uint32_t val;
};

union sysreg_buscsr_pcie_sm_hdma_sid_lut {
	struct {
		uint32_t valid:16; /* [15:0] */
		uint32_t i_sid_mode:1; /* [16:16] */
	};
	uint32_t val;
};

union sysreg_buscsr_pcie_sfr_apb {
	struct {
		uint32_t en_timeout:1; /* [0:0] */
	};
	uint32_t val;
};

struct sysreg_buscsr_pcie_register {
	union sysreg_buscsr_pcie_m0_cache_ovrd_value m0_cache_ovrd_value; /* offset : 0x0 */
	union sysreg_buscsr_pcie_m0_qos_ovrd_value m0_qos_ovrd_value; /* offset : 0x4 */
	union sysreg_buscsr_pcie_m0_prot_ovrd_value m0_prot_ovrd_value; /* offset : 0x8 */
	union sysreg_buscsr_pcie_m0_user_ovrd_value m0_user_ovrd_value; /* offset : 0xc */
	uint32_t reserved_1[28];
	union sysreg_buscsr_pcie_m0_cache_ovrd_sel m0_cache_ovrd_sel; /* offset : 0x80 */
	union sysreg_buscsr_pcie_m0_qos_ovrd_sel m0_qos_ovrd_sel; /* offset : 0x84 */
	union sysreg_buscsr_pcie_m0_prot_ovrd_sel m0_prot_ovrd_sel; /* offset : 0x88 */
	union sysreg_buscsr_pcie_m0_user_ovrd_sel m0_user_ovrd_sel; /* offset : 0x8c */
	uint32_t reserved_2[4];
	union sysreg_buscsr_pcie_m0_sel_pnd m0_sel_pnd; /* offset : 0xa0 */
	uint32_t reserved_3[7];
	union sysreg_buscsr_pcie_m0_mon_status m0_mon_status; /* offset : 0xc0 */
	uint32_t reserved_4[15];
	union sysreg_buscsr_pcie_m1_cache_ovrd_value m1_cache_ovrd_value; /* offset : 0x100 */
	union sysreg_buscsr_pcie_m1_qos_ovrd_value m1_qos_ovrd_value; /* offset : 0x104 */
	union sysreg_buscsr_pcie_m1_prot_ovrd_value m1_prot_ovrd_value; /* offset : 0x108 */
	union sysreg_buscsr_pcie_m1_user_ovrd_value m1_user_ovrd_value; /* offset : 0x10c */
	uint32_t reserved_5[28];
	union sysreg_buscsr_pcie_m1_cache_ovrd_sel m1_cache_ovrd_sel; /* offset : 0x180 */
	union sysreg_buscsr_pcie_m1_qos_ovrd_sel m1_qos_ovrd_sel; /* offset : 0x184 */
	union sysreg_buscsr_pcie_m1_prot_ovrd_sel m1_prot_ovrd_sel; /* offset : 0x188 */
	union sysreg_buscsr_pcie_m1_user_ovrd_sel m1_user_ovrd_sel; /* offset : 0x18c */
	uint32_t reserved_6[4];
	union sysreg_buscsr_pcie_m1_sel_pnd m1_sel_pnd; /* offset : 0x1a0 */
	uint32_t reserved_7[7];
	union sysreg_buscsr_pcie_m1_mon_status m1_mon_status; /* offset : 0x1c0 */
	union sysreg_buscsr_pcie_m1_mon_ctrl m1_mon_ctrl; /* offset : 0x1c4 */
	uint32_t reserved_8[14];
	union sysreg_buscsr_pcie_s0_aruser_sfr0_m0 s0_aruser_sfr0_m0; /* offset : 0x200 */
	union sysreg_buscsr_pcie_s0_aruser_sfr1_m0 s0_aruser_sfr1_m0; /* offset : 0x204 */
	union sysreg_buscsr_pcie_s0_aruser_sfr2_m0 s0_aruser_sfr2_m0; /* offset : 0x208 */
	union sysreg_buscsr_pcie_s0_aruser_sfr3_m0 s0_aruser_sfr3_m0; /* offset : 0x20c */
	union sysreg_buscsr_pcie_s0_aruser_sfr0_m1 s0_aruser_sfr0_m1; /* offset : 0x210 */
	union sysreg_buscsr_pcie_s0_aruser_sfr1_m1 s0_aruser_sfr1_m1; /* offset : 0x214 */
	union sysreg_buscsr_pcie_s0_aruser_sfr2_m1 s0_aruser_sfr2_m1; /* offset : 0x218 */
	union sysreg_buscsr_pcie_s0_aruser_sfr3_m1 s0_aruser_sfr3_m1; /* offset : 0x21c */
	union sysreg_buscsr_pcie_s0_awuser_sfr0_m0 s0_awuser_sfr0_m0; /* offset : 0x220 */
	union sysreg_buscsr_pcie_s0_awuser_sfr1_m0 s0_awuser_sfr1_m0; /* offset : 0x224 */
	union sysreg_buscsr_pcie_s0_awuser_sfr2_m0 s0_awuser_sfr2_m0; /* offset : 0x228 */
	union sysreg_buscsr_pcie_s0_awuser_sfr3_m0 s0_awuser_sfr3_m0; /* offset : 0x22c */
	union sysreg_buscsr_pcie_s0_awuser_sfr4_m0 s0_awuser_sfr4_m0; /* offset : 0x230 */
	union sysreg_buscsr_pcie_s0_awuser_sfr5_m0 s0_awuser_sfr5_m0; /* offset : 0x234 */
	uint32_t reserved_9[2];
	union sysreg_buscsr_pcie_s0_awuser_sfr0_m1 s0_awuser_sfr0_m1; /* offset : 0x240 */
	union sysreg_buscsr_pcie_s0_awuser_sfr1_m1 s0_awuser_sfr1_m1; /* offset : 0x244 */
	union sysreg_buscsr_pcie_s0_awuser_sfr2_m1 s0_awuser_sfr2_m1; /* offset : 0x248 */
	union sysreg_buscsr_pcie_s0_awuser_sfr3_m1 s0_awuser_sfr3_m1; /* offset : 0x24c */
	union sysreg_buscsr_pcie_s0_awuser_sfr4_m1 s0_awuser_sfr4_m1; /* offset : 0x250 */
	union sysreg_buscsr_pcie_s0_awuser_sfr5_m1 s0_awuser_sfr5_m1; /* offset : 0x254 */
	uint32_t reserved_10[13];
	union sysreg_buscsr_pcie_s0_user_ovrd_sel s0_user_ovrd_sel; /* offset : 0x28c */
	uint32_t reserved_11[4];
	union sysreg_buscsr_pcie_s0_sel_pnd s0_sel_pnd; /* offset : 0x2a0 */
	uint32_t reserved_12[23];
	union sysreg_buscsr_pcie_sm_sid_ovrd_value sm_sid_ovrd_value; /* offset : 0x300 */
	union sysreg_buscsr_pcie_sm_ssid_ovrd_value sm_ssid_ovrd_value; /* offset : 0x304 */
	union sysreg_buscsr_pcie_sm_ssidv_ovrd_value sm_ssidv_ovrd_value; /* offset : 0x308 */
	union sysreg_buscsr_pcie_sm_secsid_ovrd_value sm_secsid_ovrd_value; /* offset : 0x30c */
	uint32_t reserved_13[28];
	union sysreg_buscsr_pcie_sm_sid_ovrd_sel sm_sid_ovrd_sel; /* offset : 0x380 */
	union sysreg_buscsr_pcie_sm_ssid_ovrd_sel sm_ssid_ovrd_sel; /* offset : 0x384 */
	union sysreg_buscsr_pcie_sm_ssidv_ovrd_sel sm_ssidv_ovrd_sel; /* offset : 0x388 */
	union sysreg_buscsr_pcie_sm_secsid_ovrd_sel sm_secsid_ovrd_sel; /* offset : 0x38c */
	uint32_t reserved_14[4];
	union sysreg_buscsr_pcie_sm_sel_pnd sm_sel_pnd; /* offset : 0x3a0 */
	uint32_t reserved_15[7];
	union sysreg_buscsr_pcie_sm_hdma_sid_lut0 sm_hdma_sid_lut0; /* offset : 0x3c0 */
	union sysreg_buscsr_pcie_sm_hdma_sid_lut1 sm_hdma_sid_lut1; /* offset : 0x3c4 */
	union sysreg_buscsr_pcie_sm_hdma_sid_lut2 sm_hdma_sid_lut2; /* offset : 0x3c8 */
	union sysreg_buscsr_pcie_sm_hdma_sid_lut3 sm_hdma_sid_lut3; /* offset : 0x3cc */
	union sysreg_buscsr_pcie_sm_hdma_sid_lut4 sm_hdma_sid_lut4; /* offset : 0x3d0 */
	union sysreg_buscsr_pcie_sm_hdma_sid_lut5 sm_hdma_sid_lut5; /* offset : 0x3d4 */
	union sysreg_buscsr_pcie_sm_hdma_sid_lut6 sm_hdma_sid_lut6; /* offset : 0x3d8 */
	union sysreg_buscsr_pcie_sm_hdma_sid_lut7 sm_hdma_sid_lut7; /* offset : 0x3dc */
	union sysreg_buscsr_pcie_sm_hdma_sid_lut8 sm_hdma_sid_lut8; /* offset : 0x3e0 */
	union sysreg_buscsr_pcie_sm_hdma_sid_lut9 sm_hdma_sid_lut9; /* offset : 0x3e4 */
	union sysreg_buscsr_pcie_sm_hdma_sid_lut10 sm_hdma_sid_lut10; /* offset : 0x3e8 */
	union sysreg_buscsr_pcie_sm_hdma_sid_lut11 sm_hdma_sid_lut11; /* offset : 0x3ec */
	union sysreg_buscsr_pcie_sm_hdma_sid_lut12 sm_hdma_sid_lut12; /* offset : 0x3f0 */
	union sysreg_buscsr_pcie_sm_hdma_sid_lut13 sm_hdma_sid_lut13; /* offset : 0x3f4 */
	union sysreg_buscsr_pcie_sm_hdma_sid_lut14 sm_hdma_sid_lut14; /* offset : 0x3f8 */
	union sysreg_buscsr_pcie_sm_hdma_sid_lut15 sm_hdma_sid_lut15; /* offset : 0x3fc */
	union sysreg_buscsr_pcie_sm_hdma_sid_lut sm_hdma_sid_lut; /* offset : 0x400 */
	uint32_t reserved_16[766];
	union sysreg_buscsr_pcie_sfr_apb sfr_apb; /* offset : 0xffc */
};
