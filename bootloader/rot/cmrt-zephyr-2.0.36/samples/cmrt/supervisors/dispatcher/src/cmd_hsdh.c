/*
 * Copyright (c) 2021-2023 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

#include <zephyr.h>
#include <string.h>
#include <assert.h>
#include <stdalign.h>

#include <cri/cmrt.h>
#include <cri/cmrt/dd.h>
#include <cri/cmrt/hsdh.h>
#include <cri/cmrt/sic.h>
#include <cri/cmrt/hs_aes.h>
#include <cri/cmrt/pdma_reg.h>
#include <cri/cmrt/pdma.h>
#include <cri/cmrt/ext_ddr.h>
#include <common.h>

#define AT_ROW_MAX_DATA_SIZE 0x10000 /* 64KB */
#define MK_PA(at) (((u64_t) ((at)->phys_addr[1])) << 32 | (at)->phys_addr[0])
#define CIRCULAR_BUF_IN (CRI_EXT_MEMORY_DDR_CMRT + 0x200000)
#define CIRCULAR_BUF_OUT (CIRCULAR_BUF_IN + (16 * 4 * 1024))
#define CTRL_BLOCK_ADDR (CRI_EXT_MEMORY_DDR_CMRT + 0x9200000)
#define MAX_BATCH_PAGES 1
#define NR_CONTEXTS (CMRT_HSAES_NR_CHANNELS * CMRT_HSAES_NR_KEY_BANKS)

#undef VERBOSE
#undef DEBUG

#ifdef VERBOSE
#define vrbo(fmt, ...) printk("hsdh:%d\t%s\t" fmt, __LINE__, __func__, ##__VA_ARGS__)
#else
#define vrbo(...) do {} while (0)
#endif

#ifdef DEBUG
#define dbg(fmt, ...) printk("hsdh:%d\t%s\t" fmt, __LINE__, __func__, ##__VA_ARGS__)
#else
#define dbg(...) do {} while (0)
#endif

#define log(fmt, ...) printk("hsdh:%d\t%s\t" fmt, __LINE__, __func__, ##__VA_ARGS__)

#define WORKER_STOP(ret, fmt, ...) ({ \
	hsdh.state_next = WORKER_STOPPED; \
	log(fmt, ##__VA_ARGS__); \
	ret; \
})

#define SIC_RETURN(ret, type) do { \
	type *resp = *data; \
	resp->result = ret; \
	*size = sizeof(type); \
	log("SIC response code %d\n", ret); \
	return; \
} while (0)

#define RETURN(ret, fmt, ...) do { \
	if (ret && ret != -EAGAIN && ret != -EBUSY) \
		dbg("returned %d " fmt "\n", ret, ##__VA_ARGS__); \
	return ret; \
} while (0)

enum worker_state {
	WORKER_STOPPED = 1,
	WORKER_STARTING,
	WORKER_RUNNING,
};

/* Event contexts */
#define NR_EVENTS (2+(CMRT_HSAES_NR_CHANNELS*CMRT_HSAES_NR_KEY_BANKS*2))
typedef struct hsdh_ec {
	struct hsdh_context *context;
	bool is_hs_aes;
} hsdh_ec_t;

typedef struct hsdh_context {
	cri_hs_aes_t hs_aes;
	cri_pdma_t pdma;

	/* Context is on watch queue if it has active desc. */
	sys_snode_t ln__watch_hs_aes;
	sys_snode_t ln__watch_pdma;

	bool at_busy_hs_aes;
	bool at_busy_pdma;
	bool delayed_close_channel;

	hsdh_rec_t *rec;
	hsdh_rec_t *rec_close_ch;
	u32_t nr_pend;
} hsdh_context_t;

typedef struct hsdh_request_batch {
	enum batch_state {
		BATCH_NOT_IN_USE = 0, /* Batch is not being handled by eSW. */
		BATCH_PULL,           /* Batch is ready at HLOS; can be copied to eSW. */
		BATCH_PULLING,        /* Batch is being copied to eSW. */
		BATCH_READY,          /* Batch is ready for enqueuing. */
		BATCH_BUSY,           /* Batch is not fully enqueued. */
		BATCH_WAIT,           /* Batch is fully enqueued and waiting on drivers. */
		BATCH_PUSH,           /* Batch has completed; can be copied to HLOS. */
		BATCH_PUSHING,        /* Batch is being copied to HLOS. */
	} state;
	hsdh_rec_t *next_rec;
} hsdh_request_batch_t;

static struct hsdh {
	hsdh_context_t contexts[NR_CONTEXTS];
	hsdh_request_batch_t batches[1];
	u32_t nr_open_contexts;

	/* hsdh_context's with active desc. */
	sys_slist_t l_ctx__watch_hs_aes;
	sys_slist_t l_ctx__watch_pdma;

	/* Once set, all driver context needs to be closed. */
	bool hw_error;
	bool hlos2esw_interrupt;

	struct {
		/* eSW address of batch pages (located in EXT DDR). */
		void *addr;

		/* Physical address of AT array. */
		u64_t hlos_pa;
		u32_t nr_pages;
		u32_t page_shift;   /* Page size = 1 << page_shift */

		/* Device contexts for control channel. */
		hsdh_context_t *context;
	} ctrl;

	/* Events for SIC and all HSAES + PDMA contexts. */
	struct k_poll_event events[NR_EVENTS];
	hsdh_ec_t ec[NR_EVENTS];

	/* Worker thread stuff */
	enum worker_state state_next;
	enum worker_state state;
	struct k_poll_signal worker_signal;

	cri_sic_t sic;
	alignas(4) char sic_buf[20];
	size_t sic_size;
	u32_t peerid;
} hsdh = {
	.ctrl.addr = (void *) CTRL_BLOCK_ADDR,
	.state_next = WORKER_STOPPED,
	.state = WORKER_STOPPED,
};

void hsdh_set_snode_dequeued(sys_snode_t *n)
{
	n->next = n;
}

