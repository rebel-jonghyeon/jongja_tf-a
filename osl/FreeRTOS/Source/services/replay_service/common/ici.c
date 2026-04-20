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
#include <stdbool.h>

#include "mailbox.h"
#include "rbln/log.h"
//#include "rbln/errors.h"
#include "rl_errors.h"
#include "rbln/abort.h"
#include "common/ici.h"
//#include "common/cb_tcb.h"
#include "hal/hw_spec.h"
//#include "cb_mgr/command_buffer_manager.h"
#include "chiplet.h"
#include "common/rl_queue.h"
#include "common/debug.h"
#include "system_api.h"
//#include "cli_taskmgr.h"
#include "replay.h"
#include "common_test.h"	/* test_exception_mark() */

#define ICI_POLLING_TIMEOUT_MS	(600 * 1000)	/* 600 seconds */

static int ici_cur_cl_id;
static bool initialized;
spinlock_t ici_lock;

#define ICI_RSVD					4
#define ICI_PI_IDX					0
#define ICI_CI_IDX					1
#define ICI_URG_LOCK_IDX			2
#define ICI_SYNC_RESPONSE_IDX		3
#define ICI_SYNC_RESPONSE_LOCK		1
#define ICI_URG_ENTRY_SIZE_WORD		(ICI_URG_ENTRY_SIZE / sizeof(uint32_t))		/* 2 */
#define ICI_SYNC_ENTRY_SIZE_WORD	(ICI_SYNC_ENTRY_SIZE / sizeof(uint32_t))	/* 4 */
#define ICI_NRM_ENTRY_SIZE_WORD		(ICI_NRM_ENTRY_SIZE / sizeof(uint32_t))		/* 6 */
#define ICI_URG_ENTRY_START			(ICI_RSVD)
#define ICI_SYNC_ENTRY_START		(ICI_RSVD + ICI_URG_ENTRY_SIZE_WORD)
#define ICI_NRM_ENTRY_START			(ICI_RSVD + ICI_URG_ENTRY_SIZE_WORD + ICI_SYNC_ENTRY_SIZE_WORD)
#define ICI_WORD_MAX				64
#define ICI_WORD_NUM				(ICI_WORD_MAX - ICI_RSVD)
#define ICI_NRM_WORD_NUM			(ICI_WORD_MAX - ICI_RSVD - ICI_URG_ENTRY_SIZE_WORD - ICI_SYNC_ENTRY_SIZE_WORD)
#define ICI_NRM_ENTRY_MAX			(ICI_NRM_WORD_NUM / ICI_NRM_ENTRY_SIZE_WORD)
#define ICI_NRM_ENTRY_MASK			(ICI_NRM_ENTRY_MAX - 1)

#define ICI_CHIP_SORTING_IDX		10
#define ICI_CHIP_SORTING_ENTRY_SIZE ((sizeof(struct ici_chip_sorting_entry))/(sizeof(uint32_t)))

enum _MAILBOX_ID inst[MAX_CHIPLET_COUNT][MAX_CHIPLET_COUNT] = {
	{0, IDX_MAILBOX_PERI0_M7_CPU0, IDX_MAILBOX_PERI0_M7_CPU0, IDX_MAILBOX_PERI0_M7_CPU0},
	{IDX_MAILBOX_PERI0_M7_CPU1, 0, IDX_MAILBOX_PERI0_M7_CPU1, IDX_MAILBOX_PERI0_M7_CPU1},
	{IDX_MAILBOX_PERI0_M8_CPU0, IDX_MAILBOX_PERI0_M8_CPU0, 0, IDX_MAILBOX_PERI0_M8_CPU0},
	{IDX_MAILBOX_PERI1_M8_CPU1, IDX_MAILBOX_PERI1_M8_CPU1, IDX_MAILBOX_PERI1_M8_CPU1, 0},
};

