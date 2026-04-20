/*
 * Copyright (c) 2019-2023 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

/**
 * @file
 * @brief Sample container demonstrate trusted communication between
 *        HLOS Application(teectest) and CMRT container.
 */

#include <stdbool.h>

#include <container.h>
#include <logging/log.h>
#include <drivers/cmrt/cmrt.h>
#include <drivers/cmrt/dmac.h>
#include <drivers/cmrt/sic.h>
#include <drivers/cmrt/sac_mem.h>

#include <cmrt/tee_client_api.h> /* TEEC_MEMREF values */
#include <cmrt/tee_client_abi.h>
#include <cmrt/tee_error.h>

static uint32_t invoke_command(teec_abi_invokecommand_t *c)
{
	LOG_INF("Input offset %d and size %d",
		(int)c->params[0].memref.offset, (int)c->params[0].memref.size);
	LOG_INF("Output offset %d and size %d",
		(int)c->params[1].memref.offset, (int)c->params[1].memref.size);

	/* Copy input buffer to output for the test application. */
	void *src = (void *)(SAC_MEMORY_BASE + c->params[0].memref.offset);
	void *dst = (void *)(SAC_MEMORY_BASE + c->params[1].memref.offset);

	const cmrt_dmac_t dma = cmrt_dmac_open(CMRT_O_SYNC);
	if (!cmrt_is_valid(dma)) {
		LOG_ERR("DMA open failed");
		return TEE_ERROR_COMMUNICATION;
	}
	int res = cmrt_dmac_data(dma, (uint32_t)src, (uint32_t)dst,
				 c->params[0].memref.size, 0);
	if (res) {
		LOG_ERR("Cannot dma copy dest:%p src:%p len:%d res:%d",
			dst, src, (int)c->params[0].memref.size, res);
	}
	cmrt_dmac_close(dma);
	return res == 0 ? TEE_SUCCESS : TEE_ERROR_EXCESS_DATA;
}

enum { TEEC_MEMREF = 4 };

static bool memrefin(uint16_t v)
{
	return (v & (TEEC_MEMREF | TEEC_MEM_INPUT)) == (TEEC_MEMREF | TEEC_MEM_INPUT);
}

static bool memrefout(uint16_t v)
{
	return (v & (TEEC_MEMREF | TEEC_MEM_OUTPUT)) == (TEEC_MEMREF | TEEC_MEM_OUTPUT);
}

/* Valid parameters have two memref arguments (in->out.)-- they can
 * be either memref temp, whole, or partial. There's no check on the
 * actual offsets here -- we will let the memory management crash us
 * in case they point outside our access range.
 */
static bool validargs(uint16_t v)
{
	return memrefin(TEEC_PARAM_TYPE_GET(v, 0)) &&
		memrefout(TEEC_PARAM_TYPE_GET(v, 1)) &&
		TEEC_PARAM_TYPE_GET(v, 2) == TEEC_NONE &&
		TEEC_PARAM_TYPE_GET(v, 3) == TEEC_NONE;
}

static int process_tee_message(teec_abi_header_t *h, size_t s)
{
	static int session_id;

	if (s < sizeof(teec_abi_header_t) ||
	    h->magic != CMRT_TEEC_MAGIC ||
	    h->version[0] != CMRT_TEEC_ABI_MAJOR) {
		LOG_ERR("Invalid TEE header!");
		return TEE_ERROR_BAD_FORMAT;
	}
	switch (h->type) {
	case TEEC_ABI_MSG_OPEN_SESSION:
		LOG_INF("Open session %d", session_id);
		if (s < sizeof(teec_abi_opensession_t)) {
			LOG_ERR("Invalid TEE command!");
			return TEE_ERROR_BAD_FORMAT;
		}
		h->session = session_id++;
		break;
	case TEEC_ABI_MSG_CLOSE_SESSION:
		LOG_INF("Close session %d", (int)h->session);
		if (s < sizeof(teec_abi_closesession_t)) {
			LOG_ERR("Invalid TEE command!");
			return TEE_ERROR_BAD_FORMAT;
		}
		break;
	case TEEC_ABI_MSG_INVOKE_COMMAND:
		LOG_INF("Invoke command %d", (int)h->cmdres);
		if (s < sizeof(teec_abi_invokecommand_t)) {
			LOG_ERR("Invalid TEE command!");
			return TEE_ERROR_BAD_FORMAT;
		}
		if (!validargs(h->param_types)) {
			LOG_ERR("Invalid parameters!");
			return TEE_ERROR_BAD_PARAMETERS;
		}
		h->cmdres = invoke_command((teec_abi_invokecommand_t *)h);
		break;
	case TEEC_ABI_MSG_REQUEST_CANCELLATION:
		LOG_INF("Request cancellation %d", (int)h->session);
		if (s < sizeof(teec_abi_requestcancellation_t)) {
			LOG_ERR("Invalid TEE command!");
			return TEE_ERROR_BAD_FORMAT;
		}
		break;
	default:
		LOG_INF("Unknown request %x (ABI change?)", (int)h->type);
		return TEE_ERROR_GENERIC;
	}
	return TEE_SUCCESS;
}

void container(void *p1, void *p2, void *p3)
{
	(void)p2;
	(void)p3;

	LOG_INF("teec container starting...");

	uint32_t flowid = (uint32_t)p1;
	cmrt_sic_t sic = cmrt_sic_open(CMRT_O_SYNC, flowid);
	if (!cmrt_is_valid(sic)) {
		LOG_ERR("SIC open failed");
		return;
	}
	while (true) {
		char buffer[256];
		size_t buflen = sizeof(buffer);
		uint32_t peerid = 0;
		int res = cmrt_sic_read(sic, buffer, &buflen, &peerid, 0);
		if (res < 0) {
			LOG_INF("Failed to read from HLOS: %d!", res);
			break;
		}
		LOG_INF("Received sic message from 0x%x", (int)peerid);
		res = process_tee_message((teec_abi_header_t *)buffer, buflen);
		if (res) break;
		LOG_INF("Sending sic message to 0x%x", (int)peerid);
		cmrt_sic_write(sic, buffer, buflen, peerid);
	}
	cmrt_sic_close(sic);
	LOG_INF("teec container exiting");
}
