add_library(test_qspiapb
	OBJECT
	test_qspiapb.c
)

target_link_libraries(test_qspiapb
	PUBLIC
	cli_service
	${DD_LISTS}
)

target_include_directories(test_qspiapb
	PUBLIC
	${DD_COMMON_INCLUDES}
	../common # For test_common.h
)