enum _CPU_ID cpu[MAX_CHIPLET_COUNT][MAX_CHIPLET_COUNT] = {
	{0, CPU0, CPU0, CPU0},
	{CPU1, 0, CPU1, CPU1},
	{CPU0, CPU0, 0, CPU0},
	{CPU1, CPU1, CPU1, 0},
};

static inline void init_queue_para(int sender_cl_id, int cl_id)
{
	ipm_samsung_write(inst[sender_cl_id][cl_id], cl_id, &(uint32_t){0}, sizeof(uint32_t), ICI_PI_IDX); // pi
	ipm_samsung_write(inst[sender_cl_id][cl_id], cl_id, &(uint32_t){0}, sizeof(uint32_t), ICI_CI_IDX); // ci
	ipm_samsung_write(inst[sender_cl_id][cl_id], cl_id, &(uint32_t){0}, sizeof(uint32_t), ICI_URG_LOCK_IDX); // lock
}

static uint32_t get_ici_entry(const int instance, struct ici_nrm_entry *entry)
{
	uint32_t pi, ci;
	uint32_t ret;

	ipm_samsung_read(instance, ici_cur_cl_id, &pi, sizeof(uint32_t), ICI_PI_IDX);
	ipm_samsung_read(instance, ici_cur_cl_id, &ci, sizeof(uint32_t), ICI_CI_IDX);

	ret = pi - ci;

	if (ret == 0) {
		RLOG_ERR("queue is empty\r\n");
		return ret;
	}

	ipm_samsung_receive(instance, (void *)entry, ICI_NRM_ENTRY_SIZE,
						ICI_NRM_ENTRY_START + (ci & ICI_NRM_ENTRY_MASK) * ICI_NRM_ENTRY_SIZE_WORD);
	ci++;
	ipm_samsung_write(instance, ici_cur_cl_id, &ci, sizeof(uint32_t), ICI_CI_IDX);

	RLOG_DBG("%s: cl%d cipi[%d/%d] op:%d idx:%d\r\n",
			 __func__, ici_cur_cl_id, ci, pi, entry->opcode, ICI_NRM_ENTRY_START + ((ci - 1) & ICI_NRM_ENTRY_MASK));

	return ret;
}

static void get_ici_urg_entry(const int inst, struct ici_urg_entry *entry)
{
	ipm_samsung_receive(inst, (void *)entry, ICI_URG_ENTRY_SIZE, ICI_URG_ENTRY_START);
	ipm_samsung_write(inst, ici_cur_cl_id, &(uint32_t){0}, sizeof(uint32_t), ICI_URG_LOCK_IDX);
}

static void get_ici_sync_entry(const int inst, struct ici_sync_entry *entry)
{
	ipm_samsung_receive(inst, (void *)entry, ICI_SYNC_ENTRY_SIZE, ICI_SYNC_ENTRY_START);
}

static int ici_enqueue_cs_proc_queue(struct rl_entry *entry)
{
	int ret;
	uint32_t cl_id;

	RLOG_DBG("cs entry receivce: %p\r\n", entry);
	RLOG_DBG("\t-opcode:%d\r\n", entry->cp.opcode);
	RLOG_DBG("\t-cb_tcb:%#lx\r\n", entry->cp.cb_tcb);
	RLOG_DBG("\t-pkt:%#lx\r\n", entry->cp.pkt);

	cl_id = *((uint32_t *)entry->cp.pkt);

	ret = rl_cs_enqueue(entry, cl_id);

	/* clean cache after used */
	//cpu_inv_dcache_range((uintptr_t)entry, sizeof(struct rl_entry));

	return ret;
}

