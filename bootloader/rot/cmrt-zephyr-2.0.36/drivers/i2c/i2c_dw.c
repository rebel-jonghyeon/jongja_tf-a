/* dw_i2c.c - I2C file for Design Ware */

/*
 * Copyright (c) 2015 Intel Corporation
 * Copyright (c) 2024 SAMSUNG Electronics Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include <stddef.h>
#include <zephyr/types.h>
#include <stdlib.h>
#include <stdbool.h>

#include <drivers/i2c.h>
#include <drivers/i2c_dw_slave.h>
#include <kernel.h>
#include <init.h>
#include <arch/cpu.h>
#include <string.h>

#include <soc.h>
#include <errno.h>
#include <sys/sys_io.h>

#include <sys/util.h>

#ifdef CONFIG_IOAPIC
#include <drivers/interrupt_controller/ioapic.h>
#endif /* CONFIG_IOAPIC */

#include "i2c_dw.h"
#include "i2c_dw_registers.h"
#define LOG_LEVEL CONFIG_I2C_LOG_LEVEL
#include <logging/log.h>
LOG_MODULE_REGISTER(i2c_dw);

#include "i2c-priv.h"

#ifdef CONFIG_I2C_DW_DMA_DRIVEN
#include <drivers/dma.h>
#include "../dma/dw_axi_dmac.h"
#endif /* CONFIG_I2C_DW_DMA_DRIVEN */

bool g_dma_write_cb_called = false;

static inline uint32_t get_regs(const struct device *dev)
{
    return (uint32_t)DEVICE_MMIO_GET(dev);
}

static inline void i2c_dw_data_ask(const struct device *dev)
{
    struct i2c_dw_dev_config *const dw = dev->data;
    uint32_t                        data;
    uint8_t                         tx_empty;
    uint8_t                         rx_empty;
    uint8_t                         cnt;
    uint8_t                         rx_buffer_depth;
    uint8_t                         tx_buffer_depth;
    union ic_comp_param_1_register  ic_comp_param_1;
    uint32_t                        reg_base = get_regs(dev);

    /* No more bytes to request, so command queue is no longer needed */
    if (dw->request_bytes == 0U) {
        clear_bit_intr_mask_tx_empty(reg_base);
        return;
    }

    /* Get the FIFO depth that could be from 2 to 256 from HW spec */
    ic_comp_param_1.raw = read_comp_param_1(reg_base);
    rx_buffer_depth     = ic_comp_param_1.bits.rx_buffer_depth + 1;
    tx_buffer_depth     = ic_comp_param_1.bits.tx_buffer_depth + 1;

    /* How many bytes we can actually ask */
    rx_empty = (rx_buffer_depth - read_rxflr(reg_base)) - dw->rx_pending;

    if (rx_empty < 0) {
        /* RX FIFO expected to be full.
         * So don't request any bytes, yet.
         */
        return;
    }

    /* How many empty slots in TX FIFO (as command queue) */
    tx_empty = tx_buffer_depth - read_txflr(reg_base);

#ifndef CONFIG_I2C_DW_DMA_DRIVEN
    /* Figure out how many bytes we can request */
    cnt = MIN(rx_buffer_depth, dw->request_bytes);
    cnt = MIN(MIN(tx_empty, rx_empty), cnt);
#else
    if (!strcmp(dev->name, DT_LABEL(DT_PATH(soc, i2c_66048000)))) {
        /* Figure out how many bytes we can request */
        cnt = MIN(rx_buffer_depth, dw->request_bytes);
        cnt = MIN(MIN(tx_empty, rx_empty), cnt);
    } else {
        if (dw->request_bytes != (dw->xfr_len % DMA_MSIZE_2)) {
            cnt = DMA_MSIZE_2;
        } else {
            cnt = dw->xfr_len % DMA_MSIZE_2;
        }
    }
#endif /* CONFIG_I2C_DW_DMA_DRIVEN */

    while (cnt > 0) {
        /* Tell controller to get another byte */
        data = IC_DATA_CMD_CMD;

        /* Send RESTART if needed */
        if (dw->xfr_flags & I2C_MSG_RESTART) {
            data |= IC_DATA_CMD_RESTART;
            dw->xfr_flags &= ~(I2C_MSG_RESTART);
        }

        /* After receiving the last byte, send STOP if needed */
        if ((dw->xfr_flags & I2C_MSG_STOP) && (dw->request_bytes == 1U)) {
            data |= IC_DATA_CMD_STOP;
        }

        write_cmd_data(data, reg_base);

        dw->rx_pending++;
        dw->request_bytes--;
        cnt--;
    }
}

static void i2c_dw_data_read(const struct device *dev)
{
    struct i2c_dw_dev_config *const dw       = dev->data;
    uint32_t                        reg_base = get_regs(dev);

    union ic_interrupt_register intr_stat;
    intr_stat.raw = read_intr_stat(reg_base);

    while (test_bit_status_rfne(reg_base) && (dw->xfr_len > 0)) {
        dw->xfr_buf[0] = (uint8_t)read_cmd_data(reg_base);

        dw->xfr_buf++;
        dw->xfr_len--;
        dw->rx_pending--;

        if (dw->xfr_len == 0U) {
            break;
        }
    }

    /* Nothing to receive anymore */
    if (dw->xfr_len == 0U) {
        dw->state &= ~I2C_DW_CMD_RECV;
        return;
    }
}

