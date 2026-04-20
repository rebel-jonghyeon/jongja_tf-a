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

#include <string.h>
#include "common/rl_queue.h"
#include "rl_errors.h"
#include "rbln/log.h"
#include "g_sysfw_addrmap.h"
#include "cpu.h"

static struct rl_queue cs_queue;
static struct rl_queue queues[MAX_QUEUES_CNT];

static struct rl_queue *queue_initialize(struct rl_queue *q, const char *name)
{
	if (strlen(name) >= MAX_NAME_LEN) {
		RLOG_ERR("queue name(%s) length(%u) should be smaller than %u\r\n",
				 name, strlen(name), MAX_NAME_LEN);
		return NULL;
	}

	q->mask = MAX_ENTRIES_CNT - 1;
	q->pi = 0;
	q->ci = 0;
	memcpy(q->name, name, strlen(name));
	q->initialized = true;
	spin_lock_init(&q->lock);

	return q;
}

struct rl_queue *rl_queue_initialize(uint32_t idx, const char *name)
{
	if (idx >= MAX_QUEUES_CNT) {
		RLOG_ERR("failed to initialize queue id: %u\r\n", idx);
		return NULL;
	}

	return queue_initialize(&queues[idx], name);
}

struct rl_queue *rl_cs_queue_initialize(void)
{
	return queue_initialize(&cs_queue, "cs_proc");
}

int rl_queue_deinit(struct rl_queue *q)
{
	if (!q) {
		RLOG_ERR("%s: queue is null\r\n", __func__);
		return RL_BADARG;
	}

	q->mask = 0;
	q->pi = 0;
	q->ci = 0;
	q->initialized = false;

	return RL_OK;
}

static void _rl_enqueue(struct rl_queue *q, struct rl_entry *entry)
{
	memcpy(&q->entry[q->pi & q->mask], entry, sizeof(struct rl_entry));

	/*
	 * Write memory barrier is added to ensure that the pi value is incremented after memcpy
	 * has completed. If this is not guaranteed, when a dequeue is executed on another core
	 * immediately after an enqueue, it's possible that pi is incremented and entry is fetched,
	 * but memcpy is not finished and an incorrect value is feched.
	 */
	__asm__ volatile("dmb sy" ::: "memory");
	q->pi++;
}

int rl_enqueue(struct rl_queue *q, struct rl_entry *entry)
{
	if (!entry || !q) {
		RLOG_ERR("%s: null parameter(s). q(%p) entry(%p)\r\n", __func__, q, entry);
		return RL_BADARG;
	}

	if (rl_queue_is_full(q)) {
		RLOG_ERR("%s is full\r\n", q->name);
		return RL_NORESOURCE;
	}

	_rl_enqueue(q, entry);
	return RL_OK;
}

int rl_cs_enqueue(struct rl_entry *entry, uint32_t cl_id)
{
	RLOG_DBG("%s: cl_id %u\r\n", __func__, cl_id);

	return rl_enqueue(&cs_queue, entry);
}

int rl_enqueue_lock(struct rl_queue *q, struct rl_entry *entry)
{
	unsigned long flags = 0;

	if (!entry || !q) {
		RLOG_ERR("%s: null parameter(s). q(%p) entry(%p)\r\n", __func__, q, entry);
		return RL_BADARG;
	}

	flags = spin_lock_irqsave(&q->lock);
	if (rl_queue_is_full(q)) {
		spin_unlock_irqrestore(&q->lock, flags);
		RLOG_ERR("%s is full\r\n", q->name);
		return RL_NORESOURCE;
	}

	_rl_enqueue(q, entry);
	spin_unlock_irqrestore(&q->lock, flags);
	return RL_OK;
}

struct rl_entry *rl_peek(struct rl_queue *q)
{
	if (!q) {
		RLOG_ERR("%s: q(%p) is null\r\n", __func__, q);
		return NULL;
	}

	if (rl_queue_is_empty(q))
		return NULL;

	return &q->entry[q->ci & q->mask];
}

struct rl_entry *rl_cs_peek(void)
{
	struct rl_queue *q = &cs_queue;

	if (rl_queue_is_empty(q))
		return NULL;

	return &q->entry[q->ci & q->mask];
}

struct rl_entry *rl_dequeue(struct rl_queue *q)
{
	struct rl_entry *entry;

	if (!q) {
		RLOG_ERR("%s: q(%p) is null\r\n", __func__, q);
		return NULL;
	}

	if (rl_queue_is_empty(q))
		return NULL;

	entry = &q->entry[q->ci & q->mask];
	q->ci++;

	return entry;
}

struct rl_entry *rl_cs_dequeue(void)
{
	struct rl_entry *entry;
	struct rl_queue *q = &cs_queue;

	if (rl_queue_is_empty(q))
		return NULL;

	entry = &q->entry[q->ci & q->mask];
	q->ci++;

	return entry;
}

bool rl_cs_queue_is_full(void)
{
	return rl_queue_is_full(&cs_queue);
}

struct rl_queue *rl_get_queue(uint32_t idx)
{
	struct rl_queue *q;

	if (idx >= MAX_QUEUES_CNT) {
		RLOG_ERR("failed to get queue-%d\r\n", idx);
		return NULL;
	}

	q = &queues[idx];

	if (!q->initialized) {
		RLOG_ERR("queue-%d is not initialized\r\n", idx);
		return NULL;
	}

	return q;
}

void rl_queue_print_info(void)
{
	for (int i = 0; i < MAX_QUEUES_CNT; i++)
		if (queues[i].initialized)
			RLOG_ERR("%s queue info: ci %u, pi %u\r\n", queues[i].name, queues[i].ci, queues[i].pi);
}
