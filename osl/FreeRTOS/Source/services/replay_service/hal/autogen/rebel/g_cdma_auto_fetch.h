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

#ifndef _G_CDMA_AUTO_FETCH_COMMON_H_
#define _G_CDMA_AUTO_FETCH_COMMON_H_

#define ADDR_OFFSET_RBDMA_PROC0_PTR			 0x000
#define ADDR_OFFSET_RBDMA_PROC0_PTR_BYTESIZE 0x004
#define ADDR_OFFSET_RBDMA_PROC0_RSV			 0x008
#define ADDR_OFFSET_RBDMA_PROC0_STATUS		 0x00C
#define ADDR_OFFSET_RBDMA_PROC1_PTR			 0x010
#define ADDR_OFFSET_RBDMA_PROC1_PTR_BYTESIZE 0x014
#define ADDR_OFFSET_RBDMA_PROC1_RSV			 0x018
#define ADDR_OFFSET_RBDMA_PROC1_STATUS		 0x01C
#define ADDR_OFFSET_RBDMA_PROC2_PTR			 0x020
#define ADDR_OFFSET_RBDMA_PROC2_PTR_BYTESIZE 0x024
#define ADDR_OFFSET_RBDMA_PROC2_RSV			 0x028
#define ADDR_OFFSET_RBDMA_PROC2_STATUS		 0x02C
#define ADDR_OFFSET_RBDMA_PROC3_PTR			 0x030
#define ADDR_OFFSET_RBDMA_PROC3_PTR_BYTESIZE 0x034
#define ADDR_OFFSET_RBDMA_PROC3_RSV			 0x038
#define ADDR_OFFSET_RBDMA_PROC3_STATUS		 0x03C

enum rbdma_proc0_status_state {
	RBDMA_PROC0_STATUS_STATE_IDLE,
	RBDMA_PROC0_STATUS_STATE_RUN,
};

enum rbdma_proc1_status_state {
	RBDMA_PROC1_STATUS_STATE_IDLE,
	RBDMA_PROC1_STATUS_STATE_RUN,
};

enum rbdma_proc2_status_state {
	RBDMA_PROC2_STATUS_STATE_IDLE,
	RBDMA_PROC2_STATUS_STATE_RUN,
};

enum rbdma_proc3_status_state {
	RBDMA_PROC3_STATUS_STATE_IDLE,
	RBDMA_PROC3_STATUS_STATE_RUN,
};

union rbdma_proc0_ptr {
	struct __attribute__((packed)) {
		uint32_t header : 32;
	};
	uint32_t bits;
};

union rbdma_proc0_ptr_bytesize {
	struct __attribute__((packed)) {
		uint32_t msb_ptr : 8;
		uint32_t size : 24;
	};
	uint32_t bits;
};

union rbdma_proc0_rsv {
	struct __attribute__((packed)) {
		uint32_t reserve : 32;
	};
	uint32_t bits;
};

union rbdma_proc0_status {
	struct __attribute__((packed)) {
		uint32_t idx_of_task : 16;
		uint32_t state : 1;
		uint32_t reserve : 15;
	};
	uint32_t bits;
};

union rbdma_proc1_ptr {
	struct __attribute__((packed)) {
		uint32_t header : 32;
	};
	uint32_t bits;
};

union rbdma_proc1_ptr_bytesize {
	struct __attribute__((packed)) {
		uint32_t msb_ptr : 8;
		uint32_t size : 24;
	};
	uint32_t bits;
};

union rbdma_proc1_rsv {
	struct __attribute__((packed)) {
		uint32_t reserve : 32;
	};
	uint32_t bits;
};

union rbdma_proc1_status {
	struct __attribute__((packed)) {
		uint32_t idx_of_task : 16;
		uint32_t state : 1;
		uint32_t reserve : 15;
	};
	uint32_t bits;
};

union rbdma_proc2_ptr {
	struct __attribute__((packed)) {
		uint32_t header : 32;
	};
	uint32_t bits;
};

union rbdma_proc2_ptr_bytesize {
	struct __attribute__((packed)) {
		uint32_t msb_ptr : 8;
		uint32_t size : 24;
	};
	uint32_t bits;
};

union rbdma_proc2_rsv {
	struct __attribute__((packed)) {
		uint32_t reserve : 32;
	};
	uint32_t bits;
};

union rbdma_proc2_status {
	struct __attribute__((packed)) {
		uint32_t idx_of_task : 16;
		uint32_t state : 1;
		uint32_t reserve : 15;
	};
	uint32_t bits;
};

union rbdma_proc3_ptr {
	struct __attribute__((packed)) {
		uint32_t header : 32;
	};
	uint32_t bits;
};

union rbdma_proc3_ptr_bytesize {
	struct __attribute__((packed)) {
		uint32_t msb_ptr : 8;
		uint32_t size : 24;
	};
	uint32_t bits;
};

union rbdma_proc3_rsv {
	struct __attribute__((packed)) {
		uint32_t reserve : 32;
	};
	uint32_t bits;
};

union rbdma_proc3_status {
	struct __attribute__((packed)) {
		uint32_t idx_of_task : 16;
		uint32_t state : 1;
		uint32_t reserve : 15;
	};
	uint32_t bits;
};

#endif /* _G_CDMA_AUTO_FETCH_COMMON_H_*/
