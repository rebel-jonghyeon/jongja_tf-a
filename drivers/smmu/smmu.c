#include <util.h>
#include <rebel_h_platform.h>
#include <driver.h>
#include "interrupt.h"
#include "smmu.h"
#include <stdlib.h>
#include <string.h>
#include "cpu.h"
#include "gic.h"
#include "semphr.h"
#include "mmu.h"
#include "rl_utils.h"

#define CMDQ_LOG2   10UL
#define EVTQ_LOG2   10UL

#define Q_IDX(q, p)     ((p) & ((1 << (q)->size_log2) - 1))
#define Q_WRP(q, p)     ((p) & (1 << (q)->size_log2))
#define Q_OVF(p)        ((p) & (1 << 31)) /* Event queue overflowed */
#define Q_ENT(q, p, dwords)    (~(1UL << 62) & ((q)->base + Q_IDX(q, p) * (dwords) * 8))

#define ACK_TIMEOUT 100000

#define TCU_EVENT_Q_NS_ID   762
#define TCU_CMD_SYNC_NS_ID  763
#define TCU_GLOBAL_SYNC_NS_ID   765
#define TCU_PRI_Q_NS_ID     769

#define CMDQ_ENTRY_DWORDS   2
#define EVTQ_ENTRY_DWORDS   4
#define PRIQ_ENTRY_DWORDS   2

#define STRTAB_L1_SZ_SHIFT  20
#define STRTAB_SPLIT        6

#define STRTAB_L1_DESC_L2PTR_M  (0x3fffffffffff << 6)
#define STRTAB_L1_DESC_DWORDS   1

#define STRTAB_STE_DWORDS   8
#define CD_DWORDS       8

#define GERROR_ERR_MASK         0x1fd
#define GERROR_SFM_ERR          BIT(8)
#define GERROR_MSI_GERROR_ABT_ERR   BIT(7)
#define GERROR_MSI_PRIQ_ABT_ERR     BIT(6)
#define GERROR_MSI_EVTQ_ABT_ERR     BIT(5)
#define GERROR_MSI_CMDQ_ABT_ERR     BIT(4)
#define GERROR_PRIQ_ABT_ERR     BIT(3)
#define GERROR_EVTQ_ABT_ERR     BIT(2)
#define GERROR_CMDQ_ERR         BIT(0)

#define CMDQ_CONS_ERR           RL_GENMASK(30, 24)
#define CMDQ_CONS_RD			RL_GENMASK(19, 0)
#define CMDQ_ERR_CERROR_NONE_IDX    0
#define CMDQ_ERR_CERROR_ILL_IDX     1
#define CMDQ_ERR_CERROR_ABT_IDX     2
#define CMDQ_ERR_CERROR_ATC_INV_IDX 3

#define SMMU_EVT_IRQ	762
#define SMMU_GERR_IRQ	765

#define CMDQ_BASE		(0x140f8000ULL)
#define EVTQ_BASE		(0x140f0000ULL)
#define ST_ADDR			(0x14000000ULL)
#define CDT_ADDR		(0x14001000ULL)
#define SMMU_REGION_0	(0x14020000ULL)
#define SMMU_REGION_1	(0x14030000ULL)
#ifdef __TEST
#define SMMU_REGION_PCIE	(0x14040000ULL)
#endif

SemaphoreHandle_t mtx;

static uint16_t smmu_xlat_use_count[MAX_XLAT_TABLES];
static uint16_t smmu_xlat_sid0_use_count[MAX_XLAT_TABLES];

extern const char dma_mcode_start[];

/* TODO : The following regions are for testing. */
struct mmu_region smmu_regions[] = {
	MMU_REGION_FLAT_ENTRY("dma0_mcode",
						  0x00600000ULL,
						  0x4000,
						  MT_NORMAL_NC | MT_P_RX_U_RX | MT_NS | MT_NG),
	MMU_REGION_FLAT_ENTRY("dma1_mcode",
						  0x2000600000ULL,
						  0x4000,
						  MT_NORMAL_NC | MT_P_RX_U_RX | MT_NS | MT_NG),
	MMU_REGION_FLAT_ENTRY("dma2_mcode",
						  0x4000600000ULL,
						  0x4000,
						  MT_NORMAL_NC | MT_P_RX_U_RX | MT_NS | MT_NG),
	MMU_REGION_FLAT_ENTRY("dma3_mcode",
						  0x6000600000ULL,
						  0x4000,
						  MT_NORMAL_NC | MT_P_RX_U_RX | MT_NS | MT_NG),
	MMU_REGION_FLAT_ENTRY("DRAM0 User Region",
						  0x0040000000ULL,
						  0x08C0000000ULL,
						  MT_NORMAL_NC | MT_P_RW_U_RW | MT_NS | MT_NG),
	MMU_REGION_FLAT_ENTRY("DRAM1 User Region",
						  0x2040000000ULL,
						  0x08C0000000ULL,
						  MT_NORMAL_NC | MT_P_RW_U_RW | MT_NS | MT_NG),
	MMU_REGION_FLAT_ENTRY("DRAM2 User Region",
						  0x4040000000ULL,
						  0x08C0000000ULL,
						  MT_NORMAL_NC | MT_P_RW_U_RW | MT_NS | MT_NG),
	MMU_REGION_FLAT_ENTRY("DRAM3 User Region",
						  0x6040000000ULL,
						  0x08C0000000ULL,
						  MT_NORMAL_NC | MT_P_RW_U_RW | MT_NS | MT_NG),
};

