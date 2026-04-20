/* dw_i2c.h - header for Design Ware I2C operations */

/*
 * Copyright (c) 2015 Intel Corporation
 * Copyright (c) 2024 SAMSUNG Electronics Co., Ltd
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef ZEPHYR_DRIVERS_I2C_I2C_DW_H_
#define ZEPHYR_DRIVERS_I2C_I2C_DW_H_

#include <drivers/i2c.h>
#include <stdbool.h>

#define DT_DRV_COMPAT snps_designware_i2c

#if DT_ANY_INST_ON_BUS_STATUS_OKAY(pcie)
BUILD_ASSERT(IS_ENABLED(CONFIG_PCIE), "DW I2C in DT needs CONFIG_PCIE");
#include <drivers/pcie/pcie.h>
#endif /* DT_ANY_INST_ON_BUS_STATUS_OKAY(pcie) */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#define I2C_DW_MAGIC_KEY 0x44570140

typedef void (*i2c_isr_cb_t)(const struct device *port);

#define IC_ACTIVITY (1 << 0)
#define IC_ENABLE_BIT (1 << 0)

/* dev->state values from IC_DATA_CMD Data transfer mode settings (bit 8) */
#define I2C_DW_STATE_READY (0)
#define I2C_DW_CMD_SEND (1 << 0)
#define I2C_DW_CMD_RECV (1 << 1)
#define I2C_DW_CMD_ERROR (1 << 2)
#define I2C_DW_BUSY (1 << 3)

#define DW_ENABLE_TX_INT_I2C_MASTER                 \
    (DW_INTR_STAT_TX_OVER | DW_INTR_STAT_TX_EMPTY | \
     DW_INTR_STAT_TX_ABRT | DW_INTR_STAT_STOP_DET)
#define DW_ENABLE_RX_INT_I2C_MASTER                 \
    (DW_INTR_STAT_RX_UNDER | DW_INTR_STAT_RX_OVER | \
     DW_INTR_STAT_RX_FULL | DW_INTR_STAT_STOP_DET)

#define DW_ENABLE_TX_INT_I2C_SLAVE \
    (DW_INTR_STAT_RD_REQ | DW_INTR_STAT_TX_ABRT | DW_INTR_STAT_STOP_DET)
#define DW_ENABLE_RX_INT_I2C_SLAVE \
    (DW_INTR_STAT_RX_FULL | DW_INTR_STAT_STOP_DET)

#define DW_DISABLE_ALL_I2C_INT 0x00000000

/* IC_CON Low count and high count default values */
/* CONFIG_I2C_DW_CLOCK_SPEED should be 52 */
#define I2C_STD_HCNT (CONFIG_I2C_DW_CLOCK_SPEED * 4)
#define I2C_STD_LCNT (CONFIG_I2C_DW_CLOCK_SPEED * 5)
#define I2C_FS_HCNT  ((CONFIG_I2C_DW_CLOCK_SPEED * 16) / 16)
#define I2C_FS_LCNT  ((CONFIG_I2C_DW_CLOCK_SPEED * 19) / 16)
#define I2C_FSP_HCNT ((CONFIG_I2C_DW_CLOCK_SPEED * 5) / 16)
#define I2C_FSP_LCNT ((CONFIG_I2C_DW_CLOCK_SPEED * 7) / 16)
#define I2C_HS_HCNT  ((CONFIG_I2C_DW_CLOCK_SPEED * 6) / 8)
#define I2C_HS_LCNT  ((CONFIG_I2C_DW_CLOCK_SPEED * 7) / 8)

/*
 * DesignWare speed values don't directly translate from the Zephyr speed
 * selections in include/i2c.h so here we do a little translation
 */
#define I2C_DW_SPEED_STANDARD  0x1
#define I2C_DW_SPEED_FAST      0x2
#define I2C_DW_SPEED_FAST_PLUS 0x2
#define I2C_DW_SPEED_HIGH      0x3

/*
 * These values have been randomly selected.  It would be good to test different
 * watermark levels for performance capabilities
 */
