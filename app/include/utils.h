/**
 * \file utils.h
 * \brief Header for utils internal librairy..
 * \author Bogdan G.
 * \version 0.1
 * \date 21/09/2020
 */

#ifndef TELLO_UTILS_H
#define TELLO_UTILS_H

/// Macro needed for get_next_line.c
#ifndef READ_SIZE
#define READ_SIZE (60)
#endif

#include <stdbool.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

// file_handler.c

/**
 * \struct file_t
 * \brief Object handling files.
 *
 * Contains its name, stats and content.
 */
typedef struct file_s
{
    char *name;
    char *content;
    struct stat st;
} file_t;

/**
 * \fn file_t get_file(char const *filepath)
 * \brief loads file information into memory.
 *
 * \param filepath path of the file you want to read.
 * \return filled file_t structure.
 */
file_t get_file(char const *filepath);

/**
 * \fn void destroy_file(file_t file)
 * \brief destroys file_t structure.
 *
 * \param file structure you want to erase.
 */
void destroy_file(file_t file);


// strings.c
/**
 * \fn int my_strlen(char const *s)
 * \brief gets the length of a string.
 *
 * \param s string you want to mesure.
 * \return length of the string.
 */
int my_strlen(char const *s);

/**
 * \fn char *my_strdup(char const *s)
 * \brief makes a deep copy of a string.
 *
 * \param s string you want to copy.
 * \return memory allocated copy of s.
 */
char *my_strdup(char const *s);

/**
 * \fn char *my_strcat(char const *s1, char const *s2)
 * \brief makes a deep copy of two stirngs, and concatenates them together.
 *
 * \param s1 first string you want to copy.
 * \param s2 second string you want to copy.
 * \return memory allocated s1 + s2.
 */
char *my_strcat(char const *s1, char const *s2);

/**
 * \fn char *my_itoa(int nb)
 * \brief converts an int into a string.
 *
 * \param nb the int you want to convert.
 * \return a string containing the number.
 */
char *my_itoa(int nb);

/**
 * \fn char *set_to_lowercase(char *s)
 * \brief sets a string to lowercase.
 *
 * \param s a string.
 * \return s but in lowercase.
 */
char *set_to_lowercase(char *s);

/**
 * \fn char *set_to_uppercase(char *s)
 * \brief sets a string to uppercase.
 *
 * \param s a string.
 * \return s but in uppercase.
 */
char *set_to_uppercase(char *s);

/**
 * \fn char *my_revstr(char *s)
 * \brief reverses a string.
 *
 * \param s a string.
 * \return s but reversed.
 */
char *my_revstr(char *s);

/**
 * \fn char *my_strcpy(char *dest, char const *src)
 * \brief copies a string into another.
 *  You will need to alloc the string.
 *
 * \param src the string you want to copy.
 * \param dest the string where you want to copy.
 * \return a copy of src.
 */
char *my_strcpy(char *dest, char const *src);

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
char *my_strncpy(char *dest, char const *src, int n);

/**
 * \fn bool is_same_string(char const *s1, char const *s2)
 * \brief tests if 2 strings are the same.
 *
 * \param s1 your first string.
 * \param s2 the string you want to compare.
 * \return a boolean explicitly telling you if your strings are the same.
 */
bool is_same_string(char const *s1, char const *s2);

/**
 * \fn bool is_same_stringn(char const *s1, char const *s2, int n)
 * \brief tests if 2 strings are the same, for n characters.
 *
 * \param s1 your first string.
 * \param s2 the string you want to compare.
 * \param n range of how much you want to compare.
 * \return a boolean explicitly telling you if your strings are the same.
 */
bool is_same_stringn(char const *s1, char const *s2, int n);

/**
 * \fn bool is_num(const char *s)
 * \brief tests if a string can be translated into an int.
 *
 * \param s your string.
 * \return a boolean explicitly telling you if your string is a number.
 */
bool is_num(const char *s);

/**
 * \fn bool is_a_letter(char c, bool is_lower)
 * \brief tests if a character is a letter.
 * (lowercase, or uppercase, depending on the boolean)
 *
 * \param c a character.
 * \param is_lower a boolean asking if you want to test lowercase of uppercase characters
 * \return a boolean explicitly telling you if your string is a letter..
 */
bool is_a_letter(char c, bool is_lower);

/**
 * \fn bool is_alphabetic(char *s)
 * \brief  tests if a string only contains alphabetic characters.
 *
 * \param s your string.
 * \return a boolean explicitly telling you if your string is a letter..
 */
bool is_alphabetic(char *s);

/**
 * \fn int is_in_string(char const *s, char to_find)
 * \brief tests if a specific character is in a string.
 *
 * \param s your string.
 * \param to_find the character you want to find.
 * \return the index of the character if found, or -1.
 */
int is_in_string(char const *s, char to_find);

/**
 * \fn char *get_last_occurence_of(char *s, char to_find)
 * \brief  gets the substring after the last occurence of a character.
 * useful for paths: /var/log/tello.log becomes tello.log if to_find == '/'
 *
 * \param s your string.
 * \param to_find the character you want to find.
 * \return a substring after the last occurence of to_find.
 */
char *get_last_occurence_of(char *s, char to_find);

/**
 * \fn char *append_char(char *s, char c)
 * \brief appends a character to a string.
 *
 * \param s your string.
 * \param c the character you want to append.
 * \return s + c.
 */
char *append_char(char *s, char c);

