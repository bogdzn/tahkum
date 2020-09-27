/**
 * \file input_checking.c
 * \brief Handles all parsing related checking..
 * \author Bogdan G..
 * \version 0.1
 * \date 27/09/2020
 */

#include <stdbool.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include "./../../includes/logger.h"
#include "./../../includes/parser.h"
#include "./../lib/utils/utils.h"

inline bool always_true(__attribute__ ((unused)) char const *s)
{
    return true;
}

inline bool is_comment(char *string)
{
    return (*string == 0 || *string == '#' || *string == '\n');
}
