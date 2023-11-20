#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>

#include "chat.h"

#define ROWS getTerminalHeight()
#define COLUMNS getTerminalWidth()

void clearScreen() {
    printf("\033[H\033[J");  // ANSI escape sequence to clear the screen
}

int getTerminalHeight() {
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    return w.ws_row;
}

int getTerminalWidth() {
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    return w.ws_col;
}

// Set the terminal to non-blocking mode
void set_nonblocking_mode() {
    struct termios ttystate;

    // Get the terminal state
    tcgetattr(STDIN_FILENO, &ttystate);

    // Turn off canonical mode and echo
    ttystate.c_lflag &= ~ICANON;
    ttystate.c_lflag &= ~ECHO;

    // Set the new attributes
    tcsetattr(STDIN_FILENO, TCSANOW, &ttystate);
}

// Restore the terminal to blocking mode
void restore_blocking_mode() {
    struct termios ttystate;

    // Get the terminal state
    tcgetattr(STDIN_FILENO, &ttystate);

    // Turn on canonical mode and echo
    ttystate.c_lflag |= ICANON;
    ttystate.c_lflag |= ECHO;

    // Set the new attributes
    tcsetattr(STDIN_FILENO, TCSANOW, &ttystate);
}

// Check if there is input available
int is_input_available() {
    fd_set fds;
    struct timeval timeout;

    FD_ZERO(&fds);
    FD_SET(STDIN_FILENO, &fds);

    timeout.tv_sec = 0;
    timeout.tv_usec = 0;

    return select(STDIN_FILENO + 1, &fds, NULL, NULL, &timeout) > 0;
}

// Read a non-blocking character from the user
int read_nonblocking_char() {
    char ch;
    int n = read(STDIN_FILENO, &ch, 1);

    if (n == 1) {
        return ch;
    }

    return -1; // No input available
}

void getUserInput(char* userName)
{
    printf("%s || ", userName);
    if (fgets(userInputData, sizeof(userInputData), stdin) != NULL) {
        snprintf(buffer, sizeof(buffer), "%s || %s", userName, userInputData);
        //strcpy(userInputData, userName);
    }
}