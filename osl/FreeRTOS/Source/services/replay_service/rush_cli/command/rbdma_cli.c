/*
 * [Rebellions Inc.]("Rebellions") CONFIDENTIAL
 * Unpublished Copyright (c) 2021-2026 [Rebellions Inc.], All Rights Reserved.
 *
 * NOTICE: All information contained herein is, and remains the property of Rebellions.
 * The intellectual and technical concepts contained herein are proprietary to Rebellions
 * and may be covered by Republic of Korea, U.S., and other countries' Patents, patents
 * in process, and are protected by trade secret or copyright law.
 *
 * Dissemination of this information or reproduction of this material is strictly forbidden
 * unless prior written permission is obtained from Rebellions. Access to the source code
 * contained herein is hereby forbidden to anyone except current Rebellions employees, managers
 * or contractors who have executed Confidentiality and Non-disclosure agreements explicitly
 * covering such access.
 *
 * The copyright notice above does not evidence any actual or intended publication or disclosure
 * of this source code, which includes information that is confidential and/or proprietary, and
 * is a trade secret, of Rebellions.
 *
 * ANY REPRODUCTION, MODIFICATION, DISTRIBUTION, PUBLIC PERFORMANCE, OR PUBLIC DISPLAY OF OR
 * THROUGH USE OF THIS SOURCE CODE WITHOUT THE EXPRESS WRITTEN CONSENT OF REBELLIONS IS STRICTLY
 * PROHIBITED, AND IN VIOLATION OF APPLICABLE LAWS AND INTERNATIONAL TREATIES. THE RECEIPT OR
 * POSSESSION OF THIS SOURCE CODE AND/OR RELATED INFORMATION DOES NOT CONVEY OR IMPLY ANY RIGHTS
 * TO REPRODUCE, DISCLOSE OR DISTRIBUTE ITS CONTENTS, OR TO MANUFACTURE, USE, OR SELL ANYTHING
 * THAT IT MAY DESCRIBE, IN WHOLE OR IN PART.
 */

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "system_api.h"

#include "rl_utils.h"
#include "argparse.h"

#include "rush_cli_util.h"
#include "rush_cli_msg_buf.h"
#include "rush_cli.h"

/*
 * RBDMA Register Map
 */
#define CHIPLET_OFFSET_BIT	37
#define RBDMA_BASE_ADDR		0x1FF3700000ull

#define CDMA_GLOBAL_OFF		0x00000000
#define CDMA_TASK_OFF		0x00000200
#define CDMA_DPLOG_OFF		0x00000400
#define CDMA_TSYNC_OFF		0x00000800

#define EDMA_GLOBAL_OFF		0x00008000

#define CDMA_GLOBAL_BASE_ADDR	(RBDMA_BASE_ADDR + CDMA_GLOBAL_OFF)
#define CDMA_TASK_BASE_ADDR		(RBDMA_BASE_ADDR + CDMA_TASK_OFF)
#define CDMA_DPLOG_BASE_ADDR	(RBDMA_BASE_ADDR + CDMA_DPLOG_OFF)
#define CDMA_TSYNC_BASE_ADDR	(RBDMA_BASE_ADDR + CDMA_TSYNC_OFF)

#define EDMA_GLOBAL_BASE_ADDR	(RBDMA_BASE_ADDR + EDMA_GLOBAL_OFF)

/* CDMA GLOBAL */
#define IP_INFO2_REG_OFF			0x008
#define CL_ID_MASK					RL_GENMASK(7, 0)

#define IP_INFO3_REG_OFF			0x00C
#define NUM_OF_EXECUTER_MASK		RL_GENMASK(15, 8)

#define STOP_RESUME_KILL_OFF		0x1C0
#define STOP_BIT					RL_BIT(0)
#define RESUME_BIT					RL_BIT(1)
#define KILL_BIT					RL_BIT(2)
#define KILL_LEVEL_BIT				RL_BIT(3)

#define TASK_KILL_ID_OFF			0x1C4
#define TASK_KILL_STATUS_OFF		0x1C8

/* CDMA TASK */
#define TD_PTID_INIT_OFF			0x000
#define FUNC_ID_MASK				RL_GENMASK(3, 0)
#define CTX_ID_MASK					RL_GENMASK(11, 4)
#define THREAD_ID_MASK				RL_GENMASK(15, 12)
#define CMD_ID_MASK					RL_GENMASK(31, 16)

#define TD_SRCADDRESS_OR_CONST_OFF	0x004

#define TD_DESTADDRESS_OFF			0x008

#define TD_SIZEOF128BLOCK_OFF		0x00C

