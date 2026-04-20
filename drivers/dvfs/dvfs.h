/*
 * Copyright 2025 Samsung Electronics Co, Ltd. All Rights Reserved.
 *
 * PROPRIETARY/CONFIDENTIAL
 *
 * This software is the confidential and proprietary information of
 * Samsung Electronics Co., Ltd. ("Confidential Information").
 * You shall not disclose such Confidential Information and shall use it only
 * in accordance with the terms of the license agreement you entered into with
 * Samsung Electronics Co., Ltd. ("SAMSUNG").
 *
 * SAMSUNG MAKES NO REPRESENTATIONS OR WARRANTIES ABOUT THE SUITABILITY OF
 * THE SOFTWARE, EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, OR
 * NON-INFRINGEMENT. SAMSUNG SHALL NOT BE LIABLE FOR ANY DAMAGES SUFFERED BY
 * LICENSEE AS A RESULT OF USING, MODIFYING OR DISTRIBUTING THIS SOFTWARE OR
 * ITS DERIVATIVES.
 *
 */

#define ADDR_MASK				0x7FFFFFFFFFULL
#define CHIPLET_BASE_OFFSET		0x2000000000ULL
#define VDD_CP_CHIPLET02		0x72
#define VDD_CP_CHIPLET13		0x73
#define VDD_DCL					0x30
#define VDD_DCL_ODD				0x32

struct get_pll_info {
	uint64_t vals[4];
};

struct dvfs_info {
	uint64_t freq[2][4];
	uint32_t vout[2];
};

struct dvfs_entry {
	uint32_t freq_mhz;
	uint32_t vout_mv;
	uint32_t freq_numeric;
};

enum dvfs_domain {
	DVFS_DOMAIN_CP,
	DVFS_DOMAIN_DNC,
};

int set_dvfs_lvl(uint32_t domain, uint32_t lvl);
int get_dvfs_lvl(uint32_t domain, struct dvfs_info *info);

extern struct dvfs_entry cp_dvfs_table[];
extern struct dvfs_entry dnc_dvfs_table[];
