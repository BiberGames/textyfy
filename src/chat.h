int getTerminalHeight();
int getTerminalWidth();
void set_nonblocking_mode();
void restore_blocking_mode();
int is_input_available();
int read_nonblocking_char();
void addToBuffer(char buffer[], size_t bufferSize, char newChar);
void getUserInput(char* userName);
char buffer[1024];
char userInputData[1024];