struct mmu_region smmu_regions1[] = {
	MMU_REGION_FLAT_ENTRY("dma_mcode",
						  0x0044A000ULL,
						  0x4000,
						  MT_NORMAL_NC | MT_P_RX_U_RX | MT_NS | MT_NG),
};

#ifdef __TEST
/* NOTE: SMMU regions for PCIe HDMA test*/
struct mmu_region smmu_regions_pcie[] = {
	MMU_REGION_FLAT_ENTRY("PCIE_HDMA_DESC",
						  0x1E08000000ULL,
						  0x40000,
						  MT_NORMAL_NC | MT_P_RW_U_RW | MT_NS | MT_NG),
	MMU_REGION_FLAT_ENTRY("DRAM0 User Region",
						  0x0040000000ULL,
						  0x08C0000000ULL,
						  MT_NORMAL_NC | MT_P_RW_U_RW | MT_NS | MT_NG),
	MMU_REGION_FLAT_ENTRY("DRAM1 User Region",
						  0x2040000000ULL,
						  0x08C0000000ULL,
						  MT_NORMAL_NC | MT_P_RW_U_RW | MT_NS | MT_NG),
	MMU_REGION_FLAT_ENTRY("DRAM2 User Region",
						  0x4040000000ULL,
						  0x08C0000000ULL,
						  MT_NORMAL_NC | MT_P_RW_U_RW | MT_NS | MT_NG),
	MMU_REGION_FLAT_ENTRY("DRAM3 User Region",
						  0x6040000000ULL,
						  0x08C0000000ULL,
						  MT_NORMAL_NC | MT_P_RW_U_RW | MT_NS | MT_NG),
};
#endif

/* TODO : The following struct is for testing. */
struct mmu_ptables smmu_ptables[] = {
	{
		.mmu_flat_range = NULL,
		.mmu_flat_range_size = 0,
		.mmu_region = smmu_regions,
		.mmu_region_size = (sizeof(smmu_regions) / sizeof((smmu_regions)[0])),
		.base_xlat_table = (void *)SMMU_REGION_0,
		.xlat_use_count = smmu_xlat_sid0_use_count,
		.xlat_table_count = MAX_XLAT_TABLES,
		.xlat_table_size = Ln_NUM_ENTRIES,
		.flag = 0,
	},
	{
		.mmu_flat_range = NULL,
		.mmu_flat_range_size = 0,
		.mmu_region = smmu_regions1,
		.mmu_region_size = (sizeof(smmu_regions1) / sizeof((smmu_regions1)[0])),
		.base_xlat_table = (void *)SMMU_REGION_1,
		.xlat_use_count = smmu_xlat_use_count,
		.xlat_table_count = MAX_XLAT_TABLES,
		.xlat_table_size = Ln_NUM_ENTRIES,
		.flag = 0,
	},
#ifdef __TEST
	{
		.mmu_flat_range = NULL,
		.mmu_flat_range_size = 0,
		.mmu_region = smmu_regions_pcie,
		.mmu_region_size = (sizeof(smmu_regions_pcie) / sizeof((smmu_regions_pcie)[0])),
		.base_xlat_table = (void *)SMMU_REGION_PCIE,
		.xlat_use_count = smmu_xlat_use_count,
		.xlat_table_count = MAX_XLAT_TABLES,
		.xlat_table_size = Ln_NUM_ENTRIES,
		.flag = 0,
	},
#endif
};

static struct stream_table *st;
static struct cd_tables *cdt;

