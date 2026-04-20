#include <unity_fixture.h>
#include "aw_ucie.h"
#include <system_api.h>
#include <rebel_h_platform.h>
#ifndef USE_DILIGENT_PTR
#include "test_common.h"
#endif
#include "rbc_cmd.h"

static const char help_rbc[] = "Not implemented yet.\r\n";

static void run_ucie_all_tests_except_only_for_mock(void)
{
	RUN_TEST_GROUP(ucie_init_except_only_for_mock);
	/**
	 * AW UCIe not support D2D Comp Test.
	 * RUN_TEST_GROUP(ucie_d2d_comp_except_only_for_mock);
	 */
	RUN_TEST_GROUP(ucie_d2d_err_and_link_except_only_for_mock);
	RUN_TEST_GROUP(ucie_retraining_except_only_for_mock);
	RUN_TEST_GROUP(ucie_sideband_except_only_for_mock);
	RUN_TEST_GROUP(ucie_training_except_only_for_mock);
	RUN_TEST_GROUP(ucie_runtime_link_test_except_only_for_mock);
	RUN_TEST_GROUP(ucie_exception_except_only_for_mock);
	RUN_TEST_GROUP(ucie_phy_compliance_test_except_only_for_mock);
	RUN_TEST_GROUP(ucie_eye_of_margin_except_only_for_mock);
	RUN_TEST_GROUP(rbc_driver_except_only_for_mock);
}

#ifdef USE_DILIGENT_PTR
static void run_ucie_all_tests_only_for_mock(void)
{
	RUN_TEST_GROUP(ucie_init_only_for_mock);
	RUN_TEST_GROUP(ucie_d2d_comp_only_for_mock);
	RUN_TEST_GROUP(ucie_d2d_err_and_link_only_for_mock);
	RUN_TEST_GROUP(ucie_retraining_only_for_mock);
	RUN_TEST_GROUP(ucie_sideband_only_for_mock);
	RUN_TEST_GROUP(ucie_training_only_for_mock);
	RUN_TEST_GROUP(ucie_runtime_link_test_only_for_mock);
	RUN_TEST_GROUP(ucie_exception_only_for_mock);
	RUN_TEST_GROUP(ucie_phy_compliance_test_only_for_mock);
	RUN_TEST_GROUP(ucie_eye_of_margin_only_for_mock);
	RUN_TEST_GROUP(rbc_driver_only_for_mock);

}

static void run_fake_timer_test(void)
{
	RUN_TEST_CASE(fake_timer, set_fake_tick);
	RUN_TEST_CASE(fake_timer, set_fake_tick_increment);
}

static void run_fake_gic_test(void)
{
	RUN_TEST_CASE(fake_gic, call_isr);
}
#endif /* USE_DILIGENT_PTR */

static void run_ucie_all_tests(void)
{
	run_ucie_all_tests_except_only_for_mock();
#ifdef USE_DILIGENT_PTR
	run_ucie_all_tests_only_for_mock();
	run_fake_timer_test();
	run_fake_gic_test();
#endif /* USE_DILIGENT_PTR */
}

#ifndef USE_DILIGENT_PTR
static void run_init_test(void)
{
	RUN_TEST_GROUP(ucie_init_except_only_for_mock);
}

static void run_sideband_test(void)
{
	RUN_TEST_GROUP(ucie_sideband_except_only_for_mock);
}

static void run_phy_comp_test(void)
{
	RUN_TEST_GROUP(ucie_phy_compliance_test_except_only_for_mock);
}

static void run_err_and_link_test(void)
{
	RUN_TEST_GROUP(ucie_d2d_err_and_link_except_only_for_mock);
}

static void run_training_test(void)
{
	RUN_TEST_GROUP(ucie_training_except_only_for_mock);
}

static void run_retraining_test(void)
{
	RUN_TEST_GROUP(ucie_retraining_except_only_for_mock);
}

static void run_runtime_link_test(void)
{
	RUN_TEST_GROUP(ucie_runtime_link_test_except_only_for_mock);
}

static void run_exception_test(void)
{
	RUN_TEST_GROUP(ucie_exception_except_only_for_mock);
}

static void run_eye_of_margin_test(void)
{
	RUN_TEST_GROUP(ucie_eye_of_margin_except_only_for_mock);
}

