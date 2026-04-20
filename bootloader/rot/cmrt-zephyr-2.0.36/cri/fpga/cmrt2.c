/**
 * Copyright (c) 2022-2023 Cryptography Research, Inc. (CRI).
 */

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/poll.h>
#include <linux/firmware.h>
#include <linux/device.h>
#include <linux/uaccess.h>
#include <linux/mutex.h>
#include <linux/delay.h>
#include <linux/pci.h>
#include <linux/io.h>
#include <linux/kthread.h>
#include <linux/slab.h>
#include <linux/mtio.h>
#include <linux/mm.h>
#include <linux/of.h>
#include <linux/of_device.h>
#include <linux/interrupt.h>
#include <linux/version.h>
#include <linux/random.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Rambus Cryptography Research, Inc.");
MODULE_DESCRIPTION("CMRT Linux kernel module example");

#define DEVICE_NAME "cmrt2"
#define CMRT_MAJORNO 123UL

#define R_SYSCTL_VERSION           0x00UL
#define R_SYSCTL_CONTROL           0x04UL
#define R_SYSCTL_SOC_INTERRUPT_OUT 0x18UL

#define CMRT_SYSCTL_RESET_HARD     (1UL << 0)
#define CMRT_SYSCTL_RESET_POWERON  (1UL << 1)
#define CMRT_SYSCTL_RESET_MASK     (CMRT_SYSCTL_RESET_HARD | CMRT_SYSCTL_RESET_POWERON)

/*
 * Module configuration using array parameters, for example:
 * 0x00100000,0x0000C000,0x40200000,0x0000C000,0,0 = SOG is there fully mapped
 * 0x00100000,0x0000C000,0x00000000,0x00000000,0,0 = No backdoor for SOG
 * 0x40000000,0x40000000,0x41500000,0x00080000,0,0 = 1G SAC in CMRT, 512K phys
 *
 * Default configs for a version of Zynq706 FPGA that has
 * 256K SRAM, 256K masked ROM, 1K OTP, 1G SAC RAM.
 *
 * Additional mappings like dm are at end of CMRT device area
 * in case they need to be visible for the userspace.
 */
enum {
	MPA_CMRT_BASE, MPA_CMRT_SIZE, MPA_PHYS_BASE, MPA_PHYS_SIZE, MPA_BAR_NUM, MPA_BAR_OFFSET, MPA_CONF_COLS
};

static unsigned long devcfg_conf[MPA_CONF_COLS] = {
	0x00000000, 0x0, 0xF8007000, 0x1000, 0, 0
};
static unsigned long sysctl_conf[MPA_CONF_COLS] = {
	0x00000000, 0x1000, 0x40000000, 0x1000, 0, 0
};
static unsigned long sic_conf[MPA_CONF_COLS] = {
	0x00001000, 0x1000, 0x40800000, 0x1000, 0, 0
};
static unsigned long sog_conf[MPA_CONF_COLS] = {
	0x00800000, 0x10000, 0x40100000, 0x10000, 0, 0
};
static unsigned long cfi_conf[MPA_CONF_COLS] = {
	0x00810000, 0x10000, 0x40180000, 0x10000, 0, 0
};
static unsigned long rom_conf[MPA_CONF_COLS] = {
	0x00880000, 0x0, 0x40200000, 0x0, 0, 0
};
static unsigned long sram_conf[MPA_CONF_COLS] = {
	0x01000000, 0x80000, 0x40400000, 0x80000, 0, 0
};
static unsigned long otp_conf[MPA_CONF_COLS] = {
	0x00300000, 0x4000, 0x40300000, 0x4000, 0, 0
};
static unsigned long sac_conf[MPA_CONF_COLS] = {
	0x40000000, 0x40000000, 0x41500000, 0x80000, 0, 0
};
static unsigned long dm_conf[MPA_CONF_COLS] = {
	0x000FF000, 0x1000, 0x41200000, 0x1000, 0, 0
};
static unsigned long oec_conf[MPA_CONF_COLS] = {
	0x00000000, 0x0, 0x00000000, 0x0, 0, 0
};
static unsigned long fic_conf[MPA_CONF_COLS] = {
	0x00000000, 0x0, 0x00000000, 0x0, 0, 0
};
static unsigned long puf_conf[MPA_CONF_COLS] = {
	0x00000000, 0x0, 0x00000000, 0x0, 0, 0
};

