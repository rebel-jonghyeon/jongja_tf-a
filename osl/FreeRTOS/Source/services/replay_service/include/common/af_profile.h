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

#ifndef _AF_PROFILE_H_
#define _AF_PROFILE_H_
#include <stdint.h>

#define AF_MAX_PROFILE_EVENT_NUM 131072

enum af_profile_event {
	AF_CHECK_DEP,
	AF_FETCH_TRIGGER,
	AF_CHECK_HW_DONE,
	AF_HANDLER,
	AF_PROFILE_EVENT_NUM,
};

struct af_profile_log {
	uint64_t start_time;
	uint64_t duration;
	uint16_t cmd_id;
	uint32_t task_id;
	uint8_t cmd_type;
	enum af_profile_event evt_type;
};

#if defined(AF_PROFILE_ENABLED) && !defined(VDK)
void af_profile_reset(void);
void af_profile_log(enum af_profile_event evt_type, uint16_t cmd_id, uint8_t cmd_type);
void af_profile_log_start(enum af_profile_event evt_type);
#else
static inline void af_profile_reset(void) {}
static inline void af_profile_log(enum af_profile_event evt_type, uint16_t cmd_id, uint8_t cmd_type) {}
static inline void af_profile_log_start(enum af_profile_event evt_type) {}
#endif /* AF_PROFILE_ENABLED && !VDK */
#endif /* _AF_PROFILE_H_ */
