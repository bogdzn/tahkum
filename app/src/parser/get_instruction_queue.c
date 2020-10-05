/**
 * \file get_instruction_queue.c
 * \brief Loads instructions from file.
 * \author Adina C.
 * \version 0.1
 * \date 25/09/2020
 */

#include <stdio.h>
#include <stdlib.h>
#include "logger.h"
#include "api_commands.h"
#include <stdbool.h>
#include <errno.h>

static char **extract_from_file(char const *filename)
{
    file_t file = get_file(filename);

    if (file.content == NULL) {
        __log(ERROR, "Could not read the file %s.\n", filename);
        return NULL;
    } else return tabgen(file.content, '\n');
}

static bool is_command(char *cmd)
{
    char **words = tabgen(cmd, ' ');

    for (int i = 0; API_COMMANDS[i].command != NULL; i++)
        if (is_same_string(words[0], API_COMMANDS[i].command))
            return true;
    return false;
}

char **get_instructions_queue(char *filename)
{
    char **extracted = extract_from_file(filename);
    char **result = NULL;

    for (int i = 0; extracted[i] != NULL; i++) {
        if (extracted[i][0] == 0)
            continue;
        else if (is_command(extracted[i]))
            result = append_line_to_tab(result, extracted[i]);
    }
    return result;
}
