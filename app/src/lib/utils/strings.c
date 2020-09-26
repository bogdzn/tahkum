/**
 * \file strings.c
 * \brief everything related to strings !
 * \author Bogdan G.
 * \date 21/09/2020
 */

#include "./utils.h"

#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <limits.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>

/**
 * \fn int my_strlen(char const *s)
 * \brief gets the length of a string.
 *
 * \param s string you want to mesure.
 * \return length of the string.
 */
int my_strlen(char const *s)
{
    int size = 0;

    if (s == NULL || *s == 0)
        return 0;
    for (; s[size] != 0; size++);
    return size;
}

/**
 * \fn char *my_strdup(char const *s)
 * \brief makes a deep copy of a string.
 *
 * \param s string you want to copy.
 * \return memory allocated copy of s.
 */
char *my_strdup(char const *s)
{
    int len = my_strlen(s);
    char *result = NULL;

    if (s == NULL || *s == 0)
        return NULL;
    result = malloc(sizeof(char) * (len + 1));
    if (result == NULL)
        return result;
    for (int i = 0; s[i] != 0; i++)
        result[i] = s[i];
    result[len] = 0;
    return result;
}

/**
 * \fn char *my_strcat(char const *s1, char const *s2)
 * \brief makes a deep copy of two stirngs, and concatenates them together.
 *
 * \param s1 first string you want to copy.
 * \param s2 second string you want to copy.
 * \return memory allocated s1 + s2.
 */
char *my_strcat(const char *s1, const char *s2)
{
    int len_string = 0;
    char *result = (void *) 0;
    int ctr = 0;

    if (s2 == (void *) 0 || s2[0] == 0)
        return (my_strdup(s1));
    else if (s1 == (void *) 0 || s1[0] == 0)
        return (my_strdup(s2));
    len_string = my_strlen(s1) + my_strlen(s2) + 1;
    if (len_string == 1)
        return ((void *) 0);
    result = malloc(sizeof(char) * (len_string + 1));
    for (; s1[ctr] != '\0'; ctr++)
        result[ctr] = s1[ctr];
    for (int ctr2 = 0; s2[ctr2] != '\0'; ctr2++)
        result[ctr + ctr2] = s2[ctr2];
    result[len_string] = '\0';
    return (result);
}

/**
 * \fn char *my_itoa(int nb)
 * \brief converts an int into a string.
 *
 * \param nb the int you want to convert.
 * \return a string containing the number.
 */
char *my_itoa(int nb)
{
    int nb_len = my_nblen(nb);
    char *result = (void *) 0;
    bool is_negative = nb < 0 ? true : false;

    if (nb == 0)
        return (my_strdup("0"));
    result = malloc(sizeof(char) * (nb_len + 1));
    nb = is_negative == true ? nb * -1 : nb;
    result[nb_len] = '\0';
    for (int i = nb_len - 1; i > -1; i--) {
        result[i] = (nb % 10) + 48;
        nb = nb / 10;
    }
    return (is_negative ? my_strcat("-", result) : result);
}

/**
 * \fn char *set_to_lowercase(char *s)
 * \brief sets a string to lowercase.
 *
 * \param s a string.
 * \return s but in lowercase.
 */
char *set_to_lowercase(char *s)
{
    if (s == (void *) 0 || s[0] == '\0')
        return ((void *) 0);
    for (int i = 0; s[i] != '\0'; i++)
        if (s[i] >= 'A' && s[i] <= 'Z')
            s[i] += 32;
    return (s);
}

/**
 * \fn char *set_to_uppercase(char *s)
 * \brief sets a string to uppercase.
 *
 * \param s a string.
 * \return s but in uppercase.
 */
char *set_to_uppercase(char *s)
{
    if (s == (void *) 0 || s[0] == '\0')
        return ((void *) 0);
    for (int i = 0; s[i] != '\0'; i++)
        if (s[i] >= 'a' && s[i] <= 'z')
            s[i] -= 32;
    return (s);
}