#define TD_TSYNC_CONF_MASK_OFF		0x010
#define GET_DNC_MASK				RL_GENMASK(15, 0)
#define PUT_DNC_MASK				RL_GENMASK(31, 16)

#define TD_SYNC_CONF_GIDX_OFF		0x014
#define GET_TSYNC_GIDX_MASK			RL_GENMASK(6, 0)
#define GET_TSYNC_EN_BIT			RL_BIT(7)
#define PUT_TSYNC_GIDX_MASK			RL_GENMASK(14, 8)
#define PUT_TSYNC_EN_BIT			RL_BIT(15)
#define GET_LSYNC_GIDX_MASK			RL_GENMASK(21, 16)
#define GET_LSYNC_EN_BIT			RL_BIT(22)
#define GET_RLSYNC_EN_BIT			RL_BIT(23)
#define PUT_LSYNC_GIDX_MASK			RL_GENMASK(29, 24)
#define PUT_LSYNC_EN_BIT			RL_BIT(30)
#define PUT_RLSYNC_EN_BIT			RL_BIT(31)

#define TD_RUN_CONF0_OFF			0x018
#define TASK_TYPE_MASK				RL_GENMASK(3, 0)
enum td_run_task_type {
	TASK_TYPE_OTO	= 0x00,		/* one to one transfer */
	TASK_TYPE_CST	= 0x01,		/* constant copy */
	TASK_TYPE_GTH	= 0x02,		/* gather */
	TASK_TYPE_SCT	= 0x03,		/* scatter */
	TASK_TYPE_GTHR	= 0x06,		/* gather with regular ( fixed size and fixed step(stride) */
	TASK_TYPE_SCTR	= 0x07,		/* scatter with regular ( fixed size and fixed step(stride)) */
	TASK_TYPE_PTL	= 0x08,		/* page table loading */
	TASK_TYPE_IVL	= 0x09,		/* page table invalidation */
	TASK_TYPE_VCM	= 0x0A,		/* DNC Virtual to Physical core-ID mapping table loading */
	TASK_TYPE_DUM	= 0x0B,		/* Dummy task (this task does not transfer to eDMA) */
	TASK_TYPE_DAS	= 0xC,		/* Data shift */
};

#define SPLIT_GRANULE_L2_MASK		RL_GENMASK(7, 4)
#define EXT_NUM_OF_CHUNK_MASK		RL_GENMASK(19, 8)
#define SRC_ADDR_MSB_MASK			RL_GENMASK(21, 20)
#define DST_ADDR_MSB_MASK			RL_GENMASK(23, 22)
#define TSYNC_DNC_CODE_MASK			RL_GENMASK(27, 24)
#define EXT_DNC_MASK				RL_GENMASK(30, 28)
#define FID_MAX_BIT					RL_BIT(31)

#define TD_RUN_CONF1_OFF			0x01C
#define INTR_DISABLE_BIT			RL_BIT(0)
#define EN_DONERPT_MST_BIT			RL_BIT(1)
#define EN_INVALID_PT_BIT			RL_BIT(2)
#define NO_TLB_BIT					RL_BIT(3)
#define MAP_LVL_MASK				RL_GENMASK(5, 4)
#define IV_LVL_MASK					RL_GENMASK(7, 6)
#define PTNUM_OR_V2PNUM_MASK		RL_GENMASK(15, 8)
#define READ_BL_MASK				RL_GENMASK(17, 16)
#define WRITE_BL_MASK				RL_GENMASK(19, 18)
#define TE_MASK						RL_GENMASK(27, 20)
#define READ_QOS_BIT				RL_BIT(28)
#define WRITE_QOS_BIT				RL_BIT(29)
#define TD_MST_BIT					RL_BIT(30)
#define QUEUE_TYPE_BIT				RL_BIT(31)

#define TDE_RLSYNC_CONF_MASK_OFF	0x078
#define GET_RBDMA_MASK				RL_GENMASK(3, 0)
#define PUT_RBDMA_MASK				RL_GENMASK(11, 8)

/* CDMA DPLog */
#define DPLOG_CLOG_CLEAR_OFF		0x000
#define DPLOG_CLEAR_BIT				RL_BIT(0)

#define DPLOG_CONTROL_OFF			0x110
#define DPLOG_ENABLE_BIT			RL_BIT(0)
#define DPLOG_RESET_TIMER_BIT		RL_BIT(1)
#define DPLOG_CLEAR_BUFFER_BIT		RL_BIT(2)
#define DPLOG_RESET_DUMP_BIT		RL_BIT(3)

