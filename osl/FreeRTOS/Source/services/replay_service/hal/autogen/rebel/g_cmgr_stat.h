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

#ifndef _G_CMGR_STAT_COMMON_H_
#define _G_CMGR_STAT_COMMON_H_

#define ADDR_OFFSET_CMGR_STAT_COMP_TASK_0	  0x0
#define ADDR_OFFSET_CMGR_STAT_COMP_TASK_1	  0x4
#define ADDR_OFFSET_CMGR_STAT_COMP_TASK_2	  0x8
#define ADDR_OFFSET_CMGR_STAT_COMP_TASK_3	  0xC
#define ADDR_OFFSET_CMGR_STAT_COMP_CREDIT_0	  0x10
#define ADDR_OFFSET_CMGR_STAT_COMP_CREDIT_1	  0x14
#define ADDR_OFFSET_CMGR_STAT_COMP_CREDIT_2	  0x18
#define ADDR_OFFSET_CMGR_STAT_COMP_CREDIT_3	  0x1C
#define ADDR_OFFSET_CMGR_STAT_UDMA_TASK_0	  0x20
#define ADDR_OFFSET_CMGR_STAT_UDMA_TASK_1	  0x24
#define ADDR_OFFSET_CMGR_STAT_UDMA_TASK_2	  0x28
#define ADDR_OFFSET_CMGR_STAT_UDMA_TASK_3	  0x2C
#define ADDR_OFFSET_CMGR_STAT_UDMA_CREDIT_0	  0x30
#define ADDR_OFFSET_CMGR_STAT_UDMA_CREDIT_1	  0x34
#define ADDR_OFFSET_CMGR_STAT_UDMA_CREDIT_2	  0x38
#define ADDR_OFFSET_CMGR_STAT_UDMA_CREDIT_3	  0x3C
#define ADDR_OFFSET_CMGR_STAT_LPUDMA_TASK_0	  0x40
#define ADDR_OFFSET_CMGR_STAT_LPUDMA_TASK_1	  0x44
#define ADDR_OFFSET_CMGR_STAT_LPUDMA_TASK_2	  0x48
#define ADDR_OFFSET_CMGR_STAT_LPUDMA_TASK_3	  0x4C
#define ADDR_OFFSET_CMGR_STAT_LPUDMA_CREDIT_0 0x50
#define ADDR_OFFSET_CMGR_STAT_LPUDMA_CREDIT_1 0x54
#define ADDR_OFFSET_CMGR_STAT_LPUDMA_CREDIT_2 0x58
#define ADDR_OFFSET_CMGR_STAT_LPUDMA_CREDIT_3 0x5C
#define ADDR_OFFSET_CMGR_STAT_STUDMA_TASK_0	  0x60
#define ADDR_OFFSET_CMGR_STAT_STUDMA_TASK_1	  0x64
#define ADDR_OFFSET_CMGR_STAT_STUDMA_TASK_2	  0x68
#define ADDR_OFFSET_CMGR_STAT_STUDMA_TASK_3	  0x6C
#define ADDR_OFFSET_CMGR_STAT_STUDMA_CREDIT_0 0x70
#define ADDR_OFFSET_CMGR_STAT_STUDMA_CREDIT_1 0x74
#define ADDR_OFFSET_CMGR_STAT_STUDMA_CREDIT_2 0x78
#define ADDR_OFFSET_CMGR_STAT_STUDMA_CREDIT_3 0x7C
#define ADDR_OFFSET_CMGR_STAT_RBDMA_CREDIT_0  0x80
#define ADDR_OFFSET_CMGR_STAT_RBDMA_CREDIT_1  0x84
#define ADDR_OFFSET_CMGR_STAT_TCNT_DNC0		  0x100
#define ADDR_OFFSET_CMGR_STAT_TCNT_DNC1		  0x104
#define ADDR_OFFSET_CMGR_STAT_TCNT_DNC2		  0x108
#define ADDR_OFFSET_CMGR_STAT_TCNT_DNC3		  0x10C
#define ADDR_OFFSET_CMGR_STAT_TCNT_DNC4		  0x110
#define ADDR_OFFSET_CMGR_STAT_TCNT_DNC5		  0x114
#define ADDR_OFFSET_CMGR_STAT_TCNT_DNC6		  0x118
#define ADDR_OFFSET_CMGR_STAT_TCNT_DNC7		  0x11C
#define ADDR_OFFSET_CMGR_STAT_TCNT_DNC8		  0x120
#define ADDR_OFFSET_CMGR_STAT_TCNT_DNC9		  0x124
#define ADDR_OFFSET_CMGR_STAT_TCNT_DNC10	  0x128
#define ADDR_OFFSET_CMGR_STAT_TCNT_DNC11	  0x12C
#define ADDR_OFFSET_CMGR_STAT_TCNT_DNC12	  0x130
#define ADDR_OFFSET_CMGR_STAT_TCNT_DNC13	  0x134
#define ADDR_OFFSET_CMGR_STAT_TCNT_DNC14	  0x138
#define ADDR_OFFSET_CMGR_STAT_TCNT_DNC15	  0x13C
#define ADDR_OFFSET_CMGR_STAT_TCNT_RBDMA_N	  0x140
#define ADDR_OFFSET_CMGR_STAT_TCNT_RBDMA_U	  0x144
#define ADDR_OFFSET_CMGR_STAT_NOTI_ACC_0	  0x180
#define ADDR_OFFSET_CMGR_STAT_NOTI_ACC_1	  0x184
#define ADDR_OFFSET_CMGR_STAT_NOTI_ACC_2	  0x188
#define ADDR_OFFSET_CMGR_STAT_NOTI_ACC_3	  0x18C
#define ADDR_OFFSET_CMGR_STAT_NOTI_ACC_4	  0x190
#define ADDR_OFFSET_CMGR_STAT_NOTI_ACC_5	  0x194
#define ADDR_OFFSET_CMGR_STAT_NOTI_ACC_6	  0x198
#define ADDR_OFFSET_CMGR_STAT_NOTI_ACC_7	  0x19C
#define ADDR_OFFSET_CMGR_STAT_NOTI_ACC_8	  0x1A0
#define ADDR_OFFSET_CMGR_STAT_NOTI_ACC_9	  0x1A4
#define ADDR_OFFSET_CMGR_STAT_NOTI_ACC_10	  0x1A8
#define ADDR_OFFSET_CMGR_STAT_LOG_MSG_0		  0x33C
#define ADDR_OFFSET_CMGR_STAT_LOG_MSG_1		  0x340
#define ADDR_OFFSET_CMGR_STAT_LOG_MSG_2		  0x344
#define ADDR_OFFSET_CMGR_STAT_LOG_MSG_3		  0x348
#define ADDR_OFFSET_CMGR_STAT_LOG_MSG_4		  0x34C
#define ADDR_OFFSET_CMGR_STAT_LOG_ADDR_0	  0x350
#define ADDR_OFFSET_CMGR_STAT_LOG_ADDR_1	  0x354
#define ADDR_OFFSET_CMGR_STAT_PORT_STAT_0	  0x3A0
#define ADDR_OFFSET_CMGR_STAT_PORT_STAT_1	  0x3A4

