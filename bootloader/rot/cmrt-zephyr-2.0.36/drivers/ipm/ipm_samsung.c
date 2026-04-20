/*
 * Copyright (c) 2019 Linaro Limited
 * Copyright (c) 2024 Samsung Electronics Co, Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#define DT_DRV_COMPAT samsung_mailbox

#include <errno.h>
#include <device.h>
#include <soc.h>
#include <drivers/cmrt/sac.h>
#include <rebel_h.h>
#include "ipm_samsung.h"

#define DEV_CFG(dev) \
	((const struct ipm_samsung_device_config * const)(dev)->config)
#define DEV_DATA(dev) \
	((struct ipm_samsung_data *)(dev)->data)
#define IPM_SAMSUNG_REGS(dev) \
	(uint64_t)(DEV_CFG(dev)->base)

#define IPM_SAMSUNG_MAX_DATA_SIZE		(4)
#define IPM_SAMSUNG_MAX_ID_VAL			(1)

#define MCUCTLR							(0x0)
#define INTGR0							(0x8)
#define INTCR0							(0xc)
#define INTMR0							(0x10)
#define INTSR0							(0x14)
#define INTMSR0							(0x18)
#define INTGR1							(0x1c)
#define INTCR1							(0x20)
#define INTMR1							(0x24)
#define INTSR1							(0x28)
#define INTMSR1							(0x2c)
#define IS_VERSION						(0x50)
#define ISSR							(0x80)
#define SEMAPHORE						(0x180)

#define SW_RESET						(0x1)
#define CLEAR_INTERRUPT					(0x1)

#define ISSR_MAX						(63)
#define IRQ_NUM_MAX						(32)
#define IRQ_NUM_HIGH					(16)
#define CHANNEL_PER_CPU					(32)
#define CHANNEL_PER_HIGH_LOW			(16)
#define HIGH_IRQ(n)						((n) * IRQ_NUM_HIGH)
#define ISSR_OFFSET(n)					((n) * 4)

#define DATA_SIZE(s)					(((s) - 1) / 4 + 1)

/* Device data structure */
struct ipm_samsung_data {
	ipm_samsung_callback_t callback;
};

struct ipm_samsung_device_config {
	uint64_t base;
	void (*irq_config_func)(void);
};

static int ipm_samsung_send(const struct device *d, const uint32_t target_id, const int channel,
							const uint32_t cpu_id)
{
	uint64_t intgr;
	uint64_t base = IPM_SAMSUNG_REGS(d) + (target_id * CHIPLET_BASE_OFFSET);

	if (cpu_id == CPU0) {
		intgr = base + INTGR0;
	} else {
		intgr = base + INTGR1;
	}

	cmrt_sac_set_base(NULL, GET_SAC_BASE(intgr));
	cmrt_sac_write32(BIT(channel), GET_SAC_OFFSET(intgr));

	return 0;
}

static uint32_t ipm_samsung_max_id_val_get(const struct device *d)
{
	ARG_UNUSED(d);

	return IPM_SAMSUNG_MAX_ID_VAL;
}

static int ipm_samsung_init(const struct device *d)
{
	const struct ipm_samsung_device_config *config = DEV_CFG(d);

	config->irq_config_func();

	cmrt_sac_set_base(NULL, GET_SAC_BASE(config->base + MCUCTLR));
	cmrt_sac_write32(SW_RESET, GET_SAC_OFFSET(config->base + MCUCTLR));

	return 0;
}

static void ipm_samsung_isr(const struct device *d)
{
	struct ipm_samsung_data *driver_data = DEV_DATA(d);
	uint32_t chan;
	uint32_t intmsr_val;
	uint32_t chiplet_id = get_chiplet_id();
	uint64_t base = IPM_SAMSUNG_REGS(d) + (chiplet_id * CHIPLET_BASE_OFFSET);
	int key = irq_lock();

	cmrt_sac_set_base(NULL, GET_SAC_BASE(base + INTMSR0));
	intmsr_val = cmrt_sac_read32(GET_SAC_OFFSET(base + INTMSR0));
	chan = find_msb_set(intmsr_val) - 1u;
	if (chan > IRQ_NUM_MAX)
		z_irq_spurious(NULL);

	if (driver_data->callback) {
		driver_data->callback(d, chan);
	}

	cmrt_sac_set_base(NULL, GET_SAC_BASE(base + INTCR0));
	cmrt_sac_write32((CLEAR_INTERRUPT << chan), GET_SAC_OFFSET(base + INTCR0));

	irq_unlock(key);
}

static int ipm_samsung_set_enabled(const struct device *d, int enable)
{
	ARG_UNUSED(d);
	ARG_UNUSED(enable);

	return 0;
}

