CC=gcc
CFLAGS=-Wall -Wextra -pedantic -std=c99 -ggdb

test: darryl.o test.c
	$(CC) -o test darryl.o test.c $(CFLAGS)

darryl.o: darryl.c darryl.h
	$(CC) -c darryl.c darryl.h $(CFLAGS)

test2: darryl.o test2.c
	$(CC) -o test2 darryl.o test2.c $(CFLAGS) -lgmp

test3: darryl.o test3.c
	$(CC) -o test3 darryl.o test3.c $(CFLAGS) -lgmp

clean: 
	-rm test
	-rm *.o
	-rm *.gch
