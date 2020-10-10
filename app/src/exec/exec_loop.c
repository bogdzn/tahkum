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

int exec_loop(socket_t ryze, settings_t settings, char **cmds)
{
    int status = 0;
    char *drone_response = NULL;


    for (int i = 0; cmds[i] && status == 0; i++) {
        for (int timeout = 0; timeout < settings.max_timeout; timeout++) {
            send_command(ryze, cmds[i], settings);
            drone_response = get_response(ryze, settings);
            if (is_drone_ok(drone_response))
                break;
            __log(WARNING, "command %[s] failed...Retrying [%i/%i]\n",
            cmds[i], timeout, settings.max_timeout);
            if (timeout + 1 == settings.max_timeout) {
                __log(ERROR, "command [%s] timed out, exiting...");
                return -1;
            }
        }
        sleep(settings.sleep_time);
    }
    free_array((void **)cmds);
    return 0;
}
