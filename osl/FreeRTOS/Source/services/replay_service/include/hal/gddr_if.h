/*
 * [Rebellions Inc.]("Rebellions") CONFIDENTIAL
 * Unpublished Copyright (c) 2021-2023 [Rebellions Inc.], All Rights Reserved.
 *
 * NOTICE: All information contained herein is, and remains the property of Rebellions.
 * The intellectual and technical concepts contained herein are proprietary to Rebellions
 * and may be covered by Republic of Korea, U.S., and other countries' Patents, patents
 * in process, and are protected by trade secret or copyright law.
 *
 * Dissemination of this information or reproduction of this material is strictly forbidden
 * unless prior written permission is obtained from Rebellions. Access to the source code
 * contained herein is hereby forbidden to anyone except current Rebellions employees, managers
 * or contractors who have executed Confidentiality and Non-disclosure agreements explicitly
 * covering such access.
 *
 * The copyright notice above does not evidence any actual or intended publication or disclosure
 * of this source code, which includes information that is confidential and/or proprietary, and
 * is a trade secret, of Rebellions.
 *
 * ANY REPRODUCTION, MODIFICATION, DISTRIBUTION, PUBLIC PERFORMANCE, OR PUBLIC DISPLAY OF OR
 * THROUGH USE OF THIS SOURCE CODE WITHOUT THE EXPRESS WRITTEN CONSENT OF REBELLIONS IS STRICTLY
 * PROHIBITED, AND IN VIOLATION OF APPLICABLE LAWS AND INTERNATIONAL TREATIES. THE RECEIPT OR
 * POSSESSION OF THIS SOURCE CODE AND/OR RELATED INFORMATION DOES NOT CONVEY OR IMPLY ANY RIGHTS
 * TO REPRODUCE, DISCLOSE OR DISTRIBUTE ITS CONTENTS, OR TO MANUFACTURE, USE, OR SELL ANYTHING
 * THAT IT MAY DESCRIBE, IN WHOLE OR IN PART.
 */

#ifndef _CP_GDDR_IF_H
#define _CP_GDDR_IF_H

#define RL_GDDR6_INT_STATUS_MASTER		(0x354)
#define RL_GDDR6_INT_STATUS_TIMEOUT		(0x35C)
#define RL_GDDR6_INT_STATUS_ECC			(0x360)
#define RL_GDDR6_INT_STATUS_LOWPOWER	(0x364)
#define RL_GDDR6_INT_STATUS_USERIF		(0x370)
#define RL_GDDR6_INT_STATUS_CRC			(0x374)
#define RL_GDDR6_INT_STATUS_CRC_ERR_ON_READ	((0x1 << 2) << 24)
#define RL_GDDR6_INT_STATUS_CRC_ERR_ON_WRITE	((0x1 << 0) << 24)
#define RL_GDDR6_INT_STATUS_BIST		(0x374)
#define RL_GDDR6_INT_STATUS_MISC		(0x374)
#define RL_GDDR6_INT_STATUS_INIT		(0x378)
#define RL_GDDR6_INT_STATUS_FREQ		(0x378)
#define RL_GDDR6_INT_STATUS_DFI			(0x378)
#define RL_GDDR6_INT_STATUS_PARITY		(0x37C)
#define RL_GDDR6_INT_STATUS_MODE		(0x37C)
#define RL_GDDR6_INT_MASK_TIMEOUT		(0xFFFFFFFF)
#define RL_GDDR6_INT_MASK_ECC			(0xFFFFFFFF)
#define RL_GDDR6_INT_MASK_LOWPOWER		(0xFFFF)
#define RL_GDDR6_INT_MASK_USERIF		(0xFFFFFFFF)
#define RL_GDDR6_INT_MASK_CRC			(0xFFu << 24)
#define RL_GDDR6_INT_MASK_BIST			(0xFF << 16)
#define RL_GDDR6_INT_MASK_MISC			(0xFFFF)
#define RL_GDDR6_INT_MASK_INIT			(0xFFu << 24)
#define RL_GDDR6_INT_MASK_FREQ			(0xFF << 16)
#define RL_GDDR6_INT_MASK_DFI			(0xFF)
#define RL_GDDR6_INT_MASK_PARITY		(0xFF << 8)
#define RL_GDDR6_INT_MASK_MODE			(0xFF)

#define RL_GDDR6_CRC_WR_ERR_ADDR_LOW	(0x2E8)
#define RL_GDDR6_CRC_WR_ERR_ADDR_HIGH	(0x2EC)
#define RL_GDDR6_CRC_RD_ERR_ADDR_LOW	(0x2F0)
#define RL_GDDR6_CRC_RD_ERR_ADDR_HIGH	(0x2F4)

#define RL_GDDR6_INT_STATUS_TIMEOUT_ERRMASK		(0x000F4000)
	// Bit [19] = The auto-refresh max deficit timeout has expired.
	// Bit [18] = The low power interface wakeup timeout has expired.
	// Bit [17] = The low power interface wakeup timeout has expired.
	// Bit [16] = The DFI update FM timeout has expired.
	// Bit [14] = The MRR temperature check FM timeout has expired.
