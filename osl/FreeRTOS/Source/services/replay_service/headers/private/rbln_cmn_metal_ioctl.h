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

#ifndef _RBLN_CMN_METAL_IOCTL_H
#define _RBLN_CMN_METAL_IOCTL_H

/* Chip Info */
struct rbln_opt_die_info {
	union {
		struct {
			uint32_t id:5;
			uint32_t test_year:4;
			uint32_t test_week:6;
			uint32_t good_die:2;
			uint32_t fab_id:2;
			uint32_t reserved0:13;
		};
		uint32_t raw;
	} wafer;
	union {
		struct {
			uint32_t id2:8;
			uint32_t id1:8;
			uint32_t y_cord:8;
			uint32_t x_cord:8;
		};
		uint32_t raw;
	} lot_info0;
	union lot_info1 {
		struct {
			uint32_t id6:8;
			uint32_t id5:8;
			uint32_t id4:8;
			uint32_t id3:8;
		};
		uint32_t raw;
	} lot_info1;
};

struct rbln_opt_product_info {
	union {
		struct {
			uint32_t prod_id3:8;
			uint32_t prod_id2:8;
			uint32_t prod_id1:8;
			uint32_t prod_mn_cnt:4;
			uint32_t prod_type:1;
			uint32_t prod_rev:3;
		};
		uint32_t raw;
	} info0;
	union {
		struct {
			uint32_t reserved:8;
			uint32_t prod_id6:8;
			uint32_t prod_id5:8;
			uint32_t prod_id4:8;
		};
		uint32_t raw;
	} info1;
};

struct rbln_opt_soc_info {
	char chip_magic[16];
	char project_name[16];
	char chip_version[8];
	uint16_t zsbl_info_version;
} __attribute__((packed, aligned(4)));

/*
 * struct rbln_chip_info_v1
 *
 * @version: version of structure
 * @length: size of structure
 * @die_info: chip die info
 * @prod_info: chip product info
 * @board_version: board version for EVB, -1 otherwise
 * @board_type: board type, -1 otherwise
 */
struct rbln_chip_info_v1 {
	uint16_t version;
	uint16_t length;
	struct rbln_opt_die_info die_info;
	struct rbln_opt_product_info prod_info;
	struct rbln_opt_soc_info soc_info;
	int8_t board_version;
	int8_t board_type;
};

typedef struct rbln_chip_info_v1	rbln_chip_info_t;		/* alias */
#define RBLN_CHIP_INFO_MAX_LEN		128
#define RBLN_CHIP_INFO_LEN		sizeof(rbln_chip_info_t)
#define RBLN_CHIP_INFO_VER		1

#endif /* _RBLN_CMN_METAL_IOCTL_H */
