#!/bin/sh

# Add autoload container to the end of OS image bundle.
# For the middleware we expect that to be a user container image.

die () { printf '%s\n' "$@"; exit 1; } >&2

set -euf

needcmd () {
	command -v "$1" >/dev/null || die "'$1': command not found"
}

needcmd cmrt-image-header.py

# check whether mwtest is in the same dir as this script
case $0 in */*) mwtest_py=${0%/*}/mwtest.py
	;; *) mwtest_py=./mwtest.py
esac
test -x "$mwtest_py" || {
	mwtest_py=mwtest.py
	needcmd $mwtest_py
}

test $# = 3 || die "Usage: ${0##*/} os.img container.img os-autoload.img"

for arg
do case $arg in *"'"*) die "\"'\"s in '$arg'"; esac
done

test -f "$1" || die "'$1' does not exist"
test -f "$2" || die "'$2' does not exist"

test -f "$3" && die "'$3' exists."

x () { printf '+ %s\n' "$*" >&2; "$@"; }
x_eval () { printf '+ %s\n' "$*" >&2; eval "$*"; }

# Remove temp files at the end of execution.
trap "x rm -f '$2.tmp1' '$2.tmp2'" 0

# Write mw run command to the front of the image.
x_eval "$mwtest_py -n -c 100 run '$2' > '$2.tmp1'"

# Write an image header to the front of the image.
x cmrt-image-header.py "$2.tmp1" "$2.tmp2"

# Catenate the image to the OS image bundle.
x_eval "cat '$1' '$2.tmp2' > '$3'"
