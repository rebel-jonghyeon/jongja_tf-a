/*
 * Copyright (c) 2017-2023 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

#define DT_DRV_COMPAT rambus_cmrt_sic2

#include <device.h>
#include <sys/sys_io.h>
#include <drivers/cmrt/dd.h>
#include <drivers/cmrt/sic.h>
#ifdef CONFIG_CMRT_DMAC
#include <drivers/cmrt/dmac.h>
#endif
#include <drivers/cmrt/sac.h>
#include <drivers/cmrt/util.h>
#include <sys/__assert.h>
#include <string.h>
#include <errno.h>
#include <assert.h>

#include <logging/log.h>
LOG_MODULE_DECLARE(cmrt, CONFIG_CMRT_LOG_LEVEL);

#define R_BASE DT_INST_REG_ADDR(0)
static_assert(R_BASE == CMRT_SIC_BASE); /* device tree must match headers */
#if CMRT_SIC_NUM_INSTANCES >= 32
static_assert(CONFIG_SOC_NUM_IRQS == 32);
#else
static_assert(CONFIG_SOC_NUM_IRQS >= CMRT_SIC_NUM_INSTANCES);
#endif

#define LOG_SIC LOG_DBG
#define LOG_HEXDUMP_SIC LOG_HEXDUMP_DBG

typedef struct {
	uint32_t flowid;
	uint8_t *buffer;
	uint32_t buflen;
	uint32_t flags;
	int length;
	int index;
	uint32_t address_high; /* set for read if data is in ext RAM */
	uint32_t address_low; /* set for read if data is in ext RAM */
	uint64_t uptime;
} cmrt_sic_rw_t;

typedef struct cmrt_sic_context {
	cmrt_dd_context_t ddc;
	uint32_t flowid;
	cmrt_sic_rw_t recv;
	uint32_t *peerid;
	uint32_t *buflen;
	uint32_t lasthdr;
	cmrt_sic_rw_t send;
	uint32_t timeout;
} cmrt_sic_buffer_t;

#ifdef CONFIG_MULTITHREADING
#define SIC_BUFFERS (9u + CMRT_SIC_NUM_INSTANCES)
#else
#define SIC_BUFFERS (3u)
#endif
static CMRT_DD_CONTEXT cmrt_sic_buffer_t buffers[SIC_BUFFERS];

static cmrt_sic_buffer_t *request[CMRT_SIC_NUM_INSTANCES];

static void sic_init_rw(cmrt_sic_rw_t *rw)
{
	rw->flowid = -1;
	rw->buffer = NULL;
	rw->buflen = 0;
	rw->length = 0;
	rw->index = -1;
	rw->address_high = 0;
	rw->address_low = 0;
	rw->uptime = 0;
}

static void sic_reset_buffer(cmrt_sic_buffer_t *b)
{
	sic_init_rw(&b->recv);
	b->peerid = NULL;
	b->buflen = NULL;
	sic_init_rw(&b->send);
}

static int sic_find_buffer_cb(cmrt_dd_context_t *ddc, void *arg)
{
	cmrt_sic_buffer_t *b = (cmrt_sic_buffer_t *)ddc;
	uint32_t flowid = (uint32_t)(uintptr_t)arg;

	return flowid == b->flowid || flowid == CMRT_DD_WILDCARD ? 0 : -EAGAIN;
}

static int sic_open_buffer_cb(cmrt_dd_context_t *ddc, void *arg)
{
	cmrt_sic_buffer_t *b = (cmrt_sic_buffer_t *)ddc;
	uint32_t flowid = (uint32_t)(uintptr_t)arg;

	b->flowid = GET_FLOWID(flowid);
	b->timeout = GET_SICTIMEOUT(flowid);

	return 0;
}

static int sic_get_send_buffer(cmrt_sic_buffer_t *b,
							   const uint8_t *buffer, uint32_t buflen, uint32_t flowid)
{
	cmrt_sic_rw_t *rw = &b->send;

	if (rw->flowid != -1 || rw->buffer) {
		/* Buffer is active, cannot use. */
		return -EBUSY;
	}

	rw->flowid = flowid;
	rw->buffer = (uint8_t *)buffer; /* transmit buffer not written to */
	rw->buflen = buflen;
	rw->flags = 0;
	rw->length = 0;
	rw->index = -1;
	rw->uptime = 0;
	b->lasthdr = 0; /* reset last header always when sending */

	return 0;
}