/* CDMA TSYNC */
#define TSYNC_DNC_GET_INFO_OFF		0x024
#define DNCID_MASK					RL_GENMASK(6, 0)
#define GIDX_MASK					RL_GENMASK(12, 8)
#define P_TASKID_MASK				RL_GENMASK(31, 16)

/* EDMA GLOBAL */
#define EDMA_TASK_KILL_CMD_OFF		0x064
#define KILL_CMD_RUN_BIT			RL_BIT(0)
#define KILL_CMD_LEVEL_MASK			RL_GENMASK(31, 28)

#define EDMA_TASK_KILL_STATUS_OFF	0x068
#define KILL_DONE_BIT				RL_BIT(0)

#define CL_ADDR_OFFSET(cl)			((uint64_t)(cl) << CHIPLET_OFFSET_BIT)

/* RBDMA register helper function */
static inline void write_cdma_global_reg(uint32_t cl, uint32_t offset, uint32_t val)
{
	uint64_t addr = CL_ADDR_OFFSET(cl) + CDMA_GLOBAL_BASE_ADDR + offset;

	rl_writel(val, (void __iomem *)addr);
}

static inline uint32_t read_cdma_global_reg(uint32_t cl, uint32_t offset)
{
	uint64_t addr = CL_ADDR_OFFSET(cl) + CDMA_GLOBAL_BASE_ADDR + offset;

	return rl_readl((void __iomem *)addr);
}

#define WRITE_CDMA_GLOBAL(cl, offset, val) write_cdma_global_reg(cl, offset, val)
#define READ_CDMA_GLOBAL(cl, offset) read_cdma_global_reg(cl, offset)

static inline void write_cdma_task_reg(uint32_t cl, uint32_t offset, uint32_t val)
{
	uint64_t addr = CL_ADDR_OFFSET(cl) + CDMA_TASK_BASE_ADDR + offset;

	rl_writel(val, (void __iomem *)addr);
}

static inline uint32_t read_cdma_task_reg(uint32_t cl, uint32_t offset)
{
	uint64_t addr = CL_ADDR_OFFSET(cl) + CDMA_TASK_BASE_ADDR + offset;

	return rl_readl((void __iomem *)addr);
}

#define WRITE_CDMA_TASK(cl, offset, val) write_cdma_task_reg(cl, offset, val)
#define READ_CDMA_TASK(cl, offset) read_cdma_task_reg(cl, offset)

static inline void write_cdma_dplog_reg(uint32_t cl, uint32_t offset, uint32_t val)
{
	uint64_t addr = CL_ADDR_OFFSET(cl) + CDMA_DPLOG_BASE_ADDR + offset;

	rl_writel(val, (void __iomem *)addr);
}

static inline uint32_t read_cdma_dplog_reg(uint32_t cl, uint32_t offset)
{
	uint64_t addr = CL_ADDR_OFFSET(cl) + CDMA_DPLOG_BASE_ADDR + offset;

	return rl_readl((void __iomem *)addr);
}

#define WRITE_CDMA_DPLOG(cl, offset, val) write_cdma_dplog_reg(cl, offset, val)
#define READ_CDMA_DPLOG(cl, offset) read_cdma_dplog_reg(cl, offset)

static inline void write_cdma_tsync_reg(uint32_t cl, uint32_t offset, uint32_t val)
{
	uint64_t addr = CL_ADDR_OFFSET(cl) + CDMA_TSYNC_BASE_ADDR + offset;

	rl_writel(val, (void __iomem *)addr);
}

static inline uint32_t read_cdma_tsync_reg(uint32_t cl, uint32_t offset)
{
	uint64_t addr = CL_ADDR_OFFSET(cl) + CDMA_TSYNC_BASE_ADDR + offset;

	return rl_readl((void __iomem *)addr);
}

#define WRITE_CDMA_TSYNC(cl, offset, val) write_cdma_tsync_reg(cl, offset, val)
#define READ_CDMA_TSYNC(cl, offset) read_cdma_tsync_reg(cl, offset)

static inline void write_edma_global_reg(uint32_t cl, uint32_t te_idx,
										 uint32_t offset, uint32_t val)
{
	uint64_t addr = CL_ADDR_OFFSET(cl) + EDMA_GLOBAL_BASE_ADDR + (te_idx << 12) + offset;

	rl_writel(val, (void __iomem *)addr);
}

static inline uint32_t read_edma_global_reg(uint32_t cl, uint32_t te_idx, uint32_t offset)
{
	uint64_t addr = CL_ADDR_OFFSET(cl) + EDMA_GLOBAL_BASE_ADDR + (te_idx << 12) + offset;

	return rl_readl((void __iomem *)addr);
}