/**
 * \fn char *my_revstr(char *s)
 * \brief reverses a string.
 *
 * \param s a string.
 * \return s but reversed.
 */
char *my_revstr(char *s)
{
    int len_s = my_strlen(s) - 1;

    if (s == (void *) 0 || s[0] == '\0')
        return ((void *) 0);
    for (int i = 0; i < len_s; i++, len_s--)
        swapc((void *) &s[i], (void *) &s[len_s]);
    return (s);
}

/**
 * \fn char *my_strcpy(char *dest, char const *src)
 * \brief copies a string into another.
 *  You will need to alloc the string.
 *
 * \param src the string you want to copy.
 * \param dest the string where you want to copy.
 * \return a copy of src.
 */
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

/**
 * \fn char *my_strncpy(char *dest, char const *src, int n)
 * \brief copies a string into another, for n characters.
 *  You will need to alloc the string.
 *
 * \param src the string you want to copy.
 * \param dest the string where you want to copy.
 * \param n the size of your copy.
 * \return a copy of src for n characters.
 */
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

/**
 * \fn bool is_same_string(char const *s1, char const *s2)
 * \brief tests if 2 strings are the same.
 *
 * \param s1 your first string.
 * \param s2 the string you want to compare.
 * \return a boolean explicitly telling you if your strings are the same.
 */
