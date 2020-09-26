#include <stdio.h>
#include <stdlib.h>
#include "parser.h"
#include "../lib/utils.h"
#include <stdbool.h>

instr_t *init_instr(void)
{
    instr_t *instr = malloc(sizeof(instr_t));

    instr->next = NULL;
    instr->id = 0;
    instr->params = NULL;
    return instr;
}

instr_t *fill_instruction(char *instr)
{
    char *end_ptr = NULL;
    instr_t *instr = malloc(sizeof(instr_t));
    char **parsed_instr = tabgen(instr, ' ');
    int id = get_instr_id(parsed_instr[0]);

    instr->id = id;
    if (USER_CMD[id].nb_param != 0)
        instr->params = strtof(parsed_instr[1], &end_ptr); // we considere there is only one parameter
    else instr->params = NULL;
    instr->next = NULL;
    free_array(parsed_instr);
    return instr;
}

instr_t *get_instructions_queue(char *filename)
{
    instr_t *instr = init_instr();
    long head = (long)instr;
    input_file_t = parse(filename);

    for (int i = 0; ipt.instructions[i] != NULL; i++, instr = instr->next)
        instr->next = fill_instruction(ipt.instructions[i]);
    return (instr_t *)head;
}