#define WRITE_EDMA_GLOBAL(cl, te_idx, offset, val) write_edma_global_reg(cl, te_idx, offset, val)
#define READ_EDMA_GLOBAL(cl, te_idx, offset) read_edma_global_reg(cl, te_idx, offset)

#define RBDMA_NORMAL_QUEUE_SIZE			64
#define RBDMA_DEFAULT_CMD_ID			0xDD3A

#define PKG_DATA_FMT_FIELD_NUM			3
#define ADDR_128B_LSB_MASK				RL_GENMASK(6, 0)	/* LSB: 128 Bytes */
#define SHIFT_128B						7
#define TARGET_CL_MASK					RL_GENMASK(3, 0)

/* Default values */
#define SPLIT_GRANULE_L2_DEF			0xF
#define GIDX_DEF						0x1
#define TE_MASK_DEF						0xF

#define STATUS_POLLING_CNT				1000

struct rbdma_cli_pkg_opt {
	char *pkg[RBDMA_NORMAL_QUEUE_SIZE];
	uint32_t cnt;
};

struct rbdma_cli_pkg_data {
	uint64_t src;
	uint64_t dst;
	uint32_t size;

	uint32_t repeat_cnt;
};

static int rbdma_cli_pkg_cb_func(struct argparse *self, const struct argparse_option *option,
								 void *ctx, int flags)
{
	int ret;
	char *str;
	size_t len;
	struct rbdma_cli_pkg_opt *opt = ctx;

	str = *(char **)option->value;
	len = strlen(str);
	ret = rush_cli_split_to_fields(str, len, '|', opt->pkg, RBDMA_NORMAL_QUEUE_SIZE);
	if (ret <= 0) {
		argparse_error(self, option, "invalid pkg format\n", flags);
		return ret;
	}
	opt->cnt = ret;

	return 0;
}

static int rbdma_cli_pkg_parse_repeat_cnt(char *str, uint32_t *repeat_cnt)
{
	int ret;
	char *endptr;

	*repeat_cnt = 1;
	if (str[0] == '*') {
		errno = 0;
		ret = strtoul(&str[1], &endptr, 10);
		if (errno || endptr == &str[1])
			return -EINVAL;

		*repeat_cnt = ret;
	}

	return 0;
}

static int rbdma_cli_pkg_parse_cl_mask(char *str, uint32_t *cl_mask)
{
	int ret;
	size_t len;
	char *endptr;

	len = strlen(str);
	if (!len)
		return -EINVAL;

	if (str[0] != '(' || str[len - 1] != ')')
		return -EINVAL;

	/* replace '(' and ')' with 0 in advance to make string parsing easier */
	str[0] = 0;
	str[len - 1] = 0;

	errno = 0;
	ret = strtoul(&str[1], &endptr, 16);
	if (errno || endptr == &str[1])
		return -EINVAL;

	if (!RL_BITFIELD_FIT(TARGET_CL_MASK, ret))
		return -EINVAL;

	*cl_mask = ret;

	return 0;
}

static int rbdma_cli_pkg_parse_data_opt(struct rush_cli_msg_buf *msg_buf,
										char *str, struct rbdma_cli_pkg_data *data)
{
	int ret;
	size_t len;
	uint32_t i;
	uint32_t r_pos;
	uint64_t size;
	char *field[PKG_DATA_FMT_FIELD_NUM];

	if (str[1] != '(') {
		RUSH_CLI_MSG(msg_buf, "failed to find (\r\n");
		return -EINVAL;
	}

	len = strlen(str);

	/* replace '(' and ')' with 0 in advance to make string parsing easier */
	r_pos = 0;
	str[1] = 0;
	for (i = len - 1; i > 0; i--) {
		if (str[i] == ')') {
			str[i] = 0;
			break;
		}
		r_pos++;
	}
	if (i == 0) {
		RUSH_CLI_MSG(msg_buf, "failed to find )\r\n");
		return -EINVAL;
	}

	ret = rush_cli_split_to_fields(&str[2], len - r_pos - 2, ',',
								   field, PKG_DATA_FMT_FIELD_NUM);
	if (ret <= 0 || ret != PKG_DATA_FMT_FIELD_NUM) {
		RUSH_CLI_MSG(msg_buf, "invalid Data package format, ret %d\r\n", ret);
		return -EINVAL;
	}

	data->src = strtoull(field[0], NULL, 0);
	if (data->src & ADDR_128B_LSB_MASK) {
		RUSH_CLI_MSG(msg_buf, "src address should be 128 bytes align\r\n");
		return -EINVAL;
	}

	data->dst = strtoull(field[1], NULL, 0);
	if (data->dst & ADDR_128B_LSB_MASK) {
		RUSH_CLI_MSG(msg_buf, "invalid data dst address, should be 128 bytes align\r\n");
		return -EINVAL;
	}

	ret = rush_cli_parse_size(field[2], &size);
	if (ret < 0) {
		RUSH_CLI_MSG(msg_buf, "failed to parse size\r\n");
		return -EINVAL;
	}
	data->size = (uint32_t)size;

	/* parser repeat count */
	ret = rbdma_cli_pkg_parse_repeat_cnt(&str[len - r_pos], &data->repeat_cnt);
	if (ret < 0) {
		RUSH_CLI_MSG(msg_buf, "failed to parser repeat count\r\n");
		return ret;
	}

	return 0;
}