module_param_array(devcfg_conf, ulong, NULL, 0);
MODULE_PARM_DESC(devcfg_conf, "FPGA device register mapping.");

module_param_array(sysctl_conf, ulong, NULL, 0);
MODULE_PARM_DESC(sysctl_conf, "FPGA sysctl register mapping.");

module_param_array(sic_conf, ulong, NULL, 0);
MODULE_PARM_DESC(sic_conf, "CMRT SIC register mapping.");

module_param_array(sog_conf, ulong, NULL, 0);
MODULE_PARM_DESC(sog_conf, "CMRT SoG ROM mapping.");

module_param_array(cfi_conf, ulong, NULL, 0);
MODULE_PARM_DESC(cfi_conf, "CMRT CFI ROM mapping.");

module_param_array(rom_conf, ulong, NULL, 0);
MODULE_PARM_DESC(rom_conf, "CMRT masked ROM mapping.");

module_param_array(sram_conf, ulong, NULL, 0);
MODULE_PARM_DESC(sram_conf, "CMRT SRAM mapping.");

module_param_array(otp_conf, ulong, NULL, 0);
MODULE_PARM_DESC(otp_conf, "CMRT OTP mapping.");

module_param_array(sac_conf, ulong, NULL, 0);
MODULE_PARM_DESC(sac_conf, "CMRT SAC RAM mapping.");

module_param_array(dm_conf, ulong, NULL, 0);
MODULE_PARM_DESC(dm_conf, "CMRT debug module mapping.");

module_param_array(oec_conf, ulong, NULL, 0);
MODULE_PARM_DESC(oec_conf, "CMRT OEC mapping.");

module_param_array(fic_conf, ulong, NULL, 0);
MODULE_PARM_DESC(fic_conf, "CMRT FIC mapping.");

module_param_array(puf_conf, ulong, NULL, 0);
MODULE_PARM_DESC(puf_conf, "CMRT PUF mapping.");

typedef struct cmrt_mem_conf {
	unsigned long *conf;
	const char *name;
	void __iomem *mem;
	phys_addr_t phys;
} cmrt_mem_conf_t;

enum {
	MEM_CONF_DEVCFG,
	MEM_CONF_SYSCTL,
	MEM_CONF_SIC,
	MEM_CONF_SOG,
	MEM_CONF_CFI,
	MEM_CONF_ROM,
	MEM_CONF_SRAM,
	MEM_CONF_OTP,
	MEM_CONF_SAC,
	MEM_CONF_DM,
	MEM_CONF_OEC,
	MEM_CONF_FIC,
	MEM_CONF_PUF,
	MEM_CONF_SIZE
};

static cmrt_mem_conf_t mem_conf[MEM_CONF_SIZE] = {
	{ devcfg_conf, "devcfg", NULL, 0 },
	{ sysctl_conf, "sysctl", NULL, 0 },
	{ sic_conf, "sic", NULL, 0 },
	{ sog_conf, "sog", NULL, 0 },
	{ cfi_conf, "cfi", NULL, 0 },
	{ rom_conf, "rom", NULL, 0 },
	{ sram_conf, "sram", NULL, 0 },
	{ otp_conf, "otp", NULL, 0 },
	{ sac_conf, "sac", NULL, 0 },
	{ dm_conf, "dm", NULL, 0 },
	{ oec_conf, "oec", NULL, 0 },
	{ fic_conf, "fic", NULL, 0 },
	{ puf_conf, "puf", NULL, 0 }
};

static DEFINE_MUTEX(cmrt_lock);
static struct task_struct *irq_thread;
static HLIST_HEAD(cmrt_procs);

