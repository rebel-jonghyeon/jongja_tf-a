/**
 ******************************************************************************
 * @file:      sys_command_line.h
 * @author:    Cat
 * @version:   V1.0
 * @date:      2018-1-18
 * @brief:     command line
 * @attention:
 ******************************************************************************
 * The MIT License (MIT)
 *
 * Copyright (c) 2017-2018 ShareCat (sharecat73@gmail.com)
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * 'Software'), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED 'AS IS', WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE
 */

#ifndef __SYS_COMMAND_LINE_H__
#define __SYS_COMMAND_LINE_H__

#include <stdint.h>
#include <string.h>

#define MAX_INPUT_ARGUMENTS	32
#define CLI_HANDLE_LEN		256
#define CLI_MAX_CMD_COUNT	128

/* Macro config --------------------------------------------------------------*/
#define CLI_HISTORY			true				/* history command enable/disable */
#define HISTORY_MAX			32					/* maximum number ofhistory command */

#define KEY_ESC				0x1B
#define KEY_UP				"\x1b\x5b\x41"		/* [up] key: 0x1b 0x5b 0x41 */
#define KEY_DOWN			"\x1b\x5b\x42"		/* [down] key: 0x1b 0x5b 0x42 */
#define KEY_RIGHT			"\x1b\x5b\x43"		/* [right] key: 0x1b 0x5b 0x43 */
#define KEY_LEFT			"\x1b\x5b\x44"		/* [left] key: 0x1b 0x5b 0x44 */
#define KEY_ENTER			'\r'				/* [enter] key */
#define KEY_BACKSPACE		'\b'				/* [backspace] key */
#define KEY_BACKSPACE2		0x7F				/* [backspace] key */
#define KEY_DELETE			"\x1b\x5b\x33\x7e"	/* [delete] key */
#define KEY_HOME			"\x1b\x5b\x48"		/* [home] key */
#define KEY_HOME2			"\x1b\x5b\x31\x7e"	/* [home] key */
#define KEY_HOME3			"\x1b\x5b\x37\x7e"	/* [home] key */
#define KEY_END				"\x1b\x5b\x46"		/* [end] key */
#define KEY_END2			"\x1b\x5b\x34\x7e"	/* [end] key */
#define KEY_END3			"\x1b\x5b\x38\x7e"	/* [end] key */

/* terminal clear end */
#define TERMINAL_CLEAR_END()		CLI_PRINTF("\033[K")

/* terminal clear line */
#define TERMINAL_CLEAR_LINE()		CLI_PRINTF("\033[2K")

/* terminal clear all */
#define TERMINAL_DISPLAY_CLEAR()	CLI_PRINTF("\033[2J")

/* cursor move up */
#define TERMINAL_MOVE_UP(x)			CLI_PRINTF("\033[%dA", (x))

/* cursor move down */
#define TERMINAL_MOVE_DOWN(x)		CLI_PRINTF("\033[%dB", (x))

/* cursor move left */
#define TERMINAL_MOVE_LEFT(y)		CLI_PRINTF("\033[%dD", (y))

/* cursor move right */
#define TERMINAL_MOVE_RIGHT(y)		CLI_PRINTF("\033[%dC", (y))

/* cursor move to */
#define TERMINAL_MOVE_TO(x, y)		CLI_PRINTF("\033[%d;%dH", (x), (y))

/* cursor reset */
#define TERMINAL_RESET_CURSOR()		CLI_PRINTF("\033[H")

/* cursor invisible */
#define TERMINAL_HIDE_CURSOR()		CLI_PRINTF("\033[?25l")

/* cursor visible */
#define TERMINAL_SHOW_CURSOR()		CLI_PRINTF("\033[?25h")

/* reverse display */
#define TERMINAL_HIGH_LIGHT()		CLI_PRINTF("\033[7m")
#define TERMINAL_UN_HIGH_LIGHT()	CLI_PRINTF("\033[27m")

/* terminal display-------------------------------------------------------END */

typedef uint8_t (*cli_init_ptr)(void);
typedef uint8_t (*cli_func_ptr)(int argc, char *argv[]);

typedef int (*cli_printf_ptr)(const char *format, ...);
typedef int (*cli_put_data_ptr)(int data);

typedef struct {
	const char *pCmd;
	const char *pHelp;
	cli_init_ptr pInit;
	cli_func_ptr pFunc;
} COMMAND_S;

/*! @brief Register printf & putc functions for CLI. Uart must be initialized before CLI.
 * @param cli_printf The function pointer for printf
 * @param cli_put_data The function pointer for putc
 * @return None
 */
void cli_init(cli_printf_ptr cli_printf, cli_put_data_ptr cli_put_data);

/*! @brief Add received character and run CLI handler
 * @param data Received character
 * @return None
 */void cli_run(int data);

/*! @brief Do not call this function directly. Use CLI_REGISTER macro.
 * Register the command in CLI
 * @param cmd The pointer for text of command name
 * @param pInit The function pointer for initial to register in CLI
 * @param pFunc The function pointer for Handling RX cmd to register in CLI
 * @param help The pointer for text of the help string
 * @return 0 if register succeeds
 */
int cli_register(const char *cmd, const cli_init_ptr pInit,
	const cli_func_ptr pFunc, const char *help);

#define CLI_REGISTER(cmd, pInit, pFunc, help)				\
void cli_register_##cmd(void)				\
{							\
	cli_register(#cmd, pInit, pFunc, help);		\
}							\
void (*pcli_register_##cmd)() __attribute__ ((section(".cli_register_funcs"))) \
		= cli_register_##cmd

/**
 * @brief  find cli registered function
 * @param  command buffer
 * @retval 0 if failed
 */
int cli_find_function(char *handle_buf);

#endif /* __SYS_COMMAND_LINE_H__ */
