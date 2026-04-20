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

#ifndef _G_DNC_INIT_CFG_COMMON_H_
#define _G_DNC_INIT_CFG_COMMON_H_

#define ADDR_OFFSET_DNC_INIT_CFG_CFG00A 0x000
#define ADDR_OFFSET_DNC_INIT_CFG_CFG00D 0x004
#define ADDR_OFFSET_DNC_INIT_CFG_CFG01A 0x008
#define ADDR_OFFSET_DNC_INIT_CFG_CFG01D 0x00C
#define ADDR_OFFSET_DNC_INIT_CFG_CFG02A 0x010
#define ADDR_OFFSET_DNC_INIT_CFG_CFG02D 0x014
#define ADDR_OFFSET_DNC_INIT_CFG_CFG03A 0x018
#define ADDR_OFFSET_DNC_INIT_CFG_CFG03D 0x01C
#define ADDR_OFFSET_DNC_INIT_CFG_CFG04A 0x020
#define ADDR_OFFSET_DNC_INIT_CFG_CFG04D 0x024
#define ADDR_OFFSET_DNC_INIT_CFG_CFG05A 0x028
#define ADDR_OFFSET_DNC_INIT_CFG_CFG05D 0x02C
#define ADDR_OFFSET_DNC_INIT_CFG_CFG06A 0x030
#define ADDR_OFFSET_DNC_INIT_CFG_CFG06D 0x034
#define ADDR_OFFSET_DNC_INIT_CFG_CFG07A 0x038
#define ADDR_OFFSET_DNC_INIT_CFG_CFG07D 0x03C

union dnc_init_cfg_cfg00a {
	struct __attribute__((packed)) {
		uint32_t addr : 32;
	};
	uint32_t bits;
};

union dnc_init_cfg_cfg00d {
	struct __attribute__((packed)) {
		uint32_t data : 32;
	};
	uint32_t bits;
};

union dnc_init_cfg_cfg01a {
	struct __attribute__((packed)) {
		uint32_t addr : 32;
	};
	uint32_t bits;
};

union dnc_init_cfg_cfg01d {
	struct __attribute__((packed)) {
		uint32_t data : 32;
	};
	uint32_t bits;
};

union dnc_init_cfg_cfg02a {
	struct __attribute__((packed)) {
		uint32_t addr : 32;
	};
	uint32_t bits;
};

union dnc_init_cfg_cfg02d {
	struct __attribute__((packed)) {
		uint32_t data : 32;
	};
	uint32_t bits;
};

union dnc_init_cfg_cfg03a {
	struct __attribute__((packed)) {
		uint32_t addr : 32;
	};
	uint32_t bits;
};

union dnc_init_cfg_cfg03d {
	struct __attribute__((packed)) {
		uint32_t data : 32;
	};
	uint32_t bits;
};

union dnc_init_cfg_cfg04a {
	struct __attribute__((packed)) {
		uint32_t addr : 32;
	};
	uint32_t bits;
};

union dnc_init_cfg_cfg04d {
	struct __attribute__((packed)) {
		uint32_t data : 32;
	};
	uint32_t bits;
};

union dnc_init_cfg_cfg05a {
	struct __attribute__((packed)) {
		uint32_t addr : 32;
	};
	uint32_t bits;
};

union dnc_init_cfg_cfg05d {
	struct __attribute__((packed)) {
		uint32_t data : 32;
	};
	uint32_t bits;
};

union dnc_init_cfg_cfg06a {
	struct __attribute__((packed)) {
		uint32_t addr : 32;
	};
	uint32_t bits;
};

union dnc_init_cfg_cfg06d {
	struct __attribute__((packed)) {
		uint32_t data : 32;
	};
	uint32_t bits;
};

union dnc_init_cfg_cfg07a {
	struct __attribute__((packed)) {
		uint32_t addr : 32;
	};
	uint32_t bits;
};

union dnc_init_cfg_cfg07d {
	struct __attribute__((packed)) {
		uint32_t data : 32;
	};
	uint32_t bits;
};

#endif /* _G_DNC_INIT_CFG_COMMON_H_*/
