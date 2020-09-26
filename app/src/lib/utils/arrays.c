//
// Created by bogdan on 21/09/2020.
//

#include "./utils.h"
#include <string.h>
#include <stdlib.h>

void free_array(void **array)
{
	if (array == (void *) 0)
		return;
	for (int i = 0; array[i] != (void *) 0; i++)
		free(array[i]);
	free(array);
}

int my_tablen(char const **tab)
{
	int result = 0;

	if (tab == (void *) 0 || tab[0] == (void *) 0)
		return (0);
	for (; tab[result] && tab[result] != (void *) 0; result++);
	return (result);
}

static int get_nb_cols(const char *str, int n, char separator)
{
	int i = n;
	int res = 0;

	if (str == NULL || str[0] == '\0')
		return 0;
	for (; str[i] != '\0' && str[i] != separator; i++, res++);
	return (res);
}

static int get_nb_rows(const char *str, char separator)
{
	int i;
	int res = 0;

	if (str == NULL || str[0] == '\0')
		return 0;
	if (str == NULL || str[0] == '\0')
		return (0);
	for (i = 0; str[i] != '\0'; i++)
		if (str[i] == separator)
			res++;
	return (res + 1);
}

char **tabgen(const char *str, char separator)
{
	int i = 0;
	int mem_size = 0;
	int index_str = 0;
	char **res = NULL;

	if (str == NULL || str[0] == '\0')
		return NULL;
	res = malloc(sizeof(char *) * (get_nb_rows(str, separator) + 1));
	if (res == NULL)
		return NULL;
	for (; i < get_nb_rows(str, separator); i++) {
		mem_size = get_nb_cols(str, index_str, separator);
		res[i] = malloc(sizeof(char) * (mem_size + 1));
		if (res[i] == NULL)
			return NULL;
		res[i] = my_strncpy(res[i], &str[index_str], mem_size);
		index_str = index_str + mem_size + 1;
	}
	res[i] = NULL;
	return (res);
}

void display_tab(char const **tab)
{
	if (tab == NULL || tab[0] == NULL || tab[0][0] == '\0')
		return;
	for (int i = 0; tab[i] != NULL; i++)
		my_putstr(tab[i]);
}

char **append_line_to_tab(char **tab, char *line)
{
	char **new_tab = NULL;
	int i = 0;

	if (tab == NULL) {
		if (line == NULL)
			return NULL;
		new_tab = malloc(sizeof(char *) * 2);
		new_tab[0] = my_strdup(line);
		new_tab[1] = NULL;
		return new_tab;
	} else if (line == NULL)
		return tab;
	new_tab = malloc(sizeof(char *) * (my_tablen((char const **) tab) + 1));
	for (; tab[i] != NULL; i++)
		new_tab[i] = my_strdup(tab[i]);
	new_tab[i] = my_strdup(line);
	new_tab[i + 1] = NULL;
	return new_tab;
}