/**
 * \file file_handler.c
 * \brief Handles files.
 * \author Bogdan G.
 * \date 21/09/2020
 */

#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <limits.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include "parser.h"
#include "utils.h"

file_t get_file(char const *filepath)
{
    int size = 0;
    int fd = 0;
    file_t result = {
            .name = NULL,
            .content = NULL
    };

    if (filepath == NULL || *filepath == 0)
        return result;
    if (stat(filepath, &result.st) == -1 || result.st.st_size < 1)
        return result;
    result.name = get_last_occurence_of((char *) filepath, '/');
    result.content = malloc(sizeof(char) * (result.st.st_size + 1));
    fd = open(filepath, O_RDONLY);
    if (result.content == NULL || fd == -1 ||
            (size = read(fd, result.content, result.st.st_size)) == -1)
        return result;
    result.content[size] = 0;
    close(fd);
    return result;
}

void destroy_file(file_t file)
{
    free(file.content);
    free(file.name);
}