union cmgr_stat_comp_task_0 {
	struct __attribute__((packed)) {
		uint32_t dnc0 : 8;
		uint32_t dnc1 : 8;
		uint32_t dnc2 : 8;
		uint32_t dnc3 : 8;
	};
	uint32_t bits;
};

union cmgr_stat_comp_task_1 {
	struct __attribute__((packed)) {
		uint32_t dnc4 : 8;
		uint32_t dnc5 : 8;
		uint32_t dnc6 : 8;
		uint32_t dnc7 : 8;
	};
	uint32_t bits;
};

union cmgr_stat_comp_task_2 {
	struct __attribute__((packed)) {
		uint32_t dnc8 : 8;
		uint32_t dnc9 : 8;
		uint32_t dnc10 : 8;
		uint32_t dnc11 : 8;
	};
	uint32_t bits;
};

union cmgr_stat_comp_task_3 {
	struct __attribute__((packed)) {
		uint32_t dnc12 : 8;
		uint32_t dnc13 : 8;
		uint32_t dnc14 : 8;
		uint32_t dnc15 : 8;
	};
	uint32_t bits;
};

union cmgr_stat_comp_credit_0 {
	struct __attribute__((packed)) {
		uint32_t dnc0 : 8;
		uint32_t dnc1 : 8;
		uint32_t dnc2 : 8;
		uint32_t dnc3 : 8;
	};
	uint32_t bits;
};

