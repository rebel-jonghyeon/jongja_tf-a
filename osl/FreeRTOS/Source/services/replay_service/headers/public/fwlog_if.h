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

#ifndef FWLOG_IF_H
#define FWLOG_IF_H

#ifdef __REBEL_FW__
#include <stdint.h>
#include "rl_utils.h"

typedef uint64_t	__le64;
typedef uint32_t	__le32;
typedef uint16_t	__le16;

typedef uint8_t		__u8;
typedef int8_t		__s8;
#else
#include <linux/types.h>
#endif /* __REBEL_FW__ */

/* FW_SYNC : below should be sync with FW */
#define RBLN_TASK_NAME_LEN	16u
#define RBLN_LOGTYPE_NAME_LEN	8u
#define RBLN_LOG_STR_LEN	100u

#pragma pack(push, 4)
struct rbln_fwlog {
	__le64 tick;
	__u8 type;
	__u8 cpu;
	__u8 func_id;
	__u8 rsvd;
	__s8 task[RBLN_TASK_NAME_LEN];
	__s8 logstr[RBLN_LOG_STR_LEN];
};
#pragma pack(pop)

/* H2D_SHARE - located at CTX_CFG_BASE + 0x2B00 */
struct rbln_logbuf_info {
	__le32 magic_code;	/* magic code to check whether logbuf is ready */
	__le32 base_addr;	/* rbln_fwlog struct address (fixed) */
	__le32 item_cnt;	/* logbuf array total item count */
	__le32 item_size;	/* logbuf array each item size - for double check */
	__le32 wi;		/* write index - FW will update */
	__le32 ri;		/* read index - driver will update */
};

#endif /* FWLOG_IF_H */
