/**
 * \file socket_handler.c
 * \brief minimalistic socket handler.
 * \author Bogdan G.
 * \date 28/09/2020
 */

#include "socket.h"
#include "logger.h"
#include "utils.h"
#include <errno.h>

socket_t create_socket(char const *ip_addr, int port)
{
    __log(INFO, "creating socket for address %s:%i\n", ip_addr, port);

    socket_t result = {
            .port = port,
            .ip_addr = my_strdup(ip_addr),
            .socket = socket(AF_INET, SOCK_STREAM, 0),
            .addr = {
                    .sin_addr.s_addr = inet_addr(ip_addr),
                    .sin_port = htons(port),
                    .sin_family = AF_INET
            },
            .status = connect(
                    result.socket,
                    (struct sockaddr *) &result.addr,
                    sizeof(result.addr)
            )
    };

    log_if_errno(errno, "create_socket");
    bind(result.socket, (struct sockaddr *) &result.addr, sizeof(result.addr));
    if (result.status > 0 || is_socket_ok(result))
        __log(INFO, "Connected.\n");
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
    return (sock.status != -1 || sock.socket != -1);
}
