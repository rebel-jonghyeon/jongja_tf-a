#
# Copyright (c) 2022-2023 Cryptography Research, Inc. (CRI)
#
# Some parts originally from zephyr-env.sh (by Wind River Systems):
#
##
## Copyright (c) 2015 Wind River Systems, Inc.
##
## SPDX-License-Identifier: Apache-2.0
##

test "${RISCV32_TOOLCHAIN_PATH-}" || {
	echo
	echo "RISCV32_TOOLCHAIN_PATH not defined in environment."
	echo "Source CMRT SDK environment first."
	echo
	return 1
	exit 1
	export RISCV32_TOOLCHAIN_PATH # not executed, sed(1)ed by with-cmrt-env.sh...
} >&2

_cze_gcc=$RISCV32_TOOLCHAIN_PATH/./bin/riscv32-unknown-elf-gcc-10.2.0
test -x $_cze_gcc || {
	echo
	echo "'$_cze_gcc': no such executable."
	echo 'Unexpected $RISCV32_TOOLCHAIN_PATH.'
	unset _cze_gcc
	return 1
	exit 1
} >&2
unset _cze_gcc

if [ -z "${ZEPHYR_BASE:-}" ]
then
  # In zsh the value of $0 depends on the FUNCTION_ARGZERO option which is
  # set by default. FUNCTION_ARGZERO, when it is set, sets $0 temporarily
  # to the name of the function/script when executing a shell function or
  # sourcing a script. POSIX_ARGZERO option, when it is set, exposes the
  # original value of $0 in spite of the current FUNCTION_ARGZERO setting.
  #
  # Note: The version of zsh need to be 5.0.6 or above. Any versions below
  # 5.0.6 maybe encounter errors when sourcing this script.
  if [ -n "${ZSH_VERSION-}" ]
  then	_cze_path="${(%):-%N}"
	case $options[posixargzero]
	in on)
		_cze_bn0=${0##*/}
	;; off)
		setopt posixargzero
		_cze_bn0=${0##*/}
		unsetopt posixargzero
	;; *)
		_cze_bn0=unknown
	esac
	_cze_pwd_opt=-q
  else
	# note: if not zsh, bash is expected. no prob if ZEPHYR_ENV is set...
	_cze_path="${BASH_SOURCE[0]}"
	_cze_bn0=${0##*/}
	_cze_pwd_opt=
  fi

  _cze_name='cmrt-zephyr-env.sh'
  if [ "$_cze_bn0" = $_cze_name ]
  then	printf 'Source this file (do NOT execute it!) '
	echo to set the CMRT Zephyr Kernel environment.
	return 1 2>/dev/null
	exit 1
  fi

  # identify OS source tree root directory
  case $_cze_path in
	$_cze_name | ./$_cze_name )
		ZEPHYR_BASE=$PWD
		;;
	../$_cze_name )
		ZEPHYR_BASE=$(builtin cd $_cze_pwd_opt .. && pwd )
		;;
	*/$_cze_name )
		ZEPHYR_BASE=$(builtin cd $_cze_pwd_opt ${_cze_path%/*} && pwd )
		;;
	*)
		echo "Cannot resolve ZEPHYR_BASE from '$_cze_path'"
		return 1
		exit 1
  esac
  unset _cze_path _cze_bn0 _cze_pwd_opt _cze_name
  export ZEPHYR_BASE
fi

export BOARD=cmrt_finchley

export CROSS_COMPILE=$RISCV32_TOOLCHAIN_PATH/bin/riscv32-unknown-elf-
export ZEPHYR_TOOLCHAIN_VARIANT=cross-compile

case $PATH in *$ZEPHYR_BASE/build/*) ;; *)
 export PATH=$ZEPHYR_BASE/scripts:$ZEPHYR_BASE/build/bin:$ZEPHYR_BASE/cmrt/bin:$PATH
esac

case ${LD_LIBRARY_PATH-} in *$ZEPHYR_BASE/build/*) ;; *)
 export LD_LIBRARY_PATH=$ZEPHYR_BASE/build/lib${LD_LIBRARY_PATH:+:$LD_LIBRARY_PATH}
esac

case ${PYTHONPATH-} in *$ZEPHYR_BASE/build/*) ;; *)
 export PYTHONPATH=$ZEPHYR_BASE/build/lib/python:$ZEPHYR_BASE/cmrt/lib/python${PYTHONPATH:+:$PYTHONPATH}
esac

