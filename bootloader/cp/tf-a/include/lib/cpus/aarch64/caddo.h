/*
<<<<<<<< HEAD:include/lib/cpus/aarch64/cortex_a520.h
 * Copyright (c) 2021-2023, Arm Limited. All rights reserved.
========
 * Copyright (c) 2025, Arm Limited. All rights reserved.
>>>>>>>> upstream_import/upstream_v2_14_1:include/lib/cpus/aarch64/caddo.h
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

<<<<<<<< HEAD:include/lib/cpus/aarch64/cortex_a520.h
#ifndef CORTEX_A520_H
#define CORTEX_A520_H

#define CORTEX_A520_MIDR					U(0x410FD800)
========
#ifndef CADDO_H
#define CADDO_H

#define CADDO_MIDR		                        U(0x410FDA00)
>>>>>>>> upstream_import/upstream_v2_14_1:include/lib/cpus/aarch64/caddo.h

/*******************************************************************************
 * CPU Extended Control register specific definitions
 ******************************************************************************/
<<<<<<<< HEAD:include/lib/cpus/aarch64/cortex_a520.h
#define CORTEX_A520_CPUECTLR_EL1				S3_0_C15_C1_4
========
#define CADDO_IMP_CPUECTLR_EL1		        	S3_0_C15_C1_4
>>>>>>>> upstream_import/upstream_v2_14_1:include/lib/cpus/aarch64/caddo.h

/*******************************************************************************
 * CPU Power Control register specific definitions
 ******************************************************************************/
<<<<<<<< HEAD:include/lib/cpus/aarch64/cortex_a520.h
#define CORTEX_A520_CPUPWRCTLR_EL1				S3_0_C15_C2_7
#define CORTEX_A520_CPUPWRCTLR_EL1_CORE_PWRDN_BIT		U(1)

#endif /* CORTEX_A520_H */
========
#define CADDO_IMP_CPUPWRCTLR_EL1			S3_0_C15_C2_7
#define CADDO_IMP_CPUPWRCTLR_EL1_CORE_PWRDN_EN_BIT	U(1)

#endif /* CADDO_H */

>>>>>>>> upstream_import/upstream_v2_14_1:include/lib/cpus/aarch64/caddo.h
