//
// Created by bogdan on 23/09/2020.
//

#include "../../utils.h"
#include <criterion/critetion.h>
#include <criterion/redirect.h>

Test(get_next_line, test_gnl_failure)
{
	int fd = open("fortnite", O_RDONLY);

	cr_assert_eq(get_next_line(fd), 0);
	close(fd);
}

Test(get_next_line, test_gnl)
{
	// todo change that with the start of the root Makefile

	int fd = open("Makefile", O_RDONLY);

	cr_assert_str_eq(get_next_line(fd), "##");
	cr_assert_str_eq(get_next_line(fd), "## EPITECH PROJECT, 2019");
	cr_assert_str_eq(get_next_line(fd), "## Makefile");
	cr_assert_str_eq(get_next_line(fd), "## File description:");
	cr_assert_str_eq(get_next_line(fd), "## Makefile");
	cr_assert_str_eq(get_next_line(fd), "##");
	close(fd);
}

