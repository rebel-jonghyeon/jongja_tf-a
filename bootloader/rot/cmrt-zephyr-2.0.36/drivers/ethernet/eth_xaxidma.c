/*
 * Copyright (c) 2020-2023 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

#define DT_DRV_COMPAT xlnx_axi_eth

#include <kernel.h>
#include <stdbool.h>
#include <errno.h>
#include <stddef.h>
#include <stdalign.h>
#include <string.h>
#include <assert.h>

#include <net/ethernet.h>
#include <net/net_pkt.h>
#include <net/net_if.h>
#include <net/mii.h>
#include <device.h>
#include <soc.h>
#include <ethernet/eth_stats.h>
#include <sys/util.h>
#include <drivers/cmrt/dd.h>
#include <drivers/cmrt/dmac.h>
#include <drivers/cmrt/sic_reg.h>
#include "eth_xaxidma_priv.h"

#define LOG_MODULE_NAME eth_xaxidma
#define LOG_LEVEL CONFIG_ETHERNET_LOG_LEVEL
#include <logging/log.h>
LOG_MODULE_REGISTER(LOG_MODULE_NAME);

/*
 * The driver supports multiple ethernet instances. The first release only
 * defines one instance. All the driver functions use the dev instance for
 * operations.
 *
 * Initialization order:
 * 1. eth_xaxidma_dev_init() is called at kernel init. It only resets the HW
 *    and sets the MAC address based on the configuration.
 * 2. eth_xaxidma_init() is called at startup via net_if_init. It does the
 *    normal Ethernet device init as required by the kernel.
 * 3. eth_xaxidma_start() is called last via net_if_post_init. Start can also
 *    be called separately as part of the Ethernet API. It sets up the DMA
 *    queues, enables interrupts and sets up the Ethernet HW as configured.
 *
 * Sending packets:
 * 1. Ethernet API function eth_xaxidma_send() is called by one of the traffic
 *    class threads. By default there's only one. Send sets up the DMAC TX
 *    tail BD (buffer descriptor) and calls eth_xaxidma_send_pkt() to copy the
 *    packet data from SRAM net_pkt to DDR.
 * 2. AXI DMA sends the packet to Ethernet HW to send it to the wire.
 *    Interrupt handler eth_xaxidma_tx_isr() is called to signal completed
 *    transmission.
 * 3. The send thread wakes up again and checks the result of the transmit.
 *    Error statistics is updated in the driver, the general ethernet layer
 *    takes care of the normal stats updates.
 *
 * Receiving packets:
 * 1. Interrupt handler eth_xaxidma_rx_isr() is called to signal for incoming
 *    packet(s). It only checks the possible errors and wakes up the receive
 *    thread.
 * 2. eth_xaxidma_rx_thread() calls eth_xaxidma_recv() to process the packet
 *    at current RX BD. The packet is copied from DDR to a net_pkt in SRAM
 *    by eth_xaxidma_recv_pkt().
 * 3. If all is good and eth_xaxidma_recv() returns a packet pointer, this
 *    packet is given to the network stack by calling net_recv_data().
 */

#define eth_read32(o) sys_read32(dev_conf->eth_base + (o))
#define dma_read32(o) sys_read32(dev_conf->dma_base + (o))
#define dtx_read32(o) sys_read32(dev_conf->dma_base + XAXIDMA_TX_OFFSET + (o))
#define drx_read32(o) sys_read32(dev_conf->dma_base + XAXIDMA_RX_OFFSET + (o))
#define eth_write32(v, o) sys_write32((v), dev_conf->eth_base + (o))
#define dma_write32(v, o) sys_write32((v), dev_conf->dma_base + (o))
#define dtx_write32(v, o) sys_write32((v), dev_conf->dma_base + XAXIDMA_TX_OFFSET + (o))
#define drx_write32(v, o) sys_write32((v), dev_conf->dma_base + XAXIDMA_RX_OFFSET + (o))

static int eth_xaxidma_phy_wait(const struct device *dev)
{
	struct eth_xaxidma_config *dev_conf = DEV_CFG(dev);

	/* Wait until MDIO is ready. */
	for (int i = 0; i < 1000; i++) {
		uint32_t val = eth_read32(XAE_MDIO_MCR_OFFSET);
		if (val & XAE_MDIO_MCR_READY_MASK) {
			/* Ready for new transaction. */
			return 0;
		}
		k_sleep(K_MSEC(1));
	}
	return -EAGAIN;
}

static int eth_xaxidma_phy_read(const struct device *dev, uint32_t reg, uint32_t *val)
{
	struct eth_xaxidma_config *dev_conf = DEV_CFG(dev);

	int res = eth_xaxidma_phy_wait(dev);
	if (res) {
		return res;
	}
	eth_write32((((dev_conf->phy_id << XAE_MDIO_MCR_PHYAD_SHIFT) &
		      XAE_MDIO_MCR_PHYAD_MASK) |
		     ((reg << XAE_MDIO_MCR_REGAD_SHIFT) &
		      XAE_MDIO_MCR_REGAD_MASK) |
		     XAE_MDIO_MCR_INITIATE_MASK |
		     XAE_MDIO_MCR_OP_READ_MASK),
		    XAE_MDIO_MCR_OFFSET);

	res = eth_xaxidma_phy_wait(dev);
	if (res) {
		return res;
	}
	*val = eth_read32(XAE_MDIO_MRD_OFFSET) & 0x0000FFFF;

	LOG_DBG("MDIO read phy %d reg %d: 0x%x", dev_conf->phy_id, reg, *val);

	return 0;
}

static int eth_xaxidma_phy_write(const struct device *dev, uint32_t reg, uint32_t val)
{
	struct eth_xaxidma_config *dev_conf = DEV_CFG(dev);

	LOG_DBG("MDIO write phy %d reg %d: 0x%x", dev_conf->phy_id, reg, val);

	int res = eth_xaxidma_phy_wait(dev);
	if (res) {
		return res;
	}
	eth_write32(val, XAE_MDIO_MWD_OFFSET);
	eth_write32((((dev_conf->phy_id << XAE_MDIO_MCR_PHYAD_SHIFT) &
		      XAE_MDIO_MCR_PHYAD_MASK) |
		     ((reg << XAE_MDIO_MCR_REGAD_SHIFT) &
		      XAE_MDIO_MCR_REGAD_MASK) |
		     XAE_MDIO_MCR_INITIATE_MASK |
		     XAE_MDIO_MCR_OP_WRITE_MASK),
		    XAE_MDIO_MCR_OFFSET);

	return eth_xaxidma_phy_wait(dev);
}