static uint32_t i2c_dw_data_send(const struct device *dev)
{
    struct i2c_dw_dev_config *const dw       = dev->data;
    uint32_t                        data     = 0U;
    uint32_t                        reg_base = get_regs(dev);

    /* Nothing to send anymore, mask the interrupt */
    if (dw->xfr_len == 0U) {
        clear_bit_intr_mask_tx_empty(reg_base);

        dw->state &= ~I2C_DW_CMD_SEND;

        return 0;
    }

    while (test_bit_status_tfnt(reg_base) && (dw->xfr_len > 0)) {
        /* We have something to transmit to a specific host */
        data = dw->xfr_buf[0];

        /* Send RESTART if needed */
        if (dw->xfr_flags & I2C_MSG_RESTART) {
            data |= IC_DATA_CMD_RESTART;
            dw->xfr_flags &= ~(I2C_MSG_RESTART);
        }

        /* Send STOP if needed */
        if ((dw->xfr_len == 1U) && (dw->xfr_flags & I2C_MSG_STOP)) {
            data |= IC_DATA_CMD_STOP;
        }

        write_cmd_data(data, reg_base);

        dw->xfr_len--;
        dw->xfr_buf++;

        if (test_bit_intr_stat_tx_abrt(reg_base)) {
            return -EIO;
        }
    }

    return 0;
}

static inline void i2c_dw_transfer_complete(const struct device *dev)
{
    struct i2c_dw_dev_config *const dw       = dev->data;
    uint32_t                        value;
    uint32_t                        reg_base = get_regs(dev);

    if (test_bit_con_master_mode(reg_base)) {
        write_intr_mask(DW_DISABLE_ALL_I2C_INT, reg_base);
        k_sem_give(&dw->device_sync_sem);
    } else {
        dw->xfr_buf = dw->xfr_buf - (MAX_XFR_LEN - dw->xfr_len);
        dw->xfr_len = MAX_XFR_LEN;
    }

    value = read_clr_intr(reg_base);
}

static void i2c_dw_isr(void *arg)
{
    const struct device            *port     = (const struct device *)arg;
    struct i2c_dw_dev_config *const dw       = port->data;
    union ic_interrupt_register     intr_stat;
    uint32_t                        value;
    uint32_t                        ret      = 0;
    uint32_t                        reg_base = get_regs(port);

    /* Cache ic_intr_stat for processing, so there is no need to read
     * the register multiple times.
     */
    intr_stat.raw = read_intr_stat(reg_base);

    /*
     * Causes of an interrupt:
     *   - STOP condition is detected
     *   - Transfer is aborted
     *   - Transmit FIFO is empty
     *   - Transmit FIFO has overflowed
     *   - Receive FIFO is full
     *   - Receive FIFO has overflowed
     *   - Received FIFO has underrun
     *   - Transmit data is required (tx_req)
     *   - Receive data is available (rx_avail)
     */

    LOG_DBG("I2C: interrupt received");

    /* Check if we are configured as a master device */
    if (test_bit_con_master_mode(reg_base)) {
        /* Bail early if there is any error. */
        if ((DW_INTR_STAT_TX_ABRT | DW_INTR_STAT_TX_OVER |
             DW_INTR_STAT_RX_OVER | DW_INTR_STAT_RX_UNDER) & intr_stat.raw) {
            dw->state = I2C_DW_CMD_ERROR;
            goto done;
        }

#ifdef CONFIG_I2C_DW_DMA_DRIVEN
        if (strcmp(port->name, DT_LABEL(DT_PATH(soc, i2c_66048000)))) {
            /* Clear interrupt masks and flags */
            goto done;
        }
#endif /* CONFIG_I2C_DW_DMA_DRIVEN */

        /* Check if the RX FIFO reached threshold */
        if (intr_stat.bits.rx_full) {
            i2c_dw_data_read(port);
        }

        /* Check if the TX FIFO is ready for commands.
         * TX FIFO also serves as command queue where read requests
         * are written to TX FIFO.
         */
        if (intr_stat.bits.tx_empty) {
            if ((dw->xfr_flags & I2C_MSG_RW_MASK) == I2C_MSG_WRITE) {
                ret = i2c_dw_data_send(port);
            } else {
                i2c_dw_data_ask(port);
            }

            /* If STOP is not expected, finish processing this
             * message if there is nothing left to do anymore.
             */
            if (((dw->xfr_len == 0U) && !(dw->xfr_flags & I2C_MSG_STOP)) ||
                (ret != 0)) {
                goto done;
            }
        }
    } else {
        if (intr_stat.bits.rx_full) {
            i2c_dw_data_read(port);
        }
    }

    /* STOP detected: finish processing this message */
    if (intr_stat.bits.stop_det) {
        value = read_clr_stop_det(reg_base);
        goto done;
    }

    return;

done:
    i2c_dw_transfer_complete(port);
}

#ifdef CONFIG_I2C_DW_DMA_DRIVEN
static void type_conversion(uint8_t *xfr_buf, uint16_t *buf16, uint32_t xfr_len)
{
    for (uint32_t i = 0; i < xfr_len; i++) {
        buf16[i] = (uint16_t)xfr_buf[i];

        if (i == xfr_len - 1) {
            buf16[i] |= IC_DATA_CMD_STOP;
        }
    }
}

