#include <stdio.h>
#include <stdlib.h>
#include "./../../includes/parser.h"
#include "./../lib/utils/utils.h"
#include <stdbool.h>

input_file_t parse(char const *filepath)
{
    input_file_t parsed_file = NULL;
    file_t file = get_file(filepath);

    if (!file) {
        my_puterr("Error while loading the file. Retry with -h.");
        free(filepath);
        exit(F_LOADING_FILE);
    }
    parsed_file.instructions = clean_file(file.content);
    parsed_file.len = tab_len(parsed_file.instructions);
    if (!check_file(parsed_file.instructions)) {
        destroy_file(file);
        free_array(parsed_file.instructions);
        free(filepath);
        exit(F_INVALID_CMD_FILE);
    }
    my_putstr("The file has been successfully downloaded.\n");
    free(filepath);
    return parsed_file;
}

int get_instr_id(char *instr)
{
    if (instr == NULL || instr[0] == 0)
        return -1;
    for (int j = 0; USER_CMD[j].cmd != NULL; j++)
        if (!is_same_stringn(instr, USER_CMD[j].cmd, my_strlen(USER_CMD[j].cmd)))
            return j;
    return -1;
}

char **crop_from_start(char **tab)
{
    if (!tab || !tab[0] || !tab[0][0])
        return NULL;
    for (int i = 0; tab[i] != NULL; i++) {
        if (!is_same_string("start", tab[i])) {
            return &tab[i];
        }
    }
    return NULL;
}

char **clean_file(char *file)
{
    char **cleaned_file = NULL;
    
    if (!file || !file[0])
        return NULL;
    cleaned_file = tabgen(file, '\n');
    cleaned_file = crop_from_start(cleaned_file);
    for (int i = 0; cleaned_file[i] != NULL; i++) {
        cleaned_file[i] = clean_line(cleaned_file[i]);
    }
    return cleaned_file;
}

bool check_if_cmd_exists(char **user_instructions)
{
    bool found = false;

    for (int i = 0; user_instructions[i] != NULL; i++) {
        if (get_instr_id(user_instructions[i]) == -1)
            return false;
        found = false;
    }
    return true;
}

bool check_param_type(char **line_instr, int idx)
{
    int nb_params = USER_CMD[idx].nb_param;

    for (int i = 0; i < nb_params; i++) {
        if (!line_instr[i])
            return false;
        if (USER_CMD[idx].size[i] == sizeof(int))
            if (!is_num(line_instr[i]))
                return false;
        if (USER_CMD[idx].size[i] == sizeof(float))
            if (!is_float(line_instr[i]))
                return false;
    }
    return true;
}

bool check_parameters(char **user_instructions)
{
    char **line_instr = NULL;
    bool right_param = true;
    int nb_params = 0;
    int id = 0;

    for (int i = 0; user_instructions[i] != NULL; i++) {
        id = get_instr_id(user_instructions[i]);
        line_instr = tabgen(user_instructions[i], ' ');
        nb_params = USER_CMD[id].nb_param;
        if (tab_len(line_instr) - 1 != nb_params) {
            right_param = false;
                break;
        }
        if (!check_param_type(&line_instr[1], id)) {
            right_param = false;
            break;
        }
    }
    free_array((void **)line_instr);
    return right_param;
}

bool check_file(char **user_instructions)
{
    if (!user_instructions || !user_instructions[0] || !user_instructions[0][0])
        return false;
    if (!check_if_cmd_exists(user_instructions))
        return false;
    if (!check_parameters(user_instructions))
        return false;
    return true;
}