add_library(test_rbdma
	OBJECT
	rbdma_tsync_test.c
	test_main_rbdma.c
	cache.S
)

target_link_libraries(test_rbdma
	PUBLIC
	cli_service
)

target_include_directories(test_rbdma
	PUBLIC
	${TEST_COMMON_INCLUDES}
)

target_include_directories(test_rbdma
	PRIVATE
	${CMAKE_CURRENT_LIST_DIR}/../../bootloader/cp/tf-a/include
	${CMAKE_CURRENT_LIST_DIR}/../../bootloader/cp/tf-a/include/arch/aarch64
)
