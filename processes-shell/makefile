CC = gcc
CFLAGS = -Wall -Werror

all: wish

wish: wish.o parser.o
	$(CC) $^ -o $@ $(CFLAGS)

%.o:%.c
	$(CC) -c $^ -o $@ $(CFLAGS)

.PHONY: clean

clean:
	rm -f wish.o parser.o wish