union cmgr_stat_comp_credit_1 {
	struct __attribute__((packed)) {
		uint32_t dnc4 : 8;
		uint32_t dnc5 : 8;
		uint32_t dnc6 : 8;
		uint32_t dnc7 : 8;
	};
	uint32_t bits;
};

union cmgr_stat_comp_credit_2 {
	struct __attribute__((packed)) {
		uint32_t dnc8 : 8;
		uint32_t dnc9 : 8;
		uint32_t dnc10 : 8;
		uint32_t dnc11 : 8;
	};
	uint32_t bits;
};

union cmgr_stat_comp_credit_3 {
	struct __attribute__((packed)) {
		uint32_t dnc12 : 8;
		uint32_t dnc13 : 8;
		uint32_t dnc14 : 8;
		uint32_t dnc15 : 8;
	};
	uint32_t bits;
};

union cmgr_stat_udma_task_0 {
	struct __attribute__((packed)) {
		uint32_t dnc0 : 8;
		uint32_t dnc1 : 8;
		uint32_t dnc2 : 8;
		uint32_t dnc3 : 8;
	};
	uint32_t bits;
};

union cmgr_stat_udma_task_1 {
	struct __attribute__((packed)) {
		uint32_t dnc4 : 8;
		uint32_t dnc5 : 8;
		uint32_t dnc6 : 8;
		uint32_t dnc7 : 8;
	};
	uint32_t bits;
};

union cmgr_stat_udma_task_2 {
	struct __attribute__((packed)) {
		uint32_t dnc8 : 8;
		uint32_t dnc9 : 8;
		uint32_t dnc10 : 8;
		uint32_t dnc11 : 8;
	};
	uint32_t bits;
};

union cmgr_stat_udma_task_3 {
	struct __attribute__((packed)) {
		uint32_t dnc12 : 8;
		uint32_t dnc13 : 8;
		uint32_t dnc14 : 8;
		uint32_t dnc15 : 8;
	};
	uint32_t bits;
};

union cmgr_stat_udma_credit_0 {
	struct __attribute__((packed)) {
		uint32_t dnc0 : 8;
		uint32_t dnc1 : 8;
		uint32_t dnc2 : 8;
		uint32_t dnc3 : 8;
	};
	uint32_t bits;
};

union cmgr_stat_udma_credit_1 {
	struct __attribute__((packed)) {
		uint32_t dnc4 : 8;
		uint32_t dnc5 : 8;
		uint32_t dnc6 : 8;
		uint32_t dnc7 : 8;
	};
	uint32_t bits;
};

union cmgr_stat_udma_credit_2 {
	struct __attribute__((packed)) {
		uint32_t dnc8 : 8;
		uint32_t dnc9 : 8;
		uint32_t dnc10 : 8;
		uint32_t dnc11 : 8;
	};
	uint32_t bits;
};

union cmgr_stat_udma_credit_3 {
	struct __attribute__((packed)) {
		uint32_t dnc12 : 8;
		uint32_t dnc13 : 8;
		uint32_t dnc14 : 8;
		uint32_t dnc15 : 8;
	};
	uint32_t bits;
};