static int eth_xaxidma_phy_start(const struct device *dev)
{
	struct eth_xaxidma_config *dev_conf = DEV_CFG(dev);

	/* Set MDIO clock divisor based on this formula:
	 *
	 * 			f[HOSTCLK]
	 *	f[MDC] = -----------------------
	 *			(1 + Divisor) * 2
	 *
	 * where f[HOSTCLK] is the bus clock frequency in MHz, and f[MDC] is the
	 * MDIO clock frequency in MHz to the PHY. Typically, f[MDC] should not
	 * exceed 2.5 MHz.
	 *
	 * If we set f[MDC] = 2500000 then Divisor >= (f[HOSTCLK] / 5000000) - 1
	 */
	uint32_t divisor = (dev_conf->clock_frequency / 5000000) - 1;
	if (dev_conf->clock_frequency % 5000000) {
		/* In case there's remainder add one. */
		divisor++;
	}
	eth_write32(divisor | XAE_MDIO_MC_MDIOEN_MASK, XAE_MDIO_MC_OFFSET);

	return eth_xaxidma_phy_wait(dev);
}

static void eth_xaxidma_phy_stop(const struct device *dev)
{
	struct eth_xaxidma_config *dev_conf = DEV_CFG(dev);

	eth_write32(0, XAE_MDIO_MC_OFFSET);
}

static int eth_xaxidma_auto_negotiate(const struct device *dev)
{
	struct eth_xaxidma_runtime *dev_data = DEV_DATA(dev);
	uint32_t val, advertised, received, advertised2, received2;

	LOG_DBG("Starting PHY auto-negotiation");

	/* Read PHY default advertising parameters. */
	int res = eth_xaxidma_phy_read(dev, MII_ANAR, &advertised);
	if (res) {
		LOG_ERR("Failed to read MII_ANAR: %d", res);
		return res;
	}
	res = eth_xaxidma_phy_read(dev, MII_CTRL1000, &advertised2);
	if (res) {
		LOG_ERR("Failed to read MII_CTRL1000: %d", res);
		return res;
	}
	/* Configure and start auto-negotiation process. */
	res = eth_xaxidma_phy_read(dev, MII_BMCR, &val);
	if (res) {
		LOG_ERR("Failed to read MII_BMCR: %d", res);
		return res;
	}
	val |= MII_BMCR_AUTONEG_ENABLE | MII_BMCR_AUTONEG_RESTART;
	val &= ~MII_BMCR_ISOLATE; /* don't isolate the PHY */

	res = eth_xaxidma_phy_write(dev, MII_BMCR, val);
	if (res) {
		LOG_ERR("Failed to write MII_BMCR: %d", res);
		return res;
	}
	/* Wait for the auto-negotiation process to complete. */
	for (int i = 0; i < 37; i++) {
		/* Maximum time to establish a link through auto-negotiation
		 * for 10BASE-T and 100BASE-TX is 3.7s. */
		k_sleep(K_MSEC(100));

		res = eth_xaxidma_phy_read(dev, MII_BMSR, &val);
		if (res) {
			LOG_ERR("Failed to read MII_BMSR: %d", res);
			break;
		}
		if (val & MII_BMSR_AUTONEG_COMPLETE) {
			res = 0;
			break;
		}
		res = -ETIMEDOUT;
	}
	if (res) {
		LOG_ERR("PHY auto-negotiation failed");
		return res;
	}

	/* Read abilities of the remote device. */
	res = eth_xaxidma_phy_read(dev, MII_ANLPAR, &received);
	if (res) {
		LOG_ERR("Failed to read MII_ANLPAR: %d", res);
		return res;
	}
	res = eth_xaxidma_phy_read(dev, MII_STAT1000, &received2);
	if (res) {
		LOG_ERR("Failed to read MII_STAT1000: %d", res);
		return res;
	}
	LOG_DBG("PHY advertised=0x%x 0x%x, received=0x%x 0x%x",
		advertised, advertised2, received, received2);

	/* We only support full duplex. */
	if ((advertised2 & MII_ADVERTISE_1000_FULL) && (received2 & MII_LPA_1000_FULL)) {
		LOG_DBG("Using link speed 1000Mbps");
		dev_data->link_speed = XAE_EMMC_LINKSPD_1000;
	} else if ((advertised & received) & MII_ADVERTISE_100_FULL) {
		LOG_DBG("Using link speed 100Mbps");
		dev_data->link_speed = XAE_EMMC_LINKSPD_100;
	} else if ((advertised & received) & MII_ADVERTISE_10_FULL) {
		LOG_DBG("Using link speed 10Mbps");
		dev_data->link_speed = XAE_EMMC_LINKSPD_10;
	} else {
		LOG_WRN("Cannot detect link speed, using default");
	}

	return 0;
}

static void eth_xaxidma_reset(const struct device *dev)
{
	struct eth_xaxidma_config *dev_conf = DEV_CFG(dev);

	/* Writing to tx channel control resets both channels. */
	dtx_write32(XAXIDMA_CR_RESET_MASK, XAXIDMA_CR_OFFSET);
	while (true) {
		/* However, both channels need to be monitored. */
		uint32_t tx_cr = dtx_read32(XAXIDMA_CR_OFFSET);
		uint32_t rx_cr = drx_read32(XAXIDMA_CR_OFFSET);
		/* Reset is done when the reset bits are zero. */
		if ((tx_cr & XAXIDMA_CR_RESET_MASK) ||
		    (rx_cr & XAXIDMA_CR_RESET_MASK)) {
			k_busy_wait(1);
		} else {
			break;
		}
	}
	/* Reseting AXI DMA reseted AXI Ethernet, too. */
}

