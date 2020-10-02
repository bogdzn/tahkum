/**
 * \file socket_handler.c
 * \brief minimalistic socket handler.
 * \author Bogdan G.
 * \date 01/10/2020
 */

#include "socket.h"
#include "logger.h"
#include "utils.h"
#include <errno.h>

static void close_if_errno(int err, int sock, char *func_name)
{
    if (err != 2 && errno != 0) {
        close(sock);
        log_if_errno(errno, func_name);
        _exit(1);
    }
}

socket_t create_socket(char const *ip_addr, int port)
{
    int sock_option = 1;
    socket_t result;

    __log(INFO, "creating socket for address %s:%i\n", ip_addr, port);
    result.port = (port < 0) ? RYZE_PORT : port;
    result.ip_addr = (!ip_addr) ? RYZE_IP_ADDR : my_strdup(ip_addr);
    result.socket = socket(AF_INET, SOCK_STREAM, 0);
    close_if_errno(errno, result.socket, "create socket");

    result.addr.sin_addr.s_addr = inet_addr(result.ip_addr);
    result.addr.sin_port = htons(result.port);
    result.addr.sin_family = AF_INET;
    result.status = connect(result.socket, (struct sockaddr *) &result.addr, sizeof(result.addr));
    close_if_errno(errno, result.socket, "connecting to socket");

    bind(result.socket, (struct sockaddr *) &result.addr, sizeof(result.addr));
    close_if_errno(errno, result.socket, "bind");

    setsockopt(result.socket, SOL_SOCKET, SO_REUSEADDR, &sock_option, sizeof(sock_option));
    close_if_errno(errno, result.socket, "setsockopt");

    if (is_socket_ok(result))
        __log(INFO, "Connected.\n");
    else __log(WARNING, "Couldn't connect socket to %s:%i.\n", result.ip_addr, result.port);

    return result;
}

inline socket_t create_default_socket(void)
{
    return create_socket(RYZE_IP_ADDR, RYZE_PORT);
}

void close_socket(socket_t sock)
{
    __log(INFO, "Closing socket %s:%i.\n", sock.ip_addr, sock.port);
    close(sock.socket);
    free(sock.ip_addr);
}

inline bool is_socket_ok(socket_t sock)
{
    return (sock.status != -1 && sock.socket != -1);
}
