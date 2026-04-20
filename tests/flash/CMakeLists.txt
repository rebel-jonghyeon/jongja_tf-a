add_library(test_flash
	OBJECT
	test_flash.c
)

target_link_libraries(test_flash
	PRIVATE	cli_service
	PUBLIC	flash
)

target_include_directories(test_flash
	PUBLIC
	${TEST_COMMON_INCLUDES}
)
