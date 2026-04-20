#define DT_DRV_COMPAT samsung_sysreg_rot

#include <errno.h>
#include <device.h>
#include <soc.h>
#include <drivers/cmrt/sac.h>
#include <rebel_h.h>

#define DEV_CFG(dev) \
	((const struct sysreg_rot_device_config * const)(dev)->config)
#define SYSREG_SAMSUNG_REGS(dev) \
	(uint64_t)(DEV_CFG(dev)->base)

struct sysreg_rot {
	uint32_t sys_cm_alarms;
	uint32_t sys_cm_interrupt;
};

struct sysreg_rot_device_config {
	uint64_t base;
};

static const struct sysreg_rot_device_config sysreg_rot_cfg = {
	.base = (uint64_t)DT_INST_REG_ADDR(0),
};

#define CLEAR_INTERRUPT	(0)
#define SYS_CM_INTERRUPT	(0x4)
static void sysreg_rot_isr(const struct device *d)
{
	uint64_t sys_cm_interrupt = SYSREG_SAMSUNG_REGS(d) + SYS_CM_INTERRUPT;
	uint64_t current_base = cmrt_sac_get_base(NULL);

	cmrt_sac_set_base(NULL, GET_SAC_BASE(sys_cm_interrupt));
	cmrt_sac_write32(CLEAR_INTERRUPT, GET_SAC_OFFSET(sys_cm_interrupt));
	cmrt_sac_set_base(NULL, current_base);
}

static void sysreg_rot_irq_config(void)
{
	IRQ_CONNECT(DT_INST_IRQN(0),
				DT_INST_IRQ(0, priority), sysreg_rot_isr,
				DEVICE_DT_INST_GET(0), 0);
	irq_enable(DT_INST_IRQN(0));
}

static int sysreg_rot_init(const struct device *d)
{
	ARG_UNUSED(d);

	sysreg_rot_irq_config();

	return 0;
}

DEVICE_DT_INST_DEFINE(0, sysreg_rot_init, NULL,
					  NULL, &sysreg_rot_cfg, PRE_KERNEL_1,
					  CONFIG_KERNEL_INIT_PRIORITY_DEVICE, NULL);
