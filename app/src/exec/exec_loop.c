/**
 * \file exec_loop.c
 * \brief handles command execution.
 * \author Bogdan G.
 * \version 0.2
 * \date 18/10/2020
 */

#include "../../include/utils.h"
#include "../../include/exec.h"
#include "../../include/parser.h"
#include <string.h>
#include <unistd.h>
#include <ctype.h>

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
    drone_answer = get_response(ryze, settings);
    __log(INFO, "SERIAL NUMBER:%s\n", drone_answer);
    free(drone_answer);
    settings.is_newer_api = true;
    return settings;
}

settings_t send_startup_commands(socket_t ryze, settings_t settings)
{
    char *answer = NULL;

    send_command(ryze, "command", settings);
    answer = get_response(ryze, settings);
    if (strcmp(str_to_lower(answer), "ok") != 0) {
        __log(ERROR, "drone returned an error.\n");
        set_keyboard_mode();
        free(answer);
        exit(1);
    }
    free(answer);
    send_command(ryze, "speed 50", settings);
    return check_supported_api(ryze, settings);
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
    char *answer = NULL;

    for (int retry = 0; retry < settings.max_retries; retry++) {
        send_command(ryze, cmds[0], settings);
        answer = get_response(ryze, settings);
        if (is_drone_ok(answer))
            break;
        else {
            __log(WARNING, "command %[s] failed...\n", cmds[0]);
            sleep(settings.wait);
        }
    }
    free(answer);
    free_array((void **)cmds);
    return 0;
}

