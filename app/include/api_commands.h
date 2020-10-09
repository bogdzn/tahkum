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
    __u16 code;
} authorized_cmd_t;

/// If you want to re-implement this on your own, please note:
/// You should first send "command" to the drone, before takeoff
/// If you don't the drone doesn't interact with you.

/// authorized_commands must be ordered alphabetically
static authorized_cmd_t API_COMMANDS[] = {
        { "battery?",       KEY_B },          /*!< to get the battery level. */
        { "cw 90",          KEY_Q },          /*!< to rotate clockwise. */
        { "ccw 90",         KEY_E },          /*!< to rotate counter-clockwise. */
        { "delay",          KEY_X },          /*!< to call sleep() for n seconds. */
        { "flip front",     KEY_UP },         /*!< to execute a flip. */
        { "flip back",      KEY_DOWN },       /*!< to execute a flip. */
        { "flip left",      KEY_LEFT },       /*!< to execute a flip. */
        { "flip right",     KEY_RIGHT },      /*!< to execute a flip. */
        { "height?",        KEY_H },          /*!< to get the drone's height. */
        { "land",           KEY_LEFTCTRL },   /*!< to execute landing process. */
        { "move up",        KEY_SPACE},       /*!< to move the drone. */
        { "move down",      KEY_LEFTSHIFT},   /*!< to move the drone. */
        { "move right",     KEY_SPACE},       /*!< to move the drone. */
        { "move left",      KEY_SPACE},       /*!< to move the drone. */
        { "move forward",   KEY_W },          /*!< to move the drone. */
        { "move backward",  KEY_S },          /*!< to move the drone. */
        { "takeoff",        KEY_R },          /*!< to execute takeoff process. */
        { "time?",          KEY_T },          /*!< get flight time. */
        { NULL,             KEY_RESERVED }
};

#endif //TELLIB_AUTHORIZED_COMMANDS_H
