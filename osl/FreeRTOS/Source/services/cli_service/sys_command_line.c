/**
 ******************************************************************************
 * @file:      sys_command_line.c
 * @author:    Cat
 * @version:   V1.0
 * @date:      2018-1-18
 * @brief:     command line
 * @attention:
 *
 *             V0.5: [add] colorful log print API
 *             V0.6: [add] history command support
 *
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

#include <stdarg.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

#include "sys_command_line.h"

#define ENABLE	true
#define DISABLE	false

#define CLI_PRINTF(...)		do { if (cli_printf) cli_printf(__VA_ARGS__); } while (0)
#define CLI_PUTC(data)		do { if (cli_put_data) cli_put_data(data); } while (0)

static uint8_t cli_help(int argc, char *argv[]);
static uint8_t cli_clear(int argc, char *argv[]);
static uint8_t cli_echo(int argc, char *argv[]);

typedef struct {
	char buff[CLI_HANDLE_LEN];
	uint8_t len;
} HANDLE_TYPE_S;

// uint8_t cli_echo_flag = DISABLE; /* ECHO default: disable */
uint8_t cli_echo_flag = ENABLE; /* ECHO default: disable */

static const char cli_prompt_buf[] = "REBELLIONS$ ";

const char CLI_Cmd_Help[] =
	"\r\n"
	"[help]\r\n"
	" * show commands\r\n"
	"\r\n";

const char CLI_Cmd_Clear[] =
	"[cls]\r\n"
	" * clear the screen\r\n"
	"\r\n";

const char CLI_Cmd_Echo[] =
	"[echo]\r\n"
	" * echo 1: echo on\r\n"
	" * echo 0: echo off\r\n"
	"\r\n";

/**
 * cmd struct
 */
COMMAND_S CLI_Cmd[CLI_MAX_CMD_COUNT] = {
	/* cmd			cmd help			init func.	func. */
	{"help",		CLI_Cmd_Help,		NULL,		cli_help},
	{"cls",			CLI_Cmd_Clear,		NULL,		cli_clear},
	{"echo",		CLI_Cmd_Echo,		NULL,		cli_echo},

	/* application cmd start */
};
static int num_cli_cmds = 3;

static cli_printf_ptr cli_printf;
static cli_put_data_ptr cli_put_data;

static void __attribute__((__used__)) cli_delay(uint32_t nCount)
{
	while (nCount--)
		;
}

static char *strtok_(char *s, const char *ct)
{
	char *sbegin, *send;

	sbegin  = s;
	if (!sbegin)
		return 0;

	sbegin += strspn(sbegin, ct);
	if (*sbegin == '\0')
		return 0;

	send = strpbrk(sbegin, ct);
	if (send && *send != '\0')
		*send++ = '\0';

	return sbegin;
}

static void cli_prompt(void)
{
	CLI_PRINTF("%s", cli_prompt_buf);
}

static uint8_t parse_arguments(char *para, uint8_t para_len, int *argc, char **argv)
{
	char *arg = NULL;
	int arg_cnt = 0;

	*argc = 0;

	if (para_len <= 0)
		return -1;

	arg = strtok_(para, " ");

	while (arg != NULL && arg_cnt < MAX_INPUT_ARGUMENTS) {
		argv[arg_cnt++] = arg;

		arg = strtok_(arg + strlen(arg) + 1, " ");
	}

	*argc = arg_cnt;

	return 0;
}

int cli_cmd_cmp(const void *a, const void *b)
{
	return strcmp(((const COMMAND_S *)a)->pCmd, ((const COMMAND_S *)b)->pCmd);
}

/**
 * @brief  printf the help info.
 * @param  para addr. & length
 * @retval True means OK
 */
static uint8_t cli_help(int argc, char *argv[])
{
	uint8_t i;

	for (i = 0; i < sizeof(CLI_Cmd) / sizeof(COMMAND_S); i++) {
		if (CLI_Cmd[i].pHelp != NULL)
			CLI_PRINTF("%s", CLI_Cmd[i].pHelp);
	}

	return true;
}

/**
 * @brief  clear the screen
 * @param  para addr. & length
 * @retval True means OK
 */
static uint8_t cli_clear(int argc, char *argv[])
{
	/* This prints the clear screen and move cursor to top-left corner control
	 * characters for VT100 terminals. This means it will not work on
	 * non-VT100 compliant terminals, namely Windows' cmd.exe, but should
	 * work on anything unix-y.
	 */
	TERMINAL_RESET_CURSOR();
	TERMINAL_DISPLAY_CLEAR();

	return true;
}

