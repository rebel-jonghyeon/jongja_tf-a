#include <stdint.h>
#include <stdbool.h>

enum tc_type {
	DATA_TC_TYPE_STC, // not used for VDK2.0 or higher, only for single chiplet
	DATA_TC_TYPE_UNIT_TEST,
	DATA_TC_TYPE_REPLAY_TEST, // not used for VDK2.0 or higher, only for single chiplet
	DATA_TC_TYPE_UCIE_STC,
	DATA_TC_TYPE_UCIE_REPLAY_TEST,  /* not use, legacy replay */
	DATA_TC_TYPE_UCIE_STRESS,
	DATA_TC_TYPE_STRESS_TEST,
	DATA_TC_TYPE_UCIE_AF_STC_POWER,
	DATA_TC_TYPE_UCIE_QUAD_REPLAY_TEST,
};

enum tc_data_element_type {
	DATA_EL_TYPE_DMA,
	DATA_EL_TYPE_DB,
	DATA_EL_TYPE_MAX_NUM,
};

enum tc_dma_direction {
	DMA_H2D,
	DMA_D2H
};

enum tc_data_type {
    DATA_TYPE_MEMORY,
    DATA_TYPE_COMMND,
    DATA_TYPE_OUTPUT,
    DATA_TYPE_DUMP,
    DATA_TYPE_MAX_NUM,
};

struct __attribute__((packed)) tc_dma_info {
    uint32_t el_type;
    uint32_t dir;
    uint32_t type;
    int channel;
    uint64_t offset;
    uint64_t size;
    uint32_t reserved[4];
};

struct __attribute__((packed)) tc_db_info {
    uint32_t el_type;
    uint32_t idx;
    uint32_t mailbox;
    uint32_t reserved[4];
};

struct __attribute__((packed)) tc_info {
	char name[64];		/* test case name */
	uint32_t type;		/* TC Type (STC, UNIT_TEST, REPLAY_TEST) */
	char param[64];		/* param for test run */
	//uint32_t iter;		/* test iteration count */
	uint32_t length;		/* length of TC data */
	uint32_t iter_per_test;	/* test iteration count for one test */
	uint32_t nr;		/* number of TC elements */
	char data[];		/* variable data of TC element */
};

struct __attribute__((packed)) hdma_desc {
    uint32_t channel_control;
    uint32_t transfer_size;
    uint64_t sar;
    uint64_t dar;
//    uint32_t next_desc_addr;
};

struct hdma_desc_node {
    struct hdma_desc desc;
    struct hdma_desc_node *next;
};