static inline uint32_t rbdma_read_cdma_num_te(void)
{
	uint32_t val = READ_CDMA_GLOBAL(0, IP_INFO3_REG_OFF);

	return RL_BITFIELD_GET(NUM_OF_EXECUTER_MASK, val);
}

static int rbdma_sw_reset(struct rush_cli_msg_buf *msg_buf, uint32_t cl)
{
	uint32_t i;
	uint32_t val;
	uint32_t timeout;
	uint32_t num_te = rbdma_read_cdma_num_te();

	RUSH_CLI_MSG(msg_buf, "RBDMA SW RESET\r\n");

	/* pause CDMA */
	val = RL_BITFIELD_PREP(STOP_BIT, 1);
	WRITE_CDMA_GLOBAL(cl, STOP_RESUME_KILL_OFF, val);

	/* process kill command to TE0 ~ N */
	val = RL_BITFIELD_PREP(KILL_CMD_RUN_BIT, 1);
	for (i = 0; i < num_te; i++)
		WRITE_EDMA_GLOBAL(cl, i, EDMA_TASK_KILL_CMD_OFF, val);

	/* check TE0 ~ N kill done */
	for (i = 0; i < num_te; i++) {
		timeout = STATUS_POLLING_CNT;
		while (timeout--) {
			val = READ_EDMA_GLOBAL(cl, i, EDMA_TASK_KILL_STATUS_OFF);
			if (RL_BITFIELD_GET(KILL_DONE_BIT, val))
				break;

			udelay(1);
		}
		if (timeout == 0) {
			RUSH_CLI_MSG(msg_buf, "TE%u kill polling timeout\r\n", i);
			return -ETIMEDOUT;
		}
	}

	/* clear Log Manager */
	val = RL_BITFIELD_PREP(DPLOG_CLEAR_BIT, 1);
	WRITE_CDMA_DPLOG(cl, DPLOG_CLOG_CLEAR_OFF, val);

	/* enable Log Manager after clear */
	val = RL_BITFIELD_PREP(DPLOG_ENABLE_BIT, 1) |
		  RL_BITFIELD_PREP(DPLOG_RESET_TIMER_BIT, 1) |
		  RL_BITFIELD_PREP(DPLOG_CLEAR_BUFFER_BIT, 1) |
		  RL_BITFIELD_PREP(DPLOG_RESET_DUMP_BIT, 1);
	WRITE_CDMA_DPLOG(cl, DPLOG_CONTROL_OFF, val);

	/* process kill command to CDMA */
	WRITE_CDMA_GLOBAL(cl, TASK_KILL_ID_OFF, 0x0);
	val = RL_BITFIELD_PREP(KILL_BIT, 1) |
		  RL_BITFIELD_PREP(KILL_LEVEL_BIT, 1);
	WRITE_CDMA_GLOBAL(cl, STOP_RESUME_KILL_OFF, val);

	/* check CDMA kill done */
	timeout = STATUS_POLLING_CNT;
	while (timeout--) {
		val = READ_CDMA_GLOBAL(cl, TASK_KILL_STATUS_OFF);
		if (val)
			break;

		udelay(1);
	}
	if (timeout == 0) {
		RUSH_CLI_MSG(msg_buf, "CDMA kill done polling timeout\r\n");
		return -ETIMEDOUT;
	}

	/* resume CDMA */
	val = RL_BITFIELD_PREP(RESUME_BIT, 1);
	WRITE_CDMA_GLOBAL(cl, STOP_RESUME_KILL_OFF, val);

	return 0;
}

