add_library(test_rbc
	OBJECT
	test/all_test.c
	test/test_aw_ucie_init.c
	test/test_aw_ucie_d2d_comp.c
	test/test_aw_ucie_d2d_err_and_link.c
	test/test_aw_ucie_retraining.c
	test/test_aw_ucie_sideband.c
	test/test_aw_ucie_training.c
	test/test_aw_ucie_runtime_link_test.c
	test/test_aw_ucie_phy_compliance_test.c
	test/test_aw_ucie_exception.c
	test/test_aw_ucie_eye_of_margin.c
	test/test_aw_ucie_util.c
	test/test_fake_timer.c
	test/test_rbc_driver.c
	mocks/fake_timer.c
	mocks/fake_gic.c
)

#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DUNIT_TEST -DUNITY_FIXTURE_NO_EXTRAS")
target_compile_definitions(test_rbc
	PRIVATE
	UNIT_TEST
	UNITY_FIXTURE_NO_EXTRAS
)

target_link_libraries(test_rbc
	PUBLIC
	cli_service
	rbc
	unity
	PRIVATE
	mailbox
	pmu
)

target_include_directories(test_rbc
	PUBLIC
	${CMAKE_CURRENT_LIST_DIR}/test
	${CMAKE_CURRENT_LIST_DIR}/mocks
	${TEST_COMMON_INCLUDES}
	${CMAKE_CURRENT_LIST_DIR}/../../drivers/rbc/registers
	${CMAKE_CURRENT_LIST_DIR}/../../lib/unity
)