/**
 * @brief  ECHO setting
 * @param  para addr. & length
 * @retval True means OK
 */
static uint8_t cli_echo(int argc, char *argv[])
{
	uint8_t ret = true;

	if (argc == 0) {

	} else if (argc == 1)	{
		if (strcmp(argv[0], "on") == 0)
			cli_echo_flag = ENABLE;
		else if (strcmp(argv[0], "off") == 0)
			cli_echo_flag = DISABLE;
		else
			ret = false;
	} else
		ret = false;

	CLI_PRINTF("Current echo = %s", cli_echo_flag ? "on" : "off");

	return ret;
}

#if CLI_HISTORY
typedef struct {
	char cmd[HISTORY_MAX][CLI_HANDLE_LEN];
	uint8_t count;
	uint8_t latest;
	uint8_t show;
} HISTORY_S;

static HISTORY_S history;

/**
 * @brief          add a history command
 * @param  buff:   command
 * @retval         null
 */
static void cli_history_add(char *buff)
{
	uint16_t len;
	uint8_t index = history.latest;

	if (buff == NULL)
		return;

	len = strlen((const char *)buff);
	/* command too long */
	if (len >= CLI_HANDLE_LEN)
		return;

	/* find the latest one */
	if (index != 0)
		index--;
	else
		index = HISTORY_MAX - 1;

	if ((memcmp(history.cmd[index], buff, len) != 0) ||
			(strlen((const char *)history.cmd[history.latest]) != len)) {
		/* if the new one is different with the latest one, the save */
		memset((void *)history.cmd[history.latest], 0x00, CLI_HANDLE_LEN);
		memcpy((void *)history.cmd[history.latest], (const void *)buff, len);
		if (history.count < HISTORY_MAX)
			history.count++;

		history.latest++;
		if (history.latest >= HISTORY_MAX)
			history.latest = 0;
	}

	history.show = 0;
}

/**
 * @brief              display history command
 * @param  mode:       TRUE for look up, FALSE for look down
 * @param  p_history:  target history command
 * @retval             TRUE for no history found, FALSE for success
 */
static uint8_t cli_history_show(uint8_t mode, char **p_history)
{
	uint8_t err = true;
	uint8_t num;
	uint8_t index;

	if (history.count == 0)
		return err;

	if (mode == true) {
		/* look up */
		if (history.show < history.count)
			history.show++;
	} else {
		/* look down */
		if (history.show > 0)
			history.show--;
	}

	num = history.show;
	index = history.latest;
	while (num) {
		if (index != 0)
			index--;
		else
			index = HISTORY_MAX - 1;

		num--;
	}

	err = false;
	*p_history = history.cmd[index];

	/* CLI_PRINTF("history: %s \r\n", history.cmd[index]); */

	return err;
}
#endif /* CLI_HISTORY */

/**
 * @brief  command line init.
 * @param  bandrate
 * @retval null
 */
void cli_init(cli_printf_ptr printf_func, cli_put_data_ptr put_data_func)
{
	uint32_t i;

	extern uintptr_t __cli_register_funcs_start, __cli_register_funcs_end;
	void (*beg)() = (void (*)())&__cli_register_funcs_start;
	void (*end)() = (void (*)())&__cli_register_funcs_end;

	void (**p)(void);

	cli_printf = printf_func;
	cli_put_data = put_data_func;

#if CLI_HISTORY
	memset((uint8_t *)&history, 0, sizeof(history));
#endif /* CLI_HISTORY */

	/* register CLI commands */
	while ((uintptr_t)beg < (uintptr_t)end) {
		p = (void(**)(void))beg;
		(*p)();
		beg += sizeof(p);
	}

	/* Sorting the CLI_Cmd array based on the command name */
	// qsort(CLI_Cmd, num_cli_cmds, sizeof(COMMAND_S), cli_cmd_cmp);

	/* init. every command */
	for (i = 0; i < sizeof(CLI_Cmd) / sizeof(COMMAND_S); i++) {
		/* need to init. or not */
		if (CLI_Cmd[i].pInit != NULL) {
			if (CLI_Cmd[i].pInit() == false) {
				/* something wrong */
				CLI_PRINTF("\r\n-> FUN[%d] INIT WRONG\r\n", i);
			}
		}
	}

#if CLI_PRINT_INIT_LOG
	CLI_PRINTF(" \r\n");

	CLI_PRINTF("-----------------------------------\r\n");
	CLI_PRINTF("    Command Line Interface         \r\n");
	CLI_PRINTF("-----------------------------------\r\n");
#endif /* CLI_PRINT_INIT_LOG */
	cli_prompt();
}

