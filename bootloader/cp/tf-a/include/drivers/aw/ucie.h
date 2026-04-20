#pragma once
#include <stdint.h>
#include <stdbool.h>

#define BLK_RBC_V00_BASE		(0x1E05000000ULL)
#define BLK_RBC_V01_BASE		(0x1E05400000ULL)
#define BLK_RBC_V10_BASE		(0x1E05800000ULL)
#define BLK_RBC_V11_BASE		(0x1E05C00000ULL)
#define BLK_RBC_H00_BASE		(0x1E06000000ULL)
#define BLK_RBC_H01_BASE		(0x1E06400000ULL)

#define CMU_RBC_BASE_OFFSET		(0x00000)
#define SYSREG_RBC_BASE_OFFSET	(0x10000)
#define UCIE_SS_BASE_OFFSET		(0x20000)

/**
 * @fn		enable_ucie_core(const uint32_t chiplet_id, const uint64_t base_addr)
 * @brief	Initialize UCIE_SS and Release reset of IBEX-Core in each BLK_RBC for target chiplet.
 * @param	chiplet_id: The target chiplet id.
 * @param	base_addr:  The base address of the UCIE_SS.
 */
void enable_ucie_core(const uint32_t chiplet_id, const uint64_t base_addr);

/**
 * @fn		check_link_up(const uint32_t chiplet_id)
 * @brief	Check if link state is up or not.
 * @param	chiplet_id: The target chiplet id.
 * @param	base_addr:  The base address of the UCIE_SS.
 */
bool check_link_up(const uint32_t chiplet_id, const uint64_t base_addr);
