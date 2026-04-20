/*
 * Copyright (c) 2017-2023 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

/**
 * @file pke4_driver.h
 *
 * @brief PKE4 driver.
 */

#ifndef CMRT_PKE_DRIVER_H
#define CMRT_PKE_DRIVER_H

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#ifndef CRI_PKE_STANDALONE
#include <device.h>
#include <init.h>
#include <kernel.h>
#include <drivers/cmrt/dd.h>
#include <drivers/cmrt/pke.h>
#include <drivers/cmrt/cmrt.h>
#endif

/**
 * @brief PKE4 driver.
 * @defgroup cmrt_pke_driver Math Engine Driver Definitions
 * @ingroup io_interfaces
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif

#include "pke4_reg.h"

/**
 * @brief Base Address
 * @details Note: This is CRI specific.
 * Register addresses are derived
 * using this address
 */
#define CMRT_PKE_REGISTER_BASE_ADDRESS 0x40000000

/**
 * @brief Base Address of MAU SRAM
 * @details Note: This is CRI specific.
 * PKE RAM addresses are derived
 * using this address.
 */
#ifdef CRI_PKE_STANDALONE
#define CMRT_PKE_SRAM_BASE_ADDRESS 0x40002000
#else
#define CMRT_PKE_SRAM_BASE_ADDRESS CONFIG_SRAM_BASE_ADDRESS
#endif

/**
 * @brief Base Address of MAU SRAM
 */
#define MAU_SRAM_OFFSET 0x4000

/**
 * @brief Get address for required RAM slot number
 */
#define SLOT(x) (R_MAU_ADDR_RAM_SLOTS + (x))

/**
 * @brief Get address for required ROM slot number
 */
#define ROM_SLOT(x) (R_MAU_ADDR_ROM_SLOTS + (x))

/**
 * @brief Generate MAU RAM address for CPU
 * addressing
 */
#ifdef CMRT_PKE_32_BIT
#define CPU_SRAM_ADDRESS(x) \
	(uint32_t*)(CMRT_PKE_SRAM_BASE_ADDRESS + (((uint32_t)x) << 2))
#else
#define CPU_SRAM_ADDRESS(x) \
	(uint32_t*)(CMRT_PKE_SRAM_BASE_ADDRESS + (((uint32_t)x) << 3))
#endif

/**
 * @brief Mcg Unit Status
 */
typedef enum mcgUnitStatus{
	MCG_STATUS_IDLE = 0x0,  /**< MCG is idle. */
	MCG_STATUS_BUSY = 0x1,  /**< MCG is busy. */
	MCG_STATUS_ERROR = 0x4, /**< MCG error.   */
	MCG_STATUS_PANIC = 0x8  /**< MCG panic.   */
} MCG_UNIT_STATUS;

/**
 * @brief Main state of the MAU
 */
typedef enum mauState{
	MAU_STATUS_READY = 0x00,        /**< MAU ready to accept commands */
	MAU_STATUS_BUSY = 0x01,         /**< MAU busy executing commands */
	MAU_STATUS_ERROR = 0x02,        /**< MAU is idle and encountered an error*/
	MAU_STATUS_PANIC = 0x08         /**< MAU Panic */
} MAU_STATE;

/**
 * @brief Opcodes for the different MAU Commands
 */
typedef enum mauOpcode{
	LOAD = 0x01,
	STORE = 0x02,
	MOD_ADD = 0x03,
	MOD_SUB = 0x04,
	MOD_DBL = 0x05,
	STORE_MOD_DBL = 0x06,
	CANON = 0x07,
	SET_MAND = 0x08,
	MONT_MUL = 0x09,
	MONT_SQR = 0x0a,
	STORE_MONT_MUL = 0x0b,
	STORE_MONT_SQR = 0x0c,
	MONT_MUL_INPLACE = 0x0d,
	MONTGOMERIZE = 0x0e,
	INT_ADD = 0x10,
	INT_SUB = 0x11,
	INT_MUL = 0x12,
	INT_MAC = 0x13,
	COMPARE = 0x14,
	IS_REDUCED = 0x15,
	INT_DIV_SMALL_EXACT = 0x16,
	SET_PARAMS = 0x19,
	SET_SPECIAL_PARAMS = 0x1a,
	SET_RAM_SLOTS = 0x1b,
	COPY = 0x1e,
	FLUSH = 0x1f
} MAU_OPCODE;

