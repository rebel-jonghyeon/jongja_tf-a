#!/bin/sh

# An alternative to sourcing cmrt-zephyr-env.sh; useful in automation,
# and in cases user not running supported shell (bash or zsh).

case ${BASH_VERSION-} in *.*) set -o posix; shopt -s xpg_echo; esac
case ${ZSH_VERSION-} in *.*) emulate ksh; esac

set -euf  # hint: sh -x thisfile [args] to trace execution

die () { printf '%s\n' '' "$@" ''; exit 1; } >&2

#echo "'$0'"
# now absolute path...
case $0 in /*/../*) dn0=`cd "${0%/*}" && pwd`
	;; /*)	dn0=${0%/*}
	;; */*/*) dn0=`cd "${0%/*}" && pwd`
	;; ./*) dn0=$PWD
	;; */*) dn0=`cd "${0%/*}" && pwd`
	;; *)	dn0=$PWD
esac

export ZEPHYR_BASE=$dn0
shrc=$dn0/cmrt-zephyr-env.sh
. $shrc

test $# = 0 || { exec "$@"; exit not reached; }

echo No command given
echo Environment variables touched when ${0##*/} is run with command '[args]'
echo

for v in `sed -n '/\<export / { s/.*\<export  *//; s/[= ].*//; p; }' $shrc`
do
case $v in *[!A-Z0-9_]*) ;; *) eval echo $v=\$$v ;; esac
done
echo
