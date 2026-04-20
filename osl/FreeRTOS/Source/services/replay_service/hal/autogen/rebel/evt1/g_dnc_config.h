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

#ifndef _G_DNC_CONFIG_EVT1_H_
#define _G_DNC_CONFIG_EVT1_H_

#define ADDR_OFFSET_DNC_CONFIG_PTHROT_ICPS_EN		0x09C
#define ADDR_OFFSET_DNC_CONFIG_PTHROT_ICPS_ADDR0L	0x0A0
#define ADDR_OFFSET_DNC_CONFIG_PTHROT_ICPS_ADDR0H	0x0A4
#define ADDR_OFFSET_DNC_CONFIG_PTHROT_ICPS_ADDR1L	0x0A8
#define ADDR_OFFSET_DNC_CONFIG_PTHROT_ICPS_ADDR1H	0x0AC
#define ADDR_OFFSET_DNC_CONFIG_PTHROT_ICPS_SMOOTHER 0x0B0
#define ADDR_OFFSET_DNC_CONFIG_PTHROT_ICPS_RECOVER	0x0B4
#define ADDR_OFFSET_DNC_CONFIG_PTHROT_ICPS_DELAY	0x0B8

union dnc_config_pthrot_icps_en {
	struct __attribute__((packed)) {
		uint32_t en : 32;
	};
	uint32_t bits;
};

union dnc_config_pthrot_icps_addr0l {
	struct __attribute__((packed)) {
		uint32_t addr : 32;
	};
	uint32_t bits;
};

union dnc_config_pthrot_icps_addr0h {
	struct __attribute__((packed)) {
		uint32_t addr : 16;
		uint32_t rsvd16 : 16;
	};
	uint32_t bits;
};

union dnc_config_pthrot_icps_addr1l {
	struct __attribute__((packed)) {
		uint32_t addr : 32;
	};
	uint32_t bits;
};

union dnc_config_pthrot_icps_addr1h {
	struct __attribute__((packed)) {
		uint32_t addr : 16;
		uint32_t rsvd16 : 16;
	};
	uint32_t bits;
};

union dnc_config_pthrot_icps_smoother {
	struct __attribute__((packed)) {
		uint32_t smth : 32;
	};
	uint32_t bits;
};

union dnc_config_pthrot_icps_recover {
	struct __attribute__((packed)) {
		uint32_t rcvry : 32;
	};
	uint32_t bits;
};

union dnc_config_pthrot_icps_delay {
	struct __attribute__((packed)) {
		uint32_t dly : 12;
		uint32_t rsvd20 : 20;
	};
	uint32_t bits;
};

enum dnc_config_ip_info1_min_ver {
	DNC_CONFIG_IP_INFO1_MIN_VER_DEV0,
	DNC_CONFIG_IP_INFO1_MIN_VER_DEV1,
	DNC_CONFIG_IP_INFO1_MIN_VER_DEV2,
	DNC_CONFIG_IP_INFO1_MIN_VER_DEV3,
	DNC_CONFIG_IP_INFO1_MIN_VER_DEV4,
	DNC_CONFIG_IP_INFO1_MIN_VER_DEV5,
};

enum dnc_config_ip_info1_maj_ver {
	DNC_CONFIG_IP_INFO1_MAJ_VER_ML1,
	DNC_CONFIG_IP_INFO1_MAJ_VER_ML2,
	DNC_CONFIG_IP_INFO1_MAJ_VER_ML3,
	DNC_CONFIG_IP_INFO1_MAJ_VER_ML4,
};

enum dnc_config_ip_info1_ip_ver {
	DNC_CONFIG_IP_INFO1_IP_VER_V0_0,
	DNC_CONFIG_IP_INFO1_IP_VER_V1_0,
	DNC_CONFIG_IP_INFO1_IP_VER_V1_1,
};

#endif /* _G_DNC_CONFIG_EVT1_H_*/
