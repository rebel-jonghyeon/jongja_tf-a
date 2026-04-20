#include <assert.h>
#include <errno.h>
#include <inttypes.h>
#include <limits.h>
#include <stdint.h>

#include "platform_def.h"
#include <lib/sic/sic.h>

#define CMRT_SIC_BASE				(0x1E00400000ULL)

#define R_SOC_INTERRUPT_OUT			(0x500UL)

#define R_ESW2HLOS0_D0				(0x600UL)
#define R_ESW2HLOS0_D1				(0x604UL)
#define R_ESW2HLOS0_D2				(0x608UL)
#define R_ESW2HLOS0_D3				(0x60CUL)
#define R_HLOS2ESW0_D0				(0x610UL)
#define R_HLOS2ESW0_D1				(0x614UL)
#define R_HLOS2ESW0_D2				(0x618UL)
#define R_HLOS2ESW0_D3				(0x61CUL)
#define R_HLOS2ESW0_LOCK			(0x620UL)

#define R_ESW2HLOS1_D0				(0x624UL)
#define R_ESW2HLOS1_D1				(0x628UL)
#define R_ESW2HLOS1_D2				(0x62CUL)
#define R_ESW2HLOS1_D3				(0x630UL)
#define R_HLOS2ESW1_D0				(0x634UL)
#define R_HLOS2ESW1_D1				(0x638UL)
#define R_HLOS2ESW1_D2				(0x63CUL)
#define R_HLOS2ESW1_D3				(0x640UL)
#define R_HLOS2ESW1_LOCK			(0x644UL)

#define SIC_INSTANCE_OFFSET			(0x24UL)
#define MAX_SIC_INSTANCES			(64UL)

#define SIC_CMD_REQUEST				(0x1)
#define SIC_CMD_RESPONSE			(0x2)
#define SIC_CMD_DATA				(0x3)
#define SIC_CMD_CONTROL				(0x4)

union sic_head {
	struct {
		uint32_t dest_flow_id : 12;
		uint32_t packet_type : 4;
		uint32_t source_flow_id : 12;
		uint32_t sic_ver : 4;
	};
	uint32_t val;
};

static uint32_t poll_reg_same_val(uint64_t addr, uint32_t val)
{
	volatile uint32_t cur = *(volatile uint32_t *)addr;

	while (cur != val) {
		cur = *(volatile uint32_t *)addr;
	}
	return cur;
}

static uint32_t poll_reg_diff_val(uint64_t addr, uint32_t val)
{
	volatile uint32_t cur = *(volatile uint32_t *)addr;

	while (cur == val) {
		cur = *(volatile uint32_t *)addr;
	}
	return cur;
}

static uint32_t sic_lock_reg(void)
{
	return poll_reg_diff_val(CMRT_SIC_BASE + R_HLOS2ESW0_LOCK, 0);
}

static void sic_clean(void)
{
	*(volatile uint32_t *)(CMRT_SIC_BASE + R_ESW2HLOS0_D0) = 0;
	*(volatile uint32_t *)(CMRT_SIC_BASE + R_SOC_INTERRUPT_OUT) = 1;
}

static void sic_send_request(uint32_t sic_id, uint32_t length)
{
	union sic_head head = {
		.dest_flow_id = 0,
		.packet_type = SIC_CMD_REQUEST,
		.source_flow_id = sic_id & 0xfff,
		.sic_ver = 2,
	};

	*(volatile uint32_t *)(CMRT_SIC_BASE + R_HLOS2ESW0_D1) = length;
	*(volatile uint32_t *)(CMRT_SIC_BASE + R_HLOS2ESW0_D1) = 0x10;
	*(volatile uint32_t *)(CMRT_SIC_BASE + R_HLOS2ESW0_D2) = 0;
	*(volatile uint32_t *)(CMRT_SIC_BASE + R_HLOS2ESW0_D3) = 0;
	*(volatile uint32_t *)(CMRT_SIC_BASE + R_HLOS2ESW0_D0) = head.val;

	*(volatile uint32_t *)(SYSREG_ROT + SYS_CM_INTERRUPT) = 1;

	poll_reg_same_val(CMRT_SIC_BASE + R_HLOS2ESW0_D0, 0);
}

static void sic_send_data(uint32_t sic_id, uint32_t data)
{
	union sic_head head = {
		.dest_flow_id = 0,
		.packet_type = SIC_CMD_DATA,
		.source_flow_id = sic_id & 0xfff,
		.sic_ver = 2,
	};

	poll_reg_same_val(CMRT_SIC_BASE + R_HLOS2ESW0_D0, 0);

	*(volatile uint32_t *)(CMRT_SIC_BASE + R_HLOS2ESW0_D1) = data;
	*(volatile uint32_t *)(CMRT_SIC_BASE + R_HLOS2ESW0_D2) = 0x0;
	*(volatile uint32_t *)(CMRT_SIC_BASE + R_HLOS2ESW0_D3) = 0;

	*(volatile uint32_t *)(CMRT_SIC_BASE + R_HLOS2ESW0_D0) = head.val;

	poll_reg_same_val(CMRT_SIC_BASE + R_HLOS2ESW0_D0, 0);

	*(volatile uint32_t *)(CMRT_SIC_BASE + R_HLOS2ESW0_D1) = 0x4;
	*(volatile uint32_t *)(CMRT_SIC_BASE + R_HLOS2ESW0_D2) = 0;
	*(volatile uint32_t *)(CMRT_SIC_BASE + R_HLOS2ESW0_D3) = 0;

	*(volatile uint32_t *)(CMRT_SIC_BASE + R_HLOS2ESW0_D0) = head.val;

	poll_reg_same_val(CMRT_SIC_BASE + R_HLOS2ESW0_D0, 0);

	*(volatile uint32_t *)(CMRT_SIC_BASE + R_SOC_INTERRUPT_OUT) = 0;

	/* handle response */
	poll_reg_diff_val(CMRT_SIC_BASE + R_ESW2HLOS0_D0, 0);
	*(volatile uint32_t *)(CMRT_SIC_BASE + R_ESW2HLOS0_D0) = 0x0;
}

static void sic_release_reg(uint32_t sic_id)
{
	*(volatile uint32_t *)(CMRT_SIC_BASE + R_HLOS2ESW0_LOCK) = sic_id;
}

void request_to_cmrt(uint32_t data)
{
	volatile uint32_t sic_id = sic_lock_reg();

	sic_clean();
	sic_send_request(sic_id, sizeof(uint32_t) * 4);
	sic_send_data(sic_id, data);
	sic_release_reg(sic_id);
}
