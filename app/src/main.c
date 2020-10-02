/**
 * \file main.c
 * \brief main file of the project.
 * \author Bogdan G.
 * \date 27/09/2020
 */

#include "utils.h"
#include "logger.h"
#include "socket.h"
#include "parser.h"

int main(int ac, char **av)
{
    socket_t ryze;
    instr_t *instructions = NULL;
    char *msg = NULL;
    cmdline_settings_t settings = initial_setup(ac, av);

    instructions = get_instructions_queue(settings.filepath);
    ryze = create_default_socket();
    if (!is_socket_ok(ryze) || !instructions_are_valid(instructions))
        return 1;

    // this is horrendous but i will change this
    // when i will know it works.
    int timeout = 0;

    do {
        do {
            send_command(ryze, instructions->command);
            msg = get_response(ryze);
            printf("Recieved:%s\n", msg);
            __log(INFO, "Recieved %s\n", msg);
            timeout++;
            sleep(settings.sleep_time);
        } while (is_drone_ok(msg) && timeout != settings.max_timeout);

        timeout = 0;
        instructions = to_next(instructions);
    } while (instructions != NULL);

    close_socket(ryze);
    return 0;
}
