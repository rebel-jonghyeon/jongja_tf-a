/*
 * Protocol manager definitions.
 *
 * Protocol manager interface mimics a device driver interface.
 * This makes it possible to call system functions directly in case
 * we have a device driver (FPGA). If not (QEMU) one has to call the
 * corresponding protocol manager functions.
 *
 * Copyright (c) 2017-2023 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

#ifndef CMRT_SIC_EXT_H
#define CMRT_SIC_EXT_H

#ifdef __KERNEL__
#include <linux/types.h>
#include <linux/ioctl.h>
#else
#include <stdint.h>
#include <stdarg.h>

#ifndef __MINGW32__
#include <sys/ioctl.h>
#endif

#endif

typedef struct {
	uint32_t base;
	uint32_t offset;
	uint32_t value;
} cmrt_sic_register_t;

typedef struct {
	uint32_t base;
	uint32_t offset;
	uint32_t length;
} cmrt_sic_memory_t;

typedef struct {
	uint32_t flowid; /* container id */
	uint32_t address;
	uint32_t length;
} cmrt_sic_data_t;

typedef struct {
	uint32_t sideband;
} cmrt_sic_sideband_t;

typedef struct {
	uint32_t how;
} cmrt_sic_reset_t;

typedef struct {
	uint32_t val;
} cmrt_sic_pmu_t;

typedef struct {
	uint32_t val;
} cmrt_sic_query_t;

#define CMRT_PMU_CMD_STATE  0x10000000UL
#define CMRT_PMU_CMD_SLEEP  0x20000000UL
#define CMRT_PMU_CMD_RESUME 0x30000000UL

#define CMRT_QUERY_CMD_ID          0x50000000UL
#define CMRT_QUERY_CMD_PHYS_DEVCFG 0x50000010UL
#define CMRT_QUERY_CMD_PHYS_SYSCTL 0x50000011UL
#define CMRT_QUERY_CMD_PHYS_SIC    0x50000012UL
#define CMRT_QUERY_CMD_PHYS_SOG    0x50000013UL
#define CMRT_QUERY_CMD_PHYS_ROM    0x50000014UL
#define CMRT_QUERY_CMD_PHYS_OTP    0x50000015UL
#define CMRT_QUERY_CMD_PHYS_SRAM   0x50000016UL
#define CMRT_QUERY_CMD_PHYS_SAC    0x50000017UL
#define CMRT_QUERY_CMD_PHYS_DM     0x50000018UL
#define CMRT_QUERY_CMD_PHYS_OEC    0x50000019UL
#define CMRT_QUERY_CMD_PHYS_FIC    0x5000001AUL

#define CMRT_PMU_OFF        0x00000001UL
#define CMRT_PMU_ACTIVE     0x00000002UL
#define CMRT_PMU_INACTIVE   0x00000003UL
#define CMRT_PMU_IDLE       0x00000004UL
#define CMRT_PMU_SLEEP      0x00000005UL

typedef struct {
	uint32_t cmd;           /* see below */
	uint32_t rsrvd;         /* must be zero for normal esw message */
	uint32_t timeout;       /* set as mseconds */
	union {                 /* set according to cmd */
		cmrt_sic_register_t r;
		cmrt_sic_memory_t m;
		cmrt_sic_data_t d;
		cmrt_sic_sideband_t s;
		cmrt_sic_reset_t t;
		cmrt_sic_pmu_t p;
		cmrt_sic_query_t q;
	} u;
} cmrt_sic_packet_t;

#define CMRT_SIC_READ_REGISTER  0x001UL
#define CMRT_SIC_WRITE_REGISTER 0x002UL
#define CMRT_SIC_READ_MEMORY    0x004UL
#define CMRT_SIC_WRITE_MEMORY   0x008UL
#define CMRT_SIC_READ_DATA      0x010UL
#define CMRT_SIC_WRITE_DATA     0x020UL
#define CMRT_SIC_READ_SIDEBAND  0x040UL
#define CMRT_SIC_WRITE_SIDEBAND 0x080UL
#define CMRT_SIC_RESET_CPU      0x100UL
#define CMRT_SIC_OPEN_MEMORY    0x200UL
#define CMRT_SIC_CLOSE_MEMORY   0x400UL
#define CMRT_SIC_PMU_COMMAND    0x800UL
#define CMRT_SIC_RESERVED_1     0x1000UL
#define CMRT_SIC_QUERY_COMMAND  0x2000UL
#define CMRT_SIC_READ_MMAP      0x4000UL
#define CMRT_SIC_WRITE_MMAP     0x8000UL
#define CMRT_SIC_STATUS_COMMAND 0x10000UL
#define CMRT_SIC_SOC_INTERRUPT  0x20000UL
#define CMRT_SIC_READ_FPGA      0x40000UL
#define CMRT_SIC_WRITE_FPGA     0x80000UL
#define CMRT_SIC_FIPS_MODE      0x100000UL

/*
 * Max data size is limited by Unix domain socket payload size.
 * Currently with Ubuntu 18.04 it is 212992 bytes by default.
 */
#define CMRT_SIC_MAX_PACKET (200 * 1024)
#define CMRT_SIC_MAX_DATA (CMRT_SIC_MAX_PACKET - sizeof(cmrt_sic_packet_t))

/*
 * Definitions for simulate abnormal SIC driver on QEMU SIC.
 */
