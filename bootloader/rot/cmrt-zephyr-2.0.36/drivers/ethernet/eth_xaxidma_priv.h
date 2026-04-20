/*
 * Copyright (c) 2020-2023 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

#ifndef ETH_XAXIDMA_PRIV_H_
#define ETH_XAXIDMA_PRIV_H_

#include <kernel.h>
#include <net/net_stats.h>

#include "xaxidma_hw.h"
#include "xaxiethernet_hw.h"

/* LogiCORE IP AXI DMA v7.1 PG021 Scatter Gather Descriptor */
struct xaxidma_bd {
	uint32_t nxtdesc;            /* Next Descriptor Pointer */
	uint32_t nxtdesc_msb;        /* Upper 32 bits of nxtdesc N/A */
	uint32_t buffer_address;     /* Buffer address */
	uint32_t buffer_address_msb; /* Upper 32 bits of buffer_address N/A */
	uint32_t reserved0;          /* N/A */
	uint32_t reserved1;          /* N/A */
	uint32_t control;            /* XAXIDMA_BD_CTRL_... in xaxidma_hw.h */
	uint32_t status;             /* XAXIDMA_BD_STS_... in xaxidma_hw.h */
	uint32_t app0;               /* N/A */
	uint32_t app1;               /* N/A */
	uint32_t app2;               /* N/A */
	uint32_t app3;               /* N/A */
	uint32_t app4;               /* N/A */
} __aligned(XAXIDMA_BD_MINIMUM_ALIGNMENT);

/* We have one TX and one RX queue both having multiple descriptors */
struct xaxidma_queue {
	struct xaxidma_bd *tx_bd; /* transmit buffer descriptors */
	struct xaxidma_bd *rx_bd; /* receive buffer descriptors */

	uint32_t tx_bd_curr; /* check transmitted packet status here */
	uint32_t tx_bd_tail; /* write next transmit packet here */
	uint32_t rx_bd_curr; /* read receive packet here */
};

#define DEV_DATA(dev)					\
	((struct eth_xaxidma_runtime *)(dev)->data)
#define DEV_CFG(dev) \
	((struct eth_xaxidma_config *const)(dev)->config)

struct eth_xaxidma_runtime {
	struct net_if *iface;
	bool auto_negotiation;
	uint32_t link_speed;
	struct net_eth_addr mac;
	bool promisc_mode;
	struct k_mutex tx_mutex;
	struct k_sem rx_sem;
	volatile int error;
	struct xaxidma_queue queue;
	struct k_thread rx_thread;
#ifdef CONFIG_NET_STATISTICS_ETHERNET
	struct net_stats_eth stats;
#endif
};

typedef void (*eth_xaxidma_config_irq_t)(const struct device *dev);

struct eth_xaxidma_config {
	uint32_t eth_base;
	uint32_t dma_base;
	uint32_t phy_id;
	uint32_t clock_frequency;
	eth_xaxidma_config_irq_t enable_func;
	eth_xaxidma_config_irq_t disable_func;
	uint32_t tx_bd_base;
	uint32_t tx_bd_size;
	uint32_t rx_bd_base;
	uint32_t rx_bd_size;
	uint32_t tx_buf_base;
	uint32_t tx_buf_size;
	uint32_t rx_buf_base;
	uint32_t rx_buf_size;
};

#endif /* ETH_XAXIDMA_PRIV_H_ */
