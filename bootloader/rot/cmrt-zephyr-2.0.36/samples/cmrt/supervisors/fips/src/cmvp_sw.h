/*
 * Copyright (c) 2020-2023 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

#ifndef CRI_CMVP_SW_H
#define CRI_CMVP_SW_H

#include <stdint.h>
#include <stddef.h>
#include <stdalign.h>

#include <cri/cmrt/fips/fips_types.h>

#include <hexutil.h>

#define MAX_WORKCONTEXT_LEN 0x4800
extern alignas(4) uint8_t workcontext[MAX_WORKCONTEXT_LEN];

#include <cri/cmrt/sic.h>
extern cri_sic_t sic;

#ifdef CONFIG_DEBUG
#define dprintk printk
#else
#define dprintk(f_, ...) while (0)
#endif

#ifdef CONFIG_DEBUG
#define dhexdump(x, y, z) do { dprintk(x); dprintk("\n"); hexdump((y), (z)); } while (0)
#else
#define dhexdump(x, y, z) while (0)
#endif

#endif
