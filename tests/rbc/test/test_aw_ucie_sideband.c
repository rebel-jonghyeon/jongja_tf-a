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
#include "aw_ucie_reg.h"
#ifdef USE_DILIGENT_PTR
	#include "diligent_ptr.h"
#endif /* USE_DILIGENT_PTR */
#include "test_aw_ucie_util.h"
#include "rl_utils.h"
#include "rl_errors.h"
#include "unity_fixture.h"

static struct aw_ucie *mmio_ptr;
static struct aw_ucie *wr_buf_ptr;
static const int32_t ucie_ss_id = UCIE_SS_H00_ID;
static int32_t (*link_training_bk)(void);

TEST_GROUP(ucie_sideband);

TEST_SETUP(ucie_sideband)
{
	CLEAR_SNAPSHOT_ARR(reg[ucie_ss_id]);
	CLEAR_SNAPSHOT_ARR(target_ss);

	link_training_bk = aw_ucie_link_training;
#ifdef USE_DILIGENT_PTR
	aw_ucie_link_training = dummy_aw_ucie_link_training;
#endif /* USE_DILIGENT_PTR */
	init_mmio_map(ucie_ss_id);

	mmio_ptr = get_aw_ucie_mmio_var();
	wr_buf_ptr = get_aw_ucie_mmio_write_buf();
	real_map = get_aw_ucie_real_map();

	PAUSE(target_ss);
	aw_ucie_init(ucie_ss_id, real_map);
	aw_ucie_set_target_ss(ucie_ss_id);
	aw_ucie_link_training();
	RESUME(target_ss);
}

TEST_TEAR_DOWN(ucie_sideband)
{
	VERIFY(reg[ucie_ss_id]);
	VERIFY(target_ss);

	aw_ucie_link_training = link_training_bk;
}

static union aw_ucie_dvsec1_reg_reg_global_dvsec1_sb_mailbox_index_low default_idx_low = {
	.sb_mailbox_index_low_opcode = UCIE_SB_32B_CONFIG_RD,
	.sb_mailbox_index_low_be = 0xF,
	.sb_mailbox_index_low_addr = 0,
};

static void _set_mock_for_sb_mbox(uint32_t opcode, uint32_t rl, uint32_t offset,
								  uint32_t result, uint32_t *buf)
{
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);

	union aw_ucie_dvsec1_reg_reg_global_dvsec1_sb_mailbox_index_low idx_low = default_idx_low;

	mmio_ptr->dvsec1_reg_reg_global_dvsec1_sb_mailbox_data_low.val = idx_low.val;
	*wr_buf_ptr = *mmio_ptr;
	idx_low.sb_mailbox_index_low_opcode = RL_BITFIELD_GET(RL_GENMASK(4, 0), opcode);
	idx_low.sb_mailbox_index_low_be = 0xF;
	if (opcode == UCIE_SB_32B_CONFIG_RD || opcode == UCIE_SB_32B_CONFIG_WR ||
		opcode == UCIE_SB_64B_CONFIG_RD || opcode == UCIE_SB_64B_CONFIG_WR) {
		idx_low.sb_mailbox_index_low_addr = RL_BITFIELD_GET(RL_GENMASK(11, 0), offset);
	} else {
		idx_low.sb_mailbox_index_low_addr = RL_BITFIELD_GET(RL_GENMASK(18, 0), offset);
	}
	wr_buf_ptr->dvsec1_reg_reg_global_dvsec1_sb_mailbox_index_low.val = idx_low.val;
	PUSH_EXPECT_WRITE(target_ss, mmio_ptr, wr_buf_ptr);
	*mmio_ptr = *wr_buf_ptr;

	union aw_ucie_dvsec1_reg_reg_global_dvsec1_sb_mailbox_index_high idx_high = {};

	mmio_ptr->dvsec1_reg_reg_global_dvsec1_sb_mailbox_index_high.val = idx_high.val;

	*wr_buf_ptr = *mmio_ptr;
	idx_high.sb_mailbox_index_high_addr = RL_BITFIELD_GET(RL_GENMASK64(3, 0), rl) << 1;
	if (opcode == UCIE_SB_32B_MEM_RD || opcode == UCIE_SB_32B_MEM_WR ||
		opcode == UCIE_SB_64B_MEM_RD || opcode == UCIE_SB_64B_MEM_WR) {
		idx_high.sb_mailbox_index_high_addr |= RL_BITFIELD_GET(RL_BIT(19), offset);
	}
	wr_buf_ptr->dvsec1_reg_reg_global_dvsec1_sb_mailbox_index_high.val = idx_high.val;
	PUSH_EXPECT_WRITE(target_ss, mmio_ptr, wr_buf_ptr);
	*mmio_ptr = *wr_buf_ptr;

	if (opcode == UCIE_SB_32B_MEM_WR || opcode == UCIE_SB_32B_CONFIG_WR) {
		mmio_ptr->dvsec1_reg_reg_global_dvsec1_sb_mailbox_data_low.val = buf[0];
		PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);
	} else if (opcode == UCIE_SB_64B_MEM_WR || opcode == UCIE_SB_64B_CONFIG_WR) {
		mmio_ptr->dvsec1_reg_reg_global_dvsec1_sb_mailbox_data_low.val = buf[0];
		PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);
		mmio_ptr->dvsec1_reg_reg_global_dvsec1_sb_mailbox_data_high.val = buf[1];
		PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);
	}

	mmio_ptr->dvsec1_reg_reg_global_dvsec1_sb_mailbox_ctrl_stats.val = 0;
	*wr_buf_ptr = *mmio_ptr;
