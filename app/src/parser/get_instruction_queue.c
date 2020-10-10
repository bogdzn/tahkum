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

char **get_user_commands(char extracted, int status)
{
    char **cmds = tabgen("height?", ' ');

    if (status == -1)
        return cmds;
    for (int i = 0; API_COMMANDS[i].command != NULL; i++) {
        if (API_COMMANDS[i].code == extracted) {
            return tabgen(API_COMMANDS->command, ' ');
        }
    }
    return cmds;
}
