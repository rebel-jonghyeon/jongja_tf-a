add_library(test_i2c
	OBJECT
	test_i2c_main.c
)

target_link_libraries(test_i2c
	PUBLIC
	cli_service
	${DD_LISTS}
)

target_include_directories(test_i2c
	PUBLIC
	${DD_COMMON_INCLUDES}
	../common # For test_common.h
)
