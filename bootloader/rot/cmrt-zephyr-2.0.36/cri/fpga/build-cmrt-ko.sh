#!/bin/sh
# -*- mode: shell-script; sh-basic-offset: 8; tab-width: 8 -*-
# $ build-cmrt-ko.sh $
#
# Copyright (c) 2022-2023 Cryptography Research, Inc. (CRI).
#
# This program builds cmrt.ko easily and conveniently,
# and without polluting current shell environment.

set -euf

LANG=C LC_ALL=C; export LANG LC_ALL; unset LANGUAGE
#PATH='/sbin:/usr/sbin:/bin:/usr/bin'; export PATH

saved_IFS=$IFS; readonly saved_IFS

vendor=poky  # yocto default
vendor=cri   # our variant

die () { printf '%s\n' "$*"; exit 1; } >&2

test "$0" -ef "./${0##*/}" || die "Execute ./${0##*/} in `exec dirname "$0"`/"

for f in cmrt2.c Makefile-zynq706
do  test -f $f || die "'$f' does not exist."
done

case ${CC-} in *arm*)
    die "Arm cross-compilation environment already set up. Unsafe to continue."
esac


test $# = 1 || test $# = 2 || {
    exec >&2
    echo
    echo Usage: $0 path-to-bsp-root '[--sudo-fixdep]'
    echo
    echo 'Install cmrt cmrt2 zynq bsp if path-to-bsp-root/ is not (yet) available.'
    echo
    echo "'--sudo-fixdep' is needed when building fixdep(1) (in bsp-root)"
    echo ' requires more permissions. The build needs to be done only once.'
    echo
    echo Build copies Makefile and and cmrt2.c to ./cmrt-out/ -- and overwrites
    echo these every time. Edit the originals in this directory.
    echo
    exit 1
}

case $1 in /*) ;; *) die "'$1' not absolute path" ;; esac

if test $# = 2
then
        test $2 = --sudo-fixdep || die "'$2' is not '--sudo-fixdep'"
        sudo_fixdep=true
else
        sudo_fixdep=false
fi

kdir=$1/sysroots/cortexa9hf-neon-$vendor-linux-gnueabi/usr/src/kernel

test -d "$kdir" || die "'$kdir/': no such directory"

envfile=$1/environment-setup-cortexa9hf-neon-$vendor-linux-gnueabi

test -f "$envfile" || die "'$envfile: no such file"

setci () {
        # Note: in case of shallow clone change is usually older than observed.
        set -- `git log -1 --abbrev=7 --name-status --format='%ci %h' cmrt2.c`
        commit_info=$1-g$4
        case ${5-} in (M) ;; *) commit_info=before-$commit_info; esac
        if test "`git status --porcelain cmrt2.c`"
        then commit_info=$commit_info-mod
        fi
}
commit_info=`date +%Y-%m-%d`-g0000000

echo sourcing "'$envfile'"
set +uf
. "$envfile"
set -uf

# neat: environment-setup-... decided to clobber the same variable
envfile=$1/environment-setup-cortexa9hf-neon-$vendor-linux-gnueabi

test -f "$kdir"/scripts/basic/fixdep || (
    set -x
    cd "$kdir"
    if $sudo_fixdep
    then sudo /bin/sh -xc '. "$1"; make scripts' arg0 "$envfile"
    else make scripts
    fi
)
# append '--sudo-fixdep' to the command line if above failed
# due to missing root permissions

test -d cmrt-out || mkdir cmrt-out

cp Makefile-zynq706 cmrt-out/Makefile
sed "/^int init_module/,/pr_info/ s/%s/%s (cmrt.ko $commit_info)/" \
    cmrt2.c > cmrt-out/cmrt2.c

( CMRT_INCDIR=`cd ../../include/drivers/cmrt && pwd -P`
  cd cmrt-out
  x_exec () { printf '+ %s\n' "$*" >&2; exec "$@"; }
  x_exec make -C "$kdir" M="$PWD" CMRT_INCDIR="$CMRT_INCDIR"
)
echo
echo + commit $commit_info
set -x
md5sum cmrt-out/cmrt2.ko
command -v modinfo >/dev/null && modinfo cmrt-out/cmrt2.ko || :
