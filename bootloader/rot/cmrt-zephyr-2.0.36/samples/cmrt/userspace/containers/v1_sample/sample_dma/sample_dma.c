/*
 * Copyright (c) 2018-2023 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

/**
 * @file
 * @brief Sample container to demonstrate supported dma operations.
 */

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

#include <cri/cmrt.h>
#include <cri/cmrt/sic.h>
#include <cri/cmrt/sac.h>
#include <cri/cmrt/dmac.h>
#include "crisyscall-user.h"
#include "crilog-user.h"

enum {
	DMA_COPY_RAM_TO_EXTMEM = 1,
	DMA_REVERSE_COPY_RAM_TO_EXTMEM = 2,
	DMA_COPY_EXTMEM_TO_RAM = 3,
	DMA_REVERSE_COPY_EXTMEM_TO_RAM = 4,
	DMA_COPY_EXTMEM_TO_EXTMEM = 5,
	DMA_REVERSE_COPY_EXTMEM_TO_EXTMEM = 6,
	DMA_FILL_EXTMEM = 7,
	DMA_MEMCOPY = 8,
	DMA_REVERSE_MEMCOPY = 9,
	DMA_MEMSET_EXTMEM = 10,
	SAC_SEGMENT_CONFIG = 11,
	DIRECT_MEM_READ = 12,
	DIRECT_MEM_WRITE = 13
};

struct ram_to_extmem {
	uint32_t command;
	uint32_t addr;
	uint32_t len;
	unsigned char data[0];
};

struct extmem_to_ram {
	uint32_t command;
	uint32_t addr;
	uint32_t len;
};

struct extmem_to_extmem {
	uint32_t command;
	uint32_t dst_addr;
	uint32_t src_addr;
	uint32_t len;
};

# pragma pack (1)
struct fill_extmem {
	uint32_t command;
	uint32_t addr;
	uint32_t len;
	uint8_t  val;
};

struct sac_segment_config {
	uint32_t command;
	uint32_t index;
	uint32_t value;
};

#define _CMSG_DATA_BUF_WORDS 32
#define _CMSG_DATA_BUF_SIZE ((_CMSG_DATA_BUF_WORDS) * sizeof(uint32_t))

/*
 * Note: Somewhat experimental; this always turned out to be more
 *       complex than anticipated...
 */
static union {
	uint32_t command;
	char msgbuf[sizeof(struct ram_to_extmem) + _CMSG_DATA_BUF_SIZE];
	struct {
		uint32_t command; /* "data" when filled */
		char buf[_CMSG_DATA_BUF_SIZE + 8];
	} response_data;
	struct ram_to_extmem ram_to_extmem;
	struct extmem_to_ram extmem_to_ram;
	struct extmem_to_extmem extmem_to_extmem;
	struct fill_extmem fill_extmem;
	struct sac_segment_config sac_segment_config;
} cmsg_blob;

/* had to adjust sizes for coverity to not complain, now check all add up */
static_assert (sizeof cmsg_blob == sizeof cmsg_blob.response_data, "");
static_assert (sizeof cmsg_blob == sizeof cmsg_blob.msgbuf, "");

static_assert (sizeof cmsg_blob.command == 4, "");
static const size_t cmsg_max_data_bufsize =
	sizeof cmsg_blob - sizeof cmsg_blob.command;

static cri_sic_t sic;
static uint32_t peer;