static void eth_xaxidma_assign_mac(const struct device *dev)
{
	struct eth_xaxidma_runtime *dev_data = DEV_DATA(dev);
	struct eth_xaxidma_config *dev_conf = DEV_CFG(dev);

	eth_write32((dev_data->mac.addr[0]) |
		    (dev_data->mac.addr[1] << 8) |
		    (dev_data->mac.addr[2] << 16) |
		    (dev_data->mac.addr[3] << 24),
		    XAE_UAW0_OFFSET);
	eth_write32((eth_read32(XAE_UAW1_OFFSET) & ~XAE_UAW1_UNICASTADDR_MASK) |
		    (dev_data->mac.addr[4]) |
		    (dev_data->mac.addr[5] << 8),
		    XAE_UAW1_OFFSET);
}

/* https://en.wikipedia.org/wiki/Ethernet_frame */
#ifdef CONFIG_NET_VLAN
#define ETH_XAXIDMA_MAX_FRAME_SIZE (NET_ETH_MTU + sizeof(struct net_eth_vlan_hdr) + sizeof(uint32_t))
#else
#define ETH_XAXIDMA_MAX_FRAME_SIZE (NET_ETH_MTU + sizeof(struct net_eth_hdr) + sizeof(uint32_t))
#endif

static void eth_xaxidma_queue_init(const struct device *dev)
{
	struct eth_xaxidma_runtime *dev_data = DEV_DATA(dev);
	struct eth_xaxidma_config *dev_conf = DEV_CFG(dev);

	/* Setup TX BDs. */
	uint32_t bd_addr = dev_conf->tx_bd_base;
	struct xaxidma_bd *bd = (struct xaxidma_bd *)bd_addr;
	dev_data->queue.tx_bd_curr = bd_addr;
	dev_data->queue.tx_bd_tail = bd_addr;
	uint32_t buf_addr = dev_conf->tx_buf_base;
	for (int i = 0; i < CONFIG_NET_BUF_TX_COUNT; i++) {
		bd_addr += sizeof(struct xaxidma_bd);
		bd[i].nxtdesc = bd_addr;
		bd[i].buffer_address = buf_addr;
		buf_addr += ROUND_UP(NET_ETH_MAX_FRAME_SIZE, 4);
	}
	bd[CONFIG_NET_BUF_TX_COUNT-1].nxtdesc = dev_conf->tx_bd_base;

	/* Set up the current descriptor pointer. */
	dtx_write32(dev_conf->tx_bd_base, XAXIDMA_CDESC_OFFSET);
	/* Enable channel interrupts and make it ready. */
	uint32_t val = dtx_read32(XAXIDMA_CR_OFFSET);
	val &= ~XAXIDMA_IRQ_ALL_MASK |
		~XAXIDMA_COALESCE_MASK |
		~XAXIDMA_DELAY_MASK;
	val |= XAXIDMA_CR_RUNSTOP_MASK |
#if CONFIG_ETH_XAXIDMA_COALESCE_DELAY > 0
		XAXIDMA_IRQ_DELAY_MASK |
#endif
		XAXIDMA_IRQ_IOC_MASK | XAXIDMA_IRQ_ERROR_MASK |
		(CONFIG_ETH_XAXIDMA_COALESCE_COUNT << XAXIDMA_COALESCE_SHIFT) |
		(CONFIG_ETH_XAXIDMA_COALESCE_DELAY << XAXIDMA_DELAY_SHIFT);
	dtx_write32(val, XAXIDMA_CR_OFFSET);

	/* Setup RX BDs. */
	bd_addr = dev_conf->rx_bd_base;
	bd = (struct xaxidma_bd *)bd_addr;
	dev_data->queue.rx_bd_curr = bd_addr;
	buf_addr = dev_conf->rx_buf_base;
	for (int i = 0; i < CONFIG_NET_BUF_RX_COUNT * 3; i++) {
		bd_addr += sizeof(struct xaxidma_bd);
		bd[i].nxtdesc = bd_addr;
		bd[i].buffer_address = buf_addr;
		buf_addr += ROUND_UP(ETH_XAXIDMA_MAX_FRAME_SIZE, 4);
		bd[i].control = ETH_XAXIDMA_MAX_FRAME_SIZE;
		bd[i].status = 0;
	}
	bd[CONFIG_NET_BUF_RX_COUNT*3-1].nxtdesc = dev_conf->rx_bd_base;

	/* Set up the current and tail descriptor pointers. */
	drx_write32(dev_conf->rx_bd_base, XAXIDMA_CDESC_OFFSET);
	/* Enable channel interrupts and make it ready. */
	val = drx_read32(XAXIDMA_CR_OFFSET);
	val &= ~XAXIDMA_IRQ_ALL_MASK |
		~XAXIDMA_COALESCE_MASK |
		~XAXIDMA_DELAY_MASK;
	val |= XAXIDMA_CR_RUNSTOP_MASK |
#if CONFIG_ETH_XAXIDMA_COALESCE_DELAY > 0
		XAXIDMA_IRQ_DELAY_MASK |
#endif
		XAXIDMA_IRQ_IOC_MASK | XAXIDMA_IRQ_ERROR_MASK |
		(CONFIG_ETH_XAXIDMA_COALESCE_COUNT << XAXIDMA_COALESCE_SHIFT) |
		(CONFIG_ETH_XAXIDMA_COALESCE_DELAY << XAXIDMA_DELAY_SHIFT);
	drx_write32(val, XAXIDMA_CR_OFFSET);
	drx_write32((uint32_t)(bd_addr - sizeof(struct xaxidma_bd)), XAXIDMA_TDESC_OFFSET);
}

static void eth_xaxidma_set_options(const struct device *dev)
{
	struct eth_xaxidma_runtime *dev_data = DEV_DATA(dev);
	struct eth_xaxidma_config *dev_conf = DEV_CFG(dev);

	/* Set operating speed to configured/negotiated. */
	uint32_t val = eth_read32(XAE_EMMC_OFFSET);
	val &= ~XAE_EMMC_LINKSPEED_MASK;
	val |= dev_data->link_speed;
	eth_write32(val, XAE_EMMC_OFFSET);

	/* Enable or disable promiscuous mode. */
	val = eth_read32(XAE_FMI_OFFSET);
	if (dev_data->promisc_mode) {
		val |= XAE_FMI_PM_MASK;
	} else {
		val &= ~XAE_FMI_PM_MASK;
	}
	eth_write32(val, XAE_FMI_OFFSET);

	/* Enable receive error interrupts. */
	eth_write32(XAE_INT_RECV_ERROR_MASK, XAE_IE_OFFSET);

	/* Enable transmitter. */
	val = eth_read32(XAE_TC_OFFSET);
#ifdef CONFIG_NET_VLAN
	/* Enable basic VLAN TX packet support. */
	val |= XAE_TC_VLAN_MASK;
#endif
	val |= XAE_TC_TX_MASK;
	eth_write32(val, XAE_TC_OFFSET);

	/* Enable receiver. */
	val = eth_read32(XAE_RCW1_OFFSET);
#ifdef CONFIG_NET_VLAN
	/* Enable basic VLAN RX packet support. */
	val |= XAE_RCW1_VLAN_MASK;
#endif
	val |= XAE_RCW1_RX_MASK;
	eth_write32(val, XAE_RCW1_OFFSET);
}

