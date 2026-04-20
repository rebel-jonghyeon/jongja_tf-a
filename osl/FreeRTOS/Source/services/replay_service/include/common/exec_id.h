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

#ifndef _CP_EXEC_ID_H_
#define _CP_EXEC_ID_H_

//#include "rbln/utils.h"
#include "rl_utils.h"
#include "hal/hw_spec.h"

union exec_id {
	struct __attribute__((packed, aligned(4))) {
		uint32_t	func_id		: BIT_WIDTH_ID_INFO_FUNC_ID;
		uint32_t	ctx_id		: BIT_WIDTH_ID_INFO_CTX_ID;
		uint32_t	proc_id		: BIT_WIDTH_ID_INFO_PROC_ID;
		uint32_t	cmd_id		: BIT_WIDTH_ID_INFO_CMD_ID;
	};
	uint32_t bits;
};

union proc_exec_id {
	struct  __attribute__((packed, aligned(4))) {
		uint8_t		func_id;	/* mapped to "function" in the terminology of SR-IOV */
		uint8_t		ctx_id;
		uint8_t		proc_id;	/* mapped to address space id */
		uint8_t		htid;
	};
	uint32_t bits;
};

#endif /* _CP_EXEC_ID_H_ */
