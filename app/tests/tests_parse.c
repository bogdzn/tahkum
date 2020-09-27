#include <stdio.h>
#include <stdlib.h>
#include "./../includes/parser.h"
#include "./../src/lib/utils/utils.h"
#include <stdbool.h>
#include <criterion/criterion.h>

Test(parse, test_if_parse)
{

}

Test(get_instr_id, test_get_instr_id)
{
    char *test = strdup('start');
    char *wrong = strdup("doesnotexists");
    char *wrong_2 = NULL;

    cr_assert_eq(get_instr_id(test), 0);
    cr_assert_eq(get_instr_id(wrong), -1);
    cr_assert_eq(get_instr_id(wrong_2), -1);
}

Test(crop_from_start, test_crop_from_start)
{
    char **test = tabgen(strdup("this a start test"), ' ');
    char *ptr = test[2];
    char **wrong = tabgen(strdup("world cup"), ' ');

    cr_assert_eq(crop_from_start(test), ptr);
    cr_assert_eq(crop_from_start(wrong), 0);
    cr_assert_eq(crop_from_start(NULL), 0);
}

Test(clean_file, test_if_clean_file)
{
    char *test = strdup('b b b b b    \nb fezkjfejf   fbb \nstart\nend');
    char **output = clean_file(test);
    char *wrong = strdup(" ");
    char **output_2 = clean_file(wrong);

    cr_assert_str_eq(output[0], "start");
    cr_assert_str_eq(output[1], "end");
    cr_assert_eq(output_2, 0);
    cr_assert_eq(clean_file(NULL), 0);
}

Test(check_if_command_exists, test_check_if_command_exists)
{
    //do the exact same job as get_instruction_id
}

Test(check_param_type, check_if_param_type)
{
    char **test = tabgen(strdup('sleep 5'), ' ');
    char **wrong = tabgen(strdup('sleep a'), ' ');
    char **noparam = tabgen(strdup('takeoff', ' '));
    char **float_param = tabgen(strdup('longitude 45,6'));

    cr_assert_eq(check_if_param_type(test, 3), true);
    cr_assert_eq(check_if_param_type(wrong, 3), false);
    cr_assert_eq(check_if_param_type(noparam, 1), true);
    cr_assert_eq(check_if_param_type(float_param, 6), true);
}

Test(check_parameters, test_check_parameters)
{
    char **test = tabgen(strdup('start/sleep 5'), '/');
    char **wrong = tabgen(strdup('start sleep'), ' ');

    cr_assert_eq(check_parameters(test), true);
    cr_assert_eq(check_parameters(wrong), false);
}

Test(check_file, test_check_file)
{
    char **correct_file = tabgen(strdup('start/sleep 3/lattitude 45,_end'), '/');
    char **incorrect_file = tabgen(strdup('blablacar'), ' ');
    char **incorrect_file2 = tabgen(strdup('start/sleep ouhiuuo'));

    cr_assert_eq(check_file(correct_file), true);
    cr_assert_eq(check_file(incorrect_file), false);
    cr_assert_eq(check_file(incorrect_file2), false);
    cr_assert_eq(check_file(NULL), false);
}

Test(init_instr, test_init_instr)
{
    instr_t *test = init_instr();

    cr_assert_eq(test->id, 0);
    cr_assert_eq(test->previous, 0);
    cr_assert_eq(test->next, 0);
}

Test(fill_instruction, test_fill_instructions)
{
    char *test = strdup('sleep 5');
    instr_t *instr = fill_instruction(test);

    cr_assert_eq(instr->id, 3);
    cr_assert_eq(instr->params, 5);
}

Test(get_instructions_queue, test_get_instructions_queue)
{
    // to do 
}
