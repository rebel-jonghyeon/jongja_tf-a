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
#include "rl_errors.h"
#include "unity_fixture.h"

static struct aw_ucie *mmio_ptr;
static const int32_t ucie_ss_id = UCIE_SS_H00_ID;

TEST_GROUP(ucie_init);

TEST_SETUP(ucie_init)
{
	CLEAR_SNAPSHOT_ARR(target_ss);

	init_mmio_map(ucie_ss_id);

	mmio_ptr = get_aw_ucie_mmio_var();
	real_map = get_aw_ucie_real_map();
}

TEST_TEAR_DOWN(ucie_init)
{
	VERIFY(target_ss);
}

static int32_t _normal_ucie_init(int32_t ucie_ss_id)
{
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);/* pcie extnd cap hdr */
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);/* dvs hdr1 */

	/* Register Locator + check header */
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);/* reg loc0 */

	/* Compare address */
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);/* reg loc0 */
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);/* reg loc1 */
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);/* reg loc2 */
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);/* reg loc3 */

	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);/* PHY Test/Comp Reg Block Offset */
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);/* D2D Apater Test/Comp Reg Block Offset */

	return aw_ucie_init(ucie_ss_id, real_map);
}

TEST(ucie_init, normal_init_aw_ucie)
{
	TEST_ASSERT_EQUAL(RL_OK, _normal_ucie_init(ucie_ss_id));
}

TEST(ucie_init, fail_set_target_ss_before_setting)
{
#ifdef USE_DILIGENT_PTR
	reg[ucie_ss_id] = 0;
#endif /* USE_DILIGENT_PTR */
	TEST_ASSERT_EQUAL(RL_NOTREADY, aw_ucie_set_target_ss(ucie_ss_id));
}

TEST(ucie_init, fail_set_target_ss_w_invalid_value)
{
	_normal_ucie_init(ucie_ss_id);

	TEST_ASSERT_EQUAL(RL_BADARG, aw_ucie_set_target_ss(-1));
	TEST_ASSERT_EQUAL(RL_BADARG, aw_ucie_set_target_ss(NUM_OF_UCIE_SS_ID));
}

TEST(ucie_init, set_target_ss_w_valid_value)
{
	_normal_ucie_init(ucie_ss_id);

	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_set_target_ss(ucie_ss_id));
	TEST_ASSERT_EQUAL(ucie_ss_id, aw_ucie_get_target_ss());
}

TEST(ucie_init, check_dvsec_hdr_after_init)
{
	uint32_t val;

	_normal_ucie_init(ucie_ss_id);
	aw_ucie_set_target_ss(ucie_ss_id);

	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);
	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_get_pcie_cap_hdr(&val));
	TEST_ASSERT_EQUAL(get_default_pcie_extnd_cap_hdr(), val);

	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);
	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_get_dvs_hdr1(&val));
	TEST_ASSERT_EQUAL(get_default_dvs_hdr1(), val);

	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);
	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_get_dvs_hdr2_cap_desc(&val));
	TEST_ASSERT_EQUAL(get_default_dvs_hdr2_cap_desc(), val);
}

TEST(ucie_init, check_link_capability_after_init)
{
	uint32_t val;

	_normal_ucie_init(ucie_ss_id);
	aw_ucie_set_target_ss(ucie_ss_id);

	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);
	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_get_dvs_hdr2_cap_desc(&val));
	TEST_ASSERT_EQUAL(get_default_dvs_hdr2_cap_desc(), val);

	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);
	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_get_link_capability(&val));
	TEST_ASSERT_EQUAL(get_default_link_cap(), val);
}

TEST(ucie_init, fail_init_due_to_invalid_d2d_test_comp_blk_offset)
{
	const uint32_t INVALID_OFFSET = 123;

	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);/* pcie extnd cap hdr */
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);/* dvs hdr1 */

	/* Register Locator + check header */
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);/* reg loc0 */

	/* Compare address */
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);/* reg loc0 */
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);/* reg loc1 */
	mmio_ptr->test_comp_reg_reg_glbl_d2d_adapter_testcompl_reg_blk_offset.d2d_adapter_testcompl_blk_offset =
		INVALID_OFFSET;
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);/* D2D Apater Test/Comp Reg Block Offset */

	TEST_ASSERT_EQUAL(RL_ERROR, aw_ucie_init(ucie_ss_id, real_map));
}

