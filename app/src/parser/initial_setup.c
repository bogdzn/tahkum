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
        {"max_timeout", required_argument,  0,  't'},
        {"sleep_time",  required_argument,  0,  's'},
        {"help",        no_argument,        0,  'h'},
        {"file",        required_argument,  0,  'f'},
        {"debug",       no_argument,        0,  'd'},
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

static settings_t switchcase(char *arg, char flag, settings_t data, int ind)
{
    switch (flag) {
        case '?':
            __log(ERROR, "triggered error -- argv[%i]:%s\n", ind, arg);
            _exit(1);
        case 'f':
            data.filepath = my_strdup(optarg);
            __log(INFO, "setting filepath to [%s]\n", data.filepath);
            break;
        case 'd':
            data.fake_socket = true;
            __log(INFO, "setting fake_socket to TRUE.\n");
            break;
        case 'a':
            data.max_timeout = my_getnbr(arg);
            __log(INFO, "setting max_timeout to [%i]\n", data.max_timeout);
            break;
        case 's':
            data.sleep_time = my_getnbr(arg);
            __log(INFO, "setting max_timeout to [%i]\n", data.sleep_time);
            break;
        case 'h':
            display_usage("tahkum");
            _exit(0);
        default:
            break;
    }
    return data;
}

settings_t initial_setup(int ac, char **av)
{
    int opt_idx = 0;
    char opt_flag = 0;
    settings_t data = {
            .max_timeout = 10,
            .sleep_time = 2,
            .filepath = (ac == 2) ? my_strdup(av[1]) : NULL,
            .fake_socket = false
    };

    setup_logfile(ac, av);
    if (ac == 2 && av[1][0] != '-')
        return data;
    while ((opt_flag = getopt_long(ac, av, "t:s:hf:d",long_options, &opt_idx)) != -1)
        data = switchcase(optarg, opt_flag, data, optind);
    if (data.filepath == NULL) {
        __log(ERROR, "filepath not specified.\n");
        exit(1);
    }
    return data;
}

void display_usage(char const *bin_name)
{
    my_puterr(bin_name);
    my_puterr(":\n\t-t\tsets max timeout.\n\t-s\tsets sleep time between calls to drone.\n");
    my_puterr("\t-h\tprints this message.\n\t-f\tspecifies the file with the commands.\n");
    my_puterr("\t-d\tenables debug mode, and doesn't actually interact with the drone.\n");
}