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

#include <stdint.h>
#include "rl_errors.h"
#include <rebel_h_platform.h>

#include "pcie_dw.h"

static void pcie_phy_set_cntx_restore_mode(const struct dw_pcie_config *cfg)
{
	volatile struct pcie_subctrl_register *subctrl_base = cfg->subctrl_base;

	subctrl_base->sfr_phy_cfg_120_reg.phy_lane0_cntx_en = 1;
	subctrl_base->sfr_phy_cfg_120_reg.phy_lane1_cntx_en = 1;
	subctrl_base->sfr_phy_cfg_120_reg.phy_lane2_cntx_en = 1;
	subctrl_base->sfr_phy_cfg_120_reg.phy_lane3_cntx_en = 1;
	subctrl_base->sfr_phy_cfg_120_reg.phy_lane4_cntx_en = 1;
	subctrl_base->sfr_phy_cfg_120_reg.phy_lane5_cntx_en = 1;
	subctrl_base->sfr_phy_cfg_120_reg.phy_lane6_cntx_en = 1;
	subctrl_base->sfr_phy_cfg_120_reg.phy_lane7_cntx_en = 1;
	subctrl_base->sfr_phy_cfg_120_reg.phy_lane8_cntx_en = 1;
	subctrl_base->sfr_phy_cfg_120_reg.phy_lane9_cntx_en = 1;
	subctrl_base->sfr_phy_cfg_120_reg.phy_lane10_cntx_en = 1;
	subctrl_base->sfr_phy_cfg_120_reg.phy_lane11_cntx_en = 1;
	subctrl_base->sfr_phy_cfg_120_reg.phy_lane12_cntx_en = 1;
	subctrl_base->sfr_phy_cfg_120_reg.phy_lane13_cntx_en = 1;
	subctrl_base->sfr_phy_cfg_120_reg.phy_lane14_cntx_en = 1;
	subctrl_base->sfr_phy_cfg_120_reg.phy_lane15_cntx_en = 1;

	subctrl_base->sfr_phy_cfg_121_reg.phy_rx0_cntx_sel_g1 = 10;
	subctrl_base->sfr_phy_cfg_121_reg.phy_rx0_cntx_sel_g2 = 11;
	subctrl_base->sfr_phy_cfg_121_reg.phy_rx0_cntx_sel_g3 = 12;
	subctrl_base->sfr_phy_cfg_121_reg.phy_rx0_cntx_sel_g4 = 13;
	subctrl_base->sfr_phy_cfg_122_reg.phy_rx0_cntx_sel_g5 = 14;
	subctrl_base->sfr_phy_cfg_123_reg.phy_rx1_cntx_sel_g1 = 10;
	subctrl_base->sfr_phy_cfg_123_reg.phy_rx1_cntx_sel_g2 = 11;
	subctrl_base->sfr_phy_cfg_123_reg.phy_rx1_cntx_sel_g3 = 12;
	subctrl_base->sfr_phy_cfg_123_reg.phy_rx1_cntx_sel_g4 = 13;
	subctrl_base->sfr_phy_cfg_124_reg.phy_rx1_cntx_sel_g5 = 14;
	subctrl_base->sfr_phy_cfg_125_reg.phy_rx2_cntx_sel_g1 = 10;
	subctrl_base->sfr_phy_cfg_125_reg.phy_rx2_cntx_sel_g2 = 11;
	subctrl_base->sfr_phy_cfg_125_reg.phy_rx2_cntx_sel_g3 = 12;
	subctrl_base->sfr_phy_cfg_125_reg.phy_rx2_cntx_sel_g4 = 13;
	subctrl_base->sfr_phy_cfg_126_reg.phy_rx2_cntx_sel_g5 = 14;
	subctrl_base->sfr_phy_cfg_127_reg.phy_rx3_cntx_sel_g1 = 10;
	subctrl_base->sfr_phy_cfg_127_reg.phy_rx3_cntx_sel_g2 = 11;
	subctrl_base->sfr_phy_cfg_127_reg.phy_rx3_cntx_sel_g3 = 12;
	subctrl_base->sfr_phy_cfg_127_reg.phy_rx3_cntx_sel_g4 = 13;
	subctrl_base->sfr_phy_cfg_128_reg.phy_rx3_cntx_sel_g5 = 14;
	subctrl_base->sfr_phy_cfg_129_reg.phy_rx4_cntx_sel_g1 = 10;
	subctrl_base->sfr_phy_cfg_129_reg.phy_rx4_cntx_sel_g2 = 11;
	subctrl_base->sfr_phy_cfg_129_reg.phy_rx4_cntx_sel_g3 = 12;
	subctrl_base->sfr_phy_cfg_129_reg.phy_rx4_cntx_sel_g4 = 13;
	subctrl_base->sfr_phy_cfg_130_reg.phy_rx4_cntx_sel_g5 = 14;
	subctrl_base->sfr_phy_cfg_131_reg.phy_rx5_cntx_sel_g1 = 10;
	subctrl_base->sfr_phy_cfg_131_reg.phy_rx5_cntx_sel_g2 = 11;
	subctrl_base->sfr_phy_cfg_131_reg.phy_rx5_cntx_sel_g3 = 12;
	subctrl_base->sfr_phy_cfg_131_reg.phy_rx5_cntx_sel_g4 = 13;
	subctrl_base->sfr_phy_cfg_132_reg.phy_rx5_cntx_sel_g5 = 14;
	subctrl_base->sfr_phy_cfg_133_reg.phy_rx6_cntx_sel_g1 = 10;
	subctrl_base->sfr_phy_cfg_133_reg.phy_rx6_cntx_sel_g2 = 11;
	subctrl_base->sfr_phy_cfg_133_reg.phy_rx6_cntx_sel_g3 = 12;
	subctrl_base->sfr_phy_cfg_133_reg.phy_rx6_cntx_sel_g4 = 13;
	subctrl_base->sfr_phy_cfg_134_reg.phy_rx6_cntx_sel_g5 = 14;
	subctrl_base->sfr_phy_cfg_135_reg.phy_rx7_cntx_sel_g1 = 10;
	subctrl_base->sfr_phy_cfg_135_reg.phy_rx7_cntx_sel_g2 = 11;
	subctrl_base->sfr_phy_cfg_135_reg.phy_rx7_cntx_sel_g3 = 12;
	subctrl_base->sfr_phy_cfg_135_reg.phy_rx7_cntx_sel_g4 = 13;
	subctrl_base->sfr_phy_cfg_136_reg.phy_rx7_cntx_sel_g5 = 14;
	subctrl_base->sfr_phy_cfg_137_reg.phy_rx8_cntx_sel_g1 = 10;
	subctrl_base->sfr_phy_cfg_137_reg.phy_rx8_cntx_sel_g2 = 11;
	subctrl_base->sfr_phy_cfg_137_reg.phy_rx8_cntx_sel_g3 = 12;
	subctrl_base->sfr_phy_cfg_137_reg.phy_rx8_cntx_sel_g4 = 13;
	subctrl_base->sfr_phy_cfg_138_reg.phy_rx8_cntx_sel_g5 = 14;
	subctrl_base->sfr_phy_cfg_139_reg.phy_rx9_cntx_sel_g1 = 10;
	subctrl_base->sfr_phy_cfg_139_reg.phy_rx9_cntx_sel_g2 = 11;
	subctrl_base->sfr_phy_cfg_139_reg.phy_rx9_cntx_sel_g3 = 12;
	subctrl_base->sfr_phy_cfg_139_reg.phy_rx9_cntx_sel_g4 = 13;
	subctrl_base->sfr_phy_cfg_140_reg.phy_rx9_cntx_sel_g5 = 14;
	subctrl_base->sfr_phy_cfg_141_reg.phy_rx10_cntx_sel_g1 = 10;
	subctrl_base->sfr_phy_cfg_141_reg.phy_rx10_cntx_sel_g2 = 11;
	subctrl_base->sfr_phy_cfg_141_reg.phy_rx10_cntx_sel_g3 = 12;
	subctrl_base->sfr_phy_cfg_141_reg.phy_rx10_cntx_sel_g4 = 13;
	subctrl_base->sfr_phy_cfg_142_reg.phy_rx10_cntx_sel_g5 = 14;
	subctrl_base->sfr_phy_cfg_143_reg.phy_rx11_cntx_sel_g1 = 10;
	subctrl_base->sfr_phy_cfg_143_reg.phy_rx11_cntx_sel_g2 = 11;
	subctrl_base->sfr_phy_cfg_143_reg.phy_rx11_cntx_sel_g3 = 12;
	subctrl_base->sfr_phy_cfg_143_reg.phy_rx11_cntx_sel_g4 = 13;
	subctrl_base->sfr_phy_cfg_144_reg.phy_rx11_cntx_sel_g5 = 14;
	subctrl_base->sfr_phy_cfg_145_reg.phy_rx12_cntx_sel_g1 = 10;
	subctrl_base->sfr_phy_cfg_145_reg.phy_rx12_cntx_sel_g2 = 11;
	subctrl_base->sfr_phy_cfg_145_reg.phy_rx12_cntx_sel_g3 = 12;
	subctrl_base->sfr_phy_cfg_145_reg.phy_rx12_cntx_sel_g4 = 13;
	subctrl_base->sfr_phy_cfg_146_reg.phy_rx12_cntx_sel_g5 = 14;
	subctrl_base->sfr_phy_cfg_147_reg.phy_rx13_cntx_sel_g1 = 10;
	subctrl_base->sfr_phy_cfg_147_reg.phy_rx13_cntx_sel_g2 = 11;
	subctrl_base->sfr_phy_cfg_147_reg.phy_rx13_cntx_sel_g3 = 12;
	subctrl_base->sfr_phy_cfg_147_reg.phy_rx13_cntx_sel_g4 = 13;
	subctrl_base->sfr_phy_cfg_148_reg.phy_rx13_cntx_sel_g5 = 14;
	subctrl_base->sfr_phy_cfg_149_reg.phy_rx14_cntx_sel_g1 = 10;
	subctrl_base->sfr_phy_cfg_149_reg.phy_rx14_cntx_sel_g2 = 11;
	subctrl_base->sfr_phy_cfg_149_reg.phy_rx14_cntx_sel_g3 = 12;
	subctrl_base->sfr_phy_cfg_149_reg.phy_rx14_cntx_sel_g4 = 13;
	subctrl_base->sfr_phy_cfg_150_reg.phy_rx14_cntx_sel_g5 = 14;
	subctrl_base->sfr_phy_cfg_151_reg.phy_rx15_cntx_sel_g1 = 10;
	subctrl_base->sfr_phy_cfg_151_reg.phy_rx15_cntx_sel_g2 = 11;
	subctrl_base->sfr_phy_cfg_151_reg.phy_rx15_cntx_sel_g3 = 12;
	subctrl_base->sfr_phy_cfg_151_reg.phy_rx15_cntx_sel_g4 = 13;
	subctrl_base->sfr_phy_cfg_152_reg.phy_rx15_cntx_sel_g5 = 14;

	subctrl_base->sfr_phy_cfg_153_reg.phy_tx_cmn0_cntx_sel_g1 = 2;
	subctrl_base->sfr_phy_cfg_153_reg.phy_tx_cmn0_cntx_sel_g2 = 2;
	subctrl_base->sfr_phy_cfg_153_reg.phy_tx_cmn0_cntx_sel_g3 = 2;
	subctrl_base->sfr_phy_cfg_153_reg.phy_tx_cmn0_cntx_sel_g4 = 2;
	subctrl_base->sfr_phy_cfg_154_reg.phy_tx_cmn0_cntx_sel_g5 = 2;
	subctrl_base->sfr_phy_cfg_155_reg.phy_tx0_cntx_sel_g1 = 10;
	subctrl_base->sfr_phy_cfg_155_reg.phy_tx0_cntx_sel_g2 = 11;
	subctrl_base->sfr_phy_cfg_155_reg.phy_tx0_cntx_sel_g3 = 12;
	subctrl_base->sfr_phy_cfg_155_reg.phy_tx0_cntx_sel_g4 = 13;
	subctrl_base->sfr_phy_cfg_156_reg.phy_tx0_cntx_sel_g5 = 14;
	subctrl_base->sfr_phy_cfg_157_reg.phy_tx_cmn1_cntx_sel_g1 = 2;
	subctrl_base->sfr_phy_cfg_157_reg.phy_tx_cmn1_cntx_sel_g2 = 2;
	subctrl_base->sfr_phy_cfg_157_reg.phy_tx_cmn1_cntx_sel_g3 = 2;
	subctrl_base->sfr_phy_cfg_157_reg.phy_tx_cmn1_cntx_sel_g4 = 2;
	subctrl_base->sfr_phy_cfg_158_reg.phy_tx_cmn1_cntx_sel_g5 = 2;
	subctrl_base->sfr_phy_cfg_159_reg.phy_tx1_cntx_sel_g1 = 10;
	subctrl_base->sfr_phy_cfg_159_reg.phy_tx1_cntx_sel_g2 = 11;
	subctrl_base->sfr_phy_cfg_159_reg.phy_tx1_cntx_sel_g3 = 12;
	subctrl_base->sfr_phy_cfg_159_reg.phy_tx1_cntx_sel_g4 = 13;
	subctrl_base->sfr_phy_cfg_160_reg.phy_tx1_cntx_sel_g5 = 14;
	subctrl_base->sfr_phy_cfg_161_reg.phy_tx_cmn2_cntx_sel_g1 = 2;
	subctrl_base->sfr_phy_cfg_161_reg.phy_tx_cmn2_cntx_sel_g2 = 2;
	subctrl_base->sfr_phy_cfg_161_reg.phy_tx_cmn2_cntx_sel_g3 = 2;
	subctrl_base->sfr_phy_cfg_161_reg.phy_tx_cmn2_cntx_sel_g4 = 2;
	subctrl_base->sfr_phy_cfg_162_reg.phy_tx_cmn2_cntx_sel_g5 = 2;
	subctrl_base->sfr_phy_cfg_163_reg.phy_tx2_cntx_sel_g1 = 10;
	subctrl_base->sfr_phy_cfg_163_reg.phy_tx2_cntx_sel_g2 = 11;
	subctrl_base->sfr_phy_cfg_163_reg.phy_tx2_cntx_sel_g3 = 12;
	subctrl_base->sfr_phy_cfg_163_reg.phy_tx2_cntx_sel_g4 = 13;
	subctrl_base->sfr_phy_cfg_164_reg.phy_tx2_cntx_sel_g5 = 14;
	subctrl_base->sfr_phy_cfg_165_reg.phy_tx_cmn3_cntx_sel_g1 = 2;
	subctrl_base->sfr_phy_cfg_165_reg.phy_tx_cmn3_cntx_sel_g2 = 2;
	subctrl_base->sfr_phy_cfg_165_reg.phy_tx_cmn3_cntx_sel_g3 = 2;
	subctrl_base->sfr_phy_cfg_165_reg.phy_tx_cmn3_cntx_sel_g4 = 2;
	subctrl_base->sfr_phy_cfg_166_reg.phy_tx_cmn3_cntx_sel_g5 = 2;
	subctrl_base->sfr_phy_cfg_167_reg.phy_tx3_cntx_sel_g1 = 10;
	subctrl_base->sfr_phy_cfg_167_reg.phy_tx3_cntx_sel_g2 = 11;
	subctrl_base->sfr_phy_cfg_167_reg.phy_tx3_cntx_sel_g3 = 12;
	subctrl_base->sfr_phy_cfg_167_reg.phy_tx3_cntx_sel_g4 = 13;
	subctrl_base->sfr_phy_cfg_168_reg.phy_tx3_cntx_sel_g5 = 14;
	subctrl_base->sfr_phy_cfg_169_reg.phy_tx_cmn4_cntx_sel_g1 = 2;
	subctrl_base->sfr_phy_cfg_169_reg.phy_tx_cmn4_cntx_sel_g2 = 2;
	subctrl_base->sfr_phy_cfg_169_reg.phy_tx_cmn4_cntx_sel_g3 = 2;
	subctrl_base->sfr_phy_cfg_169_reg.phy_tx_cmn4_cntx_sel_g4 = 2;
	subctrl_base->sfr_phy_cfg_170_reg.phy_tx_cmn4_cntx_sel_g5 = 2;
	subctrl_base->sfr_phy_cfg_171_reg.phy_tx4_cntx_sel_g1 = 10;
	subctrl_base->sfr_phy_cfg_171_reg.phy_tx4_cntx_sel_g2 = 11;
	subctrl_base->sfr_phy_cfg_171_reg.phy_tx4_cntx_sel_g3 = 12;
	subctrl_base->sfr_phy_cfg_171_reg.phy_tx4_cntx_sel_g4 = 13;
	subctrl_base->sfr_phy_cfg_172_reg.phy_tx4_cntx_sel_g5 = 14;
	subctrl_base->sfr_phy_cfg_173_reg.phy_tx_cmn5_cntx_sel_g1 = 2;
	subctrl_base->sfr_phy_cfg_173_reg.phy_tx_cmn5_cntx_sel_g2 = 2;
	subctrl_base->sfr_phy_cfg_173_reg.phy_tx_cmn5_cntx_sel_g3 = 2;
	subctrl_base->sfr_phy_cfg_173_reg.phy_tx_cmn5_cntx_sel_g4 = 2;
	subctrl_base->sfr_phy_cfg_174_reg.phy_tx_cmn5_cntx_sel_g5 = 2;
	subctrl_base->sfr_phy_cfg_175_reg.phy_tx5_cntx_sel_g1 = 10;
	subctrl_base->sfr_phy_cfg_175_reg.phy_tx5_cntx_sel_g2 = 11;
	subctrl_base->sfr_phy_cfg_175_reg.phy_tx5_cntx_sel_g3 = 12;
	subctrl_base->sfr_phy_cfg_175_reg.phy_tx5_cntx_sel_g4 = 13;
	subctrl_base->sfr_phy_cfg_176_reg.phy_tx5_cntx_sel_g5 = 14;
	subctrl_base->sfr_phy_cfg_177_reg.phy_tx_cmn6_cntx_sel_g1 = 2;
	subctrl_base->sfr_phy_cfg_177_reg.phy_tx_cmn6_cntx_sel_g2 = 2;
	subctrl_base->sfr_phy_cfg_177_reg.phy_tx_cmn6_cntx_sel_g3 = 2;
	subctrl_base->sfr_phy_cfg_177_reg.phy_tx_cmn6_cntx_sel_g4 = 2;
	subctrl_base->sfr_phy_cfg_178_reg.phy_tx_cmn6_cntx_sel_g5 = 2;
	subctrl_base->sfr_phy_cfg_179_reg.phy_tx6_cntx_sel_g1 = 10;
	subctrl_base->sfr_phy_cfg_179_reg.phy_tx6_cntx_sel_g2 = 11;
	subctrl_base->sfr_phy_cfg_179_reg.phy_tx6_cntx_sel_g3 = 12;
	subctrl_base->sfr_phy_cfg_179_reg.phy_tx6_cntx_sel_g4 = 13;
	subctrl_base->sfr_phy_cfg_180_reg.phy_tx6_cntx_sel_g5 = 14;
	subctrl_base->sfr_phy_cfg_181_reg.phy_tx_cmn7_cntx_sel_g1 = 2;
	subctrl_base->sfr_phy_cfg_181_reg.phy_tx_cmn7_cntx_sel_g2 = 2;
	subctrl_base->sfr_phy_cfg_181_reg.phy_tx_cmn7_cntx_sel_g3 = 2;
	subctrl_base->sfr_phy_cfg_181_reg.phy_tx_cmn7_cntx_sel_g4 = 2;
	subctrl_base->sfr_phy_cfg_182_reg.phy_tx_cmn7_cntx_sel_g5 = 2;
	subctrl_base->sfr_phy_cfg_183_reg.phy_tx7_cntx_sel_g1 = 10;
	subctrl_base->sfr_phy_cfg_183_reg.phy_tx7_cntx_sel_g2 = 11;
	subctrl_base->sfr_phy_cfg_183_reg.phy_tx7_cntx_sel_g3 = 12;
	subctrl_base->sfr_phy_cfg_183_reg.phy_tx7_cntx_sel_g4 = 13;
	subctrl_base->sfr_phy_cfg_184_reg.phy_tx7_cntx_sel_g5 = 14;
	subctrl_base->sfr_phy_cfg_185_reg.phy_tx_cmn8_cntx_sel_g1 = 2;
	subctrl_base->sfr_phy_cfg_185_reg.phy_tx_cmn8_cntx_sel_g2 = 2;
	subctrl_base->sfr_phy_cfg_185_reg.phy_tx_cmn8_cntx_sel_g3 = 2;
	subctrl_base->sfr_phy_cfg_185_reg.phy_tx_cmn8_cntx_sel_g4 = 2;
	subctrl_base->sfr_phy_cfg_186_reg.phy_tx_cmn8_cntx_sel_g5 = 2;
	subctrl_base->sfr_phy_cfg_187_reg.phy_tx8_cntx_sel_g1 = 10;
	subctrl_base->sfr_phy_cfg_187_reg.phy_tx8_cntx_sel_g2 = 11;
	subctrl_base->sfr_phy_cfg_187_reg.phy_tx8_cntx_sel_g3 = 12;
	subctrl_base->sfr_phy_cfg_187_reg.phy_tx8_cntx_sel_g4 = 13;
	subctrl_base->sfr_phy_cfg_188_reg.phy_tx8_cntx_sel_g5 = 14;
	subctrl_base->sfr_phy_cfg_189_reg.phy_tx_cmn9_cntx_sel_g1 = 2;
	subctrl_base->sfr_phy_cfg_189_reg.phy_tx_cmn9_cntx_sel_g2 = 2;
	subctrl_base->sfr_phy_cfg_189_reg.phy_tx_cmn9_cntx_sel_g3 = 2;
	subctrl_base->sfr_phy_cfg_189_reg.phy_tx_cmn9_cntx_sel_g4 = 2;
	subctrl_base->sfr_phy_cfg_190_reg.phy_tx_cmn9_cntx_sel_g5 = 2;
	subctrl_base->sfr_phy_cfg_191_reg.phy_tx9_cntx_sel_g1 = 10;
	subctrl_base->sfr_phy_cfg_191_reg.phy_tx9_cntx_sel_g2 = 11;
	subctrl_base->sfr_phy_cfg_191_reg.phy_tx9_cntx_sel_g3 = 12;
	subctrl_base->sfr_phy_cfg_191_reg.phy_tx9_cntx_sel_g4 = 13;
	subctrl_base->sfr_phy_cfg_192_reg.phy_tx9_cntx_sel_g5 = 14;
	subctrl_base->sfr_phy_cfg_193_reg.phy_tx_cmn10_cntx_sel_g1 = 2;
	subctrl_base->sfr_phy_cfg_193_reg.phy_tx_cmn10_cntx_sel_g2 = 2;
	subctrl_base->sfr_phy_cfg_193_reg.phy_tx_cmn10_cntx_sel_g3 = 2;
	subctrl_base->sfr_phy_cfg_193_reg.phy_tx_cmn10_cntx_sel_g4 = 2;
	subctrl_base->sfr_phy_cfg_194_reg.phy_tx_cmn10_cntx_sel_g5 = 2;
	subctrl_base->sfr_phy_cfg_195_reg.phy_tx10_cntx_sel_g1 = 10;
	subctrl_base->sfr_phy_cfg_195_reg.phy_tx10_cntx_sel_g2 = 11;
	subctrl_base->sfr_phy_cfg_195_reg.phy_tx10_cntx_sel_g3 = 12;
	subctrl_base->sfr_phy_cfg_195_reg.phy_tx10_cntx_sel_g4 = 13;
	subctrl_base->sfr_phy_cfg_196_reg.phy_tx10_cntx_sel_g5 = 14;
	subctrl_base->sfr_phy_cfg_197_reg.phy_tx_cmn11_cntx_sel_g1 = 2;
	subctrl_base->sfr_phy_cfg_197_reg.phy_tx_cmn11_cntx_sel_g2 = 2;
	subctrl_base->sfr_phy_cfg_197_reg.phy_tx_cmn11_cntx_sel_g3 = 2;
	subctrl_base->sfr_phy_cfg_197_reg.phy_tx_cmn11_cntx_sel_g4 = 2;
	subctrl_base->sfr_phy_cfg_198_reg.phy_tx_cmn11_cntx_sel_g5 = 2;
	subctrl_base->sfr_phy_cfg_199_reg.phy_tx11_cntx_sel_g1 = 10;
	subctrl_base->sfr_phy_cfg_199_reg.phy_tx11_cntx_sel_g2 = 11;
	subctrl_base->sfr_phy_cfg_199_reg.phy_tx11_cntx_sel_g3 = 12;
	subctrl_base->sfr_phy_cfg_199_reg.phy_tx11_cntx_sel_g4 = 13;
	subctrl_base->sfr_phy_cfg_200_reg.phy_tx11_cntx_sel_g5 = 14;
	subctrl_base->sfr_phy_cfg_201_reg.phy_tx_cmn12_cntx_sel_g1 = 2;
	subctrl_base->sfr_phy_cfg_201_reg.phy_tx_cmn12_cntx_sel_g2 = 2;
	subctrl_base->sfr_phy_cfg_201_reg.phy_tx_cmn12_cntx_sel_g3 = 2;
	subctrl_base->sfr_phy_cfg_201_reg.phy_tx_cmn12_cntx_sel_g4 = 2;
	subctrl_base->sfr_phy_cfg_202_reg.phy_tx_cmn12_cntx_sel_g5 = 2;
	subctrl_base->sfr_phy_cfg_203_reg.phy_tx12_cntx_sel_g1 = 10;
	subctrl_base->sfr_phy_cfg_203_reg.phy_tx12_cntx_sel_g2 = 11;
	subctrl_base->sfr_phy_cfg_203_reg.phy_tx12_cntx_sel_g3 = 12;
	subctrl_base->sfr_phy_cfg_203_reg.phy_tx12_cntx_sel_g4 = 13;
	subctrl_base->sfr_phy_cfg_204_reg.phy_tx12_cntx_sel_g5 = 14;
	subctrl_base->sfr_phy_cfg_205_reg.phy_tx_cmn13_cntx_sel_g1 = 2;
	subctrl_base->sfr_phy_cfg_205_reg.phy_tx_cmn13_cntx_sel_g2 = 2;
	subctrl_base->sfr_phy_cfg_205_reg.phy_tx_cmn13_cntx_sel_g3 = 2;
	subctrl_base->sfr_phy_cfg_205_reg.phy_tx_cmn13_cntx_sel_g4 = 2;
	subctrl_base->sfr_phy_cfg_206_reg.phy_tx_cmn13_cntx_sel_g5 = 2;
	subctrl_base->sfr_phy_cfg_207_reg.phy_tx13_cntx_sel_g1 = 10;
	subctrl_base->sfr_phy_cfg_207_reg.phy_tx13_cntx_sel_g2 = 11;
	subctrl_base->sfr_phy_cfg_207_reg.phy_tx13_cntx_sel_g3 = 12;
	subctrl_base->sfr_phy_cfg_207_reg.phy_tx13_cntx_sel_g4 = 13;
	subctrl_base->sfr_phy_cfg_208_reg.phy_tx13_cntx_sel_g5 = 14;
	subctrl_base->sfr_phy_cfg_209_reg.phy_tx_cmn14_cntx_sel_g1 = 2;
	subctrl_base->sfr_phy_cfg_209_reg.phy_tx_cmn14_cntx_sel_g2 = 2;
	subctrl_base->sfr_phy_cfg_209_reg.phy_tx_cmn14_cntx_sel_g3 = 2;
	subctrl_base->sfr_phy_cfg_209_reg.phy_tx_cmn14_cntx_sel_g4 = 2;
	subctrl_base->sfr_phy_cfg_210_reg.phy_tx_cmn14_cntx_sel_g5 = 2;
	subctrl_base->sfr_phy_cfg_211_reg.phy_tx14_cntx_sel_g1 = 10;
	subctrl_base->sfr_phy_cfg_211_reg.phy_tx14_cntx_sel_g2 = 11;
	subctrl_base->sfr_phy_cfg_211_reg.phy_tx14_cntx_sel_g3 = 12;
	subctrl_base->sfr_phy_cfg_211_reg.phy_tx14_cntx_sel_g4 = 13;
	subctrl_base->sfr_phy_cfg_212_reg.phy_tx14_cntx_sel_g5 = 14;
	subctrl_base->sfr_phy_cfg_213_reg.phy_tx_cmn15_cntx_sel_g1 = 2;
	subctrl_base->sfr_phy_cfg_213_reg.phy_tx_cmn15_cntx_sel_g2 = 2;
	subctrl_base->sfr_phy_cfg_213_reg.phy_tx_cmn15_cntx_sel_g3 = 2;
	subctrl_base->sfr_phy_cfg_213_reg.phy_tx_cmn15_cntx_sel_g4 = 2;
	subctrl_base->sfr_phy_cfg_214_reg.phy_tx_cmn15_cntx_sel_g5 = 2;
	subctrl_base->sfr_phy_cfg_215_reg.phy_tx15_cntx_sel_g1 = 10;
	subctrl_base->sfr_phy_cfg_215_reg.phy_tx15_cntx_sel_g2 = 11;
	subctrl_base->sfr_phy_cfg_215_reg.phy_tx15_cntx_sel_g3 = 12;
	subctrl_base->sfr_phy_cfg_215_reg.phy_tx15_cntx_sel_g4 = 13;
	subctrl_base->sfr_phy_cfg_216_reg.phy_tx15_cntx_sel_g5 = 14;
}

