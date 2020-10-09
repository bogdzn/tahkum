/**
 * \file parser.h
 * \brief Handles initial parsing.
 * \author Adina C.
 * \version 0.1
 * \date 02/10/2020
 */

#ifndef PARSER_H
#define PARSER_H

#include <stdbool.h>
#include "utils.h"
#include <getopt.h>

/**
 * \typedef bool (*check_t)(char const *);
 * \brief function pointer containing input check.
 *
 * Returns true if correct, false if not. (duh)
 */
typedef bool (*check_t)(char const *);

/**
 * \struct input_s settings_t;
 * \brief user-defined settings
 *
 * \param max_timeout defines the number of the time a command will be retied if it fails.
 * \param sleep_time defines the amout of time we wait before sending another command.
 * \param fake_socket allows program to pretend it sends information to a drone.
 * \param filepath path of the file full of commands.
 */
typedef struct input_s settings_t;
struct input_s {
    int max_timeout;
    unsigned int sleep_time;
    bool fake_socket;
    char *filepath;
};

// initial_setup.c

/**
 * \fn settings_t initial_setup(int ac, char **av)
 * \brief sets up logfile, and parses arguments
 *
 * \param ac argument count
 * \param av arguments
 * \return a structure containing user-specified settings.
 */
settings_t initial_setup(int ac, char **av);

/**
 * \fn void display_usage(char const *bin_name)
 * \brief displays program usage
 *
 * \param bin_name binary's name
 */
void display_usage(char const *bin_name);


// get_instr_queue.c

/**
 * \fn instr_t *get_instructions_queue(char *filename)
 * \brief loads instructions in memory.
 *
 * \param filename the path of the file you want to load.
 * \return your commands.
 */
char **get_instructions_queue(char *filename);

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
 * \fn bool is_comment(char *string)
 * \brief checks if a line read from the file is a comment.
 *  this function also returns true if the string you sent is empty of NULL.
 *
 * \param string the string you want to test.
 * \return a boolean, depending on if it's a comment or not.
 */
bool is_comment(char *string);

#endif