bool is_same_string(const char *s1, const char *s2)
{
    int i = 0;

    if ((s1 == (void *) 0 || s1[0] == '\0') || (s2 == (void *) 0 || s2[0] == '\0'))
        return (false);
    for (; s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0'; i++);
    return (s1[i] - s2[i]);
}

/**
 * \fn bool is_same_stringn(char const *s1, char const *s2, int n)
 * \brief tests if 2 strings are the same, for n characters.
 *
 * \param s1 your first string.
 * \param s2 the string you want to compare.
 * \param n range of how much you want to compare.
 * \return a boolean explicitly telling you if your strings are the same.
 */
bool is_same_stringn(const char *s1, const char *s2, int n)
{
    int i = 0;

    if ((s1 == (void *) 0 || s1[0] == '\0') || (s2 == (void *) 0 || s2[0] == '\0'))
        return (false);
    for (; i < n && s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0'; i++);
    return (s1[i] - s2[i]);
}

/**
 * \fn bool is_num(const char *s)
 * \brief tests if a string can be translated into an int.
 *
 * \param s your string.
 * \return a boolean explicitly telling you if your string is a number.
 */
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

/**
 * \fn bool is_a_letter(char c, bool is_lower)
 * \brief tests if a character is a letter.
 * (lowercase, or uppercase, depending on the boolean)
 *
 * \param c a character.
 * \param is_lower a boolean asking if you want to test lowercase of uppercase characters
 * \return a boolean explicitly telling you if your string is a letter..
 */
bool is_a_letter(char c, bool is_lower)
{
    int offset = is_lower == true ? 0 : 32;

    return (c >= 'a' + offset && c <= 'z' + offset ? true : false);
}

/**
 * \fn bool is_alphabetic(char *s)
 * \brief  tests if a string only contains alphabetic characters.
 *
 * \param s your string.
 * \return a boolean explicitly telling you if your string is a letter..
 */
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

/**
 * \fn int is_in_string(char const *s, char to_find)
 * \brief tests if a specific character is in a string.
 *
 * \param s your string.
 * \param to_find the character you want to find.
 * \return the index of the character if found, or -1.
 */
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

/**
 * \fn char *get_last_occurence_of(char *s, char to_find)
 * \brief  gets the substring after the last occurence of a character.
 * useful for paths: /var/log/tello.log becomes tello.log if to_find == '/'
 *
 * \param s your string.
 * \param to_find the character you want to find.
 * \return a substring after the last occurence of to_find.
 */
char *get_last_occurence_of(char *s, char to_find)
{
    int position = is_in_string(s, to_find);

    if (position < 0)
        return (s);
    return (get_last_occurence_of(&s[position + 1], to_find));
}

/**
 * \fn char *append_char(char *s, char c)
 * \brief appends a character to a string.
 *
 * \param s your string.
 * \param c the character you want to append.
 * \return s + c.
 */
char *append_char(char *s, char c)
{
    char *result = (void *) 0;

    if (s == (void *) 0) {
        result = malloc(sizeof(char) * 2);
        result[0] = c;
        result[1] = '\0';
        return (result);
    } else {
        result = malloc(sizeof(char) * (my_strlen(s) + 2));
        result = my_strcpy(result, s);
        result[my_strlen(s)] = c;
        result[my_strlen(s) + 1] = '\0';
        free(s);
    }
    return (result);
}

/**
 * \fn void my_putstr(char const *s)
 * \brief writes a string to stdout
 *
 * \param s your string.
 */
void my_putstr(char const *s)
{
    if (!write(1, s, my_strlen(s)))
        return;
}

/**
 * \fn void my_puterr(char const *s)
 * \brief writes a string to stderr.
 *
 * \param s your string.
 */
void my_puterr(char const *s)
{
    if (!write(2, s, my_strlen(s)))
        return;
}

static char *__strip_front(char *line, char to_strip)
{
    int i = 0;

    for (; line[i] != 0 && line[i] == to_strip; i++);
    return &line[i];
}

static char *__strip_back(char *line, char to_strip)
{
    int i = my_strlen(line);

    for (; i != 0 && line[i] == to_strip; i--);
    if (i > 0 && line[i - 1] == to_strip)
        line[i - 1] = 0;
    return line;
}

/**
 * \fn char *strip(char *line, char to_strip)
 * \brief strips a string of trailing of leading to_strip characters.
 * useful to remove trailing or leading spaces.
 *
 * \param line your string.
 * \param to_strip the character you want to strip.
 * \return line, stripped of leading and trailing to_strip.
 */
char *strip(char *line, char to_strip)
{
    if (line == NULL || line[0] == 0 || to_strip == 0)
        return NULL;
    return __strip_back(__strip_front(line, to_strip), to_strip);
}

/**
 * \fn char *remove_tabs(char *line)
 * \brief transforms tabs into spaces.
 *
 * \param line your string.
 * \return line, but with spaces instead of tabs.
 */
char *remove_tabs(char *line)
{
    if (line == NULL || *line == 0)
        return NULL;
    for (int i = 0; line[i] != 0; i++)
        line[i] = line[i] == '\t' ? ' ' : line[i];
    return line;
}

/**
 * \fn char *clean_line(char *line)
 * \brief removes double-spaces, trailing and leading spaces from a string.
 *
 * \param line your string.
 * \return line, stripped of leading and trailing spaces.
 */
char *clean_line(char *line)
{
    char *stripped = strip(remove_tabs(line), ' ');
    char *result = NULL;
    char temp = 0;

    if (stripped == NULL)
        return NULL;
    for (int i = 0; stripped[i] != 0; i++) {
        if (temp == ' ' && stripped[i] == ' ')
            continue;
        temp = stripped[i];
        result = append_char(result, temp);
    }
    return strip(result, ' ');
}

/**
 * \fn bool is_float(char const *s)
 * \brief tests if a string can be converted to a float.
 *
 * \param s your string.
 * \return a boolean telling you if your string can be converted to a float.
 */
bool is_float(char const *s)
{
    int nb_dots = 0;

    if (s == NULL || *s == 0)
        return NULL;
    if (s[0] == '-')
        s = &s[1];
    for (int i = 0; s[i] != 0; i++) {
        if ((s[i] == '.' || s[i] == ',') && nb_dots == 0) {
            nb_dots++;
            continue;
        } else if (s[i] >= '0' && s[i] <= '9')
            continue;
        else return false;
    }
    return true;
}