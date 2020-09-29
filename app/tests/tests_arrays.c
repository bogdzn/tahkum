//
// Created by bogdan on 23/09/2020.
//

#include "utils.h"
#include <criterion/criterion.h>
#include <criterion/redirect.h>

void redirect_all(void)
{
	cr_redirect_stdout();
	cr_redirect_stderr();
}

Test(tabgen, tbgn)
{
	char **tab = tabgen((void *) 0, '\n');
	char **tab2 = tabgen("lol i love this game", ' ');

	cr_assert_eq(tab,0);
	cr_assert_str_eq(tab2[0],"lol");
	free_array((void **)tab2);
}

Test(display_tab, test_display_tab, .init = redirect_all)
{
	char **test = tabgen("this is a tab.\n", ' ');

	display_tab((char const **)test);
	cr_assert_stdout_eq_str("thisisatab.\n");
	free_array((void **)test);
}

Test(free_array, test_free_tab)
{
	char **tab = tabgen("i love being alive", ' ');
	int **inttab = malloc(sizeof(int *) * 3);
	char **lol = (void *) 0;

	inttab[0] = malloc(sizeof(int) * 2);
	inttab[0][0] = 1;
	inttab[0][1] = 15;
	inttab[1] = malloc(sizeof(int) * 1);
	inttab[1][0] = 17;
	inttab[2] = (void *)0;
	free_array((void **)tab);
	free_array((void **)inttab);
	free_array((void **)lol);
}

Test(append_line_to_tab, appendline)
{
	char **example = tabgen("this is an example", ' ');
	char *line = my_strdup("appended");

	char **normal_case = append_line_to_tab(example, line);
	cr_assert_eq(my_tablen((char const **)normal_case), 5);

	char **line_empty = append_line_to_tab(example, NULL);
	cr_assert_eq(my_tablen((char const **)line_empty), 4);

	char **tab_empty = append_line_to_tab(NULL, line);
	cr_assert_eq(my_tablen((char const **)tab_empty), 1);

	char **both_null = append_line_to_tab(NULL, NULL);
	cr_assert_eq(both_null, 0);

}
