/*
<<<<<<< HEAD
 * Copyright (c) 2017-2023, Arm Limited and Contributors. All rights reserved.
=======
 * Copyright (c) 2017-2025, Arm Limited and Contributors. All rights reserved.
>>>>>>> upstream_import/upstream_v2_14_1
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <assert.h>
#include <cdefs.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>

#include <arch.h>
#include <arch_features.h>
#include <arch_helpers.h>
#include <common/debug.h>
#include <lib/el3_runtime/pubsub_events.h>
#include <lib/extensions/amu.h>
#include <lib/per_cpu/per_cpu.h>
#include <lib/utils_def.h>
#include <platform_def.h>

PER_CPU_DEFINE(amu_regs_t, amu_ctx);

<<<<<<< HEAD
#if ENABLE_AMU_FCONF
#	include <lib/fconf/fconf.h>
#	include <lib/fconf/fconf_amu_getter.h>
#endif

#if ENABLE_MPMM
#	include <lib/mpmm/mpmm.h>
#endif

struct amu_ctx {
	uint64_t group0_cnts[AMU_GROUP0_MAX_COUNTERS];
#if ENABLE_AMU_AUXILIARY_COUNTERS
	uint64_t group1_cnts[AMU_GROUP1_MAX_COUNTERS];
#endif

	/* Architected event counter 1 does not have an offset register */
	uint64_t group0_voffsets[AMU_GROUP0_MAX_COUNTERS - 1U];
#if ENABLE_AMU_AUXILIARY_COUNTERS
	uint64_t group1_voffsets[AMU_GROUP1_MAX_COUNTERS];
#endif

	uint16_t group0_enable;
#if ENABLE_AMU_AUXILIARY_COUNTERS
	uint16_t group1_enable;
#endif
};

static struct amu_ctx amu_ctxs_[PLATFORM_CORE_COUNT];

CASSERT((sizeof(amu_ctxs_[0].group0_enable) * CHAR_BIT) <= AMU_GROUP0_MAX_COUNTERS,
	amu_ctx_group0_enable_cannot_represent_all_group0_counters);

#if ENABLE_AMU_AUXILIARY_COUNTERS
CASSERT((sizeof(amu_ctxs_[0].group1_enable) * CHAR_BIT) <= AMU_GROUP1_MAX_COUNTERS,
	amu_ctx_group1_enable_cannot_represent_all_group1_counters);
#endif

static inline __unused uint64_t read_hcr_el2_amvoffen(void)
{
	return (read_hcr_el2() & HCR_AMVOFFEN_BIT) >>
		HCR_AMVOFFEN_SHIFT;
}

static inline __unused void write_cptr_el2_tam(uint64_t value)
{
	write_cptr_el2((read_cptr_el2() & ~CPTR_EL2_TAM_BIT) |
		((value << CPTR_EL2_TAM_SHIFT) & CPTR_EL2_TAM_BIT));
}

static inline __unused void ctx_write_scr_el3_amvoffen(cpu_context_t *ctx, uint64_t amvoffen)
{
	uint64_t value = read_ctx_reg(get_el3state_ctx(ctx), CTX_SCR_EL3);

	value &= ~SCR_AMVOFFEN_BIT;
	value |= (amvoffen << SCR_AMVOFFEN_SHIFT) & SCR_AMVOFFEN_BIT;

	write_ctx_reg(get_el3state_ctx(ctx), CTX_SCR_EL3, value);
}

static inline __unused void write_hcr_el2_amvoffen(uint64_t value)
{
	write_hcr_el2((read_hcr_el2() & ~HCR_AMVOFFEN_BIT) |
		((value << HCR_AMVOFFEN_SHIFT) & HCR_AMVOFFEN_BIT));
}

static inline __unused void write_amcr_el0_cg1rz(uint64_t value)
{
	write_amcr_el0((read_amcr_el0() & ~AMCR_CG1RZ_BIT) |
		((value << AMCR_CG1RZ_SHIFT) & AMCR_CG1RZ_BIT));
}

static inline __unused uint64_t read_amcfgr_el0_ncg(void)
{
	return (read_amcfgr_el0() >> AMCFGR_EL0_NCG_SHIFT) &
		AMCFGR_EL0_NCG_MASK;
}

static inline __unused uint64_t read_amcgcr_el0_cg0nc(void)
{
	return (read_amcgcr_el0() >> AMCGCR_EL0_CG0NC_SHIFT) &
		AMCGCR_EL0_CG0NC_MASK;
}

static inline __unused uint64_t read_amcg1idr_el0_voff(void)
{
	return (read_amcg1idr_el0() >> AMCG1IDR_VOFF_SHIFT) &
		AMCG1IDR_VOFF_MASK;
}

