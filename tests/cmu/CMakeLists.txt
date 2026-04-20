add_library(test_cmu
	OBJECT
	test_cmu_main.c
)

target_link_libraries(test_cmu
	PUBLIC
	cli_service
	${DD_LISTS}
)

target_include_directories(test_cmu
	PUBLIC
	${DD_COMMON_INCLUDES}
	../common # For test_common.h
)
