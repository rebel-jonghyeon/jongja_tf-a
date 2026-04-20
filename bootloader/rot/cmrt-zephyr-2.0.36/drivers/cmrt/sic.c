/*
 * Copyright (c) 2017-2023 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

#define DT_DRV_COMPAT rambus_cmrt_sic

#include <device.h>
#include <sys/sys_io.h>
#include <drivers/cmrt/dd.h>
#include <drivers/cmrt/sic.h>
#ifdef CONFIG_CMRT_DMAC
#include <drivers/cmrt/dmac.h>
#endif
#include <drivers/cmrt/sac.h>
#include <sys/__assert.h>
#include <string.h>
#include <errno.h>
#include <assert.h>

#include <logging/log.h>
LOG_MODULE_DECLARE(cmrt, CONFIG_CMRT_LOG_LEVEL);

#define R_BASE DT_INST_REG_ADDR(0)
static_assert(R_BASE == CMRT_SIC_BASE); /* device tree must match headers */

typedef struct {
	uint32_t flowid;
	uint8_t *buffer;
	uint32_t buflen;
	uint32_t flags;
	int length;
	int index;
	uint32_t address; /* set for read if data is in ext RAM */
} cmrt_sic_rw_t;

typedef struct cmrt_sic_context {
	cmrt_dd_context_t ddc;
	uint32_t flowid;
	cmrt_sic_rw_t recv;
	uint32_t *peerid;
	uint32_t *buflen;
	cmrt_sic_rw_t send;
	uint32_t sideband;
} cmrt_sic_buffer_t;

#ifdef CONFIG_MULTITHREADING
#define SIC_BUFFERS 9u
#else
#define SIC_BUFFERS 3u
#endif
CMRT_DD_CONTEXT static cmrt_sic_buffer_t buffers[SIC_BUFFERS];

static volatile cmrt_sic_buffer_t *request;  /* current request */
static volatile cmrt_sic_buffer_t *response; /* current response */

static void sic_init_rw(cmrt_sic_rw_t *rw)
{
	rw->flowid = -1;
	rw->buffer = NULL;
	rw->buflen = 0;
	rw->length = 0;
	rw->index = -1;
	rw->address = 0;
}

static void sic_init_buffer_cb(cmrt_dd_context_t *ddc)
{
	cmrt_sic_buffer_t *b = (cmrt_sic_buffer_t *)ddc;
	b->flowid = -1;
	sic_init_rw(&b->recv);
	b->peerid = NULL;
	b->buflen = NULL;
	sic_init_rw(&b->send);
	b->sideband = 0;
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
	if (flowid <= MAX_ESW_FLOWID) {
		b->flowid = flowid;
		return 0;
	}
	return -EINVAL;
}

static int sic_get_xmit_buffer(cmrt_sic_buffer_t *b,
			       const uint8_t *buffer, uint32_t buflen, uint32_t flowid)
{
	cmrt_sic_rw_t *rw = &b->send;
	if (rw->flowid != -1 || rw->buffer != NULL) {
		/* Buffer is active, cannot use. */
		return -EBUSY;
	}
	rw->flowid = flowid;
	rw->buffer = (uint8_t *)buffer; /* transmit buffer not written to */
	rw->buflen = buflen;
	rw->flags = 0;
	rw->length = 0;
	rw->index = -1;
	return 0;
}

/* When flowid == -1, we're idle, and index == -1. */
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

	return 0;
}

static void sic_put_buffer(cmrt_sic_buffer_t *b)
{
	if (b->peerid != NULL) {
		*b->peerid = b->recv.flowid;
	}
	if (b->buflen != NULL) {
		*b->buflen = b->recv.length;
	}
#ifdef CONFIG_MULTITHREADING
	k_sem_reset(&b->ddc.sem);
#endif
	sic_init_rw(&b->recv);
	b->peerid = NULL;
	b->buflen = NULL;
	sic_init_rw(&b->send);
}

static bool sic_done_buffer(cmrt_sic_buffer_t *b)
{
	if ((b->recv.index < b->recv.length && b->recv.buffer != NULL) ||
	    (b->send.index < b->send.length && b->send.flowid != -1)) {
		/* Not yet completed. */
		return false;
	}
	return true;
}

