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

inline instr_t * to_next(instr_t *ins)
{
    return (instr_t *)ins->next;
}

inline bool instructions_are_valid(instr_t *instructions)
{
    long head = (long)instructions;

    if (!instructions || !is_same_string(instructions->command, "takeoff"))
        return false;
    for (; instructions->next != NULL; instructions = to_next(instructions));
    if (!is_same_string(instructions->command, "land"))
        return false;
    instructions = (instr_t *)head;
    return (true);
}