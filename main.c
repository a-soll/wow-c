#include "utility.h"
#include <curl/curl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "creds.c" // provides client and secred

int main() {
    CURL *curl_handle;
    CURLcode res;
    char url[] = "https://us.battle.net/oauth/token";
    char buffer[200];

    struct MemoryStruct chunk;
    chunk.memory = malloc(1);
    chunk.size = 0;

    struct curl_slist *list = NULL;

    curl_handle = curl_easy_init();
    // list = curl_slist_append(list, "Content-Type: application/json");
    // list = curl_slist_append(list, "Accept: application/json");
    if (curl_handle) {
        const char* data = "grant_type=client_credentials";
        curl_easy_setopt(curl_handle, CURLOPT_URL, url);
        curl_easy_setopt(curl_handle, CURLOPT_CUSTOMREQUEST, "POST");
        curl_easy_setopt(curl_handle, CURLOPT_USERNAME, client);
        curl_easy_setopt(curl_handle, CURLOPT_PASSWORD, secret);
        curl_easy_setopt(curl_handle, CURLOPT_POSTFIELDS, data);
        curl_easy_setopt(curl_handle, CURLOPT_FOLLOWLOCATION, 1L);
        curl_easy_setopt(curl_handle,CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
        curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, (void *)&chunk);
        curl_easy_setopt(curl_handle, CURLOPT_USERAGENT, "libcurl-agent/1.0");

        res = curl_easy_perform(curl_handle);

        if (res != CURLE_OK) {
            fprintf(stderr, "error: %s\n", curl_easy_strerror(res));
        }
        else {
            printf("Size: %lu\n", (unsigned long)chunk.size);
            printf("Data: %s\n", chunk.memory);
        }
        curl_easy_cleanup(curl_handle);
        free(chunk.memory);
    }
    return 0;
}
