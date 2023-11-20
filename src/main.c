#include <stdio.h>
#include <string.h>

#include "main.h"
#include "send.h"
#include "get.h"
#include "chat.h"

char *appendchar(char *szString, size_t strsize, char c)
{
    size_t len = strlen(szString);
    if((len+1) < strsize)
    {
        szString[len++] = c;
        szString[len] = '\0';
        return szString;
    }
    return NULL;
}

int main(int argc, char *argv[]) {
    if(argc < 1) {
        printf("Usage: %s <baseUrl> <text>", argv[0]);
        return 1;
    }

    int cPos = 0;

    userName = argv[1];
    baseUrl = argv[2];
    getUrl = argv[3];

    //pthread_create(&sendChat_thread, NULL, sendChat(userName, baseUrl, buffer), NULL);
    //pthread_join(sendChat(userName, baseUrl, buffer), NULL); 

    //set_nonblocking_mode();

    while (1)
    {
        getFromNtfy(getUrl);
        getUserInput(userName);
        sendToNtfy(baseUrl, buffer);
        /*if (is_input_available()) {
            int c = read_nonblocking_char();
            if (c != -1) {
                
                //printf("You pressed: %c\n", (char)c);

                appendchar(userInputData, sizeof(userInputData), (char)c);
                printf("%c", userInputData[cPos]);
                cPos ++;

                //snprintf(buffer, sizeof(buffer), "%c", (char)c);
                if (c == '\n') {
                    cPos = 0;
                    snprintf(buffer, sizeof(buffer), "%s || %s", userName, userInputData);
                    appendchar(buffer, sizeof(buffer), '\0\n');
                    sendToNtfy(baseUrl, buffer);
                    printf("%s", buffer);
                    memset(buffer, 0, sizeof(buffer));
                    memset(userInputData, 0, sizeof(userInputData));
                }
            }
        }*/


        //getUserInput(userName);
        //getFromNtfy(getUrl);
    }

    

    //restore_blocking_mode();

    return 0;
}