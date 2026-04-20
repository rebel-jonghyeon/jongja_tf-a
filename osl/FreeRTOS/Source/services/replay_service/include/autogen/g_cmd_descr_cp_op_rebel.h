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

#ifndef _G_CMD_DESCR_CP_OP_REBEL_H_
#define _G_CMD_DESCR_CP_OP_REBEL_H_
#include <stdint.h>

#define CMD_DESCR_CP_OP_ARCH_MAJOR 0
#define CMD_DESCR_CP_OP_ARCH_MINOR 9
#define CMD_DESCR_CP_OP_ARCH_PATCH 0

/* Constants: Bitfield size */
#define BIT_WIDTH_CMD_DESCR_CP_OP_PARA_ADDR	  40
#define BIT_WIDTH_CMD_DESCR_CP_OP_PARA_SIZE	  40
#define BIT_WIDTH_CMD_DESCR_CP_OP_INPUT_ADDR  40
#define BIT_WIDTH_CMD_DESCR_CP_OP_INPUT_SIZE  40
#define BIT_WIDTH_CMD_DESCR_CP_OP_RESERVED1	  16
#define BIT_WIDTH_CMD_DESCR_CP_OP_OUTPUT_ADDR 40
#define BIT_WIDTH_CMD_DESCR_CP_OP_OUTPUT_SIZE 40
#define BIT_WIDTH_CMD_DESCR_CP_OP_RESERVED2	  16
#define BIT_WIDTH_CMD_DESCR_CP_OP_TASK_CONF	  32

/* Constants: Byte Unit size */

/* Structure of register */
struct __attribute__((packed, aligned(4))) cmd_descr_para_conf {
	uint64_t para_addr : 40;
	uint64_t para_size : 40;
	uint64_t reserved : 16;
};

struct __attribute__((packed, aligned(4))) cmd_descr_ib_conf {
	uint64_t input_addr : 40;
	uint64_t input_size : 40;
	uint64_t reserved1 : 16;
};

struct __attribute__((packed, aligned(4))) cmd_descr_ob_conf {
	uint64_t output_addr : 40;
	uint64_t output_size : 40;
	uint64_t reserved2 : 16;
};

struct __attribute__((packed, aligned(4))) cmd_descr_cp_op {
	uint64_t task_conf : 32;
	struct cmd_descr_para_conf para_conf;
	struct cmd_descr_ib_conf ib_conf;
	struct cmd_descr_ob_conf ob_conf;
	uint64_t reserved : 32;
};

/* Constants: Possible enum value of field */
#endif /* _G_CMD_DESCR_CP_OP_REBEL_H_ */
