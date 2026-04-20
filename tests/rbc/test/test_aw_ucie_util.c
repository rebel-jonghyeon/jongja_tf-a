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
	#include "fake_gic.h"
#endif /* USE_DILIGENT_PTR */
#include "timer.h"
#include "test_aw_ucie_util.h"
#include "string.h"

static const union aw_ucie_dvsec1_reg_reg_global_dvsec1_pcie_extnd_cap_hdr _pcie_ext_cap_hdr = {
	.pcie_extnd_cap_hdr_cap_id = PCIE_EXT_CAP_ID,
	.pcie_extnd_cap_hdr_revision_id = 1,
	.pcie_extnd_cap_hdr_next_cap_offset = 0/* MSI cap not used */
};

static const union aw_ucie_dvsec1_reg_reg_global_dvsec1_hdr1 default_dvs_hdr1 = {
	.hdr1_dvsec_vndr_id = DVSEC_VENDOR_ID_FOR_UCIE,
	.hdr1_dvsec_revision = 0,
	/* .hdr1_len =  TBD */
};

static const union aw_ucie_dvsec1_reg_reg_global_dvsec1_hdr2_and_cap_descriptor _dvs_hdr2_cap_ds = {
	.hdr2_dvsec_id = 0,
	.cap_descriptor_no_of_reg_locators = 2,/* 4 register locators */
	.cap_descriptor_sb_mailbox_reg_present = ENABLE,
};

static const union aw_ucie_dvsec1_reg_reg_global_dvsec1_ucie_link_cap default_link_cap = {
	.lcap_raw_format = ENABLE,
	.lcap_max_link_width = TARGET_LINK_WIDTH_X64,
	.lcap_max_link_speed = TARGET_LINK_SPEED_16GT,
	.lcap_adv_pkg = ENABLE,
	.lcap_lat_opt_256b_flit_fmt_optnl_bytes_strmng = ENABLE,
	.lcap_runtime_link_test_parity_feat_err_signaling = ENABLE,
	.lcap_width32_mode = ENABLE,
};

static const union aw_ucie_dvsec1_reg_reg_global_dvsec1_ucie_link_status _link_stat = {
	.val = 0
};

static const union aw_ucie_dvsec1_reg_reg_global_dvsec1_ucie_link_status _done_link_stat = {
	.lstatus_link_status = ENABLE,
	.lstatus_link_status_change = ENABLE,
	.lstatus_flit_format_status = FLIT_FORMAT_6_LAT_256_W
};

static const union aw_ucie_dvsec1_reg_reg_global_dvsec1_ucie_link_cntrl _link_ctrl = {
	.lcntrl_lat_opt_256b_flit_fmt_optnl_bytes_strmng = ENABLE
};

static const union aw_ucie_phy_d2d_reg_reg_phy_d2d_phy_cntrl _phy_ctrl = {
	.cntrl_mod_to_byte_map = ENABLE,
};

static const union aw_ucie_adapter_d2d_reg_reg_adapter_d2d_ucie_blk_hdr_reg1 _d2d_phy_hdr1 = {
	.vndr_id = DVSEC_VENDOR_ID_FOR_UCIE,
	.vndr_id_reg_block = UCIE_REG_BLK_ID_D2D_PHY
};

static const union aw_ucie_adapter_d2d_reg_reg_adapter_d2d_ucie_blk_hdr_reg2 _d2d_phy_hdr2 = {
	.vndr_reg_block_version = 0
};

static const union aw_ucie_adapter_d2d_reg_reg_adapter_d2d_ucie_blk_hdr_reg3 _d2d_phy_hdr3 = {
	.vndr_reg_block_length = 0x2000
};

static const union aw_ucie_test_comp_reg_reg_glbl_tstcmp_ucie_blk_hdr1 _test_comp_hdr1 = {
	.blk_hdr1_vndr_id = DVSEC_VENDOR_ID_FOR_UCIE,
	.blk_hdr1_vndr_id_reg_blk = UCIE_REG_BLK_ID_TEST_COMP
};

static const union aw_ucie_test_comp_reg_reg_glbl_tstcmp_ucie_blk_hdr2 _test_comp_hdr2 = {
	.blk_hdr2_vndr_blk_version = 0,
};

static const union aw_ucie_test_comp_reg_reg_glbl_tstcmp_ucie_blk_hdr3 _test_comp_hdr3 = {
	.blk_hdr3_vndr_blk_len = 0x2000
};