int hsdh_is_snode_dequeued(sys_snode_t *n)
{
	return n->next == n;
}

static inline void hsdh_watchq_add_context(hsdh_context_t *c, bool is_hs_aes)
{
	vrbo("\n");
	sys_slist_t *list = is_hs_aes ? &hsdh.l_ctx__watch_hs_aes : &hsdh.l_ctx__watch_pdma;
	sys_snode_t *n = is_hs_aes ? &c->ln__watch_hs_aes : &c->ln__watch_pdma;
	if (hsdh_is_snode_dequeued(n)) {
		vrbo("context %p ch %d added to watchq\n", c, c - hsdh.contexts);
		sys_slist_append(list, n);
	}
}

static inline void hsdh_watchq_remove_context(hsdh_context_t *c, bool is_hs_aes)
{
	vrbo("\n");
	sys_slist_t *list = is_hs_aes ? &hsdh.l_ctx__watch_hs_aes : &hsdh.l_ctx__watch_pdma;
	sys_snode_t *n = is_hs_aes ? &c->ln__watch_hs_aes : &c->ln__watch_pdma;
	if (sys_slist_find_and_remove(list, n)) {
		vrbo("context %p ch %d removed from watchq\n", c, c - hsdh.contexts);
		hsdh_set_snode_dequeued(n);
		return;
	}
	dbg("context was not on watch list!!\n");
}

__used static const char *hsdh_cmd_str(enum sic_req_cmd cmd)
{
	static struct {
		char name[21];
		enum sic_req_cmd cmd;
	} map[] = {
		{"HSDH_INIT_REQ",       HSDH_INIT_REQ},
		{"HSDH_PROCESS_REQ",    HSDH_PROCESS_REQ},
	};
	for (size_t i = 0; i < sizeof(map)/sizeof(map[0]); i++) {
		if (cmd == map[i].cmd) {
			return map[i].name;
		}
	}
	return "Unknown request";
}

static const char *batch_state_str(enum batch_state state)
{
	static struct {
		char name[21];
		enum batch_state state;
	} map[] = {
		{"BATCH_NOT_IN_USE", BATCH_NOT_IN_USE},
		{"BATCH_PULL", BATCH_PULL},
		{"BATCH_PULLING", BATCH_PULLING},
		{"BATCH_READY", BATCH_READY},
		{"BATCH_BUSY", BATCH_BUSY},
		{"BATCH_WAIT", BATCH_WAIT},
		{"BATCH_PUSH", BATCH_PUSH},
		{"BATCH_PUSHING", BATCH_PUSHING},
	};
	for (size_t i = 0; i < sizeof(map)/sizeof(map[0]); i++) {
		if (state == map[i].state) {
			return map[i].name;
		}
	}
	return "Unknown batch state";
}

static int hsdh_open_channel(bool bidi, u32_t context_id, u32_t keysplit_id, void *salt);
static int hsdh_open_ctrl_channel(void)
{
	vrbo("\n");
	if (hsdh.ctrl.context) {
		return 0; /* Control channel is already open. */
	}
	int ret = hsdh_open_channel(0 /* uni */, 0, 0, 0);
	if (ret) {
		RETURN(ret, "failed to open control channel");
	}
	hsdh.ctrl.context = &hsdh.contexts[0];
	hsdh.ctrl.context->at_busy_pdma = 1;
	return 0;
}

static int hsdh_open_channel(bool bidi, u32_t context_id, u32_t keysplit_id, void *salt)
{
	vrbo("\n");
	hsdh_context_t *c = &hsdh.contexts[context_id];
	if (cri_is_valid(c->hs_aes)) {
		RETURN(-EINVAL, "context is already open");
	}

	/* Open HSAES and PDMA contexts. */
	cri_hs_aes_t hs_aes = cri_hs_aes_open(0);
	if (!cri_is_valid(hs_aes)) {
		RETURN(-ENODEV, "HSAES device open failed");
	}

	u32_t channel, key_bank;
	cri_hs_aes_get_channel_context(hs_aes, &channel, &key_bank);
	cri_pdma_t pdma = cri_pdma_open(0, channel, key_bank);
	if (!cri_is_valid(pdma)) {
		cri_hs_aes_close(hs_aes);
		RETURN(-ENODEV, "PDMA device open failed");
	}

	if (bidi) {
		/* Derive key with KDC and set it to HSAES context. */
		kdc_cmd_t cmd = { .base_key_id = keysplit_id };
		memcpy(cmd.diversify_path, salt, sizeof(cmd.diversify_path));
		cmd.diversify_len = sizeof(cmd.diversify_path);
		hsdh_rec_t rec;
		static_assert(sizeof(cmd.diversify_path) <= sizeof(rec.o.salt), "");

		int ret = cri_hs_aes_kdc_cmd(hs_aes, CMRT_HSAES_KEY_SIZE, &cmd);
		if (ret) {
			cri_pdma_close(pdma);
			cri_hs_aes_close(hs_aes);
			RETURN(ret, "failed to set key");
		}
	}

	/* Store context information */
	*c = (hsdh_context_t) {
		.hs_aes = hs_aes,
		.pdma = pdma,
	};
	hsdh_set_snode_dequeued(&c->ln__watch_hs_aes);
	hsdh_set_snode_dequeued(&c->ln__watch_pdma);

	hsdh.nr_open_contexts++;
	dbg("      ch %d HSAES ch %d kb %u %s context %p\n", context_id, channel, key_bank, bidi ? "bidi" : "", c);
	return 0;
}