/**
 * @brief specmod for the different MCG Commands
 */
typedef enum mcgSpecMod{
	SPEC_MOD_DISABLED = 0x00,
	SPEC_MOD_ENABLED = 0x01
} MCG_SPEC_MOD;

/**
 * @brief rommod for curve parameters in ROM
 */
typedef enum mcgROMMod{
	SPEC_MOD_NOT_ROM = 0x00,
	SPEC_MOD_IN_ROM = 0x01
} MCG_ROM_MOD;

/**
 * @brief elliptic curves with parameters in ROM
 */
typedef enum mcgROMCurves{
	NOT_ROM = 0x00,
	NIST_SECP192r1 = 0x01,
	NIST_SECP224r1 = 0x02,
	NIST_SECP256r1 = 0x03,
	NIST_SECP384r1 = 0x04,
	NIST_SECP521r1 = 0x05,
	NIST_SECP256k1 = 0x07,
	BRAINPOOL_SECP192r1 = 0x11,
	BRAINPOOL_SECP224r1 = 0x12,
	BRAINPOOL_SECP256r1 = 0x13,
	BRAINPOOL_SECP320r1 = 0x14,
	BRAINPOOL_SECP384r1 = 0x15,
	BRAINPOOL_SECP512r1 = 0x16,
	ANSSI_FRP256v1 = 0x17,
	SM2_CURVE = 0x18,
	CURVE_25519 = 0x21,
	CURVE_448 = 0x22
} MCG_ROM_CURVES;

/**
 *  @brief Prepares an opcode before placing in the fifo.
 *	\return opcode
 */
#define PREPARE_MAU_COMMAND(opCode,addr,len) ( \
		(((uint32_t)(opCode)) << 25) | \
		(((uint32_t)(addr)) << 10) |   \
		((uint32_t)(len)))

/**
 * @brief Fifo Status
 */
typedef enum mauFifoStatus{
	FIFO_EMPTY = 0x00,      /**< Fifo is empty. */
	FIFO_NOTEMPTY = 0x01,   /**< Fifo is not empty. */
	FIFO_FULL = 0x03,       /**< Fifo is full. */
	FIFO_ERROR = 0x04       /**< Fifo error. */
} MAU_FIFO_STATUS;

/**
 *  @brief Reports Fifo Status.
 *  @return MAU_FIFO_STATUS
 */
#define MAU_GET_FIFO_STATUS() (MAU_READ_REG(R_MAU_STATUS) & MAU_FIFO_MASK)

/**
 * @brief Generate 15 bit SRAM base address
 */
#ifdef CMRT_PKE_32_BIT
#define MAU_SRAM_ADDRESS(x) \
	((((((uint32_t)(x)) - CMRT_PKE_SRAM_BASE_ADDRESS) >> 2) + MAU_SRAM_OFFSET) & 0x7fff)
#else
#define MAU_SRAM_ADDRESS(x) \
	((((((uint32_t)(x)) - CMRT_PKE_SRAM_BASE_ADDRESS) >> 3) + MAU_SRAM_OFFSET) & 0x7fff)
#endif

/**
 *  @brief Sends a single command to the MAU once there is space in the FIFO
 */
#define WRITE_MAU_COMMAND(command)  do {				    \
		while (((MAU_GET_FIFO_STATUS()) & FIFO_FULL) == FIFO_FULL); \
		MAU_WRITE_REG(R_MAU_MAU_COMMAND,command);		    \
} while (0);

/**
 *  @brief Send prepared command to MAU once there is space in the FIFO
 */
#define ISSUE_MAU_COMMAND(opcode,addr,len) \
	WRITE_MAU_COMMAND(PREPARE_MAU_COMMAND((opcode),(addr),(len)))

/**
 *  @brief Make a const code word, note tha tlength needs to be added later
 */
#define SLOT_CMD(opcode, addr) PREPARE_MAU_COMMAND((opcode), (addr), 0)

/**
 *  @brief Write to the MAU Registers
 *  \details Implementation is specific to CRI which uses memory mapping for all
 *  registers. This will change based on how registers are mapped
 *  \param[in]  x MAU register to write to.
 *  \param[in]  y value to be written
 */
#ifdef CRI_PKE_STANDALONE
#define MAU_WRITE_REG(x, y) ((*((volatile uint32_t *)(CMRT_PKE_REGISTER_BASE_ADDRESS + (x)))) = (y))
#else
#define MAU_WRITE_REG(x, y) sys_write32((y), (mm_reg_t)(R_PKE_BASE + (x)))
#endif

