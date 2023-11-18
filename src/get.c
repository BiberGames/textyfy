#include <stdio.h>
#include <curl/curl.h>

#include "get.h"

// Callback function to write received data to stdout
size_t write_data_callback(void *ptr, size_t size, size_t nmemb, void *stream) {
    size_t written = fwrite(ptr, size, nmemb, stdout);
    return written;
}

void getFromNtfy(char* topic) {
   // Initialize libcurl
    CURLcode init_res = curl_global_init(CURL_GLOBAL_DEFAULT);
    if (init_res != CURLE_OK) {
        fprintf(stderr, "Failed to initialize cURL: %s\n", curl_easy_strerror(init_res));
        return;
    }

    // Create a cURL handle
    CURL *curl = curl_easy_init();
    if (!curl) {
        fprintf(stderr, "Failed to initialize cURL handle.\n");
        curl_global_cleanup();
        return;
    }

    // Set the URL for the request
    curl_easy_setopt(curl, CURLOPT_URL, topic);

    // Set the callback function to write received data to stdout
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data_callback);

    // Set the cURL handle to non-blocking mode
    curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 1L);
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, 1L);

    // Create multi handle
    CURLM *multi_handle = curl_multi_init();

    // Add the easy handle to the multi handle
    curl_multi_add_handle(multi_handle, curl);

    int still_running;

    // Perform the non-blocking request
    do {
        curl_multi_perform(multi_handle, &still_running);

        // Wait for activity, timeout or "nothing" to be done
        if (curl_multi_wait(multi_handle, NULL, 0, 1000, NULL) != CURLM_OK) {
            fprintf(stderr, "curl_multi_wait() failed.\n");
            break;
        }
    } while (still_running);

    // Clean up
    curl_multi_remove_handle(multi_handle, curl);
    curl_easy_cleanup(curl);
    curl_multi_cleanup(multi_handle);

    // Cleanup global state
    curl_global_cleanup();

    return;
}