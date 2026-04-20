/*
 * Copyright (c) 2017-2023 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

#define DT_DRV_COMPAT rambus_cmrt_mpu

#include <kernel.h>
#include <device.h>
#include <sys/sys_io.h>
#include <sys/byteorder.h>
#include <sys/__assert.h>
#include <linker/linker-defs.h>
#include <drivers/cmrt/sac.h>
#include <cmrt_mpu.h>
#include <string.h>
#include <assert.h>
#include <errno.h>
#include <assert.h>

#include <logging/log.h>
LOG_MODULE_DECLARE(cmrt, CONFIG_CMRT_LOG_LEVEL);

#define R_BASE DT_INST_REG_ADDR(0)
static_assert(R_BASE == CMRT_MPU_BASE); /* device tree must match headers */
static_assert(CONFIG_CMRT_MPU_NUM_REGIONS <= NR_OF_MPRRS);

static int first_user; /* index of first user region */
static int first_free; /* index of first free region */

uint32_t cmrt_mpu_read_region(int index)
{
	if (index >= 0 && index < CONFIG_CMRT_MPU_NUM_REGIONS) {
		uint32_t offset = index << 2;
		return sys_read32((mm_reg_t)(R_BASE + R_MPRR0 + offset));
	}
	return 0;
}

void cmrt_mpu_write_region(int index, uint32_t region)
{
	if (index >= 0 && index < CONFIG_CMRT_MPU_NUM_REGIONS) {
		uint32_t offset = index << 2;
		if (index >= first_free && region != 0) {
			first_free = index + 1;
		}
		if (index < first_free && region == 0) {
			first_free = index;
		}
		return sys_write32(region, (mm_reg_t)(R_BASE + R_MPRR0 + offset));
	}
}

void cmrt_mpu_read_regions(int index, uint32_t *regions)
{
	for (int i = 0; index < CONFIG_CMRT_MPU_NUM_REGIONS; i++) {
		regions[i] = (index >= 0 && index < CONFIG_CMRT_MPU_NUM_REGIONS) ?
			cmrt_mpu_read_region(index++) : 0;
	}
}

void cmrt_mpu_write_regions(int index, const uint32_t *regions)
{
	first_free = index;
	for (int i = 0; index < CONFIG_CMRT_MPU_NUM_REGIONS; i++) {
		uint32_t region = (regions != NULL) ? regions[i] : 0;
		if ((region & MPU_LOCKED) == MPU_LOCKED) {
			index++;
			continue;
		}
		cmrt_mpu_write_region(index++, region);
	}
}

int cmrt_mpu_first_user(void)
{
	return first_user;
}

int cmrt_mpu_first_free(void)
{
	return first_free;
}

#define ROM_BASE DT_REG_ADDR(DT_CHOSEN(zephyr_flash))
#define ROM_SIZE DT_REG_SIZE(DT_CHOSEN(zephyr_flash))
#define RAM_BASE CONFIG_SRAM_BASE_ADDRESS
#define RAM_SIZE KB(CONFIG_SRAM_SIZE)

bool cmrt_mpu_has_access(uint32_t address, uint32_t size, uint32_t privilege, uint32_t bits)
{
	if (size == 0) {
		return true;
	}
	if (address < (uint32_t)ROM_BASE ||
	    address + size < address ||
	    address + size > (uint32_t)RAM_BASE + (uint32_t)RAM_SIZE) {
		return false;
	}
	if (((privilege & ~MPU_PRIVILEGE_MASK) != 0u) ||
	    ((bits & ~MPU_BITS_MASK) != 0u)) {
		return false;
	}
	uint32_t high, low = 0;
	int index = (privilege == MPU_PRIVILEGE_U) ? first_user : 0;
	for (; index < first_free; index++) {
		uint32_t offset = index << 2;
		uint32_t region = sys_read32((mm_reg_t)(R_BASE + R_MPRR0 + offset));
		high = CMRT_MPU_ADDRESS(region);
		if ((region & MPU_RESERVED) == 0u &&
		    (privilege == CMRT_MPU_PRIVILEGE(region)) &&
		    (region != 0u)) {
			/*
			 * We were able to read the region,
			 * region privilege equals given privilege,
			 * and the region wasn't completely unused.
			 */
			if ((address >= low) &&
			    (address + size <= high) &&
			    ((bits & CMRT_MPU_BITS(region)) == bits)) {
				return true;
			}
		}
		low = high;
	}
	return false;
}

