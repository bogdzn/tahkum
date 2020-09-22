//
// Created by bogdan on 21/09/2020.
//

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "../utils.h"

static int get_size(char *s, char sep)
{
	int i = 0;

	if (s == NULL || s[0] == '\0')
		return (0);
	else if (sep == '\n' && s[0] == '\n')
		return (1);
	for (; s[i] != sep && s[i] != '\0'; i++);
	return (i);
}

static char *copy_until(char *s, char separator, int from)
{
	int size_malloc = 0;
	char *result = NULL;
	int i = 0;

	if (s == NULL || s[0] == '\0')
		return (NULL);
	size_malloc = get_size(&s[from], separator);
	if (size_malloc == 0)
		return (NULL);
	result = malloc(sizeof(char) * (size_malloc + 1));
	for (; i < size_malloc; i++, from++)
		result[i] = s[from];
	result[i - 1] = result[i - 1] == separator ? '\0' : result[i - 1];
	result[i] = '\0';
	return (result);
}

static char *concat_str(char *s1, char *s2)
{
	char *result;
	int i = 0;

	if (s1 == NULL || s1[0] == '\0')
		return (copy_until(s2, '\0', 0));
	else if (s2 == NULL || s2[0] == '\0')
		return (copy_until(s1, '\0', 0));
	result = malloc(sizeof(char) * (get_size(s1, 0) + get_size(s2, 0) + 1));
	for (; s1[i] != '\0'; i++)
		result[i] = s1[i];
	for (int j = 0; s2[j] != '\0'; j++, i++)
		result[i] = s2[j];
	result[i] = '\0';
	free(s1);
	return (result);
}

static bool rest_got_a_line(char *rest)
{
	if (rest == NULL || rest[0] == '\0')
		return (false);
	for (int i = 0; rest[i] != '\0'; i++)
		if (rest[i] == '\n')
			return (true);
	return (false);
}

char *get_next_line(int fd)
{
	static char *rest = NULL;
	char *buffer = malloc(sizeof(char) * (READ_SIZE + 1));
	char *res = NULL;

	if (fd == -1 || buffer == NULL)
		return (NULL);
	buffer[0] = '\0';
	for (int bzero = 0; !rest_got_a_line(rest);)
	{
		bzero = read(fd, buffer, READ_SIZE);
		if (bzero == -1 || bzero == 0)
			break;
		buffer[bzero] = '\0';
		rest = concat_str(rest, buffer);
	}
	free(buffer);
	res = copy_until(rest, '\n', 0);
	rest = copy_until(rest, '\0', get_size(res, '\0') + 1);
	return (res);
}
