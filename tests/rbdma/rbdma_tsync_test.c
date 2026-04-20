#include "rbdma_tsync_test.h"
#include "rl_utils.h"
#include "core_timer.h"
#include "system_api.h"
#include "cache.h"
#include "rebel_h_platform.h"

static uint64_t rbdma_base = 0x1FF3700000; //NBUS_L_RBDMA_CFG_BASE

#define CDMA_GLOBAL						(rbdma_base + ADDR_OFFSET_RBDMA_CDMA_GLOBAL)
#define CDMA_TASK						(rbdma_base + ADDR_OFFSET_RBDMA_CDMA_TASK)
#define CDMA_PT							(rbdma_base + ADDR_OFFSET_RBDMA_CDMA_PT)
#define CDMA_DPLOG						(rbdma_base + ADDR_OFFSET_RBDMA_CDMA_DPROFILE)
#define CDMA_TSYNC						(rbdma_base + ADDR_OFFSET_RBDMA_CDMA_TSYNC)
#define CDMA_DBG_UTLB					(rbdma_base + ADDR_OFFSET_RBDMA_CDMA_DBG_UTLB)
#define CDMA_DBG_TSYNC					(rbdma_base + ADDR_OFFSET_RBDMA_CDMA_DBG_TSYNC)
#define CDMA_AUTO_FETCH					(rbdma_base + ADDR_OFFSET_RBDMA_CDMA_AUTO_FETCH)

#define CDMA_TASK_WRITE(val, offset)	rl_writel_relaxed(val, (void *)(CDMA_TASK + (offset)))

#define CDMA_GLOBAL_WRITE(val, offset)	rl_writel_relaxed(val, (void *)(CDMA_GLOBAL + (offset)))
#define CDMA_GLOBAL_READ(offset)		rl_readl_relaxed((void *)(CDMA_GLOBAL + (offset)))

#define CDMA_DPLOG_WRITE(val, offset)	rl_writel_relaxed(val, (void *)(CDMA_DPLOG + (offset)))
#define CDMA_DPLOG_READ(offset)			rl_readl_relaxed((void *)(CDMA_DPLOG + (offset)))

#define CDMA_TSYNC_WRITE(val, offset)	rl_writel_relaxed(val, (void *)(CDMA_TSYNC + (offset)))
#define CDMA_TSYNC_READ(offset)			rl_readl_relaxed((void *)(CDMA_TSYNC + (offset)))

#define CDMA_AUTO_FETCH_WRITE(val, offset)  rl_writel_relaxed(val, (void *)(CDMA_AUTO_FETCH + (offset)))
#define CDMA_AUTO_FETCH_READ(offset)		rl_readl_relaxed((void *)(CDMA_AUTO_FETCH + (offset)))

// generate seed on input state (Splitmix64)
static uint64_t _gen_states(uint64_t *state)
{
	*state += 0x9e3779b97f4a7c15ULL;
	uint64_t z = *state;

	z = (z ^ (z >> 30)) * 0xbf58476d1ce4e5b9;
	z = (z ^ (z >> 27)) * 0x94d049bb133111eb;
	return z ^ (z >> 31);
}

static inline uint64_t rol64(uint64_t v, int r)
{ return (v << r) | (v >> (64 - r)); }

// generate 64 bit prandom value from states
static uint64_t _gen_64b_rand(uint64_t s[4])
{
	uint64_t const r = rol64(s[0] + s[3], 23) + s[0];
	uint64_t const t = s[1] << 17;

	s[2] ^= s[0];
	s[3] ^= s[1];
	s[1] ^= s[2];
	s[0] ^= s[3];
	s[2] ^= t;
	s[3] = rol64(s[3], 45);

	return r;
}

// User CPU counter as seed to generate pseudo random pattern of input size
static void _rand_fill(void *addr, size_t size)
{
	// Add size/addr limit
	uint64_t state[4];
	uint64_t seed = get_current_count();

	uint8_t *ptr = addr;

	for (int i = 0; i < 4; i++)
		state[i] = _gen_states(&seed);

	printf("\r\nGenerating pseudo-random pattern of size %d (memcpy'd as %d 64 bit chunks)"
		   " at %p (seed: %lx %lx %lx %lx)\n",
		   size, size / 8, addr, state[0], state[1], state[2], state[3]);

	// Assume size is 64bit_aligned
	for (int i = 0; i < (size / 8); i++, ptr += 8) {
		uint64_t chunk = _gen_64b_rand(state);

		memcpy(ptr, &chunk, 8);
		// if ((i % 1000) == 0)
		// printf(".");
	}

	clean_dcache_range((uintptr_t)addr, size);
}

