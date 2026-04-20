#include <driver.h>
#include "stdlib.h"
#include "mailbox.h"
#include <interrupt.h>
#include <string.h>
#include <errno.h>
#include <rebel_h_platform.h>

#if defined __TARGET_PCIE
#include "../pcie/pcie_mailbox_callback.h"
#include "core_cm7.h"
#define MAILBOX_PCIE				(MAILBOX_PCIE_PRIVATE)
#endif

#define MAILBOX_SFR_SIZE			(0x1000)
#define MAILBOX_PCIE_VF1			(MAILBOX_PCIE + MAILBOX_SFR_SIZE)
#define MAILBOX_PCIE_VF2			(MAILBOX_PCIE_VF1 + MAILBOX_SFR_SIZE)
#define MAILBOX_PCIE_VF3			(MAILBOX_PCIE_VF2 + MAILBOX_SFR_SIZE)
#define MAILBOX_PCIE_VF4			(MAILBOX_PCIE_VF3 + MAILBOX_SFR_SIZE)
#define MAILBOX_PCIE_VF5			(MAILBOX_PCIE_VF4 + MAILBOX_SFR_SIZE)
#define MAILBOX_PCIE_VF6			(MAILBOX_PCIE_VF5 + MAILBOX_SFR_SIZE)
#define MAILBOX_PCIE_VF7			(MAILBOX_PCIE_VF6 + MAILBOX_SFR_SIZE)
#define MAILBOX_PCIE_VF8			(MAILBOX_PCIE_VF7 + MAILBOX_SFR_SIZE)
#define MAILBOX_PCIE_VF9			(MAILBOX_PCIE_VF8 + MAILBOX_SFR_SIZE)
#define MAILBOX_PCIE_VF10			(MAILBOX_PCIE_VF9 + MAILBOX_SFR_SIZE)
#define MAILBOX_PCIE_VF11			(MAILBOX_PCIE_VF10 + MAILBOX_SFR_SIZE)
#define MAILBOX_PCIE_VF12			(MAILBOX_PCIE_VF11 + MAILBOX_SFR_SIZE)
#define MAILBOX_PCIE_VF13			(MAILBOX_PCIE_VF12 + MAILBOX_SFR_SIZE)
#define MAILBOX_PCIE_VF14			(MAILBOX_PCIE_VF13 + MAILBOX_SFR_SIZE)
#define MAILBOX_PCIE_VF15			(MAILBOX_PCIE_VF14 + MAILBOX_SFR_SIZE)
#define MAILBOX_PCIE_PF				(MAILBOX_PCIE_VF15 + MAILBOX_SFR_SIZE)

#define ISSR_MAX				(63)
#define IRQ_NUM_MAX				(32)
#define IRQ_NUM_HIGH			(16)
#define CHANNEL_PER_CPU			(32)
#define CHANNEL_PER_HIGH_LOW	(16)
#define HIGH_IRQ(n)				((n) * IRQ_NUM_HIGH)
#define ISSR_OFFSET(n)			((n) * 4)

#define DATA_SIZE(s)		(((s) - 1) / 4 + 1)

struct ipm_device {
	uint32_t inst;
	#if defined __TARGET_CP
	uint64_t base;
	#else
	uint32_t base;
	#endif
	enum _CPU_ID cpu_id;
	uint32_t irq_num_low;
	uint32_t irq_num_high;
	void (*callback)(int inst, int channel);
};