static const union aw_ucie_test_comp_reg_reg_glbl_d2d_adapter_testcompl_reg_blk_offset _d2d_test_comp_offset = {
	.d2d_adapter_testcompl_blk_offset = 0,
	.d2d_adapter_testcompl_blk_len = 1
};

static const union aw_ucie_test_comp_reg_reg_glbl_phy_testcompl_reg_blk_offset _phy_test_comp_offset = {
	.phy_testcompl_blk_offset = 1,
	.phy_testcompl_blk_len = 1
};

static const union aw_ucie_adapter_imp_spec_rdi_reg_reg_adapter_impsp_ucie_blk_hdr1 _d2dimp_hdr1 = {
	.vndr_id = DVSEC_VENDOR_ID_FOR_UCIE,
	.vndr_id_reg_block = UCIE_REG_BLK_ID_D2D_IMP,
};

static const union aw_ucie_adapter_imp_spec_rdi_reg_reg_adapter_impsp_ucie_blk_hdr2 _d2dimp_hdr2 = {
	.vndr_reg_block_version = 0
};

static const union aw_ucie_adapter_imp_spec_rdi_reg_reg_adapter_impsp_ucie_blk_hdr3 _d2dimp_hdr3 = {
	.vndr_reg_block_length = 0x1000
};

static const union aw_ucie_phy_imp_spec_reg_reg_phy_impsp_ucie_blk_hdr1 _phy_imp_hdr1 = {
	.vndr_id = DVSEC_VENDOR_ID_FOR_UCIE,
	.vndr_id_reg_blk = UCIE_REG_BLK_ID_PHY_IMP,
};

static const union aw_ucie_phy_imp_spec_reg_reg_phy_impsp_ucie_blk_hdr2 _phy_imp_hdr2 = {
	.vndr_reg_blk_version = 0,
};

static const union aw_ucie_phy_imp_spec_reg_reg_phy_impsp_ucie_blk_hdr3 _phy_imp_hdr3 = {
	.vndr_reg_blk_length = 0x1000,
};

static const union aw_ucie_dvsec1_reg_reg_global_dvsec1_reg_loc0_low _reg_loc0_low = {
	.reg_loc0_low_reg_blk_identifier = UCIE_REG_BLK_ID_D2D_PHY,
	.reg_loc0_low_reg_blk_offset = 0x5,
};

static const union aw_ucie_dvsec1_reg_reg_global_dvsec1_reg_loc1_low _reg_loc1_low = {
	.reg_loc1_low_reg_blk_identifier = UCIE_REG_BLK_ID_TEST_COMP,
	.reg_loc1_low_reg_blk_offset = 0x7,
};

static const union aw_ucie_dvsec1_reg_reg_global_dvsec1_reg_loc2_low _reg_loc2_low = {
	.reg_loc2_low_reg_blk_identifier = UCIE_REG_BLK_ID_D2D_IMP,
	.reg_loc2_low_reg_blk_offset = 0x9,
};

static const union aw_ucie_dvsec1_reg_reg_global_dvsec1_reg_loc3_low _reg_loc3_low = {
	.reg_loc3_low_reg_blk_identifier = UCIE_REG_BLK_ID_PHY_IMP,
	.reg_loc3_low_reg_blk_offset = 0xA,
};

static const union aw_ucie_phy_d2d_reg_reg_phy_d2d_pcie_extnd_cap_hdr _phy_extnd_cap_hdr = {
	.extnd_cap_hdr_cap_id = PCIE_EXT_CAP_ID,
	.extnd_cap_hdr_revision_id = 1,
	.extnd_cap_hdr_next_cap_offset = 0,
};

static const union aw_ucie_phy_d2d_reg_reg_phy_d2d_dvsec_hdr1 _uhm_dvsec_hdr1 = {
	.dvsec_hdr1_vendor_id = DVSEC_VENDOR_ID_FOR_UCIE,
	.dvsec_hdr1_revision = 0,
	.dvsec_hdr1_length = 0,
};

static const union aw_ucie_phy_d2d_reg_reg_phy_d2d_dvsec_hdr2 _uhm_dvsec_hdr2 = {
	.dvsec_hdr2_dvsec_id = 1,
};

static const union aw_ucie_phy_d2d_reg_reg_phy_d2d_phy_cap _phy_cap = {
	.val = 0
	/* need to check
	 * .cap_mod_to_byte_map = ENABLE,
	 * .cap_terminated_link = ENABLE,
	 * .cap_tx_equalization = ENABLE,
	 * .cap_vswing_enc =
	 */
};

static struct aw_ucie real_map_stuff;
static struct aw_ucie mmio_var;
static struct aw_ucie mmio_write_buf;