static int _basic_test_compare(uint64_t src_addr, uint64_t dst_addr, uint32_t size)
{
	volatile uint32_t *p_golden = (volatile uint32_t *)src_addr;
	volatile uint32_t *p_result = (volatile uint32_t *)dst_addr;

	inv_dcache_range((uintptr_t)p_golden, size);
	inv_dcache_range((uintptr_t)p_result, size);

	for (int i = 0; i < size / sizeof(uint32_t); i++) {
		if (*p_result != *p_golden) {
			printf("--------------------------------------------------\r\n");
			printf("The value is different %#x(result) %#x(golden) , addr is %#lx\r\n",
				   *p_result, *p_golden, dst_addr + i * 4);
			printf("--------------------------------------------------\r\n");
			return -1;
		} else {
			// if (i % 1024 == 0) {
			//	printf(".");
			// }
		}
		p_result++;
		p_golden++;
	}
	printf("\r\n");

	return 0;
}

static uint32_t _rbdma_set_max_perf_mode(uint32_t sp_ratio)
{
	union rbdma_global_config_cdma_opmode0 config_cdma_opmode = {0x0, };
	uint32_t prev_bits = 0;

	prev_bits = CDMA_GLOBAL_READ(ADDR_OFFSET_RBDMA_GLOBAL_CONFIG_CDMA_OPMODE0);
	config_cdma_opmode.mp_hash_pos1 = 0xd;
	config_cdma_opmode.mp_hash_pos0 = 0xc;
	config_cdma_opmode.write_bl = 0x2;
	config_cdma_opmode.read_bl = 0x2;
	config_cdma_opmode.split_granule = (sp_ratio & 0x2f);
	config_cdma_opmode.max_perf = 0x1;
	CDMA_GLOBAL_WRITE(config_cdma_opmode.bits, ADDR_OFFSET_RBDMA_GLOBAL_CONFIG_CDMA_OPMODE0);

	return prev_bits;
}

static void _generate_rbdma_task_tsync(uint32_t task_id, uint64_t src_addr, uint64_t dst_addr, uint32_t transfer_size,
									   uint32_t split_granule, uint8_t task_type, uint32_t te_mask, uint32_t is_tsync)
{
	union rbdma_td_ptid_init	ptid_init = {0x0, };
	union rbdma_td_srcaddress_or_const  srcaddr = {0x0, };
	union rbdma_td_destaddress  destaddr = {0x0, };
	union rbdma_td_sizeof128block   trs_size = {0x0, };
	union rbdma_td_tsync_conf_mask  tsync_conf_mask = {0x0, };
	union rbdma_td_sync_conf_gidx   sync_conf_gidx = {0x0, };
	union rbdma_td_run_conf0		run_conf0 = {0x0, };
	union rbdma_td_run_conf1		run_conf1 = {0x0, };

	ptid_init.bits = task_id;
	printf("\r\n%-18s : 0x%08x\r\n", "ptid_init", ptid_init.bits);
	CDMA_TASK_WRITE(ptid_init.bits, ADDR_OFFSET_RBDMA_TD_PTID_INIT);

	srcaddr.bits = src_addr >> 7;
	printf("%-18s : 0x%08x (0x%lx)\r\n", "srcaddr", srcaddr.bits, src_addr);
	CDMA_TASK_WRITE(srcaddr.bits, ADDR_OFFSET_RBDMA_TD_SRCADDRESS_OR_CONST);

	destaddr.bits = dst_addr >> 7;
	printf("%-18s : 0x%08x (0x%lx)\r\n", "destaddr", destaddr.bits, dst_addr);
	CDMA_TASK_WRITE(destaddr.bits, ADDR_OFFSET_RBDMA_TD_DESTADDRESS);

	trs_size.bits = transfer_size >> 7;
	printf("%-18s : 0x%08x (0x%x)\r\n", "trs_size", trs_size.bits, transfer_size);
	CDMA_TASK_WRITE(trs_size.bits, ADDR_OFFSET_RBDMA_TD_SIZEOF128BLOCK);

	if (is_tsync == 1) {
		tsync_conf_mask.bits = 0x1;
		printf("%-18s : 0x%08x\r\n", "tsync_conf_mask", tsync_conf_mask.bits);
		CDMA_TASK_WRITE(tsync_conf_mask.bits, ADDR_OFFSET_RBDMA_TD_TSYNC_CONF_MASK);

		sync_conf_gidx.bits = 0x8f;
		printf("%-18s : 0x%08x\r\n", "sync_conf_gidx", sync_conf_gidx.bits);
		CDMA_TASK_WRITE(sync_conf_gidx.bits, ADDR_OFFSET_RBDMA_TD_SYNC_CONF_GIDX);
	} else {
		tsync_conf_mask.bits = 0x0;
		printf("%-18s : 0x%08x\r\n", "tsync_conf_mask", tsync_conf_mask.bits);
		CDMA_TASK_WRITE(tsync_conf_mask.bits, ADDR_OFFSET_RBDMA_TD_TSYNC_CONF_MASK);

		sync_conf_gidx.bits = 0x0;
		printf("%-18s : 0x%08x\r\n", "sync_conf_gidx", sync_conf_gidx.bits);
		CDMA_TASK_WRITE(sync_conf_gidx.bits, ADDR_OFFSET_RBDMA_TD_SYNC_CONF_GIDX);
	}

	run_conf0.task_type = task_type;
	run_conf0.split_granule_l2 = split_granule;
	run_conf0.ext_num_of_chunk = 0x0;
	printf("%-18s : 0x%08x\r\n", "run_conf0", run_conf0.bits);
	CDMA_TASK_WRITE(run_conf0.bits, ADDR_OFFSET_RBDMA_TD_RUN_CONF0);

	run_conf1.no_tlb	= 1;
	run_conf1.read_bl	= 3;
	run_conf1.write_bl	= 3;
	run_conf1.te_mask = te_mask;
	if (is_tsync == 1) {
		run_conf1.intr_disable = 1;
	}

	printf("%-18s : 0x%08x\r\n", "run_conf1", run_conf1.bits);
	CDMA_TASK_WRITE(run_conf1.bits, ADDR_OFFSET_RBDMA_TD_RUN_CONF1);
}

