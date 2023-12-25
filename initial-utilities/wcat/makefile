CC = gcc
CFLAGS = -Wall -Werror

all: wcat

wcat: wcat.o
	$(CC) $^ -o $@ $(CFLAGS)

%.o:%.c
	$(CC) -c $^ -o $@ $(CFLAGS)

.PHONY: clean

clean:
	rm -f wcat.o wcat
