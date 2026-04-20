add_library(system_test
	OBJECT
	test_system.c
	dma_transaction.c
	test_dma_transaction.c
	data_process.c
	test_data_process.c
)

target_compile_definitions(system_test
	PRIVATE
	UNITY_FIXTURE_NO_EXTRAS
)

target_link_libraries(system_test
	PUBLIC
	cli_service
	PRIVATE
	dma
	unity
	mailbox
)

target_include_directories(system_test
	PUBLIC
	${TEST_COMMON_INCLUDES}
)
