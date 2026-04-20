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

#ifndef _G_CMGR_QUEUE_COMMON_H_
#define _G_CMGR_QUEUE_COMMON_H_

#define ADDR_OFFSET_CMGR_QUEUE_QUEUE_0_0_0	 0x0
#define ADDR_OFFSET_CMGR_QUEUE_QUEUE_0_0_1	 0x4
#define ADDR_OFFSET_CMGR_QUEUE_QUEUE_0_0_2	 0x8
#define ADDR_OFFSET_CMGR_QUEUE_QUEUE_0_0_3	 0xC
#define ADDR_OFFSET_CMGR_QUEUE_QUEUE_0_1_0	 0x10
#define ADDR_OFFSET_CMGR_QUEUE_QUEUE_0_1_1	 0x14
#define ADDR_OFFSET_CMGR_QUEUE_QUEUE_0_1_2	 0x18
#define ADDR_OFFSET_CMGR_QUEUE_QUEUE_0_1_3	 0x1C
#define ADDR_OFFSET_CMGR_QUEUE_QUEUE_0_511_0 0x1FF0
#define ADDR_OFFSET_CMGR_QUEUE_QUEUE_0_511_1 0x1FF4
#define ADDR_OFFSET_CMGR_QUEUE_QUEUE_0_511_2 0x1FF8
#define ADDR_OFFSET_CMGR_QUEUE_QUEUE_0_511_3 0x1FFC
#define ADDR_OFFSET_CMGR_QUEUE_QUEUE_1_0_0	 0x2000
#define ADDR_OFFSET_CMGR_QUEUE_QUEUE_1_0_1	 0x2004
#define ADDR_OFFSET_CMGR_QUEUE_QUEUE_1_0_2	 0x2008
#define ADDR_OFFSET_CMGR_QUEUE_QUEUE_1_0_3	 0x200C
#define ADDR_OFFSET_CMGR_QUEUE_QUEUE_1_511_0 0x3FF0
#define ADDR_OFFSET_CMGR_QUEUE_QUEUE_1_511_1 0x3FF4
#define ADDR_OFFSET_CMGR_QUEUE_QUEUE_1_511_2 0x3FF8
#define ADDR_OFFSET_CMGR_QUEUE_QUEUE_1_511_3 0x3FFC

union cmgr_queue_queue_0_0_0 {
	struct __attribute__((packed)) {
		uint32_t entry : 32;
	};
	uint32_t bits;
};

union cmgr_queue_queue_0_0_1 {
	struct __attribute__((packed)) {
		uint32_t entry : 32;
	};
	uint32_t bits;
};

union cmgr_queue_queue_0_0_2 {
	struct __attribute__((packed)) {
		uint32_t entry : 32;
	};
	uint32_t bits;
};

union cmgr_queue_queue_0_0_3 {
	struct __attribute__((packed)) {
		uint32_t entry : 32;
	};
	uint32_t bits;
};

union cmgr_queue_queue_0_1_0 {
	struct __attribute__((packed)) {
		uint32_t entry : 32;
	};
	uint32_t bits;
};

union cmgr_queue_queue_0_1_1 {
	struct __attribute__((packed)) {
		uint32_t entry : 32;
	};
	uint32_t bits;
};

union cmgr_queue_queue_0_1_2 {
	struct __attribute__((packed)) {
		uint32_t entry : 32;
	};
	uint32_t bits;
};

union cmgr_queue_queue_0_1_3 {
	struct __attribute__((packed)) {
		uint32_t entry : 32;
	};
	uint32_t bits;
};

union cmgr_queue_queue_0_511_0 {
	struct __attribute__((packed)) {
		uint32_t entry : 32;
	};
	uint32_t bits;
};

union cmgr_queue_queue_0_511_1 {
	struct __attribute__((packed)) {
		uint32_t entry : 32;
	};
	uint32_t bits;
};

union cmgr_queue_queue_0_511_2 {
	struct __attribute__((packed)) {
		uint32_t entry : 32;
	};
	uint32_t bits;
};

union cmgr_queue_queue_0_511_3 {
	struct __attribute__((packed)) {
		uint32_t entry : 32;
	};
	uint32_t bits;
};

union cmgr_queue_queue_1_0_0 {
	struct __attribute__((packed)) {
		uint32_t entry : 32;
	};
	uint32_t bits;
};

union cmgr_queue_queue_1_0_1 {
	struct __attribute__((packed)) {
		uint32_t entry : 32;
	};
	uint32_t bits;
};

union cmgr_queue_queue_1_0_2 {
	struct __attribute__((packed)) {
		uint32_t entry : 32;
	};
	uint32_t bits;
};

union cmgr_queue_queue_1_0_3 {
	struct __attribute__((packed)) {
		uint32_t entry : 32;
	};
	uint32_t bits;
};

union cmgr_queue_queue_1_511_0 {
	struct __attribute__((packed)) {
		uint32_t entry : 32;
	};
	uint32_t bits;
};

union cmgr_queue_queue_1_511_1 {
	struct __attribute__((packed)) {
		uint32_t entry : 32;
	};
	uint32_t bits;
};

union cmgr_queue_queue_1_511_2 {
	struct __attribute__((packed)) {
		uint32_t entry : 32;
	};
	uint32_t bits;
};

union cmgr_queue_queue_1_511_3 {
	struct __attribute__((packed)) {
		uint32_t entry : 32;
	};
	uint32_t bits;
};

#endif /* _G_CMGR_QUEUE_COMMON_H_*/