static int eth_xaxidma_start(const struct device *dev)
{
	/* Called at startup via net_if_post_init. */
	struct eth_xaxidma_config *dev_conf = DEV_CFG(dev);
	struct eth_xaxidma_runtime *dev_data = DEV_DATA(dev);

	/* Check it's ok to start. */
	if (dev_data->error != -ENOENT) {
		LOG_ERR("Invalid device state %d", dev_data->error);
		return -EIO;
	}
	/* Start the MDIO interface. */
	int res = eth_xaxidma_phy_start(dev);
	if (res) {
		LOG_ERR("Cannot start physical device: %d", res);
		return res;
	}
	/* Reset semaphores. */
	k_sem_reset(&dev_data->rx_sem);

	/* Assign MAC address to Hardware. */
	eth_xaxidma_assign_mac(dev);

	/* Assign link local address. */
	net_if_set_link_addr(dev_data->iface, dev_data->mac.addr, 6, NET_LINK_ETHERNET);

	/* Initialize AXI DMA TX and RX queues. */
	eth_xaxidma_queue_init(dev);

	/* Set to OK status. */
	dev_data->error = 0;

	/* Enable interrupts. */
	dev_conf->enable_func(dev);

	/* Perform auto-negotiation. */
	if (dev_data->auto_negotiation) {
		eth_xaxidma_auto_negotiate(dev);
	}
	/* Set running options for the HW. */
	eth_xaxidma_set_options(dev);

	return 0;
}

static int eth_xaxidma_stop(const struct device *dev)
{
	struct eth_xaxidma_config *dev_conf = DEV_CFG(dev);
	struct eth_xaxidma_runtime *dev_data = DEV_DATA(dev);

	/* Set device to stopped state. */
	dev_data->error = -ENOENT;

	/* Stop TX queue and interrupts. */
	uint32_t val = dtx_read32(XAXIDMA_CR_OFFSET);
	val &= ~(XAXIDMA_CR_RUNSTOP_MASK | XAXIDMA_IRQ_ALL_MASK);
	dtx_write32(val, XAXIDMA_CR_OFFSET);

	/* Stop RX queue and interrupts. */
	val = drx_read32(XAXIDMA_CR_OFFSET);
	val &= ~(XAXIDMA_CR_RUNSTOP_MASK | XAXIDMA_IRQ_ALL_MASK);
	drx_write32(val, XAXIDMA_CR_OFFSET);

	/* Disable core Ethernet interrupts. */
	eth_write32(0, XAE_IE_OFFSET);

	/* Disable transmitter and receiver. */
	val = eth_read32(XAE_TC_OFFSET);
	val &= ~XAE_TC_TX_MASK;
	eth_write32(val, XAE_TC_OFFSET);
	val = eth_read32(XAE_RCW1_OFFSET);
	val &= ~XAE_RCW1_RX_MASK;
	eth_write32(val, XAE_RCW1_OFFSET);

	/* Disable interrupts. */
	dev_conf->disable_func(dev);
	val = eth_read32(XAE_IP_OFFSET);
	if (val & XAE_INT_RXRJECT_MASK) {
		/* Disabling in mid-packet may cause this, clear it. */
		eth_write32(XAE_INT_RXRJECT_MASK, XAE_IS_OFFSET);
	}

	/* Wait TX DMA to halt. */
	for (int i = 0; i < 5; i++) {
		val = dtx_read32(XAXIDMA_SR_OFFSET);
		if (val & XAXIDMA_HALTED_MASK) {
			break;
		}
		k_sleep(K_MSEC(10));
	}
	/* Wait RX DMA to halt. */
	for (int i = 0; i < 5; i++) {
		val = drx_read32(XAXIDMA_SR_OFFSET);
		if (val & XAXIDMA_HALTED_MASK) {
			break;
		}
		k_sleep(K_MSEC(10));
	}
	/* Finally reset to make sure. */
	eth_xaxidma_phy_stop(dev);
	eth_xaxidma_reset(dev);

	return 0;
}

#ifdef CONFIG_ETH_XAXIDMA_DMAC_COPY
static int eth_xaxidma_dmac_copy(uint32_t src, uint32_t dst, size_t len)
{
	if (len < CONFIG_ETH_XAXIDMA_DMAC_THRESHOLD) {
		/* It's less expensive to copy here. Note that memcpy
		 * is a word copy for these aligned addresses. */
		memcpy((void *)dst, (const void *)src, len);
	} else {
		/* Set up DMAC to make the copy. */
		int res = -ENODEV;
		cmrt_dmac_t dmac = cmrt_dmac_open(CMRT_O_SYNC);
		if (cmrt_is_valid(dmac)) {
			res = cmrt_dmac_data(dmac, src, dst, len, 0);
			cmrt_dmac_close(dmac);
		}
		return res;
	}
	return 0;
}
#endif

