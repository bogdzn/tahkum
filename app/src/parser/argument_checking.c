/**
 * \file argument_checking.c
 * \brief checks if the arguments sent by the user are valid.
 * \author Bogdan G.
 * \date 29/09/2020
 */

#include "utils.h"
#include "parser.h"
#include <stdlib.h>
#include <unistd.h>
#include "logger.h"
#include <stdbool.h>

inline bool instructions_are_valid(instr_t *instructions)
{
    long head = (long)instructions;
    int nb_takeoff = 0;
    int nb_land = 0;

    if (!instructions || !is_same_string(instructions->command, "start"))
        return false;
    do {
        instructions = (instr_t *)instructions->next;
        if (is_same_string(instructions->command, "takeoff"))
            nb_takeoff++;
        else if (is_same_string(instructions->command, "land"))
            nb_land++;
    } while (instructions->next != NULL);
    if (!is_same_string(instructions->command, "end"))
        return false;
    instructions = (instr_t *)head;
    return (nb_takeoff == nb_land);
}