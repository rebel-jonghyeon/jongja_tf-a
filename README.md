# Rebellion FDS Collab

## Table of Contents

<!-- toc -->
- [Rebellion FDS Collab](#rebellion-fds-collab)
  - [Table of Contents](#table-of-contents)
- [빌드하기](#빌드하기)
  - [환경변수 설정하기](#환경변수-설정하기)
  - [한꺼번에 모두 빌드하기](#한꺼번에-모두-빌드하기)
  - [FreeRTOS](#freertos)
    - [FreeRTOS CA73/CM7](#freertos-ca73cm7)
  - [Bootrom and bootloader](#bootrom-and-bootloader)
  - [CMRT](#cmrt)
  - [Clean images](#clean-images)
  - [LOG_HASH](#log_hash)
- [FreeRTOS-Kernel](#freertos-kernel)
  - [Getting started](#getting-started)
    - [Getting help](#getting-help)
  - [To consume FreeRTOS-Kernel](#to-consume-freertos-kernel)
    - [Consume with CMake](#consume-with-cmake)
    - [Consuming stand-alone - Cloning this repository](#consuming-stand-alone---cloning-this-repository)
  - [Repository structure](#repository-structure)
    - [Code Formatting](#code-formatting)
    - [Line Endings](#line-endings)
    - [Git History Optimizations](#git-history-optimizations)
    - [Spelling and Formatting](#spelling-and-formatting)
<!-- tocstop -->

# 빌드하기

## 환경변수 설정하기
1. [source_rebel_h.sh](source_rebel_h.sh) 파일로 이동
2. ZEBU 및 VWP 환경에서 작업하는 경우, `if [[ "$HOST_NAME" =~ ^vwp* ]]; then` 안에 있는 환경변수를 변경
3. 이외의 환경에서 작업하는 경우, `else` 안에 있는 환경변수를 변경

## 한꺼번에 모두 빌드하기
1. [최상위 폴더](#rebellion-fds-collab)로 이동
2. [`./build.sh all`](build.sh) 을 수행
3. [`binaries/`](binaries/) 아래에 image들이 생성됨

## FreeRTOS
1. [최상위 폴더](#rebellion-fds-collab)로 이동
2. [`./build.sh rtos`](osl/FreeRTOS/Source/build.sh)을 수행
3. [`binaries/FreeRTOS_CP`](binaries/FreeRTOS_CP/)에는 CA73의 image들이, [`binaries/FreeRTOS_PCIE`](binaries/FreeRTOS_PCIE/)에는 CM7의 image들이 생성됨

### FreeRTOS CA73/CM7
1. [`cd osl/FreeRTOS/Source`](osl/FreeRTOS/Source/)
2. [`./build.sh ca`](osl/FreeRTOS/Source/build.sh) 혹은 [`./build.sh cm`](osl/FreeRTOS/Source/build.sh) 을 수행 (ca는 CA73, cm은 CM7을 위한 FreeRTOS를 빌드)
3. [`binaries/FreeRTOS_CP`](binaries/FreeRTOS_CP/)에는 CA73의 image들이, [`binaries/FreeRTOS_PCIE`](binaries/FreeRTOS_PCIE/)에는 CM7의 image들이 생성됨

## Bootrom and bootloader
1. [`cd bootloader/cp`](bootloader/cp/)
2. [`./build.sh`](bootloader/cp/build.sh) 실행
3. [`binaries/BootLoader_CP`](binaries/BootLoader_CP/)에 `fboot_n/` `sboot_n/` `tboot_n`이 생성됨

## CMRT
1. [`cd bootloader/rotcmrt-zephyr-2.0.36`](bootloader/rot/cmrt-zephyr-2.0.36/)
2. [`source source sourceme-env-setup`](bootloader/rot/cmrt-zephyr-2.0.36/sourceme-env-setup)와 [`source cmrt-zephyr-env.sh`](bootloader/rot/cmrt-zephyr-2.0.36/cmrt-zephyr-env.sh) 실행
3. 빌드하려고 하는 Directory로 이동 후, `make RELEASE_BUILD=1` 실행

## Clean images
- [`./build.sh clean`](build.sh) : Clean all
- `cd {child_directory} ; ./build.sh clean` : Clean specific image

binaries경로에 lst, elf, bin, map 파일들이 함께생성되니 디버깅에 사용하면 됨

## LOG_HASH
1. **Encoding logs to hash with build option**
   - Basic Encoding Build : `./build.sh --loghash`
   - Build with Release Messages : `./build.sh --loghash --rel_msg "1124_buildtest"`

       record build information "1124_buildtest" in hashmap.csv as header

2. **How to decode**

   **Copy and Use scripts/log_hash directory at any location**

   Decode a Single Text File (Anywhere) : `python3 log_hash_decoder.py <hashmap.csv path> <textfile path to decode>`

   Decode a Whole Directory (In the Log Hash Scripts Folder) : `python3 log_hash_decoder.py`

---

# FreeRTOS-Kernel

[![CMock Unit Tests](https://github.com/FreeRTOS/FreeRTOS-Kernel/actions/workflows/unit-tests.yml/badge.svg?branch=main&event=push)](https://github.com/FreeRTOS/FreeRTOS-Kernel/actions/workflows/unit-tests.yml?query=branch%3Amain+event%3Apush+workflow%3A%22CMock+Unit+Tests%22++)
[![codecov](https://codecov.io/gh/FreeRTOS/FreeRTOS-Kernel/badge.svg?branch=main)](https://codecov.io/gh/FreeRTOS/FreeRTOS-Kernel)

## Getting started

This repository contains FreeRTOS kernel source/header files and kernel
ports only. This repository is referenced as a submodule in
[FreeRTOS/FreeRTOS](https://github.com/FreeRTOS/FreeRTOS)
repository, which contains pre-configured demo application projects under
```FreeRTOS/Demo``` directory.

The easiest way to use FreeRTOS is to start with one of the pre-configured demo
application projects.  That way you will have the correct FreeRTOS source files
included, and the correct include paths configured. Once a demo application is
building and executing you can remove the demo application files, and start to
add in your own application source files.  See the
[FreeRTOS Kernel Quick Start Guide](https://www.FreeRTOS.org/FreeRTOS-quick-start-guide.html)
for detailed instructions and other useful links.

Additionally, for FreeRTOS kernel feature information refer to the
[Developer Documentation](https://www.FreeRTOS.org/features.html),
and [API Reference](https://www.FreeRTOS.org/a00106.html).

Also for contributing and creating a Pull Request please refer to
[the instructions here](.github/CONTRIBUTING.md#contributing-via-pull-request).

### Getting help

If you have any questions or need assistance troubleshooting your FreeRTOS project,
we have an active community that can help on the
[FreeRTOS Community Support Forum](https://forums.freertos.org).

## To consume FreeRTOS-Kernel

### Consume with CMake

If using CMake, it is recommended to use this repository using FetchContent.
Add the following into your project's main or a subdirectory's `CMakeLists.txt`:

- Define the source and version/tag you want to use:

```cmake
FetchContent_Declare( freertos_kernel
  GIT_REPOSITORY https://github.com/FreeRTOS/FreeRTOS-Kernel.git
  GIT_TAG        main #Note: Best practice to use specific git-hash or tagged version
)
```

In case you prefer to add it as a git submodule, do:

```bash
git submodule add https://github.com/FreeRTOS/FreeRTOS-Kernel.git <path of the submodule>
git submodule update --init
```

- Add a freertos_config library (typically an INTERFACE library) The following assumes the directory structure:
  - `include/FreeRTOSConfig.h`

```cmake
add_library(freertos_config INTERFACE)

target_include_directories(freertos_config SYSTEM
INTERFACE
    include
)

target_compile_definitions(freertos_config
  INTERFACE
    projCOVERAGE_TEST=0
)
```

In case you installed FreeRTOS-Kernel as a submodule, you will have to add it as a subdirectory:

```cmake
add_subdirectory(${FREERTOS_PATH})
```

- Configure the FreeRTOS-Kernel and make it available
  - this particular example supports a native and cross-compiled build option.

```cmake
set( FREERTOS_HEAP "4" CACHE STRING "" FORCE)
# Select the native compile PORT
set( FREERTOS_PORT "GCC_POSIX" CACHE STRING "" FORCE)
# Select the cross-compile PORT
if (CMAKE_CROSSCOMPILING)
  set(FREERTOS_PORT "GCC_ARM_CA9" CACHE STRING "" FORCE)
endif()

FetchContent_MakeAvailable(freertos_kernel)
```

- In case of cross compilation, you should also add the following to `freertos_config`:

```cmake
target_compile_definitions(freertos_config INTERFACE ${definitions})
target_compile_options(freertos_config INTERFACE ${options})
```

### Consuming stand-alone - Cloning this repository

To clone using HTTPS:

```
git clone https://github.com/FreeRTOS/FreeRTOS-Kernel.git
```

Using SSH:

```
git clone git@github.com:FreeRTOS/FreeRTOS-Kernel.git
```

## Repository structure

- The root of this repository contains the three files that are common to
every port - list.c, queue.c and tasks.c.  The kernel is contained within these
three files.  croutine.c implements the optional co-routine functionality - which
is normally only used on very memory limited systems.

- The ```./portable``` directory contains the files that are specific to a particular microcontroller and/or compiler.
See the readme file in the ```./portable``` directory for more information.

- The ```./include``` directory contains the real time kernel header files.

- The ```./template_configuration``` directory contains a sample `FreeRTOSConfig.h` to help jumpstart a new project.
See the [FreeRTOSConfig.h](examples/template_configuration/FreeRTOSConfig.h) file for instructions.

### Code Formatting

FreeRTOS files are formatted using the
"[uncrustify](https://github.com/uncrustify/uncrustify)" tool.
The configuration file used by uncrustify can be found in the
[FreeRTOS/CI-CD-GitHub-Actions's](https://github.com/FreeRTOS/CI-CD-Github-Actions)
[uncrustify.cfg](https://github.com/FreeRTOS/CI-CD-Github-Actions/tree/main/formatting)
file.

### Line Endings

File checked into the FreeRTOS-Kernel repository use unix-style LF line endings
for the best compatibility with git.

For optimal compatibility with Microsoft Windows tools, it is best to enable
the git autocrlf feature. You can enable this setting for the current
repository using the following command:

```
git config core.autocrlf true
```

### Git History Optimizations

Some commits in this repository perform large refactors which touch many lines
and lead to unwanted behavior when using the `git blame` command. You can
configure git to ignore the list of large refactor commits in this repository
with the following command:

```
git config blame.ignoreRevsFile .git-blame-ignore-revs
```

### Spelling and Formatting

We recommend using [Visual Studio Code](https://code.visualstudio.com),
commonly referred to as VSCode, when working on the FreeRTOS-Kernel.
The FreeRTOS-Kernel also uses [cSpell](https://cspell.org/) as part of its
spelling check. The config file for which can be found at [cspell.config.yaml](cspell.config.yaml)
There is additionally a
[cSpell plugin for VSCode](https://marketplace.visualstudio.com/items?itemName=streetsidesoftware.code-spell-checker)
that can be used as well.
*[.cSpellWords.txt](.github/.cSpellWords.txt)* contains words that are not
traditionally found in an English dictionary. It is used by the spellchecker
to verify the various jargon, variable names, and other odd words used in the
FreeRTOS code base are correct. If your pull request fails to pass the spelling
and you believe this is a mistake, then add the word to
*[.cSpellWords.txt](.github/.cSpellWords.txt)*. When adding a word please
then sort the list, which can be done by running the bash command:
`sort -u .cSpellWords.txt -o .cSpellWords.txt`
Note that only the FreeRTOS-Kernel Source Files, [include](include),
[portable/MemMang](portable/MemMang), and [portable/Common](portable/Common)
files are checked for proper spelling, and formatting at this time.
