zephyr_include_directories(include)

zephyr_library()
zephyr_library_sources_ifdef(CONFIG_CMRT_SHSIG_LMS
	src/lms.c
	src/lms_ots.c
	src/tinycrypt/sha256.c
	src/tinycrypt/utils.c
)
zephyr_library_sources_ifdef(CONFIG_CMRT_SHSIG_XMSS src/xmss.c)
zephyr_library_sources_ifdef(CONFIG_CMRT_SHSIG_XMSS_MT src/xmss_mt.c)
