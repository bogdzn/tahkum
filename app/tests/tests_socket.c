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
