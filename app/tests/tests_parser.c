#include <stdio.h>
#include <stdlib.h>
#include "parser.h"
#include "utils.h"
#include <stdbool.h>
#include <criterion/criterion.h>

Test(is_comment, iscomment)
{
    cr_assert_eq(is_comment("# whatever"), true);
    cr_assert_eq(is_comment("\n"), true);
    cr_assert_eq(is_comment("takeoff"), false);
    cr_assert_eq(is_comment(""), true);
    cr_assert_eq(is_comment(NULL), true);
    cr_assert_eq(is_comment("// comment"), true);
    cr_assert_eq(is_comment("''' Python style comment"), true);
    cr_assert_eq(is_comment("123"), true);
}

Test(always_true, trueXD)
{
    cr_assert_eq(always_true("asd"), true);
}

Test(get_instructions_queue, check_if_loading_something)
{
    char **instruc = get_instructions_queue("./tests/.tests_files/valid");

    cr_assert_str_eq(instruc[0], "takeoff");
    cr_assert_str_eq(instruc[1], "battery?");
    cr_assert_str_eq(instruc[2], "time?");
    cr_assert_str_eq(instruc[3], "land");
}

Test(initial_setup, basicparser)
{
    int ac = 2;
    char **av = tabgen("tahkum file", ' ');
    settings_t settings = initial_setup(ac, av);

    cr_assert_eq(settings.max_timeout, 10);
    cr_assert_eq(settings.sleep_time, 2);
    cr_assert_eq(settings.fake_socket, false);
    cr_assert_str_eq(settings.filepath, "file");
}

Test(initial_setup, oneoption)
{
    int ac = 6;
    char **av = tabgen("tahkum --file filename -d --sleep_time 5", ' ');
    settings_t settings = initial_setup(ac, av);

    cr_assert_eq(settings.max_timeout, 10);
    cr_assert_eq(settings.sleep_time, 5);
    cr_assert_eq(settings.fake_socket, true);
    cr_assert_str_eq(settings.filepath, "filename");
}