static struct smmu_event events[] = {
	{ 0x01, "F_UUT",
		"Unsupported Upstream Transaction."},
	{ 0x02, "C_BAD_STREAMID",
		"Transaction StreamID out of range."},
	{ 0x03, "F_STE_FETCH",
		"Fetch of STE caused external abort."},
	{ 0x04, "C_BAD_STE",
		"Used STE invalid."},
	{ 0x05, "F_BAD_ATS_TREQ",
		"Address Translation Request disallowed for a StreamID "
		"and a PCIe ATS Translation Request received."},
	{ 0x06, "F_STREAM_DISABLED",
		"The STE of a transaction marks non-substream transactions "
		"disabled."},
	{ 0x07, "F_TRANSL_FORBIDDEN",
		"An incoming PCIe transaction is marked Translated but "
		"SMMU bypass is disallowed for this StreamID."},
	{ 0x08, "C_BAD_SUBSTREAMID",
		"Incoming SubstreamID present, but configuration is invalid."},
	{ 0x09, "F_CD_FETCH",
		"Fetch of CD caused external abort."},
	{ 0x0a, "C_BAD_CD",
		"Fetched CD invalid."},
	{ 0x0b, "F_WALK_EABT",
		"An external abort occurred fetching (or updating) "
		"a translation table descriptor."},
	{ 0x10, "F_TRANSLATION",
		"Translation fault."},
	{ 0x11, "F_ADDR_SIZE",
		"Address Size fault."},
	{ 0x12, "F_ACCESS",
		"Access flag fault due to AF == 0 in a page or block TTD."},
	{ 0x13, "F_PERMISSION",
		"Permission fault occurred on page access."},
	{ 0x20, "F_TLB_CONFLICT",
		"A TLB conflict occurred because of the transaction."},
	{ 0x21, "F_CFG_CONFLICT",
		"A configuration cache conflict occurred due to "
		"the transaction."},
	{ 0x24, "E_PAGE_REQUEST",
		"Speculative page request hint."},
	{ 0x25, "F_VMS_FETCH",
		"Fetch of VMS caused external abort."},
	{ 0, NULL, NULL },
};

static struct smmu_queue smmu_cmdq = {
	.paddr = CMDQ_BASE,
	.size_log2 = CMDQ_LOG2,
};

static struct smmu_queue smmu_evtq = {
	.paddr = EVTQ_BASE,
	.size_log2 = EVTQ_LOG2,
};

static void make_cmd(uint64_t *cmd, struct smmu_cmdq_entry *entry)
{
	memset(cmd, 0, CMDQ_ENTRY_DWORDS * 8);
	cmd[0] = entry->opcode << CMD_QUEUE_OPCODE_S;

	switch (entry->opcode) {
	case CMD_TLBI_NH_VA:
	    cmd[0] |= (uint64_t)entry->tlbi.asid << TLBI_0_ASID_S;
	    cmd[1] = entry->tlbi.addr & TLBI_1_ADDR_M;
	    if (entry->tlbi.leaf) {
			/*
			 * Leaf flag means that only cached entries
			 * for the last level of translation table walk
			 * are required to be invalidated.
			 */
			cmd[1] |= TLBI_1_LEAF;
	    }
	    break;
	case CMD_TLBI_NH_ASID:
		cmd[0] |= (uint64_t)entry->tlbi.asid << TLBI_0_ASID_S;
		cmd[0] |= (uint64_t)entry->tlbi.vmid << TLBI_0_VMID_S;
	    break;
	case CMD_TLBI_NSNH_ALL:
	case CMD_TLBI_NH_ALL:
	case CMD_TLBI_EL2_ALL:
	    break;
	case CMD_CFGI_CD_ALL:
		cmd[0] |= ((uint64_t)entry->cfgi.sid << CFGI_0_STE_SID_S);
	case CMD_CFGI_CD:
	    cmd[0] |= ((uint64_t)entry->cfgi.ssid << CFGI_0_SSID_S);
	    /* FALLTROUGH */
	case CMD_CFGI_STE:
	    cmd[0] |= ((uint64_t)entry->cfgi.sid << CFGI_0_STE_SID_S);
	    cmd[1] |= ((uint64_t)entry->cfgi.leaf << CFGI_1_LEAF_S);
	    break;
	case CMD_CFGI_STE_RANGE:
	    cmd[1] = (5 << CFGI_1_STE_RANGE_S);
	    break;
	case CMD_SYNC:
	    cmd[0] |= SYNC_0_MSH_IS | SYNC_0_MSIATTR_OIWB;
	    if (entry->sync.msiaddr) {
			cmd[0] |= SYNC_0_CS_SIG_IRQ;
			cmd[1] |= (entry->sync.msiaddr & SYNC_1_MSIADDRESS_M);
	    } else
			cmd[0] |= SYNC_0_CS_SIG_SEV;
	    break;
	case CMD_PREFETCH_CONFIG:
	    cmd[0] |= ((uint64_t)entry->prefetch.sid << PREFETCH_0_SID_S);
	    cmd[0] |= ((uint64_t)entry->prefetch.ssid << PREFETCH_0_SSID_S);
	    cmd[0] |= ((uint64_t)entry->prefetch.ssv << PREFETCH_0_SSV_S);
	    cmd[0] |= ((uint64_t)entry->prefetch.ssec << PREFETCH_0_SSEC_S);
	    break;
	};
}

