add_library(test_arm
	OBJECT
	test_cm7.c
)

target_link_libraries(test_arm
	PRIVATE	cli_service
)

target_include_directories(test_arm
	PUBLIC
	${TEST_COMMON_INCLUDES}
)
