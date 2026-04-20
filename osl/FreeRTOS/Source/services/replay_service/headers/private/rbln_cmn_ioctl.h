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

#ifndef _RBLN_CMN_IOCTL_H
#define _RBLN_CMN_IOCTL_H

#include <stdint.h>

/*
 * struct rbln_fw_image_info_v1
 *
 * @version: version of structure
 * @length: size of structure
 * @image_magic: REBELLIONS.AI
 * @major: major version number
 * @minor: minor version number
 * @patch_lebel: patch level
 * @dirty: indicate modified or clean
 * @build_type: type of build - release, performance, debug
 * @builder: who built the firmware
 * @build_date: date of fw build
 * @git_sha: git sha
 */

struct rbln_fw_image_info_v1 {
	uint16_t version;
	uint16_t length;
	uint64_t image_magic[2];
	uint8_t major;
	uint8_t minor;
	uint8_t patch_level;
	uint8_t dirty;
	char git_sha[8];
	char build_type[16];
	char builder[32];
	char build_date[32];
	char build_desc[32];
};

/* Alias */
typedef struct rbln_fw_image_info_v1	rbln_fw_image_info_t;
#define RBLN_FW_IMAGE_INFO_LEN		sizeof(rbln_fw_image_info_t)
/* Current version of rbln_fw_image_info_t */
#define RBLN_FW_IMAGE_INFO_VER		1

/*
 * struct rbln_log_ctrbln_v1
 *
 * @header: header
 * @level: log level
 * @clear: clear log
 */
enum rbln_log_level {
	RBLN_LOG_ERR,
	RBLN_LOG_INFO,
	RBLN_LOG_DBG,
	RBLN_LOG_VERBOSE,
};

struct rbln_log_ctrbln_v1 {
	uint32_t header;
	uint32_t clear;
	uint32_t level;		/* Plus one to level to indicate log level change */
};

/* Alias */
typedef struct rbln_log_ctrbln_v1	rbln_log_ctrbln_t;
#define RBLN_LOG_CTRBLN_LEN		sizeof(rbln_log_ctrbln_t)

struct rbln_proc_info {
	uint32_t proc_id;
	uint32_t htid;
	uint32_t func_id;
	uint32_t asid;
	uint32_t ptid;
	uint32_t ci;
	uint32_t pi;
	uint32_t proc_state;
};

#endif /* _RBLN_CMN_IOCTL_H */