static int sic_get_recv_buffer(cmrt_sic_buffer_t *b,
							   uint8_t *buffer, uint32_t buflen, uint32_t flags)
{
	cmrt_sic_rw_t *rw = &b->recv;

	if (rw->flowid != -1) {
		return -EBUSY;
	}

	rw->buffer = buffer;
	rw->buflen = buflen;
	rw->flags = flags;
	rw->uptime = 0;

	return 0;
}

static void sic_put_buffer(cmrt_sic_buffer_t *b)
{
	if (b->peerid) {
		*b->peerid = b->recv.flowid;
	}

	if (b->buflen) {
		*b->buflen = b->recv.length;
	}

#ifdef CONFIG_MULTITHREADING
	k_sem_reset(&b->ddc.sem);
#endif
	sic_reset_buffer(b);
}

static bool sic_done_buffer(cmrt_sic_buffer_t *b)
{
	if ((b->recv.index < b->recv.length && b->recv.buffer) ||
	    (b->send.index < b->send.length && b->send.flowid != -1)) {

		/* Not yet completed. */
		return false;
	}

	return true;
}

static bool sic_receive_buffer(volatile cmrt_sic_buffer_t *b)
{
	return b->recv.buffer && b->recv.index < 0;
}

static bool sic_active_buffer(volatile cmrt_sic_buffer_t *b)
{
	return b->recv.buffer || b->send.flowid != -1;
}

static int sic_local_copy(cmrt_dd_t *dd, cmrt_sic_buffer_t *src)
{
	int rv = 0;
	cmrt_sic_buffer_t *dst = cmrt_dd_find_context(dd,
												  (void *)(intptr_t)GET_FLOWID(src->send.flowid),
												  sic_find_buffer_cb);

	if (!dst) {
		/* No target flowid. */
		rv = -ENOENT;
		goto out;
	}

	uint32_t allowed = GET_SICID(dst->recv.flags);

	if (allowed != 0 && allowed != LOCAL_SICID) {
		/* Not allowed SIC instance. */
		rv = -EACCES;
		goto out;
	}

	if (!sic_receive_buffer(dst)) {
		/* Buffer is not receiving. */
		rv = -EBUSY;
		goto out;
	}

	if (src->send.buflen > dst->recv.buflen) {
		/* Not enough buffer space. */
		rv = -ENOSPC;
		goto out;
	}

	/* Prepare receiver buffer for sync. */
	dst->recv.flowid = SET_LOCAL_SICID(src->flowid);
	dst->recv.length = src->send.buflen;

	if ((dst->recv.flags & CMRT_SIC_ALIGN_RIGHT) == CMRT_SIC_ALIGN_RIGHT) {
		/* Right align the data. */
		uint32_t alignment = dst->recv.buflen - ROUND_UP(dst->recv.length, sizeof(uint32_t));

		dst->recv.buffer += alignment;
	}

	dst->recv.index = src->send.buflen;
	dst->recv.address_high = src->send.address_high;
	dst->recv.address_low = src->send.address_low;

	/* Copy the actual data from sender to receiver. */
	if (dst->recv.address_high == 0u && dst->recv.address_low == 0u) {
		(void)memcpy(dst->recv.buffer, src->send.buffer, src->send.buflen);
	}

	/* Prepare sender buffer for sync. */
	src->send.length = src->send.buflen;
	src->send.index = src->send.buflen;
#ifdef CONFIG_MULTITHREADING
	/* Notify sender that write was done. */
	k_sem_give(&src->ddc.sem);
	/* Finally notify receiver that read completed. */
	k_sem_give(&dst->ddc.sem);
#endif
	return 0;
 out:
	/*
	 * Not able to send data locally, reset sender buffer and
	 * return error to tell sic_write to send an error to caller.
	 */
	sic_put_buffer(src);

	return rv;
}

#define sic_read32(i, r) sys_read32((mm_reg_t)(R_BASE + (r) + ((i) * SIC_INSTANCE_OFFSET)))
#define sic_write32(v, i, r) sys_write32((v), (mm_reg_t)(R_BASE + (r) + ((i) * SIC_INSTANCE_OFFSET)))

