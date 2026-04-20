/*
 * [Rebellions Inc.]("Rebellions") CONFIDENTIAL
 * Unpublished Copyright (c) 2025 [Rebellions Inc.], All Rights Reserved.
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

#ifndef _RBCM_COMMON_H
#define _RBCM_COMMON_H

#define TIMEOUT_NS_DEFAULT (50000000U) /* 50ms */

/*
 * =================================================================================
 * Register Access Macros
 * =================================================================================
 */

#define rbcm_reg_writel(reg, n, v) \
	((reg)->n.value = (v))

#define rbcm_reg_readl(reg, n) \
	((reg)->n.value)

#define rbcm_reg_field_write(reg, n, f_n, f_v) \
	do { \
		taskENTER_CRITICAL(); \
		typeof((reg)->n) temp_reg_val; \
		temp_reg_val.value = (reg)->n.value; \
		temp_reg_val.f_n = (f_v); \
		(reg)->n.value = temp_reg_val.value; \
		taskEXIT_CRITICAL(); \
	} while (0)

/*
 * =================================================================================
 * RBCM_LOGX Macros
 * =================================================================================
 */

#define RBCM_LOGE(fmt, ...) printf("[E] " dev_fmt(fmt), ##__VA_ARGS__)
#define RBCM_LOGW(fmt, ...) printf("[W] " dev_fmt(fmt), ##__VA_ARGS__)
#define RBCM_LOGI(fmt, ...) printf("[I] " dev_fmt(fmt), ##__VA_ARGS__)
#define RBCM_LOGD(fmt, ...) printf("[D] " dev_fmt(fmt), ##__VA_ARGS__)
#define RBCM_PRINTF(fmt, ...) printf(fmt, ##__VA_ARGS__)

#endif /* _RBCM_COMMON_H */