TEST(ucie_init, fail_init_due_to_invalid_d2d_test_comp_blk_length)
{
	const uint32_t INVALID_LENGTH = 123;

	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);/* pcie extnd cap hdr */
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);/* dvs hdr1 */

	/* Register Locator + check header */
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);/* reg loc0 */

	/* Compare address */
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);/* reg loc0 */
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);/* reg loc1 */
	mmio_ptr->test_comp_reg_reg_glbl_d2d_adapter_testcompl_reg_blk_offset.d2d_adapter_testcompl_blk_len =
		INVALID_LENGTH;
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);/* D2D Apater Test/Comp Reg Block Offset */

	TEST_ASSERT_EQUAL(RL_ERROR, aw_ucie_init(ucie_ss_id, real_map));
}

TEST(ucie_init, fail_init_due_to_invalid_phy_test_comp_blk_offset)
{
	const uint32_t INVALID_OFFSET = 123;

	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);/* pcie extnd cap hdr */
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);/* dvs hdr1 */

	/* Register Locator + check header */
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);/* reg loc0 */

	/* Compare address */
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);/* reg loc0 */
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);/* reg loc1 */
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);/* D2D Apater Test/Comp Reg Block Offset */
	mmio_ptr->test_comp_reg_reg_glbl_phy_testcompl_reg_blk_offset.phy_testcompl_blk_offset = INVALID_OFFSET;
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);/* PHY Test/Comp Reg Block Offset */

	TEST_ASSERT_EQUAL(RL_ERROR, aw_ucie_init(ucie_ss_id, real_map));
}

TEST(ucie_init, fail_init_due_to_invalid_phy_test_comp_blk_length)
{
	const uint32_t INVALID_LENGTH = 123;

	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);/* pcie extnd cap hdr */
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);/* dvs hdr1 */

	/* Register Locator + check header */
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);/* reg loc0 */

	/* Compare address */
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);/* reg loc0 */
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);/* reg loc1 */
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);/* D2D Apater Test/Comp Reg Block Offset */
	mmio_ptr->test_comp_reg_reg_glbl_phy_testcompl_reg_blk_offset.phy_testcompl_blk_len = INVALID_LENGTH;
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);/* PHY Test/Comp Reg Block Offset */

	TEST_ASSERT_EQUAL(RL_ERROR, aw_ucie_init(ucie_ss_id, real_map));
}

TEST(ucie_init, fail_init_due_to_invalid_pcie_ext_dvsec_cap_hdr)
{
	mmio_ptr->dvsec1_reg_reg_global_dvsec1_pcie_extnd_cap_hdr.pcie_extnd_cap_hdr_cap_id = 0;
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);
	TEST_ASSERT_EQUAL(RL_NOT_FOUND, aw_ucie_init(ucie_ss_id, real_map));
}

TEST(ucie_init, fail_init_due_to_invalid_dvsec_vendor_id)
{
	mmio_ptr->dvsec1_reg_reg_global_dvsec1_hdr1.hdr1_dvsec_vndr_id = 0;
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);
	TEST_ASSERT_EQUAL(RL_NOT_FOUND, aw_ucie_init(ucie_ss_id, real_map));
}

TEST(ucie_init, fail_init_due_to_invalid_reg_loc0)
{
	mmio_ptr->dvsec1_reg_reg_global_dvsec1_reg_loc0_low.reg_loc0_low_reg_blk_offset = 0x1000;
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);
	TEST_ASSERT_EQUAL(RL_ERROR, aw_ucie_init(ucie_ss_id, real_map));
}

TEST(ucie_init, fail_init_due_to_invalid_reg_loc1)
{
	mmio_ptr->dvsec1_reg_reg_global_dvsec1_reg_loc1_low.reg_loc1_low_reg_blk_offset = 0x0;
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);
	TEST_ASSERT_EQUAL(RL_ERROR, aw_ucie_init(ucie_ss_id, real_map));
}

TEST(ucie_init, fail_init_due_to_invalid_reg_loc2)
{
	mmio_ptr->dvsec1_reg_reg_global_dvsec1_reg_loc2_low.reg_loc2_low_reg_blk_offset = 0x1000;
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);
	TEST_ASSERT_EQUAL(RL_ERROR, aw_ucie_init(ucie_ss_id, real_map));
}