static int rbdma_cli_prog_cmd(int argc, const char **argv, struct rush_cli_msg_buf *msg_buf)
{
	int cl = 0;
	int ret = 0;
	uint32_t val;
	uint32_t i, j;
	uint32_t queue_push_cnt;
	uint32_t repeat_cnt;
	uint32_t cl_mask;
	uint32_t ctx_id = 0;
	uint32_t task_id = RL_BITFIELD_PREP(CMD_ID_MASK, RBDMA_DEFAULT_CMD_ID);
	const char *arg_str;
	struct rbdma_cli_pkg_opt pkg_opt = {0, };
	struct argparse argparse;
	struct argparse_option options[] = {
		OPT_HELP(),
		OPT_INTEGER(0, "cl", &cl, "target chiplet"),
		OPT_STRING(0, "pkg", &arg_str, "RBDMA TD extended package",
				   rbdma_cli_pkg_cb_func, &pkg_opt),
		OPT_END(),
	};
	const char *const usage[] = {
		"prog [args]",
		" $ prog --cl <chiplet> --pkg <RBDMA TD extended packages>",
		" * RBDMA TD extended package format (max package num: 64)",
		"    D(src,dst,size)    - Data package",
		"                         src, dst: address",
		"                         size    : num[k/K/m/M/g/G]",
		"    d                  - Dummy package",
		"    R(Target CL Mask)  - Waiting rlsync",
		"                         Target CL Mask(Hex, 0x1:CL0, ..., 0x8:CL4)",
		"    T(Target CL Mask)  - Waiting tsync and send rlsync to CL",
		"                         Target CL Mask(Hex, 0x1:CL0, ..., 0x8:CL4)",
		"    S                  - Send tsync",
		"    *N                 - Optional, Repeat N time, N is numeric",
		"                         Only valid to 'D' or 'd'",
		"                          d*8                   // programming 8 dummy packages",
		"                          D(src,dst,size)*16    // programming 16 data packages",
		"    |                  - Separator",
		" * Example",
		"  $ rush rbdma prog --cl 1 --pkg R(0x0)|d*24|D(0x3FE4000000,0x1FE4000000,32M)*4",
		"  $ rush rbdma prog --cl 0 --pkg T(0x1)|D(0x1FE4000000,0x3FE4000000,32M)*4|S",
		NULL
	};

	argparse_init(&argparse, options, usage, 0, msg_buf);
	argc = argparse_parse(&argparse, argc, argv);
	if (argc < 0) {
		RUSH_CLI_MSG(msg_buf, "argc: %d\r\n", argc);
		return 0;
	}

	if (cl >= MAX_CHIPLET_COUNT) {
		RUSH_CLI_MSG(msg_buf, "invalid target chiplet\r\n");
		return -EINVAL;
	}

	val = RL_BITFIELD_PREP(CL_ID_MASK, cl);
	WRITE_CDMA_GLOBAL(cl, IP_INFO2_REG_OFF, val);

	queue_push_cnt = 0;
	for (i = 0; i < pkg_opt.cnt; i++) {
		switch (pkg_opt.pkg[i][0]) {
		case 'D':	/* Data */
			struct rbdma_cli_pkg_data data = {0, };

			ret = rbdma_cli_pkg_parse_data_opt(msg_buf, pkg_opt.pkg[i], &data);
			if (ret < 0) {
				RUSH_CLI_MSG(msg_buf, "failed to parse data pkg, ret %d\n", ret);
				goto err;
			}

			if (queue_push_cnt + data.repeat_cnt > RBDMA_NORMAL_QUEUE_SIZE) {
				RUSH_CLI_MSG(msg_buf, "overflow RBDMA queue to push DATA pkg (MAX Queue: 64)\r\n");
				ret = -EOVERFLOW;
				goto err;
			}

			for (j = 0; j < data.repeat_cnt; j++) {
				task_id = RL_BITFIELD_SET(CTX_ID_MASK, ctx_id++, task_id);
				WRITE_CDMA_TASK(cl, TD_PTID_INIT_OFF, task_id);

				WRITE_CDMA_TASK(cl, TD_SRCADDRESS_OR_CONST_OFF, data.src >> SHIFT_128B);
				WRITE_CDMA_TASK(cl, TD_DESTADDRESS_OFF, data.dst >> SHIFT_128B);
				WRITE_CDMA_TASK(cl, TD_SIZEOF128BLOCK_OFF, data.size >> SHIFT_128B);

				WRITE_CDMA_TASK(cl, TD_TSYNC_CONF_MASK_OFF, 0x00);
				WRITE_CDMA_TASK(cl, TD_SYNC_CONF_GIDX_OFF, 0x00);

				val = RL_BITFIELD_PREP(TASK_TYPE_MASK, TASK_TYPE_OTO) |
					  RL_BITFIELD_PREP(SPLIT_GRANULE_L2_MASK, SPLIT_GRANULE_L2_DEF);
				WRITE_CDMA_TASK(cl, TD_RUN_CONF0_OFF, val);

				val = RL_BITFIELD_PREP(NO_TLB_BIT, 1) |
					  RL_BITFIELD_PREP(READ_BL_MASK, 0x03) |
					  RL_BITFIELD_PREP(WRITE_BL_MASK, 0x03) |
					  RL_BITFIELD_PREP(TE_MASK, TE_MASK_DEF);
				WRITE_CDMA_TASK(cl, TD_RUN_CONF1_OFF, val);

				queue_push_cnt++;
			}

			break;
		case 'd':	/* Dummy */
			ret = rbdma_cli_pkg_parse_repeat_cnt(&pkg_opt.pkg[i][1], &repeat_cnt);
			if (ret < 0) {
				RUSH_CLI_MSG(msg_buf, "failed to parse DUMMY pkg, ret %d\n", ret);
				goto err;
			}

			if (queue_push_cnt + repeat_cnt > RBDMA_NORMAL_QUEUE_SIZE) {
				RUSH_CLI_MSG(msg_buf, "overflow RBDMA queue to push DUMMY pkg (MAX Queue: 64)\r\n");
				ret = -EOVERFLOW;
				goto err;
			}

			for (j = 0; j < repeat_cnt; j++) {
				task_id = RL_BITFIELD_SET(CTX_ID_MASK, ctx_id++, task_id);
				WRITE_CDMA_TASK(cl, TD_PTID_INIT_OFF, task_id);

				WRITE_CDMA_TASK(cl, TD_SYNC_CONF_GIDX_OFF, 0x0);

				WRITE_CDMA_TASK(cl, TD_RUN_CONF0_OFF,
									RL_BITFIELD_PREP(TASK_TYPE_MASK, TASK_TYPE_DUM));
				val = RL_BITFIELD_PREP(NO_TLB_BIT, 1) |
					  RL_BITFIELD_PREP(READ_BL_MASK, 0x03) |
					  RL_BITFIELD_PREP(WRITE_BL_MASK, 0x03) |
					  RL_BITFIELD_PREP(TE_MASK, TE_MASK_DEF);
				WRITE_CDMA_TASK(cl, TD_RUN_CONF1_OFF, val);

				queue_push_cnt++;
			}

			break;
		case 'R':	/* Waiting rlsync */
			ret = rbdma_cli_pkg_parse_cl_mask(&pkg_opt.pkg[i][1], &cl_mask);
			if (ret < 0)
				goto err;

			queue_push_cnt++;
			if (queue_push_cnt > RBDMA_NORMAL_QUEUE_SIZE) {
				RUSH_CLI_MSG(msg_buf, "overflow RBDMA queue to push rlsync pkg (MAX Queue: 64)\r\n");
				ret = -EOVERFLOW;
				goto err;
			}

			val = RL_BITFIELD_PREP(GET_RBDMA_MASK, cl_mask);
			WRITE_CDMA_TASK(cl, TDE_RLSYNC_CONF_MASK_OFF, val);

			task_id = RL_BITFIELD_SET(CTX_ID_MASK, ctx_id++, task_id);
			WRITE_CDMA_TASK(cl, TD_PTID_INIT_OFF, task_id);

			val = RL_BITFIELD_PREP(GET_LSYNC_GIDX_MASK, GIDX_DEF) |
				  RL_BITFIELD_PREP(GET_RLSYNC_EN_BIT, 1);
			WRITE_CDMA_TASK(cl, TD_SYNC_CONF_GIDX_OFF, val);

			WRITE_CDMA_TASK(cl, TD_RUN_CONF0_OFF,
								RL_BITFIELD_PREP(TASK_TYPE_MASK, TASK_TYPE_DUM));
			val = RL_BITFIELD_PREP(NO_TLB_BIT, 1) |
				  RL_BITFIELD_PREP(READ_BL_MASK, 0x03) |
				  RL_BITFIELD_PREP(WRITE_BL_MASK, 0x03) |
				  RL_BITFIELD_PREP(TE_MASK, TE_MASK_DEF);
			WRITE_CDMA_TASK(cl, TD_RUN_CONF1_OFF, val);

			break;
		case 'T':	/* Waiting tsync */
			ret = rbdma_cli_pkg_parse_cl_mask(&pkg_opt.pkg[i][1], &cl_mask);
			if (ret < 0)
				goto err;

			queue_push_cnt++;
			if (queue_push_cnt > RBDMA_NORMAL_QUEUE_SIZE) {
				RUSH_CLI_MSG(msg_buf, "overflow RBDMA queue to push tsync pkg (MAX Queue: 64)\r\n");
				ret = -EOVERFLOW;
				goto err;
			}

			val = RL_BITFIELD_PREP(PUT_RBDMA_MASK, cl_mask);
			WRITE_CDMA_TASK(cl, TDE_RLSYNC_CONF_MASK_OFF, val);

			task_id = RL_BITFIELD_SET(CTX_ID_MASK, ctx_id++, task_id);
			WRITE_CDMA_TASK(cl, TD_PTID_INIT_OFF, task_id);

			val = RL_BITFIELD_PREP(GET_DNC_MASK, 0xFFFF);
			WRITE_CDMA_TASK(cl, TD_TSYNC_CONF_MASK_OFF, val);

			val = RL_BITFIELD_PREP(GET_TSYNC_GIDX_MASK, GIDX_DEF) |
				  RL_BITFIELD_PREP(GET_TSYNC_EN_BIT, 1) |
				  RL_BITFIELD_PREP(PUT_LSYNC_GIDX_MASK, GIDX_DEF) |
				  RL_BITFIELD_PREP(PUT_RLSYNC_EN_BIT, 1);
			WRITE_CDMA_TASK(cl, TD_SYNC_CONF_GIDX_OFF, val);

			WRITE_CDMA_TASK(cl, TD_RUN_CONF0_OFF,
								RL_BITFIELD_PREP(TASK_TYPE_MASK, TASK_TYPE_DUM));
			val = RL_BITFIELD_PREP(NO_TLB_BIT, 1) |
				  RL_BITFIELD_PREP(READ_BL_MASK, 0x03) |
				  RL_BITFIELD_PREP(WRITE_BL_MASK, 0x03) |
				  RL_BITFIELD_PREP(TE_MASK, TE_MASK_DEF);
			WRITE_CDMA_TASK(cl, TD_RUN_CONF1_OFF, val);

			break;
		case 'S':	/* Sending tsync */
			val = RL_BITFIELD_PREP(DNCID_MASK, 0x40) |
				  RL_BITFIELD_PREP(GIDX_MASK, GIDX_DEF);
			WRITE_CDMA_TSYNC(cl, TSYNC_DNC_GET_INFO_OFF, val);
			break;
		default:
			RUSH_CLI_MSG(msg_buf, "Invalid pkg format\r\n");
			ret = -EINVAL;
			goto err;
		}
	}

err:
	if (ret < 0) {
		RUSH_CLI_MSG(msg_buf, "Failed to program RBDMA TD extended package\n");
		rbdma_sw_reset(msg_buf, cl);
	}

	return ret;
}

