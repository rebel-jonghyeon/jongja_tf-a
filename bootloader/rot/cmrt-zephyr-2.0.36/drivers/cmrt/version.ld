/*
 * Copyright (c) 2022 Cryptography Research, Inc. (CRI).
 */

	. = ALIGN(4);
	__cmrt_version_head = .;
	BYTE(0x43)
	BYTE(0x10)
	BYTE((__cmrt_version_end - __cmrt_random_end + 3) / 4)
	BYTE((__cmrt_random_end - __cmrt_random_begin) / 4)
	HIDDEN(__cmrt_random_begin = .);
	KEEP(*(version.random .version.random))
	. = ALIGN(4);
	HIDDEN(__cmrt_random_end = .);
	KEEP(*(SORT_BY_NAME(version*) SORT_BY_NAME(.version*)))
	. = ALIGN(4);
	PROVIDE_HIDDEN(__cmrt_version_end = .);
