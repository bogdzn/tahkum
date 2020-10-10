/**
 * \file parser.h
 * \brief Handles initial parsing.
 * \author Adina C.
 * \version 0.1
 * \date 02/10/2020
 */

#ifndef PARSER_H
#define PARSER_H

#include <linux/input.h>
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


/**
 * \struct file_t
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


// get_instr_queue.c
/**
 * \fn char **get_user_commands(struct input_event *evts, int status);
 * \brief interprets the user input we extracted from key_listener.c
 *
 * \param evts 64 potential events.
 * \param status read return value
 * \return an array of instructions to execute.
 */
char **get_user_commands(struct input_event *evts, int status);

#endif
