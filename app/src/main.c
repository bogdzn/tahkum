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
#include <stdio.h>
/*
int main(int ac, char **av)
{
    settings_t settings = initial_setup(ac, av);
    socket_t ryze = create_default_socket(settings);
    char **instructions = get_instructions_queue(settings.filepath);;

    if (instructions != NULL)
        exec_loop(ryze, instructions, settings);
    close_socket(ryze, settings);
    return 0;
}
*/

int main(void)
{
    if (create_logfile() != 0)
        return 0;

    while (1) {
        char c = get_pressed_key();
       printf("Pressed key: %c\n", c);
      if (c == 'b')
         break;
    }
    return 0;
}
