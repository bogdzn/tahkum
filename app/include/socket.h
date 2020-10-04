/**
 * \file socket.h
 * \brief all things related to socket handling.
 * \author Bogdan G.
 * \date 01/10/2020
 */

#ifndef TELLIB_SOCKET_H
#define TELLIB_SOCKET_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include "parser.h"
#include <stdbool.h>

/// Reply size defines the max size of an expected reply.
#ifndef REPLY_SIZE
#define REPLY_SIZE (2000)
#endif

/// Local IP
#ifndef LOCAL_IP_ADDR
#define LOCAL_IP_ADDR ("0.0.0.0")
#endif

/// Drone's configured IP address.
#ifndef RYZE_IP_ADDR
#define RYZE_IP_ADDR ("192.168.10.1")
#endif

/// Port on which the drone listens.
#ifndef RYZE_PORT
#define RYZE_PORT (8889)
#endif

typedef struct socket_s
{
    int drone_port;
    int local_port;
    char *drone_ip;
    char *local_ip;
    int socket;
    struct sockaddr_in drone_addr;
    struct sockaddr_in local_addr;
} socket_t;


/**
 * \fn bool is_drone_ok(char const *response)
 * \\brief tests drone's response.
 *
 * \param response the drone's answer.
 * \return true if contains "OK"
 */
bool is_drone_ok(char const *response);

socket_t create_default_socket(settings_t user_settings);

void close_socket(socket_t sock);

socket_t create_socket(char **ips, int *ports, settings_t settings);

bool is_socket_ok(socket_t socket);

// messages.c

char *get_response(socket_t sock, settings_t settings);

void send_command(socket_t sock, char const *data, settings_t settings);

// exec_loop.c

void exec_loop(socket_t ryze, instr_t *instructions, settings_t settings);

#endif //TELLIB_SOCKET_H
