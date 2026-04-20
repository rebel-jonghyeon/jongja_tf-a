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
 * is a trade secret, of Rebellions.xp
 *
 * ANY REPRODUCTION, MODIFICATION, DISTRIBUTION, PUBLIC PERFORMANCE, OR PUBLIC DISPLAY OF OR
 * THROUGH USE OF THIS SOURCE CODE WITHOUT THE EXPRESS WRITTEN CONSENT OF REBELLIONS IS STRICTLY
 * PROHIBITED, AND IN VIOLATION OF APPLICABLE LAWS AND INTERNATIONAL TREATIES. THE RECEIPT OR
 * POSSESSION OF THIS SOURCE CODE AND/OR RELATED INFORMATION DOES NOT CONVEY OR IMPLY ANY RIGHTS
 * TO REPRODUCE, DISCLOSE OR DISTRIBUTE ITS CONTENTS, OR TO MANUFACTURE, USE, OR SELL ANYTHING
 * THAT IT MAY DESCRIBE, IN WHOLE OR IN PART.
 */

#ifndef __RL_EXT_SYNC_H__
#define __RL_EXT_SYNC_H__

#include <stdbool.h>
#include "rbln/spinlock.h"

#define SYNC_ID_MASK 0xff
#define HOST_SYNC_BIT 0x200
#define PUT_SYNC_BIT 0x100
#define MULTI_SYNC_BIT 0x1000

struct rl_ext_sync {
	uint64_t sync[2];
	spinlock_t lck;
};

void rl_ext_sync_init(struct rl_ext_sync *ext_sync);
bool rl_ext_sync_check(struct rl_ext_sync *ext_sync, uint64_t *bits);
bool rl_ext_sync_update(struct rl_ext_sync *ext_sync, uint64_t *bits);
void rl_ext_sync_send(struct rl_ext_sync *ext_sync, int sync);
bool rl_ext_sync_peek(struct rl_ext_sync *ext_sync, int sync);
#endif /* __RL_EXT_SYNC_H__ */