static int smmu_q_has_space(struct smmu_queue *q)
{
	if (Q_IDX(q, q->lc.cons) != Q_IDX(q, q->lc.prod) ||
		Q_WRP(q, q->lc.cons) == Q_WRP(q, q->lc.prod))
	    return (1);

	return 0;
}

static uint32_t smmu_q_inc_prod(struct smmu_queue *q)
{
	uint32_t prod;
	uint32_t val;

	prod = (Q_WRP(q, q->lc.prod) | Q_IDX(q, q->lc.prod)) + 1;
	val = (Q_OVF(q->lc.prod) | Q_WRP(q, prod) | Q_IDX(q, prod));

	return val;
}

static uint32_t smmu_q_inc_cons(struct smmu_queue *q)
{
	uint32_t cons;
	uint32_t val;

	cons = (Q_WRP(q, q->lc.cons) | Q_IDX(q, q->lc.cons)) + 1;
	val = (Q_OVF(q->lc.cons) | Q_WRP(q, cons) | Q_IDX(q, cons));

	return val;
}

static int smmu_q_empty(struct smmu_queue *q)
{

	if (Q_IDX(q, q->lc.cons) == Q_IDX(q, q->lc.prod) &&
		Q_WRP(q, q->lc.cons) == Q_WRP(q, q->lc.prod))
		return 1;

	return 0;
}

static int smmu_write_ack(uint32_t reg, uint32_t reg_ack, uint32_t val)
{
	uint32_t v;
	int timeout;

	timeout = ACK_TIMEOUT;

	v = sys_read32(TCU + reg);
	v |= val;

	sys_write32(v, TCU + reg);

	do {
	    v = sys_read32(TCU + reg_ack);
	    if (v & val)
			break;
	} while (timeout--);

	if (timeout <= 0) {
	    printf("Failed to write reg.\n");
	    return -1;
	}

	return 0;
}

void smmu_cmdq_enqueue_cmd(struct smmu_cmdq_entry *entry)
{
	uint64_t cmd[CMDQ_ENTRY_DWORDS];
	struct smmu_queue *cmdq;
	void *entry_addr;

	cmdq = &smmu_cmdq;

	make_cmd(cmd, entry);

	xSemaphoreTake(mtx, portMAX_DELAY);

	/* Ensure that a space is available. */
	do {
	    cmdq->lc.cons = sys_read32(TCU + cmdq->cons_off);
	} while (smmu_q_has_space(cmdq) == 0);

	/* Write the command to the current prod entry. */
	entry_addr = (void *)(cmdq->paddr + Q_IDX(cmdq, cmdq->lc.prod) * CMDQ_ENTRY_DWORDS * 8 + CHIPLET_BASE_ADDRESS);
	memcpy(entry_addr, cmd, CMDQ_ENTRY_DWORDS * 8);

	/* Increment prod index. */
	cmdq->lc.prod = smmu_q_inc_prod(cmdq);
	sys_write32(cmdq->lc.prod, TCU + cmdq->prod_off);

	xSemaphoreGive(mtx);
}

int smmu_sync(void)
{
	struct smmu_cmdq_entry cmd;
	struct smmu_queue *q;
	uint32_t *base;
	int timeout;
	int prod;

	q = &smmu_cmdq;
	prod = q->lc.prod;

	/* Enqueue sync command. */
	cmd.opcode = CMD_SYNC;
	cmd.sync.msiaddr = q->paddr + Q_IDX(q, prod) * CMDQ_ENTRY_DWORDS * 8 + CHIPLET_BASE_ADDRESS;
	smmu_cmdq_enqueue_cmd(&cmd);

	/* Wait for the sync completion. */
	base = (void *)(q->paddr + Q_IDX(q, prod) * CMDQ_ENTRY_DWORDS * 8 + CHIPLET_BASE_ADDRESS);

	timeout = ACK_TIMEOUT;

	do {
	    if (*base == 0) {
			/* MSI write completed. */
			break;
	    }
	    __asm__ volatile("yield" ::: "memory");
	} while (timeout--);

	if (timeout < 0)
	    printf("Failed to sync\n");

	return 0;
}

void smmu_invalidate_all_cd(void)
{
	struct smmu_cmdq_entry cmd;

	cmd.opcode = CMD_CFGI_CD_ALL;
	smmu_cmdq_enqueue_cmd(&cmd);
	smmu_sync();
}

void smmu_invalidate_sid(uint32_t sid)
{
	struct smmu_cmdq_entry cmd;

	cmd.opcode = CMD_CFGI_STE;
	cmd.cfgi.sid = sid;
	smmu_cmdq_enqueue_cmd(&cmd);
	smmu_sync();
}

void smmu_prefetch(uint32_t sid, uint32_t ssid, uint8_t ssv, uint8_t ssec)
{
	struct smmu_cmdq_entry cmd;

	cmd.opcode = CMD_PREFETCH_CONFIG;
	cmd.prefetch.sid = sid;
	cmd.prefetch.ssid = ssid;
	cmd.prefetch.ssv = ssv;
	cmd.prefetch.ssec = ssec;
	smmu_cmdq_enqueue_cmd(&cmd);
	smmu_sync();
}

