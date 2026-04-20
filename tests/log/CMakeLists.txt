add_library(show_log
	OBJECT
	rebel_h_log.c
)

target_link_libraries(show_log
	PUBLIC
	cli_service
	${DD_LISTS}
)

target_include_directories(show_log
	PUBLIC
	${DD_COMMON_INCLUDES}
	../common # For test_common.h
)