wr_buf_ptr->dvsec1_reg_reg_global_dvsec1_sb_mailbox_ctrl_stats.sb_mailbox_ctrl_wr_or_rd_trigger = 1;
	PUSH_EXPECT_WRITE(target_ss, mmio_ptr, wr_buf_ptr);
	*mmio_ptr = *wr_buf_ptr;

	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);

	mmio_ptr->dvsec1_reg_reg_global_dvsec1_sb_mailbox_ctrl_stats.sb_mailbox_ctrl_wr_or_rd_trigger =
		0;
	mmio_ptr->dvsec1_reg_reg_global_dvsec1_sb_mailbox_ctrl_stats.sb_mailbox_stats_wr_or_rd_status =
		result;
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);

	if (result == UCIE_SB_MBOX_STAT_SUCCESS) {
		if (opcode == UCIE_SB_32B_MEM_RD || opcode == UCIE_SB_32B_CONFIG_RD) {
			mmio_ptr->dvsec1_reg_reg_global_dvsec1_sb_mailbox_data_low.val = buf[0];
			PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);
		} else if (opcode == UCIE_SB_64B_MEM_RD || opcode == UCIE_SB_64B_CONFIG_RD) {
			mmio_ptr->dvsec1_reg_reg_global_dvsec1_sb_mailbox_data_low.val = buf[0];
			PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);
			mmio_ptr->dvsec1_reg_reg_global_dvsec1_sb_mailbox_data_high.val = buf[1];
			PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);
		}
	} else {
	/* Table 6-7. Field Descriptions for a Completion
	 * UR : On UCIe, this is a completion with 64b Data when a
	 * request is aborted by the completer, and the Data carries the original request header that
	 * resulted in UR.
	 * CA : On UCIe, this is a completion with 64b Data, and the Data
	 * carries original request header that resulted in CA
	 */
		mmio_ptr->dvsec1_reg_reg_global_dvsec1_sb_mailbox_data_low.val = buf[0];
		mmio_ptr->dvsec1_reg_reg_global_dvsec1_sb_mailbox_data_high.val = buf[1];
		PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);
		PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);
	}
}

TEST(ucie_sideband, normal_send_sb_mem_rd32)
{
	uint32_t offset = 0;
	uint32_t buf[1] = {};

	buf[0] = get_default_phy_impsp_blk_hdr1();
	_set_mock_for_sb_mbox(UCIE_SB_32B_MEM_RD, UCIE_SB_MEM_REG_LOCATOR_3, offset,
						  UCIE_SB_MBOX_STAT_SUCCESS, buf);
	buf[0] = 0;
	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_sb_mem_rd32(UCIE_SB_MEM_REG_LOCATOR_3, offset, buf));
	TEST_ASSERT_EQUAL(get_default_phy_impsp_blk_hdr1(), buf[0]);
}