static int do_hsdh_close_channel(hsdh_context_t *c)
{
	vrbo("\n");
	if (!cri_is_valid(c->hs_aes)) {
		RETURN(-EINVAL, "ERROR: context %p is not open\n", c);
	}

	u32_t channel, key_bank;
	cri_hs_aes_get_channel_context(c->hs_aes, &channel, &key_bank);

	cri_hs_aes_close(c->hs_aes);
	cri_pdma_close(c->pdma);
	if (c->delayed_close_channel) {
		c->delayed_close_channel = 0;
		c->rec_close_ch->type |= HSDH_REC_DONE;
	}

	/* Clear context. */
	*c = (hsdh_context_t) { 0 };
	hsdh_set_snode_dequeued(&c->ln__watch_hs_aes);
	hsdh_set_snode_dequeued(&c->ln__watch_pdma);

	--hsdh.nr_open_contexts;
	dbg("  ch %u HSAES ch %u kb %u closed context %p\n", c - hsdh.contexts, channel, key_bank, c);

	/* Clear HW error flag if all context have closed now. */
	if (hsdh.hw_error) {
		hsdh.hw_error = hsdh.nr_open_contexts ? 1 : 0;
		if (!hsdh.hw_error) {
			log("recovered from HW error\n");
		}
	}
	return 0;
}

static int hsdh_close_channel(u32_t context_id)
{
	vrbo("\n");
	if (context_id >= NR_CONTEXTS) {
		RETURN(-EINVAL, "context ID > max ID %u > %u", context_id, NR_CONTEXTS-1);
	}
	hsdh_context_t *c = &hsdh.contexts[context_id];
	if (!cri_is_valid(c->hs_aes)) {
		RETURN(-EINVAL, "context %d is already closed", context_id);
	}
	if (c->at_busy_hs_aes || c->at_busy_pdma) {
		/* Context will be closed when all its ATs complete. */
		c->delayed_close_channel = true;
		return -EBUSY;
	}
	return do_hsdh_close_channel(c);
}

static int hsdh_enqueue_bidi_batch(hsdh_context_t *c, hsdh_rec_bidi_batch_t *b)
{
	vrbo("\n");
	/*
	 * Try to queue same number of ATs to PDMA and HSAES.
	 * First queue PDMA operation, its queue has less number of slots and
	 * will run out of free slots first. So we do not have to handle
	 * situation where an AT is on only one of the core's queue.
	 */
	int ret = 0;
	u32_t from = c->nr_pend ? b->nr_at - c->nr_pend : 0;
	u32_t i, j;
	for (i = from; i < b->nr_at && ret == 0; i++) {
		u64_t pa = REC_AT(GET, PA, &b->at[i]) << 12;
		u32_t nr_rows = REC_AT(GET, NR_ROWS, &b->at[i]);
		vrbo("PDMA  %u pa 0x%016llx  in 0x%016lx out 0x%016lx nr_rows %u\n",
				i, pa, CIRCULAR_BUF_IN, CIRCULAR_BUF_OUT, nr_rows);
		ret = cri_pdma_copy(c->pdma, pa, nr_rows, CIRCULAR_BUF_IN, CIRCULAR_BUF_OUT, b->is_encrypt);
	}
	if (ret) {
		i--;
		if (i == from) {
			/* No operation started; nothing to do for HSAES. */
			return ret;
		}
	}

	ret = 0;
	for (j = from; j < i && ret == 0; j++) {
		u32_t nr_rows = REC_AT(GET, NR_ROWS, &b->at[j]);
		vrbo("HSAES %u %s nr_rows %u\n", j, b->is_encrypt ? "encrypt" : "decrypt", nr_rows);
		ret = cri_hs_aes_queue_at(c->hs_aes,
				b->is_encrypt ? CRI_AES_ENCRYPT : CRI_AES_DECRYPT,
				CRI_AES_GCM, 0, 0, nr_rows, CIRCULAR_BUF_IN, CIRCULAR_BUF_OUT);
	}
	j -= ret ? 1 : 0;
	c->at_busy_hs_aes += j > from;
	c->at_busy_pdma += 1;
	c->nr_pend = b->nr_at - i;
	dbg("ch %u ATs queued %u left %u/%u\n", b->channel, i - from, c->nr_pend, b->nr_at);
	if (j < i) {
		/*
		 * We are in a pickle!
		 * The last descriptor we queued to PDMA will never complete
		 * because corresponding HSAES descriptor was rejected.
		 * The only viable option is to issue abort.
		 */
		return -EIO;
	}
	ret = ret ? ret : (c->nr_pend ? -EAGAIN : 0);
	RETURN(ret, "");
}

static int hsdh_enqueue_uni_batch(hsdh_context_t *c, hsdh_rec_uni_batch_t *b)
{
	vrbo("\n");
	int ret = 0;
	uint32_t i, from;
	u64_t esw_addr = b->esw_addr;
	from = c->nr_pend ? b->nr_at - c->nr_pend : 0;
	for (i = from; i < b->nr_at && ret == 0; i++) {
		u64_t pa = REC_AT(GET, PA, &b->at[i]) << 12;
		u32_t nr_rows = REC_AT(GET, NR_ROWS, &b->at[i]);
		vrbo("DESC %u AT pa 0x%016llx  in 0x%016llx out 0x%016llx nr_rows %u h2f %u\n",
				i, pa,
				b->is_h2f ? esw_addr : 0,
				b->is_h2f ? 0 : esw_addr,
				nr_rows, b->is_h2f);
		ret = cri_pdma_copy(c->pdma, pa, nr_rows,
				b->is_h2f ? esw_addr : 0,
				b->is_h2f ? 0 : esw_addr,
				0);
		esw_addr += nr_rows * AT_ROW_MAX_DATA_SIZE;
	}
	i -= ret ? 1 : 0;
	c->at_busy_pdma += i > from;
	c->nr_pend = b->nr_at - i;
	dbg("ch %u queued %u left %u/%u ATs\n", b->channel, i - from, c->nr_pend, b->nr_at);
	return ret;
}