static void i2c_dw_dma_transfer_done(
        const struct device *dma_dev,
        void                *user_data,
        uint32_t             channel,
        int                  error_code)
{
    if (dma_dev == NULL) {
        printk("Wrong device\n");
        return;
    }

    if (user_data == NULL) {
        printk("No user_data\n");
        return;
    }

    const struct device *dev     = (const struct device *)user_data;
    struct i2c_dw_dev_config *dw = dev->data;
    uint32_t reg_base = get_regs(dev);

    ARG_UNUSED(dev);
    ARG_UNUSED(channel);

    uint32_t key = irq_lock();

    union ic_interrupt_register intr_stat;
    intr_stat.raw = read_intr_stat(reg_base);

    /* Error detected */
    if ((DW_INTR_STAT_TX_ABRT | DW_INTR_STAT_TX_OVER | DW_INTR_STAT_RX_OVER |
         DW_INTR_STAT_RX_UNDER) & intr_stat.raw) {
        dw->state = I2C_DW_CMD_ERROR;

        i2c_dw_transfer_complete(dev);

        irq_unlock(key);
        return;
    }

    if (error_code < 0) {
        write_intr_mask(DW_DISABLE_ALL_I2C_INT, reg_base);

        irq_unlock(key);

        dw->state = I2C_DW_CMD_ERROR;

        k_sem_give(&dw->device_sync_sem);
        return;
    }

    irq_unlock(key);

    if ((dw->xfr_flags & I2C_MSG_RW_MASK) == I2C_MSG_WRITE) {
        dw->xfr_len = 0;
        g_dma_write_cb_called = true;
    }
}

static uint32_t i2c_dw_dma_write_start(const struct device *dev)
{
    if (dev == NULL) {
        return -EINVAL;
    }

    struct i2c_dw_dev_config *dw       = dev->data;
    uint32_t                  reg_base = get_regs(dev);
    uint32_t                  retval;

    if (dw->dma_channel == VAL_DMA_CH_RANGE) {
        return -EINVAL;
    }

    struct dma_config       dma_cfg = {0};
    struct dma_block_config dma_blk = {0};

    dma_cfg.channel_direction   = MEMORY_TO_PERIPHERAL;
    dma_cfg.source_data_size    = sizeof(uint16_t);
    dma_cfg.dest_data_size      = sizeof(uint16_t);
    dma_cfg.source_burst_length = DMA_MSIZE_2;
    dma_cfg.dest_burst_length   = DMA_MSIZE_2;
    dma_cfg.user_data           = (void *)dev;
    dma_cfg.dma_callback        = i2c_dw_dma_transfer_done;
    dma_cfg.block_count         = 1;
    dma_cfg.head_block          = &dma_blk;
    dma_cfg.dma_slot            = dw->dma_hw_handshake_channel;

    uint16_t *buf16 = k_aligned_alloc(sizeof(void *),
                                      sizeof(uint16_t) * dw->xfr_len);
    type_conversion(dw->xfr_buf, buf16, dw->xfr_len);
    DCACHE_FLUSH(buf16, sizeof(uint16_t) * dw->xfr_len);

    dma_blk.block_size      = dw->xfr_len * sizeof(uint16_t);
    dma_blk.source_address  = (uint32_t)buf16;
    dma_blk.source_addr_adj = DMA_ADDR_ADJ_INCREMENT;
    dma_blk.dest_address    = (uint32_t)(reg_base + DW_IC_REG_DATA_CMD);
    dma_blk.dest_addr_adj   = DMA_ADDR_ADJ_NO_CHANGE;

    DCACHE_FLUSH((uint32_t)&dma_cfg, sizeof(struct dma_config));
    DCACHE_FLUSH((uint32_t)&dma_blk, sizeof(struct dma_block_config));

    retval = dma_config(dw->dma_dev, dw->dma_channel, &dma_cfg);
    if (retval != 0) {
        printk("DMA config failed\n");
        return -EINVAL;
    }

    retval = dma_start(dw->dma_dev, dw->dma_channel);
    if (retval == 0) {
        printk("DMA started\n");
    } else if (retval == -EBUSY) {
        printk("DMA channel#%d is busy!!\n", dw->dma_channel);
    } else {
        printk("retval = %d\n", retval);
        printk("DMA start failed\n");
        return -EINVAL;
    }

    write_intr_mask(DW_ENABLE_TX_INT_I2C_MASTER, reg_base);
    do {
        if(k_sem_take(&dw->device_sync_sem, K_FOREVER) == 0) {
            if(g_dma_write_cb_called == true) {
                g_dma_write_cb_called = false;
                printk("DMA callback called\n");
                break;
            }
            write_intr_mask(DW_ENABLE_TX_INT_I2C_MASTER, reg_base);
        }
    } while(1);

    k_free(buf16);

    return 0;
}

