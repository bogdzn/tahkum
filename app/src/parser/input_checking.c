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
#include "logger.h"
#include "parser.h"
#include "utils.h"

inline bool always_true(__attribute__ ((unused)) char const *s)
{
    return true;
}

inline bool is_comment(char *string)
{
    return (!string || *string == 0 || !is_a_letter(*string, true) ||
    *string == '#' || *string == '\n' || *string == '\'');
}
