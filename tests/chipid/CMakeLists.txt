add_library(test_chipid
	OBJECT
	read_chipid.c
)

target_link_libraries(test_chipid
	PUBLIC
	cli_service
	${DD_LISTS}
)

target_include_directories(test_chipid
	PUBLIC
	${DD_COMMON_INCLUDES}
	../common # For test_common.h
)