static uint32_t i2c_dw_dma_read_start(const struct device *dev)
{
    if (dev == NULL) {
        return -EINVAL;
    }

    struct i2c_dw_dev_config *dw       = dev->data;
    uint32_t                  reg_base = get_regs(dev);
    uint32_t                  retval;

    if (dw->dma_channel == VAL_DMA_CH_RANGE) {
        printk("ERR: Wrong Channel!!\n");
        return -EINVAL;
    }

    struct dma_config       dma_cfg = {0};
    struct dma_block_config dma_blk = {0};

    dma_cfg.channel_direction   = PERIPHERAL_TO_MEMORY;
    dma_cfg.source_data_size    = sizeof(uint8_t);
    dma_cfg.dest_data_size      = sizeof(uint8_t);
    dma_cfg.source_burst_length = DMA_MSIZE_2;
    dma_cfg.dest_burst_length   = DMA_MSIZE_2;
    dma_cfg.user_data           = (void *)dev;
    dma_cfg.dma_callback        = i2c_dw_dma_transfer_done;
    dma_cfg.block_count         = 1;
    dma_cfg.head_block          = &dma_blk;
    dma_cfg.dma_slot            = dw->dma_hw_handshake_channel;

    dma_blk.block_size      = dw->xfr_len;
    dma_blk.source_address  = (uint32_t)(reg_base + DW_IC_REG_DATA_CMD);
    dma_blk.source_addr_adj = DMA_ADDR_ADJ_NO_CHANGE;
    dma_blk.dest_address    = (uint32_t)dw->xfr_buf;
    dma_blk.dest_addr_adj   = DMA_ADDR_ADJ_INCREMENT;

    DCACHE_FLUSH((uint32_t)&dma_cfg, sizeof(struct dma_config));
    DCACHE_FLUSH((uint32_t)&dma_blk, sizeof(struct dma_block_config));

    retval = dma_config(dw->dma_dev, dw->dma_channel, &dma_cfg);
    if (retval != 0) {
        printk("DMA config failed\n");
        return -EINVAL;
    }

    retval = dma_start(dw->dma_dev, dw->dma_channel);
    if (retval == 0) {
        printk("DMA started\n");
    } else if (retval == -EBUSY) {
        printk("DMA channel#%d is busy!!\n", dw->dma_channel);
    } else {
        printk("retval = %d\n", retval);
        printk("DMA start failed\n");
        return -EINVAL;
    }

    uint32_t cnt = 1;
    uint32_t xfr_len = dw->xfr_len;

    while (dw->xfr_len > 0) {
        i2c_dw_data_ask(dev);

        while (1) {
            if (read_rxflr(reg_base) == DMA_MSIZE_2) {
                write_intr_mask(DW_INTR_STAT_RX_FULL, reg_base);
                break;
            }

            if (cnt > (xfr_len / DMA_MSIZE_2) &&
                (read_rxflr(reg_base) == (xfr_len % DMA_MSIZE_2))) {
                write_rx_tl(xfr_len % DMA_MSIZE_2 - 1, reg_base);
                write_intr_mask(DW_INTR_STAT_RX_FULL, reg_base);
                break;
            }
        }

        /* Waiting for I2C ISR that clears i2c intr masks and flags */
        k_sem_take(&dw->device_sync_sem, K_FOREVER);

        dw->xfr_len = dw->request_bytes;

        dw->rx_pending = 0;

        cnt++;
    }

    if (dw->request_bytes != 0) {
        printk("request_bytes should be zero.\n");
    }

    return 0;
}
#endif /* CONFIG_I2C_DW_DMA_DRIVEN */

