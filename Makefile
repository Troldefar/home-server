CC = gcc
CFLAGS = -Wall -Wextra -O2

SRC = src/main.c src/server.c src/router.c src/response.c
OBJ = $(SRC:.c=.o)

all: server

server: $(OBJ)
	$(CC) $(CFLAGS) -o server $(OBJ)

clean:
	rm -f server $(OBJ)
