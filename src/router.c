#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "router.h"
#include "response.h"

void handle_request(int client_fd) {
    // Baby don't hurt me
    char buffer[1024] = {0};
    read(client_fd, buffer, 1024);

    // Simple request parsing
    if (strncmp(buffer, "GET / ", 6) == 0) {
        send_response(client_fd, 200, "text/html", "<h1>Welcome to the Home Page</h1>");
    } else if (strncmp(buffer, "GET /static/index.html", 22) == 0) {
        send_file_response(client_fd, "static/index.html");
    } else {
        send_response(client_fd, 404, "text/html", "<h1>404 Not Found</h1>");
    }
}