static uint32_t i2c_dw_setup(const struct device *dev, uint16_t slave_address)
{
    struct i2c_dw_dev_config *const dw = dev->data;
    uint32_t                        value;
    union ic_con_register           ic_con;
    union ic_tar_register           ic_tar;
    uint32_t                        reg_base = get_regs(dev);

    ic_con.raw = 0U;

    /* Disable the device controller to be able set TAR */
    clear_bit_enable_en(reg_base);

    /* Disable interrupts */
    write_intr_mask(0, reg_base);

    /* Clear interrupts */
    value = read_clr_intr(reg_base);

    /* Set master or slave mode - (initialization = slave) */
    if (I2C_MODE_MASTER & dw->app_config) {
        /*
         * Make sure to set both the master_mode and slave_disable_bit
         * to both 0 or both 1
         */
        LOG_DBG("I2C: host configured as Master Device");
        ic_con.bits.master_mode   = 1U;
        ic_con.bits.slave_disable = 1U;
    }

    ic_con.bits.restart_en = 1U;

    /* Set addressing mode - (initialization = 7 bit) */
    if (I2C_ADDR_10_BITS & dw->app_config) {
        LOG_DBG("I2C: using 10-bit address");
        ic_con.bits.addr_master_10bit = 1U;
        ic_con.bits.addr_slave_10bit  = 1U;
    }

    /* Setup the clock frequency and speed mode */
    switch (I2C_SPEED_GET(dw->app_config)) {
        case I2C_SPEED_STANDARD:
            LOG_DBG("I2C: speed set to STANDARD");
            write_ss_scl_lcnt(dw->lcnt, reg_base);
            write_ss_scl_hcnt(dw->hcnt, reg_base);
            ic_con.bits.speed = I2C_DW_SPEED_STANDARD;
            break;
        case I2C_SPEED_FAST:
            __fallthrough;
        case I2C_SPEED_FAST_PLUS:
            LOG_DBG("I2C: speed set to FAST or FAST_PLUS");
            write_fs_scl_lcnt(dw->lcnt, reg_base);
            write_fs_scl_hcnt(dw->hcnt, reg_base);
            ic_con.bits.speed = I2C_DW_SPEED_FAST;
            break;
        case I2C_SPEED_HIGH:
            printk("High speed mode is not supported\n");
            break;
        default:
            LOG_DBG("I2C: invalid speed requested");
            return -EINVAL;
    }

    LOG_DBG("I2C: lcnt = %d", dw->lcnt);
    LOG_DBG("I2C: hcnt = %d", dw->hcnt);

    /* Set the IC_CON register */
    write_con(ic_con.raw, reg_base);

    /* Set RX fifo threshold level.
     * Setting it to zero automatically triggers interrupt
     * RX_FULL whenever there is data received.
     */
#ifndef CONFIG_I2C_DW_DMA_DRVIEN
    write_rx_tl(0, reg_base);
#else
    if (!strcmp(dev->name, DT_LABEL(DT_PATH(soc, i2c_66048000)))) {
        write_rx_tl(0, reg_base);
    } else {
        write_rx_tl(DMA_MSIZE_2 - 1, reg_base);
    }
#endif /* CONFIG_I2C_DW_DMA_DRIVEN */

    /* Set TX fifo threshold level.
     * TX_EMPTY interrupt is triggered only when the
     * TX FIFO is truly empty. So that we can let
     * the controller do the transfers for longer period
     * before we need to fill the FIFO again. This may
     * cause some pauses during transfers, but this keeps
     * the device from interrupting often.
     */
    write_tx_tl(0, reg_base);

    ic_tar.raw = read_tar(reg_base);

    if (test_bit_con_master_mode(reg_base)) {
        /* Set address of target slave */
        ic_tar.bits.ic_tar = slave_address;
    } else {
        /* Set slave address for device */
        write_sar(slave_address, reg_base);
    }

    /* If I2C is being operated in master mode and I2C_DYNAMIC_TAR_UPDATE
     * configuration parameter is set to Yes (1), the ic_10bitaddr_master
     * bit in ic_tar register would control whether the DW_apb_i2c starts
     * its transfers in 7-bit or 10-bit addressing mode.
     */
    if (I2C_MODE_MASTER & dw->app_config) {
        if (I2C_ADDR_10_BITS & dw->app_config) {
            ic_tar.bits.ic_10bitaddr_master = 1U;
        } else {
            ic_tar.bits.ic_10bitaddr_master = 0U;
        }
    }

    write_tar(ic_tar.raw, reg_base);

    return 0;
}

static int i2c_dw_transfer(
        const struct device *dev,
        struct i2c_msg      *msgs,
        uint8_t              num_msgs,
        uint16_t             slave_address)
{
    struct i2c_dw_dev_config *const dw       = dev->data;
    struct i2c_msg                 *cur_msg  = msgs;
    uint8_t                         msg_left = num_msgs;
    uint8_t                         pflags;
    uint32_t                        ret;
    uint32_t                        retval   = 1;
    uint32_t                        reg_base = get_regs(dev);

    __ASSERT_NO_MSG(msgs);
    if (!num_msgs) {
        return 0;
    }

    /* First step, check if there is current activity */
    if (test_bit_status_activity(reg_base) || (dw->state & I2C_DW_BUSY)) {
        return -EIO;
    }

    dw->state |= I2C_DW_BUSY;

    ret = i2c_dw_setup(dev, slave_address);
    if (ret) {
        dw->state = I2C_DW_STATE_READY;
        return ret;
    }

    /* Enable controller */
    set_bit_enable_en(reg_base);

    /*
     * While waiting at device_sync_sem, kernel can switch to idle
     * task which in turn can call pm_system_suspend() hook of Power
     * Management App (PMA).
     * pm_device_busy_set() call here, would indicate to PMA that it should
     * not execute PM policies that would turn off this ip block, causing an
     * ongoing hw transaction to be left in an inconsistent state.
     * Note : This is just a sample to show a possible use of the API, it is
     * upto the driver expert to see, if he actually needs it here, or
     * somewhere else, or not needed as the driver's suspend()/resume()
     * can handle everything
     */
    pm_device_busy_set(dev);

    /* Process all the messages */
    while (msg_left > 0) {
        pflags = dw->xfr_flags;

        dw->xfr_buf    = cur_msg->buf;
        dw->xfr_len    = cur_msg->len;
        dw->xfr_flags  = cur_msg->flags;
        dw->rx_pending = 0U;

        /* Need to RESTART if changing transfer direction */
        if ((pflags & I2C_MSG_RW_MASK) != (dw->xfr_flags & I2C_MSG_RW_MASK)) {
            dw->xfr_flags |= I2C_MSG_RESTART;
        }

        /* Send STOP if this is the last message */
        if (msg_left == 1U) {
            dw->xfr_flags |= I2C_MSG_STOP;
        }

        dw->state &= ~(I2C_DW_CMD_SEND | I2C_DW_CMD_RECV);

        if ((dw->xfr_flags & I2C_MSG_RW_MASK) == I2C_MSG_WRITE) {
            dw->state |= I2C_DW_CMD_SEND;
            dw->request_bytes = 0U;
#ifdef CONFIG_I2C_DW_DMA_DRIVEN
            if (strcmp(dev->name, DT_LABEL(DT_PATH(soc, i2c_66048000)))) {
                retval = i2c_dw_dma_write_start(dev);
            }
#endif /* CONFIC_I2C_DW_DMA_DRIVEN */
        } else {
            dw->state |= I2C_DW_CMD_RECV;
            dw->request_bytes = dw->xfr_len;
#ifdef CONFIG_I2C_DW_DMA_DRIVEN
            if (strcmp(dev->name, DT_LABEL(DT_PATH(soc, i2c_66048000)))) {
                retval = i2c_dw_dma_read_start(dev);
            }
#endif /* CONFIG_I2C_DW_DMA_DRIVEN */
        }

#ifdef CONFIG_I2C_DW_DMA_DRIVEN
        if (!strcmp(dev->name, DT_LABEL(DT_PATH(soc, i2c_66048000)))) {
#endif /* CONFIG_I2C_DW_DMA_DRIVEN */
            /* Enable interrupts to trigger ISR */
            if (test_bit_con_master_mode(reg_base) && retval) {
                /* Enable necessary interrupts */
                write_intr_mask((DW_ENABLE_TX_INT_I2C_MASTER |
                                 DW_ENABLE_RX_INT_I2C_MASTER), reg_base);
            } else if (!test_bit_con_master_mode(reg_base) && retval) {
                /* Enable necessary interrupts */
                write_intr_mask(DW_ENABLE_TX_INT_I2C_SLAVE, reg_base);
            }

            /* Wait for transfer to be done */
            k_sem_take(&dw->device_sync_sem, K_FOREVER);
#ifdef CONFIG_I2C_DW_DMA_DRIVEN
        }
#endif /* CONFIG_I2C_DW_DMA_DRIVEN */

        if (dw->state & I2C_DW_CMD_ERROR) {
            ret = -EIO;
            break;
        }

        /* Something wrong if there is something left to do */
        if (dw->xfr_len > 0) {
            ret = -EIO;
            break;
        }

        cur_msg++;
        msg_left--;
    }

    pm_device_busy_clear(dev);

    dw->state = I2C_DW_STATE_READY;

    return ret;
}

