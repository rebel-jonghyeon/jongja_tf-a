#include <rebel_h_rbc.h>
#include <rebel_h_pmu.h>
#include <rebel_h_plat.h>
#include <drivers/aw/ucie.h>
#include <drivers/synopsys/qspi_bridge.h>
#include <drivers/arm/pl330.h>
#include <cmu.h>
#include <common/debug.h>
#include <lib/mmio.h>

#define ZEBU_PRE_LOAD		(ZEBU & !USE_GPT)

#define NUM_OF_CHIPS		(4)
#define NUM_OF_ACTIVE_RBC	(4)

#define TBOOT_U_SRC_ADDR	(0x1f80170010ULL)

static const uint64_t active_rbc_base[NUM_OF_CHIPS/* chip id */][NUM_OF_ACTIVE_RBC] = {
	{
		BLK_RBC_V10_BASE, BLK_RBC_V11_BASE,
		BLK_RBC_H00_BASE, BLK_RBC_H01_BASE
	},
	{
		BLK_RBC_V01_BASE, BLK_RBC_V00_BASE,
		BLK_RBC_H00_BASE, BLK_RBC_H01_BASE
	},
	{
		BLK_RBC_V00_BASE, BLK_RBC_V01_BASE,
		BLK_RBC_H00_BASE, BLK_RBC_H01_BASE
	},
	{
		BLK_RBC_V11_BASE, BLK_RBC_V10_BASE,
		BLK_RBC_H00_BASE, BLK_RBC_H01_BASE
	}
};

uint32_t num_of_chips = NUM_OF_CHIPS;
uint32_t num_of_active_rbc = NUM_OF_ACTIVE_RBC;

#if ZEBU
uint32_t set_num_of_chips_and_rbc_for_ZEBU(void)
{
	num_of_chips = plat_get_secondary_chiplet_cnt() + 1;

	if (num_of_chips <= 2) {
		num_of_active_rbc = 2;
	} else {
		num_of_active_rbc = 4;
	}
	return num_of_chips;
}
#endif /* ZEBU */

void repeat_func_for_all_rbc(void (*func)(uint32_t, uint64_t), const uint32_t base_offset,
							 uint32_t start_chiplet)
{
#if ZEBU
	/* ZEBU Unity Image does not contain BLK_RBC. */
	if (num_of_chips < 2)
		return;
#endif /* ZEBU */
	for (uint32_t chiplet_id = start_chiplet; chiplet_id < num_of_chips; chiplet_id++) {
		for (uint32_t rbc_idx = 0; rbc_idx < num_of_active_rbc; rbc_idx++) {
			const uint64_t base_addr = active_rbc_base[chiplet_id][rbc_idx];
			const uint32_t qspi_ch = 2;

			qspi_bridge_set_upper_addr(qspi_ch, ((uint32_t)base_addr) & 0xFC000000, chiplet_id);
			func(chiplet_id, base_addr + base_offset);
		}
	}
}

static bool chiplet_reachability[NUM_OF_CHIPS] = { true, false, false, false };

#if !ZEBU_PRE_LOAD
static void _load_image_using_qspi(const uint32_t chiplet_id, const uint64_t base_addr)
{
	uint64_t before_tick = 0, after_tick = 0;
	const uint32_t qspi_channel = 2;
	uint32_t *src_data = (uint32_t *)GPT_DEST_ADDR_UCIE_SS1_V1;

	qspi_bridge_set_upper_addr(qspi_channel, ((uint32_t)base_addr) & 0xFC000000, chiplet_id);
	VERBOSE("\nqspi 0x%p -> 0x%lx, size : 0x%llx start ", src_data, base_addr, GPT_DEST_SIZE_UCIE);
	before_tick = read_cntpct_el0();
	for (uint32_t offset = 0; offset < GPT_DEST_SIZE_UCIE; offset += 64) {
		qspi_bridge_write_16word(qspi_channel, base_addr + offset, src_data, chiplet_id);
		src_data += 16;
		if (offset % 0x1000 == 0)
			INFO("0x%lx\n", base_addr + offset);
	}
	after_tick = read_cntpct_el0();
	VERBOSE("before tick : %ld, after tick %ld\n", before_tick, after_tick);
	VERBOSE("diff = %ld\n", after_tick - before_tick);
}

