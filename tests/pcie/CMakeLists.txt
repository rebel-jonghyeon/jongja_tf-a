add_library(pcie_test
	OBJECT
	test_pcie_main.c
	test_pcie_msix.c
	test_pcie_hdma.c
	test_pcie_capability.c
	test_pcie_mode.c
	test_pcie_iatu.c
	test_pcie_history_store.c
	test_pcie_doe.c
	test_pcie_ide.c
	test_pcie_ide_scenario.c
	test_pcie_rasdp.c
	test_pcie_rasdes.c
	test_pcie_epf.c
)

target_compile_definitions(pcie_test
	PRIVATE
	UNITY_FIXTURE_NO_EXTRAS
)

target_link_libraries(pcie_test
	PUBLIC
	cli_service
	pcie
	unity
	mailbox
	bat
)

target_include_directories(pcie_test
	PUBLIC
	${TEST_COMMON_INCLUDES}
)
