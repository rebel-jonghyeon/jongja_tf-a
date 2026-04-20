add_library(test_gpio
	OBJECT
	test_gpio.c
)

target_link_libraries(test_gpio
	PRIVATE	cli_service
	PUBLIC	gpio
)

target_include_directories(test_gpio
	PUBLIC
	${TEST_COMMON_INCLUDES}
)
