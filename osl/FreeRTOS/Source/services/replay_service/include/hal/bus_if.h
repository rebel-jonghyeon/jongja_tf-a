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

#ifndef _CP_BUS_IF_H
#define _CP_BUS_IF_H

#include "rbln/utils.h"

#define CBUS_ERRORLOGGER_OFFSET			(0)
#define DBUS_READ_ERRORLOGGER_OFFSET	(0x1000)
#define DBUS_WRITE_ERRORLOGGER_OFFSET	(0x1000)
#define DBUS_READ_SIDEBAND_OFFSET		(0x5000)
#define DBUS_WRITE_SIDEBAND_OFFSET		(0x5000)

#define RL_BUS_SIDEBAND_FAULTEN_OFFSET		(0x8)
#define RL_BUS_SIDEBAND_FLAGINEN0_OFFSET	(0x10)

#define RL_BUS_FAULTEN_OFFSET		(0x8)
#define RL_BUS_ERRVID_OFFSET		(0xC)
#define RL_BUS_ERRCLR_OFFSET		(0x10)
#define RL_BUS_ERRLOG0_OFFSET		(0x14)
#define RL_BUS_ERRLOG1_OFFSET		(0x18)
#define RL_BUS_ERRLOG3_OFFSET		(0x20)
#define RL_BUS_ERRLOG4_OFFSET		(0x24)
#define RL_BUS_ERRLOG5_OFFSET		(0x28)
#define RL_BUS_ERRLOG6_OFFSET		(0x2C)

#define RL_BUS_TMO_PERIOD_OFFSET	(0x4)
#define RL_BUS_TMO_EN_OFFSET		(0x8)

/* timeout period 0x10000 * 128 ticks = 8M tick = 8ms (BUS 1GHz) */
#define RL_BUS_TMO_PERIOD			(0x10000)

#define RL_NOC_IDLE_EN		(1)
#define RL_NOC_IDLE_DIS		(0)

enum RL_ENUM_NOC {
	RL_NOC_BUS = 0,
	RL_NOC_CPU,
	RL_NOC_DC0,
	RL_NOC_DC1,
	RL_NOC_DRAM0,
	RL_NOC_DRAM1,
	RL_NOC_DRAM2,
	RL_NOC_DRAM3,
	RL_NOC_PCIE,
	RL_NOC_PERI,
	RL_NOC_ROT,
	RL_NOC_MAX,
};
void rl_init_bus(void);
void rl_enable_noc_idle(enum RL_ENUM_NOC idx);
void rl_disable_noc_idle(enum RL_ENUM_NOC idx);
uint32_t rl_get_noc_idle_status(enum RL_ENUM_NOC idx);

#endif /* _CP_BUS_IF_H */