typedef struct cmrt_proc {
	struct hlist_node proc_node;
	wait_queue_head_t waitq;
	uint32_t irq_mask;
} cmrt_proc_t;

/* Translate CMRT address into iomem pointer. */
static void __iomem *find_iomem(uint32_t cmrt_addr, size_t size, size_t *phys_size)
{
	int i;

	for (i = 0; i < MEM_CONF_SIZE; i++) {
		cmrt_mem_conf_t *mc = &mem_conf[i];
		if (mc->mem == NULL) {
			continue;
		}
		if (cmrt_addr >= mc->conf[MPA_CMRT_BASE]) {
			size_t offset = cmrt_addr - mc->conf[MPA_CMRT_BASE];
			if (offset + size <= mc->conf[MPA_CMRT_SIZE]) {
				*phys_size = mc->conf[MPA_PHYS_SIZE];
				if (offset + size > *phys_size) {
					/* Physical mem wraps around. It must be
					 * a power of 2 for things to work! */
					return mc->mem + (offset & (*phys_size - 1));
				}
				*phys_size = 0; /* skip wrapping read/write */
				return mc->mem + offset;
			}
		}
	}
	return NULL;
}

/* Return iomem pointer for the base and offset. */
static void __iomem *mem_ptr(unsigned long index, unsigned long offset)
{
	cmrt_mem_conf_t *mc;
	void __iomem *ptr;

	BUG_ON(index >= MEM_CONF_SIZE);
	mc = &mem_conf[index];
	ptr = mc->mem;
	BUG_ON(ptr == NULL);
	BUG_ON((offset & 0x03) || (offset >= mc->conf[MPA_PHYS_SIZE]));
	return ptr + offset;
}

static bool mem_read(void __iomem *mapped, char __user *buf, size_t count)
{
	while (count) {
		/* Read word at a time to avoid problems. */
		uint32_t word = ioread32(mapped);
		if (copy_to_user(buf, &word, sizeof(uint32_t))) {
			return false;
		}
		mapped += sizeof(uint32_t);
		buf += sizeof(uint32_t);
		count -= sizeof(uint32_t);
	}
	return true;
}

static ssize_t device_read(struct file *filp, char __user *buf, size_t count, loff_t *f_pos)
{
	size_t phys_size;
	ssize_t rv = count;
	uint32_t cmrt_addr = (uint32_t)*f_pos;
	void __iomem *mapped = find_iomem(cmrt_addr, count, &phys_size);
	cmrt_proc_t *proc = filp->private_data;
	void __iomem *sio = mem_ptr(MEM_CONF_SYSCTL,
				    R_SYSCTL_SOC_INTERRUPT_OUT);

	pr_info("%s: 0x%x->0x%x %u\n", __func__, cmrt_addr, (int)(long)mapped, (unsigned)count);

	if ((cmrt_addr & 0x03) || ((long)buf & 0x03) || (count & 0x03) || !mapped) {
		/* Allow only word aligned operations. */
		pr_info("%s: invalid read (0x%x 0x%x 0x%x 0x%x)\n",
			__func__, cmrt_addr, (int)(long)buf, (int)count, (int)(long)mapped);
		rv = -EINVAL;
		goto out;
	}
	if (mapped == sio && count == sizeof(uint32_t)) {
		/* Check interrupt mask for the process. */
		while (!(proc->irq_mask & ioread32(sio))) {
			/* No interrupt available now. */
			if (filp->f_flags & O_NONBLOCK) {
				rv = -EAGAIN;
				goto out;
			}
			if (wait_event_interruptible(proc->waitq, (proc->irq_mask & ioread32(sio)))) {
				rv = -ERESTARTSYS; /* signal */
				goto out;
			}
		}
	}
	if (phys_size > 0) {
		/* Applies to wrapping memories. */
		while ((cmrt_addr & (phys_size - 1)) + count > phys_size) {
			/* Handle physical memory wrapping. */
			size_t offset = cmrt_addr & (phys_size - 1);
			size_t length = phys_size - offset;
			if (!mem_read(mapped, buf, length)) {
				rv = -EIO;
				goto out;
			}
			buf += length;
			mapped += length;
			mapped -= phys_size;
			count -= length;
			cmrt_addr += length;
		}
	}
	/* The normal case. */
	if (!mem_read(mapped, buf, count)) {
		rv = -EIO;
		goto out;
	}
	*f_pos += count;
 out:
	return rv;
}

