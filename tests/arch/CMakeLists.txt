add_library(test_arch
	OBJECT
	test_cli.c
)

target_link_libraries(test_arch
	PRIVATE	cli_service
)

target_include_directories(test_arch
	PUBLIC
	${TEST_COMMON_INCLUDES}
)
