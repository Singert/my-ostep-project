CC := gcc
CFLAGS := -Wall -Werror -g

SRCDIR := src
OBJDIR := obj

SRC := $(wildcard $(SRCDIR)/*.c)
OBJ := $(SRC:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

.PHONY: clean all

all: $(OBJDIR) wish

wish: $(OBJ)
	$(CC) $^ -o $@ $(CFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) -c $< -o $@ $(CFLAGS)

$(OBJDIR):
	mkdir -p $@

clean:
	rm -rf wish $(OBJDIR)