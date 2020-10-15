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
#include <string.h>

settings_t check_supported_api(socket_t ryze, settings_t settings)
{
    char *drone_answer = NULL;

    send_command(ryze, "sdk?", settings);
    drone_answer = get_response(ryze, settings);
    if (!is_drone_ok(drone_answer)) {
        free(drone_answer);
        settings.is_newer_api = false;
        __log(WARNING, "THIS DRONE ONLY SUPPORTS AN OLDER SDK VERSION.\n");
        __log(WARNING, "Please check for a firmware update if you want to enjoy all features.\n");
        return settings;
    } else __log(INFO, "SDK VERSION: %s.\n", drone_answer);
    send_command(ryze, "sn?", settings);
    free(drone_answer);
    __log(INFO, "SERIAL NUMBER:%S\n", get_response(ryze, settings));
    settings.is_newer_api = true;
    return settings;
}

settings_t send_startup_commands(socket_t ryze, settings_t settings)
{
    send_command(ryze, "command", settings);
    if (strcmp(str_to_lower(get_response(ryze, settings)), "ok") != 0) {
        __log(ERROR, "drone returned an error.\n");
        set_keyboard_mode();
        exit(1);
    } else return check_supported_api(ryze, settings);
}

bool is_drone_ok(char *response)
{
    char **tab = NULL;
    bool result = false;

    if (response == NULL)
        return false;
    tab = tabgen(response, ' ');
    result = (strcmp("error", str_to_lower(tab[0])) == 0);
    free_array((void **)tab);
    return !result;
}

int exec_loop(socket_t ryze, settings_t settings, char **cmds)
{
    int status = 0;
    char *drone_response = NULL;


    for (int i = 0; cmds[i] && status == 0; i++) {
        for (int retry = 0; retry < settings.max_retries; retry++) {
            send_command(ryze, cmds[i], settings);
            drone_response = get_response(ryze, settings);
            if (is_drone_ok(drone_response))
                break;
            __log(WARNING, "command %[s] failed...Retrying [%i/%i]\n", cmds[i],
                    retry, settings.max_retries);
            if (retry + 1 >= settings.max_retries) {
                __log(ERROR, "command [%s] timed out, exiting...");
                return -1;
            }
        }
        sleep(settings.wait);
    }
    free_array((void **)cmds);
    return 0;
}