/**
 *  @brief Reading the MAU Registers
 *  \details Implementation is specific to CRI which uses memory mapping for all
 *  registers. This will change based on how registers are mapped
 *  \param[in]  x MAU register to write to.
 *  \return value read from register,
 */
#ifdef CRI_PKE_STANDALONE
#define MAU_READ_REG(x) (*((volatile uint32_t *)(CMRT_PKE_REGISTER_BASE_ADDRESS + (x))))
#else
#define MAU_READ_REG(x) sys_read32((mm_reg_t)(R_PKE_BASE + (x)))
#endif

/**
 *  @brief Read the MAU status register
 */
#define READ_MAU_STATUS() MAU_READ_REG(R_MAU_STATUS)

/**
 *  @brief Mask the MCG staatus bits
 */
#define MCG_STATUS(x) ((MCG_UNIT_STATUS)(((x) & MAU_MCG_MASK) >> MAU_MCG_OFFSET))

/**
 *  @brief Mask the MAU staatus bits
 */
#define MAU_STATE(x) ((MAU_STATE)(((x) & MAU_CORE_MASK) >> MAU_CORE_OFFSET))

/**
 * @brief MAU Computation Results
 */
typedef enum mauCompResult {
	MAU_EQ = 0x00,
	MAU_GT = 0x01,
	MAU_LT = 0x03,
	MAU_COMP_ERROR = 0x04
} MAU_COMP_RESULT;

/**
 *  @brief Get the result of compare instruction
 */
#define MAU_GET_COMPARE_RESULT() ((READ_MAU_STATUS() >> 30) & 3)

/**
 *  @brief Define PKE response pointers to copy
 */
typedef struct {
	uint32_t bits; /* override other lengths */
	void *rAddr;
	uint32_t *pkeAddr;
} ret_pke_param_t;

/**
 *  @brief Define PKE response type
 */
#define MAX_RET_PARAMS 3
typedef struct cmrt_pke_response {
	const struct dpa_ecc_curve_struct *curve;
	uint32_t bits;
	uint32_t copies_to_make;
	uint32_t slot;
	ret_pke_param_t ret_param[MAX_RET_PARAMS];
} cmrt_pke_response_t;

#ifdef CRI_PKE_STANDALONE
typedef struct cmrt_pke_context {
	uint64_t cmd;
	cmrt_pke_response_t response;
} cmrt_pke_context_t;
#else
typedef struct cmrt_pke_context {
	cmrt_dd_context_t ddc;
	uint64_t cmd;
	cmrt_pke_response_t response;
} cmrt_pke_context_t;
#endif

/**
 *  @brief Define copy parameters
 */
typedef struct cmrt_pke_copy_command_struct {
	uint8_t *in;
	uint32_t *out;
} cmrt_pke_copy_command;

/**
 *  @brief Structure to contain as many copies as required
 */
typedef struct cmrt_pke_copy_inputs_struct {
	uint32_t length;
	uint32_t copies_to_make;
	uint32_t slot;
	cmrt_pke_copy_command *copy_command;
} cmrt_pke_copy_inputs;


/**
 *  @brief Get the address of the beginning of a slot when using a cureve type or parameters, or
 *  values of the given bit length, the other parameter can be set to NULL or zero as required.
 */
uint32_t *pke_addr(uint32_t slot, const struct dpa_ecc_curve_struct *curve, const uint32_t bits);

/**
 *  @brief Test if PKE is idle and ready for commands
 */
#ifdef CRI_PKE_STANDALONE
#define IS_PKE_IDLE() (MCG_STATUS(MAU_READ_REG(R_MAU_STATUS)) == MCG_STATUS_IDLE \
		       && MAU_STATE(MAU_READ_REG(R_MAU_STATUS)) == MAU_STATUS_READY)
#else
int is_pke_idle(void);
#define IS_PKE_IDLE() is_pke_idle()
#endif

/**
 * @brief Opcodes for MCG Commands
 */
