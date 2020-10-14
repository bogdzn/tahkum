/**
 * \file key_listener.c
 * \brief implements getch from ncurses without using initscr() !
 * \author Bogdan G.
 * \date 09/10/2020
 */

#include "utils.h"
#include "parser.h"
#include <linux/input-event-codes.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/select.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <linux/kd.h>
#include <termios.h>
#include "exec.h"
#include <linux/input.h>

int set_keyboard_mode(void)
{
    static int old_kb_mode = 0;
    static struct termios tty_attr_old;
    static bool is_raw_mode = false;
    struct termios tty_attr;
    int flags = 0;

    // resetting keyboard mode
    if (is_raw_mode) {
        tcsetattr(STDIN_FILENO, TCSAFLUSH, &tty_attr_old);
        ioctl(STDIN_FILENO, KDSKBMODE, old_kb_mode);
        is_raw_mode = false;
        return 0;
    } else if (!isatty(STDIN_FILENO)) {
        __log(ERROR, "not in a tty.\n");
        return -1;
    }

    // making stdin non blocking
    flags = fcntl(STDIN_FILENO, F_GETFL);
    log_if_errno(errno, "fcntl: getflags");
    flags |= O_NONBLOCK;
    fcntl(STDIN_FILENO, F_SETFL, flags);
    log_if_errno(errno, "making stdin non blocking");

    tcgetattr(STDIN_FILENO, &tty_attr_old);

    //turn off buffering, echo and key processing.
    tty_attr = tty_attr_old;
    tty_attr.c_lflag &= ~(ICANON | ECHO | ISIG);
    tty_attr.c_lflag |= (CS8);
    tty_attr.c_iflag &=~(ISTRIP | INLCR | ICRNL | IGNCR | IXON | IXOFF);
    tcsetattr(STDIN_FILENO, TCSANOW, &tty_attr);
    is_raw_mode = true;
    return 0;
}

int loop_wrapper(socket_t ryze, settings_t settings)
{
    int status = 0;
    char **commands = NULL;
    char buffer = 0;

    if (set_keyboard_mode() == -1) {
        __log(ERROR, "Couldn't set terminal in raw mode.\n");
        return 0;
    }
    send_startup_commands(ryze, settings);
    while (status != 1) {
        do {
            usleep(75000);
            status = read(STDIN_FILENO, &buffer, 1);
        } while (status < 0);
        buffer = (buffer >= 'A' && buffer <= 'Z') ? buffer + 32 : buffer;
        if (buffer == 'c') {
            send_command(ryze, "land", settings);
            __log(WARNING, "c has been triggered. Exiting.\n");
            break;
        }
        commands = get_user_commands(buffer, status);
        status = (status == -1) ? status : exec_loop(ryze, settings, commands);
    }
    return set_keyboard_mode();
}
