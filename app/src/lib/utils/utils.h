//
// Created by bogdan on 21/09/2020.
//

#ifndef TELLO_UTILS_H
#define TELLO_UTILS_H

// Macro needed for get_next_line.c
#ifndef READ_SIZE
#define READ_SIZE (60)
#endif

#include <stdbool.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

// file_handler.c

// structure used to handle files, stores its stats, content, and name
typedef struct file_s
{
    char *name;
    char *content;
    struct stat st;
} file_t;

// loads file information into memory.
file_t get_file(char const *filepath);

// destroys file structure.
void destroy_file(file_t file);


// strings.c

// gets the length of a string.
int my_strlen(char const *s);

// makes a deep copy of a string.
char *my_strdup(char const *s);

// makes a deep copy of two stirngs, and appends them together.
char *my_strcat(char const *s1, char const *s2);

// converts an int into a string.
char *my_itoa(int nb);

// sets a string to lowercase.
char *set_to_lowercase(char *s);

// sets a string to uppercase.
char *set_to_uppercase(char *s);

// reverses a string.
char *my_revstr(char *s);

// copies a string into another, for n characters.
// You will need to alloc the string.
char *my_strncpy(char *dest, char const *src, int n);

// tests if 2 strings are the same.
bool is_same_string(char const *s1, char const *s2);

// tests if 2 strings are the same, for n characters.
bool is_same_stringn(char const *s1, char const *s2, int n);

// tests if a string can be translated into an int.
bool is_num(const char *s);

// tests if a character is a letter
// (lowercase, or uppercase, depending on the boolean)
bool is_a_letter(char c, bool is_lower);

// tests if a string only contains alphabetic characters.
bool is_alphabetic(char *s);

// tests if a specific character is in a string.
int is_in_string(char const *s, char to_find);

// gets the substring after the last occurence of a character.
// useful for paths: /var/log/tello.log becomes tello.log if to_find == '/'
char *get_last_occurence_of(char *s, char to_find);

// appends a character to a string.
char *append_char(char *s, char c);

// displays a string to stdout.
void my_putstr(char const *s);

// displays a string to stderr.
void my_puterr(char const *s);

// strips a string of trailing of leading to_strip characters.
// useful to remove trailing or leading spaces.
char *strip(char *line, char to_strip);

// removes double-spaces, trailing and leading spaces from a string.
char *clean_line(char *line);

// transforms tabs into spaces.
char *remove_tabs(char *line);

// tests if a string can be converted to a float.
bool is_float(char const *s);


// swaps.c

//swaps 2 arrays.
void swap_array(void **one, void **two);

// swaps 2 characters.
void swapc(char *one, char *two);

// swaps 2 ints.
void swap(int *one, int *two);

// arrays.c

// frees a 2dimentionnal array.
void free_array(void **array);

// generated a 2dimentionnal array, based on a string.
// splits it every time it finds a separator.
char **tabgen(char const *str, char separator);

// displays a 2dimentionnal array.
void display_tab(char const **tab);

// appends a line to a 2dimentionnal array.
char **append_line_to_tab(char **tab, char *line);

// gets the length of a 2dimentionnal array.
int my_tablen(char const **tab);


// nums.c

// executes a specific operation, depending on the sign.
int do_op(int first_nb, int second_nb, char sign);

// gets the length of a number, in numbers of characters.
// doesn't count the - character.
int my_nblen(int nb);

// transforms an int into whatever base you want.
// useful for addresses.
char *my_getnbr_base(int nb, const char *base_to);

// displays a number into whatever base you want.
// useful for addresses.
void my_putnbr_base(int nb, char const *base_to);


// get_next_line.c

// reads the next line from a file.
char *get_next_line(int fd);

#endif //TELLO_UTILS_H