static int i2c_dw_runtime_configure(
        const struct device *dev,
        uint32_t config)
{
    struct i2c_dw_dev_config *const dw       = dev->data;
    uint32_t                        value    = 0U;
    uint32_t                        rc       = 0U;
    uint32_t                        reg_base = get_regs(dev);

    dw->app_config = config;

    /* Make sure we have a supported speed for the DesignWare model */
    /* and have setup the clock frequency and speed mode */
    switch (I2C_SPEED_GET(dw->app_config)) {
        case I2C_SPEED_STANDARD:
            /* Following the directions on DW spec page 59, IC_SS_SCL_LCNT
             * must have register values larger than IC_FS_SPKLEN + 7
             */
            if (I2C_STD_LCNT <= (read_fs_spklen(reg_base) + 7)) {
                value = read_fs_spklen(reg_base) + 8;
            } else {
                value = I2C_STD_LCNT;
            }

            dw->lcnt = value;

            /* Following the directions on DW spec page 59, IC_SS_SCL_HCNT
             * must have register values larger than IC_FS_SPKLEN + 5
             */
            if (I2C_STD_HCNT <= (read_fs_spklen(reg_base) + 5)) {
                value = read_fs_spklen(reg_base) + 6;
            } else {
                value = I2C_STD_HCNT;
            }

            dw->hcnt = value;
            break;
        case I2C_SPEED_FAST:
            /*
             * Following the directions on DW spec page 59, IC_FS_SCL_LCNT
             * must have register values larger than IC_FS_SPKLEN + 7
             */
            if (I2C_FS_LCNT <= (read_fs_spklen(reg_base) + 7)) {
                value = read_fs_spklen(reg_base) + 8;
            } else {
                value = I2C_FS_LCNT;
            }

            dw->lcnt = value;

            /*
             * Following the directions on DW spec page 59, IC_FS_SCL_HCNT
             * must have register values larger than IC_FS_SPKLEN + 5
             */
            if (I2C_FS_HCNT <= (read_fs_spklen(reg_base) + 5)) {
                value = read_fs_spklen(reg_base) + 6;
            } else {
                value = I2C_FS_HCNT;
            }

            dw->hcnt = value;
            break;
        case I2C_SPEED_FAST_PLUS:
            /*
             * Following the directions on DW spec page 59, IC_FS_SCL_LCNT
             * must have register values larger than IC_FS_SPKLEN + 7
             */
            if (I2C_FS_LCNT <= (read_fs_spklen(reg_base) + 7)) {
                value = read_fs_spklen(reg_base) + 8;
            } else {
                value = I2C_FSP_LCNT;
            }

            dw->lcnt = value;

            /*
             * Following the directions on DW spec page 59, IC_FS_SCL_HCNT
             * must have register values larger than IC_FS_SPKLEN + 5
             */
            if (I2C_FS_HCNT <= (read_fs_spklen(reg_base) + 5)) {
                value = read_fs_spklen(reg_base) + 6;
            } else {
                value = I2C_FSP_HCNT;
            }

            dw->hcnt = value;
            break;
        case I2C_SPEED_HIGH:
            printk("High speed mode is not supported\n");
            break;
        default:
            rc = -EINVAL;
    }

    /*
     * Clear any interrupts currently waiting in the controller
     */
    value = read_clr_intr(reg_base);

    return rc;
}

