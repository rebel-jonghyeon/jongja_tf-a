/*
 * Copyright (c) 2022-2023, Intel Corporation. All rights reserved.
<<<<<<< HEAD
=======
 * Copyright (c) 2025, Altera Corporation. All rights reserved.
>>>>>>> upstream_import/upstream_v2_14_1
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

<<<<<<< HEAD
#ifndef DDR_H
#define DDR_H
=======
#ifndef NAND_H
#define NAND_H
>>>>>>> upstream_import/upstream_v2_14_1

#include <lib/mmio.h>
#include "socfpga_handoff.h"

/* FUNCTION DEFINATION */
/*
 * @brief Nand controller initialization function
 *
<<<<<<< HEAD
 * @hoff_ptr: Pointer to the hand-off data
 * Return: 0 on success, a negative errno on failure
 */
int nand_init(handoff *hoff_ptr);

#endif
=======
 * Return: 0 on success, a negative errno on failure
 */
int nand_init(void);

#endif
>>>>>>> upstream_import/upstream_v2_14_1
