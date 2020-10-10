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
#include <linux/input.h>

static int set_keyboard_mode(void)
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
    }

    // making stdin non blocking
    flags = fcntl(STDIN_FILENO, F_GETFL);
    flags |= O_NONBLOCK;
    fcntl(STDIN_FILENO, F_SETFL, flags);

    // saving old keyboard mode
    if (ioctl(STDIN_FILENO, KDGKBMODE, &old_kb_mode) < 0)
        return -1; // if ioctl fails here, it means the code isn't running through a terminal

    tcgetattr(STDIN_FILENO, &tty_attr_old);

    //turn off buffering, echo and key processing.
    tty_attr = tty_attr_old;
    tty_attr.c_lflag &= ~(ICANON | ECHO | ISIG);
    tty_attr.c_iflag &=~(ISTRIP | INLCR | ICRNL | IGNCR | IXON | IXOFF);
    tcsetattr(STDIN_FILENO, TCSANOW, &tty_attr);
    ioctl(STDIN_FILENO, KDSKBMODE, K_RAW);
    is_raw_mode = true;
    return 0;
}

char get_pressed_key(void)
{
    int status = 0;
    struct input_event inputs[64];
    char **commands = NULL;

    if (set_keyboard_mode() == -1) {
        __log(ERROR, "Couldn't set terminal in raw mode.\n");
        return 0;
    }
    do {
        status = read(STDIN_FILENO, &inputs, sizeof(inputs));
        commands = get_user_commands(inputs, status);
        status = execute_user_commands(commands);
    } while (status != -1);
    return set_keyboard_mode();
}
