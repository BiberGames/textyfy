#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
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

// Function to add a character to an existing buffer
void addToBuffer(char buffer[], size_t bufferSize, char newChar) {
    // Find the length of the existing buffer
    size_t len = strlen(buffer);

    // Check if there is enough space in the buffer
    if (len < bufferSize - 1) {
        // Add the new character to the buffer
        buffer[len] = newChar;
        buffer[len + 1] = '\0';  // Null-terminate the string
    } else {
        // Handle buffer overflow (optional)
        fprintf(stderr, "Buffer overflow. Cannot add more characters.\n");
    }
}

void getUserInput(char* userName)
{
    printf("%s || ", userName);
    if (fgets(userInputData, sizeof(userInputData), stdin) != NULL) {
        snprintf(buffer, sizeof(buffer), "%s || %s", userName, userInputData);
        //strcpy(userInputData, userName);
    }
}