#include <stdio.h>
#include <curl/curl.h>

#include "send.h"

// Callback function to discard received data
size_t discard_data_callback_send(void *contents, size_t size, size_t nmemb, void *userp) {
    // Return the size of the received data to indicate it has been processed (discarded)
    return size * nmemb;
}

void sendToNtfy(char* topic, char* post_data) {
    CURL *curl;
    CURLcode res;

    // Initialize cURL
    curl = curl_easy_init();
    
    if(curl) {
        // Set the URL for the request
        curl_easy_setopt(curl, CURLOPT_URL, topic);

        // Set the callback function to discard data
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, discard_data_callback_send);

        // Set the request type to POST
        curl_easy_setopt(curl, CURLOPT_POST, 1);

        // Set the data to be sent
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, post_data);


        // Perform the request
        res = curl_easy_perform(curl);

        // Check for errors
        if(res != CURLE_OK)
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));

        // Cleanup
        curl_easy_cleanup(curl);
    }
}