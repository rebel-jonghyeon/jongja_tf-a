add_library(mailbox_test
	OBJECT
	test_mailbox_main.c
)

target_link_libraries(mailbox_test
	PUBLIC
	cli_service
	${DD_LISTS}
)

target_include_directories(mailbox_test
	PUBLIC
	${DD_COMMON_INCLUDES}
	../common # For test_common.h
)