static struct ipm_device mailbox_data[] = {
#if defined __TARGET_PCIE
	{IDX_MAILBOX_M2,		MAILBOX_ROT_M2_PRIVATE, CPU1, 25, 26, default_cb},
	{IDX_MAILBOX_CP0_M4,	MAILBOX_CP0_M4_PRIVATE, CPU1, 27, 28, default_cb},
	{IDX_MAILBOX_CP1_M4,	MAILBOX_CP1_M4_PRIVATE, CPU1, 29, 30, default_cb},
	{IDX_MAILBOX_CP0_M4_C3,	MAILBOX_CP0_M4_PRIVATE, CPU1, 0, 0, NULL},
	{IDX_MAILBOX_PCIE_VF0,	MAILBOX_PCIE, CPU0, 14, 0, default_cb},
	{IDX_MAILBOX_PCIE_VF1,	MAILBOX_PCIE_VF1, CPU0, 0, 0, default_cb},
	{IDX_MAILBOX_PCIE_VF2,	MAILBOX_PCIE_VF2, CPU0, 0, 0, default_cb},
	{IDX_MAILBOX_PCIE_VF3,	MAILBOX_PCIE_VF3, CPU0, 0, 0, default_cb},
	{IDX_MAILBOX_PCIE_VF4,	MAILBOX_PCIE_VF4, CPU0, 0, 0, default_cb},
	{IDX_MAILBOX_PCIE_VF5,	MAILBOX_PCIE_VF5, CPU0, 0, 0, default_cb},
	{IDX_MAILBOX_PCIE_VF6,	MAILBOX_PCIE_VF6, CPU0, 0, 0, default_cb},
	{IDX_MAILBOX_PCIE_VF7,	MAILBOX_PCIE_VF7, CPU0, 0, 0, default_cb},
	{IDX_MAILBOX_PCIE_VF8,	MAILBOX_PCIE_VF8, CPU0, 0, 0, default_cb},
	{IDX_MAILBOX_PCIE_VF9,	MAILBOX_PCIE_VF9, CPU0, 0, 0, default_cb},
	{IDX_MAILBOX_PCIE_VF10,	MAILBOX_PCIE_VF10, CPU0, 0, 0, default_cb},
	{IDX_MAILBOX_PCIE_VF11,	MAILBOX_PCIE_VF11, CPU0, 0, 0, default_cb},
	{IDX_MAILBOX_PCIE_VF12,	MAILBOX_PCIE_VF12, CPU0, 0, 0, default_cb},
	{IDX_MAILBOX_PCIE_VF13,	MAILBOX_PCIE_VF13, CPU0, 0, 0, default_cb},
	{IDX_MAILBOX_PCIE_VF14,	MAILBOX_PCIE_VF14, CPU0, 0, 0, default_cb},
	{IDX_MAILBOX_PCIE_VF15,	MAILBOX_PCIE_VF15, CPU0, 0, 0, default_cb},
	{IDX_MAILBOX_PCIE_PF,	MAILBOX_PCIE_PF, CPU0, 13, 0, default_cb},
#elif (__TARGET_CP == 0)
	{ IDX_MAILBOX_M0,		MAILBOX_ROT_M0, CPU1, 32, 33, default_cb},
	{ IDX_MAILBOX_CP0_M3,	MAILBOX_CP0_M3, CPU0, 144, 145, default_cb},
	{ IDX_MAILBOX_CP0_M4,	MAILBOX_CP0_M4, CPU0, 148, 149, default_cb},
	{ IDX_MAILBOX_CP1_M3,	MAILBOX_CP1_M3, CPU0, 154, 155, default_cb},
	{ IDX_MAILBOX_CP1_M4,	MAILBOX_CP1_M4, CPU0, 158, 159, default_cb},

	{ IDX_MAILBOX_PERI0_M5,			MAILBOX_PERI0_M5, CPU0, 248, 249, default_cb},
	{ IDX_MAILBOX_PERI0_M7_CPU0,	MAILBOX_PERI0_M7, CPU0, 216, 217, default_cb},
	{ IDX_MAILBOX_PERI0_M7_CPU1,	MAILBOX_PERI0_M7, CPU1, 218, 219, default_cb},
	{ IDX_MAILBOX_PERI0_M8_CPU0,	MAILBOX_PERI0_M8, CPU0, 220, 221, default_cb},
	{ IDX_MAILBOX_PERI0_M8_CPU1,	MAILBOX_PERI0_M8, CPU1, 222, 223, default_cb},
	{ IDX_MAILBOX_PERI0_M9_CPU0,	MAILBOX_PERI0_M9, CPU0, 0, 0, default_cb},
	{ IDX_MAILBOX_PERI0_M9_CPU1,	MAILBOX_PERI0_M9, CPU1, 0, 0, default_cb},
	{ IDX_MAILBOX_PERI0_M10_CPU0,	MAILBOX_PERI0_M10, CPU0, 0, 0, default_cb},
	{ IDX_MAILBOX_PERI0_M10_CPU1,	MAILBOX_PERI0_M10, CPU1, 0, 0, default_cb},
	{ IDX_MAILBOX_PERI0_M11_CPU0,	MAILBOX_PERI0_M11, CPU0, 232, 233, default_cb},
	{ IDX_MAILBOX_PERI0_M11_CPU1,	MAILBOX_PERI0_M11, CPU1, 234, 235, default_cb},
	{ IDX_MAILBOX_PERI0_M12_CPU0,	MAILBOX_PERI0_M12, CPU0, 236, 237, default_cb},
	{ IDX_MAILBOX_PERI0_M12_CPU1,	MAILBOX_PERI0_M12, CPU1, 238, 239, default_cb},

