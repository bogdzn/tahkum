/**
 * \file initial_setup.c
 * \brief Loads user settings and log file.
 * \author Bogdan G.
 * \version 0.1
 * \date 02/10/2020
 */

#include "utils.h"
#include "logger.h"
#include "socket.h"
#include "parser.h"
#include <getopt.h>
#include <unistd.h>
#include <stdlib.h>

static struct option long_options[] = {
        {"max_timeout", required_argument,  0,  'a'},
        {"sleep_time",  required_argument,  0,  's'},
        {"help",        no_argument,        0,  'h'},
        {"file",        required_argument,  0,  'f'},
        {NULL,          no_argument,        0,  '\0'}
};

static void setup_logfile(int ac, char **av)
{
    if (ac == 1) {
        my_puterr(av[0]);
        my_puterr(": Error -- you have to specify a file.\n");
        _exit(1);
    } else if (create_logfile() != 0) {
        my_puterr("Unexpected error while creating logfile, exiting...\n");
        _exit(1);
    } else __log(INFO, "Successfully created log file.\n");
}

static cmdline_settings_t switchcase(char *arg, char flag, cmdline_settings_t data, int ind)
{
    switch (flag) {
        case '?':
            __log(ERROR, "triggered error -- argv[%i]:%s\n", ind, arg);
            _exit(1);
        case 'f':
            __log(INFO, "setting filepath to [%s]\n", arg);
            data.filepath = my_strdup(optarg);
            break;
        case 'a':
            __log(INFO, "setting max_timeout to [%s]\n", arg);
            data.max_timeout = atoi(arg);
            break;
        case 's':
            __log(INFO, "setting sleep_time to [%s]\n", arg);
            data.sleep_time = atoi(arg);
            break;
        case 'h':
            display_usage("tahkum");
            _exit(0);
        default:
            break;
    }
    return data;
}

cmdline_settings_t initial_setup(int ac, char **av)
{
    int opt_idx = 0;
    char opt_flag = 0;
    cmdline_settings_t data = {
            .max_timeout = 10,
            .sleep_time = 1,
            .filepath = (ac == 2) ? my_strdup(av[1]) : NULL
    };

    setup_logfile(ac, av);
    if (ac == 2)
        return data;
    while ((opt_flag = getopt_long(ac, av, "a:s:hf:",long_options, &opt_idx)) != -1)
        switchcase(optarg, opt_flag, data, optind);
    if (data.filepath == NULL) {
        my_puterr(av[0]);
        my_puterr(": Error -- filepath not specified.\n");
        exit(1);
    }
    return data;
}

void display_usage(char const *bin_name)
{
    my_puterr(bin_name);
    my_puterr(":\n\t-a\tsets max timeout.\n\t-s\tsets sleep time between calls to drone.\n");
    my_puterr("\t-h\tprints this message.\n\t-f\tspecifies the file with the commands.\n");
}