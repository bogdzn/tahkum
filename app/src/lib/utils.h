//
// Created by bogdan on 21/09/2020.
//

#ifndef TELLO_UTILS_H
#define TELLO_UTILS_H

// file_handler.c
typedef struct file_s
{
	char *name;
	char *content;
	struct stat st;
} file_t;

file_t get_file(char const *filepath);

void destroy_file(file_t file);


// strings.c
int my_strlen(char const *s);

char *my_strdup(char const *s);

char *my_strcat(char const *s1, char const *s2);

char *my_itoa(int nb);

char *set_to_lowercase(char *s);

char *set_to_uppercase(char *s);

char *my_revstr(char *dest, char const *src);

char *my_strncpy(char *dest, char const *src, int n);

bool is_same_string(char const *s1, char const *s2);

bool is_same_stringn(char const *s1, char const *s2, int n);

bool is_num(const char *s);

bool is_a_letter(char c, bool is_lower);

bool is_alphabetic(char *s);

bool is_in_string(char const *s, char to_find);

char *get_last_occurence_of(char *s, char to_find);

char *append_char(char *s, char c);

void my_putstr(char const *s);

void my_puterr(char const *s);


// swaps.c
void swap_array(void **one, void **two);

void swapc(char *one, char *two);

char swap(int *one, int *two);

// arrays.c
void free_array(void **array);

char **tabgen(char const *str, char separator);

void display_tab(char const **tab);


// nums.c
int do_op(int first_nb, int second_nb, char sign);

int my_nblen(int nb);

char *my_getnbr_base(int nb, const char *base_to);

void my_putnbr_base(int nb, char const *base_to);


// get_next_line.c
char *get_next_line(int fd);

#endif //TELLO_UTILS_H