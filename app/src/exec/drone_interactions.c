/**
 * \\file messages.c
 * \brief reads and writes messages.
 * \author Bogdan G.
 * \date 28/09/2020
 */

#include "exec.h"
#include "utils.h"
#include <stdlib.h>
#include <errno.h>

void send_command(socket_t sock, char const *data, settings_t settings)
{
    unsigned int socklen = 0;

    if (settings.fake_socket) {
        __log(INFO, "(debug) sending [%s].\n", data);
        return;
    }
    socklen = sizeof(sock.drone_addr);
    __log(INFO, "sending \"%s\"\n", data);
    sendto(sock.socket, data, my_strlen(data),0, (struct sockaddr *) &sock.drone_addr, socklen);
    log_if_errno(errno, "sendto");
}

char *get_response(socket_t sock, settings_t settings)
{
    char *reply = NULL;
    unsigned int socklen = sizeof(sock.drone_addr);
    int msg_size = 0;

    if (settings.fake_socket) {
        __log(INFO, "(debug) received \"OK\".\n");
        return my_strdup("OK");
    }
    __log(INFO, "waiting for a message ...\n");
    reply = malloc(sizeof(char) * (REPLY_SIZE + 1));
    msg_size = recvfrom(sock.socket, reply, REPLY_SIZE, 0,
            (struct sockaddr *) &sock.drone_addr,&socklen);

    log_if_errno(errno, "recvfrom");
    if (msg_size == -1 || reply == NULL) {
        __log(ERROR, "empty message.\n");
        return NULL;
    } else reply[msg_size] = 0;
    reply[msg_size - 1] = (reply[msg_size - 1] == '\n') ? 0 : reply[msg_size - 1];
    __log(INFO, "received [%s]\n", reply);
    return reply;
}