#define CMRT_SIC_TEST_OP_DISABLED 0UL
#define CMRT_SIC_TEST_OP_DROP_AFTER_REQ 1UL
#define CMRT_SIC_TEST_OP_DROP_DURING_DATA 2UL
#define CMRT_SIC_TEST_OP_MAX CMRT_SIC_TEST_OP_DROP_DURING_DATA

/*
 * Definitions for FPGA driver.
 */
#define CMRT_SIC_DEVICE "/dev/cmrt"
#define CMRT_SIC_MAJORNO 123UL

#ifndef _IOWR
#define _IOWR(g, n, t) 0
#endif

#define CMRT_SIC_PACKET _IOWR(CMRT_SIC_MAJORNO, 0, void *)

#define CMRT_SIC_RESET_HARD     (1UL << 0)
#define CMRT_SIC_RESET_POWERON  (1UL << 1)
#define CMRT_SIC_RESET_PDMA     (1UL << 8)
#define CMRT_SIC_RESET_MASK     (CMRT_SIC_RESET_HARD | CMRT_SIC_RESET_POWERON)
/* Hold the reset. */
#define CMRT_SIC_RESET_HOLD     (1UL << 7)

#define CMRT_PMU_CSYSREQ    (1UL << 0)
#define CMRT_PMU_CSYSACTIVE (1UL << 1)
#define CMRT_PMU_CSYSACK    (1UL << 2)

#if !defined(__KERNEL__) && !defined(CMRT_SIC_INTERFACE)
#define CMRT_SIC_INTERFACE

/*
 * Definitions for QEMU driver.
 */
#define CMRT_SIC_SERVER "cmrt_sic_server.socket"

/**
 * @brief Open SIC connection.
 *
 * Open connection to the device driver controlling access to SIC,
 * SAC memory and SIC protocol messaging.
 *
 * @param pathname Hostname for WEMU, device name for FPGA. NULL for default.
 * @param flags Zero for QEMU, see open(2) manual page for FPGA.
 * @retval File descriptor on success.
 * @retval -1 on error with errno set.
 */
int cmrt_sic_open(const char *pathname, int flags);

/**
 * @brief Send command to SIC.
 *
 * The ioctl(2) interface for sending commands to SIC via the device driver.
 *
 * @param fd File descriptor returned in open.
 * @param request Currently must be set to CMRT_SIC_PACKET.
 * @param ... Pointer to cmrt_sic_packet_t.
 * @retval Number of bytes on success.
 * @retval 0 on timeout with errno set to ETIMEDOUT
 * @retval -1 on error with errno set
 */
int cmrt_sic_ioctl(int fd, unsigned long request, ...);

/**
 * @brief Map external memory.
 *
 * The mmap(2) interface for mapping external memory into process address
 * space. External memory is visible to CMRT via SAC, using external memory
 * eliminates the need to copy data via SIC.
 *
 * Currently CMRT driver only allows one user process to map external memory
 * but it can call mmap many times.
 *
 * @param addr Address to map, must be NULL.
 * @param length Mapped length.
 * @param prot See mmap(2).
 * @param flags See mmap(2).
 * @param fd Driver handle from cmrt_sic_open.
 * @param offset Offset to external memory.
 * @retval 0 on success.
 * @retval -1 on error with errno set.
 */
void *cmrt_sic_mmap(void *addr, size_t length, int prot, int flags, int fd, off_t offset);

/**
 * @brief Unmap external memory.
 *
 * Reverse of mmap.
 *
 * @param addr Mapped address.
 * @param length Mapped length.
 * @retval 0 on success.
 * @retval -1 on error with errno set.
 */
int cmrt_sic_munmap(void *addr, size_t length);

/**
 * @brief Close SIC connection.
 *
 * Reverse of open.
 *
 * @param fd File descriptor returned in open.
 * @retval 0 on success.
 * @retval -1 on error with errno set.
 */
int cmrt_sic_close(int fd);

/**
 * @brief Write data to the CMRT via the SIC protocol.
 *
 * @param flowid    The endpoint flow ID to which to write the message.
 * @param num_bytes The number of bytes in the data array.
 * @param data      Data written to the CMRT via the SIC protocol.
 * @retval          Returns 0 on success, otherwise -1.
 */
int cmrt_sic_write_data(uint32_t flowid, size_t num_bytes, const void *data);

/**
 * @brief Read data from the CMRT via the SIC protocol.
 *
 * @param num_bytes Number of bytes to read from the CMRT.
 * @param data      Buffer for values read from the CMRT.
 * @retval          Returns 0 on success, otherwise -1.
 */
int cmrt_sic_read_data(size_t num_bytes, void *data);

/**
 * @brief Write data to the CMRT via SIC protocl, and receives the answer.
 *
 * @param flowid          The endpoint flow ID to which to write the message.
 * @param num_write_bytes Number of bytes to be writen to the CMRT.
 * @param write_data      Date to be written.
 * @param num_read_bytes  Number of bytes to be read from the CMRT.
 * @param read_data       Buffer for values read from the CMRT.
 * @retval                Returns 0 on success, otherwise -1.
 */
int cmrt_sic_write_read(uint32_t flowid, size_t num_write_bytes,
			const void *write_data, size_t num_read_bytes,
			void *read_data);
#endif /* !__KERNEL__ && !CMRT_SIC_INTERFACE */

#endif
