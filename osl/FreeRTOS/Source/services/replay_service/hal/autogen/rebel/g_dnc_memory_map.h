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

#ifndef _G_DNC_MEMORY_MAP_COMMON_H_
#define _G_DNC_MEMORY_MAP_COMMON_H_

#define ADDR_OFFSET_DNC_CONFIG	  0x00000000
#define ADDR_OFFSET_DNC_STATUS	  0x00000400
#define ADDR_OFFSET_DNC_TASK_32B  0x00000800

//EVT0
#define ADDR_OFFSET_DNC_TASK_16B  0x00000900

//EVT1
//#define ADDR_OFFSET_DNC_TASK_16B  0x00000300

#define ADDR_OFFSET_DNC_TASK_DONE 0x00000A00
#define ADDR_OFFSET_DNC_EXCEPTION 0x00000B00
#define ADDR_OFFSET_DNC_ADDRESS	  0x00000C00
#define ADDR_OFFSET_DNC_SYNC	  0x00000E00
#define ADDR_OFFSET_DNC_UAN		  0x00001000
#define ADDR_OFFSET_DNC_INIT_CFG  0x00000000
#endif /* _G_DNC_MEMORY_MAP_COMMON_H_*/