void print_ici_chip_sorting_entry(struct ici_chip_sorting_entry *entry)
{
	RLOG_INFO("<< ici_chip_sorting_entry >>\r\n");
	RLOG_INFO("message valid : %d\r\n", entry->message_valid);
	RLOG_INFO("task type: %d\r\n", entry->task_type);
	RLOG_INFO("ucie_stress_rbdma_on_mask: 0x%x\r\n", entry->ucie_stress_rbdma_on_mask);
	RLOG_INFO("ucie_stress_pattern: %d\r\n", entry->ucie_stress_pattern);
	RLOG_INFO("ucie_traffic_direction: %d\r\n", entry->ucie_traffic_direction);
	RLOG_INFO("arg: %s\r\n", entry->arg);
	RLOG_INFO("result: %d\r\n", entry->result);
	RLOG_INFO("size: %d\r\n", entry->size);
	RLOG_INFO("\r\n");
}

static void ici_callback(const int inst, const int channel)
{
	RLOG_DBG("%s in inst %d chan %d\r\n", __func__, inst, channel);

	if (channel == ICI_CHAN_URG) {
		struct ici_urg_entry entry = {0};

		get_ici_urg_entry(inst, &entry);

		switch (entry.opcode) {
		case ICI_URG_OPCODE_ABORT:
			break;
		default:
			RLOG_ERR("no registered processing for opcode %d\r\n", entry.opcode);
			break;
		}
	} else if (channel == ICI_CHAN_NORMAL) {
		// erased legacy code from syssw
	} else if (channel == ICI_CHAN_SYNC) {
		// erased legacy code from syssw
	} else if (channel == ICI_CHAN_CHIP_SORTING) {
		ici_callback_chip_sorting(inst);
	} else {
		RLOG_ERR("unknown channel #%d\r\n", channel);
	}
}

int ici_init(int cl_id)
{
	RLOG_DBG("clid:%d initialize ici interface\r\n", cl_id);
	RLOG_DBG("entry sz(word): %d entry num: %d\r\n", ICI_NRM_ENTRY_SIZE_WORD, ICI_NRM_ENTRY_MAX);
	printf("%s: %d\r\n", __func__, cl_id);

	ici_cur_cl_id = cl_id;

	for (int sender = 0; sender < CHIPLET_COUNT; sender++) {
		if (sender == cl_id)
			continue;
		init_queue_para(sender, cl_id);
		ipm_samsung_register_callback(inst[sender][cl_id], ici_callback);
	}

	spin_lock_init(&ici_lock);
	initialized = true;

	return RL_OK;
}

int ici_send_event(struct ici_nrm_entry *entry, uint32_t tgt_cl_id, int chan)
{
	uint32_t pi, ci;
	enum _MAILBOX_ID instance = inst[ici_cur_cl_id][tgt_cl_id];
	unsigned long flags;

	if (!initialized)
		return RL_NOTREADY;

	flags = spin_lock_irqsave(&ici_lock);

	ipm_samsung_read(instance, tgt_cl_id, &pi, sizeof(uint32_t), ICI_PI_IDX);
	ipm_samsung_read(instance, tgt_cl_id, &ci, sizeof(uint32_t), ICI_CI_IDX);

	if ((pi - ci) == ICI_NRM_ENTRY_MAX) {
		RLOG_ERR("queue is full\r\n");
		return RL_NORESOURCE;
	}

	ipm_samsung_write(instance, tgt_cl_id, (const void *)entry, ICI_NRM_ENTRY_SIZE,
					  ICI_NRM_ENTRY_START + (pi & ICI_NRM_ENTRY_MASK) * ICI_NRM_ENTRY_SIZE_WORD);
	pi++;
	ipm_samsung_write(instance, tgt_cl_id, &pi, sizeof(uint32_t), ICI_PI_IDX);

	spin_unlock_irqrestore(&ici_lock, flags);
	ipm_samsung_send(instance, tgt_cl_id, chan, cpu[ici_cur_cl_id][tgt_cl_id]);

	printf("%s: cl%d -> cl%d\r\n", __func__, ici_cur_cl_id, tgt_cl_id);

	return RL_OK;
}