static int rbdma_cli_reset_cmd(int argc, const char **argv, struct rush_cli_msg_buf *msg_buf)
{
	int cl = 0;
	struct argparse argparse;
	struct argparse_option options[] = {
		OPT_HELP(),
		OPT_INTEGER(0, "cl", &cl, "target chiplet"),
		OPT_END(),
	};

	const char *const usage[] = {
		"reset [args]",
		" $ reset --cl <chiplet>",
		NULL
	};

	argparse_init(&argparse, options, usage, 0, msg_buf);
	argc = argparse_parse(&argparse, argc, argv);
	if (argc < 0)
		return 0;

	if (cl >= MAX_CHIPLET_COUNT) {
		RUSH_CLI_MSG(msg_buf, "invalid target chiplet\r\n");
		return -EINVAL;
	}

	rbdma_sw_reset(msg_buf, cl);

	return 0;
}

static struct rush_cli_sub_cmd rbdma_cmd_tbl[] = {
	{"prog", "programming RBDMA TD Ext. package", rbdma_cli_prog_cmd},
	{"reset", "Reset programmed RBDMA TD Ext. package", rbdma_cli_reset_cmd},
};

int rbdma_cli(int argc, const char **argv, const size_t msg_buf_size)
{
	int ret;
	struct rush_cli_msg_buf msg_buf;
	static const char *const usage[] = {
		"rbdma {command} [args]",
		NULL,
	};

	if (msg_buf_size) {
		ret = rush_cli_msg_buf_init(&msg_buf, msg_buf_size);
		if (ret < 0) {
			return ret;
		}
	}

	ret = rush_cli_cmd_proc(argc, argv, "RBDMA Operation", usage,
							rbdma_cmd_tbl, ARRAY_SIZE(rbdma_cmd_tbl),
							msg_buf_size ? &msg_buf : NULL);

	if (msg_buf_size) {
		if (msg_buf.pos)
			rush_cli_msg_buf_flush(&msg_buf);
		rush_cli_msg_buf_deinit(&msg_buf);
	}

	return ret;
}

int rbdma_cli_init(void)
{
	return 0;
}
