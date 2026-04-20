add_library(hbm3_test
	OBJECT
	memtest.c
	hbm3_irq_test.c
)

target_link_libraries(hbm3_test
	PUBLIC cli_service
	PUBLIC uart
)

target_include_directories(hbm3_test
	PUBLIC
	${TEST_COMMON_INCLUDES}
	${CMAKE_CURRENT_LIST_DIR}/../../drivers/hbm3
	${CMAKE_CURRENT_LIST_DIR}/../../bootloader/cp/tf-a/include
	${CMAKE_CURRENT_LIST_DIR}/../../bootloader/cp/tf-a/include/drivers
	${CMAKE_CURRENT_LIST_DIR}/../../bootloader/cp/tf-a/include/drivers/hbm3
)
