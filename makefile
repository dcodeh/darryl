CC=gcc
CFLAGS=-Wall -Wextra -pedantic -std=c99 -ggdb

darryl-dev: darryl.c darryl.h
	$(CC) -o darryl darryl.c darryl.h $(CFLAGS)
