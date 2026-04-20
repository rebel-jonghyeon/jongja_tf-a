#!/bin/bash

# Read files/directories to exclude from ALL checkpatch rules.
# Patterns in this file are regular expressions.
ALL_EXCLUDE_CONF="./scripts/checkpatch_all_exclude.conf"

ALL_EXCLUDE_ARGS=()
if [ -f "$ALL_EXCLUDE_CONF" ]; then
    while IFS= read -r line; do
        line=$(echo "$line" | sed 's/#.*//' | xargs)
        if [ -n "$line" ]; then
            ALL_EXCLUDE_ARGS+=("--exclude=$line")
        fi
    done < "$ALL_EXCLUDE_CONF"
fi

# Read directories that should skip the max line length check.
# These directories are excluded from Pass 1 and re-checked in Pass 3
# with LONG_LINE checks disabled.
LONG_LINE_EXCLUDE_CONF="./scripts/checkpatch_long_line_exclude.conf"

LONG_LINE_EXCLUDE_ARGS=()
LONG_LINE_CHECK_ONLY_ARGS=()
if [ -f "$LONG_LINE_EXCLUDE_CONF" ]; then
    while IFS= read -r line; do
        line=$(echo "$line" | sed 's/#.*//' | xargs)
        if [ -n "$line" ]; then
            LONG_LINE_EXCLUDE_ARGS+=("--exclude=$line")
            LONG_LINE_CHECK_ONLY_ARGS+=("--check-only=$line")
        fi
    done < "$LONG_LINE_EXCLUDE_CONF"
fi

# Pass 1: Main check (long-line-exempt dirs excluded here, re-checked in Pass 3)
./scripts/checkpatch.pl -g origin/master..HEAD \
--no-signoff \
--no-tree \
--tab-size=4 \
--ignore=CAMELCASE,FILE_PATH_CHANGES,COMMIT_MESSAGE,MACRO_ARG_REUSE,SPDX_LICENSE_TAG,NEW_TYPEDEFS,\
VOLATILE,EMBEDDED_FILENAME,DEEP_INDENTATION,EMAIL_SUBJECT,MACRO_WITH_FLOW_CONTROL,PREFER_SECTION,\
SPLIT_STRING,UNNECESSARY_ELSE,EMBEDDED_FUNCTION_NAME,PREFER_PACKED,PREFER_ALIGNED,AVOID_EXTERNS,\
MULTISTATEMENT_MACRO_USE_DO_WHILE,COMPLEX_MACRO,BRACES,REPEATED_WORD,SSCANF_TO_KSTRTO,PREFER_KERNEL_TYPES,\
BAD_SIGN_OFF \
--exclude=osl/FreeRTOS \
--max-line-length=120 \
--strict \
--exclude=bootloader/cp/tf-a/plat/mediatek/drivers/apusys/apusys_rv/2.0 \
--exclude=bootloader/cp/tf-a/drivers/aw \
"${ALL_EXCLUDE_ARGS[@]}" \
"${LONG_LINE_EXCLUDE_ARGS[@]}" \
&& \
# Pass 2: FreeRTOS services check
./scripts/checkpatch.pl -g origin/master..HEAD \
--no-signoff \
--no-tree \
--tab-size=4 \
--ignore=FILE_PATH_CHANGES,COMMIT_MESSAGE,MACRO_ARG_REUSE,SPDX_LICENSE_TAG,NEW_TYPEDEFS,\
VOLATILE,EMBEDDED_FILENAME,DEEP_INDENTATION,EMAIL_SUBJECT,MACRO_WITH_FLOW_CONTROL,PREFER_SECTION,\
SPLIT_STRING,UNNECESSARY_ELSE,EMBEDDED_FUNCTION_NAME,PREFER_PACKED,PREFER_ALIGNED,AVOID_EXTERNS,\
MULTISTATEMENT_MACRO_USE_DO_WHILE,COMPLEX_MACRO,BRACES,REPEATED_WORD,SSCANF_TO_KSTRTO,BAD_SIGN_OFF \
--check-only=osl/FreeRTOS/Source/services \
--max-line-length=120 \
"${ALL_EXCLUDE_ARGS[@]}" \
&& \
# Pass 3: Re-check long-line-exempt dirs with LONG_LINE checks disabled
{ [ ${#LONG_LINE_EXCLUDE_ARGS[@]} -eq 0 ] || \
./scripts/checkpatch.pl -g origin/master..HEAD \
--no-signoff \
--no-tree \
--tab-size=4 \
--ignore=CAMELCASE,FILE_PATH_CHANGES,COMMIT_MESSAGE,MACRO_ARG_REUSE,SPDX_LICENSE_TAG,NEW_TYPEDEFS,\
VOLATILE,EMBEDDED_FILENAME,DEEP_INDENTATION,EMAIL_SUBJECT,MACRO_WITH_FLOW_CONTROL,PREFER_SECTION,\
SPLIT_STRING,UNNECESSARY_ELSE,EMBEDDED_FUNCTION_NAME,PREFER_PACKED,PREFER_ALIGNED,AVOID_EXTERNS,\
MULTISTATEMENT_MACRO_USE_DO_WHILE,COMPLEX_MACRO,BRACES,REPEATED_WORD,SSCANF_TO_KSTRTO,PREFER_KERNEL_TYPES,\
BAD_SIGN_OFF,LONG_LINE,LONG_LINE_COMMENT,LONG_LINE_STRING \
--max-line-length=120 \
--strict \
"${ALL_EXCLUDE_ARGS[@]}" \
"${LONG_LINE_CHECK_ONLY_ARGS[@]}"; } \
&& \
# Pass 4: Re-check dirs that need extra checks disabled
# (GLOBAL_INITIALISERS, BAD_SIGN_OFF, TRAILING_WHITESPACE)
./scripts/checkpatch.pl -g origin/master..HEAD \
--no-signoff \
--no-tree \
--tab-size=4 \
--ignore=CAMELCASE,FILE_PATH_CHANGES,COMMIT_MESSAGE,MACRO_ARG_REUSE,SPDX_LICENSE_TAG,NEW_TYPEDEFS,\
VOLATILE,EMBEDDED_FILENAME,DEEP_INDENTATION,EMAIL_SUBJECT,MACRO_WITH_FLOW_CONTROL,PREFER_SECTION,\
SPLIT_STRING,UNNECESSARY_ELSE,EMBEDDED_FUNCTION_NAME,PREFER_PACKED,PREFER_ALIGNED,AVOID_EXTERNS,\
MULTISTATEMENT_MACRO_USE_DO_WHILE,COMPLEX_MACRO,BRACES,REPEATED_WORD,SSCANF_TO_KSTRTO,PREFER_KERNEL_TYPES,\
GLOBAL_INITIALISERS,BAD_SIGN_OFF,TRAILING_WHITESPACE \
--check-only=bootloader/cp/tf-a/plat/mediatek/drivers/apusys/apusys_rv/2.0 \
--check-only=bootloader/cp/tf-a/drivers/aw \
--max-line-length=120 \
--strict \
"${ALL_EXCLUDE_ARGS[@]}"
