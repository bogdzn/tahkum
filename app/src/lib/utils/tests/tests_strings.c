//
// Created by bogdan on 24/09/2020.
//

#include "./../utils.h"
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

Test(my_strlen, test_my_strlen)
{
    cr_assert_eq(my_strlen("test"), 4);
    cr_assert_eq(my_strlen((void *)0), 0);
    cr_assert_eq(my_strlen(""), 0);
    cr_assert_eq(my_strlen("fortnite\n"), 9);
}

Test(my_strdup, test_strdup)
{
    char *asd = my_strdup("asdfortnite");
    char *lol = my_strdup((void *)0);

    cr_assert_str_eq("asdfortnite", asd);
    cr_assert_eq(0, lol);
    free(asd);
}

Test(my_strcat, test_strcat)
{
    char *asd = my_strcat("this is", " a test");
    char *a = my_strcat("this is", (void *)0);
    char *s = my_strcat((void *)0, " a test");

    cr_assert_str_eq("this is a test", asd);
    cr_assert_str_eq(a, "this is");
    cr_assert_str_eq(s, " a test");
    free(asd);
    free(a);
    free(s);
}

Test(my_itoa, test_itoa)
{
    cr_assert_str_eq(my_itoa(15), "15");
    cr_assert_str_eq(my_itoa(0), "0");
    cr_assert_str_eq(my_itoa(-666), "-666");
    cr_assert_str_eq(my_itoa(-7), "-7");
}

Test(my_strncpy, strncp)
{
    char *result = malloc(sizeof(char) * 8);

    cr_assert_str_eq(my_strncpy(result, "hello world !", 5), "hello");
    cr_assert_eq(my_strncpy(result, (void *)0, 12), 0);
    cr_assert_eq(my_strncpy(result, "hello world !", -1), 0);
    free(result);
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
    char *test = my_strdup("/home/$USER/work/github/perso/teklib");
    char *test2 = (void *)0;
    char *test3 = my_strdup("no occurences !");

    cr_assert_str_eq(get_last_occurence_of(test, '/'), "teklib");
    cr_assert_str_eq(get_last_occurence_of(test3, '/'), "no occurences !");
    cr_assert_eq(get_last_occurence_of(test2, '3'), 0);
}

Test(set_to_lowercase, settolower)
{
    char *t = my_strdup("Paris Saint-Germain fucking SUCKS");
    char *d = my_strdup("LOL");
    char *f = (void *)0;

    cr_assert_str_eq(set_to_lowercase(t), "paris saint-germain fucking sucks");
    cr_assert_str_eq(set_to_lowercase(d), "lol");
    cr_assert_eq(set_to_lowercase(f), 0);
}

Test(set_to_uppercase, settoupper)
{
    char *t = my_strdup("Paris Saint-Germain fucking SUCKS");
    char *d = my_strdup("lol");
    char *f = (void *)0;

    cr_assert_str_eq(set_to_uppercase(t), "PARIS SAINT-GERMAIN FUCKING SUCKS");
    cr_assert_str_eq(set_to_uppercase(d), "LOL");
    cr_assert_eq(set_to_uppercase(f), 0);
}

Test(my_revstr, testrevstr)
{
    char *y = my_strdup("yes");
    char *f = my_strdup("fortnite");

    cr_assert_str_eq(my_revstr(y), "sey");
    cr_assert_str_eq(my_revstr(f), "etintrof");
    cr_assert_eq(my_revstr((void *)0), 0);
}

Test(strip, stripstring)
{
	char *stripped = strip(my_strdup("  lol "), ' ');
	char *not_stripped = strip(my_strdup("lol"), ' ');

	cr_assert_str_eq(stripped, "lol");
	cr_assert_str_eq(not_stripped, "lol");
}

Test(clean_line, cleanlineofspaces)
{
	char *cleaned = clean_line(my_strdup("   this     is    a      line   "));

	cr_assert_str_eq(cleaned, "this is a line");
}