static inline __unused uint64_t read_amcgcr_el0_cg1nc(void)
=======
static inline uint8_t read_amcgcr_el0_cg1nc(void)
>>>>>>> upstream_import/upstream_v2_14_1
{
	return (read_amcgcr_el0() >> AMCGCR_EL0_CG1NC_SHIFT) &
		AMCGCR_EL0_CG1NC_MASK;
}

void amu_enable(cpu_context_t *ctx)
{
<<<<<<< HEAD
	return (read_amcntenset0_el0() >> AMCNTENSET0_EL0_Pn_SHIFT) &
		AMCNTENSET0_EL0_Pn_MASK;
}

static inline __unused uint64_t read_amcntenset1_el0_px(void)
{
	return (read_amcntenset1_el0() >> AMCNTENSET1_EL0_Pn_SHIFT) &
		AMCNTENSET1_EL0_Pn_MASK;
}

static inline __unused void write_amcntenset0_el0_px(uint64_t px)
{
	uint64_t value = read_amcntenset0_el0();

	value &= ~AMCNTENSET0_EL0_Pn_MASK;
	value |= (px << AMCNTENSET0_EL0_Pn_SHIFT) & AMCNTENSET0_EL0_Pn_MASK;

	write_amcntenset0_el0(value);
}

static inline __unused void write_amcntenset1_el0_px(uint64_t px)
{
	uint64_t value = read_amcntenset1_el0();

	value &= ~AMCNTENSET1_EL0_Pn_MASK;
	value |= (px << AMCNTENSET1_EL0_Pn_SHIFT) & AMCNTENSET1_EL0_Pn_MASK;

	write_amcntenset1_el0(value);
}

static inline __unused void write_amcntenclr0_el0_px(uint64_t px)
{
	uint64_t value = read_amcntenclr0_el0();

	value &= ~AMCNTENCLR0_EL0_Pn_MASK;
	value |= (px << AMCNTENCLR0_EL0_Pn_SHIFT) & AMCNTENCLR0_EL0_Pn_MASK;

	write_amcntenclr0_el0(value);
}

static inline __unused void write_amcntenclr1_el0_px(uint64_t px)
{
	uint64_t value = read_amcntenclr1_el0();

	value &= ~AMCNTENCLR1_EL0_Pn_MASK;
	value |= (px << AMCNTENCLR1_EL0_Pn_SHIFT) & AMCNTENCLR1_EL0_Pn_MASK;

	write_amcntenclr1_el0(value);
}

#if ENABLE_AMU_AUXILIARY_COUNTERS
static __unused bool amu_group1_supported(void)
{
	return read_amcfgr_el0_ncg() > 0U;
}
#endif

/*
 * Enable counters. This function is meant to be invoked by the context
 * management library before exiting from EL3.
 */
void amu_enable(cpu_context_t *ctx)
{
	/* Initialize FEAT_AMUv1p1 features if present. */
	if (is_feat_amuv1p1_supported()) {
		/*
		 * Set SCR_EL3.AMVOFFEN to one so that accesses to virtual
		 * offset registers at EL2 do not trap to EL3
		 */
		ctx_write_scr_el3_amvoffen(ctx, 1U);
	}
}

void amu_enable_per_world(per_world_context_t *per_world_ctx)
{
	/*
	 * Set CPTR_EL3.TAM to zero so that any accesses to the Activity Monitor
	 * registers do not trap to EL3.
	 */
	uint64_t cptr_el3 = per_world_ctx->ctx_cptr_el3;

	cptr_el3 &= ~TAM_BIT;
	per_world_ctx->ctx_cptr_el3 = cptr_el3;
}

