//
// Created by bogdan on 01/10/2020.
//

#include "parser.h"
#include "utils.h"
#include "exec.h"
#include <criterion/criterion.h>
#include <criterion/redirect.h>

void redirect_all(void);

settings_t set_test_settings(void)
{
    settings_t settings = {
        .max_retries = 2,
        .wait = 2,
        .fake_socket = true,
        .filepath = NULL
    };

    return settings;
}

Test(is_socket_ok, issockok)
{
    socket_t basic_socket = {
        .local_port = RYZE_PORT,
        .drone_port = RYZE_PORT,
        .drone_ip = my_strdup(RYZE_IP_ADDR),
        .local_ip = my_strdup(LOCAL_IP_ADDR),
        .socket = 0,
    };

    socket_t evilsocket = {
        .drone_port = RYZE_PORT,
        .local_port = RYZE_PORT,
        .drone_ip = my_strdup(RYZE_IP_ADDR),
        .local_ip = my_strdup(LOCAL_IP_ADDR),
        .socket = -1,
    };

    cr_assert_eq(is_socket_ok(basic_socket), true);
    cr_assert_eq(is_socket_ok(evilsocket), false);
}

Test(get_response, mockresponse)
{
    settings_t set = set_test_settings();
    socket_t sock;

    cr_assert_str_eq(get_response(sock, set), "OK");
}

Test(send_command, mocksend, .init = redirect_all)
{
    settings_t set = set_test_settings();
    socket_t sock;

    send_command(sock, "message", set);
    cr_assert_stderr_eq_str("\033[0;36m[INFO]:\033[m (debug) sending [message].\n");
}

Test(is_drone_ok, isdroneok)
{
    cr_assert_eq(is_drone_ok("17%"), true);
    cr_assert_eq(is_drone_ok("ok"), true);
    cr_assert_eq(is_drone_ok("error whatever"), false);
}

Test(create_default_socket, fakesocket, .init = redirect_all)
{
    settings_t set = set_test_settings();
    socket_t sock = create_default_socket(set);

    cr_assert_stderr_eq_str("\033[0;36m[INFO]:\033[m (debug) creating socket for [0.0.0.0:3000].\n");
}

Test(close_socket, fakeclose, .init = redirect_all)
{
    settings_t set = set_test_settings();
    socket_t sock;

    close_socket(sock, set);
    cr_assert_stderr_eq_str("\033[0;36m[INFO]:\033[m (debug) closing socket.\n");

}
