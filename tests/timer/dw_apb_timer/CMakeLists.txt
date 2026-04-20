add_library(test_dw_apb_timer
	OBJECT
	test_dw_apb_timer.c
)

target_link_libraries(test_dw_apb_timer
	PRIVATE	cli_service
	PUBLIC	dw_apb_timer
)

target_include_directories(test_dw_apb_timer
	PUBLIC
	${TEST_COMMON_INCLUDES}
)
