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

static struct termios set_raw(int *flags, struct termios tty_attr, struct termios old)
{
    *flags = fcntl(STDIN_FILENO, F_GETFL);
    log_if_errno(errno, "fcntl: getflags");
    *flags |= O_NONBLOCK;
    fcntl(STDIN_FILENO, F_SETFL, flags);
    log_if_errno(errno, "making stdin non blocking");

    //turn off buffering, echo and key processing.
    tty_attr = old;
    tty_attr.c_lflag &= ~(ICANON | ECHO | ISIG);
    tty_attr.c_lflag |= (CS8);
    tty_attr.c_iflag &=~(ISTRIP | INLCR | ICRNL | IGNCR | IXON | IXOFF);
    tcsetattr(STDIN_FILENO, TCSANOW, &tty_attr);
    return tty_attr;
}

int set_keyboard_mode(void)
{
    static int old_kb_mode = 0;
    static struct termios tty_attr_old;
    static bool is_raw_mode = false;
    struct termios tty_attr;
    int flags = 0;

    if (is_raw_mode) {
        tcsetattr(STDIN_FILENO, TCSAFLUSH, &tty_attr_old);
        ioctl(STDIN_FILENO, KDSKBMODE, old_kb_mode);
        log_if_errno(errno, "reseting keyboard mode.");
        is_raw_mode = false;
        return 0;
    } else if (!isatty(STDIN_FILENO)) {
        __log(ERROR, "not in a tty.\n");
        return -1;
    }
    tcgetattr(STDERR_FILENO, &tty_attr_old);
    tty_attr = set_raw(&flags, tty_attr, tty_attr_old);
    is_raw_mode = true;
    return 0;
}