static int hsdh_enqueue_batch(hsdh_rec_t *rec)
{
	vrbo("\n");
	if (rec->o.channel == 0 || rec->o.channel >= NR_CONTEXTS) {
		RETURN(-EINVAL, "invalid context ID %u (min 1 max %u)", rec->b.channel, NR_CONTEXTS-1);
	}
	hsdh_context_t *c = &hsdh.contexts[rec->b.channel];
	if (!cri_is_valid(c->hs_aes)) {
		RETURN(-EINVAL, "context is not open");
	}
	if (c->rec && c->rec != rec) {
		dbg("ch %u has active rec %p, can't processes rec %p\n", rec->b.channel, c->rec, rec);
		return -EAGAIN;
	}
	c->rec = rec;
	int ret;
	if (rec->type & HSDH_REC_CONTEXT_BIDI) {
		ret = hsdh_enqueue_bidi_batch(c, (void *)rec);
	} else {
		ret = hsdh_enqueue_uni_batch(c, (void *)rec);
	}

	/* Add context to watch list */
	hsdh_watchq_add_context(c, 0);
	hsdh_watchq_add_context(c, 1);
	if (ret) {
		RETURN(ret, "");
	}
	return -EBUSY;
}

static u32_t hsdh_get_batch_addr(int batch)
{
	return CTRL_BLOCK_ADDR + (batch * (1 << hsdh.ctrl.page_shift));
}

static void hsdh_handle_error(void);
static void hsdh_batch_pull_push(int batch, bool pull)
{
	vrbo("\n");
	bool retry = 1;
again:
	if (hsdh_open_ctrl_channel()) {
		return;
	}
	cri_pdma_t pdma = hsdh.ctrl.context->pdma;
	u64_t at_pa = hsdh.ctrl.hlos_pa + (batch * CMRT_PDMA_AT_SIZE);
	u64_t batch_addr = hsdh_get_batch_addr(batch);
	u64_t in = pull ? batch_addr : 0;
	u64_t out = pull ? 0 : batch_addr;

	dbg("%s batch\n", pull ? "pulling in" : "pushing out");
	vrbo("pa 0x%016llx  in 0x%016llx out 0x%016llx nr_rows %u\n", at_pa, in, out, 1);
	int ret = cri_pdma_copy(pdma, at_pa, 1, in, out, false);
	if (ret) {
		if (!retry) {
			log("ERROR: HSDH control channel can't operate %d\n", ret);
			hsdh.state_next = WORKER_STOPPED;
			return;
		}
		log("batch %d transfer failed %d, retrying once\n", batch, ret);
		hsdh_handle_error();
		retry = 0;
		goto again;
	}
	hsdh.batches[0].state = pull ? BATCH_PULLING : BATCH_PUSHING;
}

static int hsdh_batch_process_rec(void **prec, bool check)
{
	u32_t size = 0;
	hsdh_rec_t *rec = *prec;

	int ret = 0;
	switch (HSDH_REC_TYPE(rec)) {
	case HSDH_REC_START:
		size = sizeof(rec->s);
		if (check) {
			break;
		}
		if (rec->s.state != HSDH_REC_STATE_IDLE) {
			RETURN(-EINVAL, "error: batch state is not idle but %u state\n", rec->s.state);
		}
		rec->s.state = HSDH_REC_STATE_BUSY;
		break;
	case HSDH_REC_OPEN_CHANNEL:
		size = sizeof(rec->o);
		if (check) {
			break;
		}
		if (rec->o.channel == 0 || rec->o.channel >= NR_CONTEXTS) {
			ret = -EINVAL;
			log("invalid context ID %u (min 1 max %u)", rec->o.channel, NR_CONTEXTS-1);
			break;
		}
		ret = hsdh_open_channel(rec->type & HSDH_REC_CONTEXT_BIDI,
				rec->o.channel, rec->o.keysplit_id, rec->o.salt);
		break;
	case HSDH_REC_CLOSE_CHANNEL:
		size = sizeof(rec->c);
		if (check) {
			break;
		}
		ret = hsdh_close_channel(rec->c.channel);
		if (ret == -EBUSY) {
			hsdh_context_t *c = &hsdh.contexts[rec->c.channel];
			c->rec_close_ch = rec;
			*prec += size;
			return 0;
		}
		break;
	case HSDH_REC_AT_BATCH:
		size = rec->type & HSDH_REC_CONTEXT_BIDI ?
			sizeof(rec->b) + (sizeof(hsdh_rec_at_t) * rec->b.nr_at) :
			sizeof(rec->u) + (sizeof(hsdh_rec_at_t) * rec->u.nr_at);
		if (check) {
			break;
		}
		ret = hsdh_enqueue_batch(rec);
		break;
	case HSDH_REC_END:
		return 0;
	default:
		ret = -EINVAL;
	}
	if (check) {
		*prec += size;
		return rec->type & HSDH_REC_DONE ? 0 : -EAGAIN;
	}
	switch (ret) {
	case -EAGAIN:
		/* Batch record is not fully enqueued; do not advance to next record. */
		return ret;
	case -EBUSY:
		/* Do not mark batch record done. */
		ret = 0;
		break;
	case 0:
		rec->type |= HSDH_REC_DONE;
		break;
	default:
		rec->type |= HSDH_REC_DONE | HSDH_REC_ERROR;
	}
	*prec += size;
	RETURN(ret, "");
}

static void do_hsdh_batch_process(int batch, void *pos)
{
	void *end = ((void *)hsdh_get_batch_addr(batch)) + (1<<hsdh.ctrl.page_shift);
	do {
		if (pos >= end) {
			log("WARN: end record not found\n");
			break;
		}
		int ret = hsdh_batch_process_rec(&pos, 0);
		if (ret == -EAGAIN) {
			/* Save resume point */
			hsdh.batches[batch].next_rec = pos;
			hsdh.batches[batch].state = BATCH_BUSY;
			return;
		}
		if (ret) {
			hsdh_rec_start_t *s = (void *)hsdh_get_batch_addr(batch);
			s->type |= HSDH_REC_ERROR;
			hsdh_handle_error();
			return;
		}
	} while (HSDH_REC_TYPE(pos) != HSDH_REC_END);

	hsdh.batches[batch].next_rec = pos;
	hsdh.batches[batch].state = BATCH_WAIT;
}

