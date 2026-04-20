#!/bin/sh
#
# run-riscv32-gdb.sh - debug on qemu via tcp port, or on fpga via jtag port
#
# Copyright (c) 2019 Cryptography Research, Inc. (CRI).
#-
#- Usage: %0 (q[emu]|f[pga]) {gdb-args}
#-
#- Enter '.' for {gdb-args} if no args are to be given.
#-
#- In case of fpga, among other things, creates and writes
#- 'openocd.log' to current directory.
#-
#  Also, in case of fpga:
#  You may have distribution-provided udev rules in place,
#  (/usr/lib/udev/rules.d/60-openocd.rules) for usb jtag connection.
#  If not, copy %csdk/share/udev/60-openocd.rules
#  to /etc/udev/rules.d/ and execute
#    sh -c 'udevadm control --reload-rules && udevadm trigger'
#

# after changes, before commit, test also with /bin/dash {this-command} [args]

openocd=openocd

set -euf

test $# -gt 1 || exec sed -n 's/%0/'"${0##*/}"'/; s/^#-//p' "$0"

case $1 in q|qe|qem|qemu)
	test "$#$2" = 2. && shift 2 || shift
	exec riscv32-unknown-elf-gdb \
		-ex 'set arch riscv:rv32' \
		-ex 'set disassemble-next-line on' \
		-ex 'set riscv use-compressed-breakpoints off' \
		-ex 'target remote localhost:1234' "$@"
	exit not reached
esac

case $1 in f|fp|fpg|fpga) ;; *)
	echo; echo " '$1' not 'qemu' nor 'fpga'"; echo
	exit 1
esac

test "$#$2" = 2. && shift 2 || shift

die () { printf '%s\n' "$*"; exit 1; } >&2

for x in riscv32-unknown-elf-gdb $openocd
do	command -v $x >/dev/null || die "'$x': command not found"
done

if test "${XDG_RUNTIME_DIR-}" && test -d "$XDG_RUNTIME_DIR"
then
	oocfg=$XDG_RUNTIME_DIR/cmrt-digilent-$$.cfg
else
	oocfg=`exec /bin/mktemp /tmp/cmrt-digilent-XXXXXX.cfg`
fi

# create openocd config
printf %s\\n '
# some modifications/additions done by Prashanth (orig digilent_jtag_hs3.cfg ?)
adapter_khz 10000
interface ftdi
ftdi_device_desc "Digilent USB Device"
ftdi_vid_pid 0x0403 0x6014
ftdi_channel 0
ftdi_layout_init 0x00e8 0x60eb
reset_config none
set _CHIPNAME riscv_debug
jtag newtap $_CHIPNAME cpu -irlen 5 -expected-id 0x10e31913
set _TARGETNAME $_CHIPNAME.cpu
target types
target create $_TARGETNAME riscv -chain-position $_TARGETNAME
init
$_TARGETNAME curstate
$_TARGETNAME configure -work-area-phys 0x80000000 -work-area-size 10000 -work-area-backup 1
halt' > "$oocfg"

exec 9<"$oocfg"
/bin/rm "$oocfg"
unset oocfg

exec riscv32-unknown-elf-gdb \
	-ex 'set arch riscv:rv32' \
	-ex 'set remotetimeout 240' \
	-ex 'set disassemble-next-line on' \
	-ex 'set riscv use-compressed-breakpoints off' \
	-ex 'target extended-remote | '$openocd' -p -l openocd.log -d3 -f /dev/fd/9' \
	"$@"


# Local variables:
# mode: shell-script
# sh-basic-offset: 8
# tab-width: 8
# End:
# vi: set sw=8 ts=8