typedef enum mcgOpcode {
	ECDSA_VERIFY = 0x00,
	EC_BLIND_PRIVATE_KEY = 0x01,
	ECDSA_KEYGEN = 0x02,
	ECDSA_SIGN = 0x03,
	ECDH_KEYGEN_EPH = 0x04,
	ECDH_KEYGEN_LT = 0x05,
	ECDH_SHARED_EPH = 0x06,
	ECDH_SHARED_LT = 0x07,
	ECC_ONCURVE = 0x08,
	SM2DSA_KEYGEN = 0x09,
	ECC_ONCURVE_XONLY = 0x0A,
	ECC_DECOMPRESS = 0x0B,
	ECDSA_SIGN2 = 0x0C,
	SM2DSA_SIGN = 0x0D,
	SM2DSA_VERIFY = 0x0E,
	SM2DSA_SIGN_2 = 0x0F,
	ECDH_MONTGOMERY_KEYGEN_EPH = 0x14,
	ECDH_MONTGOMERY_SHARED_EPH = 0x16,
	ED448_KEYGEN = 0x10,
	ED448_SIGN_PHASE_1 = 0x11,
	ED448_SIGN_PHASE_2 = 0x12,
	ED448_VERIFY = 0x13,
	ED25519_KEYGEN = 0x1A,
	ED25519_SIGN_PHASE_1 = 0x1B,
	ED25519_SIGN_PHASE_2 = 0x1C,
	ED25519_VERIFY = 0x1D,
	ECC_ROM_SETUP = 0x1F,
	RSA_PUBLIC = 0x21,
	RSA_SIGN = 0x22,
	RSA_DECRYPT = 0x23,
	MOD_EXP = 0x24,
	MONTGOMERY_MOD_EXP = 0x25
} MCG_OPCODE;

/* FIXME put it to kconfig? */
#define CMRT_PKE_ECDH_EPHEMERAL 1

#ifdef CMRT_PKE_ECDH_EPHEMERAL
#define PKE_ECDH_SHARED_OPCODE ECDH_SHARED_EPH
#define PKE_ECDH_KEYGEN_OPCODE ECDH_KEYGEN_EPH
#else
#define PKE_ECDH_SHARED_OPCODE ECDH_SHARED_LT
#define PKE_ECDH_KEYGEN_OPCODE ECDH_KEYGEN_LT
#endif


/**
 *  @brief Prepares an mcg command before placing in the fifo.
 */
#define MCG_PREPARE_COMMAND(opCode, specMod, ROMMod, length) ( \
		((uint32_t)opCode) |			       \
		(((uint32_t)(specMod)) << 7) |		       \
		(((uint32_t)(ROMMod)) << 15) |		       \
		(((uint32_t)(length)) << 8))

/**
 *  @brief Issue a MCG command, for use with polling
 */
#define ISSUE_MCG_COMMAND(opCode, specMod, ROMMod, length) \
	MAU_WRITE_REG(R_MAU_MCG_COMMAND, MCG_PREPARE_COMMAND((opCode), (specMod), (ROMMod), (length)))

/**
 *  @brief Issue a MCG command, for use with interrupts or polling
 */
int cmrt_pke_issue_mcg_command(cmrt_pke_t context, uint32_t cmd);

#ifdef CRI_PKE_STANDALONE
/**
 *  @brief Flush a PKE error and zero the PKE RAM
 */
void pke_flush_error(void);
#endif

/**
 *  @brief Send in a sequence of MAU commands
 */
int cmrt_pke_mau_command_sequence(const uint32_t *command_word,
				  const uint32_t command_length,
				  const uint32_t variable_length);

/**
 *  @brief Zero the PKE RAM
 */
int cmrt_pke_clear_ram(void);


/*!
 * Run and finish MCG command synchronously.  The call will finish
 * synchronously and may yield the CPU while doing so.
 * @param pke valid pke context
 * @param cmd MCG command
 * @pre interrupts and pke interrupts must be enabled
 * @return success code (0) or an error return (< 0)
 */
static inline int cmrt_pke_run_mcg_command(cmrt_pke_t pke, uint32_t cmd)
{
	int res = cmrt_pke_issue_mcg_command(pke, cmd);
	if (res >= 0) {
		res = cmrt_dd_sync((cmrt_dd_context_t *)pke);
	}
	return res;
}


/**
 *  @brief Check PKE ECC curve validity in supervisor and machine mode
 */
cmrt_ecc_curve_t cmrt_pke_verify_curve(cmrt_ecc_curve_t curve);


/**
 *  @brief Check PKE ECC curve validity in user mode
 */
cmrt_ecc_curve_t cmrt_pke_verify_user_curve(cmrt_ecc_curve_t curve);

#ifdef __cplusplus
}
#endif
/**
 * @}
 */
#endif
