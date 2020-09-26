#ifndef PARSER_H
#define PARSER_H

#ifndef F_LOADING_FILE
#define F_LOADING_FILE 111
#endif

#ifndef F_INVALID_CMD_FILE
#define F_INVALID_CMD_FILE 112
#endif

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
    {1, "take off",         0, NULL},
    {2, "delay",            1, {"time",     [sizeof(int),   -1]}},
    {3, "sleep until",      1, {"time",     [sizeof(float), -1]}},
    {4, "move foreward",    0, NULL},
    {5, "turn lattitude at",1, {"degrees",  [sizeof(float), -1]}},
    {6, "turn longitude at",1, {"degrees",  [sizeof(float), -1]}},
    {7, "land",             0, NULL},
    {8, "end",              0, NULL},
    {0, NULL,               0, NULL}
};

#endif