/**
 * \file exec_loop.c
 * \brief handles command execution.
 * \author Bogdan G.
 * \version 0.1
 * \date 02/10/2020
 */

#include "utils.h"
#include "exec.h"
#include "parser.h"

bool is_drone_ok(char *response)
{
    char **tab = NULL;
    bool result = false;

    if (response == NULL)
        return false;
    tab = tabgen(response, ' ');
    result = is_same_string("error", set_to_lowercase(tab[0]));
    free_array((void **)tab);
    return !result;
}

void exec_loop(socket_t ryze, settings_t settings)
{
    int status = 0;
    char *drone_response = NULL;

    send_command(ryze, "command", settings);
    if (!is_same_string(get_response(ryze, settings), "ok"))
        return;

    while (status == 0) {
        status = get_pressed_key();
        for (int timeout = 0; timeout < settings.max_timeout; timeout++) {

        }
        sleep(settings.sleep_time);
    }

}
