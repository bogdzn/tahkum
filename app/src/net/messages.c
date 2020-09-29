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

void send_data(socket_t sock, char const *data)
{
    __log(INFO, "sending:%s\n", data);
    send(sock.socket, data, my_strlen(data), 0);
    log_if_errno(errno, "send_data");
}

char *get_data(socket_t sock)
{
    char *reply = malloc(sizeof(char) * (REPLY_SIZE + 1));
    int msg_size = 0;

    msg_size = recv(sock.socket, reply, REPLY_SIZE, 0);
    if (msg_size == -1 || reply == NULL) {
        __log(ERROR, "message reception failed.\n");
        return NULL;
    } else reply[msg_size] = 0;
    __log(INFO, "received:%s\n", reply);
    return reply;
}