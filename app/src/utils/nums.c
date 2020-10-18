/**
 * \file nums.c
 * \brief Handles nums.
 * \author Bogdan G.
 * \date 21/09/2020
 */

#include <string.h>
#include <stdio.h>
#include "utils.h"
#include <stdlib.h>

typedef int(*ptr)(int, int);

static int mod(int nb1, int nb2)
{
    return nb1 % nb2;
}

static int _div(int nb1, int nb2)
{
    return nb1 / nb2;
}

static int mult(int nb1, int nb2)
{
    return nb1 * nb2;
}

static int sub(int nb1, int nb2)
{
    return nb1 - nb2;
}

static int add(int nb1, int nb2)
{
    return nb1 + nb2;
}

int do_op(int first, int second, char flag)
{
    ptr functions[] = { &sub, &mult, &_div, &mod, &add, (void *) 0 };
    char signs[] = { '-', '*', '/', '%', '+', '\0' };

    for (int i = 0; signs[i] != '\0'; i++)
        if (flag == signs[i])
            return (functions[i](first, second));
    return (0);
}

int my_nblen(int nb)
{
    int result = 0;

    nb = nb < 0 ? nb * -1 : nb;
    if (nb == 0)
        return (0);
    for (; nb > 0; nb = nb / 10)
        result++;
    return (result);
}

static void my_putchar(char c)
{
    if (!write(1, &c, 1))
        return;
}

void my_putnbr(int nb)
{
    if (nb < 0) {
        my_putchar('-');
        nb = nb * -1;
    }
    if (nb >= 0) {
        if (nb >= 10) {
            my_putnbr(nb / 10);
            my_putchar(nb % 10 + 48);
        } else my_putchar(nb + 48);
    }
}

static int get_length_of_new_base(int nb, int base_len)
{
    int result = 0;

    nb = nb < 0 ? nb * -1 : nb;
    if (base_len == 0)
        return (0);
    for (; nb > 0; result++)
        nb = nb / base_len;
    return (result);
}

char *my_getnbr_base(int nb, const char *base_to)
{
    char *result = (void *) 0;
    bool is_negative = nb < 0 ? true : false;
    int nb_len = 0;
    int base_len = 0;
    int ctr = 0;

    if (base_to == (void *) 0 || base_to[0] == '\0')
        return ((void *) 0);
    else if (nb == 0)
        return (strdup("0"));

    base_len = strlen(base_to);
    nb_len = get_length_of_new_base(nb, strlen(base_to));
    ctr = nb_len - 1;

    nb = nb < 0 ? nb * -1 : nb;
    result = malloc(sizeof(char) * (nb_len + 1));

    for (int tmp = 0; ctr >= 0; ctr--) {
        tmp = nb % base_len;
        result[ctr] = base_to[tmp];
        nb = nb / base_len;
    }
    result[nb_len] = '\0';

    return (is_negative == true ? concat_str("-", result) : result);
}

void my_putnbr_base(int nb, const char *base)
{
    char *converted_nb = my_getnbr_base(nb, base);

    if (converted_nb != (void *) 0)
        my_putstr(converted_nb);
}
