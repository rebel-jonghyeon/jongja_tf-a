add_library(test_arm64
	OBJECT
	test_ca73.c
)

target_link_libraries(test_arm64
	PRIVATE	cli_service
	PUBLIC uart
)

target_include_directories(test_arm64
	PUBLIC
	${TEST_COMMON_INCLUDES}
)