/**
 * @brief  find cli registered function
 * @param  command buffer
 * @retval 0 if failed
 */
int cli_find_function(char *handle_buf)
{
	uint8_t i;
	uint8_t handle_buf_len = 0;
	uint8_t ParaLen;
	char *ParaAddr;

	int argc;
	char *argv[MAX_INPUT_ARGUMENTS];

	uint8_t cmd_match = false;

	uint8_t history_buffer[CLI_HANDLE_LEN];

	/* looking for a match */
	for (i = 0; i < sizeof(CLI_Cmd) / sizeof(COMMAND_S); i++) {
		if (CLI_Cmd[i].pCmd == 0)
			break;
		if ((strncmp(handle_buf, (void *)CLI_Cmd[i].pCmd,
			strlen(CLI_Cmd[i].pCmd)) == 0) &&
				(((handle_buf)[strlen(CLI_Cmd[i].pCmd)] == '\0') ||
			((handle_buf)[strlen(CLI_Cmd[i].pCmd)] == ' ')))  {
			cmd_match = true;

			handle_buf_len = strlen(handle_buf);
			ParaLen = handle_buf_len - strlen(CLI_Cmd[i].pCmd);	/* para. length */
			ParaAddr = &handle_buf[strlen(CLI_Cmd[i].pCmd)];	/* para. address */

			if (CLI_Cmd[i].pFunc != NULL) {
				memset((char *)history_buffer, 0, sizeof(history_buffer));
				strncpy((char *)history_buffer, handle_buf, CLI_HANDLE_LEN - 1);

				parse_arguments(ParaAddr, ParaLen, &argc, argv);

				/* call the func. */
				if (CLI_Cmd[i].pFunc(argc, argv)) {
					CLI_PRINTF("\r\n-> FINISHED\r\n");

#if CLI_HISTORY
					cli_history_add((char *)history_buffer);
#endif  /* CLI_HISTORY */

					/* ECHO */
					if (cli_echo_flag == ENABLE) {
						handle_buf[handle_buf_len] = '\0';
						CLI_PRINTF("[echo]: %s\r\n", handle_buf);
					}
				} else {
					CLI_PRINTF("\r\n-> PARA. ERR\r\n");
					/* parameter wrong */
					CLI_PRINTF("%s", CLI_Cmd[i].pHelp);
				}
			} else {
				/* func. is void */
				CLI_PRINTF("\r\n-> FUNC. ERR\r\n");
			}
		}
	}

	/* no matching command */
	if (cmd_match == false)
		CLI_PRINTF("\r\n-> CMD ERR(%s), try: help\r\n\r\n", handle_buf);

	return cmd_match;
}

/**
 * @brief  handle commands from the terminal
 * @param  commands
 * @retval null
 */
