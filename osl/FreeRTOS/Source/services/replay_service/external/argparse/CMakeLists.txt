set(EXT_LIB_ARGPARSE_INCLUDE, "${CMAKE_CURRENT_LIST_DIR}")
add_library(argparse
	OBJECT
	argparse.c
)

target_link_libraries(argparse
	PUBLIC
	freertos_kernel
)

target_include_directories(argparse
	PUBLIC
	${CMAKE_CURRENT_LIST_DIR}
	${SVC_COMMON_INCLUDES}
	${RUSH_CLI_INCLUDES}
)
