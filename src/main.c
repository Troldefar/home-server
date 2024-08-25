#include <stdio.h>
#include <stdlib.h>
#include "server.h"
#include "router.h"

int main() {
    int port = 8080;
    int server_fd = start_server(port);

    if (server_fd < 0) {
        perror("Failed to start server");
        return 1;
    }

    printf("Server running on port %d\n", port);

    while (1) {
        int client_fd = accept_connection(server_fd);
        if (client_fd < 0) {
            perror("Failed to accept connection");
            continue;
        }

        handle_request(client_fd);
        close(client_fd);
    }

    close(server_fd);
    return 0;
}