	{ IDX_MAILBOX_PERI1_M7_CPU0,	MAILBOX_PERI1_M7, CPU0, 266, 267, default_cb},
	{ IDX_MAILBOX_PERI1_M7_CPU1,	MAILBOX_PERI1_M7, CPU1, 268, 269, default_cb},
	{ IDX_MAILBOX_PERI1_M8_CPU0,	MAILBOX_PERI1_M8, CPU0, 270, 271, default_cb},
	{ IDX_MAILBOX_PERI1_M8_CPU1,	MAILBOX_PERI1_M8, CPU1, 272, 273, default_cb},
	{ IDX_MAILBOX_PERI1_M9_CPU0,	MAILBOX_PERI1_M9, CPU0, 0, 0, default_cb},
	{ IDX_MAILBOX_PERI1_M9_CPU1,	MAILBOX_PERI1_M9, CPU1, 0, 0, default_cb},
	{ IDX_MAILBOX_PERI1_M10_CPU0,	MAILBOX_PERI1_M10, CPU0, 0, 0, default_cb},
	{ IDX_MAILBOX_PERI1_M10_CPU1,	MAILBOX_PERI1_M10, CPU1, 0, 0, default_cb},
	{ IDX_MAILBOX_PERI1_M11_CPU0,	MAILBOX_PERI1_M11, CPU0, 282, 283, default_cb},
	{ IDX_MAILBOX_PERI1_M11_CPU1,	MAILBOX_PERI1_M11, CPU1, 284, 285, default_cb},
	{ IDX_MAILBOX_PERI1_M12_CPU0,	MAILBOX_PERI1_M12, CPU0, 286, 287, default_cb},
	{ IDX_MAILBOX_PERI1_M12_CPU1,	MAILBOX_PERI1_M12, CPU1, 288, 289, default_cb},

	{IDX_MAILBOX_PCIE_VF0,	MAILBOX_PCIE, CPU1, 185, 0, default_cb},
	{IDX_MAILBOX_PCIE_VF1,	MAILBOX_PCIE_VF1, CPU1, 0, 0, default_cb},
	{IDX_MAILBOX_PCIE_VF2,	MAILBOX_PCIE_VF2, CPU1, 0, 0, default_cb},
	{IDX_MAILBOX_PCIE_VF3,	MAILBOX_PCIE_VF3, CPU1, 0, 0, default_cb},
	{IDX_MAILBOX_PCIE_VF4,	MAILBOX_PCIE_VF4, CPU1, 0, 0, default_cb},
	{IDX_MAILBOX_PCIE_VF5,	MAILBOX_PCIE_VF5, CPU1, 0, 0, default_cb},
	{IDX_MAILBOX_PCIE_VF6,	MAILBOX_PCIE_VF6, CPU1, 0, 0, default_cb},
	{IDX_MAILBOX_PCIE_VF7,	MAILBOX_PCIE_VF7, CPU1, 0, 0, default_cb},
	{IDX_MAILBOX_PCIE_VF8,	MAILBOX_PCIE_VF8, CPU1, 0, 0, default_cb},
	{IDX_MAILBOX_PCIE_VF9,	MAILBOX_PCIE_VF9, CPU1, 0, 0, default_cb},
	{IDX_MAILBOX_PCIE_VF10,	MAILBOX_PCIE_VF10, CPU1, 0, 0, default_cb},
	{IDX_MAILBOX_PCIE_VF11,	MAILBOX_PCIE_VF11, CPU1, 0, 0, default_cb},
	{IDX_MAILBOX_PCIE_VF12,	MAILBOX_PCIE_VF12, CPU1, 0, 0, default_cb},
	{IDX_MAILBOX_PCIE_VF13,	MAILBOX_PCIE_VF13, CPU1, 0, 0, default_cb},
	{IDX_MAILBOX_PCIE_VF14,	MAILBOX_PCIE_VF14, CPU1, 0, 0, default_cb},
	{IDX_MAILBOX_PCIE_VF15,	MAILBOX_PCIE_VF15, CPU1, 0, 0, default_cb},
	{IDX_MAILBOX_PCIE_PF,	MAILBOX_PCIE_PF, CPU1, 0, 0, default_cb},
#else
	{IDX_MAILBOX_M1,		MAILBOX_ROT_M2_PRIVATE, CPU1, 25, 26, default_cb},
	{IDX_MAILBOX_CP0_M3,	MAILBOX_CP0_M4_PRIVATE, CPU1, 27, 28, default_cb},
	{IDX_MAILBOX_CP1_M3,	MAILBOX_CP1_M4_PRIVATE, CPU1, 29, 30, default_cb},