int ici_urg_send_event(struct ici_urg_entry *entry, uint32_t tgt_cl_id)
{
	uint32_t lock;

	if (!initialized)
		return RL_NOTREADY;

	/* TODO: This should be implemented using atomic operations, Test and Set */
	ipm_samsung_read(inst[ici_cur_cl_id][tgt_cl_id], tgt_cl_id, &lock, sizeof(uint32_t), ICI_URG_LOCK_IDX);
	if (lock) {
		RLOG_ERR("%s: an urgent event is already in progress.\r\n");
		return RL_NORESOURCE;
	}
	ipm_samsung_write(inst[ici_cur_cl_id][tgt_cl_id], tgt_cl_id, &(uint32_t){1}, sizeof(uint32_t), ICI_URG_LOCK_IDX);

	RLOG_DBG("%s: cl%d->cl%d opcode:%d\r\n", __func__, ici_cur_cl_id, tgt_cl_id, entry->opcode);

	ipm_samsung_write(inst[ici_cur_cl_id][tgt_cl_id], tgt_cl_id, (const void *)entry,
					  ICI_URG_ENTRY_SIZE, ICI_URG_ENTRY_START);
	ipm_samsung_send(inst[ici_cur_cl_id][tgt_cl_id], tgt_cl_id, ICI_CHAN_URG, cpu[ici_cur_cl_id][tgt_cl_id]);

	return RL_OK;
}

#define ICI_SYNC_TIMEOUT_US 1000000
int ici_sync_send_event(struct ici_sync_entry *entry, uint32_t tgt_cl_id, int *ret)
{
	volatile uint32_t timeout_us = 0;
	volatile uint32_t response;

	if (!initialized)
		return RL_NOTREADY;

	/* TODO: This should be implemented using atomic operations, Test and Set */
	ipm_samsung_read(inst[ici_cur_cl_id][tgt_cl_id], tgt_cl_id, (void *)&response, sizeof(uint32_t),
					 ICI_SYNC_RESPONSE_IDX);

	while (response & ICI_SYNC_RESPONSE_LOCK) {
		udelay(1);

		if (++timeout_us == ICI_SYNC_TIMEOUT_US) {
			RLOG_ERR("%s: busy timeout\r\n");
			return RL_NORESOURCE;
		}

		ipm_samsung_read(inst[ici_cur_cl_id][tgt_cl_id], tgt_cl_id, (void *)&response, sizeof(uint32_t),
						 ICI_SYNC_RESPONSE_IDX);
	}

	ipm_samsung_write(inst[ici_cur_cl_id][tgt_cl_id], tgt_cl_id, &(uint32_t){ICI_SYNC_RESPONSE_LOCK},
					  sizeof(uint32_t), ICI_SYNC_RESPONSE_IDX);
	RLOG_DBG("%s: cl%d->cl%d opcode:%d\r\n", __func__, ici_cur_cl_id, tgt_cl_id, entry->opcode);

	ipm_samsung_write(inst[ici_cur_cl_id][tgt_cl_id], tgt_cl_id, (const void *)entry,
					  ICI_SYNC_ENTRY_SIZE, ICI_SYNC_ENTRY_START);
	ipm_samsung_send(inst[ici_cur_cl_id][tgt_cl_id], tgt_cl_id, ICI_CHAN_SYNC,
					 cpu[ici_cur_cl_id][tgt_cl_id]);

	/* polling */
	timeout_us = 0;
	do {
		ipm_samsung_read(inst[ici_cur_cl_id][tgt_cl_id], tgt_cl_id, (void *)&response, sizeof(uint32_t),
						 ICI_SYNC_RESPONSE_IDX);
		if (!(response & ICI_SYNC_RESPONSE_LOCK)) {
			RLOG_DBG("%s:lock released elapsed time %dus\r\n", __func__, timeout_us);
			break;
		}

		udelay(1);

		if (++timeout_us == ICI_SYNC_TIMEOUT_US) {
			RLOG_ERR("%s:lock release timeout\r\n", __func__);
			return RL_TIMEOUT;
		}
	} while (1);

	if (ret)
		*ret = (int)response >> 1;

	return RL_OK;
}

