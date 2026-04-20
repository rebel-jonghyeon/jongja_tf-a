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

#ifndef _CP_ICI_H_
#define _CP_ICI_H_

#define ICI_NRM_ENTRY_SIZE (sizeof(struct ici_nrm_entry))

enum ici_opcode {
	ICI_OPCODE_ENQUEUE_CS_PROC_QUEUE = 0,
	ICI_OPCODE_PUT_EXT_SYNC,
	ICI_OPCODE_MOVE_SYNC,
	ICI_OPCODE_ADD_BARRIER,
	ICI_OPCODE_PKT_DONE,
	ICI_OPCODE_CONST_BUF_SYNC,
	ICI_OPCODE_CLKSYNC,
    ICI_OPCODE_LOOPBACK,
	ICI_OPCODE_CDB,
    ICI_OPCODE_MAX,
};

struct __attribute__((aligned(4))) ici_nrm_entry {
	uint8_t opcode;
	union {
		struct cb_sync {
			uint64_t cb_tcb;
			uint64_t pkt;
			uint32_t cookie;
		} cb_sync;
		struct cs_proc {
			uint64_t cs_entry;
		} cs;
		struct clksync {
			uint64_t cyclecount;
		} clk;
	};
};


#define ICI_URG_ENTRY_SIZE (sizeof(struct ici_urg_entry))

enum ici_urg_opcode {
	ICI_URG_OPCODE_ABORT,
	ICI_URG_OPCODE_MAX,
};

struct __attribute__((aligned(4))) ici_urg_entry {
	uint8_t opcode;
	union {
		struct abort {
			uint32_t err_code;
		} abort;
	};
};

#define ICI_SYNC_ENTRY_SIZE (sizeof(struct ici_sync_entry))

enum ici_sync_opcode {
	ICI_SYNC_OPCODE_FLUSH,
	ICI_SYNC_OPCODE_CDB,
	ICI_SYNC_OPCODE_MAX,
};

struct __attribute__((aligned(4))) ici_sync_entry {
	uint32_t opcode;
	uint64_t addr;
	uint32_t size;
	union {
		struct flush {
			uint64_t addr;
			uint32_t size;
		} flush;
		struct ici_cdb {
			uint32_t command;
			uint64_t data; // or data
		} cdb;
	};
};

enum _ucie_stress_pattern {
	UCIE_STRESS_PATTERN_READ,
	UCIE_STRESS_PATTERN_WRITE
};

enum _ucie_stress_test_type {
	UCIE_STRESS_TEST_TYPE_NONE,
	UCIE_STRESS_TEST_TYPE_ONLY_RBDMA,
	UCIE_STRESS_TEST_TYPE_RBDMA_AND_STC,
	UCIE_STRESS_TEST_TYPE_HALT,
};

enum _ici_chip_sorting_task_type {
	TASK_TYPE_NONE,
	TASK_TYPE_RBDMA_PICK_STC_VECTOR,
	TASK_TYPE_UCIE_STC_STRESS,
	TASK_TYPE_BASIC_TEST,
	TASK_TYPE_RBDMA_PICK_REPLAY_TEST_VECTOR,
	TASK_TYPE_STC,
	TASK_TYPE_REPLAY_TEST,
	TASK_TYPE_POWER_MODE_UCIE_TEST,
	TASK_TYPE_HBM_PERF_TEST,
	TASK_TYPE_AF_STC,
	TASK_TYPE_RBDMA_PICK_QUAD_REPLAY_TEST_VECTOR,
	TASK_TYPE_QUAD_REPLAY_TEST,
	TASK_TYPE_DRAM_HARSH_STRESS,
	TASK_TYPE_DRAM_ALL_ARRAY,
};

enum _ucie_traffic_direction {
	UCIE_TRAFFIC_DIRECTION_NONE,
	UCIE_TRAFFIC_DIRECTION_HORIZONTAL,
	UCIE_TRAFFIC_DIRECTION_VERTICAL,
};
enum _ucie_sync_event {
	UCIE_SYNC_NONE,
	UCIE_SYNC_SEND,
	UCIE_SYNC_RECEIVE,
};

struct __attribute__((aligned(4))) ici_chip_sorting_entry {
	// common
	int task_type;
	int sync_event;
	// ucie stress test
	int ucie_stress_test_type;
	int ucie_stress_rbdma_on_mask; // per chiplet mask (0x1 ~ 0xF)
	int ucie_stress_pattern; // _ucie_stress_pattern
	int ucie_traffic_direction; // _ucie_traffic_direction
	// ucie basic test
	char arg[8];
	// ucie replay test
	// for future
	int result; // from cl 1, 2, 3 to cl 0 , data : 1 pass, 0 or 2 no data, else fail
	uint32_t size;
	int message_valid;
};

enum ici_chan {
	ICI_CHAN_NORMAL,
	ICI_CHAN_URG,
	ICI_CHAN_SYNC,
	ICI_CHAN_CHIP_SORTING,
};

int ici_init(int cl_id);
int ici_send_event(struct ici_nrm_entry *entry, uint32_t tgt_cl_id, int chan);
int ici_urg_send_event(struct ici_urg_entry *entry, uint32_t tgt_cl_id);

void ici_callback_chip_sorting(const int inst);
void ici_send_event_chip_sorting(struct ici_chip_sorting_entry *entry, uint32_t tgt_cl_id);
void ici_message_receive_polling(uint32_t tgt_cl_id);
void ici_message_receive_polling(uint32_t tgt_cl_id);
void read_entry(int tgt_cl_id, struct ici_chip_sorting_entry *entry);
void read_inst_entry(int sender_cl_id, int tgt_cl_id, struct ici_chip_sorting_entry *entry);
void write_entry(int tgt_cl_id, struct ici_chip_sorting_entry *entry);
void ici_message_clear(struct ici_chip_sorting_entry entry);
void print_ici_chip_sorting_entry(struct ici_chip_sorting_entry *entry);

void ici_send_sync_event(uint32_t tgt_cl_id);
void ici_sync_receive_polling(uint32_t tgt_cl_id);
void ici_sync_message_clear();
void ici_wait_sync_event();

#endif /* _CP_ICI_H_ */