int32_t pcie_phy_init(const struct dw_pcie_config *cfg, struct dw_pcie_drv *data)
{
	volatile struct pcie_subctrl_register *subctrl_base = cfg->subctrl_base;

	/* This is for bring-up! Will clean-up after bring-up done */
	subctrl_base->sfr_phy_cfg_0_reg.phy0_mplla_ssc_en = 0;
	subctrl_base->sfr_phy_cfg_0_reg.phy0_mpllb_ssc_en = 0;
	subctrl_base->sfr_phy_cfg_102_reg.phy1_mplla_ssc_en = 0;
	subctrl_base->sfr_phy_cfg_102_reg.phy1_mpllb_ssc_en = 0;
	subctrl_base->sfr_phy_cfg_103_reg.phy2_mplla_ssc_en = 0;
	subctrl_base->sfr_phy_cfg_103_reg.phy2_mpllb_ssc_en = 0;
	subctrl_base->sfr_phy_cfg_104_reg.phy3_mplla_ssc_en = 0;
	subctrl_base->sfr_phy_cfg_104_reg.phy3_mpllb_ssc_en = 0;

	subctrl_base->sfr_app_sris_mode.app_sris_mode = 0;

	subctrl_base->sfr_phy_cfg_693_reg.phy0_mplla_short_lock_en = 1;
	subctrl_base->sfr_phy_cfg_693_reg.phy0_mpllb_short_lock_en = 1;
	subctrl_base->sfr_phy_cfg_695_reg.phy1_mplla_short_lock_en = 1;
	subctrl_base->sfr_phy_cfg_695_reg.phy1_mpllb_short_lock_en = 1;
	subctrl_base->sfr_phy_cfg_697_reg.phy2_mplla_short_lock_en = 1;
	subctrl_base->sfr_phy_cfg_697_reg.phy2_mpllb_short_lock_en = 1;
	subctrl_base->sfr_phy_cfg_699_reg.phy3_mplla_short_lock_en = 1;
	subctrl_base->sfr_phy_cfg_699_reg.phy3_mpllb_short_lock_en = 1;

	subctrl_base->sfr_phy_cfg_693_reg.phy0_refa_lane_clk_en = 0;
	subctrl_base->sfr_phy_cfg_693_reg.phy0_refb_lane_clk_en = 0;
	subctrl_base->sfr_phy_cfg_695_reg.phy1_refa_lane_clk_en = 0;
	subctrl_base->sfr_phy_cfg_695_reg.phy1_refb_lane_clk_en = 0;
	subctrl_base->sfr_phy_cfg_697_reg.phy2_refa_lane_clk_en = 0;
	subctrl_base->sfr_phy_cfg_697_reg.phy2_refb_lane_clk_en = 0;
	subctrl_base->sfr_phy_cfg_699_reg.phy3_refa_lane_clk_en = 0;
	subctrl_base->sfr_phy_cfg_699_reg.phy3_refb_lane_clk_en = 0;

	subctrl_base->sfr_phy_cfg_0_reg.phy_lane0_power_present = 1;
	subctrl_base->sfr_phy_cfg_0_reg.phy0_pma_pwr_stable = 1;
	subctrl_base->sfr_phy_cfg_0_reg.phy0_pcs_pwr_stable = 1;
	subctrl_base->sfr_phy_cfg_0_reg.phy0_ana_pwr_en = 1;
	subctrl_base->sfr_phy_cfg_0_reg.phy_rx0_term_acdc = 1;

	subctrl_base->sfr_phy_cfg_722_reg.pipe_lane0_lanepll_bypass_mode = 0x1F;
	subctrl_base->sfr_phy_cfg_723_reg.pipe_lane1_lanepll_bypass_mode = 0x1F;
	subctrl_base->sfr_phy_cfg_724_reg.pipe_lane2_lanepll_bypass_mode = 0x1F;
	subctrl_base->sfr_phy_cfg_725_reg.pipe_lane3_lanepll_bypass_mode = 0x1F;
	subctrl_base->sfr_phy_cfg_726_reg.pipe_lane4_lanepll_bypass_mode = 0x1F;
	subctrl_base->sfr_phy_cfg_727_reg.pipe_lane5_lanepll_bypass_mode = 0x1F;
	subctrl_base->sfr_phy_cfg_728_reg.pipe_lane6_lanepll_bypass_mode = 0x1F;
	subctrl_base->sfr_phy_cfg_729_reg.pipe_lane7_lanepll_bypass_mode = 0x1F;
	subctrl_base->sfr_phy_cfg_730_reg.pipe_lane8_lanepll_bypass_mode = 0x1F;
	subctrl_base->sfr_phy_cfg_731_reg.pipe_lane9_lanepll_bypass_mode = 0x1F;
	subctrl_base->sfr_phy_cfg_732_reg.pipe_lane10_lanepll_bypass_mode = 0x1F;
	subctrl_base->sfr_phy_cfg_733_reg.pipe_lane11_lanepll_bypass_mode = 0x1F;
	subctrl_base->sfr_phy_cfg_734_reg.pipe_lane12_lanepll_bypass_mode = 0x1F;
	subctrl_base->sfr_phy_cfg_735_reg.pipe_lane13_lanepll_bypass_mode = 0x1F;
	subctrl_base->sfr_phy_cfg_736_reg.pipe_lane14_lanepll_bypass_mode = 0x1F;
	subctrl_base->sfr_phy_cfg_737_reg.pipe_lane15_lanepll_bypass_mode = 0x1F;

	pcie_phy_set_cntx_restore_mode(cfg);

	/* Hold the PHY in Reset state */
	subctrl_base->sfr_app_ctrl_signals.app_hold_phy_rst = 1;

#if PCIE_PHY_SRAM_LOAD
	/* Config sram bootload bypass mode */
	subctrl_base->sfr_phy_cfg_0_reg.phy0_sram_bootload_bypass = 1;
	subctrl_base->sfr_phy_cfg_102_reg.phy1_sram_bootload_bypass = 1;
	subctrl_base->sfr_phy_cfg_103_reg.phy2_sram_bootload_bypass = 1;
	subctrl_base->sfr_phy_cfg_104_reg.phy3_sram_bootload_bypass = 1;
#endif /* PCIE_PHY_SRAM_LOAD */

	/* Release the PHY */
	/* De-assert phy_reset (phy_reset_ovrd & power_up_rst_n_ovrd) */
	subctrl_base->sfr_phy_reset_ovrd.phy_reset_ovrd = 1;
	/* De-assert phy_rst_n (pipe_laneX_reset_n) */
	subctrl_base->sfr_app_ctrl_signals.app_hold_phy_rst = 0;

#ifndef ZEBU_POC
#if !PCIE_PHY_SRAM_LOAD
	while (!(subctrl_base->sfr_phy_cfg_28_reg.phy0_sram_init_done == 1 &&
			 subctrl_base->sfr_phy_cfg_99_reg.phy1_sram_init_done == 1 &&
			 subctrl_base->sfr_phy_cfg_100_reg.phy2_sram_init_done == 1 &&
			 subctrl_base->sfr_phy_cfg_101_reg.phy3_sram_init_done == 1))
		;

	subctrl_base->sfr_phy_cfg_0_reg.phy0_sram_ext_ld_done = 1;
	subctrl_base->sfr_phy_cfg_102_reg.phy1_sram_ext_ld_done = 1;
	subctrl_base->sfr_phy_cfg_103_reg.phy2_sram_ext_ld_done = 1;
	subctrl_base->sfr_phy_cfg_104_reg.phy3_sram_ext_ld_done = 1;
#endif /* !PCIE_PHY_SRAM_LOAD */

	while (!(subctrl_base->sfr_phy_cfg_0_reg.phy0_sram_ext_ld_done == 1 &&
			 subctrl_base->sfr_phy_cfg_102_reg.phy1_sram_ext_ld_done == 1 &&
			 subctrl_base->sfr_phy_cfg_103_reg.phy2_sram_ext_ld_done == 1 &&
			 subctrl_base->sfr_phy_cfg_104_reg.phy3_sram_ext_ld_done == 1))
		;
#endif /* ZEBU_POC */

	return RL_OK;
}