#define I2C_DW_TX_WATERMARK 2
#define I2C_DW_RX_WATERMARK 7

#define I2C_DW_FIFO_DEPTH 8

#define MAX_XFR_LEN 0xFFFFFFFF

/* I2C index */
#define DT_INST_BOOT_I2C 0
#define DT_INST_I2C_0    1
#define DT_INST_I2C_1    2
#define DT_INST_I2C_2    3
#define DT_INST_I2C_3    4
#define TOTAL_NUM_I2C    5
#define I2C_INDEX_CHAR_ORDER 3

/* Pinmux settings for I2C */
#define PINMUX_FIELD_3 0x661a0008
#define PINMUX_FIELD_4 0x661a000c
#define PINMUX_FIELD_3_I2C_CLEAR 0x3FFF
#define PINMUX_FIELD_4_I2C_CLEAR 0xC0
#define PINMUX_FIELD_3_I2C_EN 0xC000
#define PINMUX_FIELD_4_I2C_EN 0x3F

struct i2c_dw_rom_config {
    DEVICE_MMIO_ROM;
    i2c_isr_cb_t config_func;
    uint32_t     bitrate;
#if DT_ANY_INST_ON_BUS_STATUS_OKAY(pcie)
    bool       pcie;
    pcie_bdf_t pcie_bdf;
    pcie_id_t  pcie_id;
#endif /* DT_ANY_INST_ON_BUS_STATUS_OKAY(pcie) */
};

struct i2c_dw_dev_config {
    DEVICE_MMIO_RAM;
    struct   k_sem device_sync_sem;
    uint32_t app_config;

    uint8_t *xfr_buf;
    uint32_t xfr_len;
    uint32_t rx_pending;

    uint16_t hcnt;
    uint16_t lcnt;

    volatile uint8_t state; /* last direction of transfer */
    uint32_t         request_bytes;
    uint8_t          xfr_flags;
    bool             support_hs_mode;
    uint16_t         slave_addr;

#ifdef CONFIG_I2C_DW_DMA_DRIVEN
    const struct device *dma_dev;
    uint8_t              dma_channel;
    uint8_t              dma_hw_handshake_channel;
#endif /* CONFIG_I2C_DW_DMA_DRIVEN */
};

#define Z_REG_READ(__sz) sys_read##__sz
#define Z_REG_WRITE(__sz) sys_write##__sz
#define Z_REG_SET_BIT sys_set_bit
#define Z_REG_CLEAR_BIT sys_clear_bit
#define Z_REG_TEST_BIT sys_test_bit

#define DEFINE_MM_REG_READ(__reg, __off, __sz)         \
    static inline uint32_t read_##__reg(uint32_t addr) \
    {                                                  \
        return Z_REG_READ(__sz)(addr + __off);         \
    }
#define DEFINE_MM_REG_WRITE(__reg, __off, __sz)                    \
    static inline void write_##__reg(uint32_t data, uint32_t addr) \
    {                                                              \
        Z_REG_WRITE(__sz)(data, addr + __off);                     \
    }

#define DEFINE_SET_BIT_OP(__reg_bit, __reg_off, __bit)    \
    static inline void set_bit_##__reg_bit(uint32_t addr) \
    {                                                     \
        Z_REG_SET_BIT(addr + __reg_off, __bit);           \
    }

#define DEFINE_CLEAR_BIT_OP(__reg_bit, __reg_off, __bit)    \
    static inline void clear_bit_##__reg_bit(uint32_t addr) \
    {                                                       \
        Z_REG_CLEAR_BIT(addr + __reg_off, __bit);           \
    }

#define DEFINE_TEST_BIT_OP(__reg_bit, __reg_off, __bit)   \
    static inline int test_bit_##__reg_bit(uint32_t addr) \
    {                                                     \
        return Z_REG_TEST_BIT(addr + __reg_off, __bit);   \
    }

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* ZEPHYR_DRIVERS_I2C_I2C_DW_H_ */