static uint8_t rl_test_ici_sync(int argc, char *argv[])
{
	struct ici_sync_entry entry = {0};

	if (get_chiplet_id() != 0) {
#if ZEBU
		printf("%s only available on CL0\r\n", __func__);
#else
		RLOG_ERR("%s only available on CL0\r\n", __func__);
#endif /* ZEBU */
		return false;
	}

	for (int i = 1; i < CHIPLET_COUNT; i++)
		ici_sync_send_event(&entry, i, NULL);

	return true;
}

void ici_callback_chip_sorting(const int inst)
{
	struct ici_chip_sorting_entry entry;
	struct ici_callback_data c_data;

	ipm_samsung_receive(inst, &entry, sizeof(struct ici_chip_sorting_entry), ICI_CHIP_SORTING_IDX);

	print_ici_chip_sorting_entry(&entry);

	switch (entry.task_type) {
	case TASK_TYPE_RBDMA_PICK_STC_VECTOR:
		RLOG_INFO("ici callback: TASK_TYPE_RBDMA_PICK_STC_VECTOR\r\n");
		ici_callback_pick_rbdma_stc_data(entry);
		entry.message_valid = 0;
		entry.task_type = TASK_TYPE_NONE;
		ipm_samsung_write(inst, ici_cur_cl_id, &entry, sizeof(struct ici_chip_sorting_entry), ICI_CHIP_SORTING_IDX);
		break;
	case TASK_TYPE_RBDMA_PICK_REPLAY_TEST_VECTOR:
		RLOG_INFO("ici callback: TASK_TYPE_RBDMA_PICK_REPLAY_TEST_VECTOR\r\n");
		ici_callback_pick_rbdma_replay_test_data(entry);
		entry.message_valid = 0;
		entry.task_type = TASK_TYPE_NONE;
		ipm_samsung_write(inst, ici_cur_cl_id, &entry, sizeof(struct ici_chip_sorting_entry), ICI_CHIP_SORTING_IDX);
		break;
	case TASK_TYPE_STC:
		RLOG_INFO("ici callback: TASK_TYPE_STC\r\n");
		c_data.func_type = ICI_STC_TEST_START;
		c_data.size = entry.size;
		ici_callback_trigger(c_data);
		entry.task_type = TASK_TYPE_NONE;
		break;
	case TASK_TYPE_REPLAY_TEST:
		RLOG_INFO("ici callback: TASK_TYPE_REPLAY_TEST\r\n");
		c_data.func_type = ICI_REPLAY_TEST_START;
		c_data.size = entry.size;
		strncpy(c_data.arg, entry.arg, 8);
		ici_callback_trigger(c_data);
		entry.task_type = TASK_TYPE_NONE;
		break;
	case TASK_TYPE_BASIC_TEST:
		RLOG_INFO("ici callback: TASK_TYPE_BASIC_TEST\r\n");
		c_data.func_type = ICI_BASIC_TEST_START;
		c_data.size = entry.size;
		strncpy(c_data.arg, entry.arg, 8);
		ici_callback_trigger(c_data);
		entry.task_type = TASK_TYPE_NONE;
		break;
	case TASK_TYPE_UCIE_STC_STRESS:
		printf("ici callback: TASK_TYPE_UCIE_STC_STRESS\r\n");
		c_data.func_type = ICI_UCIE_STC_STRESS_START;
		c_data.size = entry.size;
		strncpy(c_data.arg, entry.arg, 8);
		ici_callback_trigger(c_data);
		entry.task_type = TASK_TYPE_NONE;
		break;
	case TASK_TYPE_POWER_MODE_UCIE_TEST:
		RLOG_INFO("ici callback: POWER_MODE_UCIE_TEST\r\n");
		c_data.func_type = ICI_POWER_MODE_UCIE_TEST_START;
		strncpy(c_data.arg, entry.arg, 8);
		ici_callback_trigger(c_data);
		entry.task_type = TASK_TYPE_NONE;
		break;
	case TASK_TYPE_HBM_PERF_TEST:
		RLOG_INFO("ici callback: TASK_TYPE_HBM_PERF_TEST\r\n");
		c_data.func_type = ICI_HBM_PERF_TEST_START;
		strncpy(c_data.arg, entry.arg, 8);
		ici_callback_trigger(c_data);
		entry.task_type = TASK_TYPE_NONE;
		break;
	case TASK_TYPE_AF_STC:
		RLOG_INFO("ici callback: TASK_TYPE_AF_STC\r\n");
		c_data.func_type = ICI_AF_STC_TEST_START;
		c_data.size = entry.size;
		ici_callback_trigger(c_data);
		entry.task_type = TASK_TYPE_NONE;
		break;
	case TASK_TYPE_QUAD_REPLAY_TEST:
		RLOG_INFO("ici callback: TASK_TYPE_QUAD_REPLAY_TEST\r\n");
		c_data.func_type = ICI_QUAD_REPLAY_TEST_START;
		c_data.size = entry.size;
		strncpy(c_data.arg, entry.arg, 8);
		ici_callback_trigger(c_data);
		entry.task_type = TASK_TYPE_NONE;
		break;
	case TASK_TYPE_NONE:
	default:
		break;
	}
}

