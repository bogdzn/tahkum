/**
 * \file api_commands.h
 * \brief a static char ** holding all the commands handled by the Ryze Tello..
 * \author Bogdan G.
 * \version 0.1
 * \date 05/10/2020
 */

#ifndef TELLIB_API_COMMANDS_H
#define TELLIB_API_COMMANDS_H

#include <asm-generic/int-ll64.h>
#include <linux/input-event-codes.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdbool.h>
#include "parser.h"
#include "utils.h"

/// this file should only be refecterenced in get_instructions_queue.c

/**
 * \struct authorized_t
 * \brief a function authorized by the API.
 *
 * \param command the command you want to send to your drone
 * \param code code defined in <linux/input-event-codes.h>
 */
typedef struct authorized_s
{
    char *command;
    char code;
} authorized_cmd_t;

/// If you want to re-implement this on your own, please note:
/// You should first send "command" to the drone, before takeoff
/// If you don't the drone doesn't interact with you.

static authorized_cmd_t API_COMMANDS[] = {
        { "battery?",       'b' },          /*!< to get the battery level. */
        { "cw 90",          'q' },          /*!< to rotate clockwise. */
        { "ccw 90",         'e' },          /*!< to rotate counter-clockwise. */
        { "delay 5",        'x' },          /*!< to call sleep() for n seconds. */
        { "flip front",     'o' },          /*!< to execute a flip. */
        { "flip back",      'l' },          /*!< to execute a flip. */
        { "flip left",      ';' },          /*!< to execute a flip. */
        { "flip right",     'k' },          /*!< to execute a flip. */
        { "height?",        'h' },          /*!< to get the drone's height. */
        { "land",           'm' },          /*!< to execute landing process. */
        { "move up",        ' ' },          /*!< to move the drone. */
        { "move down",      'z' },          /*!< to move the drone. */
        { "move right",     'd' },          /*!< to move the drone. */
        { "move left",      'a' },          /*!< to move the drone. */
        { "move forward",   'w' },          /*!< to move the drone. */
        { "move backward",  's' },          /*!< to move the drone. */
        { "takeoff",        'r' },          /*!< to execute takeoff process. */
        { "time?",          't' },          /*!< get flight time. */
        { NULL,             '\0' }
};

#endif //TELLIB_AUTHORIZED_COMMANDS_H
