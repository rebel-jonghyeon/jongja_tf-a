/*
<<<<<<<< HEAD:include/lib/cpus/aarch64/cortex_a715.h
 * Copyright (c) 2021-2023, Arm Limited. All rights reserved.
========
 * Copyright (c) 2025, Arm Limited. All rights reserved.
>>>>>>>> upstream_import/upstream_v2_14_1:include/lib/cpus/aarch64/canyon.h
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

<<<<<<<< HEAD:include/lib/cpus/aarch64/cortex_a715.h
#ifndef CORTEX_A715_H
#define CORTEX_A715_H

#define CORTEX_A715_MIDR					U(0x410FD4D0)

/* Cortex-A715 loop count for CVE-2022-23960 mitigation */
#define CORTEX_A715_BHB_LOOP_COUNT				U(38)
========
#ifndef CANYON_H
#define CANYON_H

#define CANYON_MIDR					U(0x410FD960)
>>>>>>>> upstream_import/upstream_v2_14_1:include/lib/cpus/aarch64/canyon.h

/*******************************************************************************
 * CPU Extended Control register specific definitions
 ******************************************************************************/
<<<<<<<< HEAD:include/lib/cpus/aarch64/cortex_a715.h
#define CORTEX_A715_CPUECTLR_EL1				S3_0_C15_C1_4
========
#define CANYON_IMP_CPUECTLR_EL1				S3_0_C15_C1_4
>>>>>>>> upstream_import/upstream_v2_14_1:include/lib/cpus/aarch64/canyon.h

/*******************************************************************************
 * CPU Power Control register specific definitions
 ******************************************************************************/
<<<<<<<< HEAD:include/lib/cpus/aarch64/cortex_a715.h
#define CORTEX_A715_CPUPWRCTLR_EL1				S3_0_C15_C2_7
#define CORTEX_A715_CPUPWRCTLR_EL1_CORE_PWRDN_BIT		U(1)

#endif /* CORTEX_A715_H */
========
#define CANYON_IMP_CPUPWRCTLR_EL1			S3_0_C15_C2_7
#define CANYON_IMP_CPUPWRCTLR_EL1_CORE_PWRDN_EN_BIT	U(1)

#endif /* CANYON_H */

>>>>>>>> upstream_import/upstream_v2_14_1:include/lib/cpus/aarch64/canyon.h