static bool sic_read_message(uint32_t id, cmrt_sic2_message_t *m)
{
	if (id >= CMRT_SIC_NUM_INSTANCES || sic_read32(id, R_HLOS2ESW0_D0) == 0u) {
		return false;
	}

	for (int i = 0; i < SIC2_DATA_REGS; i++) {
		m->raw.data[i] = sic_read32(id, R_HLOS2ESW0_D0 + i * 4);
	}

	LOG_HEXDUMP_SIC(m, sizeof(cmrt_sic2_message_t), "sic_read_message:");

	return true;
}

static void sic_write_message(uint32_t id, cmrt_sic2_message_t *m)
{
	if (id < CMRT_SIC_NUM_INSTANCES) {
		for (int i = SIC2_DATA_REGS - 1; i >= 0; i--) {
			/* Write backwards so that D0 is written last. */
			sic_write32(m->raw.data[i], id, R_ESW2HLOS0_D0 + i * 4);
		}
		LOG_HEXDUMP_SIC(m, sizeof(cmrt_sic2_message_t), "sic_write_message:");
	}
}

static void sic_send_now(uint32_t id, uint32_t src, uint32_t dst, uint32_t status, uint32_t error)
{
	cmrt_sic2_message_t m;

	memset(&m, 0, sizeof(m));
	SET_HEADER_VER(m.hdr.hdr, 2u);
	SET_HEADER_SRC(m.hdr.hdr, src);
	SET_HEADER_CMD(m.hdr.hdr, CMD_RESPONSE);
	SET_HEADER_DST(m.hdr.hdr, dst);
	m.res.length = 0;
	m.res.address_high = status;
	m.res.address_low = error;
	sic_write_message(id, &m);
	/* SIC instance id defines the interrupt line. */
	sys_write32(1 << (id & 31), (mm_reg_t)(R_BASE + R_SOC_INTERRUPT_OUT));
}

static void sic_finish_last(cmrt_sic_buffer_t *b)
{
	for (uint32_t id = 0; id < CMRT_SIC_NUM_INSTANCES; id++) {
		if (request[id] == b) {
			if (b->lasthdr != 0) {
				/* Re-read or close after read, send null. */
				sic_send_now(id, GET_HEADER_SRC(b->lasthdr), GET_HEADER_DST(b->lasthdr), 0, 0);
			}
			request[id] = NULL;
		}
	}
	b->lasthdr = 0;
}

static inline bool sic_is_receiving(cmrt_sic_buffer_t *b)
{
	return b->recv.index != -1 && b->recv.index < b->recv.length;
}

static inline bool sic_is_sending(cmrt_sic_buffer_t *b)
{
	return b->send.index != -1 && b->send.index < b->send.length;
}