TEST(ucie_sideband, fail_send_sb_msg_due_to_be_in_progress_already)
{
	uint32_t offset = 0;
	uint32_t buf[1] = {};

	mmio_ptr->dvsec1_reg_reg_global_dvsec1_sb_mailbox_ctrl_stats.sb_mailbox_ctrl_wr_or_rd_trigger = 1;
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);
	TEST_ASSERT_EQUAL(RL_BUSY, aw_ucie_sb_mem_rd32(UCIE_SB_MEM_REG_LOCATOR_3, offset, buf));
}

TEST(ucie_sideband, fail_send_sb_mem_rd32_w_ur)
{
	uint32_t offset = 0;
	uint32_t buf[2] = {};
	const uint32_t invalid_opcode = 0x1f;
	struct ucie_sb_reg_req sb_req = {};

	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);

	sb_req.phase0.opcode = invalid_opcode & 0x1f;
	sb_req.phase0.ep = DISABLE;
	sb_req.phase0.be = 0xF;
	sb_req.phase0.srcid = 0x1;
	sb_req.phase1.addr = (UCIE_SB_MEM_REG_LOCATOR_3 << 20) | (offset & 0xfffff);
	sb_req.phase1.dstid = 0;
	sb_req.phase1.cr = 1;

	buf[0] = sb_req.phase0.val;
	buf[1] = sb_req.phase1.val;

	/* Set Mocking for setting header */
	mmio_ptr->adapter_d2d_reg_reg_adapter_d2d_hdr_log1_1.val = sb_req.phase0.val;
	mmio_ptr->adapter_d2d_reg_reg_adapter_d2d_hdr_log1_2.val = sb_req.phase1.val;

	union aw_ucie_dvsec1_reg_reg_global_dvsec1_sb_mailbox_index_low idx_low = default_idx_low;

	mmio_ptr->dvsec1_reg_reg_global_dvsec1_sb_mailbox_data_low.val = idx_low.val;
	*wr_buf_ptr = *mmio_ptr;
	idx_low.sb_mailbox_index_low_opcode = sb_req.phase0.opcode;
	idx_low.sb_mailbox_index_low_be = sb_req.phase0.be;
	idx_low.sb_mailbox_index_low_addr = sb_req.phase1.addr & 0x7ffff;

	wr_buf_ptr->dvsec1_reg_reg_global_dvsec1_sb_mailbox_index_low.val = idx_low.val;
	PUSH_EXPECT_WRITE(target_ss, mmio_ptr, wr_buf_ptr);
	*mmio_ptr = *wr_buf_ptr;

	union aw_ucie_dvsec1_reg_reg_global_dvsec1_sb_mailbox_index_high idx_high = {};

	mmio_ptr->dvsec1_reg_reg_global_dvsec1_sb_mailbox_index_high.val = idx_high.val;

	*wr_buf_ptr = *mmio_ptr;
	idx_high.sb_mailbox_index_high_addr = sb_req.phase1.addr >> 19;
	wr_buf_ptr->dvsec1_reg_reg_global_dvsec1_sb_mailbox_index_high.val = idx_high.val;
	PUSH_EXPECT_WRITE(target_ss, mmio_ptr, wr_buf_ptr);
	*mmio_ptr = *wr_buf_ptr;

	/* Set Mocking for triggering */
mmio_ptr->dvsec1_reg_reg_global_dvsec1_sb_mailbox_ctrl_stats.val = 0;
	*wr_buf_ptr = *mmio_ptr;