union cmgr_stat_lpudma_task_0 {
	struct __attribute__((packed)) {
		uint32_t dnc0 : 8;
		uint32_t dnc1 : 8;
		uint32_t dnc2 : 8;
		uint32_t dnc3 : 8;
	};
	uint32_t bits;
};

union cmgr_stat_lpudma_task_1 {
	struct __attribute__((packed)) {
		uint32_t dnc4 : 8;
		uint32_t dnc5 : 8;
		uint32_t dnc6 : 8;
		uint32_t dnc7 : 8;
	};
	uint32_t bits;
};

union cmgr_stat_lpudma_task_2 {
	struct __attribute__((packed)) {
		uint32_t dnc8 : 8;
		uint32_t dnc9 : 8;
		uint32_t dnc10 : 8;
		uint32_t dnc11 : 8;
	};
	uint32_t bits;
};

union cmgr_stat_lpudma_task_3 {
	struct __attribute__((packed)) {
		uint32_t dnc12 : 8;
		uint32_t dnc13 : 8;
		uint32_t dnc14 : 8;
		uint32_t dnc15 : 8;
	};
	uint32_t bits;
};

union cmgr_stat_lpudma_credit_0 {
	struct __attribute__((packed)) {
		uint32_t dnc0 : 8;
		uint32_t dnc1 : 8;
		uint32_t dnc2 : 8;
		uint32_t dnc3 : 8;
	};
	uint32_t bits;
};

union cmgr_stat_lpudma_credit_1 {
	struct __attribute__((packed)) {
		uint32_t dnc4 : 8;
		uint32_t dnc5 : 8;
		uint32_t dnc6 : 8;
		uint32_t dnc7 : 8;
	};
	uint32_t bits;
};

union cmgr_stat_lpudma_credit_2 {
	struct __attribute__((packed)) {
		uint32_t dnc8 : 8;
		uint32_t dnc9 : 8;
		uint32_t dnc10 : 8;
		uint32_t dnc11 : 8;
	};
	uint32_t bits;
};

union cmgr_stat_lpudma_credit_3 {
	struct __attribute__((packed)) {
		uint32_t dnc12 : 8;
		uint32_t dnc13 : 8;
		uint32_t dnc14 : 8;
		uint32_t dnc15 : 8;
	};
	uint32_t bits;
};

union cmgr_stat_studma_task_0 {
	struct __attribute__((packed)) {
		uint32_t dnc0 : 8;
		uint32_t dnc1 : 8;
		uint32_t dnc2 : 8;
		uint32_t dnc3 : 8;
	};
	uint32_t bits;
};

union cmgr_stat_studma_task_1 {
	struct __attribute__((packed)) {
		uint32_t dnc4 : 8;
		uint32_t dnc5 : 8;
		uint32_t dnc6 : 8;
		uint32_t dnc7 : 8;
	};
	uint32_t bits;
};

union cmgr_stat_studma_task_2 {
	struct __attribute__((packed)) {
		uint32_t dnc8 : 8;
		uint32_t dnc9 : 8;
		uint32_t dnc10 : 8;
		uint32_t dnc11 : 8;
	};
	uint32_t bits;
};

union cmgr_stat_studma_task_3 {
	struct __attribute__((packed)) {
		uint32_t dnc12 : 8;
		uint32_t dnc13 : 8;
		uint32_t dnc14 : 8;
		uint32_t dnc15 : 8;
	};
	uint32_t bits;
};

union cmgr_stat_studma_credit_0 {
	struct __attribute__((packed)) {
		uint32_t dnc0 : 8;
		uint32_t dnc1 : 8;
		uint32_t dnc2 : 8;
		uint32_t dnc3 : 8;
	};
	uint32_t bits;
};

union cmgr_stat_studma_credit_1 {
	struct __attribute__((packed)) {
		uint32_t dnc4 : 8;
		uint32_t dnc5 : 8;
		uint32_t dnc6 : 8;
		uint32_t dnc7 : 8;
	};
	uint32_t bits;
};

