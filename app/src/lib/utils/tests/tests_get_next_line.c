//
// Created by bogdan on 23/09/2020.
//

#include "./../utils.h"
#include <criterion/critetion.h>
#include <criterion/redirect.h>

#include <fcntl.h>
#include <unistd.h>

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
	cr_assert_str_eq(get_next_line(fd), "## Bogdan G. // Adina C.");
	cr_assert_str_eq(get_next_line(fd), "##");
	close(fd);
}