static void hsdh_batch_process(int batch)
{
	vrbo("\n");
	hsdh_rec_start_t *s = (void *)hsdh_get_batch_addr(batch);
	if (HSDH_REC_TYPE(s) != HSDH_REC_START) {
		log("ERROR: batch %d not started by state record but %u\n", batch, HSDH_REC_TYPE(s));
		return;
	}
	if (s->state != HSDH_REC_STATE_IDLE) {
		log("ERROR: batch %d is not in idle state but (0x%x)\n", batch, s->state);
		return;
	}
	do_hsdh_batch_process(batch, s);
}

static void hsdh_batch_process_resume(int batch)
{
	vrbo("\n");
	void *pos = hsdh.batches[batch].next_rec;
	hsdh.batches[batch].next_rec = NULL;
	if (!pos) {
		log("ERROR: resume record point not saved\n");
		return;
	}
	do_hsdh_batch_process(batch, pos);
}

static void hsdh_batch_check(int batch)
{
	hsdh_rec_start_t *s = (void *)hsdh_get_batch_addr(batch);
	void *pos = s;
	void *end = (void *)s + (1<<hsdh.ctrl.page_shift);
	do {
		if (pos >= end) {
			log("ERROR: end record not found\n");
			break;
		}
		int ret = hsdh_batch_process_rec(&pos, 1 /* Check only. */);
		if (ret == -EAGAIN) {
			vrbo("rec %u is not ready\n", ((hsdh_rec_t *)pos)->type);
			return; /* Some batches are pending. */
		}
	} while (HSDH_REC_TYPE(pos) != HSDH_REC_END);
	s->type |= HSDH_REC_DONE;
	s->state = HSDH_REC_STATE_DONE;
	hsdh.batches[batch].state = BATCH_PUSH;
}

static void hsdh_service_batch(void)
{
	vrbo("\n");
	int batch = 0;
	enum batch_state *state = &hsdh.batches[batch].state;
	enum batch_state old;
	do {
		dbg("\n         batch %d %s\n\n", batch, batch_state_str(*state));
		old = *state;
		switch (*state) {
		case BATCH_PULL:
			hsdh_batch_pull_push(batch, 1 /* PULL */);
			break;
		case BATCH_READY:
			hsdh_batch_process(batch);
			break;
		case BATCH_BUSY:
			hsdh_batch_process_resume(batch);
			break;
		case BATCH_WAIT:
			hsdh_batch_check(batch);
			break;
		case BATCH_PUSH:
			hsdh_batch_pull_push(batch, 0 /* PUSH */);
			break;
		case BATCH_PULLING:
		case BATCH_PUSHING:
			/* Handled in hsdh_service_ctrl_channel() */
			break;
		case BATCH_NOT_IN_USE:
			break;
		default:
			log("unknown batch state %u\n", *state);
			return;
		}
	} while (old != *state);
}

static void hsdh_init_ctrl_channel(void **data, u32_t *size)
{
	if (*size != sizeof(hsdh_init_req_t)) {
		SIC_RETURN(-EINVAL, cmrt_hsdh_resp_t);
	}

	hsdh_init_req_t *req = *data;
	if (req->nr_pages > MAX_BATCH_PAGES || req->page_shift < 12) {
		SIC_RETURN(-EINVAL, cmrt_hsdh_resp_t);
	}

	hsdh.ctrl.hlos_pa = req->ctrl_block_pa;
	hsdh.ctrl.nr_pages = req->nr_pages;
	hsdh.ctrl.page_shift = req->page_shift;
	log("control channel configured. batch pages %u size %u\n", hsdh.ctrl.nr_pages, 1<<hsdh.ctrl.page_shift);
	SIC_RETURN(0, cmrt_hsdh_resp_t);
}

static void hsdh_process_request(void **data, u32_t *size)
{
	cmrt_hsdh_sic_request_t *req = *data;
	if (*size < sizeof(cmrt_hsdh_sic_request_t)) {
		SIC_RETURN(-EINVAL, cmrt_hsdh_resp_t);
	}

	dbg("New command: %s\n", hsdh_cmd_str(req->cmd));
	*data = req->payload;
	*size -= sizeof(*req);
	switch (req->cmd) {
	case HSDH_INIT_REQ:
		hsdh_init_ctrl_channel(data, size);
		break;
	case HSDH_PROCESS_REQ:
		if (hsdh.batches[0].state != BATCH_NOT_IN_USE) {
			log("ERROR: can't pull batch %d in state %s\n", 0, batch_state_str(hsdh.batches[0].state));
			SIC_RETURN(-EBUSY, cmrt_hsdh_resp_t);
			break;
		}
		if (!hsdh.ctrl.hlos_pa) {
			log("ERROR: can't pull batch, control channel is not configured\n");
			SIC_RETURN(-EINVAL, cmrt_hsdh_resp_t);
			break;
		}

		hsdh.hlos2esw_interrupt = 1;
		SIC_RETURN(0, cmrt_hsdh_resp_t);
		break;
	default:
		SIC_RETURN(-EINVAL, cmrt_hsdh_resp_t);
	}
}

static int hsdh_service_ctrl_channel(void)
{
	vrbo("\n");
	static bool retry = 1;

	int batch = 0;
	enum batch_state *state = &hsdh.batches[batch].state;
	int nr_failed = cri_pdma_sync(hsdh.ctrl.context->pdma);
	if (nr_failed) {
		log("ERROR: failed to transfer batch\n");
		log("hsaes status: 0x%0x\n", sys_read32(CMRT_HSAES_BASE+R_HSAES_STATUS));
		log("pdma status: 0x%0x\n", sys_read32(CMRT_PDMA_BASE+R_PDMA_STATUS));
		cri_hs_aes_abort(hsdh.ctrl.context->hs_aes);
		hsdh_handle_error();
		if (retry) {
			retry = 0;
			log("WARN: batch %d transfer failed, retrying once\n", batch);
			hsdh_batch_pull_push(batch, *state == BATCH_PULLING);
			return 0;
		}
		log("ERROR: HSDH control channel can't operate\n");
		return 0;
	}
	retry = 1;

	switch (*state) {
	case BATCH_PULLING:
		dbg("batch %d ready for esw to process\n", batch);
		*state = BATCH_READY;
		break;
	case BATCH_PUSHING:
		dbg("batch %d ready for hlos, send interrupt\n", batch);
		*state = BATCH_NOT_IN_USE;
		return 1; /* Send interrupt to HLOS. */
	default:
		log("WARN: batch %d is in unexpected state %u (%s)\n", batch, *state, batch_state_str(*state));
	}
	return 0;
}

