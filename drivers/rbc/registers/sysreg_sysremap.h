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

union sysreg_sysremap_m0_cache_ovrd_value {
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

union sysreg_sysremap_m0_qos_ovrd_value {
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

union sysreg_sysremap_m0_prot_ovrd_value {
	struct {
		uint32_t arprot1_sfr:1; /* [0:0] */
		uint32_t reserved_bit_0:7;
		uint32_t awprot1_sfr:1; /* [8:8] */
	};
	uint32_t val;
};

union sysreg_sysremap_m0_user_ovrd_value {
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

union sysreg_sysremap_m0_cache_ovrd_sel {
	struct {
		uint32_t arcache_ovrd_sel:1; /* [0:0] */
		uint32_t reserved_bit_0:15;
		uint32_t awcache_ovrd_sel:1; /* [16:16] */
	};
	uint32_t val;
};

union sysreg_sysremap_m0_qos_ovrd_sel {
	struct {
		uint32_t arqos_ovrd_sel:1; /* [0:0] */
		uint32_t reserved_bit_0:15;
		uint32_t awqos_ovrd_sel:1; /* [16:16] */
	};
	uint32_t val;
};

union sysreg_sysremap_m0_prot_ovrd_sel {
	struct {
		uint32_t arprot1_ovrd_sel:1; /* [0:0] */
		uint32_t reserved_bit_0:15;
		uint32_t awprot1_ovrd_sel:1; /* [16:16] */
	};
	uint32_t val;
};

union sysreg_sysremap_m0_user_ovrd_sel {
	struct {
		uint32_t aruser_ovrd_sel:1; /* [0:0] */
		uint32_t reserved_bit_0:15;
		uint32_t awuser_ovrd_sel:1; /* [16:16] */
	};
	uint32_t val;
};

union sysreg_sysremap_m0_sel_pnd {
	struct {
		uint32_t status:1; /* [0:0] */
	};
	uint32_t val;
};

union sysreg_sysremap_m1_cache_ovrd_value {
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

union sysreg_sysremap_m1_qos_ovrd_value {
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

union sysreg_sysremap_m1_prot_ovrd_value {
	struct {
		uint32_t arprot1_sfr:1; /* [0:0] */
		uint32_t reserved_bit_0:7;
		uint32_t awprot1_sfr:1; /* [8:8] */
	};
	uint32_t val;
};

union sysreg_sysremap_m1_user_ovrd_value {
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

union sysreg_sysremap_m1_cache_ovrd_sel {
	struct {
		uint32_t arcache_ovrd_sel:1; /* [0:0] */
		uint32_t reserved_bit_0:15;
		uint32_t awcache_ovrd_sel:1; /* [16:16] */
	};
	uint32_t val;
};

union sysreg_sysremap_m1_qos_ovrd_sel {
	struct {
		uint32_t arqos_ovrd_sel:1; /* [0:0] */
		uint32_t reserved_bit_0:15;
		uint32_t awqos_ovrd_sel:1; /* [16:16] */
	};
	uint32_t val;
};

union sysreg_sysremap_m1_prot_ovrd_sel {
	struct {
		uint32_t arprot1_ovrd_sel:1; /* [0:0] */
		uint32_t reserved_bit_0:15;
		uint32_t awprot1_ovrd_sel:1; /* [16:16] */
	};
	uint32_t val;
};

union sysreg_sysremap_m1_user_ovrd_sel {
	struct {
		uint32_t aruser_ovrd_sel:1; /* [0:0] */
		uint32_t reserved_bit_0:15;
		uint32_t awuser_ovrd_sel:1; /* [16:16] */
	};
	uint32_t val;
};

union sysreg_sysremap_m1_sel_pnd {
	struct {
		uint32_t status:1; /* [0:0] */
	};
	uint32_t val;
};

union sysreg_sysremap_m2_cache_ovrd_value {
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

union sysreg_sysremap_m2_qos_ovrd_value {
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

union sysreg_sysremap_m2_prot_ovrd_value {
	struct {
		uint32_t arprot1_sfr:1; /* [0:0] */
		uint32_t reserved_bit_0:7;
		uint32_t awprot1_sfr:1; /* [8:8] */
	};
	uint32_t val;
};

union sysreg_sysremap_m2_user_ovrd_value {
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

union sysreg_sysremap_m2_cache_ovrd_sel {
	struct {
		uint32_t arcache_ovrd_sel:1; /* [0:0] */
		uint32_t reserved_bit_0:15;
		uint32_t awcache_ovrd_sel:1; /* [16:16] */
	};
	uint32_t val;
};

union sysreg_sysremap_m2_qos_ovrd_sel {
	struct {
		uint32_t arqos_ovrd_sel:1; /* [0:0] */
		uint32_t reserved_bit_0:15;
		uint32_t awqos_ovrd_sel:1; /* [16:16] */
	};
	uint32_t val;
};

union sysreg_sysremap_m2_prot_ovrd_sel {
	struct {
		uint32_t arprot1_ovrd_sel:1; /* [0:0] */
		uint32_t reserved_bit_0:15;
		uint32_t awprot1_ovrd_sel:1; /* [16:16] */
	};
	uint32_t val;
};

union sysreg_sysremap_m2_user_ovrd_sel {
	struct {
		uint32_t aruser_ovrd_sel:1; /* [0:0] */
		uint32_t reserved_bit_0:15;
		uint32_t awuser_ovrd_sel:1; /* [16:16] */
	};
	uint32_t val;
};

union sysreg_sysremap_m2_sel_pnd {
	struct {
		uint32_t status:1; /* [0:0] */
	};
	uint32_t val;
};

union sysreg_sysremap_m3_cache_ovrd_value {
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

union sysreg_sysremap_m3_qos_ovrd_value {
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

union sysreg_sysremap_m3_prot_ovrd_value {
	struct {
		uint32_t arprot1_sfr:1; /* [0:0] */
		uint32_t reserved_bit_0:7;
		uint32_t awprot1_sfr:1; /* [8:8] */
	};
	uint32_t val;
};

union sysreg_sysremap_m3_user_ovrd_value {
	struct {
		uint32_t aruser_sfr:12; /* [11:0] */
		uint32_t reserved_bit_0:4;
		uint32_t awuser_sfr:12; /* [27:16] */
	};
	uint32_t val;
};

union sysreg_sysremap_m3_sid_ovrd_value {
	struct {
		uint32_t arsid_sfr:8; /* [7:0] */
		uint32_t awsid_sfr:8; /* [15:8] */
	};
	uint32_t val;
};

union sysreg_sysremap_m3_ssid_ovrd_value {
	struct {
		uint32_t arssid_sfr:8; /* [7:0] */
		uint32_t awssid_sfr:8; /* [15:8] */
	};
	uint32_t val;
};

union sysreg_sysremap_m3_ssidv_ovrd_value {
	struct {
		uint32_t arssidv_sfr:1; /* [0:0] */
		uint32_t reserved_bit_0:7;
		uint32_t awssidv_sfr:1; /* [8:8] */
	};
	uint32_t val;
};

union sysreg_sysremap_m3_secsid_ovrd_value {
	struct {
		uint32_t arsecsid_sfr:1; /* [0:0] */
		uint32_t reserved_bit_0:7;
		uint32_t awsecsid_sfr:1; /* [8:8] */
	};
	uint32_t val;
};

union sysreg_sysremap_m3_cache_ovrd_sel {
	struct {
		uint32_t arcache_ovrd_sel:1; /* [0:0] */
		uint32_t reserved_bit_0:15;
		uint32_t awcache_ovrd_sel:1; /* [16:16] */
	};
	uint32_t val;
};

union sysreg_sysremap_m3_qos_ovrd_sel {
	struct {
		uint32_t arqos_ovrd_sel:1; /* [0:0] */
		uint32_t reserved_bit_0:15;
		uint32_t awqos_ovrd_sel:1; /* [16:16] */
	};
	uint32_t val;
};

union sysreg_sysremap_m3_prot_ovrd_sel {
	struct {
		uint32_t arprot1_ovrd_sel:1; /* [0:0] */
		uint32_t reserved_bit_0:15;
		uint32_t awprot1_ovrd_sel:1; /* [16:16] */
	};
	uint32_t val;
};

union sysreg_sysremap_m3_user_ovrd_sel {
	struct {
		uint32_t aruser_ovrd_sel:1; /* [0:0] */
		uint32_t reserved_bit_0:15;
		uint32_t awuser_ovrd_sel:1; /* [16:16] */
	};
	uint32_t val;
};

union sysreg_sysremap_m3_sid_ovrd_sel {
	struct {
		uint32_t arsid_ovrd_sel:1; /* [0:0] */
		uint32_t reserved_bit_0:15;
		uint32_t awsid_ovrd_sel:1; /* [16:16] */
	};
	uint32_t val;
};

union sysreg_sysremap_m3_ssid_ovrd_sel {
	struct {
		uint32_t arssid_ovrd_sel:1; /* [0:0] */
		uint32_t reserved_bit_0:15;
		uint32_t awssid_ovrd_sel:1; /* [16:16] */
	};
	uint32_t val;
};

union sysreg_sysremap_m3_ssidv_ovrd_sel {
	struct {
		uint32_t arssidv_ovrd_sel:1; /* [0:0] */
		uint32_t reserved_bit_0:15;
		uint32_t awssidv_ovrd_sel:1; /* [16:16] */
	};
	uint32_t val;
};

union sysreg_sysremap_m3_secsid_ovrd_sel {
	struct {
		uint32_t arsecsid_ovrd_sel:1; /* [0:0] */
		uint32_t reserved_bit_0:15;
		uint32_t awsecsid_ovrd_sel:1; /* [16:16] */
	};
	uint32_t val;
};

union sysreg_sysremap_m3_sel_pnd {
	struct {
		uint32_t status:1; /* [0:0] */
	};
	uint32_t val;
};

union sysreg_sysremap_remap_noc {
	struct {
		uint32_t mode_offset_0x00:2; /* [1:0] */
		uint32_t reserved_bit_0:2;
		uint32_t mode_offset_0x20:2; /* [5:4] */
		uint32_t reserved_bit_1:2;
		uint32_t mode_offset_0x40:2; /* [9:8] */
		uint32_t reserved_bit_2:2;
		uint32_t mode_offset_0x60:2; /* [13:12] */
		uint32_t reserved_bit_3:2;
		uint32_t mode_host_dir:2; /* [17:16] */
	};
	uint32_t val;
};

union sysreg_sysremap_remap_nic {
	struct {
		uint32_t mode_nic; /* [31:0] */
	};
	uint32_t val;
};

union sysreg_sysremap_chiplet {
	struct {
		uint32_t id:2; /* [1:0] */
	};
	uint32_t val;
};

union sysreg_sysremap_sfr_apb {
	struct {
		uint32_t en_timeout:1; /* [0:0] */
	};
	uint32_t val;
};

struct sysreg_sysremap {
	union sysreg_sysremap_m0_cache_ovrd_value m0_cache_ovrd_value; /* offset : 0x0 */
	union sysreg_sysremap_m0_qos_ovrd_value m0_qos_ovrd_value; /* offset : 0x4 */
	union sysreg_sysremap_m0_prot_ovrd_value m0_prot_ovrd_value; /* offset : 0x8 */
	union sysreg_sysremap_m0_user_ovrd_value m0_user_ovrd_value; /* offset : 0xc */
	uint32_t reserved_1[28];
	union sysreg_sysremap_m0_cache_ovrd_sel m0_cache_ovrd_sel; /* offset : 0x80 */
	union sysreg_sysremap_m0_qos_ovrd_sel m0_qos_ovrd_sel; /* offset : 0x84 */
	union sysreg_sysremap_m0_prot_ovrd_sel m0_prot_ovrd_sel; /* offset : 0x88 */
	union sysreg_sysremap_m0_user_ovrd_sel m0_user_ovrd_sel; /* offset : 0x8c */
	uint32_t reserved_2[4];
	union sysreg_sysremap_m0_sel_pnd m0_sel_pnd; /* offset : 0xa0 */
	uint32_t reserved_3[23];
	union sysreg_sysremap_m1_cache_ovrd_value m1_cache_ovrd_value; /* offset : 0x100 */
	union sysreg_sysremap_m1_qos_ovrd_value m1_qos_ovrd_value; /* offset : 0x104 */
	union sysreg_sysremap_m1_prot_ovrd_value m1_prot_ovrd_value; /* offset : 0x108 */
	union sysreg_sysremap_m1_user_ovrd_value m1_user_ovrd_value; /* offset : 0x10c */
	uint32_t reserved_4[28];
	union sysreg_sysremap_m1_cache_ovrd_sel m1_cache_ovrd_sel; /* offset : 0x180 */
	union sysreg_sysremap_m1_qos_ovrd_sel m1_qos_ovrd_sel; /* offset : 0x184 */
	union sysreg_sysremap_m1_prot_ovrd_sel m1_prot_ovrd_sel; /* offset : 0x188 */
	union sysreg_sysremap_m1_user_ovrd_sel m1_user_ovrd_sel; /* offset : 0x18c */
	uint32_t reserved_5[4];
	union sysreg_sysremap_m1_sel_pnd m1_sel_pnd; /* offset : 0x1a0 */
	uint32_t reserved_6[23];
	union sysreg_sysremap_m2_cache_ovrd_value m2_cache_ovrd_value; /* offset : 0x200 */
	union sysreg_sysremap_m2_qos_ovrd_value m2_qos_ovrd_value; /* offset : 0x204 */
	union sysreg_sysremap_m2_prot_ovrd_value m2_prot_ovrd_value; /* offset : 0x208 */
	union sysreg_sysremap_m2_user_ovrd_value m2_user_ovrd_value; /* offset : 0x20c */
	uint32_t reserved_7[28];
	union sysreg_sysremap_m2_cache_ovrd_sel m2_cache_ovrd_sel; /* offset : 0x280 */
	union sysreg_sysremap_m2_qos_ovrd_sel m2_qos_ovrd_sel; /* offset : 0x284 */
	union sysreg_sysremap_m2_prot_ovrd_sel m2_prot_ovrd_sel; /* offset : 0x288 */
	union sysreg_sysremap_m2_user_ovrd_sel m2_user_ovrd_sel; /* offset : 0x28c */
	uint32_t reserved_8[4];
	union sysreg_sysremap_m2_sel_pnd m2_sel_pnd; /* offset : 0x2a0 */
	uint32_t reserved_9[23];
	union sysreg_sysremap_m3_cache_ovrd_value m3_cache_ovrd_value; /* offset : 0x300 */
	union sysreg_sysremap_m3_qos_ovrd_value m3_qos_ovrd_value; /* offset : 0x304 */
	union sysreg_sysremap_m3_prot_ovrd_value m3_prot_ovrd_value; /* offset : 0x308 */
	uint32_t reserved_10[4];
	union sysreg_sysremap_m3_user_ovrd_value m3_user_ovrd_value; /* offset : 0x31c */
	union sysreg_sysremap_m3_sid_ovrd_value m3_sid_ovrd_value; /* offset : 0x320 */
	union sysreg_sysremap_m3_ssid_ovrd_value m3_ssid_ovrd_value; /* offset : 0x324 */
	union sysreg_sysremap_m3_ssidv_ovrd_value m3_ssidv_ovrd_value; /* offset : 0x328 */
	union sysreg_sysremap_m3_secsid_ovrd_value m3_secsid_ovrd_value; /* offset : 0x32c */
	uint32_t reserved_11[20];
	union sysreg_sysremap_m3_cache_ovrd_sel m3_cache_ovrd_sel; /* offset : 0x380 */
	union sysreg_sysremap_m3_qos_ovrd_sel m3_qos_ovrd_sel; /* offset : 0x384 */
	union sysreg_sysremap_m3_prot_ovrd_sel m3_prot_ovrd_sel; /* offset : 0x388 */
	union sysreg_sysremap_m3_user_ovrd_sel m3_user_ovrd_sel; /* offset : 0x38c */
	union sysreg_sysremap_m3_sid_ovrd_sel m3_sid_ovrd_sel; /* offset : 0x390 */
	union sysreg_sysremap_m3_ssid_ovrd_sel m3_ssid_ovrd_sel; /* offset : 0x394 */
	union sysreg_sysremap_m3_ssidv_ovrd_sel m3_ssidv_ovrd_sel; /* offset : 0x398 */
	union sysreg_sysremap_m3_secsid_ovrd_sel m3_secsid_ovrd_sel; /* offset : 0x39c */
	union sysreg_sysremap_m3_sel_pnd m3_sel_pnd; /* offset : 0x3a0 */
	uint32_t reserved_12[23];
	union sysreg_sysremap_remap_noc remap_noc; /* offset : 0x400 */
	union sysreg_sysremap_remap_nic remap_nic; /* offset : 0x404 */
	uint32_t reserved_13[15];
	union sysreg_sysremap_chiplet chiplet; /* offset : 0x444 */
	uint32_t reserved_14[749];
	union sysreg_sysremap_sfr_apb sfr_apb; /* offset : 0xffc */
};