static void _rbdma_tsync_by_cp(void)
{
	CDMA_TSYNC_WRITE(0xf40, 0x24);
}

#define RBDMA_TIMEOUT_THRESHOLD 3000000
static uint32_t _rbdma_done_acc_count(uint32_t cl_id, uint32_t count)
{
	union rbdma_clog_num_nrm_tdone_tstc0	tdone = {0,};
	uint32_t timeout;
	uint32_t status = 1;

	timeout = 0;
	do {
		tdone.bits = CDMA_DPLOG_READ(ADDR_OFFSET_RBDMA_CLOG_NUM_NRM_TDONE_TSTC0);

		if (tdone.na == count) {
			status = 0;
		}

		if (++timeout > RBDMA_TIMEOUT_THRESHOLD) {
			printf("RBDMA[%02d] Timeout Error! ACC:[%d] ACC:[%d]\r\n", tdone.bits, count);
			return 1;
		}
		udelay(1);
	} while (status);

	printf("cl%02d _rbdma_done_acc_count():%d\r\n", cl_id, count);
	return 0;
}

static void _rbdma_done_clear(uint32_t cl_id)
{
	union rbdma_clog_clear clog_clear = {0,};

	clog_clear.clear = 1;
	CDMA_DPLOG_WRITE(clog_clear.bits, ADDR_OFFSET_RBDMA_CLOG_CLEAR);

	printf("CL%02d RBDMA done accumulated counter cleared.\r\n", cl_id);
}

static void _rbdma_set_global_config_cdma_opmode0(uint32_t bits)
{
	CDMA_GLOBAL_WRITE(bits, ADDR_OFFSET_RBDMA_GLOBAL_CONFIG_CDMA_OPMODE0);
}

//=================================================================================================
//	RBDMA Test
//=================================================================================================