union cmgr_stat_studma_credit_2 {
	struct __attribute__((packed)) {
		uint32_t dnc8 : 8;
		uint32_t dnc9 : 8;
		uint32_t dnc10 : 8;
		uint32_t dnc11 : 8;
	};
	uint32_t bits;
};

union cmgr_stat_studma_credit_3 {
	struct __attribute__((packed)) {
		uint32_t dnc12 : 8;
		uint32_t dnc13 : 8;
		uint32_t dnc14 : 8;
		uint32_t dnc15 : 8;
	};
	uint32_t bits;
};

union cmgr_stat_rbdma_credit_0 {
	struct __attribute__((packed)) {
		uint32_t credit : 32;
	};
	uint32_t bits;
};

union cmgr_stat_rbdma_credit_1 {
	struct __attribute__((packed)) {
		uint32_t credit : 32;
	};
	uint32_t bits;
};

union cmgr_stat_tcnt_dnc0 {
	struct __attribute__((packed)) {
		uint32_t count_et1 : 16;
		uint32_t count_et2 : 16;
	};
	uint32_t bits;
};

union cmgr_stat_tcnt_dnc1 {
	struct __attribute__((packed)) {
		uint32_t count_et1 : 16;
		uint32_t count_et2 : 16;
	};
	uint32_t bits;
};

union cmgr_stat_tcnt_dnc2 {
	struct __attribute__((packed)) {
		uint32_t count_et1 : 16;
		uint32_t count_et2 : 16;
	};
	uint32_t bits;
};

union cmgr_stat_tcnt_dnc3 {
	struct __attribute__((packed)) {
		uint32_t count_et1 : 16;
		uint32_t count_et2 : 16;
	};
	uint32_t bits;
};

union cmgr_stat_tcnt_dnc4 {
	struct __attribute__((packed)) {
		uint32_t count_et1 : 16;
		uint32_t count_et2 : 16;
	};
	uint32_t bits;
};

union cmgr_stat_tcnt_dnc5 {
	struct __attribute__((packed)) {
		uint32_t count_et1 : 16;
		uint32_t count_et2 : 16;
	};
	uint32_t bits;
};

union cmgr_stat_tcnt_dnc6 {
	struct __attribute__((packed)) {
		uint32_t count_et1 : 16;
		uint32_t count_et2 : 16;
	};
	uint32_t bits;
};

union cmgr_stat_tcnt_dnc7 {
	struct __attribute__((packed)) {
		uint32_t count_et1 : 16;
		uint32_t count_et2 : 16;
	};
	uint32_t bits;
};

union cmgr_stat_tcnt_dnc8 {
	struct __attribute__((packed)) {
		uint32_t count_et1 : 16;
		uint32_t count_et2 : 16;
	};
	uint32_t bits;
};

union cmgr_stat_tcnt_dnc9 {
	struct __attribute__((packed)) {
		uint32_t count_et1 : 16;
		uint32_t count_et2 : 16;
	};
	uint32_t bits;
};

union cmgr_stat_tcnt_dnc10 {
	struct __attribute__((packed)) {
		uint32_t count_et1 : 16;
		uint32_t count_et2 : 16;
	};
	uint32_t bits;
};

union cmgr_stat_tcnt_dnc11 {
	struct __attribute__((packed)) {
		uint32_t count_et1 : 16;
		uint32_t count_et2 : 16;
	};
	uint32_t bits;
};

union cmgr_stat_tcnt_dnc12 {
	struct __attribute__((packed)) {
		uint32_t count_et1 : 16;
		uint32_t count_et2 : 16;
	};
	uint32_t bits;
};

union cmgr_stat_tcnt_dnc13 {
	struct __attribute__((packed)) {
		uint32_t count_et1 : 16;
		uint32_t count_et2 : 16;
	};
	uint32_t bits;
};