static int i2c_dw_configure_slave(
        const struct device *dev,
        uint32_t config,
        uint8_t *rx_buf)
{
    i2c_dw_runtime_configure(dev, config);

    struct i2c_dw_dev_config *const dw       = dev->data;
    uint32_t                        value    = 0U;
    uint32_t                        reg_base = get_regs(dev);

    dw->app_config = config;

    dw->xfr_buf = rx_buf;
    dw->xfr_len = MAX_XFR_LEN;

    uint8_t num;

    num = *(dev->name + I2C_INDEX_CHAR_ORDER);

    switch (num) {
        case '0':
            dw->slave_addr = DT_INST_PROP(DT_INST_I2C_0, slave_address);
            break;
        case '1':
            dw->slave_addr = DT_INST_PROP(DT_INST_I2C_1, slave_address);
            break;
        case '2':
            dw->slave_addr = DT_INST_PROP(DT_INST_I2C_2, slave_address);
            break;
        case '3':
            dw->slave_addr = DT_INST_PROP(DT_INST_I2C_3, slave_address);
            break;
        default:
            dw->slave_addr = DT_INST_PROP(DT_INST_BOOT_I2C, slave_address);
            break;
    }

    i2c_dw_setup(dev, dw->slave_addr);

    value = read_clr_intr(reg_base);

    set_bit_enable_en(reg_base);

    write_intr_mask(DW_ENABLE_RX_INT_I2C_SLAVE, reg_base);

    return 0;
}

static const struct i2c_dw_driver_api funcs = {
    .i2c_driver_api.configure = i2c_dw_runtime_configure,
    .i2c_driver_api.transfer  = i2c_dw_transfer,
    .configure_slave = i2c_dw_configure_slave,
};

static int i2c_dw_initialize(const struct device *dev)
{
    const struct i2c_dw_rom_config *const rom = dev->config;
    struct i2c_dw_dev_config             *dw  = dev->data;
    union ic_con_register                 ic_con;
    uint32_t                              reg_base = get_regs(dev);
    uint32_t                              val;

#if DT_ANY_INST_ON_BUS_STATUS_OKAY(pcie)
    if (rom->pcie) {
        struct pcie_mbar mbar;

        if (!pcie_probe(rom->pcie_bdf, rom->pcie_id)) {
            return -EINVAL;
        }

        pcie_probe_mbar(rom->pcie_bdf, 0, &mbar);
        pcie_set_cmd(rom->pcie_bdf, PCIE_CONF_CMDSTAT_MEM, true);

        device_map(DEVICE_MMIO_RAM_PTR(dev),
                   mbar.phys_addr,
                   mbar.size,
                   K_MEM_CACHE_NONE);
    } else
#endif /* DT_ANY_INST_ON_BUS_STATUS_OKAY(pcie) */
    {
        DEVICE_MMIO_MAP(dev, K_MEM_CACHE_NONE);
    }

    k_sem_init(&dw->device_sync_sem, 0, K_SEM_MAX_LIMIT);

    clear_bit_enable_en(reg_base);

    /* verify that we have a valid DesignWare register first */
    if (read_comp_type(reg_base) != I2C_DW_MAGIC_KEY) {
        LOG_DBG(
            "I2C: DesignWare magic key not found, check base "
            "address. Stopping initialization");
        return -EIO;
    }

    /*
     * grab the default value on initialization.  This should be set to the
     * IC_MAX_SPEED_MODE in the hardware.  If it does support high speed we
     * can move provide support for it
     */
    ic_con.raw = read_con(reg_base);
    if (ic_con.bits.speed == I2C_DW_SPEED_HIGH) {
        LOG_DBG("I2C: high speed supported");
        dw->support_hs_mode = true;
    } else {
        LOG_DBG("I2C: high speed NOT supported");
        dw->support_hs_mode = false;
    }

    rom->config_func(dev);

    dw->app_config = I2C_MODE_MASTER | i2c_map_dt_bitrate(rom->bitrate);

    if (i2c_dw_runtime_configure(dev, dw->app_config) != 0) {
        LOG_DBG("I2C: Cannot set default configuration");
        return -EIO;
    }

    dw->state = I2C_DW_STATE_READY;

    /* gpio setting for connection between I2C_0~3 and EEPROM */
    val = sys_read32(PINMUX_FIELD_3);
    val &= PINMUX_FIELD_3_I2C_CLEAR;
    val |= PINMUX_FIELD_3_I2C_EN;
    sys_write32(val, PINMUX_FIELD_3);

    val = sys_read32(PINMUX_FIELD_4);
    val &= PINMUX_FIELD_4_I2C_CLEAR;
    val |= PINMUX_FIELD_4_I2C_EN;
    sys_write32(val, PINMUX_FIELD_4);

    return 0;
}

#ifdef CONFIG_I2C_DW_DMA_DRIVEN
#define DMA_HANDSHAKE_CHANNELS(n) \
    .dma_dev = DEVICE_DT_GET(DT_INST_DMAS_CTLR_BY_NAME(n, dma)),            \
    .dma_channel = DT_INST_DMAS_CELL_BY_NAME(n, dma, channel),              \
    .dma_hw_handshake_channel = DT_INST_DMAS_CELL_BY_NAME(n, dma, request)