static int eth_xaxidma_send_pkt(struct net_pkt *pkt, uint32_t data, size_t length)
{
	if (length > ETH_XAXIDMA_MAX_FRAME_SIZE - sizeof(uint32_t)) {
		/* Note: not counting CRC32 to the max size. */
		LOG_ERR("Packet too big %d > %d", length,
			ETH_XAXIDMA_MAX_FRAME_SIZE - sizeof(uint32_t));
		return -EIO;
	}
#ifdef CONFIG_ETH_XAXIDMA_DMAC_COPY
	/* Packet can be in fragments, read it into word aligned buffer. */
	static alignas(4) uint8_t tx_buffer[ROUND_UP(ETH_XAXIDMA_MAX_FRAME_SIZE, 4)];
#else
	/* If we don't use DMAC we don't need to honour word alignment. */
	void *tx_buffer = (void *)data;
#endif
	int res = net_pkt_read(pkt, tx_buffer, length);
	if (res) {
		LOG_ERR("Failed to read the packet %d", res);
		return res;
	}
#ifdef CONFIG_ETH_XAXIDMA_DMAC_COPY
	/* Use DMAC to copy data into DDR for AXI DMA. */
	res = eth_xaxidma_dmac_copy((uint32_t)tx_buffer, data, ROUND_UP(length, 4));
	if (res) {
		LOG_ERR("DMAC error %d in send", res);
		return res;
	}
#endif
	return 0;
}

static inline bool eth_xaxidma_tx_nxtdesc(struct eth_xaxidma_config *dev_conf, uint32_t nxtdesc)
{
	/* Verify next TX descriptor validity. */
	if ((nxtdesc & (XAXIDMA_BD_MINIMUM_ALIGNMENT - 1)) ||
	    (nxtdesc < dev_conf->tx_bd_base) ||
	    (nxtdesc >= dev_conf->rx_bd_base)) {
		/* Not ok, memory corruption? */
		return false;
	}
	return true;
}

static int eth_xaxidma_send(const struct device *dev, struct net_pkt *pkt)
{
	struct eth_xaxidma_runtime *dev_data = DEV_DATA(dev);
	struct eth_xaxidma_config *dev_conf = DEV_CFG(dev);
	size_t length = net_pkt_get_len(pkt);
	int res = 0;

	/* Only one TC thread can enter at a time. */
	k_mutex_lock(&dev_data->tx_mutex, K_FOREVER);

	/* Bail out if device is in error state. */
	if (dev_data->error) {
		goto out;
	}
	struct xaxidma_bd *bd = (struct xaxidma_bd *)dev_data->queue.tx_bd_tail;
	res = eth_xaxidma_send_pkt(pkt, bd->buffer_address, length);
	if (res) {
		goto out;
	}
	/* Setup the descriptor and send it. */
	bd->control = length;
	bd->control |= XAXIDMA_BD_CTRL_ALL_MASK;
	bd->status = 0;
	bd->app0 = 0;
	bd->app1 = 0;
	bd->app2 = 0;
	bd->app3 = 0;
	bd->app4 = 0;
	dtx_write32((uint32_t)bd, XAXIDMA_TDESC_OFFSET);

	/* Verify next descriptor validity. */
	if (eth_xaxidma_tx_nxtdesc(dev_conf, bd->nxtdesc)) {
		/* Ok, set it for the next packet. */
		dev_data->queue.tx_bd_tail = bd->nxtdesc;
	} else {
		LOG_ERR("Invalid TX descriptor memory");
		dev_data->error = -EIO;
	}
 out:
	k_mutex_unlock(&dev_data->tx_mutex);

	/* We consider the packet as sent now and don't wait and check for
	 * complete status in the BD. While this is not perfect since the
	 * same packet can be marked twice in stats, once good here and later
	 * on failed in the interrupt handler, this goes around the problems
	 * we could have dealing with different priority TC threads trying
	 * to match their sent packets. It's also faster not having to
	 * context switch back here only to check for status for statistics.
	 */
	if (dev_data->error) {
		res = dev_data->error;
		LOG_WRN("Device status is %d", dev_data->error);
	} else if (res) {
		LOG_WRN("Failed to send packet %p: %d", pkt, res);
	} else {
		LOG_DBG("Packet %p sent length %d", pkt, length);
	}
	return res;
}

static void eth_xaxidma_tx_isr(const struct device *dev)
{
	struct eth_xaxidma_runtime *dev_data = DEV_DATA(dev);
	struct eth_xaxidma_config *dev_conf = DEV_CFG(dev);

	uint32_t lock = irq_lock();

	/* Read the interrupt status */
	uint32_t status = dtx_read32(XAXIDMA_SR_OFFSET);
	dtx_write32(status & XAXIDMA_IRQ_ALL_MASK, XAXIDMA_SR_OFFSET);
	if ((status & XAXIDMA_IRQ_IOC_MASK) ||
	    (status & XAXIDMA_IRQ_DELAY_MASK)) {
		/* TX completed. */
		int pkts = 0;
		while (dev_data->queue.tx_bd_curr != dtx_read32(XAXIDMA_CDESC_OFFSET)) {
			struct xaxidma_bd *bd = (struct xaxidma_bd *)dev_data->queue.tx_bd_curr;
			/* Only check for errors here. */
			if (bd->status & XAXIDMA_BD_STS_ALL_ERR_MASK) {
				/* BD error. */
#ifdef CONFIG_NET_STATISTICS_ETHERNET
				eth_stats_update_errors_tx(dev_data->iface);
#endif
			}
			/* Verify next descriptor validity. */
			if (!eth_xaxidma_tx_nxtdesc(dev_conf, bd->nxtdesc)) {
				dev_data->error = -EIO;
				break;
			}
			/* And assign it to be checked out next. */
			dev_data->queue.tx_bd_curr = bd->nxtdesc;
			if (++pkts == CONFIG_NET_BUF_TX_COUNT) {
				/* Avoid looping forever in isr. */
				break;
			}
		}
	}
	if (status & XAXIDMA_IRQ_ERROR_MASK) {
		/* DMA error. */
#ifdef CONFIG_NET_STATISTICS_ETHERNET
		eth_stats_update_errors_tx(dev_data->iface);
		dev_data->stats.error_details.tx_dma_failed++;
#endif
		/* Set device to error. */
		dev_data->error = -EIO;
	}

	irq_unlock(lock);
}

