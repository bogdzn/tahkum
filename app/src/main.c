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
    cmdline_settings_t settings = initial_setup(ac, av);

    instructions = get_instructions_queue(settings.filepath);
    ryze = create_default_socket();

    if (!is_socket_ok(ryze) || !instructions_are_valid(instructions))
        return 1;
    exec_loop(ryze, instructions, settings);
    close_socket(ryze);
    return 0;
}
