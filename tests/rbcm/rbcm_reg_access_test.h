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

#ifndef __RBCM_REG_ACCESS_TEST_H
#define __RBCM_REG_ACCESS_TEST_H

#include <stdint.h>
#include "rbcm_driver.h"

enum access_type {
	RO = 0, /* Read Only */
	RW = 1, /* Read Write */
	WO = 2, /* Write Only */
};

struct rbcm_reg_access_test {
	uint64_t offset;
	uint32_t expected_value;
	uint32_t mask;
	enum access_type access;
	uint32_t test_val;
};

#define RBCM_REG_ACCESS_ENTRY(reg_name, access_type)       \
	{ .offset = (ADR_RBC_##reg_name),    \
	  .expected_value = (RST_##reg_name), \
	  .mask = (MASK_##reg_name), \
	  .access = (access_type), \
	  .test_val = (TEST_##reg_name) }

int32_t rbcm_run_reg_rst_test(enum rbcm_module idx);
int32_t rbcm_run_reg_acc_test(enum rbcm_module idx);

#endif /* __RBCM_REG_ACCESS_TEST_H */
