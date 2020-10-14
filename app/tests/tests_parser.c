#include <stdio.h>
#include <stdlib.h>
#include "parser.h"
#include "utils.h"
#include <stdbool.h>
#include <criterion/criterion.h>

Test(initial_setup, basicparser)
{
    int ac = 2;
    char **av = tabgen("tahkum file", ' ');
    settings_t settings = initial_setup(ac, av);

    cr_assert_eq(settings.max_retries, 5);
    cr_assert_eq(settings.wait, 2);
    cr_assert_eq(settings.fake_socket, false);
    cr_assert_str_eq(settings.filepath, "file");
}

Test(initial_setup, oneoption)
{
    int ac = 6;
    char **av = tabgen("tahkum --file filename -d --sleep_time 5", ' ');
    settings_t settings = initial_setup(ac, av);

    cr_assert_eq(settings.max_retries, 5);
    cr_assert_eq(settings.wait, 5);
    cr_assert_eq(settings.fake_socket, true);
    cr_assert_str_eq(settings.filepath, "filename");
}

Test(get_user_commands, getusrcmd)
{
    char **first = get_user_commands('a', 0);
    char **second = get_user_commands('z', 0);
    char **third = get_user_commands(' ', 0);
    char **fourth = get_user_commands('g', 0);
    char **fifth = get_user_commands('m', 0);

    cr_assert_str_eq(*first, "left 20");
    cr_assert_str_eq(*second, "down 20");
    cr_assert_str_eq(*third, "up 20");
    cr_assert_str_eq(*fourth, "height?");
    cr_assert_str_eq(*fifth, "land");
}
