/*
<<<<<<< HEAD
<<<<<<<< HEAD:include/lib/cpus/aarch64/cortex_a715.h
 * Copyright (c) 2021-2023, Arm Limited. All rights reserved.
========
 * Copyright (c) 2025, Arm Limited. All rights reserved.
>>>>>>>> upstream_import/upstream_v2_14_1:include/lib/cpus/aarch64/canyon.h
=======
 * Copyright (c) 2021-2025, Arm Limited. All rights reserved.
>>>>>>> upstream_import/upstream_v2_14_1
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

<<<<<<< HEAD
<<<<<<<< HEAD:include/lib/cpus/aarch64/cortex_a715.h
=======
>>>>>>> upstream_import/upstream_v2_14_1
#ifndef CORTEX_A715_H
#define CORTEX_A715_H

#define CORTEX_A715_MIDR					U(0x410FD4D0)

/* Cortex-A715 loop count for CVE-2022-23960 mitigation */
#define CORTEX_A715_BHB_LOOP_COUNT				U(38)
<<<<<<< HEAD
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
=======

/*******************************************************************************
 * CPU Register Mappings
 ******************************************************************************/
#define CORTEX_A715_CPUCFR_EL1					S3_0_C15_C0_0
#define CORTEX_A715_CPUACTLR_EL1				S3_0_C15_C1_0
#define CORTEX_A715_CPUACTLR2_EL1				S3_0_C15_C1_1
#define CORTEX_A715_CPUACTLR3_EL1				S3_0_C15_C1_2
#define CORTEX_A715_CPUECTLR_EL1				S3_0_C15_C1_4
#define CORTEX_A715_CPUECTLR2_EL1				S3_0_C15_C1_5
#define CORTEX_A715_CPUPSELR_EL3				S3_6_C15_C8_0
#define CORTEX_A715_CPUPCR_EL3					S3_6_C15_C8_1
#define CORTEX_A715_CPUPOR_EL3					S3_6_C15_C8_2
#define CORTEX_A715_CPUPMR_EL3					S3_6_C15_C8_3
>>>>>>> upstream_import/upstream_v2_14_1

/*******************************************************************************
 * CPU Power Control register specific definitions
 ******************************************************************************/
<<<<<<< HEAD
<<<<<<<< HEAD:include/lib/cpus/aarch64/cortex_a715.h
#define CORTEX_A715_CPUPWRCTLR_EL1				S3_0_C15_C2_7
#define CORTEX_A715_CPUPWRCTLR_EL1_CORE_PWRDN_BIT		U(1)

#endif /* CORTEX_A715_H */
========
#define CANYON_IMP_CPUPWRCTLR_EL1			S3_0_C15_C2_7
#define CANYON_IMP_CPUPWRCTLR_EL1_CORE_PWRDN_EN_BIT	U(1)

#endif /* CANYON_H */

>>>>>>>> upstream_import/upstream_v2_14_1:include/lib/cpus/aarch64/canyon.h
=======
#define CORTEX_A715_CPUPWRCTLR_EL1				S3_0_C15_C2_7
#define CORTEX_A715_CPUPWRCTLR_EL1_CORE_PWRDN_BIT		U(1)

#ifndef __ASSEMBLER__
long check_erratum_cortex_a715_3699560(long cpu_rev);
#endif /* __ASSEMBLER__ */

#endif /* CORTEX_A715_H */
>>>>>>> upstream_import/upstream_v2_14_1
