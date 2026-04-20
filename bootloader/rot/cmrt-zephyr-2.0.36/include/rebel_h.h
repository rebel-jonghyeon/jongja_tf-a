#pragma once
#include "util.h"
#include "sac.h"

#define SYSREG_SYSREMAP					(0x1E00220000ULL)
#define CHIPLET_ID						(0x444)
#define CHIPLET_BASE_OFFSET				(0x2000000000ULL)
#define CHIPLET_PRIMARY					(0x0)

#define CPMU							(0x1FF0230000ULL)
#define CPMU_PRIVATE					(0x1E00230000ULL)
#define CHIPLET_CNT						(0x840)
#define SWRESET							(0x400)
#define RESET							(0x1)

/* Boot log sfr */
#define BOOT_LOG_BASE					(0x1E00230800ULL)
#define BOOT_LOG_ADDR					(CMRT_SAC_BASE + R_CPU_DATA + 0x180)
#define BOOT_FLAG_ADDR					(CMRT_SAC_BASE + R_CPU_DATA + 0x184)

#define CPMU_RESET_ADDR					(CMRT_SAC_BASE + R_CPU_DATA + 0x404)

/* Boot binary index */
#define BOOT_SBOOT_S					(1)
#define BOOT_ROT_MW						(2)

/* Boot log */
#define BOOT_CP0_STEP_SIZE				(5)
#define BOOT_ROT_STEP_SIZE				(5)
#define BOOT_CM7_STEP_SIZE				(4)
#define BOOT_CP1_STEP_SIZE				(2)
#define BOOT_CP0_BIN_SIZE				(3)
#define BOOT_ROT_BIN_SIZE				(2)
#define BOOT_CM7_BIN_SIZE				(2)
#define BOOT_CP1_BIN_SIZE				(2)
#define BOOT_RESET_TYPE_SIZE			(5)
#define BOOT_CHIPLET_ID_SIZE			(2)

#define BOOT_CP0_STEP_OFFSET			(0)
#define BOOT_ROT_STEP_OFFSET			(BOOT_CP0_STEP_OFFSET + BOOT_CP0_STEP_SIZE)
#define BOOT_CM7_STEP_OFFSET			(BOOT_ROT_STEP_OFFSET + BOOT_ROT_STEP_SIZE)
#define BOOT_CP1_STEP_OFFSET			(BOOT_CM7_STEP_OFFSET + BOOT_CM7_STEP_SIZE)
#define BOOT_CP0_BIN_OFFSET				(BOOT_CP1_STEP_OFFSET + BOOT_CP1_STEP_SIZE)
#define BOOT_ROT_BIN_OFFSET				(BOOT_CP0_BIN_OFFSET + BOOT_CP0_BIN_SIZE)
#define BOOT_CM7_BIN_OFFSET				(BOOT_ROT_BIN_OFFSET + BOOT_ROT_BIN_SIZE)
#define BOOT_CP1_BIN_OFFSET				(BOOT_CM7_BIN_OFFSET + BOOT_CM7_BIN_SIZE)
#define BOOT_RESET_TYPE_OFFSET			(BOOT_CP1_BIN_OFFSET + BOOT_CP1_BIN_SIZE)
#define BOOT_CHIPLET_ID_OFFSET			(BOOT_RESET_TYPE_OFFSET + BOOT_RESET_TYPE_SIZE)

#define BOOT_DONE(cpu)					(BIT(BOOT_##cpu##_STEP_SIZE) - 1)
#define _BOOT_GET_MASK(size, offset)	(~(((1 << (size)) - 1) << (offset)))