int smmu_sync_cd(int sid, int ssid, bool leaf)
{
	struct smmu_cmdq_entry cmd;

	cmd.opcode = CMD_CFGI_CD;
	cmd.cfgi.sid = sid;
	cmd.cfgi.ssid = ssid;
	cmd.cfgi.leaf = leaf;
	smmu_cmdq_enqueue_cmd(&cmd);

	return 0;
}

void smmu_invalidate_tlb_asid(uint32_t sid, uint32_t ssid)
{
	struct smmu_cmdq_entry cmd;

	cmd.opcode = CMD_TLBI_NH_ASID;
	cmd.tlbi.vmid = sid;
	cmd.tlbi.asid = ssid;
	smmu_cmdq_enqueue_cmd(&cmd);
	smmu_sync();
}

void smmu_activate_ctx(int func_id, int ctx_id, uint64_t pt_base)
{
	cdt[func_id].cd[ctx_id].val[0] |= CD0_VALID;
	cdt[func_id].cd[ctx_id].val[1] = pt_base;

	/* Sync CD update before invalidating TLB */
	smmu_sync_cd(func_id, ctx_id, 1);
//	smmu_sync();  /* Wait for CD update to complete */
	smmu_invalidate_tlb_asid(func_id, ctx_id);
}

static void smmu_init_ste_bypass(uint32_t sid)
{
	uint32_t bypass_sid;
	uint64_t val;

	val = STE0_VALID | STE0_CONFIG_BYPASS;
	bypass_sid = sid + BYPASS_START_SID;

	st[bypass_sid].ste[0] = val;

	smmu_invalidate_sid(bypass_sid);
}

void smmu_s2_enable(int func_id, uint64_t pt_base)
{
	uint64_t val;

	st[func_id].ste[3] = pt_base;

	val = st[func_id].ste[0];
	val |= STE0_CONFIG_ALL_TRANS;
	st[func_id].ste[0] = val;

	val = STE2_S2AA64;
	val |= STE2_S2TG_4KB;
	val |= (26ULL << STE2_S2T0SZ_S);
	val |= STE2_S2SL0_L1;
	val |= STE2_S2IR0_WBC_RA;
	val |= STE2_S2OR0_WBC_RA;
	val |= STE2_S2SH0_IS;
	val |= (0x5ULL << STE2_S2PS_S);
	val |= STE2_S2AFFD;
	val |= STE2_S2R;
	val |= (func_id << STE2_S2VMID_S);

	st[func_id].ste[2] = val;

	assert(func_id < BYPASS_START_SID);
	smmu_init_ste_bypass(func_id);

	smmu_invalidate_all_sid();
}

void smmu_s2_disable(int func_id)
{
	uint64_t val;

	/* STE[0]에서 STE0_CONFIG_ALL_TRANS 제거, STE0_CONFIG_S1_TRANS만 유지 */
	val = st[func_id].ste[0];
	val &= ~STE0_CONFIG_ALL_TRANS;  /* S2 설정 제거 */
	val |= STE0_CONFIG_S1_TRANS;     /* S1만 유지 */
	st[func_id].ste[0] = val;

	/* STE[2]를 원래대로 복원 (S2VMID만, S2 translation 설정 제거) */
	st[func_id].ste[2] = (func_id << STE2_S2VMID_S);

	/* STE[3] S2TTB 초기화 */
	st[func_id].ste[3] = 0;

	/* 변경사항 동기화 */
	smmu_invalidate_sid(func_id);
	smmu_sync();
}

void smmu_deinit_ste(uint32_t sid)
{
	st[sid].ste[0] = 0;

	smmu_invalidate_sid(sid);
	smmu_sync_cd(sid, 0, true);
	smmu_invalidate_sid(sid);
}

int smmu_init_ste(uint64_t sid)
{
	uint64_t val;
	const uint64_t vf_system_hidden_offset = 0x10000000; // 256MB
	const uint64_t pf_system_ipa_base = 0x40000000; // 1GB

	val = STE0_VALID;

	/* S1 */
	st[sid].ste[1] =  STE1_S1STALLD | STE1_EATS_FULLATS | STE1_STRW_NS_EL1 | STE1_S1CSH_IS |
					  STE1_S1CIR_WBRA | STE1_S1COR_WBRA | STE1_S1DSS_BYPASS;
	st[sid].ste[2] = (sid << STE2_S2VMID_S);                     /* S2VMID, S2T0SZ, S2TG */
	st[sid].ste[3] = 0;                     /* S2TTB */
	st[sid].ste[4] = 0;                     /* S2T0SZ, S2TG */
	st[sid].ste[5] = 0;                     /* VMSptr */
	st[sid].ste[6] = 0;                     /* S2TTB Sec*/
	st[sid].ste[7] = 0;                     /* RES0 */

	/* Configure STE */
	val |= ((uint64_t)(cdt + sid) & (CHIPLET_OFFSET - 1) & STE0_S1CONTEXTPTR_M);
	val |= STE0_CONFIG_S1_TRANS;
	val |= (6UL << STE0_S1CDMAX_S);

	val += (sid > 0) ? vf_system_hidden_offset : pf_system_ipa_base;

	smmu_invalidate_sid(sid);

	/* The STE[0] has to be written in a single blast, last of all. */
	st[sid].ste[0] = val;                   /* Valid, Config, S1contextPtr */
	dsb();

	smmu_invalidate_sid(sid);

	return 0;
}

