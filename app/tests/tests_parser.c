#include <stdio.h>
#include <stdlib.h>
#include "./../includes/parser.h"
#include "./../src/lib/utils/utils.h"
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