static bool mem_write(void __iomem *mapped, const char __user *buf, size_t count)
{
	while (count) {
		/* Write word at a time to avoid problems. */
		uint32_t word;
		if (copy_from_user(&word, buf, sizeof(uint32_t))) {
			return false;
		}
		iowrite32(word, mapped);
		mapped += sizeof(uint32_t);
		buf += sizeof(uint32_t);
		count -= sizeof(uint32_t);
	}
	return true;
}

static ssize_t device_write(struct file *filp, const char __user *buf, size_t count, loff_t *f_pos)
{
	size_t phys_size;
	ssize_t rv = count;
	uint32_t cmrt_addr = (uint32_t)*f_pos;
	void __iomem *mapped = find_iomem(cmrt_addr, count, &phys_size);
	cmrt_proc_t *proc = filp->private_data;
	void __iomem *sio = mem_ptr(MEM_CONF_SYSCTL,
				    R_SYSCTL_SOC_INTERRUPT_OUT);

	pr_info("%s: 0x%x->0x%x %u\n", __func__, cmrt_addr, (int)(long)mapped, (unsigned)count);

	if ((cmrt_addr & 0x03) || ((long)buf & 0x03) || (count & 0x03) || !mapped) {
		/* Allow only word aligned operations. */
		pr_info("%s: invalid write (0x%x or 0x%x or 0x%x or 0x%x)\n",
			__func__, cmrt_addr, (int)(long)buf, (int)count, (int)(long)mapped);
		rv = -EINVAL;
		goto out;
	}
	if (mapped == sio && count == sizeof(uint32_t)) {
		/* Set interrupt mask for the process. */
		if (copy_from_user(&proc->irq_mask, buf, sizeof(uint32_t))) {
			rv = -EIO;
		}
		goto out;
	}
	if (phys_size > 0) {
		/* Applies to wrapping memories. */
		while ((cmrt_addr & (phys_size - 1)) + count > phys_size) {
			/* Handle physical memory wrapping. */
			size_t offset = cmrt_addr & (phys_size - 1);
			size_t length = phys_size - offset;
			if (!mem_write(mapped, buf, length)) {
				rv = -EIO;
				goto out;
			}
			buf += length;
			mapped += length;
			mapped -= phys_size;
			count -= length;
			cmrt_addr += length;
		}
	}
	/* The normal case. */
	if (!mem_write(mapped, buf, count)) {
		rv = -EIO;
		goto out;
	}
	*f_pos += count;
 out:
	return rv;
}

static unsigned int device_poll(struct file *filp, poll_table *wait)
{
	cmrt_proc_t *proc = filp->private_data;
	void __iomem *sio = mem_ptr(MEM_CONF_SYSCTL,
				    R_SYSCTL_SOC_INTERRUPT_OUT);
	uint32_t irqs = ioread32(sio);

	poll_wait(filp, &proc->waitq,  wait);
	if (proc->irq_mask & irqs) {
		/* Interrupt is available. */
		return POLLIN | POLLRDNORM;
	}
	return 0;
}

/* Translate CMRT address into physical address for mmap. */
static unsigned long find_phys(uint32_t cmrt_addr, size_t size)
{
	int i;

	for (i = 0; i < MEM_CONF_SIZE; i++) {
		cmrt_mem_conf_t *mc = &mem_conf[i];
		if (mc->mem == NULL) {
			continue;
		}
		if (cmrt_addr >= mc->conf[MPA_CMRT_BASE]) {
			size_t offset = cmrt_addr - mc->conf[MPA_CMRT_BASE];
			if (offset + size <= mc->conf[MPA_CMRT_SIZE]) {
				if (offset + size > mc->conf[MPA_PHYS_SIZE]) {
					/* Wrapping memory outsize phys. */
					return 0;
				}
				return mc->phys + offset;
			}
		}
	}
	return 0;
}

