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

#ifndef _AUTOFETCH_H_
#define _AUTOFETCH_H_
#include <stdint.h>
#include "hal/hw_spec.h"

#define UNIT_CMD_BUFFER_SIZE	(32*2048)
#define AUTOFETCH_BASE_OFFSET	(0x40000000 + 32*16)

/* Chiplet-specific base addresses */
#define AUTOFETCH_BASE_ADDR_CL(x)	(cl_base[(x)] + AUTOFETCH_BASE_OFFSET)
#define AF_COMP_BASE_ADDR_CL(x, id)		(AUTOFETCH_BASE_ADDR_CL(x) + id*UNIT_CMD_BUFFER_SIZE)
#define AF_LDUDMA_BASE_ADDR_CL(x, id)	(AUTOFETCH_BASE_ADDR_CL(x) + id*UNIT_CMD_BUFFER_SIZE + UNIT_CMD_BUFFER_SIZE*16)
#define AF_LPUDMA_BASE_ADDR_CL(x, id)	(AUTOFETCH_BASE_ADDR_CL(x) + id*UNIT_CMD_BUFFER_SIZE + UNIT_CMD_BUFFER_SIZE*32)
#define AF_STUDMA_BASE_ADDR_CL(x, id)	(AUTOFETCH_BASE_ADDR_CL(x) + id*UNIT_CMD_BUFFER_SIZE + UNIT_CMD_BUFFER_SIZE*48)
#define AF_RBDMA_BASE_ADDR_CL(x)		(AUTOFETCH_BASE_ADDR_CL(x) + UNIT_CMD_BUFFER_SIZE*4*16)
#define AF_CMGR_BASE_ADDR_CL(x)		(AUTOFETCH_BASE_ADDR_CL(x) + \
					UNIT_CMD_BUFFER_SIZE*4*16 + UNIT_CMD_BUFFER_SIZE)

/* Legacy macros for backward compatibility (use current chiplet) */
#define AUTOFETCH_BASE_ADDR	(cl_base[cur_cl_id] + AUTOFETCH_BASE_OFFSET)
#define AF_COMP_BASE_ADDR(id)		(AUTOFETCH_BASE_ADDR + id*UNIT_CMD_BUFFER_SIZE)
#define AF_LDUDMA_BASE_ADDR(id)		(AUTOFETCH_BASE_ADDR + id*UNIT_CMD_BUFFER_SIZE + UNIT_CMD_BUFFER_SIZE*16)
#define AF_LPUDMA_BASE_ADDR(id)		(AUTOFETCH_BASE_ADDR + id*UNIT_CMD_BUFFER_SIZE + UNIT_CMD_BUFFER_SIZE*32)
#define AF_STUDMA_BASE_ADDR(id)		(AUTOFETCH_BASE_ADDR + id*UNIT_CMD_BUFFER_SIZE + UNIT_CMD_BUFFER_SIZE*48)
#define AF_RBDMA_BASE_ADDR			(AUTOFETCH_BASE_ADDR + UNIT_CMD_BUFFER_SIZE*4*16)
#define AF_CMGR_BASE_ADDR			(AUTOFETCH_BASE_ADDR + UNIT_CMD_BUFFER_SIZE*4*16 + UNIT_CMD_BUFFER_SIZE)

#endif
/*
 * _AUTOFETCH_H_
 */
