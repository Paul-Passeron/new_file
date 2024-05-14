CC=gcc
CFLAGS=-Wall -Wextra -std=c99

all: new_file

new_file: new_file.c
	$(CC) $(CFLAGS) -o $@ $^

install:
	mv new_file /usr/bin/