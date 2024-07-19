CC = gcc
CFLAGS = -Wall -Werror

all: wgrep


wgrep: wgrep.o
	$(CC) $^ -o $@ $(OPTCFLAGSS)

%.o:%.c
	$(CC) -c $^ -o $@ $(CFLAGS)

.PHONY: clean

clean:
	rm -f wgrep.o wgrep