wr_buf_ptr->dvsec1_reg_reg_global_dvsec1_sb_mailbox_ctrl_stats.sb_mailbox_ctrl_wr_or_rd_trigger = 1;
	PUSH_EXPECT_WRITE(target_ss, mmio_ptr, wr_buf_ptr);
	*mmio_ptr = *wr_buf_ptr;

	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);

	mmio_ptr->dvsec1_reg_reg_global_dvsec1_sb_mailbox_ctrl_stats.sb_mailbox_ctrl_wr_or_rd_trigger =
		0;
	mmio_ptr->dvsec1_reg_reg_global_dvsec1_sb_mailbox_ctrl_stats.sb_mailbox_stats_wr_or_rd_status =
		UCIE_SB_MBOX_STAT_UR;
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);

	/* Set Mocking for getting response data*/
	mmio_ptr->dvsec1_reg_reg_global_dvsec1_sb_mailbox_data_low.val = buf[0];
	mmio_ptr->dvsec1_reg_reg_global_dvsec1_sb_mailbox_data_high.val = buf[1];
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);

	/* Run CUT */
	TEST_ASSERT_EQUAL(UCIE_SB_MBOX_STAT_UR,
					  aw_ucie_sb_mbox_manual(sb_req.phase0.opcode, sb_req.phase0.be,
											 sb_req.phase1.addr & 0x3ffff, sb_req.phase1.addr >> 19,
											 NULL, buf));

	/* Check Result */
	sb_req.phase0.val = buf[0];
	sb_req.phase1.val = buf[1];
	TEST_ASSERT_EQUAL(invalid_opcode, sb_req.phase0.opcode);
	TEST_ASSERT_EQUAL(DISABLE, sb_req.phase0.ep);
	TEST_ASSERT_EQUAL(0xF, sb_req.phase0.be);
	TEST_ASSERT_EQUAL(1/* D2D Adapter */, sb_req.phase0.srcid);
	TEST_ASSERT_EQUAL((UCIE_SB_MEM_REG_LOCATOR_3 << 20) | (offset & 0xfffff), sb_req.phase1.addr);
	TEST_ASSERT_EQUAL(0/* reserved */, sb_req.phase1.dstid);
	TEST_ASSERT_EQUAL(1/* reserved */, sb_req.phase1.cr);

	uint8_t sb_mbox_stat = 0;

	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);
	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_get_sb_mbox_status(&sb_mbox_stat));
	TEST_ASSERT_EQUAL(UCIE_SB_MBOX_STAT_UR, sb_mbox_stat);

	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);
	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_get_d2d_hdr_log1_1(&buf[0]));
	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_get_d2d_hdr_log1_2(&buf[1]));
	TEST_ASSERT_EQUAL(sb_req.phase0.val, buf[0]);
	TEST_ASSERT_EQUAL(sb_req.phase1.val, buf[1]);
}

IGNORE_TEST(ucie_sideband, fail_send_sb_mem_rd32_w_ca)
{
	TEST_IGNORE_MESSAGE("need to find how to occur 'CA'");
}

TEST(ucie_sideband, fail_send_w_invalid_arg)
{
	uint32_t buf[2] = {};

	TEST_ASSERT_EQUAL(RL_BADARG, aw_ucie_sb_mem_rd32(5, 0, buf));
	TEST_ASSERT_EQUAL(RL_BADARG, aw_ucie_sb_mem_rd32(0, 0, NULL));
	TEST_ASSERT_EQUAL(RL_BADARG, aw_ucie_sb_mem_rd32(0, RL_BIT(20), buf));

	TEST_ASSERT_EQUAL(RL_BADARG, aw_ucie_sb_mem_rd64(5, 0, buf));
	TEST_ASSERT_EQUAL(RL_BADARG, aw_ucie_sb_mem_rd64(0, 0, NULL));
	TEST_ASSERT_EQUAL(RL_BADARG, aw_ucie_sb_mem_rd64(0, RL_BIT(20), buf));

	TEST_ASSERT_EQUAL(RL_BADARG, aw_ucie_sb_config_rd32(5, 0, buf));
	TEST_ASSERT_EQUAL(RL_BADARG, aw_ucie_sb_config_rd32(0, 0, NULL));
	TEST_ASSERT_EQUAL(RL_BADARG, aw_ucie_sb_config_rd32(0, RL_BIT(12), buf));

	TEST_ASSERT_EQUAL(RL_BADARG, aw_ucie_sb_config_rd64(5, 0, buf));
	TEST_ASSERT_EQUAL(RL_BADARG, aw_ucie_sb_config_rd64(0, 0, NULL));
	TEST_ASSERT_EQUAL(RL_BADARG, aw_ucie_sb_config_rd64(0, RL_BIT(12), NULL));

	TEST_ASSERT_EQUAL(RL_BADARG, aw_ucie_sb_mem_wr32(5, 0, buf));
	TEST_ASSERT_EQUAL(RL_BADARG, aw_ucie_sb_mem_wr32(0, 0, NULL));
	TEST_ASSERT_EQUAL(RL_BADARG, aw_ucie_sb_mem_wr32(0, RL_BIT(20), buf));

	TEST_ASSERT_EQUAL(RL_BADARG, aw_ucie_sb_mem_wr64(5, 0, buf));
	TEST_ASSERT_EQUAL(RL_BADARG, aw_ucie_sb_mem_wr64(0, 0, NULL));
	TEST_ASSERT_EQUAL(RL_BADARG, aw_ucie_sb_mem_wr64(0, RL_BIT(20), buf));

	TEST_ASSERT_EQUAL(RL_BADARG, aw_ucie_sb_config_wr32(5, 0, buf));
	TEST_ASSERT_EQUAL(RL_BADARG, aw_ucie_sb_config_wr32(0, 0, NULL));
	TEST_ASSERT_EQUAL(RL_BADARG, aw_ucie_sb_config_wr32(0, RL_BIT(12), buf));

	TEST_ASSERT_EQUAL(RL_BADARG, aw_ucie_sb_config_wr64(5, 0, buf));
	TEST_ASSERT_EQUAL(RL_BADARG, aw_ucie_sb_config_wr64(0, 0, NULL));
	TEST_ASSERT_EQUAL(RL_BADARG, aw_ucie_sb_config_wr64(0, RL_BIT(12), NULL));
}