static struct net_pkt *eth_xaxidma_recv_pkt(struct net_if *iface, uint32_t data, size_t length)
{
	/* Use the root interface, will be updated in net_recv_data(). */
	struct net_pkt *pkt = net_pkt_rx_alloc_with_buffer(iface, length,
							   AF_UNSPEC, 0, K_NO_WAIT);
	if (!pkt) {
		LOG_ERR("Out of net buffers");
		return NULL;
	}
#ifdef CONFIG_ETH_XAXIDMA_DMAC_COPY
	/* Word aligned receive buffer for DMAC across SAC. */
	static alignas(4) uint8_t rx_buffer[ROUND_UP(ETH_XAXIDMA_MAX_FRAME_SIZE, 4)];
	/* Use DMAC to copy data from DDR for AXI DMA. */
	int res = eth_xaxidma_dmac_copy(data, (uint32_t)rx_buffer, ROUND_UP(length, 4));
	if (res) {
		LOG_ERR("DMAC error %d in recv", res);
		goto error;
	}
#else
	/* If we don't use DMAC we don't need to honour word alignment. */
	void *rx_buffer = (void *)data;
#endif
	if (net_pkt_write(pkt, rx_buffer, length)) {
		LOG_ERR("Out of memory for received frame");
		goto error;
	}
	return pkt;
 error:
	net_pkt_unref(pkt);
	return NULL;
}

static inline bool eth_xaxidma_rx_nxtdesc(struct eth_xaxidma_config *dev_conf, uint32_t nxtdesc)
{
	/* Verify next RX descriptor validity. */
	if ((nxtdesc & (XAXIDMA_BD_MINIMUM_ALIGNMENT - 1)) ||
	    (nxtdesc < dev_conf->rx_bd_base) ||
	    (nxtdesc >= dev_conf->tx_buf_base)) {
		/* Not ok, memory corruption? */
		return false;
	}
	return true;
}

static struct net_pkt *eth_xaxidma_recv(const struct device *dev)
{
	struct eth_xaxidma_runtime *dev_data = DEV_DATA(dev);
	struct eth_xaxidma_config *dev_conf = DEV_CFG(dev);
	struct net_if *iface = dev_data->iface;
	struct net_pkt *pkt = NULL;

	if (dev_data->error) {
		/* Device restart needed. */
		LOG_WRN("Device status is %d", dev_data->error);
		return NULL;
	}
	struct xaxidma_bd *bd = (struct xaxidma_bd *)dev_data->queue.rx_bd_curr;
	if (bd->status & XAXIDMA_BD_STS_ALL_ERR_MASK) {
		/* BD error. Returning NULL will add to the errors. */
	} else if (bd->status & XAXIDMA_BD_STS_COMPLETE_MASK) {
		/* BD completed. */
		size_t length = bd->status & ~XAXIDMA_BD_STS_ALL_MASK;
		if (!length) {
			/* Linux driver and QEMU do this, verify in FPGA! */
			length = bd->app4 & 0x0000FFFF;
		}
		pkt = eth_xaxidma_recv_pkt(iface, bd->buffer_address, length);
		if (pkt) LOG_DBG("Packet %p received length %d", pkt, length);
	}
	if (!eth_xaxidma_rx_nxtdesc(dev_conf, bd->nxtdesc)) {
		/* Descriptor setup is invalid, restart required. */
		LOG_ERR("Invalid RX descriptor memory");
		dev_data->error = -EIO;
	} else {
		/* Ok to reuse this descriptor. */
		bd->status = 0;
		dev_data->queue.rx_bd_curr = bd->nxtdesc;
		drx_write32(dev_data->queue.rx_bd_curr, XAXIDMA_TDESC_OFFSET);
	}
	return pkt;
}

static inline struct net_if *get_iface(struct eth_xaxidma_runtime *dev_data, uint16_t vlan_tag)
{
#ifdef CONFIG_NET_VLAN
	struct net_if *iface = net_eth_get_vlan_iface(dev_data->iface, vlan_tag);
	if (iface) {
		return iface;
	}
#else
	ARG_UNUSED(vlan_tag);
#endif
	return dev_data->iface;
}

#define NET_ETH_VLAN_HDR(pkt) ((struct net_eth_vlan_hdr *)net_pkt_data(pkt))

static void eth_xaxidma_rx_thread(const struct device *dev)
{
	struct eth_xaxidma_runtime *dev_data = DEV_DATA(dev);
	struct eth_xaxidma_config *dev_conf = DEV_CFG(dev);
	struct net_if *iface = dev_data->iface;

	LOG_DBG("Starting RX thread");

	while (true) {
		int pkts = 0;
		k_sem_take(&dev_data->rx_sem, K_FOREVER);
		if (net_if_is_up(iface) && !dev_data->error) {
			while (dev_data->queue.rx_bd_curr != drx_read32(XAXIDMA_CDESC_OFFSET)) {
				uint16_t vlan_tag = NET_VLAN_TAG_UNSPEC;
				struct net_pkt *pkt = eth_xaxidma_recv(dev);
				if (pkt) {
#ifdef CONFIG_NET_VLAN
					struct net_eth_hdr *hdr = NET_ETH_HDR(pkt);
					if (ntohs(hdr->type) == NET_ETH_PTYPE_VLAN) {
						struct net_eth_vlan_hdr *hdr_vlan = NET_ETH_VLAN_HDR(pkt);

						net_pkt_set_vlan_tci(pkt, ntohs(hdr_vlan->vlan.tci));
						vlan_tag = net_pkt_vlan_tag(pkt);
#if CONFIG_NET_TC_RX_COUNT > 1
						enum net_priority prio = net_vlan2priority(net_pkt_vlan_priority(pkt));
						net_pkt_set_priority(pkt, prio);
#endif
					}
#endif
					net_recv_data(get_iface(dev_data, vlan_tag), pkt);
				} else {
#ifdef CONFIG_NET_STATISTICS_ETHERNET
					eth_stats_update_errors_rx(get_iface(dev_data, vlan_tag));
#endif
				}
				if (++pkts == CONFIG_NET_BUF_RX_COUNT) {
					/* Apps need time to process. */
					break;
				}
			}
		}
		k_sleep(K_MSEC(10 * pkts));
	}
}

