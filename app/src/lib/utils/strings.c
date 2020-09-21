//
// Created by bogdan on 21/09/2020.
//

#include "utils.h"

#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <limits.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>

int my_strlen(char const *s)
{
    int size = 0;

    if (s == NULL || *s == 0)
        return 0;
    for (; s[size] != 0; size++);
    return size;
}

char *my_strdup(char const *s)
{
    int len = my_strlen(s);
    char *result = NULL;

    if (s == NULL || *s == 0)
        return NULL;
    memset(&result, sizeof(char), len + 1);
    if (result == NULL)
        return result;
    for (int i = 0; s[i] != 0; i++)
        result[i] = s[i];
    result[len] = 0;
    return result;
}

char *my_strcat(const char *s1, const char *s2)
{
    int len_string = 0;
    char *result = (void *)0;
    int ctr = 0;

    if (s2 == (void *)0 || s2[0] == 0)
        return (my_strdup(s1));
    else if (s1 == (void *)0 || s1[0] == 0)
        return (my_strdup(s2));
    len_string = my_strlen(s1) + my_strlen(s2) + 1;
    if (len_string == 1)
        return ((void *)0);
    memset(&result, sizeof(char), len_string + 1)
    for (; s1[ctr] != '\0'; ctr++)
        result[ctr] = s1[ctr];
    for (int ctr2 = 0; s2[ctr2] != '\0'; ctr2++)
        result[ctr + ctr2] = s2[ctr2];
    result[len_string] = '\0';
    return (result);
}

char *my_itoa(int nb)
{
    int nb_len = my_nblen(nb); //todo
    char *result = (void *)0;
    bool is_negative = nb < 0 ? true : false;

    if (nb == 0)
        return (my_strdup("0"));
    memset(&result, sizeof(char), nb_len + 1);
    nb = is_negative == true ? nb * -1 : nb;
    result[nb_len] = '\0';
    for (int i = nb_len - 1; i > -1; i--) {
        result[i] = (nb % 10) + 48;
        nb = nb / 10;
    }
    return (is_negative ? my_strcat("-", result) : result);
}

char *set_to_lowercase(char *s)
{
    if (s == (void *)0 || s[0] == '\0')
        return ((void *)0);
    for (int i = 0; s[i] != '\0'; i++)
        if (s[i] >= 'A' && s[i] <= 'Z')
            s[i] += 32;
    return (s);
}

char *set_to_uppercase(char *s)
{
    if (s == (void *)0 || s[0] == '\0')
        return ((void *)0);
    for (int i = 0; s[i] != '\0'; i++)
        if (s[i] >= 'a' && s[i] <= 'z')
            s[i] -= 32;
    return (s);
}

char *my_revstr(char *s)
{
    int len_s = my_strlen(s) - 1;

    if (s == (void *)0 || s[0] == '\0')
        return ((void *)0);
    for (int i = 0; i < len_s; i++, len_s--)
        swapc((void *)&s[i], (void *)&s[len_s]);
    return (s);
}

char *my_strcpy(char *dest, char const *src)
{
    int i = 0;

    if ((src == NULL || src[0] == '\0'))
        return (NULL);
    for (; src[i] != '\0'; i++)
        dest[i] = src[i];
    dest[i] = '\0';
    return dest;
}

char *my_strncpy(char *dest, char const *src, int n)
{
    int i = 0;

    if (src == NULL || src[0] == 0 || n < 1)
        return (NULL);
    for (; src[i] && i < n; i++)
        dest[i] = src[i];
    dest[i] = '\0';
    return dest;
}

bool is_same_string(const char *s1, const char *s2)
{
    int i = 0;

    if ((s1 == (void *)0 || s1[0] =='\0') || (s2 == (void *)0 || s2[0] == '\0'))
        return (false);
    for (; s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0'; i++);
    return (s1[i] - s2[i]);
}

bool is_same_stringn(const char *s1, const char *s2, int n)
{
    int i = 0;

    if ((s1 == (void *)0 || s1[0] =='\0') || (s2 == (void *)0 || s2[0] == '\0'))
        return (false);
    for (; i < n && s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0'; i++);
    return (s1[i] - s2[i]);
}

bool is_num(const char *s)
{
    if (s == (void *)0 || s[0] == '\0')
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
    if (s == (void *)0 || s[0] == '\0')
        return (false);
    for (int i = 0; s[i] != '\0'; i++) {
        if (!is_a_letter(s[i], false) && !is_a_letter(s[i], true))
            return (false);
    }
    return (true);
}

int is_in_string(const char *s, char to_find)
{
    if (s == (void *)0 || s[0] == '\0')
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
    char *result = (void *)0;

    if (s == (void *)0) {
        result = malloc(sizeof(char) * 2);
        result[0] = c;
        result[1] = '\0';
        return (result);
    } else {
        result = malloc(sizeof(char) * (my_strlen(s) + 2));
        result = my_strcpy(result, s);
        result[my_strlen(s)] = c;
        result[my_strlen(s) + 1] = '\0';
    }
    return (result);
}

void my_putstr(char const *s)
{
    if (!write(1, s, my_strlen(s)))
        return;
}

void my_puterr(char const *s)
{
    if (!write(2, s, my_strlen(s)))
        return;
}
