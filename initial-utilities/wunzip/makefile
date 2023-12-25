CC = gcc
CFLAGS = -Wall -Werror

all: wunzip

wcat: wunzip.o
	$(CC) $^ -o $@ $(CFLAGS)

%.o:%.c
	$(CC) -c $^ -o $@ $(CFLAGS)

.PHONY: clean

clean:
	rm -f wunzip.o wunzip
