//
// Created by bogdan on 24/09/2020.
//

#include "utils.h"
#include <criterion/criterion.h>
#include <criterion/redirect.h>

void redirect_all(void);

Test(my_putstr, tests_putstr, .init = redirect_all)
{
    my_putstr("this is a string.\n");
    cr_assert_stdout_eq_str("this is a string.\n");
}

Test(my_puterror, test_puterror, .init = redirect_all)
{
    my_puterr("This is a string on the error canal.\n");
    cr_assert_stderr_eq_str("This is a string on the error canal.\n");
}

Test(my_itoa, test_itoa)
{
    cr_assert_str_eq(my_itoa(15), "15");
    cr_assert_str_eq(my_itoa(0), "0");
//    cr_assert_str_eq(my_itoa(-666), "-666");
    cr_assert_str_eq(my_itoa(-7), "-7");
}

Test(is_num, testisnum)
{
    cr_assert_eq(is_num("-14"), true);
    cr_assert_eq(is_num("asd"), false);
    cr_assert_eq(is_num((void *)0), false);
    cr_assert_eq(is_num("1235"), true);
}

Test(is_in_string, testisinstring)
{
    cr_assert_eq(is_in_string("test", 's'), 2);
    cr_assert_eq(is_in_string("fortnite", 'z'), -1);
    cr_assert_eq(is_in_string((void *)0, 's'), -1);
}

Test(is_alphabetic, testisalpha)
{
    cr_assert_eq(is_alphabetic("isalphabetic"), true);
    cr_assert_eq(is_alphabetic("is not alpha"), false);
    cr_assert_eq(is_alphabetic((void *)0), false);
}

Test(is_a_letter, testisaletter)
{
    cr_assert_eq(is_a_letter('c', true), true);
    cr_assert_eq(is_a_letter('D', false), false);
    cr_assert_eq(is_a_letter('D', false), false);
    cr_assert_eq(is_a_letter('\n', false), false);
}

Test(get_last_occurence_of, testlastocc)
{
    char *test = strdup("/home/$USER/work/github/perso/teklib");
    char *test2 = (void *)0;
    char *test3 = strdup("no occurences !");

    cr_assert_str_eq(get_last_occurence_of(test, '/'), "teklib");
    cr_assert_str_eq(get_last_occurence_of(test3, '/'), "no occurences !");
    cr_assert_eq(get_last_occurence_of(test2, '3'), 0);
}

Test(strip, stripstring)
{
	char *stripped = strip(strdup("  lol "), ' ');
	char *not_stripped = strip(strdup("lol"), ' ');

	cr_assert_str_eq(stripped, "lol");
	cr_assert_str_eq(not_stripped, "lol");
}
