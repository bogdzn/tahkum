/**
 * \file main.c
 * \brief main file of the project.
 * \author Bogdan G.
 * \date 10/10/2020
 */

#include "utils.h"
#include "parser.h"
#include <string.h>
#include <stdio.h>
#include "exec.h"
#include "ui.h"

int main(int ac, char **av)
{
    ctx_t context;

    if (init_ctx(&context, ac, av) != 0)
        return 1;

    // main loop
    destroy_ctx(context);
    return 0;
}
