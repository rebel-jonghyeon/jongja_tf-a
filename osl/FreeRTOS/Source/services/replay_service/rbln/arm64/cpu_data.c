#include "arm64/cpu_data.h"
#include "cpu.h"

#define Z_STRINGIFY(x) #x
#define STRINGIFY(s)   Z_STRINGIFY(s)

#define read_sysreg(reg)															\
	({																				\
		uint64_t val;																\
		__asm__ volatile("mrs %0, " STRINGIFY(reg) : "=r"(val)::"memory");			\
		val;																		\
	})

#define write_sysreg(val, reg)														\
	({ __asm__ volatile("msr " STRINGIFY(reg) ", %0" ::"r"(val) : "memory"); })

struct cpu_data *get_cpu_data(void)
{
	return (struct cpu_data *)read_sysreg(tpidr_el1);
}
