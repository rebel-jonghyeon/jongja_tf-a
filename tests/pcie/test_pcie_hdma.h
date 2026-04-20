/*
 * Copyright 2024 Samsung Electronics Co., Ltd. All Rights Reserved.
 *
 * PROPRIETARY/CONFIDENTIAL
 *
 * This software is the confidential and proprietary information of Samsung
 * Electronics Co., Ltd. ("Confidential Information"). You shall not disclose such
 * Confidential Information and shall use it only in accordance with the terms of
 * the license agreement you entered into with Samsung Electronics Co., Ltd. (“SAMSUNG”).
 *
 * SAMSUNG MAKES NO REPRESENTATIONS OR WARRANTIES ABOUT THE SUITABILITY OF THE SOFTWARE,
 * EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, OR NON-INFRINGEMENT.
 *
 * SAMSUNG SHALL NOT BE LIABLE FOR ANY DAMAGES SUFFERED BY LICENSEE AS A RESULT OF USING,
 * MODIFYING OR DISTRIBUTING THIS SOFTWARE OR ITS DERIVATIVES.
 */

/* Test apis */
void test_non_linked_list_read(struct pcie_ep_hdma_controller *hdmac, uint64_t sar,
							   uint64_t dar, uint32_t size);
void test_non_linked_list_write(struct pcie_ep_hdma_controller *hdmac, uint64_t sar,
								uint64_t dar, uint32_t size);
void epf_test_start_hdma_linked_list(struct pcie_ep_hdma_controller *hdmac, uint32_t ch, int32_t num,
									 uint64_t *src_addr, uint64_t *dst_addr, uint32_t *size);
