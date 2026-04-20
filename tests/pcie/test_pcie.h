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

/* commands - pcie */
int32_t test_pcie_request_msix(int argc, char *argv[]);
void test_pcie_set_hdma_lut(int argc, char *argv[]);
void test_pcie_invalidate_hdma_lut(int argc, char *argv[]);
void test_pcie_prepare_data(int argc, char *argv[]);
int32_t test_pcie_hdma_ll_mode(int argc, char *argv[]);
int32_t test_pcie_hdma_non_ll_mode(int argc, char *argv[]);
int32_t test_pcie_select_function(int argc, char *argv[]);
int32_t test_pcie_find_capability(int argc, char *argv[]);
int32_t test_pcie_find_ext_capability(int argc, char *argv[]);
int32_t test_pcie_disable_capability(int argc, char *argv[]);
int32_t test_pcie_disable_ext_capability(int argc, char *argv[]);
int32_t test_pcie_set_speed(int argc, char *argv[]);
int32_t test_pcie_set_width(int argc, char *argv[]);
int32_t test_pcie_get_speed(void);
int32_t test_pcie_get_width(void);
uint8_t test_pcie_iatu_inbound(int argc, char *argv[]);
uint8_t test_pcie_iatu_outbound(int argc, char *argv[]);
int32_t test_pcie_iatu_disable_region(int argc, char *argv[]);
int32_t test_pcie_outbound_write(int argc, char *argv[]);
int32_t test_pcie_outbound_read(int argc, char *argv[]);
void test_pcie_iatu_disable_inbound_region_all(void);
int32_t test_pcie_history_store(int argc, char *argv[]);
void test_pcie_show_history(int argc, char *argv[]);
void test_pcie_clear_buffer(int argc, char *argv[]);
int32_t test_pcie_write_to_rmb(int argc, char *argv[]);
int32_t test_pcie_doe_print_wmb_data(int argc, char *argv[]);
int32_t test_pcie_doe_setup_addr(int argc, char *argv[]);
int32_t test_pcie_show_iatu_table(void);
int32_t test_pcie_ide(void);
int32_t test_pcie_ide_key_swap(int argc, char *argv[]);
bool test_pcie_rasdp(int argc, char *argv[]);
bool test_pcie_rasdes_tba(int argc, char *argv[]);
bool test_pcie_rasdes_ecnt(int argc, char *argv[]);
bool test_pcie_rasdes_sd(int argc, char *argv[]);
bool test_pcie_rasdes_sd_eq(int argc, char *argv[]);

/* command - test_pcie */
int32_t test_pcie_iatu(int argc, char *argv[]);
int32_t test_pcie_mode(int argc, char *argv[]);
int32_t test_pcie_doe(int argc, char *argv[]);
int32_t test_pcie_msix(int argc, char *argv[]);
uint8_t test_pcie_main(int argc, char *argv[]);
