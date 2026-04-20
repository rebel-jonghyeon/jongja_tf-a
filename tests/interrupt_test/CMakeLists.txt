add_library(test_irq
	OBJECT
	test_m7_irq.c
)

target_link_libraries(test_irq
	PUBLIC
	cli_service
	interrupt_test_helper
)

target_include_directories(test_irq
	PUBLIC
	${TEST_COMMON_INCLUDES}
)