static void sic_handle_request(uint32_t id, cmrt_sic2_message_t *m, cmrt_dd_t *dd)
{
	uint32_t h = m->hdr.hdr;
	uint32_t ver = GET_HEADER_VER(h);
	uint32_t src = GET_HEADER_SRC(h);
	uint32_t cmd = GET_HEADER_CMD(h);
	uint32_t dst = GET_HEADER_DST(h);

	if (ver != 2u) {
		return;
	}

	if (cmd == CMD_REQUEST) {
		LOG_SIC("new request id=%d src=0x%X dst=0x%X len=%d\n",
				(int)id, src, dst, m->req.length);

		cmrt_sic_buffer_t *b = cmrt_dd_find_context(dd, (void *)(uintptr_t)dst, sic_find_buffer_cb);

		if (!b) {
			/* No target flowid. */
			return sic_send_now(id, src, dst, 0, ENOENT);
		}

		if (sic_is_sending(b)) {
			if (id == GET_SICID(b->send.flowid)) {
				/* Terminate sending via SIC registers, new
				 * request was written to the same instance.
				 */
				b->lasthdr = h;
			}
		}

		uint32_t allowed = GET_SICID(b->recv.flags);

		if (allowed != 0 && allowed != id) {
			/* Not allowed SIC instance. */
			return sic_send_now(id, src, dst, 0, EACCES);
		}

		if (!sic_receive_buffer(b)) {
			/* Buffer is not receiving. */
			return sic_send_now(id, src, dst, 0, EBUSY);
		}

		/* We have target for the request. */
		if (m->req.length > b->recv.buflen) {
			/* Not enough buffer space. */
			return sic_send_now(id, src, dst, 0, ENOSPC);
		}
		/* Data fits into buffer. */
		k_tid_t thread = b->ddc.tid;

		if (m->req.address_low != 0 ||
		    m->req.address_high != 0) {
			uint64_t addr = (uint64_t)m->req.address_high << 32 | m->req.address_low;

			if (!is_aligned(m->req.address_low, 4u) ||
			    !cmrt_sac_has_access(thread, addr, m->req.length, false)) {
				/* Data is not in SAC or access is not allowed */
				return sic_send_now(id, src, dst, 0, EPERM);
			}
			/* Data is in SAC and access is allowed */
			b->recv.index = m->req.length;
			b->recv.address_high = m->req.address_high;
			b->recv.address_low = m->req.address_low;
		} else {
			/* Data via SIC registers. */
			b->recv.index = 0;
		}
		b->recv.flowid = SET_SICID(src, id);
		b->recv.length = m->req.length;
		if ((b->recv.flags & CMRT_SIC_ALIGN_RIGHT) == CMRT_SIC_ALIGN_RIGHT) {
			/* Right align the data. */
			uint32_t alignment = b->recv.buflen - ROUND_UP(b->recv.length, sizeof(uint32_t));

			b->recv.buffer += alignment;
		}
		b->lasthdr = h;
		request[id] = b;

#ifdef CONFIG_MULTITHREADING
		k_sem_give((struct k_sem *)&b->ddc.sem);
#endif
	} else if (cmd == CMD_CONTROL) {
		if (m->ctrl.cmd == SIDEBAND_PING) {
			if (cmrt_dd_find_context(dd, (void *)(uintptr_t)dst, sic_find_buffer_cb)) {
				/* There is a reader. */
				return sic_send_now(id, src, dst, SIDEBAND_PONG2, 0);
			}
			/* No such flowid, is anyone listening? */
			if (cmrt_dd_find_context(dd, (void *)(uintptr_t)CMRT_DD_WILDCARD, sic_find_buffer_cb)) {
				/* There is a reader. */
				return sic_send_now(id, src, dst, SIDEBAND_PONG1, 0);
			}
			return sic_send_now(id, src, dst, SIDEBAND_PONG0, 0);
		} else if (m->ctrl.cmd == SIDEBAND_RESET) {
			request[id] = NULL;
			return sic_send_now(id, src, dst, 0, 0);
		}
		/* Unknown control command. */
		return sic_send_now(id, src, dst, 0, EINVAL);
	}
	/* Skip all unknown commands and data commands. */
}

int z_impl_cmrt_sic_read(cmrt_sic_t context, void *buffer, size_t *buflen,
						 uint32_t *peerid, uint32_t flags)
{
	if (!cmrt_dd_valid(context) || !buffer || !buflen || !peerid) {
		return -EINVAL;
	}
#ifdef CONFIG_CMRT_DMAC
	if (!is_aligned(buffer, 4u)) {
		/* Require word alignment for possible DMA in sic_sync. */
		return -EINVAL;
	}
#endif
	if (IS_SAC_SPACE(buffer, *buflen)) {
		/* Receive buffer cannot be in SAC. */
		return -EINVAL;
	}

	cmrt_dd_t *dd = context->ddc.dd;
	uint32_t mask = cmrt_dd_lock(dd);
	cmrt_sic_buffer_t *b = context;
	int rv = sic_get_recv_buffer(b, buffer, *buflen, flags);

	if (rv == 0) {
		sic_finish_last(b);
		b->buflen = buflen;
		b->peerid = peerid;
	}
	cmrt_dd_unlock(dd, mask);

	return cmrt_dd_autosync(&context->ddc, rv);
}