static uint64_t convert_priv2mmio(uint32_t chiplet_id, uint64_t ori_addr)
{
	uint64_t converted_addr = ori_addr;

	converted_addr |= 0x1ff0000000;
	converted_addr += 0x2000000000 * chiplet_id;

	return converted_addr;
}
#endif /* not ZEBU_PRE_LOAD */

void load_ucie_image(const uint32_t chiplet_id, const uint64_t base_addr)
{
	VERBOSE("[to chiplet #%d] copy to 0x%lx", chiplet_id, base_addr);

#if !ZEBU_PRE_LOAD
	if (chiplet_id == CHIPLET_ID) {
		if (base_addr == BLK_RBC_V11_BASE + UCIE_SS_BASE_OFFSET) {
#if USE_GPT
			dma_load_image(base_addr, TBOOT_U_SRC_ADDR, GPT_DEST_SIZE_UCIE);
			dma_wait_xfer_done(0); /*FIX ME : to be modified to ensure completion of operation inside the dma_start().*/
#endif /* not USE_GPT */
		} else
			dma_load_image(base_addr, GPT_DEST_ADDR_UCIE_SS1_V1, GPT_DEST_SIZE_UCIE);
	} else {
		if (chiplet_reachability[chiplet_id])
			dma_load_image(convert_priv2mmio(chiplet_id, base_addr), GPT_DEST_ADDR_UCIE_SS1_V1, GPT_DEST_SIZE_UCIE);
		else
			_load_image_using_qspi(chiplet_id, base_addr);
	}
#endif /* not ZEBU_PRE_LOAD */

	VERBOSE("end\n");
}

void wait_ucie_link_up(const uint32_t chiplet_id, const uint64_t base_addr)
{
	VERBOSE("[chip %d]wait start 0x%lx ", chiplet_id, base_addr);
	uint64_t before_tick = 0, after_tick = 0;

	before_tick = read_cntpct_el0();
	while (!check_link_up(chiplet_id, base_addr)) {
	};
	after_tick = read_cntpct_el0();

	VERBOSE("end\n");
	VERBOSE("before tick : %ld, after tick %ld\n", before_tick, after_tick);
	VERBOSE("diff = %ld\n", after_tick - before_tick);

	chiplet_reachability[chiplet_id] = true;
}

static void _clear_sign_region_of_rbcv11(void)
{
	const uint32_t sign_data_len = 288;

	memset((void *)(BLK_RBC_V11_BASE + UCIE_SS_BASE_OFFSET + GPT_DEST_SIZE_UCIE - sign_data_len), 0, sign_data_len);
}

/**
 * The CP accesses the entire range through the following three UCIe links.
 * CH0 RBCv10(load by DMA)		<->	CH1 RBCv01(load by QSPI)
 * CH0 RBCh0(load by DMA)		<->	CH2 RBCh1(load by QSPI)
 * CH1 RBCh0(load by DMA+UCIe)	<->	CH3 RBCh1(load by QSPI)
 */
