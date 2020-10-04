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
    settings_t settings = initial_setup(ac, av);
    socket_t ryze = create_default_socket(settings);
    instr_t *instructions = get_instructions_queue(settings.filepath);;

    if (instructions)
        exec_loop(ryze, instructions, settings);
    close_socket(ryze);
    return 0;
}