uint32_t get_default_pcie_extnd_cap_hdr(void) { return _pcie_ext_cap_hdr.val; }
uint32_t get_default_dvs_hdr1(void) { return default_dvs_hdr1.val; }
uint32_t get_default_dvs_hdr2_cap_desc(void) { return _dvs_hdr2_cap_ds.val; }
uint32_t get_default_link_cap(void) { return default_link_cap.val; }
uint32_t get_default_link_stat(void) { return _link_stat.val; }
uint32_t get_done_link_stat(void) { return _done_link_stat.val; }
uint32_t get_default_link_ctrl(void) { return _link_ctrl.val; }
uint32_t get_default_phy_ctrl(void) { return _phy_ctrl.val; }
uint32_t get_default_phy_impsp_blk_hdr1(void) { return _phy_imp_hdr1.val; }
uint32_t get_default_phy_impsp_blk_hdr2(void) {	return _phy_imp_hdr2.val; }
uint32_t get_default_phy_capability(void) { return _phy_cap.val; }
uint32_t get_default_phy_extnd_cap_hdr(void) { return _phy_extnd_cap_hdr.val; }
uint32_t get_default_uhm_dvsec_hdr1(void) { return _uhm_dvsec_hdr1.val; }
uint32_t get_default_uhm_dvsec_hdr2(void) { return _uhm_dvsec_hdr2.val; }

struct aw_ucie *get_aw_ucie_mmio_var(void) { return &mmio_var; };
struct aw_ucie *get_aw_ucie_mmio_write_buf(void) { return &mmio_write_buf; };
struct aw_ucie *get_aw_ucie_real_map(void) { return real_map; };

static void init_mmio_var_to_default(void)
{
	memset(&mmio_var, 0, sizeof(mmio_var));
	mmio_var.dvsec1_reg_reg_global_dvsec1_pcie_extnd_cap_hdr = _pcie_ext_cap_hdr;
	mmio_var.dvsec1_reg_reg_global_dvsec1_hdr1 = default_dvs_hdr1;
	mmio_var.dvsec1_reg_reg_global_dvsec1_hdr2_and_cap_descriptor = _dvs_hdr2_cap_ds;
	mmio_var.dvsec1_reg_reg_global_dvsec1_ucie_link_cap = default_link_cap;
	mmio_var.dvsec1_reg_reg_global_dvsec1_ucie_link_status = _link_stat;
	mmio_var.dvsec1_reg_reg_global_dvsec1_ucie_link_cntrl = _link_ctrl;

	mmio_var.dvsec1_reg_reg_global_dvsec1_reg_loc0_low = _reg_loc0_low;
	mmio_var.dvsec1_reg_reg_global_dvsec1_reg_loc1_low = _reg_loc1_low;
	mmio_var.dvsec1_reg_reg_global_dvsec1_reg_loc2_low = _reg_loc2_low;
	mmio_var.dvsec1_reg_reg_global_dvsec1_reg_loc3_low = _reg_loc3_low;

	mmio_var.adapter_d2d_reg_reg_adapter_d2d_ucie_blk_hdr_reg1 = _d2d_phy_hdr1;
	mmio_var.adapter_d2d_reg_reg_adapter_d2d_ucie_blk_hdr_reg2 = _d2d_phy_hdr2;
	mmio_var.adapter_d2d_reg_reg_adapter_d2d_ucie_blk_hdr_reg3 = _d2d_phy_hdr3;
	mmio_var.test_comp_reg_reg_glbl_tstcmp_ucie_blk_hdr1 = _test_comp_hdr1;
	mmio_var.test_comp_reg_reg_glbl_tstcmp_ucie_blk_hdr2 = _test_comp_hdr2;
	mmio_var.test_comp_reg_reg_glbl_tstcmp_ucie_blk_hdr3 = _test_comp_hdr3;
	mmio_var.test_comp_reg_reg_glbl_d2d_adapter_testcompl_reg_blk_offset = _d2d_test_comp_offset;
	mmio_var.test_comp_reg_reg_glbl_phy_testcompl_reg_blk_offset = _phy_test_comp_offset;
	mmio_var.adapter_imp_spec_rdi_reg_reg_adapter_impsp_ucie_blk_hdr1 = _d2dimp_hdr1;
	mmio_var.adapter_imp_spec_rdi_reg_reg_adapter_impsp_ucie_blk_hdr2 = _d2dimp_hdr2;
	mmio_var.adapter_imp_spec_rdi_reg_reg_adapter_impsp_ucie_blk_hdr3 = _d2dimp_hdr3;
	mmio_var.phy_imp_spec_reg_reg_phy_impsp_ucie_blk_hdr1 = _phy_imp_hdr1;
	mmio_var.phy_imp_spec_reg_reg_phy_impsp_ucie_blk_hdr2 = _phy_imp_hdr2;
	mmio_var.phy_imp_spec_reg_reg_phy_impsp_ucie_blk_hdr3 = _phy_imp_hdr3;

	mmio_var.phy_d2d_reg_reg_phy_d2d_phy_cap = _phy_cap;
	mmio_var.phy_d2d_reg_reg_phy_d2d_pcie_extnd_cap_hdr = _phy_extnd_cap_hdr;
	mmio_var.phy_d2d_reg_reg_phy_d2d_dvsec_hdr1 = _uhm_dvsec_hdr1;
	mmio_var.phy_d2d_reg_reg_phy_d2d_dvsec_hdr2 = _uhm_dvsec_hdr2;
}

