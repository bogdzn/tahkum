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

/// this file should only be referenced in get_instructions_queue.c

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
    char keycode;
} authorized_cmd_t;

/// If you want to re-implement this on your own, please note:
/// You should first send "command" to the drone, before takeoff
/// If you don't the drone doesn't interact with you.

static authorized_cmd_t OLD_API[] = {
        { "battery?",           'b' },          /*!< to get the battery level. */
        { "streamon",           'x' },          /*!< turns stream on. */
        { "streamoff",          'v' },          /*!< turns stream off. */
        { "emergency",          'n' },          /*!< turns off motors. */
        { "cw 200",             'q' },          /*!< to rotate clockwise. */
        { "ccw 200",            'e' },          /*!< to rotate counter-clockwise. */
        { "flip f",             'o' },          /*!< to execute a flip. */
        { "flip b",             'l' },          /*!< to execute a flip. */
        { "flip l",             ';' },          /*!< to execute a flip. */
        { "flip r",             'k' },          /*!< to execute a flip. */
        { "height?",            'h' },          /*!< to get the drone's height. */
        { "land",               'm' },          /*!< to execute landing process. */
        { "up 50",              ' ' },          /*!< to move the drone. */
        { "down 50",            'z' },          /*!< to move the drone. */
        { "right 50",           'd' },          /*!< to move the drone. */
        { "left 50",            'a' },          /*!< to move the drone. */
        { "forward 50",         'w' },          /*!< to move the drone. */
        { "back 50",            's' },          /*!< to move the drone. */
        { "takeoff",            'r' },          /*!< to execute takeoff process. */
        { "time?",              't' },          /*!< get flight time. */
        { "temp?",              'y' },          /*!< get temp. */
        { NULL,                 '\0' }
};


static authorized_cmd_t NEW_API[] = {
        { "battery?",           'b' },          /*!< to get the battery level. */
        { "streamon",           'x' },          /*!< turns stream on. */
        { "streamoff",          'v' },          /*!< turns stream off. */
        { "emergency",          'n' },          /*!< turns off motors. */
        { "stop",               'f' },          /*!< hovers in the air. */
        { "cw 200",             'q' },          /*!< to rotate clockwise. */
        { "ccw 200",            'e' },          /*!< to rotate counter-clockwise. */
        { "flip f",             'o' },          /*!< to execute a flip. */
        { "flip b",             'l' },          /*!< to execute a flip. */
        { "flip l",             ';' },          /*!< to execute a flip. */
        { "flip r",             'k' },          /*!< to execute a flip. */
        { "height?",            'h' },          /*!< to get the drone's height. */
        { "land",               'm' },          /*!< to execute landing process. */
        { "up 50",              ' ' },          /*!< to move the drone. */
        { "down 50",            'z' },          /*!< to move the drone. */
        { "right 50",           'd' },          /*!< to move the drone. */
        { "left 50",            'a' },          /*!< to move the drone. */
        { "forward 50",         'w' },          /*!< to move the drone. */
        { "back 50",            's' },          /*!< to move the drone. */
        { "takeoff",            'r' },          /*!< to execute takeoff process. */
        { "time?",              't' },          /*!< get flight time. */
        { "temp?",              'y' },          /*!< get temp. */
        { NULL,                 '\0' }
};

#endif //TELLIB_AUTHORIZED_COMMANDS_H