int z_impl_cmrt_sic_write(cmrt_sic_t context, const void *buffer, size_t buflen, uint32_t peerid)
{
	if (!cmrt_dd_valid(context) || (!buffer && buflen != 0u)) {
		return -EINVAL;
	}
#ifdef CONFIG_CMRT_DMAC
	if (!is_aligned(buffer, 4u)) {
		/* Require word alignment for possible DMA in sic_sync. */
		return -EINVAL;
	}
#endif
	if (IS_SAC_SPACE(buffer, buflen) &&
	    !cmrt_sac_has_access(NULL, cmrt_sac_translate((mem_addr_t)buffer), buflen, false)) {
		/* Cannot use this SAC area. */
		return -EPERM;
	}

	uint32_t id = GET_SICID(peerid);

	if (id >= CMRT_SIC_NUM_INSTANCES && !IS_LOCAL_SICID(peerid)) {
		/* Invalid SIC instance. */
		return -EINVAL;
	}

	cmrt_dd_t *dd = context->ddc.dd;
	uint32_t mask = cmrt_dd_lock(dd);
	cmrt_sic_buffer_t *b = context;
	int rv = sic_get_send_buffer(b, buffer, buflen, peerid);

	if (rv == 0) {
		if (IS_LOCAL_SICID(peerid)) {
			/* Local thread to thread message. */
			rv = sic_local_copy(dd, b);
		} else if (b != request[id]) {
			/* This request is not active. */
			sic_reset_buffer(b);
			rv = -ENXIO;
		} else {
			/* The normal case, response to HLOS. */
			cmrt_sic2_message_t m;

			m.hdr.hdr = 0;
			SET_HEADER_VER(m.hdr.hdr, 2u);
			SET_HEADER_SRC(m.hdr.hdr, peerid);
			SET_HEADER_CMD(m.hdr.hdr, CMD_RESPONSE);
			m.res.length = buflen;
			if (IS_SAC_SPACE(buffer, buflen)) {
				uint64_t addr = cmrt_sac_translate((mem_addr_t)buffer);

				m.res.address_high = (uint32_t)(addr >> 32);
				m.res.address_low = (uint32_t)addr;
				b->send.index = buflen;
			} else {
				m.res.address_high = 0;
				m.res.address_low = 0;
				b->send.index = 0;
			}
			b->send.length = buflen;
			SET_HEADER_DST(m.hdr.hdr, b->flowid);
			sic_write_message(id, &m);
			/* SIC instance id defines the interrupt line. */
			sys_write32(1 << (id & 31), (mm_reg_t)(R_BASE + R_SOC_INTERRUPT_OUT));
			rv = 0;
		}
	}
#ifdef CONFIG_MULTITHREADING
	if (rv == 0) {
		/* Sync requires the semaphore to be set. */
		k_sem_give((struct k_sem *)&b->ddc.sem);
	}
#endif
	cmrt_dd_unlock(dd, mask);
	if ((context->ddc.flags & CMRT_O_ASYNC) != 0u) {
		/* Do not sync write in async mode. */
		return rv;
	}

	/* Otherwise write will sync automatically. */
	return rv < 0 ? rv : cmrt_dd_sync(&context->ddc);
}

static int sic_sync_dma(uint32_t src, uint32_t dst, uint32_t len)
{
	int rv = -ENOENT;
#ifdef CONFIG_CMRT_DMAC
	while (len > 0) {
		cmrt_dmac_t dmac = cmrt_dmac_open(CMRT_O_SYNC);

		if (!cmrt_dd_valid(dmac)) {
			break;
		}

		uint32_t dmalen = (len > (DMAC_DATA_DST_SIZE_MASK << 2)) ?
			(DMAC_DATA_DST_SIZE_MASK << 2) : len;

		rv = cmrt_dmac_data(dmac, src, dst, dmalen, 0);
		cmrt_dmac_close(dmac);

		if (rv != 0) {
			break;
		}

		src += dmalen >> 2;
		dst += dmalen >> 2;
		len -= dmalen;
	}
#endif
	return rv;
}

