/**
 * \file main.c
 * \brief main file of the project.
 * \author Bogdan G.
 * \date 27/09/2020
 */

#include "./lib/utils/utils.h"
#include "../includes/logger.h"

int main(int ac, char **av)
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