#define MPU_REGION_DEFAULTS_ROM \
	(((((uint32_t)ROM_BASE + (uint32_t)ROM_SIZE) >> 2) &	\
	  MPU_ADDRESS_MASK) |					\
	 MPU_MODE_READABLE | MPU_MODE_EXECUTABLE |		\
	 MPU_START_OF_RANGE)

#define MPU_REGION_DEFAULTS_GAP \
	(((uint32_t)RAM_BASE >> 2) & MPU_ADDRESS_MASK)

#define MPU_REGION_DEFAULTS_SRAM \
	(((((uint32_t)RAM_BASE + (uint32_t)RAM_SIZE) >> 2) &		\
	  MPU_ADDRESS_MASK) |						\
	 MPU_MODE_WRITABLE | MPU_MODE_READABLE | MPU_MODE_EXECUTABLE)

void cmrt_mpu_init_early(void)
{
	/*
	 * Set regions for M, S and U to allow everything for testing.
	 * Instead of using the API, we use direct register writes here in
	 * order to not require a stack setup from the caller.
	 */
	sys_write32(MPU_REGION_DEFAULTS_ROM | MPU_PRIVILEGE_M | MPU_LOCKED,
		    (mm_reg_t)(R_BASE + R_MPRR0 + (0UL << 2)));
	sys_write32(MPU_REGION_DEFAULTS_GAP | MPU_PRIVILEGE_M | MPU_LOCKED,
		    (mm_reg_t)(R_BASE + R_MPRR0 + (1UL << 2)));
	sys_write32(MPU_REGION_DEFAULTS_SRAM | MPU_PRIVILEGE_M | MPU_LOCKED,
		    (mm_reg_t)(R_BASE + R_MPRR0 + (2UL << 2)));
	sys_write32(MPU_REGION_DEFAULTS_ROM | MPU_PRIVILEGE_S | MPU_LOCKED,
		    (mm_reg_t)(R_BASE + R_MPRR0 + (3UL << 2)));
	sys_write32(MPU_REGION_DEFAULTS_GAP | MPU_PRIVILEGE_S | MPU_LOCKED,
		    (mm_reg_t)(R_BASE + R_MPRR0 + (4UL << 2)));
	sys_write32(MPU_REGION_DEFAULTS_SRAM | MPU_PRIVILEGE_S | MPU_LOCKED,
		    (mm_reg_t)(R_BASE + R_MPRR0 + (5UL << 2)));
	/*
	 * This user mode setup is intended for stand-alone testing of
	 * Zephyr userspace samples with CONFIG_SUPERVISOR_MODE=y.
	 * By default user mode has no access anywhere, the rules are
	 * set for each thread in z_riscv_user_mode_enter_syscall.
	 */
	sys_write32(cmrt_mpu_encode_region((uint32_t)(uintptr_t)__text_region_start,
					   MPU_PRIVILEGE_U,
					   MPU_START_OF_RANGE | MPU_LOCKED),
		    (mm_reg_t)(R_BASE + R_MPRR0 + (6UL << 2)));
	sys_write32(cmrt_mpu_encode_region((uint32_t)(RAM_BASE + RAM_SIZE),
					   MPU_PRIVILEGE_U,
					   0),
		    (mm_reg_t)(R_BASE + R_MPRR0 + (7UL << 2)));
}

static int cmrt_mpu_init(const struct device *dev)
{
	ARG_UNUSED(dev);

	/* Scan the regions backwards to setup first_user and first_free. */
	for (int index = CONFIG_CMRT_MPU_NUM_REGIONS - 1; index >= 0; index--) {
		uint32_t region = cmrt_mpu_read_region(index);
		if (region != 0) {
			if (first_free == 0) {
				first_free = index + 1;
			}
			if (CMRT_MPU_PRIVILEGE(region) == MPU_PRIVILEGE_U) {
				first_user = index;
			}
		}
	}
	return 0;
}

SYS_INIT(cmrt_mpu_init, PRE_KERNEL_1, CONFIG_KERNEL_INIT_PRIORITY_OBJECTS);

#ifdef CONFIG_USERSPACE
extern ulong_t is_user_mode; /* MCU state */

