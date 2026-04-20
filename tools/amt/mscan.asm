//
// Microsequencer assembly language for the MSCAN algorithm
//
MINADDR = 0x0
LENGTH = 0x100
MAXADDR = 0x3FFC

START = r0
LENREG = r1
WRDATA = r2
RDDATA = r3
LOOPCNT = r4
SINGLE = r5

set START, MINADDR
set LENREG, LENGTH
set WRDATA, 0x00003cc3
set LOOPCNT, 0x1
set SINGLE, 1
add RDDATA, WRDATA, 0x1

STAGE1:
    mem_write START, LENREG, 1, 0, 0, 0, 0
    mem_read START, LENREG, 1, 0, 0, 1, 0
    add LOOPCNT, LOOPCNT, -1
    jump_not0 LOOPCNT, STAGE1

halt
