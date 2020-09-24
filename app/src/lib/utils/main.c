#include "utils.h"
#include <stdio.h>

int main(int ac, char **av)
{
    if (ac != 2) return 0;


    file_t example = get_file(av[1]);

    printf("for %s, we have:\n%s\n", example.name, example.content);

    return 0;
}
