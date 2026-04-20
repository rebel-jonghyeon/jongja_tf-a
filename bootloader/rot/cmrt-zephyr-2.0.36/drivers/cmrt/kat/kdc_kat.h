/*
 * Copyright (c) 2020-2023 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

#ifndef CMRT_KDC_KAT_H
#define CMRT_KDC_KAT_H

#include <device.h>
#include <drivers/cmrt/dd.h>


int kdc_init_kat(const struct device *dev);
void kdc_open_kat(cmrt_dd_context_t *context);

#endif
