#pragma once
#include <stdint.h>

/* PSCI v1.1 interface. */
#define PSCI_1_1_FN_BASE                  (0x84000000U)
#define PSCI_1_1_64BIT                    (0x40000000U)
#define PSCI_1_1_FN64_BASE                (PSCI_1_1_FN_BASE + PSCI_1_1_64BIT)
#define PSCI_1_1_FN(n)                    (PSCI_1_1_FN_BASE + (n))
#define PSCI_1_1_FN64(n)                  (PSCI_1_1_FN64_BASE + (n))
#define PSCI_1_1_FN_PSCI_VERSION          PSCI_1_1_FN(0)
#define PSCI_1_1_FN_CPU_SUSPEND           PSCI_1_1_FN(1)
#define PSCI_1_1_FN_CPU_OFF               PSCI_1_1_FN(2)
#define PSCI_1_1_FN_CPU_ON                PSCI_1_1_FN(3)
#define PSCI_1_1_FN_AFFINITY_INFO         PSCI_1_1_FN(4)
#define PSCI_1_1_FN_MIGRATE               PSCI_1_1_FN(5)
#define PSCI_1_1_FN_MIGRATE_INFO_TYPE     PSCI_1_1_FN(6)
#define PSCI_1_1_FN_MIGRATE_INFO_UP_CPU   PSCI_1_1_FN(7)
#define PSCI_1_1_FN_SYSTEM_OFF            PSCI_1_1_FN(8)
#define PSCI_1_1_FN_SYSTEM_RESET          PSCI_1_1_FN(9)
#define PSCI_1_1_FN_PSCI_FEATURES         PSCI_1_1_FN(10)
#define PSCI_1_1_FN_SYSTEM_RESET2         PSCI_1_1_FN(18)
#define PSCI_1_1_FN64_CPU_SUSPEND         PSCI_1_1_FN64(1)
#define PSCI_1_1_FN64_CPU_ON              PSCI_1_1_FN64(3)
#define PSCI_1_1_FN64_AFFINITY_INFO       PSCI_1_1_FN64(4)
#define PSCI_1_1_FN64_MIGRATE             PSCI_1_1_FN64(5)
#define PSCI_1_1_FN64_MIGRATE_INFO_UP_CPU PSCI_1_1_FN64(7)
/* PSCI function ID is same for both 32 and 64 bit.*/
#define PSCI_1_1_FN64_SYSTEM_RESET        PSCI_1_1_FN(9)
#define PSCI_1_1_FN64_PSCI_FEATURES       PSCI_1_1_FN(10)
#define PSCI_1_1_FN64_SYSTEM_RESET2       PSCI_1_1_FN64(18)

struct arm_smccc_res {
	unsigned long x0;
	unsigned long x1;
	unsigned long x2;
	unsigned long x3;
	unsigned long x4;
	unsigned long x5;
	unsigned long x6;
	unsigned long x7;
};

int psci_cpu_on(unsigned long cpuid, uintptr_t entry_point);
void psci_cpu_off(void);

extern void arm_smccc_smc(unsigned long function_id, unsigned long arg0, unsigned long arg1,
						  unsigned long arg2, unsigned long arg3, unsigned long arg4,
						  unsigned long arg5, unsigned long arg, struct arm_smccc_res *res);
