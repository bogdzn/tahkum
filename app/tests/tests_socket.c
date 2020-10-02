//
// Created by bogdan on 01/10/2020.
//

#include "utils.h"
#include "socket.h"
#include <criterion/criterion.h>
#include <criterion/redirect.h>

Test(is_socket_ok, issockok)
{
    socket_t basic_socket = {
        .ip_addr = my_strdup(RYZE_IP_ADDR),
        .port = RYZE_PORT,
        .status = 0,
        .socket = 0
    };

    socket_t evilsocket = {
        .ip_addr = my_strdup("looser"),
        .port = 6969,
        .status = -1,
        .socket = -1
    };

    cr_assert_eq(is_socket_ok(basic_socket), true);
    cr_assert_eq(is_socket_ok(evilsocket), false);
}