TEST(ucie_init, fail_init_due_to_invalid_reg_loc3)
{
	mmio_ptr->dvsec1_reg_reg_global_dvsec1_reg_loc3_low.reg_loc3_low_reg_blk_offset = 0x1000;
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);
	TEST_ASSERT_EQUAL(RL_ERROR, aw_ucie_init(ucie_ss_id, real_map));
}

TEST(ucie_init, fail_init_due_to_invalid_vndr_id_of_d2d_phy_blk_hdr)
{
	mmio_ptr->adapter_d2d_reg_reg_adapter_d2d_ucie_blk_hdr_reg1.vndr_id =
		DVSEC_VENDOR_ID_FOR_UCIE - 1;
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);
	TEST_ASSERT_EQUAL(RL_ERROR, aw_ucie_init(ucie_ss_id, real_map));
}

TEST(ucie_init, fail_init_due_to_invalid_blk_id_of_d2d_phy_blk_hdr)
{
	mmio_ptr->adapter_d2d_reg_reg_adapter_d2d_ucie_blk_hdr_reg1.vndr_id_reg_block =
		UCIE_REG_BLK_ID_TEST_COMP;
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);
	TEST_ASSERT_EQUAL(RL_ERROR, aw_ucie_init(ucie_ss_id, real_map));
}

TEST(ucie_init, fail_init_due_to_invalid_vndr_id_of_test_comp_blk_hdr)
{
	mmio_ptr->test_comp_reg_reg_glbl_tstcmp_ucie_blk_hdr1.blk_hdr1_vndr_id =
		DVSEC_VENDOR_ID_FOR_UCIE - 1;
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);
	TEST_ASSERT_EQUAL(RL_ERROR, aw_ucie_init(ucie_ss_id, real_map));
}

TEST(ucie_init, fail_init_due_to_invalid_blk_id_of_test_comp_blk_hdr)
{
	mmio_ptr->test_comp_reg_reg_glbl_tstcmp_ucie_blk_hdr1.blk_hdr1_vndr_id_reg_blk =
		UCIE_REG_BLK_ID_D2D_IMP;
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);
	TEST_ASSERT_EQUAL(RL_ERROR, aw_ucie_init(ucie_ss_id, real_map));
}

TEST(ucie_init, fail_init_due_to_invalid_vndr_id_of_d2d_imp_blk_hdr)
{
	mmio_ptr->adapter_imp_spec_rdi_reg_reg_adapter_impsp_ucie_blk_hdr1.vndr_id =
		DVSEC_VENDOR_ID_FOR_UCIE - 1;
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);
	TEST_ASSERT_EQUAL(RL_ERROR, aw_ucie_init(ucie_ss_id, real_map));
}

TEST(ucie_init, fail_init_due_to_invalid_blk_id_of_d2d_imp_blk_hdr)
{
	mmio_ptr->adapter_imp_spec_rdi_reg_reg_adapter_impsp_ucie_blk_hdr1.vndr_id_reg_block =
		UCIE_REG_BLK_ID_TEST_COMP;
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);
	TEST_ASSERT_EQUAL(RL_ERROR, aw_ucie_init(ucie_ss_id, real_map));
}

TEST(ucie_init, fail_init_due_to_invalid_vndr_id_of_phy_imp_blk_hdr)
{
	mmio_ptr->phy_imp_spec_reg_reg_phy_impsp_ucie_blk_hdr1.vndr_id = DVSEC_VENDOR_ID_FOR_UCIE - 1;
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);
	TEST_ASSERT_EQUAL(RL_ERROR, aw_ucie_init(ucie_ss_id, real_map));
}

TEST(ucie_init, fail_init_due_to_invalid_blk_id_of_phy_imp_blk_hdr)
{
	mmio_ptr->phy_imp_spec_reg_reg_phy_impsp_ucie_blk_hdr1.vndr_id_reg_blk =
		UCIE_REG_BLK_ID_TEST_COMP;
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);
	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);
	TEST_ASSERT_EQUAL(RL_ERROR, aw_ucie_init(ucie_ss_id, real_map));
}

TEST(ucie_init, check_phy_capability_after_init)
{
	uint32_t val;

	_normal_ucie_init(ucie_ss_id);
	aw_ucie_set_target_ss(ucie_ss_id);

	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);
	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_get_phy_cap(&val));
	TEST_ASSERT_EQUAL(get_default_phy_capability(), val);
}

