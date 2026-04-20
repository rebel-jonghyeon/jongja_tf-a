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

#ifndef _RL_QUEUE_H_
#define _RL_QUEUE_H_

#include <stdbool.h>
#include "rbln/spinlock.h"
#include "gic.h"
#include "qman_if.h"
#include "cpu.h"

#define CQ_QUEUES_CNT		2
#define MAX_QUEUES_CNT		(CQ_QUEUES_CNT)
#define MAX_ENTRIES_CNT		(1 << 8) /* 256 */
#define MAX_NAME_LEN		16

enum rl_queue_opcode {
	RL_QUEUE_OPCODE_ACTIVATE_CTX = 0,
	RL_QUEUE_OPCODE_DELIVER_CTX,
	RL_QUEUE_OPCODE_CONF_STATIC_PT,
	RL_QUEUE_OPCODE_RUN_PROC,
	RL_QUEUE_OPCODE_QR_START,
	RL_QUEUE_OPCODE_MAX,
};

enum rl_queue_idx {
	RL_QUEUE_HDMA_H2D,
	RL_QUEUE_HDMA_D2H,
};

struct rl_entry {
	union {
		struct rl_entry_cp {
			uint8_t opcode;
			uint64_t cb_tcb;
			uint64_t pkt;
			uint16_t sync_op;
		} cp;
		struct rl_entry_init {
			uint8_t opcode;
			uint32_t num_vfs;
		} init;
		struct rl_entry_hdma {
			uint64_t cb_tcb;
			uint64_t pkt;
			uint16_t sync_op;
		} hdma;
	};
};

struct rl_queue {
	char name[MAX_NAME_LEN];
	struct rl_entry entry[MAX_ENTRIES_CNT];
	uint32_t mask;
	uint32_t pi;
	uint32_t ci;
	bool initialized;
	spinlock_t lock;
};

struct rl_queue *rl_queue_initialize(uint32_t idx, const char *name);
struct rl_queue *rl_cs_queue_initialize(void);
int rl_queue_deinit(struct rl_queue *q);
int rl_enqueue(struct rl_queue *q, struct rl_entry *entry);
int rl_enqueue_lock(struct rl_queue *q, struct rl_entry *entry);
int rl_cs_enqueue(struct rl_entry *entry, uint32_t cl_id);
struct rl_entry *rl_peek(struct rl_queue *q);
struct rl_entry *rl_cs_peek(void);
struct rl_entry *rl_dequeue(struct rl_queue *q);
struct rl_entry *rl_cs_dequeue(void);
struct rl_queue *rl_get_queue(uint32_t idx);
static inline bool rl_queue_is_full(struct rl_queue *q)
{
	return ((q->pi - q->ci) == MAX_ENTRIES_CNT);
}
bool rl_cs_queue_is_full(void);

static inline bool rl_queue_is_empty(struct rl_queue *q)
{
	return (q->pi == q->ci);
}

void rl_queue_print_info(void);
#endif /* _RL_QUEUE_H_ */