#define RL_GDDR6_INT_STATUS_ECC_ERRMASK			(0x0000004C)
	// Bit [8] = An ECC correctable error has been detected in a scrubbing read operation.
	// Bit [7] = The scrub operation triggered by setting the ecc_scrub_start parameter has
	//		completed.
	// Bit [6] = One or more ECC writeback commands could not be executed.
	// Bit [3] = Multiple uncorrectable ECC events have been detected.
	// Bit [2] = A uncorrectable ECC event has been detected.
	// Bit [1] = Multiple correctable ECC events have been detected.
	// Bit [0] = A correctable ECC event has been detected.
#define RL_GDDR6_INT_STATUS_LOWPOWER_ERRMASK	(0x00000008)
	// Bit [3] = A Low Power Interface (LPI) timeout error has occurred.
	// Bit [0] = The low power operation has been completed.
#define RL_GDDR6_INT_STATUS_USERIF_ERRMASK		(0x000000C7)
	// Bit [7] = The user has programmed an invalid setting associated with core words per burst.
	//		Examples: Setting the mem_dp_reduction parameter when burst length is 2 or
	//		specifying a 1:2 MC:PHY clock ratio when burst length is 2.
	// Bit [6] = A wrap cycle crossing a DRAM page has been detected.
	//		This is unsupported and may result in memory data corruption.
	// Bit [2] = An error occurred on the port command channel.
	// Bit [1] = Multiple accesses outside the defined PHYSICAL memory space have occurred.
	// Bit [0] = A memory access outside the defined PHYSICAL memory space has occurred.
#define RL_GDDR6_INT_STATUS_CRC_FATAL_ERRMASK			(0x1D << 24)
#define RL_GDDR6_INT_STATUS_CRC_NONFATAL_ERRMASK		(0x18 << 24)
	// Bit [4] = A read CRC error occurred during CRC retry.
	// Bit [3] = A write CRC error occurred during CRC retry.
	// Bit [2] = A CRC error occurred on the read data bus.
	// Bit [0] = A CRC error occurred on the write data bus.
#define RL_GDDR6_INT_STATUS_BIST_ERRMASK		(0x00 << 16)
	// Bit [0] = The BIST operation has been completed.
#define RL_GDDR6_INT_STATUS_MISC_ERRMASK		(0x0000)
	// Bit [11] = The sw requested refresh operation has resulted in a status bit being set.
	// Bit [7] = The refresh operation has resulted in a status bit being set.
	// Bit [3] = The assertion of the inhibit_dram_cmd parameter has successfully inhibited
	//		the command queue and/or MRR traffic.
#define RL_GDDR6_INT_STATUS_INIT_ERRMASK		(0x00 << 24)
	// Bit [3] = The state machine is in the power on software initialization state
	//		during initialization.
	// Bit [1] = The MC initialization has been completed.
	// Bit [0] = The memory reset is valid on the DFI bus.
#define RL_GDDR6_INT_STATUS_FREQ_ERRMASK		(0x7F << 16)	// DFS is not performed as of now
	// Bit [6] = Set when the DFS state machine reaches a state to wait for software
	//		and param_wait_for_sw_after_dfs = 1. Clear to zero to move on.
	// Bit [5] = A DFS operation initiated by software completed.
	// Bit [4] = The DFS operation initiated by the software interface was terminated
	//		because the PHY did not de-assert the dfi_init_complete signal within the
	//		time specified in the tdfi_init_start_fN parameter after the controller
	//		asserted the dfi_init_start signal during a DFS operation.
	// Bit [3] = The DFS request from software was ignored because the dfs_enable parameter
	//		is cleared to ’b0, the memory was still initializing, or the DQS oscillator was
	//		in progress.
	// Bit [2] = A DFS operation initiated by the hardware interface completed.
	// Bit [1] = The DFS operation initiated by the hardware interface was terminated because
	//		the PHY did not de-assert the dfi_init_complete signal within the time specified
	//		in the tdfi_init_start_fN parameter after the controller asserted the dfi_init_start
	//		signal during a DFS operation.
	// Bit [0] = The DFS request from the hardware interface was ignored because the dfs_enable
	//		parameter is cleared to ’b0, the memory was still initializing,
	//		or the DQS oscillator was in progress.
#define RL_GDDR6_INT_STATUS_DFI_ERRMASK			(0x3F)
	// Bit [5] = The DFI tinit−complete value has timed out. This value is specified in the
	//		dfi_init_complete parameter.
	// Bit [4] = The user-initiated DLL resynchronization has completed.
	// Bit [3] = A state change has been detected on the dfi_init_complete signal after
	//		initialization.
	// Bit [2] = Error received from the PHY on the DFI bus.
	// Bit [1] = A DFI PHY Master Interface error has occurred. Error information can be found in
	//		the phymstr_ error_status parameter.
	// Bit [0] = A DFI update error has occurred. Error information can be found in
	//		the update_error_status parameter.