TEST(ucie_init, check_phy_extended_cap_hdr_after_init)
{
	uint32_t val;

	_normal_ucie_init(ucie_ss_id);
	aw_ucie_set_target_ss(ucie_ss_id);

	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);
	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_get_phy_extnd_cap_hdr(&val));
	TEST_ASSERT_EQUAL(get_default_phy_extnd_cap_hdr(), val);
}

TEST(ucie_init, check_uhm_dvsec_hdr_after_init)
{
	uint32_t val;

	_normal_ucie_init(ucie_ss_id);
	aw_ucie_set_target_ss(ucie_ss_id);

	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);
	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_get_uhm_dvsec_hdr1(&val));
	TEST_ASSERT_EQUAL(get_default_uhm_dvsec_hdr1(), val);

	PUSH_EXPECT_READ_AND_RETURN(target_ss, mmio_ptr);
	TEST_ASSERT_EQUAL(RL_OK, aw_ucie_get_uhm_dvsec_hdr2(&val));
	TEST_ASSERT_EQUAL(get_default_uhm_dvsec_hdr2(), val);
}

TEST_GROUP_RUNNER(ucie_init_except_only_for_mock)
{
	RUN_TEST_CASE(ucie_init, normal_init_aw_ucie);
	RUN_TEST_CASE(ucie_init, fail_set_target_ss_before_setting);
	RUN_TEST_CASE(ucie_init, fail_set_target_ss_w_invalid_value);
	RUN_TEST_CASE(ucie_init, set_target_ss_w_valid_value);
	RUN_TEST_CASE(ucie_init, check_dvsec_hdr_after_init);
	RUN_TEST_CASE(ucie_init, check_link_capability_after_init);
	RUN_TEST_CASE(ucie_init, check_phy_capability_after_init);
	RUN_TEST_CASE(ucie_init, check_phy_extended_cap_hdr_after_init);
	RUN_TEST_CASE(ucie_init, check_uhm_dvsec_hdr_after_init);
}

TEST_GROUP_RUNNER(ucie_init_only_for_mock)
{
	RUN_TEST_CASE(ucie_init, fail_init_due_to_invalid_pcie_ext_dvsec_cap_hdr);
	RUN_TEST_CASE(ucie_init, fail_init_due_to_invalid_dvsec_vendor_id);
	RUN_TEST_CASE(ucie_init, fail_init_due_to_invalid_reg_loc0);
	RUN_TEST_CASE(ucie_init, fail_init_due_to_invalid_reg_loc1);
	RUN_TEST_CASE(ucie_init, fail_init_due_to_invalid_reg_loc2);
	RUN_TEST_CASE(ucie_init, fail_init_due_to_invalid_reg_loc3);
	RUN_TEST_CASE(ucie_init, fail_init_due_to_invalid_vndr_id_of_d2d_phy_blk_hdr);
	RUN_TEST_CASE(ucie_init, fail_init_due_to_invalid_blk_id_of_d2d_phy_blk_hdr);
	RUN_TEST_CASE(ucie_init, fail_init_due_to_invalid_vndr_id_of_test_comp_blk_hdr);
	RUN_TEST_CASE(ucie_init, fail_init_due_to_invalid_blk_id_of_test_comp_blk_hdr);
	RUN_TEST_CASE(ucie_init, fail_init_due_to_invalid_vndr_id_of_d2d_imp_blk_hdr);
	RUN_TEST_CASE(ucie_init, fail_init_due_to_invalid_blk_id_of_d2d_imp_blk_hdr);
	RUN_TEST_CASE(ucie_init, fail_init_due_to_invalid_vndr_id_of_phy_imp_blk_hdr);
	RUN_TEST_CASE(ucie_init, fail_init_due_to_invalid_blk_id_of_phy_imp_blk_hdr);
	RUN_TEST_CASE(ucie_init, fail_init_due_to_invalid_d2d_test_comp_blk_offset);
	RUN_TEST_CASE(ucie_init, fail_init_due_to_invalid_d2d_test_comp_blk_length);
	RUN_TEST_CASE(ucie_init, fail_init_due_to_invalid_phy_test_comp_blk_offset);
	RUN_TEST_CASE(ucie_init, fail_init_due_to_invalid_phy_test_comp_blk_length);
}
