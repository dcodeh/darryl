CC=gcc
CFLAGS=-Wall -Wextra -pedantic -std=c99 -ggdb

darryl.o: darryl.c darryl.h
	$(CC) -c darryl.c darryl.h $(CFLAGS)

test2: darryl.o test2.c
	$(CC) -o test2 darryl.o test2.c $(CFLAGS) -lgmp

test1: darryl.o test1.c
	$(CC) -o test1 darryl.o test1.c $(CFLAGS) -lgmp

clean: 
	-rm test
	-rm *.o
	-rm *.gch