void init_mmio_map(int32_t ucie_ss_id)
{
	init_mmio_var_to_default();
	memset(&real_map_stuff, 0, sizeof(real_map_stuff));
#ifdef USE_DILIGENT_PTR
	real_map = &real_map_stuff;
#else
	/* need to sw reset? */
	real_map = (struct aw_ucie *)ucie_ss_base_addr_array[ucie_ss_id];
#endif /* USE_DILIGENT_PTR */
}

uint32_t get_random_of_range(uint32_t start, uint32_t end)
{
	uint32_t offset = get_tick() % (end - start + 1);

	return start + offset;
}

#ifdef USE_DILIGENT_PTR
extern void ucie_irq_handler(void *data);
extern struct diligent_ptr < struct aw_ucie > reg[NUM_OF_UCIE_SS_ID];
extern struct diligent_ptr < struct aw_ucie > target_ss;
int32_t fake_aw_ucie_init(int32_t ucie_ss_id, void * const base_addr)
{
	const uint32_t ucie_ss_intr_id[] = {
	BLK_RBC_H00_UCIE_INTR_ID,
	BLK_RBC_H01_UCIE_INTR_ID,
	BLK_RBC_V00_UCIE_INTR_ID,
	BLK_RBC_V01_UCIE_INTR_ID,
	BLK_RBC_V10_UCIE_INTR_ID,
	BLK_RBC_V11_UCIE_INTR_ID,
	};

	if (ucie_ss_id >= NUM_OF_UCIE_SS_ID) {
		return -2;
	}
	reg[ucie_ss_id] = (struct aw_ucie *)(base_addr);
	target_ss = reg[ucie_ss_id];

	gic_irq_connect(ucie_ss_intr_id[ucie_ss_id], ucie_irq_handler, (void *)(uint64_t)ucie_ss_id);

	return 0;
}

uint32_t link_retraining_counter;
int32_t dummy_aw_ucie_link_training(void)
{
	return 0;
}

int32_t dummy_aw_ucie_link_retraining(void)
{
	link_retraining_counter++;
	return 0;
}

int32_t dummy_aw_ucie_sb_mem_wr32(const uint32_t, const uint32_t, uint32_t *const)
{
	return 0;
}

int32_t dummy_aw_ucie_sb_mem_rd32_all_clear(const uint32_t, const uint32_t, uint32_t *const val)
{
	*val = 0;

	return 0;
}

int32_t dummy_aw_ucie_sb_mem_rd32_all_set(const uint32_t, const uint32_t, uint32_t *const val)
{
	*val = 0xFFFFFFFF;

	return 0;
}

int32_t dummy_aw_ucie_mb_inject_test_flit(const uint32_t inj_mode, const uint32_t flit_num,
										  const uint32_t payload_type, const uint32_t pattern,
										  const uint32_t offset, const uint32_t repetition)
{
	return 0;
}

int32_t dummy_aw_ucie_inject_nop_flit(const uint32_t inj_mode, const uint32_t flit_num)
{
	return 0;
}

int32_t dummy_aw_ucie_inject_crc_err(const uint32_t inverted_bits, const uint32_t injection_cnt)
{
	return 0;
}

static uint32_t reg_val;

void set_value_fake_aw_ucie_sb_mem_rd32(const uint32_t val)
{
	reg_val = val;
}

int32_t fake_aw_ucie_sb_mem_rd32(const uint32_t rl, const uint32_t offset, uint32_t *const val)
{
	*val = reg_val;
	return 0;
}
#endif /* USE_DILIGENT_PTR */

