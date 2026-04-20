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

#ifndef _CMGR_IF_H_
#define _CMGR_IF_H_

#include <stdint.h>

typedef struct{
	uint32_t	func_id;		
	uint32_t    ctx_id;
    uint32_t    thread_id;
    uint32_t    cmd_id;
    uint32_t    affinity;
    uint32_t    notification;
    uint8_t     event_code_dnc;
    uint8_t     event_group_idx_dnc;
    uint8_t     event_group_idx_rbdma;
    uint8_t     cmd_type;
} __attribute__((packed)) cmgr_desc_t;


void cmgr_config(cmgr_desc_t desc_conf);
int cmgr_display_status(void);
void cmgr_init(uint32_t cl_id);
void cmgr_acc_count_clear(void);

void cmgr_workload_converter_init();

void cmgr_autofetch_run(uint64_t af_str_addr, uint32_t af_size);

#endif /* _CMGR_IF_H_ */
