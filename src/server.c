// src/server.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include "server.h"

int start_server(int port) {
    int server_fd;
    struct sockaddr_in address;

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket failed");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 10) < 0) {
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }

    return server_fd;
}

int accept_connection(int server_fd) {
    struct sockaddr_in client_address;
    socklen_t addr_len = sizeof(client_address);
    int client_fd = accept(server_fd, (struct sockaddr *)&client_address, &addr_len);
    if (client_fd < 0) {
        perror("Accept failed");
    }
    return client_fd;
}

