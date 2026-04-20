/*
 * Copyright (c) 2018, ARM Limited and Contributors. All rights reserved.
 * Copyright (c) 2025, Samsung Electronics Corporation. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <assert.h>
#include <mmio.h>
#include <rebel_sip_svc.h>
#include <common/runtime_svc.h>

#pragma weak rebel_plat_sip_handler
uintptr_t rebel_plat_sip_handler(uint32_t smc_fid,
								 u_register_t x1, u_register_t x2,
								 u_register_t x3, u_register_t x4,
								 void *cookie,
								 void *handle,
								 u_register_t flags)
{
	ERROR("%s: unhandled SMC (0x%x)\n", __func__, smc_fid);
	SMC_RET1(handle, SMC_UNK);
}

uintptr_t rebel_sip_smc_handler(uint32_t smc_fid,
								u_register_t x1, u_register_t x2,
								u_register_t x3, u_register_t x4,
								void *cookie,
								void *handle,
								u_register_t flags)
{
	uint32_t ns;

	ns = is_caller_non_secure(flags);
	if (!ns)
		SMC_RET1(handle, SMC_UNK);

	return rebel_plat_sip_handler(smc_fid, x1, x2, x3, x4, cookie, handle, flags);
}

DECLARE_RT_SVC(rebel_sip_svc, OEN_SIP_START, OEN_SIP_END, SMC_TYPE_FAST,
			   NULL, rebel_sip_smc_handler);
