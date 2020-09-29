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
    __log(INFO, "creating socket for address [%s:%i]\n", ip_addr, port);

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
                    sizeof(result.add)
            )
    }

    log_if_errno(errno, "create_socket");
    bind(result.socket, (struct sockaddr *) &result.addr, sizeof(result.addr));
    if (result.status > 0 || is_socket_ok(result))
        __log(INFO, "Connected.\n");
    return result;
}

void send_data(socket_t sock, char const *data)
{
    __log(INFO, "sending:%s\n", data);
    send(sock.socket, data, my_strlen(data), 0);
    log_if_errno(errno, "send_data");
}

char *get_data(socket_t sock)
{
    char *reply = malloc(sizeof(char) * (REPLY_SIZE + 1));
    size_t msg_size = 0;

    msg_size = recv(sock.socket, reply, REPLY_SIZE, 0);
    if (msg_size == -1 || reply == NULL) {
        __log(ERROR, "message reception failed.\n");
        return NULL;
    } else reply[msg_size] = 0;
    __log(INFO, "received:%s\n", reply);
    return reply;
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
