//
// Created by bogdan on 01/10/2020.
//

#include "parser.h"
#include "utils.h"
#include "exec.h"
#include <criterion/criterion.h>
#include <criterion/redirect.h>

void redirect_all(void);

Test(create_logfile, creating_logfile)
{
    create_logfile();
    cr_assert_eq(logfile_exists(), true);
}

Test(__log, testlog, .init = redirect_all)
{
    __log(WARNING, "this is a warning.\n");
    cr_assert_stderr_eq_str("[WARNING]: this is a warning.\n");
}

Test(log_if_errno, ifsuccess, .init = redirect_all)
{
    log_if_errno(0, "func");
    cr_assert_stderr_eq_str("[INFO]: success for [func].\n");
}

Test(log_if_errno, iferrno, .init = redirect_all)
{
    log_if_errno(32, "function");
    cr_assert_stderr_eq_str("[ERROR ON function]: Broken pipe\n");
}

Test(__log, withargs, .init = redirect_all)
{
    __log(INFO, "testing to send %i %c %s\n", 15, 2.3, 'c', "lol");
    cr_assert_stderr_eq_str("[INFO]: testing to send 15 c lol\n");
}
