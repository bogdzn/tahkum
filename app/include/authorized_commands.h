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
    check_t input_check;
} authorized_cmd_t;

/// If you want to re-implement this on your own, please note:
/// You should first send "command" to the drone, before takeoff
/// If you don't the drone doesn't interact with you.

/// authorized_commands must be ordered alphabetically
//static authorized_cmd_t AUTHORIZED_COMMANDS[] = {
//        { "backward", &always_true },   /*!< to go backwards */
//        { "battery?", &always_true },   /*!< to get the battery level. */
//        { "cw",       &is_num },        /*!< to rotate clockwise. */
//        { "ccw",      &is_num },        /*!< to rotate counter-clockwise. */
//        { "delay",    &is_num },        /*!< to call sleep() for n seconds. */
//        { "flip",     &is_float },      /*!< to execute a flip. */
//        { "height?",  &always_true },   /*!< to get the drone's height. */
//        { "land",     &always_true },   /*!< to execute landing process. */
//        { "move",     &is_legal_move }, /*!< to move the drone. */
 //       { "takeoff",  &always_true },   /*!< to execute takeoff process. */
//        { "time?",    &always_true },   /*!< get flight time. */
//        { NULL,       NULL }
//};

#endif //TELLIB_AUTHORIZED_COMMANDS_H
