/**
 * \file get_instruction_queue.c
 * \brief Loads instructions from key listener.
 * \author Adina C.
 * \version 0.1
 * \date 10/10/2020
 */

#include <stdio.h>
#include <stdlib.h>
#include "api_commands.h"
#include "utils.h"
#include <stdbool.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <linux/kd.h>
#include <termios.h>
#include <linux/input.h>

char **get_user_commands(struct input_event *evts, int status)
{
    char **cmds = NULL;

    if (status == -1)
        return NULL;
    else if (evts == NULL)
        return tabgen("time?", '\n');
    for (int i = 0; i < (status / sizeof(struct input_event)); i++) {
        for (int j = 0; API_COMMANDS[j].command != NULL; j++) {
            cmds = (evts[i].code == API_COMMANDS[j].code)
                ? append_line_to_tab(cmds, API_COMMANDS[j].command)
                : cmds;
        }
    }
    return (cmds == NULL) ? tabgen("time?", '\n') : cmds;
}
