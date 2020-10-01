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

static int arg_handling(int ac, char **av)
{
    if (ac != 2) {
        my_puterr(av[0]);
        my_puterr(": Error -- you have to specify an argument.\n");
        return 1;
    } else if (create_logfile() != 0) {
        my_puterr("Unexpected error while creating logfile, exiting...\n");
        return 1;
    } else __log(INFO, "Successfully created log file.\n");
    return 0;
}

int main(int ac, char **av)
{
    socket_t ryze;
    instr_t *instructions = NULL;
    char *msg = NULL;

    if (arg_handling(ac, av) != 0)
        return 1;
    instructions = get_instructions_queue(av[1]);
    ryze = create_default_socket();
    if (!is_socket_ok(ryze) || !instructions_are_valid(instructions))
        return 1;

    // todo implement while loop sending instructions and checking if result is ok
    do {
        send_command(ryze, instructions->command);
        msg = get_response(ryze);
        printf("Recieved:%s\n", msg);
        __log(INFO, "Recieved %s\n", msg);
        instructions = (instr_t*)instructions->next;
    } while (instructions != NULL);

    close_socket(ryze);
    return 0;
}
