add_library(mailbox
	OBJECT
	mailbox.c
	mailbox_cb.c
)

target_link_libraries(mailbox
	PUBLIC
	${DEVICE_DRIVER_COMMON_LIBS}
)

target_include_directories(mailbox
	PUBLIC
	${CMAKE_CURRENT_LIST_DIR}
)