static void hsdh_service_context(hsdh_context_t *c);
static void hsdh_handle_error(void)
{
	if (hsdh.hw_error) {
		return;
	}
	log("ERROR: an HW error occurred\n");
	log("trying to recover from error\n");
	hsdh.ctrl.context = NULL;
	for (int i = 0; i < NR_CONTEXTS; i++) {
		hsdh_context_t *c = &hsdh.contexts[i];
		if (!cri_is_valid(c->hs_aes))  {
			vrbo("skip closed context %p HSAES %p PDMA %p\n", c, c->hs_aes, c->pdma);
			continue;
		}
		if (!hsdh.hw_error) {
			cri_hs_aes_abort(c->hs_aes);
			cri_pdma_abort(c->pdma);
			hsdh.hw_error = true;
		}
		hsdh_service_context(c);
		do_hsdh_close_channel(c);
	}

	hsdh_rec_start_t *s = (void *)hsdh_get_batch_addr(0);
	enum batch_state *state = &hsdh.batches[0].state;
	switch (*state) {
	case BATCH_PULLING:
		*state = BATCH_PULL;
		break;
	case BATCH_PUSHING:
		*state = BATCH_PUSH;
		break;
	default:
		s->type |= HSDH_REC_DONE | HSDH_REC_ERROR;
		s->state = HSDH_REC_STATE_DONE;
		*state = BATCH_PUSH;
	}
}

static void hsdh_service_context(hsdh_context_t *c)
{
	vrbo("\n");
	if (!c->hs_aes) {
		return; /* Context has been closed. */
	}
	vrbo("Servicing context %p\n", c);

	/* Check operation status. */
	unsigned int check_hs_aes = k_sem_count_get(cmrt_dd_sem((void *)c->hs_aes));
	unsigned int check_pdma = k_sem_count_get(cmrt_dd_sem((void *)c->pdma));
	if (check_hs_aes == 0 && check_pdma == 0) {
		return;
	}

	/* Remove context from watch list; all of it's AT have been processed. */
	hsdh_watchq_remove_context(c, 1);
	hsdh_watchq_remove_context(c, 0);

	if (c == &hsdh.contexts[0]) {
		/*
		 * It is control channel context. Control channel has a separate
		 * service function. It can only come here while recovering from
		 * an error. There is no batch record to update, so let's return
		 * here.
		 */
		return;
	}

	/*
	 * During normal operation it is safe to check status of HSAES and PDMA
	 * in any order. However in case of an error, abort command needs to be
	 * issued to core that has not erred, otherwise it may endlessly wait on
	 * the other core.
	 *
	 * We check status of first core that we find in ready state
	 * (sem_count != 0). If an error has occurred then abort is issued to
	 * other core and then its operation status can be checked safely.
	 */
	int nr_failed_hs_aes = 0, nr_failed_pdma = 0;
	for (int i = 0; i < 2; i++) {
		if (c->at_busy_hs_aes && check_hs_aes) {
			nr_failed_hs_aes = cri_hs_aes_sync(c->hs_aes);
			if (nr_failed_hs_aes && !hsdh.hw_error) {
				log("hsaes status: 0x%0x\n", sys_read32(CMRT_HSAES_BASE+R_HSAES_STATUS));
				log("pdma status: 0x%0x\n", sys_read32(CMRT_PDMA_BASE+R_PDMA_STATUS));
				cri_pdma_abort(c->pdma);
			}
			check_hs_aes = 0;
			check_pdma = 1;
			c->at_busy_hs_aes = 0;
		}
		if (c->at_busy_pdma && check_pdma) {
			nr_failed_pdma = cri_pdma_sync(c->pdma);
			if (nr_failed_pdma && !hsdh.hw_error) {
				log("hsaes status: 0x%0x\n", sys_read32(CMRT_HSAES_BASE+R_HSAES_STATUS));
				log("pdma status: 0x%0x\n", sys_read32(CMRT_PDMA_BASE+R_PDMA_STATUS));
				cri_hs_aes_abort(c->hs_aes);
			}
			check_pdma = 0;
			check_hs_aes = 1;
			c->at_busy_pdma = 0;
		}
	}

	int nr_failed = nr_failed_hs_aes > nr_failed_pdma ? nr_failed_hs_aes : nr_failed_pdma;
	dbg("   ch %u ATs left %u/%u errored %d\n", c->rec->b.channel, c->nr_pend, c->rec->b.nr_at, nr_failed + c->nr_pend);
	if (nr_failed) {
		/* Mark all pending ATs errored. */
		c->rec->b.nr_err = nr_failed + c->nr_pend;
		c->nr_pend = 0;
		c->rec->type |= HSDH_REC_ERROR | HSDH_REC_DONE;
		if (!hsdh.hw_error) {
			do_hsdh_close_channel(c);
			hsdh_handle_error();
		}
		return;
	}
	if (!c->nr_pend) {
		c->rec->type |= HSDH_REC_DONE;
		c->rec = 0;
		if (c->delayed_close_channel) {
			do_hsdh_close_channel(c);
		}
	}
}

