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
#pragma once
#include <rebel_h_platform.h>

#define NOT_USED_ARG	(0)
#define NOT_APPLICABLE	(0)
#define ENABLE			(1)
#define DISABLE			(0)
#define X_ENA			(ENABLE)
#define X_DIS			(DISABLE)

#ifdef USE_DILIGENT_PTR
	extern struct diligent_ptr < struct aw_ucie > reg[NUM_OF_UCIE_SS_ID];
	extern struct diligent_ptr < struct aw_ucie > target_ss;
	static struct aw_ucie *real_map;

int32_t fake_aw_ucie_init(int32_t ucie_s_id, void * const base_addr);
int32_t dummy_aw_ucie_link_training(void);
extern uint32_t link_retraining_counter;
int32_t dummy_aw_ucie_link_retraining(void);
int32_t dummy_aw_ucie_sb_mem_wr32(const uint32_t rl, const uint32_t offset, uint32_t *const val);
int32_t dummy_aw_ucie_sb_mem_rd32_all_clear(const uint32_t rl, const uint32_t offset, uint32_t *const val);
int32_t dummy_aw_ucie_sb_mem_rd32_all_set(const uint32_t rl, const uint32_t offset, uint32_t *const val);
int32_t dummy_aw_ucie_mb_inject_test_flit(const uint32_t inj_mode, const uint32_t flit_num,
										  const uint32_t payload_type, const uint32_t pattern,
										  const uint32_t offset, const uint32_t repetition);
int32_t dummy_aw_ucie_inject_crc_err(const uint32_t inverted_bits, const uint32_t injection_cnt);
int32_t dummy_aw_ucie_inject_nop_flit(const uint32_t inj_mode, const uint32_t flit_num);
#else
	static const uint64_t ucie_ss_base_addr_array[NUM_OF_UCIE_SS_ID] = {
	UCIE_SS0_H_PRIVATE, UCIE_SS1_H_PRIVATE,
	UCIE_SS0_V0_PRIVATE, UCIE_SS1_V0_PRIVATE,
	UCIE_SS0_V1_PRIVATE, UCIE_SS1_V1_PRIVATE};

	static struct aw_ucie *real_map;
	#define PUSH_EXPECT_READ_AND_RETURN(target_ptr, val_ptr)
	#define PUSH_COMPARE_SNAPSHOT(target_ptr, val_ptr)
	#define PUSH_EXPECT_WRITE(target_ptr, current_val_ptr, write_val_ptr)
	#define CLEAR_SNAPSHOT_ARR(target_ptr)
	#define VERIFY(target_ptr)
	#define PAUSE(target_ptr)
	#define RESUME(target_ptr)
#endif /* USE_DILIGENT_PTR */

uint32_t get_default_pcie_extnd_cap_hdr(void);
uint32_t get_default_dvs_hdr1(void);
uint32_t get_default_dvs_hdr2_cap_desc(void);
uint32_t get_default_link_cap(void);
uint32_t get_default_link_stat(void);
uint32_t get_done_link_stat(void);
uint32_t get_default_link_ctrl(void);
uint32_t get_default_phy_ctrl(void);
uint32_t get_default_phy_impsp_blk_hdr1(void);
uint32_t get_default_phy_impsp_blk_hdr2(void);
uint32_t get_default_phy_capability(void);
uint32_t get_default_phy_extnd_cap_hdr(void);
uint32_t get_default_uhm_dvsec_hdr1(void);
uint32_t get_default_uhm_dvsec_hdr2(void);
struct aw_ucie *get_aw_ucie_mmio_var(void);
struct aw_ucie *get_aw_ucie_mmio_write_buf(void);
struct aw_ucie *get_aw_ucie_real_map(void);

void init_mmio_map(int32_t ucie_ss_id);
uint32_t get_random_of_range(uint32_t start, uint32_t end);

void set_value_fake_aw_ucie_sb_mem_rd32(const uint32_t val);
int32_t fake_aw_ucie_sb_mem_rd32(const uint32_t rl, const uint32_t offset, uint32_t *const val);
