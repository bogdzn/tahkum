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

void exec_loop(socket_t ryze, instr_t *instructions, cmdline_settings_t settings)
{
    // this is horrendous but i will change this
    // when i will know it works.
    int timeout = 0;
    char *msg = NULL;

    do {
        do {
            send_command(ryze, instructions->command);
            msg = get_response(ryze);
            printf("Recieved:%s\n", msg);
            __log(INFO, "Recieved %s\n", msg);
            timeout++;
            sleep(settings.sleep_time);
        } while (is_drone_ok(msg) && timeout != settings.max_timeout);

        if (settings.max_timeout == timeout)
            break;
        timeout = 0;
        instructions = to_next(instructions);
    } while (instructions != NULL);
}