union cmgr_stat_tcnt_dnc14 {
	struct __attribute__((packed)) {
		uint32_t count_et1 : 16;
		uint32_t count_et2 : 16;
	};
	uint32_t bits;
};

union cmgr_stat_tcnt_dnc15 {
	struct __attribute__((packed)) {
		uint32_t count_et1 : 16;
		uint32_t count_et2 : 16;
	};
	uint32_t bits;
};

union cmgr_stat_tcnt_rbdma_n {
	struct __attribute__((packed)) {
		uint32_t count_et1 : 16;
		uint32_t count_et2 : 16;
	};
	uint32_t bits;
};

union cmgr_stat_tcnt_rbdma_u {
	struct __attribute__((packed)) {
		uint32_t count_et1 : 16;
		uint32_t count_et2 : 16;
	};
	uint32_t bits;
};

union cmgr_stat_noti_acc_0 {
	struct __attribute__((packed)) {
		uint32_t count : 32;
	};
	uint32_t bits;
};

union cmgr_stat_noti_acc_1 {
	struct __attribute__((packed)) {
		uint32_t count : 32;
	};
	uint32_t bits;
};

union cmgr_stat_noti_acc_2 {
	struct __attribute__((packed)) {
		uint32_t count : 32;
	};
	uint32_t bits;
};

union cmgr_stat_noti_acc_3 {
	struct __attribute__((packed)) {
		uint32_t count : 32;
	};
	uint32_t bits;
};

union cmgr_stat_noti_acc_4 {
	struct __attribute__((packed)) {
		uint32_t count : 32;
	};
	uint32_t bits;
};

union cmgr_stat_noti_acc_5 {
	struct __attribute__((packed)) {
		uint32_t count : 32;
	};
	uint32_t bits;
};

union cmgr_stat_noti_acc_6 {
	struct __attribute__((packed)) {
		uint32_t count : 32;
	};
	uint32_t bits;
};

union cmgr_stat_noti_acc_7 {
	struct __attribute__((packed)) {
		uint32_t count : 32;
	};
	uint32_t bits;
};

union cmgr_stat_noti_acc_8 {
	struct __attribute__((packed)) {
		uint32_t count : 32;
	};
	uint32_t bits;
};

union cmgr_stat_noti_acc_9 {
	struct __attribute__((packed)) {
		uint32_t count : 32;
	};
	uint32_t bits;
};

union cmgr_stat_noti_acc_10 {
	struct __attribute__((packed)) {
		uint32_t count : 32;
	};
	uint32_t bits;
};

union cmgr_stat_log_msg_0 {
	struct __attribute__((packed)) {
		uint32_t data : 32;
	};
	uint32_t bits;
};

union cmgr_stat_log_msg_1 {
	struct __attribute__((packed)) {
		uint32_t data : 32;
	};
	uint32_t bits;
};

union cmgr_stat_log_msg_2 {
	struct __attribute__((packed)) {
		uint32_t data : 32;
	};
	uint32_t bits;
};

union cmgr_stat_log_msg_3 {
	struct __attribute__((packed)) {
		uint32_t data : 32;
	};
	uint32_t bits;
};

union cmgr_stat_log_msg_4 {
	struct __attribute__((packed)) {
		uint32_t data : 32;
	};
	uint32_t bits;
};

union cmgr_stat_log_addr_0 {
	struct __attribute__((packed)) {
		uint32_t addr : 32;
	};
	uint32_t bits;
};

union cmgr_stat_log_addr_1 {
	struct __attribute__((packed)) {
		uint32_t addr : 32;
	};
	uint32_t bits;
};

union cmgr_stat_port_stat_0 {
	struct __attribute__((packed)) {
		uint32_t slv_w : 32;
	};
	uint32_t bits;
};

union cmgr_stat_port_stat_1 {
	struct __attribute__((packed)) {
		uint32_t slv_r : 32;
	};
	uint32_t bits;
};

#endif /* _G_CMGR_STAT_COMMON_H_*/