TEST(ucie_sideband, normal_send_sb_mem_wr32)
{
	uint32_t offset = (size_t)&mmio_ptr->adapter_test_comp_reg_reg_adapter_tstcmp_flit_tx_inj_ctrl2
		- (size_t)&mmio_ptr->test_comp_reg_reg_glbl_tstcmp_ucie_blk_hdr1;
	uint32_t buf[1] = {};
	uint32_t backup[1] = {};

	_set_mock_for_sb_mbox(UCIE_SB_32B_MEM_RD, UCIE_SB_MEM_REG_LOCATOR_1, offset,
						  UCIE_SB_MBOX_STAT_SUCCESS, buf);
	aw_ucie_sb_mem_rd32(UCIE_SB_MEM_REG_LOCATOR_1, offset, buf);
	backup[0] = buf[0];/* back up current data for comparing */

	buf[0] = ~backup[0];
	_set_mock_for_sb_mbox(UCIE_SB_32B_MEM_WR, UCIE_SB_MEM_REG_LOCATOR_1, offset,
						  UCIE_SB_MBOX_STAT_SUCCESS, buf);
	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_sb_mem_wr32(UCIE_SB_MEM_REG_LOCATOR_1, offset, buf));

	_set_mock_for_sb_mbox(UCIE_SB_32B_MEM_RD, UCIE_SB_MEM_REG_LOCATOR_1, offset,
						  UCIE_SB_MBOX_STAT_SUCCESS, buf);
	buf[0] = backup[0];
	aw_ucie_sb_mem_rd32(UCIE_SB_MEM_REG_LOCATOR_1, offset, buf);
	TEST_ASSERT_EQUAL(~backup[0], buf[0]);
}

TEST(ucie_sideband, normal_send_sb_mem_rd64)
{
	uint32_t offset = 0;
	uint32_t buf[2] = {};

	buf[0] = get_default_phy_impsp_blk_hdr1();
	buf[1] = get_default_phy_impsp_blk_hdr2();
	_set_mock_for_sb_mbox(UCIE_SB_64B_MEM_RD, UCIE_SB_MEM_REG_LOCATOR_3, offset,
						  UCIE_SB_MBOX_STAT_SUCCESS, buf);
	buf[0] = 0;
	buf[1] = 0;
	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_sb_mem_rd64(UCIE_SB_MEM_REG_LOCATOR_3, offset, buf));
	TEST_ASSERT_EQUAL(get_default_phy_impsp_blk_hdr1(), buf[0]);
	TEST_ASSERT_EQUAL(get_default_phy_impsp_blk_hdr2(), buf[1]);
}

