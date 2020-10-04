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

void send_command(socket_t sock, char const *data, settings_t settings)
{
    unsigned int socklen = 0;

    if (settings.fake_socket) {
        __log(INFO, "(debug) sending [%s].\n", data);
        return;
    }
    socklen =sizeof(sock.drone_addr);
    __log(INFO, "sending \"%s\"\n", data);
    sendto(
            sock.socket,
            data,
            my_strlen(data),
            0,
            (struct sockaddr *) &sock.drone_addr,
            socklen
    );
    log_if_errno(errno, "send_command");
}

char *get_response(socket_t sock, settings_t settings)
{
    if (settings.fake_socket) {
        __log(INFO, "(debug) received \"OK\".\n");
        return my_strdup("OK");
    }
    __log(INFO, "waiting for a message ...\n");
    char *reply = malloc(sizeof(char) * (REPLY_SIZE + 1));
    unsigned int socklen = sizeof(sock.local_addr);
    int msg_size = recvfrom(
            sock.socket,
            reply,
            REPLY_SIZE,
            0,
            (struct sockaddr *) &sock.local_addr,
            &socklen
    );

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