static void cmrt_mpu_add_dynamic(uint32_t *regions, uint32_t address, uint32_t size, uint32_t bits)
{
	uint32_t new_regions[CONFIG_CMRT_MPU_NUM_REGIONS] = { 0 };

	/* Add new user region to the correct place. */
	uint32_t high, low = 0;
	for (int index = 0, new_index = 0; index < CONFIG_CMRT_MPU_NUM_REGIONS; index++) {
		uint32_t region = regions[index];
		if (region == 0) {
			break;
		}
		high = CMRT_MPU_ADDRESS(region);
		__ASSERT(!((address <= low) && (address + size >= high)),
			 "dynamic region cannot overwrite existing region");
		if ((address >= low) && (address + size <= high)) {
			__ASSERT((region & MPU_LOCKED) == 0, "locked MPU region");
			__ASSERT(new_index < CONFIG_CMRT_MPU_NUM_REGIONS - 2, "too many regions");
			new_regions[new_index++] = cmrt_mpu_encode_region(address, MPU_PRIVILEGE_U, CMRT_MPU_BITS(region));
			new_regions[new_index++] = cmrt_mpu_encode_region(address + size, MPU_PRIVILEGE_U, bits);
		}
		new_regions[new_index++] = region;
		low = high;
	}
	memcpy(regions, new_regions, sizeof(new_regions));
}

static void cmrt_mpu_remove_dynamic(uint32_t *regions, uint32_t address, uint32_t size, uint32_t bits)
{
	uint32_t new_regions[CONFIG_CMRT_MPU_NUM_REGIONS] = { 0 };

	/* Remove the region with exact match. */
	uint32_t high, low = 0;
	for (int index = 0, new_index = 0; index < CONFIG_CMRT_MPU_NUM_REGIONS; index++) {
		uint32_t region = regions[index];
		if (region == 0) {
			break;
		}
		high = CMRT_MPU_ADDRESS(region);
		if ((address == low) && (address + size == high)) {
			__ASSERT((region & MPU_LOCKED) == 0, "locked MPU region");
			__ASSERT(new_index >= 1, "too few regions");
			new_regions[new_index--] = 0;
			new_regions[new_index] = 0;
		} else {
			new_regions[new_index++] = region;
		}
		low = high;
	}
	memcpy(regions, new_regions, sizeof(new_regions));
}

static struct k_thread *last_user;

void z_riscv_init_user_accesses(struct k_thread *thread)
{
	if ((thread->base.user_options & K_CONTAINER) == 0) {
		/* Add MCU state for user threads but not for containers. */
		cmrt_mpu_add_dynamic(thread->arch.u_regions, (uint32_t)(uintptr_t)&is_user_mode, sizeof(is_user_mode), MPU_MODE_READABLE);
	}
	/* Add thread user mode stack. */
	cmrt_mpu_add_dynamic(thread->arch.u_regions, (uint32_t)thread->stack_info.start, thread->stack_info.size, MPU_MODE_READABLE | MPU_MODE_WRITABLE);
	/* Clear last user thread pointer if context is reused. */
	if (last_user == thread) {
		last_user = NULL;
	}
}

void z_riscv_configure_user_allowed_stack(struct k_thread *thread)
{
	/* Only set the MPU rules if user thread changes. */
	if (last_user != thread) {
		cmrt_mpu_write_regions(cmrt_mpu_first_user(), thread->arch.u_regions);
		last_user = thread;
	}
}

int arch_buffer_validate(void *addr, size_t size, int write)
{
	if (IS_SAC_SPACE(addr, size)) {
		return cmrt_sac_has_access(NULL, cmrt_sac_translate((uintptr_t)addr), size, !!write) ? 0 : 1;
	}
	uint32_t bits = MPU_MODE_READABLE;
	if (write) {
		bits |= MPU_MODE_WRITABLE;
	}
	return cmrt_mpu_has_access((uint32_t)(uintptr_t)addr, (uint32_t)size,
				   MPU_PRIVILEGE_U, bits) ? 0 : 1;
}

static inline uint32_t attr2bits(unsigned char attr)
{
	uint32_t bits = 0;
	if (attr & PMP_R) {
		bits |= MPU_MODE_READABLE;
	}
	if (attr & PMP_W) {
		bits |= MPU_MODE_WRITABLE;
	}
	if (attr & PMP_X) {
		bits |= MPU_MODE_EXECUTABLE;
	}
	return bits;
}

