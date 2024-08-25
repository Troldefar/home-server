#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "response.h"

void send_response(int client_fd, int status_code, const char *content_type, const char *body) {
    char header[256];
    snprintf(header, sizeof(header),
             "HTTP/1.1 %d OK\r\n"
             "Content-Type: %s\r\n"
             "Content-Length: %ld\r\n"
             "Connection: close\r\n\r\n",
             status_code, content_type, strlen(body));

    write(client_fd, header, strlen(header));
    write(client_fd, body, strlen(body));
}

void send_file_response(int client_fd, const char *filepath) {
    FILE *file = fopen(filepath, "r");
    if (!file) {
        send_response(client_fd, 404, "text/html", "<h1>404 File Not Found</h1>");
        return;
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    rewind(file);

    char *file_content = malloc(file_size + 1);
    fread(file_content, 1, file_size, file);
    file_content[file_size] = '\0';

    fclose(file);

    send_response(client_fd, 200, "text/html", file_content);
    free(file_content);
}

