/**
 * \file exec_loop.c
 * \brief handles command execution.
 * \author Bogdan G.
 * \version 0.1
 * \date 02/10/2020
 */

#include "utils.h"
#include "logger.h"
#include "socket.h"
#include "parser.h"

void exec_loop(socket_t ryze, char **ins, settings_t settings)
{
    char *msg = NULL;

    send_command(ryze, "command", settings);
    for (int i = 0; ins[i] != NULL; i++) {
        for (int timeout = 0; timeout != settings.max_timeout; timeout++) {
            send_command(ryze, ins[i], settings);
            usleep(10000 * settings.sleep_time);
            msg = get_response(ryze, settings);
            if (!is_same_string(msg, "KO"))
                break;
        }
        usleep(10000 * settings.sleep_time);
    }
    free(msg);
    free_array((void **)ins);
}