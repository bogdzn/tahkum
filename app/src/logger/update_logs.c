/**
 * \file update_logs.c
 * \brief Handles logs updates.
 * \author Bogdan G.
 * \date 27/09/2020
 */

#include "logger.h"
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <fcntl.h>
#include <errno.h>
#include "utils.h"

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
        return my_strdup("[INFO] :");
    else if (type == WARNING)
        return my_strdup("[WARNING} :");
    else return my_strdup("[ERROR] :");
}

static void write_logfile(log_type_e type, char *log)
{
    char *start_of_msg = get_start_of_msg(type);
    int fd = OPEN_LOGFILE;

    if (fd == -1 || !logfile_exists())
        return;
    log = my_strcat(start_of_msg, log);
    if (log[my_strlen(log)] != '\n')
        log = my_strcat(log, "\n");
    if (!write(fd, log, my_strlen(log)))
        return;
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
            msg = my_strcat(msg, switch_case(string[i + 1], ap));
            i++;
        } else msg = append_char(msg, string[i]);
    }
    va_end(ap);
    write_logfile(type, msg);
    free(msg);
}

void log_if_errno(int err, char *function_name)
{
    int fd = 0;
    char *err_msg = NULL;

    if (err == 0 || err == 2 || !logfile_exists())
        return;
    err_msg = my_strcat("[ERROR] -- ", function_name);
    err_msg = my_strcat(err_msg, strerror(err));
    if (err_msg[my_strlen(err_msg)] != '\n')
        err_msg= my_strcat(err_msg, "\n");
    fd = OPEN_LOGFILE;
    if (!write(fd, err_msg, my_strlen(err_msg)))
        return;
    close(fd);
    free(err_msg);
}
