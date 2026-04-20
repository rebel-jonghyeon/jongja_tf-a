add_library(test_common
	OBJECT
	test_mailbox_cb.c
)

target_link_libraries(test_common
	PRIVATE	cli_service
	PUBLIC mailbox
)

target_include_directories(test_common
	PUBLIC
	${TEST_COMMON_INCLUDES}
)
