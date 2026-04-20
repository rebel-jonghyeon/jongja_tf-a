/*-
 * SPDX-License-Identifier: BSD-2-Clause
 *
 * Copyright (c) 2019-2020 Ruslan Bukin <br@bsdpad.com>
 *
 * This software was developed by SRI International and the University of
 * Cambridge Computer Laboratory (Department of Computer Science and
 * Technology) under DARPA contract HR0011-18-C-0016 ("ECATS"), as part of the
 * DARPA SSITH research programme.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#include "FreeRTOS.h"

struct smmu_event {
	int ident;
	char *str;
	char *msg;
};

struct smmu_queue_local_copy {
	union {
		uint64_t val;
		struct {
			uint32_t prod;
			uint32_t cons;
		};
	};
};

struct smmu_queue {
	struct smmu_queue_local_copy lc;
	uint64_t paddr;
	uint32_t prod_off;
	uint32_t cons_off;
	int size_log2;
	uint64_t base;
};

struct smmu_cmdq_entry {
	uint8_t opcode;
	union {
		struct {
			uint16_t asid;
			uint16_t vmid;
			uint64_t addr;
			bool leaf;
		} tlbi;
		struct {
			uint32_t sid;
			uint32_t ssid;
			bool leaf;
		} cfgi;
		struct {
			uint32_t sid;
			uint32_t ssid;
			uint8_t ssv;
			uint8_t ssec;
		} prefetch;
		struct {
			uint64_t msiaddr;
		} sync;
	};
};

struct stream_table {
	uint64_t ste[8];
};

struct context_desc {
	uint64_t val[6];
	uint64_t rsvd[2]; /* for align */
};

struct cd_tables {
	struct context_desc cd[64];
};