static int ipm_samsung_max_data_size_get(const struct device *d)
{
	ARG_UNUSED(d);

	return IPM_SAMSUNG_MAX_DATA_SIZE;
}

static void ipm_samsung_register_cb(const struct device *d, ipm_samsung_callback_t cb)
{
	struct ipm_samsung_data *driver_data = DEV_DATA(d);

	if (!driver_data) {
		return;
	}

	driver_data->callback = cb;
}

static int ipm_samsung_write(const struct device *d, const uint32_t target_id, const void *data,
							 const int size, int issr_index)
{
	uint64_t base = IPM_SAMSUNG_REGS(d) + (target_id * CHIPLET_BASE_OFFSET);

	uint64_t issr = base + ISSR + ISSR_OFFSET(issr_index);
	const uint32_t *ptr = data;
	uint32_t i;

	for (i = 0; i < DATA_SIZE(size); ++i) {
		if ((issr_index + i) > ISSR_MAX)
			return -ENOBUFS;
		cmrt_sac_set_base(NULL, GET_SAC_BASE(issr));
		cmrt_sac_write32(*(ptr + i), GET_SAC_OFFSET(issr));
		issr += sizeof(uint32_t);
	}

	return i * sizeof(uint32_t);
}

static int ipm_samsung_receive(const struct device *d, void *data, const int size,
							   const int issr_index)
{
	uint32_t chiplet_id = get_chiplet_id();
	uint64_t base = IPM_SAMSUNG_REGS(d) + (chiplet_id * CHIPLET_BASE_OFFSET);
	uint64_t issr = base + ISSR + ISSR_OFFSET(issr_index);
	uint32_t *ptr = data;
	uint32_t i;

	for (i = 0; i < DATA_SIZE(size); ++i) {
		if ((issr_index + i) > ISSR_MAX)
			return -ENOBUFS;
		cmrt_sac_set_base(NULL, GET_SAC_BASE(issr));
		*(ptr + i) = cmrt_sac_read32(GET_SAC_OFFSET(issr));
		issr += sizeof(uint32_t);
	}

	return i * sizeof(uint32_t);
}

static const struct ipm_samsung_api ipm_samsung_driver_api = {
	.api.max_data_size_get = ipm_samsung_max_data_size_get,
	.api.max_id_val_get = ipm_samsung_max_id_val_get,
	.api.set_enabled = ipm_samsung_set_enabled,

	.send = ipm_samsung_send,
	.write = ipm_samsung_write,
	.receive = ipm_samsung_receive,
	.register_callback = ipm_samsung_register_cb,
};

#define SAMSUNG_MAILBOX_DEVICE_INIT(inst_num)										\
	static void ipm_samsung_irq_config_func_##inst_num(void);						\
																					\
	static const struct ipm_samsung_device_config ipm_samsung_cfg_##inst_num = {	\
		.base = DT_INST_REG_ADDR(inst_num),											\
		.irq_config_func = ipm_samsung_irq_config_func_##inst_num,					\
	};																				\
																					\
	static struct ipm_samsung_data ipm_samsung_data_##inst_num = {					\
		.callback = NULL,															\
	};																				\
																					\
	DEVICE_DT_INST_DEFINE(															\
		inst_num,																	\
		&ipm_samsung_init,															\
		NULL,																		\
		&ipm_samsung_data_##inst_num,												\
		&ipm_samsung_cfg_##inst_num,												\
		PRE_KERNEL_1,																\
		CONFIG_KERNEL_INIT_PRIORITY_DEVICE,											\
		&ipm_samsung_driver_api);													\
																					\
	static void ipm_samsung_irq_config_func_##inst_num(void)						\
	{																				\
		IRQ_CONNECT(																\
			DT_INST_IRQ_BY_IDX(inst_num, 0, irq),									\
			DT_INST_IRQ_BY_IDX(inst_num, 0, priority),								\
			ipm_samsung_isr,														\
			DEVICE_DT_INST_GET(inst_num),											\
			0);																		\
		irq_enable(DT_INST_IRQ_BY_IDX(inst_num, 0, irq));							\
		IRQ_CONNECT(																\
			DT_INST_IRQ_BY_IDX(inst_num, 1, irq),									\
			DT_INST_IRQ_BY_IDX(inst_num, 1, priority),								\
			ipm_samsung_isr,														\
			DEVICE_DT_INST_GET(inst_num),											\
			0);																		\
		irq_enable(DT_INST_IRQ_BY_IDX(inst_num, 1, irq));							\
	}

DT_INST_FOREACH_STATUS_OKAY(SAMSUNG_MAILBOX_DEVICE_INIT)
