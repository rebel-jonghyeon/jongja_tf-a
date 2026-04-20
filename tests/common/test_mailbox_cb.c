#include "test_common.h"
#include "../../drivers/mailbox/mailbox.h"
#if defined(__TARGET_CP)
#include "../../drivers/rbc/rbc_driver.h"
#include "../../drivers/rbc/aw_ucie.h"
#include "../../drivers/pmu/pmu.h"
#include "../../common/rebel_h_platform.h"
#endif

void test_cb(int inst, int chan)
{
	uint32_t cmd = 0;

	printf("%s called inst: %d, chan: %d\n", __func__, inst, chan);

	ipm_samsung_receive(inst, &cmd, TEST_CMD_SIZE, TEST_BUF);
	switch (cmd) {
	case INTEGRATED_TEST:
		printf("========integrated test start=========\n");

#if defined(__TARGET_PCIE)
#if defined(USE_PCIE)
		/* Need to add test cases for cm7 below*/
		test_pcie_main(1, (char **)cm7_test_params);
#endif /* USE_PCIE */
#else
		/* TODO: Need to add test cases for sacondary chiplet ca73 below*/
#endif /* __TARGET_PCIE */

		printf("========integrated test done=========\n");
		printf("integrated test list:\n");
		printf("\t test_pcie iatu\n");
		break;
#if defined(__TARGET_CP)
	case RBC_V00_INIT_TEST:
		rbc_driver_init(BLK_RBC_V00_ID,
						(void *)CMU_RBC_V00_PRIVATE, (void *)SYSREG_RBC_V00_PRIVATE, (void *)UCIE_SS0_V0_PRIVATE);
		rbc_set_target_blk_id(BLK_RBC_V00_ID);
		break;
	case RBC_LPI_ENTRY_TEST:
		pmu_rbc_lpi_entry(rbc_get_target_blk_id());
		rbc_pch_mux_on();
		break;
	case RBC_SET_LP_MODE_L1_TEST:
		rbc_set_lp_mode(1);
		break;
	case RBC_SET_LP_MODE_L2_TEST:
		rbc_set_lp_mode(2);
		break;
	case RBC_LP_ENTRY_TEST:
		rbc_lp_entry();
		break;
	case RBC_LP_EXIT_TEST:
		rbc_lp_exit();
		break;
	case RBC_LPI_EXIT_TEST:
		rbc_pch_mux_off();
		pmu_rbc_lpi_exit(rbc_get_target_blk_id());
		break;
#endif
	default:
	}
}
