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
    __log(INFO, "SERIAL NUMBER:%s\n", get_response(ryze, settings));
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
    send_command(ryze, "rc 0 0 0 0", settings);
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
    int status = 0;
    char *drone_response = NULL;

    settings.max_retries = DEFAULT_MAX_RETRIES;
    for (int i = 0; cmds[i] && status == 0; i++) {
        for (int retry = 0; retry < settings.max_retries; retry++) {
            send_command(ryze, cmds[i], settings);
            drone_response = get_response(ryze, settings);
            if (is_drone_ok(drone_response))
                break;
            __log(WARNING, "command %[s] failed...\n", cmds[i]);
            if (retry + 1 >= settings.max_retries) {
                __log(ERROR, "command [%s] timed out, Exiting...");
                return -1;
            }
        }
        sleep(settings.wait);
    }
    free_array((void **)cmds);
    return 0;
}

static char get_keycode(void)
{
    char result = 0;
    int status = read(STDIN_FILENO, &result, 1);

    usleep(50000);
    return (status == -1) ? get_keycode() : result;
}

int loop_wrapper(socket_t ryze, settings_t settings)
{
    if (set_keyboard_mode() == -1) {
        __log(ERROR, "Couldn't set terminal in raw mode.\n");
        return 0;
    } else settings = send_startup_commands(ryze, settings);

    for (char buffer = 0 ;; buffer = tolower(get_keycode())) {
        if (buffer == 'c') {
            send_command(ryze, "land", settings);
            __log(WARNING, "c has been triggered. Exiting.\n");
            break;
        }
        exec_loop(ryze, settings, get_user_commands(buffer, settings.is_newer_api));
    }
    return set_keyboard_mode();
}
