/*
 * [Rebellions Inc.]("Rebellions") CONFIDENTIAL
 * Unpublished Copyright (c) 2021-2024 [Rebellions Inc.], All Rights Reserved.
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

#ifndef _G_SYSFW_ADDRMAP_H_
#define _G_SYSFW_ADDRMAP_H_

#define DRAM_SYSTEM_MEMORY_BASE			0x000000000
#define BL31_CP0_BASE					0x000000000
#define FW_CP0_BASE						0x000200000
#define PLATFORM_LOAD_IMAGE_BASE		0x00FE00000
#define QUAD_CL_BOOTDONE_MASK			0x00FE00000
#define LOG_BUF_BASE					0x020000000
#define DEVICE_COMMUNICATION_SPACE_BASE 0x010200000
#define BOOTLOADER_LOG_DUMP				0x0102FE000
#define CORE_DUMP						0x0102FF000
#define VSERIAL							0x010300000
#define MMU_PT_BASE						0x010400000
#define SMMU_PCIE_PT_BASE				0x014000000
#define BL31_CP1_BASE					0x014100000
#define FW_CP1_BASE						0x014200000
#define HOST_READ_ONLY_REGION_BASE		0x03E000000
#define ROT_RESERVED_BASE				0x03F000000
#define DRAM_USER_BASE					0x040000000
#endif /* _G_SYSFW_ADDRMAP_H_ */
