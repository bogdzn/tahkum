#ifndef PARSER_H
#define PARSER_H

#ifndef F_LOADING_FILE
#define F_LOADING_FILE 111
#endif

#ifndef F_INVALID_CMD_FILE
#define F_INVALID_CMD_FILE 112
#endif

#include <stdbool.h>
#include "./../src/lib/utils/utils.h"

typedef struct input_file {
    char **instructions;
    int len;
}input_file_t;

typedef struct param
{
    char *desc;
    int *size;
}param_t;

typedef struct cmd_list
{
    int instruction_id;
    char *cmd;
    int nb_param;
    param_t params;
} cmd_list_t;

typedef struct instr instr_t;
struct instr_t {
    int id;
    float *params;
    instr_t *next;
};

const cmd_list_t USER_CMD[] = {
    {0, "start",            0, NULL},
    {1, "takeoff",          0, NULL},
    {2, "delay",            1, {"time",     (int *){sizeof(float), -1}}},
    {3, "sleep",      	    1, {"time",     (int *){sizeof(float), -1}}},
    {4, "foreward",    	    0, NULL},
    {5, "lattitude",	    1, {"degrees",  (int *){sizeof(float), -1}}},
    {6, "longitude",        1, {"degrees",  (int *){sizeof(float), -1}}},
    {7, "land",             0, NULL},
    {8, "end",              0, NULL},
    {0, NULL,               0, NULL}
};


// get_instr_queue.c
instr_t *init_instr(void);
instr_t *fill_instruction(char *instr);
instr_t *get_instructions_queue(char *filename);

//get_instr_from_file.c
input_file_t parse(char const *filepath);
int get_instr_id(char *instr);
char **crop_from_start(char **tab);
char **clean_file(char *file);
bool check_if_cmd_exists(char **user_instructions);
bool check_param_type(char **line_instr, int idx);
bool check_parameters(char **user_instructions);
bool check_file(char **user_instructions);


#endif