static void smmu_create_ptables(void)
{
	struct mmu_ptables ptables;

	for (int i = 0; i < sizeof(smmu_ptables) / sizeof(struct mmu_ptables); i++) {
		ptables = smmu_ptables[i];
		ptables.base_xlat_table = (void *)((uint64_t)ptables.base_xlat_table + CHIPLET_BASE_ADDRESS);
		new_table(&ptables);
		setup_page_tables(&ptables);
	}
}

void smmu_init_cd(struct context_desc *cd)
{
	uint64_t val;

	for (uint64_t ssid = 0; ssid < 64; ssid++) {
		val = CD0_AA64;
		val |= CD0_TG0_4KB;
		val |= CD0_TG1_4KB;
		val |= CD0_EPD1; /* Disable TT1 */
		val |= (23 << CD0_T0SZ_S);
		val |= CD0_IPS_40BITS;
		val |= CD0_TBI0;
		val |= CD0_TBI1;
		val |= CD0_SH0_IS;
		val |= CD0_OR0_WBC_RA;
		val |= CD0_IR0_WBC_RA;
		val |= CD0_R;
		val |= CD0_A;	// for quad replay, 2026-02-12
		val |= CD0_AFFD;
		val |= CD0_ASET;
		val |= ssid << CD0_ASID_S;

		cd[ssid].val[1] = 0; /* table address */
		cd[ssid].val[2] = 0;
		cd[ssid].val[3] = MEMORY_ATTRIBUTES;

		/* Install the CD. */
		cd[ssid].val[0] = val;
	}
}

static int smmu_init_queue(struct smmu_queue *q, uint32_t prod_off, uint32_t cons_off,
						   uint32_t dwords)
{
	q->prod_off = prod_off;
	q->cons_off = cons_off;

	q->base = CMDQ_BASE_RA | EVENTQ_BASE_WA;
	q->base |= q->paddr + CHIPLET_BASE_ADDRESS;
	q->base |= q->size_log2 << Q_LOG2SIZE_S;

	return 0;
}

static int smmu_init_queues(void)
{
	int err;

	/* Command queue. */
	err = smmu_init_queue(&smmu_cmdq, SMMU_CMDQ_PROD, SMMU_CMDQ_CONS, CMDQ_ENTRY_DWORDS);
	if (err)
	    return -ENXIO;

	/* Event queue. */
	err = smmu_init_queue(&smmu_evtq, SMMU_EVENTQ_PROD, SMMU_EVENTQ_CONS, EVTQ_ENTRY_DWORDS);
	if (err)
	    return -ENXIO;

	return 0;
}

void smmu_invalidate_all_sid(void)
{
	struct smmu_cmdq_entry cmd;

	cmd.opcode = CMD_CFGI_STE_RANGE;
	smmu_cmdq_enqueue_cmd(&cmd);
	smmu_sync();
}

void smmu_tlbi_all(void)
{
	struct smmu_cmdq_entry cmd;

	cmd.opcode = CMD_TLBI_NSNH_ALL;
	smmu_cmdq_enqueue_cmd(&cmd);
	smmu_sync();
}

static void smmu_evtq_dequeue(uint32_t *evt)
{
	void *entry_addr;

	smmu_evtq.lc.val = sys_read64(TCU + smmu_evtq.prod_off);
	entry_addr = (void *)((uint64_t)smmu_evtq.paddr + smmu_evtq.lc.cons * EVTQ_ENTRY_DWORDS * 8 + CHIPLET_BASE_ADDRESS);
	memcpy(evt, entry_addr, EVTQ_ENTRY_DWORDS * 8);
	smmu_evtq.lc.cons = smmu_q_inc_cons(&smmu_evtq);
	sys_write32(smmu_evtq.lc.cons, TCU + smmu_evtq.cons_off);
}

