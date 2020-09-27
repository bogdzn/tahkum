/**
 * \file logger.h
 * \brief Handles logifle.
 * \author Bogdan G.
 * \version 0.1
 * \date 26/09/2020
 */

#ifndef LOGGER_H
#define LOGGER_H

#include "./../src/lib/utils/utils.h"
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

/// path where the log file is stored.
#ifndef LOG_PATH
#define LOG_PATH ("/var/log/tello.log")
#endif

/// Macro opening the log file, with O_APPEND flag set.
#ifndef OPEN_LOGFILE
#define OPEN_LOGFILE (open(LOG_PATH, \
        O_NDELAY | O_CREAT | O_APPEND | O_RDWR, \
        S_IRUSR | S_IRGRP | S_IROTH))
#endif

/// macro for truncating the log file.
#ifndef CREATE_LOGFILE
#define CREATE_LOGFILE (open(LOG_PATH, \
        O_NDELAY | O_CREAT | O_TRUNC | O_RDWR, \
        S_IRUSR | S_IRGRP | S_IROTH))
#endif

/**
 * \enum LOG_TYPE
 * \brief Log messages types.
 *
 * Defines which type of log we want to write.
 */
typedef enum LOG_TYPE {
    INFO, /*!< used for misc infos. */
    WARNING, /*!< used for warnings and non-critical errors. */
    ERROR /*!< used for critical errors. */
} log_type_e;

/**
 * \fn int create_logfile(void)
 * \brief creates log file in LOG_PATH.
 *
 * \return 0 if successful, 1 if not.
 */
int create_logfile(void);

/**
 * \fn void log(LOG_TYPE, char *string, ...)
 * \brief appends a specific message stored in LOG_PATH.
 * You will need to specify wether the LOG_TYPE (INFO, WARNING, ERROR),
 * and then you can just use it as a printf.
 *
 * \param type type of log.
 * \param string complete log messages, including files, as used in printf.
 * \param ... eventual flags we want to specify.
 */
void __log(log_type_e type, char *string, ...);


/**
 * \fn bool logfile_exists(void)
 * \brief Tests if the log file has been created.
 *
 * \return boolean specifying if logfile exists.
*/
bool logfile_exists(void);

/**
 * \fn void log_if_errno(int errno, char *string, ...)
 * \brief Adds a log to LOG_PATH if errno is different than 2 or 0.
 * By default, every error triggered by this function is considered
 * a critical error.
 *
 * \param errno ERRNO constant.
 * \param function_name defining the operation you are currently doing.
 */
void log_if_errno(int errno, char *function_name);

#endif