static bool sic_active_buffer(const cmrt_sic_buffer_t *b)
{
	if (b->flowid == -1) {
		return false;
	}
	if (b->recv.index != -1 &&
	    b->recv.index < b->recv.length) {
		return true;
	}
	if (b->send.index != -1 &&
	    b->send.index < b->send.length) {
		return true;
	}
	return false;
}

static int sic_next_buffer_cb(cmrt_dd_context_t *ddc, void *arg)
{
	ARG_UNUSED(arg);

	/* Find next buffer to send. */
	cmrt_sic_buffer_t *b = (cmrt_sic_buffer_t *)ddc;
	if (b->send.flowid != -1 && b->send.index < 0) {
		return 0;
	}
	return -ENOENT;
}

static bool sic_isrecv_buffer(volatile cmrt_sic_buffer_t *b)
{
	return b->recv.buffer != NULL && b->recv.index < 0;
}

static int sic_local_copy(cmrt_dd_t *dd, cmrt_sic_buffer_t *src)
{
	cmrt_sic_buffer_t *dst = cmrt_dd_find_context(dd, (void *)(intptr_t)src->send.flowid,
						      sic_find_buffer_cb);
	if (dst != NULL && sic_isrecv_buffer(dst)) {
		if (src->send.buflen <= dst->recv.buflen) {
			/* Prepare receiver buffer for sync. */
			dst->recv.flowid = src->flowid;
			dst->recv.length = src->send.buflen;
			if ((dst->recv.flags & CMRT_SIC_ALIGN_RIGHT) == CMRT_SIC_ALIGN_RIGHT) {
				/* Right align the data. */
				uint32_t alignment = dst->recv.buflen - ROUND_UP(dst->recv.length, sizeof(uint32_t));
				dst->recv.buffer += alignment;
			}
			dst->recv.index = src->send.buflen;
			dst->recv.address = src->send.address;
			/* Copy the actual data from sender to receiver. */
			if (dst->recv.address == 0u) {
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
		}
	}
	/*
	 * Not able to send data locally, reset sender buffer and
	 * return EIO to tell sic_write to send an error to caller.
	 */
	sic_put_buffer(src);
	return -EIO;
}

static uint32_t sic_recv_message(cmrt_sic_message_t *m, uint32_t length)
{
	uint32_t words = (length + sizeof(uint32_t) - 1u) >> 2;
	for (uint32_t i = 0; i < words; i++) {
		m->raw.data[i] = sys_read32((mm_reg_t)(R_BASE+R_HLOS2ESW_D0+i*4));
	}
	LOG_HEXDUMP_DBG(m, length, "sic_recv_message:");
	return words;
}

static uint32_t sic_send_message(cmrt_sic_message_t *m, uint32_t length)
{
	uint32_t words = length >> 2;
	if ((length & (sizeof(uint32_t) - 1u)) != 0u) { words++; }
	for (uint32_t i = 0; i < words; i++) {
		sys_write32(m->raw.data[i], (mm_reg_t)(R_BASE+R_ESW2HLOS_D0+i*4));
	}
	LOG_HEXDUMP_DBG(m, length, "sic_send_message:");
	return length;
}

static uint32_t sic_handle_send(cmrt_dd_t *dd)
{
	uint32_t sent = 0;
	if (response != NULL) {
		if (response->sideband != 0u) {
			/* Add sideband reply to length. */
			sent = response->sideband;
			response->sideband = 0;
		}
		cmrt_sic_message_t m;
		m.hdr.hdr = 0;
		SET_HEADER_VER(m.hdr.hdr, 1u);
		SET_HEADER_SRC(m.hdr.hdr, response->flowid);
		if (response->send.index == -1) {
			/* Send response message first. */
			SET_HEADER_CMD(m.hdr.hdr, CMD_RESPONSE);
			SET_HEADER_DST(m.hdr.hdr, response->send.flowid);
			m.res.address = 0;
			m.res.length = response->send.buflen;
			if (IS_SAC_SPACE(response->send.buffer, response->send.buflen)) {
				m.res.address = (uint32_t)response->send.buffer;
			}
			response->send.length = response->send.buflen;
			sent |= sic_send_message(&m, sizeof(cmrt_sic_response_t));
			if (m.res.length == 0u || m.res.address != 0u) {
				/* No data to send, stop here. */
				response->send.index = response->send.length;
#ifdef CONFIG_MULTITHREADING
				k_sem_give((struct k_sem *)&response->ddc.sem);
#endif
				response = cmrt_dd_find_context(dd, NULL, sic_next_buffer_cb);
			} else {
				/* Start sending data on the next round. */
				response->send.index = 0;
			}
		} else if (response->send.index < response->send.length) {
			/* Send data fragments until done. */
			SET_HEADER_CMD(m.hdr.hdr, CMD_DATA);
			SET_HEADER_DST(m.hdr.hdr, response->send.flowid);
			size_t length = response->send.length - response->send.index < sizeof(m.data.data) ? response->send.length - response->send.index : sizeof(m.data.data);
			(void)memcpy((uint8_t *)m.data.data,
				     response->send.buffer + response->send.index, length);
			sent |= sic_send_message(&m, sizeof(cmrt_sic_header_t) + length);
			response->send.index += length;
			if (response->send.index >= response->send.length) {
				/* All done for this response. */
#ifdef CONFIG_MULTITHREADING
				k_sem_give((struct k_sem *)&response->ddc.sem);
#endif
				response = cmrt_dd_find_context(dd, NULL, sic_next_buffer_cb);
			}
		} else {
			/* All data fragments sent. */
		}
	}
	return sent;
}

/*!
 * Start sending.  The send operation is started if the current
 * ESW2HLOS_LENGTH register is zero.  This will prevent the overwrite
 * of an existing message, but has the possibility of losing a
 * sideband message.
 * @param sic dd device driver
 * @param sideband sideband message (0 if none)
 * @return > 0 if send started, <= 0 denote either busy with previous
 * message, or empty message
 */
static int sic_start_sending(cmrt_dd_t *dd, uint32_t sideband)
{
	uint32_t length = sys_read32((mm_reg_t)(R_BASE+R_ESW2HLOS_LENGTH));
	if (length == 0u) {
		length = sideband | sic_handle_send(dd);
		if (length != 0u) {
			sys_write32(length, (mm_reg_t)(R_BASE+R_ESW2HLOS_LENGTH));
			sys_write32(SOC_MESSAGE_INTERRUPT_OUT, (mm_reg_t)(R_BASE+R_SOC_INTERRUPT_OUT));
		}
		return length;
	}
	return -(int)length;
}

/*!
 * Send sideband message.
 * @param dd device driver
 * @param src source flow id
 * @param cmd sideband command
 * @return > 0 if sideband send, 0 for empty, < 0 if not sent due to busy
 */
static int sic_send_sideband(cmrt_dd_t *dd, uint32_t src, uint32_t cmd)
{
	uint32_t sideband = 0;
	SET_HEADER_VER(sideband, 1u);
	SET_HEADER_SRC(sideband, src);
	SET_HEADER_CMD(sideband, cmd);
	LOG_DBG("sending sideband 0x%08x\n", sideband);

	if (response != NULL) {
		/* Next send takes care of sideband too. */
		if (response->sideband != 0u) {
			LOG_DBG("overwriting sideband data 0x%08x => 0x%08x\n",
			      response->sideband, sideband);
		}
		response->sideband = sideband;
	}
	/*
	 * Start the send of the message.  It is possible for sideband
	 * messages to remain lost (the sideband notification is not
	 * retrieved by HLOS side.)  Make sure the new sideband is
	 * sent in every case so the send doesn't get stuck.
	 */
	return sic_start_sending(dd, sideband);
}

static void sic_handle_receive(cmrt_dd_t *dd, uint32_t length)
{
	cmrt_sic_message_t m;
	(void)sic_recv_message(&m, length);
	uint32_t h = m.hdr.hdr;
	uint32_t ver = GET_HEADER_VER(h);
	uint32_t src = GET_HEADER_SRC(h);
	uint32_t cmd = GET_HEADER_CMD(h);
	uint32_t dst = GET_HEADER_DST(h);
	if (ver != 1u || length < sizeof(cmrt_sic_header_t)) {
		return;
	}
	if (cmd == CMD_REQUEST &&
	    length == sizeof(cmrt_sic_request_t)) {
		LOG_DBG("new request src=0x%X dst=0x%X len=%d\n",
			src, dst, m.req.length);
		if (request == NULL) {
			request = cmrt_dd_find_context(dd, (void *)(uintptr_t)dst,
						       sic_find_buffer_cb);
			if (request != NULL) {
				if (sic_isrecv_buffer(request)) {
					/* We have target for the request. */
					if (m.req.length <= request->recv.buflen) {
						/* Data fits into buffer. */
						request->recv.flowid = src;
						request->recv.length = m.req.length;
						if ((request->recv.flags & CMRT_SIC_ALIGN_RIGHT) == CMRT_SIC_ALIGN_RIGHT) {
							/* Right align the data. */
							uint32_t alignment = request->recv.buflen - ROUND_UP(request->recv.length, sizeof(uint32_t));
							request->recv.buffer += alignment;
						}
						if (m.req.address != 0u) {
							/* Data in ext RAM. */
							k_tid_t thread = request->ddc.tid;
							if (is_aligned(m.req.address, 4u) &&
							    IS_SAC_SPACE(m.req.address, m.req.length) &&
							    cmrt_sac_has_access(thread, (uint64_t)m.req.address, m.req.length, false)) {
								/* Data is in SAC area and access is allowed */
								request->recv.index = m.req.length;
								request->recv.address = m.req.address;
#ifdef CONFIG_MULTITHREADING
								k_sem_give((struct k_sem *)&request->ddc.sem);
#endif
								request = NULL;
							} else {
								/* Data is not in SAC area or access is not allowed */
								(void)sic_send_sideband(dd, src, SIDEBAND_EPERM);
								request = NULL;
							}
						} else {
							/* Wait for data. */
							request->recv.index = 0;
							if (request->recv.length == 0) {
#ifdef CONFIG_MULTITHREADING
								/* Zero length data. */
								k_sem_give((struct k_sem *)&request->ddc.sem);
#endif
								request = NULL;
							}
						}
					} else {
						/* Not enough buffer space. */
						(void)sic_send_sideband(dd, src, SIDEBAND_ENOSPC);
						request = NULL;
					}
				} else {
					/* Buffer is not receiving. */
					(void)sic_send_sideband(dd, src, SIDEBAND_EBUSY);
					request = NULL;
				}
			} else {
				/* No target flowid. */
				(void)sic_send_sideband(dd, src, SIDEBAND_ENOENT);
			}
		} else {
			/* Serving another request. */
			(void)sic_send_sideband(dd, src, SIDEBAND_EPIPE);
		}
	} else if (cmd == CMD_DATA &&
		   length > sizeof(cmrt_sic_header_t) &&
		   length <= sizeof(cmrt_sic_message_t)) {
		if (request != NULL) {
			if (src == request->recv.flowid &&
			    dst == request->flowid &&
			    request->recv.index < request->recv.length &&
			    request->recv.index >= 0) {
				length -= sizeof(cmrt_sic_header_t);
				LOG_DBG("request data src=0x%X dst=0x%X len=%d\n",
				       src, dst, length);
				if (length > request->recv.length - request->recv.index) {
					length = request->recv.length - request->recv.index;
				}
				(void)memcpy(request->recv.buffer + request->recv.index,
					     (uint8_t *)m.data.data, length);
				request->recv.index += length;
				if (request->recv.index >= request->recv.length) {
#ifdef CONFIG_MULTITHREADING
					/* Hand over received data to container. */
					k_sem_give((struct k_sem *)&request->ddc.sem);
#endif
					request = NULL;
				}
			}
		}
	} else { /* unknown or not valid, drop */ }
}

static void sic_handle_sideband(cmrt_dd_t *dd, uint32_t sideband)
{
	uint32_t ver = GET_HEADER_VER(sideband);
	uint32_t src = GET_HEADER_SRC(sideband);
	uint32_t cmd = GET_HEADER_CMD(sideband);
	if (ver == 1u) {
		if (cmd == SIDEBAND_RESET && src == HLOS_DD_FLOWID) {
			/*
			 * Reset communications to resolve situations where we
			 * are waiting for data that never comes, for example
			 * due to a buggy HLOS driver.
			 */
			if (request != NULL) {
				request->recv.flowid = -1;
				request->recv.length = 0;
				request->recv.index = -1;
				request->recv.address = 0;
				request = NULL;
			}
			if (response != NULL) {
				response->send.index = response->send.length;
#ifdef CONFIG_MULTITHREADING
				k_sem_give((struct k_sem *)&response->ddc.sem);
#endif
				response = NULL;
			}
		} else if (cmd == SIDEBAND_PING) {
			/* Change command to PONG0 or PONG1. */
			(void)sic_send_sideband(dd, src, cmrt_dd_find_context(dd, (void *)(uintptr_t)CMRT_DD_WILDCARD, sic_find_buffer_cb) != NULL ? SIDEBAND_PONG1 : SIDEBAND_PONG0);
		} else { /* drop invalid commands */ }
	} /* else drop invalid messages */
}

int z_impl_cmrt_sic_read(cmrt_sic_t context, void *buffer, size_t *buflen, uint32_t *peerid, uint32_t flags)
{
	if (!cmrt_dd_valid(context) || buffer == NULL ||
	    buflen == NULL || *buflen == 0u || peerid == NULL) {
		return -EINVAL;
	}
#ifdef CONFIG_CMRT_DMAC
	if (!is_aligned(buffer, 4u) || !is_aligned(*buflen, 4u)) {
		/* Require word alignment for possible DMA in sic_sync. */
		return -EINVAL;
	}
#endif
	if (IS_SAC_SPACE(buffer, *buflen)) {
		/* Receive buffer cannot be in SAC. */
		return -EINVAL;
	}
	int rv = -EIO;
	cmrt_dd_t *dd = context->ddc.dd;
	uint32_t mask = cmrt_dd_lock(dd);
	cmrt_sic_buffer_t *b = context;
	if (b != NULL) {
		rv = sic_get_recv_buffer(b, buffer, *buflen, flags);
		if (rv == 0) {
			b->buflen = buflen;
			b->peerid = peerid;
		}
	}
	cmrt_dd_unlock(dd, mask);
	return cmrt_dd_autosync(&context->ddc, rv);
}

int z_impl_cmrt_sic_write(cmrt_sic_t context, const void *buffer, size_t buflen, uint32_t peerid)
{
	if (!cmrt_dd_valid(context) || (buffer == NULL && buflen != 0u) ||
	    peerid < MIN_ESW_FLOWID || peerid > MAX_HLOS_FLOWID) {
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
	int rv = -EIO;
	cmrt_dd_t *dd = context->ddc.dd;
	uint32_t mask = cmrt_dd_lock(dd);
	cmrt_sic_buffer_t *b = context;
	if (b != NULL) {
		rv = sic_get_xmit_buffer(b, buffer, buflen, peerid);
		if (rv == 0) {
			if (IS_HLOS_FLOWID(peerid)) {
				/* The normal case, response to HLOS. */
				if (response == NULL) {
					/* Kickstart sending. */
					response = cmrt_dd_find_context(dd, NULL, sic_next_buffer_cb);
					(void)sic_start_sending(dd, 0);
				}
			} else {
				/* Local thread to thread message. */
				rv = sic_local_copy(dd, b);
			}
		}
	}
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
		if (!cmrt_dd_valid(dmac)) { break; }
		uint32_t dmalen = (len > (DMAC_DATA_DST_SIZE_MASK << 2)) ?
			(DMAC_DATA_DST_SIZE_MASK << 2) : len;
		rv = cmrt_dmac_data(dmac, src, dst, dmalen, 0);
		cmrt_dmac_close(dmac);
		if (rv != 0) { break; }
		src += dmalen >> 2;
		dst += dmalen >> 2;
		len -= dmalen;
	}
#endif
	return rv;
}

static int sic_poll_cb(cmrt_dd_context_t *ddc)
{
	cmrt_sic_buffer_t *b = (cmrt_sic_buffer_t *)ddc;
	return sic_done_buffer(b) ? 0 : 1;
}

static int sic_sync_cb(cmrt_dd_context_t *ddc, uint32_t *mask)
{
	cmrt_sic_buffer_t *b = (cmrt_sic_buffer_t *)ddc;
	cmrt_dd_t *dd = ddc->dd;
	int rv = 0;
	if (b->recv.address != 0u && b->recv.length != 0) {
		/* Use DMAC to move data from external RAM. */
		uint32_t src = b->recv.address;
		uint32_t dst = (uint32_t)b->recv.buffer;
		uint32_t len = ROUND_UP(b->recv.length, sizeof(uint32_t));
		cmrt_dd_unlock(dd, *mask);
		if (len > 0) {
			rv = sic_sync_dma(src, dst, len);
		}
		*mask = cmrt_dd_lock(dd);
	}
	sic_put_buffer(b);
	return rv;
}

bool cmrt_sic_is_idle(void)
{
	if (sys_read32(R_BASE + R_ESW2HLOS_LENGTH) != 0u) {
		return false;
	}
	for (unsigned int i = 0; i < SIC_BUFFERS; i++) {
		if (sic_active_buffer(&buffers[i])) {
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
	uint32_t pending = sys_read32((mm_reg_t)(R_BASE+R_CORE_INTERRUPT));
	uint32_t mask = sys_read32((mm_reg_t)(R_BASE+R_CORE_INTERRUPT_MASK));
	/* Clear all bits, including those we cannot handle yet. */
	sys_write32(mask, (mm_reg_t)(R_BASE+R_CORE_INTERRUPT));
	LOG_DBG("pending irqs 0x%x mask 0x%x\n", pending, mask);
	pending &= mask; /* handle only those that are set in the mask */

	if ((pending & HLOS2ESW_INTERRUPT_IN) != 0u) {
		/* Process incoming data and possible sideband commands. */
		uint32_t length = sys_read32((mm_reg_t)(R_BASE+R_HLOS2ESW_LENGTH));
		uint32_t sideband = length & SIDEBAND_MASK;
		if (sideband != 0u) {
			sic_handle_sideband(&sic_dd, sideband);
			length &= ~SIDEBAND_MASK;
		}
		if (length != 0u) {
			sic_handle_receive(&sic_dd, length);
		}
		if (sideband != 0u || length != 0u) {
			sys_write32(0, (mm_reg_t)(R_BASE+R_HLOS2ESW_LENGTH));
			sys_write32(SOC_MESSAGE_INTERRUPT_OUT, (mm_reg_t)(R_BASE+R_SOC_INTERRUPT_OUT));
		}
	}
	if ((pending & ESW2HLOS_INTERRUPT_IN) != 0u) {
		/* Process outgoing data. */
		(void)sic_start_sending(&sic_dd, 0);
	}

	/* Handle SOC interrupts. */
	pending &= CMRT_SOC_INTERRUPT_IN_MASK;
	(void)cmrt_slic_irq_handler(pending);
}

void cmrt_sic_init_early(cmrt_sic_t context)
{
	ARG_UNUSED(context);
	/* Clear interrupt mask when going from machine to supervisor */
	sys_write32(0, (mm_reg_t)(R_BASE+R_CORE_INTERRUPT_MASK));
}

static int cmrt_sic_init(const struct device *dev)
{
	/* Init SIC buffers (= contexts). */
	cmrt_dd_t *dd = dev->data;
	cmrt_dd_init(dd, dev);

	/* Setup IRQ handler for SIC driver */
	IRQ_CONNECT(CMRT_SIC_IRQ, 0, sic_irq_handler, NULL, 0);

	/* Enable IRQs for SIC driver */
	uint32_t mask = sys_read32((mm_reg_t)(R_BASE+R_CORE_INTERRUPT_MASK));
	sys_write32(mask | CMRT_SIC_IRQ_MASK, (mm_reg_t)(R_BASE+R_CORE_INTERRUPT_MASK));

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

static inline int z_vrfy_cmrt_sic_read(cmrt_sic_t context, void *buffer, size_t *buflen, uint32_t *peerid, uint32_t flags)
{
	z_syscall_verify_sic_context(context);
	Z_OOPS(Z_SYSCALL_MEMORY_WRITE(buflen, sizeof(*buflen)));
	Z_OOPS(Z_SYSCALL_MEMORY_WRITE(buffer, *buflen));
	Z_OOPS(Z_SYSCALL_MEMORY_WRITE(peerid, sizeof(*peerid)));
	return z_impl_cmrt_sic_read(context, buffer, buflen, peerid, flags);
}
#include <syscalls/cmrt_sic_read_mrsh.c>

static inline int z_vrfy_cmrt_sic_write(cmrt_sic_t context, const void *buffer, size_t buflen, uint32_t peerid)
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
