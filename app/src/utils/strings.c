/**
 * \file strings.c
 * \brief everything related to strings !
 * \author Bogdan G.
 * \date 17/10/2020
 */

#include "utils.h"

#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <limits.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>

char *str_to_lower(char *s)
{
    if (!s || *s == 0)
        return NULL;
    for (int i = 0; s[i] != 0; i++)
        s[i] = tolower(s[i]);
    return s;
}

char *my_itoa(int nb)
{
    int nb_len = my_nblen(nb);
    char *result = (void *) 0;
    bool is_negative = nb < 0 ? true : false;

    if (nb == 0)
        return (strdup("0"));
    result = malloc(sizeof(char) * (nb_len + 1));
    nb = is_negative == true ? nb * -1 : nb;
    result[nb_len] = '\0';
    for (int i = nb_len - 1; i > -1; i--) {
        result[i] = (nb % 10) + 48;
        nb = nb / 10;
    }
    return (is_negative ? concat_str("-", result) : result);
}

bool is_num(const char *s)
{
    if (s == (void *) 0 || s[0] == '\0')
        return (false);
    for (int i = 0; s[i] != '\0'; i++) {
        if (s[i] != '-' && (s[i] > '9' || s[i] < '0'))
            return (false);
    }
    return (true);
}

bool is_a_letter(char c, bool is_lower)
{
    int offset = is_lower == true ? 0 : 32;

    return (c >= 'a' + offset && c <= 'z' + offset ? true : false);
}

bool is_alphabetic(char *s)
{
    if (s == (void *) 0 || s[0] == '\0')
        return (false);
    for (int i = 0; s[i] != '\0'; i++) {
        if (!is_a_letter(s[i], false) && !is_a_letter(s[i], true))
            return (false);
    }
    return (true);
}

int is_in_string(const char *s, char to_find)
{
    if (s == (void *) 0 || s[0] == '\0')
        return (-1);
    for (int i = 0; s[i] != '\0'; i++) {
        if (s[i] == to_find)
            return (i);
    }
    return (-1);
}

char *get_last_occurence_of(char *s, char to_find)
{
    int position = is_in_string(s, to_find);

    if (position < 0)
        return (s);
    return (get_last_occurence_of(&s[position + 1], to_find));
}

char *append_char(char *s, char c)
{
    char *result = (void *) 0;
    int len = 0;

    if (s == (void *) 0 || *s == 0) {
        result = malloc(sizeof(char) * 2);
        result[0] = c;
        result[1] = '\0';
    } else {
        len = strlen(s);
        result = malloc(sizeof(char) * (len + 2));
        result = strcpy(result, s);
        result[len] = c;
        result[len + 1] = '\0';
        free(s);
    }
    return (result);
}

void my_putstr(char const *s)
{
    if (!write(1, s, strlen(s)))
        return;
}

void my_puterr(char const *s)
{
    if (!write(2, s, strlen(s)))
        return;
}

static char *__strip_front(char *line, char to_strip)
{
    int i = 0;

    if (line == NULL || *line == 0)
        return NULL;
    for (; line[i] != 0 && line[i] == to_strip; i++);
    return &line[i];
}

static char *__strip_back(char *line, char to_strip)
{
    int i = 0;

    if (line == NULL || *line == 0)
        return NULL;
    for (i = strlen(line); i != 0 && line[i] == to_strip; i--);
    if (i > 0 && line[i - 1] == to_strip)
        line[i - 1] = 0;
    return line;
}

char *strip(char *line, char to_strip)
{
    if (line == NULL || line[0] == 0 || to_strip == 0)
        return NULL;
    return __strip_back(__strip_front(line, to_strip), to_strip);
}