void ici_message_clear(struct ici_chip_sorting_entry entry)
{
	ipm_samsung_write(inst[0][ici_cur_cl_id], ici_cur_cl_id, &entry, sizeof(struct ici_chip_sorting_entry), ICI_CHIP_SORTING_IDX);
}

void ici_send_event_chip_sorting(struct ici_chip_sorting_entry *entry, uint32_t tgt_cl_id)
{
	ipm_samsung_write(inst[ici_cur_cl_id][tgt_cl_id], tgt_cl_id, (void *)entry, sizeof(struct ici_chip_sorting_entry), ICI_CHIP_SORTING_IDX);
	ipm_samsung_send(inst[ici_cur_cl_id][tgt_cl_id], tgt_cl_id, ICI_CHAN_CHIP_SORTING, cpu[ici_cur_cl_id][tgt_cl_id]);

	RLOG_INFO("%s: to chiplet %d\r\n", __func__, tgt_cl_id);
	print_ici_chip_sorting_entry(entry);
}

void ici_send_sync_event(uint32_t tgt_cl_id)
{
	struct ici_chip_sorting_entry entry = {0};

	read_entry(tgt_cl_id, &entry);
	entry.sync_event = UCIE_SYNC_SEND;
	entry.task_type = TASK_TYPE_NONE;
	ipm_samsung_write(inst[ici_cur_cl_id][tgt_cl_id], tgt_cl_id, &entry, sizeof(struct ici_chip_sorting_entry), ICI_CHIP_SORTING_IDX);
	ipm_samsung_send(inst[ici_cur_cl_id][tgt_cl_id], tgt_cl_id, ICI_CHAN_CHIP_SORTING, cpu[ici_cur_cl_id][tgt_cl_id]);
}

void ici_wait_sync_event(void)
{
	struct ici_chip_sorting_entry entry;
	int polling_index = 1;

	do {
		read_entry(ici_cur_cl_id, &entry);
		if (polling_index % 10000000 == 0) {
			printf("(%d) chiplet %d is waiting for sync event\r\n", polling_index, ici_cur_cl_id);
			print_ici_chip_sorting_entry(&entry);
		}
		polling_index++;
		mdelay(100);
	} while (entry.sync_event != UCIE_SYNC_SEND);
	RLOG_INFO("(%d) sync event received: chiplet %d\r\n", polling_index, ici_cur_cl_id);
}

