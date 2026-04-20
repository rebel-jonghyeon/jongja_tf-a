/*
<<<<<<< HEAD
<<<<<<<< HEAD:include/lib/cpus/aarch64/cortex_a720.h
 * Copyright (c) 2021-2023, Arm Limited. All rights reserved.
========
 * Copyright (c) 2025, Arm Limited. All rights reserved.
>>>>>>>> upstream_import/upstream_v2_14_1:include/lib/cpus/aarch64/dionysus.h
=======
 * Copyright (c) 2021-2025, Arm Limited. All rights reserved.
>>>>>>> upstream_import/upstream_v2_14_1
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

<<<<<<< HEAD
<<<<<<<< HEAD:include/lib/cpus/aarch64/cortex_a720.h
=======
>>>>>>> upstream_import/upstream_v2_14_1
#ifndef CORTEX_A720_H
#define CORTEX_A720_H

#define CORTEX_A720_MIDR					U(0x410FD810)

<<<<<<< HEAD
/* Cortex A720 loop count for CVE-2022-23960 mitigation */
#define CORTEX_A720_BHB_LOOP_COUNT				U(132)
========
#ifndef DIONYSUS_H
#define DIONYSUS_H

#include <lib/utils_def.h>

#define DIONYSUS_MIDR						U(0x410FD940)
>>>>>>>> upstream_import/upstream_v2_14_1:include/lib/cpus/aarch64/dionysus.h
=======
/*******************************************************************************
 * CPU Auxiliary Control register 1 specific definitions.
 ******************************************************************************/
#define CORTEX_A720_CPUACTLR_EL1				S3_0_C15_C1_0

/*******************************************************************************
 * CPU Auxiliary Control register 2 specific definitions.
 ******************************************************************************/
#define CORTEX_A720_CPUACTLR2_EL1				S3_0_C15_C1_1

/*******************************************************************************
 * CPU Auxiliary Control register 4 specific definitions.
 ******************************************************************************/
#define CORTEX_A720_CPUACTLR4_EL1				S3_0_C15_C1_3
>>>>>>> upstream_import/upstream_v2_14_1

/*******************************************************************************
 * CPU Extended Control register specific definitions
 ******************************************************************************/
<<<<<<< HEAD
<<<<<<<< HEAD:include/lib/cpus/aarch64/cortex_a720.h
#define CORTEX_A720_CPUECTLR_EL1				S3_0_C15_C1_4
========
#define DIONYSUS_IMP_CPUECTLR_EL1				S3_0_C15_C1_4
>>>>>>>> upstream_import/upstream_v2_14_1:include/lib/cpus/aarch64/dionysus.h
=======
#define CORTEX_A720_CPUECTLR_EL1				S3_0_C15_C1_4
>>>>>>> upstream_import/upstream_v2_14_1

/*******************************************************************************
 * CPU Power Control register specific definitions
 ******************************************************************************/
<<<<<<< HEAD
<<<<<<<< HEAD:include/lib/cpus/aarch64/cortex_a720.h
#define CORTEX_A720_CPUPWRCTLR_EL1				S3_0_C15_C2_7
#define CORTEX_A720_CPUPWRCTLR_EL1_CORE_PWRDN_BIT		U(1)

#endif /* CORTEX_A720_H */
========
#define DIONYSUS_CPUPWRCTLR_EL1					S3_0_C15_C2_7
#define DIONYSUS_CPUPWRCTLR_EL1_CORE_PWRDN_BIT			U(1)

#endif /* DIONYSUS_H */
>>>>>>>> upstream_import/upstream_v2_14_1:include/lib/cpus/aarch64/dionysus.h
=======
#define CORTEX_A720_CPUPWRCTLR_EL1				S3_0_C15_C2_7
#define CORTEX_A720_CPUPWRCTLR_EL1_CORE_PWRDN_BIT		U(1)

/*******************************************************************************
 * CPU Instruction Patching Register Definitions
 ******************************************************************************/
#define CORTEX_A720_CPUPSELR_EL3				S3_6_C15_C8_0
#define CORTEX_A720_CPUPCR_EL3					S3_6_C15_C8_1
#define CORTEX_A720_CPUPOR_EL3					S3_6_C15_C8_2
#define CORTEX_A720_CPUPMR_EL3					S3_6_C15_C8_3

#ifndef __ASSEMBLER__
long check_erratum_cortex_a720_3699561(long cpu_rev);
#endif /* __ASSEMBLER__ */

#endif /* CORTEX_A720_H */
>>>>>>> upstream_import/upstream_v2_14_1
