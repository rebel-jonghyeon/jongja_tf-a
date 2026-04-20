/*
 * Copyright (c) 2024, Samsung Electronics Co., Ltd. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef REBEL_H_RBC_H
#define REBEL_H_RBC_H

#include <stdint.h>

#if ZEBU
/**
 * @fn		set_num_of_chips_and_rbc_for_ZEBU(void);
 * @brief	Set by recognizing the number of chipsets and blk_rbc according to various zebu images.
 */
uint32_t set_num_of_chips_and_rbc_for_ZEBU(void);
#endif /* ZEBU */

/**
 * @fn		set_route_table
 * @brief	Set remap value in routing table of target chiplet.
 * @param	chiplet_id: The target chiplet id.
 * @param	base_addr:  The base address of the UCIE_SS.
 */
void set_route_table(const uint32_t chiplet_id, const uint32_t remap_noc, const uint32_t remap_nic);

/**
 * @fn		repeat_func_for_all_rbc
 * @brief	Execute the transmitted function for each rbc of each chiplet from start_chiplet.
 * @param	func: It is a function to be performed in each blk_rbc.
 *			  The arguments are the base address of the chiplet id and SFR base address.
 * @param	base_offset:  SFR base address offset in blk_rbc.
 * @param	start_chiplet:  First chiplet id to start performing func.
 */
void repeat_func_for_all_rbc(void (*func)(uint32_t, uint64_t), const uint32_t base_offset,
							 uint32_t start_chiplet);

/**
 * @fn		load_ucie_image
 * @brief	Load ucie firmware of ABEX-Core in each BLK_RBC for target chiplet.
 * @param	chiplet_id: The target chiplet id.
 * @param	base_addr:  The base address of the UCIE_SS.
 */
void load_ucie_image(const uint32_t chiplet_id, const uint64_t base_addr);

/**
 * @fn		wait_ucie_link_up
 * @brief	Wait link up state of each UCIe channel.
 * @param	chiplet_id: The target chiplet id.
 * @param	base_addr:  The base address of the UCIE_SS.
 */
void wait_ucie_link_up(const uint32_t chiplet_id, const uint64_t base_addr);

/**
 * @fn		load_and_enable_ucie_link_for_CP
 * @brief	Load AW UCIe FW and enable links for CP to access all chiplets.
 * @param	chiplet_id: The target chiplet id.
 * @param	base_addr:  The base address of the UCIE_SS.
 */
void load_and_enable_ucie_link_for_CP(const uint32_t bootmode);

/**
 * @fn		wait_ucie_link_up_for_CP
 * @brief	Wait until the links used by the CP are up.
 * @param	chiplet_id: The target chiplet id.
 * @param	base_addr:  The base address of the UCIE_SS.
 */
void wait_ucie_link_up_for_CP(void);

/**
 * @fn		ucie_link_up_for_others
 * @brief	Load AW UCIe FW and enable links for other blocks to access all chiplets.
 * @param	chiplet_id: The target chiplet id.
 * @param	base_addr:  The base address of the UCIE_SS.
 */
void ucie_link_up_for_others(void);

/**
 * @fn		set_remap_table
 * @brief	Set the chiplet routing table of each chiplet to the reset value.
 */
void set_remap_table(void);

/**
 * @fn		set_num_of_chips_and_rbc_for_ZEBU
 * @brief	Test whether each chiplet can be accessed through ukie link.
 */
void chiplet_access_test(void);
#endif /* REBEL_H_RBC_H */
