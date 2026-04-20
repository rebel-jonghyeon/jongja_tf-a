/*
 * Copyright (c) 2017-2023 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

/* Internal APIs for the DMAC driver. */

#ifndef CMRT_DMAC_INT_H
#define CMRT_DMAC_INT_H

#include <stdint.h>
#include <dmac_reg.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Start DMAC crypto transfer with descriptor flags.
 *
 * Start DMAC crypto transfer. Caller must call cmrt_dmac_sync to wait for
 * completion, or CMRT_O_SYNC must be set in cmrt_dmac_open.
 *
 * @param channel Pointer to the device.
 * @param dev_base Device address.
 * @param src_addr Source address.
 * @param dst_addr Destination address.
 * @param data_size Data size in bytes (must be word aligned).
 * @param flags Descriptor flags, zero until supported by HW.
 * @return Zero on success, -ERRNO on error.
 */
int cmrt_dmac_crypto(cmrt_dmac_t channel, uint32_t dev_base, uint32_t src_addr, uint32_t dst_addr, uint32_t data_size, uint32_t flags);

#ifdef TEST_DMAC_LOCK
int cmrt_dmac_lock(cmrt_dmac_t channel, uint32_t dev_addr);
#endif /* TEST_DMAC_LOCK */

/**
 * @brief Do DMAC CSR write.
 *
 * Command DMAC to write to a CSR register. This is useful when the CPU
 * cannot do the write, e.g. when DMAC holds a lock for a core. Caller must
 * call cmrt_dmac_sync to wait for completion, or CMRT_O_SYNC must be set in
 * cmrt_dmac_open.
 *
 * @param channel Pointer to the device.
 * @param csr_data0 First data to write.
 * @param csr_addr0 First address to write.
 * @param csr_data1 Second data to write.
 * @param csr_addr1 Second address to write.
 * @return Zero on success, -ERRNO on error.
 */
int cmrt_dmac_csr(cmrt_dmac_t channel, uint32_t csr_data0, uint32_t csr_addr0, uint32_t csr_data1, uint32_t csr_addr1);

/**
 * @brief Helper function to transfer data.
 *
 * Transfer data in a loop until there's less than block_size left.
 * Can be used for plain data move or with HW cores. Opens and closes
 * DMAC handle internally.
 *
 * @param dev_base Device base for crypto operations, or zero.
 * @param src_addr Source address which can be device base.
 * @param dst_addr Destination address which can be device base.
 * @param data_size Data size in bytes (must be word aligned).
 * @param block_size Minimum size in bytes (must be word aligned).
 * @param flags Descriptor flags, zero until supported by HW.
 * @return Bytes left on success, -ERRNO on error.
 */
int cmrt_dmac_helper(uint32_t dev_base, uint32_t src_addr, uint32_t dst_addr, uint32_t data_size, uint32_t block_size, cmrt_dmac_flags_t flags);

#ifdef __cplusplus
}
#endif

#endif
