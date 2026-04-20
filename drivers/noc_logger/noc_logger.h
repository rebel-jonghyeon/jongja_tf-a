/*
 * Copyright 2025 Samsung Electronics Co., Ltd. All Rights Reserved.
 *
 * PROPRIETARY/CONFIDENTIAL
 *
 * This software is the confidential and proprietary information of Samsung
 * Electronics Co., Ltd. ("Confidential Information"). You shall not disclose such
 * Confidential Information and shall use it only in accordance with the terms of
 * the license agreement you entered into with Samsung Electronics Co., Ltd. (“SAMSUNG”).
 *
 * SAMSUNG MAKES NO REPRESENTATIONS OR WARRANTIES ABOUT THE SUITABILITY OF THE SOFTWARE,
 * EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, OR NON-INFRINGEMENT.
 *
 * SAMSUNG SHALL NOT BE LIABLE FOR ANY DAMAGES SUFFERED BY LICENSEE AS A RESULT OF USING,
 * MODIFYING OR DISTRIBUTING THIS SOFTWARE OR ITS DERIVATIVES.
 */

#pragma once

union noc_logger_id_coreid {
	struct {
		uint32_t coretypeid:8; /* [7:0] */
		uint32_t corechecksum:24; /* [31:8] */
	};
	uint32_t val;
};

union noc_logger_id_revisionid {
	struct {
		uint32_t userid:8; /* [7:0] */
		uint32_t flexnocid:24; /* [31:8] */
	};
	uint32_t val;
};

union noc_logger_faulten {
	struct {
		uint32_t faulten:1; /* [0:0] */
	};
	uint32_t val;
};

union noc_logger_errvld {
	struct {
		uint32_t errvld:1; /* [0:0] */
	};
	uint32_t val;
};

union noc_logger_errclr {
	struct {
		uint32_t errclr:1; /* [0:0] */
	};
	uint32_t val;
};

union noc_logger_errlog0 {
	struct {
		uint32_t lock:1; /* [0:0] */
		uint32_t opc:4; /* [4:1] */
		uint32_t reserved_bit_0:3;
		uint32_t errcode:3; /* [10:8] */
		uint32_t reserved_bit_1:5;
		uint32_t len1:12; /* [27:16] */
		uint32_t reserved_bit_2:3;
		uint32_t format:1; /* [31:31] */
	};
	uint32_t val;
};

union noc_logger_errlog1 {
	struct {
		uint32_t errlog1;
	};
	uint32_t val;
};

union noc_logger_errlog3 {
	struct {
		uint32_t errlog3;
	};
	uint32_t val;
};

union noc_logger_errlog4 {
	struct {
		uint32_t errlog4;
	};
	uint32_t val;
};

union noc_logger_errlog5 {
	struct {
		uint32_t errlog5;
	};
	uint32_t val;
};

union noc_logger_errlog6 {
	struct {
		uint32_t errlog6;
	};
	uint32_t val;
};

union noc_logger_errlog7 {
	struct {
		uint32_t errlog7:1; /* [0:0] */
	};
	uint32_t val;
};

union noc_logger_stallen {
	struct {
		uint32_t stallen:1; /* [0:0] */
	};
	uint32_t val;
};

struct noc_logger {
	union noc_logger_id_coreid id_coreid; /* offset : 0x0 */
	union noc_logger_id_revisionid id_revisionid; /* offset : 0x4 */
	union noc_logger_faulten faulten; /* offset : 0x8 */
	union noc_logger_errvld errvld; /* offset : 0xc */
	union noc_logger_errclr errclr; /* offset : 0x10 */
	union noc_logger_errlog0 errlog0; /* offset : 0x14 */
	union noc_logger_errlog1 errlog1; /* offset : 0x18 */
	uint32_t reserved_1;
	union noc_logger_errlog3 errlog3; /* offset : 0x20 */
	union noc_logger_errlog4 errlog4; /* offset : 0x24 */
	union noc_logger_errlog5 errlog5; /* offset : 0x28 */
	union noc_logger_errlog6 errlog6; /* offset : 0x2c */
	union noc_logger_errlog7 errlog7; /* offset : 0x30 */
	uint32_t reserved_3[6];
	union noc_logger_stallen stallen; /* offset : 0x4c */
};
