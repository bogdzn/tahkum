/**
 * \file authorized_commands.h
 * \brief a static char ** holding all the commands handled by the Ryze Tello..
 * \author Bogdan G.
 * \version 0.1
 * \date 27/09/2020
 */

#ifndef TELLIB_AUTHORIZED_COMMANDS_H
#define TELLIB_AUTHORIZED_COMMANDS_H

#include <unistd.h>
#include <stdbool.h>
#include "parser.h"
#include "utils.h"

/**
 * \struct authorized_t
 * \brief a function authorized by the API.
 *
 * \param command the command you want to send to your drone
 * \param is_local a boolean explaining if the command should be executed locally.
 * \param input_check a function pointer checking if the arguments are valid.
 */
typedef struct authorized_s
{
    char *command;
    bool is_local;
    check_t input_check;
} authorized_cmd_t;

static authorized_cmd_t AUTHORIZED_COMMANDS[] = {
        { "start",   true,  &always_true },
        { "stop",    true,  &always_true },
        { "takeoff", false, &always_true },
        { "land",    false, &always_true },
        { "flip",    false, &is_float },
        { "turn",    false, &is_float },
        { "up",      false, &always_true },
        { "down",    false, &always_true },
        { "delay",   true,  &is_num },
        { NULL,      true,  NULL }
};

#endif //TELLIB_AUTHORIZED_COMMANDS_H