void load_and_enable_ucie_link_for_CP(const uint32_t bootmode)
{
#if ZEBU
	if (set_num_of_chips_and_rbc_for_ZEBU() == 1)
		return;
#endif /* ZEBU */
	/* CH0<->CH1 : CH0 RBC V10 <-> CH1 RBC V01 */
	if (bootmode == NORMAL_BOOT || bootmode == WFD_BOOT) {
		load_ucie_image(0, BLK_RBC_V11_BASE + UCIE_SS_BASE_OFFSET);
	}
	_clear_sign_region_of_rbcv11();

	load_ucie_image(0, BLK_RBC_V10_BASE + UCIE_SS_BASE_OFFSET);
	load_ucie_image(1, BLK_RBC_V01_BASE + UCIE_SS_BASE_OFFSET);
	enable_ucie_core(0, BLK_RBC_V10_BASE + UCIE_SS_BASE_OFFSET);
	enable_ucie_core(1, BLK_RBC_V01_BASE + UCIE_SS_BASE_OFFSET);
	if (num_of_chips == 4) {
		/* CH0<->CH2 : CH0 RBC H0 <-> CH2 RBC H1 */
		load_ucie_image(0, BLK_RBC_H00_BASE + UCIE_SS_BASE_OFFSET);
		load_ucie_image(2, BLK_RBC_H01_BASE + UCIE_SS_BASE_OFFSET);
		enable_ucie_core(0, BLK_RBC_H00_BASE + UCIE_SS_BASE_OFFSET);
		enable_ucie_core(2, BLK_RBC_H01_BASE + UCIE_SS_BASE_OFFSET);

		/* wait CH0<->CH1 link up to use UCIe link for loading FW into CH1 RBC H0 */
		wait_ucie_link_up(0, BLK_RBC_V10_BASE + UCIE_SS_BASE_OFFSET);
		wait_ucie_link_up(1, BLK_RBC_V01_BASE + UCIE_SS_BASE_OFFSET);

		/* CH1<->CH3 : CH1 RBC H0 <-> CH3 RBC H1 */
		load_ucie_image(1, BLK_RBC_H00_BASE + UCIE_SS_BASE_OFFSET);
		load_ucie_image(3, BLK_RBC_H01_BASE + UCIE_SS_BASE_OFFSET);
		enable_ucie_core(1, BLK_RBC_H00_BASE + UCIE_SS_BASE_OFFSET);
		enable_ucie_core(3, BLK_RBC_H01_BASE + UCIE_SS_BASE_OFFSET);
	}
}

void wait_ucie_link_up_for_CP(void)
{
#if ZEBU
	if (set_num_of_chips_and_rbc_for_ZEBU() == 1)
		return;
#endif /* ZEBU */
	wait_ucie_link_up(0, BLK_RBC_V10_BASE + UCIE_SS_BASE_OFFSET);
	wait_ucie_link_up(1, BLK_RBC_V01_BASE + UCIE_SS_BASE_OFFSET);
	if (num_of_chips == 4) {
		wait_ucie_link_up(0, BLK_RBC_H00_BASE + UCIE_SS_BASE_OFFSET);
		wait_ucie_link_up(2, BLK_RBC_H01_BASE + UCIE_SS_BASE_OFFSET);

		wait_ucie_link_up(1, BLK_RBC_H00_BASE + UCIE_SS_BASE_OFFSET);
		wait_ucie_link_up(3, BLK_RBC_H01_BASE + UCIE_SS_BASE_OFFSET);
	}
}

struct private_ucie_ss_base {
	uint32_t chiplet_id;
	uint64_t base;
};

