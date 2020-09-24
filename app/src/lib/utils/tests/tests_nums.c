//
// Created by bogdan on 23/09/2020.
//

#include "./../utils.h"
#include <criterion/critetion.h>
#include <criterion/redirect.h>

void redirect_all(void);

Test(my_getnbr_base, gnbase)
{
	cr_assert_str_eq(my_getnbr_base(12, "01234567"), "14");
	cr_assert_str_eq(my_getnbr_base(10, "01"), "1010");
	cr_assert_str_eq(my_getnbr_base(236, "0123456789abcdef"), "ec");
	cr_assert_str_eq(my_getnbr_base(12, "0123456789ABCDEF"), "C");
	cr_assert_eq(my_getnbr_base(12, (void *)0), 0);
}

Test(my_nblen, test_nb_len)
{
	cr_assert_eq(my_nblen(15), 2);
	cr_assert_eq(my_nblen(155), 3);
	cr_assert_eq(my_nblen(-12), 2);
	cr_assert_eq(my_nblen(0), 0);
}

Test(my_putnbr_base, testputnbrbase, .init = redirect_all)
{
	my_putnbr_base(12, "01234567");
	cr_assert_stdout_eq_str("14");
}

Test(do_op, doop)
{
	cr_assert_eq(do_op(5, 12, '+'), 17);
	cr_assert_eq(do_op(5, 17, '-'), -12);
	cr_assert_eq(do_op(3, 5, '*'), 15);
	cr_assert_eq(do_op(15, 3, '/'), 5);
	cr_assert_eq(do_op(12, 5, '%'), 2);
}