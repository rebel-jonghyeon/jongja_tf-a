#include <FreeRTOS.h>
#include "rbln/cache.h"
#include "cpu_data.h"
#include "gic.h"
#include "rbln/abort.h"
#include "rbln/spinlock.h"
#include "rbln/log.h"
#include "rbln/rebel.h"
#include "task.h"
#include "external/atomic/atomic.h"
#include "rl_sizes.h"
#include "rbln/sgi.h"
#include "external/backtrace/backtrace.h"

#ifdef CONFIG_PCIE_RAS_DES
#include "pcie_ras_des.h"
#endif /* CONFIG_PCIE_RAS_DES */

//TODO: Remove after porting terminal_task
#define LOG_ASSERT(...)

static bool abort_event;
static bool hang;
static bool device_halted;

extern void dump_gp_regs(void);
extern void dump_state_regs_el3(void);
extern void dump_state_regs_el1(void);

static char *el_state_regnames[] = {
	"ESR_EL",
	"FAR_EL",
	"SCR_EL3",
	"SPSR_EL",
	"ELR_EL",
	"RUNTIME_SP",
	"CURRENT_EL",
	"CPSR_EL"
};

static uint32_t aborted_core = 0xff;
static uint32_t abort_others = true;

#define START_ABORT() \
	do { \
		if (aborted_core == 0xff) { \
			if (xPortIsInsideInterrupt()) \
				taskENTER_CRITICAL_FROM_ISR(); \
			else \
				taskENTER_CRITICAL(); \
			aborted_core = get_current_cpuid(); \
			if (abort_others) \
				gic_raise_sgi(SGI_ID_ABORT, SGI_TARGET_AFF, \
					SGI_TARGET_LIST & ~(1 << aborted_core)); \
			dump_regs(); \
			print_crashbuf(); \
		} \
	} while (0)

static void print_crashbuf(void)
{
	const uint32_t gpreg_num = CTX_GPREGS_END / REG_SZ;
	const uint32_t elreg_num = CTX_ELSTATE_END / REG_SZ;
	struct cpu_data *cpu_data = get_cpu_data();
	uint32_t i;

	RLOG_ERR("aborted core %u dump gp regs\r\n", get_current_cpuid());

	for (i = 0; i < gpreg_num; (i += 2)) {
		RLOG_ERR("x%02u: 0x%016llx\tx%02u: 0x%016llx\r\n", i, cpu_data->regs[i],
		i + 1, cpu_data->regs[i + 1]);
	}

	for (i = 0; i < elreg_num; i++)
		RLOG_ERR("%s: 0x%016llx\r\n", el_state_regnames[i], cpu_data->regs[gpreg_num + i]);
}

void abort_other_cores(void)
{
	uint32_t core = get_current_cpuid();

	if (abort_others)
		gic_raise_sgi(SGI_ID_ABORT, SGI_TARGET_AFF, SGI_TARGET_LIST & ~(1 << core));

	abort_others = false;
}

inline uint64_t get_current_el(void)
{
#ifndef __TARGET_PCIE
	uint64_t el;

	__asm__ volatile ("mrs %0, currentel" : "=r" (el) :: "memory");
	return el;
#else
	return 1;
#endif
}

static inline void dump_regs(void)
{
#ifndef __TARGET_PCIE
	/* Dump general purpose regs after saving x0, x1 */
	asm volatile (
		"str x0, [sp, #-16]!\n\t"
		"mrs x0, tpidr_el1\n\t"
		"str x1, [x0, 8]\n\t"
		"ldr x1, [sp]\n\t"
		"add sp, sp, #16\n\t"
		"str x1, [x0]\n\t"
	:
	:
	: "x0", "x1");

	dump_gp_regs();

	if ((get_current_el() >> 2) == 1)
		dump_state_regs_el1();
	else
		dump_state_regs_el3();
#endif
}

static void abort_handler(void *irq_data)
{
	uint32_t core_id;
	struct cpu_data *cpu_data;
	static atomic_t done_mask;

	core_id = get_current_cpuid();
	RLOG_ERR("%s: core %d started.\r\n", __func__, core_id);

	if (core_id != aborted_core)
		dump_regs();

	cpu_data = get_cpu_data();
	clean_dcache_range((uintptr_t)cpu_data, CPU_DATA_SIZE);
	dsb();

	atomic_set_bit(&done_mask, core_id);
	RLOG_ERR("core %u cache clean finished\r\n", core_id);

	if (core_id == aborted_core) {
		/* Wait until all cores clean cache */
		while (atomic_get(&done_mask) != 0xF)
			__asm__ volatile("nop");
	}

	rl_shutdown(-1);
}

void enable_abort_interrupt(uint32_t core_id)
{
	// aborts may occur in the interrupt handler, so set the highest priority
	// to the abort interrupt to nest the lower interrupt handler, if any.
	gic_irq_set_priority(SGI_ID_ABORT, 0, IRQ_TYPE_LEVEL);
	gic_irq_enable_dedicated_core(core_id, SGI_ID_ABORT);
	gic_irq_connect(SGI_ID_ABORT, abort_handler, NULL);
}

/* custom abort function to dump arm core registers to percpu_data area.
 * It triggers exception handler by sending SGI to all cores.
 * percpu_data area for each core is as follows.
 * core 0: 0x1FF415F000++0x14F
 * core 1: 0x1FF415F150++0x14F
 * core 2: 0x1FF415F2A0+0x14F
 * core 3: 0x1FF415F3F0++0x14F
 */