void hsdh_context_add_watch(hsdh_context_t *c, struct k_poll_event *event, hsdh_ec_t *ec, bool is_hs_aes)
{
	cri_handle_t h = is_hs_aes ? (void *)c->hs_aes : (void *)c->pdma;
	u32_t type = K_POLL_TYPE_SEM_AVAILABLE;
	if (!cri_is_valid(h)) {
		dbg("WARN: context %p has invalid %s context %p, removed from watchlist\n", c, is_hs_aes ? "HSAES" : "PDMA", h);
		k_poll_event_init(event, K_POLL_TYPE_IGNORE, K_POLL_MODE_NOTIFY_ONLY, 0);
		hsdh_watchq_remove_context(c, is_hs_aes);
		return;
	}
	if ((is_hs_aes && c->at_busy_hs_aes) ||
			(!is_hs_aes && c->at_busy_pdma)) {
		k_poll_event_init(event, type, K_POLL_MODE_NOTIFY_ONLY, cmrt_dd_sem(h));
		ec->context = c;
		ec->is_hs_aes = is_hs_aes;
		return;
	}
	dbg("WARN: context %p does not have active ATs\n", c);
}

int hsdh_prepare_events(struct k_poll_event *events, int nr_events)
{
	/* First three events are reserved for sic, control channel and HSDH thread signal. */
	k_poll_event_init(&events[0], K_POLL_TYPE_SEM_AVAILABLE, K_POLL_MODE_NOTIFY_ONLY, cmrt_dd_sem(hsdh.sic));
	if (hsdh.ctrl.context) {
		hsdh_context_add_watch(hsdh.ctrl.context, &events[1], &hsdh.ec[1], 0 /* PDMA */);
	} else {
		/* Control channel is not open; still reserve its event. */
		k_poll_event_init(&events[1], K_POLL_TYPE_IGNORE, K_POLL_MODE_NOTIFY_ONLY, 0);
	}
	k_poll_event_init(&events[2], K_POLL_TYPE_SIGNAL, K_POLL_MODE_NOTIFY_ONLY, &hsdh.worker_signal);

	/* Rest of the events are used for contexts on watch list. */
	int n = 3;
	hsdh_context_t *c;
	SYS_SLIST_FOR_EACH_CONTAINER(&hsdh.l_ctx__watch_hs_aes, c, ln__watch_hs_aes) {
		hsdh_context_add_watch(c, &events[n], &hsdh.ec[n], 1 /* HSAES */);
		n++;
	}
	SYS_SLIST_FOR_EACH_CONTAINER(&hsdh.l_ctx__watch_pdma, c, ln__watch_pdma) {
		hsdh_context_add_watch(c, &events[n], &hsdh.ec[n], 0 /* PDMA */);
		n++;
	}
	return n;
}

int service_sic(void)
{
	int ret = cri_sic_sync(hsdh.sic);
	if (ret) {
		log("ERROR: sic read sync failed %d\n", ret);
		return ret;
	}

	/* Process command. */
	void *data = hsdh.sic_buf;
	hsdh_process_request(&data, &hsdh.sic_size);

	if (hsdh.sic_size > sizeof(hsdh.sic_buf)) {
		log("SIC reply overruns buffer %u/%u\n", hsdh.sic_size, sizeof(hsdh.sic_buf));
		return -75; /* -EOVERFLOW */
	}
	ret = cri_sic_write(hsdh.sic, data, hsdh.sic_size, hsdh.peerid);
	if (ret) {
		log("ERROR: sic write failed %d\n", ret);
		return ret;
	}
	hsdh.sic_size = sizeof(hsdh.sic_buf);
	ret = cri_sic_read(hsdh.sic, hsdh.sic_buf, &hsdh.sic_size, &hsdh.peerid);
	if (ret) {
		log("ERROR: sic read setup failed %d\n", ret);
		return ret;
	}
	dbg("HSDH waiting for SIC message\n");
	return 0;
}

int hsdh_wait_and_service(void)
{
	/* Wait on events. */
	int n = hsdh_prepare_events(hsdh.events, NR_EVENTS);
	bool notify_esw = 0;

	int ret = k_poll(hsdh.events, n, K_FOREVER);
	if (ret == -EAGAIN) {
		/* No event happened; nothing to do. */
		return ret;
	} else if (ret < 0) {
		return WORKER_STOP(ret, "ERROR: k_poll failed\n");
	} else {
		dbg("--------------------------------------------------\n");

		/* Service control channel. */
		if (hsdh.events[1].state == K_POLL_STATE_SEM_AVAILABLE) {
			notify_esw = hsdh_service_ctrl_channel();
		}
		/* Service HSAES and PDMA contexts. */
		for (int i = 3; i < n && !hsdh.hw_error; ++i) {
			if (hsdh.events[i].state == K_POLL_STATE_SEM_AVAILABLE) {
				/* Check operation status and update batch records. */
				hsdh_service_context(hsdh.ec[i].context);
			}
		}

		/* Process batch. */
		hsdh_service_batch();

		/* Process sic request. */
		if (hsdh.events[0].state == K_POLL_STATE_SEM_AVAILABLE) {
			ret = service_sic();
			if (ret) {
				return WORKER_STOP(ret, "ERROR: sic operation failed");
			}
		}

		/*
		 * Reset signal here instead of hsdh_prepare_events() to avoid
		 * it getting lost, if it is raised between here and hsdh_prepare_events().
		 */
		k_poll_signal_init(&hsdh.worker_signal);
		while (hsdh.hlos2esw_interrupt) {
			dbg("\n\nnew request batch\n");
			hsdh.hlos2esw_interrupt = 0;

			if (!hsdh.ctrl.hlos_pa) {
				log("ERROR: can't pull batch, control channel is not configured\n");
				break;
			}
			enum batch_state *state = &hsdh.batches[0].state;
			if (*state != BATCH_NOT_IN_USE) {
				log("ERROR: can't pull batch %d in state %s\n", 0, batch_state_str(*state));
				break;
			}
			*state = BATCH_PULL;
			hsdh_service_batch();
		}
	}
	if (notify_esw) {
		dbg("send interrupt to hlos\n");
		sys_write32(1<<2, CMRT_SIC_BASE+R_SOC_INTERRUPT_OUT);
	}
	return 0;
}

