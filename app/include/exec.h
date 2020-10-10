/**
 * \file exec.h
 * \brief all things related to command execution, such as sockets, or the exec loop.
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

/// Local port
#ifndef LOCAL_PORT
#define LOCAL_PORT (3000)
#endif

/**
 * \typedef struct socket_s socket_t
 * \brief holds any relevant information regarding socket creation.
 * \param drone_port port where the drone sends data.
 * \param local_port port where the drone expects data.
 * \param drone_ip ip address for the drone.
 * \param local_ip ip address where the drone sends data.
 * \param socket the actual socket.
 * \param drone_addr drone address wrapped in a struct sockaddr_in.
 * \param local_addr local address wrapped in a struct sockaddr_in.
 */
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
 * \fn socket_t create_default_socket(settings_t user_settings)
 * \\brief creates the socket needed to control the drone
 *
 * \param user_settings settings, used to check if we are in debug mode
 * \return a structure with a socket and relevant information
 */
socket_t create_default_socket(settings_t user_settings);

/**
 * \fn void close_socket(socket_t sock, settings_t settings)
 * \\brief closes a socket
 *
 * \param sock your socket
 * \param settings user settings, used to check if we're in debug mode
 */
void close_socket(socket_t sock, settings_t settings);

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
 * \fn int exec_loop(socket_t ryze, instr_t *instructions, settings_t settings)
 * \brief loops through instructions and sends them to the drone
 *
 * \param ryze structure containing all relevant connection information
 * \param instructions user-specified insctructions
 * \param settings user settings
 * \param cmds user-extracted commands
 * \return 0 if successfull, -1 if fails
 */
int exec_loop(socket_t ryze, settings_t settings, char **cmds);

/**
 * \fn bool is_drone_ok(char *response)
 * \\brief tests drone's response.
 *
 * \param response the drone's answer.
 * \return true if contains "OK"
 */
bool is_drone_ok(char *response);

// key_listener.c
/**
  * \fn int loop_wrapper(socket_t ryze, settings_t settings)
  * \brief wraps around exec_loop, sets the tty in raw_mode and read keyboard input
  *
  * \param ryze socket containing ryze data
  * \param settings user settings
  * \return 0 if successfull
  */
int loop_wrapper(socket_t ryze, settings_t settings);

#endif //TELLIB_SOCKET_H
