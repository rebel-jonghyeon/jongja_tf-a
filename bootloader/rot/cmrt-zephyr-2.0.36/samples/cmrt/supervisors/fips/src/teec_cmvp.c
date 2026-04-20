/*
 * Copyright (c) 2020-2021 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

#include <zephyr.h>
#include <device.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <ctype.h>

#include <teefs.h>
#include <cri/cmrt/teedev_dmac.h>
#include <cri/cmrt/aes.h>
#include <cri/cmrt/hc.h>
#include <cri/cmrt/sic.h>
#include <cri/cmrt/kdc.h>
#include <cri/cmrt/ktc.h>

#include <cri/cmrt/fips/fips_types.h>

#include "cmvp_sw.h"
#include "fips.h"
#include "teec_cmvp.h"

enum { TEEC_MEMREF = 4 };

int process_tee_message(fips_state_t *state,
	io_t *input)
{
	int status = 0;

	teec_abi_header_t *h = (teec_abi_header_t *) input->data;
	size_t s = (size_t)input->size;

	dprintk("Processing message\n");

	if ((s < sizeof(teec_abi_header_t)) ||
		(h->magic != CMRT_TEEC_MAGIC) ||
		(h->version[0] != CMRT_TEEC_ABI_MAJOR)) {
		dprintk("Invalid TEE header!");
		status = -EINVAL;
		goto direct_exit;
	}

	switch (h->type) {
	case TEEC_ABI_MSG_OPEN_SESSION:
		dprintk("Open session\n");

		if (s < sizeof(teec_abi_opensession_t)) {
			dprintk("Invalid TEE command!\n");
			status = -EINVAL;
			goto direct_exit;
		}
		/* only support one single session */
		if (state->teec_session) {
			dprintk("Session is in use\n");
			status = -EBUSY;
			goto direct_exit;
		}

		dprintk("Going to login.\n");
		status = fips_login(state, h);
		if (status) {
			dprintk("Error during login");
			goto direct_exit;
		}

		state->teec_session = 1;

		break;

	case TEEC_ABI_MSG_CLOSE_SESSION:
		dprintk("Close session %d\n", h->session);
		if (s < sizeof(teec_abi_closesession_t)) {
			dprintk("Invalid TEE command!");
			status = -EINVAL;
			goto direct_exit;
		}

		if (!state->teec_session) {
			dprintk("No session to close");
			status = -EINVAL;
			goto direct_exit;
		}

		status = fips_logout(state, h);
		if (status) {
			goto direct_exit;
		}

		state->teec_session = 0;
		dprintk("Closed session\n");
		status = TEEC_SUCCESS;
		break;
	case TEEC_ABI_MSG_INVOKE_COMMAND:
		dprintk("Invoke command %d\n", h->cmdres);
		if (s < sizeof(teec_abi_invokecommand_t)) {
			dprintk("Invalid TEE command!");
			status = -EINVAL;
			goto direct_exit;
		}

		if ((!state->teec_session) && (!state->authenticated_login_started)) {
			dprintk("Session not started");
			status = -EINVAL;
			goto direct_exit;
		}

		status = fips_service_command(state, (teec_abi_invokecommand_t *)h);
		dprintk("Returning from fips service command with %d\n", status);

		break;
	case TEEC_ABI_MSG_REQUEST_CANCELLATION:
		dprintk("Request cancellation %d\n", h->session);
		if (s < sizeof(teec_abi_requestcancellation_t)) {
			dprintk("Invalid TEE command!");
			status = -EINVAL;
			goto direct_exit;
		}
		break;
	default:
		dprintk("Unknown request %x (ABI change?)\n", h->type);
		status = -EINVAL;
	}

direct_exit:
	return status;
}
