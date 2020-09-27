/**
 * \file get_instruction_queue.c
 * \brief Loads instructions from file.
 * \author Adina C.
 * \version 0.1
 * \date 25/09/2020
 */

#include <stdio.h>
#include <stdlib.h>
#include "./../../includes/logger.h"
#include "./../../includes/authorized_commands.h"
#include <stdbool.h>
#include <errno.h>

static instr_t *init_instr(void)
{
    instr_t *instr = malloc(sizeof(instr_t));

    if (instr == NULL) {
        __log(ERROR,
              "memory allocation failed for init_instr().\n");
        return NULL;
    }
    instr->next =NULL;
    instr->command = NULL;
    instr->params = NULL;
    return instr;
}

static instr_t *load_command(char **split)
{
    instr_t *result = init_instr();
    int tablen = my_tablen((char const **)split);

    for (int i = 0; AUTHORIZED_COMMANDS[i].command != NULL; i++) {
        if (is_same_string(AUTHORIZED_COMMANDS[i].command, split[0])) {
            result->command = my_strdup(split[0]);
            result->params = (tablen != 1) ? my_strdup(split[1]) : NULL;
            result->input_check = AUTHORIZED_COMMANDS[i].input_check;
            break;
        }
    }
    log_if_errno(errno, "load command");
    return result;
}

static instr_t *fill_instruction(char *instruction)
{
    char **split_instructions = NULL;
    instr_t *instr = NULL;

    if (is_comment(instruction))
        return free(instr), NULL;
    split_instructions = tabgen(instruction, ' ');
    log_if_errno(errno, "fill instructions");
    instr = load_command(split_instructions);
    free_array((void **)split_instructions);
    return instr->input_check(instr->params) ? instr : NULL;
}

static char **extract_from_file(char const *filename)
{
    file_t file = get_file(filename);

    if (file.content == NULL) {
        __log(ERROR, "Could not read the file %s.\n", filename);
        return NULL;
    } else return tabgen(file.content, '\n');
}

instr_t *get_instructions_queue(char *filename)
{
    instr_t *instr = init_instr();
    long head = (long)instr;
    char **instructions = extract_from_file(filename);
    int i = 0;

    if (instructions == NULL)
        return NULL;
    do {
        instr = fill_instruction(instructions[i]);
        if (instr != NULL)
            instr = (instr_t *)instr->next;
        i++;
    } while (instructions[i] != NULL);
    log_if_errno(errno, "get_instructions_queue");
    return (instr_t *)head;
}