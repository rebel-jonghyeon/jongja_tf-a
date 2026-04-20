/*
 * Copyright (c) 2018, ARM Limited and Contributors. All rights reserved.
 * Copyright (c) 2025, Samsung Electronics Corporation. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef __REBEL_SIP_SVC_H
#define __REBEL_SIP_SVC_H

uintptr_t rebel_plat_sip_handler(uint32_t smc_fid,
								 u_register_t x1, u_register_t x2,
								 u_register_t x3, u_register_t x4,
								 void *cookie,
								 void *handle,
								 u_register_t flags);

#endif  /* __REBEL_SIP_SVC_H */
