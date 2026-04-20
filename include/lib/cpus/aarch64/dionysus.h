/*
<<<<<<<< HEAD:include/lib/cpus/aarch64/cortex_a720.h
 * Copyright (c) 2021-2023, Arm Limited. All rights reserved.
========
 * Copyright (c) 2025, Arm Limited. All rights reserved.
>>>>>>>> upstream_import/upstream_v2_14_1:include/lib/cpus/aarch64/dionysus.h
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

<<<<<<<< HEAD:include/lib/cpus/aarch64/cortex_a720.h
#ifndef CORTEX_A720_H
#define CORTEX_A720_H

#define CORTEX_A720_MIDR					U(0x410FD810)

/* Cortex A720 loop count for CVE-2022-23960 mitigation */
#define CORTEX_A720_BHB_LOOP_COUNT				U(132)
========
#ifndef DIONYSUS_H
#define DIONYSUS_H

#include <lib/utils_def.h>

#define DIONYSUS_MIDR						U(0x410FD940)
>>>>>>>> upstream_import/upstream_v2_14_1:include/lib/cpus/aarch64/dionysus.h

/*******************************************************************************
 * CPU Extended Control register specific definitions
 ******************************************************************************/
<<<<<<<< HEAD:include/lib/cpus/aarch64/cortex_a720.h
#define CORTEX_A720_CPUECTLR_EL1				S3_0_C15_C1_4
========
#define DIONYSUS_IMP_CPUECTLR_EL1				S3_0_C15_C1_4
>>>>>>>> upstream_import/upstream_v2_14_1:include/lib/cpus/aarch64/dionysus.h

/*******************************************************************************
 * CPU Power Control register specific definitions
 ******************************************************************************/
<<<<<<<< HEAD:include/lib/cpus/aarch64/cortex_a720.h
#define CORTEX_A720_CPUPWRCTLR_EL1				S3_0_C15_C2_7
#define CORTEX_A720_CPUPWRCTLR_EL1_CORE_PWRDN_BIT		U(1)

#endif /* CORTEX_A720_H */
========
#define DIONYSUS_CPUPWRCTLR_EL1					S3_0_C15_C2_7
#define DIONYSUS_CPUPWRCTLR_EL1_CORE_PWRDN_BIT			U(1)

#endif /* DIONYSUS_H */
>>>>>>>> upstream_import/upstream_v2_14_1:include/lib/cpus/aarch64/dionysus.h