void arch_mem_domain_thread_add(struct k_thread *thread)
{
	for (int i = 0, pcount = 0; pcount < thread->mem_domain_info.mem_domain->num_partitions; i++) {
		struct k_mem_partition *partition = &thread->mem_domain_info.mem_domain->partitions[i];
		if (partition->size == 0) {
			continue;
		}
		pcount++;

		cmrt_mpu_add_dynamic(thread->arch.u_regions,
				     (uint32_t)partition->start,
				     (uint32_t)partition->size,
				     attr2bits(partition->attr.pmp_attr));
	}
}

void arch_mem_domain_thread_remove(struct k_thread *thread)
{
	for (int i = 0, pcount = 0; pcount < thread->mem_domain_info.mem_domain->num_partitions; i++) {
		struct k_mem_partition *partition = &thread->mem_domain_info.mem_domain->partitions[i];
		if (partition->size == 0) {
			continue;
		}
		pcount++;

		cmrt_mpu_remove_dynamic(thread->arch.u_regions,
					(uint32_t)partition->start,
					(uint32_t)partition->size,
					attr2bits(partition->attr.pmp_attr));
	}
}

int arch_mem_domain_max_partitions_get(void)
{
	/* New partition requires two new MPU regions always. */
	return (CONFIG_CMRT_MPU_NUM_REGIONS - cmrt_mpu_first_free()) / 2;
}

void arch_mem_domain_partition_add(struct k_mem_domain *domain,
				   uint32_t partition_id)
{
	sys_dnode_t *node, *next_node;
	struct k_mem_partition *partition = &domain->partitions[partition_id];
	SYS_DLIST_FOR_EACH_NODE_SAFE(&domain->mem_domain_q, node, next_node) {
		struct k_thread *thread = CONTAINER_OF(node, struct k_thread, mem_domain_info);

		cmrt_mpu_add_dynamic(thread->arch.u_regions,
				     (uint32_t)partition->start,
				     (uint32_t)partition->size,
				     attr2bits(partition->attr.pmp_attr));
	}
}

void arch_mem_domain_partition_remove(struct k_mem_domain *domain,
				      uint32_t  partition_id)
{
	sys_dnode_t *node, *next_node;
	struct k_mem_partition *partition = &domain->partitions[partition_id];
	SYS_DLIST_FOR_EACH_NODE_SAFE(&domain->mem_domain_q, node, next_node) {
		struct k_thread *thread = CONTAINER_OF(node, struct k_thread, mem_domain_info);

		cmrt_mpu_remove_dynamic(thread->arch.u_regions,
					(uint32_t)partition->start,
					(uint32_t)partition->size,
					attr2bits(partition->attr.pmp_attr));
	}
}

extern char __cmrt_text_start[];
extern char __cmrt_text_end[];
extern char __cmrt_rodata_start[];
extern char __cmrt_rodata_end[];

#include <drivers/cmrt/fboot.h>

static void got_offsets(uint32_t *pstart, uint32_t *pend, const cmrt_raw_footer_t *raw)
{
	/* Add relocation offset to each got word. */
	while (pend > pstart) {
		uint32_t org = *pstart;
		*pstart += raw->relocation_offset;
		LOG_INF("Relocating at %p: 0x%x -> 0x%x", pstart, org, *pstart);
		pstart++;
	}
}

static void relo_offsets(uint32_t *pstart, uint32_t *pend, const cmrt_raw_footer_t *raw)
{
	/* Add relocation offset to each image offset. */
	uint32_t max_offset = raw->data_end - raw->text_start;
	while (pend > pstart) {
		uint32_t offset = *pstart; /* offset within image */
		if (offset < max_offset) {
			/* Add relocation offset to the place in the image. */
			uint32_t *p = (uint32_t *)(offset + raw->text_start);
			uint32_t org = *p;
			*p += raw->relocation_offset;
			LOG_INF("Relocating at %p: 0x%x -> 0x%x", p, org, *p);
		}
		pstart++;
	}
}

