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

socket_t create_default_socket(void);

bool is_socket_ok(socket_t sock);

#endif //TELLIB_SOCKET_H