static void eth_xaxidma_rx_isr(const struct device *dev)
{
	struct eth_xaxidma_runtime *dev_data = DEV_DATA(dev);
	struct eth_xaxidma_config *dev_conf = DEV_CFG(dev);

	uint32_t lock = irq_lock();

	uint32_t status = drx_read32(XAXIDMA_SR_OFFSET);
	drx_write32(status & XAXIDMA_IRQ_ALL_MASK, XAXIDMA_SR_OFFSET);
	if ((status & XAXIDMA_IRQ_IOC_MASK) ||
	    (status & XAXIDMA_IRQ_DELAY_MASK)) {
		/* RX completed, signal the thread. */
		k_sem_give(&dev_data->rx_sem);
	}
	if (status & XAXIDMA_IRQ_ERROR_MASK) {
		/* DMA error. */
#ifdef CONFIG_NET_STATISTICS_ETHERNET
		eth_stats_update_errors_rx(dev_data->iface);
		dev_data->stats.error_details.rx_dma_failed++;
#endif
		/* Set device to error state. */
		dev_data->error = -EIO;
	}

	irq_unlock(lock);
}

static void eth_xaxidma_isr(const struct device *dev)
{
	struct eth_xaxidma_config *dev_conf = DEV_CFG(dev);

	uint32_t lock = irq_lock();

	/* Only add errors to statistics. */
	uint32_t pending = eth_read32(XAE_IP_OFFSET);
#ifdef CONFIG_NET_STATISTICS_ETHERNET
	struct eth_xaxidma_runtime *dev_data = DEV_DATA(dev);
	eth_stats_update_errors_rx(dev_data->iface);
	if (pending & XAE_INT_RXFIFOOVR_MASK)
		dev_data->stats.error_details.rx_missed_errors++;

	if (pending & XAE_INT_RXRJECT_MASK)
		dev_data->stats.error_details.rx_frame_errors++;
#endif
	eth_write32(pending, XAE_IS_OFFSET);

	irq_unlock(lock);
}

static enum ethernet_hw_caps eth_xaxidma_get_capabilities(const struct device *dev)
{
	ARG_UNUSED(dev);

	return (ETHERNET_HW_VLAN |
		ETHERNET_AUTO_NEGOTIATION_SET |
		ETHERNET_LINK_10BASE_T |
		ETHERNET_LINK_100BASE_T |
		ETHERNET_LINK_1000BASE_T |
		ETHERNET_PROMISC_MODE);
}

static int eth_xaxidma_set_config(const struct device *dev,
				  enum ethernet_config_type type,
				  const struct ethernet_config *config)
{
	struct eth_xaxidma_runtime *dev_data = DEV_DATA(dev);

	switch (type) {
	case ETHERNET_CONFIG_TYPE_AUTO_NEG:
		dev_data->auto_negotiation = config->auto_negotiation;
		return 0;
	case ETHERNET_CONFIG_TYPE_LINK:
		if (config->l.link_10bt) {
			dev_data->link_speed = XAE_EMMC_LINKSPD_10;
		}
		if (config->l.link_100bt) {
			dev_data->link_speed = XAE_EMMC_LINKSPD_100;
		}
		if (config->l.link_1000bt) {
			dev_data->link_speed = XAE_EMMC_LINKSPD_1000;
		}
		return 0;
	case ETHERNET_CONFIG_TYPE_MAC_ADDRESS:
		memcpy(&dev_data->mac, &config->mac_address, sizeof(struct net_eth_addr));
		return 0;
#ifdef CONFIG_NET_PROMISCUOUS_MODE
	case ETHERNET_CONFIG_TYPE_PROMISC_MODE:
		dev_data->promisc_mode = config->promisc_mode;
		return 0;
#endif
	default:
		break;
	}

	return -ENOTSUP;
}

static int eth_xaxidma_get_config(const struct device *dev,
				  enum ethernet_config_type type,
				  struct ethernet_config *config)
{
	struct eth_xaxidma_runtime *dev_data = DEV_DATA(dev);

	switch (type) {
	case ETHERNET_CONFIG_TYPE_AUTO_NEG:
		config->auto_negotiation = dev_data->auto_negotiation;
		return 0;
	case ETHERNET_CONFIG_TYPE_LINK:
		switch (dev_data->link_speed) {
		case XAE_EMMC_LINKSPD_10:
			config->l.link_10bt = true;
			break;
		case XAE_EMMC_LINKSPD_100:
			config->l.link_100bt = true;
			break;
		case XAE_EMMC_LINKSPD_1000:
		default:
			config->l.link_1000bt = true;
			break;
		}
		return 0;
	case ETHERNET_CONFIG_TYPE_MAC_ADDRESS:
		memcpy(&config->mac_address, &dev_data->mac, sizeof(struct net_eth_addr));
		return 0;
#ifdef CONFIG_NET_PROMISCUOUS_MODE
	case ETHERNET_CONFIG_TYPE_PROMISC_MODE:
		config->promisc_mode = dev_data->promisc_mode;
		return 0;
#endif
	default:
		break;
	}

	return -ENOTSUP;
}

static void eth_xaxidma_init(struct net_if *iface)
{
	/* Called at startup via net_if_init. */
	const struct device *dev = net_if_get_device(iface);
	struct eth_xaxidma_runtime *dev_data = DEV_DATA(dev);

	if (dev_data->iface == NULL) {
		/* The first one is the root inteface, the rest are VLANs. */
		dev_data->iface = iface;

		/* Set device to stopped state. */
		dev_data->error = -ENOENT;

		/* Initialize mutexes and semaphores. */
		k_mutex_init(&dev_data->tx_mutex);
		k_sem_init(&dev_data->rx_sem, 0, 1);
	}
	/* Initialize upper layer. */
	ethernet_init(iface);
	LOG_DBG("Interface %p initialized", iface);
}

#ifdef CONFIG_NET_STATISTICS_ETHERNET
static struct net_stats_eth *eth_xaxidma_get_stats(const struct device *dev)
{
	return &(DEV_DATA(dev)->stats);
}
#endif

static const struct ethernet_api eth_xaxidma_api = {
	.iface_api.init	= eth_xaxidma_init,
	.get_capabilities = eth_xaxidma_get_capabilities,
	.set_config = eth_xaxidma_set_config,
	.get_config = eth_xaxidma_get_config,
	.send = eth_xaxidma_send,
	.stop = eth_xaxidma_stop,
	.start = eth_xaxidma_start,
#ifdef CONFIG_NET_STATISTICS_ETHERNET
	.get_stats = eth_xaxidma_get_stats,
#endif
};

static int eth_xaxidma_dev_init(const struct device *dev)
{
	/* First reset the HW. */
	eth_xaxidma_phy_stop(dev);
	eth_xaxidma_reset(dev);

	return 0;
}

