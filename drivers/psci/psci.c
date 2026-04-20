#include "psci.h"

static unsigned long invoke_psci_fn(unsigned long function_id,
									unsigned long arg0,
									unsigned long arg1,
									unsigned long arg2)
{
	struct arm_smccc_res res;

	arm_smccc_smc(function_id, arg0, arg1, arg2, 0, 0, 0, 0, &res);

	return res.x0;
}

int psci_cpu_on(unsigned long cpuid, uintptr_t entry_point)
{
	int ret;

	ret = invoke_psci_fn(PSCI_1_1_FN64_CPU_ON, cpuid, (unsigned long)entry_point, 0);

	return ret;
}

void psci_cpu_off(void)
{
	invoke_psci_fn(PSCI_1_1_FN_CPU_OFF, 0, 0, 0);
}