static void hsdh_irq_handler(void *arg)
{
	ARG_UNUSED(arg);

	dbg("interrupt from hlos\n");
	/* Acknowledge interrupt and wakeup HSDH thread. */
	sys_write32(1 << SOC_HSDH_INTERRUPT_IN, CMRT_SIC_BASE+R_CORE_INTERRUPT);
	hsdh.hlos2esw_interrupt = 1;
	k_poll_signal_raise(&hsdh.worker_signal, 0);
}

static void hsdh_work_loop(void)
{
	dbg("hsdh work loop started\n");
	do {
		hsdh_wait_and_service();
	/* Check if thread need to stop. */
	} while (hsdh.state_next != WORKER_STOPPED);

	dbg("hsdh work loop ended\n");
}

static void hsdh_cleanup(void);
static int hsdh_init(u32_t flowid)
{
	vrbo("\n");

	IRQ_CONNECT(CMRT_SOC_IRQ(SOC_HSDH_INTERRUPT_IN), 0, hsdh_irq_handler, NULL, 0);
	irq_enable(CMRT_SOC_IRQ(SOC_HSDH_INTERRUPT_IN));
	irq_enable(CMRT_PDMA_SOC_IRQ);
	irq_enable(CMRT_HSAES_SOC_IRQ);
	k_poll_signal_init(&hsdh.worker_signal);

	/* Open control channel. */
	if (hsdh_open_ctrl_channel()) {
		goto out;
	}

	/* Setup SIC. */
	hsdh.sic = cri_sic_open(0, flowid);
	if (!cri_is_valid(hsdh.sic)) {
		log("can not open SIC at flowid %u\n", flowid);
		goto out;
	}
	hsdh.sic_size = sizeof(hsdh.sic_buf);
	int ret = cri_sic_read(hsdh.sic, hsdh.sic_buf, &hsdh.sic_size, &hsdh.peerid);
	if (ret < 0) {
		log("sic read setup failed %d\n", ret);
		goto out;
	}
	log("HSDH service ready for SIC requests at flowid %u\n", flowid);
	return 0;
out:
	hsdh_cleanup();
	return 1;
}

static void hsdh_cleanup(void)
{
	/* Close all open context. */
	for (int i = 0; i < NR_CONTEXTS; i++) {
		hsdh_context_t *c = &hsdh.contexts[i];
		if (cri_is_valid(c->hs_aes)) {
			cri_hs_aes_close(c->hs_aes);
		}
		if (cri_is_valid(c->pdma)) {
			cri_pdma_close(c->pdma);
		}
		*c = (hsdh_context_t) { 0 };
		hsdh_set_snode_dequeued(&hsdh.contexts[i].ln__watch_hs_aes);
		hsdh_set_snode_dequeued(&hsdh.contexts[i].ln__watch_pdma);
	}
	/* Reset state. */
	cri_sic_close(hsdh.sic);
	hsdh = (struct hsdh) { 0 };

	irq_disable(CMRT_SOC_IRQ(SOC_HSDH_INTERRUPT_IN));
	irq_disable(CMRT_PDMA_SOC_IRQ);
	irq_disable(CMRT_HSAES_SOC_IRQ);
}

void hsdh_worker(void *flowid, void *unused1, void *unused2)
{
	log("hsdh worker starting ...\n");
	hsdh.state = WORKER_STARTING;
	if (!hsdh_init((u32_t)flowid)) {
		hsdh.state = WORKER_RUNNING;
		hsdh_work_loop();
		hsdh_cleanup();
	}
	hsdh.state = WORKER_STOPPED;
	log("hsdh worker stopped\n");
}

static int wait_on_worker(enum worker_state to_state)
{
	for (int i = 0; i < 10; i++) {
		if (to_state == hsdh.state) {
			return 0;
		}
		k_sleep(100);
	}
	return 1;
}

typedef struct {
	/* to eSW */
	u32_t cmd;
#define CMD_ENABLE 1
#define CMD_DISABLE 2
#define CMD_GET_STATE 3

	u32_t flowid;

	/* to HLOS */
	u32_t state;
} hsdh_msg_t;

#define STACK_SIZE (1024*8)
static K_THREAD_STACK_DEFINE(hsdh_stack, STACK_SIZE);
static struct k_thread hsdh_k_thread;
static int hsdh_ctrl(void *input, u32_t in_used, void *output, u32_t *out_used, u32_t out_size)
{
	hsdh_msg_t *args = (hsdh_msg_t *) input;
	hsdh_msg_t *resp = (hsdh_msg_t *) output;
	*out_used = sizeof(hsdh_msg_t);

	*resp = (hsdh_msg_t) {};
	switch (args->cmd) {
	case CMD_ENABLE:
		if (wait_on_worker(WORKER_STOPPED)) {
			return -EBUSY;
		}

		hsdh.state_next = WORKER_RUNNING;
		k_thread_create(&hsdh_k_thread, hsdh_stack, STACK_SIZE,
				hsdh_worker, (void *) args->flowid, NULL, NULL,
				CONFIG_MAIN_THREAD_PRIORITY, 0, K_NO_WAIT);
		if (wait_on_worker(WORKER_RUNNING)) {
			hsdh.state_next = WORKER_STOPPED;
			return -EFAULT;
		}
		break;
	case CMD_DISABLE:
		if (wait_on_worker(WORKER_STARTING) && wait_on_worker(WORKER_RUNNING)) {
			return -ESRCH;
		}
		hsdh.state_next = WORKER_STOPPED;
		k_poll_signal_raise(&hsdh.worker_signal, 0);
		if (wait_on_worker(WORKER_STOPPED)) {
			return -ETIMEDOUT;
		}
		break;
	case CMD_GET_STATE:
		/* Done below. */
		break;
	default:
		return -EINVAL;
	}
	resp->state = hsdh.state;
	return 0;
}

const cmd_t cmd_hsdh = { CMDID_HSDH, "HSDH", "Hight Speed Data Handler (HSDH) service", hsdh_ctrl };
