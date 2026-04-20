/*
 * Copyright 2025 Samsung Electronics Co, Ltd. All Rights Reserved.
 *
 * PROPRIETARY/CONFIDENTIAL
 *
 * This software is the confidential and proprietary information of
 * Samsung Electronics Co., Ltd. ("Confidential Information").
 * You shall not disclose such Confidential Information and shall use it only
 * in accordance with the terms of the license agreement you entered into with
 * Samsung Electronics Co., Ltd. ("SAMSUNG").
 *
 * SAMSUNG MAKES NO REPRESENTATIONS OR WARRANTIES ABOUT THE SUITABILITY OF
 * THE SOFTWARE, EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, OR
 * NON-INFRINGEMENT. SAMSUNG SHALL NOT BE LIABLE FOR ANY DAMAGES SUFFERED BY
 * LICENSEE AS A RESULT OF USING, MODIFYING OR DISTRIBUTING THIS SOFTWARE OR
 * ITS DERIVATIVES.
 *
 */
#include <rebel_h_platform.h>
#include <driver.h>
#include "pmu.h"

uint32_t pmu_get_bootmode(void)
{
	volatile struct pmu *pmu = (struct pmu *)CPMU_PRIVATE;

	return pmu->om_stat.om;
}

void pmu_sw_reset(void)
{
	volatile struct pmu *pmu = (struct pmu *)CPMU_PRIVATE;

	pmu->swreset.system = 1;
}

void pmu_rbc_lpi_entry(uint32_t blk_rbc_id)
{
	if (blk_rbc_id > 5)
		return;

	volatile struct pmu *pmu = (struct pmu *)CPMU_PRIVATE;
	const uint32_t REG_INTERVAL = 8;

	/* For convenience, the h00 register is used for common use. */
	volatile union pmu_lpi_busmaster_cmu_rbch00_configuration *lpi_busmaster_cmu_rbc_configuration = NULL;
	volatile union pmu_lpi_busmaster_cmu_rbch00_status *lpi_busmaster_cmu_rbc_status = NULL;

	lpi_busmaster_cmu_rbc_configuration = &pmu->lpi_busmaster_cmu_rbch00_configuration + (REG_INTERVAL * blk_rbc_id);
	lpi_busmaster_cmu_rbc_status = &pmu->lpi_busmaster_cmu_rbch00_status + (REG_INTERVAL * blk_rbc_id);

	lpi_busmaster_cmu_rbc_configuration->local_pwr_cfg = 0;
	while (lpi_busmaster_cmu_rbc_status->status) {
	}

	volatile union pmu_lpi_bus_cmu_rbch00_configuration *lpi_bus_cmu_rbc_configuration = NULL;
	volatile union pmu_lpi_bus_cmu_rbch00_status *lpi_bus_cmu_rbc_status = NULL;

	lpi_bus_cmu_rbc_configuration = &pmu->lpi_bus_cmu_rbch00_configuration + (REG_INTERVAL * blk_rbc_id);
	lpi_bus_cmu_rbc_status = &pmu->lpi_bus_cmu_rbch00_status + (REG_INTERVAL * blk_rbc_id);

	lpi_bus_cmu_rbc_configuration->local_pwr_cfg = 0;
	while (lpi_bus_cmu_rbc_status->status) {
	}

	volatile union pmu_lpi_residual_cmu_rbch00_configuration *lpi_residual_cmu_rbc_configuration = NULL;
	volatile union pmu_lpi_residual_cmu_rbch00_status *lpi_residual_cmu_rbc_status = NULL;

	lpi_residual_cmu_rbc_configuration = &pmu->lpi_residual_cmu_rbch00_configuration + (REG_INTERVAL * blk_rbc_id);
	lpi_residual_cmu_rbc_status = &pmu->lpi_residual_cmu_rbch00_status + (REG_INTERVAL * blk_rbc_id);

	lpi_residual_cmu_rbc_configuration->local_pwr_cfg = 0;
	while (lpi_residual_cmu_rbc_status->status) {
	}
}

void pmu_rbc_lpi_exit(uint32_t blk_rbc_id)
{
	if (blk_rbc_id > 5)
		return;

	volatile struct pmu *pmu = (struct pmu *)CPMU_PRIVATE;
	const uint32_t REG_INTERVAL = 8;

	/* For convenience, the h00 register is used for common use. */
	volatile union pmu_lpi_busmaster_cmu_rbch00_configuration *lpi_busmaster_cmu_rbc_configuration = NULL;
	volatile union pmu_lpi_busmaster_cmu_rbch00_status *lpi_busmaster_cmu_rbc_status = NULL;

	lpi_busmaster_cmu_rbc_configuration = &pmu->lpi_busmaster_cmu_rbch00_configuration + (REG_INTERVAL * blk_rbc_id);
	lpi_busmaster_cmu_rbc_status = &pmu->lpi_busmaster_cmu_rbch00_status + (REG_INTERVAL * blk_rbc_id);

	lpi_busmaster_cmu_rbc_configuration->local_pwr_cfg = 1;
	while (!lpi_busmaster_cmu_rbc_status->status) {
	}

	volatile union pmu_lpi_bus_cmu_rbch00_configuration *lpi_bus_cmu_rbc_configuration = NULL;
	volatile union pmu_lpi_bus_cmu_rbch00_status *lpi_bus_cmu_rbc_status = NULL;

	lpi_bus_cmu_rbc_configuration = &pmu->lpi_bus_cmu_rbch00_configuration + (REG_INTERVAL * blk_rbc_id);
	lpi_bus_cmu_rbc_status = &pmu->lpi_bus_cmu_rbch00_status + (REG_INTERVAL * blk_rbc_id);

	lpi_bus_cmu_rbc_configuration->local_pwr_cfg = 1;
	while (!lpi_bus_cmu_rbc_status->status) {
	}

	volatile union pmu_lpi_residual_cmu_rbch00_configuration *lpi_residual_cmu_rbc_configuration = NULL;
	volatile union pmu_lpi_residual_cmu_rbch00_status *lpi_residual_cmu_rbc_status = NULL;

	lpi_residual_cmu_rbc_configuration = &pmu->lpi_residual_cmu_rbch00_configuration + (REG_INTERVAL * blk_rbc_id);
	lpi_residual_cmu_rbc_status = &pmu->lpi_residual_cmu_rbch00_status + (REG_INTERVAL * blk_rbc_id);

	lpi_residual_cmu_rbc_configuration->local_pwr_cfg = 1;
	while (!lpi_residual_cmu_rbc_status->status) {
	}
}

uint32_t pmu_get_num_of_secondary_chiplet(void)
{
	volatile struct pmu *pmu = (struct pmu *)CPMU_PRIVATE;

	return pmu->inform4.inform;
}