	{ IDX_MAILBOX_PERI0_M6,			MAILBOX_PERI0_M6, CPU1, 250, 251, default_cb},
	{ IDX_MAILBOX_PERI0_M9_CPU0,	MAILBOX_PERI0_M9, CPU0, 224, 225, default_cb},
	{ IDX_MAILBOX_PERI0_M9_CPU1,	MAILBOX_PERI0_M9, CPU1, 226, 227, default_cb},
	{ IDX_MAILBOX_PERI0_M10_CPU0,	MAILBOX_PERI0_M10, CPU0, 228, 229, default_cb},
	{ IDX_MAILBOX_PERI0_M10_CPU1,	MAILBOX_PERI0_M10, CPU1, 230, 231, default_cb},
	{ IDX_MAILBOX_PERI0_M11_CPU0,	MAILBOX_PERI0_M11, CPU0, 0, 0, default_cb},
	{ IDX_MAILBOX_PERI0_M11_CPU1,	MAILBOX_PERI0_M11, CPU1, 0, 0, default_cb},
	{ IDX_MAILBOX_PERI0_M12_CPU0,	MAILBOX_PERI0_M12, CPU0, 0, 0, default_cb},
	{ IDX_MAILBOX_PERI0_M12_CPU1,	MAILBOX_PERI0_M12, CPU1, 0, 0, default_cb},
	{ IDX_MAILBOX_PERI0_M13_CPU0,	MAILBOX_PERI0_M13, CPU0, 240, 241, default_cb},
	{ IDX_MAILBOX_PERI0_M13_CPU1,	MAILBOX_PERI0_M13, CPU1, 242, 243, default_cb},
	{ IDX_MAILBOX_PERI0_M14_CPU0,	MAILBOX_PERI0_M14, CPU0, 244, 245, default_cb},
	{ IDX_MAILBOX_PERI0_M14_CPU1,	MAILBOX_PERI0_M14, CPU1, 246, 247, default_cb},

	{ IDX_MAILBOX_PERI1_M9_CPU0,	MAILBOX_PERI1_M9, CPU0, 274, 275, default_cb},
	{ IDX_MAILBOX_PERI1_M9_CPU1,	MAILBOX_PERI1_M9, CPU1, 276, 277, default_cb},
	{ IDX_MAILBOX_PERI1_M10_CPU0,	MAILBOX_PERI1_M10, CPU0, 278, 279, default_cb},
	{ IDX_MAILBOX_PERI1_M10_CPU1,	MAILBOX_PERI1_M10, CPU1, 280, 281, default_cb},
	{ IDX_MAILBOX_PERI1_M11_CPU0,	MAILBOX_PERI1_M11, CPU0, 0, 0, default_cb},
	{ IDX_MAILBOX_PERI1_M11_CPU1,	MAILBOX_PERI1_M11, CPU1, 0, 0, default_cb},
	{ IDX_MAILBOX_PERI1_M12_CPU0,	MAILBOX_PERI1_M12, CPU0, 0, 0, default_cb},
	{ IDX_MAILBOX_PERI1_M12_CPU1,	MAILBOX_PERI1_M12, CPU1, 0, 0, default_cb},
	{ IDX_MAILBOX_PERI1_M13_CPU0,	MAILBOX_PERI1_M13, CPU0, 290, 291, default_cb},
	{ IDX_MAILBOX_PERI1_M13_CPU1,	MAILBOX_PERI1_M13, CPU1, 292, 293, default_cb},
	{ IDX_MAILBOX_PERI1_M14_CPU0,	MAILBOX_PERI1_M14, CPU0, 294, 295, default_cb},
	{ IDX_MAILBOX_PERI1_M14_CPU1,	MAILBOX_PERI1_M14, CPU1, 296, 297, default_cb},
#endif
};

