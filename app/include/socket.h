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

/**
 * \fn socket_t create_default_socket(settings_t user_settings)
 * \\brief creates the socket needed to control the drone
 *
 * \param user_settings settings, used to check if we are in debug mode
 * \return a structure with a socket and relevant information
 */
socket_t create_default_socket(settings_t user_settings);

/**
 * \fn void close_socket(socket_t sock)
 * \\brief closes a socket
 *
 * \param sock your socket
 */
void close_socket(socket_t sock);

/**
 * \fn socket_t create_socket(char **ips, int *ports, settings_t settings)
 * \\brief creates a SOCK_DGRAM socket, and adds relevant information
 *
 * \param ips two valid ip addresses
 * \param ports two valid ports
 * \param settings user settings, used to check if we're in debug mode
 * \return  a structure with a socket and relevant information
 */
socket_t create_socket(char **ips, int *ports, settings_t settings);

/**
 * \fn bool is_socket_ok(socket_t socket)
 * \\brief tests socket status.
 *
 * \param socket your sock.
 * \return a boolean
 */
bool is_socket_ok(socket_t socket);

// messages.c
/**
 * \fn char *get_response(socket_t sock, settings_t settings)
 * \\brief gets a message from the drone
 *
 * \param sock a structure containing the drone's address
 * \param settings user settings, used to check if we're in debug mode
 * \return the string the drone sent us
 */
char *get_response(socket_t sock, settings_t settings);

/**
 * \fn void send_command(socket_t sock, char const *data, settings_t settings)
 * \\brief sends a message to the drone.
 *
 * \param sock a structure containing the drone's address
 * \param data your message
 * \param settings user settings, used to check if we're in debug mode
 */
void send_command(socket_t sock, char const *data, settings_t settings);

// exec_loop.c

/**
 * \fn void exec_loop(socket_t ryze, instr_t *instructions, settings_t settings)
 * \\brief loops through instructions and sends them to the drone
 *
 * \param ryze structure containing all relevant connection information
 * \param instructions user-specified insctructions
 * \param settings user settings
 */
void exec_loop(socket_t ryze, instr_t *instructions, settings_t settings);

#endif //TELLIB_SOCKET_H
