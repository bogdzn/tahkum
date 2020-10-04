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

static char *get_cmd(instr_t *ins)
{
    return (!ins) ? NULL : my_strcat(my_strcat(ins->command, " "), ins->params);
}

void exec_loop(socket_t ryze, instr_t *ins, settings_t settings)
{
    char *msg = NULL;

    send_command(ryze, "command", settings);
    while (ins != NULL) {
        for (int timeout = 0; timeout != settings.max_timeout; timeout++) {
            send_command(ryze, get_cmd(ins), settings);
            usleep(10000 * settings.sleep_time);
            msg = get_response(ryze, settings);
            if (is_drone_ok(msg))
                break;
        }
        usleep(10000 * settings.sleep_time);
        ins = to_next(ins);
    }
    free(msg);
    // todo destroy instructions here
}