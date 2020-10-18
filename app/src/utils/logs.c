/**
 * \file logs.c
 * \brief Handles logifle creation and updating.
 * \author Bogdan G.
 * \date 17/10/2020
 */

#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <fcntl.h>
#include <errno.h>
#include "utils.h"
#include <stdio.h>
#include <stdarg.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

static char *switch_case(char flag, va_list ap)
{
    char *result = (void *) 0;
    int decimal, sign = 0;
    int float_max_len = 6;

    switch (flag) {
        case 'c' :
            result = append_char(result, va_arg(ap,int));
            break;
        case 'i' :
            result = my_itoa(va_arg(ap, int));
            break;
        case 's' :
            result = strdup(va_arg(ap,char *));
            break;
        case 'f':
            result = fcvt(va_arg(ap, double), float_max_len, &decimal, &sign);
            break;
        default :
            result = append_char(result, '%');
    }
    return (result);
}

static char *get_start_of_msg(log_type_e type)
{
    if (type == INFO)
        return strdup("\033[0;36m[INFO]:\033[m ");
    else if (type == WARNING)
        return strdup("\033[0;33m[WARNING]: \033[m");
    else return strdup("\033[0;31m[ERROR]: \033[m");
}

static void write_logfile(log_type_e type, char *log)
{
    char *start_of_msg = get_start_of_msg(type);
    int fd = OPEN_LOGFILE;

    if (fd == -1 || !logfile_exists()) {
        free(log);
        free(start_of_msg);
        return;
    }
    log = concat_str(start_of_msg, log);
    free(start_of_msg);
    if (!write(fd, log, strlen(log)) || !write(2, log, strlen(log))) {
        free(log);
        return;
    }
    free(log);
    close(fd);
}

void __log(log_type_e type, char *string, ...)
{
    va_list ap;
    char *msg = (void *) 0;

    if (string == (void *) 0 || string[0] == '\0')
        return;
    va_start(ap, string);
    for (int i = 0; string[i] != 0; i++) {
        if (string[i] == '%' && string[i + 1] != 0) {
            msg = concat_str(msg, switch_case(string[i + 1], ap));
            i++;
        } else msg = append_char(msg, string[i]);
    }
    va_end(ap);
    write_logfile(type, msg);
}

void log_if_errno(int err, char *function_name)
{
    int fd = 0;
    char *err_msg = NULL;

    if (!logfile_exists())
        return;
    else if (err == 0 || err == 2) {
        __log(INFO, "\033[0;32msuccess for [\033[0;33m%s\033[0;32m].\033[m\n", function_name);
        return;
    }
    err_msg = concat_str("\033[0;31m[ERROR ON ", function_name);
    err_msg = concat_str(err_msg, "]\033[m: ");
    err_msg = concat_str(err_msg, strerror(err));
    err_msg = concat_str(err_msg, "\n");
    fd = OPEN_LOGFILE;
    if (!write(fd, err_msg, strlen(err_msg)) || !write(2, err_msg, strlen(err_msg)))
        return;
    close(fd);
    free(err_msg);
}

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
    return (fd == -1) ? 1 : 0;
}