void cli_rx_handle(uint8_t rx_data)
{
	static HANDLE_TYPE_S Handle = {.len = 0};
	uint8_t i = Handle.len;
	static char key_temp_buf[sizeof(KEY_DELETE)];
	static uint8_t key_temp_idx;
	bool esc_key_parse_end = false;

	/* ---------------------------------------
	 * Step1: save chars from the terminal
	 * ---------------------------------------
	 */
	if (Handle.len < CLI_HANDLE_LEN) {	/* check the buffer */
		/* new char coming from the terminal, copy it to Handle.buff */

		/* KEY_BACKSPACE -->get DELETE key from keyboard */
		if ((rx_data == KEY_BACKSPACE) || (rx_data == KEY_BACKSPACE2)) {
			/* buffer not empty */
			if (Handle.len > 0) {
				uint32_t copy_len;
				/* delete a char in terminal */
				TERMINAL_MOVE_LEFT(1);
				TERMINAL_CLEAR_END();
				Handle.len -= 1;
				copy_len = strlen((const char *)Handle.buff) - Handle.len;
				memcpy(&Handle.buff[Handle.len], &Handle.buff[Handle.len + 1], copy_len);
				/* to avoid assertion caused when deleting a char at the end of string */
				if (copy_len - 1 > 0) {
					/* display history command */
					CLI_PRINTF("%s", &Handle.buff[Handle.len]);
					TERMINAL_MOVE_LEFT(copy_len - 1);
				}
			}
		} else if ((rx_data == KEY_ESC) || (key_temp_idx != 0)) {
			key_temp_buf[key_temp_idx++] = rx_data;
			if (strstr(key_temp_buf, KEY_RIGHT) != 0) {
				esc_key_parse_end = true;
				if (strlen((const char *)Handle.buff) > Handle.len) {
					TERMINAL_MOVE_RIGHT(1);
					Handle.len++;
					i = Handle.len;
				}
			} else if (strstr(key_temp_buf, KEY_LEFT) != 0) {
				esc_key_parse_end = true;
				if (Handle.len) {
					TERMINAL_MOVE_LEFT(1);
					Handle.len--;
					i = Handle.len;
				}
			} else if (strstr(key_temp_buf, KEY_DELETE) != 0) {
				esc_key_parse_end = true;
				if ((strlen((const char *)Handle.buff) > 0) && (Handle.len != strlen((const char *)Handle.buff))) {
					uint32_t copy_len;
					/* delete a char in terminal */
					TERMINAL_CLEAR_LINE();
					TERMINAL_MOVE_LEFT(Handle.len + strlen(cli_prompt_buf));
					cli_prompt();
					copy_len = strlen((const char *)Handle.buff) - Handle.len;
					memcpy(&Handle.buff[Handle.len], &Handle.buff[Handle.len + 1],
						copy_len + 1);
					CLI_PRINTF("%s", Handle.buff);  /* display history command */
					if (copy_len - 1)
						TERMINAL_MOVE_LEFT(copy_len - 1);
				}
			} else if ((strstr(key_temp_buf, KEY_HOME) != 0) ||
					(strstr(key_temp_buf, KEY_HOME2) != 0) ||
					(strstr(key_temp_buf, KEY_HOME3) != 0)) {
				esc_key_parse_end = true;
				if (Handle.len)
					TERMINAL_MOVE_LEFT(Handle.len);
				Handle.len = 0;
			} else if ((strstr(key_temp_buf, KEY_END) != 0) ||
				(strstr(key_temp_buf, KEY_END2) != 0) ||
				(strstr(key_temp_buf, KEY_END3) != 0)) {
				esc_key_parse_end = true;
				if (Handle.len != strlen((const char *)Handle.buff))
					TERMINAL_MOVE_RIGHT(strlen((const char *)Handle.buff) - Handle.len);
				Handle.len = strlen((const char *)Handle.buff);
				i = Handle.len;
			} else if ((strstr(key_temp_buf, KEY_UP) != 0) ||
				(strstr(key_temp_buf, KEY_DOWN) != 0)) {
				esc_key_parse_end = true;
				memcpy(&Handle.buff[Handle.len], key_temp_buf, key_temp_idx);
				Handle.len += key_temp_idx;
			} else if (strlen(key_temp_buf) == sizeof(key_temp_buf)) {
				esc_key_parse_end = true;
				memcpy(&Handle.buff[Handle.len], key_temp_buf, key_temp_idx);
				Handle.len += key_temp_idx;
			}
			if (esc_key_parse_end) {
				memset(key_temp_buf, 0, sizeof(key_temp_buf));
				key_temp_idx = 0;
			}
		} else if (rx_data != KEY_ENTER) {
			//CLI_PRINTF("%02x ", Handle.buff[Handle.len]); /* debug */
			if (Handle.len < strlen((const char *)Handle.buff)) {
				uint32_t count = strlen((const char *)Handle.buff) - Handle.len;

				while (count--)
					Handle.buff[Handle.len + count + 1] = Handle.buff[Handle.len + count];
				Handle.buff[Handle.len++] = rx_data;
				for (; i < strlen((const char *)Handle.buff); i++)
					CLI_PUTC(Handle.buff[i]);
				TERMINAL_MOVE_LEFT(strlen((const char *)Handle.buff) - Handle.len);
			} else {
				Handle.buff[Handle.len++] = rx_data;
			}
		}

			/* all chars copied to Handle.buff */
#if CLI_HISTORY
		uint8_t key = 0;
		uint8_t err = 0xff;
		char *p_hist_cmd = 0;

		if (Handle.len > 2) {
			if (strstr((const char *)Handle.buff, KEY_UP) != 0) {
				//CLI_PRINTF("KEY_UP \r\n");
				key = 1;
				err = cli_history_show(true, &p_hist_cmd);
			} else if (strstr((const char *)Handle.buff, KEY_DOWN) != 0) {
				//CLI_PRINTF("KEY_DOWN \r\n");
				key = 2;
				err = cli_history_show(false, &p_hist_cmd);
			}

			if (key != 0) {
				TERMINAL_CLEAR_LINE();
				TERMINAL_MOVE_LEFT(Handle.len + strlen(cli_prompt_buf));
				cli_prompt();
				if (err == false && *p_hist_cmd) {
					memset(&Handle, 0x00, sizeof(Handle));
					memcpy(Handle.buff, p_hist_cmd, strlen(p_hist_cmd));
					Handle.len = strlen(p_hist_cmd);
					Handle.buff[Handle.len] = '\0';
					CLI_PRINTF("%s", Handle.buff);  /* display history command */
				} else if ((err == true) || (key != 0)) {
					/* no history found */
					memset(&Handle, 0x00, sizeof(Handle));
				}
			}
		}

		if ((key == 0) && (i < Handle.len)) {
#endif /* CLI_HISTORY */
			/* display char in terminal */
			for (; i < Handle.len; i++)
				CLI_PUTC(Handle.buff[i]);
#if CLI_HISTORY
		}
#endif /* CLI_HISTORY */
	}

	/* ---------------------------------------
	 * Step2: handle the commands
	 *  ---------------------------------------
	 */
	if ((Handle.len == 0) && (rx_data == KEY_ENTER) && (strlen((const char *)Handle.buff) == 0)) {
		/* KEY_ENTER -->ENTER key from terminal */
		Handle.len = 0;
		CLI_PRINTF("\r\n");
		cli_prompt();
	} else if (strlen((const char *)Handle.buff) > 0) {  /* check for the length of command */
		/* a command must ending with KEY_ENTER */
		if (rx_data == KEY_ENTER) {
			CLI_PRINTF("\r\n");
			Handle.len = strlen((const char *)Handle.buff);
			Handle.buff[Handle.len] = '\0';

			/* find registered cli-function */
			cli_find_function(Handle.buff);

			memset(Handle.buff, 0, sizeof(Handle.buff));
			Handle.len = 0;
			cli_prompt();
		}
	}

	if (Handle.len >= CLI_HANDLE_LEN) {
		/* full, so restart the count */
		Handle.len = 0;
		memset(Handle.buff, 0, sizeof(Handle.buff));
	}
}