static void run_rbc_test(void)
{
	RUN_TEST_GROUP(rbc_driver_except_only_for_mock);
}
#endif /*USE_DILIGENT_PTR*/

#ifdef USE_DILIGENT_PTR
int main(int argc, const char **argv)
{
	return UnityMain(argc, (const char **)argv, run_ucie_all_tests);
}
#else /* USE_DILIGENT_PTR */
static uint8_t test_main_rbc(int argc, char **argv)
{
	if (argc == 0 || argv[0][0] == '-')
		UnityMain(argc, (const char **)argv, run_ucie_all_tests);

	if (strcmp(argv[0], "init") == 0) {
		UnityMain(argc, (const char **)argv, run_init_test);
	} else if (strcmp(argv[0], "training") == 0) {
		UnityMain(argc, (const char **)argv, run_training_test);
	} else if (strcmp(argv[0], "retraining") == 0) {
		UnityMain(argc, (const char **)argv, run_retraining_test);
	} else if (strcmp(argv[0], "sideband") == 0) {
		UnityMain(argc, (const char **)argv, run_sideband_test);
	} else if (strcmp(argv[0], "err_and_link_test") == 0) {
		UnityMain(argc, (const char **)argv, run_err_and_link_test);
	} else if (strcmp(argv[0], "runtime_link_test") == 0) {
		UnityMain(argc, (const char **)argv, run_runtime_link_test);
	} else if (strcmp(argv[0], "exception") == 0) {
		UnityMain(argc, (const char **)argv, run_exception_test);
	} else if (strcmp(argv[0], "phy_comp_test") == 0) {
		UnityMain(argc, (const char **)argv, run_phy_comp_test);
	} else if (strcmp(argv[0], "eye_of_margin_test") == 0) {
		UnityMain(argc, (const char **)argv, run_eye_of_margin_test);
	} else if (strcmp(argv[0], "rbc") == 0) {
		UnityMain(argc, (const char **)argv, run_rbc_test);
	} else if (strcmp(argv[0], "intr_log") == 0) {
		char log_arr[UCIE_INTR_LOG_SIZE][UCIE_INTR_LOG_LEN] = {};

		aw_ucie_get_intr_log_arr(log_arr, UCIE_INTR_LOG_SIZE);
		for (int i = 0; i < UCIE_INTR_LOG_SIZE; i++) {
			printf("[%d] %s\n", i, log_arr[i]);
		}
		aw_ucie_show_intr_counter();
	} else if (strcmp(argv[0], "show_crc") == 0) {
		show_crc_err_count();
	} else if (strcmp(argv[0], "sorting") == 0) {
		if (argc != 2) {
			printf("ex) rbc sorting \"delay time(sec)\"");
			return 1;
		}

		uint32_t delay_time = atoi(argv[1]);
		uint64_t crc_err_cnt_before[4][4] = {};
		uint64_t crc_err_cnt_after[4][4] = {};
		uint32_t test_result = 0;

		printf("delay %d sec\n", delay_time);

		get_crc_err_cnt(crc_err_cnt_before);

		delay(delay_time);

		get_crc_err_cnt(crc_err_cnt_after);

		for (uint32_t chiplet_id = 0; chiplet_id < NUM_OF_CHIPS; chiplet_id++) {
			for (uint32_t rbc_idx = 0; rbc_idx < NUM_OF_ACTIVE_RBC; rbc_idx++) {
				uint32_t before = crc_err_cnt_before[chiplet_id][rbc_idx];
				uint32_t after = crc_err_cnt_after[chiplet_id][rbc_idx];
				uint32_t count = after - before;

				if (count) {
					uint64_t base = crc_err_count_base[chiplet_id][rbc_idx];

					printf("ch%d(0x%llx) - crc err count %d during %d sec\n", chiplet_id, base, count, delay_time);
					printf("before %d -> after %d\n", before, after);
					test_result = 1;
				}
			}
		}
		if (test_result)
			printf("FAIL\n");
		else
			printf("PASS\n");
	}

	return 1;
}
#endif /* not USE_DILIGENT_PTR */

#ifndef USE_DILIGENT_PTR
CLI_REGISTER(rbc, NULL, test_main_rbc, help_rbc);
#endif /* not USE_DILIGENT_PTR */
