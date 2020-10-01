//
// Created by bogdan on 01/10/2020.
//

#include "utils.h"
#include "socket.h"
#include <criterion/criterion.h>
#include <criterion/redirect.h>

Test(create_socket, creating_socket)
{
    socket_t basic_socket = create_socket("127.0.1.1", 2499);

    cr_assert_str_eq(basic_socket.ip_addr, "127.0.1.1");
    cr_assert_eq(basic_socket.port, 2499);

    close_socket(basic_socket);
}

Test(is_socket_ok, issockok)
{
    socket_t basic_socket = create_socket("127.0.1.1", 2800);

    cr_assert_eq(is_socket_ok(basic_socket), false);
    close_socket(basic_socket);
}
