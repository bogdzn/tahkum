//
// Created by bogdan on 26/09/2020.
//

#ifndef LOGGER_H
#define LOGGER_H

#include "./../src/lib/utils/utils.h"
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

char const *LOG_PATH = "/var/log/tello.log";

#ifndef OPEN_LOGFILE
#define OPEN_LOGFILE (open(LOG_PATH, \
        O_NDELAY | O_CREAT | O_APPEND, O_RDWR, \
        S_IRUSR | S_IRGRP | S_IROTH))
#endif

#ifndef CREATE_LOGFILE
#define CREATE_LOGFILE (open(LOG_PATH, \
        O_NDELAY | O_CREAT | O_TRUNC, O_RDWR, \
        S_IRUSR | S_IRGRP | S_IROTH))
#endif

typedef enum LOG_TYPE = {
    INFO, WARNING, ERROR
};

// create_logfile.c
int create_logfile(void);

void log(LOG_TYPE, char *string, ...);

bool logfile_exists(void);

void log_if_errno(int errno, char *function_name);

#endif