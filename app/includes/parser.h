/**
 * \file parser.h
 * \brief Handles initial parsing.
 * \author Adina C.
 * \version 0.1
 * \date 27/09/2020
 */

#ifndef PARSER_H
#define PARSER_H

#include <stdbool.h>
#include "./../src/lib/utils/utils.h"

/**
 * \brief function pointer containing input check.
 *
 * Returns true if correct, false if not. (duh)
 */
typedef bool (*check_t)(char const *);

/**
 * \struct instr_t
 * \brief Linked list holding a command.
 *
 * Contains the command, it's parameters, and if it is locally executed.
 */
typedef struct instr {
    char *command;
    char *params;
    check_t input_check;
    struct instr_s *next;
} instr_t;

// get_instr_queue.c

/**
 * \fn instr_t *get_instructions_queue(char *filename)
 * \brief loads instructions in memory.
 *
 * \param filename the path of the file you want to load.
 * \return a linked list containing your commands.
 */
instr_t *get_instructions_queue(char *filename);

// input_checking.c

/**
 * \fn bool always_true(char const *s)
 * \brief inline function always returning true.
 *
 * \param s a string.
 * \return true. (duh)
 */
bool always_true(char const *s);

/**
 * \fn bool is_comment(char *string
 * \brief checks if a line read from the file is a comment.
 *  this function also returns true if the string you sent is empty of NULL.
 *
 * \param string the string you want to test.
 * \return a boolean, depending on if it's a comment or not.
 */
bool is_comment(char *string);

#endif