static int sic_poll_cb(cmrt_dd_context_t *ddc)
{
	cmrt_sic2_message_t m;
	cmrt_sic_buffer_t *b = (cmrt_sic_buffer_t *)ddc;

	if (!sic_active_buffer(b)) {
		/* Transaction was canceled. */
		b->lasthdr = 0; /* no null answer */
		sic_put_buffer(b);
		LOG_SIC("Transaction was canceled");

		return -EINTR;
	}

	if (sic_is_receiving(b)) {
		/* Handle request via SIC. */
		uint32_t id = GET_SICID(b->recv.flowid);

		if (id >= CMRT_SIC_NUM_INSTANCES || b != request[id]) {
			/* Serving different request now. */
			b->lasthdr = 0; /* no null answer */
			sic_put_buffer(b);
			LOG_SIC("Serving different request now (recv)");
			return -EINTR;
		}

		if (sic_read_message(id, &m)) {
			uint32_t h = m.hdr.hdr;
			uint32_t ver = GET_HEADER_VER(h);
			uint32_t src = SET_SICID(GET_HEADER_SRC(h), id);
			uint32_t cmd = GET_HEADER_CMD(h);
			uint32_t dst = GET_HEADER_DST(h);

			if (ver == 2u && src == b->recv.flowid && cmd == CMD_DATA && dst == b->flowid) {
				/* Valid packet for this flow. */
				sic_write32(0, id, R_HLOS2ESW0_D0);
				uint32_t length = b->recv.length - b->recv.index < sizeof(m.data.data) ?
								  b->recv.length - b->recv.index : sizeof(m.data.data);

				(void)memcpy(b->recv.buffer + b->recv.index, m.data.data, length);
				b->recv.index += length;
			} else {
				/* Something else, let irq handler take it. */
				b->lasthdr = 0; /* no null answer */
				sic_put_buffer(b);
				LOG_SIC("Something else, let irq handler take it");

				return -EINTR;
			}
		} else if (b->timeout != 0) {
			/* Monitor HLOS slowness. */
			uint64_t uptime = cmrt_uptime_get();

			if (b->recv.uptime == 0) {
				/* Set reference time. */
				b->recv.uptime = uptime;
			} else if (b->recv.uptime + b->timeout < uptime) {
				/* HLOS is too slow! */
				b->lasthdr = 0; /* no null answer */
				sic_put_buffer(b);

				return -ETIMEDOUT;
			}
		}
	}
	if (sic_is_sending(b)) {
		/* Handle response via SIC. */
		uint32_t id = GET_SICID(b->send.flowid);

		if (id >= CMRT_SIC_NUM_INSTANCES || b != request[id] ||
		    b->lasthdr != 0u) {
			/* Serving different request now. */
			b->lasthdr = 0; /* no null answer */
			sic_put_buffer(b);
			LOG_SIC("Serving different request now (send)");

			return -EINTR;
		}

		if (sic_read32(id, R_ESW2HLOS0_D0) == 0u) {
			m.hdr.hdr = 0;
			SET_HEADER_VER(m.hdr.hdr, 2u);
			SET_HEADER_SRC(m.hdr.hdr, b->send.flowid);
			SET_HEADER_CMD(m.hdr.hdr, CMD_DATA);
			SET_HEADER_DST(m.hdr.hdr, b->flowid);
			uint32_t length = b->send.length - b->send.index < sizeof(m.data.data) ?
							  b->send.length - b->send.index : sizeof(m.data.data);

			(void)memcpy(m.data.data, b->send.buffer + b->send.index, length);
			b->send.index += length;
			sic_write_message(id, &m);
		} else if (b->timeout != 0) {
			/* Monitor HLOS slowness. */
			uint64_t uptime = cmrt_uptime_get();

			if (b->send.uptime == 0) {
				/* Set reference time. */
				b->send.uptime = uptime;
			} else if (b->send.uptime + b->timeout < uptime) {
				/* HLOS is too slow! */
				sic_put_buffer(b);

				return -ETIMEDOUT;
			}
		}
	}
	return sic_done_buffer(b) ? 0 : 1;
}

static int sic_sync_cb(cmrt_dd_context_t *ddc, uint32_t *mask)
{
	cmrt_sic_buffer_t *b = (cmrt_sic_buffer_t *)ddc;
	cmrt_dd_t *dd = ddc->dd;
	int rv = 0;

	if (b->recv.address_high != 0u || b->recv.address_low != 0u) {
		/* Use DMAC to move data from external RAM. */
		uint64_t addr = (uint64_t)b->recv.address_high << 32 | b->recv.address_low;
		uint64_t base = cmrt_sac_get_base(NULL);

		rv = cmrt_sac_set_base(NULL, addr & (0xFFFFFFFFULL << 32 | CPU_ADDR_LO_MASK));

		if (rv == 0) {
			uint32_t src = SAC_MEMORY_BASE + (addr & ~CPU_ADDR_LO_MASK);
			uint32_t dst = (uint32_t)b->recv.buffer;
			uint32_t len = ROUND_UP(b->recv.length, sizeof(uint32_t));

			cmrt_dd_unlock(dd, *mask);
			if (len > 0) {
				rv = sic_sync_dma(src, dst, len);
			}
			*mask = cmrt_dd_lock(dd);
			(void)cmrt_sac_set_base(NULL, base); /* restore base */
		}
	}
	sic_put_buffer(b);

	return rv;
}

