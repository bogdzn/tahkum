/**
 * \file swaps.c
 * \brief handles swaps..
 * \author Bogdan G.
 * \date 21/09/2020
 */

#include "./utils.h"

void swap_array(void **one, void **two)
{
    void *temp = *one;

    *one = *two;
    *two = temp;
}

void swapc(char *one, char *two)
{
    char tmp = *two;

    *two = *one;
    *one = tmp;
}

void swap(int *one, int *two)
{
    int temp = *two;

    *two = *one;
    *one = temp;
}