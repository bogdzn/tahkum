/**
 * \file get_instruction_queue.c
 * \brief Loads instructions from key listener.
 * \author Bogdan G..
 * \version 0.2
 * \date 17/10/2020
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

static char **load_drone_command(char keycode, authorized_cmd_t *commands)
{
    for (int i = 0; commands[i].command != NULL; i++) {
        if (keycode == commands[i].keycode)
            return tabgen(commands[i].command, '\t');
    }
    return tabgen("height?", '\n');
}

char **get_user_commands(char keycode, bool is_newer_api)
{
  return load_drone_command(keycode, is_newer_api ? NEW_API : OLD_API);
}
