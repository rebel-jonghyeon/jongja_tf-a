add_library(test_dma
	OBJECT
	test_dma_main.c
)

target_link_libraries(test_dma
	PRIVATE	cli_service
	PUBLIC	dma
)

target_include_directories(test_dma
	PUBLIC
	${TEST_COMMON_INCLUDES}
)
