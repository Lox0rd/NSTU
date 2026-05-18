CC = gcc

SRCS := $(wildcard *.c)

EXES := $(SRCS:.c=)

all: $(EXES) delete

delete:
	g++ -o delete delete.cpp

%: %.c
	$(CC) -o $@ $<

.PHONY: all
