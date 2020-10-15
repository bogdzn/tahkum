/**
 * \file main.c
 * \brief main file of the project.
 * \author Bogdan G.
 * \date 27/09/2020
 */

#include "utils.h"
#include "parser.h"
#include <string.h>
#include <stdio.h>
#include "exec.h"

int main(int ac, char **av)
{
    settings_t settings = initial_setup(ac, av);
    socket_t ryze = create_default_socket(settings);
    int status = loop_wrapper(ryze, settings);

    close_socket(ryze, settings);
    return status;
}