static int device_mmap(struct file *filp, struct vm_area_struct *vma)
{
	unsigned long size = vma->vm_end - vma->vm_start;
	unsigned long cmrt_addr = vma->vm_pgoff << PAGE_SHIFT;
	unsigned long phys_addr = find_phys(cmrt_addr, size);

	pr_info("%s: 0x%lx bytes for 0x%08lx from 0x%08lx to 0x%08lx\n",
		__func__, size, cmrt_addr, phys_addr, vma->vm_start);

	if (phys_addr == 0) {
		return -EINVAL;
	}

	vma->vm_page_prot = pgprot_noncached(vma->vm_page_prot);

	if (io_remap_pfn_range(vma, vma->vm_start, phys_addr >> PAGE_SHIFT,
			       size, vma->vm_page_prot)) {
		return -EAGAIN;
	}
	return 0;
}

static int device_open(struct inode *inode, struct file *filp)
{
	cmrt_proc_t *proc;

	pr_info("%s\n", __func__);

	if (imajor(inode) != CMRT_MAJORNO) {
		return -ENXIO;
	}
	proc = kzalloc(sizeof(*proc), GFP_KERNEL);
	if (proc == NULL) {
		return -ENOMEM;
	}
	init_waitqueue_head(&proc->waitq);
	proc->irq_mask = 0;

	mutex_lock(&cmrt_lock);
	hlist_add_head(&proc->proc_node, &cmrt_procs);
	mutex_unlock(&cmrt_lock);

	filp->private_data = proc;

	return 0;
}

static int device_release(struct inode *inode, struct file *filp)
{
	cmrt_proc_t *proc = filp->private_data;

	pr_info("%s\n", __func__);

	mutex_lock(&cmrt_lock);
	hlist_del(&proc->proc_node);
	mutex_unlock(&cmrt_lock);

	kfree(proc);

	return 0;
}

static const struct file_operations fops = {
	.owner          = THIS_MODULE,
	.read           = device_read,
	.write          = device_write,
	.poll           = device_poll,
	.mmap           = device_mmap,
	.open           = device_open,
	.release        = device_release,
};

/*
 * Interrupts coming from CMRT are not actually connected into real irq
 * lines on the ARM side in our FPGA setup. We have to use a thread to poll.
 */
static int cmrt_irq_thread(void *unused)
{
	void __iomem *sio = mem_ptr(MEM_CONF_SYSCTL,
				    R_SYSCTL_SOC_INTERRUPT_OUT);

	pr_info("%s: starting\n", __func__);

	while (!kthread_should_stop()) {
		uint32_t irqs;
		cmrt_proc_t *proc;
		cpu_relax();
		irqs = ioread32(sio);
		if (irqs != 0) {
			mutex_lock(&cmrt_lock);
			hlist_for_each_entry(proc, &cmrt_procs, proc_node) {
				/* Wake up processes waiting for irqs. */
				if (proc->irq_mask & irqs) {
					wake_up_interruptible(&proc->waitq);
				}
			}
			mutex_unlock(&cmrt_lock);
		}
		msleep_interruptible(10);
	}
	pr_info("%s: stopping\n", __func__);
	return 0;
}

/* Start thread to poll for interrupts. */
static int start_irq_thread(void)
{
	if (!irq_thread) {
		irq_thread = kthread_create(cmrt_irq_thread, NULL, "cmrt_irq_thread");
		if (IS_ERR(irq_thread)) {
			int ret = PTR_ERR(irq_thread);
			irq_thread = NULL;
			return ret;
		}
		wake_up_process(irq_thread);
	}
	return 0;
}