TEST(ucie_sideband, normal_send_sb_mem_wr64)
{
	uint32_t offset = (size_t)&mmio_ptr->phy_d2d_reg_reg_phy_d2d_m0_train_setup3_1 -
		(size_t)&mmio_ptr->phy_d2d_reg_reg_phy_d2d_phy_cap;
	uint32_t buf[2] = {};
	uint32_t backup[2] = {};

	_set_mock_for_sb_mbox(UCIE_SB_64B_MEM_RD, UCIE_SB_MEM_REG_LOCATOR_0, offset,
						  UCIE_SB_MBOX_STAT_SUCCESS, buf);
	aw_ucie_sb_mem_rd64(UCIE_SB_MEM_REG_LOCATOR_0, offset, buf);
	backup[0] = buf[0];/* back up current data for comparing */
	backup[1] = buf[1];

	buf[0] = ~backup[0];
	buf[1] = ~backup[1];
	_set_mock_for_sb_mbox(UCIE_SB_64B_MEM_WR, UCIE_SB_MEM_REG_LOCATOR_0, offset,
						  UCIE_SB_MBOX_STAT_SUCCESS, buf);
	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_sb_mem_wr64(UCIE_SB_MEM_REG_LOCATOR_0, offset, buf));

	_set_mock_for_sb_mbox(UCIE_SB_64B_MEM_RD, UCIE_SB_MEM_REG_LOCATOR_0, offset,
						  UCIE_SB_MBOX_STAT_SUCCESS, buf);
	buf[0] = backup[0];
	buf[1] = backup[1];
	aw_ucie_sb_mem_rd64(UCIE_SB_MEM_REG_LOCATOR_0, offset, buf);
	TEST_ASSERT_EQUAL(~backup[0], buf[0]);
	TEST_ASSERT_EQUAL(~backup[1], buf[1]);
}

TEST(ucie_sideband, normal_send_sb_config_rd32)
{
	uint32_t offset = 4;
	uint32_t buf[1] = {};

	buf[0] = get_default_dvs_hdr1();
	_set_mock_for_sb_mbox(UCIE_SB_32B_CONFIG_RD, UCIE_SB_MEM_REG_LOCATOR_0, offset,
						  UCIE_SB_MBOX_STAT_SUCCESS, buf);
	buf[0] = 0;
	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_sb_config_rd32(UCIE_SB_MEM_REG_LOCATOR_0, offset, buf));
	TEST_ASSERT_EQUAL(get_default_dvs_hdr1(), buf[0]);
}

TEST(ucie_sideband, normal_send_sb_config_wr32)
{
	uint32_t offset = (size_t)&mmio_ptr->dvsec1_reg_reg_global_dvsec1_sb_mailbox_data_low -
		(size_t)&mmio_ptr->dvsec1_reg_reg_global_dvsec1_pcie_extnd_cap_hdr;
	uint32_t buf[1] = {};
	uint32_t backup[1] = {};

	_set_mock_for_sb_mbox(UCIE_SB_32B_CONFIG_RD, UCIE_SB_MEM_REG_LOCATOR_0, offset,
						  UCIE_SB_MBOX_STAT_SUCCESS, buf);
	aw_ucie_sb_config_rd32(UCIE_SB_MEM_REG_LOCATOR_0, offset, buf);
	backup[0] = buf[0];/* back up current data for comparing */

	buf[0] = ~backup[0];
	_set_mock_for_sb_mbox(UCIE_SB_32B_CONFIG_WR, UCIE_SB_MEM_REG_LOCATOR_0, offset,
						  UCIE_SB_MBOX_STAT_SUCCESS, buf);
	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_sb_config_wr32(UCIE_SB_MEM_REG_LOCATOR_0, offset, buf));

	_set_mock_for_sb_mbox(UCIE_SB_32B_CONFIG_RD, UCIE_SB_MEM_REG_LOCATOR_0, offset,
						  UCIE_SB_MBOX_STAT_SUCCESS, buf);
	buf[0] = backup[0];
	aw_ucie_sb_config_rd32(UCIE_SB_MEM_REG_LOCATOR_0, offset, buf);
	TEST_ASSERT_EQUAL(~backup[0], buf[0]);
}