void amu_init_el3(void)
{
	uint64_t group0_impl_ctr = read_amcgcr_el0_cg0nc();
	uint64_t group0_en_mask = (1 << (group0_impl_ctr)) - 1U;
	uint64_t num_ctr_groups = read_amcfgr_el0_ncg();

	/* Enable all architected counters by default */
	write_amcntenset0_el0_px(group0_en_mask);

#if ENABLE_AMU_AUXILIARY_COUNTERS
	if (num_ctr_groups > 0U) {
		uint64_t amcntenset1_el0_px = 0x0; /* Group 1 enable mask */
		const struct amu_topology *topology;

		/*
		 * The platform may opt to enable specific auxiliary counters.
		 * This can be done via the common FCONF getter, or via the
		 * platform-implemented function.
		 */
#if ENABLE_AMU_FCONF
		topology = FCONF_GET_PROPERTY(amu, config, topology);
#else
		topology = plat_amu_topology();
#endif /* ENABLE_AMU_FCONF */

		if (topology != NULL) {
			unsigned int core_pos = plat_my_core_pos();

			amcntenset1_el0_px = topology->cores[core_pos].enable;
		} else {
			ERROR("AMU: failed to generate AMU topology\n");
		}

		write_amcntenset1_el0_px(amcntenset1_el0_px);
	}
#else /* ENABLE_AMU_AUXILIARY_COUNTERS */
	if (num_ctr_groups > 0U) {
		VERBOSE("AMU: auxiliary counters detected but support is disabled\n");
	}
#endif /* ENABLE_AMU_AUXILIARY_COUNTERS */

	if (is_feat_amuv1p1_supported()) {
=======
	/* Initialize FEAT_AMUv1p1 features if present. */
	if (is_feat_amuv1p1_supported()) {
		el3_state_t *state = get_el3state_ctx(ctx);
		u_register_t reg;

		/*
		 * Set SCR_EL3.AMVOFFEN to one so that accesses to virtual
		 * offset registers at EL2 do not trap to EL3
		 */
		reg = read_ctx_reg(state, CTX_SCR_EL3);
		reg |= SCR_AMVOFFEN_BIT;
		write_ctx_reg(state, CTX_SCR_EL3, reg);
	}
}

void amu_enable_per_world(per_world_context_t *per_world_ctx)
{
	/*
	 * Set CPTR_EL3.TAM to zero so that any accesses to the Activity Monitor
	 * registers do not trap to EL3.
	 */
	uint64_t cptr_el3 = per_world_ctx->ctx_cptr_el3;

	cptr_el3 &= ~TAM_BIT;
	per_world_ctx->ctx_cptr_el3 = cptr_el3;
}

void amu_init_el3(unsigned int core_pos)
{
	/* architecture is currently pinned to 4 */
	assert((read_amcgcr_el0() & AMCGCR_EL0_CG0NC_MASK) == CTX_AMU_GRP0_ALL);

	/* Enable all architected counters by default */
	write_amcntenset0_el0(AMCNTENSET0_EL0_Pn_MASK);
	if (is_feat_amu_aux_supported()) {
		/* something went wrong if we're trying to write higher bits */
		assert((get_amu_aux_enables(core_pos) & ~AMCNTENSET1_EL0_Pn_MASK) == 0);
		write_amcntenset1_el0(get_amu_aux_enables(core_pos));
	}

	if (is_feat_amuv1p1_supported()) {
>>>>>>> upstream_import/upstream_v2_14_1
#if AMU_RESTRICT_COUNTERS
		/*
		 * FEAT_AMUv1p1 adds a register field to restrict access to
		 * group 1 counters at all but the highest implemented EL. This
		 * is controlled with the `AMU_RESTRICT_COUNTERS` compile time
		 * flag, when set, system register reads at lower ELs return
		 * zero. Reads from the memory mapped view are unaffected.
		 */
		VERBOSE("AMU group 1 counter access restricted.\n");
		write_amcr_el0(AMCR_CG1RZ_BIT);
#else
		/* HDBG = 0 in both cases */
		write_amcr_el0(0);
#endif
	}
}

void amu_init_el2_unused(void)
<<<<<<< HEAD
{
	/*
	 * CPTR_EL2.TAM: Set to zero so any accesses to the Activity Monitor
	 *  registers do not trap to EL2.
	 */
	write_cptr_el2_tam(0U);

	/* Initialize FEAT_AMUv1p1 features if present. */
	if (is_feat_amuv1p1_supported()) {
		/* Make sure virtual offsets are disabled if EL2 not used. */
		write_hcr_el2_amvoffen(0U);
	}
}

/* Read the group 0 counter identified by the given `idx`. */
static uint64_t amu_group0_cnt_read(unsigned int idx)
=======
>>>>>>> upstream_import/upstream_v2_14_1
{
	/*
	 * CPTR_EL2.TAM: Set to zero so any accesses to the Activity Monitor
	 *  registers do not trap to EL2.
	 */
	write_cptr_el2(read_cptr_el2() & ~CPTR_EL2_TAM_BIT);

	if (is_feat_amuv1p1_supported()) {
		/* Make sure virtual offsets are disabled */
		write_hcr_el2(read_hcr_el2() & ~HCR_AMVOFFEN_BIT);
	}
}

static void *amu_context_save(const void *arg)
{
	if (!is_feat_amu_supported()) {
		return (void *)0;
	}

	unsigned int core_pos = *(unsigned int *)arg;
	amu_regs_t *ctx = PER_CPU_CUR(amu_ctx);

	/* disable all counters so we can write them safely later */
	write_amcntenclr0_el0(AMCNTENCLR0_EL0_Pn_MASK);
	if (is_feat_amu_aux_supported()) {
		write_amcntenclr1_el0(get_amu_aux_enables(core_pos));
	}

	isb();

	write_amu_grp0_ctx_reg(ctx, 0, read_amevcntr00_el0());
	write_amu_grp0_ctx_reg(ctx, 1, read_amevcntr01_el0());
	write_amu_grp0_ctx_reg(ctx, 2, read_amevcntr02_el0());
	write_amu_grp0_ctx_reg(ctx, 3, read_amevcntr03_el0());

	if (is_feat_amu_aux_supported()) {
		uint8_t num_counters = read_amcgcr_el0_cg1nc();

		switch (num_counters) {
		case 0x10:
			write_amu_grp1_ctx_reg(ctx, 0xf, read_amevcntr1f_el0());
			__fallthrough;
		case 0x0f:
			write_amu_grp1_ctx_reg(ctx, 0xe, read_amevcntr1e_el0());
			__fallthrough;
		case 0x0e:
			write_amu_grp1_ctx_reg(ctx, 0xd, read_amevcntr1d_el0());
			__fallthrough;
		case 0x0d:
			write_amu_grp1_ctx_reg(ctx, 0xc, read_amevcntr1c_el0());
			__fallthrough;
		case 0x0c:
			write_amu_grp1_ctx_reg(ctx, 0xb, read_amevcntr1b_el0());
			__fallthrough;
		case 0x0b:
			write_amu_grp1_ctx_reg(ctx, 0xa, read_amevcntr1a_el0());
			__fallthrough;
		case 0x0a:
			write_amu_grp1_ctx_reg(ctx, 0x9, read_amevcntr19_el0());
			__fallthrough;
		case 0x09:
			write_amu_grp1_ctx_reg(ctx, 0x8, read_amevcntr18_el0());
			__fallthrough;
		case 0x08:
			write_amu_grp1_ctx_reg(ctx, 0x7, read_amevcntr17_el0());
			__fallthrough;
		case 0x07:
			write_amu_grp1_ctx_reg(ctx, 0x6, read_amevcntr16_el0());
			__fallthrough;
		case 0x06:
			write_amu_grp1_ctx_reg(ctx, 0x5, read_amevcntr15_el0());
			__fallthrough;
		case 0x05:
			write_amu_grp1_ctx_reg(ctx, 0x4, read_amevcntr14_el0());
			__fallthrough;
		case 0x04:
			write_amu_grp1_ctx_reg(ctx, 0x3, read_amevcntr13_el0());
			__fallthrough;
		case 0x03:
			write_amu_grp1_ctx_reg(ctx, 0x2, read_amevcntr12_el0());
			__fallthrough;
		case 0x02:
			write_amu_grp1_ctx_reg(ctx, 0x1, read_amevcntr11_el0());
			__fallthrough;
		case 0x01:
			write_amu_grp1_ctx_reg(ctx, 0x0, read_amevcntr10_el0());
			__fallthrough;
		case 0x00:
			break;
		default:
			assert(0); /* something is wrong */
		}
	}

	return (void *)0;
}

static void *amu_context_restore(const void *arg)
{
<<<<<<< HEAD
	uint64_t i, j;

	unsigned int core_pos;
	struct amu_ctx *ctx;

	uint64_t hcr_el2_amvoffen = 0;	/* AMU virtual offsets enabled */

	uint64_t amcgcr_el0_cg0nc;	/* Number of group 0 counters */

#if ENABLE_AMU_AUXILIARY_COUNTERS
	uint64_t amcfgr_el0_ncg;	/* Number of counter groups */
	uint64_t amcgcr_el0_cg1nc;	/* Number of group 1 counters */
	uint64_t amcg1idr_el0_voff;	/* Auxiliary counters with virtual offsets */
#endif

=======
>>>>>>> upstream_import/upstream_v2_14_1
	if (!is_feat_amu_supported()) {
		return (void *)0;
	}

	unsigned int core_pos = *(unsigned int *)arg;
	amu_regs_t *ctx = PER_CPU_CUR(amu_ctx);

<<<<<<< HEAD
	amcgcr_el0_cg0nc = read_amcgcr_el0_cg0nc();
=======
	write_amevcntr00_el0(read_amu_grp0_ctx_reg(ctx, 0));
	write_amevcntr01_el0(read_amu_grp0_ctx_reg(ctx, 1));
	write_amevcntr02_el0(read_amu_grp0_ctx_reg(ctx, 2));
	write_amevcntr03_el0(read_amu_grp0_ctx_reg(ctx, 3));
>>>>>>> upstream_import/upstream_v2_14_1

	if (is_feat_amu_aux_supported()) {
		uint8_t num_counters = read_amcgcr_el0_cg1nc();

<<<<<<< HEAD
#if ENABLE_AMU_AUXILIARY_COUNTERS
	amcfgr_el0_ncg = read_amcfgr_el0_ncg();
	amcgcr_el0_cg1nc = (amcfgr_el0_ncg > 0U) ? read_amcgcr_el0_cg1nc() : 0U;
	amcg1idr_el0_voff = (hcr_el2_amvoffen != 0U) ? read_amcg1idr_el0_voff() : 0U;
#endif

	/*
	 * Restore the counter values from the local context.
	 */

	for (i = 0U; i < amcgcr_el0_cg0nc; i++) {
		amu_group0_cnt_write(i, ctx->group0_cnts[i]);
	}

#if ENABLE_AMU_AUXILIARY_COUNTERS
	for (i = 0U; i < amcgcr_el0_cg1nc; i++) {
		amu_group1_cnt_write(i, ctx->group1_cnts[i]);
	}
#endif

	/*
	 * Restore virtual offsets for counters that offer them.
	 */

	if (hcr_el2_amvoffen != 0U) {
		for (i = 0U, j = 0U; i < amcgcr_el0_cg0nc; i++) {
			if (!amu_group0_voffset_supported(i)) {
				continue; /* No virtual offset */
			}

			amu_group0_voffset_write(i, ctx->group0_voffsets[j++]);
=======
		switch (num_counters) {
		case 0x10:
			write_amevcntr1f_el0(read_amu_grp1_ctx_reg(ctx, 0xf));
			__fallthrough;
		case 0x0f:
			write_amevcntr1e_el0(read_amu_grp1_ctx_reg(ctx, 0xe));
			__fallthrough;
		case 0x0e:
			write_amevcntr1d_el0(read_amu_grp1_ctx_reg(ctx, 0xd));
			__fallthrough;
		case 0x0d:
			write_amevcntr1c_el0(read_amu_grp1_ctx_reg(ctx, 0xc));
			__fallthrough;
		case 0x0c:
			write_amevcntr1b_el0(read_amu_grp1_ctx_reg(ctx, 0xb));
			__fallthrough;
		case 0x0b:
			write_amevcntr1a_el0(read_amu_grp1_ctx_reg(ctx, 0xa));
			__fallthrough;
		case 0x0a:
			write_amevcntr19_el0(read_amu_grp1_ctx_reg(ctx, 0x9));
			__fallthrough;
		case 0x09:
			write_amevcntr18_el0(read_amu_grp1_ctx_reg(ctx, 0x8));
			__fallthrough;
		case 0x08:
			write_amevcntr17_el0(read_amu_grp1_ctx_reg(ctx, 0x7));
			__fallthrough;
		case 0x07:
			write_amevcntr16_el0(read_amu_grp1_ctx_reg(ctx, 0x6));
			__fallthrough;
		case 0x06:
			write_amevcntr15_el0(read_amu_grp1_ctx_reg(ctx, 0x5));
			__fallthrough;
		case 0x05:
			write_amevcntr14_el0(read_amu_grp1_ctx_reg(ctx, 0x4));
			__fallthrough;
		case 0x04:
			write_amevcntr13_el0(read_amu_grp1_ctx_reg(ctx, 0x3));
			__fallthrough;
		case 0x03:
			write_amevcntr12_el0(read_amu_grp1_ctx_reg(ctx, 0x2));
			__fallthrough;
		case 0x02:
			write_amevcntr11_el0(read_amu_grp1_ctx_reg(ctx, 0x1));
			__fallthrough;
		case 0x01:
			write_amevcntr10_el0(read_amu_grp1_ctx_reg(ctx, 0x0));
			__fallthrough;
		case 0x00:
			break;
		default:
			assert(0); /* something is wrong */
>>>>>>> upstream_import/upstream_v2_14_1
		}
	}


	/* now enable them again */
	write_amcntenset0_el0(AMCNTENSET0_EL0_Pn_MASK);
	if (is_feat_amu_aux_supported()) {
		write_amcntenset1_el0(get_amu_aux_enables(core_pos));
	}

	isb();
	return (void *)0;
}

SUBSCRIBE_TO_EVENT(psci_suspend_pwrdown_start, amu_context_save);
SUBSCRIBE_TO_EVENT(psci_suspend_pwrdown_finish, amu_context_restore);