static int z_riscv_pmp_user_rules(struct k_thread *thread, int i)
{
	if ((thread->base.user_options & K_CONTAINER) == 0) {
		/* <R-X> for Supervisor text. */
		thread->arch.u_regions[i++] = cmrt_mpu_encode_region((uint32_t)(uintptr_t)__cmrt_text_end, MPU_PRIVILEGE_U, MPU_MODE_READABLE | MPU_MODE_EXECUTABLE);
		/* <---> up to the start of Supervisor rodata. */
		thread->arch.u_regions[i++] = cmrt_mpu_encode_region((uint32_t)(uintptr_t)__cmrt_rodata_start, MPU_PRIVILEGE_U, 0);
		/* <R--> for Supervisor rodata. */
		thread->arch.u_regions[i++] = cmrt_mpu_encode_region((uint32_t)(uintptr_t)__cmrt_rodata_end, MPU_PRIVILEGE_U, MPU_MODE_READABLE);
	} else {
		/* Check for CMRT image header. */
		struct __esf *stack_init = (struct __esf *)(uintptr_t)thread->callee_saved.sp;
		cmrt_img_header_t *hdr = (cmrt_img_header_t *)stack_init->a0;
		if (cmrt_is_valid_hdr(hdr, KB(CONFIG_SRAM_SIZE))) {
			/* Possibly, try loading the image. */
			cmrt_raw_footer_t raw;
			cmrt_usr_footer_t usr;
			int res = fboot_load_image(hdr + 1, hdr->length, &raw, &usr);
			if (res < 0) {
				/* Failed to load. */
				thread->base.thread_state = _THREAD_DEAD;
				return i;
			}
			/* Relocation of .got. The first 3 slots are dummy. */
			got_offsets((uint32_t *)(uintptr_t)usr.got_start + 3, (uint32_t *)(uintptr_t)usr.got_end, &raw);
			/* Relocation offsets are prepended in the footer. */
			relo_offsets((uint32_t *)(uintptr_t)usr.relo_start, (uint32_t *)(uintptr_t)usr.relo_end, &raw);
			/* <---> up to the start of User text. */
			thread->arch.u_regions[i++] = cmrt_mpu_encode_region(raw.text_start, MPU_PRIVILEGE_U, 0);
			/* <R-X> for User text. */
			thread->arch.u_regions[i++] = cmrt_mpu_encode_region(raw.text_end, MPU_PRIVILEGE_U, MPU_MODE_READABLE | MPU_MODE_EXECUTABLE);
			/* <R--> for User rodata. */
			if (raw.rodata_end > raw.text_end) {
				thread->arch.u_regions[i++] = cmrt_mpu_encode_region(raw.rodata_end, MPU_PRIVILEGE_U, MPU_MODE_READABLE);
			}
			/* <RW-> for User bss, noinit and data. */
			if (raw.data_end > raw.rodata_end) {
				thread->arch.u_regions[i++] = cmrt_mpu_encode_region(raw.data_end, MPU_PRIVILEGE_U, MPU_MODE_READABLE | MPU_MODE_WRITABLE);
			}
			/* Change the thread entry in initial stack frame. */
			stack_init->a0 = (ulong_t)raw.entry_point;
			/* Change global pointer for the thread context. */
			thread->arch.user_gp = usr.global_pointer;
		}
	}
	return i;
}

void z_riscv_pmp_init_thread(struct k_thread *thread)
{
	/* Basic user rules for all threads. */
	int i = 0;
	/* <---> Before supervisor text. */
	thread->arch.u_regions[i++] = cmrt_mpu_encode_region((uint32_t)(uintptr_t)__text_region_start, MPU_PRIVILEGE_U, MPU_START_OF_RANGE | MPU_LOCKED);
	if ((thread->base.user_options & K_USER) != 0) {
		/* User mode thread, add specific user rules. */
		i = z_riscv_pmp_user_rules(thread, i);
	}
	/* <---> Rest of SRAM is not accessible by default. */
	thread->arch.u_regions[i++] = cmrt_mpu_encode_region(CONFIG_SRAM_BASE_ADDRESS + KB(CONFIG_SRAM_SIZE), MPU_PRIVILEGE_U, 0);
	/* Clear the rest of the rules. */
	while (i < CONFIG_CMRT_MPU_NUM_REGIONS) {
		thread->arch.u_regions[i++] = 0;
	}
}
#endif