TEST(ucie_sideband, normal_send_sb_config_rd64)
{
	uint32_t offset = 4;
	uint32_t buf[2] = {};

	buf[0] = get_default_dvs_hdr1();
	buf[1] = get_default_dvs_hdr2_cap_desc();
	_set_mock_for_sb_mbox(UCIE_SB_64B_CONFIG_RD, UCIE_SB_MEM_REG_LOCATOR_0, offset,
						  UCIE_SB_MBOX_STAT_SUCCESS, buf);
	buf[0] = 0;
	buf[1] = 0;
	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_sb_config_rd64(UCIE_SB_MEM_REG_LOCATOR_0, offset, buf));
	TEST_ASSERT_EQUAL(get_default_dvs_hdr1(), buf[0]);
	TEST_ASSERT_EQUAL(get_default_dvs_hdr2_cap_desc(), buf[1]);
}

TEST(ucie_sideband, normal_send_sb_config_wr64)
{
	uint32_t offset = (size_t)&mmio_ptr->dvsec1_reg_reg_global_dvsec1_sb_mailbox_data_low -
		(size_t)&mmio_ptr->dvsec1_reg_reg_global_dvsec1_pcie_extnd_cap_hdr;
	uint32_t buf[2] = {};
	uint32_t backup[2] = {};

	_set_mock_for_sb_mbox(UCIE_SB_64B_CONFIG_RD, UCIE_SB_MEM_REG_LOCATOR_0, offset,
						  UCIE_SB_MBOX_STAT_SUCCESS, buf);
	aw_ucie_sb_config_rd64(UCIE_SB_MEM_REG_LOCATOR_0, offset, buf);
	backup[0] = buf[0];/* back up current data for comparing */
	backup[1] = buf[1];

	buf[0] = ~backup[0];
	buf[1] = ~backup[1];
	_set_mock_for_sb_mbox(UCIE_SB_64B_CONFIG_WR, UCIE_SB_MEM_REG_LOCATOR_0, offset,
						  UCIE_SB_MBOX_STAT_SUCCESS, buf);
	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_sb_config_wr64(UCIE_SB_MEM_REG_LOCATOR_0, offset, buf));

	_set_mock_for_sb_mbox(UCIE_SB_64B_CONFIG_RD, UCIE_SB_MEM_REG_LOCATOR_0, offset,
						  UCIE_SB_MBOX_STAT_SUCCESS, buf);
	buf[0] = backup[0];
	aw_ucie_sb_config_rd64(UCIE_SB_MEM_REG_LOCATOR_0, offset, buf);
	TEST_ASSERT_EQUAL(~backup[0], buf[0]);
}

IGNORE_TEST(ucie_sideband, four_credit_for_sb)
{
	/* It will be added after testing adapter timeout exception case */
}

TEST_GROUP_RUNNER(ucie_sideband_except_only_for_mock)
{
	RUN_TEST_CASE(ucie_sideband, normal_send_sb_mem_rd32);
	RUN_TEST_CASE(ucie_sideband, fail_send_sb_mem_rd32_w_ur);
	RUN_TEST_CASE(ucie_sideband, fail_send_sb_mem_rd32_w_ca);
	RUN_TEST_CASE(ucie_sideband, fail_send_w_invalid_arg);
	RUN_TEST_CASE(ucie_sideband, normal_send_sb_mem_wr32);
	RUN_TEST_CASE(ucie_sideband, normal_send_sb_mem_rd64);
	RUN_TEST_CASE(ucie_sideband, normal_send_sb_mem_wr64);
	RUN_TEST_CASE(ucie_sideband, normal_send_sb_config_rd32);
	RUN_TEST_CASE(ucie_sideband, normal_send_sb_config_wr32);
	RUN_TEST_CASE(ucie_sideband, normal_send_sb_config_rd64);
	RUN_TEST_CASE(ucie_sideband, normal_send_sb_config_wr64);
	RUN_TEST_CASE(ucie_sideband, four_credit_for_sb);
}

TEST_GROUP_RUNNER(ucie_sideband_only_for_mock)
{
	RUN_TEST_CASE(ucie_sideband, fail_send_sb_msg_due_to_be_in_progress_already);
}