static void smmu_print_event(uint32_t *evt)
{
	struct smmu_event *ev;
	uintptr_t input_addr;
	uint8_t event_id;
	int sid;
	int i;

	ev = NULL;
	event_id = evt[0] & 0xff;
	for (i = 0; events[i].ident != 0; i++) {
		if (events[i].ident == event_id) {
		    ev = &events[i];
		    break;
		}
	}

	sid = evt[1];
	input_addr = evt[5];
	input_addr <<= 32;
	input_addr |= evt[4];

	if (ev) {
		printf("Event %s (%s) received.\n", ev->str, ev->msg);
	} else
		printf("Event 0x%x received\n", event_id);

	printf("SID %d, Input Address: 0x%jx\n", sid, input_addr);

	for (i = 0; i < 8; i++)
		printf("evt[%d] %x\n", i, evt[i]);
}

static void smmu_cmdq_skip_err(void)
{
	static const char * const cerror_str[] = {
		[CMDQ_ERR_CERROR_NONE_IDX]  = "No error",
		[CMDQ_ERR_CERROR_ILL_IDX]   = "Illegal command",
		[CMDQ_ERR_CERROR_ABT_IDX]   = "Abort on command fetch",
		[CMDQ_ERR_CERROR_ATC_INV_IDX]   = "ATC invalidate timeout",
	};

	int i;
	uint64_t cmd[CMDQ_ENTRY_DWORDS];
	uint32_t val = sys_read32(TCU + smmu_cmdq.cons_off);
	uint32_t idx = RL_BITFIELD_GET(CMDQ_CONS_ERR, val);
	uint32_t cons = RL_BITFIELD_GET(CMDQ_CONS_RD, val);
	void *entry_addr;
	struct smmu_queue *q;

	q = &smmu_cmdq;

	struct smmu_cmdq_entry cmd_sync;

	cmd_sync.opcode = CMD_SYNC;

	printf("CMDQ error (cons 0x%08x): %s\n", cons,
		   idx < ARRAY_SIZE(cerror_str) ?  cerror_str[idx] : "Unknown");

	switch (idx) {
	case CMDQ_ERR_CERROR_ABT_IDX:
		printf("retrying command fetch\n");
		return;
	case CMDQ_ERR_CERROR_NONE_IDX:
		return;
	case CMDQ_ERR_CERROR_ATC_INV_IDX:
		return;
	case CMDQ_ERR_CERROR_ILL_IDX:
	default:
		break;
	}

	entry_addr = (void *)(q->paddr + Q_IDX(q, q->lc.cons) * CMDQ_ENTRY_DWORDS * 8 + CHIPLET_BASE_ADDRESS);
	memcpy(cmd, entry_addr, CMDQ_ENTRY_DWORDS * 8);

	printf("skipping command in error state:\n");
	for (i = 0; i < ARRAY_SIZE(cmd); ++i)
		printf("\t0x%016llx\n", (unsigned long long)cmd[i]);

	make_cmd(cmd, &cmd_sync);

	memcpy(entry_addr, cmd, CMDQ_ENTRY_DWORDS * 8);
}

void smmu_disable(void)
{
	uint32_t val;

	val = sys_read32(TCU + SMMU_CR0);
	val &= ~CR0_SMMUEN;
	sys_write32(val, TCU + SMMU_CR0);
}

static void smmu_event_intr(void)
{
	uint32_t evt[EVTQ_ENTRY_DWORDS * 2];

	do {
		smmu_evtq_dequeue(evt);
		smmu_print_event(evt);
	} while (!smmu_q_empty(&smmu_evtq));
}

static void smmu_gerr_intr(void)
{
	uint32_t gerror, gerrorn, active;

	gerror = sys_read32(TCU + SMMU_GERROR);
	gerrorn = sys_read32(TCU + SMMU_GERRORN);
	active = gerror ^ gerrorn;

	if (!(active & GERROR_ERR_MASK))
		return;

	if (active & GERROR_SFM_ERR) {
		printf("device has entered Service Failure Mode!\n");
		smmu_disable();
	}

	if (active & GERROR_MSI_GERROR_ABT_ERR)
		printf("GERROR MSI write aborted\n");

	if (active & GERROR_MSI_EVTQ_ABT_ERR)
		printf("EVTQ MSI write aborted\n");

	if (active & GERROR_MSI_CMDQ_ABT_ERR)
		printf("CMDQ MSI write aborted\n");

	if (active & GERROR_EVTQ_ABT_ERR)
		printf("EVTQ write aborted -- events may have been lost\n");

	if (active & GERROR_CMDQ_ERR)
		smmu_cmdq_skip_err();

	sys_write32(gerror, TCU + SMMU_GERRORN);
}