static inline void rl_abort(void)
{
	abort_handler(NULL);
	rl_shutdown(-1);
}

#if !defined(__TARGET_RELEASE__)
static void rl_assert_err_reason(uint32_t err_code)
{
	int err;
	const char *err_reason = NULL;

	LOG_ASSERT("err_code: 0x%x\r\n", err_code);
	RL_FOREACH_BIT(err, err_code) {
		if (err & ERR_HIGH_TEMP)
			err_reason = "ERR_HIGH_TEMP";
		else if (err & ERR_PCIE_LINK)
			err_reason = "ERR_PCIE_LINK";
		else if (err & ERR_CORE_EXCEPTION)
			err_reason = "ERR_CORE_EXCEPTION";
		else if (err & ERR_DNC)
			err_reason = "ERR_DNC";
		else if (err & ERR_RBDMA)
			err_reason = "ERR_RBDMA";
		else if (err & ERR_HDMA)
			err_reason = "ERR_HDMA";
		else if (err & ERR_SHM)
			err_reason = "ERR_SHM";
		else if (err & ERR_CPU_NOTREADY)
			err_reason = "ERR_CPU_NOTREADY";
		else if (err & ERR_WATCHDOG)
			err_reason = "ERR_WATCHDOG";
		else if (err & ERR_GDDR6)
			err_reason = "ERR_GDDR6";

		if (err_reason)
			LOG_ASSERT("err_reason: %s\r\n", err_reason);
	}
}
#endif

static void rl_print_debug_info(uint32_t err_code)
{
#if !defined(__TARGET_RELEASE__)
	rl_assert_err_reason(err_code);
#endif
}

void rl_hang(bool halt_device)
{
	START_ABORT();
	hang = true;
	device_halted = halt_device;
	rl_print_debug_info(0);
	rl_abort();
}

static inline void rl_set_guilty_ctx(uint32_t func_id, uint32_t ctx_id, uint32_t err_code) {}

void rl_abort_guilty_ctx(uint32_t func_id, uint32_t ctx_id, uint32_t err_code)
{
	assert(func_id <= MAX_FUNC_CNT);

	START_ABORT();

	rl_set_guilty_ctx(func_id, ctx_id, err_code);
	rl_print_debug_info(err_code);
	rl_abort();
}

void rl_abort_event(uint32_t event)
{
	START_ABORT();

	abort_event = true;

	RLOG_ERR("%s: err_code %#lx\r\n", __func__, event);

	if (event == ERR_CORE_EXCEPTION)
		RLOG_ERR("Exception raised from core %u\r\n", aborted_core);

	rl_print_debug_info(event);
	rl_abort();
}

void rl_abort_cur_ctx(uint32_t err_code)
{
	bool guilty_ctx_exists = false;

	START_ABORT();

	if (!guilty_ctx_exists)
		rl_abort_event(err_code);
}

#define GET_EXCEPTION_CLASS(val)	(((val) >> 26) & ((1 << 6) - 1))
#define GET_DFSC(val)	((val) & ((1 << 6) - 1))
#define EC_DATA_ABORT	(0b100101)

static void check_data_abort(uint64_t elr)
{
#ifndef __TARGET_PCIE
	uint64_t esr = 0;
	uint64_t far = 0;
	uint64_t ec = 0;

	if ((get_current_el() >> 2) == 1) {
		__asm__ volatile ("mrs %0, esr_el1" : "=r" (esr));
		__asm__ volatile ("mrs %0, far_el1" : "=r" (far));
	} else {
		__asm__ volatile ("mrs %0, esr_el3" : "=r" (esr));
		__asm__ volatile ("mrs %0, far_el3" : "=r" (far));
	}

	ec = GET_EXCEPTION_CLASS(esr);
	RLOG_ERR("ESR: 0x%016llx, exception class: 0x%016llx\r\n", esr, ec);
	RLOG_ERR("ELR: 0x%016llx\r\n", elr);
	RLOG_ERR("FAR: 0x%016llx\r\n", far);

	if (ec != EC_DATA_ABORT)
		return;

	switch (GET_DFSC(esr)) {
	case 0b000000:
	case 0b000001:
	case 0b000010:
	case 0b000011:
		RLOG_ERR("Address size fault\r\n");
		break;
	case 0b000100:
	case 0b000101:
	case 0b000110:
	case 0b000111:
		RLOG_ERR("Translation fault\r\n");
		/* TODO: Move FW load address to 2MB */
		if (far < SZ_1M)
			RLOG_ERR("Nullptr dereference occurs\r\n");
		break;
	case 0b001001:
	case 0b001010:
	case 0b001011:
	case 0b001000:
		RLOG_ERR("Access flag fault\r\n");
		break;
	case 0b001100:
	case 0b001101:
	case 0b001110:
	case 0b001111:
		RLOG_ERR("Permission fault\r\n");
	}
#endif
}

/* Wrapper function for FreeRTOS exception handlers */
void rl_abort_exception(uint64_t elr)
{
	START_ABORT();

	check_data_abort(elr);

	backtrace("CORE EXCEPTION");

	rl_abort_cur_ctx(ERR_CORE_EXCEPTION);
}

bool is_abort_event(void)
{
	return abort_event;
}