#define PCI_DEVICE_ID_XILINX_VCU108 0x8038
static struct pci_dev *pdev; /* non-null for PCI based FPGAs */

/* Reset the debug module interface and enable JTAG. */
static void start_fpga(void)
{
	void __iomem *dm_control = mem_ptr(MEM_CONF_DM, 0);
	void __iomem *sc_version = mem_ptr(MEM_CONF_SYSCTL, R_SYSCTL_VERSION);
	void __iomem *sc_control = mem_ptr(MEM_CONF_SYSCTL, R_SYSCTL_CONTROL);

	/* Reset is active low. */
	iowrite32(0x0, sc_control);
	iowrite32(0x0, dm_control);
	msleep_interruptible(10);
	mb();
	pr_info("%s: releasing CMRT from reset\n", __func__);
	iowrite32(CMRT_SYSCTL_RESET_MASK, sc_control);
	pr_info("%s: releasing DM from reset\n", __func__);
	iowrite32(0x1, dm_control);
	if (pdev) {
		/* Enable jtag when pdev exists. */
		void __iomem *fic_control = mem_ptr(MEM_CONF_FIC, 0);
		pr_info("%s: enable JTAG on VCU108\n", __func__);
		iowrite32(0x1, fic_control);
	}
	msleep_interruptible(10);
	pr_info("%s: SYSCTL version register = 0x%08x\n", __func__,
		ioread32(sc_version));
}

/* Get base and size of all FPGA physical memory. */
static unsigned long mem_region(unsigned long *size)
{
	int i;
	unsigned long start = -1;
	unsigned long end = 0;

	for (i = 0; i < MEM_CONF_SIZE; i++) {
		cmrt_mem_conf_t *mc = &mem_conf[i];
		if (mc->conf[MPA_CMRT_BASE] && mc->conf[MPA_PHYS_BASE]) {
			if (mc->conf[MPA_PHYS_BASE] < start) {
				start = mc->conf[MPA_PHYS_BASE];
			}
			if (mc->conf[MPA_PHYS_BASE] + mc->conf[MPA_PHYS_SIZE] > end) {
				end = mc->conf[MPA_PHYS_BASE] + mc->conf[MPA_PHYS_SIZE];
			}
		}
	}
	*size = end - start;
	return start;
}

/* Go through the memory config and unmap all used. */
static void unmap_mems(void)
{
	int i;

	for (i = 0; i < MEM_CONF_SIZE; i++) {
		cmrt_mem_conf_t *mc = &mem_conf[i];
		if (mc->mem) {
			if (mc->conf[MPA_BAR_NUM]) {
				/* Must unmap the BAR start address. */
				mc->mem -= mc->conf[MPA_BAR_OFFSET];
			}
			iounmap(mc->mem);
			mc->mem = NULL;
			mc->phys = 0;
		}
	}
}

/* Go through the memory config and map all configured. */
static bool map_mems(void)
{
	int i;

	for (i = 0; i < MEM_CONF_SIZE; i++) {
		cmrt_mem_conf_t *mc = &mem_conf[i];
		if (mc->conf[MPA_PHYS_BASE] && mc->conf[MPA_PHYS_SIZE]) {
			if (pdev) {
				mc->mem = pci_ioremap_bar(pdev, mc->conf[MPA_BAR_NUM]);
				if (mc->mem) {
					mc->mem += mc->conf[MPA_BAR_OFFSET];
					mc->phys = pci_resource_start(pdev, mc->conf[MPA_BAR_NUM]) + mc->conf[MPA_BAR_OFFSET];
				}
			} else {
				mc->mem = ioremap(mc->conf[MPA_PHYS_BASE], mc->conf[MPA_PHYS_SIZE]);
				if (mc->mem) {
					mc->phys = mc->conf[MPA_PHYS_BASE];
				}
			}
			if (!mc->mem) {
				pr_err("%s: unable to map %s\n",
				       __func__, mc->name);
				return false;
			}
			pr_info("%s: %s: 0x%lx - 0x%lx -> 0x%lx = 0x%p - 0x%lx\n", __func__, mc->name, mc->conf[MPA_CMRT_BASE], mc->conf[MPA_CMRT_SIZE], mc->conf[MPA_PHYS_BASE], mc->mem, mc->conf[MPA_PHYS_SIZE]);
			if (i == MEM_CONF_PUF) {
				/* Initialize PUF memory with random data. */
				get_random_bytes(mc->mem, mc->conf[MPA_PHYS_SIZE]);
			}
		}
	}
	return true;
}

