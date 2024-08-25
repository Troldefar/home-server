#ifndef RESPONSE_H
#define RESPONSE_H

void send_response(int client_fd, int status_code, const char *content_type, const char *body);
void send_file_response(int client_fd, const char *filepath);

#endif

