set(RUSH_CLI_SOURCES
	rush_cli.c
	rush_cli_util.c
	rush_cli_msg_buf.c
	command/tpg_cli.c
	command/rbdma_cli.c
	command/mem_cli.c
)

add_library(rush_cli
	OBJECT
	${RUSH_CLI_SOURCES}
)

target_link_libraries(rush_cli
	PUBLIC
	argparse
	freertos_kernel
	c
)

target_include_directories(rush_cli
	PUBLIC
	${CMAKE_CURRENT_LIST_DIR}
	${SVC_COMMON_INCLUDES}
	${EXT_LIB_ARGPARSE_INCLUDE}
)
