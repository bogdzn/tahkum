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
    cr_assert_stderr_eq_str("\033[0;33m[WARNING]: \033[mthis is a warning.\n");
}

Test(log_if_errno, ifsuccess, .init = redirect_all)
{
    log_if_errno(0, "func");
    cr_assert_stderr_eq_str("\033[0;36m[INFO]:\033[m \033[0;32msuccess for [\033[0;33mfunc\033[0;32m].\033[m\n");
}

Test(log_if_errno, iferrno, .init = redirect_all)
{
    log_if_errno(32, "function");
    cr_assert_stderr_eq_str("\033[0;31m[ERROR ON function]\033[m: Broken pipe\n");
}

Test(__log, withargs, .init = redirect_all)
{
    __log(INFO, "testing to send %i %c %s\n", 15, 2.3, 'c', "lol");
    cr_assert_stderr_eq_str("\033[0;36m[INFO]:\033[m testing to send 15 c lol\n");
}