/**
 * @brief  tx handle
 * @param  null
 * @retval null
 */
static void cli_tx_handle(void)
{
	/* not used for now */
}

/**
 * @brief  command line task, schedule by sys. every 50ms
 * @param  null
 * @retval null
 */
void cli_run(int data)
{
	cli_rx_handle(data);
	cli_tx_handle();
}


int cli_register(const char *cmd, const cli_init_ptr pInit,
	const cli_func_ptr pFunc, const char *help)
{
	int i;
	COMMAND_S *ptr;

#ifdef CLI_CMDS
// CLI_CMDS holds the list of CLI commands to be enabled separated by spaces.
#define __XSTR(x) __STR(x)
#define __STR(x) #x
	char enabled_cmds[] = __XSTR(CLI_CMDS);
	char *en = strtok(enabled_cmds, " ");

	while (en != NULL) {
		if (!strncmp(en, "all", 3) ||
			!strcmp(en, cmd)) {
			break;
		}
		en = strtok(NULL, " ");
	}

	if (en == NULL) {
		// CLI command DISABLED
		return 0;
	}
#endif

	for (i = 0; i < CLI_MAX_CMD_COUNT; i++) {
		ptr = (COMMAND_S *)&CLI_Cmd[i];
		if (ptr->pFunc == NULL) {
			ptr->pCmd  = cmd;
			ptr->pInit = pInit;
			ptr->pFunc = pFunc;
			ptr->pHelp = help;
			break;
		}
	}

	if (i >= CLI_MAX_CMD_COUNT) {
		CLI_PRINTF("Error : Command buffer full(%d)\r\n", CLI_MAX_CMD_COUNT);
		configASSERT(0);
		return -1;
	}

	num_cli_cmds = i + 1;

	return 0;
}
