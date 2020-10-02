/**
 * \\file messages.c
 * \brief reads and writes messages.
 * \author Bogdan G.
 * \date 28/09/2020
 */

#include "socket.h"
#include "logger.h"
#include "utils.h"
#include <stdlib.h>
#include <errno.h>

void send_command(socket_t sock, char const *data)
{
    __log(INFO, "sending [%s]\n", data);
    send(sock.socket, data, my_strlen(data), 0);
    log_if_errno(errno, "send_command");
}

char *get_response(socket_t sock)
{
    char *reply = malloc(sizeof(char) * (REPLY_SIZE + 1));
    int msg_size =  recv(sock.socket, reply, REPLY_SIZE, 0);

    log_if_errno(errno, "get_response");
    if (msg_size == -1 || reply == NULL) {
        __log(ERROR, "message reception failed.\n");
        return NULL;
    } else reply[msg_size] = 0;
    __log(INFO, "received [%s]\n", reply);
    return reply;
}

bool is_drone_ok(char const *response)
{
    if (!is_same_string(response, "OK")) {
        __log(ERROR, "drone returned [%s]\n", response);
        return false;
    } else return true;
}