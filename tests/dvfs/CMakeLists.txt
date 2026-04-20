add_library(test_dvfs
	OBJECT
	test_dvfs_main.c
)

target_link_libraries(test_dvfs
	PUBLIC
	cli_service
	${DD_LISTS}
)

target_include_directories(test_dvfs
	PUBLIC
	${DD_COMMON_INCLUDES}
	../common # For test_common.h
)
