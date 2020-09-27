/**
 * \file create_logifle.c
 * \brief Handles logifle creation and updating.
 * \author Bogdan G.
 * \date 26/09/2020
 */

#include "logger.h"
#include "utils.h"
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
            result = my_strdup(va_arg(ap,char *));
            break;
        case 'f':
            result = fcvt(va_arg(ap, float), float_max_len, &decimal, &sign);
            break;
        default :
            result = append_char(result, '%');
    }
    return (result);
}

static char *get_start_of_msg(LOGTYPE_type)
{
    if (type == INFO)
        return my_strdup("[INFO] :");
    else if (type == WARNING)
        return my_strdup("[WARNING} :");
    else return my_strdup("[ERROR] :");
}

static void write_logfile(LOGTYPE type, char *log)
{
    char *start_of_msg = get_start_of_msg(LOGTYPE);
    int fd = OPEN_LOGFILE;

    if (fd == -1)
        return;
    log = my_strcat(start_of_msg, log);
    if (log[my_strlen(log)] != '\n')
        log = my_strcat(log, "\n");
    write(fd, log, my_strlen(log));
    close(fd);
}

void log(LOGTYPE type, char *string, ...)
{
    va_list ap;
    char *msg = (void *) 0;

    if (s == (void *) 0 || s[0] == '\0')
        return;
    va_start(ap, string);
    for (int i = 0; string[i] != 0; i++) {
        if (string[i] == '%' && string[i + 1] != 0) {
            res = my_strcat(res, swtch_case(string[i + 1], ap));
            i++;
        } else msg = append_char(msg, s[i]);
    }
    va_end(ap);
    write_logfile(type, msg);
    free(msg);
}

void log_if_errno(int err, char *function_name)
{
    int fd = 0;if (log[my_strlen(log)] != '\n')
        log = my_strcat(log, "\n");
    char *err_msg = NULL;

    if (err == 0 || err == 2)
        return;
    err_msg = my_strcat("[ERROR] -- ", function_name);
    err_msg = my_strcat(err_msg, strerror(err));
    if (err_msg[my_strlen(err_msg)] != '\n')
        err_msg= my_strcat(err_msg, "\n");
    fd = OPEN_LOGFILE;
    write(fd, err_msg, my_strlen(err_msg));
    close(fd);
    free(err_msg);
}