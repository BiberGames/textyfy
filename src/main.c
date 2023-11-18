#include <stdio.h>

#include "main.h"
#include "send.h"
#include "get.h"
#include "chat.h"

int main(int argc, char *argv[]) {
    if(argc < 1) {
        printf("Usage: %s <baseUrl> <text>", argv[0]);
        return 1;
    }

    userName = argv[1];
    baseUrl = argv[2];
    getUrl = argv[3];

    //pthread_create(&sendChat_thread, NULL, sendChat(userName, baseUrl, buffer), NULL);
    //pthread_join(sendChat(userName, baseUrl, buffer), NULL); 

    while (1)
    {
        getUserInput(userName);
        sendToNtfy(baseUrl, buffer);
        getFromNtfy(getUrl);
    }


    return 0;
}