static void sic_init_buffer_cb(cmrt_dd_context_t *ddc)
{
	cmrt_sic_buffer_t *b = (cmrt_sic_buffer_t *)ddc;

	sic_finish_last(b);
	sic_reset_buffer(b);
	b->flowid = -1;
}

bool cmrt_sic_is_idle(void)
{
	for (int id = 0; id < CMRT_SIC_NUM_INSTANCES; id++) {
		if (!request[id]) {
			return false;
		}
	}
	return true;
}

static cmrt_dd_t sic_dd = {
	.base = CMRT_SIC_BASE,
	.is_locking = 0,
	.context_count = SIC_BUFFERS,
	.context_size = sizeof(cmrt_sic_buffer_t),
	.irq_mask = CMRT_SIC_IRQ_MASK,
	.contexts = buffers,
};

static void sic_irq_handler(const void *arg)
{
	ARG_UNUSED(arg);

	/* Get pending interrupts and clear them. */
	uint32_t pending = sys_read32((mm_reg_t)(R_BASE + R_CORE_INTERRUPT));
	uint32_t mask = sys_read32((mm_reg_t)(R_BASE + R_CORE_INTERRUPT_MASK));

	/* Clear all bits, including those we cannot handle yet. */
	sys_write32(mask, (mm_reg_t)(R_BASE + R_CORE_INTERRUPT));
	LOG_SIC("pending irqs 0x%x mask 0x%x\n", pending, mask);
	pending &= mask; /* handle only those that are set in the mask */

	for (uint32_t id = 0; id < CMRT_SIC_NUM_INSTANCES; id++) {
		/* SIC instance id defines the interrupt line. */
		uint32_t bit = 1 << (id & 31);

		if ((pending & bit) != 0u) {
			/* Process incoming request. */
			cmrt_sic2_message_t m;

			if (sic_read_message(id, &m)) {
				sic_write32(0, id, R_HLOS2ESW0_D0);
				sic_handle_request(id, &m, &sic_dd);
			}
		}
	}
	/* Handle SOC interrupts. */
	pending &= CMRT_SOC_INTERRUPT_IN_MASK;
	(void)cmrt_slic_irq_handler(pending);
}

void cmrt_sic_init_early(cmrt_sic_t context)
{
	ARG_UNUSED(context);
	/* Clear interrupt mask when going from machine to supervisor */
	sys_write32(0, (mm_reg_t)(R_BASE + R_CORE_INTERRUPT_MASK));
}

static int cmrt_sic_init(const struct device *dev)
{
	/* Init SIC buffers (= contexts). */
	cmrt_dd_t *dd = dev->data;

	cmrt_dd_init(dd, dev);

	/* Setup IRQ handler for SIC driver. */
	IRQ_CONNECT(CMRT_SIC_IRQ, 0, sic_irq_handler, NULL, 0);

	/* Enable IRQs for SIC driver */
	uint32_t mask = sys_read32((mm_reg_t)(R_BASE + R_CORE_INTERRUPT_MASK));

	sys_write32(mask | CMRT_SIC_IRQ_MASK, (mm_reg_t)(R_BASE + R_CORE_INTERRUPT_MASK));

	return 0;
}

static const struct cmrt_driver_api sic_driver_api = {
	.open_cb = sic_open_buffer_cb,
	.find_cb = sic_find_buffer_cb,
	.poll_cb = sic_poll_cb,
	.sync_cb = sic_sync_cb,
	.close_cb = sic_init_buffer_cb,
};

DEVICE_DT_INST_DEFINE(0, cmrt_sic_init, NULL, &sic_dd, NULL,
					  PRE_KERNEL_1, CONFIG_KERNEL_INIT_PRIORITY_DEVICE,
					  (void *)&sic_driver_api);