#endif /* CONFIG_I2C_DMA_DRIVEN */

#define I2C_DW_INIT_PCIE0(n)
#define I2C_DW_INIT_PCIE1(n)         \
    .pcie = true,                    \
    .pcie_bdf = DT_INST_REG_ADDR(n), \
    .pcie_id = DT_INST_REG_SIZE(n),
#define I2C_DW_INIT_PCIE(n) \
    _CONCAT(I2C_DW_INIT_PCIE, DT_INST_ON_BUS(n, pcie))(n)

#define I2C_DW_IRQ_FLAGS_SENSE0(n) 0
#define I2C_DW_IRQ_FLAGS_SENSE1(n) DT_INST_IRQ(n, sense)
#define I2C_DW_IRQ_FLAGS(n) \
    _CONCAT(I2C_DW_IRQ_FLAGS_SENSE, DT_INST_IRQ_HAS_CELL(n, sense))(n)

/* not PCI(e) */
#define I2C_DW_IRQ_CONFIG_PCIE0(n)                        \
    static void i2c_config_##n(const struct device *port) \
    {                                                     \
        ARG_UNUSED(port);                                 \
        IRQ_CONNECT(                                      \
            DT_INST_IRQN(n),                              \
            DT_INST_IRQ(n, priority),                     \
            i2c_dw_isr,                                   \
            DEVICE_DT_INST_GET(n),                        \
            I2C_DW_IRQ_FLAGS(n));                         \
        irq_enable(DT_INST_IRQN(n));                      \
    }

/* PCI(e) with auto IRQ detection */
#define I2C_DW_IRQ_CONFIG_PCIE1(n)                              \
    static void i2c_config_##n(const struct device *port)       \
    {                                                           \
        ARG_UNUSED(port);                                       \
        BUILD_ASSERT(                                           \
            DT_INST_IRQN(n) == PCIE_IRQ_DETECT,                 \
            "Only runtime IRQ configuration is supported");     \
        BUILD_ASSERT(                                           \
            IS_ENABLED(CONFIG_DYNAMIC_INTERRUPTS),              \
            "DW I2C PCI needs CONFIG_DYNAMIC_INTERRUPTS");      \
        unsigned int irq = pcie_alloc_irq(DT_INST_REG_ADDR(n)); \
        if (irq == PCIE_CONF_INTR_IRQ_NONE) {                   \
            return;                                             \
        }                                                       \
        irq_connect_dynamic(                                    \
            irq,                                                \
            DT_INST_IRQ(n, priority),                           \
            (void (*)(const void *))i2c_dw_isr,                 \
            DEVICE_DT_INST_GET(n),                              \
            I2C_DW_IRQ_FLAGS(n));                               \
        pcie_irq_enable(DT_INST_REG_ADDR(n), irq);              \
    }

#define I2C_DW_IRQ_CONFIG(n) \
    _CONCAT(I2C_DW_IRQ_CONFIG_PCIE, DT_INST_ON_BUS(n, pcie))(n)

#ifdef CONFIG_I2C_DW_DMA_DRIVEN
#define I2C_DEVICE_INIT_DW(n)                                   \
    static void i2c_config_##n(const struct device *port);      \
    static const struct i2c_dw_rom_config i2c_config_dw_##n = { \
        DEVICE_MMIO_ROM_INIT(DT_DRV_INST(n)),                   \
        .config_func = i2c_config_##n,                          \
        .bitrate     = DT_INST_PROP(n, clock_frequency),        \
        I2C_DW_INIT_PCIE(n)};                                   \
    static struct i2c_dw_dev_config i2c_##n##_runtime = {       \
        DMA_HANDSHAKE_CHANNELS(n)};                             \
    DEVICE_DT_INST_DEFINE(                                      \
        n,                                                      \
        &i2c_dw_initialize,                                     \
        NULL,                                                   \
        &i2c_##n##_runtime,                                     \
        &i2c_config_dw_##n,                                     \
        POST_KERNEL,                                            \
        CONFIG_KERNEL_INIT_PRIORITY_DEVICE,						\
        &funcs);                                                \
    I2C_DW_IRQ_CONFIG(n)
#else
#define I2C_DEVICE_INIT_DW(n)                                   \
    static void i2c_config_##n(const struct device *port);      \
    static const struct i2c_dw_rom_config i2c_config_dw_##n = { \
        DEVICE_MMIO_ROM_INIT(DT_DRV_INST(n)),                   \
        .config_func = i2c_config_##n,                          \
        .bitrate     = DT_INST_PROP(n, clock_frequency),        \
        I2C_DW_INIT_PCIE(n)};                                   \
    static struct i2c_dw_dev_config i2c_##n##_runtime;          \
    DEVICE_DT_INST_DEFINE(                                      \
        n,                                                      \
        &i2c_dw_initialize,                                     \
        NULL,                                                   \
        &i2c_##n##_runtime,                                     \
        &i2c_config_dw_##n,                                     \
        POST_KERNEL,                                            \
        CONFIG_KERNEL_INIT_PRIORITY_DEVICE,						\
        &funcs);                                                \
    I2C_DW_IRQ_CONFIG(n)
#endif /* CONFIG_I2C_DW_DMA_DRIVEN */

DT_INST_FOREACH_STATUS_OKAY(I2C_DEVICE_INIT_DW)