static inline int is_valid_inst(int inst)
{
	if (inst < IDX_MAILBOX_START || inst >= IDX_MAILBOX_END) {
		return 0;
	}
	return 1;
}

int ipm_samsung_write(const int inst, const uint32_t target_id, const void *data, const int size,
					  const int issr_index)
{
	if (!is_valid_inst(inst)) {
		return -ENODEV;
	}
#if defined __TARGET_CP
	volatile struct ipm_samsung *const sfr = (struct ipm_samsung *)(mailbox_data[inst].base +
											  (target_id * CHIPLET_OFFSET) - FREERTOS_VA_OFFSET);
#elif defined __TARGET_PCIE
	volatile struct ipm_samsung *const sfr = (struct ipm_samsung *)(mailbox_data[inst].base);
#endif
	uint32_t *issr = (uint32_t *)(&sfr->issr0) + issr_index;
	uint32_t i;
	const uint32_t *ptr = data;

	for (i = 0; i < DATA_SIZE(size); ++i) {
		if ((issr_index + i) > ISSR_MAX) {
			return -ENOBUFS;
		}
		issr[i] = *(ptr + i);
	}

	return i * sizeof(uint32_t);
}

int ipm_samsung_send(const int inst, const uint32_t target_id, const int channel,
					 const uint32_t cpu_id)
{
	if (!is_valid_inst(inst)) {
		return -ENODEV;
	}

	volatile uint32_t *intgr;
#if defined __TARGET_CP
	volatile struct ipm_samsung *const sfr = (struct ipm_samsung *)(mailbox_data[inst].base +
											  (target_id * CHIPLET_OFFSET) - FREERTOS_VA_OFFSET);
#elif defined __TARGET_PCIE
	volatile struct ipm_samsung *const sfr = (struct ipm_samsung *)(mailbox_data[inst].base);
#endif

	if (cpu_id == CPU0) {
		intgr = &sfr->intgr0.val;
	} else {
		intgr = &sfr->intgr1.val;
	}
	*intgr = (uint32_t)BIT(channel);

	return 0;
}

int ipm_samsung_receive(const int inst, void *data, const int size, const int issr_index)
{
	if (!is_valid_inst(inst)) {
		return -ENODEV;
	}

	volatile struct ipm_samsung *const sfr = (struct ipm_samsung *)mailbox_data[inst].base;
	uint32_t *issr = (uint32_t *)(&sfr->issr0) + issr_index;
	uint32_t i;
	uint32_t *ptr = data;

	for (i = 0 ; i < DATA_SIZE(size); ++i) {
		if ((issr_index + i) > ISSR_MAX)
			return -ENOBUFS;
		*(ptr + i) = issr[i];
	}

	return i * sizeof(uint32_t);
}

static inline uint32_t find_msb_set(uint32_t op)
{
	if (op == 0) {
		return 0;
	}

	return 32 - __builtin_clz(op);
}

#if defined __TARGET_PCIE
static int get_instance_num(const int int_num)
{
	int inst;

	for (inst = IDX_MAILBOX_START; inst < IDX_MAILBOX_END; ++inst) {
		if (int_num == mailbox_data[inst].irq_num_high || int_num == mailbox_data[inst].irq_num_low)
			return inst;
	}
	return -1;
}
#endif

/*
 * This function is called by the isr, but if it cannot find a pending instance, it returns
 * the representative instance of the PCIE mailbox, which is VF0, and terminates the operation
 * in the subsequent channel verification process.
 */
static struct ipm_device *get_pend_pcie(int inst, const int idx_end)
{
	volatile struct ipm_samsung *sfr;
	int intmsr_val;
	struct ipm_device *d = &mailbox_data[inst];

	while (inst <= idx_end) {
		d = &mailbox_data[inst++];
		sfr = (struct ipm_samsung *)d->base;

		if (d->cpu_id == CPU0) {
			intmsr_val = sfr->intmsr0.val;
		} else {
			intmsr_val = sfr->intmsr1.val;
		}
		if (intmsr_val & 0xffff) {
			break;
		}
	}

	return d;
}

