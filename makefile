CC=gcc
CFLAGS=-Wall -Wextra -pedantic -std=c99 -ggdb

test: darryl.o test.c
	$(CC) -o test darryl.o test.c $(CFLAGS)

darryl.o: darryl.c darryl.h
	$(CC) -c darryl.c darryl.h $(CFLAGS)

clean: 
	-rm test
	-rm *.o
	-rm *.gch
