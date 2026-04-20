/*
 * Copyright (c) 2020-2023 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

#ifndef CMRT_DCM_REG_H
#define CMRT_DCM_REG_H

#include "sac_reg.h"

#define CMRT_DCM_NR_DDR_BUFFERS     16
#define CMRT_DCM_DDR_BUFFER_SIZE    4096 /* Bytes */

/* Registers */
#define CMRT_DCM_BASE               (EXT_MEMORY_CMRT + 0x30000)
#define R_DCM_IN_WPTR               0x100
#define R_DCM_IN_RPTR               0x104
#define R_DCM_OUT_WPTR              0x108
#define R_DCM_OUT_RPTR              0x10C
#define R_DCM_CONTROL               0x130
#define R_DCM_MAX                   0x10000

/* Control values */
#define DCM_CONTROL_FLUSH           0xFF
#define DCM_CONTROL_MASK            0XFF

typedef struct cmrt_dcm_ddr_buf {
	uint8_t buffer[CMRT_DCM_DDR_BUFFER_SIZE];
} cmrt_dcm_ddr_buf_t;
#endif /* CMRT_DCM_REG_H */
