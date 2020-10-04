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
    char **msg_tab = NULL;

    send_command(ryze, "command", settings);
    if (!is_same_string(get_response(ryze, settings), "ok"))
        return;
    for (int i = 0; ins[i] != NULL; i++) {
        for (int timeout = 0; timeout != settings.max_timeout; timeout++) {
            send_command(ryze, ins[i], settings);
            msg = get_response(ryze, settings);
            msg_tab = tabgen(msg, ' ');
            sleep(settings.sleep_time);
            if (!is_same_string("error", set_to_lowercase(msg_tab[0])))
                break;
        }
        //sleep(settings.sleep_time);
    }
    free(msg);
    free_array((void **)ins);
}