static inline void smmu_enable_interrupt(void)
{

	sys_write64(0, TCU + SMMU_GERROR_IRQ_CFG0);
	sys_write32(0, TCU + SMMU_GERROR_IRQ_CFG1);
	sys_write32(0, TCU + SMMU_GERROR_IRQ_CFG2);

	sys_write64(0, TCU + SMMU_EVENTQ_IRQ_CFG0);
	sys_write32(0, TCU + SMMU_EVENTQ_IRQ_CFG1);
	sys_write32(0, TCU + SMMU_EVENTQ_IRQ_CFG2);

	connect_interrupt_with_handler(SMMU_EVT_IRQ, GIC_PRI_DEF, IRQ_TYPE_EDGE, smmu_event_intr, NULL);
	connect_interrupt_with_handler(SMMU_GERR_IRQ, GIC_PRI_DEF, IRQ_TYPE_EDGE, smmu_gerr_intr, NULL);

	smmu_write_ack(SMMU_IRQ_CTRL, SMMU_IRQ_CTRLACK, IRQ_CTRL_GERROR_IRQEN | IRQ_CTRL_EVENTQ_IRQEN);
}

static inline void smmu_enable_queues(void)
{
	sys_write64(smmu_cmdq.base, TCU + SMMU_CMDQ_BASE);
	sys_write32(smmu_cmdq.lc.prod, TCU + SMMU_CMDQ_PROD);
	sys_write32(smmu_cmdq.lc.cons, TCU + SMMU_CMDQ_CONS);
	smmu_write_ack(SMMU_CR0, SMMU_CR0ACK, CR0_CMDQEN);

	sys_write64(smmu_evtq.base, TCU + SMMU_EVENTQ_BASE);
	sys_write32(smmu_evtq.lc.prod, TCU + SMMU_EVENTQ_PROD);
	sys_write32(smmu_evtq.lc.cons, TCU + SMMU_EVENTQ_CONS);
	smmu_write_ack(SMMU_CR0, SMMU_CR0ACK, CR0_EVENTQEN);
}

static inline void smmu_init_strtab(void)
{
	sys_write32(5 << STRTAB_BASE_CFG_LOG2SIZE_S, TCU + SMMU_STRTAB_BASE_CFG);
	sys_write64((uint64_t)st | STRTAB_BASE_RA, TCU + SMMU_STRTAB_BASE);
}

void smmu_enable(void)
{
	smmu_write_ack(SMMU_CR0, SMMU_CR0ACK, CR0_SMMUEN);
}

void smmu_check_early_event(void)
{
	smmu_evtq.lc.prod = sys_read32(TCU + SMMU_EVENTQ_PROD);

	if (smmu_evtq.lc.prod != 0)
		smmu_event_intr();
}

void smmu_attach_ptable(void)
{
	uint64_t val;

	val = cdt[0].cd[0].val[0];
	val |= CD0_VALID;
	cdt[0].cd[0].val[0] = val;
	cdt[0].cd[0].val[1] = SMMU_REGION_0;

	val = cdt[2].cd[1].val[0];
	val |= CD0_VALID;
	cdt[2].cd[1].val[0] = val;
	cdt[2].cd[1].val[1] = SMMU_REGION_1 + CHIPLET_BASE_ADDRESS;

#ifdef __TEST
	/* SID:0, SSID:1 */
	val = cdt[0].cd[1].val[0];
	val |= CD0_VALID;
	cdt[0].cd[1].val[0] = val;
	cdt[0].cd[1].val[1] = SMMU_REGION_PCIE + CHIPLET_BASE_ADDRESS;

	/* SID:8, SSID:1 */
	val = cdt[8].cd[1].val[0];
	val |= CD0_VALID;
	cdt[8].cd[1].val[0] = val;
	cdt[8].cd[1].val[1] = SMMU_REGION_PCIE + CHIPLET_BASE_ADDRESS;

	/* SID:16, SSID:1 */
	val = cdt[16].cd[1].val[0];
	val |= CD0_VALID;
	cdt[16].cd[1].val[0] = val;
	cdt[16].cd[1].val[1] = SMMU_REGION_PCIE + CHIPLET_BASE_ADDRESS;
#endif

	smmu_invalidate_all_sid();
}

int smmu_init(void)
{
	mtx = xSemaphoreCreateMutex();

	st = (struct stream_table *)(ST_ADDR + CHIPLET_BASE_ADDRESS);
	cdt = (struct cd_tables *)(CDT_ADDR + CHIPLET_BASE_ADDRESS);

	sys_write32(0x0, TCU + SMMU_CR0);

	smmu_init_strtab();

	smmu_enable_interrupt();

	smmu_init_queues();

	smmu_enable_queues();

	smmu_invalidate_all_sid();

	smmu_tlbi_all();

	//smmu_create_ptables();

	for (uint64_t sid = 0; sid <= 4; sid++) {
		smmu_init_cd(cdt[sid].cd);
		smmu_init_ste(sid);
	}

	//smmu_attach_ptable();

	smmu_enable();

	return 0;
}

#ifndef ZEBU_POC
#if defined(__RUN_RTOS)
DRIVER_INIT_ENTRY_DEFINE(4, smmu_init);
#endif
#endif /* ZEBU_POC */
