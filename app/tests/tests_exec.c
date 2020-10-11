//
// Created by bogdan on 23/09/2020.
//

#include "utils.h"
#include "parser.h"
#include "exec.h"
#include <criterion/criterion.h>
#include <criterion/redirect.h>

settings_t set_test_settings(void);

Test(is_drone_ok, drne)
{
    cr_assert_eq(is_drone_ok(NULL), false);
}

Test(exec_loop, execloop)
{
    settings_t set = set_test_settings();
    socket_t sock;
    char **args = tabgen("time? height?", ' ');

    cr_assert_eq(exec_loop(sock, set, args), 0);
}
