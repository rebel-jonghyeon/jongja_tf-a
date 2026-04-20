/*
 * [Rebellions Inc.]("Rebellions") CONFIDENTIAL
 * Unpublished Copyright (c) 2021-2025 [Rebellions Inc.], All Rights Reserved.
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

#ifndef _COMMAND_H_
#define _COMMAND_H_

#define MAX_CMD_CNT 240000	/* llama 7b full layer enc + dec total cmd cnt */

#define MAX_CMD_ID 0xF7FF

#define MAX_SUBTASK_TYPE_NUM 2
#define SUBTASK_TYPE_UDMA 0
#define SUBTASK_TYPE_RBDMA 1

#define MAX_SUBTASK_NUM 1024

#define RBDMA_SUBTASK_ID_MASK 0x03FF
#define RBDMA_SUBTASK_ID_MIN 0xFC00
#define RBDMA_SUBTASK_ID_MAX 0xFFFF

#define UDMA_SUBTASK_ID_MASK 0x03FF
#define UDMA_SUBTASK_ID_MIN 0xF800
#define UDMA_SUBTASK_ID_MAX 0xFBFF

#endif /* _COMMAND_H_ */