#define ETH_XAXIDMA_0_TX_BD_BASE DT_INST_PROP_BY_IDX(0, ddr, 0)
#define ETH_XAXIDMA_0_TX_BD_SIZE (CONFIG_NET_BUF_TX_COUNT * sizeof(struct xaxidma_bd))
#define ETH_XAXIDMA_0_RX_BD_BASE (ETH_XAXIDMA_0_TX_BD_BASE + ETH_XAXIDMA_0_TX_BD_SIZE)
#define ETH_XAXIDMA_0_RX_BD_SIZE (CONFIG_NET_BUF_RX_COUNT * 3 * sizeof(struct xaxidma_bd))
#define ETH_XAXIDMA_0_TX_BUF_BASE (ETH_XAXIDMA_0_RX_BD_BASE + ETH_XAXIDMA_0_RX_BD_SIZE)
#define ETH_XAXIDMA_0_TX_BUF_SIZE (CONFIG_NET_BUF_TX_COUNT * ROUND_UP(ETH_XAXIDMA_MAX_FRAME_SIZE, 4))
#define ETH_XAXIDMA_0_RX_BUF_BASE (ETH_XAXIDMA_0_TX_BUF_BASE + ETH_XAXIDMA_0_TX_BUF_SIZE)
#define ETH_XAXIDMA_0_RX_BUF_SIZE (CONFIG_NET_BUF_RX_COUNT * 3 * ROUND_UP(ETH_XAXIDMA_MAX_FRAME_SIZE, 4))

static void eth_xaxidma_0_irq_enable(const struct device *dev);
static void eth_xaxidma_0_irq_disable(const struct device *dev);

struct eth_xaxidma_config eth_cfg_0 = {
	.eth_base = DT_INST_REG_ADDR(0),
	.dma_base = DT_INST_PROP_BY_IDX(0, dma, 0),
	.phy_id = 7,
	.clock_frequency = DT_INST_PROP(0, clock_frequency),
	.enable_func = eth_xaxidma_0_irq_enable,
	.disable_func = eth_xaxidma_0_irq_disable,
	.tx_bd_base = ETH_XAXIDMA_0_TX_BD_BASE,
	.tx_bd_size = ETH_XAXIDMA_0_TX_BD_SIZE,
	.rx_bd_base = ETH_XAXIDMA_0_RX_BD_BASE,
	.rx_bd_size = ETH_XAXIDMA_0_RX_BD_SIZE,
	.tx_buf_base = ETH_XAXIDMA_0_TX_BUF_BASE,
	.tx_buf_size = ETH_XAXIDMA_0_TX_BUF_SIZE,
	.rx_buf_base = ETH_XAXIDMA_0_RX_BUF_BASE,
	.rx_buf_size = ETH_XAXIDMA_0_RX_BUF_SIZE,
};

/* Buffer space depends on Zephyr configuration. Make sure not to overflow. */
static_assert(DT_INST_PROP_BY_IDX(0, ddr, 0) + DT_INST_PROP_BY_IDX(0, ddr, 1) >=
	      ETH_XAXIDMA_0_RX_BUF_BASE + ETH_XAXIDMA_0_RX_BUF_SIZE,
	      "ETH_XAXIDMA_0 buffer space overflow, change configuration! "
	      "Allocated buffer space depends on CONFIG_NET_BUF_TX/RX_COUNT. ");

struct eth_xaxidma_runtime eth_data_0 = {
	.auto_negotiation = true,
	.link_speed = XAE_EMMC_LINKSPD_1000,
	.mac.addr = DT_INST_PROP(0, local_mac_address),
	.promisc_mode = false,
};

ETH_NET_DEVICE_DT_INST_DEFINE(0, eth_xaxidma_dev_init, NULL,
			      &eth_data_0, &eth_cfg_0, CONFIG_ETH_INIT_PRIORITY,
			      &eth_xaxidma_api, NET_ETH_MTU);

K_KERNEL_STACK_DEFINE(eth_xaxidma_0_rx_stack, CONFIG_ISR_STACK_SIZE);

static void eth_xaxidma_0_irq_enable(const struct device *dev)
{
	struct eth_xaxidma_runtime *dev_data = DEV_DATA(dev);

	/* Enable Error Interrupt. */
	IRQ_CONNECT(DT_INST_IRQ_BY_IDX(0, 1, irq), 0,
		    eth_xaxidma_isr, DEVICE_DT_INST_GET(0), 0);
	irq_enable(DT_INST_IRQ_BY_IDX(0, 1, irq));

	/* Enable TX interrupt. */
	IRQ_CONNECT(DT_INST_IRQ_BY_IDX(0, 2, irq), 0,
		    eth_xaxidma_tx_isr, DEVICE_DT_INST_GET(0), 0);
	irq_enable(DT_INST_IRQ_BY_IDX(0, 2, irq));

	/* Enable RX interrupt. */
	IRQ_CONNECT(DT_INST_IRQ_BY_IDX(0, 0, irq), 0,
		    eth_xaxidma_rx_isr, DEVICE_DT_INST_GET(0), 0);
	irq_enable(DT_INST_IRQ_BY_IDX(0, 0, irq));

	/* Create RX thread. */
	k_thread_create(&dev_data->rx_thread, eth_xaxidma_0_rx_stack,
			K_THREAD_STACK_SIZEOF(eth_xaxidma_0_rx_stack),
			(k_thread_entry_t)eth_xaxidma_rx_thread,
			(void *)dev, NULL, NULL, K_PRIO_COOP(14), 0, K_NO_WAIT);
}

static void eth_xaxidma_0_irq_disable(const struct device *dev)
{
	struct eth_xaxidma_runtime *dev_data = DEV_DATA(dev);

	/* Disable Error Interrupt. */
	irq_disable(DT_INST_IRQ_BY_IDX(0, 1, irq));

	/* Disable TX interrupt. */
	irq_disable(DT_INST_IRQ_BY_IDX(0, 2, irq));

	/* Disable RX interrupt. */
	irq_disable(DT_INST_IRQ_BY_IDX(0, 0, irq));

	/* Abort RX thread. */
	k_thread_abort(&dev_data->rx_thread);
}