#define _BOOT_MASK(cpu)											\
	(_BOOT_GET_MASK(BOOT_##cpu##_SIZE, BOOT_##cpu##_OFFSET))

#define _WAIT_BOOT_FLAG											\
	while (*(volatile uint32_t *)BOOT_FLAG_ADDR)

#define _SET_BOOT_FLAG(val)										\
	((*(volatile uint32_t *)BOOT_FLAG_ADDR) = (val))

#define INIT_BOOT_LOG(id)										\
	do {														\
		cmrt_sac_set_base(NULL, BOOT_LOG_BASE);					\
		_SET_BOOT_FLAG(0);										\
		(*(uint32_t *)(BOOT_LOG_ADDR)) = (id) << BOOT_CHIPLET_ID_OFFSET;			\
	} while (0)

#define _SET_BOOT_LOG(cpu, bin, n)								\
	do {														\
		*(uint32_t *)BOOT_LOG_ADDR &= _BOOT_MASK(cpu##_BIN);	\
		*(uint32_t *)BOOT_LOG_ADDR &= _BOOT_MASK(cpu##_STEP);	\
		*(uint32_t *)BOOT_LOG_ADDR |= (n) << (BOOT_##cpu##_STEP_OFFSET);			\
		*(uint32_t *)BOOT_LOG_ADDR |= (BOOT_##bin) << (BOOT_##cpu##_BIN_OFFSET);	\
	} while (0)

#define BOOT_LOG(cpu, bin, step)								\
	do {														\
		cmrt_sac_set_base(NULL, BOOT_LOG_BASE);					\
		_WAIT_BOOT_FLAG;										\
		_SET_BOOT_FLAG(1);										\
		_SET_BOOT_LOG(cpu, bin, step);							\
		_SET_BOOT_FLAG(0);										\
	} while (0)

#define FSB(x)													\
	do {														\
		uint32_t i = 0;											\
																\
		while (!((x) & 0x1)) {									\
			i++;												\
			(x) >>= 1;											\
		}														\
		(x) = i;												\
	} while (0)

#define _SET_RESET_STATUS										\
	do {														\
		cmrt_sac_set_base(NULL, CPMU_PRIVATE);					\
		uint32_t val = *(uint32_t *)CPMU_RESET_ADDR;			\
																\
		cmrt_sac_set_base(NULL, BOOT_LOG_BASE);					\
		uint32_t log = *(volatile uint32_t *)BOOT_LOG_ADDR;		\
																\
		log &= _BOOT_MASK(RESET_TYPE);							\
		FSB(val);												\
		log |= val << BOOT_RESET_TYPE_OFFSET;					\
		(*(uint32_t *)BOOT_LOG_ADDR) = log;						\
	} while (0)

#define UPDATE_RESET_LOG										\
	do {														\
		cmrt_sac_set_base(NULL, BOOT_LOG_BASE);					\
		_WAIT_BOOT_FLAG;										\
		_SET_BOOT_FLAG(1);										\
		_SET_RESET_STATUS;										\
		_SET_BOOT_FLAG(0);										\
	} while (0)

#define MAX_SIZE					(0x400000)
#define NORMAL_IMG_PADDING_SIZE		(8)
#define FOOTER_MAX_LEN				(0x150)

#define GET_SAC_BASE(val)			((val) & CPU_ADDR_MASK)
#define GET_SAC_OFFSET(val)			(uint32_t)((((val) & ~CPU_ADDR_MASK) + SAC_MEMORY_BASE))
#define GET_SAC_R_CPU_DATA(val)		(((val) & ~CPU_ADDR_LO_MASK) + CMRT_SAC_BASE + R_CPU_DATA)

#define OTP_CON_PRIVATE	(0x1E00250000ULL)
#define OTP_EVT_INFO	(0x1014)

#define REVISION_EVT1	(1)
#define REVISION_EVT0	(0)

static inline uint32_t get_chiplet_id(void)
{
	uint64_t chiplet_id = SYSREG_SYSREMAP + CHIPLET_ID;

	cmrt_sac_set_base(NULL, GET_SAC_BASE(chiplet_id));

	return sys_read32(GET_SAC_R_CPU_DATA(chiplet_id));
}

static inline uint32_t get_chiplet_cnt(void)
{
	uint64_t chiplet_cnt = CPMU_PRIVATE + CHIPLET_CNT;

	cmrt_sac_set_base(NULL, GET_SAC_BASE(chiplet_cnt));

	return sys_read32(GET_SAC_R_CPU_DATA(chiplet_cnt));
}

static inline uint32_t get_revision(void)
{
	uint64_t revision_info = OTP_CON_PRIVATE + OTP_EVT_INFO;

	cmrt_sac_set_base(NULL, GET_SAC_BASE(revision_info));

	return sys_read32(GET_SAC_R_CPU_DATA(revision_info));
}
