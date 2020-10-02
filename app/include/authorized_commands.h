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

/// authorized_commands must be ordered alphabetically
static authorized_cmd_t AUTHORIZED_COMMANDS[] = {
        { "backward", false, &always_true }, /*!< to go backwards */
        { "delay",    true,  &is_num },      /*!< to call sleep() for n seconds. */
        { "down",     false, &always_true }, /*!< to go down. */
        { "flip",     false, &is_float },    /*!< to execute a flip. */
        { "forward",  false, &always_true }, /*!< to go backward. */
        { "land",     false, &always_true }, /*!< to execute landing process. */
        { "left",     false, &is_float },    /*!< to go left. */
        { "ping",     false, &always_true},  /*!< to test connection status. */
        { "right",    false, &is_float },    /*!< to go right. */
        { "takeoff",  false, &always_true }, /*!< to execute takeoff process. */
        { "up",       false, &always_true }, /*!< to go up. */
        { NULL,        true, NULL }
};

#endif //TELLIB_AUTHORIZED_COMMANDS_H
