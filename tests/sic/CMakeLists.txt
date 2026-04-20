add_library(test_sic
	OBJECT
	test_sic.c
)

target_link_libraries(test_sic
	PRIVATE	cli_service
	PUBLIC	sic
)

target_include_directories(test_sic
	PUBLIC
	${TEST_COMMON_INCLUDES}
)