#define RL_GDDR6_INT_STATUS_PARITY_ERRMASK		(0x00000003 << 8)
	// Bit [1] = An overlapping write data parity error has been detected at the memory controller
	//		boundary.
	// Bit [0] = A write data parity error has been detected.
#define RL_GDDR6_INT_STATUS_MODE_ERRMASK		(0x00000001)
	// Bit [3] = The register interface-initiated mode register write has completed and another
	//		mode register write may be issued.
	// Bit [2] = The requested mode register read has completed. The chip and data can be read in
	//		the peripheral_ mrr_data parameter.
	// Bit [0] = An MRR error has occurred. Error information can be found in the mrr_error_status
	//		parameter.


#define RL_GDDR6_INT_ACK_OFFSET			(0x24)

enum RL_GDDR6_INT_MASTER_BIT {
	RL_GDDR6_INT_TIMEOUT = 0,
	RL_GDDR6_INT_ECC = 1,
	RL_GDDR6_INT_LOWPOWER = 2,
	RL_GDDR6_INT_USERIF = 6,
	RL_GDDR6_INT_MISC = 7,
	RL_GDDR6_INT_BIST = 8,
	RL_GDDR6_INT_CRC = 9,
	RL_GDDR6_INT_DFI = 10,
	RL_GDDR6_INT_FREQ = 12,
	RL_GDDR6_INT_INIT = 13,
	RL_GDDR6_INT_MODE = 14,
	RL_GDDR6_INT_PARITY = 15,
};

void init_gddr_error_handler(void);

/* WRITE MR REQ */
#define RL_GDDR6_CTL_100_ADDR			(0x190)
#define CTL_100_MRNUM_MASK				RL_GENMASK(7, 0)
#define CTL_100_CS_MASK					RL_GENMASK(15, 8)
#define CTL_100_MRW_TYPE_MASK			RL_GENMASK(23, 16)
#define CTL_100_ALLCS_MASK				RL_GENMASK(24, 24)
#define CTL_100_TRIG_MASK				RL_GENMASK(25, 25)

/* READ MR REQ */
#define RL_GDDR6_CTL_101_ADDR			(0x194)
#define CTL_101_MRNUM_MASK				RL_GENMASK(15, 8)
#define CTL_101_CS_MASK					RL_GENMASK(23, 16)
#define CTL_101_TRIG_MASK				RL_GENMASK(24, 24)

/* READ MR DATA */
#define RL_GDDR6_CTL_102_ADDR			(0x198)

/* WRITE MR DATA */
#define RL_GDDR6_CTL_107_ADDR			(0x1ac)
#define CTL_107_BIST_GO_MASK			RL_GENMASK(16, 16)
#define CTL_107_MRSINGLE_DATA_0_MASK	RL_GENMASK(11, 0)

#define RL_GDDR6_CTL_184_ADDR			(0x2e0)
#define CTL_184_CRC_RETRY_EN_MASK		RL_GENMASK(8, 8)

#define RL_GDDR6_CTL_223_ADDR			(0x37c)
#define CTL_223_INT_STATUS_PARITY_MASK	RL_GENMASK(15, 8)
#define CTL_223_INT_STATUS_MODE_MASK	RL_GENMASK(7, 0)
#define CTL_223_INT_STATUS_MODE_WR_DONE	0x8
#define CTL_223_INT_STATUS_MODE_RD_DONE	0x4

#define RL_GDDR6_CTL_232_ADDR			(0x3a0)
#define CTL_232_INT_ACK_PARITY_MASK		RL_GENMASK(15, 8)
#define CTL_232_INT_ACK_MODE_MASK		RL_GENMASK(7, 0)

#define RL_GDDR6_MEM_MR3_DRAM_INFO_OFF				0x0
#define RL_GDDR6_MEM_MR3_DRAM_INFO_VID1				0x1
#define RL_GDDR6_MEM_MR3_DRAM_INFO_TEMP_READ_OUT	0x2
#define RL_GDDR6_MEM_MR3_DRAM_INFO_VID2				0x3

/* PHY registers */
/* Cadence document shows that phy register offset is based on
 * CTRL_BASE not PHY_BASE so we need subtract 0x4000
 * which is PHY_BASE_OFFSET from CTRL_BASE
 */
#define RL_GDDR6_PHY_4097_ADDR			(0x4004) /* e.g. 0x8004 - 0x4000 */
#define RL_GDDR6_PHY_INT_ACK			(0x4228)
#define RL_GDDR6_PHY_INT_STATUS			(0x4230)
#define PHY_4097_PHY_PI_DARRAY0_3_MASK	RL_GENMASK(27, 16)

void gddr_readnsave_temp_all(void);
int gddr_get_temp(int channel, int sub_ch, int *temp);
#endif /* _CP_GDDR_IF_H */
