/**
 * \file swaps.c
 * \brief handles swaps..
 * \author Bogdan G.
 * \date 21/09/2020
 */

#include "./utils.h"

/**
 * \fn void swap_array(void **one, void **two)
 * \brief tests if a string can be converted to a float.
 *
 * \param one your first array address.
 * \param two your second array address.
 */
void swap_array(void **one, void **two)
{
    void *temp = *one;

    *one = *two;
    *two = temp;
}

/// swaps 2 characters.
/**
 * \fn void swapc(char *one, char *two)
 * \brief swaps 2 characters.
 *
 * \param one your first char address.
 * \param two your second char address.
 */
void swapc(char *one, char *two)
{
    char tmp = *two;

    *two = *one;
    *one = tmp;
}

/**
 * \fn void swap(int *one, int *two)
 * \brief swaps 2 ints.
 *
 * \param one your first int address.
 * \param two your second int address.
 */
void swap(int *one, int *two)
{
    int temp = *two;

    *two = *one;
    *one = temp;
}