void ici_sync_receive_polling(uint32_t tgt_cl_id)
{
	struct ici_chip_sorting_entry entry;
	int polling_index = 1;

	RLOG_INFO("(%d) start polling sync event message of chiplet %d\r\n", polling_index, tgt_cl_id);
	do {
		ipm_samsung_read(inst[ici_cur_cl_id][tgt_cl_id], tgt_cl_id, &entry, sizeof(struct ici_chip_sorting_entry), ICI_CHIP_SORTING_IDX);
		if (polling_index % 10000000 == 0) {
			printf("(%d) chiplet 0 is polling sync event of chiplet %d\r\n", polling_index, tgt_cl_id);
			print_ici_chip_sorting_entry(&entry);
		}
		polling_index++;
		mdelay(100);
	} while (entry.sync_event != UCIE_SYNC_RECEIVE);
	RLOG_INFO("(%d) sync polling done: chiplet %d\r\n", polling_index, tgt_cl_id);
}

void ici_sync_message_clear(void)
{
	struct ici_chip_sorting_entry entry = {0};

	read_entry(ici_cur_cl_id, &entry);
	entry.sync_event = UCIE_SYNC_RECEIVE;
	ipm_samsung_write(inst[0][ici_cur_cl_id], ici_cur_cl_id, &entry, sizeof(struct ici_chip_sorting_entry), ICI_CHIP_SORTING_IDX);
	RLOG_INFO("sync message cleared: chiplet %d\r\n", ici_cur_cl_id);
}

void ici_message_receive_polling(uint32_t tgt_cl_id)
{
	struct ici_chip_sorting_entry entry;
	int polling_index = 1;
	uint32_t elapsed_ms = 0;

	RLOG_INFO("(%d) start polling message of chiplet %d to be clear\r\n", polling_index, tgt_cl_id);
	do {
		ipm_samsung_read(inst[ici_cur_cl_id][tgt_cl_id], tgt_cl_id, &entry, sizeof(struct ici_chip_sorting_entry), ICI_CHIP_SORTING_IDX);
		if (polling_index % 10000000 == 0) {
			printf("(%d) chiplet 0 is polling message of chiplet %d to be clear\r\n", polling_index, tgt_cl_id);
			print_ici_chip_sorting_entry(&entry);
		}
		polling_index++;
		mdelay(100);
		elapsed_ms += 100;
		if (elapsed_ms >= ICI_POLLING_TIMEOUT_MS) {
			RLOG_ERR("[TIMEOUT] chiplet %d did not respond within %d s\r\n",
				 tgt_cl_id, ICI_POLLING_TIMEOUT_MS / 1000);
			printf("[TIMEOUT] chiplet %d did not respond within %d s\r\n",
			       tgt_cl_id, ICI_POLLING_TIMEOUT_MS / 1000);
			test_exception_mark();
			return;
		}
	} while (entry.message_valid != 0);
	RLOG_INFO("(%d) polling done: chiplet %d\r\n", polling_index, tgt_cl_id);
}

void write_entry(int tgt_cl_id, struct ici_chip_sorting_entry *entry)
{
	ipm_samsung_write(inst[ici_cur_cl_id][tgt_cl_id], tgt_cl_id, (void *)entry, sizeof(struct ici_chip_sorting_entry), ICI_CHIP_SORTING_IDX);
}

void read_entry(int tgt_cl_id, struct ici_chip_sorting_entry *entry)
{
	ipm_samsung_read(inst[0][tgt_cl_id], tgt_cl_id, (void *)entry, sizeof(struct ici_chip_sorting_entry), ICI_CHIP_SORTING_IDX);
}

void read_inst_entry(int sender_cl_id, int tgt_cl_id, struct ici_chip_sorting_entry *entry)
{
	ipm_samsung_read(inst[sender_cl_id][tgt_cl_id], tgt_cl_id, (void *)entry, sizeof(struct ici_chip_sorting_entry), ICI_CHIP_SORTING_IDX);
}