cmrt_sic_t z_impl_cmrt_sic_open(uint32_t flags, uint32_t flowid)
{
	return (cmrt_sic_t)cmrt_dd_open(DEVICE_DT_INST_GET(0), flags, (void *)(uintptr_t)flowid);
}

void z_impl_cmrt_sic_close(cmrt_sic_t context)
{
	if (cmrt_dd_valid(context)) {
		cmrt_dd_close((cmrt_dd_context_t *)context);
	}
}

int z_impl_cmrt_sic_sync(cmrt_sic_t context)
{
	if (!cmrt_dd_valid(context)) {
		return -EINVAL;
	}
	if ((context->ddc.flags & CMRT_O_SYNC) != 0u) {
		/* Already synced internally. */
		return 0;
	}
	return cmrt_dd_sync((cmrt_dd_context_t *)context);
}

uint32_t z_impl_cmrt_sic_read_reg(uint32_t reg)
{
	return cmrt_read_reg(CMRT_SIC_BASE, reg);
}

void z_impl_cmrt_sic_write_reg(uint32_t reg, uint32_t value)
{
	cmrt_write_reg(CMRT_SIC_BASE, reg, value);
}

#ifdef CONFIG_USERSPACE
#include <syscall_handler.h>

static inline void z_syscall_verify_sic_context(cmrt_sic_t context)
{
	cmrt_dd_syscall_verify((cmrt_dd_context_t *)context, &sic_driver_api);
}

static inline cmrt_sic_t z_vrfy_cmrt_sic_open(uint32_t flags, uint32_t flowid)
{
	return z_impl_cmrt_sic_open(flags, flowid);
}

#include <syscalls/cmrt_sic_open_mrsh.c>

static inline void z_vrfy_cmrt_sic_close(cmrt_sic_t context)
{
	z_syscall_verify_sic_context(context);
	z_impl_cmrt_sic_close(context);
}

#include <syscalls/cmrt_sic_close_mrsh.c>

static inline int z_vrfy_cmrt_sic_read(cmrt_sic_t context, void *buffer, size_t *buflen,
									   uint32_t *peerid, uint32_t flags)
{
	z_syscall_verify_sic_context(context);
	Z_OOPS(Z_SYSCALL_MEMORY_WRITE(buffer, *buflen));
	Z_OOPS(Z_SYSCALL_MEMORY_WRITE(peerid, sizeof(*peerid)));
	return z_impl_cmrt_sic_read(context, buffer, buflen, peerid, flags);
}

#include <syscalls/cmrt_sic_read_mrsh.c>

static inline int z_vrfy_cmrt_sic_write(cmrt_sic_t context, const void *buffer, size_t buflen,
										uint32_t peerid)
{
	z_syscall_verify_sic_context(context);
	Z_OOPS(Z_SYSCALL_MEMORY_READ(buffer, buflen));
	return z_impl_cmrt_sic_write(context, buffer, buflen, peerid);
}

#include <syscalls/cmrt_sic_write_mrsh.c>

static inline int z_vrfy_cmrt_sic_sync(cmrt_sic_t context)
{
	z_syscall_verify_sic_context(context);
	return z_impl_cmrt_sic_sync(context);
}

#include <syscalls/cmrt_sic_sync_mrsh.c>

static bool is_custom_reg(uint32_t reg)
{
	return is_aligned(reg, 4u) &&
		((reg >= R_CUSTOM_0) &&
		 (reg < (R_CUSTOM_0 + (4u * CMRT_SIC_NUM_CUSTOM))));

}

static bool is_user_allowed_reg(uint32_t reg)
{
	return (reg == R_SCRATCH_0) || is_custom_reg(reg);
}

static inline uint32_t z_vrfy_cmrt_sic_read_reg(uint32_t reg)
{
	Z_OOPS(Z_SYSCALL_VERIFY(is_user_allowed_reg(reg)));
	return z_impl_cmrt_sic_read_reg(reg);
}

#include <syscalls/cmrt_sic_read_reg_mrsh.c>

static inline void z_vrfy_cmrt_sic_write_reg(uint32_t reg, uint32_t value)
{
	Z_OOPS(Z_SYSCALL_VERIFY(is_user_allowed_reg(reg)));
	return z_impl_cmrt_sic_write_reg(reg, value);
}

#include <syscalls/cmrt_sic_write_reg_mrsh.c>

#endif /* CONFIG_USERSPACE */
