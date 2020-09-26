//
// Created by bogdan on 26/09/2020.
//

#ifndef LOGGER_H
#define LOGGER_H

#include "./../src/lib/utils/utils.h"
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

// path where the log file is stored.
char const *LOG_PATH = "/var/log/tello.log";

// Macro opening the log file, with O_APPEND flag set.
#ifndef OPEN_LOGFILE
#define OPEN_LOGFILE (open(LOG_PATH, \
        O_NDELAY | O_CREAT | O_APPEND, O_RDWR, \
        S_IRUSR | S_IRGRP | S_IROTH))
#endif

// macro for truncating the log file.
#ifndef CREATE_LOGFILE
#define CREATE_LOGFILE (open(LOG_PATH, \
        O_NDELAY | O_CREAT | O_TRUNC, O_RDWR, \
        S_IRUSR | S_IRGRP | S_IROTH))
#endif

// enum defining the type of log we want to print.
typedef enum LOG_TYPE = {
    INFO, WARNING, ERROR
};

// CREATE_LOGFILE.C

// creates the log file in /var/log/tello.log. Returns 0 if successful.
int create_logfile(void);

/*
 * appends a specific message stored in /var/log/tello.log.
 * You will need to specify wether the LOG_TYPE (INFO, WARNING, ERROR),
 * and then you can just use it as a printf.
 */
void log(LOG_TYPE, char *string, ...);


// Tests if logfile is present. For debug purposes.
bool logfile_exists(void);

/*
 * Sends a log to /var/log/tello.log, if errno is different that 2 or 0.
*/
void log_if_errno(int errno, char *function_name);

#endif