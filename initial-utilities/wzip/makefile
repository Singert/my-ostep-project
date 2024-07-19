CC = gcc
CFLAGS = -Wall -Werror

all: wzip

wcat: wzip.o
	$(CC) $^ -o $@ $(CFLAGS)

%.o:%.c
	$(CC) -c $^ -o $@ $(CFLAGS)

.PHONY: clean

clean:
	rm -f wzip.o wzip
