#include "stdlib.h"
#include <drivers/mailbox/mailbox.h>
#include <string.h>
#include <errno.h>
#include <platform_def.h>

#define ISSR_MAX				(63)
#define DATA_SIZE(s)			(((s) - 1) / 4 + 1)

struct ipm_device {
	uint32_t inst;
	uint64_t base;
	enum _CPU_ID cpu_id;
	uint32_t irq_num_low;
	uint32_t irq_num_high;
	void (*callback)(int inst, int channel);
};

static struct ipm_device mailbox_data[] = {
	{ IDX_MAILBOX_M0,		MAILBOX_ROT_M0, M_CPU1, 32, 33, NULL},
	{ IDX_MAILBOX_CP0_M3,	MAILBOX_CP0_M3, M_CPU0, 144, 145, NULL},
	{ IDX_MAILBOX_CP0_M4,	MAILBOX_CP0_M4, M_CPU0, 148, 149, NULL},
	{ IDX_MAILBOX_CP1_M3,	MAILBOX_CP1_M3, M_CPU0, 154, 155, NULL},
	{ IDX_MAILBOX_CP1_M4,	MAILBOX_CP1_M4, M_CPU0, 158, 159, NULL},
	{ IDX_MAILBOX_CP0_M4_C3, MAILBOX_CP0_M4_C3, M_CPU0, 0, 0, NULL},
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

	volatile struct ipm_samsung *const sfr = (struct ipm_samsung *)(mailbox_data[inst].base);
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
	volatile struct ipm_samsung *const sfr = (struct ipm_samsung *)(mailbox_data[inst].base);

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
