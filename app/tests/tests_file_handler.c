//
// Created by bogdan on 23/09/2020.
//

#include "utils.h"
#include "parser.h"
#include <criterion/criterion.h>
#include <criterion/redirect.h>

Test(get_file, filehandler)
{
	file_t valid = get_file("./Makefile");
	file_t invalid = get_file("fortnite");

	cr_assert_str_eq(valid.name, "Makefile");
	cr_assert_eq(invalid.name, 0);
}