/**
 * \fn void my_putstr(char const *s)
 * \brief writes a string to stdout
 *
 * \param s your string.
 */
void my_putstr(char const *s);

/**
 * \fn void my_puterr(char const *s)
 * \brief writes a string to stderr.
 *
 * \param s your string.
 */
void my_puterr(char const *s);

/**
 * \fn char *strip(char *line, char to_strip)
 * \brief strips a string of trailing of leading to_strip characters.
 * useful to remove trailing or leading spaces.
 *
 * \param line your string.
 * \param to_strip the character you want to strip.
 * \return line, stripped of leading and trailing to_strip.
 */
char *strip(char *line, char to_strip);

/**
 * \fn char *clean_line(char *line)
 * \brief removes double-spaces, trailing and leading spaces from a string.
 *
 * \param line your string.
 * \return line, stripped of leading and trailing spaces.
 */
char *clean_line(char *line);

/**
 * \fn char *remove_tabs(char *line)
 * \brief transforms tabs into spaces.
 *
 * \param line your string.
 * \return line, but with spaces instead of tabs.
 */
char *remove_tabs(char *line);

/**
 * \fn bool is_float(char const *s)
 * \brief tests if a string can be converted to a float.
 *
 * \param s your string.
 * \return a boolean telling you if your string can be converted to a float.
 */
bool is_float(char const *s);


// swaps.c
/**
 * \fn void swap_array(void **one, void **two)
 * \brief tests if a string can be converted to a float.
 *
 * \param one your first array address.
 * \param two your second array address.
 */
void swap_array(void **one, void **two);

/// swaps 2 characters.
/**
 * \fn void swapc(char *one, char *two)
 * \brief swaps 2 characters.
 *
 * \param one your first char address.
 * \param two your second char address.
 */
void swapc(char *one, char *two);

/**
 * \fn void swap(int *one, int *two)
 * \brief swaps 2 ints.
 *
 * \param one your first int address.
 * \param two your second int address.
 */
void swap(int *one, int *two);

// arrays.c
/**
 * \fn void free_array(void **array)
 * \brief frees a 2dimentionnal array.
 *
 * \param array the array you want to destroy.
 */
void free_array(void **array);

/**
 * \fn char **tabgen(char const *str, char separator)
 * \brief generated a 2dimentionnal array, based on a string.
 * splits it every time it finds a separator.
 *
 * \param str your string.
 * \param separator the separating character
 * \return an array of string seperated by a specific character.
 */
char **tabgen(char const *str, char separator);

/**
 * \fn void display_tab(char const **tab)
 * \brief displays a 2dimentionnal array.
 *
 * \param tab the array you want to display.
 */
void display_tab(char const **tab);

/**
 * \fn char **append_line_to_tab(char **tab, char *line)
 * \brief appends a line to a 2dimentionnal array.
 *
 * \param tab an array of strings.
 * \param line the string you want to concatenate.
 * \return an array of strings. (tab + line)
 */
char **append_line_to_tab(char **tab, char *line);

/**
 * \fn int my_tablen(char const **tab)
 * \brief gets the length of a 2dimentionnal array.
 *
 * \param tab an array of strings.
 * \return the number of string in your array.
 */
int my_tablen(char const **tab);


// nums.c
/**
 * \fn int do_op(int first_nb, int second_nb, char sign)
 * \brief executes a specific operation, depending on the sign.
 *
 * \param first_nb your first number
 * \param second_nb your second number
 * \param the sign of your operation (+, -, %, /, *)
 * \return results of your operation.
 */
int do_op(int first_nb, int second_nb, char sign);

/**
 * \fn void my_putnbr(int nb)
 * \brief displays a number to stdout.
 *
 * \param nb the number your want to display.
 */
void my_putnbr(int nb);

/**
 * \fn int my_nblen(int nb)
 * \brief gets the length of a number, in numbers of characters.
 * doesn't count the - character.
 *
 * \param nb the number you want to mesure.
 * \return the length of your number.
 */
int my_nblen(int nb);

/**
 * \fn int my_getnbr(char *nb)
 * \brief Extracts a number from a string.
 * Will only bypass whitespaces.
 *
 * \param nb the number you want to convert.
 * \return you converted number, in an int.
 */
int my_getnbr(char *nb);

/**
 * \fn char *my_getnbr_base(int nb, const char *base_to)
 * \brief transforms an int into whatever base you want.
 * useful for addresses.
 *
 * \param nb the number you want to convert.
 * \param base_to the base you want to convert to.
 * \return you converted number, in a string.
 */
char *my_getnbr_base(int nb, const char *base_to);

/**
 * \fn char *my_putnbr_base(int nb, const char *base_to)
 * \brief displays an int into whatever base you want.
 * useful for addresses.
 *
 * \param nb the number you want to convert.
 * \param base_to the base you want to convert to.
 */
void my_putnbr_base(int nb, char const *base_to);


// get_next_line.c
/**
 * \fn char *get_next_line(int fd)
 * \brief reads the next line from a file.
 * the file descriptor needs to be open and closed manually.
 *
 * \param fd the file descriptor of the file you want to read.
 * \return the next line of the file.
 */
char *get_next_line(int fd);

/**
 * \fn char *concat_str(char *s1, char *s2);
 * \brief concatenates two strings
 * \param s1 first string
 * \param s2 second string
 * \return s1 + s2
 */
char *concat_str(char *s1, char *s2);

#endif //TELLO_UTILS_H