#if LINUX_VERSION_CODE <= KERNEL_VERSION(4,9,0)
/* For now Linux kernel version determines the FPGA type (zynq706 or vmk180). */
#define FPGA_TYPE "zynq706"

#define DEVCFG_INT_STATUS_OFFSET 0xC
#define PCFG_DONE_INT (1 << 2)

/* Cannot start if bitfile is not programmed. */
static bool is_fpga_programmed(void)
{
	void __iomem *devcfg_status = mem_ptr(MEM_CONF_DEVCFG,
					      DEVCFG_INT_STATUS_OFFSET);
	if (ioread32(devcfg_status) & PCFG_DONE_INT) {
		pr_info("%s: yes\n", __func__);
		return true;
	}
	pr_info("%s: no\n", __func__);
	return false;
}
#else
#define FPGA_TYPE "vmk180"
static bool is_fpga_programmed(void)
{
	return true;
}
#endif

int init_module(void)
{
	int ret;

	pr_info("%s\n", __func__);

	ret = register_chrdev(CMRT_MAJORNO, DEVICE_NAME, &fops);
	if (ret != 0) {
		pr_err("%s: failed to register chrdev\n", __func__);
		return -EINVAL;
	}
	pdev = pci_get_device(PCI_VENDOR_ID_XILINX, PCI_DEVICE_ID_XILINX_VCU108, NULL);
	if (pdev) {
		pr_info("%s: Found VCU108 PCI device\n", __func__);
		if (pci_enable_device(pdev)) {
			pr_err("%s: cannot enable PCI device\n", __func__);
			ret = -ENXIO;
			goto out_err;
		}
		if (pci_request_regions(pdev, DEVICE_NAME)) {
			pr_err("%s: unable to request PCI regions\n", __func__);
			ret = -ENXIO;
			goto out_err;
		}
	} else {
		unsigned long size, base = mem_region(&size);
		pr_info("%s: " FPGA_TYPE " device base 0x%lx size 0x%lx\n",
			__func__, base, size);
		if (request_mem_region(base, size, DEVICE_NAME) == NULL) {
			pr_err("%s: unable to reserve memory\n", __func__);
			ret = -ENXIO;
			goto out_err;
		}
	}
	if (!map_mems()) {
		pr_err("%s: failed to initialize MMIO\n", __func__);
		ret = -ENXIO;
		goto out_err;
	}
	if (!is_fpga_programmed()) {
		pr_err("%s: FPGA is not programmed\n", __func__);
		ret = -EIO;
		goto out_err;
	}
	start_fpga();
	irq_thread = NULL;
	ret = start_irq_thread();
	if (ret != 0) {
		pr_err("%s: failed to start irq thread\n", __func__);
		ret = -EINVAL;
		goto out_err;
	}
	return 0;
out_err:
	cleanup_module();
	return ret;
}

void cleanup_module(void)
{
	pr_info("%s\n", __func__);

	if (irq_thread) {
		mutex_lock(&cmrt_lock);
		kthread_stop(irq_thread);
		mutex_unlock(&cmrt_lock);
		msleep_interruptible(20);
	}
	unmap_mems();
	if (pdev) {
		pci_release_regions(pdev);
		pci_disable_device(pdev);
		pci_dev_put(pdev);
	} else {
		unsigned long size, base = mem_region(&size);
		release_mem_region(base, size);
	}
	unregister_chrdev(CMRT_MAJORNO, DEVICE_NAME);
}