void ucie_link_up_for_others(void)
{
#if ZEBU
	if (set_num_of_chips_and_rbc_for_ZEBU() == 1)
		return;
#endif /* ZEBU */
	const struct private_ucie_ss_base ss_base[] = {
		{0, BLK_RBC_V11_BASE + UCIE_SS_BASE_OFFSET},
		{1, BLK_RBC_V00_BASE + UCIE_SS_BASE_OFFSET},
		{0, BLK_RBC_H01_BASE + UCIE_SS_BASE_OFFSET},
		{1, BLK_RBC_H01_BASE + UCIE_SS_BASE_OFFSET},
		{2, BLK_RBC_V01_BASE + UCIE_SS_BASE_OFFSET},
		{2, BLK_RBC_V00_BASE + UCIE_SS_BASE_OFFSET},
		{2, BLK_RBC_H00_BASE + UCIE_SS_BASE_OFFSET},
		{3, BLK_RBC_V10_BASE + UCIE_SS_BASE_OFFSET},
		{3, BLK_RBC_V11_BASE + UCIE_SS_BASE_OFFSET},
		{3, BLK_RBC_H00_BASE + UCIE_SS_BASE_OFFSET},
	};

	uint32_t num_of_ucie_ss = (num_of_chips == 2) ? 2 : ARRAY_SIZE(ss_base);

	/* It should be performed by UCIe Link */
	for (uint32_t i = 1/* V11 image was loaded @BL1 */; i < num_of_ucie_ss; ++i)
		load_ucie_image(ss_base[i].chiplet_id, ss_base[i].base);

	for (uint32_t i = 0; i < num_of_ucie_ss; ++i)
		enable_ucie_core(ss_base[i].chiplet_id, ss_base[i].base);

	for (uint32_t i = 0; i < num_of_ucie_ss; ++i)
		wait_ucie_link_up(ss_base[i].chiplet_id, ss_base[i].base);
}

void set_remap_table(void)
{
#if CHIPLET_COUNT > 1
	const uint32_t default_remap_noc[NUM_OF_CHIPS] = {
	0x00001210, 0x00032303, 0x00022022, 0x00020222
	// 0x00002210, 0x00033303, 0x00023022, 0x00010111 // 2025-12-01, just try this
	};
	const uint32_t default_remap_nic[NUM_OF_CHIPS] = {
		0x00000001, 0x00000002, 0x00000004, 0x00000008
	};
#else
	const uint32_t default_remap_noc[NUM_OF_CHIPS] = {
		0x00000000, 0x00000000, 0x00000000, 0x00000000
	};
	const uint32_t default_remap_nic[NUM_OF_CHIPS] = {
		0x00000001, 0x00000001, 0x00000001, 0x00000001
	};
#endif /* CHIPLET_COUNT */
	uint32_t chiplet_id = 0;

	for (; chiplet_id < num_of_chips; chiplet_id++) {
		const uint32_t qspi_channel = 2;

		if (chiplet_id == CHIPLET_ID) {
			mmio_write_32(SYSREG_SYSREMAP_REMAP_NOC, default_remap_noc[chiplet_id]);
			mmio_write_32(SYSREG_SYSREMAP_REMAP_NIC, default_remap_nic[chiplet_id]);
		} else {
			qspi_bridge_write_1word(qspi_channel, SYSREG_SYSREMAP_REMAP_NOC, default_remap_noc[chiplet_id], chiplet_id);
			qspi_bridge_write_1word(qspi_channel, SYSREG_SYSREMAP_REMAP_NIC, default_remap_nic[chiplet_id], chiplet_id);
		}
	}
}

void chiplet_access_test(void)
{
	uint64_t base_addr[4] = {
		0x1FF5820000/* V10 */, 0x3FF5420000/* V01 */,
		0x5FF5020000/* V00 */, 0x7FF5C20000/* V11 */
	};
	uint64_t size = 0x20000;/* It should be changed to 0x10000 for F3 version. */
	uint64_t chiplet_id = 0;
	uint32_t patterns[4] = { 0xa5a5a5a5, 0x5a5a5a5a, 0x66666666, 0x99999999 };
	uint32_t data = 0;
	uint32_t offset = 0;

	for (chiplet_id = 0; chiplet_id < num_of_chips; chiplet_id++) {
		for (uint32_t pat_idx = 0; pat_idx < 4; pat_idx++) {
			for (offset = 0; offset < size; offset += 2048) {
				uint64_t addr = base_addr[chiplet_id] + offset;

				mmio_write_32(addr, patterns[pat_idx]);
				data = mmio_read_32(addr);
				if (data != patterns[pat_idx]) {
					ERROR("fail!! ch%lu a:%lx e:0x%x | a:0x%x", chiplet_id, addr, patterns[pat_idx],
						  data);
					while (1) {
					}
				}
			}
		}
	}
}
