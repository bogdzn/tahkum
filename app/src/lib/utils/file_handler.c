//
// Created by bogdan on 21/09/2020.
//

#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <limits.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>

#include "utils.h"

file_t get_file(char const *filepath)
{
    int fd = 0;
    file_t result = {
            .name = NULL,
            .content = NULL
    };

    if (filepath == NULL || *filepath == 0)
        return result;
    result.name = my_strdup(filepath);
    else if (stat(filepath, &result.st) == -1 || result.st_size < 1)
        return result;
    memset(&result.content, sizeof(char), result.st.st_size);
    fd = open(result.path, O_RDONLY);
    if (result.content == NULL || fd == -1 ||
    read(fd, result.content) == -1)
        return result;
    close(fd);
    return result;
}

void destroy_file(file_t file)
{
    free(file.content);
    free(file.name);
}