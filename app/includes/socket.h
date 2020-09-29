/**
 * \file socket.h
 * \brief all things related to socket handling.
 * \author Bogdan G.
 * \date 28/09/2020
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
#include <stdbool.h>

/// Reply size defines the max size of an expected reply.
#ifndef REPLY_SIZE
#define REPLY_SIZE (2000)
#endif

/// Drone's configured IP address.
#ifndef RYZE_IP_ADDR
#define RYZE_IP_ADDR ("192.168.10.1")
#endif

/// Port on which the drone listens.
#ifndef RYZE_PORT
#define RYZE_PORT (8899)
#endif

/**
 * \struct socket_t
 * \brief holds a socket, its status and a sockaddr_in.
 */
typedef struct sckt_s
{
    char *ip_addr; /*!< socket's ip address. */
    int port; /*!< socket's configured port. */
    int status; /*!< socket's current status. */
    struct sockaddr_in addr; /*!< socket's address info. */
    int socket; /*!< the actual socket. */
} socket_t;

// socket_handler.c

/**
 * \fn socket_t create_socket(char const *ip_addr, int port)
 * \\brief loads a socket_t struct into memory, binded to specified address and port.
 * The ip_addr has to be IPV4, as the socket is set to AF_INET.
 *
 * \return a socket_t instance.
 */
socket_t create_socket(char const *ip_addr, int port);

/**
 * \fn socket_t create_default_socket(void)
 * \\brief calls `create_socket()` with RYZE_IP_ADDR and RYZE_PORT as parameters.
 *
 * \return a socket_t structure filled with default params.
 */
socket_t create_default_socket(void);

/**
 * \fn bool is_socket_ok(socket_t sock)
 * \\brief checks if status and socket are not equal to -1.
 *
 * \return a boolean.
 */
bool is_socket_ok(socket_t sock);

/**
 * \fn void close_socket(socket_t sock)
 * \\brief closes sock.socket.
 *
 * \param sock your socket.
 */
void close_socket(socket_t sock);

#endif //TELLIB_SOCKET_H
