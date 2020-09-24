//
// Created by bogdan on 23/09/2020.
//

#include "./../utils.h"
#include <criterion/criterion.h>
#include <criterion/redirect.h>

//todo fix munmap_chunk():invalid pointer
/*Test(get_file, filehandler)
{
	file_t valid = get_file("./Makefile");
	file_t invalid = get_file("fortnite");

	cr_assert_str_eq(valid.name, "Makefile");
	destroy_file(valid);
	cr_assert_eq(invalid.name, 0);
}*/