#define response_message(fmt, ...) \
	snprintf(cmsg_blob.msgbuf, sizeof cmsg_blob, fmt, ##__VA_ARGS__)

static int respond_status(int status)
{
	c_log("Container response: peer %d status: %d\n", peer, status);
	return response_message("Status: %d", status);
}

static int respond_data(size_t dlen)
{
	c_log("Container response: peer %d data len: %u\n", peer, dlen);

	memcpy(cmsg_blob.msgbuf, "data", 4);
	return sizeof cmsg_blob.command + dlen;
}

static int dma_copy_and_poll(void *dst, const void *src, size_t n,
			     uint32_t rvse_copy)
{
	if (n == 0) return 0;

	void *res = NULL;

	cri_dmac_t dma = cri_dmac_open(0);
	if (!cri_is_valid(dma)) {
		c_error("DMA open failed: %d\n", dma);
		return -1;
	}
	const int copy_result = rvse_copy
		? cri_dmac_data_ex(dma, (uint32_t)src, (uint32_t)dst, n, DESC_SWPDSTBYTES_BIT | DESC_DECDSTADDR_BIT)
		: cri_dmac_data(dma, (uint32_t)src, (uint32_t)dst, n);

	if (copy_result == 0) {
		int ret = cri_wait(1, &dma, CRI_FOREVER);

		if (ret > 0) {
			if (cri_dmac_sync(dma) >= 0)
				res = dst;
		}
	}

	cri_dmac_close(dma);

	if (res == NULL) {
		c_error("DMA poll failed: %x\n", res);
		c_log("DMAC copy failed\n");
		return -1;
	}
	return 0;
}

static int dma_fill_and_poll(void *dst, int value, size_t n)
{
	if (n == 0) return 0;

	void *p = NULL;
	cri_dmac_t dma = cri_dmac_open(0);

	if (!cri_is_valid(dma)) {
		c_error("DMA open failed: %d\n", dma);
		return -1;
	}
	int res = cri_dmac_fill(dma, value, (uint32_t)dst, n);

	if (res >= 0) {
		int ret = cri_wait(1, &dma, CRI_FOREVER);

		if (ret > 0) {
			res = cri_dmac_sync(dma);
			if (res >= 0)
				p = dst;
		}
	}

	cri_dmac_close(dma);

	if (p == NULL) {
		c_error("DMA poll failed: %x\n", res);
		c_log("DMAC Fill failed\n");
		return -1;
	}
	return 0;
}

#define LOG_VAR(var) do { c_log("value of " #var ": 0x%08x\n", var); } while (0)

static int handle_sic_data(size_t rl)
{
	int res = -1;
	if (rl < 4) {
		c_log("Short msg: %d < 4\n", rl);
		return response_message("Error: short message (%d bytes)", rl);
	}
	LOG_VAR(cmsg_blob.command);
	switch (cmsg_blob.command) {

	case DMA_REVERSE_COPY_RAM_TO_EXTMEM:
	case DMA_COPY_RAM_TO_EXTMEM: {
		if (rl < sizeof cmsg_blob.ram_to_extmem) {
			c_log("Short msg for DMA copy (len %d)\n", rl);
			break;
		}
		struct ram_to_extmem *c = &cmsg_blob.ram_to_extmem;
		LOG_VAR(c->addr);
		LOG_VAR(c->len); /* note: wild lengths accepted here */

		if (cmsg_blob.command == DMA_REVERSE_COPY_RAM_TO_EXTMEM)
			res = dma_copy_and_poll((void *)c->addr,
						c->data, c->len, 1);
		else
			res = dma_copy_and_poll((void *)c->addr,
						c->data, c->len, 0);
		if (res) {
			c_log("dma_memcpy() failed: %d\n", res);
			break;
		}
		return respond_status(0);
	}
	case DMA_REVERSE_COPY_EXTMEM_TO_RAM:
	case DMA_COPY_EXTMEM_TO_RAM: {
		if (rl < sizeof(struct extmem_to_ram)) {
			c_log("Short msg for DMA copy (len %d)\n", rl);
			break;
		}
		struct extmem_to_ram *c = &cmsg_blob.extmem_to_ram;
		LOG_VAR(c->addr);
		LOG_VAR(c->len);
		if (c->len > cmsg_max_data_bufsize) {
			c_log("Request length too large (%d > %d)\n",
			      c->len, cmsg_max_data_bufsize);
			break;
		}
		const void *addr = (const void *)c->addr;
		const uint32_t len = c->len;

		if (cmsg_blob.command == DMA_REVERSE_COPY_EXTMEM_TO_RAM)
			res = dma_copy_and_poll(cmsg_blob.response_data.buf,
						addr, len, 1);
		else
			res = dma_copy_and_poll(cmsg_blob.response_data.buf,
						addr, len, 0);
		if (res) {
			c_log("dma_memcpy() failed: %d\n", res);
			break;
		}
		LOG_VAR(len);
		return respond_data(len);
	}
	case DMA_REVERSE_COPY_EXTMEM_TO_EXTMEM:
	case DMA_COPY_EXTMEM_TO_EXTMEM: {
		if (rl < sizeof cmsg_blob.extmem_to_extmem) {
			c_log("Short msg for Ext to Ext DMA copy (len %d)\n", rl);
			break;
		}
		struct extmem_to_extmem *c = &cmsg_blob.extmem_to_extmem;
		LOG_VAR(c->dst_addr);
		LOG_VAR(c->src_addr);
		LOG_VAR(c->len); /* note: wild lengths accepted here */

		if (cmsg_blob.command == DMA_REVERSE_COPY_EXTMEM_TO_EXTMEM)
			res = dma_copy_and_poll((void *)c->dst_addr,
						(void *)c->src_addr, c->len, 1);
		else
			res = dma_copy_and_poll((void *)c->dst_addr,
						(void *)c->src_addr, c->len, 0);
		if (res) {
			c_log("dma_memcpy() failed: %d\n", res);
			break;
		}
		return respond_status(0);
	}
	case DMA_FILL_EXTMEM: {
		if (rl < sizeof(struct fill_extmem)) {
			c_log("Short msg for DMA fill (len %d)\n", rl);
			break;
		}
		struct fill_extmem *c = &cmsg_blob.fill_extmem;
		LOG_VAR(c->addr);
		LOG_VAR(c->len);
		LOG_VAR(c->val);
		res = dma_fill_and_poll((void *)c->addr, c->val, c->len);
		if (res) {
			c_log("cri_dma_fill() failed\n");
			break;
		}
		return respond_status(0);
	}
	case DMA_MEMSET_EXTMEM: {
		if (rl < sizeof(struct fill_extmem)) {
			c_log("Short msg for DMA memset (len %d)\n", rl);
			break;
		}
		struct fill_extmem *c = &cmsg_blob.fill_extmem;
		LOG_VAR(c->addr);
		LOG_VAR(c->len);
		LOG_VAR(c->val);

		cri_dmac_t dma = cri_dmac_open(0);
		if (!cri_is_valid(dma)) {
			c_error("DMA open failed: %d\n", dma);
			return -1;
		}
		res = cri_dmac_fill(dma, c->val, c->addr, c->len);
		if (res) {
			c_log("cri_dmac_fill() failed\n");
			cri_dmac_close(dma);
			break;
		}
		res = cri_dmac_sync(dma);
		cri_dmac_close(dma);
		if (res) {
			c_log("cri_dmac_sync() failed\n");
			break;
		}
		return respond_status(0);
	}
	case DMA_REVERSE_MEMCOPY:
	case DMA_MEMCOPY: {
		/* Copy message from extmem to internal buffer,
		 * reverse and send it back */
		if (rl < sizeof(struct extmem_to_ram)) {
			c_log("Short msg for DMA memcopy (len %d)\n", rl);
			break;
		}
		struct extmem_to_ram *c = &cmsg_blob.extmem_to_ram;
		LOG_VAR(c->addr);
		LOG_VAR(c->len);
		if (c->len > cmsg_max_data_bufsize) {
			c_log("Request length too large (%d > %d)\n",
			      c->len, cmsg_max_data_bufsize);
			break;
		}
		cri_dmac_t dma = cri_dmac_open(0);
		if (!cri_is_valid(dma)) {
			c_error("DMA open failed: %d\n", dma);
			res = -1;
			break;
		}
		const uint32_t len = c->len;
		if (cmsg_blob.command == DMA_REVERSE_MEMCOPY)
			res = cri_dmac_data_ex(dma, c->addr, (uint32_t)cmsg_blob.response_data.buf,
					       len, DESC_SWPDSTBYTES_BIT | DESC_DECDSTADDR_BIT);
		else
			res = cri_dmac_data(dma, c->addr, (uint32_t)cmsg_blob.response_data.buf, len);

		if (res) {
			c_log("cri_dmac_data[_ex]() failed\n");
			cri_dmac_close(dma);
			break;
		}
		res = cri_dmac_sync(dma);
		cri_dmac_close(dma);
		if (res) {
			c_log("cri_dmac_sync() failed\n");
			break;
		}
		LOG_VAR(len);
		hexdump(cmsg_blob.response_data.buf, len);
		return respond_data(len);
	}
	case SAC_SEGMENT_CONFIG: {
		if (rl < sizeof(struct sac_segment_config)) {
			c_log("Short msg for SAC Segment Config "
			      "(len %d)\n", rl);
			break;
		}
		struct sac_segment_config *c = &cmsg_blob.sac_segment_config;
		LOG_VAR(c->index);
		LOG_VAR(c->value);
		res = cri_sac_segment_config(c->index, c->value);
		if (res) {
			c_log("SAC segment configuration failed for index %d, "
			      "value %x; response %d\n",
			      c->index, c->value, res);
			break;
		}
		c_log("sac segment configured: index %d value %x\n",
		      c->index, c->value);
		return respond_status(0);
	}
	case DIRECT_MEM_READ: {
		/* note: expect crash with some address ranges */
		if (rl < sizeof(struct extmem_to_ram)) {
			c_log("Short msg for direct mem read (len %d)\n", rl);
			break;
		}
		struct extmem_to_ram *c = &cmsg_blob.extmem_to_ram;
		LOG_VAR(c->addr);
		LOG_VAR(c->len);
		if (c->len > cmsg_max_data_bufsize) {
			c_log("Request length too large (%d > %d)\n",
			      c->len, cmsg_max_data_bufsize);
			break;
		}
		const void *addr = (const void *)c->addr;
		const uint32_t len = c->len;
		memcpy(cmsg_blob.response_data.buf, addr, len);
		/* may have crashed in memcpy() above */
		return respond_data(len);
	}
	case DIRECT_MEM_WRITE: {
		/* note: expect crash with some address ranges */
		if (rl < sizeof(struct ram_to_extmem)) {
			c_log("Short msg for direct mem write (len %d)\n", rl);
			break;
		}
		/* note: not checking that there is c->len bytes of data... */
		struct ram_to_extmem *c = &cmsg_blob.ram_to_extmem;
		LOG_VAR(c->addr);
		LOG_VAR(c->len);
		memcpy((void *)c->addr, c->data, c->len);
		/* note: may crash before next line if dest... inaccessible */
		return respond_status(0);
	}
	default:
		c_log("'%x': unknown command\n", cmsg_blob.command);
		break;
	}

	/* when not responded and returned above */
	return response_message("Error: request failed. Read eSW log.");
}

int main(void)
{
	c_log("Sample (dma) container starting; open sic flow %d\n",
	      CRI_UNIT_CONTAINER_SAMPLE);

	sic = cri_sic_open(0, CRI_UNIT_CONTAINER_SAMPLE);
	if (!cri_is_valid(sic)) {
		c_error("SIC open failed: %d\n", sic);
		return 1;
	}
	cri_log("cri_sic_open(%d) returned fd %d\n",
		CRI_UNIT_CONTAINER_SAMPLE, sic);

	c_log("Call cri_sic_read(%d, &cmsg_blob, %d)\n", sic,
	      sizeof(cmsg_blob));
	size_t msglen = sizeof(cmsg_blob);
	int err = cri_sic_read(sic, &cmsg_blob, &msglen, &peer);
	c_log("cri_sic_read() returned %d\n", err);
	if (err) goto out;

	while (true) {
		c_log("Call cri_wait(1, {%d}, 30s)\n", sic);
		const int fout = cri_wait(1, &sic, CRI_SECONDS(30));
		c_log("cri_wait(1, {%d}, 30s) returned %d\n", sic, fout);

		if ((fout > 0) && (fout & 1u)) {
			err = cri_sic_sync(sic);
			c_log("cri_sic_sync() returned %d\n", err);
			if (err) break;

			c_log("Received sic message from 0x%x (%u bytes)\n",
			      peer, msglen);

			msglen = handle_sic_data(msglen);
			//if (msglen == 0) break;
			if (msglen > sizeof (cmsg_blob)) {
				c_log("Response length too large (%u > %u)."
				      " Exiting.\n", msglen, sizeof(cmsg_blob));
				break;
			}
			c_log("Sending sic response to 0x%x\n", peer);
			err = cri_sic_write(sic, &cmsg_blob, msglen, peer);
			c_log("cri_sic_write() returned %d\n", err);
			if (err) break;

			c_log("Call cri_sic_read(%d, &cmsg_blob, %d)"
			      "\n", sic, sizeof(cmsg_blob));
			msglen = sizeof(cmsg_blob);
			err = cri_sic_read(sic, &cmsg_blob, &msglen, &peer);
			c_log("cri_sic_read() returned %d\n", err);
			if (err) break;
		}
		else if (fout < 0) {
			c_log("cri_wait() returned %d\n", fout);
			break;
		}
		else {
			c_log("No sic messages in 30 seconds...\n");
		}
	}
out:
	cri_sic_close(sic);
	c_log("Sample container (dma) exiting.\n");
	return 1;
}
