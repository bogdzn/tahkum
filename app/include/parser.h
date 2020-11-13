/**
 * \file parser.h
 * \brief Handles initial parsing.
 * \author Bogdan G.
 * \version 0.1
 * \date 17/10/2020
 */

#ifndef PARSER_H
#define PARSER_H

#include <linux/input.h>
#include <stdbool.h>
#include "utils.h"
#include <getopt.h>


#ifndef DEFAULT_WAIT_TIME
#define DEFAULT_WAIT_TIME (1)
#endif

#ifndef DEFAULT_MAX_RETRIES
#define DEFAULT_MAX_RETRIES (3)
#endif

/**
 * \typedef bool (*check_t)(char const *);
 * \brief function pointer containing input check.
 *
 * Returns true if correct, false if not. (duh)
 */
typedef bool (*check_t)(char const *);


/**
 * \typedef struct input_s settings_t
 * \brief user-defined settings
 *
 * \param max_retries defines the number of the time a command will be retied if it fails.
 * \param wait defines the amout of time we wait before sending another command.
 * \param fake_socket allows program to pretend it sends information to a drone.
 * \param filepath path of the file full of commands.
 * \param is_newer_api specifies firmware API version
 */
typedef struct input_s settings_t;
struct input_s {
    int max_retries;
    int wait;
    bool fake_socket;
    char *filepath;
    bool is_newer_api;
};


/**
 * \typedef struct file_s file_t
 * \brief Object handling files.
 *
 * Contains its name, stats and content.
 */
typedef struct file_s
{
    char *name;
    char *content;
    struct stat st;
} file_t;

/**
 * \fn file_t get_file(char const *filepath)
 * \brief loads file information into memory.
 *
 * \param filepath path of the file you want to read.
 * \return filled file_t structure.
 */
file_t get_file(char const *filepath);

/**
 * \fn void destroy_file(file_t file)
 * \brief destroys file_t structure.
 *
 * \param file structure you want to erase.
 */
void destroy_file(file_t file);



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


// get_instruction_queue.c
/**
 * \fn char **get_user_commands(char extracted, int status);
 * \brief interprets the user input we extracted from key_listener.c
 *
 * \param extracted extracted letter
 * \param is_newer_api specifies which API is compatible.
 * \return an array of instructions to execute.
 */
char **get_user_commands(char extracted, bool is_newer_api);

#endif
