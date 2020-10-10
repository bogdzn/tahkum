/**
 * \file socket_handler.c
 * \brief minimalistic socket handler.
 * \author Bogdan G.
 * \date 01/10/2020
 */

#include "socket.h"
#include "utils.h"
#include <string.h>
#include "parser.h"
#include <errno.h>

static void close_if_errno(int socket, int err, char *func_name)
{
    if (err != 2 && errno != 0) {
        close(socket);
        log_if_errno(errno, func_name);
        _exit(1);
    } else __log(INFO, "success for [%s].\n", func_name);
}

static socket_t load_initial_data(char **ip, int *port)
{
    socket_t sock;

    __log(INFO, "creating socket for address %s:%i\n", ip[0], port[0]);
    sock.local_port = port[0];
    sock.local_ip = my_strdup(ip[0]);
    sock.drone_port = port[1];
    sock.drone_ip = my_strdup(ip[1]);
    return sock;
}

static struct sockaddr_in create_addr(char *ip, int port)
{
    struct sockaddr_in s;

    if (is_same_string(LOCAL_IP_ADDR, ip)) {
        s.sin_addr.s_addr = htonl(INADDR_ANY);
    } else s.sin_addr.s_addr = inet_addr(ip);
    s.sin_port = htons(port);
    s.sin_family = AF_INET;
    return s;
}

socket_t create_socket(char **ips, int *ports, settings_t settings)
{
    socket_t sock;

    if (settings.fake_socket) {
        __log(INFO, "(debug) creating socket for [%s:%i].\n", ips[0], ports[0]);
        return sock;
    }
    sock = load_initial_data(ips, ports);
    sock.local_addr = create_addr(sock.local_ip, sock.local_port);
    sock.drone_addr = create_addr(sock.drone_ip, sock.drone_port);
    sock.socket = socket(AF_INET, SOCK_DGRAM, 0);
    close_if_errno(sock.socket, errno, "create_socket");
    bind(sock.socket, (struct sockaddr *) &sock.local_addr, sizeof(sock.local_addr));
    close_if_errno(errno, sock.socket, "bind");
    return sock;
}

socket_t create_default_socket(settings_t settings)
{
    char *ip[2] = { LOCAL_IP_ADDR, RYZE_IP_ADDR };
    int ports[2] = { LOCAL_PORT, RYZE_PORT };

    return create_socket(ip, ports, settings);
}

bool is_socket_ok(socket_t socket)
{
    return (socket.socket == 0);
}

void close_socket(socket_t sock, settings_t settings)
{
    if (settings.fake_socket) {
        __log(INFO, "(debug) closing socket.\n");
        return;
    }
    __log(INFO, "closing socket on address [%s:%i]\n", sock.local_ip, sock.local_port);
    free(sock.drone_ip);
    free(sock.local_ip);
    close(sock.socket);
}
