//
// Created by bogdan on 24/09/2020.
//

#include <unistd.h>
#include "utils.h"
#include <criterion/criterion.h>
#include <criterion/redirect.h>

void redirect_all(void);

void my_putchar(char c)
{
    if (!write(1, &c, 1))
        return;
}

Test(swap, testswap, .init = redirect_all)
{
    int asd = 15;
    int lol = 13;

    swap(&asd, &lol);
    cr_assert_eq(lol, 15);
    cr_assert_eq(asd, 13);
}

Test(swap_array, testswaparray)
{
    char *asd = my_strdup("asd");
    char *lol = my_strdup("lol");

    swap_array((void **)&asd, (void **)&lol);
    cr_assert_str_eq(asd, "lol");
    cr_assert_str_eq(lol, "asd");
    free(asd);
    free(lol);
}

Test(swapc, swapchar, .init = redirect_all)
{
    char a = 'a';
    char b = 'b';

    swapc(&a, &b);
    my_putchar(a);
    my_putchar(b);
    cr_assert_stdout_eq_str("ba");
}
