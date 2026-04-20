/*
 * Copyright (c) 2020-2023 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

#ifndef CMRT_PKE_KAT_H
#define CMRT_PKE_KAT_H

#include <device.h>
#include <drivers/cmrt/dd.h>

int pke_init_kat(const struct device *dev);
void pke_open_kat(cmrt_dd_context_t *context);

#endif
