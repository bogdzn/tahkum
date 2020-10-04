//
// Created by bogdan on 01/10/2020.
//

#include "parser.h"
#include "utils.h"
#include "socket.h"
#include <criterion/criterion.h>
#include <criterion/redirect.h>


settings_t set_test_settings(void)
{
    settings_t settings = {
        .max_timeout = 2,
        .sleep_time = 2,
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

Test(is_drone_ok, isdroneok)
{
    cr_assert_eq(is_drone_ok("17%"), true);
    cr_assert_eq(is_drone_ok("ok"), true);
    cr_assert_eq(is_drone_ok("error whatever"), false);
}

