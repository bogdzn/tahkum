/**
 * \file utils.h
 * \brief Header for utils internal librairy..
 * \author Bogdan G.
 * \version 0.1
 * \date 17/10/2020
 */

#ifndef TELLO_UTILS_H
#define TELLO_UTILS_H

#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <sys/stat.h>

/// path where the log file is stored.
#ifndef LOG_PATH
#define LOG_PATH ("./tello.log")
#endif

/// Macro opening the log file, with O_APPEND flag set.
#ifndef OPEN_LOGFILE
#define OPEN_LOGFILE (open(LOG_PATH, \
        O_CREAT | O_APPEND | O_RDWR, \
        S_IRWXU | S_IRWXG | S_IRWXO))
#endif

/// macro for truncating the log file.
#ifndef CREATE_LOGFILE
#define CREATE_LOGFILE (open(LOG_PATH, \
        O_CREAT | O_TRUNC | O_RDWR, \
        S_IRWXU | S_IRWXG | S_IRWXO))
#endif

/// Macro needed for get_next_line.c
#ifndef READ_SIZE
#define READ_SIZE (60)
#endif

/**
 * \enum log_type_e
 * \brief Log messages types.
 *
 * Defines which type of log we want to write.
 */
typedef enum LOG_TYPE
{
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
 * \fn void __log(LOG_TYPE, char *string)
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
 * \fn void log_if_errno(int errno, char *function_name)
 * \brief Adds a log to LOG_PATH if errno is different than 2 or 0.
 * By default, every error triggered by this function is considered
 * a critical error.
 *
 * \param errno ERRNO constant.
 * \param function_name defining the operation you are currently doing.
 */
void log_if_errno(int err, char *function_name);

// strings.c
/**
 * \fn char *my_itoa(int nb)
 * \brief converts an int into a string.
 *
 * \param nb the int you want to convert.
 * \return a string containing the number.
 */
char *my_itoa(int nb);

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
 * \fn char *str_to_lower(char *s)
 * \brief sets a string to lowercase
 *
 * \param s your string.
 * \return s but in lowercase.
 */
char *str_to_lower(char *s);

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


// key_listener.c
/**
  * \fn char get_pressed_key(void)
  * \brief reads user input from terminal, in a non-blocking way.
  *
  * \return user-pressed key, or \0 if nothing.
  */
char get_pressed_key(void);

#endif //TELLO_UTILS_H
