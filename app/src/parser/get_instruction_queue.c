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
#include "authorized_commands.h"
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

char **get_instructions_queue(char *filename)
{
    return extract_from_file(filename);
}