void ipm_samsung_isr(struct ipm_device *d)
{
	disable_all_interrupts();

	volatile struct ipm_samsung *sfr;
	uint32_t intmsr_val;
	int inst = d->inst;

	#if defined __TARGET_PCIE
		uint32_t icsr = ((SCB->ICSR) & 0x1ff) - 16;

		inst = get_instance_num(icsr);
		if (inst < IDX_MAILBOX_START)
			return;

		if (inst >= IDX_MAILBOX_PCIE_START && inst <= IDX_MAILBOX_PCIE_VF15) {
			d = get_pend_pcie(IDX_MAILBOX_PCIE_VF0, IDX_MAILBOX_PCIE_VF15);
			inst = d->inst;
		} else {
			d = &mailbox_data[inst];
		}
	#elif (__TARGET_CP == 0)
		if (d->inst >= IDX_MAILBOX_PCIE_START && d->inst <= IDX_MAILBOX_PCIE_PF) {
			d = get_pend_pcie(IDX_MAILBOX_PCIE_VF0, IDX_MAILBOX_PCIE_PF);
		}

		inst = d->inst;
	#endif

	sfr = (struct ipm_samsung *)d->base;

	if (d->cpu_id == CPU0)
		intmsr_val = sfr->intmsr0.val;
	else
		intmsr_val = sfr->intmsr1.val;

	int chan = find_msb_set(intmsr_val) - 1;

	if (chan < 0) {
		return;
	}

	if (d->cpu_id == CPU0)
		sfr->intcr0.val |= BIT(chan);
	else
		sfr->intcr1.val |= BIT(chan);

	if (d->callback) {
		d->callback(inst, chan);
	}

	enable_all_interrupts();
}

void ipm_samsung_register_callback(const int inst, void (*cb)(const int, const int))
{
	if (is_valid_inst(inst)) {
		mailbox_data[inst].callback = cb;
	}
}

#if (__TARGET_CP == 1)
int ipm_samsung_init(void)
{
	for (int i = IDX_MAILBOX_START; i < IDX_MAILBOX_END; ++i) {
		if (mailbox_data[i].irq_num_low != 0) {
			connect_interrupt_with_core_handler(mailbox_data[i].irq_num_low, 0, IRQ_TYPE_LEVEL,
												0x100, ipm_samsung_isr, &mailbox_data[i]);
		}
		if (mailbox_data[i].irq_num_high != 0) {
			connect_interrupt_with_core_handler(mailbox_data[i].irq_num_high, 0, IRQ_TYPE_LEVEL,
												0x100, ipm_samsung_isr, &mailbox_data[i]);
		}
	}
	return 0;
}
#else
int ipm_samsung_init(void)
{
	for (int i = IDX_MAILBOX_START; i < IDX_MAILBOX_END; ++i) {
		if (mailbox_data[i].irq_num_low != 0) {
			connect_interrupt_with_handler(mailbox_data[i].irq_num_low, 0, IRQ_TYPE_LEVEL,
										   ipm_samsung_isr, &mailbox_data[i]);
		}
		if (mailbox_data[i].irq_num_high != 0) {
			connect_interrupt_with_handler(mailbox_data[i].irq_num_high, 0, IRQ_TYPE_LEVEL,
										   ipm_samsung_isr, &mailbox_data[i]);
		}
	}
	return 0;
}
#endif

int ipm_samsung_read(const int inst, const uint32_t target_id, void *data, const int size, const int issr_index)
{
	if (!is_valid_inst(inst)) {
		return -ENODEV;
	}

#if defined __TARGET_CP
	volatile struct ipm_samsung *const sfr = (struct ipm_samsung *)(mailbox_data[inst].base +
											  (target_id * CHIPLET_OFFSET) - FREERTOS_VA_OFFSET);
#elif defined __TARGET_PCIE
	volatile struct ipm_samsung *const sfr = (struct ipm_samsung *)(mailbox_data[inst].base);
#endif

	uint32_t *issr = (uint32_t *)(&sfr->issr0) + issr_index;
	uint32_t i;
	uint32_t *ptr = data;

	for (i = 0 ; i < DATA_SIZE(size); ++i) {
		if ((issr_index + i) > ISSR_MAX)
			return -ENOBUFS;
		*(ptr + i) = issr[i];
	}

	return i * sizeof(uint32_t);
}

#if defined(__RUN_RTOS)
DRIVER_INIT_ENTRY_DEFINE(8, ipm_samsung_init);
#endif
