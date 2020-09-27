/**
 * \file create_logfile.c
 * \brief Handles logifle creation and updating.
 * \author Bogdan G.
 * \date 26/09/2020
 */

#include "logger.h"
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <fcntl.h>
#include <errno.h>
#include "../lib/utils/utils.h"

bool logfile_exists(void)
{
    int fd = open(LOG_PATH, O_RDWR);
    bool result = (fd != -1);

    close(fd);
    return result;
}

int create_logfile(void)
{
    int fd = CREATE_LOGFILE;
    close(fd);
    return (fd == -1) ? 0 : 1;
}