int rbdma_test_dram_2_shm(void)
{
	uint32_t trs_size = 0x01000000;
	uint64_t src_addr0 = 0x60000000 + (CHIPLET_ID * 0x2000000000);
	uint64_t dst_addr0 = 0x1fe5000000 + (CHIPLET_ID * 0x2000000000);
	uint64_t src_addr1 = 0x60000000 + 0x01000000  + (CHIPLET_ID * 0x2000000000);
	uint64_t dst_addr1 = 0x1fe7000000  + (CHIPLET_ID * 0x2000000000);
	uint32_t prev_global_config_cdma_opmode0_bits = 0;

	printf("rbdma_dram_2_shm\r\n");

	_rand_fill((void *)src_addr0, trs_size);
	_rand_fill((void *)src_addr1, trs_size);

	prev_global_config_cdma_opmode0_bits = _rbdma_set_max_perf_mode(0x7);

	printf("\r\n[dram -> dcl0_shm & dcl1_shm]\r\n");
	_generate_rbdma_task_tsync(0xDD3A0000, src_addr0, dst_addr0, trs_size, 0x7, 0, 0xf, 1);
	_generate_rbdma_task_tsync(0xDD3A0001, src_addr1, dst_addr1, trs_size, 0x7, 0, 0xf0, 0);
	_rbdma_tsync_by_cp();
	_rbdma_done_acc_count(0, 2);
	_rbdma_done_clear(0);	// cl0

	_rbdma_set_global_config_cdma_opmode0(prev_global_config_cdma_opmode0_bits);

	if (_basic_test_compare(src_addr0, dst_addr0, trs_size) < 0)
		return true;
	if (_basic_test_compare(src_addr1, dst_addr1, trs_size) < 0)
		return true;

	return false;
}

int rbdma_test_shm_2_dram(void)
{
	uint32_t trs_size = 0x01000000;
	uint64_t src_addr0 = 0x1fe5000000 + (CHIPLET_ID * 0x2000000000);
	uint64_t dst_addr0 = 0x60000000 + (CHIPLET_ID * 0x2000000000);
	uint64_t src_addr1 = 0x1fe7000000 + (CHIPLET_ID * 0x2000000000);
	uint64_t dst_addr1 = 0x60000000 + 0x01000000 + (CHIPLET_ID * 0x2000000000);
	uint32_t prev_global_config_cdma_opmode0_bits = 0;

	printf("rbdma_shm_2_dram\r\n");

	_rand_fill((void *)src_addr0, trs_size);
	_rand_fill((void *)src_addr1, trs_size);

	prev_global_config_cdma_opmode0_bits = _rbdma_set_max_perf_mode(0x7);

	printf("\r\n[dcl0_shm & dcl1_shm -> dram]\r\n");
	_generate_rbdma_task_tsync(0xDD3A0000, src_addr0, dst_addr0, trs_size, 0x7, 0, 0xf, 1);
	_generate_rbdma_task_tsync(0xDD3A0001, src_addr1, dst_addr1, trs_size, 0x7, 0, 0xf0, 0);
	_rbdma_tsync_by_cp();
	_rbdma_done_acc_count(0, 2); // cl0 , count is
	_rbdma_done_clear(0);	// cl0

	_rbdma_set_global_config_cdma_opmode0(prev_global_config_cdma_opmode0_bits);

	if (_basic_test_compare(src_addr0, dst_addr0, trs_size) < 0)
		return true;
	if (_basic_test_compare(src_addr1, dst_addr1, trs_size) < 0)
		return true;

	return false;
}

int rbdma_test_dram_2_dram(void)
{
	uint32_t trs_size = 0x01000000;
	uint64_t src_addr0 = 0x50000000 + (CHIPLET_ID * 0x2000000000);
	uint64_t dst_addr0 = 0x60000000 + (CHIPLET_ID * 0x2000000000);
	uint64_t src_addr1 = 0x70000000 + (CHIPLET_ID * 0x2000000000);
	uint64_t dst_addr1 = 0x80000000 + (CHIPLET_ID * 0x2000000000);
	uint32_t prev_global_config_cdma_opmode0_bits = 0;

	printf("rbdma_dram_2_dram\r\n");

	_rand_fill((void *)src_addr0, trs_size);
	_rand_fill((void *)src_addr1, trs_size);

	prev_global_config_cdma_opmode0_bits = _rbdma_set_max_perf_mode(0x7);

	printf("\r\n[dram -> dram]\r\n");
	_generate_rbdma_task_tsync(0xDD3A0000, src_addr0, dst_addr0, trs_size, 0x7, 0, 0xf, 1);
	_generate_rbdma_task_tsync(0xDD3A0001, src_addr1, dst_addr1, trs_size, 0x7, 0, 0xf0, 0);
	_rbdma_tsync_by_cp();
	_rbdma_done_acc_count(0, 2); // cl0 , count is
	_rbdma_done_clear(0);	// cl0

	_rbdma_set_global_config_cdma_opmode0(prev_global_config_cdma_opmode0_bits);

	if (_basic_test_compare(src_addr0, dst_addr0, trs_size) < 0)
		return true;
	if (_basic_test_compare(src_addr1, dst_addr1, trs_size) < 0)
		return true;

	return false;
}
